#include "parser.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- Parser state ---- */

typedef struct {
    char *name;         /* field name */
    char *struct_type;  /* NULL for int fields */
    int is_ptr;
    int bit_width;      /* 0 = normal field, >0 = bitfield width */
    int array_size;     /* -1 = not array, >=0 = array element count */
} FieldInfo;

typedef struct {
    char *name;
    FieldInfo *fields;
    int nfields;
    int nwords;     /* bitfield-packed word count; 0 = no bitfields */
} StructDefInfo;

typedef struct {
    char *name;
    char *struct_type;  /* NULL for int vars */
    int is_ptr;
    int array_size;     /* -1 if not an array */
} LocalVar;

typedef struct {
    char *name;
    int value;
} EnumConst;

static Tok *toks;
static int ntoks;
static int pos;

static StructDefInfo *struct_defs;
static int nstruct_defs;
static int struct_defs_cap;

static StructDef *inline_structs;
static int ninline_structs;
static int inline_structs_cap;

static LocalVar *local_vars;
static int nlocal_vars;
static int local_vars_cap;

/* Tracks struct type from most recent cast, for offsetof pattern: ((Type*)0)->field */
static const char *last_cast_struct_type;

static EnumConst *enum_consts;
static int nenum_consts;
static int enum_consts_cap;

/* Typedef table: maps typedef name to struct type (NULL for int-like) */
typedef struct {
    char *name;
    char *struct_type;  /* NULL for int/char/void/etc, struct name for struct types */
    int is_char;        /* 1 if typedef of char/unsigned char */
} TypedefEntry;

static TypedefEntry *typedefs;
static int ntypedefs;
static int typedefs_cap;

/* Global variable table: track struct types for globals (for field access resolution) */
typedef struct {
    char *name;
    char *struct_type;
    int is_ptr;
} GlobalVarInfo;

static GlobalVarInfo *global_var_infos;
static int nglobal_var_infos;
static int global_var_infos_cap;

static void add_global_var_info(const char *name, const char *struct_type, int is_ptr) {
    GROW(global_var_infos, nglobal_var_infos, global_var_infos_cap, GlobalVarInfo);
    global_var_infos[nglobal_var_infos].name = xstrdup(name);
    global_var_infos[nglobal_var_infos].struct_type = struct_type ? xstrdup(struct_type) : NULL;
    global_var_infos[nglobal_var_infos].is_ptr = is_ptr;
    nglobal_var_infos++;
}

static GlobalVarInfo *find_global_var(const char *name) {
    for (int i = 0; i < nglobal_var_infos; i++)
        if (strcmp(global_var_infos[i].name, name) == 0)
            return &global_var_infos[i];
    return NULL;
}

/* Function return struct type registry */
typedef struct {
    char *name;
    char *ret_struct_type; /* NULL if not returning struct ptr */
} FuncRetInfo;

static FuncRetInfo *func_ret_infos;
static int nfunc_ret_infos;
static int func_ret_infos_cap;

static void add_func_ret_info(const char *name, const char *ret_struct_type) {
    /* Update existing entry if present */
    for (int i = 0; i < nfunc_ret_infos; i++) {
        if (strcmp(func_ret_infos[i].name, name) == 0) {
            if (ret_struct_type && !func_ret_infos[i].ret_struct_type)
                func_ret_infos[i].ret_struct_type = xstrdup(ret_struct_type);
            return;
        }
    }
    GROW(func_ret_infos, nfunc_ret_infos, func_ret_infos_cap, FuncRetInfo);
    func_ret_infos[nfunc_ret_infos].name = xstrdup(name);
    func_ret_infos[nfunc_ret_infos].ret_struct_type = ret_struct_type ? xstrdup(ret_struct_type) : NULL;
    nfunc_ret_infos++;
}

static const char *find_func_ret_struct(const char *name) {
    for (int i = 0; i < nfunc_ret_infos; i++)
        if (strcmp(func_ret_infos[i].name, name) == 0)
            return func_ret_infos[i].ret_struct_type;
    return NULL;
}

/* Flags set by parse_base_type */
static int last_type_unsigned;
static int last_type_is_char;
static Type *last_type;  /* Type* built by most recent parse_base_type call */

/* ---- Helpers ---- */

static Tok *cur(void) {
    return &toks[pos];
}

