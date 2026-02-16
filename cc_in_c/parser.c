#include "parser.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

/* ---- Parser state ---- */

typedef struct {
    char *name;         /* field name */
    char *struct_type;  /* NULL for int fields */
    int is_ptr;
} FieldInfo;

typedef struct {
    char *name;
    FieldInfo *fields;
    int nfields;
} StructDefInfo;

typedef struct {
    char *name;
    char *struct_type;  /* NULL for int vars */
    int is_ptr;
} LocalVar;

typedef struct {
    char *name;
    int value;
} EnumConst;

static Tok *toks;
static int ntoks;
static int pos;

static StructDefInfo struct_defs[64];
static int nstruct_defs;

static LocalVar local_vars[256];
static int nlocal_vars;

static EnumConst enum_consts[1024];
static int nenum_consts;

/* ---- Helpers ---- */

static Tok *cur(void) {
    return &toks[pos];
}

static Tok *eat(TokKind kind, const char *value) {
    Tok *t = cur();
    if (t->kind != kind)
        fatal("Expected %s, got %s '%s' at %d", tokkind_str(kind), tokkind_str(t->kind), t->value, t->pos);
    if (value && strcmp(t->value, value) != 0)
        fatal("Expected '%s', got '%s' at %d", value, t->value, t->pos);
    pos++;
    return t;
}

static int match(TokKind kind, const char *value) {
    Tok *t = cur();
    if (t->kind != kind) return 0;
    if (value && strcmp(t->value, value) != 0) return 0;
    return 1;
}

static LocalVar *find_local(const char *name) {
    for (int i = 0; i < nlocal_vars; i++)
        if (strcmp(local_vars[i].name, name) == 0)
            return &local_vars[i];
    return NULL;
}

static StructDefInfo *find_struct_def(const char *name) {
    for (int i = 0; i < nstruct_defs; i++)
        if (strcmp(struct_defs[i].name, name) == 0)
            return &struct_defs[i];
    return NULL;
}

static const char *field_struct_type(const char *struct_name, const char *field_name) {
    StructDefInfo *sd = find_struct_def(struct_name);
    if (!sd) fatal("Unknown struct '%s'", struct_name);
    for (int i = 0; i < sd->nfields; i++) {
        if (strcmp(sd->fields[i].name, field_name) == 0) {
            if (sd->fields[i].struct_type)
                return sd->fields[i].struct_type;
            fatal("Field '%s' of struct '%s' is not a struct type", field_name, struct_name);
        }
    }
    fatal("Struct '%s' has no field '%s'", struct_name, field_name);
    return NULL;
}

static void add_local(const char *name, const char *struct_type, int is_ptr) {
    if (nlocal_vars >= 256) fatal("Too many local variables");
    local_vars[nlocal_vars].name = xstrdup(name);
    local_vars[nlocal_vars].struct_type = struct_type ? xstrdup(struct_type) : NULL;
    local_vars[nlocal_vars].is_ptr = is_ptr;
    nlocal_vars++;
}

static int find_enum_const(const char *name, int *out_val) {
    for (int i = 0; i < nenum_consts; i++) {
        if (strcmp(enum_consts[i].name, name) == 0) {
            *out_val = enum_consts[i].value;
            return 1;
        }
    }
    return 0;
}

static void add_enum_const(const char *name, int value) {
    if (nenum_consts >= 1024) fatal("Too many enum constants");
    enum_consts[nenum_consts].name = xstrdup(name);
    enum_consts[nenum_consts].value = value;
    nenum_consts++;
}

/* ---- Type parsing ---- */

/* Skip type qualifiers: const, volatile, register */
static void skip_qualifiers(void) {
    while (match(TK_KW, "const") || match(TK_KW, "volatile") || match(TK_KW, "register"))
        eat(TK_KW, NULL);
}

/* Check if the current token starts a type specifier */
static int is_type_start(void) {
    if (match(TK_KW, "int") || match(TK_KW, "char") || match(TK_KW, "void") ||
        match(TK_KW, "unsigned") || match(TK_KW, "signed") ||
        match(TK_KW, "long") || match(TK_KW, "short") ||
        match(TK_KW, "struct") || match(TK_KW, "union") || match(TK_KW, "enum") ||
        match(TK_KW, "const") || match(TK_KW, "volatile") || match(TK_KW, "register") ||
        match(TK_KW, "static") || match(TK_KW, "extern") || match(TK_KW, "typedef") ||
        match(TK_KW, "_Bool") || match(TK_KW, "bool") || match(TK_KW, "inline"))
        return 1;
    return 0;
}

