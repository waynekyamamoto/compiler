#include "ast.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

void exprarray_push(ExprArray *a, Expr *e) {
    if (a->len >= a->cap) {
        a->cap = a->cap ? a->cap * 2 : 8;
        a->data = realloc(a->data, a->cap * sizeof(Expr *));
        if (!a->data) fatal("out of memory");
    }
    a->data[a->len++] = e;
}

void stmtarray_push(StmtArray *a, Stmt *s) {
    if (a->len >= a->cap) {
        a->cap = a->cap ? a->cap * 2 : 8;
        a->data = realloc(a->data, a->cap * sizeof(Stmt *));
        if (!a->data) fatal("out of memory");
    }
    a->data[a->len++] = s;
}

Expr *new_num(int val) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_NUM;
    e->u.num = val;
    return e;
}

Expr *new_var(const char *name) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_VAR;
    e->u.var_name = xstrdup(name);
    return e;
}

Expr *new_strlit(const char *val) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_STRLIT;
    e->u.str_val = xstrdup(val);
    return e;
}

Expr *new_call(const char *name, ExprArray args) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_CALL;
    e->u.call.name = xstrdup(name);
    e->u.call.args = args;
    return e;
}

Expr *new_unary(char op, Expr *rhs) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_UNARY;
    e->u.unary.op = op;
    e->u.unary.rhs = rhs;
    return e;
}

Expr *new_binary(const char *op, Expr *lhs, Expr *rhs) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_BINARY;
    e->u.binary.op = xstrdup(op);
    e->u.binary.lhs = lhs;
    e->u.binary.rhs = rhs;
    return e;
}

Expr *new_index(Expr *base, Expr *index) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_INDEX;
    e->u.index.base = base;
    e->u.index.index = index;
    return e;
}

Expr *new_field(Expr *obj, const char *field, const char *struct_type) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_FIELD;
    e->u.field.obj = obj;
    e->u.field.field = xstrdup(field);
    e->u.field.struct_type = xstrdup(struct_type);
    return e;
}

Expr *new_arrow(Expr *obj, const char *field, const char *struct_type) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_ARROW;
    e->u.field.obj = obj;
    e->u.field.field = xstrdup(field);
    e->u.field.struct_type = xstrdup(struct_type);
    return e;
}

Expr *new_assign(Expr *target, Expr *rhs) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_ASSIGN;
    e->u.assign.target = target;
    e->u.assign.rhs = rhs;
    return e;
}

Expr *new_postinc(Expr *operand) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_POSTINC;
    e->u.postinc_operand = operand;
    return e;
}

Expr *new_postdec(Expr *operand) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_POSTDEC;
    e->u.postinc_operand = operand;
    return e;
}

Expr *new_ternary(Expr *cond, Expr *then_expr, Expr *else_expr) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_TERNARY;
    e->u.ternary.cond = cond;
    e->u.ternary.then_expr = then_expr;
    e->u.ternary.else_expr = else_expr;
    return e;
}

Expr *new_compound_lit(const char *struct_type, Expr *init) {
    Expr *e = xmalloc(sizeof(Expr));
    e->kind = ND_COMPOUND_LIT;
    e->u.compound_lit.struct_type = xstrdup(struct_type);
    e->u.compound_lit.init = init;
    return e;
}

Stmt *new_return(Expr *e) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_RETURN;
    s->u.ret_expr = e;
    return s;
}

Stmt *new_if(Expr *cond, Block then_blk, Block *else_blk) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_IF;
    s->u.if_s.cond = cond;
    s->u.if_s.then_blk = then_blk;
    s->u.if_s.else_blk = else_blk;
    return s;
}

Stmt *new_while(Expr *cond, Block body) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_WHILE;
    s->u.while_s.cond = cond;
    s->u.while_s.body = body;
    return s;
}

Stmt *new_for(Stmt *init, Expr *cond, Expr *post, Block body) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_FOR;
    s->u.for_s.init = init;
    s->u.for_s.cond = cond;
    s->u.for_s.post = post;
    s->u.for_s.body = body;
    return s;
}

Stmt *new_break(void) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_BREAK;
    return s;
}

Stmt *new_continue(void) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_CONTINUE;
    return s;
}

Stmt *new_exprstmt(Expr *e) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_EXPR;
    s->u.expr = e;
    return s;
}

Stmt *new_vardecl(VarDeclList vdl) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_VARDECL;
    s->u.vardecl = vdl;
    return s;
}

Stmt *new_dowhile(Expr *cond, Block body) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_DOWHILE;
    s->u.dowhile_s.cond = cond;
    s->u.dowhile_s.body = body;
    return s;
}

Stmt *new_switch(Expr *cond, SwitchCase *cases, int ncases) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_SWITCH;
    s->u.switch_s.cond = cond;
    s->u.switch_s.cases = cases;
    s->u.switch_s.ncases = ncases;
    return s;
}

Stmt *new_goto(const char *label) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_GOTO;
    s->u.goto_label = xstrdup(label);
    return s;
}

Stmt *new_label(const char *name, Stmt *stmt) {
    Stmt *s = xmalloc(sizeof(Stmt));
    s->kind = ST_LABEL;
    s->u.label_s.name = xstrdup(name);
    s->u.label_s.stmt = stmt;
    return s;
}

/* ---- Type system ---- */