static Tok *eat(TokKind kind, const char *value) {
    Tok *t = cur();
    if (t->kind != kind) {
        fprintf(stderr, "Context around error (tok %d):\n", pos);
        for (int d = (pos > 5 ? pos - 5 : 0); d < pos + 5 && d < ntoks; d++)
            fprintf(stderr, "  tok[%d] = '%s' (pos=%d)\n", d, toks[d].value, toks[d].pos);
        fatal("Expected %s, got %s '%s' at %d", tokkind_str(kind), tokkind_str(t->kind), t->value, t->pos);
    }
    if (value && strcmp(t->value, value) != 0) {
        fprintf(stderr, "Context around error (tok %d):\n", pos);
        for (int d = (pos > 30 ? pos - 30 : 0); d < pos + 5 && d < ntoks; d++)
            fprintf(stderr, "  tok[%d] = %s:'%s' (pos=%d)\n", d, tokkind_str(toks[d].kind), toks[d].value, toks[d].pos);
        fatal("Expected '%s', got '%s' at %d", value, t->value, t->pos);
    }
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

/* Recursively compute total 8-byte slots for a struct type */
static int parser_struct_nslots(const char *name) {
    StructDefInfo *sd = find_struct_def(name);
    if (!sd) return 1;
    if (sd->nwords > 0) return sd->nwords;
    /* Check if this is a union by looking it up in the inline structs or program structs */
    int is_union = 0;
    for (int k = 0; k < ninline_structs; k++)
        if (strcmp(inline_structs[k].name, name) == 0) { is_union = inline_structs[k].is_union; break; }
    int total = 0;
    int max_field = 0;
    for (int i = 0; i < sd->nfields; i++) {
        int field_slots;
        if (sd->fields[i].struct_type && !sd->fields[i].is_ptr) {
            field_slots = parser_struct_nslots(sd->fields[i].struct_type);
            if (sd->fields[i].array_size > 0)
                field_slots *= sd->fields[i].array_size;
        } else {
            if (sd->fields[i].array_size > 0)
                field_slots = (sd->fields[i].array_size + 7) / 8;
            else
                field_slots = 1;
        }
        if (is_union) {
            if (field_slots > max_field) max_field = field_slots;
        } else {
            total += field_slots;
        }
    }
    if (is_union) return max_field > 0 ? max_field : 1;
    return total > 0 ? total : 1;
}

static const char *field_struct_type(const char *struct_name, const char *field_name) {
    StructDefInfo *sd = find_struct_def(struct_name);
    if (!sd) return NULL;  /* unknown struct — return NULL for lenient handling */
    for (int i = 0; i < sd->nfields; i++) {
        if (strcmp(sd->fields[i].name, field_name) == 0) {
            return sd->fields[i].struct_type;  /* may be NULL if not a struct field */
        }
    }
    return NULL;  /* field not found — lenient */
}

static void add_local_arr(const char *name, const char *struct_type, int is_ptr, int array_size) {
    GROW(local_vars, nlocal_vars, local_vars_cap, LocalVar);
    local_vars[nlocal_vars].name = xstrdup(name);
    local_vars[nlocal_vars].struct_type = struct_type ? xstrdup(struct_type) : NULL;
    local_vars[nlocal_vars].is_ptr = is_ptr;
    local_vars[nlocal_vars].array_size = array_size;
    nlocal_vars++;
}

static void add_local(const char *name, const char *struct_type, int is_ptr) {
    add_local_arr(name, struct_type, is_ptr, -1);
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

static TypedefEntry *find_typedef(const char *name) {
    for (int i = 0; i < ntypedefs; i++)
        if (strcmp(typedefs[i].name, name) == 0)
            return &typedefs[i];
    return NULL;
}

static void add_typedef_ex(const char *name, const char *struct_type, int is_char) {
    GROW(typedefs, ntypedefs, typedefs_cap, TypedefEntry);
    typedefs[ntypedefs].name = xstrdup(name);
    typedefs[ntypedefs].struct_type = struct_type ? xstrdup(struct_type) : NULL;
    typedefs[ntypedefs].is_char = is_char;
    ntypedefs++;
}
static void add_typedef(const char *name, const char *struct_type) {
    add_typedef_ex(name, struct_type, 0);
}

static void add_enum_const(const char *name, int value) {
    GROW(enum_consts, nenum_consts, enum_consts_cap, EnumConst);
    enum_consts[nenum_consts].name = xstrdup(name);
    enum_consts[nenum_consts].value = value;
    nenum_consts++;
}

static int parse_const_expr(void);
static int parse_const_unary(void);

/* ---- Helpers for function pointer parsing ---- */

/* Check if we're looking at a function pointer declarator: (*name)(params)
   Returns 1 if so. Does not advance pos. */
static int is_funcptr_decl(void) {
    if (!match(TK_OP, "(")) return 0;
    return (pos + 1 < ntoks && toks[pos+1].kind == TK_OP &&
            strcmp(toks[pos+1].value, "*") == 0);
}

/* Skip a parenthesized parameter list: (type1, type2, ...) or (type1 name1, ...)
   Handles nested parentheses. */
static void skip_param_list(void) {
    eat(TK_OP, "(");
    int depth = 1;
    while (depth > 0) {
        if (match(TK_OP, "(")) depth++;
        else if (match(TK_OP, ")")) depth--;
        if (depth > 0) eat(cur()->kind, NULL);
    }
    eat(TK_OP, ")");
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
        match(TK_KW, "_Bool") || match(TK_KW, "bool") || match(TK_KW, "inline") ||
        match(TK_KW, "float") || match(TK_KW, "double"))
        return 1;
    /* Check if current identifier is a typedef name */
    if (cur()->kind == TK_ID && find_typedef(cur()->value))
        return 1;
    return 0;
}

/* Returns struct name (allocated) or NULL for int/char/void/unsigned/etc */
static int anon_struct_counter;

static char *parse_base_type(void) {
    skip_qualifiers();

    if (match(TK_KW, "struct") || match(TK_KW, "union")) {
        int is_union = match(TK_KW, "union");
        eat(TK_KW, is_union ? "union" : "struct");
        if (match(TK_OP, "{")) {
            /* Anonymous/inline struct: struct { ... } */
            char synth_name[64];
            snprintf(synth_name, sizeof(synth_name), "__anon_%d", anon_struct_counter++);
            eat(TK_OP, "{");
            FieldInfo *finfo = NULL;
            int nfields = 0, fcap = 0;
            while (!match(TK_OP, "}")) {
                char *ftype = parse_base_type();
                while (1) {
                int is_ptr = 0;
                int is_funcptr = 0;
                if (is_funcptr_decl()) {
                    eat(TK_OP, "("); eat(TK_OP, "*");
                    is_ptr = 1; is_funcptr = 1;
                }
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); is_ptr++; }
                if (!is_funcptr && is_funcptr_decl()) {
                    eat(TK_OP, "("); eat(TK_OP, "*");
                    is_ptr++; is_funcptr = 1;
                }
                skip_qualifiers();
                Tok *fname_tok = eat(TK_ID, NULL);
                if (is_funcptr) { eat(TK_OP, ")"); skip_param_list(); }
                int field_arr = -1;
                if (match(TK_OP, "[")) {
                    eat(TK_OP, "[");
                    if (match(TK_OP, "]")) {
                        field_arr = 0;
                        eat(TK_OP, "]");
                    } else {
                        field_arr = parse_const_expr();
                        eat(TK_OP, "]");
                    }
                    while (match(TK_OP, "[")) {
                        eat(TK_OP, "[");
                        int dim2 = parse_const_expr();
                        eat(TK_OP, "]");
                        if (field_arr > 0 && dim2 > 0) field_arr *= dim2;
                    }
                }
                int bw = 0;
                if (match(TK_OP, ":")) { eat(TK_OP, ":"); bw = parse_const_expr(); }
                if (nfields >= fcap) {
                    fcap = fcap ? fcap * 2 : 8;
                    finfo = realloc(finfo, fcap * sizeof(FieldInfo));
                }
                finfo[nfields].name = xstrdup(fname_tok->value);
                finfo[nfields].struct_type = ftype ? xstrdup(ftype) : NULL;
                finfo[nfields].is_ptr = is_ptr;
                finfo[nfields].bit_width = bw;
                finfo[nfields].array_size = field_arr;
                nfields++;
                if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
                break;
                } /* end while(1) for comma-separated fields */
                eat(TK_OP, ";");
            }
            eat(TK_OP, "}");
            /* Register in parser's struct table */
            GROW(struct_defs, nstruct_defs, struct_defs_cap, StructDefInfo);
            struct_defs[nstruct_defs].name = xstrdup(synth_name);
            struct_defs[nstruct_defs].fields = finfo;
            struct_defs[nstruct_defs].nfields = nfields;
            nstruct_defs++;
            /* Also register for codegen */
            GROW(inline_structs, ninline_structs, inline_structs_cap, StructDef);
            StructDef *isd = &inline_structs[ninline_structs++];
            isd->name = xstrdup(synth_name);
            isd->fields = xmalloc(nfields * sizeof(char *));
            isd->field_types = xmalloc(nfields * sizeof(char *));
            isd->nfields = nfields;
            isd->is_union = is_union;
            isd->bit_widths = NULL;
            isd->bit_offsets = NULL;
            isd->word_indices = NULL;
            isd->nwords = 0;
            /* Build field_array_sizes for inline struct */
            {
                int has_arr = 0;
                for (int k = 0; k < nfields; k++)
                    if (finfo[k].array_size >= 0) { has_arr = 1; break; }
                if (has_arr) {
                    isd->field_array_sizes = xmalloc(nfields * sizeof(int));
                    for (int k = 0; k < nfields; k++)
                        isd->field_array_sizes[k] = finfo[k].array_size;
                } else {
                    isd->field_array_sizes = NULL;
                }
            }
            isd->field_ptr_types = xmalloc(nfields * sizeof(char *));
            for (int k = 0; k < nfields; k++) {
                isd->fields[k] = xstrdup(finfo[k].name);
                isd->field_types[k] = (finfo[k].struct_type && !finfo[k].is_ptr) ? xstrdup(finfo[k].struct_type) : NULL;
                isd->field_ptr_types[k] = (finfo[k].struct_type && finfo[k].is_ptr == 1) ? xstrdup(finfo[k].struct_type) : NULL;
            }
            last_type = is_union ? ty_union(synth_name) : ty_struct(synth_name);
            return xstrdup(synth_name);
        }
        Tok *name = eat(TK_ID, NULL);
        /* Named inline struct/union definition: struct Name { ... } used as field type */
        if (match(TK_OP, "{")) {
            eat(TK_OP, "{");
            FieldInfo *finfo2 = NULL;
            int nf2 = 0, fc2 = 0;
            while (!match(TK_OP, "}")) {
                char *ftype2 = parse_base_type();
                while (1) {
                int isp2 = 0, isfp2 = 0;
                if (is_funcptr_decl()) {
                    eat(TK_OP, "("); eat(TK_OP, "*");
                    isp2 = 1; isfp2 = 1;
                }
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); isp2 = 1; }
                if (!isfp2 && is_funcptr_decl()) {
                    eat(TK_OP, "("); eat(TK_OP, "*");
                    isp2++; isfp2 = 1;
                }
                skip_qualifiers();
                Tok *fn2 = eat(TK_ID, NULL);
                if (isfp2) { eat(TK_OP, ")"); skip_param_list(); }
                int fa2 = -1;
                if (match(TK_OP, "[")) {
                    eat(TK_OP, "[");
                    if (match(TK_OP, "]")) {
                        fa2 = 0;
                        eat(TK_OP, "]");
                    } else {
                        fa2 = parse_const_expr();
                        eat(TK_OP, "]");
                    }
                    while (match(TK_OP, "[")) {
                        eat(TK_OP, "[");
                        int dim2 = parse_const_expr();
                        eat(TK_OP, "]");
                        if (fa2 > 0 && dim2 > 0) fa2 *= dim2;
                    }
                }
                int bw2 = 0;
                if (match(TK_OP, ":")) { eat(TK_OP, ":"); bw2 = parse_const_expr(); }
                if (nf2 >= fc2) {
                    fc2 = fc2 ? fc2 * 2 : 8;
                    finfo2 = realloc(finfo2, fc2 * sizeof(FieldInfo));
                }
                finfo2[nf2].name = xstrdup(fn2->value);
                finfo2[nf2].struct_type = ftype2 ? xstrdup(ftype2) : NULL;
                finfo2[nf2].is_ptr = isp2;
                finfo2[nf2].bit_width = bw2;
                finfo2[nf2].array_size = fa2;
                nf2++;
                if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
                break;
                }
                eat(TK_OP, ";");
            }
            eat(TK_OP, "}");
            GROW(struct_defs, nstruct_defs, struct_defs_cap, StructDefInfo);
            struct_defs[nstruct_defs].name = xstrdup(name->value);
            struct_defs[nstruct_defs].fields = finfo2;
            struct_defs[nstruct_defs].nfields = nf2;
            nstruct_defs++;
            GROW(inline_structs, ninline_structs, inline_structs_cap, StructDef);
            StructDef *isd2 = &inline_structs[ninline_structs++];
            isd2->name = xstrdup(name->value);
            isd2->fields = xmalloc(nf2 * sizeof(char *));
            isd2->field_types = xmalloc(nf2 * sizeof(char *));
            isd2->nfields = nf2;
            isd2->is_union = is_union;
            isd2->bit_widths = NULL;
            isd2->bit_offsets = NULL;
            isd2->word_indices = NULL;
            isd2->nwords = 0;
            /* Build field_array_sizes for named inline struct */
            {
                int has_arr = 0;
                for (int k = 0; k < nf2; k++)
                    if (finfo2[k].array_size >= 0) { has_arr = 1; break; }
                if (has_arr) {
                    isd2->field_array_sizes = xmalloc(nf2 * sizeof(int));
                    for (int k = 0; k < nf2; k++)
                        isd2->field_array_sizes[k] = finfo2[k].array_size;
                } else {
                    isd2->field_array_sizes = NULL;
                }
            }
            isd2->field_ptr_types = xmalloc(nf2 * sizeof(char *));
            for (int k = 0; k < nf2; k++) {
                isd2->fields[k] = xstrdup(finfo2[k].name);
                isd2->field_types[k] = (finfo2[k].struct_type && !finfo2[k].is_ptr) ? xstrdup(finfo2[k].struct_type) : NULL;
                isd2->field_ptr_types[k] = (finfo2[k].struct_type && finfo2[k].is_ptr == 1) ? xstrdup(finfo2[k].struct_type) : NULL;
            }
        }
        last_type = is_union ? ty_union(name->value) : ty_struct(name->value);
        return xstrdup(name->value);
    }
    if (match(TK_KW, "enum")) {
        eat(TK_KW, "enum");
        if (match(TK_ID, NULL))
            eat(TK_ID, NULL);  /* skip enum tag */
        last_type = ty_enum();
        return NULL;
    }
    /* All integer-like types: int, char, void, unsigned, signed, long, short, float, double */
    int got_type = 0;
    last_type_unsigned = 0;
    last_type_is_char = 0;
    int has_char = 0, has_short = 0, has_long = 0, has_void = 0;
    int has_float = 0, has_double = 0, has_signed = 0;
    int long_count = 0;
    while (match(TK_KW, "int") || match(TK_KW, "char") || match(TK_KW, "void") ||
           match(TK_KW, "unsigned") || match(TK_KW, "signed") ||
           match(TK_KW, "long") || match(TK_KW, "short") ||
           match(TK_KW, "_Bool") || match(TK_KW, "bool") ||
           match(TK_KW, "float") || match(TK_KW, "double")) {
        if (match(TK_KW, "unsigned")) last_type_unsigned = 1;
        else if (match(TK_KW, "signed")) has_signed = 1;
        else if (match(TK_KW, "char")) { has_char = 1; last_type_is_char = 1; }
        else if (match(TK_KW, "short")) has_short = 1;
        else if (match(TK_KW, "long")) { has_long = 1; long_count++; }
        else if (match(TK_KW, "void")) has_void = 1;
        else if (match(TK_KW, "float")) has_float = 1;
        else if (match(TK_KW, "double")) has_double = 1;
        eat(TK_KW, NULL);
        got_type = 1;
    }
    if (got_type) {
        skip_qualifiers();
        /* signed char: treat as int-sized (not byte) to preserve sign on load */
        if (has_char && has_signed && !last_type_unsigned)
            last_type_is_char = 0;
        /* Build Type* based on what we saw */
        if (has_void)        last_type = ty_void();
        else if (has_float)  last_type = ty_float();
        else if (has_double) last_type = ty_double();
        else if (has_char)   last_type = ty_char();
        else if (has_short)  last_type = ty_short();
        else if (long_count >= 2) last_type = ty_llong();
        else if (has_long)   last_type = ty_long();
        else                 last_type = ty_int();
        if (last_type_unsigned) last_type = ty_unsigned(last_type);
        return NULL;
    }
    /* Check if it's a typedef name */
    if (cur()->kind == TK_ID) {
        TypedefEntry *td = find_typedef(cur()->value);
        if (td) {
            eat(TK_ID, NULL);
            skip_qualifiers();
            if (td->struct_type) {
                last_type = ty_struct(td->struct_type);
                return xstrdup(td->struct_type);
            }
            if (td->is_char) last_type_is_char = 1;
            last_type = ty_int();  /* typedef of non-struct = int-like for now */
            return NULL;
        }
    }
    /* Debug: show surrounding tokens */
    fprintf(stderr, "  context (tok#%d): ", pos);
    for (int di = (pos > 5 ? pos - 5 : 0); di < pos + 8 && di < ntoks; di++) {
        fprintf(stderr, "%s[%s:'%s'] ", di == pos ? ">>>" : "", tokkind_str(toks[di].kind), toks[di].value);
    }
    fprintf(stderr, "\n");
    fatal("Expected type, got '%s' at %d (tok#%d)", cur()->value, cur()->pos, pos);
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
        int is_funcptr = 0;
        /* Function pointer field: type (*name)(params) */
        if (is_funcptr_decl()) {
            eat(TK_OP, "(");
            eat(TK_OP, "*");
            is_ptr = 1;
            is_funcptr = 1;
        }
        while (match(TK_OP, "*")) {
            eat(TK_OP, "*");
            skip_qualifiers();
            is_ptr++;
        }
        /* Check again for funcptr after consuming pointer stars: type *(*name)(params) */
        if (!is_funcptr && is_funcptr_decl()) {
            eat(TK_OP, "(");
            eat(TK_OP, "*");
            is_funcptr = 1;
        }
        /* Handle complex nested funcptr: after eating outer (*, we may see (*name)(...)
         * e.g. void (*(*xDlSym)(sqlite3_vfs*,void*,const char*))(void);
         * At this point we've consumed the outer (* and current is ( * xDlSym ) ( ... ) ) ( void ) ;
         */
        if (is_funcptr && is_funcptr_decl()) {
            /* Nested funcptr e.g. void (*(*xDlSym)(p1,p2))(void);
             * We've already consumed the outer '(' '*' from is_funcptr_decl.
             * Skip everything to ';' */
            while (pos < ntoks && !match(TK_OP, ";")) pos++;
            eat(TK_OP, ";");
            if (nfields >= fcap) {
                fcap = fcap ? fcap * 2 : 8;
                fields = realloc(fields, fcap * sizeof(char *));
                finfo = realloc(finfo, fcap * sizeof(FieldInfo));
            }
            fields[nfields] = xstrdup("__nested_fptr");
            finfo[nfields].name = xstrdup("__nested_fptr");
            finfo[nfields].struct_type = ftype;
            finfo[nfields].is_ptr = 1;
            finfo[nfields].bit_width = 0;
            finfo[nfields].array_size = -1;
            nfields++;
            continue;
        }
        /* Handle other complex patterns where we see ( but not (* */
        if (!is_funcptr && match(TK_OP, "(")) {
            while (pos < ntoks && !match(TK_OP, ";")) pos++;
            eat(TK_OP, ";");
            if (nfields >= fcap) {
                fcap = fcap ? fcap * 2 : 8;
                fields = realloc(fields, fcap * sizeof(char *));
                finfo = realloc(finfo, fcap * sizeof(FieldInfo));
            }
            fields[nfields] = xstrdup("__complex_fptr");
            finfo[nfields].name = xstrdup("__complex_fptr");
            finfo[nfields].struct_type = ftype;
            finfo[nfields].is_ptr = 1;
            finfo[nfields].bit_width = 0;
            finfo[nfields].array_size = -1;
            nfields++;
            continue;
        }
        /* Loop for multiple declarators: int *a, *b, c; */
        for (;;) {
            /* Handle extra pointer stars for this declarator */
            int decl_is_ptr = is_ptr;
            if (!is_funcptr) {
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); decl_is_ptr++; }
            }
            Tok *fname_tok = eat(TK_ID, NULL);
            if (is_funcptr) {
                eat(TK_OP, ")");
                skip_param_list();
            }
            /* Parse array dimensions in struct fields */
            int field_arr_size = -1;
            if (match(TK_OP, "[")) {
                eat(TK_OP, "[");
                if (match(TK_OP, "]")) {
                    field_arr_size = 0; /* flexible array member */
                    eat(TK_OP, "]");
                } else {
                    field_arr_size = parse_const_expr();
                    eat(TK_OP, "]");
                }
                /* Skip additional dimensions (treat as flat) */
                while (match(TK_OP, "[")) {
                    eat(TK_OP, "[");
                    int dim2 = parse_const_expr();
                    eat(TK_OP, "]");
                    if (field_arr_size > 0 && dim2 > 0)
                        field_arr_size *= dim2;
                }
            }
            /* Bitfield: field : width */
            int bit_width = 0;
            if (match(TK_OP, ":")) {
                eat(TK_OP, ":");
                bit_width = atoi(eat(TK_NUMBER, NULL)->value);
            }

            if (nfields >= fcap) {
                fcap = fcap ? fcap * 2 : 8;
                fields = realloc(fields, fcap * sizeof(char *));
                finfo = realloc(finfo, fcap * sizeof(FieldInfo));
            }
            fields[nfields] = xstrdup(fname_tok->value);
            finfo[nfields].name = xstrdup(fname_tok->value);
            finfo[nfields].struct_type = ftype;
            finfo[nfields].is_ptr = decl_is_ptr;
            finfo[nfields].bit_width = bit_width;
            finfo[nfields].array_size = field_arr_size;
            nfields++;

            if (match(TK_OP, ",")) {
                eat(TK_OP, ",");
                /* Reset ptr for next declarator - base type stays same */
                is_funcptr = 0;
                continue;
            }
            break;
        }
        eat(TK_OP, ";");
    }
    eat(TK_OP, "}");
    eat(TK_OP, ";");

    /* Register in struct_defs for parser lookups */
    GROW(struct_defs, nstruct_defs, struct_defs_cap, StructDefInfo);
    struct_defs[nstruct_defs].name = xstrdup(name);
    struct_defs[nstruct_defs].fields = finfo;
    struct_defs[nstruct_defs].nfields = nfields;
    nstruct_defs++;

    /* Build field_types array for codegen
     * field_types: non-NULL for embedded (non-pointer) struct fields
     * field_ptr_types: non-NULL for pointer-to-struct fields */
    char **ftypes = xmalloc(nfields * sizeof(char *));
    char **fptypes = xmalloc(nfields * sizeof(char *));
    for (int i = 0; i < nfields; i++) {
        ftypes[i] = (finfo[i].struct_type && !finfo[i].is_ptr) ? xstrdup(finfo[i].struct_type) : NULL;
        fptypes[i] = (finfo[i].struct_type && finfo[i].is_ptr == 1) ? xstrdup(finfo[i].struct_type) : NULL;
    }

    /* Compute bitfield packing */
    int has_bitfields = 0;
    for (int i = 0; i < nfields; i++)
        if (finfo[i].bit_width > 0) { has_bitfields = 1; break; }

    StructDef sd;
    sd.name = name;
    sd.fields = fields;
    sd.field_types = ftypes;
    sd.field_ptr_types = fptypes;
    sd.nfields = nfields;
    sd.is_union = is_union;
    sd.bit_widths = NULL;
    sd.bit_offsets = NULL;
    sd.word_indices = NULL;
    sd.nwords = 0;
    /* Build field_array_sizes */
    int has_array_fields = 0;
    for (int i = 0; i < nfields; i++)
        if (finfo[i].array_size >= 0) { has_array_fields = 1; break; }
    if (has_array_fields) {
        sd.field_array_sizes = xmalloc(nfields * sizeof(int));
        for (int i = 0; i < nfields; i++)
            sd.field_array_sizes[i] = finfo[i].array_size;
    } else {
        sd.field_array_sizes = NULL;
    }

    if (has_bitfields) {
        sd.bit_widths = xmalloc(nfields * sizeof(int));
        sd.bit_offsets = xmalloc(nfields * sizeof(int));
        sd.word_indices = xmalloc(nfields * sizeof(int));
        int cur_word = 0;
        int cur_bit = 0;
        for (int i = 0; i < nfields; i++) {
            sd.bit_widths[i] = finfo[i].bit_width;
            if (finfo[i].bit_width > 0) {
                /* Bitfield: pack into current word */
                if (cur_bit + finfo[i].bit_width > 64) {
                    /* Doesn't fit, start new word */
                    cur_word++;
                    cur_bit = 0;
                }
                sd.bit_offsets[i] = cur_bit;
                sd.word_indices[i] = cur_word;
                cur_bit += finfo[i].bit_width;
            } else {
                /* Regular field: always gets its own word */
                if (cur_bit > 0) {
                    cur_word++;
                    cur_bit = 0;
                }
                sd.bit_offsets[i] = 0;
                sd.word_indices[i] = cur_word;
                cur_word++;
            }
        }
        if (cur_bit > 0) cur_word++;  /* last partial word counts */
        sd.nwords = cur_word;
        /* Update struct_defs entry with nwords */
        struct_defs[nstruct_defs - 1].nwords = cur_word;
    }

    return sd;
}