/* Returns struct name (allocated) or NULL for int/char/void/unsigned/etc */
static char *parse_base_type(void) {
    skip_qualifiers();

    if (match(TK_KW, "struct")) {
        eat(TK_KW, "struct");
        Tok *name = eat(TK_ID, NULL);
        return xstrdup(name->value);
    }
    if (match(TK_KW, "union")) {
        eat(TK_KW, "union");
        Tok *name = eat(TK_ID, NULL);
        return xstrdup(name->value);
    }
    if (match(TK_KW, "enum")) {
        eat(TK_KW, "enum");
        if (match(TK_ID, NULL))
            eat(TK_ID, NULL);  /* skip enum tag */
        return NULL;
    }
    /* All integer-like types: int, char, void, unsigned, signed, long, short */
    /* Consume all type specifier keywords */
    int got_type = 0;
    while (match(TK_KW, "int") || match(TK_KW, "char") || match(TK_KW, "void") ||
           match(TK_KW, "unsigned") || match(TK_KW, "signed") ||
           match(TK_KW, "long") || match(TK_KW, "short") ||
           match(TK_KW, "_Bool") || match(TK_KW, "bool")) {
        eat(TK_KW, NULL);
        got_type = 1;
    }
    if (got_type) {
        skip_qualifiers();
        return NULL;
    }
    fatal("Expected type, got '%s' at %d", cur()->value, cur()->pos);
    return NULL;
}

/* ---- Forward declarations ---- */
static Expr *parse_expr(int min_prec);
static Stmt *parse_stmt(void);
static Block parse_block(void);

/* ---- Struct definition ---- */

static StructDef parse_struct_or_union_def(int is_union) {
    if (is_union)
        eat(TK_KW, "union");
    else
        eat(TK_KW, "struct");
    Tok *name_tok = eat(TK_ID, NULL);
    char *name = xstrdup(name_tok->value);
    eat(TK_OP, "{");

    char **fields = NULL;
    FieldInfo *finfo = NULL;
    int nfields = 0;
    int fcap = 0;

    while (!match(TK_OP, "}")) {
        char *ftype = parse_base_type();
        int is_ptr = 0;
        while (match(TK_OP, "*")) {
            eat(TK_OP, "*");
            is_ptr = 1;
        }
        Tok *fname_tok = eat(TK_ID, NULL);
        /* skip array dimensions in struct fields */
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            if (!match(TK_OP, "]"))
                eat(TK_NUMBER, NULL);
            eat(TK_OP, "]");
        }
        eat(TK_OP, ";");

        if (nfields >= fcap) {
            fcap = fcap ? fcap * 2 : 8;
            fields = realloc(fields, fcap * sizeof(char *));
            finfo = realloc(finfo, fcap * sizeof(FieldInfo));
        }
        fields[nfields] = xstrdup(fname_tok->value);
        finfo[nfields].name = xstrdup(fname_tok->value);
        finfo[nfields].struct_type = ftype;
        finfo[nfields].is_ptr = is_ptr;
        nfields++;
    }
    eat(TK_OP, "}");
    eat(TK_OP, ";");

    /* Register in struct_defs for parser lookups */
    if (nstruct_defs >= 64) fatal("Too many struct definitions");
    struct_defs[nstruct_defs].name = xstrdup(name);
    struct_defs[nstruct_defs].fields = finfo;
    struct_defs[nstruct_defs].nfields = nfields;
    nstruct_defs++;

    StructDef sd;
    sd.name = name;
    sd.fields = fields;
    sd.nfields = nfields;
    sd.is_union = is_union;
    return sd;
}

/* ---- Enum definition ---- */

static void parse_enum_def(void) {
    eat(TK_KW, "enum");
    if (match(TK_ID, NULL))
        eat(TK_ID, NULL);  /* optional tag name */
    eat(TK_OP, "{");

    int value = 0;
    while (!match(TK_OP, "}")) {
        Tok *name_tok = eat(TK_ID, NULL);
        if (match(TK_OP, "=")) {
            eat(TK_OP, "=");
            /* support optional negative sign and integer literal */
            int neg = 0;
            if (match(TK_OP, "-")) {
                eat(TK_OP, "-");
                neg = 1;
            }
            Tok *num_tok = eat(TK_NUMBER, NULL);
            value = atoi(num_tok->value);
            if (neg) value = -value;
        }
        add_enum_const(name_tok->value, value);
        value++;
        if (match(TK_OP, ","))
            eat(TK_OP, ",");
    }
    eat(TK_OP, "}");
    eat(TK_OP, ";");
}

/* ---- VarDecl ---- */

static Stmt *parse_vardecl_stmt(void) {
    char *stype = parse_base_type();
    VarDeclEntry *entries = NULL;
    int count = 0;
    int ecap = 0;

    while (1) {
        int is_ptr = 0;
        while (match(TK_OP, "*")) {
            eat(TK_OP, "*");
            is_ptr = 1;
        }
        skip_qualifiers();
        Tok *name_tok = eat(TK_ID, NULL);
        char *name = xstrdup(name_tok->value);
        int arr_size = -1;
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            Tok *num = eat(TK_NUMBER, NULL);
            arr_size = atoi(num->value);
            eat(TK_OP, "]");
        }
        Expr *init = NULL;
        /* struct_type in decl: only for direct (non-pointer) struct variables */
        char *decl_stype = (stype && !is_ptr && arr_size < 0) ? xstrdup(stype) : NULL;
        if (!decl_stype && arr_size < 0 && match(TK_OP, "=")) {
            eat(TK_OP, "=");
            init = parse_expr(0);
        }

        if (count >= ecap) {
            ecap = ecap ? ecap * 2 : 4;
            entries = realloc(entries, ecap * sizeof(VarDeclEntry));
        }
        entries[count].name = name;
        entries[count].struct_type = decl_stype;
        entries[count].array_size = arr_size;
        entries[count].init = init;
        count++;

        if (stype)
            add_local(name, stype, is_ptr);

        if (match(TK_OP, ",")) {
            eat(TK_OP, ",");
            continue;
        }
        break;
    }
    eat(TK_OP, ";");

    VarDeclList vdl;
    vdl.entries = entries;
    vdl.count = count;
    return new_vardecl(vdl);
}

