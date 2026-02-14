#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TK_NUMBER,
    TK_ID,
    TK_STRING,
    TK_KW,
    TK_OP,
    TK_EOF,
} TokKind;

typedef struct {
    TokKind kind;
    char *value;
    int pos;
} Tok;

typedef struct {
    Tok *data;
    int len;
    int cap;
} TokArray;

TokArray lex(const char *src);
const char *tokkind_str(TokKind k);

#endif
