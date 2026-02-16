#include "util.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) fatal("Cannot open file: %s", path);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = xmalloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    return buf;
}

/* Simple #define macro table */
typedef struct {
    char *name;
    char *value;
} Macro;

static Macro macros[256];
static int nmacros;

static void add_macro(const char *name, const char *value) {
    /* Overwrite if exists */
    for (int i = 0; i < nmacros; i++) {
        if (strcmp(macros[i].name, name) == 0) {
            free(macros[i].value);
            macros[i].value = xstrdup(value);
            return;
        }
    }
    macros[nmacros].name = xstrdup(name);
    macros[nmacros].value = xstrdup(value);
    nmacros++;
}

static int is_ident_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

static char *expand_macros(const char *src) {
    if (nmacros == 0) return xstrdup(src);
    Buf b;
    buf_init(&b);
    int len = strlen(src);
    int i = 0;
    while (i < len) {
        /* Skip string literals */
        if (src[i] == '"') {
            buf_push(&b, src[i++]);
            while (i < len && src[i] != '"') {
                if (src[i] == '\\' && i + 1 < len) {
                    buf_push(&b, src[i++]);
                }
                buf_push(&b, src[i++]);
            }
            if (i < len) buf_push(&b, src[i++]);
            continue;
        }
        /* Skip char literals */
        if (src[i] == '\'') {
            buf_push(&b, src[i++]);
            while (i < len && src[i] != '\'') {
                if (src[i] == '\\' && i + 1 < len) {
                    buf_push(&b, src[i++]);
                }
                buf_push(&b, src[i++]);
            }
            if (i < len) buf_push(&b, src[i++]);
            continue;
        }
        /* Try to match an identifier */
        if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z') || src[i] == '_') {
            int start = i;
            while (i < len && is_ident_char(src[i])) i++;
            int ilen = i - start;
            /* Check against macros */
            int found = 0;
            for (int m = 0; m < nmacros; m++) {
                if ((int)strlen(macros[m].name) == ilen &&
                    strncmp(src + start, macros[m].name, ilen) == 0) {
                    buf_append(&b, macros[m].value);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                for (int k = start; k < i; k++) buf_push(&b, src[k]);
            }
            continue;
        }
        buf_push(&b, src[i++]);
    }
    return buf_detach(&b);
}

static char *strip_preprocessor(const char *src) {
    nmacros = 0;
    Buf b;
    buf_init(&b);
    const char *p = src;
    while (*p) {
        /* Find start of line */
        const char *line_start = p;
        /* Skip leading whitespace */
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#') {
            p++; /* skip '#' */
            while (*p == ' ' || *p == '\t') p++;
            /* Check for #define */
            if (strncmp(p, "define", 6) == 0 && (p[6] == ' ' || p[6] == '\t')) {
                p += 6;
                while (*p == ' ' || *p == '\t') p++;
                /* Read macro name */
                const char *name_start = p;
                while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '(') p++;
                int name_len = p - name_start;
                char *name = xmalloc(name_len + 1);
                memcpy(name, name_start, name_len);
                name[name_len] = '\0';
                /* Skip function-like macros (with parentheses) */
                if (*p == '(') {
                    /* Skip entire line */
                    while (*p && *p != '\n') p++;
                    free(name);
                } else {
                    /* Read value (rest of line, trimmed) */
                    while (*p == ' ' || *p == '\t') p++;
                    const char *val_start = p;
                    while (*p && *p != '\n') p++;
                    /* Trim trailing whitespace */
                    const char *val_end = p;
                    while (val_end > val_start && (val_end[-1] == ' ' || val_end[-1] == '\t')) val_end--;
                    int val_len = val_end - val_start;
                    char *value = xmalloc(val_len + 1);
                    memcpy(value, val_start, val_len);
                    value[val_len] = '\0';
                    add_macro(name, value);
                    free(name);
                    free(value);
                }
            } else {
                /* Skip entire line (other preprocessor directives) */
                while (*p && *p != '\n') p++;
            }
            if (*p == '\n') {
                buf_push(&b, '\n');
                p++;
            }
        } else {
            /* Copy entire line */
            p = line_start;
            while (*p && *p != '\n') {
                buf_push(&b, *p);
                p++;
            }
            if (*p == '\n') {
                buf_push(&b, '\n');
                p++;
            }
        }
    }
    char *stripped = buf_detach(&b);
    char *expanded = expand_macros(stripped);
    free(stripped);
    return expanded;
}