/* ---- Expressions ---- */

static int get_prec(const char *op) {
    if (strcmp(op, "||") == 0) return 1;
    if (strcmp(op, "&&") == 0) return 2;
    if (strcmp(op, "|") == 0) return 3;
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "&") == 0) return 5;
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) return 6;
    if (strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) return 7;
    if (strcmp(op, "<<") == 0 || strcmp(op, ">>") == 0) return 8;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 9;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) return 10;
    return -1;
}

/* Check if an op token is a compound assignment */
static int is_compound_assign(const char *op) {
    return (strcmp(op, "+=") == 0 || strcmp(op, "-=") == 0 ||
            strcmp(op, "*=") == 0 || strcmp(op, "/=") == 0 ||
            strcmp(op, "%=") == 0 || strcmp(op, "&=") == 0 ||
            strcmp(op, "|=") == 0 || strcmp(op, "^=") == 0 ||
            strcmp(op, "<<=") == 0 || strcmp(op, ">>=") == 0);
}

static Expr *parse_unary(void);
static Expr *parse_primary(void);

static Expr *parse_expr(int min_prec) {
    Expr *e = parse_unary();

    while (1) {
        Tok *t = cur();

        /* comma operator: lowest precedence, only in expression-statement context */
        if (t->kind == TK_OP && strcmp(t->value, ",") == 0 && min_prec < 0) {
            eat(TK_OP, ",");
            Expr *rhs = parse_expr(0);
            e = new_binary(",", e, rhs);
            continue;
        }

        /* ternary: lower precedence than all binary ops */
        if (t->kind == TK_OP && strcmp(t->value, "?") == 0 && min_prec <= 0) {
            eat(TK_OP, "?");
            Expr *then_e = parse_expr(0);
            eat(TK_OP, ":");
            Expr *else_e = parse_expr(0);
            e = new_ternary(e, then_e, else_e);
            continue;
        }

        /* assignment */
        if (t->kind == TK_OP && strcmp(t->value, "=") == 0 && min_prec <= 0) {
            eat(TK_OP, "=");
            Expr *rhs = parse_expr(0);
            e = new_assign(e, rhs);
            continue;
        }

        /* compound assignment: desugar x op= e to x = x op e */
        if (t->kind == TK_OP && is_compound_assign(t->value) && min_prec <= 0) {
            char *full_op = xstrdup(t->value);
            eat(TK_OP, NULL);
            /* Extract base op: remove trailing '=' */
            int olen = strlen(full_op);
            char *base_op = xmalloc(olen);
            memcpy(base_op, full_op, olen - 1);
            base_op[olen - 1] = '\0';
            Expr *rhs = parse_expr(0);
            e = new_assign(e, new_binary(base_op, e, rhs));
            continue;
        }

        if (t->kind != TK_OP) break;
        int prec = get_prec(t->value);
        if (prec < 0 || prec < min_prec) break;

        char *op = xstrdup(t->value);
        eat(TK_OP, NULL);
        Expr *rhs = parse_expr(prec + 1);
        e = new_binary(op, e, rhs);
    }

    return e;
}

static Expr *parse_unary(void) {
    /* pre-increment/decrement: desugar ++x to (x = x + 1), --x to (x = x - 1) */
    if (match(TK_OP, "++")) {
        eat(TK_OP, "++");
        Expr *rhs = parse_unary();
        return new_assign(rhs, new_binary("+", rhs, new_num(1)));
    }
    if (match(TK_OP, "--")) {
        eat(TK_OP, "--");
        Expr *rhs = parse_unary();
        return new_assign(rhs, new_binary("-", rhs, new_num(1)));
    }

    if (match(TK_OP, "-") || match(TK_OP, "!") || match(TK_OP, "*") || match(TK_OP, "&") || match(TK_OP, "~")) {
        char op = cur()->value[0];
        eat(TK_OP, NULL);
        Expr *rhs = parse_unary();
        return new_unary(op, rhs);
    }

    /* cast: (type)expr — disambiguate from parenthesized expression */
    if (match(TK_OP, "(")) {
        int saved = pos;
        eat(TK_OP, "(");
        skip_qualifiers();
        if (is_type_start()) {
            /* It's a cast — consume the type and closing paren, then parse unary */
            parse_base_type();
            while (match(TK_OP, "*")) eat(TK_OP, "*");
            eat(TK_OP, ")");
            Expr *operand = parse_unary();
            return operand; /* cast is a no-op for now */
        }
        /* Not a cast, backtrack and let parse_primary handle it */
        pos = saved;
    }

    return parse_primary();
}