static Type _ty_void  = { TY_VOID,  NULL, NULL, 0, 0, 0, 0 };
static Type _ty_char  = { TY_CHAR,  NULL, NULL, 0, 0, 1, 1 };
static Type _ty_short = { TY_SHORT, NULL, NULL, 0, 0, 2, 2 };
static Type _ty_int   = { TY_INT,   NULL, NULL, 0, 0, 4, 4 };
static Type _ty_long  = { TY_LONG,  NULL, NULL, 0, 0, 8, 8 };
static Type _ty_llong = { TY_LLONG, NULL, NULL, 0, 0, 8, 8 };
static Type _ty_float = { TY_FLOAT, NULL, NULL, 0, 0, 4, 4 };
static Type _ty_double= { TY_DOUBLE,NULL, NULL, 0, 0, 8, 8 };
static Type _ty_uchar = { TY_CHAR,  NULL, NULL, 0, 1, 1, 1 };
static Type _ty_ushort= { TY_SHORT, NULL, NULL, 0, 1, 2, 2 };
static Type _ty_uint  = { TY_INT,   NULL, NULL, 0, 1, 4, 4 };
static Type _ty_ulong = { TY_LONG,  NULL, NULL, 0, 1, 8, 8 };
static Type _ty_ullong= { TY_LLONG, NULL, NULL, 0, 1, 8, 8 };

Type *ty_void(void)  { return &_ty_void; }
Type *ty_char(void)  { return &_ty_char; }
Type *ty_short(void) { return &_ty_short; }
Type *ty_int(void)   { return &_ty_int; }
Type *ty_long(void)  { return &_ty_long; }
Type *ty_llong(void) { return &_ty_llong; }
Type *ty_float(void) { return &_ty_float; }
Type *ty_double(void){ return &_ty_double; }

Type *ty_ptr(Type *base) {
    Type *t = xmalloc(sizeof(Type));
    t->kind = TY_PTR;
    t->base = base;
    t->struct_name = NULL;
    t->array_len = 0;
    t->is_unsigned = 0;
    t->size = 8;
    t->align = 8;
    return t;
}

Type *ty_array(Type *base, int len) {
    Type *t = xmalloc(sizeof(Type));
    t->kind = TY_ARRAY;
    t->base = base;
    t->struct_name = NULL;
    t->array_len = len;
    t->is_unsigned = 0;
    t->size = (len > 0) ? type_size(base) * len : 0;
    t->align = type_align(base);
    return t;
}

Type *ty_struct(const char *name) {
    Type *t = xmalloc(sizeof(Type));
    t->kind = TY_STRUCT;
    t->base = NULL;
    t->struct_name = xstrdup(name);
    t->array_len = 0;
    t->is_unsigned = 0;
    t->size = 0;  /* computed later from struct layout */
    t->align = 0;
    return t;
}

Type *ty_union(const char *name) {
    Type *t = xmalloc(sizeof(Type));
    t->kind = TY_UNION;
    t->base = NULL;
    t->struct_name = xstrdup(name);
    t->array_len = 0;
    t->is_unsigned = 0;
    t->size = 0;
    t->align = 0;
    return t;
}

Type *ty_enum(void) {
    /* Enums are ints */
    return &_ty_int;
}

Type *ty_unsigned(Type *base) {
    if (!base) return &_ty_uint;
    switch (base->kind) {
    case TY_CHAR:  return &_ty_uchar;
    case TY_SHORT: return &_ty_ushort;
    case TY_INT:   return &_ty_uint;
    case TY_LONG:  return &_ty_ulong;
    case TY_LLONG: return &_ty_ullong;
    default: return base;
    }
}

int type_size(Type *ty) {
    if (!ty) return 8;  /* default: treat as long/ptr */
    if (ty->size > 0) return ty->size;
    switch (ty->kind) {
    case TY_VOID:   return 1;  /* sizeof(void) = 1 in GCC */
    case TY_CHAR:   return 1;
    case TY_SHORT:  return 2;
    case TY_INT:    return 4;
    case TY_LONG:   return 8;
    case TY_LLONG:  return 8;
    case TY_FLOAT:  return 4;
    case TY_DOUBLE: return 8;
    case TY_PTR:    return 8;
    case TY_ARRAY:  return ty->array_len > 0 ? type_size(ty->base) * ty->array_len : 8;
    case TY_ENUM:   return 4;
    case TY_FUNC:   return 8;
    case TY_STRUCT:
    case TY_UNION:
        /* struct/union size must be set externally */
        return ty->size > 0 ? ty->size : 8;
    }
    return 8;
}

int type_align(Type *ty) {
    if (!ty) return 8;
    if (ty->align > 0) return ty->align;
    switch (ty->kind) {
    case TY_CHAR:   return 1;
    case TY_SHORT:  return 2;
    case TY_INT:    return 4;
    case TY_LONG:   return 8;
    case TY_LLONG:  return 8;
    case TY_FLOAT:  return 4;
    case TY_DOUBLE: return 8;
    case TY_PTR:    return 8;
    case TY_ARRAY:  return type_align(ty->base);
    case TY_STRUCT:
    case TY_UNION:
        return ty->align > 0 ? ty->align : 8;
    default:        return 4;
    }
}

int type_is_integer(Type *ty) {
    if (!ty) return 1;
    return ty->kind >= TY_CHAR && ty->kind <= TY_LLONG;
}

int type_is_ptr_like(Type *ty) {
    if (!ty) return 0;
    return ty->kind == TY_PTR || ty->kind == TY_ARRAY;
}
