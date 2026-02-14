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

static Tok *toks;
static int ntoks;
static int pos;

static StructDefInfo struct_defs[64];
static int nstruct_defs;

static LocalVar local_vars[256];
static int nlocal_vars;

/* ---- Helpers ---- */

static Tok *cur(void) {
    return &toks[pos];
}

static Tok *eat(TokKind kind, const char *value) {
    Tok *t = cur();
    if (t->kind != kind)
        fatal("Expected %s, got %s at %d", tokkind_str(kind), tokkind_str(t->kind), t->pos);
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

/* ---- Type parsing ---- */

/* Returns struct name (allocated) or NULL for 'int' */
static char *parse_base_type(void) {
    if (match(TK_KW, "int")) {
        eat(TK_KW, "int");
        return NULL;
    }
    if (match(TK_KW, "struct")) {
        eat(TK_KW, "struct");
        Tok *name = eat(TK_ID, NULL);
        return xstrdup(name->value);
    }
    fatal("Expected type, got '%s' at %d", cur()->value, cur()->pos);
    return NULL;
}

/* ---- Forward declarations ---- */
static Expr *parse_expr(int min_prec);
static Stmt *parse_stmt(void);
static Block parse_block(void);

/* ---- Struct definition ---- */

static StructDef parse_struct_def(void) {
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
    return sd;
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
    if (strcmp(op, "&") == 0) return 4;
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) return 5;
    if (strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) return 6;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 7;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) return 8;
    return -1;
}

static Expr *parse_unary(void);
static Expr *parse_primary(void);