static Expr *parse_primary(void) {
    Tok *t = cur();
    Expr *e;

    if (t->kind == TK_NUMBER) {
        eat(TK_NUMBER, NULL);
        e = new_num(atoi(t->value));
    } else if (t->kind == TK_STRING) {
        eat(TK_STRING, NULL);
        e = new_strlit(t->value);
    } else if (t->kind == TK_ID) {
        char *name = xstrdup(eat(TK_ID, NULL)->value);

        /* Check if it's an enum constant */
        int enum_val;
        if (!match(TK_OP, "(") && find_enum_const(name, &enum_val)) {
            e = new_num(enum_val);
        } else if (match(TK_OP, "(")) {
            eat(TK_OP, "(");
            ExprArray args = {NULL, 0, 0};
            if (!match(TK_OP, ")")) {
                while (1) {
                    exprarray_push(&args, parse_expr(0));
                    if (match(TK_OP, ",")) {
                        eat(TK_OP, ",");
                        continue;
                    }
                    break;
                }
            }
            eat(TK_OP, ")");
            e = new_call(name, args);
        } else {
            e = new_var(name);
        }
    } else if (match(TK_OP, "(")) {
        eat(TK_OP, "(");
        e = parse_expr(-1);
        eat(TK_OP, ")");
    } else if (match(TK_KW, "sizeof")) {
        /* Parse sizeof and return 8 (all our types are 8 bytes) */
        eat(TK_KW, NULL);
        if (match(TK_OP, "(")) {
            eat(TK_OP, "(");
            /* Could be sizeof(type) or sizeof(expr) */
            if (is_type_start()) {
                parse_base_type();
                while (match(TK_OP, "*")) eat(TK_OP, "*");
            } else {
                parse_expr(0);
            }
            eat(TK_OP, ")");
        } else {
            parse_unary();
        }
        e = new_num(8);
    } else {
        fatal("Unexpected token %s:'%s' at %d", tokkind_str(t->kind), t->value, t->pos);
        return NULL;
    }

    /* postfix: [], ., ->, ++, -- */
    while (match(TK_OP, "[") || match(TK_OP, ".") || match(TK_OP, "->") ||
           match(TK_OP, "++") || match(TK_OP, "--")) {
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            Expr *idx = parse_expr(0);
            eat(TK_OP, "]");
            e = new_index(e, idx);
        } else if (match(TK_OP, "++")) {
            eat(TK_OP, "++");
            e = new_postinc(e);
        } else if (match(TK_OP, "--")) {
            eat(TK_OP, "--");
            e = new_postdec(e);
        } else if (match(TK_OP, ".")) {
            eat(TK_OP, ".");
            char *field = xstrdup(eat(TK_ID, NULL)->value);
            const char *st = NULL;
            if (e->kind == ND_VAR) {
                LocalVar *lv = find_local(e->u.var_name);
                if (lv) st = lv->struct_type;
            } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
                st = field_struct_type(e->u.field.struct_type, e->u.field.field);
            } else if (e->kind == ND_INDEX && (e->u.index.base->kind == ND_FIELD || e->u.index.base->kind == ND_ARROW)) {
                st = field_struct_type(e->u.index.base->u.field.struct_type, e->u.index.base->u.field.field);
            }
            if (!st) fatal("Cannot resolve struct type for '.' at %d", cur()->pos);
            e = new_field(e, field, st);
        } else {
            eat(TK_OP, "->");
            char *field = xstrdup(eat(TK_ID, NULL)->value);
            const char *st = NULL;
            if (e->kind == ND_VAR) {
                LocalVar *lv = find_local(e->u.var_name);
                if (lv) st = lv->struct_type;
            } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
                st = field_struct_type(e->u.field.struct_type, e->u.field.field);
            } else if (e->kind == ND_INDEX && (e->u.index.base->kind == ND_FIELD || e->u.index.base->kind == ND_ARROW)) {
                st = field_struct_type(e->u.index.base->u.field.struct_type, e->u.index.base->u.field.field);
            }
            if (!st) fatal("Cannot resolve struct type for '->' at %d", cur()->pos);
            e = new_arrow(e, field, st);
        }
    }

    return e;
}

/* ---- Statements ---- */

static Block parse_block(void) {
    eat(TK_OP, "{");
    Block b;
    b.stmts.data = NULL;
    b.stmts.len = 0;
    b.stmts.cap = 0;
    while (!match(TK_OP, "}"))
        stmtarray_push(&b.stmts, parse_stmt());
    eat(TK_OP, "}");
    return b;
}

