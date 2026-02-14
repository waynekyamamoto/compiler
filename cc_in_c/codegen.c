#include "codegen.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- Codegen state ---- */

static Buf out;
static int label_id;

/* String pool */
typedef struct {
    char *decoded;
    char *label;
} StrPoolEntry;

static StrPoolEntry str_pool[256];
static int nstr_pool;

/* Loop stack */
typedef struct {
    char *brk_label;
    char *cont_label;
} LoopEntry;

static LoopEntry loop_stack[64];
static int nloop_stack;

/* Struct definitions: name -> field names */
typedef struct {
    char *name;
    char **fields;
    int nfields;
} CgStructDef;

static CgStructDef cg_structs[64];
static int ncg_structs;

/* Global variables */
typedef struct {
    char *name;
    int is_array;
    int is_structvar;
} GlobalVarEntry;

static GlobalVarEntry global_vars[1024];
static int nglobal_vars;

/* ---- Function layout ---- */

typedef struct {
    char *name;
    int offset;
} SlotEntry;

typedef struct {
    char *name;
    int count;
} ArrayEntry;

typedef struct {
    char *name;
    char *struct_type;
} StructVarEntry;

typedef struct {
    SlotEntry slots[256];
    int nslots;
    ArrayEntry arrays[64];
    int narrays;
    StructVarEntry structvars[64];
    int nstructvars;
    int stack_size;
} FuncLayout;

/* ---- Helpers ---- */

static void emit(const char *fmt, ...) {
    char tmp[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(tmp, sizeof(tmp), fmt, ap);
    va_end(ap);
    buf_append(&out, tmp);
    buf_push(&out, '\n');
}

static char *new_label(const char *base) {
    label_id++;
    char tmp[64];
    snprintf(tmp, sizeof(tmp), "L_%s_%d", base, label_id);
    return xstrdup(tmp);
}

static int find_slot(FuncLayout *layout, const char *name) {
    for (int i = 0; i < layout->nslots; i++)
        if (strcmp(layout->slots[i].name, name) == 0)
            return layout->slots[i].offset;
    return -1;
}

static int is_array(FuncLayout *layout, const char *name) {
    for (int i = 0; i < layout->narrays; i++)
        if (strcmp(layout->arrays[i].name, name) == 0)
            return 1;
    return 0;
}

static int is_structvar(FuncLayout *layout, const char *name) {
    for (int i = 0; i < layout->nstructvars; i++)
        if (strcmp(layout->structvars[i].name, name) == 0)
            return 1;
    return 0;
}

static CgStructDef *find_cg_struct(const char *name) {
    for (int i = 0; i < ncg_structs; i++)
        if (strcmp(cg_structs[i].name, name) == 0)
            return &cg_structs[i];
    return NULL;
}

static int field_index(const char *struct_name, const char *field_name) {
    CgStructDef *sd = find_cg_struct(struct_name);
    if (!sd) fatal("Unknown struct '%s' in codegen", struct_name);
    for (int i = 0; i < sd->nfields; i++)
        if (strcmp(sd->fields[i], field_name) == 0)
            return i;
    fatal("Struct '%s' has no field '%s'", struct_name, field_name);
    return -1;
}

static GlobalVarEntry *find_global(const char *name) {
    for (int i = 0; i < nglobal_vars; i++)
        if (strcmp(global_vars[i].name, name) == 0)
            return &global_vars[i];
    return NULL;
}

static char *intern_string(const char *decoded) {
    for (int i = 0; i < nstr_pool; i++)
        if (strcmp(str_pool[i].decoded, decoded) == 0)
            return str_pool[i].label;
    if (nstr_pool >= 256) fatal("Too many string literals");
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "l_.str_%d", nstr_pool + 1);
    str_pool[nstr_pool].decoded = xstrdup(decoded);
    str_pool[nstr_pool].label = xstrdup(tmp);
    nstr_pool++;
    return str_pool[nstr_pool - 1].label;
}

/* ---- C string decode/escape ---- */

static char *decode_c_string(const char *lit) {
    Buf b;
    buf_init(&b);
    for (int i = 0; lit[i]; ) {
        if (lit[i] != '\\') {
            buf_push(&b, lit[i++]);
            continue;
        }
        i++;
        if (!lit[i]) fatal("Bad escape in string literal");
        switch (lit[i]) {
        case 'n': buf_push(&b, '\n'); break;
        case 't': buf_push(&b, '\t'); break;
        case 'r': buf_push(&b, '\r'); break;
        case '\\': buf_push(&b, '\\'); break;
        case '"': buf_push(&b, '"'); break;
        case '0': buf_push(&b, '\0'); break;
        default: fatal("Unsupported escape: \\%c", lit[i]);
        }
        i++;
    }
    return buf_detach(&b);
}

