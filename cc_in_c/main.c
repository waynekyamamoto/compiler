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
    char *value;       /* object-like replacement text */
    char **params;     /* NULL for object-like; param names for function-like */
    int nparams;       /* -1 = object-like, >=0 = function-like */
    char *body;        /* replacement body for function-like */
    int is_variadic;   /* 1 if last param is ... (__VA_ARGS__) */
    int expanding;     /* 1 if currently being expanded (prevent recursion) */
} Macro;

static Macro *macros;
static int nmacros;
static int macros_cap;

static void add_macro(const char *name, const char *value) {
    /* Overwrite if exists */
    for (int i = 0; i < nmacros; i++) {
        if (strcmp(macros[i].name, name) == 0) {
            free(macros[i].value);
            macros[i].value = xstrdup(value);
            return;
        }
    }
    GROW(macros, nmacros, macros_cap, Macro);
    macros[nmacros].name = xstrdup(name);
    macros[nmacros].value = xstrdup(value);
    macros[nmacros].params = NULL;
    macros[nmacros].nparams = -1;
    macros[nmacros].body = NULL;
    macros[nmacros].is_variadic = 0;
    macros[nmacros].expanding = 0;
    nmacros++;
}

static void add_func_macro(const char *name, char **params, int nparams, const char *body, int is_variadic) {
    /* Overwrite if exists */
    for (int i = 0; i < nmacros; i++) {
        if (strcmp(macros[i].name, name) == 0) {
            macros[i].params = params;
            macros[i].nparams = nparams;
            free(macros[i].body);
            macros[i].body = xstrdup(body);
            macros[i].value = NULL;
            macros[i].is_variadic = is_variadic;
            return;
        }
    }
    GROW(macros, nmacros, macros_cap, Macro);
    macros[nmacros].name = xstrdup(name);
    macros[nmacros].value = NULL;
    macros[nmacros].params = params;
    macros[nmacros].nparams = nparams;
    macros[nmacros].body = xstrdup(body);
    macros[nmacros].is_variadic = is_variadic;
    macros[nmacros].expanding = 0;
    nmacros++;
}

static int is_ident_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

/* Substitute params in function-like macro body with args */
static char *subst_macro_params(const Macro *m, char **args, int nargs) {
    Buf b;
    buf_init(&b);
    const char *body = m->body;
    int blen = strlen(body);
    int i = 0;
    while (i < blen) {
        /* ## token pasting: remove whitespace around ## and concatenate */
        if (body[i] == '#' && i + 1 < blen && body[i+1] == '#') {
            /* Remove trailing whitespace from buffer */
            while (b.len > 0 && (b.data[b.len-1] == ' ' || b.data[b.len-1] == '\t'))
                b.len--;
            i += 2;
            /* Skip leading whitespace after ## */
            while (i < blen && (body[i] == ' ' || body[i] == '\t')) i++;
            continue;
        }
        /* # stringification */
        if (body[i] == '#' && i + 1 < blen && body[i+1] != '#') {
            i++;
            while (i < blen && (body[i] == ' ' || body[i] == '\t')) i++;
            if (i < blen && is_ident_char(body[i])) {
                int start = i;
                while (i < blen && is_ident_char(body[i])) i++;
                int ilen = i - start;
                int found = 0;
                for (int p = 0; p < m->nparams; p++) {
                    if ((int)strlen(m->params[p]) == ilen &&
                        strncmp(body + start, m->params[p], ilen) == 0) {
                        buf_push(&b, '"');
                        if (p < nargs) {
                            /* Escape quotes and backslashes in the arg */
                            const char *a = args[p];
                            while (*a) {
                                if (*a == '"' || *a == '\\') buf_push(&b, '\\');
                                buf_push(&b, *a);
                                a++;
                            }
                        }
                        buf_push(&b, '"');
                        found = 1;
                        break;
                    }
                }
                /* Check __VA_ARGS__ for # */
                if (!found && m->is_variadic && ilen == 11 &&
                    strncmp(body + start, "__VA_ARGS__", 11) == 0) {
                    buf_push(&b, '"');
                    for (int a = m->nparams; a < nargs; a++) {
                        if (a > m->nparams) buf_append(&b, ", ");
                        const char *s = args[a];
                        while (*s) {
                            if (*s == '"' || *s == '\\') buf_push(&b, '\\');
                            buf_push(&b, *s);
                            s++;
                        }
                    }
                    buf_push(&b, '"');
                    found = 1;
                }
                if (!found) {
                    buf_push(&b, '#');
                    for (int k = start; k < i; k++) buf_push(&b, body[k]);
                }
            } else {
                buf_push(&b, '#');
            }
            continue;
        }
        if (is_ident_char(body[i]) && (i == 0 || !is_ident_char(body[i-1]))) {
            int start = i;
            while (i < blen && is_ident_char(body[i])) i++;
            int ilen = i - start;
            int found = 0;
            /* Check named params */
            for (int p = 0; p < m->nparams; p++) {
                if ((int)strlen(m->params[p]) == ilen &&
                    strncmp(body + start, m->params[p], ilen) == 0) {
                    if (p < nargs)
                        buf_append(&b, args[p]);
                    found = 1;
                    break;
                }
            }
            /* Check __VA_ARGS__ */
            if (!found && m->is_variadic && ilen == 11 &&
                strncmp(body + start, "__VA_ARGS__", 11) == 0) {
                for (int a = m->nparams; a < nargs; a++) {
                    if (a > m->nparams) buf_append(&b, ", ");
                    buf_append(&b, args[a]);
                }
                found = 1;
            }
            if (!found) {
                for (int k = start; k < i; k++) buf_push(&b, body[k]);
            }
        } else {
            buf_push(&b, body[i++]);
        }
    }
    return buf_detach(&b);
}