/* ---- Constant expression evaluator for enum values ---- */

static int parse_const_expr(void);

static int parse_const_primary(void) {
    if (match(TK_OP, "(")) {
        /* Check for cast: (type)expr — skip the cast */
        int saved = pos;
        eat(TK_OP, "(");
        skip_qualifiers();
        if (is_type_start()) {
            parse_base_type();
            while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); }
            if (match(TK_OP, ")")) {
                eat(TK_OP, ")");
                return parse_const_unary();
            }
        }
        pos = saved;
        eat(TK_OP, "(");
        int val = parse_const_expr();
        eat(TK_OP, ")");
        return val;
    }
    if (match(TK_NUMBER, NULL)) {
        return atoi(eat(TK_NUMBER, NULL)->value);
    }
    if (match(TK_KW, "sizeof")) {
        eat(TK_KW, "sizeof");
        eat(TK_OP, "(");
        /* sizeof(type) or sizeof(expr) — just return 8 for pointers/long, 4 for int/u32, 1 for char/u8 */
        int sz = 8;
        skip_qualifiers();
        if (is_type_start()) {
            char *ty = parse_base_type();
            int nstars = 0;
            while (match(TK_OP, "*")) { eat(TK_OP, "*"); nstars++; }
            if (nstars > 0) sz = 8;
            else if (ty && (strcmp(ty, "char") == 0 || strcmp(ty, "u8") == 0 ||
                           strcmp(ty, "_Bool") == 0 || strcmp(ty, "bool") == 0)) sz = 1;
            else if (ty && (strcmp(ty, "short") == 0 || strcmp(ty, "u16") == 0 ||
                           strcmp(ty, "i16") == 0)) sz = 2;
            else if (ty && (strcmp(ty, "int") == 0 || strcmp(ty, "unsigned") == 0 ||
                           strcmp(ty, "u32") == 0 || strcmp(ty, "i32") == 0 ||
                           strcmp(ty, "float") == 0)) sz = 4;
            else if (ty) {
                /* Check if it's a struct/union type */
                StructDefInfo *sd = find_struct_def(ty);
                if (sd)
                    sz = parser_struct_nslots(ty) * 8;
                else
                    sz = 8; /* unknown type, default to 8 */
            } else sz = 8;
        } else {
            /* sizeof(expr) — skip the expression and assume 8 */
            int depth = 1;
            while (depth > 0) {
                if (match(TK_OP, "(")) depth++;
                else if (match(TK_OP, ")")) { depth--; if (depth == 0) break; }
                eat(cur()->kind, NULL);
            }
            eat(TK_OP, ")");
            return 8;
        }
        eat(TK_OP, ")");
        return sz;
    }
    if (match(TK_ID, NULL)) {
        char *name = eat(TK_ID, NULL)->value;
        int val;
        if (find_enum_const(name, &val)) return val;
        fatal("Unknown enum constant '%s'", name);
    }
    fprintf(stderr, "Context around const expr error (tok %d):\n", pos);
    for (int d = (pos > 10 ? pos - 10 : 0); d < pos + 5 && d < ntoks; d++)
        fprintf(stderr, "  tok[%d] = %s:'%s'\n", d, tokkind_str(toks[d].kind), toks[d].value);
    fatal("Expected constant expression at %d (tok#%d, '%s')", cur()->pos, pos, cur()->value);
    return 0;
}