static char *change_extension(const char *path, const char *new_ext) {
    int len = strlen(path);
    /* Find last '.' */
    int dot = -1;
    for (int i = len - 1; i >= 0; i--) {
        if (path[i] == '.') { dot = i; break; }
        if (path[i] == '/') break;
    }
    Buf b;
    buf_init(&b);
    if (dot >= 0) {
        for (int i = 0; i < dot; i++) buf_push(&b, path[i]);
    } else {
        buf_append(&b, path);
    }
    buf_append(&b, new_ext);
    return buf_detach(&b);
}

static int has_extension(const char *path, const char *ext) {
    int plen = strlen(path);
    int elen = strlen(ext);
    if (plen < elen) return 0;
    return strcmp(path + plen - elen, ext) == 0;
}

/* Compile a .c file to a .o file. Returns the .o path (allocated). */
static char *compile_c_to_o(const char *c_path) {
    char *src = read_file(c_path);
    char *cleaned = strip_preprocessor(src);

    TokArray toks = lex(cleaned);
    Program *prog = parse_program(toks);
    char *asm_str = codegen_generate(prog);

    char *s_path = change_extension(c_path, ".s");
    FILE *sf = fopen(s_path, "w");
    if (!sf) fatal("Cannot write %s", s_path);
    fputs(asm_str, sf);
    fclose(sf);

    char *o_path = change_extension(c_path, ".o");
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "clang -c %s -o %s", s_path, o_path);
    int rc = system(cmd);
    if (rc != 0) fatal("clang assembly failed for %s", c_path);

    fprintf(stderr, "Compiled %s -> %s\n", c_path, o_path);
    return o_path;
}

/* Link a list of .o files into an executable. */
static void link_objects(char **o_paths, int count, const char *out_path) {
    Buf cmd;
    buf_init(&cmd);
    buf_append(&cmd, "clang");
    for (int i = 0; i < count; i++) {
        buf_append(&cmd, " ");
        buf_append(&cmd, o_paths[i]);
    }
    buf_append(&cmd, " -o ");
    buf_append(&cmd, out_path);
    char *cmd_str = buf_detach(&cmd);
    int rc = system(cmd_str);
    if (rc != 0) fatal("clang linking failed");
    fprintf(stderr, "Linked -> %s\n", out_path);
}

int main(int argc, char **argv) {
    const char *out_path = NULL;
    int cflag = 0;
    char **inputs = NULL;
    int ninputs = 0;
    int icap = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) fatal("Missing argument for -o");
            out_path = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            cflag = 1;
        } else if (argv[i][0] == '-') {
            fatal("Unknown option: %s", argv[i]);
        } else {
            if (ninputs >= icap) {
                icap = icap ? icap * 2 : 8;
                inputs = realloc(inputs, icap * sizeof(char *));
            }
            inputs[ninputs++] = argv[i];
        }
    }

    if (ninputs == 0) {
        fprintf(stderr, "Usage: cc [-c] [-o output] file1.c [file2.c ...] [file1.o ...]\n");
        return 2;
    }

    /* Validate -c usage */
    if (cflag) {
        for (int i = 0; i < ninputs; i++) {
            if (has_extension(inputs[i], ".o"))
                fatal("-c cannot be used with .o input: %s", inputs[i]);
        }
        if (out_path && ninputs > 1)
            fatal("-c with -o only valid for a single input file");
    }

    if (cflag) {
        /* Compile-only mode */
        for (int i = 0; i < ninputs; i++) {
            char *o_path = compile_c_to_o(inputs[i]);
            /* If -o was specified (single input), rename */
            if (out_path) {
                char cmd[4096];
                snprintf(cmd, sizeof(cmd), "mv %s %s", o_path, out_path);
                system(cmd);
            }
            free(o_path);
        }
    } else {
        /* Compile .c files and collect all .o paths */
        char **o_paths = xmalloc(ninputs * sizeof(char *));
        int no_paths = 0;

        for (int i = 0; i < ninputs; i++) {
            if (has_extension(inputs[i], ".c")) {
                o_paths[no_paths++] = compile_c_to_o(inputs[i]);
            } else if (has_extension(inputs[i], ".o")) {
                o_paths[no_paths++] = xstrdup(inputs[i]);
            } else {
                fatal("Unknown file type: %s (expected .c or .o)", inputs[i]);
            }
        }

        /* Default output name */
        if (!out_path) out_path = "a.out";

        link_objects(o_paths, no_paths, out_path);
    }

    return 0;
}
