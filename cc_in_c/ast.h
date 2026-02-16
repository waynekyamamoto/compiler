#ifndef AST_H
#define AST_H

/* ---- Expression nodes ---- */

typedef enum {
    ND_NUM,
    ND_VAR,
    ND_STRLIT,
    ND_CALL,
    ND_UNARY,
    ND_BINARY,
    ND_INDEX,
    ND_FIELD,
    ND_ARROW,
    ND_ASSIGN,
    ND_POSTINC,
    ND_POSTDEC,
    ND_TERNARY,
} ExprKind;

typedef struct Expr Expr;

typedef struct {
    Expr **data;
    int len;
    int cap;
} ExprArray;

struct Expr {
    ExprKind kind;
    union {
        int num;                    /* ND_NUM */
        char *var_name;             /* ND_VAR */
        char *str_val;              /* ND_STRLIT (without quotes) */
        struct { char *name; ExprArray args; } call;  /* ND_CALL */
        struct { char op; Expr *rhs; } unary;         /* ND_UNARY */
        struct { char *op; Expr *lhs; Expr *rhs; } binary; /* ND_BINARY */
        struct { Expr *base; Expr *index; } index;    /* ND_INDEX */
        struct { Expr *obj; char *field; char *struct_type; } field; /* ND_FIELD, ND_ARROW */
        struct { Expr *target; Expr *rhs; } assign;   /* ND_ASSIGN */
        Expr *postinc_operand;      /* ND_POSTINC, ND_POSTDEC */
        struct { Expr *cond; Expr *then_expr; Expr *else_expr; } ternary; /* ND_TERNARY */
    } u;
};

/* ---- Statement nodes ---- */

typedef enum {
    ST_RETURN,
    ST_IF,
    ST_WHILE,
    ST_FOR,
    ST_BREAK,
    ST_CONTINUE,
    ST_EXPR,
    ST_VARDECL,
    ST_DOWHILE,
    ST_SWITCH,
    ST_GOTO,
    ST_LABEL,
} StmtKind;

typedef struct Stmt Stmt;

typedef struct {
    Stmt **data;
    int len;
    int cap;
} StmtArray;

typedef struct {
    StmtArray stmts;
} Block;

/* A single variable declaration entry */
typedef struct {
    char *name;
    char *struct_type;  /* NULL if not a struct type */
    int array_size;     /* -1 if not an array */
    Expr *init;         /* NULL if no initializer */
} VarDeclEntry;

typedef struct {
    VarDeclEntry *entries;
    int count;
} VarDeclList;

/* Switch case */
typedef struct {
    Expr *value;        /* NULL for default */
    StmtArray stmts;
} SwitchCase;

struct Stmt {
    StmtKind kind;
    union {
        Expr *ret_expr;                /* ST_RETURN */
        struct { Expr *cond; Block then_blk; Block *else_blk; } if_s;  /* ST_IF */
        struct { Expr *cond; Block body; } while_s;                     /* ST_WHILE */
        struct { Stmt *init; Expr *cond; Expr *post; Block body; } for_s; /* ST_FOR */
        Expr *expr;                    /* ST_EXPR */
        VarDeclList vardecl;           /* ST_VARDECL */
        struct { Expr *cond; Block body; } dowhile_s;                   /* ST_DOWHILE */
        struct { Expr *cond; SwitchCase *cases; int ncases; } switch_s; /* ST_SWITCH */
        char *goto_label;              /* ST_GOTO */
        struct { char *name; Stmt *stmt; } label_s;                     /* ST_LABEL */
    } u;
};

/* ---- Top-level ---- */

typedef struct {
    char *name;
    char **fields;
    int nfields;
} StructDef;

typedef struct {
    char *name;
    char **params;
    int nparams;
    Block body;
    int is_static;
    int ret_is_ptr;
} FuncDef;

typedef struct {
    char *name;
    char *struct_type;  /* NULL if int */
    int is_ptr;
    int array_size;     /* -1 if not an array */
    Expr *init;         /* NULL if no initializer */
    int is_extern;      /* 1 if extern declaration */
    int is_static;      /* 1 if static declaration */
} GlobalDecl;

typedef struct {
    char *name;
    int ret_is_ptr;
} FuncProto;

typedef struct {
    StructDef *structs;
    int nstructs;
    FuncDef *funcs;
    int nfuncs;
    GlobalDecl *globals;
    int nglobals;
    FuncProto *protos;
    int nprotos;
} Program;

/* ---- Constructors ---- */

Expr *new_num(int val);
Expr *new_var(const char *name);
Expr *new_strlit(const char *val);
Expr *new_call(const char *name, ExprArray args);
Expr *new_unary(char op, Expr *rhs);
Expr *new_binary(const char *op, Expr *lhs, Expr *rhs);
Expr *new_index(Expr *base, Expr *index);
Expr *new_field(Expr *obj, const char *field, const char *struct_type);
Expr *new_arrow(Expr *obj, const char *field, const char *struct_type);
Expr *new_assign(Expr *target, Expr *rhs);
Expr *new_postinc(Expr *operand);
Expr *new_postdec(Expr *operand);
Expr *new_ternary(Expr *cond, Expr *then_expr, Expr *else_expr);

Stmt *new_return(Expr *e);
Stmt *new_if(Expr *cond, Block then_blk, Block *else_blk);
Stmt *new_while(Expr *cond, Block body);
Stmt *new_for(Stmt *init, Expr *cond, Expr *post, Block body);
Stmt *new_break(void);
Stmt *new_continue(void);
Stmt *new_exprstmt(Expr *e);
Stmt *new_vardecl(VarDeclList vdl);
Stmt *new_dowhile(Expr *cond, Block body);
Stmt *new_switch(Expr *cond, SwitchCase *cases, int ncases);
Stmt *new_goto(const char *label);
Stmt *new_label(const char *name, Stmt *stmt);

void exprarray_push(ExprArray *a, Expr *e);
void stmtarray_push(StmtArray *a, Stmt *s);

#endif
