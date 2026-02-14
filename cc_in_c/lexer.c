#include "lexer.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *keywords[] = {
    "int", "return", "if", "else", "while", "for",
    "break", "continue", "struct", "extern", NULL,
};

static int is_keyword(const char *s) {
    for (int i = 0; keywords[i]; i++)
        if (strcmp(s, keywords[i]) == 0)
            return 1;
    return 0;
}

static void tokarr_push(TokArray *a, Tok t) {
    if (a->len >= a->cap) {
        a->cap = a->cap ? a->cap * 2 : 64;
        a->data = realloc(a->data, a->cap * sizeof(Tok));
        if (!a->data) fatal("out of memory");
    }
    a->data[a->len++] = t;
}

static char *substr(const char *s, int start, int end) {
    int n = end - start;
    char *p = xmalloc(n + 1);
    memcpy(p, s + start, n);
    p[n] = '\0';
    return p;
}

TokArray lex(const char *src) {
    /* Strip comments into a mutable copy */
    int slen = strlen(src);
    char *buf = xmalloc(slen + 1);
    int j = 0;
    for (int i = 0; i < slen; ) {
        if (src[i] == '/' && i + 1 < slen && src[i+1] == '/') {
            /* line comment */
            i += 2;
            while (i < slen && src[i] != '\n') i++;
        } else if (src[i] == '/' && i + 1 < slen && src[i+1] == '*') {
            /* block comment */
            i += 2;
            while (i + 1 < slen && !(src[i] == '*' && src[i+1] == '/')) i++;
            if (i + 1 < slen) i += 2;
        } else {
            buf[j++] = src[i++];
        }
    }
    buf[j] = '\0';

    TokArray toks;
    toks.data = NULL;
    toks.len = 0;
    toks.cap = 0;

    int i = 0;
    int len = j;
    while (i < len) {
        /* skip whitespace */
        if (isspace((unsigned char)buf[i])) {
            i++;
            continue;
        }

        /* number */
        if (isdigit((unsigned char)buf[i])) {
            int start = i;
            while (i < len && isdigit((unsigned char)buf[i])) i++;
            Tok t = { TK_NUMBER, substr(buf, start, i), start };
            tokarr_push(&toks, t);
            continue;
        }

        /* identifier / keyword */
        if (isalpha((unsigned char)buf[i]) || buf[i] == '_') {
            int start = i;
            while (i < len && (isalnum((unsigned char)buf[i]) || buf[i] == '_')) i++;
            char *val = substr(buf, start, i);
            TokKind kind = is_keyword(val) ? TK_KW : TK_ID;
            Tok t = { kind, val, start };
            tokarr_push(&toks, t);
            continue;
        }

        /* character literal */
        if (buf[i] == '\'') {
            int start = i;
            i++; /* skip opening quote */
            int ch = 0;
            if (buf[i] == '\\') {
                i++;
                if (buf[i] == 'n') ch = 10;
                else if (buf[i] == 't') ch = 9;
                else if (buf[i] == 'r') ch = 13;
                else if (buf[i] == '\\') ch = 92;
                else if (buf[i] == '\'') ch = 39;
                else if (buf[i] == '0') ch = 0;
                else fatal("Bad char escape: \\%c", buf[i]);
                i++;
            } else {
                ch = (unsigned char)buf[i];
                i++;
            }
            if (i < len && buf[i] == '\'') i++; /* skip closing quote */
            char val[16];
            snprintf(val, sizeof(val), "%d", ch);
            Tok t = { TK_NUMBER, xstrdup(val), start };
            tokarr_push(&toks, t);
            continue;
        }

        /* string literal */
        if (buf[i] == '"') {
            int start = i;
            i++; /* skip opening quote */
            while (i < len && buf[i] != '"') {
                if (buf[i] == '\\') i++; /* skip escaped char */
                i++;
            }
            if (i < len) i++; /* skip closing quote */
            /* store without quotes */
            char *val = substr(buf, start + 1, i - 1);
            Tok t = { TK_STRING, val, start };
            tokarr_push(&toks, t);
            continue;
        }

        /* two-character operators */
        if (i + 1 < len) {
            char c0 = buf[i], c1 = buf[i+1];
            if ((c0 == '-' && c1 == '>') ||
                (c0 == '=' && c1 == '=') ||
                (c0 == '!' && c1 == '=') ||
                (c0 == '<' && c1 == '=') ||
                (c0 == '>' && c1 == '=') ||
                (c0 == '&' && c1 == '&') ||
                (c0 == '|' && c1 == '|')) {
                char *val = substr(buf, i, i + 2);
                Tok t = { TK_OP, val, i };
                tokarr_push(&toks, t);
                i += 2;
                continue;
            }
        }

        /* single-character operators */
        if (strchr("+-*/%<>=!&.;,(){}[]", buf[i])) {
            char *val = substr(buf, i, i + 1);
            Tok t = { TK_OP, val, i };
            tokarr_push(&toks, t);
            i++;
            continue;
        }

        fatal("Unexpected character '%c' at position %d", buf[i], i);
    }

    Tok eof = { TK_EOF, xstrdup(""), len };
    tokarr_push(&toks, eof);
    return toks;
}

const char *tokkind_str(TokKind k) {
    switch (k) {
    case TK_NUMBER: return "NUMBER";
    case TK_ID:     return "ID";
    case TK_STRING: return "STRING";
    case TK_KW:     return "KW";
    case TK_OP:     return "OP";
    case TK_EOF:    return "EOF";
    }
    return "?";
}