static Expr *parse_expr(int min_prec) {
    Expr *e = parse_unary();

    while (1) {
        Tok *t = cur();

        /* assignment */
        if (t->kind == TK_OP && strcmp(t->value, "=") == 0 && min_prec <= 0) {
            eat(TK_OP, "=");
            Expr *rhs = parse_expr(0);
            e = new_assign(e, rhs);
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
    if (match(TK_OP, "-") || match(TK_OP, "!") || match(TK_OP, "*") || match(TK_OP, "&")) {
        char op = cur()->value[0];
        eat(TK_OP, NULL);
        Expr *rhs = parse_unary();
        return new_unary(op, rhs);
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
        if (match(TK_OP, "(")) {
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
        e = parse_expr(0);
        eat(TK_OP, ")");
    } else {
        fatal("Unexpected token %s:'%s' at %d", tokkind_str(t->kind), t->value, t->pos);
        return NULL;
    }

    /* postfix: [], ., -> */
    while (match(TK_OP, "[") || match(TK_OP, ".") || match(TK_OP, "->")) {
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            Expr *idx = parse_expr(0);
            eat(TK_OP, "]");
            e = new_index(e, idx);
        } else if (match(TK_OP, ".")) {
            eat(TK_OP, ".");
            char *field = xstrdup(eat(TK_ID, NULL)->value);
            const char *st = NULL;
            if (e->kind == ND_VAR) {
                LocalVar *lv = find_local(e->u.var_name);
                if (lv) st = lv->struct_type;
            } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
                st = field_struct_type(e->u.field.struct_type, e->u.field.field);
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

static Stmt *parse_stmt(void) {
    if (match(TK_KW, "return")) {
        eat(TK_KW, "return");
        Expr *e = parse_expr(0);
        eat(TK_OP, ";");
        return new_return(e);
    }

    if (match(TK_KW, "if")) {
        eat(TK_KW, "if");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        Block then_blk = parse_block();
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
            } else {
                *else_blk = parse_block();
            }
        }
        return new_if(cond, then_blk, else_blk);
    }

    if (match(TK_KW, "while")) {
        eat(TK_KW, "while");
        eat(TK_OP, "(");
        Expr *cond = parse_expr(0);
        eat(TK_OP, ")");
        Block body = parse_block();
        return new_while(cond, body);
    }

    if (match(TK_KW, "for")) {
        eat(TK_KW, "for");
        eat(TK_OP, "(");

        Stmt *init = NULL;
        if (match(TK_KW, "int") || match(TK_KW, "struct")) {
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
            post = parse_expr(0);
        eat(TK_OP, ")");

        Block body = parse_block();
        return new_for(init, cond, post, body);
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

    if (match(TK_KW, "int") || match(TK_KW, "struct"))
        return parse_vardecl_stmt();

    Expr *e = parse_expr(0);
    eat(TK_OP, ";");
    return new_exprstmt(e);
}

/* ---- Function ---- */

/* Parse a function definition or prototype.
   Returns 1 if a full definition was parsed (fd is filled in),
   0 if it was just a prototype (semicolon after params). */
static int parse_func_or_proto(FuncDef *fd) {
    nlocal_vars = 0;
    parse_base_type();  /* return type, ignored */
    while (match(TK_OP, "*")) eat(TK_OP, "*");
    Tok *name_tok = eat(TK_ID, NULL);
    eat(TK_OP, "(");

    char **params = NULL;
    int nparams = 0;
    int pcap = 0;

    if (!match(TK_OP, ")")) {
        while (1) {
            char *stype = parse_base_type();
            int is_ptr = 0;
            while (match(TK_OP, "*")) {
                eat(TK_OP, "*");
                is_ptr = 1;
            }
            Tok *pname = eat(TK_ID, NULL);
            if (nparams >= pcap) {
                pcap = pcap ? pcap * 2 : 8;
                params = realloc(params, pcap * sizeof(char *));
            }
            params[nparams++] = xstrdup(pname->value);
            if (stype)
                add_local(pname->value, stype, is_ptr);
            if (match(TK_OP, ",")) {
                eat(TK_OP, ",");
                continue;
            }
            break;
        }
    }
    eat(TK_OP, ")");

    /* Prototype: just a semicolon after params */
    if (match(TK_OP, ";")) {
        eat(TK_OP, ";");
        return 0;
    }

    Block body = parse_block();

    fd->name = xstrdup(name_tok->value);
    fd->params = params;
    fd->nparams = nparams;
    fd->body = body;
    return 1;
}

/* Parse an extern declaration: extern type [*]* name [[ N ]] ; */
static GlobalDecl parse_extern_decl(void) {
    eat(TK_KW, "extern");
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
    eat(TK_OP, ";");

    GlobalDecl gd;
    gd.name = xstrdup(name_tok->value);
    gd.struct_type = stype ? xstrdup(stype) : NULL;
    gd.is_ptr = is_ptr;
    gd.array_size = arr_size;
    gd.init = NULL;
    gd.is_extern = 1;
    return gd;
}

/* ---- Lookahead: is this a function or a global variable? ---- */
/* After parsing base type, peek: type [*]* name '(' => function, else => global */
static int is_func_lookahead(void) {
    int saved = pos;
    /* skip base type (already consumed by caller) */
    /* skip stars */
    while (match(TK_OP, "*")) eat(TK_OP, "*");
    if (!match(TK_ID, NULL)) { pos = saved; return 0; }
    eat(TK_ID, NULL);
    int result = match(TK_OP, "(");
    pos = saved;
    return result;
}

/* ---- Global variable declaration ---- */
static GlobalDecl parse_global_decl(void) {
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
        arr_size = atoi(eat(TK_NUMBER, NULL)->value);
        eat(TK_OP, "]");
    }
    Expr *init = NULL;
    if (arr_size < 0 && match(TK_OP, "=")) {
        eat(TK_OP, "=");
        init = parse_expr(0);
    }
    eat(TK_OP, ";");

    GlobalDecl gd;
    gd.name = xstrdup(name_tok->value);
    gd.struct_type = stype ? xstrdup(stype) : NULL;
    gd.is_ptr = is_ptr;
    gd.array_size = arr_size;
    gd.init = init;
    gd.is_extern = 0;
    return gd;
}

/* ---- Program ---- */

Program *parse_program(TokArray tokarr) {
    toks = tokarr.data;
    ntoks = tokarr.len;
    pos = 0;
    nstruct_defs = 0;
    nlocal_vars = 0;

    StructDef *structs = NULL;
    int nstructs = 0, scap = 0;
    FuncDef *funcs = NULL;
    int nfuncs = 0, fcap = 0;
    GlobalDecl *globals = NULL;
    int nglobals = 0, gcap = 0;

    while (!match(TK_EOF, NULL)) {
        /* extern declarations: add to globals as extern */
        if (match(TK_KW, "extern")) {
            if (nglobals >= gcap) {
                gcap = gcap ? gcap * 2 : 8;
                globals = realloc(globals, gcap * sizeof(GlobalDecl));
            }
            globals[nglobals++] = parse_extern_decl();
            continue;
        }

        if (match(TK_KW, "struct")) {
            int saved = pos;
            eat(TK_KW, "struct");
            eat(TK_ID, NULL);
            if (match(TK_OP, "{")) {
                pos = saved;
                if (nstructs >= scap) {
                    scap = scap ? scap * 2 : 4;
                    structs = realloc(structs, scap * sizeof(StructDef));
                }
                structs[nstructs++] = parse_struct_def();
            } else {
                /* struct return type: could be function, prototype, or global */
                pos = saved;
                int saved2 = pos;
                parse_base_type();
                if (is_func_lookahead()) {
                    pos = saved2;
                    FuncDef fd;
                    if (parse_func_or_proto(&fd)) {
                        if (nfuncs >= fcap) {
                            fcap = fcap ? fcap * 2 : 4;
                            funcs = realloc(funcs, fcap * sizeof(FuncDef));
                        }
                        funcs[nfuncs++] = fd;
                    }
                } else {
                    pos = saved2;
                    if (nglobals >= gcap) {
                        gcap = gcap ? gcap * 2 : 8;
                        globals = realloc(globals, gcap * sizeof(GlobalDecl));
                    }
                    globals[nglobals++] = parse_global_decl();
                }
            }
        } else {
            /* int return type: could be function, prototype, or global */
            int saved = pos;
            parse_base_type();
            if (is_func_lookahead()) {
                pos = saved;
                FuncDef fd;
                if (parse_func_or_proto(&fd)) {
                    if (nfuncs >= fcap) {
                        fcap = fcap ? fcap * 2 : 4;
                        funcs = realloc(funcs, fcap * sizeof(FuncDef));
                    }
                    funcs[nfuncs++] = fd;
                }
            } else {
                pos = saved;
                if (nglobals >= gcap) {
                    gcap = gcap ? gcap * 2 : 8;
                    globals = realloc(globals, gcap * sizeof(GlobalDecl));
                }
                globals[nglobals++] = parse_global_decl();
            }
        }
    }

    Program *prog = xmalloc(sizeof(Program));
    prog->structs = structs;
    prog->nstructs = nstructs;
    prog->funcs = funcs;
    prog->nfuncs = nfuncs;
    prog->globals = globals;
    prog->nglobals = nglobals;
    return prog;
}