static char *asm_escape_string(const char *s) {
    Buf b;
    buf_init(&b);
    for (int i = 0; s[i]; i++) {
        switch (s[i]) {
        case '\\': buf_append(&b, "\\\\"); break;
        case '"':  buf_append(&b, "\\\""); break;
        case '\n': buf_append(&b, "\\n"); break;
        case '\t': buf_append(&b, "\\t"); break;
        case '\r': buf_append(&b, "\\r"); break;
        case '\0': buf_append(&b, "\\0"); break;
        default:   buf_push(&b, s[i]); break;
        }
    }
    return buf_detach(&b);
}

/* ---- Layout ---- */

static void layout_add_slot(FuncLayout *layout, const char *name, int offset) {
    if (layout->nslots >= 256) fatal("Too many slots");
    layout->slots[layout->nslots].name = xstrdup(name);
    layout->slots[layout->nslots].offset = offset;
    layout->nslots++;
}

static void walk_block_for_layout(Block *b, FuncLayout *layout, int *offset);

static void walk_stmts_for_layout(StmtArray *stmts, FuncLayout *layout, int *offset) {
    for (int i = 0; i < stmts->len; i++) {
        Stmt *st = stmts->data[i];
        if (st->kind == ST_VARDECL) {
            for (int j = 0; j < st->u.vardecl.count; j++) {
                VarDeclEntry *e = &st->u.vardecl.entries[j];
                if (find_slot(layout, e->name) >= 0)
                    fatal("Duplicate variable '%s'", e->name);
                if (e->struct_type) {
                    CgStructDef *sd = find_cg_struct(e->struct_type);
                    if (!sd) fatal("Unknown struct '%s'", e->struct_type);
                    *offset += sd->nfields * 8;
                    if (layout->nstructvars >= 64) fatal("Too many struct vars");
                    layout->structvars[layout->nstructvars].name = xstrdup(e->name);
                    layout->structvars[layout->nstructvars].struct_type = xstrdup(e->struct_type);
                    layout->nstructvars++;
                } else if (e->array_size >= 0) {
                    *offset += e->array_size * 8;
                    if (layout->narrays >= 64) fatal("Too many arrays");
                    layout->arrays[layout->narrays].name = xstrdup(e->name);
                    layout->arrays[layout->narrays].count = e->array_size;
                    layout->narrays++;
                } else {
                    *offset += 8;
                }
                layout_add_slot(layout, e->name, *offset);
            }
        } else if (st->kind == ST_IF) {
            walk_block_for_layout(&st->u.if_s.then_blk, layout, offset);
            if (st->u.if_s.else_blk)
                walk_block_for_layout(st->u.if_s.else_blk, layout, offset);
        } else if (st->kind == ST_WHILE) {
            walk_block_for_layout(&st->u.while_s.body, layout, offset);
        } else if (st->kind == ST_FOR) {
            if (st->u.for_s.init && st->u.for_s.init->kind == ST_VARDECL) {
                StmtArray tmp;
                tmp.data = &st->u.for_s.init;
                tmp.len = 1;
                tmp.cap = 1;
                walk_stmts_for_layout(&tmp, layout, offset);
            }
            walk_block_for_layout(&st->u.for_s.body, layout, offset);
        }
    }
}

static void walk_block_for_layout(Block *b, FuncLayout *layout, int *offset) {
    walk_stmts_for_layout(&b->stmts, layout, offset);
}

static FuncLayout layout_func(FuncDef *f) {
    FuncLayout layout;
    memset(&layout, 0, sizeof(layout));
    int offset = 0;

    for (int i = 0; i < f->nparams; i++) {
        offset += 8;
        layout_add_slot(&layout, f->params[i], offset);
    }

    walk_block_for_layout(&f->body, &layout, &offset);

    layout.stack_size = ((offset + 15) / 16) * 16;
    return layout;
}

/* ---- Code generation ---- */

static void gen_addr(Expr *e, FuncLayout *layout);
static void gen_value(Expr *e, FuncLayout *layout);
static void gen_stmt(Stmt *st, FuncLayout *layout, const char *ret_label);
static void gen_block(Block *b, FuncLayout *layout, const char *ret_label);