static int starts_type(void) {
    return (match(TK_KW, "int") || match(TK_KW, "char") || match(TK_KW, "void") ||
            match(TK_KW, "unsigned") || match(TK_KW, "signed") ||
            match(TK_KW, "long") || match(TK_KW, "short") ||
            match(TK_KW, "struct") || match(TK_KW, "union") || match(TK_KW, "const") ||
            match(TK_KW, "volatile") || match(TK_KW, "register") ||
            match(TK_KW, "static") || match(TK_KW, "enum") ||
            match(TK_KW, "_Bool") || match(TK_KW, "bool"));
}

static Stmt *parse_stmt(void) {
    if (match(TK_KW, "return")) {
        eat(TK_KW, "return");
        if (match(TK_OP, ";")) {
            eat(TK_OP, ";");
            return new_return(new_num(0));
        }
        Expr *e = parse_expr(0);
        eat(TK_OP, ";");
        return new_return(e);
    }

    if (match(TK_KW, "if")) {
        eat(TK_KW, "if");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        Block then_blk;
        if (match(TK_OP, "{")) {
            then_blk = parse_block();
        } else {
            /* single statement */
            then_blk.stmts.data = NULL;
            then_blk.stmts.len = 0;
            then_blk.stmts.cap = 0;
            stmtarray_push(&then_blk.stmts, parse_stmt());
        }
        Block *else_blk = NULL;
        if (match(TK_KW, "else")) {
            eat(TK_KW, "else");
            else_blk = xmalloc(sizeof(Block));
            if (match(TK_KW, "if")) {
                /* else if: wrap the if statement in a synthetic block */
                Stmt *inner_if = parse_stmt();
                else_blk->stmts.data = NULL;
                else_blk->stmts.len = 0;
                else_blk->stmts.cap = 0;
                stmtarray_push(&else_blk->stmts, inner_if);
            } else if (match(TK_OP, "{")) {
                *else_blk = parse_block();
            } else {
                else_blk->stmts.data = NULL;
                else_blk->stmts.len = 0;
                else_blk->stmts.cap = 0;
                stmtarray_push(&else_blk->stmts, parse_stmt());
            }
        }
        return new_if(cond, then_blk, else_blk);
    }

    if (match(TK_KW, "while")) {
        eat(TK_KW, "while");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        Block body;
        if (match(TK_OP, "{")) {
            body = parse_block();
        } else {
            body.stmts.data = NULL;
            body.stmts.len = 0;
            body.stmts.cap = 0;
            stmtarray_push(&body.stmts, parse_stmt());
        }
        return new_while(cond, body);
    }

    if (match(TK_KW, "do")) {
        eat(TK_KW, "do");
        Block body;
        if (match(TK_OP, "{")) {
            body = parse_block();
        } else {
            body.stmts.data = NULL;
            body.stmts.len = 0;
            body.stmts.cap = 0;
            stmtarray_push(&body.stmts, parse_stmt());
        }
        eat(TK_KW, "while");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        eat(TK_OP, ";");
        return new_dowhile(cond, body);
    }

    if (match(TK_KW, "for")) {
        eat(TK_KW, "for");
        eat(TK_OP, "(");

        Stmt *init = NULL;
        if (starts_type()) {
            init = parse_vardecl_stmt();
        } else if (match(TK_OP, ";")) {
            eat(TK_OP, ";");
        } else {
            Expr *e = parse_expr(0);
            eat(TK_OP, ";");
            init = new_exprstmt(e);
        }

        Expr *cond = NULL;
        if (!match(TK_OP, ";"))
            cond = parse_expr(0);
        eat(TK_OP, ";");

        Expr *post = NULL;
        if (!match(TK_OP, ")"))
            post = parse_expr(-1);
        eat(TK_OP, ")");

        Block body;
        if (match(TK_OP, "{")) {
            body = parse_block();
        } else {
            body.stmts.data = NULL;
            body.stmts.len = 0;
            body.stmts.cap = 0;
            stmtarray_push(&body.stmts, parse_stmt());
        }
        return new_for(init, cond, post, body);
    }

    if (match(TK_KW, "switch")) {
        eat(TK_KW, "switch");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        eat(TK_OP, "{");

        SwitchCase *cases = NULL;
        int ncases = 0;
        int ccap = 0;

        while (!match(TK_OP, "}")) {
            Expr *case_val = NULL;
            if (match(TK_KW, "case")) {
                eat(TK_KW, "case");
                /* parse case value: optional '-', then a number or enum constant */
                int neg = 0;
                if (match(TK_OP, "-")) {
                    eat(TK_OP, "-");
                    neg = 1;
                }
                if (match(TK_NUMBER, NULL)) {
                    int val = atoi(eat(TK_NUMBER, NULL)->value);
                    if (neg) val = -val;
                    case_val = new_num(val);
                } else if (match(TK_ID, NULL)) {
                    char *name = xstrdup(eat(TK_ID, NULL)->value);
                    int ev;
                    if (find_enum_const(name, &ev)) {
                        if (neg) ev = -ev;
                        case_val = new_num(ev);
                    } else {
                        fatal("Unknown case value '%s'", name);
                    }
                } else {
                    fatal("Expected case value at %d", cur()->pos);
                }
                eat(TK_OP, ":");
            } else if (match(TK_KW, "default")) {
                eat(TK_KW, "default");
                eat(TK_OP, ":");
                case_val = NULL;
            } else {
                fatal("Expected 'case' or 'default' in switch at %d", cur()->pos);
            }

            if (ncases >= ccap) {
                ccap = ccap ? ccap * 2 : 8;
                cases = realloc(cases, ccap * sizeof(SwitchCase));
            }
            cases[ncases].value = case_val;
            cases[ncases].stmts.data = NULL;
            cases[ncases].stmts.len = 0;
            cases[ncases].stmts.cap = 0;

            /* Parse statements until next case/default/} */
            while (!match(TK_KW, "case") && !match(TK_KW, "default") && !match(TK_OP, "}")) {
                stmtarray_push(&cases[ncases].stmts, parse_stmt());
            }
            ncases++;
        }
        eat(TK_OP, "}");
        return new_switch(cond, cases, ncases);
    }

    if (match(TK_KW, "break")) {
        eat(TK_KW, "break");
        eat(TK_OP, ";");
        return new_break();
    }

    if (match(TK_KW, "continue")) {
        eat(TK_KW, "continue");
        eat(TK_OP, ";");
        return new_continue();
    }

    if (match(TK_KW, "goto")) {
        eat(TK_KW, "goto");
        char *label = xstrdup(eat(TK_ID, NULL)->value);
        eat(TK_OP, ";");
        return new_goto(label);
    }

    /* Label detection: identifier followed by ':' (not '::') */
    if (cur()->kind == TK_ID && pos + 1 < ntoks &&
        toks[pos+1].kind == TK_OP && strcmp(toks[pos+1].value, ":") == 0) {
        char *label = xstrdup(eat(TK_ID, NULL)->value);
        eat(TK_OP, ":");
        /* A label must be followed by a statement */
        Stmt *stmt;
        if (match(TK_OP, "}")) {
            /* Label at end of block — attach a no-op expression statement */
            stmt = new_exprstmt(new_num(0));
        } else {
            stmt = parse_stmt();
        }
        return new_label(label, stmt);
    }

    /* Variable declaration: starts with a type keyword */
    if (starts_type()) {
        /* skip 'static' for local statics (treat as regular local) */
        if (match(TK_KW, "static")) eat(TK_KW, "static");
        return parse_vardecl_stmt();
    }

    /* empty statement */
    if (match(TK_OP, ";")) {
        eat(TK_OP, ";");
        return new_exprstmt(new_num(0));
    }

    Expr *e = parse_expr(-1);
    eat(TK_OP, ";");
    return new_exprstmt(e);
}