static int parse_const_unary(void) {
    if (match(TK_OP, "-")) { eat(TK_OP, "-"); return -parse_const_unary(); }
    if (match(TK_OP, "~")) { eat(TK_OP, "~"); return ~parse_const_unary(); }
    if (match(TK_OP, "!")) { eat(TK_OP, "!"); return !parse_const_unary(); }
    /* &((Type*)0)->member — offsetof pattern, return 0 as approximation */
    if (match(TK_OP, "&")) {
        eat(TK_OP, "&");
        /* Skip the operand expression — count parens */
        if (match(TK_OP, "(")) {
            eat(TK_OP, "(");
            int depth = 1;
            while (depth > 0) {
                if (match(TK_OP, "(")) depth++;
                else if (match(TK_OP, ")")) depth--;
                if (depth > 0) eat(cur()->kind, NULL);
            }
            eat(TK_OP, ")");
        } else {
            eat(cur()->kind, NULL); /* skip single token */
        }
        /* Skip member access: ->member or .member chains */
        while (match(TK_OP, "->") || match(TK_OP, ".")) {
            eat(TK_OP, NULL);
            if (match(TK_ID, NULL)) eat(TK_ID, NULL);
        }
        return 0;
    }
    return parse_const_primary();
}

static int parse_const_mul(void) {
    int val = parse_const_unary();
    while (match(TK_OP, "*") || match(TK_OP, "/") || match(TK_OP, "%")) {
        char *op = cur()->value;
        eat(TK_OP, NULL);
        int rhs = parse_const_unary();
        if (op[0] == '*') val *= rhs;
        else if (op[0] == '/') val /= rhs;
        else val %= rhs;
    }
    return val;
}

static int parse_const_add(void) {
    int val = parse_const_mul();
    while (match(TK_OP, "+") || match(TK_OP, "-")) {
        char *op = cur()->value;
        eat(TK_OP, NULL);
        int rhs = parse_const_mul();
        if (op[0] == '+') val += rhs; else val -= rhs;
    }
    return val;
}

static int parse_const_shift(void) {
    int val = parse_const_add();
    while (match(TK_OP, "<<") || match(TK_OP, ">>")) {
        char *op = cur()->value;
        eat(TK_OP, NULL);
        int rhs = parse_const_add();
        if (op[0] == '<') val <<= rhs; else val >>= rhs;
    }
    return val;
}

static int parse_const_and(void) {
    int val = parse_const_shift();
    while (match(TK_OP, "&")) { eat(TK_OP, "&"); val &= parse_const_shift(); }
    return val;
}

static int parse_const_xor(void) {
    int val = parse_const_and();
    while (match(TK_OP, "^")) { eat(TK_OP, "^"); val ^= parse_const_and(); }
    return val;
}

