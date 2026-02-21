#ifndef AST_H
#define AST_H

/* ---- Type system ---- */

typedef enum {
    TY_VOID,
    TY_CHAR,
    TY_SHORT,
    TY_INT,
    TY_LONG,
    TY_LLONG,
    TY_FLOAT,
    TY_DOUBLE,
    TY_PTR,
    TY_ARRAY,
    TY_STRUCT,
    TY_UNION,
    TY_ENUM,
    TY_FUNC,
} TypeKind;

typedef struct Type Type;
struct Type {
    TypeKind kind;
    Type *base;         /* pointed-to type (PTR/ARRAY) or return type (FUNC) */
    char *struct_name;  /* for STRUCT/UNION: tag name */
    int array_len;      /* for ARRAY: element count (-1 if unspecified) */
    int is_unsigned;    /* for integer types */
    int size;           /* cached size in bytes (0 = not yet computed) */
    int align;          /* cached alignment (0 = not yet computed) */
};

/* Singleton types */
Type *ty_void(void);
Type *ty_char(void);
Type *ty_short(void);
Type *ty_int(void);
Type *ty_long(void);
Type *ty_llong(void);
Type *ty_float(void);
Type *ty_double(void);

/* Constructors */
Type *ty_ptr(Type *base);
Type *ty_array(Type *base, int len);
Type *ty_struct(const char *name);
Type *ty_union(const char *name);
Type *ty_enum(void);
Type *ty_unsigned(Type *base);

/* Queries */
int type_size(Type *ty);
int type_align(Type *ty);
int type_is_integer(Type *ty);
int type_is_ptr_like(Type *ty);

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
    ND_INITLIST,
    ND_COMPOUND_LIT,
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
        struct { ExprArray elems; int *desig_indices; } initlist; /* ND_INITLIST */
        struct { char *struct_type; Expr *init; } compound_lit; /* ND_COMPOUND_LIT */
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
    int is_ptr;         /* 1 if pointer type */
    Expr *init;         /* NULL if no initializer */
    int is_static;      /* 1 if static local */
    int is_unsigned;    /* 1 if unsigned type */
    int is_char;        /* 1 if char type (for byte-sized access) */
    int array_size2;    /* -1 if not 2D, >=0 for inner dimension */
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
    char **field_types;     /* NULL = int, non-NULL = embedded struct type name */
    char **field_ptr_types; /* NULL = not ptr-to-struct, non-NULL = pointed-to struct type */
    int nfields;
    int is_union;
    int *bit_widths;     /* 0 = regular field, >0 = bitfield width (per-field) */
    int *bit_offsets;    /* bit offset within containing word (per-field) */
    int *word_indices;   /* which 8-byte word this field maps to (per-field) */
    int nwords;          /* 0 = nfields, >0 = packed word count */
    int *field_array_sizes; /* -1 = not array, >=0 = array count (per-field) */
} StructDef;

typedef struct {
    char *name;
    char **params;
    char **param_struct_types; /* struct type per param, NULL if not struct */
    int *param_is_ptr;         /* 1 if param is pointer, per param */
    int *param_is_char;        /* 1 if param is char type, per param */
    int nparams;
    Block body;
    int is_static;
    int ret_is_ptr;
    int is_variadic;
    char *ret_struct_type; /* struct type returned (NULL if not struct ptr) */
} FuncDef;

typedef struct {
    char *name;
    char *struct_type;  /* NULL if int */
    int is_ptr;
    int array_size;     /* -1 if not an array */
    Expr *init;         /* NULL if no initializer */
    int is_extern;      /* 1 if extern declaration */
    int is_static;      /* 1 if static declaration */
    int is_func_decl;   /* 1 if this is actually a function declaration */
    int is_char;        /* 1 if base type is char/unsigned char */
} GlobalDecl;

typedef struct {
    char *name;
    int ret_is_ptr;
    int is_variadic;
    int nparams;
    char *ret_struct_type; /* struct type returned (NULL if not struct ptr) */
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

Expr *new_compound_lit(const char *struct_type, Expr *init);

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