/* ---- Function ---- */

/* Parse a function definition or prototype.
   Returns 1 if a full definition was parsed (fd is filled in),
   0 if it was just a prototype (semicolon after params). */
static int parse_func_or_proto(FuncDef *fd, FuncProto *proto, int is_static) {
    nlocal_vars = 0;
    parse_base_type();  /* return type */
    int ret_is_ptr = 0;
    while (match(TK_OP, "*")) { eat(TK_OP, "*"); ret_is_ptr = 1; }
    Tok *name_tok = eat(TK_ID, NULL);
    eat(TK_OP, "(");

    char **params = NULL;
    int nparams = 0;
    int pcap = 0;

    if (!match(TK_OP, ")")) {
        /* Check for void parameter: foo(void) */
        if (match(TK_KW, "void") && pos + 1 < ntoks &&
            toks[pos+1].kind == TK_OP && strcmp(toks[pos+1].value, ")") == 0) {
            eat(TK_KW, "void");
        } else {
            while (1) {
                /* Handle ... (variadic) */
                if (match(TK_OP, ".")) {
                    eat(TK_OP, ".");
                    eat(TK_OP, ".");
                    eat(TK_OP, ".");
                    break;
                }
                char *stype = parse_base_type();
                int is_ptr = 0;
                while (match(TK_OP, "*")) {
                    eat(TK_OP, "*");
                    is_ptr = 1;
                }
                skip_qualifiers();
                /* Parameter might be unnamed (in prototypes) */
                if (match(TK_ID, NULL)) {
                    Tok *pname = eat(TK_ID, NULL);
                    /* skip array params like char buf[] */
                    if (match(TK_OP, "[")) {
                        eat(TK_OP, "[");
                        if (!match(TK_OP, "]"))
                            eat(TK_NUMBER, NULL);
                        eat(TK_OP, "]");
                    }
                    if (nparams >= pcap) {
                        pcap = pcap ? pcap * 2 : 8;
                        params = realloc(params, pcap * sizeof(char *));
                    }
                    params[nparams++] = xstrdup(pname->value);
                    if (stype)
                        add_local(pname->value, stype, is_ptr);
                }
                if (match(TK_OP, ",")) {
                    eat(TK_OP, ",");
                    continue;
                }
                break;
            }
        }
    }
    eat(TK_OP, ")");

    /* Prototype: just a semicolon after params */
    if (match(TK_OP, ";")) {
        eat(TK_OP, ";");
        if (proto) {
            proto->name = xstrdup(name_tok->value);
            proto->ret_is_ptr = ret_is_ptr;
        }
        return 0;
    }

    Block body = parse_block();

    fd->name = xstrdup(name_tok->value);
    fd->params = params;
    fd->nparams = nparams;
    fd->body = body;
    fd->is_static = is_static;
    fd->ret_is_ptr = ret_is_ptr;
    return 1;
}