static int parse_const_expr(void) {
    int val = parse_const_xor();
    while (match(TK_OP, "|")) { eat(TK_OP, "|"); val |= parse_const_xor(); }
    return val;
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
            value = parse_const_expr();
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

/* Parse brace initializer list: { expr, expr, ... }
   Also supports designated initializers: { .field = val, [idx] = val }
   struct_type_name is optional (NULL for arrays/non-struct), used for .field resolution */
static Expr *parse_init_list(const char *struct_type_name) {
    eat(TK_OP, "{");
    ExprArray elems = {NULL, 0, 0};
    int *desig = NULL;
    int desig_cap = 0;
    int ndesig = 0;
    int has_desig = 0;

    while (!match(TK_OP, "}")) {
        int di = -1; /* -1 = positional */
        if (match(TK_OP, ".")) {
            /* Field designator: .field = expr */
            eat(TK_OP, ".");
            Tok *fname = eat(TK_ID, NULL);
            eat(TK_OP, "=");
            has_desig = 1;
            /* Resolve field name to index using parser's struct_defs */
            if (struct_type_name) {
                StructDefInfo *sd = find_struct_def(struct_type_name);
                if (sd) {
                    for (int fi = 0; fi < sd->nfields; fi++) {
                        if (strcmp(sd->fields[fi].name, fname->value) == 0) {
                            di = fi;
                            break;
                        }
                    }
                }
            }
            if (di < 0) fatal("Unknown field '%s' in designated initializer", fname->value);
        } else if (match(TK_OP, "[")) {
            /* Array index designator: [idx] = expr */
            eat(TK_OP, "[");
            di = atoi(eat(TK_NUMBER, NULL)->value);
            eat(TK_OP, "]");
            eat(TK_OP, "=");
            has_desig = 1;
        }

        if (match(TK_OP, "{")) {
            exprarray_push(&elems, parse_init_list(NULL));
        } else {
            exprarray_push(&elems, parse_expr(0));
        }
        /* Track designator index */
        if (ndesig >= desig_cap) {
            desig_cap = desig_cap ? desig_cap * 2 : 16;
            desig = realloc(desig, desig_cap * sizeof(int));
        }
        desig[ndesig++] = di;

        if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
        break;
    }
    eat(TK_OP, "}");

    Expr *e = calloc(1, sizeof(Expr));
    e->kind = ND_INITLIST;
    e->u.initlist.elems = elems;
    e->u.initlist.desig_indices = has_desig ? desig : NULL;
    return e;
}

static Stmt *parse_vardecl_stmt(int is_static) {
    char *stype = parse_base_type();
    int base_unsigned = last_type_unsigned;
    int base_is_char = last_type_is_char;
    VarDeclEntry *entries = NULL;
    int count = 0;
    int ecap = 0;

    while (1) {
        int is_ptr = 0;
        int is_funcptr = 0;
        /* Function pointer: type (*name)(params) or type *(*name)(params) */
        if (is_funcptr_decl()) {
            eat(TK_OP, "(");
            eat(TK_OP, "*");
            is_ptr = 1;
            is_funcptr = 1;
        }
        while (match(TK_OP, "*")) {
            eat(TK_OP, "*");
            is_ptr++;
            skip_qualifiers();
        }
        /* Check again after consuming stars: type * (*name)(params) */
        if (!is_funcptr && is_funcptr_decl()) {
            eat(TK_OP, "(");
            eat(TK_OP, "*");
            is_ptr++;
            is_funcptr = 1;
        }
        skip_qualifiers();
        Tok *name_tok = eat(TK_ID, NULL);
        char *name = xstrdup(name_tok->value);
        /* Close the funcptr declarator paren and skip param list */
        if (is_funcptr) {
            eat(TK_OP, ")");
            skip_param_list();
        }
        int arr_size = -1;
        int arr_size2 = -1;
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            if (match(TK_OP, "]")) {
                arr_size = 0; /* infer from initializer */
            } else {
                arr_size = parse_const_expr();
            }
            eat(TK_OP, "]");
            /* Check for second dimension: int arr[N][M] */
            if (match(TK_OP, "[")) {
                eat(TK_OP, "[");
                arr_size2 = parse_const_expr();
                eat(TK_OP, "]");
            }
        }
        Expr *init = NULL;
        /* struct_type in decl: for struct variables, struct arrays, and pointer-to-struct */
        char *decl_stype = stype ? xstrdup(stype) : NULL;
        if (arr_size >= 0 && match(TK_OP, "=")) {
            /* Array initializer: int arr[3] = {1, 2, 3}; or char s[] = "str"; */
            eat(TK_OP, "=");
            if (match(TK_STRING, NULL)) {
                /* String initializer for char array */
                Tok *str_tok = eat(TK_STRING, NULL);
                char *str = str_tok->value;
                int slen = strlen(str) + 1; /* include null terminator */
                if (arr_size == 0) arr_size = slen;
                init = new_strlit(str);
            } else {
                init = parse_init_list(decl_stype);
                if (arr_size == 0)
                    arr_size = init->u.initlist.elems.len; /* infer size */
            }
        } else if (decl_stype && !is_ptr && arr_size < 0 && match(TK_OP, "=")) {
            /* Struct initializer: struct Point p = {1, 2}; or copy: Point x = *p; */
            eat(TK_OP, "=");
            if (match(TK_OP, "{")) {
                init = parse_init_list(decl_stype);
            } else {
                init = parse_expr(0);
            }
        } else if ((!decl_stype || is_ptr) && arr_size < 0 && match(TK_OP, "=")) {
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
        entries[count].is_ptr = is_ptr;
        entries[count].init = init;
        entries[count].is_static = is_static;
        entries[count].is_unsigned = base_unsigned;
        entries[count].is_char = base_is_char;
        entries[count].array_size2 = arr_size2;
        count++;

        if (stype)
            add_local_arr(name, stype, is_ptr, arr_size);

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
            Expr *then_e = parse_expr(-1);  /* allow comma expr in then-branch */
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

    /* Unary + is a no-op — just parse the operand */
    if (match(TK_OP, "+")) {
        eat(TK_OP, "+");
        return parse_unary();
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
            char *cast_stype = parse_base_type();
            /* Function pointer cast: (type (*)(params))expr or (type (**)(params))expr */
            if (is_funcptr_decl()) {
                eat(TK_OP, "(");
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); }
                if (match(TK_ID, NULL)) eat(TK_ID, NULL); /* optional name */
                eat(TK_OP, ")");
                skip_param_list();
            } else {
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); }
                /* funcptr after pointer stars: (void*(*)(void*)) */
                if (is_funcptr_decl()) {
                    eat(TK_OP, "(");
                    while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); }
                    if (match(TK_ID, NULL)) eat(TK_ID, NULL); /* optional name */
                    eat(TK_OP, ")");
                    skip_param_list();
                }
            }
            eat(TK_OP, ")");
            /* Compound literal: (struct Type){init} */
            if (cast_stype && match(TK_OP, "{")) {
                Expr *init = parse_init_list(cast_stype);
                return new_compound_lit(cast_stype, init);
            }
            /* Track struct pointer casts for offsetof pattern: ((Type*)0)->field */
            if (cast_stype)
                last_cast_struct_type = cast_stype;
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
        if (0) fprintf(stderr, "DEBUG: sizeof at tok %d\n", pos);
        /* Parse sizeof and resolve to correct size.
         * NOTE: codegen currently uses 8-byte slots for everything,
         * so sizeof returns 8 for most types to stay consistent.
         * sizeof(char) = 1 is the exception (already handled).
         * Correct type sizes (sizeof(int)=4, etc.) deferred until
         * codegen supports width-aware loads/stores.
         */
        eat(TK_KW, NULL);
        int sz = 8; /* default */
        if (match(TK_OP, "(")) {
            eat(TK_OP, "(");
            /* Could be sizeof(type) or sizeof(expr) */
            if (is_type_start()) {
                int is_char = match(TK_KW, "char");
                char *stype = parse_base_type();
                int is_ptr = 0;
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); is_ptr = 1; }
                if (is_ptr) {
                    sz = 8;
                } else if (is_char && !stype) {
                    sz = 1;
                } else if (stype) {
                    /* struct type: look up recursive size */
                    StructDefInfo *sd = find_struct_def(stype);
                    if (sd)
                        sz = parser_struct_nslots(stype) * 8;
                    else
                        sz = 8;
                } else {
                    sz = 8; /* int, long, void, etc. */
                }
                /* Check for array dimension */
                if (match(TK_OP, "[")) {
                    eat(TK_OP, "[");
                    int arr_sz = parse_const_expr();
                    eat(TK_OP, "]");
                    sz = arr_sz * sz;
                }
            } else {
                /* sizeof(expr) — try to resolve struct var for correct size */
                /* Handle sizeof(*p) where p is a pointer to struct */
                if (match(TK_OP, "*") && pos + 1 < ntoks &&
                    toks[pos + 1].kind == TK_ID) {
                    int save_pos = pos;
                    eat(TK_OP, "*");
                    char *vname = cur()->value;
                    Tok *after = (pos + 1 < ntoks) ? &toks[pos + 1] : NULL;
                    int after_is_close = after && after->kind == TK_OP && strcmp(after->value, ")") == 0;
                    if (after_is_close) {
                        LocalVar *lv = find_local(vname);
                        if (lv && lv->is_ptr && lv->struct_type) {
                            int nf = parser_struct_nslots(lv->struct_type);
                            sz = nf * 8;
                            eat(TK_ID, NULL);
                            goto sizeof_done;
                        }
                    }
                    /* Not a pointer-to-struct deref, backtrack */
                    pos = save_pos;
                }
                if (match(TK_ID, NULL) && pos + 1 < ntoks) {
                    char *vname = cur()->value;
                    Tok *next = &toks[pos + 1];
                    int next_is_close = (next->kind == TK_OP && strcmp(next->value, ")") == 0);
                    int next_is_bracket = (next->kind == TK_OP && strcmp(next->value, "[") == 0);
                    int next_is_arrow = (next->kind == TK_OP && strcmp(next->value, "->") == 0);
                    int next_is_dot = (next->kind == TK_OP && strcmp(next->value, ".") == 0);
                    if (next_is_close || next_is_bracket) {
                        LocalVar *lv = find_local(vname);
                        if (lv && lv->struct_type) {
                            int nf = parser_struct_nslots(lv->struct_type);
                            eat(TK_ID, NULL);
                            if (next_is_bracket) {
                                eat(TK_OP, "[");
                                parse_expr(0);
                                eat(TK_OP, "]");
                                sz = nf * 8; /* single element */
                            } else if (lv->array_size > 0) {
                                sz = lv->array_size * nf * 8; /* whole array */
                            } else if (!lv->is_ptr) {
                                sz = nf * 8; /* single struct */
                            }
                            goto sizeof_done;
                        }
                        /* Non-struct local array: sizeof(arr) */
                        if (lv && !lv->struct_type && lv->array_size > 0 && next_is_close) {
                            eat(TK_ID, NULL);
                            sz = lv->array_size * 8;
                            goto sizeof_done;
                        }
                    }
                    /* sizeof(var->field) or sizeof(var.field) */
                    if (next_is_arrow || next_is_dot) {
                        LocalVar *lv = find_local(vname);
                        char *stype = NULL;
                        if (lv) stype = lv->struct_type;
                        if (stype && pos + 2 < ntoks && toks[pos + 2].kind == TK_ID) {
                            char *fname = toks[pos + 2].value;
                            /* Check if token after field name is ')' */
                            if (pos + 3 < ntoks && toks[pos + 3].kind == TK_OP &&
                                strcmp(toks[pos + 3].value, ")") == 0) {
                                StructDefInfo *sd = find_struct_def(stype);
                                if (sd) {
                                    for (int fi = 0; fi < sd->nfields; fi++) {
                                        if (strcmp(sd->fields[fi].name, fname) == 0) {
                                            if (sd->fields[fi].array_size > 0) {
                                                int elem_sz = 8;
                                                if (sd->fields[fi].struct_type)
                                                    elem_sz = parser_struct_nslots(sd->fields[fi].struct_type) * 8;
                                                sz = sd->fields[fi].array_size * elem_sz;
                                            } else if (sd->fields[fi].struct_type && !sd->fields[fi].is_ptr) {
                                                sz = parser_struct_nslots(sd->fields[fi].struct_type) * 8;
                                            } else {
                                                sz = 8;
                                            }
                                            eat(TK_ID, NULL); /* var */
                                            eat(TK_OP, NULL); /* -> or . */
                                            eat(TK_ID, NULL); /* field */
                                            goto sizeof_done;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                parse_expr(0);
            sizeof_done:;
            }
            eat(TK_OP, ")");
        } else {
            parse_unary();
            sz = 8;
        }
        e = new_num(sz);
    } else {
        /* Debug: check if we have sizeof that wasn't matched */
        if (t->kind == TK_KW && strcmp(t->value, "sizeof") == 0) {
            fprintf(stderr, "BUG: sizeof at tok %d should have matched!\n", pos);
        }
        fprintf(stderr, "Context around error (tok %d):\n", pos);
        for (int d = (pos > 30 ? pos - 30 : 0); d < pos + 5 && d < ntoks; d++)
            fprintf(stderr, "  tok[%d] = %s:'%s' (pos=%d)\n", d, tokkind_str(toks[d].kind), toks[d].value, toks[d].pos);
        fatal("Unexpected token %s:'%s' at tok %d", tokkind_str(t->kind), t->value, pos);
        return NULL;
    }

    /* postfix: [], ., ->, ++, --, () */
    while (match(TK_OP, "[") || match(TK_OP, ".") || match(TK_OP, "->") ||
           match(TK_OP, "++") || match(TK_OP, "--") || match(TK_OP, "(")) {
        /* Postfix function call: expr(args) — for indirect calls through non-identifiers */
        if (match(TK_OP, "(")) {
            eat(TK_OP, "(");
            ExprArray args = {NULL, 0, 0};
            if (!match(TK_OP, ")")) {
                while (1) {
                    exprarray_push(&args, parse_expr(0));
                    if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
                    break;
                }
            }
            eat(TK_OP, ")");
            /* Wrap as: assign e to a temp, then call.
               For codegen, we create a call node with the expression as name "__indirect"
               and prepend the function expression as the first "arg". */
            /* Actually, we need to express this in the existing AST.
               The simplest approach: if e is a VAR, create a regular CALL.
               Otherwise, create an UNARY(*) + CALL pattern won't work.
               Let's use the existing indirect call mechanism by assigning to a hidden var. */
            /* Simplest: rewrite expr(args) as a ND_CALL with name from expr if possible */
            if (e->kind == ND_VAR) {
                /* Direct call through variable — this is the normal case */
                e = new_call(e->u.var_name, args);
            } else {
                /* Indirect call through expression (e.g. s.field, arr[i], etc.)
                   Desugar: create a unary dereference of the expression, not possible with current AST.
                   For now, use a special call with "__indirect_call" and expression prepended. */
                /* Actually, let's just handle this by pushing the function expr as first arg
                   and using a special name that codegen will recognize */
                ExprArray new_args = {NULL, 0, 0};
                exprarray_push(&new_args, e);  /* function pointer expression */
                for (int ai = 0; ai < args.len; ai++)
                    exprarray_push(&new_args, args.data[ai]);
                e = new_call("__indirect_call", new_args);
            }
            continue;
        }
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
                if (!st) {
                    GlobalVarInfo *gv = find_global_var(e->u.var_name);
                    if (gv) st = gv->struct_type;
                }
            } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
                st = field_struct_type(e->u.field.struct_type, e->u.field.field);
            } else if (e->kind == ND_INDEX && e->u.index.base->kind == ND_VAR) {
                LocalVar *lv2 = find_local(e->u.index.base->u.var_name);
                if (lv2) st = lv2->struct_type;
                if (!st) {
                    GlobalVarInfo *gv2 = find_global_var(e->u.index.base->u.var_name);
                    if (gv2) st = gv2->struct_type;
                }
            } else if (e->kind == ND_INDEX && (e->u.index.base->kind == ND_FIELD || e->u.index.base->kind == ND_ARROW)) {
                st = field_struct_type(e->u.index.base->u.field.struct_type, e->u.index.base->u.field.field);
            } else if (e->kind == ND_CALL) {
                st = find_func_ret_struct(e->u.call.name);
            }
            /* Use struct type from a recent cast */
            if (!st && last_cast_struct_type) {
                st = last_cast_struct_type;
                last_cast_struct_type = NULL;
            }
            if (!st) st = "__unknown_struct";
            e = new_field(e, field, st);
        } else {
            eat(TK_OP, "->");
            char *field = xstrdup(eat(TK_ID, NULL)->value);
            const char *st = NULL;
            if (e->kind == ND_VAR) {
                LocalVar *lv = find_local(e->u.var_name);
                if (lv) st = lv->struct_type;
                if (!st) {
                    GlobalVarInfo *gv = find_global_var(e->u.var_name);
                    if (gv) st = gv->struct_type;
                }
            } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
                st = field_struct_type(e->u.field.struct_type, e->u.field.field);
            } else if (e->kind == ND_INDEX && e->u.index.base->kind == ND_VAR) {
                LocalVar *lv2 = find_local(e->u.index.base->u.var_name);
                if (lv2) st = lv2->struct_type;
                if (!st) {
                    GlobalVarInfo *gv2 = find_global_var(e->u.index.base->u.var_name);
                    if (gv2) st = gv2->struct_type;
                }
            } else if (e->kind == ND_INDEX && (e->u.index.base->kind == ND_FIELD || e->u.index.base->kind == ND_ARROW)) {
                st = field_struct_type(e->u.index.base->u.field.struct_type, e->u.index.base->u.field.field);
            } else if (e->kind == ND_CALL) {
                st = find_func_ret_struct(e->u.call.name);
            }
            /* Use struct type from a recent cast, e.g. ((Parse*)0)->field */
            if (!st && last_cast_struct_type) {
                st = last_cast_struct_type;
                last_cast_struct_type = NULL;
            }
            if (!st) st = "__unknown_struct";
            e = new_arrow(e, field, st);
        }
    }

    return e;
}