static char *expand_macros(const char *src);

/* Parse function-like macro arguments from src starting at position *pos (after '(')
   Returns array of argument strings, sets *nargs */
static char **parse_macro_args(const char *src, int len, int *pos, int *nargs) {
    char **args = xmalloc(16 * sizeof(char *));
    int cap = 16;
    *nargs = 0;
    int depth = 1;
    int i = *pos;
    Buf arg;
    buf_init(&arg);
    while (i < len && depth > 0) {
        if (src[i] == '(') depth++;
        else if (src[i] == ')') {
            depth--;
            if (depth == 0) { i++; break; }
        } else if (src[i] == ',' && depth == 1) {
            /* End of this argument */
            if (*nargs >= cap) {
                cap *= 2;
                args = realloc(args, cap * sizeof(char *));
            }
            args[(*nargs)++] = buf_detach(&arg);
            buf_init(&arg);
            i++;
            /* skip leading whitespace in next arg */
            while (i < len && (src[i] == ' ' || src[i] == '\t')) i++;
            continue;
        } else if (src[i] == '"') {
            /* String literal in macro arg */
            buf_push(&arg, src[i++]);
            while (i < len && src[i] != '"') {
                if (src[i] == '\\' && i + 1 < len)
                    buf_push(&arg, src[i++]);
                buf_push(&arg, src[i++]);
            }
            if (i < len) buf_push(&arg, src[i++]);
            continue;
        } else if (src[i] == '\'') {
            buf_push(&arg, src[i++]);
            while (i < len && src[i] != '\'') {
                if (src[i] == '\\' && i + 1 < len)
                    buf_push(&arg, src[i++]);
                buf_push(&arg, src[i++]);
            }
            if (i < len) buf_push(&arg, src[i++]);
            continue;
        }
        buf_push(&arg, src[i++]);
    }
    /* Last argument (or only argument for zero-param macros) */
    char *last = buf_detach(&arg);
    if (*nargs > 0 || strlen(last) > 0) {
        if (*nargs >= cap) {
            cap *= 2;
            args = realloc(args, cap * sizeof(char *));
        }
        args[(*nargs)++] = last;
    } else {
        free(last);
    }
    *pos = i;
    return args;
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
                    if (macros[m].expanding) {
                        break;
                    }
                    if (macros[m].nparams >= 0) {
                        /* Function-like macro: need '(' */
                        int j = i;
                        while (j < len && (src[j] == ' ' || src[j] == '\t')) j++;
                        if (j < len && src[j] == '(') {
                            j++; /* skip '(' */
                            int nargs = 0;
                            char **args = parse_macro_args(src, len, &j, &nargs);
                            /* Expand each argument before substitution */
                            for (int a = 0; a < nargs; a++) {
                                char *exp_arg = expand_macros(args[a]);
                                free(args[a]);
                                args[a] = exp_arg;
                            }
                            char *subst = subst_macro_params(&macros[m], args, nargs);
                            /* Rescan with self-reference protection */
                            macros[m].expanding = 1;
                            char *expanded = expand_macros(subst);
                            macros[m].expanding = 0;
                            buf_append(&b, expanded);
                            free(subst);
                            free(expanded);
                            for (int a = 0; a < nargs; a++) free(args[a]);
                            free(args);
                            i = j;
                            found = 1;
                            break;
                        }
                        /* No '(' follows — not a macro invocation, copy as-is */
                    } else {
                        /* Object-like macro — recursively expand */
                        macros[m].expanding = 1;
                        char *expanded = expand_macros(macros[m].value);
                        macros[m].expanding = 0;
                        buf_append(&b, expanded);
                        free(expanded);
                        found = 1;
                        break;
                    }
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

static int is_macro_defined(const char *name) {
    for (int i = 0; i < nmacros; i++) {
        if (strcmp(macros[i].name, name) == 0) return 1;
    }
    return 0;
}

/* Extract directory part of a file path */
static char *get_dir_from_path(const char *path) {
    int len = strlen(path);
    int last_slash = -1;
    for (int i = len - 1; i >= 0; i--) {
        if (path[i] == '/') { last_slash = i; break; }
    }
    if (last_slash < 0) return xstrdup(".");
    char *dir = xmalloc(last_slash + 2);
    memcpy(dir, path, last_slash + 1);
    dir[last_slash + 1] = '\0';
    return dir;
}

/* Concatenate directory and filename */
static char *concat_paths(const char *dir, const char *file) {
    Buf b;
    buf_init(&b);
    buf_append(&b, dir);
    int dlen = strlen(dir);
    if (dlen > 0 && dir[dlen - 1] != '/') buf_push(&b, '/');
    buf_append(&b, file);
    return buf_detach(&b);
}

/* If-stack for conditional compilation */
typedef struct {
    int including;
    int seen_else;
    int satisfied;  /* has any branch been taken? */
} IfState;

static IfState if_stack[32];
static int if_depth;

/* Recursive descent #if expression evaluator */
static const char *ifex;  /* current position in expression string */

static void ifex_skip_ws(void) {
    while (*ifex == ' ' || *ifex == '\t') ifex++;
}

static int ifex_parse_or(void);

static int ifex_parse_num(void) {
    int val = 0;
    if (ifex[0] == '0' && (ifex[1] == 'x' || ifex[1] == 'X')) {
        ifex += 2;
        while ((*ifex >= '0' && *ifex <= '9') || (*ifex >= 'a' && *ifex <= 'f') || (*ifex >= 'A' && *ifex <= 'F')) {
            int d;
            if (*ifex >= '0' && *ifex <= '9') d = *ifex - '0';
            else if (*ifex >= 'a' && *ifex <= 'f') d = *ifex - 'a' + 10;
            else d = *ifex - 'A' + 10;
            val = val * 16 + d;
            ifex++;
        }
    } else {
        while (*ifex >= '0' && *ifex <= '9') {
            val = val * 10 + (*ifex - '0');
            ifex++;
        }
    }
    return val;
}

static int ifex_parse_primary(void) {
    ifex_skip_ws();
    /* defined(NAME) */
    if (strncmp(ifex, "defined", 7) == 0 && !is_ident_char(ifex[7])) {
        ifex += 7;
        ifex_skip_ws();
        if (*ifex == '(') {
            ifex++;
            ifex_skip_ws();
            const char *ns = ifex;
            while (*ifex && is_ident_char(*ifex)) ifex++;
            int nlen = ifex - ns;
            char *name = xmalloc(nlen + 1);
            memcpy(name, ns, nlen);
            name[nlen] = '\0';
            ifex_skip_ws();
            if (*ifex == ')') ifex++;
            int result = is_macro_defined(name);
            free(name);
            return result;
        }
    }
    /* Parenthesized expression */
    if (*ifex == '(') {
        ifex++;
        int val = ifex_parse_or();
        ifex_skip_ws();
        if (*ifex == ')') ifex++;
        return val;
    }
    /* Number */
    if (*ifex >= '0' && *ifex <= '9') {
        return ifex_parse_num();
    }
    /* Identifier: look up as macro value, default to 0 */
    if (is_ident_char(*ifex) && !(*ifex >= '0' && *ifex <= '9')) {
        const char *ns = ifex;
        while (*ifex && is_ident_char(*ifex)) ifex++;
        int nlen = ifex - ns;
        char *name = xmalloc(nlen + 1);
        memcpy(name, ns, nlen);
        name[nlen] = '\0';
        /* Look up macro value */
        for (int i = 0; i < nmacros; i++) {
            if (strcmp(macros[i].name, name) == 0 && macros[i].value) {
                free(name);
                return atoi(macros[i].value);
            }
        }
        free(name);
        return 0; /* undefined identifier = 0 per C standard */
    }
    return 0;
}

static int ifex_parse_unary(void) {
    ifex_skip_ws();
    if (*ifex == '!') { ifex++; return !ifex_parse_unary(); }
    if (*ifex == '-') { ifex++; return -ifex_parse_unary(); }
    if (*ifex == '~') { ifex++; return ~ifex_parse_unary(); }
    return ifex_parse_primary();
}

static int ifex_parse_mul(void) {
    int val = ifex_parse_unary();
    while (1) {
        ifex_skip_ws();
        if (*ifex == '*') { ifex++; val *= ifex_parse_unary(); }
        else if (*ifex == '/' && ifex[1] != '/') { ifex++; int r = ifex_parse_unary(); val = r ? val / r : 0; }
        else break;
    }
    return val;
}

static int ifex_parse_add(void) {
    int val = ifex_parse_mul();
    while (1) {
        ifex_skip_ws();
        if (*ifex == '+') { ifex++; val += ifex_parse_mul(); }
        else if (*ifex == '-') { ifex++; val -= ifex_parse_mul(); }
        else break;
    }
    return val;
}

static int ifex_parse_shift(void) {
    int val = ifex_parse_add();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '<' && ifex[1] == '<') { ifex += 2; val <<= ifex_parse_add(); }
        else if (ifex[0] == '>' && ifex[1] == '>' && ifex[2] != '=') { ifex += 2; val >>= ifex_parse_add(); }
        else break;
    }
    return val;
}