static void gen_addr(Expr *e, FuncLayout *layout) {
    if (e->kind == ND_VAR) {
        int off = find_slot(layout, e->u.var_name);
        if (off >= 0) {
            emit("\tsub\tx0, x29, #%d", off);
            return;
        }
        /* Check global variables */
        if (find_global(e->u.var_name)) {
            emit("\tadrp\tx0, _%s@PAGE", e->u.var_name);
            emit("\tadd\tx0, x0, _%s@PAGEOFF", e->u.var_name);
            return;
        }
        fatal("Unknown variable '%s'", e->u.var_name);
        return;
    }
    if (e->kind == ND_UNARY && e->u.unary.op == '*') {
        gen_value(e->u.unary.rhs, layout);
        return;
    }
    if (e->kind == ND_INDEX) {
        gen_value(e->u.index.base, layout);
        emit("\tstr\tx0, [sp, #-16]!");
        gen_value(e->u.index.index, layout);
        emit("\tlsl\tx0, x0, #3");
        emit("\tldr\tx1, [sp], #16");
        emit("\tadd\tx0, x1, x0");
        return;
    }
    if (e->kind == ND_FIELD) {
        gen_addr(e->u.field.obj, layout);
        int fi = field_index(e->u.field.struct_type, e->u.field.field);
        if (fi > 0)
            emit("\tadd\tx0, x0, #%d", fi * 8);
        return;
    }
    if (e->kind == ND_ARROW) {
        gen_value(e->u.field.obj, layout);
        int fi = field_index(e->u.field.struct_type, e->u.field.field);
        if (fi > 0)
            emit("\tadd\tx0, x0, #%d", fi * 8);
        return;
    }
    fatal("Expression is not an lvalue");
}