/* ---- Statements ---- */

static int in_switch_depth;  /* tracks unclosed { from Duff's device patterns */

static Block parse_block(void) {
    eat(TK_OP, "{");
    if (in_switch_depth) in_switch_depth++;
    Block b;
    b.stmts.data = NULL;
    b.stmts.len = 0;
    b.stmts.cap = 0;
    while (!match(TK_OP, "}") && !(in_switch_depth && (match(TK_KW, "case") || match(TK_KW, "default"))))
        stmtarray_push(&b.stmts, parse_stmt());
    if (match(TK_OP, "}")) {
        eat(TK_OP, "}");
        if (in_switch_depth) in_switch_depth--;
    }
    /* else: case/default inside switch block (Duff's device) - leave for switch handler */
    return b;
}

static int starts_type(void) {
    if (match(TK_KW, "int") || match(TK_KW, "char") || match(TK_KW, "void") ||
            match(TK_KW, "unsigned") || match(TK_KW, "signed") ||
            match(TK_KW, "long") || match(TK_KW, "short") ||
            match(TK_KW, "struct") || match(TK_KW, "union") || match(TK_KW, "const") ||
            match(TK_KW, "volatile") || match(TK_KW, "register") ||
            match(TK_KW, "static") || match(TK_KW, "enum") ||
            match(TK_KW, "_Bool") || match(TK_KW, "bool") ||
            match(TK_KW, "float") || match(TK_KW, "double"))
        return 1;
    if (cur()->kind == TK_ID && find_typedef(cur()->value))
        return 1;
    return 0;
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
            init = parse_vardecl_stmt(0);
        } else if (match(TK_OP, ";")) {
            eat(TK_OP, ";");
        } else {
            Expr *e = parse_expr(-1);
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
        int saved_switch_depth = in_switch_depth;
        in_switch_depth = 1;

        /* Collect any statements before the first case (e.g., variable declarations) */
        StmtArray pre_stmts = {NULL, 0, 0};
        while (!match(TK_KW, "case") && !match(TK_KW, "default") && !match(TK_OP, "}")) {
            stmtarray_push(&pre_stmts, parse_stmt());
        }

        while (in_switch_depth > 0) {
            /* Skip stray } from Duff's device blocks */
            while (match(TK_OP, "}")) {
                eat(TK_OP, "}");
                in_switch_depth--;
                if (in_switch_depth == 0) goto switch_done;
            }

            Expr *case_val = NULL;
            if (match(TK_KW, "case")) {
                eat(TK_KW, "case");
                int val = parse_const_expr();
                case_val = new_num(val);
                eat(TK_OP, ":");
            } else if (match(TK_KW, "default")) {
                eat(TK_KW, "default");
                eat(TK_OP, ":");
                case_val = NULL;
            } else {
                fprintf(stderr, "Switch context (tok %d, depth=%d):\n", pos, in_switch_depth);
                for (int d = (pos > 15 ? pos - 15 : 0); d < pos + 5 && d < ntoks; d++)
                    fprintf(stderr, "  tok[%d] = %s:'%s'\n", d, tokkind_str(toks[d].kind), toks[d].value);
                fatal("Expected 'case' or 'default' in switch at %d (tok#%d, '%s')", cur()->pos, pos, cur()->value);
            }

            if (ncases >= ccap) {
                ccap = ccap ? ccap * 2 : 8;
                cases = realloc(cases, ccap * sizeof(SwitchCase));
            }
            cases[ncases].value = case_val;
            cases[ncases].stmts.data = NULL;
            cases[ncases].stmts.len = 0;
            cases[ncases].stmts.cap = 0;

            /* Prepend pre-case declarations to first case */
            if (ncases == 0 && pre_stmts.len > 0) {
                for (int pi = 0; pi < pre_stmts.len; pi++)
                    stmtarray_push(&cases[ncases].stmts, pre_stmts.data[pi]);
            }

            /* Parse statements until next case/default or switch end */
            while (!match(TK_KW, "case") && !match(TK_KW, "default") && !match(TK_OP, "}")) {
                stmtarray_push(&cases[ncases].stmts, parse_stmt());
            }
            ncases++;
        }
        switch_done:
        in_switch_depth = saved_switch_depth;
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

    /* Local typedef: typedef type name; — skip it but register the name */
    if (match(TK_KW, "typedef")) {
        eat(TK_KW, "typedef");
        /* Skip everything until semicolon, tracking parens for funcptr typedefs */
        int depth = 0;
        char *last_id = NULL;
        int has_char = 0;
        int has_ptr = 0;
        while (!(depth == 0 && match(TK_OP, ";"))) {
            if (match(TK_OP, "(")) depth++;
            else if (match(TK_OP, ")")) depth--;
            if (cur()->kind == TK_KW && strcmp(cur()->value, "char") == 0) has_char = 1;
            if (cur()->kind == TK_OP && strcmp(cur()->value, "*") == 0) has_ptr = 1;
            if (cur()->kind == TK_ID && depth <= 1) last_id = cur()->value;
            eat(cur()->kind, NULL);
        }
        eat(TK_OP, ";");
        if (last_id) add_typedef_ex(xstrdup(last_id), NULL, has_char && !has_ptr);
        return new_exprstmt(new_num(0));
    }

    /* Variable declaration: starts with a type keyword */
    if (starts_type()) {
        int local_static = 0;
        if (match(TK_KW, "static")) {
            eat(TK_KW, "static");
            local_static = 1;
        }
        /* Standalone struct/union definition: struct Name { ... }; with no variable */
        if (match(TK_KW, "struct") || match(TK_KW, "union")) {
            int saved_pos = pos;
            parse_base_type();
            if (match(TK_OP, ";")) {
                eat(TK_OP, ";");
                return new_exprstmt(new_num(0));
            }
            pos = saved_pos;
        }
        return parse_vardecl_stmt(local_static);
    }

    /* Block statement: { ... } */
    if (match(TK_OP, "{")) {
        Block blk = parse_block();
        /* Wrap block as a series of statements in a synthetic for(;;) with immediate break,
           or simpler: just return statements inline. For now, use an if(1) wrapper. */
        return new_if(new_num(1), blk, NULL);
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
    char *ret_stype = parse_base_type();  /* return type */
    int ret_is_ptr = 0;
    while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); ret_is_ptr = 1; }
    Tok *name_tok = eat(TK_ID, NULL);
    eat(TK_OP, "(");

    char **params = NULL;
    char **param_stypes = NULL;
    int *param_ptrs = NULL;
    int *param_chars = NULL;
    int nparams = 0;
    int pcap = 0;
    int is_variadic = 0;

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
                    is_variadic = 1;
                    break;
                }
                char *stype = parse_base_type();
                int p_is_char = last_type_is_char;
                int is_ptr = 0;
                int is_funcptr = 0;
                /* Function pointer param: type (*name)(params) or type (*)(params) */
                if (is_funcptr_decl()) {
                    eat(TK_OP, "(");
                    eat(TK_OP, "*");
                    is_ptr = 1;
                    is_funcptr = 1;
                }
                int ptr_depth = 0;
                while (match(TK_OP, "*")) {
                    eat(TK_OP, "*");
                    is_ptr++;
                    ptr_depth++;
                    skip_qualifiers();
                }
                /* char** or deeper: not a char pointer (deref gives pointer, not char) */
                if (ptr_depth > 1) p_is_char = 0;
                /* Check for funcptr after pointer stars: type *(*name)(params) */
                if (!is_funcptr && is_funcptr_decl()) {
                    eat(TK_OP, "(");
                    eat(TK_OP, "*");
                    is_funcptr = 1;
                }
                skip_qualifiers();
                /* Unnamed funcptr param: type (*)(params) */
                if (is_funcptr && match(TK_OP, ")")) {
                    eat(TK_OP, ")");
                    skip_param_list();
                    /* unnamed — count for variadic nparams */
                    if (nparams >= pcap) {
                        pcap = pcap ? pcap * 2 : 8;
                        params = realloc(params, pcap * sizeof(char *));
                        param_stypes = realloc(param_stypes, pcap * sizeof(char *));
                        param_ptrs = realloc(param_ptrs, pcap * sizeof(int));
                        param_chars = realloc(param_chars, pcap * sizeof(int));
                    }
                    param_stypes[nparams] = stype ? xstrdup(stype) : NULL;
                    param_ptrs[nparams] = is_ptr;
                    param_chars[nparams] = p_is_char;
                    params[nparams++] = xstrdup("__unnamed");
                    if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
                    break;
                }
                /* Parameter might be unnamed (in prototypes) */
                if (match(TK_ID, NULL)) {
                    Tok *pname = eat(TK_ID, NULL);
                    if (is_funcptr) {
                        eat(TK_OP, ")");
                        skip_param_list();
                    }
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
                        param_stypes = realloc(param_stypes, pcap * sizeof(char *));
                        param_ptrs = realloc(param_ptrs, pcap * sizeof(int));
                        param_chars = realloc(param_chars, pcap * sizeof(int));
                    }
                    param_stypes[nparams] = stype ? xstrdup(stype) : NULL;
                    param_ptrs[nparams] = is_ptr;
                    param_chars[nparams] = p_is_char;
                    params[nparams++] = xstrdup(pname->value);
                    if (stype)
                        add_local(pname->value, stype, is_ptr);
                } else {
                    /* Unnamed param (prototype): count for variadic nparams */
                    if (nparams >= pcap) {
                        pcap = pcap ? pcap * 2 : 8;
                        params = realloc(params, pcap * sizeof(char *));
                        param_stypes = realloc(param_stypes, pcap * sizeof(char *));
                        param_ptrs = realloc(param_ptrs, pcap * sizeof(int));
                        param_chars = realloc(param_chars, pcap * sizeof(int));
                    }
                    param_stypes[nparams] = stype ? xstrdup(stype) : NULL;
                    param_ptrs[nparams] = is_ptr;
                    param_chars[nparams] = p_is_char;
                    params[nparams++] = xstrdup("__unnamed");
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
            proto->is_variadic = is_variadic;
            proto->nparams = nparams;
            proto->ret_struct_type = (ret_stype && ret_is_ptr) ? xstrdup(ret_stype) : NULL;
        }
        if (ret_stype && ret_is_ptr)
            add_func_ret_info(name_tok->value, ret_stype);
        return 0;
    }

    if (ret_stype && ret_is_ptr)
        add_func_ret_info(name_tok->value, ret_stype);

    Block body = parse_block();

    fd->name = xstrdup(name_tok->value);
    fd->params = params;
    fd->param_struct_types = param_stypes;
    fd->param_is_ptr = param_ptrs;
    fd->param_is_char = param_chars;
    fd->nparams = nparams;
    fd->body = body;
    fd->is_static = is_static;
    fd->ret_is_ptr = ret_is_ptr;
    fd->is_variadic = is_variadic;
    fd->ret_struct_type = (ret_stype && ret_is_ptr) ? xstrdup(ret_stype) : NULL;
    return 1;
}