/* Parse an extern declaration: extern type [*]* name [[ N ]] ; */
static GlobalDecl parse_extern_decl(void) {
    eat(TK_KW, "extern");
    /* extern might be followed by a string literal (linkage spec) - skip */

    char *stype = parse_base_type();
    int is_ptr = 0;
    while (match(TK_OP, "*")) {
        eat(TK_OP, "*");
        is_ptr = 1;
    }
    Tok *name_tok = eat(TK_ID, NULL);
    int arr_size = -1;
    if (match(TK_OP, "[")) {
        eat(TK_OP, "[");
        if (!match(TK_OP, "]"))
            arr_size = atoi(eat(TK_NUMBER, NULL)->value);
        eat(TK_OP, "]");
    }
    /* Skip function prototype: extern int foo(int x); */
    if (match(TK_OP, "(")) {
        eat(TK_OP, "(");
        int depth = 1;
        while (depth > 0) {
            if (match(TK_OP, "(")) depth++;
            else if (match(TK_OP, ")")) depth--;
            if (depth > 0) eat(cur()->kind, NULL);
        }
        eat(TK_OP, ")");
    }
    eat(TK_OP, ";");

    GlobalDecl gd;
    gd.name = xstrdup(name_tok->value);
    gd.struct_type = stype ? xstrdup(stype) : NULL;
    gd.is_ptr = is_ptr;
    gd.array_size = arr_size;
    gd.init = NULL;
    gd.is_extern = 1;
    gd.is_static = 0;
    return gd;
}

/* ---- Lookahead: is this a function or a global variable? ---- */
/* After parsing base type, peek: type [*]* name '(' => function, else => global */
static int is_func_lookahead(void) {
    int saved = pos;
    /* skip base type (already consumed by caller) */
    /* skip stars */
    while (match(TK_OP, "*")) eat(TK_OP, "*");
    skip_qualifiers();
    if (!match(TK_ID, NULL)) { pos = saved; return 0; }
    eat(TK_ID, NULL);
    int result = match(TK_OP, "(");
    pos = saved;
    return result;
}

/* ---- Global variable declaration ---- */
static GlobalDecl parse_global_decl(int is_static) {
    char *stype = parse_base_type();
    int is_ptr = 0;
    while (match(TK_OP, "*")) {
        eat(TK_OP, "*");
        is_ptr = 1;
    }
    skip_qualifiers();
    Tok *name_tok = eat(TK_ID, NULL);
    int arr_size = -1;
    if (match(TK_OP, "[")) {
        eat(TK_OP, "[");
        if (!match(TK_OP, "]"))
            arr_size = atoi(eat(TK_NUMBER, NULL)->value);
        eat(TK_OP, "]");
    }
    Expr *init = NULL;
    if (arr_size < 0 && match(TK_OP, "=")) {
        eat(TK_OP, "=");
        /* Handle negative initializers */
        if (match(TK_OP, "-")) {
            eat(TK_OP, "-");
            Tok *num = eat(TK_NUMBER, NULL);
            init = new_num(-atoi(num->value));
        } else {
            init = parse_expr(0);
        }
    }
    eat(TK_OP, ";");

    GlobalDecl gd;
    gd.name = xstrdup(name_tok->value);
    gd.struct_type = stype ? xstrdup(stype) : NULL;
    gd.is_ptr = is_ptr;
    gd.array_size = arr_size;
    gd.init = init;
    gd.is_extern = 0;
    gd.is_static = is_static;
    return gd;
}

/* Try to parse a function or global with the given static flag */
static void parse_func_or_global(int is_static,
                                  FuncDef **funcs, int *nfuncs, int *fcap,
                                  GlobalDecl **globals, int *nglobals, int *gcap,
                                  FuncProto **protos, int *nprotos, int *pcap) {
    int saved = pos;
    parse_base_type();
    if (is_func_lookahead()) {
        pos = saved;
        FuncDef fd;
        FuncProto proto;
        if (parse_func_or_proto(&fd, &proto, is_static)) {
            if (*nfuncs >= *fcap) {
                *fcap = *fcap ? *fcap * 2 : 4;
                *funcs = realloc(*funcs, *fcap * sizeof(FuncDef));
            }
            (*funcs)[(*nfuncs)++] = fd;
        } else {
            /* Store prototype */
            if (*nprotos >= *pcap) {
                *pcap = *pcap ? *pcap * 2 : 8;
                *protos = realloc(*protos, *pcap * sizeof(FuncProto));
            }
            (*protos)[(*nprotos)++] = proto;
        }
    } else {
        pos = saved;
        if (*nglobals >= *gcap) {
            *gcap = *gcap ? *gcap * 2 : 8;
            *globals = realloc(*globals, *gcap * sizeof(GlobalDecl));
        }
        (*globals)[(*nglobals)++] = parse_global_decl(is_static);
    }
}