static int ifex_parse_rel(void) {
    int val = ifex_parse_shift();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '<' && ifex[1] == '=') { ifex += 2; val = val <= ifex_parse_shift(); }
        else if (ifex[0] == '>' && ifex[1] == '=') { ifex += 2; val = val >= ifex_parse_shift(); }
        else if (ifex[0] == '<' && ifex[1] != '<') { ifex++; val = val < ifex_parse_shift(); }
        else if (ifex[0] == '>' && ifex[1] != '>') { ifex++; val = val > ifex_parse_shift(); }
        else break;
    }
    return val;
}

static int ifex_parse_eq(void) {
    int val = ifex_parse_rel();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '=' && ifex[1] == '=') { ifex += 2; val = val == ifex_parse_rel(); }
        else if (ifex[0] == '!' && ifex[1] == '=') { ifex += 2; val = val != ifex_parse_rel(); }
        else break;
    }
    return val;
}

static int ifex_parse_bitor(void) {
    int val = ifex_parse_eq();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '|' && ifex[1] != '|') { ifex++; val |= ifex_parse_eq(); }
        else break;
    }
    return val;
}

static int ifex_parse_and(void) {
    int val = ifex_parse_bitor();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '&' && ifex[1] == '&') { ifex += 2; int rhs = ifex_parse_bitor(); val = val && rhs; }
        else break;
    }
    return val;
}