static void gen_value(Expr *e, FuncLayout *layout) {
    if (e->kind == ND_NUM) {
        int val = e->u.num;
        if (val >= -65535 && val <= 65535) {
            emit("\tmov\tx0, #%d", val);
        } else {
            unsigned long uval = (unsigned long)(long)val;
            emit("\tmovz\tx0, #%lu", uval & 0xFFFF);
            if ((uval >> 16) & 0xFFFF)
                emit("\tmovk\tx0, #%lu, lsl #16", (uval >> 16) & 0xFFFF);
            if ((uval >> 32) & 0xFFFF)
                emit("\tmovk\tx0, #%lu, lsl #32", (uval >> 32) & 0xFFFF);
            if ((uval >> 48) & 0xFFFF)
                emit("\tmovk\tx0, #%lu, lsl #48", (uval >> 48) & 0xFFFF);
        }
        return;
    }

    if (e->kind == ND_VAR) {
        gen_addr(e, layout);
        /* Check if it's an array or struct var (local or global) */
        int skip_load = 0;
        if (is_array(layout, e->u.var_name) || is_structvar(layout, e->u.var_name))
            skip_load = 1;
        if (!skip_load) {
            GlobalVarEntry *gv = find_global(e->u.var_name);
            if (gv && (gv->is_array || gv->is_structvar))
                skip_load = 1;
        }
        if (!skip_load)
            emit("\tldr\tx0, [x0]");
        return;
    }

    if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
        gen_addr(e, layout);
        emit("\tldr\tx0, [x0]");
        return;
    }

    if (e->kind == ND_INDEX) {
        gen_addr(e, layout);
        emit("\tldr\tx0, [x0]");
        return;
    }

    if (e->kind == ND_ASSIGN) {
        gen_addr(e->u.assign.target, layout);
        emit("\tstr\tx0, [sp, #-16]!");
        gen_value(e->u.assign.rhs, layout);
        emit("\tldr\tx1, [sp], #16");
        emit("\tstr\tx0, [x1]");
        return;
    }

    if (e->kind == ND_STRLIT) {
        char *decoded = decode_c_string(e->u.str_val);
        char *lab = intern_string(decoded);
        emit("\tadrp\tx0, %s@PAGE", lab);
        emit("\tadd\tx0, x0, %s@PAGEOFF", lab);
        return;
    }

    if (e->kind == ND_UNARY) {
        char op = e->u.unary.op;
        if (op == '&') {
            gen_addr(e->u.unary.rhs, layout);
            return;
        }
        if (op == '*') {
            gen_value(e->u.unary.rhs, layout);
            emit("\tldr\tx0, [x0]");
            return;
        }
        gen_value(e->u.unary.rhs, layout);
        if (op == '-') {
            emit("\tneg\tx0, x0");
        } else if (op == '!') {
            emit("\tcmp\tx0, #0");
            emit("\tcset\tx0, eq");
        } else {
            fatal("Unsupported unary '%c'", op);
        }
        return;
    }

    if (e->kind == ND_BINARY) {
        char *op = e->u.binary.op;

        if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0) {
            char *end = new_label("sc_end");
            char *rhs_lab = new_label("sc_rhs");

            gen_value(e->u.binary.lhs, layout);
            emit("\tcmp\tx0, #0");
            if (strcmp(op, "&&") == 0) {
                emit("\tb.ne\t%s", rhs_lab);
                emit("\tmov\tx0, #0");
                emit("\tb\t%s", end);
            } else {
                emit("\tb.eq\t%s", rhs_lab);
                emit("\tmov\tx0, #1");
                emit("\tb\t%s", end);
            }

            emit("%s:", rhs_lab);
            gen_value(e->u.binary.rhs, layout);
            emit("\tcmp\tx0, #0");
            emit("\tcset\tx0, ne");
            emit("%s:", end);
            return;
        }

        gen_value(e->u.binary.lhs, layout);
        emit("\tstr\tx0, [sp, #-16]!");
        gen_value(e->u.binary.rhs, layout);
        emit("\tldr\tx1, [sp], #16");

        if (strcmp(op, "+") == 0)      emit("\tadd\tx0, x1, x0");
        else if (strcmp(op, "-") == 0) emit("\tsub\tx0, x1, x0");
        else if (strcmp(op, "*") == 0) emit("\tmul\tx0, x1, x0");
        else if (strcmp(op, "/") == 0) emit("\tsdiv\tx0, x1, x0");
        else if (strcmp(op, "&") == 0) emit("\tand\tx0, x1, x0");
        else if (strcmp(op, "|") == 0) emit("\torr\tx0, x1, x0");
        else if (strcmp(op, "%") == 0) {
            emit("\tsdiv\tx9, x1, x0");
            emit("\tmsub\tx0, x9, x0, x1");
        } else if (strcmp(op, "==") == 0) { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, eq"); }
        else if (strcmp(op, "!=") == 0)   { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, ne"); }
        else if (strcmp(op, "<") == 0)    { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, lt"); }
        else if (strcmp(op, "<=") == 0)   { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, le"); }
        else if (strcmp(op, ">") == 0)    { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, gt"); }
        else if (strcmp(op, ">=") == 0)   { emit("\tcmp\tx1, x0"); emit("\tcset\tx0, ge"); }
        else fatal("Unsupported binary op '%s'", op);
        return;
    }

    if (e->kind == ND_CALL) {
        char *name = e->u.call.name;
        int nargs = e->u.call.args.len;
        Expr **args = e->u.call.args.data;

        if (strcmp(name, "__read_byte") == 0) {
            if (nargs != 2) fatal("__read_byte takes 2 args");
            gen_value(args[0], layout);
            emit("\tstr\tx0, [sp, #-16]!");
            gen_value(args[1], layout);
            emit("\tldr\tx1, [sp], #16");
            emit("\tldrb\tw0, [x1, x0]");
            return;
        }

        if (strcmp(name, "__write_byte") == 0) {
            if (nargs != 3) fatal("__write_byte takes 3 args");
            gen_value(args[0], layout);
            emit("\tstr\tx0, [sp, #-16]!");
            gen_value(args[1], layout);
            emit("\tstr\tx0, [sp, #-16]!");
            gen_value(args[2], layout);
            emit("\tldr\tx1, [sp], #16");
            emit("\tldr\tx2, [sp], #16");
            emit("\tstrb\tw0, [x2, x1]");
            return;
        }

        if (strcmp(name, "printf") == 0) {
            if (nargs < 1) fatal("printf requires at least 1 argument");
            if (args[0]->kind != ND_STRLIT) fatal("printf first arg must be string literal");

            int n_var = nargs - 1;
            if (n_var > 0) {
                int var_space = ((n_var * 8 + 15) / 16) * 16;
                emit("\tsub\tsp, sp, #%d", var_space);
                for (int i = 0; i < n_var; i++) {
                    gen_value(args[i + 1], layout);
                    emit("\tstr\tx0, [sp, #%d]", i * 8);
                }
            }

            gen_value(args[0], layout);
            emit("\tbl\t_printf");

            if (n_var > 0) {
                int var_space = ((n_var * 8 + 15) / 16) * 16;
                emit("\tadd\tsp, sp, #%d", var_space);
            }
            return;
        }

        if (nargs > 8) fatal("Supports up to 8 call arguments");

        for (int i = 0; i < nargs; i++) {
            gen_value(args[i], layout);
            emit("\tstr\tx0, [sp, #-16]!");
        }
        for (int i = 0; i < nargs; i++) {
            int disp = (nargs - 1 - i) * 16;
            emit("\tldr\tx%d, [sp, #%d]", i, disp);
        }
        emit("\tadd\tsp, sp, #%d", nargs * 16);
        emit("\tbl\t_%s", name);
        return;
    }

    fatal("Unsupported expression node");
}

static void gen_stmt(Stmt *st, FuncLayout *layout, const char *ret_label) {
    if (st->kind == ST_RETURN) {
        gen_value(st->u.ret_expr, layout);
        emit("\tb\t%s", ret_label);
        return;
    }

    if (st->kind == ST_EXPR) {
        gen_value(st->u.expr, layout);
        return;
    }

    if (st->kind == ST_VARDECL) {
        for (int i = 0; i < st->u.vardecl.count; i++) {
            VarDeclEntry *e = &st->u.vardecl.entries[i];
            if (e->struct_type) continue;
            if (e->array_size >= 0) continue;
            int off = find_slot(layout, e->name);
            if (off < 0) fatal("Internal: var missing from layout");
            if (e->init)
                gen_value(e->init, layout);
            else
                emit("\tmov\tx0, #0");
            emit("\tstr\tx0, [x29, #-%d]", off);
        }
        return;
    }

    if (st->kind == ST_IF) {
        char *else_lab = new_label("else");
        char *end_lab = new_label("endif");
        gen_value(st->u.if_s.cond, layout);
        emit("\tcmp\tx0, #0");
        if (!st->u.if_s.else_blk) {
            emit("\tb.eq\t%s", end_lab);
            gen_block(&st->u.if_s.then_blk, layout, ret_label);
            emit("%s:", end_lab);
        } else {
            emit("\tb.eq\t%s", else_lab);
            gen_block(&st->u.if_s.then_blk, layout, ret_label);
            emit("\tb\t%s", end_lab);
            emit("%s:", else_lab);
            gen_block(st->u.if_s.else_blk, layout, ret_label);
            emit("%s:", end_lab);
        }
        return;
    }

    if (st->kind == ST_WHILE) {
        char *start = new_label("while_start");
        char *end = new_label("while_end");
        if (nloop_stack >= 64) fatal("Loop nesting too deep");
        loop_stack[nloop_stack].brk_label = end;
        loop_stack[nloop_stack].cont_label = start;
        nloop_stack++;

        emit("%s:", start);
        gen_value(st->u.while_s.cond, layout);
        emit("\tcmp\tx0, #0");
        emit("\tb.eq\t%s", end);
        gen_block(&st->u.while_s.body, layout, ret_label);
        emit("\tb\t%s", start);
        emit("%s:", end);

        nloop_stack--;
        return;
    }

    if (st->kind == ST_FOR) {
        char *start = new_label("for_start");
        char *post_lab = new_label("for_post");
        char *end = new_label("for_end");

        if (st->u.for_s.init)
            gen_stmt(st->u.for_s.init, layout, ret_label);

        if (nloop_stack >= 64) fatal("Loop nesting too deep");
        loop_stack[nloop_stack].brk_label = end;
        loop_stack[nloop_stack].cont_label = post_lab;
        nloop_stack++;

        emit("%s:", start);
        if (st->u.for_s.cond) {
            gen_value(st->u.for_s.cond, layout);
            emit("\tcmp\tx0, #0");
            emit("\tb.eq\t%s", end);
        }

        gen_block(&st->u.for_s.body, layout, ret_label);

        emit("%s:", post_lab);
        if (st->u.for_s.post)
            gen_value(st->u.for_s.post, layout);

        emit("\tb\t%s", start);
        emit("%s:", end);

        nloop_stack--;
        return;
    }

    if (st->kind == ST_BREAK) {
        if (nloop_stack == 0) fatal("break used outside of a loop");
        emit("\tb\t%s", loop_stack[nloop_stack - 1].brk_label);
        return;
    }

    if (st->kind == ST_CONTINUE) {
        if (nloop_stack == 0) fatal("continue used outside of a loop");
        emit("\tb\t%s", loop_stack[nloop_stack - 1].cont_label);
        return;
    }

    fatal("Unsupported statement node");
}

static void gen_block(Block *b, FuncLayout *layout, const char *ret_label) {
    for (int i = 0; i < b->stmts.len; i++)
        gen_stmt(b->stmts.data[i], layout, ret_label);
}

static void gen_func(FuncDef *f) {
    FuncLayout layout = layout_func(f);
    char *ret_label = new_label("ret");

    emit("");
    emit("\t.p2align\t2");
    emit("\t.globl\t_%s", f->name);
    emit("_%s:", f->name);
    emit("\tstp\tx29, x30, [sp, #-16]!");
    emit("\tmov\tx29, sp");
    if (layout.stack_size)
        emit("\tsub\tsp, sp, #%d", layout.stack_size);

    for (int i = 0; i < f->nparams; i++) {
        int off = find_slot(&layout, f->params[i]);
        emit("\tstr\tx%d, [x29, #-%d]", i, off);
    }

    gen_block(&f->body, &layout, ret_label);

    emit("\tmov\tw0, #0");
    emit("%s:", ret_label);
    if (layout.stack_size)
        emit("\tadd\tsp, sp, #%d", layout.stack_size);
    emit("\tldp\tx29, x30, [sp], #16");
    emit("\tret");
}

char *codegen_generate(Program *prog) {
    buf_init(&out);
    label_id = 0;
    nstr_pool = 0;
    nloop_stack = 0;
    ncg_structs = 0;
    nglobal_vars = 0;

    /* Register struct definitions */
    for (int i = 0; i < prog->nstructs; i++) {
        if (ncg_structs >= 64) fatal("Too many structs");
        cg_structs[ncg_structs].name = prog->structs[i].name;
        cg_structs[ncg_structs].fields = prog->structs[i].fields;
        cg_structs[ncg_structs].nfields = prog->structs[i].nfields;
        ncg_structs++;
    }

    /* Register global variables */
    for (int i = 0; i < prog->nglobals; i++) {
        GlobalDecl *gd = &prog->globals[i];
        if (nglobal_vars >= 1024) fatal("Too many global variables");
        global_vars[nglobal_vars].name = gd->name;
        global_vars[nglobal_vars].is_array = (gd->array_size >= 0);
        global_vars[nglobal_vars].is_structvar = (gd->struct_type != NULL && !gd->is_ptr && gd->array_size < 0);
        nglobal_vars++;
    }

    emit("\t.text");
    for (int i = 0; i < prog->nfuncs; i++)
        gen_func(&prog->funcs[i]);

    if (nstr_pool > 0) {
        emit("");
        emit("\t.section\t__TEXT,__cstring,cstring_literals");
        for (int i = 0; i < nstr_pool; i++) {
            char *esc = asm_escape_string(str_pool[i].decoded);
            emit("%s:", str_pool[i].label);
            emit("\t.asciz\t\"%s\"", esc);
        }
    }

    /* Emit global variables (skip extern declarations) */
    if (prog->nglobals > 0) {
        int has_data = 0;
        for (int i = 0; i < prog->nglobals; i++) {
            GlobalDecl *gd = &prog->globals[i];
            if (gd->is_extern) continue;
            if (gd->array_size >= 0) {
                /* Array: use .comm */
                int size = gd->array_size * 8;
                emit("\t.comm\t_%s, %d, 3", gd->name, size);
            } else if (gd->init != NULL && gd->init->kind == ND_NUM) {
                /* Initialized scalar */
                if (!has_data) { emit(""); emit("\t.data"); has_data = 1; }
                emit("\t.globl\t_%s", gd->name);
                emit("\t.p2align\t3");
                emit("_%s:", gd->name);
                emit("\t.quad\t%d", gd->init->u.num);
            } else if (gd->init != NULL && gd->init->kind == ND_STRLIT) {
                /* String-initialized scalar */
                char *decoded = decode_c_string(gd->init->u.str_val);
                char *lab = intern_string(decoded);
                if (!has_data) { emit(""); emit("\t.data"); has_data = 1; }
                emit("\t.globl\t_%s", gd->name);
                emit("\t.p2align\t3");
                emit("_%s:", gd->name);
                emit("\t.quad\t%s", lab);
            } else {
                /* Uninitialized scalar or struct */
                if (gd->struct_type != NULL && !gd->is_ptr && gd->array_size < 0) {
                    CgStructDef *sd = find_cg_struct(gd->struct_type);
                    int size = sd ? sd->nfields * 8 : 8;
                    emit("\t.comm\t_%s, %d, 3", gd->name, size);
                } else {
                    emit("\t.comm\t_%s, 8, 3", gd->name);
                }
            }
        }
    }

    return buf_detach(&out);
}