/* ---- Program ---- */

Program *parse_program(TokArray tokarr) {
    toks = tokarr.data;
    ntoks = tokarr.len;
    pos = 0;
    nstruct_defs = 0;
    nlocal_vars = 0;
    nenum_consts = 0;

    /* Add sizeof as a keyword for recognition */

    StructDef *structs = NULL;
    int nstructs = 0, scap = 0;
    FuncDef *funcs = NULL;
    int nfuncs = 0, fcap = 0;
    GlobalDecl *globals = NULL;
    int nglobals = 0, gcap = 0;
    FuncProto *protos = NULL;
    int nprotos = 0, pcap2 = 0;

    while (!match(TK_EOF, NULL)) {
        /* typedef: skip entirely */
        if (match(TK_KW, "typedef")) {
            eat(TK_KW, "typedef");
            /* Skip everything until semicolon, handling nested parens/braces */
            int depth = 0;
            while (1) {
                if (match(TK_OP, "(") || match(TK_OP, "{")) {
                    depth++;
                    eat(TK_OP, NULL);
                } else if (match(TK_OP, ")") || match(TK_OP, "}")) {
                    depth--;
                    eat(TK_OP, NULL);
                } else if (depth == 0 && match(TK_OP, ";")) {
                    eat(TK_OP, ";");
                    break;
                } else {
                    eat(cur()->kind, NULL);
                }
            }
            continue;
        }

        /* extern declarations: add to globals as extern */
        if (match(TK_KW, "extern")) {
            if (nglobals >= gcap) {
                gcap = gcap ? gcap * 2 : 8;
                globals = realloc(globals, gcap * sizeof(GlobalDecl));
            }
            globals[nglobals++] = parse_extern_decl();
            continue;
        }

        /* enum definition */
        if (match(TK_KW, "enum")) {
            /* Peek: is this "enum { ... }" or "enum Name { ... }" (definition)
               vs "enum Name varname" (usage as type)? */
            int saved = pos;
            eat(TK_KW, "enum");
            if (match(TK_ID, NULL)) eat(TK_ID, NULL);
            if (match(TK_OP, "{")) {
                pos = saved;
                parse_enum_def();
            } else {
                /* enum used as type for function or global */
                pos = saved;
                parse_func_or_global(0, &funcs, &nfuncs, &fcap, &globals, &nglobals, &gcap, &protos, &nprotos, &pcap2);
            }
            continue;
        }

        /* static */
        if (match(TK_KW, "static")) {
            eat(TK_KW, "static");
            if (match(TK_KW, "inline")) eat(TK_KW, "inline");
            parse_func_or_global(1, &funcs, &nfuncs, &fcap, &globals, &nglobals, &gcap, &protos, &nprotos, &pcap2);
            continue;
        }

        /* inline */
        if (match(TK_KW, "inline")) {
            eat(TK_KW, "inline");
            if (match(TK_KW, "static")) eat(TK_KW, "static");
            parse_func_or_global(1, &funcs, &nfuncs, &fcap, &globals, &nglobals, &gcap, &protos, &nprotos, &pcap2);
            continue;
        }

        if (match(TK_KW, "struct") || match(TK_KW, "union")) {
            int is_union_kw = match(TK_KW, "union");
            int saved = pos;
            if (is_union_kw)
                eat(TK_KW, "union");
            else
                eat(TK_KW, "struct");
            eat(TK_ID, NULL);
            if (match(TK_OP, "{")) {
                pos = saved;
                if (nstructs >= scap) {
                    scap = scap ? scap * 2 : 4;
                    structs = realloc(structs, scap * sizeof(StructDef));
                }
                structs[nstructs++] = parse_struct_or_union_def(is_union_kw);
            } else {
                /* struct/union return type: could be function, prototype, or global */
                pos = saved;
                parse_func_or_global(0, &funcs, &nfuncs, &fcap, &globals, &nglobals, &gcap, &protos, &nprotos, &pcap2);
            }
        } else {
            /* type-based return: could be function, prototype, or global */
            parse_func_or_global(0, &funcs, &nfuncs, &fcap, &globals, &nglobals, &gcap, &protos, &nprotos, &pcap2);
        }
    }

    Program *prog = xmalloc(sizeof(Program));
    prog->structs = structs;
    prog->nstructs = nstructs;
    prog->funcs = funcs;
    prog->nfuncs = nfuncs;
    prog->globals = globals;
    prog->nglobals = nglobals;
    prog->protos = protos;
    prog->nprotos = nprotos;
    return prog;
}