static int ifex_parse_or(void) {
    int val = ifex_parse_and();
    while (1) {
        ifex_skip_ws();
        if (ifex[0] == '|' && ifex[1] == '|') { ifex += 2; int rhs = ifex_parse_and(); val = val || rhs; }
        else break;
    }
    return val;
}

static int eval_if_expr(const char *expr) {
    ifex = expr;
    return ifex_parse_or();
}

/* Check if currently including (all levels of if_stack are including) */
static int pp_is_including(void) {
    for (int i = 0; i < if_depth; i++) {
        if (!if_stack[i].including) return 0;
    }
    return 1;
}

/* Include search paths for #include <...> */
static char **include_paths;
static int ninclude_paths;
static int include_paths_cap;

static void preprocess_file(const char *src, const char *filepath, int depth, Buf *b);

static void preprocess_file(const char *src, const char *filepath, int depth, Buf *b) {
    if (depth > 32) fatal("Include depth exceeded (max 32)");
    char *dir = get_dir_from_path(filepath);
    const char *p = src;
    while (*p) {
        const char *line_start = p;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#') {
            p++;
            while (*p == ' ' || *p == '\t') p++;

            /* #ifdef */
            if (strncmp(p, "ifdef", 5) == 0 && (p[5] == ' ' || p[5] == '\t')) {
                p += 5;
                while (*p == ' ' || *p == '\t') p++;
                const char *ns = p;
                while (*p && *p != '\n' && *p != ' ' && *p != '\t') p++;
                int nlen = p - ns;
                char *name = xmalloc(nlen + 1);
                memcpy(name, ns, nlen);
                name[nlen] = '\0';
                if (if_depth >= 32) fatal("#ifdef nesting too deep");
                int cond = pp_is_including() && is_macro_defined(name);
                if_stack[if_depth].including = cond;
                if_stack[if_depth].seen_else = 0;
                if_stack[if_depth].satisfied = cond;
                if_depth++;
                free(name);
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #ifndef */
            if (strncmp(p, "ifndef", 6) == 0 && (p[6] == ' ' || p[6] == '\t')) {
                p += 6;
                while (*p == ' ' || *p == '\t') p++;
                const char *ns = p;
                while (*p && *p != '\n' && *p != ' ' && *p != '\t') p++;
                int nlen = p - ns;
                char *name = xmalloc(nlen + 1);
                memcpy(name, ns, nlen);
                name[nlen] = '\0';
                if (if_depth >= 32) fatal("#ifndef nesting too deep");
                int cond = pp_is_including() && !is_macro_defined(name);
                if_stack[if_depth].including = cond;
                if_stack[if_depth].seen_else = 0;
                if_stack[if_depth].satisfied = cond;
                if_depth++;
                free(name);
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #if */
            if (strncmp(p, "if", 2) == 0 && (p[2] == ' ' || p[2] == '\t')) {
                p += 2;
                while (*p == ' ' || *p == '\t') p++;
                const char *expr_start = p;
                while (*p && *p != '\n') p++;
                int elen = p - expr_start;
                /* Trim trailing whitespace */
                while (elen > 0 && (expr_start[elen-1] == ' ' || expr_start[elen-1] == '\t')) elen--;
                char *expr = xmalloc(elen + 1);
                memcpy(expr, expr_start, elen);
                expr[elen] = '\0';
                if (if_depth >= 32) fatal("#if nesting too deep");
                int cond = pp_is_including() && eval_if_expr(expr);
                if_stack[if_depth].including = cond;
                if_stack[if_depth].seen_else = 0;
                if_stack[if_depth].satisfied = cond;
                if_depth++;
                free(expr);
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #elif */
            if (strncmp(p, "elif", 4) == 0 && (p[4] == ' ' || p[4] == '\t')) {
                p += 4;
                while (*p == ' ' || *p == '\t') p++;
                const char *expr_start = p;
                while (*p && *p != '\n') p++;
                int elen = p - expr_start;
                while (elen > 0 && (expr_start[elen-1] == ' ' || expr_start[elen-1] == '\t')) elen--;
                char *expr = xmalloc(elen + 1);
                memcpy(expr, expr_start, elen);
                expr[elen] = '\0';
                if (if_depth <= 0) fatal("#elif without #if");
                if (if_stack[if_depth - 1].seen_else) fatal("#elif after #else");
                /* Check if parent levels are including */
                int parent_inc = 1;
                for (int i = 0; i < if_depth - 1; i++) {
                    if (!if_stack[i].including) { parent_inc = 0; break; }
                }
                if (if_stack[if_depth - 1].satisfied) {
                    if_stack[if_depth - 1].including = 0;
                } else if (parent_inc && eval_if_expr(expr)) {
                    if_stack[if_depth - 1].including = 1;
                    if_stack[if_depth - 1].satisfied = 1;
                } else {
                    if_stack[if_depth - 1].including = 0;
                }
                free(expr);
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #else */
            if (strncmp(p, "else", 4) == 0 && (p[4] == '\n' || p[4] == '\0' || p[4] == ' ' || p[4] == '\t')) {
                if (if_depth <= 0) fatal("#else without #if");
                if (if_stack[if_depth - 1].seen_else) fatal("duplicate #else");
                if_stack[if_depth - 1].seen_else = 1;
                /* Check if parent levels are including */
                int parent_inc = 1;
                for (int i = 0; i < if_depth - 1; i++) {
                    if (!if_stack[i].including) { parent_inc = 0; break; }
                }
                if (if_stack[if_depth - 1].satisfied) {
                    if_stack[if_depth - 1].including = 0;
                } else {
                    if_stack[if_depth - 1].including = parent_inc;
                    if_stack[if_depth - 1].satisfied = 1;
                }
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #endif */
            if (strncmp(p, "endif", 5) == 0 && (p[5] == '\n' || p[5] == '\0' || p[5] == ' ' || p[5] == '\t')) {
                if (if_depth <= 0) fatal("#endif without #if");
                if_depth--;
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }

            /* Only process remaining directives if including */
            if (!pp_is_including()) {
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }

            /* #include "file" */
            if (strncmp(p, "include", 7) == 0 && (p[7] == ' ' || p[7] == '\t' || p[7] == '"')) {
                p += 7;
                while (*p == ' ' || *p == '\t') p++;
                if (*p == '"') {
                    p++;
                    const char *path_start = p;
                    while (*p && *p != '"' && *p != '\n') p++;
                    int plen = p - path_start;
                    char *inc_file = xmalloc(plen + 1);
                    memcpy(inc_file, path_start, plen);
                    inc_file[plen] = '\0';
                    if (*p == '"') p++;
                    /* Build full path relative to current file */
                    char *full_path = concat_paths(dir, inc_file);
                    char *inc_src = read_file(full_path);
                    preprocess_file(inc_src, full_path, depth + 1, b);
                    free(inc_src);
                    free(full_path);
                    free(inc_file);
                    while (*p && *p != '\n') p++;
                    if (*p == '\n') { buf_push(b, '\n'); p++; }
                    continue;
                }
                if (*p == '<') {
                    /* #include <...> — search include paths */
                    p++;
                    const char *path_start = p;
                    while (*p && *p != '>' && *p != '\n') p++;
                    int plen = p - path_start;
                    char *inc_file = xmalloc(plen + 1);
                    memcpy(inc_file, path_start, plen);
                    inc_file[plen] = '\0';
                    if (*p == '>') p++;
                    /* Search include paths */
                    int found_inc = 0;
                    for (int ii = 0; ii < ninclude_paths; ii++) {
                        char *full_path = concat_paths(include_paths[ii], inc_file);
                        FILE *test = fopen(full_path, "r");
                        if (test) {
                            fclose(test);
                            char *inc_src = read_file(full_path);
                            preprocess_file(inc_src, full_path, depth + 1, b);
                            free(inc_src);
                            free(full_path);
                            found_inc = 1;
                            break;
                        }
                        free(full_path);
                    }
                    free(inc_file);
                    if (!found_inc) {
                        /* System header not found — skip silently */
                    }
                    while (*p && *p != '\n') p++;
                    if (*p == '\n') { buf_push(b, '\n'); p++; }
                    continue;
                }
                /* Unknown include form — skip */
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #define */
            if (strncmp(p, "define", 6) == 0 && (p[6] == ' ' || p[6] == '\t')) {
                p += 6;
                while (*p == ' ' || *p == '\t') p++;
                const char *name_start = p;
                while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '(') p++;
                int name_len = p - name_start;
                char *name = xmalloc(name_len + 1);
                memcpy(name, name_start, name_len);
                name[name_len] = '\0';
                if (*p == '(') {
                    /* Function-like macro: parse params */
                    p++; /* skip '(' */
                    char **params = xmalloc(16 * sizeof(char *));
                    int nparams = 0;
                    int pcap = 16;
                    int macro_variadic = 0;
                    while (*p && *p != ')' && *p != '\n') {
                        while (*p == ' ' || *p == '\t') p++;
                        if (*p == ')') break;
                        /* Check for ... (variadic) */
                        if (p[0] == '.' && p[1] == '.' && p[2] == '.') {
                            p += 3;
                            macro_variadic = 1;
                            while (*p == ' ' || *p == '\t') p++;
                            break;
                        }
                        const char *ps = p;
                        while (*p && *p != ',' && *p != ')' && *p != ' ' && *p != '\t' && *p != '\n') p++;
                        int plen = p - ps;
                        if (plen > 0) {
                            if (nparams >= pcap) {
                                pcap *= 2;
                                params = realloc(params, pcap * sizeof(char *));
                            }
                            char *param = xmalloc(plen + 1);
                            memcpy(param, ps, plen);
                            param[plen] = '\0';
                            params[nparams++] = param;
                        }
                        while (*p == ' ' || *p == '\t') p++;
                        if (*p == ',') {
                            p++;
                            /* Check for ... after comma */
                            while (*p == ' ' || *p == '\t') p++;
                            if (p[0] == '.' && p[1] == '.' && p[2] == '.') {
                                p += 3;
                                macro_variadic = 1;
                                while (*p == ' ' || *p == '\t') p++;
                                break;
                            }
                        }
                    }
                    if (*p == ')') p++;
                    /* Read body = rest of line, trimmed */
                    while (*p == ' ' || *p == '\t') p++;
                    const char *body_start = p;
                    while (*p && *p != '\n') p++;
                    const char *body_end = p;
                    while (body_end > body_start && (body_end[-1] == ' ' || body_end[-1] == '\t')) body_end--;
                    int body_len = body_end - body_start;
                    char *body = xmalloc(body_len + 1);
                    memcpy(body, body_start, body_len);
                    body[body_len] = '\0';
                    add_func_macro(name, params, nparams, body, macro_variadic);
                    free(name);
                    free(body);
                } else {
                    while (*p == ' ' || *p == '\t') p++;
                    const char *val_start = p;
                    while (*p && *p != '\n') p++;
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
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #undef */
            if (strncmp(p, "undef", 5) == 0 && (p[5] == ' ' || p[5] == '\t')) {
                p += 5;
                while (*p == ' ' || *p == '\t') p++;
                const char *ns = p;
                while (*p && *p != '\n' && *p != ' ' && *p != '\t') p++;
                int nlen = p - ns;
                char *name = xmalloc(nlen + 1);
                memcpy(name, ns, nlen);
                name[nlen] = '\0';
                /* Remove from macro table */
                for (int i = 0; i < nmacros; i++) {
                    if (strcmp(macros[i].name, name) == 0) {
                        free(macros[i].name);
                        free(macros[i].value);
                        free(macros[i].body);
                        for (int j = i; j < nmacros - 1; j++)
                            macros[j] = macros[j + 1];
                        nmacros--;
                        break;
                    }
                }
                free(name);
                while (*p && *p != '\n') p++;
                if (*p == '\n') { buf_push(b, '\n'); p++; }
                continue;
            }
            /* #error */
            if (strncmp(p, "error", 5) == 0 && (p[5] == ' ' || p[5] == '\t' || p[5] == '\n' || p[5] == '\0')) {
                p += 5;
                while (*p == ' ' || *p == '\t') p++;
                const char *msg_start = p;
                while (*p && *p != '\n') p++;
                int mlen = p - msg_start;
                char *msg = xmalloc(mlen + 1);
                memcpy(msg, msg_start, mlen);
                msg[mlen] = '\0';
                fatal("#error: %s", msg);
            }
            /* Other preprocessor directive — skip */
            while (*p && *p != '\n') p++;
            if (*p == '\n') { buf_push(b, '\n'); p++; }
        } else {
            /* Non-directive line */
            if (pp_is_including()) {
                /* Extract line, expand macros, then append.
                 * If a function-like macro invocation spans multiple lines
                 * (unbalanced parens after seeing a macro name + '('),
                 * accumulate lines until parens balance. */
                p = line_start;
                Buf lb;
                buf_init(&lb);
                int line_len = 0;
                while (p[line_len] && p[line_len] != '\n') line_len++;
                for (int k = 0; k < line_len; k++) buf_push(&lb, p[k]);
                p += line_len;
                /* Check paren balance — crude but effective for multi-line macro args */
                int pdepth = 0;
                int in_str = 0;
                for (int k = 0; k < lb.len; k++) {
                    if (lb.data[k] == '"' && !in_str) in_str = 1;
                    else if (lb.data[k] == '"' && in_str) in_str = 0;
                    else if (!in_str && lb.data[k] == '(') pdepth++;
                    else if (!in_str && lb.data[k] == ')') pdepth--;
                }
                while (pdepth > 0 && *p) {
                    if (*p == '\n') { buf_push(&lb, ' '); p++; }
                    /* Stop at directive lines — don't consume across preprocessor boundaries */
                    const char *nl = p;
                    while (*nl == ' ' || *nl == '\t') nl++;
                    if (*nl == '#') break;
                    while (*p && *p != '\n') {
                        char c = *p;
                        if (c == '"') in_str = !in_str;
                        else if (!in_str && c == '(') pdepth++;
                        else if (!in_str && c == ')') pdepth--;
                        buf_push(&lb, c);
                        p++;
                    }
                }
                char *line_buf = buf_detach(&lb);
                char *expanded = expand_macros(line_buf);
                free(line_buf);
                for (int ei = 0; expanded[ei]; ei++)
                    buf_push(b, expanded[ei]);
                free(expanded);
            } else {
                while (*p && *p != '\n') p++;
            }
            if (*p == '\n') { buf_push(b, '\n'); p++; }
        }
    }
    free(dir);
}

static char *join_backslash_lines(const char *src) {
    int len = strlen(src);
    char *out = xmalloc(len + 1);
    memcpy(out, src, len + 1);
    for (int i = 0; i < len - 1; i++) {
        if (out[i] == '\\' && out[i + 1] == '\n') {
            out[i] = ' ';
            out[i + 1] = ' ';
        }
    }
    return out;
}

/* Strip C comments, replacing with spaces (preserve newlines for line tracking).
 * Per C standard, this is translation phase 3 — before preprocessing (phase 4). */
static char *strip_comments(const char *src) {
    int len = strlen(src);
    char *out = xmalloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; ) {
        /* Check for string literals — don't strip inside them */
        if (src[i] == '"') {
            out[j++] = src[i++];
            while (i < len && src[i] != '"') {
                if (src[i] == '\\' && i + 1 < len) {
                    out[j++] = src[i++];
                    out[j++] = src[i++];
                } else {
                    out[j++] = src[i++];
                }
            }
            if (i < len) out[j++] = src[i++]; /* closing quote */
        } else if (src[i] == '\'' ) {
            out[j++] = src[i++];
            while (i < len && src[i] != '\'') {
                if (src[i] == '\\' && i + 1 < len) {
                    out[j++] = src[i++];
                    out[j++] = src[i++];
                } else {
                    out[j++] = src[i++];
                }
            }
            if (i < len) out[j++] = src[i++]; /* closing quote */
        } else if (src[i] == '/' && i + 1 < len && src[i+1] == '/') {
            /* line comment — replace with space, keep the newline */
            i += 2;
            out[j++] = ' ';
            while (i < len && src[i] != '\n') i++;
        } else if (src[i] == '/' && i + 1 < len && src[i+1] == '*') {
            /* block comment — replace with space, but preserve newlines */
            i += 2;
            out[j++] = ' ';
            while (i + 1 < len && !(src[i] == '*' && src[i+1] == '/')) {
                if (src[i] == '\n') out[j++] = '\n';
                i++;
            }
            if (i + 1 < len) i += 2; /* skip */
        } else {
            out[j++] = src[i++];
        }
    }
    out[j] = '\0';
    return out;
}

static char **cmdline_defs;
static int ncmdline_defs;
static int cmdline_defs_cap;

static char *strip_preprocessor(const char *src, const char *filepath) {
    nmacros = 0;
    /* Predefined macros */
    add_macro("__STDC__", "1");
    add_macro("__STDC_VERSION__", "201112L");
    {
        /* __FILE__ = "filepath" */
        int flen = strlen(filepath);
        char *fval = xmalloc(flen + 3);
        fval[0] = '"';
        memcpy(fval + 1, filepath, flen);
        fval[flen + 1] = '"';
        fval[flen + 2] = '\0';
        add_macro("__FILE__", fval);
        free(fval);
    }
    add_macro("__LINE__", "0");  /* placeholder; real __LINE__ needs per-line tracking */
    /* Inject -D command-line macros */
    for (int i = 0; i < ncmdline_defs; i++) {
        char *def = cmdline_defs[i];
        char *eq = strchr(def, '=');
        if (eq) {
            char *name = xmalloc(eq - def + 1);
            memcpy(name, def, eq - def);
            name[eq - def] = '\0';
            add_macro(name, xstrdup(eq + 1));
        } else {
            add_macro(xstrdup(def), xstrdup("1"));
        }
    }
    if_depth = 0;
    char *joined = join_backslash_lines(src);
    char *nocomments = strip_comments(joined);
    free(joined);
    Buf b;
    buf_init(&b);
    preprocess_file(nocomments, filepath, 0, &b);
    free(nocomments);
    if (if_depth != 0) fatal("Unterminated #if/#ifdef/#ifndef");
    char *stripped = buf_detach(&b);
    return stripped;
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
    char *cleaned = strip_preprocessor(src, c_path);

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
    int eflag = 0;  /* -E: preprocess only */
    char **inputs = NULL;
    int ninputs = 0;
    int icap = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) fatal("Missing argument for -o");
            out_path = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            cflag = 1;
        } else if (strcmp(argv[i], "-E") == 0) {
            eflag = 1;
        } else if (strncmp(argv[i], "-D", 2) == 0) {
            if (argv[i][2] != '\0') {
                GROW(cmdline_defs, ncmdline_defs, cmdline_defs_cap, char *);
                cmdline_defs[ncmdline_defs++] = argv[i] + 2;
            } else if (i + 1 < argc) {
                GROW(cmdline_defs, ncmdline_defs, cmdline_defs_cap, char *);
                cmdline_defs[ncmdline_defs++] = argv[++i];
            } else {
                fatal("Missing argument for -D");
            }
        } else if (strncmp(argv[i], "-I", 2) == 0) {
            const char *path = argv[i][2] ? argv[i] + 2 : (i + 1 < argc ? argv[++i] : NULL);
            if (!path) fatal("Missing argument for -I");
            GROW(include_paths, ninclude_paths, include_paths_cap, char *);
            include_paths[ninclude_paths++] = (char *)path;
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

    if (eflag) {
        /* Preprocess-only mode */
        for (int i = 0; i < ninputs; i++) {
            char *src = read_file(inputs[i]);
            char *cleaned = strip_preprocessor(src, inputs[i]);
            printf("%s", cleaned);
            free(cleaned);
            free(src);
        }
        return 0;
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
