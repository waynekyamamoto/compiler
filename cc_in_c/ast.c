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