/* Parse an extern declaration: extern type [*]* name [[ N ]] ; */
static GlobalDecl parse_extern_decl(void) {
    eat(TK_KW, "extern");
    /* extern might be followed by a string literal (linkage spec) - skip */

    char *stype = parse_base_type();
    int base_is_char = last_type_is_char;
    int is_ptr = 0;
    int is_funcptr = 0;
    /* extern function pointer: extern type (*name)(params); */
    if (is_funcptr_decl()) {
        eat(TK_OP, "(");
        eat(TK_OP, "*");
        is_ptr = 1;
        is_funcptr = 1;
    }
    while (match(TK_OP, "*")) {
        eat(TK_OP, "*");
        skip_qualifiers();
        is_ptr++;
    }
    Tok *name_tok = eat(TK_ID, NULL);
    if (is_funcptr) {
        eat(TK_OP, ")");
        skip_param_list();
    }
    int arr_size = -1;
    if (match(TK_OP, "[")) {
        eat(TK_OP, "[");
        if (!match(TK_OP, "]"))
            arr_size = parse_const_expr();
        eat(TK_OP, "]");
    }
    /* Skip function prototype: extern int foo(int x); */
    int is_func = 0;
    if (match(TK_OP, "(")) {
        is_func = 1;
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
    gd.is_func_decl = is_func;
    gd.is_char = base_is_char;
    if (is_func && stype && is_ptr)
        add_func_ret_info(name_tok->value, stype);
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
    int base_is_char = last_type_is_char;
    int is_ptr = 0;
    int is_funcptr = 0;
    /* Function pointer global: type (*name)(params) */
    if (is_funcptr_decl()) {
        eat(TK_OP, "(");
        eat(TK_OP, "*");
        is_ptr = 1;
        is_funcptr = 1;
    }
    while (match(TK_OP, "*")) {
        eat(TK_OP, "*");
        skip_qualifiers();
        is_ptr++;
    }
    /* funcptr after pointer stars: type *(*name)(params) */
    if (!is_funcptr && is_funcptr_decl()) {
        eat(TK_OP, "(");
        eat(TK_OP, "*");
        is_funcptr = 1;
    }
    skip_qualifiers();
    Tok *name_tok = eat(TK_ID, NULL);
    int arr_size = -1;
    if (is_funcptr) {
        /* Array of function pointers: type (*name[])(params) */
        if (match(TK_OP, "[")) {
            eat(TK_OP, "[");
            if (match(TK_OP, "]")) {
                arr_size = 0;
            } else {
                arr_size = parse_const_expr();
            }
            eat(TK_OP, "]");
        }
        eat(TK_OP, ")");
        skip_param_list();
    }
    if (arr_size < 0 && match(TK_OP, "[")) {
        eat(TK_OP, "[");
        if (match(TK_OP, "]")) {
            arr_size = 0; /* infer from initializer */
        } else {
            arr_size = parse_const_expr();
        }
        eat(TK_OP, "]");
    }
    Expr *init = NULL;
    if (arr_size >= 0 && match(TK_OP, "=")) {
        /* Array initializer */
        eat(TK_OP, "=");
        if (match(TK_STRING, NULL)) {
            Tok *str_tok = eat(TK_STRING, NULL);
            int slen = strlen(str_tok->value) + 1;
            if (arr_size == 0) arr_size = slen;
            init = new_strlit(str_tok->value);
        } else {
            init = parse_init_list(stype);
            if (arr_size == 0)
                arr_size = init->u.initlist.elems.len;
        }
    } else if (arr_size < 0 && match(TK_OP, "=")) {
        eat(TK_OP, "=");
        /* Struct initializer: = { ... } */
        if (match(TK_OP, "{")) {
            init = parse_init_list(stype);
        /* Handle negative initializers */
        } else if (match(TK_OP, "-")) {
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
    gd.is_func_decl = 0;
    gd.is_char = base_is_char;
    /* Register in parser's global variable table for struct type resolution */
    if (stype) add_global_var_info(name_tok->value, stype, is_ptr);
    return gd;
}

/* Check for function-returning-funcptr pattern: type (* name ( ...
   e.g. void (*sqlite3OsDlSym(sqlite3_vfs*, void*, const char*))(void);
   After base type has been parsed, pos is at '(' of '(* name (' */
static int is_funcptr_return(void) {
    if (!match(TK_OP, "(")) return 0;
    int s = pos;
    if (s + 2 < ntoks && toks[s].kind == TK_OP && strcmp(toks[s].value, "(") == 0 &&
        toks[s+1].kind == TK_OP && strcmp(toks[s+1].value, "*") == 0 &&
        toks[s+2].kind == TK_ID) {
        /* Check if after name there's '(' (params), not ')' (which would be funcptr var) */
        if (s + 3 < ntoks && toks[s+3].kind == TK_OP && strcmp(toks[s+3].value, "(") == 0)
            return 1;
    }
    return 0;
}

/* Skip a funcptr-return declaration/definition, recording it as a prototype.
   Pattern: type (* name (params))(ret_params) { body } or ; */
static void skip_funcptr_return_decl(int is_static,
                                      FuncDef **funcs, int *nfuncs, int *fcap,
                                      FuncProto **protos, int *nprotos, int *pcap) {
    /* We're at '(' of (* name (...  */
    eat(TK_OP, "(");
    eat(TK_OP, "*");
    Tok *name_tok = eat(TK_ID, NULL);
    /* Skip parameter list */
    skip_param_list();
    eat(TK_OP, ")");
    /* Skip return type param list */
    if (match(TK_OP, "(")) skip_param_list();
    if (match(TK_OP, ";")) {
        eat(TK_OP, ";");
        /* Record as prototype */
        if (*nprotos >= *pcap) {
            *pcap = *pcap ? *pcap * 2 : 8;
            *protos = realloc(*protos, *pcap * sizeof(FuncProto));
        }
        FuncProto p;
        p.name = xstrdup(name_tok->value);
        p.ret_is_ptr = 1;
        p.is_variadic = 0;
        p.nparams = 0;
        (*protos)[(*nprotos)++] = p;
    } else if (match(TK_OP, "{")) {
        /* Skip function body */
        eat(TK_OP, "{");
        int depth = 1;
        while (depth > 0 && !match(TK_EOF, NULL)) {
            if (match(TK_OP, "{")) depth++;
            else if (match(TK_OP, "}")) depth--;
            if (depth > 0) pos++;
        }
        eat(TK_OP, "}");
        /* Record as function def (stub) */
        if (*nfuncs >= *fcap) {
            *fcap = *fcap ? *fcap * 2 : 4;
            *funcs = realloc(*funcs, *fcap * sizeof(FuncDef));
        }
        FuncDef fd;
        fd.name = xstrdup(name_tok->value);
        fd.params = NULL;
        fd.nparams = 0;
        fd.body.stmts.data = NULL;
        fd.body.stmts.len = 0;
        fd.body.stmts.cap = 0;
        fd.is_static = is_static;
        fd.ret_is_ptr = 1;
        fd.is_variadic = 0;
        (*funcs)[(*nfuncs)++] = fd;
    }
}

/* Try to parse a function or global with the given static flag */
static void parse_func_or_global(int is_static,
                                  FuncDef **funcs, int *nfuncs, int *fcap,
                                  GlobalDecl **globals, int *nglobals, int *gcap,
                                  FuncProto **protos, int *nprotos, int *pcap) {
    int saved = pos;
    parse_base_type();
    /* Handle function-returning-funcptr: type (* name(params))(ret_params) */
    if (is_funcptr_return()) {
        skip_funcptr_return_decl(is_static, funcs, nfuncs, fcap, protos, nprotos, pcap);
        return;
    }
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
    ntypedefs = 0;
    nglobal_var_infos = 0;
    nfunc_ret_infos = 0;

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
        /* typedef */
        if (match(TK_KW, "typedef")) {
            eat(TK_KW, "typedef");

            /* typedef struct/union Tag { ... } Name; or typedef struct Tag Name; */
            if (match(TK_KW, "struct") || match(TK_KW, "union")) {
                int is_union_td = match(TK_KW, "union");
                if (is_union_td) eat(TK_KW, "union"); else eat(TK_KW, "struct");

                char *tag_name = NULL;
                if (match(TK_ID, NULL)) {
                    tag_name = xstrdup(cur()->value);
                    eat(TK_ID, NULL);
                }

                /* struct body? */
                if (match(TK_OP, "{")) {
                    /* Parse the struct def inline: rewind to re-parse */
                    /* We already consumed struct/union + name, so we need to parse body */
                    /* Parse fields directly */
                    eat(TK_OP, "{");
                    char **fields = NULL;
                    FieldInfo *finfo = NULL;
                    int nf = 0, fcap2 = 0;
                    while (!match(TK_OP, "}")) {
                        char *ftype = parse_base_type();
                        while (1) {
                        int is_ptr = 0;
                        int is_funcptr = 0;
                        if (is_funcptr_decl()) {
                            eat(TK_OP, "("); eat(TK_OP, "*");
                            is_ptr = 1; is_funcptr = 1;
                        }
                        while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); is_ptr++; }
                        if (!is_funcptr && is_funcptr_decl()) {
                            eat(TK_OP, "("); eat(TK_OP, "*");
                            is_ptr++; is_funcptr = 1;
                        }
                        skip_qualifiers();
                        Tok *fname_tok = eat(TK_ID, NULL);
                        if (is_funcptr) { eat(TK_OP, ")"); skip_param_list(); }
                        int arr_sz = -1;
                        if (match(TK_OP, "[")) {
                            eat(TK_OP, "[");
                            if (!match(TK_OP, "]")) arr_sz = parse_const_expr();
                            else arr_sz = 0; /* flexible array */
                            eat(TK_OP, "]");
                        }
                        int bw = 0;
                        if (match(TK_OP, ":")) { eat(TK_OP, ":"); bw = parse_const_expr(); }
                        if (nf >= fcap2) {
                            fcap2 = fcap2 ? fcap2 * 2 : 8;
                            fields = realloc(fields, fcap2 * sizeof(char *));
                            finfo = realloc(finfo, fcap2 * sizeof(FieldInfo));
                        }
                        fields[nf] = xstrdup(fname_tok->value);
                        finfo[nf].name = xstrdup(fname_tok->value);
                        finfo[nf].struct_type = ftype;
                        finfo[nf].is_ptr = is_ptr;
                        finfo[nf].bit_width = bw;
                        finfo[nf].array_size = arr_sz;
                        nf++;
                        if (match(TK_OP, ",")) { eat(TK_OP, ","); continue; }
                        break;
                        }
                        eat(TK_OP, ";");
                    }
                    eat(TK_OP, "}");

                    /* Generate synthetic name for anonymous typedef struct */
                    if (!tag_name) {
                        char synth[64];
                        snprintf(synth, sizeof(synth), "__anon_%d", anon_struct_counter++);
                        tag_name = xstrdup(synth);
                    }

                    /* Register struct def */
                    GROW(struct_defs, nstruct_defs, struct_defs_cap, StructDefInfo);
                    struct_defs[nstruct_defs].name = xstrdup(tag_name);
                    struct_defs[nstruct_defs].fields = finfo;
                    struct_defs[nstruct_defs].nfields = nf;
                    nstruct_defs++;

                    /* Also add to program structs */
                    char **ftypes = xmalloc(nf * sizeof(char *));
                    char **fptypes = xmalloc(nf * sizeof(char *));
                    for (int fi = 0; fi < nf; fi++) {
                        ftypes[fi] = (finfo[fi].struct_type && !finfo[fi].is_ptr) ? xstrdup(finfo[fi].struct_type) : NULL;
                        fptypes[fi] = (finfo[fi].struct_type && finfo[fi].is_ptr == 1) ? xstrdup(finfo[fi].struct_type) : NULL;
                    }
                    if (nstructs >= scap) {
                        scap = scap ? scap * 2 : 4;
                        structs = realloc(structs, scap * sizeof(StructDef));
                    }
                    structs[nstructs].name = xstrdup(tag_name);
                    structs[nstructs].fields = fields;
                    structs[nstructs].field_types = ftypes;
                    structs[nstructs].field_ptr_types = fptypes;
                    structs[nstructs].nfields = nf;
                    structs[nstructs].is_union = is_union_td;
                    structs[nstructs].bit_widths = NULL;
                    structs[nstructs].bit_offsets = NULL;
                    structs[nstructs].word_indices = NULL;
                    structs[nstructs].nwords = 0;
                    /* Build field_array_sizes */
                    {
                        int has_arr = 0;
                        for (int k = 0; k < nf; k++)
                            if (finfo[k].array_size >= 0) { has_arr = 1; break; }
                        if (has_arr) {
                            structs[nstructs].field_array_sizes = xmalloc(nf * sizeof(int));
                            for (int k = 0; k < nf; k++)
                                structs[nstructs].field_array_sizes[k] = finfo[k].array_size;
                        } else {
                            structs[nstructs].field_array_sizes = NULL;
                        }
                    }
                    nstructs++;
                }

                /* Skip pointer stars */
                while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); }

                /* The typedef alias name */
                if (match(TK_ID, NULL)) {
                    char *alias = xstrdup(eat(TK_ID, NULL)->value);
                    add_typedef(alias, tag_name);
                }
                eat(TK_OP, ";");

            } else if (match(TK_KW, "enum")) {
                /* typedef enum ... Name; — parse enum def if body, then alias */
                eat(TK_KW, "enum");
                if (match(TK_ID, NULL)) eat(TK_ID, NULL); /* optional tag */
                if (match(TK_OP, "{")) {
                    /* Parse enum body */
                    eat(TK_OP, "{");
                    int value = 0;
                    while (!match(TK_OP, "}")) {
                        Tok *ename = eat(TK_ID, NULL);
                        if (match(TK_OP, "=")) {
                            eat(TK_OP, "=");
                            value = parse_const_expr();
                        }
                        add_enum_const(ename->value, value);
                        value++;
                        if (match(TK_OP, ",")) eat(TK_OP, ",");
                    }
                    eat(TK_OP, "}");
                }
                /* alias name */
                if (match(TK_ID, NULL)) {
                    char *alias = xstrdup(eat(TK_ID, NULL)->value);
                    add_typedef(alias, NULL);  /* enum → int-like */
                }
                eat(TK_OP, ";");

            } else {
                /* typedef <base-type> [*]* Name; or typedef with function pointers */
                /* Try to parse base type */
                char *stype = parse_base_type();
                int td_is_char = last_type_is_char;
                /* Check for function pointer: (*Name)(params) */
                if (match(TK_OP, "(") && pos + 1 < ntoks &&
                    toks[pos+1].kind == TK_OP && strcmp(toks[pos+1].value, "*") == 0) {
                    /* typedef rettype (*Name)(params); — skip, store as int-like typedef */
                    eat(TK_OP, "(");
                    eat(TK_OP, "*");
                    char *alias = xstrdup(eat(TK_ID, NULL)->value);
                    eat(TK_OP, ")");
                    /* skip param list */
                    eat(TK_OP, "(");
                    int depth = 1;
                    while (depth > 0) {
                        if (match(TK_OP, "(")) depth++;
                        else if (match(TK_OP, ")")) depth--;
                        if (depth > 0) eat(cur()->kind, NULL);
                    }
                    eat(TK_OP, ")");
                    eat(TK_OP, ";");
                    add_typedef(alias, NULL);
                } else {
                    /* Normal: typedef type [*]* Name; */
                    while (match(TK_OP, "*")) { eat(TK_OP, "*"); skip_qualifiers(); stype = NULL; td_is_char = 0; /* ptr-to-struct is just ptr */ }
                    /* Check again for funcptr after stars: typedef int *(*Name)(params); */
                    if (match(TK_OP, "(") && pos + 1 < ntoks &&
                        toks[pos+1].kind == TK_OP && strcmp(toks[pos+1].value, "*") == 0) {
                        eat(TK_OP, "(");
                        eat(TK_OP, "*");
                        char *alias = xstrdup(eat(TK_ID, NULL)->value);
                        eat(TK_OP, ")");
                        eat(TK_OP, "(");
                        int depth = 1;
                        while (depth > 0) {
                            if (match(TK_OP, "(")) depth++;
                            else if (match(TK_OP, ")")) depth--;
                            if (depth > 0) eat(cur()->kind, NULL);
                        }
                        eat(TK_OP, ")");
                        eat(TK_OP, ";");
                        add_typedef(alias, NULL);
                        continue;
                    }
                    char *alias = xstrdup(eat(TK_ID, NULL)->value);
                    /* skip array dimensions like typedef int Arr[10]; */
                    if (match(TK_OP, "[")) {
                        eat(TK_OP, "[");
                        if (!match(TK_OP, "]")) parse_const_expr();
                        eat(TK_OP, "]");
                    }
                    eat(TK_OP, ";");
                    add_typedef_ex(alias, stype, td_is_char);
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
                if (match(TK_OP, ";")) eat(TK_OP, ";");
            } else if (match(TK_OP, ";")) {
                /* Forward declaration: struct Foo; — just skip */
                eat(TK_OP, ";");
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

    /* Merge inline anonymous structs */
    for (int k = 0; k < ninline_structs; k++) {
        if (nstructs >= scap) {
            scap = scap ? scap * 2 : 4;
            structs = realloc(structs, scap * sizeof(StructDef));
        }
        structs[nstructs++] = inline_structs[k];
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
