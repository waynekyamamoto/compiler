// Self-hosting C compiler - compiles itself using only the C subset it supports
// Supported: int, int *, struct, if/else/while/for/do-while/switch/break/continue/return
// Supported: enum, typedef, sizeof, goto/labels, char/void/unsigned/signed/long/short(as int)
// Supported: const/volatile/register/static/extern(skip), type casts(no-op), hex literals
// Supported: ^, <<, >>, ++x/--x, +=/-=/*=//=/%=/&=/|=/^=, ~, ternary, comma operator
// Supported: _Bool/bool, inline(skip), \a\b\f\v, \xHH, \ooo escapes
// Supported: union
// No: floating point

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __STDC__
static inline int __read_byte(void *p, int i) { return ((unsigned char*)p)[i]; }
static inline void __write_byte(void *p, int i, int v) { ((unsigned char*)p)[i] = v; }
#else
int printf(int *fmt, ...);
int *fopen(int *path, int *mode);
int fgetc(int *f);
int fclose(int *f);
int fputc(int c, int *f);
int fflush(int *f);
int *malloc(int size);
int *realloc(int *ptr, int size);
int exit(int code);
int system(int *cmd);
#endif

// ---- Constants ----
enum { TK_NUM, TK_ID, TK_STR, TK_KW, TK_OP, TK_EOF };
enum { ND_NUM, ND_VAR, ND_STRLIT, ND_CALL, ND_UNARY, ND_BINARY,
       ND_INDEX, ND_FIELD, ND_ARROW, ND_ASSIGN, ND_POSTINC, ND_POSTDEC,
       ND_TERNARY, ND_INITLIST, ND_COMPOUND_LIT, ND_CAST, ND_STMT_EXPR, ND_LABEL_ADDR };
enum { ST_RETURN, ST_IF, ST_WHILE, ST_FOR, ST_BREAK, ST_CONTINUE,
       ST_EXPR, ST_VARDECL, ST_DOWHILE, ST_GOTO, ST_LABEL, ST_SWITCH, ST_BLOCK, ST_COMPUTED_GOTO };

// Capacity constants
enum {
    MAX_TOKENS       = 1048576,  // tok_kind, tok_val, tok_pos
    MAX_STRINGS      = 65536,    // sp_decoded, sp_label
    MAX_CG_GLOBALS   = 65536,    // cg_gnames, cg_gis_array, etc.
    MAX_ENUMS        = 65536,    // ec_table
    MAX_MACRO_BUCKETS = 65536,   // macro_ht_head
    MAX_RET_FUNCS    = 16384,    // ptr_ret_names, unsigned_ret_names
    MAX_MACROS       = 16384,    // macro_names, macro_values, etc.
    MAX_GLV          = 16384,    // glv_name, glv_stype, etc.
    MAX_KNOWN_FUNCS  = 16384,    // known_funcs, defined_funcs
    MAX_PROGRAM      = 16384,    // Program struct: funcs, protos, globals
    MAX_STRUCTS      = 4096,     // cg_s*, p_sdefs, inline_sdefs
    MAX_TYPEDEFS     = 4096,     // td_name, td_stype, etc.
    MAX_STATIC_LOCALS = 4096,    // sl_names, sl_labels, etc.
    MAX_FUNC_INFO    = 4096,     // struct_ret, float_ret, barechar, variadic
    MAX_LOCAL_VARS   = 512,      // lv_name, lv_stype, etc.
    MAX_LAYOUT       = 512,      // lay_name, lay_off, lay_char_name, etc.
    MAX_LAYOUT_ARR   = 256,      // lay_arr_name, lay_sv_name, lay_psv_name
    MAX_LOOP_STACK   = 64,       // loop_brk, loop_cont
    MAX_IF_STACK     = 32        // if_stack_*
};


// ---- Structs ----
struct Expr {
  int kind;
  long ival;
  int *sval;
  int *sval2;
  struct Expr *left;
  struct Expr *right;
  struct Expr **args;
  int nargs;
  int *desig;
};

struct VarDecl {
  int *name;
  int *stype;
  int arr_size;
  int is_ptr;
  struct Expr *init;
  int is_static;
  int is_unsigned;
  int arr_size2;
  int is_char;
  int is_float;
  int is_short;
  int is_long;
};

struct Stmt {
  int kind;
  struct Expr *expr;
  struct Expr *expr2;
  struct Stmt **body;
  int nbody;
  struct Stmt **body2;
  int nbody2;
  struct Stmt *init;
  struct VarDecl **decls;
  int ndecls;
  int *sval;
  int *case_vals;
  struct Stmt ***case_bodies;
  int *case_nbodies;
  int ncases;
  struct Stmt **default_body;
  int ndefault;
};

struct FuncDef {
  int *name;
  int **params;
  int nparams;
  struct Stmt **body;
  int nbody;
  int ret_is_ptr;
  int ret_is_unsigned;
  int ret_is_long;
  int is_variadic;
  int *param_is_char;
  int *param_is_unsigned;
  int *param_is_intptr;
  int *param_is_long;
  int *param_is_short;
  int *ret_stype;
  int **param_stypes;
  int *param_is_float;
  int ret_is_float;
  int is_static;
};

struct SDef {
  int *name;
  int **fields;
  int **field_types;
  int nfields;
  int is_union;
  int *bit_widths;
  int *bit_offsets;
  int *word_indices;
  int nwords;
  int *field_is_array;
  int *field_is_char;
  int *field_is_ptr;
  int *field_is_short;
  int *field_is_long;
  int *field_is_char_type;
  int *field_is_unsigned;
};

struct SFieldInfo {
  int *name;
  int *stype;
  int is_ptr;
  int bit_width;
  int is_array;
  int is_char;
  int is_short;
  int is_long;
  int is_char_type;  // base type is char (regardless of ptr/arr)
  int is_unsigned;
};

struct SDefInfo {
  int *name;
  struct SFieldInfo **flds;
  int nflds;
  int nwords;
  int is_union;
};

struct GDecl {
  int *name;
  int is_ptr;
  int array_size;
  int init_val;
  int has_init;
  int *init_str;
  struct Expr *init_list;  // ND_INITLIST node for array init (NULL if no array init)
  int *stype;  // struct type name (or 0 for non-struct)
  int is_char;
  int is_static;
  int is_unsigned;
  int is_short;
  int is_long;
};

struct Program {
  struct SDef **structs;
  int nstructs;
  struct FuncDef **funcs;
  int nfuncs;
  int **proto_names;
  int *proto_ret_is_ptr;
  int *proto_ret_is_unsigned;
  int *proto_ret_is_long;
  int *proto_is_variadic;
  int *proto_nparams;
  int **proto_ret_stype;
  int *proto_ret_is_float;
  int nprotos;
  struct GDecl **globals;
  int nglobals;
};

// ---- Globals ----
// Output buffer (byte buffer)
int *outbuf;
int outlen;
int outcap;

// Ptr-returning function names (for sxtw after bl)
int *ptr_ret_names[MAX_RET_FUNCS];
int n_ptr_ret;

// Unsigned-returning function names (skip sxtw after bl)
int *unsigned_ret_names[MAX_RET_FUNCS];
int n_unsigned_ret;


// Struct-returning function names and their struct types
int *struct_ret_names[MAX_FUNC_INFO];
int *struct_ret_stypes[MAX_FUNC_INFO];
int n_struct_ret;

// Label counter
int label_id;

// String pool
int *sp_decoded[MAX_STRINGS];
int *sp_label[MAX_STRINGS];
int nsp;

// Loop stack
int *loop_brk[MAX_LOOP_STACK];
int *loop_cont[MAX_LOOP_STACK];
int nloop;

// Global variable names for codegen
struct CGlobal {
  int *name;
  int is_array;
  int is_char;
  int is_char_arr;
  int *stype;
  int *ptr_stype;
  int is_barechar;
  int is_intptr;
  int is_bare_char_arr;
  int esz;
  int ptr_esz;
};
struct CGlobal cgg[MAX_CG_GLOBALS];
int ncg_g;
int cgg_var_bsz[MAX_CG_GLOBALS];
int cgg_is_unsigned[MAX_CG_GLOBALS];

// Struct/union defs for codegen
int *cg_sname[MAX_STRUCTS];
int **cg_sfields[MAX_STRUCTS];
int **cg_sfield_types[MAX_STRUCTS];
int cg_snfields[MAX_STRUCTS];
int cg_s_is_union[MAX_STRUCTS];
int *cg_s_bw[MAX_STRUCTS];     // bit_widths
int *cg_s_bo[MAX_STRUCTS];     // bit_offsets
int *cg_s_wi[MAX_STRUCTS];     // word_indices
int cg_s_nw[MAX_STRUCTS];      // nwords
int *cg_s_fa[MAX_STRUCTS];     // field_is_array flags
int *cg_s_fc[MAX_STRUCTS];     // field_is_char flags
int *cg_s_fp[MAX_STRUCTS];     // field_is_ptr flags
int *cg_s_fsh[MAX_STRUCTS];    // field_is_short flags
int *cg_s_fl[MAX_STRUCTS];     // field_is_long flags
int *cg_s_fct[MAX_STRUCTS];   // field_is_char_type flags
int *cg_s_fu[MAX_STRUCTS];    // field_is_unsigned flags
int *cg_s_fbyteoff[MAX_STRUCTS];  // per-field byte offset (proper layout)
int *cg_s_fbytesize[MAX_STRUCTS]; // per-field byte size (proper layout)
int cg_s_bytesize[MAX_STRUCTS];   // total struct byte size (proper layout)
int cg_s_max_align[MAX_STRUCTS];  // max field alignment (for embedded struct alignment)
int ncg_s;

// Proper struct layout flag
int use_proper_layout = 1;

// Token arrays
struct Token {
  int kind;
  int *val;
  int pos;
};
struct Token tok[MAX_TOKENS];
int ntokens;

// Parser state
int cur_pos;

// Parser struct defs (with field type info)
struct SDefInfo *p_sdefs[MAX_STRUCTS];
int np_sdefs;

// Local variable table (reset per function)
struct LocalVar {
  int *name;
  int *stype;
  int isptr;
  int arrsize;
  int is_char;
};
struct LocalVar lv[MAX_LOCAL_VARS];
int nlv;

// Global variable struct type table (persistent across functions)
struct GlobalVar {
  int *name;
  int *stype;
  int isptr;
  int arrsize;
  int is_char;
};
struct GlobalVar glv[MAX_GLV];
int nglv;
int lv_is_long[MAX_LOCAL_VARS];
int lv_is_short[MAX_LOCAL_VARS];
int glv_is_long[MAX_GLV];
int glv_is_short[MAX_GLV];

// Layout data
int *lay_name[MAX_LAYOUT];
int lay_off[MAX_LAYOUT];
int lay_var_bsz[MAX_LAYOUT];
int nlay;
int *lay_arr_name[MAX_LAYOUT_ARR];
int lay_arr_count[MAX_LAYOUT_ARR];
int lay_arr_inner[MAX_LAYOUT_ARR];
int lay_arr_esz[MAX_LAYOUT_ARR];
int nlay_arr;
int *lay_sv_name[MAX_LAYOUT_ARR];
int *lay_sv_type[MAX_LAYOUT_ARR];
int nlay_sv;
int *lay_psv_name[MAX_LAYOUT_ARR];
int *lay_psv_type[MAX_LAYOUT_ARR];
int nlay_psv;
int *lay_unsigned_name[MAX_LAYOUT];
int nlay_unsigned;
int *lay_char_name[MAX_LAYOUT];
int nlay_char;
int *lay_char_arr_name[MAX_LAYOUT];
int nlay_char_arr;
int *lay_char_larr_name[MAX_LAYOUT]; // char local arrays: char arr[N]
int nlay_char_larr;
int *lay_intptr_name[MAX_LAYOUT];
int lay_intptr_esz[MAX_LAYOUT];
int nlay_intptr;
int *lay_float_name[MAX_LAYOUT];
int nlay_float;
int *lay_barechar_name[MAX_LAYOUT];
int lay_barechar_unsigned[MAX_LAYOUT];
int nlay_barechar;
int *lay_long_name[MAX_LAYOUT];
int nlay_long;
int lay_stack_size;

// Float-returning function names
int *float_ret_names[MAX_FUNC_INFO];
int n_float_ret;

// Enum constant table
struct EnumConst {
  int *name;
  int val;
};
struct EnumConst ec_table[MAX_ENUMS];
int nec;

// Typedef table
struct TypeDef {
  int *name;
  int *stype;
  int is_char;
  int is_unsigned;
  int is_funcptr;
};
struct TypeDef td[MAX_TYPEDEFS];
int ntd;
int td_is_long[MAX_TYPEDEFS];
int td_is_short[MAX_TYPEDEFS];
int td_is_unsigned[MAX_TYPEDEFS];
int td_is_ptr[MAX_TYPEDEFS];

// Current function name for goto label mangling
int *cg_cur_func_name;
int *cg_cur_func_ret_stype;
int cg_cur_func_ret_is_float;

// Compound literal counters
int cg_cl_counter;
int cg_cl_gen_counter;

// Anonymous struct counter
int anon_struct_counter;

// Static global dedup counter
int static_global_counter;

// Parser: last_type_unsigned flag
int last_type_unsigned;
int last_type_is_long;
int last_type_is_short;

// Inline struct defs for anonymous structs
struct SDef *inline_sdefs[MAX_STRUCTS];
int ninline_sdefs;
int anon_struct_counter;

// Macro table for #define
struct Macro {
  int *name;
  int *value;
  int nparams;
  int **params;
  int *body;
  int is_variadic;
  int def_pos;
  int ht_next;
  int nlen;
};
struct Macro macros[MAX_MACROS];
int nmacros;
// Hash table for macro lookup
int macro_ht_head[MAX_MACRO_BUCKETS]; // hash -> first macro index, -1 = empty

// Conditional compilation stack
int if_stack_including[MAX_IF_STACK];
int if_stack_seen_else[MAX_IF_STACK];
int if_stack_satisfied[MAX_IF_STACK];
int if_depth;

// Include depth tracking
int include_depth;

// Known function names (for function pointer support)
int *known_funcs[MAX_KNOWN_FUNCS];
int nknown_funcs;

// Defined function names (functions with bodies, not just prototypes)
int *defined_funcs[MAX_KNOWN_FUNCS];
int ndefined_funcs;

// Bare char parameter tracking (side table indexed by function)
int *barechar_func_names[MAX_FUNC_INFO];
int *barechar_param_data[MAX_FUNC_INFO];  // array of barechar flags per param
int nbarechar_funcs;

// Variadic function table
int *var_funcs[MAX_FUNC_INFO];
int var_nparams[MAX_FUNC_INFO];
int nvar_funcs;

// Static local variables
struct StaticLocal {
  int *name;
  int *label;
  int *func;
  int init_val;
  int has_init;
  struct Expr *init_list;
  int arr_size;
  int *stype;
};
struct StaticLocal sl[MAX_STATIC_LOCALS];
int nsl;

// ---- Forward declarations (needed for clang, which doesn't allow implicit decls) ----
#ifdef __STDC__
extern int *include_dirs[64];
extern int ninclude_dirs;
int skip_attribute();
int parse_const_expr();
struct Expr *parse_expr(int min_prec);
struct Expr *parse_unary();
struct Expr *parse_primary();
int parse_enum_def();
int parse_const_unary();
int lay_walk_stmts(struct Stmt **stmts, int nstmts, int *offset);
int gen_value(struct Expr *e);
int gen_stmt(struct Stmt *st, int *ret_label);
#endif

// ---- Utility functions ----

int my_fatal(int *msg) {
  printf("cc: %s\n", msg);
  exit(1);
  return 0;
}

int total_alloc;
int n_allocs;
int *my_malloc(int size) {
  int *p = malloc(size);
  if (p == 0) {
    printf("cc: OOM at alloc #%d, total=%d, requested=%d\n", n_allocs, total_alloc, size);
    fflush(0);
    my_fatal("out of memory");
  }
  total_alloc = total_alloc + size;
  n_allocs++;
  return p;
}

int *my_strdup(int *s) {
  int len = strlen(s);
  int *p = my_malloc(len + 1);
  for (int i = 0; i <= len; i++) {
    __write_byte(p, i, __read_byte(s, i));
  }
  return p;
}

int my_strcmp(int *a, int *b) {
  if (a == 0 || b == 0) return (a != b);
  return strcmp(a, b);
}

int my_strlen(int *s) {
  return strlen(s);
}

int is_hex_digit(int c) {
  if (c >= '0' && c <= '9') { return 1; }
  if (c >= 'a' && c <= 'f') { return 1; }
  if (c >= 'A' && c <= 'F') { return 1; }
  return 0;
}

int hex_digit_val(int c) {
  if (c >= '0' && c <= '9') { return c - '0'; }
  if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
  if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
  return 0;
}

long my_atoi(int *s) {
  long val = 0;
  int i = 0;
  int neg = 0;
  if (__read_byte(s, 0) == '-') {
    neg = 1;
    i = 1;
  }
  if (__read_byte(s, i) == '0' && (__read_byte(s, i + 1) == 'x' || __read_byte(s, i + 1) == 'X')) {
    i += 2;
    while (is_hex_digit(__read_byte(s, i))) {
      val = val * 16 + hex_digit_val(__read_byte(s, i));
      i++;
    }
  } else if (__read_byte(s, i) == '0' && (__read_byte(s, i + 1) == 'b' || __read_byte(s, i + 1) == 'B')) {
    i += 2;
    while (__read_byte(s, i) == '0' || __read_byte(s, i) == '1') {
      val = val * 2 + __read_byte(s, i) - '0';
      i++;
    }
  } else if (__read_byte(s, i) == '0' && __read_byte(s, i + 1) >= '0' && __read_byte(s, i + 1) <= '7') {
    i++;
    while (__read_byte(s, i) >= '0' && __read_byte(s, i) <= '7') {
      val = val * 8 + __read_byte(s, i) - '0';
      i++;
    }
  } else {
    while (__read_byte(s, i) >= '0' && __read_byte(s, i) <= '9') {
      val = val * 10 + __read_byte(s, i) - '0';
      i++;
    }
  }
  if (neg) {
    val = 0 - val;
  }
  return val;
}

// ---- Output helpers ----

int emit_ch(int c) {
  if (outlen >= outcap) {
    outcap *= 2;
    int *newbuf = my_malloc(outcap);
    int i = 0;
    while (i < outlen) {
      __write_byte(newbuf, i, __read_byte(outbuf, i));
      i++;
    }
    outbuf = newbuf;
  }
  __write_byte(outbuf, outlen, c);
  outlen++;
  return 0;
}

int emit_s(int *s) {
  int i = 0;
  while (__read_byte(s, i) != 0) {
    emit_ch(__read_byte(s, i));
    i++;
  }
  return 0;
}

int emit_num(int n) {
  if (n < 0) {
    emit_ch('-');
    n = 0 - n;
  }
  if (n >= 10) {
    emit_num(n / 10);
  }
  emit_ch('0' + n % 10);
  return 0;
}

int emit_unum(int n) {
  // Emit as unsigned (for movz/movk)
  if (n >= 10) {
    emit_unum(n / 10);
  }
  emit_ch('0' + n % 10);
  return 0;
}

int emit_line(int *s) {
  emit_s(s);
  emit_ch('\n');
  return 0;
}

// Emit mov reg, #imm handling large immediates via movz/movk
int emit_mov_imm(int *reg, long val) {
  if (val >= 0 && val <= 65535) {
    emit_s("\tmov\t"); emit_s(reg); emit_s(", #"); emit_num(val); emit_ch('\n');
  } else if (val < 0 && val >= 0 - 65536) {
    emit_s("\tmov\t"); emit_s(reg); emit_s(", #"); emit_num(val); emit_ch('\n');
  } else {
    int lo = val & 0xFFFF;
    int hi = (val >> 16) & 0xFFFF;
    int hi2 = ((val >> 16) >> 16) & 0xFFFF;
    emit_s("\tmovz\t"); emit_s(reg); emit_s(", #"); emit_num(lo); emit_ch('\n');
    if (hi != 0) {
      emit_s("\tmovk\t"); emit_s(reg); emit_s(", #"); emit_num(hi); emit_s(", lsl #16"); emit_ch('\n');
    }
    if (hi2 != 0) {
      emit_s("\tmovk\t"); emit_s(reg); emit_s(", #"); emit_num(hi2); emit_s(", lsl #32"); emit_ch('\n');
    }
  }
  return 0;
}

// Emit sub dst, src, #imm handling large immediates
int emit_sub_imm(int *dst, int *src, int val) {
  if (val <= 4095) {
    emit_s("\tsub\t"); emit_s(dst); emit_s(", "); emit_s(src); emit_s(", #"); emit_num(val); emit_ch('\n');
  } else {
    emit_mov_imm("x11", val);
    emit_s("\tsub\t"); emit_s(dst); emit_s(", "); emit_s(src); emit_s(", x11"); emit_ch('\n');
  }
  return 0;
}

// Emit add dst, src, #imm handling large immediates
int emit_add_imm(int *dst, int *src, int val) {
  if (val <= 4095) {
    emit_s("\tadd\t"); emit_s(dst); emit_s(", "); emit_s(src); emit_s(", #"); emit_num(val); emit_ch('\n');
  } else {
    emit_mov_imm("x11", val);
    emit_s("\tadd\t"); emit_s(dst); emit_s(", "); emit_s(src); emit_s(", x11"); emit_ch('\n');
  }
  return 0;
}

// Build a char* string from pieces
int *build_str2(int *a, int *b) {
  int la = my_strlen(a);
  int lb = my_strlen(b);
  int *buf = my_malloc(la + lb + 1);
  int i = 0;
  while (i < la) {
    __write_byte(buf, i, __read_byte(a, i));
    i++;
  }
  for (int j = 0; j < lb; j++) {
    __write_byte(buf, i + j, __read_byte(b, j));
  }
  __write_byte(buf, la + lb, 0);
  return buf;
}

// Convert int to string
int *int_to_str(int n) {
  int buf[32];
  int len = 0;
  int neg = 0;
  if (n < 0) {
    neg = 1;
    n = 0 - n;
  }
  if (n == 0) {
    buf[0] = '0';
    len = 1;
  }
  while (n > 0) {
    buf[len] = '0' + n % 10;
    len++;
    n /= 10;
  }
  int total = len;
  if (neg) {
    total++;
  }
  int *result = my_malloc(total + 1);
  int pos = 0;
  if (neg) {
    __write_byte(result, 0, '-');
    pos = 1;
  }
  for (int k = 0; k < len; k++) {
    __write_byte(result, pos + k, buf[len - 1 - k]);
  }
  __write_byte(result, total, 0);
  return result;
}

// Make a substring as a proper char* string
int *make_str(int *src, int start, int len) {
  int *buf = my_malloc(len + 1);
  for (int i = 0; i < len; i++) {
    __write_byte(buf, i, __read_byte(src, start + i));
  }
  __write_byte(buf, len, 0);
  return buf;
}

// ---- Preprocessor helpers ----

int pp_is_macro_defined(int *name) {
  int i = 0;
  while (i < nmacros) {
    if (my_strcmp(macros[i].name, name) == 0) { return 1; }
    i++;
  }
  return 0;
}

// Check if all if_stack levels are including
int pp_is_including() {
  int i = 0;
  while (i < if_depth) {
    if (if_stack_including[i] == 0) { return 0; }
    i++;
  }
  return 1;
}

// Check if parent levels (0..if_depth-2) are including
int pp_parent_including() {
  int i = 0;
  while (i < if_depth - 1) {
    if (if_stack_including[i] == 0) { return 0; }
    i++;
  }
  return 1;
}

// Get directory from a file path (returns new string)
int *pp_get_dir(int *path) {
  int len = my_strlen(path);
  int last_slash = 0 - 1;
  int i = len - 1;
  while (i >= 0) {
    if (__read_byte(path, i) == '/') { last_slash = i; i = 0 - 1; }
    i--;
  }
  if (last_slash < 0) {
    int *dot = my_malloc(2);
    __write_byte(dot, 0, '.');
    __write_byte(dot, 1, 0);
    return dot;
  }
  int *dir = my_malloc(last_slash + 2);
  i = 0;
  while (i <= last_slash) {
    __write_byte(dir, i, __read_byte(path, i));
    i++;
  }
  __write_byte(dir, last_slash + 1, 0);
  return dir;
}

// Concatenate dir + filename
int *pp_concat_paths(int *dir, int *file) {
  int dlen = my_strlen(dir);
  int flen = my_strlen(file);
  int need_slash = 0;
  if (dlen > 0 && __read_byte(dir, dlen - 1) != '/') { need_slash = 1; }
  int *result = my_malloc(dlen + need_slash + flen + 1);
  int o = 0;
  int i = 0;
  while (i < dlen) { __write_byte(result, o, __read_byte(dir, i)); o++; i++; }
  if (need_slash) { __write_byte(result, o, '/'); o++; }
  i = 0;
  while (i < flen) { __write_byte(result, o, __read_byte(file, i)); o++; i++; }
  __write_byte(result, o, 0);
  return result;
}

// Read a file into a buffer, return pointer and set *out_len
int *pp_read_file(int *path, int *out_len) {
  int *f = fopen(path, "r");
  if (f == 0) {
    printf("cc: Cannot open include: %s\n", path);
    exit(1);
  }
  int *buf = my_malloc(10 * 1000 * 1000);
  int len = 0;
  int ch = fgetc(f);
  while (ch != 0 - 1) {
    __write_byte(buf, len, ch);
    len++;
    ch = fgetc(f);
  }
  __write_byte(buf, len, 0);
  fclose(f);
  // Store length at out_len pointer (use first element)
  *out_len = len;
  return buf;
}

// Recursive descent #if expression evaluator
int *ifex_buf;    // expression buffer
int ifex_pos;     // current position
int ifex_len;     // length

int ifex_ch() {
  if (ifex_pos >= ifex_len) { return 0; }
  return __read_byte(ifex_buf, ifex_pos);
}

int ifex_skip_ws() {
  while (ifex_pos < ifex_len && (ifex_ch() == ' ' || ifex_ch() == '\t')) { ifex_pos++; }
  return 0;
}

int ifex_is_alnum(int c) {
  if (c >= 'a' && c <= 'z') { return 1; }
  if (c >= 'A' && c <= 'Z') { return 1; }
  if (c >= '0' && c <= '9') { return 1; }
  if (c == '_') { return 1; }
  return 0;
}

int ifex_parse_or();

int ifex_parse_num() {
  int val = 0;
  int d = 0;
  if (ifex_ch() == '0' && ifex_pos + 1 < ifex_len &&
      (__read_byte(ifex_buf, ifex_pos + 1) == 'x' || __read_byte(ifex_buf, ifex_pos + 1) == 'X')) {
    ifex_pos += 2;
    while (ifex_pos < ifex_len) {
      d = ifex_ch();
      if (d >= '0' && d <= '9') { val = val * 16 + d - '0'; }
      else if (d >= 'a' && d <= 'f') { val = val * 16 + d - 'a' + 10; }
      else if (d >= 'A' && d <= 'F') { val = val * 16 + d - 'A' + 10; }
      else { return val; }
      ifex_pos++;
    }
  } else if (ifex_ch() == '0' && ifex_pos + 1 < ifex_len &&
      (__read_byte(ifex_buf, ifex_pos + 1) == 'b' || __read_byte(ifex_buf, ifex_pos + 1) == 'B')) {
    ifex_pos += 2;
    while (ifex_pos < ifex_len && (ifex_ch() == '0' || ifex_ch() == '1')) {
      val = val * 2 + ifex_ch() - '0';
      ifex_pos++;
    }
  } else {
    while (ifex_pos < ifex_len && ifex_ch() >= '0' && ifex_ch() <= '9') {
      val = val * 10 + ifex_ch() - '0';
      ifex_pos++;
    }
  }
  return val;
}

int ifex_parse_primary() {
  int ns = 0;
  int nlen = 0;
  int *name = 0;
  int result = 0;
  int mi = 0;

  ifex_skip_ws();
  // defined(NAME)
  if (ifex_pos + 7 <= ifex_len &&
      __read_byte(ifex_buf, ifex_pos) == 'd' && __read_byte(ifex_buf, ifex_pos+1) == 'e' &&
      __read_byte(ifex_buf, ifex_pos+2) == 'f' && __read_byte(ifex_buf, ifex_pos+3) == 'i' &&
      __read_byte(ifex_buf, ifex_pos+4) == 'n' && __read_byte(ifex_buf, ifex_pos+5) == 'e' &&
      __read_byte(ifex_buf, ifex_pos+6) == 'd' &&
      (ifex_pos + 7 >= ifex_len || ifex_is_alnum(__read_byte(ifex_buf, ifex_pos + 7)) == 0)) {
    ifex_pos += 7;
    ifex_skip_ws();
    if (ifex_ch() == '(') {
      ifex_pos++;
      ifex_skip_ws();
      ns = ifex_pos;
      while (ifex_pos < ifex_len && ifex_is_alnum(ifex_ch())) { ifex_pos++; }
      name = make_str(ifex_buf, ns, ifex_pos - ns);
      ifex_skip_ws();
      if (ifex_ch() == ')') { ifex_pos++; }
      return pp_is_macro_defined(name);
    }
  }
  // Parenthesized expression
  if (ifex_ch() == '(') {
    ifex_pos++;
    result = ifex_parse_or();
    ifex_skip_ws();
    if (ifex_ch() == ')') { ifex_pos++; }
    return result;
  }
  // Number
  if (ifex_ch() >= '0' && ifex_ch() <= '9') {
    return ifex_parse_num();
  }
  // Identifier: look up as macro value, default to 0
  if (ifex_is_alnum(ifex_ch()) && (ifex_ch() < '0' || ifex_ch() > '9')) {
    ns = ifex_pos;
    while (ifex_pos < ifex_len && ifex_is_alnum(ifex_ch())) { ifex_pos++; }
    name = make_str(ifex_buf, ns, ifex_pos - ns);
    mi = 0;
    while (mi < nmacros) {
      if (my_strcmp(macros[mi].name, name) == 0 && macros[mi].value != 0) {
        return my_atoi(macros[mi].value);
      }
      mi++;
    }
    return 0;
  }
  return 0;
}

int ifex_parse_unary() {
  ifex_skip_ws();
  if (ifex_ch() == '!') { ifex_pos++; return ifex_parse_unary() == 0 ? 1 : 0; }
  if (ifex_ch() == '+') { ifex_pos++; return ifex_parse_unary(); }
  if (ifex_ch() == '-') { ifex_pos++; return 0 - ifex_parse_unary(); }
  if (ifex_ch() == '~') { ifex_pos++; return ~ifex_parse_unary(); }
  return ifex_parse_primary();
}

int ifex_parse_mul() {
  int val = ifex_parse_unary();
  int rhs = 0;
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '*') { ifex_pos++; val = val * ifex_parse_unary(); }
    else if (ifex_ch() == '/' && (ifex_pos + 1 >= ifex_len || __read_byte(ifex_buf, ifex_pos + 1) != '/')) {
      ifex_pos++; rhs = ifex_parse_unary(); if (rhs != 0) { val = val / rhs; }
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_add() {
  int val = ifex_parse_mul();
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '+') { ifex_pos++; val = val + ifex_parse_mul(); }
    else if (ifex_ch() == '-') { ifex_pos++; val = val - ifex_parse_mul(); }
    else { return val; }
  }
  return val;
}

int ifex_parse_shift() {
  int val = ifex_parse_add();
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '<' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '<') {
      ifex_pos += 2; val = val << ifex_parse_add();
    }
    else if (ifex_ch() == '>' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '>') {
      ifex_pos += 2; val = val >> ifex_parse_add();
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_rel() {
  int val = ifex_parse_shift();
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '<' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '=') {
      ifex_pos += 2; val = val <= ifex_parse_shift() ? 1 : 0;
    }
    else if (ifex_ch() == '>' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '=') {
      ifex_pos += 2; val = val >= ifex_parse_shift() ? 1 : 0;
    }
    else if (ifex_ch() == '<' && (ifex_pos + 1 >= ifex_len || __read_byte(ifex_buf, ifex_pos + 1) != '<')) {
      ifex_pos++; val = val < ifex_parse_shift() ? 1 : 0;
    }
    else if (ifex_ch() == '>' && (ifex_pos + 1 >= ifex_len || __read_byte(ifex_buf, ifex_pos + 1) != '>')) {
      ifex_pos++; val = val > ifex_parse_shift() ? 1 : 0;
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_eq() {
  int val = ifex_parse_rel();
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '=' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '=') {
      ifex_pos += 2; val = val == ifex_parse_rel() ? 1 : 0;
    }
    else if (ifex_ch() == '!' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '=') {
      ifex_pos += 2; val = val != ifex_parse_rel() ? 1 : 0;
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_bitor() {
  int val = ifex_parse_eq();
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '|' && (ifex_pos + 1 >= ifex_len || __read_byte(ifex_buf, ifex_pos + 1) != '|')) {
      ifex_pos++; val = val | ifex_parse_eq();
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_and() {
  int val = ifex_parse_bitor();
  int rhs = 0;
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '&' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '&') {
      ifex_pos += 2; rhs = ifex_parse_bitor(); val = (val && rhs) ? 1 : 0;
    }
    else { return val; }
  }
  return val;
}

int ifex_parse_or() {
  int val = ifex_parse_and();
  int rhs = 0;
  while (1) {
    ifex_skip_ws();
    if (ifex_ch() == '|' && ifex_pos + 1 < ifex_len && __read_byte(ifex_buf, ifex_pos + 1) == '|') {
      ifex_pos += 2; rhs = ifex_parse_and(); val = (val || rhs) ? 1 : 0;
    }
    else { return val; }
  }
  return val;
}

int pp_eval_if_expr(int *expr, int elen) {
  ifex_buf = expr;
  ifex_pos = 0;
  ifex_len = elen;
  return ifex_parse_or();
}


// ---- Preprocessor pass ----

int *strip_block_comments(int *src, int start, int end) {
  int *tmp = my_malloc(end - start + 1);
  int ri = start;
  int wi = 0;
  while (ri < end) {
    if (ri + 1 < end && __read_byte(src, ri) == '/' && __read_byte(src, ri + 1) == '*') {
      ri = ri + 2;
      int found_end = 0;
      while (ri + 1 < end) {
        if (__read_byte(src, ri) == '*' && __read_byte(src, ri + 1) == '/') { ri = ri + 2; found_end = 1; break; }
        ri++;
      }
      if (found_end == 0) { ri = end; }
    } else {
      __write_byte(tmp, wi, __read_byte(src, ri));
      wi++; ri++;
    }
  }
  while (wi > 0 && (__read_byte(tmp, wi - 1) == ' ' || __read_byte(tmp, wi - 1) == '\t')) { wi--; }
  __write_byte(tmp, wi, 0);
  return tmp;
}

// Preprocess source buffer, writing to out buffer at offset co.
// Returns new co (output offset).
int pp_preprocess(int *src, int srclen, int *filepath, int *out, int co, int depth) {
  if (depth > 32) { my_fatal("Include depth exceeded (max 32)"); }
  int *dir = pp_get_dir(filepath);
  int ci = 0;
  int si = 0;
  int nstart = 0;
  int nend = 0;
  int vstart = 0;
  int vend = 0;
  int cond = 0;
  int parent_inc = 0;
  int *name = 0;
  int estart = 0;
  int eend = 0;
  int *expr = 0;
  int pstart = 0;
  int *inc_file = 0;
  int *full_path = 0;
  int inc_len = 0;
  int *inc_src = 0;

  while (ci < srclen) {
    // Skip leading whitespace to check for #
    si = ci;
    while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) {
      si++;
    }
    if (si < srclen && __read_byte(src, si) == '#') {
      si++;
      // skip whitespace after #
      while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) {
        si++;
      }

      // Check for "ifdef"
      if (si + 5 <= srclen &&
          __read_byte(src, si) == 'i' && __read_byte(src, si+1) == 'f' &&
          __read_byte(src, si+2) == 'd' && __read_byte(src, si+3) == 'e' &&
          __read_byte(src, si+4) == 'f' &&
          (__read_byte(src, si+5) == ' ' || __read_byte(src, si+5) == '\t')) {
        si += 5;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        nstart = si;
        while (si < srclen && __read_byte(src, si) != '\n' && __read_byte(src, si) != ' ' && __read_byte(src, si) != '\t') { si++; }
        name = make_str(src, nstart, si - nstart);
        if (if_depth >= 32) { my_fatal("#ifdef nesting too deep"); }
        cond = pp_is_including() && pp_is_macro_defined(name);
        if_stack_including[if_depth] = cond;
        if_stack_seen_else[if_depth] = 0;
        if_stack_satisfied[if_depth] = cond;
        if_depth++;
        // skip rest of line
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
        // Use continue to restart while loop
        // (selfhost doesn't have continue so use goto-like pattern)
      }

      // Check for "ifndef"
      else if (si + 6 <= srclen &&
          __read_byte(src, si) == 'i' && __read_byte(src, si+1) == 'f' &&
          __read_byte(src, si+2) == 'n' && __read_byte(src, si+3) == 'd' &&
          __read_byte(src, si+4) == 'e' && __read_byte(src, si+5) == 'f' &&
          (__read_byte(src, si+6) == ' ' || __read_byte(src, si+6) == '\t')) {
        si += 6;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        nstart = si;
        while (si < srclen && __read_byte(src, si) != '\n' && __read_byte(src, si) != ' ' && __read_byte(src, si) != '\t') { si++; }
        name = make_str(src, nstart, si - nstart);
        if (if_depth >= 32) { my_fatal("#ifndef nesting too deep"); }
        cond = pp_is_including() && (1 - pp_is_macro_defined(name));
        if_stack_including[if_depth] = cond;
        if_stack_seen_else[if_depth] = 0;
        if_stack_satisfied[if_depth] = cond;
        if_depth++;
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "if " (but not ifdef/ifndef which we already handled)
      else if (si + 2 <= srclen &&
          __read_byte(src, si) == 'i' && __read_byte(src, si+1) == 'f' &&
          (__read_byte(src, si+2) == ' ' || __read_byte(src, si+2) == '\t' || __read_byte(src, si+2) == '(')) {
        si += 2;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        // Read expression until end of line
        estart = si;
        while (si < srclen && __read_byte(src, si) != '\n') { si++; }
        eend = si;
        // Trim trailing whitespace
        while (eend > estart && (__read_byte(src, eend - 1) == ' ' || __read_byte(src, eend - 1) == '\t')) { eend--; }
        expr = make_str(src, estart, eend - estart);
        if (if_depth >= 32) { my_fatal("#if nesting too deep"); }
        cond = pp_is_including() && pp_eval_if_expr(expr, eend - estart);
        if_stack_including[if_depth] = cond;
        if_stack_seen_else[if_depth] = 0;
        if_stack_satisfied[if_depth] = cond;
        if_depth++;
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "elif"
      else if (si + 4 <= srclen &&
          __read_byte(src, si) == 'e' && __read_byte(src, si+1) == 'l' &&
          __read_byte(src, si+2) == 'i' && __read_byte(src, si+3) == 'f' &&
          (__read_byte(src, si+4) == ' ' || __read_byte(src, si+4) == '\t' || __read_byte(src, si+4) == '(')) {
        si += 4;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        estart = si;
        while (si < srclen && __read_byte(src, si) != '\n') { si++; }
        eend = si;
        while (eend > estart && (__read_byte(src, eend - 1) == ' ' || __read_byte(src, eend - 1) == '\t')) { eend--; }
        expr = make_str(src, estart, eend - estart);
        if (if_depth <= 0) { my_fatal("#elif without #if"); }
        if (if_stack_seen_else[if_depth - 1]) { my_fatal("#elif after #else"); }
        parent_inc = pp_parent_including();
        if (if_stack_satisfied[if_depth - 1]) {
          if_stack_including[if_depth - 1] = 0;
        } else if (parent_inc && pp_eval_if_expr(expr, eend - estart)) {
          if_stack_including[if_depth - 1] = 1;
          if_stack_satisfied[if_depth - 1] = 1;
        } else {
          if_stack_including[if_depth - 1] = 0;
        }
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "else"
      else if (si + 4 <= srclen &&
          __read_byte(src, si) == 'e' && __read_byte(src, si+1) == 'l' &&
          __read_byte(src, si+2) == 's' && __read_byte(src, si+3) == 'e' &&
          (__read_byte(src, si+4) == '\n' || si + 4 == srclen || __read_byte(src, si+4) == ' ' || __read_byte(src, si+4) == '\t')) {
        if (if_depth <= 0) { my_fatal("#else without #if"); }
        if (if_stack_seen_else[if_depth - 1]) { my_fatal("duplicate #else"); }
        if_stack_seen_else[if_depth - 1] = 1;
        parent_inc = pp_parent_including();
        if (if_stack_satisfied[if_depth - 1]) {
          if_stack_including[if_depth - 1] = 0;
        } else {
          if_stack_including[if_depth - 1] = parent_inc;
          if_stack_satisfied[if_depth - 1] = 1;
        }
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "endif"
      else if (si + 5 <= srclen &&
          __read_byte(src, si) == 'e' && __read_byte(src, si+1) == 'n' &&
          __read_byte(src, si+2) == 'd' && __read_byte(src, si+3) == 'i' &&
          __read_byte(src, si+4) == 'f' &&
          (si + 5 == srclen || __read_byte(src, si+5) == '\n' || __read_byte(src, si+5) == ' ' || __read_byte(src, si+5) == '\t')) {
        if (if_depth <= 0) { my_fatal("#endif without #if"); }
        if_depth--;
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Not including — skip remaining directive types
      else if (pp_is_including() == 0) {
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "include"
      else if (pp_is_including() && si + 7 <= srclen &&
          __read_byte(src, si) == 'i' && __read_byte(src, si+1) == 'n' &&
          __read_byte(src, si+2) == 'c' && __read_byte(src, si+3) == 'l' &&
          __read_byte(src, si+4) == 'u' && __read_byte(src, si+5) == 'd' &&
          __read_byte(src, si+6) == 'e' &&
          (__read_byte(src, si+7) == ' ' || __read_byte(src, si+7) == '\t' || __read_byte(src, si+7) == '"')) {
        si += 7;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        if (si < srclen && __read_byte(src, si) == '"') {
          si++;
          pstart = si;
          while (si < srclen && __read_byte(src, si) != '"' && __read_byte(src, si) != '\n') { si++; }
          inc_file = make_str(src, pstart, si - pstart);
          full_path = pp_concat_paths(dir, inc_file);
          {
            int *tryf = fopen(full_path, "r");
            if (tryf != 0) {
              fclose(tryf);
            } else {
              // Try include dirs
              int idi = 0;
              while (idi < ninclude_dirs) {
                int *tp = pp_concat_paths(include_dirs[idi], inc_file);
                tryf = fopen(tp, "r");
                if (tryf != 0) { fclose(tryf); full_path = tp; idi = ninclude_dirs; }
                idi++;
              }
            }
          }
          inc_len = 0;
          inc_src = pp_read_file(full_path, &inc_len);
          co = pp_preprocess(inc_src, inc_len, full_path, out, co, depth + 1);
        } else if (si < srclen && __read_byte(src, si) == '<') {
          si++;
          pstart = si;
          while (si < srclen && __read_byte(src, si) != '>' && __read_byte(src, si) != '\n') { si++; }
          inc_file = make_str(src, pstart, si - pstart);
          {
            int idi = 0;
            int inc_found = 0;
            while (idi < ninclude_dirs && inc_found == 0) {
              full_path = pp_concat_paths(include_dirs[idi], inc_file);
              int *tryf = fopen(full_path, "r");
              if (tryf != 0) {
                fclose(tryf);
                inc_len = 0;
                inc_src = pp_read_file(full_path, &inc_len);
                co = pp_preprocess(inc_src, inc_len, full_path, out, co, depth + 1);
                inc_found = 1;
              }
              idi++;
            }
          }
        }
        // Skip rest of line
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "define"
      else if (pp_is_including() && si + 6 <= srclen &&
          __read_byte(src, si) == 'd' && __read_byte(src, si + 1) == 'e' &&
          __read_byte(src, si + 2) == 'f' && __read_byte(src, si + 3) == 'i' &&
          __read_byte(src, si + 4) == 'n' && __read_byte(src, si + 5) == 'e' &&
          (__read_byte(src, si + 6) == ' ' || __read_byte(src, si + 6) == '\t')) {
        si += 6;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) {
          si++;
        }
        // Read macro name
        nstart = si;
        while (si < srclen && __read_byte(src, si) != ' ' && __read_byte(src, si) != '\t' &&
               __read_byte(src, si) != '\n' && __read_byte(src, si) != '(') {
          si++;
        }
        nend = si;
        // Function-like macros: parse params and body
        if (si < srclen && __read_byte(src, si) == '(') {
          si++; // skip '('
          int **fparams = my_malloc(16 * 8);
          int fnp = 0;
          int fvar = 0; // variadic flag
          while (si < srclen && __read_byte(src, si) != ')' && __read_byte(src, si) != '\n') {
            while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
            if (__read_byte(src, si) == ')') { break; }
            // Check for ...
            if (__read_byte(src, si) == '.' && si + 2 < srclen && __read_byte(src, si + 1) == '.' && __read_byte(src, si + 2) == '.') {
              fvar = 1;
              si = si + 3;
              while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
              break;
            }
            int ps = si;
            while (si < srclen && __read_byte(src, si) != ',' && __read_byte(src, si) != ')' &&
                   __read_byte(src, si) != ' ' && __read_byte(src, si) != '\t' && __read_byte(src, si) != '\n') {
              si++;
            }
            if (si > ps) {
              fparams[fnp] = make_str(src, ps, si - ps);
              fnp++;
            }
            while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
            if (__read_byte(src, si) == ',') { si++; }
          }
          if (si < srclen && __read_byte(src, si) == ')') { si++; }
          // Read body = rest of line, trimmed
          while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
          int bstart = si;
          while (si < srclen && __read_byte(src, si) != '\n') { si++; }
          int bend = si;
          while (bend > bstart && (__read_byte(src, bend - 1) == ' ' || __read_byte(src, bend - 1) == '\t')) { bend--; }
          { int *mb_tmp = strip_block_comments(src, bstart, bend);
            macros[nmacros].name = make_str(src, nstart, nend - nstart);
            macros[nmacros].value = 0;
            macros[nmacros].nparams = fnp;
            macros[nmacros].params = fparams;
            macros[nmacros].body = mb_tmp;
          }
          macros[nmacros].is_variadic = fvar;
          macros[nmacros].def_pos = co;
          nmacros++;
        } else {
          // Object-like macro
          // skip whitespace
          while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
          // Read value until end of line
          vstart = si;
          while (si < srclen && __read_byte(src, si) != '\n') {
            si++;
          }
          // Trim trailing whitespace
          vend = si;
          while (vend > vstart && (__read_byte(src, vend - 1) == ' ' || __read_byte(src, vend - 1) == '\t')) {
            vend--;
          }
          { int *mv_tmp = strip_block_comments(src, vstart, vend);
            macros[nmacros].name = make_str(src, nstart, nend - nstart);
            macros[nmacros].value = mv_tmp;
          }
          macros[nmacros].nparams = 0 - 1;
          macros[nmacros].params = 0;
          macros[nmacros].body = 0;
          macros[nmacros].def_pos = co;
          nmacros++;
        }
        // Skip entire line
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "undef"
      else if (pp_is_including() && si + 5 <= srclen &&
          __read_byte(src, si) == 'u' && __read_byte(src, si+1) == 'n' &&
          __read_byte(src, si+2) == 'd' && __read_byte(src, si+3) == 'e' &&
          __read_byte(src, si+4) == 'f' &&
          (__read_byte(src, si+5) == ' ' || __read_byte(src, si+5) == '\t')) {
        si += 5;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        nstart = si;
        while (si < srclen && __read_byte(src, si) != '\n' && __read_byte(src, si) != ' ' && __read_byte(src, si) != '\t') { si++; }
        name = make_str(src, nstart, si - nstart);
        // Remove from macro table
        int ui = 0;
        while (ui < nmacros) {
          if (my_strcmp(macros[ui].name, name) == 0) {
            int uj = ui;
            while (uj < nmacros - 1) {
              macros[uj].name = macros[uj + 1].name;
              macros[uj].value = macros[uj + 1].value;
              macros[uj].nparams = macros[uj + 1].nparams;
              macros[uj].params = macros[uj + 1].params;
              macros[uj].body = macros[uj + 1].body;
              macros[uj].is_variadic = macros[uj + 1].is_variadic;
              macros[uj].def_pos = macros[uj + 1].def_pos;
              uj++;
            }
            nmacros--;
            ui = nmacros; // break
          }
          ui++;
        }
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "error"
      else if (si + 5 <= srclen &&
          __read_byte(src, si) == 'e' && __read_byte(src, si+1) == 'r' &&
          __read_byte(src, si+2) == 'r' && __read_byte(src, si+3) == 'o' &&
          __read_byte(src, si+4) == 'r' &&
          (__read_byte(src, si+5) == ' ' || __read_byte(src, si+5) == '\t' || __read_byte(src, si+5) == '\n')) {
        si += 5;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        int msg_start = si;
        while (si < srclen && __read_byte(src, si) != '\n') { si++; }
        int *msg = make_str(src, msg_start, si - msg_start);
        printf("cc: #error: %s\n", msg);
        exit(1);
      }

      // Check for "warning"
      else if (pp_is_including() && si + 7 <= srclen &&
          __read_byte(src, si) == 'w' && __read_byte(src, si+1) == 'a' &&
          __read_byte(src, si+2) == 'r' && __read_byte(src, si+3) == 'n' &&
          __read_byte(src, si+4) == 'i' && __read_byte(src, si+5) == 'n' &&
          __read_byte(src, si+6) == 'g' &&
          (__read_byte(src, si+7) == ' ' || __read_byte(src, si+7) == '\t' || __read_byte(src, si+7) == '\n')) {
        si += 7;
        while (si < srclen && (__read_byte(src, si) == ' ' || __read_byte(src, si) == '\t')) { si++; }
        int wm_start = si;
        while (si < srclen && __read_byte(src, si) != '\n') { si++; }
        int *wm_msg = make_str(src, wm_start, si - wm_start);
        printf("cc: #warning: %s\n", wm_msg);
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "line" (ignore directive, just skip)
      else if (si + 4 <= srclen &&
          __read_byte(src, si) == 'l' && __read_byte(src, si+1) == 'i' &&
          __read_byte(src, si+2) == 'n' && __read_byte(src, si+3) == 'e' &&
          (__read_byte(src, si+4) == ' ' || __read_byte(src, si+4) == '\t')) {
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      // Check for "pragma" (ignore directive, just skip)
      else if (si + 6 <= srclen &&
          __read_byte(src, si) == 'p' && __read_byte(src, si+1) == 'r' &&
          __read_byte(src, si+2) == 'a' && __read_byte(src, si+3) == 'g' &&
          __read_byte(src, si+4) == 'm' && __read_byte(src, si+5) == 'a' &&
          (__read_byte(src, si+6) == ' ' || __read_byte(src, si+6) == '\t' || __read_byte(src, si+6) == '\n')) {
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

      else {
        // Other preprocessor directive — skip
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
        if (ci < srclen) { __write_byte(out, co, '\n'); co++; ci++; }
      }

    } else {
      // Non-directive line
      if (pp_is_including()) {
        // Copy line
        while (ci < srclen && __read_byte(src, ci) != '\n') {
          __write_byte(out, co, __read_byte(src, ci));
          co++;
          ci++;
        }
      } else {
        // Skip line
        while (ci < srclen && __read_byte(src, ci) != '\n') { ci++; }
      }
      if (ci < srclen) {
        __write_byte(out, co, '\n');
        co++;
        ci++;
      }
    }
  }
  return co;
}


// ---- Lexer ----

int is_space(int c) {
  if (c == ' ') { return 1; }
  if (c == '\t') { return 1; }
  if (c == '\n') { return 1; }
  if (c == '\r') { return 1; }
  return 0;
}

int is_digit(int c) {
  return c >= '0' && c <= '9';
}

int is_alpha(int c) {
  if (c >= 'a' && c <= 'z') { return 1; }
  if (c >= 'A' && c <= 'Z') { return 1; }
  if (c == '_') { return 1; }
  if (c == '$') { return 1; }
  return 0;
}

int is_alnum(int c) {
  return is_alpha(c) || is_digit(c);
}

int is_float_literal(int *s) {
  int i = 0;
  int c = __read_byte(s, i);
  // Hex float: 0x1.fp2 — has 'p' or 'P' exponent
  if (c == '0' && (__read_byte(s, 1) == 'x' || __read_byte(s, 1) == 'X')) {
    int hi = 2;
    while (__read_byte(s, hi) != 0) { if (__read_byte(s, hi) == 'p' || __read_byte(s, hi) == 'P') { return 1; } hi++; }
    return 0;
  }
  while (c != 0) {
    if (c == '.' || c == 'e' || c == 'E') { return 1; }
    i++;
    c = __read_byte(s, i);
  }
  // Check for 'f' or 'F' suffix at end
  if (i > 0) {
    int last = __read_byte(s, i - 1);
    if (last == 'f' || last == 'F') { return 1; }
  }
  return 0;
}

// Convert float literal string to IEEE 754 double bit pattern using integer-only math
int *str_to_double_bits(int *s) {
  int sign = 0;
  int i = 0;
  int c = __read_byte(s, i);

  // Sign
  if (c == '-') { sign = 1; i++; c = __read_byte(s, i); }
  else if (c == '+') { i++; c = __read_byte(s, i); }

  // Hex float: 0xH.Hp±D  -> value = H.H * 2^(±D)
  if (c == '0' && (__read_byte(s, i + 1) == 'x' || __read_byte(s, i + 1) == 'X')) {
    i += 2; c = __read_byte(s, i);
    // Parse hex integer part
    long hm = 0;
    int hbits = 0;
    while (is_hex_digit(c)) {
      int hd = 0;
      if (c >= '0' && c <= '9') { hd = c - '0'; }
      else if (c >= 'a' && c <= 'f') { hd = c - 'a' + 10; }
      else if (c >= 'A' && c <= 'F') { hd = c - 'A' + 10; }
      hm = hm * 16 + hd;
      hbits += 4;
      i++; c = __read_byte(s, i);
    }
    int hfrac_bits = 0;
    if (c == '.') {
      i++; c = __read_byte(s, i);
      while (is_hex_digit(c)) {
        int hd = 0;
        if (c >= '0' && c <= '9') { hd = c - '0'; }
        else if (c >= 'a' && c <= 'f') { hd = c - 'a' + 10; }
        else if (c >= 'A' && c <= 'F') { hd = c - 'A' + 10; }
        hm = hm * 16 + hd;
        hfrac_bits += 4;
        hbits += 4;
        i++; c = __read_byte(s, i);
      }
    }
    int hexp = 0;
    int hexp_sign = 1;
    if (c == 'p' || c == 'P') {
      i++; c = __read_byte(s, i);
      if (c == '-') { hexp_sign = 0 - 1; i++; c = __read_byte(s, i); }
      else if (c == '+') { i++; c = __read_byte(s, i); }
      while (c >= '0' && c <= '9') { hexp = hexp * 10 + (c - '0'); i++; c = __read_byte(s, i); }
      hexp = hexp * hexp_sign;
    }
    if (hm == 0) { return 0; }
    // bin_exp: mantissa needs shifting by -hfrac_bits, then apply hexp
    int bin_exp = hexp - hfrac_bits;
    long m = hm;
    long one_shl_52 = (long)1 << 52;
    long one_shl_53 = (long)1 << 53;
    // Normalize to 53 bits
    long tmp = m; int nbits = 0;
    while (tmp > 0) { tmp = tmp / 2; nbits++; }
    if (nbits > 53) {
      int shift = nbits - 53;
      long half = 1; int si = 0;
      while (si < shift - 1) { half = half * 2; si++; }
      m = m / (half * 2);
      bin_exp = bin_exp + shift;
    } else if (nbits < 53) {
      int shift = 53 - nbits;
      int si = 0;
      while (si < shift) { m = m * 2; si++; }
      bin_exp = bin_exp - shift;
    }
    long frac = m - one_shl_52;
    int biased = bin_exp + 52 + 1023;
    if (biased <= 0) { return 0; }
    if (biased >= 2047) { biased = 2047; frac = 0; }
    long result = frac + ((long)biased << 52);
    if (sign) { result = result + ((long)1 << 63); }
    return result;
  }

  // Parse integer part (long to handle large mantissas under clang's 32-bit int)
  long intpart = 0;
  while (c >= '0' && c <= '9') {
    intpart = intpart * 10 + (c - '0');
    i++; c = __read_byte(s, i);
  }

  // Parse fractional part
  long fracpart = 0;
  int frac_digits = 0;
  if (c == '.') {
    i++; c = __read_byte(s, i);
    while (c >= '0' && c <= '9') {
      fracpart = fracpart * 10 + (c - '0');
      frac_digits++;
      i++; c = __read_byte(s, i);
    }
  }

  // Parse exponent
  int exp_val = 0;
  int exp_sign = 1;
  if (c == 'e' || c == 'E') {
    i++; c = __read_byte(s, i);
    if (c == '-') { exp_sign = 0 - 1; i++; c = __read_byte(s, i); }
    else if (c == '+') { i++; c = __read_byte(s, i); }
    while (c >= '0' && c <= '9') {
      exp_val = exp_val * 10 + (c - '0');
      i++; c = __read_byte(s, i);
    }
    exp_val = exp_val * exp_sign;
  }

  // Skip f/F/l/L suffix
  // Now: value = (intpart + fracpart/10^frac_digits) * 10^exp_val
  // Build mantissa: intpart * 10^frac_digits + fracpart
  long mantissa = intpart;
  int d = 0;
  while (d < frac_digits) { mantissa = mantissa * 10; d++; }
  mantissa = mantissa + fracpart;
  int decimal_exp = exp_val - frac_digits;

  if (mantissa == 0) { return 0; } // +0.0

  // Use long to avoid 32-bit int UB under clang (self-hosting: long == int == 8 bytes)
  long one_shl_52 = (long)1 << 52;
  long one_shl_53 = (long)1 << 53;
  long one_shl_62 = (long)1 << 62;
  long overflow_limit = one_shl_62 / 5;
  int bin_exp = 0;
  long m = mantissa;

  // Apply decimal exponent: multiply/divide by powers of 10
  if (decimal_exp > 0) {
    while (decimal_exp > 0) {
      if (m > overflow_limit) { m = m / 2; bin_exp++; }
      m = m * 10;
      decimal_exp--;
    }
  } else if (decimal_exp < 0) {
    // Shift m left to fill ~62 bits, then divide by 10^|exp|
    while (m < one_shl_62) { m = m * 2; bin_exp--; }
    while (decimal_exp < 0) {
      m = m / 10;
      decimal_exp++;
      while (m < one_shl_62 && decimal_exp < 0) { m = m * 2; bin_exp--; }
    }
    while (decimal_exp > 0) {
      if (m > overflow_limit) { m = m / 2; bin_exp++; }
      m = m * 10;
      decimal_exp--;
    }
  }

  // Normalize: shift so bit 52 is the highest set bit
  long tmp = m;
  int nbits = 0;
  while (tmp > 0) { tmp = tmp / 2; nbits++; }

  // We want nbits == 53 (bit 52 is MSB)
  if (nbits > 53) {
    int shift = nbits - 53;
    long half = 1;
    int si = 0;
    while (si < shift - 1) { half = half * 2; si++; }
    long remainder = m & (half * 2 - 1);
    m = m / (half * 2);
    if (remainder > half) { m = m + 1; }
    else if (remainder == half && (m & 1)) { m = m + 1; }
    bin_exp = bin_exp + shift;
    if (m >= one_shl_53) { m = m / 2; bin_exp++; }
  } else if (nbits < 53) {
    int shift = 53 - nbits;
    int si = 0;
    while (si < shift) { m = m * 2; si++; }
    bin_exp = bin_exp - shift;
  }

  // Remove implicit leading 1 (bit 52)
  long frac = m - one_shl_52;

  // Biased exponent: bin_exp + 52 + 1023
  int biased = bin_exp + 52 + 1023;
  if (biased <= 0) { return 0; } // underflow to zero
  if (biased >= 2047) { biased = 2047; frac = 0; } // overflow to inf

  // Pack: sign(1) | exponent(11) | fraction(52)
  long result = frac;
  result = result + ((long)biased << 52);
  if (sign) {
    result = result + ((long)1 << 63);
  }
  return result;
}

int is_keyword(int *s) {
  if (my_strcmp(s, "int") == 0) { return 1; }
  if (my_strcmp(s, "return") == 0) { return 1; }
  if (my_strcmp(s, "if") == 0) { return 1; }
  if (my_strcmp(s, "else") == 0) { return 1; }
  if (my_strcmp(s, "while") == 0) { return 1; }
  if (my_strcmp(s, "for") == 0) { return 1; }
  if (my_strcmp(s, "break") == 0) { return 1; }
  if (my_strcmp(s, "continue") == 0) { return 1; }
  if (my_strcmp(s, "struct") == 0) { return 1; }
  if (my_strcmp(s, "do") == 0) { return 1; }
  if (my_strcmp(s, "goto") == 0) { return 1; }
  if (my_strcmp(s, "sizeof") == 0) { return 1; }
  if (my_strcmp(s, "char") == 0) { return 1; }
  if (my_strcmp(s, "void") == 0) { return 1; }
  if (my_strcmp(s, "const") == 0) { return 1; }
  if (my_strcmp(s, "volatile") == 0) { return 1; }
  if (my_strcmp(s, "register") == 0) { return 1; }
  if (my_strcmp(s, "static") == 0) { return 1; }
  if (my_strcmp(s, "extern") == 0) { return 1; }
  if (my_strcmp(s, "unsigned") == 0) { return 1; }
  if (my_strcmp(s, "signed") == 0) { return 1; }
  if (my_strcmp(s, "__signed__") == 0) { return 1; }
  if (my_strcmp(s, "long") == 0) { return 1; }
  if (my_strcmp(s, "short") == 0) { return 1; }
  if (my_strcmp(s, "enum") == 0) { return 1; }
  if (my_strcmp(s, "typedef") == 0) { return 1; }
  if (my_strcmp(s, "switch") == 0) { return 1; }
  if (my_strcmp(s, "case") == 0) { return 1; }
  if (my_strcmp(s, "default") == 0) { return 1; }
  if (my_strcmp(s, "inline") == 0) { return 1; }
  if (my_strcmp(s, "_Bool") == 0) { return 1; }
  if (my_strcmp(s, "union") == 0) { return 1; }
  if (my_strcmp(s, "double") == 0) { return 1; }
  if (my_strcmp(s, "float") == 0) { return 1; }
  if (my_strcmp(s, "restrict") == 0) { return 1; }
  if (my_strcmp(s, "__attribute__") == 0) { return 1; }
  if (my_strcmp(s, "__attribute") == 0) { return 1; }
  if (my_strcmp(s, "__extension__") == 0) { return 1; }
  if (my_strcmp(s, "__inline__") == 0) { return 1; }
  if (my_strcmp(s, "__inline") == 0) { return 1; }
  if (my_strcmp(s, "__restrict") == 0) { return 1; }
  if (my_strcmp(s, "__restrict__") == 0) { return 1; }
  if (my_strcmp(s, "__volatile") == 0) { return 1; }
  if (my_strcmp(s, "__volatile__") == 0) { return 1; }
  if (my_strcmp(s, "__const") == 0) { return 1; }
  if (my_strcmp(s, "__const__") == 0) { return 1; }
  if (my_strcmp(s, "__typeof__") == 0) { return 1; }
  if (my_strcmp(s, "typeof") == 0) { return 1; }
  if (my_strcmp(s, "__typeof") == 0) { return 1; }
  if (my_strcmp(s, "_Static_assert") == 0) { return 1; }
  if (my_strcmp(s, "_Noreturn") == 0) { return 1; }
  if (my_strcmp(s, "_Alignof") == 0) { return 1; }
  if (my_strcmp(s, "_Alignas") == 0) { return 1; }
  if (my_strcmp(s, "__alignof__") == 0) { return 1; }
  if (my_strcmp(s, "__alignof") == 0) { return 1; }
  return 0;
}

void merge_string_literals() {
  int ri = 0;
  int wi = 0;
  while (ri < ntokens) {
    if (tok[ri].kind == TK_STR && ri + 1 < ntokens && tok[ri + 1].kind == TK_STR) {
      int *merged = my_strdup(tok[ri].val);
      while (ri + 1 < ntokens && tok[ri + 1].kind == TK_STR) {
        ri++;
        merged = build_str2(merged, tok[ri].val);
      }
      tok[wi].kind = TK_STR;
      tok[wi].val = merged;
      tok[wi].pos = tok[ri].pos;
    } else if (wi != ri) {
      tok[wi].kind = tok[ri].kind;
      tok[wi].val = tok[ri].val;
      tok[wi].pos = tok[ri].pos;
    }
    wi++;
    ri++;
  }
  ntokens = wi;
}

int lex(int *src, int srclen) {
  // Strip comments into a buffer (preserving string/char literal contents)
  int *buf = my_malloc(srclen + 1);
  int j = 0;
  int i = 0;
  while (i < srclen) {
    if (__read_byte(src, i) == '"') {
      __write_byte(buf, j, __read_byte(src, i)); i++; j++;
      while (i < srclen && __read_byte(src, i) != '"') {
        if (__read_byte(src, i) == '\\' && i + 1 < srclen) {
          __write_byte(buf, j, __read_byte(src, i)); i++; j++;
        }
        __write_byte(buf, j, __read_byte(src, i)); i++; j++;
      }
      if (i < srclen) { __write_byte(buf, j, __read_byte(src, i)); i++; j++; }
    } else if (__read_byte(src, i) == '\'' && i + 1 < srclen) {
      __write_byte(buf, j, __read_byte(src, i)); i++; j++;
      while (i < srclen && __read_byte(src, i) != '\'') {
        if (__read_byte(src, i) == '\\' && i + 1 < srclen) {
          __write_byte(buf, j, __read_byte(src, i)); i++; j++;
        }
        __write_byte(buf, j, __read_byte(src, i)); i++; j++;
      }
      if (i < srclen) { __write_byte(buf, j, __read_byte(src, i)); i++; j++; }
    } else if (__read_byte(src, i) == '/' && i + 1 < srclen && __read_byte(src, i + 1) == '/') {
      i += 2;
      while (i < srclen && __read_byte(src, i) != '\n') {
        i++;
      }
    } else if (__read_byte(src, i) == '/' && i + 1 < srclen && __read_byte(src, i + 1) == '*') {
      i += 2;
      while (i + 1 < srclen) {
        if (__read_byte(src, i) == '*' && __read_byte(src, i + 1) == '/') {
          break;
        }
        i++;
      }
      if (i + 1 < srclen) {
        i += 2;
      }
    } else {
      __write_byte(buf, j, __read_byte(src, i));
      j++;
      i++;
    }
  }
  __write_byte(buf, j, 0);
  int len = j;

  ntokens = 0;
  i = 0;
  int start = 0;
  int ch = 0;
  int ec = 0;
  int c1 = 0;
  int *id_val = 0;
  while (i < len) {
    int c = __read_byte(buf, i);

    if (is_space(c)) {
      i++;
      continue;
    }

    // Number (decimal or hex)
    if (is_digit(c)) {
      start = i;
      if (c == '0' && i + 1 < len && (__read_byte(buf, i + 1) == 'x' || __read_byte(buf, i + 1) == 'X')) {
        i += 2;
        while (i < len && is_hex_digit(__read_byte(buf, i))) {
          i++;
        }
        // Hex float: 0x1.fp2 — dot followed by hex digits, then p/P exponent
        if (i < len && __read_byte(buf, i) == '.') {
          i++;
          while (i < len && is_hex_digit(__read_byte(buf, i))) { i++; }
        }
        if (i < len && (__read_byte(buf, i) == 'p' || __read_byte(buf, i) == 'P')) {
          i++;
          if (i < len && (__read_byte(buf, i) == '+' || __read_byte(buf, i) == '-')) { i++; }
          while (i < len && is_digit(__read_byte(buf, i))) { i++; }
        }
      } else if (c == '0' && i + 1 < len && (__read_byte(buf, i + 1) == 'b' || __read_byte(buf, i + 1) == 'B')) {
        i += 2;
        while (i < len && (__read_byte(buf, i) == '0' || __read_byte(buf, i) == '1')) {
          i++;
        }
      } else {
        while (i < len && is_digit(__read_byte(buf, i))) {
          i++;
        }
      }
      // Handle decimal point for floats: 1.0, 0.5, 0., etc.
      if (i < len && __read_byte(buf, i) == '.') {
        int dnext = (i + 1 < len) ? __read_byte(buf, i + 1) : 0;
        if (is_digit(dnext) || dnext == 'e' || dnext == 'E' || dnext == ',' || dnext == ')' || dnext == '}' || dnext == ' ' || dnext == ';' || dnext == '\n' || dnext == '\t' || dnext == 0) {
          i++;
          while (i < len && is_digit(__read_byte(buf, i))) { i++; }
        }
      }
      // Handle exponent: 1e300, 1E-10, 1.5e+3
      if (i < len && (__read_byte(buf, i) == 'e' || __read_byte(buf, i) == 'E')) {
        i++;
        if (i < len && (__read_byte(buf, i) == '+' || __read_byte(buf, i) == '-')) { i++; }
        while (i < len && is_digit(__read_byte(buf, i))) { i++; }
      }
      tok[ntokens].kind = TK_NUM;
      tok[ntokens].val = make_str(buf, start, i - start);
      // Skip integer/float suffixes: U, L, UL, ULL, LL, F, f, etc.
      while (i < len && (__read_byte(buf, i) == 'U' || __read_byte(buf, i) == 'u' || __read_byte(buf, i) == 'L' || __read_byte(buf, i) == 'l' || __read_byte(buf, i) == 'F' || __read_byte(buf, i) == 'f')) { i++; }
      tok[ntokens].pos = start;
      ntokens++;
      continue;
    }

    // Identifier / keyword
    if (is_alpha(c)) {
      start = i;
      while (i < len && is_alnum(__read_byte(buf, i))) {
        i++;
      }
      id_val = make_str(buf, start, i - start);
      // Wide char/string prefix: L'x' or L"str" — skip the L prefix
      if (my_strcmp(id_val, "L") == 0 && i < len && (__read_byte(buf, i) == 39 || __read_byte(buf, i) == '"')) {
        // Fall through to char/string literal parsing below
      } else {
        if (is_keyword(id_val)) {
          tok[ntokens].kind = TK_KW;
        } else {
          tok[ntokens].kind = TK_ID;
        }
        tok[ntokens].val = id_val;
        tok[ntokens].pos = start;
        ntokens++;
        continue;
      }
    }

    // Character literal
    c = __read_byte(buf, i);
    if (c == 39) {
      start = i;
      i++;
      ch = 0;
      if (__read_byte(buf, i) == '\\') {
        i++;
        ec = __read_byte(buf, i);
        switch (ec) {
        case 'n': ch = 10; break;
        case 't': ch = 9; break;
        case 'r': ch = 13; break;
        case 'a': ch = 7; break;
        case 'b': ch = 8; break;
        case 'f': ch = 12; break;
        case 'v': ch = 11; break;
        case '\\': ch = 92; break;
        case 39: ch = 39; break;
        case '"': ch = 34; break;
        case '?': ch = 63; break;
        case '0':
          // \0 or \0xx octal escape
          ch = 0;
          i++;
          if (i < len && __read_byte(buf, i) >= '0' && __read_byte(buf, i) <= '7') {
            ch = ch * 8 + (__read_byte(buf, i) - '0');
            i++;
            if (i < len && __read_byte(buf, i) >= '0' && __read_byte(buf, i) <= '7') {
              ch = ch * 8 + (__read_byte(buf, i) - '0');
              i++;
            }
          }
          i--;
          break;
        case 'x':
          // hex escape \xHH
          i++;
          ch = 0;
          while (i < len) {
            ec = __read_byte(buf, i);
            if (ec >= '0' && ec <= '9') { ch = ch * 16 + (ec - '0'); }
            else if (ec >= 'a' && ec <= 'f') { ch = ch * 16 + (ec - 'a' + 10); }
            else if (ec >= 'A' && ec <= 'F') { ch = ch * 16 + (ec - 'A' + 10); }
            else { break; }
            i++;
          }
          i--;
          break;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7':
          // octal escape \ooo
          ch = ec - '0';
          i++;
          if (i < len && __read_byte(buf, i) >= '0' && __read_byte(buf, i) <= '7') {
            ch = ch * 8 + (__read_byte(buf, i) - '0');
            i++;
            if (i < len && __read_byte(buf, i) >= '0' && __read_byte(buf, i) <= '7') {
              ch = ch * 8 + (__read_byte(buf, i) - '0');
              i++;
            }
          }
          i--;
          break;
        default: my_fatal("bad char escape"); break;
        }
        i++;
      } else {
        ch = __read_byte(buf, i);
        i++;
      }
      if (i < len && __read_byte(buf, i) == 39) {
        i++;
      }
      tok[ntokens].kind = TK_NUM;
      tok[ntokens].val = int_to_str(ch);
      tok[ntokens].pos = start;
      ntokens++;
      continue;
    }

    // String literal
    if (c == '"') {
      start = i;
      i++;
      while (i < len && __read_byte(buf, i) != '"') {
        if (__read_byte(buf, i) == '\\') {
          i++;
        }
        i++;
      }
      if (i < len) {
        i++;
      }
      // Store without quotes
      tok[ntokens].kind = TK_STR;
      tok[ntokens].val = make_str(buf, start + 1, i - start - 2);
      tok[ntokens].pos = start;
      ntokens++;
      continue;
    }

    // Three-char operators
    if (i + 2 < len) {
      c1 = __read_byte(buf, i + 1);
      int c2 = __read_byte(buf, i + 2);
      if (c == '<' && c1 == '<' && c2 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("<<="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 3; continue; }
      if (c == '>' && c1 == '>' && c2 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup(">>="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 3; continue; }
    }

    // Two-char operators
    if (i + 1 < len) {
      c1 = __read_byte(buf, i + 1);
      if (c == '-' && c1 == '>') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("->"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '=' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("=="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '!' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("!="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '<' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("<="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '>' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup(">="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '&' && c1 == '&') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("&&"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '|' && c1 == '|') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("||"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '+' && c1 == '+') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("++"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '-' && c1 == '-') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("--"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '<' && c1 == '<') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("<<"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '>' && c1 == '>') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup(">>"); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '+' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("+="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '-' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("-="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '*' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("*="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '/' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("/="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '%' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("%="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '&' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("&="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '|' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("|="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '^' && c1 == '=') { tok[ntokens].kind = TK_OP; tok[ntokens].val = my_strdup("^="); tok[ntokens].pos = i; ntokens = ntokens + 1; i = i + 2; continue; }
    }

    // Single-char operators
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
        c == '<' || c == '>' || c == '=' || c == '!' || c == '&' ||
        c == '|' || c == '^' || c == '~' || c == '.' || c == ';' || c == ',' || c == '(' || c == ')' ||
        c == '{' || c == '}' || c == '[' || c == ']' ||
        c == '?' || c == ':') {
      tok[ntokens].kind = TK_OP;
      tok[ntokens].val = make_str(buf, i, 1);
      tok[ntokens].pos = i;
      ntokens++;
      i++;
      continue;
    }

    if (c == '\\' && i + 1 < len && __read_byte(src, i + 1) == '\n') { i = i + 2; continue; }
    if (c == '\\') { i++; continue; }
    printf("Unexpected char %d at %d\n", c, i);
    exit(1);
  }

  tok[ntokens].kind = TK_EOF;
  tok[ntokens].val = my_strdup("");
  tok[ntokens].pos = len;
  ntokens++;

  // String literal concatenation: merge adjacent TK_STR tokens
  merge_string_literals();

  return 0;
}

// ---- Parser helpers ----

int p_match(int kind, int *val) {
  if (tok[cur_pos].kind != kind) { return 0; }
  if (val != 0) {
    if (my_strcmp(tok[cur_pos].val, val) != 0) { return 0; }
  }
  return 1;
}

int *p_eat(int kind, int *val) {
  if (tok[cur_pos].kind != kind) {
    printf("Expected kind %d, got %d at pos %d tok#%d (val=%s)\n", kind, tok[cur_pos].kind, tok[cur_pos].pos, cur_pos, tok[cur_pos].val);
    { int dd = cur_pos > 10 ? cur_pos - 10 : 0; while (dd < cur_pos + 5 && dd < ntokens) { printf("  tok[%d] k=%d '%s'\n", dd, tok[dd].kind, tok[dd].val); dd++; } }
    fflush(0);
    exit(1);
  }
  if (val != 0 && my_strcmp(tok[cur_pos].val, val) != 0) {
    printf("Expected '%s', got '%s' at pos %d tok#%d\n", val, tok[cur_pos].val, tok[cur_pos].pos, cur_pos);
    { int di = cur_pos - 5; if (di < 0) { di = 0; } while (di <= cur_pos + 3 && di < ntokens) { printf("  tok[%d] k=%d '%s'\n", di, tok[di].kind, tok[di].val); di++; } }
    exit(1);
  }
  int *v = tok[cur_pos].val;
  cur_pos++;
  return v;
}

int *find_lv_stype(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) {
      return lv[i].stype;
    }
    i--;
  }
  // Also check global struct variable table
  i = 0;
  while (i < nglv) {
    if (my_strcmp(glv[i].name, name) == 0) {
      return glv[i].stype;
    }
    i++;
  }
  return 0;
}

int add_lv(int *name, int *stype, int is_ptr) {
  lv[nlv].name = my_strdup(name);
  if (stype != 0) {
    lv[nlv].stype = my_strdup(stype);
  } else {
    lv[nlv].stype = 0;
  }
  lv[nlv].isptr = is_ptr;
  lv[nlv].arrsize = 0 - 1;
  lv[nlv].is_char = 0;
  lv_is_long[nlv] = 0;
  lv_is_short[nlv] = 0;
  nlv++;
  return 0;
}

int set_lv_is_char(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { lv[i].is_char = 1; return 0; }
    i--;
  }
  return 0;
}

int find_lv_is_char(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { return lv[i].is_char; }
    i--;
  }
  return 0;
}

int set_lv_is_long(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { lv_is_long[i] = 1; return 0; }
    i--;
  }
  return 0;
}

int set_lv_is_short(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { lv_is_short[i] = 1; return 0; }
    i--;
  }
  return 0;
}

int find_lv_is_long(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { return lv_is_long[i]; }
    i--;
  }
  return 0;
}

int find_lv_is_short(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { return lv_is_short[i]; }
    i--;
  }
  return 0;
}

int find_glv_is_long(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv_is_long[i]; }
    i--;
  }
  return 0;
}

int find_glv_is_short(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv_is_short[i]; }
    i--;
  }
  return 0;
}

int find_lv_isptr(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { return lv[i].isptr; }
    i--;
  }
  return 0;
}

int set_lv_arrsize(int *name, int sz) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { lv[i].arrsize = sz; return 0; }
    i--;
  }
  return 0;
}

int find_lv_arrsize(int *name) {
  int i = nlv - 1;
  while (i >= 0) {
    if (my_strcmp(lv[i].name, name) == 0) { return lv[i].arrsize; }
    i--;
  }
  return 0 - 1;
}

int find_glv_arrsize(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv[i].arrsize; }
    i--;
  }
  return 0 - 1;
}

int *find_glv_stype(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv[i].stype; }
    i--;
  }
  return 0;
}

int find_glv_is_char(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv[i].is_char; }
    i--;
  }
  return 0;
}

int find_glv_isptr(int *name) {
  int i = nglv - 1;
  while (i >= 0) {
    if (my_strcmp(glv[i].name, name) == 0) { return glv[i].isptr; }
    i--;
  }
  return 0;
}

int *find_typedef(int *name);

struct SDefInfo *find_sdef(int *name) {
  int i = 0;
  while (i < np_sdefs) {
    struct SDefInfo *sdi = p_sdefs[i];
    if (my_strcmp(sdi->name, name) == 0) {
      return sdi;
    }
    i++;
  }
  // Try resolving as a typedef
  int *resolved = find_typedef(name);
  if (resolved != 0 && my_strcmp(resolved, name) != 0) {
    i = 0;
    while (i < np_sdefs) {
      struct SDefInfo *sdi = p_sdefs[i];
      if (my_strcmp(sdi->name, resolved) == 0) {
        return sdi;
      }
      i++;
    }
  }
  return 0;
}

int *field_stype(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  struct SDefInfo *sd = find_sdef(sname);
  if (sd == 0) { printf("cc: unknown struct '%s' in field_stype (field '%s')\n", sname, fname); return 0; }
  for (int i = 0; i < sd->nflds; i++) {
    struct SFieldInfo *fi = sd->flds[i];
    if (my_strcmp(fi->name, fname) == 0) {
      // Resolve typedef on the returned field type
      if (fi->stype != 0) {
        int *resolved = find_typedef(fi->stype);
        if (resolved != 0) { return resolved; }
      }
      return fi->stype;
    }
  }
  printf("cc: struct '%s' has no field '%s' (nflds=%d, fields:", sname, fname, sd->nflds);
  for (int j = 0; j < sd->nflds; j++) { printf(" %s", sd->flds[j]->name); }
  printf(")\n");
  return 0;
}

int p_align_up(int val, int align) {
  return (val + align - 1) / align * align;
}

// Compute max alignment of a struct's fields (for embedded struct alignment)
int p_struct_max_align(struct SDefInfo *sd) {
  int max_a = 1;
  int k = 0;
  while (k < sd->nflds) {
    int ka = 4;  // default: int alignment
    if (sd->flds[k]->is_ptr > 0) { ka = 8; }
    else if ((sd->flds[k]->is_char || sd->flds[k]->is_char_type) && sd->flds[k]->is_ptr == 0) { ka = 1; }
    else if (sd->flds[k]->is_short) { ka = 2; }
    else if (sd->flds[k]->is_long) { ka = 8; }
    else if (sd->flds[k]->stype != 0 && sd->flds[k]->is_ptr == 0) {
      // Embedded struct: recurse
      struct SDefInfo *inner = find_sdef(sd->flds[k]->stype);
      if (inner == 0) { int *r = find_typedef(sd->flds[k]->stype); if (r != 0) { inner = find_sdef(r); } }
      if (inner != 0) { ka = p_struct_max_align(inner); }
    }
    if (ka > max_a) { max_a = ka; }
    k++;
  }
  return max_a;
}

int p_sizeof_struct_proper(int *sname) {
  struct SDefInfo *sd = find_sdef(sname);
  if (sd == 0) {
    int *resolved = find_typedef(sname);
    if (resolved != 0) { sd = find_sdef(resolved); }
  }
  if (sd == 0) return 8;
  // Bitfield structs: use nwords * 4 bytes
  if (sd->nwords > 0) return sd->nwords * 4;
  int p_is_union = sd->is_union;
  int offset = 0;
  int max_align = 1;
  int max_size = 0;
  int fi = 0;
  while (fi < sd->nflds) {
    int *fst = sd->flds[fi]->stype;
    int fip = sd->flds[fi]->is_ptr;
    int f_arr = sd->flds[fi]->is_array;
    int f_chr = sd->flds[fi]->is_char;
    int f_cht = sd->flds[fi]->is_char_type;
    int f_sht = sd->flds[fi]->is_short;
    int f_lng = sd->flds[fi]->is_long;
    int fsz = 4;
    int falign = 4;
    if (fip > 0) {
      fsz = 8; falign = 8;
    } else if (fst != 0) {
      fsz = p_sizeof_struct_proper(fst);
      // Compute max align of embedded struct (simplified: use 4 as default)
      falign = 4;
      if (fsz >= 8) { falign = 8; }
      // More precise: check inner fields
      struct SDefInfo *fsd = find_sdef(fst);
      if (fsd == 0) { int *fr = find_typedef(fst); if (fr != 0) { fsd = find_sdef(fr); } }
      if (fsd != 0) {
        falign = p_struct_max_align(fsd);
      }
    } else if (f_chr || f_cht) {
      fsz = 1; falign = 1;
    } else if (f_sht) {
      fsz = 2; falign = 2;
    } else if (f_lng) {
      fsz = 8; falign = 8;
    } else {
      fsz = 4; falign = 4;
    }
    if (f_arr > 0) {
      if (f_chr && fip == 0) {
        fsz = f_arr; falign = 1;
      } else {
        fsz = fsz * f_arr;
      }
    }
    if (p_is_union == 0) {
      offset = p_align_up(offset, falign);
      offset = offset + fsz;
    } else {
      if (fsz > max_size) { max_size = fsz; }
    }
    if (falign > max_align) { max_align = falign; }
    fi++;
  }
  int total;
  if (p_is_union) {
    total = p_align_up(max_size, max_align);
  } else {
    total = p_align_up(offset, max_align);
  }
  if (total == 0) { total = max_align; }
  return total;
}

// Compute byte offset of field fname in struct sname using proper layout
int p_field_byte_offset(int *sname, int *fname) {
  struct SDefInfo *sd = find_sdef(sname);
  if (sd == 0) {
    int *resolved = find_typedef(sname);
    if (resolved != 0) { sd = find_sdef(resolved); }
  }
  if (sd == 0) return 0;
  if (sd->nwords > 0) return 0;
  int offset = 0;
  int fi = 0;
  while (fi < sd->nflds) {
    int *fst = sd->flds[fi]->stype;
    int fip = sd->flds[fi]->is_ptr;
    int f_arr = sd->flds[fi]->is_array;
    int f_chr = sd->flds[fi]->is_char;
    int f_cht = sd->flds[fi]->is_char_type;
    int f_sht = sd->flds[fi]->is_short;
    int f_lng = sd->flds[fi]->is_long;
    int fsz = 4;
    int falign = 4;
    if (fip > 0) {
      fsz = 8; falign = 8;
    } else if (fst != 0) {
      fsz = p_sizeof_struct_proper(fst);
      falign = 4;
      if (fsz >= 8) { falign = 8; }
    } else if (f_chr || f_cht) {
      fsz = 1; falign = 1;
    } else if (f_sht) {
      fsz = 2; falign = 2;
    } else if (f_lng) {
      fsz = 8; falign = 8;
    }
    if (f_arr > 0) {
      if (f_chr && fip == 0) {
        fsz = f_arr; falign = 1;
      } else {
        fsz = fsz * f_arr;
      }
    }
    offset = p_align_up(offset, falign);
    if (my_strcmp(sd->flds[fi]->name, fname) == 0) {
      return offset;
    }
    offset = offset + fsz;
    fi++;
  }
  return 0;
}

int p_sizeof_struct(int *sname) {
  return p_sizeof_struct_proper(sname);
}

int p_sizeof_field(int *sname, int *fname) {
  struct SDefInfo *sd = find_sdef(sname);
  if (sd == 0) {
    int *resolved = find_typedef(sname);
    if (resolved != 0) { sd = find_sdef(resolved); }
  }
  if (sd == 0) return 8;
  int fi = 0;
  while (fi < sd->nflds) {
    if (my_strcmp(sd->flds[fi]->name, fname) == 0) {
      if (sd->flds[fi]->is_ptr) return 8;
      if (sd->flds[fi]->is_array > 0 && sd->flds[fi]->is_char) return sd->flds[fi]->is_array;
      if (sd->flds[fi]->is_array > 0) {
        int elem_sz = 4;  // default: int
        if (sd->flds[fi]->stype != 0) { elem_sz = p_sizeof_struct(sd->flds[fi]->stype); }
        else if (sd->flds[fi]->is_short) { elem_sz = 2; }
        else if (sd->flds[fi]->is_long) { elem_sz = 8; }
        return sd->flds[fi]->is_array * elem_sz;
      }
      if (sd->flds[fi]->stype != 0) return p_sizeof_struct(sd->flds[fi]->stype);
      if (sd->flds[fi]->is_char_type) return 1;
      if (sd->flds[fi]->is_short) return 2;
      if (sd->flds[fi]->is_long) return 8;
      return 4;
    }
    fi++;
  }
  return 4;
}

int *resolve_stype(struct Expr *e) {
  if (e->kind == ND_VAR) {
    return find_lv_stype(e->sval);
  }
  if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
    return field_stype(e->sval2, e->sval);
  }
  if (e->kind == ND_INDEX) {
    return resolve_stype(e->left);
  }
  if (e->kind == ND_UNARY) {
    return resolve_stype(e->left);
  }
  if (e->kind == ND_BINARY) {
    // Pointer arithmetic: ptr + N or ptr - N preserves struct type
    int *lt = resolve_stype(e->left);
    if (lt != 0) { return lt; }
    return resolve_stype(e->right);
  }
  if (e->kind == ND_CAST) {
    if (e->sval != 0) return e->sval;  // Cast target struct type
    return resolve_stype(e->left);
  }
  if (e->kind == ND_CALL) {
    // Look up function return struct type from struct_ret_names/stypes
    int ci = 0;
    while (ci < n_struct_ret) {
      if (my_strcmp(struct_ret_names[ci], e->sval) == 0) { return struct_ret_stypes[ci]; }
      ci++;
    }
  }
  if (e->kind == ND_ASSIGN) {
    return resolve_stype(e->left);
  }
  if (e->kind == ND_TERNARY) {
    return resolve_stype(e->right);  // then-branch has the value type
  }
  if (e->kind == ND_COMPOUND_LIT) {
    return e->sval;
  }
  if (e->kind == ND_STMT_EXPR) {
    return 0;  // TODO: track stmt expr result type
  }
  return 0;
}

// ---- AST constructors ----

struct Expr *new_num(long val) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_NUM;
  e->ival = val;
  e->sval = 0;
  e->sval2 = 0;
  e->left = 0;
  e->right = 0;
  e->args = 0;
  e->nargs = 0;
  e->desig = 0;
  return e;
}

struct Expr *new_var(int *name) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_VAR;
  e->sval = my_strdup(name);
  return e;
}

struct Expr *new_strlit(int *val) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_STRLIT;
  e->sval = my_strdup(val);
  return e;
}

struct Expr *new_call(int *name, struct Expr **args, int nargs) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_CALL;
  e->sval = my_strdup(name);
  e->args = args;
  e->nargs = nargs;
  return e;
}

struct Expr *new_unary(int op, struct Expr *rhs) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_UNARY;
  e->ival = op;
  e->left = rhs;
  return e;
}

struct Expr *new_binary(int *op, struct Expr *lhs, struct Expr *rhs) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_BINARY;
  e->sval2 = my_strdup(op);
  e->left = lhs;
  e->right = rhs;
  return e;
}

struct Expr *new_index(struct Expr *base, struct Expr *idx) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_INDEX;
  e->left = base;
  e->right = idx;
  return e;
}

struct Expr *new_field(struct Expr *obj, int *field, int *stype) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_FIELD;
  e->left = obj;
  e->sval = my_strdup(field);
  e->sval2 = my_strdup(stype);
  return e;
}

struct Expr *new_arrow(struct Expr *obj, int *field, int *stype) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_ARROW;
  e->left = obj;
  e->sval = my_strdup(field);
  e->sval2 = my_strdup(stype);
  return e;
}

struct Expr *new_assign(struct Expr *target, struct Expr *rhs) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_ASSIGN;
  e->left = target;
  e->right = rhs;
  return e;
}

struct Expr *new_postinc(struct Expr *operand) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_POSTINC;
  e->left = operand;
  return e;
}

struct Expr *new_postdec(struct Expr *operand) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_POSTDEC;
  e->left = operand;
  return e;
}

struct Expr *new_ternary(struct Expr *cond, struct Expr *then_e, struct Expr *else_e) {
  struct Expr *e = my_malloc(72);
  e->kind = ND_TERNARY;
  e->left = cond;
  e->right = then_e;
  e->args = my_malloc(8);
  e->args[0] = else_e;
  return e;
}

struct Stmt *new_return_s(struct Expr *e) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_RETURN;
  s->expr = e;
  return s;
}

struct Stmt *new_if_s(struct Expr *cond, struct Stmt **body, int nbody, struct Stmt **body2, int nbody2) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_IF;
  s->expr = cond;
  s->body = body;
  s->nbody = nbody;
  s->body2 = body2;
  s->nbody2 = nbody2;
  return s;
}

struct Stmt *new_while_s(struct Expr *cond, struct Stmt **body, int nbody) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_WHILE;
  s->expr = cond;
  s->body = body;
  s->nbody = nbody;
  return s;
}

struct Stmt *new_for_s(struct Stmt *init, struct Expr *cond, struct Expr *post, struct Stmt **body, int nbody) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_FOR;
  s->init = init;
  s->expr = cond;
  s->expr2 = post;
  s->body = body;
  s->nbody = nbody;
  return s;
}

struct Stmt *new_break_s() {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_BREAK;
  return s;
}

struct Stmt *new_continue_s() {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_CONTINUE;
  return s;
}

struct Stmt *new_expr_s(struct Expr *e) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_EXPR;
  s->expr = e;
  return s;
}

struct Stmt *new_vardecl_s(struct VarDecl **decls, int ndecls) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_VARDECL;
  s->decls = decls;
  s->ndecls = ndecls;
  return s;
}

struct Stmt *new_dowhile_s(struct Expr *cond, struct Stmt **body, int nbody) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_DOWHILE;
  s->expr = cond;
  s->body = body;
  s->nbody = nbody;
  return s;
}

struct Stmt *new_goto_s(int *label) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_GOTO;
  s->sval = my_strdup(label);
  return s;
}

struct Stmt *new_label_s(int *label, struct Stmt *following) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_LABEL;
  s->sval = my_strdup(label);
  s->body = my_malloc(8);
  s->body[0] = following;
  s->nbody = 1;
  return s;
}

struct Stmt *new_switch_s(struct Expr *cond, int *case_vals, struct Stmt ***case_bodies, int *case_nbodies, int ncases, struct Stmt **default_body, int ndefault) {
  struct Stmt *s = my_malloc(144);
  s->kind = ST_SWITCH;
  s->expr = cond;
  s->case_vals = case_vals;
  s->case_bodies = case_bodies;
  s->case_nbodies = case_nbodies;
  s->ncases = ncases;
  s->default_body = default_body;
  s->ndefault = ndefault;
  return s;
}

// ---- Parser ----

int skip_qualifiers() {
  int skipped = 0;
  while (1) {
    if (p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "register") || p_match(TK_KW, "restrict") ||
        p_match(TK_KW, "__restrict") || p_match(TK_KW, "__restrict__") || p_match(TK_KW, "__volatile") || p_match(TK_KW, "__volatile__") || p_match(TK_KW, "__const") || p_match(TK_KW, "__const__") ||
        p_match(TK_KW, "static")) {
      cur_pos++;
      skipped = 1;
    } else if (p_match(TK_KW, "__attribute__") || p_match(TK_KW, "__attribute")) {
      skip_attribute();
      skipped = 1;
    } else if (p_match(TK_KW, "_Alignas")) {
      cur_pos++; // skip _Alignas
      if (p_match(TK_OP, "(")) {
        int adepth = 0;
        while (cur_pos < ntokens) {
          if (p_match(TK_OP, "(")) { adepth++; cur_pos++; }
          else if (p_match(TK_OP, ")")) { adepth--; cur_pos++; if (adepth == 0) break; }
          else { cur_pos++; }
        }
      }
      skipped = 1;
    } else if (p_match(TK_KW, "__extension__") || p_match(TK_KW, "__inline__") || p_match(TK_KW, "__inline") || p_match(TK_KW, "inline") || p_match(TK_KW, "_Noreturn")) {
      cur_pos++;
      skipped = 1;
    } else if (p_match(TK_OP, "[") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "[") == 0) {
      // C23 [[attribute]] syntax - skip [[...]]
      cur_pos += 2; // skip [[
      int bdepth = 1;
      while (cur_pos < ntokens && bdepth > 0) {
        if (p_match(TK_OP, "[") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "[") == 0) { bdepth++; cur_pos += 2; }
        else if (p_match(TK_OP, "]") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "]") == 0) { bdepth--; cur_pos += 2; }
        else { cur_pos++; }
      }
      skipped = 1;
    } else {
      break;
    }
  }
  return skipped;
}

int skip_attribute() {
  if (p_match(TK_KW, "__attribute__") || p_match(TK_KW, "__attribute")) {
    cur_pos++;
    if (p_match(TK_OP, "(")) {
      int depth = 0;
      while (cur_pos < ntokens) {
        if (p_match(TK_OP, "(")) { depth++; cur_pos++; }
        else if (p_match(TK_OP, ")")) { depth--; cur_pos++; if (depth == 0) break; }
        else { cur_pos++; }
      }
    }
    return 1;
  }
  if (p_match(TK_KW, "__extension__") || p_match(TK_KW, "__inline__") || p_match(TK_KW, "__inline") || p_match(TK_KW, "inline") || p_match(TK_KW, "_Noreturn")) {
    cur_pos++;
    return 1;
  }
  return 0;
}

int is_funcptr_decl() {
  if (!p_match(TK_OP, "(")) { return 0; }
  if (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "*") == 0) { return 1; }
  return 0;
}

int skip_param_list() {
  int depth = 0;
  p_eat(TK_OP, "(");
  depth = 1;
  while (depth > 0) {
    if (p_match(TK_OP, "(")) { depth = depth + 1; }
    if (p_match(TK_OP, ")")) { depth = depth - 1; }
    if (depth > 0) { cur_pos = cur_pos + 1; }
  }
  p_eat(TK_OP, ")");
  return 0;
}

int *find_typedef(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td[i].stype;
    }
    i--;
  }
  return 0;
}

int has_typedef(int *name) {
  for (int i = 0; i < ntd; i++) {
    if (my_strcmp(td[i].name, name) == 0) {
      return 1;
    }
  }
  return 0;
}

int td_lookup_is_char(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td[i].is_char ? (td[i].is_unsigned ? 2 : 1) : 0;
    }
    i--;
  }
  return 0;
}

int td_lookup_is_funcptr(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td[i].is_funcptr;
    }
    i--;
  }
  return 0;
}

int td_lookup_is_long(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td_is_long[i];
    }
    i--;
  }
  return 0;
}

int td_lookup_is_short(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td_is_short[i];
    }
    i--;
  }
  return 0;
}

int td_lookup_is_unsigned(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td_is_unsigned[i];
    }
    i--;
  }
  return 0;
}

int td_lookup_is_ptr(int *name) {
  int i = ntd - 1;
  while (i >= 0) {
    if (my_strcmp(td[i].name, name) == 0) {
      return td_is_ptr[i];
    }
    i--;
  }
  return 0;
}

int add_typedef(int *name, int *stype) {
  if (ntd >= MAX_TYPEDEFS) { printf("cc: OVERFLOW td_name ntd=%d name=%s\n", ntd, name); fflush(0); }
  td[ntd].name = my_strdup(name);
  if (stype != 0) {
    td[ntd].stype = my_strdup(stype);
  } else {
    td[ntd].stype = 0;
  }
  ntd++;
  return 0;
}

struct SFieldInfo *new_sfieldinfo(int *name, int *stype, int is_ptr, int bw, int is_arr, int is_char) {
  struct SFieldInfo *fi = my_malloc(80);
  fi->name = name;
  fi->stype = stype;
  fi->is_ptr = is_ptr;
  fi->bit_width = bw;
  fi->is_array = is_arr;
  fi->is_char = is_char;
  fi->is_short = 0;
  fi->is_long = 0;
  fi->is_unsigned = 0;
  fi->is_char_type = 0;
  return fi;
}

int *parse_base_type() {
  skip_qualifiers();
  last_type_unsigned = 0;
  last_type_is_long = 0;
  last_type_is_short = 0;
  if (p_match(TK_KW, "int")) {
    p_eat(TK_KW, "int");
    // consume trailing long/short
    while (p_match(TK_KW, "long") || p_match(TK_KW, "short")) { if (p_match(TK_KW, "long")) { last_type_is_long = 1; } if (p_match(TK_KW, "short")) { last_type_is_short = 1; } cur_pos = cur_pos + 1; }
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "char")) {
    p_eat(TK_KW, "char");
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "void")) {
    p_eat(TK_KW, "void");
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") || p_match(TK_KW, "__signed__")) {
    if (p_match(TK_KW, "unsigned")) { last_type_unsigned = 1; }
    cur_pos++;
    // optional: int, long, short, char after
    if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; }
    else if (p_match(TK_KW, "long")) { last_type_is_long = 1; cur_pos = cur_pos + 1; if (p_match(TK_KW, "long")) { cur_pos = cur_pos + 1; } if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; } }
    else if (p_match(TK_KW, "short")) { last_type_is_short = 1; cur_pos = cur_pos + 1; if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; } }
    else if (p_match(TK_KW, "char")) { cur_pos = cur_pos + 1; }
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "long")) {
    last_type_is_long = 1;
    cur_pos++;
    if (p_match(TK_KW, "long")) { cur_pos = cur_pos + 1; }
    if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; }
    else if (p_match(TK_KW, "double")) { cur_pos = cur_pos + 1; }
    else if (p_match(TK_KW, "unsigned")) { cur_pos = cur_pos + 1; if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; } }
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "short")) {
    last_type_is_short = 1;
    cur_pos++;
    if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) { last_type_unsigned = p_match(TK_KW, "unsigned"); cur_pos = cur_pos + 1; }
    if (p_match(TK_KW, "int")) { cur_pos = cur_pos + 1; }
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "double")) {
    cur_pos++;
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "float")) {
    cur_pos++;
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "_Bool")) {
    cur_pos++;
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "__typeof__") || p_match(TK_KW, "typeof") || p_match(TK_KW, "__typeof")) {
    cur_pos++;
    p_eat(TK_OP, "(");
    // Skip the expression inside typeof, handling nested parens
    int typeof_depth = 1;
    while (typeof_depth > 0) {
      if (p_match(TK_OP, "(")) { typeof_depth++; }
      else if (p_match(TK_OP, ")")) { typeof_depth--; if (typeof_depth == 0) break; }
      cur_pos++;
    }
    p_eat(TK_OP, ")");
    skip_qualifiers();
    return 0; // treat as int
  }
  if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) {
    int is_union_kw = p_match(TK_KW, "union");
    if (is_union_kw) { p_eat(TK_KW, "union"); }
    else { p_eat(TK_KW, "struct"); }
    if (p_match(TK_OP, "{")) {
      // Anonymous struct/union
      int *synth_name = build_str2("__anon_", int_to_str(anon_struct_counter));
      anon_struct_counter++;
      p_eat(TK_OP, "{");
      struct SFieldInfo **aflds = my_malloc(256 * 8);
      int **afields = my_malloc(256 * 8);
      int **afield_types = my_malloc(256 * 8);
      int anf = 0;
      while (!p_match(TK_OP, "}")) {
        int af_is_char = p_match(TK_KW, "char");
        int af_is_short = p_match(TK_KW, "short");
        int *aftype = parse_base_type();
        int af_is_long = last_type_is_long;
        if (last_type_is_short) { af_is_short = 1; }
        if (af_is_long) { af_is_short = 0; }
        int af_is_unsigned = last_type_unsigned;
        int aptr = 0;
        int afp = 0;
        if (is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); aptr = 1; afp = 1; }
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); aptr = 1; }
        if (afp == 0 && is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); afp = 1; }
        // Anonymous bitfield: type : width;
        if (p_match(TK_OP, ":")) {
          p_eat(TK_OP, ":");
          int abw2 = parse_const_expr();
          int *abname = build_str2("_anon_bf_", int_to_str(anf));
          struct SFieldInfo *afi2 = new_sfieldinfo(abname, aftype, aptr, abw2, 0, 0);
          afi2->is_short = af_is_short;
          afi2->is_long = af_is_long;
          afi2->is_unsigned = af_is_unsigned;
          afi2->is_char_type = af_is_char;
          aflds[anf] = afi2;
          afields[anf] = abname;
          afield_types[anf] = 0;
          anf++;
          p_eat(TK_OP, ";");
          continue;
        }
        int *afname = my_strdup(p_eat(TK_ID, 0));
        if (afp) { p_eat(TK_OP, ")"); skip_param_list(); }
        while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
        int abw = 0;
        if (p_match(TK_OP, ":")) { p_eat(TK_OP, ":"); abw = my_atoi(p_eat(TK_NUM, 0)); }
        struct SFieldInfo *afi = new_sfieldinfo(afname, aftype, aptr, abw, 0, af_is_char);
        afi->is_short = af_is_short;
        afi->is_long = af_is_long;
        afi->is_unsigned = af_is_unsigned;
        afi->is_char_type = af_is_char;
        aflds[anf] = afi;
        afields[anf] = afname;
        if (aftype != 0 && aptr == 0) { afield_types[anf] = aftype; } else { afield_types[anf] = 0; }
        anf++;
        // Handle comma-separated fields
        while (p_match(TK_OP, ",")) {
          p_eat(TK_OP, ",");
          int eap = aptr;
          if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); eap = 1; }
          int *ean = my_strdup(p_eat(TK_ID, 0));
          while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
          int eabw = 0;
          if (p_match(TK_OP, ":")) { p_eat(TK_OP, ":"); eabw = my_atoi(p_eat(TK_NUM, 0)); }
          afi = new_sfieldinfo(ean, aftype, eap, eabw, 0, af_is_char);
          afi->is_short = af_is_short;
          afi->is_long = af_is_long;
          afi->is_unsigned = af_is_unsigned;
          afi->is_char_type = af_is_char;
          aflds[anf] = afi;
          afields[anf] = ean;
          if (aftype != 0 && eap == 0) { afield_types[anf] = aftype; } else { afield_types[anf] = 0; }
          anf++;
        }
        p_eat(TK_OP, ";");
      }
      p_eat(TK_OP, "}");
      // Register in parser's struct table
      struct SDefInfo *asdi = my_malloc(48);
      asdi->name = my_strdup(synth_name);
      asdi->flds = aflds;
      asdi->nflds = anf;
      asdi->nwords = 0;
      asdi->is_union = is_union_kw;
      p_sdefs[np_sdefs] = asdi;
      np_sdefs++;
      // Register for codegen
      struct SDef *asd = my_malloc(128);
      asd->name = my_strdup(synth_name);
      asd->fields = afields;
      asd->field_types = afield_types;
      asd->nfields = anf;
      asd->is_union = is_union_kw;
      asd->bit_widths = 0;
      asd->bit_offsets = 0;
      asd->word_indices = 0;
      asd->nwords = 0;
      asd->field_is_array = my_malloc(anf * 8);
      asd->field_is_char = my_malloc(anf * 8);
      asd->field_is_ptr = my_malloc(anf * 8);
      asd->field_is_short = my_malloc(anf * 8);
      asd->field_is_long = my_malloc(anf * 8);
      asd->field_is_char_type = my_malloc(anf * 8);
      asd->field_is_unsigned = my_malloc(anf * 8);
      // Extract field flags from SFieldInfo into temp arrays first, then copy
      // (workaround for gen0 codegen issue with struct field access in loops)
      int *tmp_fa = my_malloc(anf * 8);
      int *tmp_fc = my_malloc(anf * 8);
      int *tmp_fp = my_malloc(anf * 8);
      int *tmp_fsh = my_malloc(anf * 8);
      int *tmp_fl = my_malloc(anf * 8);
      int *tmp_fct = my_malloc(anf * 8);
      int *tmp_fu = my_malloc(anf * 8);
      { int ti = 0; while (ti < anf) {
        struct SFieldInfo *src = aflds[ti];
        tmp_fa[ti] = src->is_array;
        tmp_fc[ti] = src->is_char;
        tmp_fp[ti] = src->is_ptr;
        tmp_fsh[ti] = src->is_short;
        tmp_fl[ti] = src->is_long;
        tmp_fct[ti] = src->is_char_type;
        tmp_fu[ti] = src->is_unsigned;
        ti = ti + 1;
      } }
      { int ci = 0; while (ci < anf) {
        asd->field_is_array[ci] = tmp_fa[ci];
        asd->field_is_char[ci] = tmp_fc[ci];
        asd->field_is_ptr[ci] = tmp_fp[ci];
        asd->field_is_short[ci] = tmp_fsh[ci];
        asd->field_is_long[ci] = tmp_fl[ci];
        asd->field_is_char_type[ci] = tmp_fct[ci];
        asd->field_is_unsigned[ci] = tmp_fu[ci];
        ci = ci + 1;
      } }
      inline_sdefs[ninline_sdefs] = asd;
      ninline_sdefs++;
      skip_qualifiers();
      return my_strdup(synth_name);
    }
    int *name = p_eat(TK_ID, 0);
    // Local/inline struct definition: struct Name { fields... }
    if (p_match(TK_OP, "{")) {
      p_eat(TK_OP, "{");
      struct SFieldInfo **lflds = my_malloc(256 * 8);
      int **lfields = my_malloc(256 * 8);
      int **lfield_types = my_malloc(256 * 8);
      int lnf = 0;
      while (!p_match(TK_OP, "}")) {
        int *lftype = parse_base_type();
        int lptr = 0;
        int lfp = 0;
        if (is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); lptr = 1; lfp = 1; }
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); lptr = 1; }
        if (lfp == 0 && is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); lfp = 1; }
        int *lfname = my_strdup(p_eat(TK_ID, 0));
        if (lfp) {
          p_eat(TK_OP, ")");
          if (p_match(TK_OP, "(")) { skip_param_list(); }
          else if (p_match(TK_OP, "[")) {
            // Pointer-to-array: type (*name)[size] — treat as pointer
            lfp = 0;
            while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
          }
        }
        while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
        if (p_match(TK_OP, ":")) { p_eat(TK_OP, ":"); p_eat(TK_NUM, 0); }
        struct SFieldInfo *lfi = new_sfieldinfo(lfname, lftype, lptr, 0, 0, 0);
        lflds[lnf] = lfi;
        lfields[lnf] = lfname;
        if (lftype != 0 && lptr == 0) { lfield_types[lnf] = lftype; } else { lfield_types[lnf] = 0; }
        lnf++;
        while (p_match(TK_OP, ",")) {
          p_eat(TK_OP, ",");
          int elp = lptr;
          if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); elp = 1; }
          int *eln = my_strdup(p_eat(TK_ID, 0));
          while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
          struct SFieldInfo *elfi = new_sfieldinfo(eln, lftype, elp, 0, 0, 0);
          lflds[lnf] = elfi;
          lfields[lnf] = eln;
          if (lftype != 0 && elp == 0) { lfield_types[lnf] = lftype; } else { lfield_types[lnf] = 0; }
          lnf++;
        }
        p_eat(TK_OP, ";");
      }
      p_eat(TK_OP, "}");
      struct SDefInfo *lsdi = my_malloc(48);
      lsdi->name = my_strdup(name);
      lsdi->flds = lflds;
      lsdi->nflds = lnf;
      lsdi->nwords = 0;
      lsdi->is_union = is_union_kw;
      p_sdefs[np_sdefs] = lsdi;
      np_sdefs++;
      struct SDef *lsd = my_malloc(128);
      lsd->name = my_strdup(name);
      lsd->fields = lfields;
      lsd->field_types = lfield_types;
      lsd->nfields = lnf;
      lsd->is_union = is_union_kw;
      lsd->bit_widths = 0;
      lsd->bit_offsets = 0;
      lsd->word_indices = 0;
      lsd->nwords = 0;
      lsd->field_is_array = my_malloc(lnf * 8);
      lsd->field_is_char = my_malloc(lnf * 8);
      lsd->field_is_ptr = my_malloc(lnf * 8);
      lsd->field_is_short = my_malloc(lnf * 8);
      lsd->field_is_long = my_malloc(lnf * 8);
      lsd->field_is_char_type = my_malloc(lnf * 8);
      lsd->field_is_unsigned = my_malloc(lnf * 8);
      // Extract field flags via temp arrays (workaround for gen0 codegen issue)
      { int *lfa = my_malloc(lnf * 8); int *lfc = my_malloc(lnf * 8); int *lfp = my_malloc(lnf * 8);
        int *lfsh = my_malloc(lnf * 8); int *lfl = my_malloc(lnf * 8); int *lfct = my_malloc(lnf * 8);
        int *lfu = my_malloc(lnf * 8);
        int li2 = 0; while (li2 < lnf) {
          struct SFieldInfo *src = lflds[li2];
          lfa[li2] = src->is_array; lfc[li2] = src->is_char; lfp[li2] = src->is_ptr;
          lfsh[li2] = src->is_short; lfl[li2] = src->is_long; lfct[li2] = src->is_char_type;
          lfu[li2] = src->is_unsigned;
          li2 = li2 + 1;
        }
        li2 = 0; while (li2 < lnf) {
          lsd->field_is_array[li2] = lfa[li2]; lsd->field_is_char[li2] = lfc[li2]; lsd->field_is_ptr[li2] = lfp[li2];
          lsd->field_is_short[li2] = lfsh[li2]; lsd->field_is_long[li2] = lfl[li2]; lsd->field_is_char_type[li2] = lfct[li2];
          lsd->field_is_unsigned[li2] = lfu[li2];
          li2 = li2 + 1;
        }
      }
      inline_sdefs[ninline_sdefs] = lsd;
      ninline_sdefs++;
    }
    skip_qualifiers();
    return my_strdup(name);
  }
  if (p_match(TK_KW, "enum")) {
    p_eat(TK_KW, "enum");
    if (p_match(TK_ID, 0)) { p_eat(TK_ID, 0); }
    skip_qualifiers();
    return 0;
  }
  if (p_match(TK_KW, "_Bool")) {
    cur_pos++;
    skip_qualifiers();
    return 0;
  }
  // Check if it's a typedef name
  if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) {
    // Mark long/short typedefs for correct sizing
    if (td_lookup_is_long(tok[cur_pos].val)) {
      last_type_is_long = 1;
    }
    else if (td_lookup_is_short(tok[cur_pos].val)) {
      last_type_is_short = 1;
    }
    else if (my_strcmp(tok[cur_pos].val, "va_list") == 0 || my_strcmp(tok[cur_pos].val, "__builtin_va_list") == 0 ||
        my_strcmp(tok[cur_pos].val, "size_t") == 0 || my_strcmp(tok[cur_pos].val, "ssize_t") == 0 ||
        my_strcmp(tok[cur_pos].val, "ptrdiff_t") == 0) {
      last_type_is_long = 1;
    }
    if (td_lookup_is_unsigned(tok[cur_pos].val)) {
      last_type_unsigned = 1;
    }
    int *td_st = find_typedef(tok[cur_pos].val);
    cur_pos++;
    skip_qualifiers();
    if (td_st != 0) {
      return my_strdup(td_st);
    }
    return 0;
  }
  // Implicit int: identifier followed by ( — K&R function definition
  if (tok[cur_pos].kind == TK_ID && !has_typedef(tok[cur_pos].val) &&
      cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "(") == 0) {
    return 0;
  }
  printf("Expected type at pos %d tok#%d (got '%s') ntd=%d\n", tok[cur_pos].pos, cur_pos, tok[cur_pos].val, ntd);
  // Treat unknown identifiers as a type and skip
  if (tok[cur_pos].kind == TK_ID) {
    cur_pos++;
    return 0;
  }
  { int dd = cur_pos > 10 ? cur_pos - 10 : 0; while (dd < cur_pos + 5 && dd < ntokens) { printf("  tok[%d] k=%d '%s'\n", dd, tok[dd].kind, tok[dd].val); dd++; } }
  fflush(0);
  exit(1);
  return 0;
}

struct Stmt *parse_stmt();

struct Stmt **parse_block(int *out_len) {
  p_eat(TK_OP, "{");
  struct Stmt **stmts = my_malloc(512 * 8);
  int n = 0;
  while (!p_match(TK_OP, "}")) {
    stmts[n] = parse_stmt();
    n++;
  }
  p_eat(TK_OP, "}");
  *out_len = n;
  return stmts;
}

struct Stmt *parse_stmt();

struct Stmt **parse_block_or_stmt(int *out_len) {
  if (p_match(TK_OP, "{")) {
    return parse_block(out_len);
  }
  struct Stmt **stmts = my_malloc(8);
  stmts[0] = parse_stmt();
  *out_len = 1;
  return stmts;
}

int parse_const_expr();

struct VarDecl *make_vd(int *name, int *stype, int arr_size, int is_ptr, struct Expr *init, int is_static) {
  struct VarDecl *vd = my_malloc(96);
  vd->name = name;
  vd->stype = stype;
  vd->arr_size = arr_size;
  vd->is_ptr = is_ptr;
  vd->init = init;
  vd->is_static = is_static;
  vd->is_unsigned = 0;
  vd->arr_size2 = 0 - 1;
  vd->is_char = 0;
  vd->is_float = 0;
  vd->is_short = 0;
  vd->is_long = 0;
  return vd;
}

// Parse brace initializer list: { expr, expr, ... }
struct Expr *parse_init_list(int *stype_name) {
  int init_cap = 256;
  struct Expr **elems = my_malloc(init_cap * 8);
  int *desig = my_malloc(init_cap * 8);
  int nelems = 0;
  int has_desig = 0;
  int di = 0;
  int *fname = 0;
  struct SDefInfo *sd = 0;
  int fi = 0;
  p_eat(TK_OP, "{");
  while (!p_match(TK_OP, "}")) {
    di = 0 - 1;
    if (p_match(TK_OP, ".")) {
      p_eat(TK_OP, ".");
      fname = p_eat(TK_ID, 0);
      // Handle nested designators: .a.b.c = val — skip to last field
      while (p_match(TK_OP, ".")) {
        p_eat(TK_OP, ".");
        fname = p_eat(TK_ID, 0);
      }
      p_eat(TK_OP, "=");
      has_desig = 1;
      if (stype_name != 0) {
        sd = find_sdef(stype_name);
        if (sd != 0) {
          fi = 0;
          while (fi < sd->nflds) {
            if (my_strcmp(sd->flds[fi]->name, fname) == 0) {
              di = fi;
              break;
            }
            fi++;
          }
        }
      }
      if (di < 0) { di = nelems; } // Unknown struct type — use positional
    } else if (tok[cur_pos].kind == TK_ID && cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, ":") == 0) {
      // GCC extension: field: value (without dot, colon instead of =)
      fname = p_eat(TK_ID, 0);
      p_eat(TK_OP, ":");
      has_desig = 1;
      if (stype_name != 0) {
        sd = find_sdef(stype_name);
        if (sd != 0) {
          fi = 0;
          while (fi < sd->nflds) {
            if (my_strcmp(sd->flds[fi]->name, fname) == 0) {
              di = fi;
              break;
            }
            fi++;
          }
        }
      }
      if (di < 0) { di = nelems; }
    } else if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      di = my_atoi(p_eat(TK_NUM, 0));
      p_eat(TK_OP, "]");
      p_eat(TK_OP, "=");
      has_desig = 1;
    }
    if (nelems >= init_cap) {
      int new_cap = init_cap * 2;
      struct Expr **new_elems = my_malloc(new_cap * 8);
      int *new_desig = my_malloc(new_cap * 8);
      for (int ri = 0; ri < nelems; ri++) { new_elems[ri] = elems[ri]; new_desig[ri] = desig[ri]; }
      elems = new_elems;
      desig = new_desig;
      init_cap = new_cap;
    }
    if (p_match(TK_OP, "{")) {
      elems[nelems] = parse_init_list(0);
    } else {
      elems[nelems] = parse_expr(0);
    }
    desig[nelems] = di;
    nelems++;
    if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); continue; }
    break;
  }
  p_eat(TK_OP, "}");
  struct Expr *e = my_malloc(80);
  e->kind = ND_INITLIST;
  e->args = elems;
  e->nargs = nelems;
  if (has_desig) {
    e->desig = desig;
  } else {
    e->desig = 0;
  }
  return e;
}

struct Stmt *parse_vardecl_stmt(int vd_is_static) {
  // Handle static appearing after const: "const static int x"
  if (vd_is_static == 0 && p_match(TK_KW, "const") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "static") == 0) {
    vd_is_static = 1;
  }
  if (vd_is_static == 0 && p_match(TK_KW, "static")) {
    p_eat(TK_KW, "static");
    vd_is_static = 1;
  }
  int base_is_char = 0;
  int base_is_float = 0;
  int base_unsigned = 0;
  int base_is_funcptr_td = 0;
  int base_is_short = 0;
  int base_is_long = 0;
  int base_td_is_ptr = 0;
  // Check if base type is char or float/double/short/long (before parse_base_type consumes it)
  {
    int sv = cur_pos;
    skip_qualifiers();
    if (p_match(TK_KW, "char")) { base_is_char = 1; }
    else if (p_match(TK_KW, "float") || p_match(TK_KW, "double")) { base_is_float = 1; }
    else if (p_match(TK_KW, "short")) { base_is_short = 1; }
    else if (p_match(TK_KW, "long")) { base_is_long = 1; }
    else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
      if (p_match(TK_KW, "unsigned")) { base_unsigned = 1; }
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { base_is_char = 1; }
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "short") == 0) { base_is_short = 1; }
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "long") == 0) { base_is_long = 1; }
    }
    else if (tok[cur_pos].kind == TK_ID) {
      int tdc = td_lookup_is_char(tok[cur_pos].val);
      if (tdc) { base_is_char = 1; if (tdc == 2) { base_unsigned = 1; } }
      if (td_lookup_is_funcptr(tok[cur_pos].val)) { base_is_funcptr_td = 1; }
      if (td_lookup_is_ptr(tok[cur_pos].val)) { base_td_is_ptr = 1; }
      if (td_lookup_is_unsigned(tok[cur_pos].val)) { base_unsigned = 1; }
    }
    cur_pos = sv;
  }
  int *stype = parse_base_type();
  if (base_unsigned == 0) { base_unsigned = last_type_unsigned; }
  // Standalone struct/union definition: struct Name { ... };
  if (stype != 0 && p_match(TK_OP, ";")) {
    p_eat(TK_OP, ";");
    struct Stmt *nop = my_malloc(144);
    nop->kind = ST_EXPR;
    nop->expr = new_num(0);
    return nop;
  }
  struct VarDecl **decls = my_malloc(64 * 8);
  int ndecls = 0;

  while (1) {
    int is_ptr = base_is_funcptr_td ? 1 : (base_td_is_ptr ? 1 : 0);
    int is_funcptr = 0;
    // Function pointer: type (*name)(params) or type *(*name)(params)
    if (is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      is_ptr = 1;
      is_funcptr = 1;
    }
    while (p_match(TK_OP, "*")) {
      p_eat(TK_OP, "*");
      is_ptr++;
    }
    // Skip post-pointer qualifiers and more pointers: char *const *volatile *p
    while (p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "restrict") || p_match(TK_KW, "__restrict") || p_match(TK_KW, "__restrict__") || p_match(TK_OP, "*")) {
      if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); is_ptr++; }
      else { cur_pos++; }
    }
    // Check again after consuming stars: type * (*name)(params)
    if (is_funcptr == 0 && is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      is_ptr++;
      is_funcptr = 1;
    }
    // Parenthesized declarator without funcptr: int *(name[N]) — skip parens
    int paren_decl = 0;
    if (is_funcptr == 0 && p_match(TK_OP, "(") && !is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      paren_decl = 1;
    }
    skip_qualifiers();
    int *name = my_strdup(p_eat(TK_ID, 0));
    int arr_size = 0 - 1;
    int arr_size2 = 0 - 1;
    if (is_funcptr) {
      // Handle array of function pointers: type (*name[N])(params)
      if (p_match(TK_OP, "[")) {
        p_eat(TK_OP, "[");
        arr_size = parse_const_expr();
        p_eat(TK_OP, "]");
      }
      p_eat(TK_OP, ")");
      if (p_match(TK_OP, "(")) {
        skip_param_list();
      } else if (p_match(TK_OP, "[")) {
        // Pointer-to-array local: type (*name)[N] — treat as pointer
        is_funcptr = 0;
        while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
      }
    }
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      if (p_match(TK_OP, "]")) {
        arr_size = 0; // infer from initializer
      } else {
        arr_size = parse_const_expr();
      }
      p_eat(TK_OP, "]");
      // Handle multi-dimensional arrays: int arr[N][M][K]... => flatten to arr[N*M*K...]
      while (p_match(TK_OP, "[")) {
        p_eat(TK_OP, "[");
        int dim_n = parse_const_expr();
        p_eat(TK_OP, "]");
        if (arr_size2 < 0) { arr_size2 = dim_n; }
        else { arr_size2 = arr_size2 * dim_n; }
        if (arr_size > 0 && dim_n > 0) { arr_size = arr_size * dim_n; }
      }
    }
    if (paren_decl) { p_eat(TK_OP, ")"); }
    while (skip_attribute()) {}
    struct Expr *init = 0;
    int *decl_stype = 0;
    if (stype != 0) {
      decl_stype = my_strdup(stype);
    }
    if (arr_size >= 0 && p_match(TK_OP, "=")) {
      // Array initializer or string init
      p_eat(TK_OP, "=");
      if (p_match(TK_STR, 0)) {
        // String initializer for char array
        int *str_val = my_strdup(p_eat(TK_STR, 0));
        int slen = my_strlen(str_val) + 1;
        if (arr_size == 0) { arr_size = slen; }
        init = new_strlit(str_val);
      } else {
        init = parse_init_list(decl_stype);
        if (arr_size == 0) { arr_size = init->nargs; }
      }
    } else if (decl_stype != 0 && is_ptr == 0 && arr_size < 0 && p_match(TK_OP, "=")) {
      // Struct initializer or struct expression assignment
      p_eat(TK_OP, "=");
      if (p_match(TK_OP, "{")) {
        init = parse_init_list(decl_stype);
      } else {
        init = parse_expr(0);
      }
    } else if ((decl_stype == 0 || is_ptr != 0) && arr_size < 0 && p_match(TK_OP, "=")) {
      p_eat(TK_OP, "=");
      init = parse_expr(0);
    }
    decls[ndecls] = make_vd(my_strdup(name), decl_stype, arr_size, is_ptr, init, vd_is_static);
    decls[ndecls]->is_unsigned = base_unsigned;
    decls[ndecls]->is_char = base_is_char;
    decls[ndecls]->is_float = base_is_float;
    decls[ndecls]->arr_size2 = arr_size2;
    decls[ndecls]->is_short = base_is_short;
    decls[ndecls]->is_long = base_is_long;
    decls[ndecls]->is_unsigned = base_unsigned;
    if (last_type_is_short) { decls[ndecls]->is_short = 1; }
    if (last_type_is_long) { decls[ndecls]->is_long = 1; }
    if (last_type_unsigned) { decls[ndecls]->is_unsigned = 1; }
    ndecls++;
    // Always register local variable name (for enum shadowing)
    if (stype != 0) {
      add_lv(name, stype, is_ptr);
    } else {
      add_lv(name, 0, is_ptr);
    }
    if (arr_size >= 0) {
      set_lv_arrsize(name, arr_size);
    }
    if (base_is_char) {
      set_lv_is_char(name);
    }
    if (base_is_long || last_type_is_long) {
      set_lv_is_long(name);
    }
    if (base_is_short || last_type_is_short) {
      set_lv_is_short(name);
    }
    if (p_match(TK_OP, ",")) {
      p_eat(TK_OP, ",");
      continue;
    }
    break;
  }
  p_eat(TK_OP, ";");
  return new_vardecl_s(decls, ndecls);
}

int get_prec(int *op) {
  if (my_strcmp(op, "||") == 0) { return 1; }
  if (my_strcmp(op, "&&") == 0) { return 2; }
  if (my_strcmp(op, "|") == 0) { return 3; }
  if (my_strcmp(op, "^") == 0) { return 4; }
  if (my_strcmp(op, "&") == 0) { return 5; }
  if (my_strcmp(op, "==") == 0 || my_strcmp(op, "!=") == 0) { return 6; }
  if (my_strcmp(op, "<") == 0 || my_strcmp(op, "<=") == 0 ||
      my_strcmp(op, ">") == 0 || my_strcmp(op, ">=") == 0) { return 7; }
  if (my_strcmp(op, "<<") == 0 || my_strcmp(op, ">>") == 0) { return 8; }
  if (my_strcmp(op, "+") == 0 || my_strcmp(op, "-") == 0) { return 9; }
  if (my_strcmp(op, "*") == 0 || my_strcmp(op, "/") == 0 || my_strcmp(op, "%") == 0) { return 10; }
  return 0 - 1;
}

struct Expr *parse_expr(int min_prec) {
  struct Expr *e = parse_unary();
  struct Expr *rhs = 0;

  while (1) {
    int k = tok[cur_pos].kind;
    int *v = tok[cur_pos].val;

    if (k == TK_OP && my_strcmp(v, "=") == 0 && min_prec <= 0) {
      p_eat(TK_OP, "=");
      rhs = parse_expr(0);
      e = new_assign(e, rhs);
      continue;
    }

    // Compound assignment: +=, -=, *=, /=, %=, &=, |=, ^=
    if (k == TK_OP && min_prec <= 0) {
      int *cop = 0;
      if (my_strcmp(v, "+=") == 0) { cop = "+"; }
      else if (my_strcmp(v, "-=") == 0) { cop = "-"; }
      else if (my_strcmp(v, "*=") == 0) { cop = "*"; }
      else if (my_strcmp(v, "/=") == 0) { cop = "/"; }
      else if (my_strcmp(v, "%=") == 0) { cop = "%"; }
      else if (my_strcmp(v, "&=") == 0) { cop = "&"; }
      else if (my_strcmp(v, "|=") == 0) { cop = "|"; }
      else if (my_strcmp(v, "^=") == 0) { cop = "^"; }
      else if (my_strcmp(v, "<<=") == 0) { cop = "<<"; }
      else if (my_strcmp(v, ">>=") == 0) { cop = ">>"; }
      if (cop != 0) {
        p_eat(TK_OP, 0);
        rhs = parse_expr(0);
        e = new_assign(e, new_binary(cop, e, rhs));
        continue;
      }
    }

    // Comma operator (lowest precedence, only in expression-statement context)
    if (k == TK_OP && my_strcmp(v, ",") == 0 && min_prec < 0) {
      p_eat(TK_OP, ",");
      rhs = parse_expr(0);
      e = new_binary(",", e, rhs);
      continue;
    }

    // Ternary
    if (k == TK_OP && my_strcmp(v, "?") == 0 && min_prec <= 0) {
      p_eat(TK_OP, "?");
      // GNU extension: x ?: y (Elvis operator) — use condition as true branch
      if (p_match(TK_OP, ":")) {
        p_eat(TK_OP, ":");
        e = new_ternary(e, e, parse_expr(0));
        continue;
      }
      rhs = parse_expr(0);
      // Handle comma operator in ternary true-branch
      while (p_match(TK_OP, ",")) {
        p_eat(TK_OP, ",");
        struct Expr *comma_rhs = parse_expr(0);
        rhs = new_binary(",", rhs, comma_rhs);
      }
      p_eat(TK_OP, ":");
      e = new_ternary(e, rhs, parse_expr(0));
      continue;
    }

    if (k != TK_OP) { break; }
    int prec = get_prec(v);
    if (prec < 0 || prec < min_prec) { break; }

    int *op = my_strdup(v);
    p_eat(TK_OP, 0);
    rhs = parse_expr(prec + 1);
    e = new_binary(op, e, rhs);
  }

  return e;
}

int is_type_keyword(int *s) {
  if (my_strcmp(s, "int") == 0) { return 1; }
  if (my_strcmp(s, "char") == 0) { return 1; }
  if (my_strcmp(s, "void") == 0) { return 1; }
  if (my_strcmp(s, "struct") == 0) { return 1; }
  if (my_strcmp(s, "unsigned") == 0) { return 1; }
  if (my_strcmp(s, "signed") == 0) { return 1; }
  if (my_strcmp(s, "__signed__") == 0) { return 1; }
  if (my_strcmp(s, "long") == 0) { return 1; }
  if (my_strcmp(s, "short") == 0) { return 1; }
  if (my_strcmp(s, "const") == 0) { return 1; }
  if (my_strcmp(s, "volatile") == 0) { return 1; }
  if (my_strcmp(s, "enum") == 0) { return 1; }
  if (my_strcmp(s, "_Bool") == 0) { return 1; }
  if (my_strcmp(s, "union") == 0) { return 1; }
  if (my_strcmp(s, "double") == 0) { return 1; }
  if (my_strcmp(s, "float") == 0) { return 1; }
  if (my_strcmp(s, "__typeof__") == 0) { return 1; }
  if (my_strcmp(s, "typeof") == 0) { return 1; }
  if (my_strcmp(s, "__typeof") == 0) { return 1; }
  return 0;
}

struct Expr *parse_unary() {
  struct Expr *operand = 0;
  struct Expr *e = 0;
  int sz_depth = 0;
  int cast_saved = 0;

  // Pre-increment/decrement
  if (p_match(TK_OP, "++")) {
    p_eat(TK_OP, "++");
    operand = parse_unary();
    return new_assign(operand, new_binary("+", operand, new_num(1)));
  }
  if (p_match(TK_OP, "--")) {
    p_eat(TK_OP, "--");
    operand = parse_unary();
    return new_assign(operand, new_binary("-", operand, new_num(1)));
  }

  // __alignof__ / __alignof / _Alignof — treat as sizeof but always return 8
  if (p_match(TK_KW, "__alignof__") || p_match(TK_KW, "__alignof") || p_match(TK_KW, "_Alignof")) {
    if (p_match(TK_KW, "__alignof__")) { p_eat(TK_KW, "__alignof__"); }
    else if (p_match(TK_KW, "__alignof")) { p_eat(TK_KW, "__alignof"); }
    else { p_eat(TK_KW, "_Alignof"); }
    if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      // Skip type or expression inside parens
      int ao_depth = 1;
      while (cur_pos < ntokens && ao_depth > 0) {
        if (p_match(TK_OP, "(")) { ao_depth++; }
        else if (p_match(TK_OP, ")")) { ao_depth--; }
        cur_pos++;
      }
    } else {
      parse_unary();
    }
    return new_num(8);
  }

  // sizeof
  if (p_match(TK_KW, "sizeof")) {
    p_eat(TK_KW, "sizeof");
    int sz = 8;
    if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      if (tok[cur_pos].kind == TK_KW && is_type_keyword(tok[cur_pos].val)) {
        int is_char_type = p_match(TK_KW, "char");
        int is_short_type = p_match(TK_KW, "short");
        int is_float_type = p_match(TK_KW, "float");
        int is_double_type = p_match(TK_KW, "double");
        int *sz_stype = parse_base_type();
        int is_long_type = last_type_is_long;
        int sz_is_ptr = 0;
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); sz_is_ptr = 1; }
        if (sz_is_ptr) {
          sz = 8;
        } else if (is_char_type && sz_stype == 0) {
          sz = 1;
        } else if (sz_stype != 0) {
          sz = p_sizeof_struct(sz_stype);
        } else {
          if (is_short_type) { sz = 2; }
          else if (is_long_type || is_double_type) { sz = 8; }
          else if (is_float_type) { sz = 4; }
          else { sz = 4; }
        }
        // Check for array dimension
        if (p_match(TK_OP, "[")) {
          p_eat(TK_OP, "[");
          int arr_n = my_atoi(p_eat(TK_NUM, 0));
          p_eat(TK_OP, "]");
          sz = arr_n * sz;
        }
      } else if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) {
        // Typedef name — resolve to struct type and look up size
        int *td_st = find_typedef(tok[cur_pos].val);
        parse_base_type();
        int td_is_ptr = 0;
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); td_is_ptr = 1; }
        if (td_is_ptr) {
          sz = 8;
        } else if (td_st != 0) {
          sz = p_sizeof_struct(td_st);
        } else {
          // Primitive typedef: check base type
          int tdc = td_lookup_is_char(tok[cur_pos - 1].val);
          if (tdc) { sz = 1; }
          else if (last_type_is_short) { sz = 2; }
          else if (last_type_is_long) { sz = 8; }
          else { sz = 4; }  // default: int
        }
      } else {
        // Check if it's a variable with a known struct type or array
        if (tok[cur_pos].kind == TK_ID) {
          int *sz_vname = tok[cur_pos].val;
          int *sz_vstype = find_lv_stype(sz_vname);
          int sz_elem = 4;
          sz = 4;
          int sz_isptr = find_lv_isptr(sz_vname);
          if (sz_isptr == 0) { sz_isptr = find_glv_isptr(sz_vname); }
          if (find_lv_is_char(sz_vname) || find_glv_is_char(sz_vname)) { sz_elem = 1; sz = 1; }
          if (find_lv_is_short(sz_vname) || find_glv_is_short(sz_vname)) { sz_elem = 2; sz = 2; }
          if (find_lv_is_long(sz_vname) || find_glv_is_long(sz_vname)) { sz_elem = 8; sz = 8; }
          if (sz_vstype == 0) { sz_vstype = find_glv_stype(sz_vname); }
          // Check for ->field or .field access: sizeof(var->field) or sizeof(var.field)
          int has_field = 0;
          if (cur_pos + 2 < ntokens && tok[cur_pos + 1].kind == TK_OP &&
              (my_strcmp(tok[cur_pos + 1].val, "->") == 0 || my_strcmp(tok[cur_pos + 1].val, ".") == 0) &&
              tok[cur_pos + 2].kind == TK_ID && sz_vstype != 0) {
            sz = p_sizeof_field(sz_vstype, tok[cur_pos + 2].val);
            has_field = 1;
          } else if (sz_isptr) {
            sz = 8; // sizeof(pointer_var) = pointer size
          } else if (sz_vstype != 0) {
            sz_elem = p_sizeof_struct(sz_vstype);
            sz = sz_elem;
          }
          if (has_field == 0) {
            // Check if variable is an array (but not if indexed: arr[0] is element-sized)
            int sz_arr = find_lv_arrsize(sz_vname);
            if (sz_arr < 0) { sz_arr = find_glv_arrsize(sz_vname); }
            int sz_is_indexed = (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "[") == 0);
            if (sz_arr > 0 && sz_is_indexed == 0) { sz = sz_arr * sz_elem; }
          }
        }
        // Check sizeof(*varname) — dereference of array returns element size
        if (tok[cur_pos].kind == TK_OP && my_strcmp(tok[cur_pos].val, "*") == 0 &&
            cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_ID) {
          int *deref_name = tok[cur_pos + 1].val;
          int *deref_stype = find_lv_stype(deref_name);
          if (deref_stype == 0) { deref_stype = find_glv_stype(deref_name); }
          if (deref_stype != 0) {
            sz = p_sizeof_struct(deref_stype);
          }
          {
            int deref_is_char = find_lv_is_char(deref_name) || find_glv_is_char(deref_name);
            int deref_isptr = find_lv_isptr(deref_name);
            if (deref_isptr == 0) { deref_isptr = find_glv_isptr(deref_name); }
            if (deref_is_char && deref_isptr < 2) { sz = 1; }
          }
        }
        parse_expr(0);
      }
      p_eat(TK_OP, ")");
    } else {
      parse_unary();
    }
    return new_num(sz);
  }

  // Type cast: (type)expr — handles funcptr casts like (int (*)(int, int))
  if (p_match(TK_OP, "(")) {
    cast_saved = cur_pos;
    p_eat(TK_OP, "(");
    int is_kw_cast = (tok[cur_pos].kind == TK_KW && is_type_keyword(tok[cur_pos].val));
    int is_td_cast = (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val));
    if (is_kw_cast || is_td_cast) {
      // Check for compound literal: (struct Name){...}
      int *cl_stype = 0;
      int cast_to_float = 0;
      int cast_to_int = 0;
      if (is_td_cast) {
        cl_stype = find_typedef(tok[cur_pos].val);
      } else if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) {
        cur_pos = cur_pos + 1;
        if (tok[cur_pos].kind == TK_ID) {
          cl_stype = my_strdup(tok[cur_pos].val);
          cur_pos = cur_pos + 1;
        }
      } else if (p_match(TK_KW, "float") || p_match(TK_KW, "double")) {
        cast_to_float = 1;
      } else if (p_match(TK_KW, "int") || p_match(TK_KW, "long") || p_match(TK_KW, "short") || p_match(TK_KW, "char") ||
                 p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") || p_match(TK_KW, "_Bool")) {
        // Detect specific narrow integer type for truncation/sign-extension
        // Scan cast tokens to find short/char and unsigned
        int ct_is_unsigned = 0;
        int ct_is_short = 0;
        int ct_is_char = 0;
        int ct_scan = cur_pos; // p_match didn't consume, cur_pos is at first type keyword
        while (ct_scan < ntokens && tok[ct_scan].kind == TK_KW) {
          if (my_strcmp(tok[ct_scan].val, "unsigned") == 0) { ct_is_unsigned = 1; }
          if (my_strcmp(tok[ct_scan].val, "short") == 0) { ct_is_short = 1; }
          if (my_strcmp(tok[ct_scan].val, "char") == 0) { ct_is_char = 1; }
          ct_scan = ct_scan + 1;
        }
        // Check if there's a '*' after type keywords — if so, it's a pointer cast (no truncation)
        int ct_is_ptr = 0;
        {
          int ct_p = ct_scan;
          while (ct_p < ntokens && !(tok[ct_p].kind == TK_OP && my_strcmp(tok[ct_p].val, ")") == 0)) {
            if (tok[ct_p].kind == TK_OP && my_strcmp(tok[ct_p].val, "*") == 0) { ct_is_ptr = 1; }
            ct_p = ct_p + 1;
          }
        }
        if (ct_is_ptr) { cast_to_int = 2; } // pointer cast — no truncation
        else if (ct_is_char && ct_is_unsigned) { cast_to_int = 4; } // (unsigned char) -> uxtb
        else if (ct_is_char) { cast_to_int = 3; } // (char) -> sxtb
        else if (ct_is_short && ct_is_unsigned) { cast_to_int = 6; } // (unsigned short) -> uxth
        else if (ct_is_short) { cast_to_int = 5; } // (short) -> sxth
        else if (ct_is_unsigned) { cast_to_int = 7; } // (unsigned int/long) — marks unsigned for comparisons
        else { cast_to_int = 2; } // regular int/long cast
      }
      // Skip the rest of the type, handling nested parens for funcptr casts
      int cast_depth = 1;
      while (cast_depth > 0) {
        if (p_match(TK_OP, "(")) { cast_depth = cast_depth + 1; }
        if (p_match(TK_OP, ")")) { cast_depth = cast_depth - 1; }
        if (cast_depth > 0) { cur_pos = cur_pos + 1; }
      }
      p_eat(TK_OP, ")");
      // Check for compound literal: (struct/union type){...}
      if (cl_stype != 0 && p_match(TK_OP, "{")) {
        struct Expr *cl_init = parse_init_list(cl_stype);
        struct Expr *cl_e = my_malloc(80);
        cl_e->kind = ND_COMPOUND_LIT;
        cl_e->sval = cl_stype;
        cl_e->left = cl_init;
        e = cl_e;
      } else if ((cast_to_int || cast_to_float) && p_match(TK_OP, "{")) {
        // Scalar/array compound literal: (int){0}, (int []){1,2,3}, (char []){...}
        struct Expr *cl_init = parse_init_list(0);
        // Scalar compound literal: (int){expr} — just return the inner value
        if (cl_init->nargs == 1) {
          e = cl_init->args[0];
        } else {
          // Multi-element: treat as compound literal with no struct type
          struct Expr *cl_e = my_malloc(80);
          cl_e->kind = ND_COMPOUND_LIT;
          cl_e->sval = 0;
          cl_e->left = cl_init;
          e = cl_e;
        }
      } else {
        struct Expr *cast_inner = parse_unary();
        struct Expr *cast_e = my_malloc(80);
        cast_e->kind = ND_CAST;
        cast_e->left = cast_inner;
        cast_e->sval = cl_stype;  // Store cast target struct type (or 0)
        if (cast_to_float) { cast_e->ival = 1; }
        else if (cast_to_int) { cast_e->ival = cast_to_int; }
        e = cast_e;
      }
    } else {
      cur_pos = cast_saved;
    }
  }

  if (e != 0) {
    // Already parsed (compound literal or cast) — skip to postfix
  } else if (p_match(TK_OP, "+")) {
    p_eat(TK_OP, "+");
    return parse_unary();
  } else if (p_match(TK_OP, "&&") && tok[cur_pos + 1].kind == TK_ID) {
    // Labels-as-values: &&label
    p_eat(TK_OP, "&&");
    struct Expr *la = my_malloc(72);
    la->kind = ND_LABEL_ADDR;
    la->sval = my_strdup(p_eat(TK_ID, 0));
    return la;
  } else if (p_match(TK_OP, "-") || p_match(TK_OP, "!") || p_match(TK_OP, "*") || p_match(TK_OP, "&") || p_match(TK_OP, "~")) {
    int unary_op_ch = __read_byte(tok[cur_pos].val, 0);
    p_eat(TK_OP, 0);
    operand = parse_unary();
    return new_unary(unary_op_ch, operand);
  } else {
    return parse_primary();
  }
  // Postfix operators on compound literals / casts
  while (p_match(TK_OP, "[") || p_match(TK_OP, ".") || p_match(TK_OP, "->")) {
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      struct Expr *idx = parse_expr(0);
      p_eat(TK_OP, "]");
      e = new_index(e, idx);
    } else if (p_match(TK_OP, ".")) {
      p_eat(TK_OP, ".");
      int *fld = my_strdup(p_eat(TK_ID, 0));
      int *st = resolve_stype(e);
      if (st == 0) { st = "unknown"; }
      e = new_field(e, fld, st);
    } else if (p_match(TK_OP, "->")) {
      p_eat(TK_OP, "->");
      int *fld = my_strdup(p_eat(TK_ID, 0));
      int *st = resolve_stype(e);
      if (st == 0) { st = "unknown"; }
      e = new_arrow(e, fld, st);
    }
  }
  return e;
}

int find_enum_const(int *name) {
  int i = 0;
  while (i < nec) {
    if (my_strcmp(ec_table[i].name, name) == 0) {
      return ec_table[i].val;
    }
    i++;
  }
  return 0 - 1;
}

int has_enum_const(int *name) {
  for (int i = 0; i < nec; i++) {
    if (my_strcmp(ec_table[i].name, name) == 0) {
      return 1;
    }
  }
  return 0;
}

int add_enum_const(int *name, int val) {
  if (nec >= MAX_ENUMS) { printf("cc: OVERFLOW ec_table nec=%d name=%s\n", nec, name); fflush(0); }
  ec_table[nec].name = my_strdup(name);
  ec_table[nec].val = val;
  nec++;
  return 0;
}

struct Expr *parse_primary() {
  int k = tok[cur_pos].kind;
  int *v = tok[cur_pos].val;
  struct Expr *e;
  int *field = 0;
  int *st = 0;

  if (k == TK_NUM) {
    p_eat(TK_NUM, 0);
    if (is_float_literal(v)) {
      int flt_bits = str_to_double_bits(v);
      e = new_num(flt_bits);
      e->nargs = 1; // mark as float literal
    } else {
      e = new_num(my_atoi(v));
    }
  } else if (k == TK_STR) {
    p_eat(TK_STR, 0);
    e = new_strlit(v);
  } else if (k == TK_ID) {
    int *name = my_strdup(p_eat(TK_ID, 0));
    // __func__ / __FUNCTION__ => string literal with function name
    if (my_strcmp(name, "__func__") == 0 || my_strcmp(name, "__FUNCTION__") == 0) {
      return new_strlit("func");
    }
    // __builtin_offsetof(struct type, member)
    if (my_strcmp(name, "__builtin_offsetof") == 0) {
      p_eat(TK_OP, "(");
      // Skip type: struct/union Name or typedef
      if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) { cur_pos++; }
      int *ofs_stype = 0;
      if (tok[cur_pos].kind == TK_ID) { ofs_stype = my_strdup(tok[cur_pos].val); cur_pos++; }
      p_eat(TK_OP, ",");
      int *ofs_field = my_strdup(p_eat(TK_ID, 0));
      p_eat(TK_OP, ")");
      // Look up proper byte offset
      int ofs_val = 0;
      if (ofs_stype != 0) {
        ofs_val = p_field_byte_offset(ofs_stype, ofs_field);
      }
      e = new_num(ofs_val);
    }
    // __builtin_va_arg(ap, type) => dereference ap and advance
    else if (my_strcmp(name, "__builtin_va_arg") == 0) {
      p_eat(TK_OP, "(");
      struct Expr *va_ap = parse_expr(0);
      p_eat(TK_OP, ",");
      // Skip type argument
      int va_depth = 0;
      while (1) {
        if (p_match(TK_OP, "(")) { va_depth++; cur_pos++; }
        else if (p_match(TK_OP, ")")) {
          if (va_depth == 0) break;
          va_depth--; cur_pos++;
        }
        else { cur_pos++; }
      }
      p_eat(TK_OP, ")");
      // Treat as a call so codegen can handle it
      struct Expr **va_args = my_malloc(8 * 8);
      va_args[0] = va_ap;
      e = new_call("__builtin_va_arg", va_args, 1);
    }
    // __builtin_va_end(ap) => no-op
    else if (my_strcmp(name, "__builtin_va_end") == 0) {
      p_eat(TK_OP, "(");
      parse_expr(0); // consume but ignore
      p_eat(TK_OP, ")");
      e = new_num(0);
    }
    // __builtin_va_copy(dest, src) => dest = src
    else if (my_strcmp(name, "__builtin_va_copy") == 0) {
      p_eat(TK_OP, "(");
      struct Expr *va_dst = parse_expr(0);
      p_eat(TK_OP, ",");
      struct Expr *va_src = parse_expr(0);
      p_eat(TK_OP, ")");
      e = new_assign(va_dst, va_src);
    }
    // __builtin_constant_p(expr) => always 0 at parse time (enables DCE)
    else if (my_strcmp(name, "__builtin_constant_p") == 0) {
      p_eat(TK_OP, "(");
      parse_expr(0); // consume but ignore
      p_eat(TK_OP, ")");
      e = new_num(0);
    }
    // __builtin_expect(expr, val) => just returns expr (branch prediction hint)
    else if (my_strcmp(name, "__builtin_expect") == 0) {
      p_eat(TK_OP, "(");
      e = parse_expr(0);
      p_eat(TK_OP, ",");
      parse_expr(0); // consume and ignore expected value
      p_eat(TK_OP, ")");
    }
    // __builtin_choose_expr(const_expr, expr1, expr2) => expr1 if const_expr != 0, else expr2
    else if (my_strcmp(name, "__builtin_choose_expr") == 0) {
      p_eat(TK_OP, "(");
      struct Expr *cond = parse_expr(0);
      p_eat(TK_OP, ",");
      struct Expr *expr1 = parse_expr(0);
      p_eat(TK_OP, ",");
      struct Expr *expr2 = parse_expr(0);
      p_eat(TK_OP, ")");
      // Evaluate cond at compile time; if it's a constant != 0, pick expr1, else expr2
      // Handle simple constant folding: !const, const
      int choose_val = 0;
      if (cond->kind == ND_NUM) { choose_val = cond->ival != 0; }
      else if (cond->kind == ND_UNARY && cond->ival == '!' && cond->left->kind == ND_NUM) { choose_val = cond->left->ival == 0; }
      if (choose_val) { e = expr1; }
      else { e = expr2; }
    }
    // Check if it's an enum constant (but local variables shadow enums)
    else if (has_enum_const(name) && !p_match(TK_OP, "(")) {
      int is_local = 0;
      int li = nlv - 1;
      while (li >= 0) { if (my_strcmp(lv[li].name, name) == 0) { is_local = 1; break; } li = li - 1; }
      if (is_local) { e = new_var(name); }
      else { e = new_num(find_enum_const(name)); }
    } else if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      struct Expr **args = my_malloc(64 * 8);
      int nargs = 0;
      if (!p_match(TK_OP, ")")) {
        while (1) {
          args[nargs] = parse_expr(0);
          nargs++;
          if (p_match(TK_OP, ",")) {
            p_eat(TK_OP, ",");
            continue;
          }
          break;
        }
      }
      p_eat(TK_OP, ")");
      e = new_call(name, args, nargs);
    } else {
      e = new_var(name);
    }
  } else if (p_match(TK_OP, "(") && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "{") == 0) {
    // Statement expression: ({ stmt; stmt; expr; })
    p_eat(TK_OP, "(");
    int se_blen = 0;
    struct Stmt **se_body = parse_block(&se_blen);
    p_eat(TK_OP, ")");
    struct Stmt *se_blk = my_malloc(144);
    se_blk->kind = ST_BLOCK;
    se_blk->body = se_body;
    se_blk->nbody = se_blen;
    e = my_malloc(80);
    e->kind = ND_STMT_EXPR;
    e->left = se_blk; // abuse left as Stmt* pointer
  } else if (p_match(TK_OP, "(")) {
    // Check if this is a cast: (type)expr
    int cast_saved = cur_pos;
    p_eat(TK_OP, "(");
    int is_cast = 0;
    if (tok[cur_pos].kind == TK_KW && (
        p_match(TK_KW, "int") || p_match(TK_KW, "char") || p_match(TK_KW, "void") ||
        p_match(TK_KW, "short") || p_match(TK_KW, "long") || p_match(TK_KW, "unsigned") ||
        p_match(TK_KW, "signed") || p_match(TK_KW, "const") || p_match(TK_KW, "volatile") ||
        p_match(TK_KW, "struct") || p_match(TK_KW, "union") || p_match(TK_KW, "enum") ||
        p_match(TK_KW, "_Bool"))) {
      is_cast = 1;
    } else if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) {
      is_cast = 1;
    }
    if (is_cast) {
      // Skip type and pointer stars until )
      int cd = 0;
      while (1) {
        if (p_match(TK_OP, "(")) { cd++; }
        else if (p_match(TK_OP, ")")) { if (cd == 0) break; cd--; }
        cur_pos++;
      }
      p_eat(TK_OP, ")");
      // Parse the operand as unary — cast is treated as identity (all 8 bytes)
      e = parse_expr(140);
    } else {
      cur_pos = cast_saved + 1; // back to after (
      e = parse_expr(-1);
      p_eat(TK_OP, ")");
    }
  } else {
    printf("Unexpected token '%s' at %d tok#=%d k=%d (cur_pos=%d, prev_tok=%s)\n", v, tok[cur_pos].pos, cur_pos, tok[cur_pos].kind, cur_pos, cur_pos > 0 ? tok[cur_pos - 1].val : "?");
    { int dd = cur_pos - 10; if (dd < 0) { dd = 0; } while (dd < cur_pos + 5 && dd < ntokens) { printf("  tok[%d] k=%d '%s'\n", dd, tok[dd].kind, tok[dd].val); dd++; } }
    exit(1);
    return 0;
  }

  // Postfix: [], ., ->, ++, --, ()
  while (p_match(TK_OP, "[") || p_match(TK_OP, ".") || p_match(TK_OP, "->") ||
         p_match(TK_OP, "++") || p_match(TK_OP, "--") || p_match(TK_OP, "(")) {
    // Postfix function call: expr(args) — for indirect calls through non-identifiers
    if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      struct Expr **ic_args = my_malloc(64 * 8);
      int ic_nargs = 0;
      if (!p_match(TK_OP, ")")) {
        while (1) {
          ic_args[ic_nargs] = parse_expr(0);
          ic_nargs++;
          if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); continue; }
          break;
        }
      }
      p_eat(TK_OP, ")");
      if (e->kind == ND_VAR) {
        e = new_call(e->sval, ic_args, ic_nargs);
      } else {
        // Indirect call: prepend function expression as first arg
        struct Expr **new_args = my_malloc(64 * 8);
        int na = 0;
        new_args[0] = e;
        na = 1;
        for (int ai = 0; ai < ic_nargs; ai++) {
          new_args[na] = ic_args[ai];
          na++;
        }
        e = new_call("__indirect_call", new_args, na);
      }
      continue;
    }
    if (p_match(TK_OP, "++")) {
      p_eat(TK_OP, "++");
      e = new_postinc(e);
      continue;
    }
    if (p_match(TK_OP, "--")) {
      p_eat(TK_OP, "--");
      e = new_postdec(e);
      continue;
    }
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      struct Expr *idx = parse_expr(0);
      p_eat(TK_OP, "]");
      e = new_index(e, idx);
    } else if (p_match(TK_OP, ".")) {
      p_eat(TK_OP, ".");
      // Handle floating-point literals: 0.0, 1.5e10, etc. — treat as integer 0
      if (e->kind == ND_NUM && tok[cur_pos].kind == TK_NUM) {
        cur_pos++; // skip decimal part
        // Skip exponent part if present (e.g., 1.0e10)
        if (tok[cur_pos].kind == TK_ID && (__read_byte(tok[cur_pos].val, 0) == 'e' || __read_byte(tok[cur_pos].val, 0) == 'E')) {
          cur_pos++;
        }
        // e is already the integer part, keep it
        continue;
      }
      field = my_strdup(p_eat(TK_ID, 0));
      st = resolve_stype(e);
      if (st == 0) {
        st = "unknown";
      }
      e = new_field(e, field, st);
    } else {
      p_eat(TK_OP, "->");
      field = my_strdup(p_eat(TK_ID, 0));
      st = resolve_stype(e);
      if (st == 0) { st = "unknown"; }
      e = new_arrow(e, field, st);
    }
  }
  return e;
}

struct Stmt *parse_stmt() {
  struct Expr *e = 0;
  struct Expr *cond = 0;
  struct Expr *post = 0;
  struct Stmt *init = 0;
  struct Stmt **body = 0;
  struct Stmt **then_body = 0;
  struct Stmt **else_body = 0;
  int blen = 0;
  int then_len = 0;
  int else_len = 0;
  int *ps_label = 0;
  struct Stmt *following = 0;
  int *cv = 0;
  struct Stmt ***cb = 0;
  int *cnb = 0;
  int nc = 0;
  struct Stmt **db = 0;
  int ndb = 0;
  int sw_neg = 0;
  int sw_cval = 0;
  int *sw_cname = 0;
  struct Stmt **sw_cstmts = 0;
  int sw_cns = 0;
  struct Stmt **sw_dstmts = 0;
  int sw_dns = 0;

  // Skip __extension__ at statement level
  if (p_match(TK_KW, "__extension__")) { p_eat(TK_KW, "__extension__"); }

  // Local enum definition: enum { A = 1, B = 2 };
  if (p_match(TK_KW, "enum")) {
    int sv_enum = cur_pos;
    cur_pos++; // skip enum
    if (p_match(TK_ID, 0)) { cur_pos++; } // skip optional tag
    if (p_match(TK_OP, "{")) {
      cur_pos = sv_enum;
      parse_enum_def();
      return new_expr_s(new_num(0));
    }
    cur_pos = sv_enum;
  }

  // Anonymous block
  if (p_match(TK_OP, "{")) {
    struct Stmt *bs = my_malloc(144);
    bs->kind = ST_BLOCK;
    bs->body = parse_block(&blen);
    bs->nbody = blen;
    return bs;
  }

  // Empty statement
  if (p_match(TK_OP, ";")) {
    p_eat(TK_OP, ";");
    return new_expr_s(new_num(0));
  }

  // case/default inside nested blocks within switch body
  if (p_match(TK_KW, "case")) {
    p_eat(TK_KW, "case");
    parse_const_expr();
    // GCC extension: case A ... B: (range)
    if (p_match(TK_OP, ".") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, ".") == 0) {
      cur_pos += 3; // skip ...
      parse_const_expr(); // skip upper bound
    }
    p_eat(TK_OP, ":");
    return parse_stmt();
  }
  if (p_match(TK_KW, "default")) {
    p_eat(TK_KW, "default");
    p_eat(TK_OP, ":");
    return parse_stmt();
  }

  if (p_match(TK_KW, "return")) {
    p_eat(TK_KW, "return");
    if (p_match(TK_OP, ";")) {
      p_eat(TK_OP, ";");
      return new_return_s(new_num(0));
    }
    e = parse_expr(0);
    p_eat(TK_OP, ";");
    return new_return_s(e);
  }

  if (p_match(TK_KW, "if")) {
    p_eat(TK_KW, "if");
    p_eat(TK_OP, "(");
    cond = parse_expr(0);
    p_eat(TK_OP, ")");
    then_len = 0;
    then_body = parse_block_or_stmt(&then_len);
    else_body = 0;
    else_len = 0;
    if (p_match(TK_KW, "else")) {
      p_eat(TK_KW, "else");
      if (p_match(TK_KW, "if")) {
        else_body = my_malloc(8);
        else_body[0] = parse_stmt();
        else_len = 1;
      } else {
        else_body = parse_block_or_stmt(&else_len);
      }
    }
    return new_if_s(cond, then_body, then_len, else_body, else_len);
  }

  if (p_match(TK_KW, "while")) {
    p_eat(TK_KW, "while");
    p_eat(TK_OP, "(");
    cond = parse_expr(0);
    p_eat(TK_OP, ")");
    blen = 0;
    body = parse_block_or_stmt(&blen);
    return new_while_s(cond, body, blen);
  }

  if (p_match(TK_KW, "for")) {
    p_eat(TK_KW, "for");
    p_eat(TK_OP, "(");

    init = 0;
    if (p_match(TK_KW, "int") || p_match(TK_KW, "struct") || p_match(TK_KW, "union") ||
        p_match(TK_KW, "char") || p_match(TK_KW, "void") ||
        p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") ||
        p_match(TK_KW, "long") || p_match(TK_KW, "short") ||
        p_match(TK_KW, "const") || p_match(TK_KW, "volatile") ||
        p_match(TK_KW, "register") || p_match(TK_KW, "enum") ||
        p_match(TK_KW, "_Bool") ||
        p_match(TK_KW, "double") || p_match(TK_KW, "float")) {
      init = parse_vardecl_stmt(0);
    } else if (p_match(TK_OP, ";")) {
      p_eat(TK_OP, ";");
    } else {
      e = parse_expr(-1);
      p_eat(TK_OP, ";");
      init = new_expr_s(e);
    }

    cond = 0;
    if (!p_match(TK_OP, ";")) {
      cond = parse_expr(-1);
    }
    p_eat(TK_OP, ";");

    post = 0;
    if (!p_match(TK_OP, ")")) {
      post = parse_expr(-1);
    }
    p_eat(TK_OP, ")");

    blen = 0;
    body = parse_block_or_stmt(&blen);
    return new_for_s(init, cond, post, body, blen);
  }

  if (p_match(TK_KW, "break")) {
    p_eat(TK_KW, "break");
    p_eat(TK_OP, ";");
    return new_break_s();
  }

  if (p_match(TK_KW, "continue")) {
    p_eat(TK_KW, "continue");
    p_eat(TK_OP, ";");
    return new_continue_s();
  }

  // do...while
  if (p_match(TK_KW, "do")) {
    p_eat(TK_KW, "do");
    blen = 0;
    body = parse_block_or_stmt(&blen);
    p_eat(TK_KW, "while");
    p_eat(TK_OP, "(");
    cond = parse_expr(0);
    p_eat(TK_OP, ")");
    p_eat(TK_OP, ";");
    return new_dowhile_s(cond, body, blen);
  }

  // goto
  if (p_match(TK_KW, "goto")) {
    p_eat(TK_KW, "goto");
    if (p_match(TK_OP, "*")) {
      // Computed goto: goto *expr;
      p_eat(TK_OP, "*");
      struct Stmt *cgs = my_malloc(144);
      cgs->kind = ST_COMPUTED_GOTO;
      cgs->expr = parse_expr(0);
      p_eat(TK_OP, ";");
      return cgs;
    }
    ps_label = my_strdup(p_eat(TK_ID, 0));
    p_eat(TK_OP, ";");
    return new_goto_s(ps_label);
  }

  // switch
  if (p_match(TK_KW, "switch")) {
    p_eat(TK_KW, "switch");
    p_eat(TK_OP, "(");
    cond = parse_expr(0);
    p_eat(TK_OP, ")");
    p_eat(TK_OP, "{");
    cv = my_malloc(1024 * 8);
    cb = my_malloc(1024 * 8);
    cnb = my_malloc(1024 * 8);
    nc = 0;
    db = 0;
    ndb = 0;

    // Collect pre-case declarations (e.g., YYMINORTYPE yylhsminor;)
    struct Stmt **sw_pre = my_malloc(64 * 8);
    int sw_npre = 0;
    while (!p_match(TK_OP, "}") && !p_match(TK_KW, "case") && !p_match(TK_KW, "default")) {
      sw_pre[sw_npre] = parse_stmt();
      sw_npre++;
    }

    while (!p_match(TK_OP, "}")) {
      if (p_match(TK_KW, "case")) {
        p_eat(TK_KW, "case");
        sw_cval = parse_const_expr();
        // GCC extension: case A ... B: (range) — use first value only
        if (p_match(TK_OP, ".") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, ".") == 0) {
          cur_pos += 3; // skip ...
          parse_const_expr(); // skip upper bound
        }
        p_eat(TK_OP, ":");
        sw_cstmts = my_malloc(512 * 8);
        sw_cns = 0;
        // Inject pre-case stmts into first case
        if (nc == 0 && sw_npre > 0) {
          for (int pi = 0; pi < sw_npre; pi++) {
            sw_cstmts[sw_cns] = sw_pre[pi];
            sw_cns++;
          }
        }
        while (!p_match(TK_KW, "case") && !p_match(TK_KW, "default") && !p_match(TK_OP, "}")) {
          sw_cstmts[sw_cns] = parse_stmt();
          sw_cns++;
        }
        cv[nc] = sw_cval;
        cb[nc] = sw_cstmts;
        cnb[nc] = sw_cns;
        nc++;
      } else if (p_match(TK_KW, "default")) {
        p_eat(TK_KW, "default");
        p_eat(TK_OP, ":");
        sw_dstmts = my_malloc(512 * 8);
        sw_dns = 0;
        while (!p_match(TK_KW, "case") && !p_match(TK_KW, "default") && !p_match(TK_OP, "}")) {
          sw_dstmts[sw_dns] = parse_stmt();
          sw_dns++;
        }
        db = sw_dstmts;
        ndb = sw_dns;
      } else {
        // Stray statements between cases — attach to current case
        parse_stmt();
      }
    }
    p_eat(TK_OP, "}");
    return new_switch_s(cond, cv, cb, cnb, nc, db, ndb);
  }

  // typedef inside function body — skip but register the name
  if (p_match(TK_KW, "typedef")) {
    p_eat(TK_KW, "typedef");
    // Find typedef name: scan for (*ID) pattern (funcptr) or last ID before ;
    int *local_td_name = 0;
    int ti = cur_pos;
    while (ti < ntokens && !(tok[ti].kind == TK_OP && my_strcmp(tok[ti].val, ";") == 0)) {
      if (tok[ti].kind == TK_OP && my_strcmp(tok[ti].val, "(") == 0 &&
          ti + 1 < ntokens && tok[ti+1].kind == TK_OP && my_strcmp(tok[ti+1].val, "*") == 0 &&
          ti + 2 < ntokens && tok[ti+2].kind == TK_ID) {
        local_td_name = tok[ti+2].val;
      }
      ti++;
    }
    if (local_td_name == 0) {
      ti = cur_pos;
      while (ti < ntokens && !(tok[ti].kind == TK_OP && my_strcmp(tok[ti].val, ";") == 0)) {
        if (tok[ti].kind == TK_ID) { local_td_name = tok[ti].val; }
        ti++;
      }
    }
    if (local_td_name != 0) { add_typedef(local_td_name, 0); }
    while (!p_match(TK_OP, ";") && !p_match(TK_EOF, 0)) { cur_pos++; }
    if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
    return new_expr_s(new_num(0));
  }

  // static before vardecl
  if (p_match(TK_KW, "static")) {
    p_eat(TK_KW, "static");
    return parse_vardecl_stmt(1);
  }

  // extern inside block scope: skip the declaration
  if (p_match(TK_KW, "extern")) {
    while (!p_match(TK_OP, ";") && !p_match(TK_EOF, 0)) { cur_pos++; }
    if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
    return new_expr_s(new_num(0));
  }

  // __attribute__ at start of statement: skip it, then re-parse
  if (p_match(TK_KW, "__attribute__")) {
    while (skip_attribute()) {}
    return parse_stmt();
  }

  // asm/asm volatile statements: skip entirely
  if (p_match(TK_ID, "asm") || p_match(TK_ID, "__asm") || p_match(TK_ID, "__asm__")) {
    cur_pos++; // skip asm keyword
    if (p_match(TK_KW, "volatile") || p_match(TK_KW, "__volatile__") || p_match(TK_KW, "__volatile") || p_match(TK_KW, "inline") || p_match(TK_ID, "goto")) { cur_pos++; }
    // Skip balanced parens
    if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      int asm_depth = 1;
      while (asm_depth > 0 && !p_match(TK_EOF, 0)) {
        if (p_match(TK_OP, "(")) { asm_depth++; }
        if (p_match(TK_OP, ")")) { asm_depth--; }
        if (asm_depth > 0) { cur_pos++; }
      }
      p_eat(TK_OP, ")");
    }
    if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
    return new_expr_s(new_num(0));
  }

  // __label__ declarations (GCC extension): skip
  if (p_match(TK_ID, "__label__")) {
    while (!p_match(TK_OP, ";") && !p_match(TK_EOF, 0)) { cur_pos++; }
    if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
    return new_expr_s(new_num(0));
  }

  // Local function prototype: void func(params); or int func(void);
  // Detect type [*]* name ( ... ) ; pattern and skip it
  if (p_match(TK_KW, "int") || p_match(TK_KW, "char") || p_match(TK_KW, "void") ||
      p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") ||
      p_match(TK_KW, "long") || p_match(TK_KW, "short") ||
      p_match(TK_KW, "_Bool") ||
      p_match(TK_KW, "double") || p_match(TK_KW, "float")) {
    int lp_sv = cur_pos;
    cur_pos++; // skip type keyword
    // skip extra type keywords (unsigned long, etc.)
    while (p_match(TK_KW, "int") || p_match(TK_KW, "long") || p_match(TK_KW, "short") || p_match(TK_KW, "char")) { cur_pos++; }
    while (p_match(TK_OP, "*")) { cur_pos++; }
    skip_qualifiers();
    if (tok[cur_pos].kind == TK_ID && cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "(") == 0) {
      // Could be func proto or func ptr var
      int lp_name = cur_pos;
      cur_pos++; // skip name
      cur_pos++; // skip (
      int lp_depth = 1;
      while (lp_depth > 0 && cur_pos < ntokens) {
        if (p_match(TK_OP, "(")) { lp_depth++; }
        else if (p_match(TK_OP, ")")) { lp_depth--; }
        if (lp_depth > 0) { cur_pos++; }
      }
      cur_pos++; // skip final )
      if (p_match(TK_OP, ";")) {
        p_eat(TK_OP, ";");
        return new_expr_s(new_num(0)); // skip local prototype
      }
    }
    cur_pos = lp_sv;
  }

  // type-keyword variable declarations
  if (p_match(TK_KW, "int") || p_match(TK_KW, "struct") || p_match(TK_KW, "union") ||
      p_match(TK_KW, "char") || p_match(TK_KW, "void") ||
      p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") ||
      p_match(TK_KW, "long") || p_match(TK_KW, "short") ||
      p_match(TK_KW, "const") || p_match(TK_KW, "volatile") ||
      p_match(TK_KW, "register") || p_match(TK_KW, "enum") ||
      p_match(TK_KW, "_Bool") ||
      p_match(TK_KW, "double") || p_match(TK_KW, "float") ||
      p_match(TK_KW, "__typeof__") || p_match(TK_KW, "typeof") || p_match(TK_KW, "__typeof") ||
      (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val))) {
    return parse_vardecl_stmt(0);
  }

  // label: identifier followed by ':'
  if (tok[cur_pos].kind == TK_ID && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, ":") == 0) {
    ps_label = my_strdup(p_eat(TK_ID, 0));
    p_eat(TK_OP, ":");
    following = parse_stmt();
    return new_label_s(ps_label, following);
  }

  e = parse_expr(-1);
  p_eat(TK_OP, ";");
  return new_expr_s(e);
}

struct SDef *parse_struct_or_union_def(int is_union) {
  if (is_union) {
    p_eat(TK_KW, "union");
  } else {
    p_eat(TK_KW, "struct");
  }
  int *name = 0;
  while (skip_attribute()) {}
  if (p_match(TK_ID, 0)) {
    name = my_strdup(p_eat(TK_ID, 0));
  } else {
    // Anonymous struct/union — generate unique name
    name = build_str2("_anon_s_", int_to_str(anon_struct_counter));
    anon_struct_counter++;
  }
  while (skip_attribute()) {}
  p_eat(TK_OP, "{");

  int **fields = my_malloc(512 * 8);
  struct SFieldInfo **finfo = my_malloc(512 * 8);
  int nf = 0;

  while (!p_match(TK_OP, "}")) {
    // Handle inline struct/union definitions: struct Name { ... } *field; or struct { ... } field;
    int *inline_sname = 0;
    if ((p_match(TK_KW, "struct") || p_match(TK_KW, "union")) &&
        ((cur_pos + 2 < ntokens && tok[cur_pos + 1].kind == TK_ID &&
          tok[cur_pos + 2].kind == TK_OP && my_strcmp(tok[cur_pos + 2].val, "{") == 0) ||
         (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "{") == 0))) {
      int iu = p_match(TK_KW, "union");
      struct SDef *inner_sd = parse_struct_or_union_def(iu);
      inline_sname = inner_sd->name;
      inline_sdefs[ninline_sdefs] = inner_sd;
      ninline_sdefs++;
    }
    int *ftype = 0;
    int f_is_char = 0;
    int f_is_short = 0;
    int f_is_long = 0;
    int f_is_unsigned = 0;
    int f_is_funcptr_td = 0;
    int f_td_is_ptr = 0;
    if (inline_sname != 0) {
      // Anonymous struct/union member: struct { ... }; — no field name, inject fields
      // parse_struct_or_union_def already ate the trailing ';', so check if next is not a field name
      int is_anon_member = 0;
      if (p_match(TK_OP, "}") || p_match(TK_KW, "int") || p_match(TK_KW, "char") ||
          p_match(TK_KW, "void") || p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") ||
          p_match(TK_KW, "long") || p_match(TK_KW, "short") || p_match(TK_KW, "struct") ||
          p_match(TK_KW, "union") || p_match(TK_KW, "enum") || p_match(TK_KW, "const") ||
          p_match(TK_KW, "volatile") || p_match(TK_KW, "double") || p_match(TK_KW, "float") ||
          p_match(TK_KW, "_Bool") || p_match(TK_OP, ";") ||
          (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val))) {
        is_anon_member = 1;
        if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
      }
      if (is_anon_member) {
        // Find the inner struct def and inject its fields
        struct SDefInfo *inner_sdi = 0;
        int isi = 0;
        while (isi < np_sdefs) {
          if (my_strcmp(p_sdefs[isi]->name, inline_sname) == 0) { inner_sdi = p_sdefs[isi]; break; }
          isi++;
        }
        if (inner_sdi != 0) {
          int ifi = 0;
          while (ifi < inner_sdi->nflds) {
            fields[nf] = my_strdup(inner_sdi->flds[ifi]->name);
            struct SFieldInfo *isrc = inner_sdi->flds[ifi];
            int *istype = isrc->stype != 0 ? my_strdup(isrc->stype) : 0;
            int *iname = my_strdup(isrc->name);
            struct SFieldInfo *iff = new_sfieldinfo(iname, istype, isrc->is_ptr, isrc->bit_width, isrc->is_array, isrc->is_char);
            iff->is_short = isrc->is_short;
            iff->is_long = isrc->is_long;
            iff->is_char_type = isrc->is_char_type;
            finfo[nf] = iff;
            nf++;
            ifi++;
          }
        }
        continue;
      }
      ftype = inline_sname;
    } else {
      if (p_match(TK_KW, "char")) { f_is_char = 1; }
      f_is_short = p_match(TK_KW, "short");
      // Pre-scan: check if type token is a funcptr or char typedef before parse_base_type resolves it
      { int sv_fp = cur_pos; skip_qualifiers();
        if (tok[cur_pos].kind == TK_ID && td_lookup_is_funcptr(tok[cur_pos].val)) { f_is_funcptr_td = 1; }
        if (tok[cur_pos].kind == TK_ID) { int ftdc = td_lookup_is_char(tok[cur_pos].val); if (ftdc) { f_is_char = 1; } }
        if (tok[cur_pos].kind == TK_ID && td_lookup_is_ptr(tok[cur_pos].val)) { f_td_is_ptr = 1; }
        if ((p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) && cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { f_is_char = 1; }
        cur_pos = sv_fp; }
      ftype = parse_base_type();
      if (last_type_is_long) { f_is_short = 0; }
      f_is_long = last_type_is_long;
      if (last_type_is_short) { f_is_short = 1; }
      f_is_unsigned = last_type_unsigned;
    }
    int is_ptr = 0;
    int is_funcptr = 0;
    if (f_is_funcptr_td) { is_ptr = 1; }
    if (f_td_is_ptr) { is_ptr = 1; }
    // Function pointer field: type (*name)(params) or type (*(*name)(params))(params)
    if (is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      skip_qualifiers();
      is_ptr = 1;
      is_funcptr = 1;
    }
    while (p_match(TK_OP, "*")) {
      p_eat(TK_OP, "*");
      is_ptr = is_ptr + 1;
    }
    // Skip post-pointer qualifiers and more pointers: const *, volatile *, etc.
    while (p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "restrict") || p_match(TK_KW, "__restrict") || p_match(TK_KW, "__restrict__") || p_match(TK_OP, "*")) {
      if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); is_ptr = is_ptr + 1; }
      else { cur_pos++; }
    }
    // Check again for funcptr after consuming pointer stars: type *(*name)(params)
    if (is_funcptr == 0 && is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      skip_qualifiers();
      is_funcptr = 1;
    }
    // Nested funcptr: (*(*name)(params))(params) — after eating outer (* we see (
    int nested_fp = 0;
    if (is_funcptr && is_funcptr_decl()) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      nested_fp = 1;
    }
    // Anonymous bitfield: type : width;
    if (p_match(TK_OP, ":")) {
      p_eat(TK_OP, ":");
      int abw = parse_const_expr();
      // Create placeholder field with generated name
      int *aname = build_str2("_anon_bf_", int_to_str(nf));
      fields[nf] = aname;
      int *afi_n = my_strdup(aname);
      int *afi_st = ftype != 0 ? my_strdup(ftype) : 0;
      struct SFieldInfo *afi = new_sfieldinfo(afi_n, afi_st, is_ptr, abw, 0, 0);
      afi->is_short = f_is_short;
      afi->is_long = f_is_long;
      finfo[nf] = afi;
      nf++;
      p_eat(TK_OP, ";");
      continue;
    }
    int *fname = my_strdup(p_eat(TK_ID, 0));
    if (nested_fp) {
      p_eat(TK_OP, ")");
      skip_param_list(); // inner param list
    }
    if (is_funcptr) {
      p_eat(TK_OP, ")");
      skip_param_list(); // outer param list
    }
    // parse array dimensions in struct fields
    int f_is_arr = 0;
    while (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      int dim_n = 0;
      if (p_match(TK_OP, "]")) {
        // Flexible array member: type field[]
        dim_n = 1;
      } else if (tok[cur_pos].kind == TK_NUM) {
        dim_n = my_atoi(tok[cur_pos].val);
        if (dim_n == 0) dim_n = 1;
        cur_pos++;
        // Skip remaining tokens in brackets (e.g. expressions)
        while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
      } else {
        dim_n = parse_const_expr();
        if (dim_n == 0) dim_n = 1;
      }
      p_eat(TK_OP, "]");
      if (f_is_arr == 0) { f_is_arr = dim_n; }
      else { f_is_arr = f_is_arr * dim_n; }
    }
    while (skip_attribute()) {}
    // Bitfield: field : width (may be a constant expression)
    int bw = 0;
    if (p_match(TK_OP, ":")) {
      p_eat(TK_OP, ":");
      bw = parse_const_expr();
    }

    fields[nf] = fname;
    int *fi_n = my_strdup(fname);
    int *fi_st = ftype != 0 ? my_strdup(ftype) : 0;
    int fi_ic = 0;
    if (f_is_char) { if (is_ptr || f_is_arr > 0) { fi_ic = 1; } }
    struct SFieldInfo *fi = new_sfieldinfo(fi_n, fi_st, is_ptr, bw, f_is_arr, fi_ic);
    fi->is_short = f_is_short;
    fi->is_long = f_is_long;
    fi->is_unsigned = f_is_unsigned;
    fi->is_char_type = f_is_char;
    finfo[nf] = fi;
    nf++;

    // Handle comma-separated fields: type *a, *b, c;
    while (p_match(TK_OP, ",")) {
      p_eat(TK_OP, ",");
      int extra_is_ptr = is_ptr;
      // Reset pointer status for each additional field
      if (p_match(TK_OP, "*")) {
        p_eat(TK_OP, "*");
        extra_is_ptr = 1;
      }
      int *extra_name = my_strdup(p_eat(TK_ID, 0));
      // parse array dimensions
      int ef_is_arr = 0;
      while (p_match(TK_OP, "[")) {
        p_eat(TK_OP, "[");
        if (p_match(TK_OP, "]")) {
          ef_is_arr = 1;
        } else if (tok[cur_pos].kind == TK_NUM) {
          ef_is_arr = my_atoi(tok[cur_pos].val);
          if (ef_is_arr == 0) ef_is_arr = 1;
          cur_pos++;
          while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
        } else {
          ef_is_arr = parse_const_expr();
          if (ef_is_arr == 0) ef_is_arr = 1;
        }
        p_eat(TK_OP, "]");
      }
      int extra_bw = 0;
      if (p_match(TK_OP, ":")) {
        p_eat(TK_OP, ":");
        extra_bw = my_atoi(p_eat(TK_NUM, 0));
      }
      fields[nf] = extra_name;
      int *efi_n = my_strdup(extra_name);
      int *efi_st = ftype != 0 ? my_strdup(ftype) : 0;
      int efi_ic = 0;
      if (f_is_char) { if (extra_is_ptr) { efi_ic = 1; } }
      struct SFieldInfo *efi = new_sfieldinfo(efi_n, efi_st, extra_is_ptr, extra_bw, ef_is_arr, efi_ic);
      efi->is_short = f_is_short;
      efi->is_long = f_is_long;
      efi->is_unsigned = f_is_unsigned;
      efi->is_char_type = f_is_char;
      finfo[nf] = efi;
      nf++;
    }
    p_eat(TK_OP, ";");
  }
  p_eat(TK_OP, "}");
  while (skip_attribute()) {}
  // Only eat ';' if present (inline struct defs inside other structs may not have one)
  if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }

  // Register in parser struct defs
  struct SDefInfo *sdi = my_malloc(48);
  sdi->name = my_strdup(name);
  sdi->flds = finfo;
  sdi->nflds = nf;
  sdi->nwords = 0;
  sdi->is_union = is_union;
  p_sdefs[np_sdefs] = sdi;
  np_sdefs++;

  // Build field_types array
  int **ftypes = my_malloc(256 * 8);
  for (int fti = 0; fti < nf; fti++) {
    if (finfo[fti]->stype != 0 && finfo[fti]->is_ptr == 0) {
      ftypes[fti] = my_strdup(finfo[fti]->stype);
    } else {
      ftypes[fti] = 0;
    }
  }

  // Compute bitfield packing
  int has_bf = 0;
  int bfi = 0;
  while (bfi < nf) {
    if (finfo[bfi]->bit_width > 0) { has_bf = 1; }
    bfi++;
  }

  struct SDef *sd = my_malloc(128);
  sd->name = name;
  sd->fields = fields;
  sd->field_types = ftypes;
  sd->nfields = nf;
  sd->is_union = is_union;
  sd->bit_widths = 0;
  sd->bit_offsets = 0;
  sd->word_indices = 0;
  sd->nwords = 0;
  sd->field_is_array = my_malloc(nf * 8);
  sd->field_is_char = my_malloc(nf * 8);
  sd->field_is_ptr = my_malloc(nf * 8);
  sd->field_is_short = my_malloc(nf * 8);
  sd->field_is_long = my_malloc(nf * 8);
  sd->field_is_char_type = my_malloc(nf * 8);
  sd->field_is_unsigned = my_malloc(nf * 8);
  for (int fai = 0; fai < nf; fai++) { sd->field_is_array[fai] = finfo[fai]->is_array; sd->field_is_char[fai] = finfo[fai]->is_char; sd->field_is_ptr[fai] = finfo[fai]->is_ptr; sd->field_is_short[fai] = finfo[fai]->is_short; sd->field_is_long[fai] = finfo[fai]->is_long; sd->field_is_char_type[fai] = finfo[fai]->is_char_type; sd->field_is_unsigned[fai] = finfo[fai]->is_unsigned; }

  if (has_bf) {
    sd->bit_widths = my_malloc(nf * 8);
    sd->bit_offsets = my_malloc(nf * 8);
    sd->word_indices = my_malloc(nf * 8);
    int cur_word = 0;
    int cur_bit = 0;
    bfi = 0;
    while (bfi < nf) {
      sd->bit_widths[bfi] = finfo[bfi]->bit_width;
      if (finfo[bfi]->bit_width > 0) {
        if (cur_bit + finfo[bfi]->bit_width > 64) {
          cur_word++;
          cur_bit = 0;
        }
        sd->bit_offsets[bfi] = cur_bit;
        sd->word_indices[bfi] = cur_word;
        cur_bit = cur_bit + finfo[bfi]->bit_width;
      } else {
        if (cur_bit > 0) { cur_word++; cur_bit = 0; }
        sd->bit_offsets[bfi] = 0;
        sd->word_indices[bfi] = cur_word;
        cur_word++;
      }
      bfi++;
    }
    if (cur_bit > 0) { cur_word++; }
    sd->nwords = cur_word;
    sdi->nwords = cur_word;
  }

  return sd;
}

struct FuncDef *parse_func() {
  nlv = 0;
  struct FuncDef *fd = 0;
  int ret_is_float = 0;
  { int sv_rf = cur_pos; skip_qualifiers();
    if (p_match(TK_KW, "float") || p_match(TK_KW, "double")) { ret_is_float = 1; }
    cur_pos = sv_rf; }
  int *ret_stype = parse_base_type();
  int ret_is_unsigned = last_type_unsigned;
  int ret_is_long = last_type_is_long;
  int ret_is_ptr = 0;
  while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); ret_is_ptr = 1; skip_qualifiers(); }
  int *name = my_strdup(p_eat(TK_ID, 0));
  p_eat(TK_OP, "(");

  int **params = my_malloc(64 * 8);
  int *param_is_char = my_malloc(64 * 4);
  int *param_is_unsigned = my_malloc(64 * 4);
  int *param_is_intptr = my_malloc(64 * 4);
  int *param_is_long = my_malloc(64 * 4);
  int *param_is_short = my_malloc(64 * 4);
  int *param_is_float = my_malloc(64 * 4);
  int *param_is_barechar = my_malloc(64 * 4);
  int **param_stypes = my_malloc(64 * 8);
  int np = 0;
  int is_variadic = 0;

  // Detect K&R style: f(a, b, c) int a; char *b; long c; { ... }
  // K&R if first token after ( is an identifier that is NOT a type/typedef
  int is_knr = 0;
  if (!p_match(TK_OP, ")")) {
    if (tok[cur_pos].kind == TK_ID && !has_typedef(tok[cur_pos].val)) {
      // Check next token is , or ) — confirms it's just a name, not "typedef_name var"
      int nxt = cur_pos + 1;
      if (nxt < ntokens && (my_strcmp(tok[nxt].val, ",") == 0 || my_strcmp(tok[nxt].val, ")") == 0)) {
        is_knr = 1;
      }
    }
  }

  if (is_knr) {
    // K&R: collect parameter names
    while (1) {
      int *pname = my_strdup(p_eat(TK_ID, 0));
      params[np] = my_strdup(pname);
      param_is_char[np] = 0;
      param_is_unsigned[np] = 0;
      param_is_intptr[np] = 0;
      param_is_long[np] = 0;
      param_is_short[np] = 0;
      param_is_float[np] = 0;
      param_stypes[np] = 0;
      np++;
      if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); continue; }
      break;
    }
    p_eat(TK_OP, ")");
    // Skip __attribute__ after parameter list
    while (skip_attribute()) {}
    // Now parse K&R type declarations until '{'
    while (!p_match(TK_OP, "{") && !p_match(TK_OP, ";")) {
      // Parse: type [*]* name [, [*]* name2] ;
      int kr_is_char = 0;
      int kr_is_float = 0;
      {
        int sv2 = cur_pos;
        skip_qualifiers();
        if (p_match(TK_KW, "char")) { kr_is_char = 1; }
        else if (p_match(TK_KW, "float") || p_match(TK_KW, "double")) { kr_is_float = 1; }
        else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
          if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { kr_is_char = 1; }
        }
        cur_pos = sv2;
      }
      int *kr_stype = parse_base_type();
      int kr_is_unsigned = last_type_unsigned;
      int kr_is_long = last_type_is_long;
      int kr_is_short = last_type_is_short;
      // Loop over comma-separated declarators for this type
      while (1) {
        int kr_is_ptr = 0;
        int kr_ptr_depth = 0;
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); kr_is_ptr = 1; kr_ptr_depth++; }
        skip_qualifiers();
        int *kr_pname = my_strdup(p_eat(TK_ID, 0));
        // Skip array dimensions: name[]
        if (p_match(TK_OP, "[")) {
          p_eat(TK_OP, "[");
          while (!p_match(TK_OP, "]")) { cur_pos++; }
          p_eat(TK_OP, "]");
          kr_is_ptr = 1;
        }
        // Find matching param and update its type info
        int ki = 0;
        while (ki < np) {
          if (my_strcmp(params[ki], kr_pname) == 0) {
            param_is_char[ki] = (kr_is_char && kr_ptr_depth == 1) ? 1 : 0;
            param_is_unsigned[ki] = kr_is_unsigned;
            {
              int krpip = 0;
              if (kr_is_ptr > 0 && kr_is_char == 0) { krpip = kr_ptr_depth; if (krpip < 1) { krpip = 1; } }
              if (kr_is_char && kr_ptr_depth >= 2) { krpip = kr_ptr_depth; }
              param_is_intptr[ki] = krpip;
            }
            param_is_long[ki] = kr_is_long;
            param_is_short[ki] = kr_is_short;
            param_is_float[ki] = kr_is_float;
            if (kr_stype != 0 && kr_is_ptr == 0) {
              param_stypes[ki] = my_strdup(kr_stype);
            }
            if (kr_stype != 0) {
              add_lv(kr_pname, kr_stype, kr_is_ptr);
            }
            break;
          }
          ki++;
        }
        if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); continue; }
        break;
      }
      p_eat(TK_OP, ";");
    }
  } else {
  if (!p_match(TK_OP, ")")) {
    while (1) {
      // Handle ... (variadic)
      if (p_match(TK_OP, ".")) {
        p_eat(TK_OP, ".");
        p_eat(TK_OP, ".");
        p_eat(TK_OP, ".");
        is_variadic = 1;
        break;
      }
      int p_is_char = 0;
      int p_is_float = 0;
      int p_is_barechar_unsigned = 0;
      int p_is_funcptr_td = 0;
      int p_td_is_ptr = 0;
      {
        int sv2 = cur_pos;
        skip_qualifiers();
        if (p_match(TK_KW, "char")) { p_is_char = 1; }
        else if (p_match(TK_KW, "float") || p_match(TK_KW, "double")) { p_is_float = 1; }
        else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
          if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { p_is_char = 1; }
        }
        else if (tok[cur_pos].kind == TK_ID) {
          int ptdc = td_lookup_is_char(tok[cur_pos].val);
          if (ptdc) { p_is_char = 1; if (ptdc == 2) { p_is_barechar_unsigned = 1; } }
          if (td_lookup_is_funcptr(tok[cur_pos].val)) { p_is_funcptr_td = 1; }
          if (td_lookup_is_ptr(tok[cur_pos].val)) { p_td_is_ptr = 1; }
        }
        cur_pos = sv2;
      }
      int *stype = parse_base_type();
      int p_is_unsigned = last_type_unsigned;
      int p_is_long = last_type_is_long;
      int p_is_short = last_type_is_short;
      if (p_is_barechar_unsigned) { p_is_unsigned = 1; }
      int is_ptr = 0;
      int is_funcptr = 0;
      int is_funcptr_from_td = p_is_funcptr_td;
      if (p_td_is_ptr) { is_ptr = 1; }
      // Function pointer param: type (*name)(params)
      if (is_funcptr_decl()) {
        p_eat(TK_OP, "(");
        p_eat(TK_OP, "*");
        is_ptr = 1;
        is_funcptr = 1;
      }
      int ptr_depth = 0;
      while (p_match(TK_OP, "*")) {
        p_eat(TK_OP, "*");
        is_ptr = 1;
        ptr_depth = ptr_depth + 1;
      }
      // Skip post-pointer qualifiers and more pointers: char *const *volatile *argv
      while (p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "restrict") || p_match(TK_KW, "__restrict") || p_match(TK_KW, "__restrict__") || p_match(TK_OP, "*")) {
        if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); is_ptr = 1; ptr_depth = ptr_depth + 1; }
        else { cur_pos++; }
      }
      // char** or deeper: not a char pointer
      if (ptr_depth > 1) p_is_char = 0;
      // Check for funcptr after pointer stars: type *(*name)(params)
      if (is_funcptr == 0 && is_funcptr_decl()) {
        p_eat(TK_OP, "(");
        p_eat(TK_OP, "*");
        is_funcptr = 1;
      }
      skip_qualifiers();
      // Unnamed funcptr param: type (*)(params) or unnamed pointer-to-array: type (*)[size]
      if (is_funcptr && p_match(TK_OP, ")")) {
        p_eat(TK_OP, ")");
        if (p_match(TK_OP, "(")) {
          skip_param_list();
        } else if (p_match(TK_OP, "[")) {
          // Pointer-to-array: type (*)[size]
          is_funcptr = 0;
          is_ptr = 1;
          while (p_match(TK_OP, "[")) {
            p_eat(TK_OP, "[");
            while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
            p_eat(TK_OP, "]");
          }
        }
        if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); continue; }
        break;
      }
      // Unnamed array parameter in prototype: int [], char *[], int [][2]
      while (p_match(TK_OP, "[")) {
        p_eat(TK_OP, "[");
        while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
        p_eat(TK_OP, "]");
        is_ptr = 1;
      }
      // Parameter might be unnamed (in prototypes)
      if (p_match(TK_ID, 0)) {
        int *pname = my_strdup(p_eat(TK_ID, 0));
        if (is_funcptr) {
          p_eat(TK_OP, ")");
          if (p_match(TK_OP, "(")) {
            skip_param_list();
          } else if (p_match(TK_OP, "[")) {
            // Pointer-to-array param: type (*name)[size] — treat as pointer
            is_funcptr = 0;
            is_ptr = 1;
            while (p_match(TK_OP, "[")) {
              p_eat(TK_OP, "[");
              while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
              p_eat(TK_OP, "]");
            }
          }
        }
        // Array parameter: int a[], char *argv[], int a[][2] — treat as pointer
        while (p_match(TK_OP, "[")) {
          p_eat(TK_OP, "[");
          while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
          p_eat(TK_OP, "]");
          is_ptr = 1;
        }
        while (skip_attribute()) {}
        params[np] = my_strdup(pname);
        param_is_char[np] = (p_is_char && is_ptr == 1) ? 1 : 0;
        param_is_unsigned[np] = p_is_unsigned;
        {
          int pip = 0;
          if ((is_ptr > 0 || is_funcptr > 0 || is_funcptr_from_td > 0) && p_is_char == 0) {
            pip = ptr_depth;
            if (pip < 1) { pip = 1; }
          }
          param_is_intptr[np] = pip;
        }
        param_is_long[np] = p_is_long;
        param_is_short[np] = p_is_short;
        param_is_float[np] = p_is_float;
        param_is_barechar[np] = (p_is_char && is_ptr == 0) ? (p_is_unsigned ? 2 : 1) : 0;
        if (stype != 0 && is_ptr == 0) {
          param_stypes[np] = my_strdup(stype);
        } else {
          param_stypes[np] = 0;
        }
        np++;
        add_lv(pname, stype, is_ptr);
      } else {
        // Unnamed parameter (prototype): still count it
        params[np] = "__unnamed";
        param_is_char[np] = (p_is_char && is_ptr == 1) ? 1 : 0;
        param_is_unsigned[np] = p_is_unsigned;
        {
          int pip = 0;
          if ((is_ptr > 0 || is_funcptr > 0 || is_funcptr_from_td > 0) && p_is_char == 0) {
            pip = ptr_depth;
            if (pip < 1) { pip = 1; }
          }
          param_is_intptr[np] = pip;
        }
        param_is_long[np] = p_is_long;
        param_is_short[np] = p_is_short;
        param_is_float[np] = p_is_float;
        param_is_barechar[np] = 0;
        param_stypes[np] = 0;
        np++;
      }
      if (p_match(TK_OP, ",")) {
        p_eat(TK_OP, ",");
        continue;
      }
      break;
    }
  }
  p_eat(TK_OP, ")");

  // Skip __attribute__ after function parameter list
  while (skip_attribute()) {}
  } // end of modern-style else

  // Prototype: semicolon after )
  if (p_match(TK_OP, ";")) {
    p_eat(TK_OP, ";");
    // Store proto info: name and ret_is_ptr
    fd = my_malloc(160);
    fd->name = name;
    fd->params = 0;
    fd->nparams = np;
    fd->body = 0;
    fd->nbody = 0 - 1;
    fd->ret_is_ptr = ret_is_ptr;
    fd->ret_is_unsigned = ret_is_unsigned;
    fd->ret_is_long = ret_is_long;
    fd->is_variadic = is_variadic;
    fd->param_is_char = param_is_char;
    fd->param_is_unsigned = param_is_unsigned;
    fd->param_is_intptr = param_is_intptr;
    fd->param_is_long = param_is_long;
    fd->param_is_short = param_is_short;
    if (ret_is_ptr == 0) { fd->ret_stype = ret_stype; }
    if (ret_stype != 0) { struct_ret_names[n_struct_ret] = my_strdup(name); struct_ret_stypes[n_struct_ret] = my_strdup(ret_stype); n_struct_ret++; }
    fd->param_stypes = param_stypes;
    fd->param_is_float = param_is_float;
    fd->ret_is_float = ret_is_float;
    fd->is_static = 0;
    barechar_func_names[nbarechar_funcs] = my_strdup(name);
    barechar_param_data[nbarechar_funcs] = param_is_barechar;
    nbarechar_funcs++;
    return fd;
  }

  int blen = 0;
  struct Stmt **body = parse_block(&blen);

  fd = my_malloc(160);
  fd->name = name;
  fd->params = params;
  fd->nparams = np;
  fd->body = body;
  fd->nbody = blen;
  fd->ret_is_ptr = ret_is_ptr;
  fd->ret_is_unsigned = ret_is_unsigned;
  fd->ret_is_long = ret_is_long;
  fd->is_variadic = is_variadic;
  fd->param_is_char = param_is_char;
  fd->param_is_unsigned = param_is_unsigned;
  fd->param_is_intptr = param_is_intptr;
  fd->param_is_long = param_is_long;
  fd->param_is_short = param_is_short;
  if (ret_is_ptr == 0) { fd->ret_stype = ret_stype; }
  if (ret_stype != 0) { struct_ret_names[n_struct_ret] = my_strdup(name); struct_ret_stypes[n_struct_ret] = my_strdup(ret_stype); n_struct_ret++; }
  fd->param_stypes = param_stypes;
  fd->param_is_float = param_is_float;
  fd->ret_is_float = ret_is_float;
  fd->is_static = 0;
  barechar_func_names[nbarechar_funcs] = my_strdup(name);
  barechar_param_data[nbarechar_funcs] = param_is_barechar;
  nbarechar_funcs++;
  return fd;
}

// Parse global variable declaration: type [*]* name [[ N ]] [= expr] ;
// Parse one global declarator given already-parsed base type info
struct GDecl *parse_global_decl_one(int *stype, int g_is_char) {
  int is_ptr = 0;
  int is_funcptr = 0;
  // Function pointer global: type (*name)(params)
  if (is_funcptr_decl()) {
    p_eat(TK_OP, "(");
    p_eat(TK_OP, "*");
    skip_qualifiers();
    is_ptr = 1;
    is_funcptr = 1;
  }
  // Skip pointers and qualifiers: type *const *volatile *name
  while (p_match(TK_OP, "*") || p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "restrict") || p_match(TK_KW, "__restrict") || p_match(TK_KW, "__restrict__")) {
    if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); is_ptr = is_ptr + 1; }
    else { cur_pos++; }
  }
  // Check again for funcptr after consuming pointer stars: type *(*name)(params)
  if (is_funcptr == 0 && is_funcptr_decl()) {
    p_eat(TK_OP, "(");
    p_eat(TK_OP, "*");
    skip_qualifiers();
    is_ptr = 1;
    is_funcptr = 1;
  }
  int *name = my_strdup(p_eat(TK_ID, 0));
  while (skip_attribute()) {}
  // Register global struct variables for resolve_stype
  if (stype != 0) {
    if (nglv >= MAX_GLV) { printf("cc: OVERFLOW glv nglv=%d name=%s\n", nglv, name); fflush(0); }
    glv[nglv].name = my_strdup(name);
    glv[nglv].stype = my_strdup(stype);
    glv[nglv].isptr = is_ptr;
    glv[nglv].arrsize = 0 - 1; // updated later when array_size is known
    glv[nglv].is_char = 0;
    nglv++;
  }
  int array_size = 0 - 1;
  if (is_funcptr) {
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      if (p_match(TK_OP, "]")) {
        array_size = 0;
      } else {
        array_size = parse_const_expr();
      }
      p_eat(TK_OP, "]");
    }
    p_eat(TK_OP, ")");
    if (p_match(TK_OP, "(")) {
      skip_param_list();
    } else if (p_match(TK_OP, "[")) {
      // Pointer-to-array: type (*name)[N] — treat as pointer
      is_funcptr = 0;
      while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } p_eat(TK_OP, "]"); }
    }
  }
  if (p_match(TK_OP, "[")) {
    p_eat(TK_OP, "[");
    if (p_match(TK_OP, "]")) {
      array_size = 0; // infer from initializer
    } else {
      array_size = parse_const_expr();
    }
    p_eat(TK_OP, "]");
    // Handle multi-dimensional arrays: type arr[N][M] => flatten to arr[N*M]
    while (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      int dim2 = parse_const_expr();
      p_eat(TK_OP, "]");
      if (array_size > 0) { array_size = array_size * dim2; }
    }
  }

  int has_init = 0;
  int init_val = 0;
  int *init_str = 0;
  struct Expr *init_list = 0;
  if (array_size >= 0 && p_match(TK_OP, "=")) {
    // Array initializer or string init
    p_eat(TK_OP, "=");
    has_init = 1;
    if (p_match(TK_STR, 0)) {
      init_str = my_strdup(p_eat(TK_STR, 0));
      int slen = my_strlen(init_str) + 1;
      if (array_size == 0) { array_size = slen; }
    } else {
      init_list = parse_init_list(0);
      if (array_size == 0) { array_size = init_list->nargs; }
    }
  } else if (p_match(TK_OP, "=")) {
    p_eat(TK_OP, "=");
    has_init = 1;
    if (p_match(TK_STR, 0)) {
      init_str = my_strdup(p_eat(TK_STR, 0));
    } else if (p_match(TK_OP, "{")) {
      // Struct/compound initializer: struct S obj = {10, 20};
      init_list = parse_init_list(stype);
    } else if (p_match(TK_OP, "&")) {
      // Address-of initializer - skip to semicolon or comma
      int gdepth = 0;
      while (1) {
        if (p_match(TK_OP, "(") || p_match(TK_OP, "{")) { gdepth++; }
        else if (p_match(TK_OP, ")") || p_match(TK_OP, "}")) { gdepth--; }
        else if (gdepth == 0 && (p_match(TK_OP, ";") || p_match(TK_OP, ","))) { break; }
        cur_pos++;
      }
      init_val = 0;
    } else {
      init_val = parse_const_expr();
    }
  }
  while (skip_attribute()) {}

  // Register global for sizeof lookups (if not already registered with stype above)
  if (stype == 0 && nglv < MAX_GLV) {
    glv[nglv].name = my_strdup(name);
    glv[nglv].stype = 0;
    glv[nglv].isptr = is_ptr;
    glv[nglv].arrsize = array_size;
    glv[nglv].is_char = g_is_char;
    nglv++;
  } else if (stype != 0) {
    // Update existing glv entry with array size (it was registered earlier without it)
    int gi = nglv - 1;
    while (gi >= 0) {
      if (my_strcmp(glv[gi].name, name) == 0) { glv[gi].arrsize = array_size; glv[gi].is_char = g_is_char; gi = 0 - 1; }
      gi--;
    }
  }
  struct GDecl *gd = my_malloc(104);
  gd->name = name;
  gd->is_ptr = is_ptr;
  gd->array_size = array_size;
  gd->init_val = init_val;
  gd->has_init = has_init;
  gd->init_str = init_str;
  gd->init_list = init_list;
  gd->stype = stype;
  gd->is_char = g_is_char;
  gd->is_static = 0;
  gd->is_unsigned = 0;
  gd->is_short = 0;
  gd->is_long = 0;
  return gd;
}

// Parse global declaration with multi-declarator support: int a, b, c;
// Stores additional declarators directly via globals/ng pointers
int parse_global_decls(struct GDecl **globals, int ng, int top_is_static) {
  int g_is_char = 0;
  {
    int sv = cur_pos;
    skip_qualifiers();
    if (p_match(TK_KW, "char")) { g_is_char = 1; }
    else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { g_is_char = 1; }
    }
    else if (tok[cur_pos].kind == TK_ID) {
      int gtdc = td_lookup_is_char(tok[cur_pos].val);
      if (gtdc) { g_is_char = 1; }
    }
    cur_pos = sv;
  }
  int g_is_short = 0;
  int g_is_long = 0;
  {
    int sv3 = cur_pos;
    skip_qualifiers();
    if (p_match(TK_KW, "short")) { g_is_short = 1; }
    else if (p_match(TK_KW, "long")) { g_is_long = 1; }
    else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "short") == 0) { g_is_short = 1; }
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "long") == 0) { g_is_long = 1; }
    }
    cur_pos = sv3;
  }
  int g_is_funcptr_td = 0;
  int g_td_is_ptr = 0;
  {
    int sv2 = cur_pos;
    skip_qualifiers();
    if (tok[cur_pos].kind == TK_ID && td_lookup_is_funcptr(tok[cur_pos].val)) { g_is_funcptr_td = 1; }
    if (tok[cur_pos].kind == TK_ID && td_lookup_is_ptr(tok[cur_pos].val)) { g_td_is_ptr = 1; }
    cur_pos = sv2;
  }
  int *stype = parse_base_type();
  int g_is_unsigned = last_type_unsigned;
  if (last_type_is_short) { g_is_short = 1; }
  if (last_type_is_long) { g_is_long = 1; }
  struct GDecl *gd = parse_global_decl_one(stype, g_is_char);
  if (g_is_funcptr_td && gd->is_ptr == 0) { gd->is_ptr = 1; }
  if (g_td_is_ptr && gd->is_ptr == 0) { gd->is_ptr = 1; }
  gd->is_static = top_is_static;
  gd->is_unsigned = g_is_unsigned;
  gd->is_short = g_is_short;
  gd->is_long = g_is_long;
  if (g_is_long || g_is_short) {
    int gi = nglv - 1;
    while (gi >= 0) {
      if (my_strcmp(glv[gi].name, gd->name) == 0) {
        if (g_is_long) { glv_is_long[gi] = 1; }
        if (g_is_short) { glv_is_short[gi] = 1; }
        gi = 0 - 1;
      }
      gi--;
    }
  }
  globals[ng] = gd;
  ng++;
  while (p_match(TK_OP, ",")) {
    p_eat(TK_OP, ",");
    struct GDecl *gd2 = parse_global_decl_one(stype, g_is_char);
    gd2->is_static = top_is_static;
    gd2->is_unsigned = g_is_unsigned;
    gd2->is_short = g_is_short;
    gd2->is_long = g_is_long;
    if (g_is_long || g_is_short) {
      int gi = nglv - 1;
      while (gi >= 0) {
        if (my_strcmp(glv[gi].name, gd2->name) == 0) {
          if (g_is_long) { glv_is_long[gi] = 1; }
          if (g_is_short) { glv_is_short[gi] = 1; }
          gi = 0 - 1;
        }
        gi--;
      }
    }
    globals[ng] = gd2;
    ng++;
  }
  p_eat(TK_OP, ";");
  return ng;
}

// Legacy single-declarator wrapper (used for funcptr globals)
struct GDecl *parse_global_decl() {
  int g_is_char = 0;
  {
    int sv = cur_pos;
    skip_qualifiers();
    if (p_match(TK_KW, "char")) { g_is_char = 1; }
    else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
      if (tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { g_is_char = 1; }
    }
    else if (tok[cur_pos].kind == TK_ID) {
      int gtdc = td_lookup_is_char(tok[cur_pos].val);
      if (gtdc) { g_is_char = 1; }
    }
    cur_pos = sv;
  }
  int g_is_funcptr_td2 = 0;
  int g_td_is_ptr2 = 0;
  {
    int sv2 = cur_pos;
    skip_qualifiers();
    if (tok[cur_pos].kind == TK_ID && td_lookup_is_funcptr(tok[cur_pos].val)) { g_is_funcptr_td2 = 1; }
    if (tok[cur_pos].kind == TK_ID && td_lookup_is_ptr(tok[cur_pos].val)) { g_td_is_ptr2 = 1; }
    cur_pos = sv2;
  }
  int *stype = parse_base_type();
  struct GDecl *gd = parse_global_decl_one(stype, g_is_char);
  if (g_is_funcptr_td2 && gd->is_ptr == 0) { gd->is_ptr = 1; }
  if (g_td_is_ptr2 && gd->is_ptr == 0) { gd->is_ptr = 1; }
  gd->is_unsigned = last_type_unsigned;
  p_eat(TK_OP, ";");
  return gd;
}

// Check if current position looks like a function (vs global variable)
// Assumes we're after type [*]* name — check if next is '('
int is_func_lookahead() {
  int saved = cur_pos;
  parse_base_type();
  while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); skip_qualifiers(); }
  if (p_match(TK_ID, 0)) { p_eat(TK_ID, 0); }
  int result = p_match(TK_OP, "(");
  cur_pos = saved;
  return result;
}

// Check if after parse_base_type() we have a function-returning-funcptr pattern:
// type (* name ( ...   e.g. void (*sqlite3OsDlSym(sqlite3_vfs*, void*, const char*))(void);
// Distinguishes from funcptr variable: type (*name)(params) — name is followed by ')' not '('
int is_funcptr_return() {
  if (!p_match(TK_OP, "(")) return 0;
  if (cur_pos + 3 < ntokens &&
      tok[cur_pos].kind == TK_OP && my_strcmp(tok[cur_pos].val, "(") == 0 &&
      tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "*") == 0 &&
      tok[cur_pos + 2].kind == TK_ID &&
      tok[cur_pos + 3].kind == TK_OP && my_strcmp(tok[cur_pos + 3].val, "(") == 0) {
    return 1;
  }
  return 0;
}

// Skip a funcptr-return declaration/definition, returning a FuncDef*.
// Pattern: type (* name (params))(ret_params) ; or { body }
// cur_pos is at '(' of '(* name (...'
struct FuncDef *skip_funcptr_return() {
  p_eat(TK_OP, "(");
  p_eat(TK_OP, "*");
  int *fname = my_strdup(p_eat(TK_ID, 0));
  // Skip parameter list: name ( ... )
  int pd = 1;
  p_eat(TK_OP, "(");
  while (pd > 0 && !p_match(TK_EOF, 0)) {
    if (p_match(TK_OP, "(")) { pd++; }
    else if (p_match(TK_OP, ")")) { pd--; if (pd == 0) break; }
    cur_pos++;
  }
  p_eat(TK_OP, ")");
  // closing ) of (* name(params) )
  p_eat(TK_OP, ")");
  // Skip return type param list if present
  if (p_match(TK_OP, "(")) {
    int rd = 1;
    p_eat(TK_OP, "(");
    while (rd > 0 && !p_match(TK_EOF, 0)) {
      if (p_match(TK_OP, "(")) { rd++; }
      else if (p_match(TK_OP, ")")) { rd--; if (rd == 0) break; }
      cur_pos++;
    }
    p_eat(TK_OP, ")");
  }

  struct FuncDef *fpr = my_malloc(328);
  fpr->name = fname;
  fpr->nparams = 0;
  fpr->ret_is_ptr = 1;
  fpr->ret_is_unsigned = 0;
  fpr->is_variadic = 0;
  fpr->ret_stype = 0;
  fpr->ret_is_float = 0;
  fpr->is_static = 0;

  if (p_match(TK_OP, ";")) {
    p_eat(TK_OP, ";");
    fpr->nbody = 0 - 1; // prototype
  } else if (p_match(TK_OP, "{")) {
    p_eat(TK_OP, "{");
    int bd = 1;
    while (bd > 0 && !p_match(TK_EOF, 0)) {
      if (p_match(TK_OP, "{")) { bd++; }
      else if (p_match(TK_OP, "}")) { bd--; if (bd == 0) break; }
      cur_pos++;
    }
    p_eat(TK_OP, "}");
    fpr->nbody = 0; // stub definition
  } else {
    fpr->nbody = 0 - 1;
  }
  return fpr;
}

// ---- Constant expression evaluator for enum values ----
int parse_const_expr();

int parse_const_primary() {
  if (p_match(TK_KW, "sizeof") || p_match(TK_KW, "__alignof__") || p_match(TK_KW, "__alignof") || p_match(TK_KW, "_Alignof")) {
    cur_pos++; // eat the keyword
    p_eat(TK_OP, "(");
    // Skip type inside sizeof/__alignof__() and return 8 (all types are 8 bytes)
    int depth = 1;
    while (depth > 0) {
      if (p_match(TK_OP, "(")) { depth++; }
      else if (p_match(TK_OP, ")")) { depth--; if (depth == 0) break; }
      cur_pos++;
    }
    p_eat(TK_OP, ")");
    return 8;
  }
  if (p_match(TK_OP, "(")) {
    p_eat(TK_OP, "(");
    // Check for cast expression: (type)expr or (TypedefName *)expr
    int is_cast = 0;
    if (tok[cur_pos].kind == TK_KW && is_type_keyword(tok[cur_pos].val)) { is_cast = 1; }
    if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) { is_cast = 1; }
    // Also detect (identifier *) pattern as a cast (struct pointer)
    if (tok[cur_pos].kind == TK_ID && tok[cur_pos + 1].kind == TK_OP &&
        (my_strcmp(tok[cur_pos + 1].val, "*") == 0 || my_strcmp(tok[cur_pos + 1].val, ")") == 0)) {
      // Could be a cast like (Parse *)0 or (Parse)0
      // Check if after closing ) the next token is not an operator that would make this a sub-expression
      int lk = cur_pos + 1;
      while (lk < ntokens && my_strcmp(tok[lk].val, "*") == 0) { lk++; }
      if (lk < ntokens && my_strcmp(tok[lk].val, ")") == 0) { is_cast = 1; }
    }
    if (is_cast) {
      int cd = 1;
      while (cd > 0) {
        if (p_match(TK_OP, "(")) { cd++; }
        else if (p_match(TK_OP, ")")) { cd--; if (cd == 0) break; }
        cur_pos++;
      }
      p_eat(TK_OP, ")");
      return parse_const_unary();
    }
    int val = parse_const_expr();
    p_eat(TK_OP, ")");
    // Handle postfix -> and . (offsetof patterns like ((Type*)0)->field)
    while (p_match(TK_OP, "->") || p_match(TK_OP, ".")) {
      cur_pos++; // skip -> or .
      cur_pos++; // skip field name
      val = 0;
    }
    return val;
  }
  if (p_match(TK_STR, 0)) {
    // Character literal: 'a', '\n', etc.
    int *cv = p_eat(TK_STR, 0);
    return __read_byte(cv, 0);
  }
  if (p_match(TK_NUM, 0)) {
    return my_atoi(p_eat(TK_NUM, 0));
  }
  if (p_match(TK_ID, 0)) {
    int *name = p_eat(TK_ID, 0);
    if (has_enum_const(name)) { return find_enum_const(name); }
    // Unknown identifier in const expr (e.g. typedef name, macro) - treat as 0
    return 0;
  }
  // If we hit ] or ) or ; without finding a value, return 0 instead of crashing
  if (p_match(TK_OP, "]") || p_match(TK_OP, ")") || p_match(TK_OP, ";") || p_match(TK_OP, ",")) {
    return 0;
  }
  printf("cc: Expected constant expression at pos=%d tok#=%d k=%d v='%s'\n", tok[cur_pos].pos, cur_pos, tok[cur_pos].kind, tok[cur_pos].val);
  { int dd = cur_pos - 5; if (dd < 0) { dd = 0; } while (dd < cur_pos + 5 && dd < ntokens) { printf("  tok[%d] k=%d '%s'\n", dd, tok[dd].kind, tok[dd].val); dd++; } }
  fflush(0);
  exit(1);
  return 0;
}

int parse_const_unary() {
  if (p_match(TK_OP, "-")) { p_eat(TK_OP, "-"); return 0 - parse_const_unary(); }
  if (p_match(TK_OP, "+")) { p_eat(TK_OP, "+"); return parse_const_unary(); }
  if (p_match(TK_OP, "~")) { p_eat(TK_OP, "~"); return ~parse_const_unary(); }
  if (p_match(TK_OP, "!")) { p_eat(TK_OP, "!"); return !parse_const_unary(); }
  // &((Type*)0)->field — offsetof pattern — skip and return 0
  if (p_match(TK_OP, "&")) {
    p_eat(TK_OP, "&");
    return parse_const_unary();
  }
  return parse_const_primary();
}

int parse_const_mul() {
  int val = parse_const_unary();
  while (p_match(TK_OP, "*") || p_match(TK_OP, "/") || p_match(TK_OP, "%")) {
    int *op = tok[cur_pos].val;
    p_eat(TK_OP, 0);
    int rhs = parse_const_unary();
    if (__read_byte(op, 0) == '*') { val = val * rhs; }
    else if (__read_byte(op, 0) == '/') { val = val / rhs; }
    else { val = val % rhs; }
  }
  return val;
}

int parse_const_add() {
  int val = parse_const_mul();
  while (p_match(TK_OP, "+") || p_match(TK_OP, "-")) {
    int *op = tok[cur_pos].val;
    p_eat(TK_OP, 0);
    int rhs = parse_const_mul();
    if (__read_byte(op, 0) == '+') { val = val + rhs; } else { val = val - rhs; }
  }
  return val;
}

int parse_const_shift() {
  int val = parse_const_add();
  while (p_match(TK_OP, "<<") || p_match(TK_OP, ">>")) {
    int *op = tok[cur_pos].val;
    p_eat(TK_OP, 0);
    int rhs = parse_const_add();
    if (__read_byte(op, 0) == '<') { val = val << rhs; } else { val = val >> rhs; }
  }
  return val;
}

int parse_const_rel() {
  int val = parse_const_shift();
  while (p_match(TK_OP, "<") || p_match(TK_OP, ">") || p_match(TK_OP, "<=") || p_match(TK_OP, ">=")) {
    int *op = tok[cur_pos].val; p_eat(TK_OP, 0); int rhs = parse_const_shift();
    if (my_strcmp(op, "<") == 0) { val = val < rhs; }
    else if (my_strcmp(op, ">") == 0) { val = val > rhs; }
    else if (my_strcmp(op, "<=") == 0) { val = val <= rhs; }
    else { val = val >= rhs; }
  }
  return val;
}

int parse_const_eq() {
  int val = parse_const_rel();
  while (p_match(TK_OP, "==") || p_match(TK_OP, "!=")) {
    int *op = tok[cur_pos].val; p_eat(TK_OP, 0); int rhs = parse_const_rel();
    if (my_strcmp(op, "==") == 0) { val = val == rhs; } else { val = val != rhs; }
  }
  return val;
}

int parse_const_and() {
  int val = parse_const_eq();
  while (p_match(TK_OP, "&")) { p_eat(TK_OP, "&"); val = val & parse_const_eq(); }
  return val;
}

int parse_const_xor() {
  int val = parse_const_and();
  while (p_match(TK_OP, "^")) { p_eat(TK_OP, "^"); val = val ^ parse_const_and(); }
  return val;
}

int parse_const_or() {
  int val = parse_const_xor();
  while (p_match(TK_OP, "|")) { p_eat(TK_OP, "|"); val = val | parse_const_xor(); }
  return val;
}

int parse_const_logand() {
  int val = parse_const_or();
  while (p_match(TK_OP, "&&")) { p_eat(TK_OP, "&&"); int rhs = parse_const_or(); val = val && rhs; }
  return val;
}

int parse_const_logor() {
  int val = parse_const_logand();
  while (p_match(TK_OP, "||")) { p_eat(TK_OP, "||"); int rhs = parse_const_logand(); val = val || rhs; }
  return val;
}

int parse_const_expr() {
  int val = parse_const_logor();
  if (p_match(TK_OP, "?")) {
    p_eat(TK_OP, "?");
    int then_val = parse_const_expr();
    p_eat(TK_OP, ":");
    int else_val = parse_const_expr();
    return val ? then_val : else_val;
  }
  return val;
}

int parse_enum_def() {
  p_eat(TK_KW, "enum");
  // optional enum tag name
  if (p_match(TK_ID, 0)) { p_eat(TK_ID, 0); }
  p_eat(TK_OP, "{");
  int val = 0;
  while (!p_match(TK_OP, "}")) {
    int *ename = my_strdup(p_eat(TK_ID, 0));
    if (p_match(TK_OP, "=")) {
      p_eat(TK_OP, "=");
      val = parse_const_expr();
    }
    add_enum_const(ename, val);
    val++;
    if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); }
  }
  p_eat(TK_OP, "}");
  // Skip optional variable name(s) after enum: enum { ... } var1, *var2;
  if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
  else {
    // Skip tokens until ; but stop at { (function body) to avoid overconsumption
    while (!p_match(TK_OP, ";") && !p_match(TK_OP, "{") && !p_match(TK_EOF, 0)) { cur_pos++; }
    if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
  }
  return 0;
}

int skip_extern_decl() {
  p_eat(TK_KW, "extern");
  // Parse type to register struct-typed variables for resolve_stype
  int sv_pos = cur_pos;
  skip_qualifiers();
  int *ext_stype = 0;
  if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) {
    cur_pos++;
    if (tok[cur_pos].kind == TK_ID && !p_match(TK_OP, "{")) {
      ext_stype = my_strdup(tok[cur_pos].val);
      cur_pos++;
    }
  } else if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) {
    ext_stype = find_typedef(tok[cur_pos].val);
    if (ext_stype != 0) { ext_stype = my_strdup(ext_stype); }
    cur_pos++;
  } else {
    // Skip base type keywords
    while (cur_pos < ntokens && tok[cur_pos].kind == TK_KW) { cur_pos++; }
  }
  // Skip pointers and qualifiers
  while (p_match(TK_OP, "*") || p_match(TK_KW, "const") || p_match(TK_KW, "volatile") || p_match(TK_KW, "restrict")) {
    cur_pos++;
  }
  // Get variable name if present — register all extern vars (even non-struct) for codegen
  if (tok[cur_pos].kind == TK_ID && !p_match(TK_OP, "(")) {
    int *ext_name = tok[cur_pos].val;
    // Don't register if next token is '(' (that's a function prototype)
    if (cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "(") != 0) {
      glv[nglv].name = my_strdup(ext_name);
      if (ext_stype != 0) { glv[nglv].stype = my_strdup(ext_stype); } else { glv[nglv].stype = 0; }
      glv[nglv].isptr = 1;
      glv[nglv].arrsize = 0 - 1;
      glv[nglv].is_char = 0;
      nglv++;
    }
  }
  // Skip rest of declaration
  cur_pos = sv_pos;
  while (!p_match(TK_OP, ";")) {
    cur_pos++;
  }
  p_eat(TK_OP, ";");
  return 0;
}

void register_td_struct(int *sname, int **td_fields, struct SFieldInfo **td_finfo, int td_nf, int is_union, struct SDef **structs, int *ns_ptr) {
  struct SDefInfo *sdi = my_malloc(48);
  sdi->name = my_strdup(sname);
  sdi->flds = td_finfo;
  sdi->nflds = td_nf;
  sdi->nwords = 0;
  sdi->is_union = is_union;
  p_sdefs[np_sdefs] = sdi;
  np_sdefs++;
  int **ftypes = my_malloc(512 * 8);
  int fti = 0;
  while (fti < td_nf) {
    if (td_finfo[fti]->stype != 0 && td_finfo[fti]->is_ptr == 0) {
      ftypes[fti] = my_strdup(td_finfo[fti]->stype);
    } else {
      ftypes[fti] = 0;
    }
    fti++;
  }
  struct SDef *sd = my_malloc(128);
  sd->name = my_strdup(sname);
  sd->fields = td_fields;
  sd->field_types = ftypes;
  sd->nfields = td_nf;
  sd->is_union = is_union;
  sd->bit_widths = 0;
  sd->bit_offsets = 0;
  sd->word_indices = 0;
  sd->nwords = 0;
  int *fia = my_malloc(td_nf * 8);
  int *fic = my_malloc(td_nf * 8);
  int *fip = my_malloc(td_nf * 8);
  sd->field_is_array = fia;
  sd->field_is_char = fic;
  sd->field_is_ptr = fip;
  int *fish = my_malloc(td_nf * 8);
  int *fil = my_malloc(td_nf * 8);
  sd->field_is_short = fish;
  sd->field_is_long = fil;
  int *fict = my_malloc(td_nf * 8);
  sd->field_is_char_type = fict;
  int *fiu = my_malloc(td_nf * 8);
  sd->field_is_unsigned = fiu;
  int tdi = 0;
  while (tdi < td_nf) {
    sd->field_is_array[tdi] = td_finfo[tdi]->is_array;
    sd->field_is_char[tdi] = td_finfo[tdi]->is_char;
    sd->field_is_ptr[tdi] = td_finfo[tdi]->is_ptr;
    sd->field_is_short[tdi] = td_finfo[tdi]->is_short;
    sd->field_is_long[tdi] = td_finfo[tdi]->is_long;
    sd->field_is_char_type[tdi] = td_finfo[tdi]->is_char_type;
    sd->field_is_unsigned[tdi] = td_finfo[tdi]->is_unsigned;
    tdi++;
  }
  structs[*ns_ptr] = sd;
  *ns_ptr = *ns_ptr + 1;
}

int parse_typedef(struct SDef **structs, int *ns_ptr) {
  int *tag_name = 0;
  int *alias = 0;
  int *ptd_stype = 0;
  int **td_fields = 0;
  struct SFieldInfo **td_finfo = 0;
  int td_nf = 0;
  int *ftype = 0;
  int fis_ptr = 0;
  int *fname = 0;
  struct SFieldInfo *fi = 0;
  int is_union_td = 0;
  int td_eval = 0;
  int *ename = 0;
  int neg = 0;
  int td_depth = 0;

  if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) {
    is_union_td = p_match(TK_KW, "union");
    if (is_union_td) { p_eat(TK_KW, "union"); } else { p_eat(TK_KW, "struct"); }

    while (skip_attribute()) {}
    if (p_match(TK_ID, 0)) {
      tag_name = my_strdup(tok[cur_pos].val);
      p_eat(TK_ID, 0);
    }
    while (skip_attribute()) {}

    // struct body?
    if (p_match(TK_OP, "{")) {
      p_eat(TK_OP, "{");
      td_fields = my_malloc(512 * 8);
      td_finfo = my_malloc(512 * 8);
      td_nf = 0;
      while (!p_match(TK_OP, "}")) {
        // Handle inline struct/union definitions (named or anonymous)
        int *td_inline_sname = 0;
        if ((p_match(TK_KW, "struct") || p_match(TK_KW, "union")) &&
            ((cur_pos + 2 < ntokens && tok[cur_pos + 1].kind == TK_ID &&
              tok[cur_pos + 2].kind == TK_OP && my_strcmp(tok[cur_pos + 2].val, "{") == 0) ||
             (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "{") == 0))) {
          int td_iu = p_match(TK_KW, "union");
          struct SDef *td_inner = parse_struct_or_union_def(td_iu);
          td_inline_sname = td_inner->name;
          inline_sdefs[ninline_sdefs] = td_inner;
          ninline_sdefs++;
        }
        int f_is_char = 0;
        int tf_is_short = 0;
        int tf_is_long = 0;
        int tf_is_funcptr_td = 0;
        int tf_td_is_ptr = 0;
        if (td_inline_sname != 0) {
          ftype = td_inline_sname;
        } else {
          // Pre-scan for char/short type
          int sv_fc = cur_pos;
          skip_qualifiers();
          if (p_match(TK_KW, "char")) { f_is_char = 1; }
          else if (p_match(TK_KW, "short")) { tf_is_short = 1; }
          else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed")) {
            if (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { f_is_char = 1; }
            if (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "short") == 0) { tf_is_short = 1; }
          }
          else if (tok[cur_pos].kind == TK_ID) {
            int ftdc = td_lookup_is_char(tok[cur_pos].val);
            if (ftdc) { f_is_char = 1; }
            if (td_lookup_is_funcptr(tok[cur_pos].val)) { tf_is_funcptr_td = 1; }
            if (td_lookup_is_ptr(tok[cur_pos].val)) { tf_td_is_ptr = 1; }
          }
          cur_pos = sv_fc;
          ftype = parse_base_type();
          tf_is_long = last_type_is_long;
          if (tf_is_long) { tf_is_short = 0; }
        }
        fis_ptr = 0;
        int td_fp = 0;
        if (tf_is_funcptr_td) { fis_ptr = 1; }
        if (tf_td_is_ptr) { fis_ptr = 1; }
        if (is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); fis_ptr = 1; td_fp = 1; }
        while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); fis_ptr = 1; }
        skip_qualifiers();
        if (td_fp == 0 && is_funcptr_decl()) { p_eat(TK_OP, "("); p_eat(TK_OP, "*"); td_fp = 1; }
        // Anonymous bitfield: type : width;
        if (p_match(TK_OP, ":")) {
          p_eat(TK_OP, ":");
          int abw = parse_const_expr();
          fname = build_str2("_anon_bf_", int_to_str(td_nf));
          int *_sfi_n = my_strdup(fname);
          int *_sfi_st = ftype != 0 ? my_strdup(ftype) : 0;
          fi = new_sfieldinfo(_sfi_n, _sfi_st, fis_ptr, abw, 0, 0);
          td_fields[td_nf] = fname;
          td_finfo[td_nf] = fi;
          td_nf++;
          p_eat(TK_OP, ";");
          continue;
        }
        fname = my_strdup(p_eat(TK_ID, 0));
        if (td_fp) { p_eat(TK_OP, ")"); skip_param_list(); }
        int f_is_arr = 0;
        while (p_match(TK_OP, "[")) {
          p_eat(TK_OP, "[");
          if (p_match(TK_OP, "]")) {
            f_is_arr = 1;
          } else if (tok[cur_pos].kind == TK_NUM) {
            f_is_arr = my_atoi(tok[cur_pos].val);
            if (f_is_arr == 0) f_is_arr = 1;
            cur_pos++;
            while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; }
          } else {
            f_is_arr = parse_const_expr();
            if (f_is_arr == 0) f_is_arr = 1;
          }
          p_eat(TK_OP, "]");
        }
        while (skip_attribute()) {}
        int td_bw = 0;
        if (p_match(TK_OP, ":")) { p_eat(TK_OP, ":"); td_bw = my_atoi(p_eat(TK_NUM, 0)); }
        td_fields[td_nf] = fname;
        int *_sfi_n = my_strdup(fname);
        int *_sfi_st = ftype != 0 ? my_strdup(ftype) : 0;
        fi = new_sfieldinfo(_sfi_n, _sfi_st, fis_ptr, td_bw, f_is_arr, f_is_char);
        fi->is_short = tf_is_short;
        fi->is_long = tf_is_long;
        fi->is_unsigned = last_type_unsigned;
        fi->is_char_type = f_is_char;
        td_finfo[td_nf] = fi;
        td_nf++;
        // Handle comma-separated fields
        while (p_match(TK_OP, ",")) {
          p_eat(TK_OP, ",");
          int eip = fis_ptr;
          if (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); eip = 1; }
          int *en = my_strdup(p_eat(TK_ID, 0));
          int ef_arr = 0;
          while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); if (p_match(TK_OP, "]")) { ef_arr = 1; } else if (tok[cur_pos].kind == TK_NUM) { ef_arr = my_atoi(tok[cur_pos].val); if (ef_arr == 0) ef_arr = 1; cur_pos++; while (!p_match(TK_OP, "]") && !p_match(TK_EOF, 0)) { cur_pos++; } } else { ef_arr = parse_const_expr(); if (ef_arr == 0) ef_arr = 1; } p_eat(TK_OP, "]"); }
          int ebw = 0;
          if (p_match(TK_OP, ":")) { p_eat(TK_OP, ":"); ebw = my_atoi(p_eat(TK_NUM, 0)); }
          td_fields[td_nf] = en;
          int *_sfi_n = my_strdup(en);
          int *_sfi_st = ftype != 0 ? my_strdup(ftype) : 0;
          fi = new_sfieldinfo(_sfi_n, _sfi_st, eip, ebw, ef_arr, f_is_char);
          fi->is_short = tf_is_short;
          fi->is_long = tf_is_long;
          fi->is_unsigned = last_type_unsigned;
          fi->is_char_type = f_is_char;
          td_finfo[td_nf] = fi;
          td_nf++;
        }
        p_eat(TK_OP, ";");
      }
      p_eat(TK_OP, "}");

      // Register struct def
      if (tag_name != 0) {
        register_td_struct(tag_name, td_fields, td_finfo, td_nf, is_union_td, structs, ns_ptr);
      }
    }

    // Skip pointer stars and qualifiers/attributes
    int su_td_is_ptr = 0;
    while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); su_td_is_ptr = 1; }
    skip_qualifiers();

    // The typedef alias name
    if (p_match(TK_ID, 0)) {
      alias = my_strdup(p_eat(TK_ID, 0));
      // For anonymous struct/union typedef, use alias as tag name
      if (tag_name == 0 && td_nf > 0) {
        tag_name = alias;
        register_td_struct(alias, td_fields, td_finfo, td_nf, is_union_td, structs, ns_ptr);
      }
      add_typedef(alias, tag_name);
      if (su_td_is_ptr) { td_is_ptr[ntd - 1] = 1; }
    }
    skip_qualifiers();
    p_eat(TK_OP, ";");
    return 0;
  }

  if (p_match(TK_KW, "enum")) {
    p_eat(TK_KW, "enum");
    if (p_match(TK_ID, 0)) { p_eat(TK_ID, 0); }
    if (p_match(TK_OP, "{")) {
      p_eat(TK_OP, "{");
      td_eval = 0;
      while (!p_match(TK_OP, "}")) {
        ename = my_strdup(p_eat(TK_ID, 0));
        if (p_match(TK_OP, "=")) {
          p_eat(TK_OP, "=");
          td_eval = parse_const_expr();
        }
        add_enum_const(ename, td_eval);
        td_eval++;
        if (p_match(TK_OP, ",")) { p_eat(TK_OP, ","); }
      }
      p_eat(TK_OP, "}");
    }
    if (p_match(TK_ID, 0)) {
      alias = my_strdup(p_eat(TK_ID, 0));
      add_typedef(alias, 0);
    }
    p_eat(TK_OP, ";");
    return 0;
  }

  // typedef <base-type> [*]* Name; or function pointer typedef
  // Pre-scan for char type
  int ptd_is_char = 0;
  int ptd_is_unsigned = 0;
  {
    int sv2 = cur_pos;
    skip_qualifiers();
    if (p_match(TK_KW, "char")) { ptd_is_char = 1; }
    else if (p_match(TK_KW, "unsigned") || p_match(TK_KW, "signed") || p_match(TK_KW, "__signed__")) {
      if (cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_KW && my_strcmp(tok[cur_pos + 1].val, "char") == 0) { ptd_is_char = 1; }
      if (my_strcmp(tok[cur_pos].val, "unsigned") == 0) { ptd_is_unsigned = 1; }
    }
    else if (tok[cur_pos].kind == TK_ID) {
      int ptdc = td_lookup_is_char(tok[cur_pos].val);
      if (ptdc) { ptd_is_char = 1; if (ptdc == 2) { ptd_is_unsigned = 1; } }
    }
    cur_pos = sv2;
  }
  ptd_stype = parse_base_type();
  if (last_type_unsigned) { ptd_is_unsigned = 1; }
  // Check for function pointer: (*Name)(params)
  if (p_match(TK_OP, "(") && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "*") == 0) {
    p_eat(TK_OP, "(");
    p_eat(TK_OP, "*");
    alias = my_strdup(p_eat(TK_ID, 0));
    p_eat(TK_OP, ")");
    // skip param list
    p_eat(TK_OP, "(");
    td_depth = 1;
    while (td_depth > 0) {
      if (p_match(TK_OP, "(")) { td_depth = td_depth + 1; }
      if (p_match(TK_OP, ")")) { td_depth = td_depth - 1; }
      if (td_depth > 0) { cur_pos = cur_pos + 1; }
    }
    p_eat(TK_OP, ")");
    p_eat(TK_OP, ";");
    add_typedef(alias, 0);
    td[ntd - 1].is_funcptr = 1;
  } else {
    // Normal: typedef type [*]* Name;
    int ptd_is_ptr = 0;
    while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); ptd_stype = 0; ptd_is_char = 0; ptd_is_ptr = 1; }
    skip_qualifiers();
    // Check again for funcptr after stars: typedef int *(*Name)(params);
    if (p_match(TK_OP, "(") && cur_pos + 1 < ntokens && tok[cur_pos + 1].kind == TK_OP && my_strcmp(tok[cur_pos + 1].val, "*") == 0) {
      p_eat(TK_OP, "(");
      p_eat(TK_OP, "*");
      alias = my_strdup(p_eat(TK_ID, 0));
      p_eat(TK_OP, ")");
      p_eat(TK_OP, "(");
      td_depth = 1;
      while (td_depth > 0) {
        if (p_match(TK_OP, "(")) { td_depth = td_depth + 1; }
        if (p_match(TK_OP, ")")) { td_depth = td_depth - 1; }
        if (td_depth > 0) { cur_pos = cur_pos + 1; }
      }
      p_eat(TK_OP, ")");
      p_eat(TK_OP, ";");
      add_typedef(alias, 0);
      td[ntd - 1].is_funcptr = 1;
      return 0;
    }
    alias = my_strdup(p_eat(TK_ID, 0));
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      if (!p_match(TK_OP, "]")) { p_eat(TK_NUM, 0); }
      p_eat(TK_OP, "]");
    }
    skip_qualifiers();
    add_typedef(alias, ptd_stype);
    if (ptd_is_ptr) { td_is_ptr[ntd - 1] = 1; }
    if (ptd_is_char) { td[ntd - 1].is_char = 1; td[ntd - 1].is_unsigned = ptd_is_unsigned; }
    if (last_type_is_long) { td_is_long[ntd - 1] = 1; }
    if (last_type_is_short) { td_is_short[ntd - 1] = 1; }
    if (last_type_unsigned) { td_is_unsigned[ntd - 1] = 1; }
    // Handle comma-separated typedefs: typedef struct { ... } A, *B;
    while (p_match(TK_OP, ",")) {
      p_eat(TK_OP, ",");
      int *extra_stype = ptd_stype;
      int extra_is_ptr = 0;
      while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); extra_stype = 0; extra_is_ptr = 1; }
      skip_qualifiers();
      int *extra_alias = my_strdup(p_eat(TK_ID, 0));
      if (p_match(TK_OP, "[")) {
        p_eat(TK_OP, "[");
        if (!p_match(TK_OP, "]")) { p_eat(TK_NUM, 0); }
        p_eat(TK_OP, "]");
      }
      add_typedef(extra_alias, extra_stype);
      if (extra_is_ptr) { td_is_ptr[ntd - 1] = 1; }
    }
    p_eat(TK_OP, ";");
  }
  return 0;
}

int is_type_start() {
  if (p_match(TK_KW, "int")) { return 1; }
  if (p_match(TK_KW, "char")) { return 1; }
  if (p_match(TK_KW, "void")) { return 1; }
  if (p_match(TK_KW, "struct")) { return 1; }
  if (p_match(TK_KW, "union")) { return 1; }
  if (p_match(TK_KW, "unsigned")) { return 1; }
  if (p_match(TK_KW, "signed")) { return 1; }
  if (p_match(TK_KW, "long")) { return 1; }
  if (p_match(TK_KW, "short")) { return 1; }
  if (p_match(TK_KW, "const")) { return 1; }
  if (p_match(TK_KW, "volatile")) { return 1; }
  if (p_match(TK_KW, "enum")) { return 1; }
  if (p_match(TK_KW, "double")) { return 1; }
  if (p_match(TK_KW, "float")) { return 1; }
  if (p_match(TK_KW, "_Bool")) { return 1; }
  if (tok[cur_pos].kind == TK_ID && has_typedef(tok[cur_pos].val)) { return 1; }
  return 0;
}

struct Program *parse_program() {
  cur_pos = 0;
  np_sdefs = 0;
  nec = 0;
  ntd = 0;
  // Built-in typedefs
  add_typedef("va_list", 0);
  add_typedef("__builtin_va_list", 0);
  add_typedef("size_t", 0);
  add_typedef("ssize_t", 0);
  add_typedef("ptrdiff_t", 0);
  add_typedef("uintptr_t", 0);
  add_typedef("intptr_t", 0);
  add_typedef("uint8_t", 0); td[ntd - 1].is_char = 1; td[ntd - 1].is_unsigned = 1;
  add_typedef("uint16_t", 0);
  add_typedef("uint32_t", 0);
  add_typedef("uint64_t", 0);
  add_typedef("int8_t", 0); td[ntd - 1].is_char = 1; td[ntd - 1].is_unsigned = 0;
  add_typedef("int16_t", 0);
  add_typedef("int32_t", 0);
  add_typedef("int64_t", 0);
  add_typedef("off_t", 0);
  add_typedef("mode_t", 0);
  add_typedef("pid_t", 0);
  add_typedef("uid_t", 0);
  add_typedef("gid_t", 0);
  add_typedef("time_t", 0);
  add_typedef("FILE", 0);
  add_typedef("DIR", 0);
  add_typedef("sqlite3_int64", 0);
  add_typedef("sqlite3_uint64", 0);

  struct SDef **structs = my_malloc(512 * 8);
  int ns = 0;
  struct FuncDef **funcs = my_malloc(MAX_PROGRAM * 8);
  int nf = 0;
  int **proto_names = my_malloc(MAX_PROGRAM * 8);
  int *proto_rip = my_malloc(MAX_PROGRAM * 8);
  int *proto_riu = my_malloc(MAX_PROGRAM * 8);
  int *proto_ril = my_malloc(MAX_PROGRAM * 8);
  int *proto_is_var = my_malloc(MAX_PROGRAM * 8);
  int *proto_np = my_malloc(MAX_PROGRAM * 8);
  int **proto_rs = my_malloc(MAX_PROGRAM * 8);
  int *proto_rif = my_malloc(MAX_PROGRAM * 8);
  int nprotos = 0;
  struct GDecl **globals = my_malloc(MAX_PROGRAM * 8);
  int ng = 0;
  struct FuncDef *fd = 0;
  int saved = 0;

  while (!p_match(TK_EOF, 0)) {
    // Skip stray semicolons at top level (e.g. after function body: }; )
    while (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
    if (p_match(TK_EOF, 0)) break;
    // Skip __extension__ at top level (may precede typedef)
    while (p_match(TK_KW, "__extension__")) { p_eat(TK_KW, "__extension__"); }

    // typedef
    if (p_match(TK_KW, "typedef")) {
      p_eat(TK_KW, "typedef");
      parse_typedef(structs, &ns);
      continue;
    }

    // extern — skip entire declaration
    if (p_match(TK_KW, "extern")) {
      skip_extern_decl();
      continue;
    }

    // _Static_assert — skip
    if (p_match(TK_KW, "_Static_assert")) {
      p_eat(TK_KW, "_Static_assert");
      p_eat(TK_OP, "(");
      int sa_depth = 1;
      while (sa_depth > 0) {
        if (p_match(TK_OP, "(")) { sa_depth++; }
        else if (p_match(TK_OP, ")")) { sa_depth--; if (sa_depth == 0) break; }
        cur_pos++;
      }
      p_eat(TK_OP, ")");
      p_eat(TK_OP, ";");
      continue;
    }

    // static/inline/__attribute__/__extension__ — skip keywords (any order)
    int top_is_static = 0;
    while (1) {
      if (p_match(TK_KW, "static")) { p_eat(TK_KW, "static"); top_is_static = 1; }
      else if (p_match(TK_KW, "inline")) { p_eat(TK_KW, "inline"); }
      else if (skip_attribute()) {}
      else { break; }
    }

    // enum definition
    if (p_match(TK_KW, "enum")) {
      saved = cur_pos;
      p_eat(TK_KW, "enum");
      // optional tag
      if (p_match(TK_ID, 0)) { p_eat(TK_ID, 0); }
      if (p_match(TK_OP, "{")) {
        cur_pos = saved;
        parse_enum_def();
        continue;
      }
      // enum as type in func/global decl
      cur_pos = saved;
      // Check for function returning funcptr: enum type (* name(params))(ret);
      {
        int sv_fpr = cur_pos;
        parse_base_type();
        if (is_funcptr_return()) {
          fd = skip_funcptr_return();
          if (fd->nbody == 0 - 1) {
            proto_names[nprotos] = fd->name;
            proto_rip[nprotos] = fd->ret_is_ptr;
            proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
            proto_ril[nprotos] = fd->ret_is_long;
            proto_is_var[nprotos] = fd->is_variadic;
            proto_np[nprotos] = fd->nparams;
            proto_rs[nprotos] = fd->ret_stype;
            proto_rif[nprotos] = fd->ret_is_float;
            nprotos++;
          } else {
            fd->is_static = top_is_static;
            funcs[nf] = fd;
            nf++;
          }
          continue;
        }
        cur_pos = sv_fpr;
      }
      if (is_func_lookahead()) {
        fd = parse_func();
        if (fd->nbody == 0 - 1) {
          proto_names[nprotos] = fd->name;
          proto_rip[nprotos] = fd->ret_is_ptr;
          proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
          proto_is_var[nprotos] = fd->is_variadic;
          proto_np[nprotos] = fd->nparams;
          proto_rs[nprotos] = fd->ret_stype;
          proto_rif[nprotos] = fd->ret_is_float;
          nprotos++;
        } else {
          fd->is_static = top_is_static;
          funcs[nf] = fd;

          nf++;
        }
      } else {
        ng = parse_global_decls(globals, ng, top_is_static);
      }
      continue;
    }

    if (p_match(TK_KW, "struct") || p_match(TK_KW, "union")) {
      int is_union_kw = p_match(TK_KW, "union");
      saved = cur_pos;
      if (is_union_kw) { p_eat(TK_KW, "union"); } else { p_eat(TK_KW, "struct"); }
      while (skip_attribute()) {}
      // Anonymous struct: struct { ... } var;
      if (p_match(TK_OP, "{")) {
        cur_pos = saved;
        structs[ns] = parse_struct_or_union_def(is_union_kw);
        ns++;
        int *sv_stype = structs[ns - 1]->name;
        // Skip storage class after struct def: struct { ... } static g;
        if (p_match(TK_KW, "static")) { p_eat(TK_KW, "static"); top_is_static = 1; }
        // Check for variable declaration after anonymous struct
        if (p_match(TK_OP, "*") || p_match(TK_ID, 0)) {
          int sv_ptr = 0;
          while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); sv_ptr = 1; }
          int *sv_name = my_strdup(p_eat(TK_ID, 0));
          int sv_arr = 0 - 1;
          if (p_match(TK_OP, "[")) {
            p_eat(TK_OP, "[");
            if (p_match(TK_OP, "]")) { p_eat(TK_OP, "]"); sv_arr = 0; }
            else { sv_arr = parse_const_expr(); p_eat(TK_OP, "]"); }
            while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); int d2 = parse_const_expr(); p_eat(TK_OP, "]"); if (sv_arr > 0) sv_arr = sv_arr * d2; }
          }
          int sv_has_init = 0; int sv_init_val = 0; int *sv_init_str = 0;
          struct Expr *sv_init_list = 0;
          if (p_match(TK_OP, "=")) {
            p_eat(TK_OP, "=");
            sv_has_init = 1;
            if (p_match(TK_OP, "{")) {
              sv_init_list = parse_init_list(0);
              if (sv_arr == 0) { sv_arr = sv_init_list->nargs; }
            } else if (p_match(TK_STR, 0)) {
              sv_init_str = my_strdup(p_eat(TK_STR, 0));
            } else {
              sv_init_val = parse_const_expr();
            }
          }
          // Handle multi-declarator: struct { ... } a[1], c = {5,1}, d;
          while (p_match(TK_OP, ",")) {
            p_eat(TK_OP, ",");
            int sv_ptr2 = 0;
            while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); sv_ptr2 = 1; }
            int *sv_name2 = my_strdup(p_eat(TK_ID, 0));
            int sv_arr2 = 0 - 1;
            if (p_match(TK_OP, "[")) {
              p_eat(TK_OP, "[");
              if (p_match(TK_OP, "]")) { p_eat(TK_OP, "]"); sv_arr2 = 0; }
              else { sv_arr2 = parse_const_expr(); p_eat(TK_OP, "]"); }
              while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); int d2 = parse_const_expr(); p_eat(TK_OP, "]"); if (sv_arr2 > 0) sv_arr2 = sv_arr2 * d2; }
            }
            int sv_has_init2 = 0; int sv_init_val2 = 0;
            struct Expr *sv_init_list2 = 0;
            if (p_match(TK_OP, "=")) {
              p_eat(TK_OP, "=");
              sv_has_init2 = 1;
              if (p_match(TK_OP, "{")) { sv_init_list2 = parse_init_list(0); }
              else { sv_init_val2 = parse_const_expr(); }
            }
            struct GDecl *sv_gd2 = my_malloc(104);
            sv_gd2->name = sv_name2; sv_gd2->is_ptr = sv_ptr2; sv_gd2->array_size = sv_arr2;
            sv_gd2->init_val = sv_init_val2; sv_gd2->has_init = sv_has_init2;
            sv_gd2->init_str = 0; sv_gd2->init_list = sv_init_list2;
            sv_gd2->stype = sv_stype; sv_gd2->is_char = 0; sv_gd2->is_unsigned = 0;
            sv_gd2->is_static = top_is_static; sv_gd2->is_short = 0; sv_gd2->is_long = 0;
            globals[ng] = sv_gd2; ng++;
            glv[nglv].name = my_strdup(sv_name2);
            glv[nglv].stype = my_strdup(sv_stype);
            glv[nglv].isptr = sv_ptr2;
            glv[nglv].arrsize = 0 - 1;
            glv[nglv].is_char = 0;
            nglv++;
          }
          p_eat(TK_OP, ";");
          struct GDecl *sv_gd = my_malloc(104);
          sv_gd->name = sv_name; sv_gd->is_ptr = sv_ptr; sv_gd->array_size = sv_arr;
          sv_gd->init_val = sv_init_val; sv_gd->has_init = sv_has_init;
          sv_gd->init_str = sv_init_str; sv_gd->init_list = sv_init_list;
          sv_gd->stype = sv_stype; sv_gd->is_char = 0; sv_gd->is_unsigned = 0;
          sv_gd->is_static = top_is_static; sv_gd->is_short = 0; sv_gd->is_long = 0;
          globals[ng] = sv_gd; ng++;
          glv[nglv].name = my_strdup(sv_name);
          glv[nglv].stype = my_strdup(sv_stype);
          glv[nglv].isptr = sv_ptr;
          glv[nglv].arrsize = sv_arr;
          glv[nglv].is_char = 0;
          nglv++;
        } else if (p_match(TK_OP, ";")) {
          p_eat(TK_OP, ";");
        }
        continue;
      }
      p_eat(TK_ID, 0);
      if (p_match(TK_OP, "{")) {
        cur_pos = saved;
        structs[ns] = parse_struct_or_union_def(is_union_kw);
        ns++;
        // After struct/union def, check for variable declaration: struct Foo { ... } var = ...;
        // Skip storage class after struct def
        if (p_match(TK_KW, "static")) { p_eat(TK_KW, "static"); top_is_static = 1; }
        // Only treat as variable if ID is NOT a type keyword or typedef
        if (p_match(TK_OP, "*") || (tok[cur_pos].kind == TK_ID && !has_typedef(tok[cur_pos].val) && tok[cur_pos].kind != TK_KW
            && !(cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "(") == 0))) {
          // There's a variable following the struct def — parse as global decl
          // Build a fake declaration start: the struct name is the type
          int *sv_stype = structs[ns - 1]->name;
          int sv_ptr = 0;
          while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); sv_ptr = 1; }
          int *sv_name = my_strdup(p_eat(TK_ID, 0));
          int sv_arr = 0 - 1;
          if (p_match(TK_OP, "[")) {
            p_eat(TK_OP, "[");
            if (p_match(TK_OP, "]")) { p_eat(TK_OP, "]"); sv_arr = 0; }
            else { sv_arr = parse_const_expr(); p_eat(TK_OP, "]"); }
            while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); int d2 = parse_const_expr(); p_eat(TK_OP, "]"); if (sv_arr > 0) sv_arr = sv_arr * d2; }
          }
          int sv_has_init = 0; int sv_init_val = 0; int *sv_init_str = 0;
          struct Expr *sv_init_list = 0;
          if (p_match(TK_OP, "=")) {
            p_eat(TK_OP, "=");
            sv_has_init = 1;
            if (p_match(TK_OP, "{")) {
              sv_init_list = parse_init_list(0);
              if (sv_arr == 0) { sv_arr = sv_init_list->nargs; }
            } else if (p_match(TK_STR, 0)) {
              sv_init_str = my_strdup(p_eat(TK_STR, 0));
            } else {
              sv_init_val = parse_const_expr();
            }
          }
          // Handle multi-declarator: struct Foo { ... } a, b, *c;
          while (p_match(TK_OP, ",")) {
            p_eat(TK_OP, ",");
            int sv_ptr2 = 0;
            while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); sv_ptr2 = 1; }
            int *sv_name2 = my_strdup(p_eat(TK_ID, 0));
            int sv_arr2 = 0 - 1;
            if (p_match(TK_OP, "[")) {
              p_eat(TK_OP, "[");
              if (p_match(TK_OP, "]")) { p_eat(TK_OP, "]"); sv_arr2 = 0; }
              else { sv_arr2 = parse_const_expr(); p_eat(TK_OP, "]"); }
              while (p_match(TK_OP, "[")) { p_eat(TK_OP, "["); int d2 = parse_const_expr(); p_eat(TK_OP, "]"); if (sv_arr2 > 0) sv_arr2 = sv_arr2 * d2; }
            }
            int sv_has_init2 = 0; int sv_init_val2 = 0;
            struct Expr *sv_init_list2 = 0;
            if (p_match(TK_OP, "=")) {
              p_eat(TK_OP, "=");
              sv_has_init2 = 1;
              if (p_match(TK_OP, "{")) { sv_init_list2 = parse_init_list(0); }
              else { sv_init_val2 = parse_const_expr(); }
            }
            struct GDecl *sv_gd2 = my_malloc(104);
            sv_gd2->name = sv_name2; sv_gd2->is_ptr = sv_ptr2; sv_gd2->array_size = sv_arr2;
            sv_gd2->init_val = sv_init_val2; sv_gd2->has_init = sv_has_init2;
            sv_gd2->init_str = 0; sv_gd2->init_list = sv_init_list2;
            sv_gd2->stype = sv_stype; sv_gd2->is_char = 0; sv_gd2->is_unsigned = 0;
            sv_gd2->is_static = top_is_static; sv_gd2->is_short = 0; sv_gd2->is_long = 0;
            globals[ng] = sv_gd2; ng++;
            if (sv_stype != 0) {
              glv[nglv].name = my_strdup(sv_name2);
              glv[nglv].stype = my_strdup(sv_stype);
              glv[nglv].isptr = sv_ptr2;
              glv[nglv].arrsize = 0 - 1;
              glv[nglv].is_char = 0;
              nglv++;
            }
          }
          p_eat(TK_OP, ";");
          struct GDecl *sv_gd = my_malloc(104);
          sv_gd->name = sv_name; sv_gd->is_ptr = sv_ptr; sv_gd->array_size = sv_arr;
          sv_gd->init_val = sv_init_val; sv_gd->has_init = sv_has_init;
          sv_gd->init_str = sv_init_str; sv_gd->init_list = sv_init_list;
          sv_gd->stype = sv_stype; sv_gd->is_char = 0; sv_gd->is_unsigned = 0;
          sv_gd->is_static = top_is_static; sv_gd->is_short = 0; sv_gd->is_long = 0;
          globals[ng] = sv_gd; ng++;
          // Register for resolve_stype
          if (sv_stype != 0) {
            glv[nglv].name = my_strdup(sv_name);
            glv[nglv].stype = my_strdup(sv_stype);
            glv[nglv].isptr = sv_ptr;
            glv[nglv].arrsize = sv_arr;
            glv[nglv].is_char = 0;
            nglv++;
          }
        } else if (p_match(TK_OP, ";")) {
          p_eat(TK_OP, ";");
        }
      } else if (p_match(TK_OP, ";")) {
        // Forward declaration: struct Foo; — just skip
        p_eat(TK_OP, ";");
      } else {
        cur_pos = saved;
        // Check for function returning funcptr: struct type (* name(params))(ret);
        int did_fpr2 = 0;
        {
          int sv_fpr2 = cur_pos;
          parse_base_type();
          if (is_funcptr_return()) {
            fd = skip_funcptr_return();
            if (fd->nbody == 0 - 1) {
              proto_names[nprotos] = fd->name;
              proto_rip[nprotos] = fd->ret_is_ptr;
              proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
            proto_ril[nprotos] = fd->ret_is_long;
              proto_is_var[nprotos] = fd->is_variadic;
              proto_np[nprotos] = fd->nparams;
              proto_rs[nprotos] = fd->ret_stype;
              proto_rif[nprotos] = fd->ret_is_float;
              nprotos++;
            } else {
              fd->is_static = top_is_static;
              funcs[nf] = fd;
              nf++;
            }
            did_fpr2 = 1;
          } else {
            cur_pos = sv_fpr2;
          }
        }
        if (!did_fpr2) {
        if (is_func_lookahead()) {
          fd = parse_func();
          if (fd->nbody == 0 - 1) {
            proto_names[nprotos] = fd->name;
            proto_rip[nprotos] = fd->ret_is_ptr;
            proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
            proto_ril[nprotos] = fd->ret_is_long;
            proto_is_var[nprotos] = fd->is_variadic;
            proto_np[nprotos] = fd->nparams;
            proto_rs[nprotos] = fd->ret_stype;
            proto_rif[nprotos] = fd->ret_is_float;
            nprotos++;
          } else {
            fd->is_static = top_is_static;
            funcs[nf] = fd;

            nf++;
          }
        } else {
          ng = parse_global_decls(globals, ng, top_is_static);
        }
        }
      }
    } else {
      // Skip top-level expression statements from macro expansions
      // Patterns: ((void)0);  funcname(args);  0;  etc.
      {
        int is_toplevel_expr = 0;
        // (void)expr or ((void)0)
        if (p_match(TK_OP, "(")) {
          int pp = cur_pos;
          while (pp < ntokens && my_strcmp(tok[pp].val, "(") == 0) { pp++; }
          if (pp < ntokens && tok[pp].kind == TK_KW && my_strcmp(tok[pp].val, "void") == 0 &&
              pp + 1 < ntokens && my_strcmp(tok[pp + 1].val, ")") == 0) {
            is_toplevel_expr = 1;
          }
        }
        // bare identifier followed by ( — could be function call OR K&R implicit int function
        if (tok[cur_pos].kind == TK_ID && !has_typedef(tok[cur_pos].val) &&
            cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "(") == 0) {
          // Scan past (...) to see if { follows — that means it's a function definition
          int pp2 = cur_pos + 2;
          int pd2 = 1;
          while (pd2 > 0 && pp2 < ntokens) {
            if (my_strcmp(tok[pp2].val, "(") == 0) { pd2++; }
            else if (my_strcmp(tok[pp2].val, ")") == 0) { pd2--; }
            pp2++;
          }
          // After ), check for { (direct body) or type keywords (K&R param decls before {)
          int is_knr_func = 0;
          if (pp2 < ntokens && my_strcmp(tok[pp2].val, "{") == 0) { is_knr_func = 1; }
          // K&R param declarations: f(a, b) int a; char *b; { ... }
          if (pp2 < ntokens && tok[pp2].kind == TK_KW) { is_knr_func = 1; }
          if (!is_knr_func) {
            is_toplevel_expr = 1;
          }
        }
        // bare number at top level (e.g. macro expanding to 0;)
        if (tok[cur_pos].kind == TK_NUM) {
          is_toplevel_expr = 1;
        }
        if (is_toplevel_expr) {
          while (!p_match(TK_OP, ";") && !p_match(TK_EOF, 0)) { cur_pos++; }
          if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
          continue;
        }
      }
      // Skip macro-expanded-away declarations like "const char *0(...);"
      {
        int save2 = cur_pos;
        parse_base_type();
        while (p_match(TK_OP, "*")) { cur_pos++; }
        if (tok[cur_pos].kind == TK_NUM) {
          // Macro expanded to 0 — skip to ;
          while (!p_match(TK_OP, ";") && !p_match(TK_EOF, 0)) { cur_pos++; }
          if (p_match(TK_OP, ";")) { p_eat(TK_OP, ";"); }
          continue;
        }
        // Function returning funcptr: type (*name(params))(ret); or { body }
        if (is_funcptr_return()) {
          fd = skip_funcptr_return();
          if (fd->nbody == 0 - 1) {
            proto_names[nprotos] = fd->name;
            proto_rip[nprotos] = fd->ret_is_ptr;
            proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
            proto_ril[nprotos] = fd->ret_is_long;
            proto_is_var[nprotos] = fd->is_variadic;
            proto_np[nprotos] = fd->nparams;
            proto_rs[nprotos] = fd->ret_stype;
            proto_rif[nprotos] = fd->ret_is_float;
            nprotos++;
          } else {
            fd->is_static = top_is_static;
            funcs[nf] = fd;
            nf++;
          }
          continue;
        }
        // Function pointer variable: type (*name)(params);
        if (p_match(TK_OP, "(") && cur_pos + 1 < ntokens && my_strcmp(tok[cur_pos + 1].val, "*") == 0) {
          cur_pos = save2;
          globals[ng] = parse_global_decl();
          globals[ng]->is_static = top_is_static;
          ng++;
          continue;
        }
        cur_pos = save2;
      }
      if (is_func_lookahead()) {
        fd = parse_func();
        if (fd->nbody == 0 - 1) {
          proto_names[nprotos] = fd->name;
          proto_rip[nprotos] = fd->ret_is_ptr;
          proto_riu[nprotos] = fd->ret_is_unsigned;
          proto_ril[nprotos] = fd->ret_is_long;
          proto_is_var[nprotos] = fd->is_variadic;
          proto_np[nprotos] = fd->nparams;
          proto_rs[nprotos] = fd->ret_stype;
          proto_rif[nprotos] = fd->ret_is_float;
          nprotos++;
        } else {
          fd->is_static = top_is_static;
          funcs[nf] = fd;

          nf++;
        }
      } else {
        ng = parse_global_decls(globals, ng, top_is_static);
      }
    }
  }

  struct Program *p = my_malloc(120);
  p->structs = structs;
  p->nstructs = ns;
  p->funcs = funcs;
  p->nfuncs = nf;
  p->proto_names = proto_names;
  p->proto_ret_is_ptr = proto_rip;
  p->proto_ret_is_unsigned = proto_riu;
  p->proto_ret_is_long = proto_ril;
  p->proto_is_variadic = proto_is_var;
  p->proto_nparams = proto_np;
  p->proto_ret_stype = proto_rs;
  p->proto_ret_is_float = proto_rif;
  p->nprotos = nprotos;
  p->globals = globals;
  p->nglobals = ng;
  return p;
}

// ---- Codegen ----

int cg_is_local(int *name) {
  int i = 0;
  while (i < nlay) {
    if (lay_name[i] != 0 && my_strcmp(lay_name[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_is_global(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_global_is_array(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].is_array; }
    i++;
  }
  return 0;
}

int cg_global_esz(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].esz; }
    i++;
  }
  return 0;
}

int cg_global_ptr_esz(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].ptr_esz; }
    i++;
  }
  return 0;
}

int cg_global_is_bare_char_arr(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].is_bare_char_arr; }
    i++;
  }
  return 0;
}

int cg_global_is_unsigned(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg_is_unsigned[i]; }
    i++;
  }
  return 0;
}

int func_returns_ptr(int *name) {
  int i = 0;
  while (i < n_ptr_ret) {
    if (my_strcmp(ptr_ret_names[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int func_returns_unsigned(int *name) {
  int i = 0;
  while (i < n_unsigned_ret) {
    if (my_strcmp(unsigned_ret_names[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int *func_ret_stype(int *name) {
  int i = 0;
  while (i < n_struct_ret) {
    if (my_strcmp(struct_ret_names[i], name) == 0) { return struct_ret_stypes[i]; }
    i++;
  }
  return 0;
}

int is_known_func(int *name) {
  int i = 0;
  while (i < nknown_funcs) {
    if (my_strcmp(known_funcs[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int is_defined_func(int *name) {
  int i = 0;
  while (i < ndefined_funcs) {
    if (my_strcmp(defined_funcs[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int *cg_new_label(int *base) {
  label_id++;
  int *num = int_to_str(label_id);
  int *tmp = build_str2("L_", base);
  int *tmp2 = build_str2(tmp, "_");
  return build_str2(tmp2, num);
}

int cg_find_slot(int *name) {
  int i = 0;
  if (name == 0) return 0 - 1;
  while (i < nlay) {
    if (lay_name[i] != 0 && my_strcmp(lay_name[i], name) == 0) {
      return lay_off[i];
    }
    i++;
  }
  return 0 - 1;
}

int cg_is_array(int *name) {
  int i = 0;
  while (i < nlay_arr) {
    if (my_strcmp(lay_arr_name[i], name) == 0) { return 1; }
    i++;
  }
  // Check static local arrays, scoped to current function
  i = 0;
  while (i < nsl) {
    if (my_strcmp(sl[i].name, name) == 0 && sl[i].arr_size >= 0 && my_strcmp(sl[i].func, cg_cur_func_name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_is_structvar(int *name) {
  int i = 0;
  while (i < nlay_sv) {
    if (my_strcmp(lay_sv_name[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int *cg_structvar_type(int *name) {
  int i = 0;
  while (i < nlay_sv) {
    if (my_strcmp(lay_sv_name[i], name) == 0) { return lay_sv_type[i]; }
    i++;
  }
  return 0;
}

int *cg_ptr_structvar_type(int *name) {
  int i = 0;
  while (i < nlay_psv) {
    if (my_strcmp(lay_psv_name[i], name) == 0) { return lay_psv_type[i]; }
    i++;
  }
  return 0;
}

int cg_struct_nfields(int *sname);

// Resolve a struct name, trying typedef if direct match fails
int *cg_resolve_sname(int *sname) {
  if (sname == 0) return 0;
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      return sname;
    }
    i++;
  }
  // Try typedef resolution
  int *resolved = find_typedef(sname);
  if (resolved != 0 && my_strcmp(resolved, sname) != 0) {
    return resolved;
  }
  return sname;
}

int cg_field_index(int *sname, int *fname) {
  int i = 0;
  int j = 0;
  int slot = 0;
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      // For unions, all fields are at offset 0
      if (cg_s_is_union[i]) { return 0; }
      // Bitfield struct: use word_indices
      if (cg_s_wi[i] != 0) {
        int *wi_arr = cg_s_wi[i];
        j = 0;
        while (j < cg_snfields[i]) {
          if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
            return wi_arr[j];
          }
          j++;
        }
        printf("cc: field '%s' not found in bitfield struct '%s'\n", fname, sname); return 0;
      }
      slot = 0;
      j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return slot;
        }
        {
          int f_sl = 1;
          if (cg_sfield_types[i][j] != 0) {
            f_sl = cg_struct_nfields(cg_sfield_types[i][j]);
          }
          if (cg_s_fa[i] != 0 && cg_s_fa[i][j] > 0) {
            if (cg_s_fc[i] != 0 && cg_s_fc[i][j]) {
              f_sl = (cg_s_fa[i][j] + 7) / 8;
            } else {
              f_sl = f_sl * cg_s_fa[i][j];
            }
          }
          slot += f_sl;
        }
        j++;
      }
      printf("cc: field '%s' not found in struct '%s' (nfields=%d)\n", fname, sname, cg_snfields[i]); return 0;
    }
    i++;
  }
  printf("cc: struct '%s' not found in codegen (field '%s') [in %s] ncg_s=%d\n", sname, fname, cg_cur_func_name, ncg_s);
  // Dump all known struct names for debugging
  if (my_strcmp(fname, "first") == 0) {
    int di = 0;
    while (di < ncg_s) {
      if (cg_sname[di] != 0 && (__read_byte(cg_sname[di], 0) == 'c' || __read_byte(cg_sname[di], 0) == 'C')) {
        printf("  cg_sname[%d] = '%s'\n", di, cg_sname[di]);
      }
      di++;
    }
  }
  return 0;
}

int cg_field_is_array(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fa[i] == 0) return 0;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fa[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_is_char(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fc[i] == 0) return 0;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fc[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_is_unsigned(int *sname, int *fname) {
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      int j = 0;
      while (j < cg_snfields[i]) {
        if (my_strcmp(cg_sfields[i][j], fname) == 0) {
          return (cg_s_fu[i] != 0) ? cg_s_fu[i][j] : 0;
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_is_ptr(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fp[i] == 0) return 0;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fp[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_is_short(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fsh[i] == 0) return 0;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fsh[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_is_long(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fl[i] == 0) return 0;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fl[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_struct_nfields(int *sname) {
  int i = 0;
  int j = 0;
  int total = 0;
  sname = cg_resolve_sname(sname);
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      // Unions: all fields overlap, allocate 1 slot
      if (cg_s_is_union[i]) { return 1; }
      // Bitfield struct: use nwords
      if (cg_s_nw[i] > 0) { return cg_s_nw[i]; }
      total = 0;
      j = 0;
      while (j < cg_snfields[i]) {
        int f_slots = 1;
        if (cg_sfield_types[i][j] != 0) {
          f_slots = cg_struct_nfields(cg_sfield_types[i][j]);
        }
        // Array fields occupy arr_size slots (or arr_size * nested_struct_size)
        // Char arrays: ceil(arr_size / 8) slots
        if (cg_s_fa[i] != 0 && cg_s_fa[i][j] > 0) {
          if (cg_s_fc[i] != 0 && cg_s_fc[i][j]) {
            f_slots = (cg_s_fa[i][j] + 7) / 8;
          } else {
            f_slots = f_slots * cg_s_fa[i][j];
          }
        }
        total += f_slots;
        j++;
      }
      return total;
    }
    i++;
  }
  printf("cc: struct '%s' not found for nfields in %s\n", sname, cg_cur_func_name);
  return 1;
}

int cg_struct_byte_size(int *sname) {
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      return cg_s_bytesize[i];
    }
    i++;
  }
  printf("cc: struct '%s' not found for byte_size\n", sname);
  return 8;
}

int cg_field_byte_offset(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fbyteoff[i] == 0) { printf("cc: WARNING: no byte offset table for struct '%s', falling back to fi*8\n", sname); return cg_field_index(sname, fname) * 8; }
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fbyteoff[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

int cg_field_byte_size(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 8;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fbytesize[i] == 0) return 8;
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_s_fbytesize[i][j];
        }
        j++;
      }
      return 8;
    }
    i++;
  }
  return 8;
}

// Returns struct type of a field, or 0 if field is not a struct
int *cg_field_struct_type(int *sname, int *fname) {
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      int j = 0;
      while (j < cg_snfields[i]) {
        if (my_strcmp(cg_sfields[i][j], fname) == 0) {
          return cg_sfield_types[i][j];
        }
        j++;
      }
      return 0;
    }
    i++;
  }
  return 0;
}

// Returns byte offset of field at index fi (proper layout), falls back to fi*8
int cg_field_byte_offset_idx(int *sname, int fi) {
  if (sname == 0) { printf("cc: WARNING: cg_field_byte_offset_idx called with null sname, fi=%d\n", fi); return fi * 8; }
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fbyteoff[i] != 0 && fi >= 0 && fi < cg_snfields[i])
        return cg_s_fbyteoff[i][fi];
      printf("cc: WARNING: no byte offset table for struct '%s' idx, falling back to fi*8\n", sname);
      return fi * 8;
    }
    i++;
  }
  printf("cc: WARNING: struct '%s' not found in cg_field_byte_offset_idx, falling back to fi*8\n", sname);
  return fi * 8;
}

// Returns byte size of field at index fi (proper layout), falls back to 8
int cg_field_byte_size_idx(int *sname, int fi) {
  if (sname == 0) return 8;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      if (cg_s_fbytesize[i] != 0 && fi >= 0 && fi < cg_snfields[i])
        return cg_s_fbytesize[i][fi];
      return 8;
    }
    i++;
  }
  return 8;
}

// Returns struct type name of field at index fi, or 0 if not a struct
int *cg_field_type_idx(int *sname, int fi) {
  if (sname == 0) return 0;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      if (fi >= 0 && fi < cg_snfields[i])
        return cg_sfield_types[i][fi];
      return 0;
    }
    i++;
  }
  return 0;
}

// Returns element size for an array field in a struct (proper layout)
// For int arr[N]: 4, for char: 1, for short: 2, for ptr/long: 8, for struct: struct_byte_size
int cg_field_arr_elem_size(int *sname, int *fname) {
  if (sname == 0 || fname == 0) return 8;
  sname = cg_resolve_sname(sname);
  int i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      int j = 0;
      while (j < cg_snfields[i]) {
        if (cg_sfields[i][j] != 0 && my_strcmp(cg_sfields[i][j], fname) == 0) {
          if (cg_s_fc[i] != 0 && cg_s_fc[i][j]) return 1;
          if (cg_s_fct[i] != 0 && cg_s_fct[i][j]) return 1;
          if (cg_s_fsh[i] != 0 && cg_s_fsh[i][j]) return 2;
          if (cg_s_fp[i] != 0 && cg_s_fp[i][j]) return 8;
          if (cg_s_fl[i] != 0 && cg_s_fl[i][j]) return 8;
          if (cg_sfield_types[i][j] != 0) return cg_struct_byte_size(cg_sfield_types[i][j]);
          return 4;
        }
        j++;
      }
      return 8;
    }
    i++;
  }
  return 8;
}

// Returns bit_width (0 if not a bitfield). Sets *out_bit_offset.
int cg_get_bitfield_info(int *sname, int *fname, int *out_bit_offset) {
  sname = cg_resolve_sname(sname);
  int i = 0;
  int *bw_arr = 0;
  int *bo_arr = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      bw_arr = cg_s_bw[i];
      bo_arr = cg_s_bo[i];
      if (bw_arr == 0) { *out_bit_offset = 0; return 0; }
      int j = 0;
      while (j < cg_snfields[i]) {
        if (my_strcmp(cg_sfields[i][j], fname) == 0) {
          *out_bit_offset = bo_arr[j];
          return bw_arr[j];
        }
        j++;
      }
      *out_bit_offset = 0;
      return 0;
    }
    i++;
  }
  *out_bit_offset = 0;
  return 0;
}

int *cg_intern_string(int *decoded) {
  if (decoded == 0) { decoded = ""; }
  int i = 0;
  while (i < nsp) {
    if (my_strcmp(sp_decoded[i], decoded) == 0) {
      return sp_label[i];
    }
    i++;
  }
  int *num = int_to_str(nsp + 1);
  int *lab = build_str2("l_.str_", num);
  sp_decoded[nsp] = my_strdup(decoded);
  sp_label[nsp] = lab;
  nsp++;
  return lab;
}

// Decode C escape sequences in string literal
int *cg_decode_string(int *lit) {
  if (lit == 0) return "";
  int slen = my_strlen(lit);
  int *buf = my_malloc(slen + 1);
  int j = 0;
  int i = 0;
  int val = 0;
  while (i < slen) {
    int c = __read_byte(lit, i);
    if (c != '\\') {
      __write_byte(buf, j, c);
      j++;
      i++;
      continue;
    }
    i++;
    int ec = __read_byte(lit, i);
    switch (ec) {
    case 'n': __write_byte(buf, j, 10); break;
    case 't': __write_byte(buf, j, 9); break;
    case 'r': __write_byte(buf, j, 13); break;
    case 'a': __write_byte(buf, j, 7); break;
    case 'b': __write_byte(buf, j, 8); break;
    case 'f': __write_byte(buf, j, 12); break;
    case 'v': __write_byte(buf, j, 11); break;
    case '\\': __write_byte(buf, j, 92); break;
    case '"': __write_byte(buf, j, 34); break;
    case '0':
      // \0 or \0xx octal escape in string
      val = 0;
      i++;
      if (i < slen && __read_byte(lit, i) >= '0' && __read_byte(lit, i) <= '7') {
        val = val * 8 + (__read_byte(lit, i) - '0');
        i++;
        if (i < slen && __read_byte(lit, i) >= '0' && __read_byte(lit, i) <= '7') {
          val = val * 8 + (__read_byte(lit, i) - '0');
          i++;
        }
      }
      __write_byte(buf, j, val);
      j++;
      continue;
    case 'x':
      // hex escape \xHH
      val = 0;
      i++;
      while (i < slen) {
        ec = __read_byte(lit, i);
        if (ec >= '0' && ec <= '9') { val = val * 16 + (ec - '0'); }
        else if (ec >= 'a' && ec <= 'f') { val = val * 16 + (ec - 'a' + 10); }
        else if (ec >= 'A' && ec <= 'F') { val = val * 16 + (ec - 'A' + 10); }
        else { break; }
        i++;
      }
      __write_byte(buf, j, val);
      j++;
      continue;
    case '1': case '2': case '3': case '4': case '5': case '6': case '7':
      // octal escape \ooo
      val = ec - '0';
      i++;
      if (i < slen && __read_byte(lit, i) >= '0' && __read_byte(lit, i) <= '7') {
        val = val * 8 + (__read_byte(lit, i) - '0');
        i++;
        if (i < slen && __read_byte(lit, i) >= '0' && __read_byte(lit, i) <= '7') {
          val = val * 8 + (__read_byte(lit, i) - '0');
          i++;
        }
      }
      __write_byte(buf, j, val);
      j++;
      continue;
    default: my_fatal("bad escape in string literal"); break;
    }
    j++;
    i++;
  }
  __write_byte(buf, j, 0);
  return buf;
}

// Escape string for .asciz directive
int cg_emit_escaped_string(int *s) {
  int i = 0;
  while (1) {
    int c = __read_byte(s, i);
    if (c == 0) { break; }
    switch (c) {
    case '\\': emit_ch('\\'); emit_ch('\\'); break;
    case '"': emit_ch('\\'); emit_ch('"'); break;
    case 10: emit_ch('\\'); emit_ch('n'); break;
    case 9: emit_ch('\\'); emit_ch('t'); break;
    case 13: emit_ch('\\'); emit_ch('r'); break;
    default: emit_ch(c); break;
    }
    i++;
  }
  return 0;
}

// Layout computation
int lay_add_slot(int *name, int off, int bsz) {
  lay_name[nlay] = my_strdup(name);
  lay_off[nlay] = off;
  lay_var_bsz[nlay] = bsz;
  nlay++;
  return 0;
}

int lay_walk_expr_cl(struct Expr *e, int *offset) {
  int ci = 0;
  if (e == 0) return 0;
  if (e < 4096) { printf("cc: bad expr ptr %d in lay_walk_expr_cl in %s\n", e, cg_cur_func_name); fflush(0); return 0; }
  if (e->kind < 0 || e->kind > 17) { printf("cc: bad expr kind %d in lay_walk_expr_cl in %s\n", e->kind, cg_cur_func_name); fflush(0); return 0; }
  if (e->kind == ND_COMPOUND_LIT) {
    int *cl_name = build_str2("__cl_", int_to_str(cg_cl_counter));
    cg_cl_counter++;
    int nf = cg_struct_nfields(e->sval);
    {
      int bsz = cg_struct_byte_size(e->sval);
      *offset = *offset + ((bsz + 7) / 8) * 8;
    }
    lay_add_slot(cl_name, *offset, 8);
    if (nlay_sv >= 64) my_fatal("too many struct vars");
    lay_sv_name[nlay_sv] = my_strdup(cl_name);
    lay_sv_type[nlay_sv] = my_strdup(e->sval);
    nlay_sv++;
    // Walk init list elements
    if (e->left != 0 && e->left->kind == ND_INITLIST) {
      ci = 0;
      while (ci < e->left->nargs) {
        lay_walk_expr_cl(e->left->args[ci], offset);
        ci++;
      }
    }
    return 0;
  }
  if (e->kind == ND_BINARY) {
    lay_walk_expr_cl(e->left, offset);
    lay_walk_expr_cl(e->right, offset);
  } else if (e->kind == ND_UNARY || e->kind == ND_CAST) {
    lay_walk_expr_cl(e->left, offset);
  } else if (e->kind == ND_ASSIGN) {
    lay_walk_expr_cl(e->left, offset);
    lay_walk_expr_cl(e->right, offset);
  } else if (e->kind == ND_CALL) {
    ci = 0;
    while (ci < e->nargs) {
      lay_walk_expr_cl(e->args[ci], offset);
      ci++;
    }
  } else if (e->kind == ND_INDEX) {
    lay_walk_expr_cl(e->left, offset);
    lay_walk_expr_cl(e->right, offset);
  } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
    lay_walk_expr_cl(e->left, offset);
  } else if (e->kind == ND_TERNARY) {
    lay_walk_expr_cl(e->left, offset);
    lay_walk_expr_cl(e->right, offset);
    lay_walk_expr_cl(e->args[0], offset);
  } else if (e->kind == ND_POSTINC || e->kind == ND_POSTDEC) {
    lay_walk_expr_cl(e->left, offset);
  } else if (e->kind == ND_STMT_EXPR) {
    // Walk the block inside the statement expression
    struct Stmt *se_blk = e->left;
    if (se_blk != 0 && se_blk->kind == ST_BLOCK) {
      lay_walk_stmts(se_blk->body, se_blk->nbody, offset);
    }
  }
  return 0;
}

int lay_walk_stmts(struct Stmt **stmts, int nstmts, int *offset) {
  int nf = 0;
  int i = 0;
  while (i < nstmts) {
    struct Stmt *st = stmts[i];
    if (st == 0 || st < 4096 || st == (0 - 1)) { i++; continue; }
    if (st->kind < 0 || st->kind > 13) { i++; continue; }
    if (st->kind == ST_VARDECL) {
      for (int j = 0; j < st->ndecls; j++) {
        struct VarDecl *vd = st->decls[j];
        if (cg_find_slot(vd->name) >= 0) {
          // Variable already exists (shadowing in inner block); reuse existing slot
          continue;
        }
        if (vd->is_static) {
          // Static local: record in static local table, use sentinel offset -1
          sl[nsl].name = my_strdup(vd->name);
          sl[nsl].func = my_strdup(cg_cur_func_name);
          sl[nsl].label = build_str2("_sl_", int_to_str(nsl));
          sl[nsl].has_init = 0;
          sl[nsl].init_val = 0;
          sl[nsl].init_list = 0;
          sl[nsl].arr_size = vd->arr_size;
          sl[nsl].stype = vd->stype;
          if (vd->init != 0 && vd->init->kind == ND_NUM) {
            sl[nsl].has_init = 1;
            sl[nsl].init_val = vd->init->ival;
          } else if (vd->init != 0 && vd->init->kind == ND_INITLIST) {
            sl[nsl].has_init = 2;
            sl[nsl].init_list = vd->init;
          }
          nsl++;
          lay_add_slot(vd->name, 0 - 1, 8);
        } else
        if (vd->stype != 0 && vd->is_ptr == 0 && vd->arr_size >= 0) {
          // struct array: allocate arr_size * nfields slots
          nf = cg_struct_nfields(vd->stype);
          {
            int bsz = cg_struct_byte_size(vd->stype);
            *offset = *offset + vd->arr_size * ((bsz + 7) / 8) * 8;
          }
          lay_sv_name[nlay_sv] = my_strdup(vd->name);
          lay_sv_type[nlay_sv] = my_strdup(vd->stype);
          nlay_sv++;
          lay_arr_name[nlay_arr] = my_strdup(vd->name);
          lay_arr_count[nlay_arr] = vd->arr_size;
          lay_arr_inner[nlay_arr] = 0 - 1;
          lay_arr_esz[nlay_arr] = 8;
          nlay_arr++;
        } else if (vd->stype != 0 && vd->is_ptr == 0) {
          nf = cg_struct_nfields(vd->stype);
          {
            int bsz = cg_struct_byte_size(vd->stype);
            *offset = *offset + ((bsz + 7) / 8) * 8;
          }
          lay_sv_name[nlay_sv] = my_strdup(vd->name);
          lay_sv_type[nlay_sv] = my_strdup(vd->stype);
          nlay_sv++;
        } else if (vd->arr_size >= 0 && vd->is_char && vd->is_ptr == 0) {
          // char local array: allocate bytes (rounded up to 8)
          int bytes = ((vd->arr_size + 7) / 8) * 8;
          *offset = *offset + bytes;
          lay_arr_name[nlay_arr] = my_strdup(vd->name);
          lay_arr_count[nlay_arr] = vd->arr_size;
          lay_arr_inner[nlay_arr] = 0 - 1;
          lay_arr_esz[nlay_arr] = 1;
          nlay_arr++;
          lay_char_larr_name[nlay_char_larr] = my_strdup(vd->name);
          nlay_char_larr++;
        } else if (vd->arr_size >= 0) {
          int total = vd->arr_size;
          if (vd->arr_size2 >= 0) { total = vd->arr_size * vd->arr_size2; }
          int esz = 8;
          if (vd->is_short && vd->is_ptr == 0 && vd->stype == 0) { esz = 2; }
          else if (vd->is_char == 0 && vd->is_ptr == 0 && vd->stype == 0 && vd->is_float == 0 && vd->is_short == 0 && vd->is_long == 0) { esz = 4; }
          *offset = *offset + ((total * esz + 7) / 8) * 8;
          lay_arr_name[nlay_arr] = my_strdup(vd->name);
          lay_arr_count[nlay_arr] = total;
          lay_arr_inner[nlay_arr] = vd->arr_size2;
          lay_arr_esz[nlay_arr] = esz;
          nlay_arr++;
        } else {
          *offset = *offset + 8;
          if (vd->stype != 0 && vd->is_ptr == 1) {
            lay_psv_name[nlay_psv] = my_strdup(vd->name);
            lay_psv_type[nlay_psv] = my_strdup(vd->stype);
            nlay_psv++;
          }
        }
        {
          int vbsz = 4;
          if (vd->is_char && vd->is_ptr == 0 && vd->arr_size < 0) { vbsz = 1; }
          else if (vd->is_short && vd->is_ptr == 0 && vd->arr_size < 0) { vbsz = 2; }
          else if (vd->is_long || vd->is_ptr > 0 || vd->stype != 0 || vd->is_float || vd->arr_size >= 0) { vbsz = 8; }
          lay_add_slot(vd->name, *offset, vbsz);
        }
        if (vd->is_unsigned) {
          lay_unsigned_name[nlay_unsigned] = my_strdup(vd->name);
          nlay_unsigned++;
        }
        if (vd->is_char && vd->is_ptr == 1 && vd->arr_size < 0) {
          lay_char_name[nlay_char] = my_strdup(vd->name);
          nlay_char++;
        }
        if (vd->is_char && vd->is_ptr == 1 && vd->arr_size >= 0) {
          lay_char_arr_name[nlay_char_arr] = my_strdup(vd->name);
          nlay_char_arr++;
        }
        if (vd->is_ptr > 0 && vd->stype == 0 && (vd->is_char == 0 || vd->is_ptr >= 2) && vd->arr_size < 0) {
          lay_intptr_name[nlay_intptr] = my_strdup(vd->name);
          {
            int pesz = 8;
            if (vd->is_ptr == 1 && vd->is_char == 0 && vd->is_float == 0 && vd->is_long == 0 && vd->is_short == 0) { pesz = 4; }
            if (vd->is_ptr == 1 && vd->is_short) { pesz = 2; }
            lay_intptr_esz[nlay_intptr] = pesz;
          }
          nlay_intptr++;
        }
        if (vd->is_float) {
          lay_float_name[nlay_float] = my_strdup(vd->name);
          nlay_float++;
        }
        if (vd->is_char && vd->is_ptr == 0 && vd->arr_size < 0) {
          lay_barechar_name[nlay_barechar] = my_strdup(vd->name);
          lay_barechar_unsigned[nlay_barechar] = vd->is_unsigned;
          nlay_barechar++;
        }
        if (vd->is_long || vd->is_ptr > 0 || vd->stype != 0) {
          lay_long_name[nlay_long] = my_strdup(vd->name);
          nlay_long++;
        }
      }
    } else if (st->kind == ST_IF) {
      lay_walk_stmts(st->body, st->nbody, offset);
      if (st->body2 != 0) {
        lay_walk_stmts(st->body2, st->nbody2, offset);
      }
    } else if (st->kind == ST_WHILE) {
      lay_walk_stmts(st->body, st->nbody, offset);
    } else if (st->kind == ST_FOR) {
      if (st->init != 0 && st->init->kind == ST_VARDECL) {
        struct Stmt *arr[1];
        arr[0] = st->init;
        lay_walk_stmts(arr, 1, offset);
      }
      lay_walk_stmts(st->body, st->nbody, offset);
    } else if (st->kind == ST_DOWHILE) {
      lay_walk_stmts(st->body, st->nbody, offset);
    } else if (st->kind == ST_LABEL) {
      lay_walk_stmts(st->body, st->nbody, offset);
    } else if (st->kind == ST_SWITCH) {
      for (int ci = 0; ci < st->ncases; ci++) {
        lay_walk_stmts(st->case_bodies[ci], st->case_nbodies[ci], offset);
      }
      if (st->default_body != 0) {
        lay_walk_stmts(st->default_body, st->ndefault, offset);
      }
    } else if (st->kind == ST_BLOCK) {
      lay_walk_stmts(st->body, st->nbody, offset);
    }
    // Scan expressions for compound literals
    if (st->kind == ST_EXPR || st->kind == ST_RETURN ||
        st->kind == ST_IF || st->kind == ST_WHILE || st->kind == ST_COMPUTED_GOTO) {
      lay_walk_expr_cl(st->expr, offset);
    } else if (st->kind == ST_VARDECL) {
      for (int vi = 0; vi < st->ndecls; vi++) {
        if (st->decls[vi]->init != 0) {
          lay_walk_expr_cl(st->decls[vi]->init, offset);
        }
      }
    } else if (st->kind == ST_FOR) {
      lay_walk_expr_cl(st->expr, offset);
      lay_walk_expr_cl(st->expr2, offset);
    }
    i++;
  }
  return 0;
}

int cg_is_unsigned(int *name) {
  int i = 0;
  while (i < nlay_unsigned) {
    if (my_strcmp(lay_unsigned_name[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_is_barechar(int *name) {
  int i = 0;
  while (i < nlay_barechar) {
    if (my_strcmp(lay_barechar_name[i], name) == 0) { return lay_barechar_unsigned[i] ? 2 : 1; }
    i++;
  }
  // Check globals, but only if name is not a local variable
  if (cg_is_local(name) == 0) {
    i = 0;
    while (i < ncg_g) {
      if (cgg[i].is_barechar && my_strcmp(cgg[i].name, name) == 0) { return cgg[i].is_barechar; }
      i++;
    }
  }
  return 0;
}

int cg_is_char(int *name) {
  int i = 0;
  while (i < nlay_char) {
    if (my_strcmp(lay_char_name[i], name) == 0) { return 1; }
    i++;
  }
  // Check global char* variables, but only if name is not a local variable
  if (cg_is_local(name) == 0) {
    i = 0;
    while (i < ncg_g) {
      if (cgg[i].is_char && my_strcmp(cgg[i].name, name) == 0) { return 1; }
      i++;
    }
  }
  return 0;
}

int cg_is_char_arr(int *name) {
  int i = 0;
  while (i < nlay_char_arr) {
    if (my_strcmp(lay_char_arr_name[i], name) == 0) { return 1; }
    i++;
  }
  // Also check global char* arrays, but only if name is not a local variable
  if (cg_is_local(name) == 0) {
    i = 0;
    while (i < ncg_g) {
      if (cgg[i].is_char_arr && my_strcmp(cgg[i].name, name) == 0) { return 1; }
      i++;
    }
  }
  return 0;
}

int *cg_global_stype(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].stype; }
    i++;
  }
  return 0;
}

int *cg_global_ptr_stype(int *name) {
  if (cg_is_local(name)) return 0;
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg[i].ptr_stype; }
    i++;
  }
  return 0;
}

int cg_is_char_larr(int *name) {
  int i = 0;
  while (i < nlay_char_larr) {
    if (my_strcmp(lay_char_larr_name[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_is_intptr(int *name) {
  int i = 0;
  while (i < nlay_intptr) {
    if (my_strcmp(lay_intptr_name[i], name) == 0) {
      return 1;
    }
    i++;
  }
  // Check global int pointer variables, but only if name is not a local variable
  if (cg_is_local(name) == 0) {
    i = 0;
    while (i < ncg_g) {
      if (cgg[i].is_intptr && my_strcmp(cgg[i].name, name) == 0) { return 1; }
      i++;
    }
  }
  return 0;
}

int cg_arr_esz(int *name) {
  int i = 0;
  while (i < nlay_arr) {
    if (my_strcmp(lay_arr_name[i], name) == 0) {
      return lay_arr_esz[i];
    }
    i++;
  }
  return 0;
}

int cg_intptr_esz(int *name) {
  int i = 0;
  while (i < nlay_intptr) {
    if (my_strcmp(lay_intptr_name[i], name) == 0) {
      return lay_intptr_esz[i];
    }
    i++;
  }
  return 0;
}

int cg_is_float(int *name) {
  int i = 0;
  while (i < nlay_float) {
    if (my_strcmp(lay_float_name[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_is_long_or_ptr(int *name) {
  int i = 0;
  while (i < nlay_long) {
    if (my_strcmp(lay_long_name[i], name) == 0) { return 1; }
    i++;
  }
  // Arrays evaluate to pointers (64-bit)
  i = 0;
  while (i < nlay_arr) {
    if (my_strcmp(lay_arr_name[i], name) == 0) { return 1; }
    i++;
  }
  // Also check globals — pointers, arrays, and long types are 64-bit
  if (cg_is_global(name)) { return cg_global_is_array(name) || cg_is_intptr(name) || cg_is_char(name) || find_glv_is_long(name); }
  return 0;
}

int func_returns_long_or_ptr(int *name) {
  return func_returns_ptr(name) || (func_ret_stype(name) != 0);
}

int func_returns_float(int *name) {
  int i = 0;
  while (i < n_float_ret) {
    if (my_strcmp(float_ret_names[i], name) == 0) { return 1; }
    i++;
  }
  return 0;
}

int cg_var_bsz(int *name) {
  int i = nlay - 1;
  while (i >= 0) {
    if (my_strcmp(lay_name[i], name) == 0) { return lay_var_bsz[i]; }
    i--;
  }
  return 0;
}

int cg_global_var_bsz(int *name) {
  int i = 0;
  while (i < ncg_g) {
    if (my_strcmp(cgg[i].name, name) == 0) { return cgg_var_bsz[i]; }
    i++;
  }
  return 0;
}

// Check if an expression evaluates to a long/pointer (64-bit) type
int expr_is_unsigned(struct Expr *e) {
  if (e == 0) return 0;
  if (e->kind == ND_VAR) return cg_is_unsigned(e->sval);
  if (e->kind == ND_CALL) return func_returns_unsigned(e->sval);
  if (e->kind == ND_CAST && (e->ival == 4 || e->ival == 6 || e->ival == 7)) return 1;
  if (e->kind == ND_BINARY) {
    if (expr_is_unsigned(e->left) || expr_is_unsigned(e->right)) return 1;
  }
  if (e->kind == ND_UNARY) return expr_is_unsigned(e->left);
  return 0;
}

int expr_is_long(struct Expr *e) {
  if (e == 0) return 0;
  if (e->kind == ND_VAR) return cg_is_long_or_ptr(e->sval);
  if (e->kind == ND_CALL) return func_returns_long_or_ptr(e->sval);
  if (e->kind == ND_UNARY && e->sval != 0 && e->sval[0] == '&') return 1;
  if (e->kind == ND_STRLIT) return 1;
  if (e->kind == ND_CAST && e->ival == 2) return 1;
  if (e->kind == ND_BINARY) {
    if (expr_is_long(e->left) || expr_is_long(e->right)) return 1;
  }
  return 0;
}

// Check if an expression evaluates to a float type
int expr_is_float(struct Expr *e) {
  if (e == 0) return 0;
  if (e->kind == ND_NUM && e->nargs == 1) return 1; // float literal (nargs=1 as marker)
  if (e->kind == ND_VAR && cg_is_float(e->sval)) return 1;
  if (e->kind == ND_CALL && func_returns_float(e->sval)) return 1;
  if (e->kind == ND_BINARY) {
    // Comparison operators always return int, even for float operands
    if (my_strcmp(e->sval2, "==") == 0 || my_strcmp(e->sval2, "!=") == 0 ||
        my_strcmp(e->sval2, "<") == 0 || my_strcmp(e->sval2, "<=") == 0 ||
        my_strcmp(e->sval2, ">") == 0 || my_strcmp(e->sval2, ">=") == 0 ||
        my_strcmp(e->sval2, "&&") == 0 || my_strcmp(e->sval2, "||") == 0) return 0;
    // Bitwise/shift/modulo ops on float don't make sense - treat as int
    if (my_strcmp(e->sval2, "|") == 0 || my_strcmp(e->sval2, "&") == 0 ||
        my_strcmp(e->sval2, "^") == 0 || my_strcmp(e->sval2, "<<") == 0 ||
        my_strcmp(e->sval2, ">>") == 0 || my_strcmp(e->sval2, "%") == 0) return 0;
    return expr_is_float(e->left) || expr_is_float(e->right);
  }
  if (e->kind == ND_UNARY) return expr_is_float(e->left);
  if (e->kind == ND_ASSIGN) return expr_is_float(e->left);
  if (e->kind == ND_TERNARY) return expr_is_float(e->right) || expr_is_float(e->args[0]);
  if (e->kind == ND_CAST) return e->ival == 1; // float cast
  return 0;
}

int cg_get_arr_inner(int *name) {
  int i = 0;
  while (i < nlay_arr) {
    if (my_strcmp(lay_arr_name[i], name) == 0) { return lay_arr_inner[i]; }
    i++;
  }
  return 0 - 1;
}

int layout_func(struct FuncDef *f) {
  nlay = 0;
  nlay_arr = 0;
  nlay_sv = 0;
  nlay_psv = 0;
  nlay_unsigned = 0;
  nlay_char = 0;
  nlay_char_arr = 0;
  nlay_char_larr = 0;
  nlay_intptr = 0;
  nlay_float = 0;
  nlay_barechar = 0;
  nlay_long = 0;
  int offset = 0;

  for (int i = 0; i < f->nparams; i++) {
    if (f->param_stypes != 0 && f->param_stypes[i] != 0) {
      int nf = cg_struct_nfields(f->param_stypes[i]);
      {
        int bsz = cg_struct_byte_size(f->param_stypes[i]);
        offset += ((bsz + 7) / 8) * 8;
      }
      lay_add_slot(f->params[i], offset, 8);
      lay_sv_name[nlay_sv] = my_strdup(f->params[i]);
      lay_sv_type[nlay_sv] = my_strdup(f->param_stypes[i]);
      nlay_sv++;
    } else if (i < 8) {
      offset += 8;
      {
        int pbsz = 4;
        if (f->param_is_char != 0 && f->param_is_char[i]) { pbsz = 8; }
        else if (f->param_is_short != 0 && f->param_is_short[i]) { pbsz = 2; }
        else if (f->param_is_long != 0 && f->param_is_long[i]) { pbsz = 8; }
        else if (f->param_is_intptr != 0 && f->param_is_intptr[i]) { pbsz = 8; }
        else if (f->param_stypes != 0 && f->param_stypes[i] != 0) { pbsz = 8; }
        else if (f->param_is_float != 0 && f->param_is_float[i]) { pbsz = 8; }
        lay_add_slot(f->params[i], offset, pbsz);
      }
    } else {
      // Stack-passed params: at [x29+16+(i-8)*8]. Use negative offset as signal.
      int above_off = 16 + (i - 8) * 8;
      lay_add_slot(f->params[i], 0 - above_off, 8);
    }
    if (f->param_is_char != 0 && f->param_is_char[i]) {
      lay_char_name[nlay_char] = my_strdup(f->params[i]);
      nlay_char++;
    }
    if (f->param_is_unsigned != 0) {
      if (f->param_is_unsigned[i]) {
        lay_unsigned_name[nlay_unsigned] = my_strdup(f->params[i]);
        nlay_unsigned++;
      }
    }
    if (f->param_is_intptr != 0 && f->param_is_intptr[i]) {
      lay_intptr_name[nlay_intptr] = my_strdup(f->params[i]);
      {
        int pesz = 4;
        if (f->param_is_short != 0 && f->param_is_short[i]) { pesz = 2; }
        if (f->param_is_long != 0 && f->param_is_long[i]) { pesz = 8; }
        if (f->param_is_intptr[i] >= 2) { pesz = 8; }
        if (f->param_stypes != 0 && f->param_stypes[i] != 0) { pesz = 8; }
        lay_intptr_esz[nlay_intptr] = pesz;
      }
      nlay_intptr++;
    }
    if (f->param_is_float != 0 && f->param_is_float[i]) {
      lay_float_name[nlay_float] = my_strdup(f->params[i]);
      nlay_float++;
    }
    if ((f->param_is_long != 0 && f->param_is_long[i]) ||
        (f->param_is_intptr != 0 && f->param_is_intptr[i]) ||
        (f->param_is_char != 0 && f->param_is_char[i]) ||
        (f->param_stypes != 0 && f->param_stypes[i] != 0)) {
      lay_long_name[nlay_long] = my_strdup(f->params[i]);
      nlay_long++;
    }
    // Check bare char params from side table
    {
      int bci = 0;
      while (bci < nbarechar_funcs) {
        if (my_strcmp(barechar_func_names[bci], f->name) == 0) {
          if (barechar_param_data[bci] != 0 && barechar_param_data[bci][i]) {
            lay_barechar_name[nlay_barechar] = my_strdup(f->params[i]);
            lay_barechar_unsigned[nlay_barechar] = (barechar_param_data[bci][i] == 2) ? 1 : 0;
            nlay_barechar++;
          }
          break;
        }
        bci++;
      }
    }
  }


  lay_walk_stmts(f->body, f->nbody, &offset);

  lay_stack_size = ((offset + 15) / 16) * 16;
  return 0;
}

// Code generation
int gen_addr(struct Expr *e) {
  int fi = 0;
  if (e->kind == ND_VAR) {
    int off = cg_find_slot(e->sval);
    // Stack-passed parameter: offset <= -2 means positive offset from x29
    if (off <= (0 - 2)) {
      int pos_off = 0 - off;
      emit_add_imm("x0", "x29", pos_off);
      return 0;
    }
    // Check for static local (sentinel offset -1)
    if (off == (0 - 1)) {
      // Find the static local label matching var name
      int sli = 0;
      while (sli < nsl) {
        if (my_strcmp(sl[sli].name, e->sval) == 0 && my_strcmp(sl[sli].func, cg_cur_func_name) == 0) {
          emit_s("\tadrp\tx0, ");
          emit_s(sl[sli].label);
          emit_line("@PAGE");
          emit_s("\tadd\tx0, x0, ");
          emit_s(sl[sli].label);
          emit_line("@PAGEOFF");
          return 0;
        }
        sli++;
      }
    }
    if (off < 0) {
      // Check if it's a global variable
      if (cg_is_global(e->sval)) {
        emit_s("\tadrp\tx0, _");
        emit_s(e->sval);
        emit_line("@PAGE");
        emit_s("\tadd\tx0, x0, _");
        emit_s(e->sval);
        emit_line("@PAGEOFF");
        return 0;
      }
      // Check if it's a function name (for function pointers)
      if (is_known_func(e->sval)) {
        if (is_defined_func(e->sval)) {
          // Function defined in this compilation unit — direct address
          emit_s("\tadrp\tx0, _");
          emit_s(e->sval);
          emit_line("@PAGE");
          emit_s("\tadd\tx0, x0, _");
          emit_s(e->sval);
          emit_line("@PAGEOFF");
        } else {
          // External function — use GOT
          emit_s("\tadrp\tx0, _");
          emit_s(e->sval);
          emit_line("@GOTPAGE");
          emit_s("\tldr\tx0, [x0, _");
          emit_s(e->sval);
          emit_line("@GOTPAGEOFF]");
        }
        return 0;
      }
      // Check if it's an extern variable (registered in glv table)
      {
        int ev_found = 0;
        for (int evi = 0; evi < nglv; evi++) {
          if (my_strcmp(glv[evi].name, e->sval) == 0) { ev_found = 1; break; }
        }
        if (ev_found) {
          // Extern variable — use GOT
          emit_s("\tadrp\tx0, _");
          emit_s(e->sval);
          emit_line("@GOTPAGE");
          emit_s("\tldr\tx0, [x0, _");
          emit_s(e->sval);
          emit_line("@GOTPAGEOFF]");
          return 0;
        }
      }
      printf("Unknown variable: %s in %s\n", e->sval, cg_cur_func_name);
      fflush(0);
      emit_line("\tmov\tx0, #0");
      return 0;
    }
    if (off <= 255) {
      emit_s("\tsub\tx0, x29, #");
      emit_num(off);
      emit_ch('\n');
    } else {
      emit_mov_imm("x0", off);
      emit_line("\tsub\tx0, x29, x0");
    }
    return 0;
  }
  if (e->kind == ND_UNARY && e->ival == '*') {
    gen_value(e->left);
    return 0;
  }
  if (e->kind == ND_INDEX) {
    int *idx_stype = 0;
    int idx_stride = 8;
    int idx_is_char = 0;
    if (e->left->kind == ND_VAR) {
      if (cg_is_char(e->left->sval)) {
        idx_stride = 1;
        idx_is_char = 1;
      } else if (cg_is_char_larr(e->left->sval)) {
        idx_stride = 1;
        idx_is_char = 1;
      } else if (cg_global_is_bare_char_arr(e->left->sval)) {
        idx_stride = 1;
        idx_is_char = 1;
      } else {
        idx_stype = cg_structvar_type(e->left->sval);
        if (idx_stype == 0) {
          idx_stype = cg_ptr_structvar_type(e->left->sval);
        }
        // Check global struct type (non-pointer embedded struct arrays)
        if (idx_stype == 0) {
          idx_stype = cg_global_stype(e->left->sval);
        }
        // Check global pointer-to-struct type
        if (idx_stype == 0) {
          idx_stype = cg_global_ptr_stype(e->left->sval);
        }
        // Check for 2D array: stride = inner_dim * esz
        if (idx_stype == 0) {
          int inner = cg_get_arr_inner(e->left->sval);
          if (inner >= 0) {
            int inner_esz = cg_arr_esz(e->left->sval);
            if (inner_esz > 0 && inner_esz < 8) {
              idx_stride = inner * inner_esz;
            } else {
              idx_stride = inner * 8;
            }
          }
        }
        // Check if this is a plain int/short array or int/short pointer
        if (idx_stype == 0 && idx_stride == 8 && idx_is_char == 0) {
          int aesz = cg_arr_esz(e->left->sval);
          if (aesz > 0 && aesz < 8) { idx_stride = aesz; }
          if (idx_stride == 8) {
            int iesz = cg_intptr_esz(e->left->sval);
            if (iesz > 0 && iesz < 8) { idx_stride = iesz; }
          }
          if (idx_stride == 8) {
            int gesz = cg_global_esz(e->left->sval);
            if (gesz > 0 && gesz < 8) { idx_stride = gesz; }
          }
          if (idx_stride == 8 && cg_global_is_array(e->left->sval) == 0) {
            int gpesz = cg_global_ptr_esz(e->left->sval);
            if (gpesz > 0 && gpesz < 8) { idx_stride = gpesz; }
          }
        }
      }
    }
    // Check if indexing a char* struct field (e.g. s->buf[i])
    if ((e->left->kind == ND_ARROW || e->left->kind == ND_FIELD) && idx_is_char == 0) {
      if (cg_field_is_char(e->left->sval2, e->left->sval) && (cg_field_is_ptr(e->left->sval2, e->left->sval) == 0 || cg_field_is_array(e->left->sval2, e->left->sval) == 0)) {
        idx_stride = 1;
        idx_is_char = 1;
      }
      // Proper layout: determine element stride for array fields in structs
      if (idx_is_char == 0 && cg_field_is_array(e->left->sval2, e->left->sval) > 0) {
        int fp = cg_field_is_ptr(e->left->sval2, e->left->sval);
        if (fp == 0) {
          int es = cg_field_arr_elem_size(e->left->sval2, e->left->sval);
          idx_stride = es;
          if (es == 1) { idx_is_char = 1; }
        }
      }
      // Check if field has a struct type (e.g. collection->defaults[i] where defaults is default_t*)
      // Only use struct stride for:
      //   - embedded struct arrays (is_ptr == 0): stride = sizeof(struct)
      //   - single pointer to struct (is_ptr == 1): stride = sizeof(struct)
      // NOT for double pointer (is_ptr >= 2): stride = 8 (array of pointers)
      if (idx_stype == 0 && idx_is_char == 0) {
        int *fs = field_stype(e->left->sval2, e->left->sval);
        int fp = cg_field_is_ptr(e->left->sval2, e->left->sval);
        if (fs != 0 && fp <= 1) { idx_stype = fs; }
      }
      // Check if field is an int*/short*/long* pointer (non-array, non-char, non-struct)
      // e.g. vm->prog[i] where prog is int* — stride should be 4, not 8
      if (idx_stype == 0 && idx_is_char == 0 && idx_stride == 8) {
        int fp2 = cg_field_is_ptr(e->left->sval2, e->left->sval);
        int fa2 = cg_field_is_array(e->left->sval2, e->left->sval);
        if (fp2 > 0 && fa2 == 0) {
          int fc2 = cg_field_is_char(e->left->sval2, e->left->sval);
          if (fc2 == 0 && fp2 == 1) {
            // Single pointer to non-char, non-struct: check short/long/plain
            if (cg_field_is_short(e->left->sval2, e->left->sval)) {
              idx_stride = 2;
            } else if (cg_field_is_long(e->left->sval2, e->left->sval)) {
              idx_stride = 8;
            } else {
              idx_stride = 4;
            }
          }
          // fp2 >= 2: pointer to pointer, stride = 8 (already default)
        }
      }
    }
    // Check if indexing result of char* array (e.g. names[i][j])
    if (e->left->kind == ND_INDEX && idx_is_char == 0 && e->left->left != 0 && e->left->left->kind == ND_VAR) {
      if (cg_is_char_arr(e->left->left->sval)) {
        idx_stride = 1;
        idx_is_char = 1;
      }
      // Check if indexing a 2D int/short array (e.g. arr[i][j])
      if (idx_is_char == 0 && idx_stype == 0 && idx_stride == 8) {
        int aesz2 = cg_arr_esz(e->left->left->sval);
        if (aesz2 > 0 && aesz2 < 8) { idx_stride = aesz2; }
      }
      // Check if indexing through global int* array (e.g. cg_s_fa[i][j])
      if (idx_is_char == 0 && idx_stype == 0 && idx_stride == 8) {
        int gpe = cg_global_ptr_esz(e->left->left->sval);
        if (gpe > 0 && gpe < 8) { idx_stride = gpe; }
      }
      // Check if double-indexing a short**/int** global (e.g. texturecolumnlump[tex][col])
      if (idx_is_char == 0 && idx_stype == 0 && idx_stride == 8) {
        if (find_glv_is_short(e->left->left->sval)) { idx_stride = 2; }
        else if (cg_is_barechar(e->left->left->sval)) { idx_stride = 1; idx_is_char = 1; }
      }
    }
    if (idx_stype != 0) {
      idx_stride = cg_struct_byte_size(idx_stype);
    }
    gen_value(e->left);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->right);
    if (idx_is_char) {
      // No scaling needed for char pointers (stride = 1)
    } else if (idx_stride == 8) {
      emit_line("\tlsl\tx0, x0, #3");
    } else if (idx_stride == 4) {
      emit_line("\tlsl\tx0, x0, #2");
    } else if (idx_stride == 2) {
      emit_line("\tlsl\tx0, x0, #1");
    } else {
      emit_s("\tmov\tx1, #");
      emit_num(idx_stride);
      emit_ch('\n');
      emit_line("\tmul\tx0, x0, x1");
    }
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tadd\tx0, x1, x0");
    return 0;
  }
  if (e->kind == ND_FIELD) {
    // Special case: arr[i].field — use struct type from field node for stride
    if (e->left->kind == ND_INDEX) {
      int *fi_stype = 0;
      int fi_stride = 8;
      if (e->left->left->kind == ND_VAR) {
        fi_stype = cg_structvar_type(e->left->left->sval);
        if (fi_stype == 0) {
          fi_stype = cg_ptr_structvar_type(e->left->left->sval);
        }
      }
      // Fallback: use the struct type from the field node
      if (fi_stype == 0) {
        fi_stype = e->sval2;
      }
      if (fi_stype != 0) {
        fi_stride = cg_struct_byte_size(fi_stype);
      }
      gen_value(e->left->left);
      emit_line("\tstr\tx0, [sp, #-16]!");
      gen_value(e->left->right);
      if (fi_stride == 8) {
        emit_line("\tlsl\tx0, x0, #3");
      } else {
        emit_s("\tmov\tx1, #"); emit_num(fi_stride); emit_ch('\n');
        emit_line("\tmul\tx0, x0, x1");
      }
      emit_line("\tldr\tx1, [sp], #16");
      emit_line("\tadd\tx0, x1, x0");
      {
        int boff = cg_field_byte_offset(e->sval2, e->sval);
        if (boff > 0) { emit_add_imm("x0", "x0", boff); }
      }
      return 0;
    }
    gen_addr(e->left);
    {
      int boff = cg_field_byte_offset(e->sval2, e->sval);
      if (boff > 0) { emit_add_imm("x0", "x0", boff); }
    }
    return 0;
  }
  if (e->kind == ND_ARROW) {
    gen_value(e->left);
    {
      int boff = cg_field_byte_offset(e->sval2, e->sval);
      if (boff > 0) { emit_add_imm("x0", "x0", boff); }
    }
    return 0;
  }
  if (e->kind == ND_COMPOUND_LIT) {
    gen_value(e);
    return 0;
  }
  if (e->kind == ND_CALL) {
    // Struct-returning function call in lvalue context
    // Call returns pointer to struct in x0 — that IS the address
    gen_value(e);
    return 0;
  }
  if (e->kind == ND_UNARY && e->ival == '*') {
    // Dereference as lvalue: addr of *ptr is just ptr's value
    gen_value(e->left);
    return 0;
  }
  printf("cc: not an lvalue (kind=%d ival=%d) in %s\n", e->kind, e->ival, cg_cur_func_name);
  fflush(0);
  emit_line("\tmov\tx0, #0");
  return 0;
}

int gen_val_cast(struct Expr *e) {
  gen_value(e->left);
  if (e->ival == 1 && expr_is_float(e->left) == 0) {
    // (float/double)int_expr: int to float
    emit_line("\tscvtf\td0, x0");
    emit_line("\tfmov\tx0, d0");
  } else if ((e->ival == 2 || e->ival == 7) && expr_is_float(e->left)) {
    // (int)float_expr: float to int
    emit_line("\tfmov\td0, x0");
    emit_line("\tfcvtzs\tx0, d0");
  } else if (e->ival == 3) {
    // (char) -> sign extend byte
    emit_line("\tsxtb\tx0, w0");
  } else if (e->ival == 4) {
    // (unsigned char) -> zero extend byte
    emit_line("\tuxtb\tw0, w0");
    emit_line("\tmov\tx0, x0");
  } else if (e->ival == 5) {
    // (short) -> sign extend halfword
    emit_line("\tsxth\tx0, w0");
  } else if (e->ival == 6) {
    // (unsigned short) -> zero extend halfword
    emit_line("\tuxth\tw0, w0");
    emit_line("\tmov\tx0, x0");
  }
#ifdef __STDC__
  return 0;
#else
  return;
#endif
}

int gen_val_num(struct Expr *e) {
  long val = e->ival;
  // Float literals need full 64-bit load via unsigned bit extraction
  if (e->nargs == 1) {
    int w0 = val & 65535;
    int v1 = val;
    v1 = val >> 16;
    int w1 = v1 & 65535;
    v1 = (val >> 16) >> 16;
    int w2 = v1 & 65535;
    v1 = ((val >> 16) >> 16) >> 16;
    int w3 = v1 & 65535;
    emit_s("\tmovz\tx0, #"); emit_unum(w0); emit_ch('\n');
    if (w1 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w1); emit_s(", lsl #16\n"); }
    if (w2 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w2); emit_s(", lsl #32\n"); }
    if (w3 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w3); emit_s(", lsl #48\n"); }
  } else if (val >= -65535 && val <= 65535) {
    emit_s("\tmov\tx0, #");
    emit_num(val);
    emit_ch('\n');
  } else {
    int lo = val & 65535;
    int w1 = (val >> 16) & 65535;
    int w2 = ((val >> 16) >> 16) & 65535;
    int w3 = (((val >> 16) >> 16) >> 16) & 65535;
    emit_s("\tmovz\tx0, #");
    emit_unum(lo);
    emit_ch('\n');
    if (w1 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w1); emit_s(", lsl #16\n"); }
    if (w2 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w2); emit_s(", lsl #32\n"); }
    if (w3 != 0) { emit_s("\tmovk\tx0, #"); emit_unum(w3); emit_s(", lsl #48\n"); }
  }
  return 0;
}

int gen_load_by_bsz(int bsz, int is_unsigned) {
  if (bsz == 1) {
    // ARM64: char is unsigned by default, always zero-extend
    emit_line("\tldrb\tw0, [x0]");
  } else if (bsz == 2) {
    if (is_unsigned) { emit_line("\tldrh\tw0, [x0]"); }
    else { emit_line("\tldrsh\tx0, [x0]"); }
  } else if (bsz == 4) {
    if (is_unsigned) { emit_line("\tldr\tw0, [x0]"); }
    else { emit_line("\tldrsw\tx0, [x0]"); }
  } else {
    emit_line("\tldr\tx0, [x0]");
  }
  return 0;
}

int gen_val_var(struct Expr *e) {
  // Function name used as value: load its address (don't dereference)
  if (cg_find_slot(e->sval) < 0 && cg_is_global(e->sval) == 0 && is_known_func(e->sval)) {
    gen_addr(e);
    return 0;
  }
  gen_addr(e);
  {
    int is_local = (cg_find_slot(e->sval) >= 0);
    if (is_local) {
      if (cg_is_array(e->sval) == 0 && cg_is_structvar(e->sval) == 0) {
        int vbsz = cg_var_bsz(e->sval);
        if (vbsz == 1) {
          int vu = cg_is_unsigned(e->sval);
          if (vu) { emit_line("\tldrb\tw0, [x0]"); }
          else { emit_line("\tldrsb\tx0, [x0]"); }
        } else if (vbsz == 2) {
          int vu = cg_is_unsigned(e->sval);
          if (vu) { emit_line("\tldrh\tw0, [x0]"); }
          else { emit_line("\tldrsh\tx0, [x0]"); }
        } else if (vbsz == 4) {
          int vu = cg_is_unsigned(e->sval);
          if (vu) { emit_line("\tldr\tw0, [x0]"); }
          else { emit_line("\tldrsw\tx0, [x0]"); }
        } else {
          emit_line("\tldr\tx0, [x0]");
        }
      }
    } else {
      if (cg_is_array(e->sval) == 0 && cg_is_structvar(e->sval) == 0 && cg_global_is_array(e->sval) == 0 && cg_global_stype(e->sval) == 0) {
        emit_line("\tldr\tx0, [x0]");
      }
    }
  }
  return 0;
}

int gen_val_field_arrow(struct Expr *e) {
  int bf_bit_off = 0;
  int bf_width = 0;
  int bf_mask = 0;
  bf_bit_off = 0;
  bf_width = cg_get_bitfield_info(e->sval2, e->sval, &bf_bit_off);
  gen_addr(e);
  if (cg_field_is_array(e->sval2, e->sval)) {
    return 0;
  }
  {
    int bsz = cg_field_byte_size(e->sval2, e->sval);
    int f_unsigned = cg_field_is_unsigned(e->sval2, e->sval);
    gen_load_by_bsz(bsz, f_unsigned);
  }
  if (bf_width > 0) {
    if (bf_bit_off > 0) {
      emit_s("\tlsr\tx0, x0, #");
      emit_num(bf_bit_off);
      emit_ch('\n');
    }
    bf_mask = (1 << bf_width) - 1;
    if (bf_mask <= 65535) {
      emit_s("\tand\tx0, x0, #");
      emit_num(bf_mask);
      emit_ch('\n');
    } else {
      emit_mov_imm("x9", bf_mask);
      emit_line("\tand\tx0, x0, x9");
    }
  }
  return 0;
}

int gen_val_index(struct Expr *e) {
  // For 2D array: arr[i] returns row address (no load), arr[i][j] loads
  if (e->left->kind == ND_VAR && cg_get_arr_inner(e->left->sval) >= 0) {
    // This is indexing a 2D array - return row pointer, don't load
    gen_addr(e);
    return 0;
  }
  // Global struct array: g_table[i] returns struct address (no load)
  if (e->left->kind == ND_VAR && cg_global_is_array(e->left->sval) && cg_global_stype(e->left->sval) != 0) {
    gen_addr(e);
    return 0;
  }
  // Local struct array: items[i] returns struct address (no load)
  if (e->left->kind == ND_VAR && cg_is_array(e->left->sval) && cg_structvar_type(e->left->sval) != 0) {
    gen_addr(e);
    return 0;
  }
  gen_addr(e);
  if (e->left->kind == ND_VAR && (cg_is_char(e->left->sval) || cg_is_char_larr(e->left->sval) || cg_global_is_bare_char_arr(e->left->sval))) {
    emit_line("\tldrb\tw0, [x0]");
  } else if ((e->left->kind == ND_ARROW || e->left->kind == ND_FIELD) && cg_field_is_char(e->left->sval2, e->left->sval) && (cg_field_is_ptr(e->left->sval2, e->left->sval) == 0 || cg_field_is_array(e->left->sval2, e->left->sval) == 0)) {
    emit_line("\tldrb\tw0, [x0]");
  } else if (e->left->kind == ND_INDEX && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_char_arr(e->left->left->sval)) {
    // char *arr[N]; arr[i][j] — second index should byte-load
    emit_line("\tldrb\tw0, [x0]");
  } else if ((e->left->kind == ND_ARROW || e->left->kind == ND_FIELD) && cg_field_is_array(e->left->sval2, e->left->sval) > 0 && cg_field_is_ptr(e->left->sval2, e->left->sval) == 0) {
    int es = cg_field_arr_elem_size(e->left->sval2, e->left->sval);
    int fu = cg_field_is_unsigned(e->left->sval2, e->left->sval);
    gen_load_by_bsz(es, fu);
  } else if ((e->left->kind == ND_ARROW || e->left->kind == ND_FIELD) && cg_field_is_ptr(e->left->sval2, e->left->sval) == 1 && cg_field_is_char(e->left->sval2, e->left->sval) == 0 && field_stype(e->left->sval2, e->left->sval) == 0) {
    // Struct field pointer indexing: s->field[i] where field is int*/short*
    { int fp_bsz = 4; int fp_u = cg_field_is_unsigned(e->left->sval2, e->left->sval);
    if (cg_field_is_short(e->left->sval2, e->left->sval)) { fp_bsz = 2; }
    else if (cg_field_is_long(e->left->sval2, e->left->sval)) { fp_bsz = 8; }
    gen_load_by_bsz(fp_bsz, fp_u); }
  } else if (e->left->kind == ND_VAR) {
    int aesz = cg_arr_esz(e->left->sval);
    if (aesz == 0) { aesz = cg_intptr_esz(e->left->sval); }
    if (aesz == 0 && cg_global_is_array(e->left->sval) == 0) { aesz = cg_global_ptr_esz(e->left->sval); }
    if (aesz == 0) { aesz = cg_global_esz(e->left->sval); }
    if (aesz == 4) { emit_line("\tldrsw\tx0, [x0]"); }
    else if (aesz == 2) { emit_line("\tldrsh\tx0, [x0]"); }
    else { emit_line("\tldr\tx0, [x0]"); }
  } else if (e->left->kind == ND_INDEX && e->left->left != 0 && e->left->left->kind == ND_VAR) {
    // 2D array element load: arr[i][j] or ptr_ptr[i][j]
    int aesz = cg_arr_esz(e->left->left->sval);
    if (aesz == 0) { aesz = cg_global_ptr_esz(e->left->left->sval); }
    if (aesz == 0) { aesz = cg_global_esz(e->left->left->sval); }
    // For short**/char** double-pointer indexing, use inner element size
    if (aesz == 0 || aesz == 8) {
      if (find_glv_is_short(e->left->left->sval) || find_lv_is_short(e->left->left->sval)) { aesz = 2; }
      else if (cg_is_barechar(e->left->left->sval)) { aesz = 1; }
    }
    if (aesz == 4) { emit_line("\tldrsw\tx0, [x0]"); }
    else if (aesz == 2) { emit_line("\tldrsh\tx0, [x0]"); }
    else if (aesz == 1) { emit_line("\tldrb\tw0, [x0]"); }
    else { emit_line("\tldr\tx0, [x0]"); }
  } else {
    emit_line("\tldr\tx0, [x0]");
  }
  return 0;
}

int gen_val_assign(struct Expr *e) {
  int bf_bit_off = 0;
  int bf_width = 0;
  int bf_mask = 0;
  int bf_clear_mask = 0;
  int *sa_type = 0;
  int sa_nf = 0;
  int sa_fi = 0;
  // Check if target is a bitfield
  if (e->left->kind == ND_FIELD || e->left->kind == ND_ARROW) {
    bf_bit_off = 0;
    bf_width = cg_get_bitfield_info(e->left->sval2, e->left->sval, &bf_bit_off);
    if (bf_width > 0) {
      bf_mask = (1 << bf_width) - 1;
      bf_clear_mask = bf_mask << bf_bit_off;
      gen_addr(e->left);
      emit_line("\tstr\tx0, [sp, #-16]!");
      gen_value(e->right);
      emit_line("\tldr\tx1, [sp], #16");
      emit_s("\tand\tx0, x0, #");
      emit_num(bf_mask);
      emit_ch('\n');
      if (bf_bit_off > 0) {
        emit_s("\tlsl\tx0, x0, #");
        emit_num(bf_bit_off);
        emit_ch('\n');
      }
      emit_line("\tldr\tx9, [x1]");
      emit_mov_imm("x10", bf_clear_mask);
      emit_line("\tbic\tx9, x9, x10");
      emit_line("\torr\tx0, x9, x0");
      emit_line("\tstr\tx0, [x1]");
      // Re-extract stored value
      if (bf_bit_off > 0) {
        emit_s("\tlsr\tx0, x0, #");
        emit_num(bf_bit_off);
        emit_ch('\n');
      }
      emit_s("\tand\tx0, x0, #");
      emit_num(bf_mask);
      emit_ch('\n');
      return 0;
    }
  }
  // Check for multi-field struct assignment
  sa_type = 0;
  if (e->left->kind == ND_VAR) {
    sa_type = cg_structvar_type(e->left->sval);
    // Also check global struct vars
    if (sa_type == 0) { sa_type = cg_global_stype(e->left->sval); }
  }
  if (sa_type == 0 && (e->left->kind == ND_FIELD || e->left->kind == ND_ARROW)) {
    sa_type = cg_field_struct_type(e->left->sval2, e->left->sval);
  }
  // Deref struct pointer: *p where p is struct*
  if (sa_type == 0 && e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left->kind == ND_VAR) {
    sa_type = cg_ptr_structvar_type(e->left->left->sval);
    if (sa_type == 0) { sa_type = cg_global_stype(e->left->left->sval); }
  }
  // Indexing struct array: arr[i]
  if (sa_type == 0 && e->left->kind == ND_INDEX && e->left->left->kind == ND_VAR) {
    sa_type = cg_structvar_type(e->left->left->sval);
    if (sa_type == 0) { sa_type = cg_ptr_structvar_type(e->left->left->sval); }
    if (sa_type == 0) { sa_type = cg_global_stype(e->left->left->sval); }
  }
  if (sa_type != 0) {
    sa_nf = cg_struct_nfields(sa_type);
    if (sa_nf >= 1) {
      if (e->right->kind == ND_UNARY && e->right->ival == '&') { sa_nf = 0; }
    }
    if (sa_nf >= 1) {
      gen_addr(e->left);
      emit_line("\tstr\tx0, [sp, #-16]!");
      // Get source address
      if (e->right->kind == ND_UNARY && e->right->ival == '*') {
        gen_value(e->right->left);
      } else {
        gen_addr(e->right);
      }
      emit_line("\tldr\tx1, [sp], #16");
      // x0 = src addr, x1 = dest addr — byte-level copy
      {
        int sa_bsz = cg_struct_byte_size(sa_type);
        int sa_bi = 0;
        while (sa_bi + 8 <= sa_bsz) {
          if (sa_bi <= 32760) {
            emit_s("\tldr\tx9, [x0, #"); emit_num(sa_bi); emit_line("]");
            emit_s("\tstr\tx9, [x1, #"); emit_num(sa_bi); emit_line("]");
          } else {
            emit_mov_imm("x10", sa_bi);
            emit_line("\tldr\tx9, [x0, x10]");
            emit_line("\tstr\tx9, [x1, x10]");
          }
          sa_bi = sa_bi + 8;
        }
        while (sa_bi + 4 <= sa_bsz) {
          emit_s("\tldr\tw9, [x0, #"); emit_num(sa_bi); emit_line("]");
          emit_s("\tstr\tw9, [x1, #"); emit_num(sa_bi); emit_line("]");
          sa_bi = sa_bi + 4;
        }
        while (sa_bi + 2 <= sa_bsz) {
          emit_s("\tldrh\tw9, [x0, #"); emit_num(sa_bi); emit_line("]");
          emit_s("\tstrh\tw9, [x1, #"); emit_num(sa_bi); emit_line("]");
          sa_bi = sa_bi + 2;
        }
        while (sa_bi < sa_bsz) {
          emit_s("\tldrb\tw9, [x0, #"); emit_num(sa_bi); emit_line("]");
          emit_s("\tstrb\tw9, [x1, #"); emit_num(sa_bi); emit_line("]");
          sa_bi = sa_bi + 1;
        }
      }
      return 0;
    }
  }
  gen_addr(e->left);
  emit_line("\tstr\tx0, [sp, #-16]!");
  gen_value(e->right);
  emit_line("\tldr\tx1, [sp], #16");
  {
    // Float conversion: int-to-float or float-to-int
    int target_is_float = 0;
    int value_is_float = expr_is_float(e->right);
    if (e->left->kind == ND_VAR && cg_is_float(e->left->sval)) { target_is_float = 1; }
    if (target_is_float && value_is_float == 0) {
      // int to float: convert x0 (int) to double bit pattern
      emit_line("\tscvtf\td0, x0");
      emit_line("\tfmov\tx0, d0");
    } else if (target_is_float == 0 && value_is_float) {
      // float to int: convert x0 (double bits) to int
      emit_line("\tfmov\td0, x0");
      emit_line("\tfcvtzs\tx0, d0");
    }
    int assign_char = 0;
    if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left->kind == ND_VAR && cg_is_char(e->left->left->sval)) { assign_char = 1; }
    // *char_ptr++ = val or *char_ptr-- = val
    if (e->left->kind == ND_UNARY && e->left->ival == '*' && (e->left->left->kind == ND_POSTINC || e->left->left->kind == ND_POSTDEC) && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR && cg_is_char(e->left->left->left->sval)) { assign_char = 1; }
    if (e->left->kind == ND_INDEX && e->left->left->kind == ND_VAR && (cg_is_char(e->left->left->sval) || cg_is_char_larr(e->left->left->sval) || cg_global_is_bare_char_arr(e->left->left->sval))) { assign_char = 1; }
    if (e->left->kind == ND_INDEX && (e->left->left->kind == ND_ARROW || e->left->left->kind == ND_FIELD) && cg_field_is_char(e->left->left->sval2, e->left->left->sval) && (cg_field_is_ptr(e->left->left->sval2, e->left->left->sval) == 0 || cg_field_is_array(e->left->left->sval2, e->left->left->sval) == 0)) { assign_char = 1; }
    if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left->kind == ND_BINARY && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR && cg_is_char(e->left->left->left->sval)) { assign_char = 1; }
    // char *arr[N]; arr[i][j] = val
    if (e->left->kind == ND_INDEX && e->left->left->kind == ND_INDEX && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR && cg_is_char_arr(e->left->left->left->sval)) { assign_char = 1; }
    // Truncate when assigning to a bare char variable
    if (e->left->kind == ND_VAR) {
      int bc = cg_is_barechar(e->left->sval);
      if (bc == 2) { emit_line("\tuxtb\tw0, w0"); }
      else if (bc == 1) { emit_line("\tsxtb\tx0, w0"); }
    }
    if (assign_char) {
      emit_line("\tstrb\tw0, [x1]");
    } else if (e->left->kind == ND_FIELD || e->left->kind == ND_ARROW) {
      int bsz = cg_field_byte_size(e->left->sval2, e->left->sval);
      if (bsz == 1) { emit_line("\tstrb\tw0, [x1]"); }
      else if (bsz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else if (bsz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_INDEX && (e->left->left->kind == ND_ARROW || e->left->left->kind == ND_FIELD) && cg_field_is_array(e->left->left->sval2, e->left->left->sval) > 0 && cg_field_is_ptr(e->left->left->sval2, e->left->left->sval) == 0) {
      int es = cg_field_arr_elem_size(e->left->left->sval2, e->left->left->sval);
      if (es == 1) { emit_line("\tstrb\tw0, [x1]"); }
      else if (es == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else if (es == 4) { emit_line("\tstr\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_INDEX && (e->left->left->kind == ND_ARROW || e->left->left->kind == ND_FIELD) && cg_field_is_ptr(e->left->left->sval2, e->left->left->sval) == 1 && cg_field_is_char(e->left->left->sval2, e->left->left->sval) == 0 && field_stype(e->left->left->sval2, e->left->left->sval) == 0) {
      // Struct field pointer store: s->field[i] = val where field is int*/short*
      if (cg_field_is_short(e->left->left->sval2, e->left->left->sval)) { emit_line("\tstrh\tw0, [x1]"); }
      else if (cg_field_is_long(e->left->left->sval2, e->left->left->sval)) { emit_line("\tstr\tx0, [x1]"); }
      else { emit_line("\tstr\tw0, [x1]"); }
    } else if (e->left->kind == ND_INDEX && e->left->left != 0 && e->left->left->kind == ND_VAR) {
      int aesz = cg_arr_esz(e->left->left->sval);
      if (aesz == 0) { aesz = cg_intptr_esz(e->left->left->sval); }
      if (aesz == 0 && cg_global_is_array(e->left->left->sval) == 0) { aesz = cg_global_ptr_esz(e->left->left->sval); }
      if (aesz == 0) { aesz = cg_global_esz(e->left->left->sval); }
      if (aesz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else if (aesz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->sval)) {
      int desz = cg_intptr_esz(e->left->left->sval);
      if (desz == 0) { desz = cg_global_ptr_esz(e->left->left->sval); }
      if (desz == 0) { desz = 4; }
      if (desz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else if (desz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left != 0 && e->left->left->kind == ND_BINARY && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->left->sval)) {
      int desz = cg_intptr_esz(e->left->left->left->sval);
      if (desz == 0) { desz = cg_global_ptr_esz(e->left->left->left->sval); }
      if (desz == 0) { desz = 4; }
      if (desz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else if (desz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left != 0 && (e->left->left->kind == ND_POSTINC || e->left->left->kind == ND_POSTDEC) && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->left->sval)) {
      int desz = cg_intptr_esz(e->left->left->left->sval);
      if (desz == 0) { desz = cg_global_ptr_esz(e->left->left->left->sval); }
      if (desz == 0) { desz = 4; }
      if (desz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else if (desz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else if (e->left->kind == ND_UNARY && e->left->ival == '*' && e->left->left != 0 && (e->left->left->kind == ND_ARROW || e->left->left->kind == ND_FIELD)) {
      // Store through struct field pointer: *mi->field = val
      int fp = cg_field_is_ptr(e->left->left->sval2, e->left->left->sval);
      if (fp == 1 && cg_field_is_char(e->left->left->sval2, e->left->left->sval)) {
        emit_line("\tstrb\tw0, [x1]");
      } else if (fp == 1 && field_stype(e->left->left->sval2, e->left->left->sval) == 0) {
        if (cg_field_is_short(e->left->left->sval2, e->left->left->sval)) { emit_line("\tstrh\tw0, [x1]"); }
        else if (cg_field_is_long(e->left->left->sval2, e->left->left->sval)) { emit_line("\tstr\tx0, [x1]"); }
        else { emit_line("\tstr\tw0, [x1]"); }
      } else {
        emit_line("\tstr\tx0, [x1]");
      }
    } else if (e->left->kind == ND_INDEX && e->left->left != 0 && e->left->left->kind == ND_INDEX && e->left->left->left != 0 && e->left->left->left->kind == ND_VAR) {
      // 2D array element store: arr[i][j] = val
      int aesz = cg_arr_esz(e->left->left->left->sval);
      if (aesz == 0) { aesz = cg_global_ptr_esz(e->left->left->left->sval); }
      if (aesz == 0) { aesz = cg_global_esz(e->left->left->left->sval); }
      if (aesz == 4) { emit_line("\tstr\tw0, [x1]"); }
      else if (aesz == 2) { emit_line("\tstrh\tw0, [x1]"); }
      else { emit_line("\tstr\tx0, [x1]"); }
    } else {
      emit_line("\tstr\tx0, [x1]");
    }
  }
  return 0;
}

int gen_val_postinc_postdec(struct Expr *e) {
  int inc = 1;
  int pi_is_float = expr_is_float(e->left);
  if (e->left->kind == ND_VAR) {
    int *pi_pstype = cg_ptr_structvar_type(e->left->sval);
    if (pi_pstype != 0) {
      inc = cg_struct_byte_size(pi_pstype);
    } else if (cg_is_intptr(e->left->sval)) {
      inc = cg_intptr_esz(e->left->sval);
      if (inc == 0) { inc = cg_global_ptr_esz(e->left->sval); }
      if (inc == 0) { inc = 4; }
    }
  }
  gen_addr(e->left);
  emit_line("\tstr\tx0, [sp, #-16]!");
  emit_line("\tldr\tx0, [x0]");
  emit_line("\tstr\tx0, [sp, #-16]!");
  if (pi_is_float) {
    // Float post-increment/decrement
    emit_line("\tfmov\td0, x0");
    emit_line("\tfmov\td1, #1.0");
    if (e->kind == ND_POSTINC) {
      emit_line("\tfadd\td0, d0, d1");
    } else {
      emit_line("\tfsub\td0, d0, d1");
    }
    emit_line("\tfmov\tx0, d0");
  } else {
    if (e->kind == ND_POSTINC) {
      emit_s("\tadd\tx0, x0, #"); emit_num(inc); emit_ch('\n');
    } else {
      emit_s("\tsub\tx0, x0, #"); emit_num(inc); emit_ch('\n');
    }
  }
  // Truncate for bare char variables
  if (e->left->kind == ND_VAR) {
    int bc = cg_is_barechar(e->left->sval);
    if (bc == 2) { emit_line("\tuxtb\tw0, w0"); }
    else if (bc == 1) { emit_line("\tsxtb\tx0, w0"); }
  }
  emit_line("\tldr\tx1, [sp, #16]");
  // Use ABI-width store for locals
  if (e->left->kind == ND_VAR) {
    int absz = cg_var_bsz(e->left->sval);
    if (absz == 1) { emit_line("\tstrb\tw0, [x1]"); }
    else if (absz == 2) { emit_line("\tstrh\tw0, [x1]"); }
    else if (absz == 4) { emit_line("\tstr\tw0, [x1]"); }
    else { emit_line("\tstr\tx0, [x1]"); }
  } else {
    emit_line("\tstr\tx0, [x1]");
  }
  emit_line("\tldr\tx0, [sp], #32");
  return 0;
}

int gen_val_compoulit(struct Expr *e) {
  int *cl_name = build_str2("__cl_", int_to_str(cg_cl_gen_counter));
  cg_cl_gen_counter++;
  int cl_base = cg_find_slot(cl_name);
  struct Expr *cl_init = e->left;
  if (cl_init != 0 && cl_init->kind == ND_INITLIST) {
    int *cl_di = cl_init->desig;
    int cl_pos = 0;
    int cl_k = 0;
    int cl_target = 0;
    int cl_off = 0;
    if (e->sval != 0) {
      // Zero-fill the compound literal first
      int bsz = cg_struct_byte_size(e->sval);
      int nslots = (bsz + 7) / 8;
      int zk = 0;
      while (zk < nslots) {
        cl_off = cl_base - zk * 8;
        emit_line("\tmov\tx0, #0");
        emit_sub_imm("x9", "x29", cl_off);
        emit_line("\tstr\tx0, [x9]");
        zk++;
      }
      while (cl_k < cl_init->nargs) {
        gen_value(cl_init->args[cl_k]);
        cl_target = cl_pos;
        if (cl_di != 0 && cl_di[cl_k] >= 0) { cl_target = cl_di[cl_k]; }
        cl_pos = cl_target + 1;
        cl_off = cl_base - cg_field_byte_offset_idx(e->sval, cl_target);
        {
          int fbsz = cg_field_byte_size_idx(e->sval, cl_target);
          emit_sub_imm("x9", "x29", cl_off);
          if (fbsz == 1) { emit_line("\tstrb\tw0, [x9]"); }
          else if (fbsz == 2) { emit_line("\tstrh\tw0, [x9]"); }
          else if (fbsz == 4) { emit_line("\tstr\tw0, [x9]"); }
          else { emit_line("\tstr\tx0, [x9]"); }
        }
        cl_k++;
      }
    } else {
    while (cl_k < cl_init->nargs) {
      gen_value(cl_init->args[cl_k]);
      cl_target = cl_pos;
      if (cl_di != 0 && cl_di[cl_k] >= 0) { cl_target = cl_di[cl_k]; }
      cl_pos = cl_target + 1;
      cl_off = cl_base - cl_target * 8;
      if (cl_off <= 255) {
        emit_s("\tstr\tx0, [x29, #-");
        emit_num(cl_off);
        emit_line("]");
      } else {
        emit_sub_imm("x9", "x29", cl_off);
        emit_line("\tstr\tx0, [x9]");
      }
      cl_k++;
    }
    }
  }
  // Leave address in x0
  emit_sub_imm("x0", "x29", cl_base);
  emit_ch('\n');
  return 0;
}

int gen_val_stmt_expr(struct Expr *e) {
  // Statement expression: ({ stmts; expr; })
  // Generate all statements in the block; last expr-stmt leaves value in x0
  struct Stmt *se_blk = e->left;
  if (se_blk != 0 && se_blk->kind == ST_BLOCK) {
    int se_i = 0;
    while (se_i < se_blk->nbody) {
      gen_stmt(se_blk->body[se_i], 0);
      se_i++;
    }
  }
  return 0;
}

int gen_val_ternary(struct Expr *e) {
  int *end_l = 0;
  int *else_l = 0;
  else_l = cg_new_label("tern_else");
  end_l = cg_new_label("tern_end");
  gen_value(e->left);
  emit_line("\tcmp\tx0, #0");
  emit_s("\tb.eq\t"); emit_line(else_l);
  gen_value(e->right);
  emit_s("\tb\t"); emit_line(end_l);
  emit_s(else_l); emit_line(":");
  gen_value(e->args[0]);
  emit_s(end_l); emit_line(":");
  return 0;
}

int gen_val_strlit(struct Expr *e) {
  int *decoded = cg_decode_string(e->sval);
  int *lab = cg_intern_string(decoded);
  emit_s("\tadrp\tx0, ");
  emit_s(lab);
  emit_line("@PAGE");
  emit_s("\tadd\tx0, x0, ");
  emit_s(lab);
  emit_line("@PAGEOFF");
  return 0;
}

int gen_val_unary(struct Expr *e) {
  int unary_op = 0;
  unary_op = e->ival;
  if (unary_op == '&') {
    gen_addr(e->left);
    return 0;
  }
  if (unary_op == '*') {
    int deref_char = 0;
    if (e->left->kind == ND_VAR && cg_is_char(e->left->sval)) { deref_char = 1; }
    if (e->left->kind == ND_BINARY && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_char(e->left->left->sval)) { deref_char = 1; }
    if (e->left->kind == ND_BINARY && e->left->right != 0 && e->left->right->kind == ND_VAR && cg_is_char(e->left->right->sval)) { deref_char = 1; }
    if (e->left->kind == ND_INDEX && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_char_arr(e->left->left->sval)) { deref_char = 1; }
    // *s++ / *s-- where s is char*
    if ((e->left->kind == ND_POSTINC || e->left->kind == ND_POSTDEC) && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_char(e->left->left->sval)) { deref_char = 1; }
    // *++s / *--s where s is char* (pre-inc/dec is ND_ASSIGN)
    if (e->left->kind == ND_ASSIGN && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_char(e->left->left->sval)) { deref_char = 1; }
    // *mi->field where field is char* in a struct
    if ((e->left->kind == ND_ARROW || e->left->kind == ND_FIELD) && cg_field_is_char(e->left->sval2, e->left->sval) && cg_field_is_ptr(e->left->sval2, e->left->sval) == 1) { deref_char = 1; }
    gen_value(e->left);
    if (deref_char) {
      emit_line("\tldrb\tw0, [x0]");
    } else {
      int deref_esz = 8;
      int deref_unsigned = 0;
      if (e->left->kind == ND_VAR && cg_is_intptr(e->left->sval)) {
        deref_esz = cg_intptr_esz(e->left->sval);
        if (deref_esz == 0) { deref_esz = cg_global_ptr_esz(e->left->sval); }
        if (deref_esz == 0) { deref_esz = 4; }
      }
      if (e->left->kind == ND_BINARY && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->sval)) {
        deref_esz = cg_intptr_esz(e->left->left->sval);
        if (deref_esz == 0) { deref_esz = cg_global_ptr_esz(e->left->left->sval); }
        if (deref_esz == 0) { deref_esz = 4; }
      }
      // Commutative: *(N + p) where pointer is on the right
      if (deref_esz == 8 && e->left->kind == ND_BINARY && e->left->right != 0 && e->left->right->kind == ND_VAR && cg_is_intptr(e->left->right->sval)) {
        deref_esz = cg_intptr_esz(e->left->right->sval);
        if (deref_esz == 0) { deref_esz = cg_global_ptr_esz(e->left->right->sval); }
        if (deref_esz == 0) { deref_esz = 4; }
      }
      if ((e->left->kind == ND_POSTINC || e->left->kind == ND_POSTDEC) && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->sval)) {
        deref_esz = cg_intptr_esz(e->left->left->sval);
        if (deref_esz == 0) { deref_esz = cg_global_ptr_esz(e->left->left->sval); }
        if (deref_esz == 0) { deref_esz = 4; }
      }
      // Pre-increment/decrement: *++p or *--p is *(p = p +/- 1)
      if (deref_esz == 8 && e->left->kind == ND_ASSIGN && e->left->left != 0 && e->left->left->kind == ND_VAR && cg_is_intptr(e->left->left->sval)) {
        deref_esz = cg_intptr_esz(e->left->left->sval);
        if (deref_esz == 0) { deref_esz = cg_global_ptr_esz(e->left->left->sval); }
        if (deref_esz == 0) { deref_esz = 4; }
      }
      // Struct field pointer dereference: *mi->field where field is int*/short*/long*
      if (deref_esz == 8 && (e->left->kind == ND_ARROW || e->left->kind == ND_FIELD)) {
        int fp = cg_field_is_ptr(e->left->sval2, e->left->sval);
        int *fst = field_stype(e->left->sval2, e->left->sval);
        if (fp == 1 && fst == 0) {
          if (cg_field_is_short(e->left->sval2, e->left->sval)) { deref_esz = 2; }
          else if (cg_field_is_long(e->left->sval2, e->left->sval)) { deref_esz = 8; }
          else { deref_esz = 4; }
          deref_unsigned = cg_field_is_unsigned(e->left->sval2, e->left->sval);
        }
      }
      gen_load_by_bsz(deref_esz, deref_unsigned);
    }
    return 0;
  }
  gen_value(e->left);
  if (unary_op == '-') {
    if (expr_is_float(e->left)) {
      emit_line("\tfmov\td0, x0");
      emit_line("\tfneg\td0, d0");
      emit_line("\tfmov\tx0, d0");
    } else {
      emit_line("\tneg\tx0, x0");
    }
  } else if (unary_op == '!') {
    emit_line("\tcmp\tx0, #0");
    emit_line("\tcset\tx0, eq");
  } else if (unary_op == '~') {
    emit_line("\tmvn\tx0, x0");
  }
  return 0;
}

int gen_val_binary(struct Expr *e) {
  int *bin_op = 0;
  int *end_l = 0;
  int *rhs_l = 0;
  bin_op = e->sval2;

  // Comma operator: evaluate left (discard), evaluate right (keep)
  if (my_strcmp(bin_op, ",") == 0) {
    gen_value(e->left);
    gen_value(e->right);
    return 0;
  }

  if (my_strcmp(bin_op, "&&") == 0 || my_strcmp(bin_op, "||") == 0) {
    end_l = cg_new_label("sc_end");
    rhs_l = cg_new_label("sc_rhs");

    gen_value(e->left);
    emit_line("\tcmp\tx0, #0");
    if (my_strcmp(bin_op, "&&") == 0) {
      emit_s("\tb.ne\t"); emit_line(rhs_l);
      emit_line("\tmov\tx0, #0");
      emit_s("\tb\t"); emit_line(end_l);
    } else {
      emit_s("\tb.eq\t"); emit_line(rhs_l);
      emit_line("\tmov\tx0, #1");
      emit_s("\tb\t"); emit_line(end_l);
    }
    emit_s(rhs_l); emit_line(":");
    gen_value(e->right);
    emit_line("\tcmp\tx0, #0");
    emit_line("\tcset\tx0, ne");
    emit_s(end_l); emit_line(":");
    return 0;
  }

  gen_value(e->left);
  emit_line("\tstr\tx0, [sp, #-16]!");
  gen_value(e->right);
  emit_line("\tldr\tx1, [sp], #16");

  // Pointer-to-struct scaling for + and -
  if (my_strcmp(bin_op, "+") == 0 || my_strcmp(bin_op, "-") == 0) {
    int *pstype = 0;
    int scale_rhs = 0;
    int *lhs_pstype = 0;
    int *rhs_pstype = 0;
    if (e->left->kind == ND_VAR) {
      lhs_pstype = cg_ptr_structvar_type(e->left->sval);
      // Also check struct arrays (items + N where items is struct array)
      if (lhs_pstype == 0 && cg_is_array(e->left->sval)) {
        lhs_pstype = cg_structvar_type(e->left->sval);
      }
    }
    if (e->right->kind == ND_VAR) {
      rhs_pstype = cg_ptr_structvar_type(e->right->sval);
      if (rhs_pstype == 0 && cg_is_array(e->right->sval)) {
        rhs_pstype = cg_structvar_type(e->right->sval);
      }
    }
    if (lhs_pstype != 0 && rhs_pstype != 0 && my_strcmp(bin_op, "-") == 0) {
      // struct ptr - struct ptr: no scaling, divide after sub
    } else if (lhs_pstype != 0) {
      pstype = lhs_pstype;
      scale_rhs = 1;
    } else if (rhs_pstype != 0) {
      pstype = rhs_pstype;
      scale_rhs = 0;
    }
    if (pstype != 0) {
      int scale = cg_struct_byte_size(pstype);
      if (scale_rhs) {
        emit_mov_imm("x9", scale);
        emit_line("\tmul\tx0, x0, x9");
      } else {
        emit_mov_imm("x9", scale);
        emit_line("\tmul\tx1, x1, x9");
      }
    } else {
      // Scale by 8 for int pointer arithmetic (not char, not struct)
      // Also includes local arrays and global arrays
      int left_intptr = 0;
      int right_intptr = 0;
      if (e->left->kind == ND_VAR) {
        if (cg_is_intptr(e->left->sval) || (cg_is_array(e->left->sval) && cg_is_char_larr(e->left->sval) == 0)) {
          left_intptr = 1;
        } else if (cg_global_is_array(e->left->sval) && cg_is_char_arr(e->left->sval) == 0 && cg_global_is_bare_char_arr(e->left->sval) == 0) {
          left_intptr = 1;
        }
      }
      if (e->right->kind == ND_VAR) {
        if (cg_is_intptr(e->right->sval) || (cg_is_array(e->right->sval) && cg_is_char_larr(e->right->sval) == 0)) {
          right_intptr = 1;
        } else if (cg_global_is_array(e->right->sval) && cg_is_char_arr(e->right->sval) == 0 && cg_global_is_bare_char_arr(e->right->sval) == 0) {
          right_intptr = 1;
        }
      }
      if (left_intptr && right_intptr && my_strcmp(bin_op, "-") == 0) {
        // ptr - ptr: don't scale, divide result by esz after sub
        // handled below after sub instruction
      } else if (left_intptr) {
        int lp_esz = 8;
        if (e->left->kind == ND_VAR) {
          int le = cg_intptr_esz(e->left->sval);
          if (le > 0) { lp_esz = le; }
          if (lp_esz == 8) { le = cg_arr_esz(e->left->sval); if (le > 0) { lp_esz = le; } }
          if (lp_esz == 8 && cg_global_is_array(e->left->sval) == 0) { le = cg_global_ptr_esz(e->left->sval); if (le > 0) { lp_esz = le; } }
          if (lp_esz == 8) { le = cg_global_esz(e->left->sval); if (le > 0) { lp_esz = le; } }
        }
        if (lp_esz == 4) { emit_line("\tlsl\tx0, x0, #2"); }
        else if (lp_esz == 2) { emit_line("\tlsl\tx0, x0, #1"); }
        else { emit_line("\tlsl\tx0, x0, #3"); }
      } else if (right_intptr) {
        int rp_esz = 8;
        if (e->right->kind == ND_VAR) {
          int re = cg_intptr_esz(e->right->sval);
          if (re > 0) { rp_esz = re; }
          if (rp_esz == 8) { re = cg_arr_esz(e->right->sval); if (re > 0) { rp_esz = re; } }
          if (rp_esz == 8 && cg_global_is_array(e->right->sval) == 0) { re = cg_global_ptr_esz(e->right->sval); if (re > 0) { rp_esz = re; } }
          if (rp_esz == 8) { re = cg_global_esz(e->right->sval); if (re > 0) { rp_esz = re; } }
        }
        if (rp_esz == 4) { emit_line("\tlsl\tx1, x1, #2"); }
        else if (rp_esz == 2) { emit_line("\tlsl\tx1, x1, #1"); }
        else { emit_line("\tlsl\tx1, x1, #3"); }
      }
    }
  }

  // Check if either operand is float
  int use_float = 0;
  if (expr_is_float(e->left) || expr_is_float(e->right)) { use_float = 1; }
  if (use_float) {
    int left_is_float = expr_is_float(e->left);
    int right_is_float = expr_is_float(e->right);
    // x1 = left, x0 = right. Move to FPU registers.
    if (left_is_float) { emit_line("\tfmov\td1, x1"); } else { emit_line("\tscvtf\td1, x1"); }
    if (right_is_float) { emit_line("\tfmov\td0, x0"); } else { emit_line("\tscvtf\td0, x0"); }
    if (my_strcmp(bin_op, "+") == 0) { emit_line("\tfadd\td0, d1, d0"); }
    else if (my_strcmp(bin_op, "-") == 0) { emit_line("\tfsub\td0, d1, d0"); }
    else if (my_strcmp(bin_op, "*") == 0) { emit_line("\tfmul\td0, d1, d0"); }
    else if (my_strcmp(bin_op, "/") == 0) { emit_line("\tfdiv\td0, d1, d0"); }
    else if (my_strcmp(bin_op, "==") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, eq"); return 0; }
    else if (my_strcmp(bin_op, "!=") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, ne"); return 0; }
    else if (my_strcmp(bin_op, "<") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, mi"); return 0; }
    else if (my_strcmp(bin_op, "<=") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, ls"); return 0; }
    else if (my_strcmp(bin_op, ">") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, gt"); return 0; }
    else if (my_strcmp(bin_op, ">=") == 0) { emit_line("\tfcmp\td1, d0"); emit_line("\tcset\tx0, ge"); return 0; }
    else { my_fatal("unsupported float binary op"); }
    emit_line("\tfmov\tx0, d0");
    return 0;
  }

  // Check if either operand is unsigned
  int use_unsigned = 0;
  if (e->left->kind == ND_VAR && cg_is_unsigned(e->left->sval)) { use_unsigned = 1; }
  if (e->right->kind == ND_VAR && cg_is_unsigned(e->right->sval)) { use_unsigned = 1; }
  if (e->left->kind == ND_CALL && func_returns_unsigned(e->left->sval)) { use_unsigned = 1; }
  if (e->right->kind == ND_CALL && func_returns_unsigned(e->right->sval)) { use_unsigned = 1; }
  if (e->left->kind == ND_CAST && (e->left->ival == 4 || e->left->ival == 6 || e->left->ival == 7)) { use_unsigned = 1; }
  if (e->right->kind == ND_CAST && (e->right->ival == 4 || e->right->ival == 6 || e->right->ival == 7)) { use_unsigned = 1; }

  // Check if either operand is 64-bit (long/pointer) — use x registers; otherwise use w registers
  int use_long = 0;
  if (expr_is_long(e->left) || expr_is_long(e->right)) { use_long = 1; }

  if (my_strcmp(bin_op, "+") == 0) { emit_line("\tadd\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, "-") == 0) {
    emit_line("\tsub\tx0, x1, x0");
    // ptr - ptr: divide by element size to get element count
    if (e->left->kind == ND_VAR && e->right->kind == ND_VAR) {
      int *left_pstype = cg_ptr_structvar_type(e->left->sval);
      int *right_pstype = cg_ptr_structvar_type(e->right->sval);
      if (left_pstype != 0 && right_pstype != 0) {
        int scale = cg_struct_byte_size(left_pstype);
        emit_mov_imm("x9", scale);
        emit_line("\tsdiv\tx0, x0, x9");
      } else if (cg_is_intptr(e->left->sval) && cg_is_intptr(e->right->sval)) {
        int pp_esz = cg_intptr_esz(e->left->sval);
        if (pp_esz == 0) { pp_esz = cg_global_ptr_esz(e->left->sval); }
        if (pp_esz == 0) { pp_esz = cg_global_esz(e->left->sval); }
        if (pp_esz == 0) { pp_esz = 8; }
        if (pp_esz == 4) { emit_line("\tasr\tx0, x0, #2"); }
        else if (pp_esz == 2) { emit_line("\tasr\tx0, x0, #1"); }
        else { emit_line("\tasr\tx0, x0, #3"); }
      }
    }
  }
  else if (my_strcmp(bin_op, "*") == 0) { emit_line("\tmul\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, "/") == 0) {
    if (use_long) {
      if (use_unsigned) { emit_line("\tudiv\tx0, x1, x0"); }
      else { emit_line("\tsdiv\tx0, x1, x0"); }
    } else {
      if (use_unsigned) { emit_line("\tudiv\tw0, w1, w0"); }
      else { emit_line("\tsdiv\tw0, w1, w0"); }
    }
  }
  else if (my_strcmp(bin_op, "&") == 0) { emit_line("\tand\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, "|") == 0) { emit_line("\torr\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, "^") == 0) { emit_line("\teor\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, "<<") == 0) { emit_line("\tlsl\tx0, x1, x0"); }
  else if (my_strcmp(bin_op, ">>") == 0) {
    // For >>, propagate unsigned through subexpressions of left operand
    int shift_unsigned = use_unsigned;
    if (shift_unsigned == 0) { shift_unsigned = expr_is_unsigned(e->left); }
    if (use_long) {
      if (shift_unsigned) { emit_line("\tlsr\tx0, x1, x0"); }
      else { emit_line("\tasr\tx0, x1, x0"); }
    } else {
      if (shift_unsigned) { emit_line("\tlsr\tw0, w1, w0"); }
      else { emit_line("\tasr\tw0, w1, w0"); }
    }
  }
  else if (my_strcmp(bin_op, "%") == 0) {
    if (use_long) {
      if (use_unsigned) { emit_line("\tudiv\tx9, x1, x0"); }
      else { emit_line("\tsdiv\tx9, x1, x0"); }
      emit_line("\tmsub\tx0, x9, x0, x1");
    } else {
      if (use_unsigned) { emit_line("\tudiv\tw9, w1, w0"); }
      else { emit_line("\tsdiv\tw9, w1, w0"); }
      emit_line("\tmsub\tw0, w9, w0, w1");
    }
  }
  else if (my_strcmp(bin_op, "==") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    emit_line("\tcset\tw0, eq");
  }
  else if (my_strcmp(bin_op, "!=") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    emit_line("\tcset\tw0, ne");
  }
  else if (my_strcmp(bin_op, "<") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    if (use_unsigned) { emit_line("\tcset\tw0, lo"); } else { emit_line("\tcset\tw0, lt"); }
  }
  else if (my_strcmp(bin_op, "<=") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    if (use_unsigned) { emit_line("\tcset\tw0, ls"); } else { emit_line("\tcset\tw0, le"); }
  }
  else if (my_strcmp(bin_op, ">") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    if (use_unsigned) { emit_line("\tcset\tw0, hi"); } else { emit_line("\tcset\tw0, gt"); }
  }
  else if (my_strcmp(bin_op, ">=") == 0) {
    if (use_long) { emit_line("\tcmp\tx1, x0"); }
    else { emit_line("\tcmp\tw1, w0"); }
    if (use_unsigned) { emit_line("\tcset\tw0, hs"); } else { emit_line("\tcset\tw0, ge"); }
  }
  return 0;
}

int gen_val_call(struct Expr *e) {
  int var_space = 0;
  int *name = e->sval;
  int nargs = e->nargs;

  // __read_byte intrinsic
  if (my_strcmp(name, "__read_byte") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tldrb\tw0, [x1, x0]");
    return 0;
  }

  // __write_byte intrinsic
  if (my_strcmp(name, "__write_byte") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[2]);
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tldr\tx2, [sp], #16");
    emit_line("\tstrb\tw0, [x2, x1]");
    return 0;
  }

  // __builtin_va_start intrinsic
  if (my_strcmp(name, "__builtin_va_start") == 0) {
    // If arg is &(ap) from our stdarg.h macro, gen_value gives addr
    // If arg is plain ap from __builtin_va_start(ap, ...), use gen_addr
    if (e->args[0]->kind == ND_UNARY && e->args[0]->ival == 38) {
      // Unary & operator: gen_value gives the address of the operand
      gen_value(e->args[0]);
    } else {
      // Plain variable: use gen_addr to get its address
      gen_addr(e->args[0]);
    }
    emit_line("\tadd\tx1, x29, #16");
    emit_line("\tstr\tx1, [x0]");
    return 0;
  }

  // __builtin_va_arg(ap, type) => load *ap, advance ap += 8
  if (my_strcmp(name, "__builtin_va_arg") == 0) {
    gen_addr(e->args[0]); // address of ap variable (so we can modify it)
    emit_line("\tldr\tx1, [x0]"); // x1 = current va ptr (value of ap)
    emit_line("\tadd\tx2, x1, #8"); // x2 = next position
    emit_line("\tstr\tx2, [x0]"); // ap = advanced pointer
    emit_line("\tldr\tx0, [x1]"); // x0 = value at current position
    return 0;
  }

  // __builtin_expect(expr, expected) => just return expr
  if (my_strcmp(name, "__builtin_expect") == 0) {
    gen_value(e->args[0]);
    return 0;
  }

  // __builtin_return_address(0) => return link register saved on stack
  if (my_strcmp(name, "__builtin_return_address") == 0) {
    emit_line("\tldr\tx0, [x29, #8]");
    return 0;
  }

  // __builtin_frame_address(0) => return frame pointer
  if (my_strcmp(name, "__builtin_frame_address") == 0) {
    emit_line("\tmov\tx0, x29");
    return 0;
  }

  // __builtin_classify_type(x) => return 1 for int (good enough default)
  if (my_strcmp(name, "__builtin_classify_type") == 0) {
    emit_line("\tmov\tx0, #1");
    return 0;
  }

  // __builtin_abort() => call abort
  if (my_strcmp(name, "__builtin_abort") == 0) {
    emit_line("\tbl\t_abort");
    return 0;
  }

  // __builtin_trap() => call abort
  if (my_strcmp(name, "__builtin_trap") == 0) {
    emit_line("\tbl\t_abort");
    return 0;
  }

  // __builtin_unreachable() => nop (undefined behavior)
  if (my_strcmp(name, "__builtin_unreachable") == 0) {
    return 0;
  }

  // __builtin_constant_p(expr) => always 0 (not a compile-time constant)
  if (my_strcmp(name, "__builtin_constant_p") == 0) {
    emit_line("\tmov\tx0, #0");
    return 0;
  }

  // __builtin_prefetch(addr, ...) => no-op hint
  if (my_strcmp(name, "__builtin_prefetch") == 0) {
    return 0;
  }

  // __builtin_expect(expr, val) => return expr (ignore hint)
  if (my_strcmp(name, "__builtin_expect") == 0) {
    gen_value(e->args[0]);
    return 0;
  }

  // __builtin_bswap16/32/64 => byte swap
  if (my_strcmp(name, "__builtin_bswap64") == 0) {
    gen_value(e->args[0]);
    emit_line("\trev\tx0, x0");
    return 0;
  }
  if (my_strcmp(name, "__builtin_bswap32") == 0) {
    gen_value(e->args[0]);
    emit_line("\trev\tw0, w0");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  if (my_strcmp(name, "__builtin_bswap16") == 0) {
    gen_value(e->args[0]);
    emit_line("\trev16\tw0, w0");
    emit_line("\tand\tw0, w0, #0xffff");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  // __builtin_copysign(x, y) => copy sign from y to x
  if (my_strcmp(name, "__builtin_copysign") == 0 || my_strcmp(name, "__builtin_copysignf") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tldr\tx1, [sp], #16");
    // Clear sign bit of x1, copy sign bit of x0 to x1
    emit_line("\tand\tx1, x1, #0x7fffffffffffffff");
    emit_line("\tand\tx0, x0, #0x8000000000000000");
    emit_line("\torr\tx0, x1, x0");
    return 0;
  }
  // __builtin_clrsb(x) => count leading redundant sign bits
  if (my_strcmp(name, "__builtin_clrsb") == 0) {
    gen_value(e->args[0]);
    emit_line("\tcls\tw0, w0");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  if (my_strcmp(name, "__builtin_clrsbl") == 0 || my_strcmp(name, "__builtin_clrsbll") == 0) {
    gen_value(e->args[0]);
    emit_line("\tcls\tx0, x0");
    return 0;
  }

  // __builtin_add_overflow(a, b, *result) => *result = a + b, return overflow
  if (my_strcmp(name, "__builtin_add_overflow") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[2]);  // pointer to result
    emit_line("\tmov\tx2, x0");
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tldr\tx0, [sp], #16");
    emit_line("\tadds\tx3, x0, x1");
    emit_line("\tstr\tx3, [x2]");
    emit_line("\tcset\tx0, vs");
    return 0;
  }
  // __builtin_sub_overflow(a, b, *result) => *result = a - b, return overflow
  if (my_strcmp(name, "__builtin_sub_overflow") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[2]);
    emit_line("\tmov\tx2, x0");
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tldr\tx0, [sp], #16");
    emit_line("\tsubs\tx3, x0, x1");
    emit_line("\tstr\tx3, [x2]");
    emit_line("\tcset\tx0, vs");
    return 0;
  }
  // __builtin_mul_overflow(a, b, *result) => *result = a * b, return overflow
  if (my_strcmp(name, "__builtin_mul_overflow") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[2]);
    emit_line("\tmov\tx2, x0");
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tldr\tx0, [sp], #16");
    emit_line("\tmul\tx3, x0, x1");
    emit_line("\tstr\tx3, [x2]");
    emit_line("\tsmulh\tx4, x0, x1");
    emit_line("\tcmp\tx4, x3, asr #63");
    emit_line("\tcset\tx0, ne");
    return 0;
  }
  // __builtin_mul_overflow_p(a, b, c) => return overflow (no store)
  if (my_strcmp(name, "__builtin_mul_overflow_p") == 0) {
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->args[1]);
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tmul\tx3, x1, x0");
    emit_line("\tsmulh\tx4, x1, x0");
    emit_line("\tcmp\tx4, x3, asr #63");
    emit_line("\tcset\tx0, ne");
    return 0;
  }

  // __builtin libc wrappers: call the underlying libc function
  if (my_strcmp(name, "__builtin_memcpy") == 0) { name = "memcpy"; }
  if (my_strcmp(name, "__builtin_memset") == 0) { name = "memset"; }
  if (my_strcmp(name, "__builtin_memcmp") == 0) { name = "memcmp"; }
  if (my_strcmp(name, "__builtin_strcmp") == 0) { name = "strcmp"; }
  if (my_strcmp(name, "__builtin_strlen") == 0) { name = "strlen"; }
  if (my_strcmp(name, "__builtin_strcpy") == 0) { name = "strcpy"; }
  if (my_strcmp(name, "__builtin_strncpy") == 0) { name = "strncpy"; }
  if (my_strcmp(name, "__builtin_printf") == 0) { name = "printf"; }
  if (my_strcmp(name, "__builtin_sprintf") == 0) { name = "sprintf"; }
  if (my_strcmp(name, "__builtin_malloc") == 0) { name = "malloc"; }
  if (my_strcmp(name, "__builtin_calloc") == 0) { name = "calloc"; }
  if (my_strcmp(name, "__builtin_free") == 0) { name = "free"; }
  if (my_strcmp(name, "__builtin_strchr") == 0) { name = "strchr"; }
  if (my_strcmp(name, "__builtin_strncmp") == 0) { name = "strncmp"; }
  if (my_strcmp(name, "__builtin_strcat") == 0) { name = "strcat"; }
  if (my_strcmp(name, "__builtin_strncat") == 0) { name = "strncat"; }
  if (my_strcmp(name, "__builtin_memmove") == 0) { name = "memmove"; }
  if (my_strcmp(name, "__builtin_bzero") == 0) { name = "bzero"; }
  if (my_strcmp(name, "__builtin_bcopy") == 0) { name = "bcopy"; }
  if (my_strcmp(name, "__builtin_fprintf") == 0) { name = "fprintf"; }
  if (my_strcmp(name, "__builtin_snprintf") == 0) { name = "snprintf"; }
  if (my_strcmp(name, "__builtin_puts") == 0) { name = "puts"; }
  if (my_strcmp(name, "__builtin_putchar") == 0) { name = "putchar"; }
  if (my_strcmp(name, "__builtin_fputc") == 0) { name = "fputc"; }
  if (my_strcmp(name, "__builtin_fputs") == 0) { name = "fputs"; }
  if (my_strcmp(name, "__builtin_fwrite") == 0) { name = "fwrite"; }
  // alloca / __builtin_alloca => stack allocation
  if (my_strcmp(name, "__builtin_alloca") == 0 || my_strcmp(name, "alloca") == 0) {
    gen_value(e->args[0]);
    // Round up to 16-byte alignment
    emit_line("\tadd\tx0, x0, #15");
    emit_line("\tand\tx0, x0, #-16");
    emit_line("\tsub\tsp, sp, x0");
    emit_line("\tmov\tx0, sp");
    return 0;
  }
  if (my_strcmp(name, "__builtin_abs") == 0) { name = "abs"; }
  if (my_strcmp(name, "__builtin_exit") == 0) { name = "exit"; }
  if (my_strcmp(name, "__builtin_puts") == 0) { name = "puts"; }
  if (my_strcmp(name, "__builtin_ffs") == 0) { name = "ffs"; }
  if (my_strcmp(name, "__builtin_ffsl") == 0) { name = "ffsl"; }
  if (my_strcmp(name, "__builtin_ffsll") == 0) { name = "ffsll"; }
  // __builtin_clz(x) => count leading zeros (32-bit)
  if (my_strcmp(name, "__builtin_clz") == 0) {
    gen_value(e->args[0]);
    emit_line("\tclz\tw0, w0");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  if (my_strcmp(name, "__builtin_clzl") == 0 || my_strcmp(name, "__builtin_clzll") == 0) {
    gen_value(e->args[0]);
    emit_line("\tclz\tx0, x0");
    return 0;
  }
  // __builtin_ctz(x) => count trailing zeros (32-bit)
  if (my_strcmp(name, "__builtin_ctz") == 0) {
    gen_value(e->args[0]);
    emit_line("\trbit\tw0, w0");
    emit_line("\tclz\tw0, w0");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  if (my_strcmp(name, "__builtin_ctzl") == 0 || my_strcmp(name, "__builtin_ctzll") == 0) {
    gen_value(e->args[0]);
    emit_line("\trbit\tx0, x0");
    emit_line("\tclz\tx0, x0");
    return 0;
  }
  // __builtin_popcount(x) => population count via bit manipulation
  if (my_strcmp(name, "__builtin_popcount") == 0 || my_strcmp(name, "__builtin_popcountl") == 0 || my_strcmp(name, "__builtin_popcountll") == 0) {
    gen_value(e->args[0]);
    emit_line("\tfmov\td0, x0");
    emit_line("\tcnt\tv0.8b, v0.8b");
    emit_line("\taddv\tb0, v0.8b");
    emit_line("\tfmov\tw0, s0");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  // __builtin_parity(x) => popcount % 2
  if (my_strcmp(name, "__builtin_parity") == 0 || my_strcmp(name, "__builtin_parityl") == 0 || my_strcmp(name, "__builtin_parityll") == 0) {
    gen_value(e->args[0]);
    emit_line("\tfmov\td0, x0");
    emit_line("\tcnt\tv0.8b, v0.8b");
    emit_line("\taddv\tb0, v0.8b");
    emit_line("\tfmov\tw0, s0");
    emit_line("\tand\tw0, w0, #1");
    emit_line("\tsxtw\tx0, w0");
    return 0;
  }
  // __builtin_signbit(x) => return sign bit
  if (my_strcmp(name, "__builtin_signbit") == 0 || my_strcmp(name, "__builtin_signbitf") == 0) {
    gen_value(e->args[0]);
    emit_line("\tlsr\tx0, x0, #63");
    return 0;
  }

  // __builtin_offsetof(type, member) => handled at parse time
  // __builtin_types_compatible_p(type1, type2) => always return 1
  if (my_strcmp(name, "__builtin_types_compatible_p") == 0) {
    emit_line("\tmov\tx0, #1");
    return 0;
  }

  // Generic variadic function call (Apple ARM64 variadic ABI)
  int vnp = 0 - 1;
  int vfi = 0;
  while (vfi < nvar_funcs) {
    if (my_strcmp(var_funcs[vfi], name) == 0) {
      vnp = var_nparams[vfi];
      vfi = nvar_funcs;
    }
    vfi++;
  }
  if (vnp >= 0) {
    int n_named = vnp;
    if (n_named > nargs) { n_named = nargs; }
    int n_var = nargs - n_named;
    // Allocate stack for variadic args
    if (n_var > 0) {
      var_space = ((n_var * 8 + 15) / 16) * 16;
      emit_s("\tsub\tsp, sp, #");
      emit_num(var_space);
      emit_ch('\n');
      int vsi = 0;
      while (vsi < n_var) {
        gen_value(e->args[n_named + vsi]);
        emit_s("\tstr\tx0, [sp, #");
        emit_num(vsi * 8);
        emit_line("]");
        vsi++;
      }
    }
    // Push named args to temp area
    int nai = 0;
    while (nai < n_named) {
      gen_value(e->args[nai]);
      emit_line("\tstr\tx0, [sp, #-16]!");
      nai++;
    }
    // Load named args into registers
    nai = 0;
    while (nai < n_named) {
      emit_s("\tldr\tx");
      emit_num(nai);
      emit_s(", [sp, #");
      emit_num((n_named - 1 - nai) * 16);
      emit_line("]");
      nai++;
    }
    // Pop named temp area so sp points to variadic args
    if (n_named > 0) {
      emit_s("\tadd\tsp, sp, #");
      emit_num(n_named * 16);
      emit_ch('\n');
    }
    emit_s("\tbl\t_");
    emit_line(name);
    // Clean up variadic stack
    if (n_var > 0) {
      var_space = ((n_var * 8 + 15) / 16) * 16;
      emit_s("\tadd\tsp, sp, #");
      emit_num(var_space);
      emit_ch('\n');
    }
    if (func_returns_ptr(name) == 0 && func_returns_unsigned(name) == 0) {
      emit_line("\tsxtw\tx0, w0");
    }
    return 0;
  }

  // Regular function call
  int ai = 0;
  int disp = 0;
  int real_nargs = 0;
  int reg_nargs = 0;
  int extra = 0;
  int stack_arg_space = 0;
  int src_disp = 0;

  // Indirect call through arbitrary expression (e.g. s.field(args))
  if (my_strcmp(name, "__indirect_call") == 0) {
    real_nargs = nargs - 1;
    gen_value(e->args[0]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    ai = 0;
    while (ai < real_nargs) {
      gen_value(e->args[1 + ai]);
      emit_line("\tstr\tx0, [sp, #-16]!");
      ai++;
    }
    reg_nargs = real_nargs;
    if (reg_nargs > 8) { reg_nargs = 8; }
    extra = real_nargs - reg_nargs;
    stack_arg_space = 0;
    if (extra > 0) { stack_arg_space = ((extra * 8 + 15) / 16) * 16; }
    if (stack_arg_space > 0) {
      emit_s("\tsub\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
    }
    ai = 0;
    while (ai < extra) {
      src_disp = (real_nargs - 1 - (8 + ai)) * 16 + stack_arg_space;
      emit_s("\tldr\tx9, [sp, #"); emit_num(src_disp); emit_line("]");
      emit_s("\tstr\tx9, [sp, #"); emit_num(ai * 8); emit_line("]");
      ai++;
    }
    emit_s("\tldr\tx8, [sp, #"); emit_num(real_nargs * 16 + stack_arg_space); emit_line("]");
    ai = 0;
    while (ai < reg_nargs) {
      disp = (real_nargs - 1 - ai) * 16 + stack_arg_space;
      emit_s("\tldr\tx"); emit_num(ai); emit_s(", [sp, #"); emit_num(disp); emit_line("]");
      ai++;
    }
    emit_line("\tblr\tx8");
    if (stack_arg_space > 0) {
      emit_s("\tadd\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
    }
    emit_s("\tadd\tsp, sp, #"); emit_num((real_nargs + 1) * 16); emit_ch('\n');
    return 0;
  }

  // Indirect call through function pointer variable
  if (is_known_func(name) == 0 && (cg_find_slot(name) >= 0 || cg_is_global(name))) {
    gen_value(new_var(name));
    emit_line("\tstr\tx0, [sp, #-16]!");
    ai = 0;
    while (ai < nargs) {
      gen_value(e->args[ai]);
      emit_line("\tstr\tx0, [sp, #-16]!");
      ai++;
    }
    reg_nargs = nargs;
    if (reg_nargs > 8) { reg_nargs = 8; }
    extra = nargs - reg_nargs;
    stack_arg_space = 0;
    if (extra > 0) { stack_arg_space = ((extra * 8 + 15) / 16) * 16; }
    if (stack_arg_space > 0) {
      emit_s("\tsub\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
    }
    ai = 0;
    while (ai < extra) {
      src_disp = (nargs - 1 - (8 + ai)) * 16 + stack_arg_space;
      emit_s("\tldr\tx9, [sp, #"); emit_num(src_disp); emit_line("]");
      emit_s("\tstr\tx9, [sp, #"); emit_num(ai * 8); emit_line("]");
      ai++;
    }
    emit_s("\tldr\tx8, [sp, #"); emit_num(nargs * 16 + stack_arg_space); emit_line("]");
    ai = 0;
    while (ai < reg_nargs) {
      disp = (nargs - 1 - ai) * 16 + stack_arg_space;
      emit_s("\tldr\tx"); emit_num(ai); emit_s(", [sp, #"); emit_num(disp); emit_line("]");
      ai++;
    }
    emit_line("\tblr\tx8");
    if (stack_arg_space > 0) {
      emit_s("\tadd\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
    }
    emit_s("\tadd\tsp, sp, #"); emit_num((nargs + 1) * 16); emit_ch('\n');
    return 0;
  }

  // Direct function call
  ai = 0;
  while (ai < nargs) {
    gen_value(e->args[ai]);
    emit_line("\tstr\tx0, [sp, #-16]!");
    ai++;
  }
  reg_nargs = nargs;
  if (reg_nargs > 8) { reg_nargs = 8; }
  extra = nargs - reg_nargs;
  stack_arg_space = 0;
  if (extra > 0) { stack_arg_space = ((extra * 8 + 15) / 16) * 16; }
  if (stack_arg_space > 0) {
    emit_s("\tsub\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
  }
  ai = 0;
  while (ai < extra) {
    src_disp = (nargs - 1 - (8 + ai)) * 16 + stack_arg_space;
    emit_s("\tldr\tx9, [sp, #"); emit_num(src_disp); emit_line("]");
    emit_s("\tstr\tx9, [sp, #"); emit_num(ai * 8); emit_line("]");
    ai++;
  }
  ai = 0;
  while (ai < reg_nargs) {
    disp = (nargs - 1 - ai) * 16 + stack_arg_space;
    emit_s("\tldr\tx"); emit_num(ai); emit_s(", [sp, #"); emit_num(disp); emit_line("]");
    ai++;
  }
  emit_s("\tbl\t_"); emit_line(name);
  if (stack_arg_space > 0) {
    emit_s("\tadd\tsp, sp, #"); emit_num(stack_arg_space); emit_ch('\n');
  }
  if (nargs > 0) {
    emit_s("\tadd\tsp, sp, #"); emit_num(nargs * 16); emit_ch('\n');
  }
  if (func_returns_float(name)) {
    emit_line("\tfmov\tx0, d0");
  } else if (func_returns_ptr(name) == 0 && func_ret_stype(name) == 0 && func_returns_unsigned(name) == 0) {
    emit_line("\tsxtw\tx0, w0");
  }
  return 0;
}

int gen_val_label_addr(struct Expr *e) {
  int *la_tmp1 = build_str2("L_usr_", cg_cur_func_name);
  int *la_tmp2 = build_str2(la_tmp1, "_");
  int *la_lbl = build_str2(la_tmp2, e->sval);
  emit_s("\tadrp\tx0, ");
  emit_s(la_lbl);
  emit_line("@PAGE");
  emit_s("\tadd\tx0, x0, ");
  emit_s(la_lbl);
  emit_line("@PAGEOFF");
  return 0;
}

int gen_value(struct Expr *e) {
  if (e == 0) { printf("cc: gen_value called with NULL\n"); fflush(0); emit_line("\tmov\tx0, #0"); return 0; }
  if (e < 4096) { printf("cc: gen_value bad ptr %d in %s\n", e, cg_cur_func_name); fflush(0); emit_line("\tmov\tx0, #0"); return 0; }
  if (e->kind < 0 || e->kind > 17) { printf("cc: gen_value bad kind %d in %s\n", e->kind, cg_cur_func_name); fflush(0); emit_line("\tmov\tx0, #0"); return 0; }
  if (e->kind == ND_CAST) return gen_val_cast(e);
  if (e->kind == ND_NUM) return gen_val_num(e);
  if (e->kind == ND_VAR) return gen_val_var(e);
  if (e->kind == ND_FIELD || e->kind == ND_ARROW) return gen_val_field_arrow(e);
  if (e->kind == ND_INDEX) return gen_val_index(e);
  if (e->kind == ND_ASSIGN) return gen_val_assign(e);
  if (e->kind == ND_POSTINC || e->kind == ND_POSTDEC) return gen_val_postinc_postdec(e);
  if (e->kind == ND_COMPOUND_LIT) return gen_val_compoulit(e);
  if (e->kind == ND_STMT_EXPR) return gen_val_stmt_expr(e);
  if (e->kind == ND_TERNARY) return gen_val_ternary(e);
  if (e->kind == ND_STRLIT) return gen_val_strlit(e);
  if (e->kind == ND_UNARY) return gen_val_unary(e);
  if (e->kind == ND_BINARY) return gen_val_binary(e);
  if (e->kind == ND_CALL) return gen_val_call(e);
  if (e->kind == ND_LABEL_ADDR) return gen_val_label_addr(e);
  printf("cc: unsupported expression kind=%d in %s\n", e->kind, cg_cur_func_name);
  fflush(0);
  emit_line("\tmov\tx0, #0");
  return 0;
}


int gen_block(struct Stmt **stmts, int nstmts, int *ret_label) {
  for (int i = 0; i < nstmts; i++) {
    if (stmts[i] == 0 || stmts[i] < 4096) continue;
    if (stmts[i]->kind < 0 || stmts[i]->kind > 13) continue;
    gen_stmt(stmts[i], ret_label);
  }
  return 0;
}

int gen_stmt_return(struct Stmt *st, int *ret_label) {
  if (cg_cur_func_ret_stype != 0) {
    gen_addr(st->expr);
  } else {
    gen_value(st->expr);
  }
  emit_s("\tb\t"); emit_line(ret_label);
  return 0;
}

int gen_stmt_expr(struct Stmt *st, int *ret_label) {
  gen_value(st->expr);
  return 0;
}

int gen_stmt_block(struct Stmt *st, int *ret_label) {
  gen_block(st->body, st->nbody, ret_label);
  return 0;
}

int gen_stmt_vardecl(struct Stmt *st, int *ret_label) {
  int i = 0;
  int base_off = 0;
  int elem_off = 0;
  int k = 0;
  int *vd_di = 0;
  int vd_pos_idx = 0;
  int vd_target = 0;
  int nf = 0;
  while (i < st->ndecls) {
    struct VarDecl *vd = st->decls[i];
    // Skip static locals (init handled in .data section)
    if (vd->is_static) { i++; continue; }
    // Struct initializer: struct Foo x = {a, b, c};
    if (vd->stype != 0 && vd->is_ptr == 0 && vd->arr_size < 0) {
      if (vd->init != 0 && vd->init->kind == ND_INITLIST) {
        base_off = cg_find_slot(vd->name);
        // Zero-fill struct before writing init elements
        {
          int bsz = cg_struct_byte_size(vd->stype);
          int nslots = (bsz + 7) / 8;
          k = 0;
          while (k < nslots) {
            elem_off = base_off - k * 8;
            emit_line("\tmov\tx0, #0");
            if (elem_off <= 255) {
              emit_s("\tstr\tx0, [x29, #-"); emit_num(elem_off); emit_line("]");
            } else {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstr\tx0, [x9]");
            }
            k++;
          }
        }
        vd_di = vd->init->desig;
        vd_pos_idx = 0;
        k = 0;
        while (k < vd->init->nargs) {
          if (vd->init->args[k] != 0 && vd->init->args[k]->kind == ND_INITLIST) {
            struct Expr *inner = vd->init->args[k];
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            int outer_boff = cg_field_byte_offset_idx(vd->stype, vd_target);
            int *inner_stype = cg_field_type_idx(vd->stype, vd_target);
            int ni_j = 0;
            while (ni_j < inner->nargs) {
              gen_value(inner->args[ni_j]);
              int inner_boff = 0;
              int inner_bsz = 8;
              if (inner_stype != 0) {
                inner_boff = cg_field_byte_offset_idx(inner_stype, ni_j);
                inner_bsz = cg_field_byte_size_idx(inner_stype, ni_j);
              } else {
                inner_boff = ni_j * 8;
              }
              elem_off = base_off - (outer_boff + inner_boff);
              emit_sub_imm("x9", "x29", elem_off);
              if (inner_bsz == 1) { emit_line("\tstrb\tw0, [x9]"); }
              else if (inner_bsz == 2) { emit_line("\tstrh\tw0, [x9]"); }
              else if (inner_bsz == 4) { emit_line("\tstr\tw0, [x9]"); }
              else { emit_line("\tstr\tx0, [x9]"); }
              ni_j++;
            }
            vd_pos_idx = vd_target + 1;
            k++;
            continue;
          }
          gen_value(vd->init->args[k]);
          vd_target = vd_pos_idx;
          if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
          vd_pos_idx = vd_target + 1;
          elem_off = base_off - cg_field_byte_offset_idx(vd->stype, vd_target);
          {
            int fbsz = cg_field_byte_size_idx(vd->stype, vd_target);
            emit_sub_imm("x9", "x29", elem_off);
            if (fbsz == 1) { emit_line("\tstrb\tw0, [x9]"); }
            else if (fbsz == 2) { emit_line("\tstrh\tw0, [x9]"); }
            else if (fbsz == 4) { emit_line("\tstr\tw0, [x9]"); }
            else { emit_line("\tstr\tx0, [x9]"); }
          }
          k++;
        }
      } else if (vd->init != 0 && vd->init->kind == ND_CALL) {
        // Struct init from function call: struct Foo x = make_foo();
        base_off = cg_find_slot(vd->name);
        gen_value(vd->init);
        // x0 = pointer to returned struct
        emit_line("\tmov\tx10, x0");
        {
          int bsz = cg_struct_byte_size(vd->stype);
          int nslots = (bsz + 7) / 8;
          k = 0;
          while (k < nslots) {
            emit_s("\tldr\tx9, [x10, #"); emit_num(k * 8); emit_line("]");
            elem_off = base_off - k * 8;
            emit_sub_imm("x11", "x29", elem_off);
            emit_line("\tstr\tx9, [x11]");
            k++;
          }
        }
      } else if (vd->init != 0) {
        // Struct copy from expression: struct Foo x = other_struct;
        base_off = cg_find_slot(vd->name);
        gen_addr(vd->init);
        emit_line("\tmov\tx10, x0");
        {
          int bsz = cg_struct_byte_size(vd->stype);
          int nslots = (bsz + 7) / 8;
          k = 0;
          while (k < nslots) {
            emit_s("\tldr\tx9, [x10, #"); emit_num(k * 8); emit_line("]");
            elem_off = base_off - k * 8;
            emit_sub_imm("x11", "x29", elem_off);
            emit_line("\tstr\tx9, [x11]");
            k++;
          }
        }
      }
      i++;
      continue;
    }
    // Array with initializer list or string
    if (vd->arr_size >= 0) {
      if (vd->init != 0 && vd->init->kind == ND_INITLIST) {
        base_off = cg_find_slot(vd->name);
        int is_clarr = cg_is_char_larr(vd->name);
        if (is_clarr) {
          // Char local array: zero-fill bytes, then store bytes
          int nbytes = ((vd->arr_size + 7) / 8) * 8;
          // Zero-fill using 8-byte stores for speed
          k = 0;
          while (k < nbytes) {
            elem_off = base_off - k;
            emit_line("\tmov\tx0, #0");
            emit_sub_imm("x9", "x29", elem_off);
            emit_line("\tstr\tx0, [x9]");
            k = k + 8;
          }
          vd_di = vd->init->desig;
          vd_pos_idx = 0;
          k = 0;
          while (k < vd->init->nargs) {
            gen_value(vd->init->args[k]);
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            vd_pos_idx = vd_target + 1;
            elem_off = base_off - vd_target;
            emit_sub_imm("x9", "x29", elem_off);
            emit_line("\tstrb\tw0, [x9]");
            k++;
          }
        } else if (vd->stype != 0 && vd->is_ptr == 0) {
        // Proper layout: array of structs
        int struct_bsz = cg_struct_byte_size(vd->stype);
        int total_bytes = vd->arr_size * struct_bsz;
        int zero_slots = (total_bytes + 7) / 8;
        k = 0;
        while (k < zero_slots) {
          elem_off = base_off - k * 8;
          emit_line("\tmov\tx0, #0");
          if (elem_off <= 255) {
            emit_s("\tstr\tx0, [x29, #-"); emit_num(elem_off); emit_line("]");
          } else {
            emit_sub_imm("x9", "x29", elem_off);
            emit_line("\tstr\tx0, [x9]");
          }
          k++;
        }
        vd_di = vd->init->desig;
        vd_pos_idx = 0;
        k = 0;
        while (k < vd->init->nargs) {
          if (vd->init->args[k] != 0 && vd->init->args[k]->kind == ND_INITLIST) {
            struct Expr *inner = vd->init->args[k];
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            int ni_j = 0;
            while (ni_j < inner->nargs) {
              gen_value(inner->args[ni_j]);
              int fboff = vd_target * struct_bsz + cg_field_byte_offset_idx(vd->stype, ni_j);
              elem_off = base_off - fboff;
              {
                int fbsz = cg_field_byte_size_idx(vd->stype, ni_j);
                emit_sub_imm("x9", "x29", elem_off);
                if (fbsz == 1) { emit_line("\tstrb\tw0, [x9]"); }
                else if (fbsz == 2) { emit_line("\tstrh\tw0, [x9]"); }
                else if (fbsz == 4) { emit_line("\tstr\tw0, [x9]"); }
                else { emit_line("\tstr\tx0, [x9]"); }
              }
              ni_j++;
            }
            vd_pos_idx = vd_target + 1;
          } else {
            gen_value(vd->init->args[k]);
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            vd_pos_idx = vd_target + 1;
            elem_off = base_off - vd_target * 8;
            if (elem_off <= 255) {
              emit_s("\tstr\tx0, [x29, #-"); emit_num(elem_off); emit_line("]");
            } else {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstr\tx0, [x9]");
            }
          }
          k++;
        }
        } else {
        // Non-char array: use tracked element size
        int init_esz = cg_arr_esz(vd->name);
        if (init_esz == 0) { init_esz = 8; }
        // Zero-fill the entire array before writing init elements
        {
          int total_bytes = 0;
          if (vd->stype != 0 && vd->is_ptr == 0) {
            total_bytes = vd->arr_size * cg_struct_byte_size(vd->stype);
          } else {
            total_bytes = vd->arr_size * init_esz;
          }
          int zbi = 0;
          while (zbi + 8 <= total_bytes) {
            elem_off = base_off - zbi;
            emit_line("\tmov\tx0, #0");
            if (elem_off <= 255) {
              emit_s("\tstr\tx0, [x29, #-"); emit_num(elem_off); emit_line("]");
            } else {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstr\tx0, [x9]");
            }
            zbi = zbi + 8;
          }
          while (zbi + 4 <= total_bytes) {
            elem_off = base_off - zbi;
            emit_line("\tmov\tw0, #0");
            emit_sub_imm("x9", "x29", elem_off);
            emit_line("\tstr\tw0, [x9]");
            zbi = zbi + 4;
          }
          while (zbi + 2 <= total_bytes) {
            elem_off = base_off - zbi;
            emit_line("\tmov\tw0, #0");
            emit_sub_imm("x9", "x29", elem_off);
            emit_line("\tstrh\tw0, [x9]");
            zbi = zbi + 2;
          }
        }
        vd_di = vd->init->desig;
        vd_pos_idx = 0;
        k = 0;
        while (k < vd->init->nargs) {
          // Handle nested init lists (array of structs: { {a,b}, {c,d} })
          if (vd->init->args[k] != 0 && vd->init->args[k]->kind == ND_INITLIST) {
            struct Expr *inner = vd->init->args[k];
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            int ni_j = 0;
            while (ni_j < inner->nargs) {
              gen_value(inner->args[ni_j]);
              elem_off = base_off - (vd_target + ni_j) * init_esz;
              emit_sub_imm("x9", "x29", elem_off);
              if (init_esz == 4) { emit_line("\tstr\tw0, [x9]"); }
              else if (init_esz == 2) { emit_line("\tstrh\tw0, [x9]"); }
              else { emit_line("\tstr\tx0, [x9]"); }
              ni_j++;
            }
            vd_pos_idx = vd_target + inner->nargs;
          } else {
            gen_value(vd->init->args[k]);
            vd_target = vd_pos_idx;
            if (vd_di != 0 && vd_di[k] >= 0) { vd_target = vd_di[k]; }
            vd_pos_idx = vd_target + 1;
            elem_off = base_off - vd_target * init_esz;
            if (init_esz == 4) {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstr\tw0, [x9]");
            } else if (init_esz == 2) {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstrh\tw0, [x9]");
            } else if (elem_off <= 255) {
              emit_s("\tstr\tx0, [x29, #-"); emit_num(elem_off); emit_line("]");
            } else {
              emit_sub_imm("x9", "x29", elem_off);
              emit_line("\tstr\tx0, [x9]");
            }
          }
          k++;
        }
        } // end non-char
      } else if (vd->init != 0 && vd->init->kind == ND_STRLIT) {
        // String initializer: char s[] = "hello";
        base_off = cg_find_slot(vd->name);
        int *decoded = cg_decode_string(vd->init->sval);
        int slen = my_strlen(decoded) + 1;
        int str_char_larr = cg_is_char_larr(vd->name);
        k = 0;
        while (k < slen && k < vd->arr_size) {
          int ch = __read_byte(decoded, k);
          emit_s("\tmov\tx0, #");
          emit_num(ch);
          emit_ch('\n');
          if (str_char_larr) {
            elem_off = base_off - k;
          } else {
            elem_off = base_off - k * 8;
          }
          if (str_char_larr) {
            emit_s("\tsub\tx9, x29, #");
            emit_num(elem_off);
            emit_ch('\n');
            emit_line("\tstrb\tw0, [x9]");
          } else if (elem_off <= 255) {
            emit_s("\tstr\tx0, [x29, #-");
            emit_num(elem_off);
            emit_line("]");
          } else {
            emit_s("\tsub\tx9, x29, #");
            emit_num(elem_off);
            emit_ch('\n');
            emit_line("\tstr\tx0, [x9]");
          }
          k++;
        }
      }
      i++;
      continue;
    }
    int off = cg_find_slot(vd->name);
    int vd_bsz = cg_var_bsz(vd->name);
    if (vd->init != 0) {
      gen_value(vd->init);
      // Int-to-float conversion for float var init
      if (vd->is_float && expr_is_float(vd->init) == 0) {
        emit_line("\tscvtf\td0, x0");
        emit_line("\tfmov\tx0, d0");
      }
      // Truncate bare char initializer
      { int bc = cg_is_barechar(vd->name);
        if (bc == 2) { emit_line("\tuxtb\tw0, w0"); }
        else if (bc == 1) { emit_line("\tsxtb\tx0, w0"); }
      }
    } else {
      emit_line("\tmov\tx0, #0");
    }
    if (vd_bsz == 1) {
      emit_sub_imm("x9", "x29", off);
      emit_line("\tstrb\tw0, [x9]");
    } else if (vd_bsz == 2) {
      emit_sub_imm("x9", "x29", off);
      emit_line("\tstrh\tw0, [x9]");
    } else if (vd_bsz == 4) {
      emit_sub_imm("x9", "x29", off);
      emit_line("\tstr\tw0, [x9]");
    } else if (off <= 255) {
      emit_s("\tstr\tx0, [x29, #-");
      emit_num(off);
      emit_line("]");
    } else {
      emit_mov_imm("x9", off);
      emit_line("\tsub\tx9, x29, x9");
      emit_line("\tstr\tx0, [x9]");
    }
    i++;
  }
  return 0;
}

int gen_stmt_if(struct Stmt *st, int *ret_label) {
  int *else_l = 0;
  int *end_l = 0;
  else_l = cg_new_label("else");
  end_l = cg_new_label("endif");
  gen_value(st->expr);
  emit_line("\tcmp\tx0, #0");
  if (st->body2 == 0) {
    emit_s("\tb.eq\t"); emit_line(end_l);
    gen_block(st->body, st->nbody, ret_label);
    emit_s(end_l); emit_line(":");
  } else {
    emit_s("\tb.eq\t"); emit_line(else_l);
    gen_block(st->body, st->nbody, ret_label);
    emit_s("\tb\t"); emit_line(end_l);
    emit_s(else_l); emit_line(":");
    gen_block(st->body2, st->nbody2, ret_label);
    emit_s(end_l); emit_line(":");
  }
  return 0;
}

int gen_stmt_while(struct Stmt *st, int *ret_label) {
  int *start_l = 0;
  int *end_l = 0;
  start_l = cg_new_label("while_start");
  end_l = cg_new_label("while_end");
  loop_brk[nloop] = end_l;
  loop_cont[nloop] = start_l;
  nloop++;

  emit_s(start_l); emit_line(":");
  gen_value(st->expr);
  emit_line("\tcmp\tx0, #0");
  emit_s("\tb.eq\t"); emit_line(end_l);
  gen_block(st->body, st->nbody, ret_label);
  emit_s("\tb\t"); emit_line(start_l);
  emit_s(end_l); emit_line(":");

  nloop--;
  return 0;
}

int gen_stmt_for(struct Stmt *st, int *ret_label) {
  int *start_l = 0;
  int *end_l = 0;
  int *post_l = 0;
  start_l = cg_new_label("for_start");
  post_l = cg_new_label("for_post");
  end_l = cg_new_label("for_end");

  if (st->init != 0) {
    gen_stmt(st->init, ret_label);
  }

  loop_brk[nloop] = end_l;
  loop_cont[nloop] = post_l;
  nloop++;

  emit_s(start_l); emit_line(":");
  if (st->expr != 0) {
    gen_value(st->expr);
    emit_line("\tcmp\tx0, #0");
    emit_s("\tb.eq\t"); emit_line(end_l);
  }

  gen_block(st->body, st->nbody, ret_label);

  emit_s(post_l); emit_line(":");
  if (st->expr2 != 0) {
    gen_value(st->expr2);
  }

  emit_s("\tb\t"); emit_line(start_l);
  emit_s(end_l); emit_line(":");

  nloop--;
  return 0;
}

int gen_stmt_break(struct Stmt *st, int *ret_label) {
  emit_s("\tb\t"); emit_line(loop_brk[nloop - 1]);
  return 0;
}

int gen_stmt_continue(struct Stmt *st, int *ret_label) {
  emit_s("\tb\t"); emit_line(loop_cont[nloop - 1]);
  return 0;
}

int gen_stmt_dowhile(struct Stmt *st, int *ret_label) {
  int *start_l = 0;
  int *end_l = 0;
  int *cont_l = 0;
  start_l = cg_new_label("dowhile_start");
  end_l = cg_new_label("dowhile_end");
  cont_l = cg_new_label("dowhile_cont");
  loop_brk[nloop] = end_l;
  loop_cont[nloop] = cont_l;
  nloop++;

  emit_s(start_l); emit_line(":");
  gen_block(st->body, st->nbody, ret_label);
  emit_s(cont_l); emit_line(":");
  gen_value(st->expr);
  emit_line("\tcmp\tx0, #0");
  emit_s("\tb.ne\t"); emit_line(start_l);
  emit_s(end_l); emit_line(":");

  nloop--;
  return 0;
}

int gen_stmt_goto(struct Stmt *st, int *ret_label) {
  int *goto_tmp1 = 0;
  int *goto_tmp2 = 0;
  int *goto_lbl = 0;
  goto_tmp1 = build_str2("L_usr_", cg_cur_func_name);
  goto_tmp2 = build_str2(goto_tmp1, "_");
  goto_lbl = build_str2(goto_tmp2, st->sval);
  emit_s("\tb\t"); emit_line(goto_lbl);
  return 0;
}

int gen_stmt_label(struct Stmt *st, int *ret_label) {
  int *goto_tmp1 = 0;
  int *goto_tmp2 = 0;
  int *goto_lbl = 0;
  goto_tmp1 = build_str2("L_usr_", cg_cur_func_name);
  goto_tmp2 = build_str2(goto_tmp1, "_");
  goto_lbl = build_str2(goto_tmp2, st->sval);
  emit_s(goto_lbl); emit_line(":");
  gen_block(st->body, st->nbody, ret_label);
  return 0;
}

int gen_stmt_switch(struct Stmt *st, int *ret_label) {
  int *end_l = 0;
  int **tramp_labels = 0;
  int **body_labels = 0;
  int *tl = 0;
  int *bl = 0;
  int *def_label = 0;
  int ci = 0;
  end_l = cg_new_label("sw_end");
  loop_brk[nloop] = end_l;
  if (nloop > 0) { loop_cont[nloop] = loop_cont[nloop - 1]; }
  else { loop_cont[nloop] = 0; }
  nloop++;

  // Evaluate condition, push to stack
  gen_value(st->expr);
  emit_line("\tstr\tx0, [sp, #-16]!");

  // Generate comparisons for each case
  tramp_labels = my_malloc((st->ncases + 1) * 8);
  ci = 0;
  while (ci < st->ncases) {
    tl = cg_new_label("sw_tramp");
    tramp_labels[ci] = tl;
    emit_line("\tldr\tx0, [sp]");
    emit_mov_imm("x1", st->case_vals[ci]);
    emit_line("\tcmp\tx0, x1");
    emit_s("\tb.eq\t"); emit_line(tl);
    ci++;
  }

  // After all comparisons: jump to default or end
  def_label = 0;
  if (st->default_body != 0 && st->ndefault > 0) {
    def_label = cg_new_label("sw_def");
    // Pop condition and jump to default
    emit_line("\tadd\tsp, sp, #16");
    emit_s("\tb\t"); emit_line(def_label);
  } else {
    // Pop condition and jump to end
    emit_line("\tadd\tsp, sp, #16");
    emit_s("\tb\t"); emit_line(end_l);
  }

  // Trampolines: pop condition, jump to body
  body_labels = my_malloc((st->ncases + 1) * 8);
  ci = 0;
  while (ci < st->ncases) {
    bl = cg_new_label("sw_body");
    body_labels[ci] = bl;
    emit_s(tramp_labels[ci]); emit_line(":");
    emit_line("\tadd\tsp, sp, #16");
    emit_s("\tb\t"); emit_line(bl);
    ci++;
  }

  // Case bodies (with fall-through)
  ci = 0;
  while (ci < st->ncases) {
    emit_s(body_labels[ci]); emit_line(":");
    gen_block(st->case_bodies[ci], st->case_nbodies[ci], ret_label);
    ci++;
  }

  // Default body
  if (def_label != 0) {
    emit_s(def_label); emit_line(":");
    gen_block(st->default_body, st->ndefault, ret_label);
  }

  emit_s(end_l); emit_line(":");
  nloop--;
  return 0;
}

int gen_stmt_computed_goto(struct Stmt *st, int *ret_label) {
  gen_value(st->expr);
  emit_line("\tbr\tx0");
  return 0;
}

int gen_stmt(struct Stmt *st, int *ret_label) {
  if (st == 0 || st < 4096) return 0;
  if (st->kind < 0 || st->kind > 13) return 0;
  if (st->kind == ST_RETURN) return gen_stmt_return(st, ret_label);
  if (st->kind == ST_EXPR) return gen_stmt_expr(st, ret_label);
  if (st->kind == ST_BLOCK) return gen_stmt_block(st, ret_label);
  if (st->kind == ST_VARDECL) return gen_stmt_vardecl(st, ret_label);
  if (st->kind == ST_IF) return gen_stmt_if(st, ret_label);
  if (st->kind == ST_WHILE) return gen_stmt_while(st, ret_label);
  if (st->kind == ST_FOR) return gen_stmt_for(st, ret_label);
  if (st->kind == ST_BREAK) return gen_stmt_break(st, ret_label);
  if (st->kind == ST_CONTINUE) return gen_stmt_continue(st, ret_label);
  if (st->kind == ST_DOWHILE) return gen_stmt_dowhile(st, ret_label);
  if (st->kind == ST_GOTO) return gen_stmt_goto(st, ret_label);
  if (st->kind == ST_LABEL) return gen_stmt_label(st, ret_label);
  if (st->kind == ST_SWITCH) return gen_stmt_switch(st, ret_label);
  if (st->kind == ST_COMPUTED_GOTO) return gen_stmt_computed_goto(st, ret_label);
  printf("cc: unsupported stmt kind=%d in %s\n", st->kind, cg_cur_func_name);
  fflush(0);
  return 0;
}


int gen_func(struct FuncDef *f) {
  if (f->name == 0) { printf("cc: gen_func NULL name, skip\n"); fflush(0); return 0; }
  cg_cur_func_name = f->name;
  cg_cur_func_ret_stype = f->ret_stype;
  cg_cur_func_ret_is_float = f->ret_is_float;
  cg_cl_counter = 0;
  cg_cl_gen_counter = 0;
  layout_func(f);

  int *ret_label = cg_new_label("ret");

  emit_ch('\n');
  emit_line("\t.p2align\t2");
  if (f->is_static == 0) { emit_s("\t.globl\t_"); emit_line(f->name); }
  emit_s("_"); emit_s(f->name); emit_line(":");
  emit_line("\tstp\tx29, x30, [sp, #-16]!");
  emit_line("\tmov\tx29, sp");
  if (lay_stack_size > 0) {
    if (lay_stack_size <= 4095) {
      emit_s("\tsub\tsp, sp, #");
      emit_num(lay_stack_size);
      emit_ch('\n');
    } else {
      emit_mov_imm("x9", lay_stack_size);
      emit_line("\tsub\tsp, sp, x9");
    }
  }

  for (int i = 0; i < f->nparams && i < 8; i++) {
    int off = cg_find_slot(f->params[i]);
    if (f->param_stypes != 0 && f->param_stypes[i] != 0) {
      int bsz = cg_struct_byte_size(f->param_stypes[i]);
      int nf_copy = (bsz + 7) / 8;
      for (int fi = 0; fi < nf_copy; fi++) {
        int src_off = fi * 8;
        int dst_off = off - fi * 8;
        if (src_off <= 32760) {
          emit_s("\tldr\tx9, [x"); emit_num(i); emit_s(", #"); emit_num(src_off); emit_line("]");
        } else {
          emit_mov_imm("x10", src_off);
          emit_s("\tadd\tx10, x"); emit_num(i); emit_line(", x10");
          emit_line("\tldr\tx9, [x10]");
        }
        if (dst_off <= 255) {
          emit_s("\tstr\tx9, [x29, #-");
          emit_num(dst_off);
          emit_line("]");
        } else {
          emit_mov_imm("x10", dst_off);
          emit_line("\tsub\tx10, x29, x10");
          emit_line("\tstr\tx9, [x10]");
        }
      }
    } else {
      // Extend params to clean upper 32 bits based on type width
      int is_64bit_param = 0;
      if (f->param_is_intptr != 0 && f->param_is_intptr[i]) { is_64bit_param = 1; }
      if (f->param_is_char != 0 && f->param_is_char[i]) { is_64bit_param = 1; }
      if (f->param_stypes != 0 && f->param_stypes[i] != 0) { is_64bit_param = 1; }
      if (f->param_is_long != 0 && f->param_is_long[i]) { is_64bit_param = 1; }
      if (is_64bit_param == 0) {
        int p_is_unsigned = (f->param_is_unsigned != 0 && f->param_is_unsigned[i]);
        int p_is_short = (f->param_is_short != 0 && f->param_is_short[i]);
        if (p_is_short) {
          if (p_is_unsigned) { emit_s("\tuxth\tw"); emit_num(i); emit_s(", w"); emit_num(i); emit_ch('\n'); }
          else { emit_s("\tsxth\tx"); emit_num(i); emit_s(", w"); emit_num(i); emit_ch('\n'); }
        } else if (p_is_unsigned) {
          // unsigned int: writing to wN zero-extends to xN, but value may already be clean
          emit_s("\tmov\tw"); emit_num(i); emit_s(", w"); emit_num(i); emit_ch('\n');
        } else {
          emit_s("\tsxtw\tx"); emit_num(i); emit_s(", w"); emit_num(i); emit_ch('\n');
        }
      }
      if (off <= 255) {
        emit_s("\tstr\tx");
        emit_num(i);
        emit_s(", [x29, #-");
        emit_num(off);
        emit_line("]");
      } else {
        emit_mov_imm("x9", off);
        emit_line("\tsub\tx9, x29, x9");
        emit_s("\tstr\tx");
        emit_num(i);
        emit_line(", [x9]");
      }
    }
  }
  // Params 8+ are already on stack at [x29+16], [x29+24], etc.

  gen_block(f->body, f->nbody, ret_label);

  emit_line("\tmov\tw0, #0");
  emit_s(ret_label); emit_line(":");
  if (lay_stack_size > 0) {
    if (lay_stack_size <= 4095) {
      emit_s("\tadd\tsp, sp, #");
      emit_num(lay_stack_size);
      emit_ch('\n');
    } else {
      emit_mov_imm("x9", lay_stack_size);
      emit_line("\tadd\tsp, sp, x9");
    }
  }
  if (cg_cur_func_ret_is_float) {
    emit_line("\tfmov\td0, x0");
  }
  emit_line("\tldp\tx29, x30, [sp], #16");
  emit_line("\tret");
  return 0;
}

int register_builtin_variadic(int *name, int np) {
  int vj;
  vj = 0;
  while (vj < nvar_funcs) {
    if (my_strcmp(var_funcs[vj], name) == 0) {
      return 0;
    }
    vj++;
  }
  var_funcs[nvar_funcs] = name;
  var_nparams[nvar_funcs] = np;
  nvar_funcs++;
  return 0;
}

int cg_register_functions(struct Program *prog) {
  struct FuncDef *fd = 0;
  // Register ptr-returning functions from prototypes
  int pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_ret_is_ptr[pi] != 0 || prog->proto_ret_stype[pi] != 0) {
      ptr_ret_names[n_ptr_ret] = prog->proto_names[pi];
      n_ptr_ret++;
    }
    pi++;
  }
  // Register ptr-returning functions from definitions
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->ret_is_ptr != 0 || fd->ret_stype != 0) {
      ptr_ret_names[n_ptr_ret] = fd->name;
      n_ptr_ret++;
    }
    pi++;
  }

  // Register unsigned-returning functions from prototypes
  pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_ret_is_unsigned[pi] != 0) {
      unsigned_ret_names[n_unsigned_ret] = prog->proto_names[pi];
      n_unsigned_ret++;
    }
    pi++;
  }
  // Register unsigned-returning functions from definitions
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->ret_is_unsigned != 0) {
      unsigned_ret_names[n_unsigned_ret] = fd->name;
      n_unsigned_ret++;
    }
    pi++;
  }

  // Register long-returning functions (add to ptr_ret_names since both skip sxtw)
  pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_ret_is_long[pi] != 0) {
      ptr_ret_names[n_ptr_ret] = prog->proto_names[pi];
      n_ptr_ret++;
    }
    pi++;
  }
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->ret_is_long != 0) {
      ptr_ret_names[n_ptr_ret] = fd->name;
      n_ptr_ret++;
    }
    pi++;
  }

  // Register struct-returning functions from prototypes (keep parse-time entries)
  pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_ret_stype[pi] != 0) {
      struct_ret_names[n_struct_ret] = prog->proto_names[pi];
      struct_ret_stypes[n_struct_ret] = prog->proto_ret_stype[pi];
      n_struct_ret++;
    }
    pi++;
  }
  // Register struct-returning functions from definitions
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->ret_stype != 0) {
      struct_ret_names[n_struct_ret] = fd->name;
      struct_ret_stypes[n_struct_ret] = fd->ret_stype;
      n_struct_ret++;
    }
    pi++;
  }

  // Register float-returning functions from prototypes and definitions
  n_float_ret = 0;
  pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_ret_is_float[pi] != 0) {
      float_ret_names[n_float_ret] = prog->proto_names[pi];
      n_float_ret++;
    }
    pi++;
  }
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->ret_is_float != 0) {
      float_ret_names[n_float_ret] = fd->name;
      n_float_ret++;
    }
    pi++;
  }

  // Register variadic functions
  nvar_funcs = 0;
  pi = 0;
  while (pi < prog->nprotos) {
    if (prog->proto_is_variadic[pi] != 0) {
      var_funcs[nvar_funcs] = prog->proto_names[pi];
      var_nparams[nvar_funcs] = prog->proto_nparams[pi];
      nvar_funcs++;
    }
    pi++;
  }
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    if (fd->is_variadic != 0) {
      var_funcs[nvar_funcs] = fd->name;
      var_nparams[nvar_funcs] = fd->nparams;
      nvar_funcs++;
    }
    pi++;
  }

  // Register well-known variadic functions if not already declared
  register_builtin_variadic("printf", 1);
  register_builtin_variadic("fprintf", 2);
  register_builtin_variadic("sprintf", 2);
  register_builtin_variadic("snprintf", 3);
  register_builtin_variadic("scanf", 1);
  register_builtin_variadic("fscanf", 2);
  register_builtin_variadic("sscanf", 2);

  // Register all known function names (for function pointer support)
  nknown_funcs = 0;
  pi = 0;
  while (pi < prog->nprotos) {
    known_funcs[nknown_funcs] = prog->proto_names[pi];
    nknown_funcs++;
    pi++;
  }
  ndefined_funcs = 0;
  pi = 0;
  while (pi < prog->nfuncs) {
    fd = prog->funcs[pi];
    known_funcs[nknown_funcs] = fd->name;
    nknown_funcs++;
    defined_funcs[ndefined_funcs] = fd->name;
    ndefined_funcs++;
    pi++;
  }
  return 0;
}

int cg_register_globals(struct Program *prog) {
  struct GDecl *gd = 0;
  // Register global variables
  ncg_g = 0;
  for (int gi = 0; gi < prog->nglobals; gi++) {
    gd = prog->globals[gi];
    cgg[ncg_g].name = gd->name;
    cgg[ncg_g].is_array = 0;
    if (gd->array_size >= 0) { cgg[ncg_g].is_array = 1; }
    cgg[ncg_g].is_char = (gd->is_char && gd->is_ptr == 1 && gd->array_size < 0) ? 1 : 0;
    cgg[ncg_g].is_char_arr = (gd->is_char && gd->is_ptr == 1 && gd->array_size >= 0) ? 1 : 0;
    cgg[ncg_g].stype = (gd->is_ptr == 0) ? gd->stype : 0;
    cgg[ncg_g].ptr_stype = 0;
    if (gd->is_ptr == 1) { if (gd->array_size < 0) { cgg[ncg_g].ptr_stype = gd->stype; } }
    cgg[ncg_g].is_barechar = (gd->is_char && gd->is_ptr == 0 && gd->array_size < 0) ? (gd->is_unsigned ? 2 : 1) : 0;
    cgg[ncg_g].is_intptr = (gd->is_ptr > 0 && gd->stype == 0 && (gd->is_char == 0 || gd->is_ptr >= 2) && gd->array_size < 0) ? 1 : 0;
    cgg[ncg_g].is_bare_char_arr = 0;
    if (gd->is_char && gd->is_ptr == 0 && gd->array_size >= 0) {
      cgg[ncg_g].is_bare_char_arr = 1;
    }
    {
      int gesz = 8;
      if (gd->is_char && gd->is_ptr == 0) { gesz = 1; }
      else if (gd->stype != 0 && gd->is_ptr == 0) { gesz = 8; }
      else if (gd->is_short && gd->is_ptr == 0) { gesz = 2; }
      else if (gd->is_char == 0 && gd->is_ptr == 0 && gd->stype == 0 && gd->is_long == 0 && gd->is_short == 0) { gesz = 4; }
      if (gd->is_ptr > 0) { gesz = 8; }
      cgg[ncg_g].esz = gesz;
    }
    {
      int pesz = 0;
      if (gd->is_ptr > 0) {
        if (gd->is_ptr >= 2) { pesz = 8; }
        else if (gd->is_char) { pesz = 1; }
        else if (gd->is_short) { pesz = 2; }
        else if (gd->is_long) { pesz = 8; }
        else if (gd->stype != 0) { pesz = 0; }
        else { pesz = 4; }
      }
      cgg[ncg_g].ptr_esz = pesz;
    }
    {
      int vbsz = 4;
      if (gd->is_char && gd->is_ptr == 0 && gd->array_size < 0) { vbsz = 1; }
      else if (gd->is_short && gd->is_ptr == 0 && gd->array_size < 0) { vbsz = 2; }
      else if (gd->is_long || gd->is_ptr > 0 || gd->stype != 0 || gd->array_size >= 0) { vbsz = 8; }
      cgg_var_bsz[ncg_g] = vbsz;
    }
    cgg_is_unsigned[ncg_g] = gd->is_unsigned;
    ncg_g++;
  }
  return 0;
}

int cg_find_struct_index(int *sname) {
  if (sname == 0) return -1;
  int i = 0;
  while (i < ncg_s) {
    if (cg_sname[i] != 0 && my_strcmp(cg_sname[i], sname) == 0) return i;
    i++;
  }
  return -1;
}

int cg_align_up(int val, int align) {
  return (val + align - 1) / align * align;
}

int cg_compute_struct_layout(int si) {
  int nf = cg_snfields[si];
  int *fbyteoff = my_malloc(nf * 8);
  int *fbytesize = my_malloc(nf * 8);
  int offset = 0;
  int max_align = 1;
  int is_union = cg_s_is_union[si];
  int max_size = 0;

  // Bitfield structs: use nwords * 4 bytes
  if (cg_s_nw[si] > 0) {
    int nw = cg_s_nw[si];
    int j = 0;
    while (j < nf) {
      int wi = (cg_s_wi[si] != 0) ? cg_s_wi[si][j] : 0;
      fbyteoff[j] = wi * 4;
      fbytesize[j] = 4;
      j++;
    }
    cg_s_fbyteoff[si] = fbyteoff;
    cg_s_fbytesize[si] = fbytesize;
    cg_s_bytesize[si] = nw * 4;
    return 0;
  }

  int j = 0;
  while (j < nf) {
    int fsz = 4;  // default: int = 4 bytes
    int falign = 4;
    int f_is_ptr = (cg_s_fp[si] != 0 && cg_s_fp[si][j]) ? 1 : 0;
    int f_is_char = (cg_s_fc[si] != 0 && cg_s_fc[si][j]) ? 1 : 0;
    int f_is_char_type = (cg_s_fct[si] != 0 && cg_s_fct[si][j]) ? 1 : 0;
    int f_is_arr = (cg_s_fa[si] != 0) ? cg_s_fa[si][j] : 0;
    int f_is_short = (cg_s_fsh[si] != 0) ? cg_s_fsh[si][j] : 0;
    int f_is_long = (cg_s_fl[si] != 0) ? cg_s_fl[si][j] : 0;
    int *f_stype = cg_sfield_types[si][j];

    if (f_is_ptr > 0) {
      // Any pointer type: 8 bytes
      fsz = 8; falign = 8;
    } else if (f_stype != 0) {
      // Embedded struct/union
      int inner = cg_find_struct_index(f_stype);
      if (inner < 0) {
        // Try typedef resolution
        int *resolved = find_typedef(f_stype);
        if (resolved != 0) { inner = cg_find_struct_index(resolved); }
      }
      if (inner >= 0 && cg_s_fbyteoff[inner] != 0) {
        fsz = cg_s_bytesize[inner];
        // Use stored max alignment of inner struct (not byte size!)
        falign = cg_s_max_align[inner];
        if (falign < 1) { falign = 1; }
      } else {
        fsz = 8; falign = 8;  // fallback
      }
    } else if (f_is_char_type || f_is_char) {
      // char type field (plain char, char*, char[])
      fsz = 1; falign = 1;
    } else if (f_is_short) {
      fsz = 2; falign = 2;
    } else if (f_is_long) {
      fsz = 8; falign = 8;
    } else {
      // Default: int = 4 bytes
      fsz = 4; falign = 4;
    }

    // Handle arrays
    if (f_is_arr > 0) {
      if (f_is_char && f_is_ptr == 0) {
        // char arr[N]: N bytes, align 1
        fsz = f_is_arr;
        falign = 1;
      } else {
        fsz = fsz * f_is_arr;
      }
    }

    // Align offset
    if (is_union == 0) {
      offset = cg_align_up(offset, falign);
    }
    fbyteoff[j] = is_union ? 0 : offset;
    fbytesize[j] = fsz;

    if (falign > max_align) { max_align = falign; }
    if (is_union) {
      if (fsz > max_size) { max_size = fsz; }
    } else {
      offset = offset + fsz;
    }
    j++;
  }

  int total;
  if (is_union) {
    total = cg_align_up(max_size, max_align);
  } else {
    total = cg_align_up(offset, max_align);
  }
  if (total == 0) { total = max_align; }

  cg_s_fbyteoff[si] = fbyteoff;
  cg_s_fbytesize[si] = fbytesize;
  cg_s_bytesize[si] = total;
  cg_s_max_align[si] = max_align;
  return 0;
}

// Build flat slot layout: for each flattened slot index, compute byte offset and byte size
// Returns number of slots filled
int cg_build_slot_layout(int *sname, int *slot_off, int *slot_sz, int max_slots) {
  sname = cg_resolve_sname(sname);
  int si = cg_find_struct_index(sname);
  if (si < 0 || cg_s_fbyteoff[si] == 0) return 0;

  // Union: 1 slot at offset 0
  if (cg_s_is_union[si]) {
    if (max_slots > 0) { slot_off[0] = 0; slot_sz[0] = cg_s_bytesize[si]; }
    return 1;
  }

  int slot = 0;
  int j = 0;
  while (j < cg_snfields[si]) {
    int f_off = cg_s_fbyteoff[si][j];
    int f_sz = cg_s_fbytesize[si][j];
    int f_is_ptr = (cg_s_fp[si] != 0) ? cg_s_fp[si][j] : 0;
    int f_is_arr = (cg_s_fa[si] != 0) ? cg_s_fa[si][j] : 0;
    int f_is_char = (cg_s_fc[si] != 0) ? cg_s_fc[si][j] : 0;
    int *f_stype = cg_sfield_types[si][j];

    if (f_stype != 0 && f_is_ptr == 0 && f_is_arr == 0) {
      // Embedded struct: recurse into sub-fields
      int sub_nf = cg_struct_nfields(f_stype);
      int *sub_off = my_malloc(sub_nf * 8);
      int *sub_sz = my_malloc(sub_nf * 8);
      int sub_n = cg_build_slot_layout(f_stype, sub_off, sub_sz, sub_nf);
      int si2 = 0;
      while (si2 < sub_n && slot < max_slots) {
        slot_off[slot] = f_off + sub_off[si2];
        slot_sz[slot] = sub_sz[si2];
        slot++;
        si2++;
      }
    } else if (f_is_arr > 0 && f_is_char && f_is_ptr == 0) {
      // Char array: ceil(arr_size / 8) packed slots
      int ca_nslots = (f_is_arr + 7) / 8;
      int csi = 0;
      while (csi < ca_nslots && slot < max_slots) {
        slot_off[slot] = f_off + csi * 8;
        slot_sz[slot] = 8;
        slot++;
        csi++;
      }
    } else if (f_is_arr > 0 && f_stype != 0 && f_is_ptr == 0) {
      // Array of structs
      int sub_nf = cg_struct_nfields(f_stype);
      int elem_bsz = cg_struct_byte_size(f_stype);
      int ai = 0;
      while (ai < f_is_arr) {
        int *sub_off = my_malloc(sub_nf * 8);
        int *sub_sz = my_malloc(sub_nf * 8);
        int sub_n = cg_build_slot_layout(f_stype, sub_off, sub_sz, sub_nf);
        int si2 = 0;
        while (si2 < sub_n && slot < max_slots) {
          slot_off[slot] = f_off + ai * elem_bsz + sub_off[si2];
          slot_sz[slot] = sub_sz[si2];
          slot++;
          si2++;
        }
        ai++;
      }
    } else if (f_is_arr > 0) {
      // Array of scalars
      int elem_sz = f_sz / f_is_arr;
      if (elem_sz < 1) { elem_sz = 1; }
      int ai = 0;
      while (ai < f_is_arr && slot < max_slots) {
        slot_off[slot] = f_off + ai * elem_sz;
        slot_sz[slot] = elem_sz;
        slot++;
        ai++;
      }
    } else {
      // Simple scalar field
      if (slot < max_slots) {
        slot_off[slot] = f_off;
        slot_sz[slot] = f_sz;
        slot++;
      }
    }
    j++;
  }
  return slot;
}

int cg_register_structs(struct Program *prog) {
#ifndef __STDC__
  struct SDef *sd = 0;
#endif
  // Register struct/union definitions
  int i = 0;
  struct SDef *sd = 0;
  while (i < prog->nstructs) {
    sd = prog->structs[i];
    cg_sname[ncg_s] = sd->name;
    cg_sfields[ncg_s] = sd->fields;
    cg_sfield_types[ncg_s] = sd->field_types;
    cg_snfields[ncg_s] = sd->nfields;
    cg_s_is_union[ncg_s] = sd->is_union;
    cg_s_bw[ncg_s] = sd->bit_widths;
    cg_s_bo[ncg_s] = sd->bit_offsets;
    cg_s_wi[ncg_s] = sd->word_indices;
    cg_s_nw[ncg_s] = sd->nwords;
    cg_s_fa[ncg_s] = sd->field_is_array;
    cg_s_fc[ncg_s] = sd->field_is_char;
    cg_s_fp[ncg_s] = sd->field_is_ptr;
    cg_s_fsh[ncg_s] = sd->field_is_short;
    cg_s_fl[ncg_s] = sd->field_is_long;
    cg_s_fct[ncg_s] = sd->field_is_char_type;
    cg_s_fu[ncg_s] = sd->field_is_unsigned;
    ncg_s++;
    i++;
  }
  // Register inline anonymous structs
  i = 0;
  while (i < ninline_sdefs) {
    sd = inline_sdefs[i];
    cg_sname[ncg_s] = sd->name;
    cg_sfields[ncg_s] = sd->fields;
    cg_sfield_types[ncg_s] = sd->field_types;
    cg_snfields[ncg_s] = sd->nfields;
    cg_s_is_union[ncg_s] = sd->is_union;
    cg_s_bw[ncg_s] = sd->bit_widths;
    cg_s_bo[ncg_s] = sd->bit_offsets;
    cg_s_wi[ncg_s] = sd->word_indices;
    cg_s_nw[ncg_s] = sd->nwords;
    cg_s_fa[ncg_s] = sd->field_is_array;
    cg_s_fc[ncg_s] = sd->field_is_char;
    cg_s_fp[ncg_s] = sd->field_is_ptr;
    cg_s_fsh[ncg_s] = sd->field_is_short;
    cg_s_fl[ncg_s] = sd->field_is_long;
    cg_s_fct[ncg_s] = sd->field_is_char_type;
    cg_s_fu[ncg_s] = sd->field_is_unsigned;
    ncg_s++;
    i++;
  }
  // Compute proper struct layouts
  { int li = 0; while (li < ncg_s) { cg_compute_struct_layout(li); li++; } }
  return 0;
}

// Try to evaluate an AST expression to a compile-time constant.
// Returns 1 if successful, 0 if not. Result stored in *out.
int try_eval_const(struct Expr *e, int *out) {
  if (e == 0) return 0;
  if (e->kind == ND_NUM) { *out = e->ival; return 1; }
  if (e->kind == ND_CAST && e->left != 0) { return try_eval_const(e->left, out); }
  if (e->kind == ND_UNARY && e->ival == '-') {
    int v = 0;
    if (try_eval_const(e->left, &v)) { *out = 0 - v; return 1; }
    return 0;
  }
  if (e->kind == ND_UNARY && e->ival == '~') {
    int v = 0;
    if (try_eval_const(e->left, &v)) { *out = ~v; return 1; }
    return 0;
  }
  if (e->kind == ND_BINARY) {
    int lv = 0; int rv = 0;
    int *op = e->sval2;
    if (op == 0) return 0;
    if (try_eval_const(e->left, &lv) == 0) return 0;
    if (try_eval_const(e->right, &rv) == 0) return 0;
    if (my_strcmp(op, "+") == 0) { *out = lv + rv; return 1; }
    if (my_strcmp(op, "-") == 0) { *out = lv - rv; return 1; }
    if (my_strcmp(op, "*") == 0) { *out = lv * rv; return 1; }
    if (my_strcmp(op, "/") == 0 && rv != 0) { *out = lv / rv; return 1; }
    if (my_strcmp(op, "%") == 0 && rv != 0) { *out = lv % rv; return 1; }
    if (my_strcmp(op, "&") == 0) { *out = lv & rv; return 1; }
    if (my_strcmp(op, "|") == 0) { *out = lv | rv; return 1; }
    if (my_strcmp(op, "^") == 0) { *out = lv ^ rv; return 1; }
    if (my_strcmp(op, "<<") == 0) { *out = lv << rv; return 1; }
    if (my_strcmp(op, ">>") == 0) { *out = lv >> rv; return 1; }
    return 0;
  }
  return 0;
}

int cg_emit_globals(struct Program *prog) {
  int ch = 0;
  int i = 0;
  int k = 0;
#ifdef __STDC__
  int fsi = 0;
#endif
  struct GDecl *gd = 0;
  // Emit global variables
  if (prog->nglobals > 0) {
    int has_data = 0;
    i = 0;
    while (i < prog->nglobals) {
      gd = prog->globals[i];
      if (gd == 0 || gd < 4096) { i++; continue; }
      if (gd->array_size >= 0 && gd->init_list != 0 && gd->init_list->kind == ND_INITLIST) {
        // Initialized array: emit .data with .quad per element
        // Build a flat array of Expr* slots to handle designated initializers
        int nf_per_elem = 1;
        if (gd->stype != 0 && gd->is_ptr == 0) { nf_per_elem = cg_struct_nfields(gd->stype); }
        int total_slots = gd->array_size * nf_per_elem;
        // Build char-array-slot map for struct arrays (before flattening)
        int *ca_slot_map = 0;
        int *ca_slot_byte_off = 0;
        if (gd->stype != 0 && gd->is_ptr == 0 && nf_per_elem > 0) {
          ca_slot_map = my_malloc(nf_per_elem * 8);
          ca_slot_byte_off = my_malloc(nf_per_elem * 8);
          int csm = 0;
          while (csm < nf_per_elem) { ca_slot_map[csm] = 0; ca_slot_byte_off[csm] = 0; csm++; }
          int *resolved_s = cg_resolve_sname(gd->stype);
          int sci = 0;
          while (sci < ncg_s) {
            if (cg_sname[sci] != 0 && my_strcmp(cg_sname[sci], resolved_s) == 0) {
              int slot_pos = 0;
              int fj = 0;
              while (fj < cg_snfields[sci]) {
                int f_slots = 1;
                if (cg_sfield_types[sci][fj] != 0) {
                  f_slots = cg_struct_nfields(cg_sfield_types[sci][fj]);
                }
                if (cg_s_fa[sci] != 0 && cg_s_fa[sci][fj] > 0) {
                  if (cg_s_fc[sci] != 0 && cg_s_fc[sci][fj]) {
                    int ca_nslots = (cg_s_fa[sci][fj] + 7) / 8;
                    int csi = 0;
                    while (csi < ca_nslots && (slot_pos + csi) < nf_per_elem) {
                      ca_slot_map[slot_pos + csi] = cg_s_fa[sci][fj];
                      ca_slot_byte_off[slot_pos + csi] = csi * 8;
                      csi++;
                    }
                    f_slots = ca_nslots;
                  } else {
                    f_slots = f_slots * cg_s_fa[sci][fj];
                  }
                }
                slot_pos += f_slots;
                fj++;
              }
              break;
            }
            sci++;
          }
        }
        struct Expr **flat = my_malloc(total_slots * 8);
        int fsi = 0;
        while (fsi < total_slots) { flat[fsi] = 0; fsi++; }
        int **g_di = gd->init_list->desig;
        int g_pos_idx = 0;
        k = 0;
        while (k < gd->init_list->nargs) {
          int g_target = g_pos_idx;
          if (g_di != 0 && g_di[k] >= 0) { g_target = g_di[k]; }
          struct Expr *elem = gd->init_list->args[k];
          if (elem->kind == ND_INITLIST) {
            int si = 0;
            int flat_base = g_target * nf_per_elem;
            int flat_off = 0;
            while (si < elem->nargs && flat_base + flat_off < total_slots) {
              flat[flat_base + flat_off] = elem->args[si];
              // If this slot starts a multi-slot char array, fill remaining slots with same string
              if (ca_slot_map != 0 && ca_slot_map[flat_off] > 0) {
                int ca_nsl = (ca_slot_map[flat_off] + 7) / 8;
                int csi2 = 1;
                while (csi2 < ca_nsl && flat_base + flat_off + csi2 < total_slots) {
                  flat[flat_base + flat_off + csi2] = elem->args[si];
                  csi2++;
                }
                flat_off += ca_nsl;
              } else {
                flat_off++;
              }
              si++;
            }
            g_pos_idx = g_target + 1;
          } else if (elem->kind == ND_STRLIT && gd->is_char && gd->is_ptr == 0) {
            // char array initialized with string: expand bytes into slots
            int *decoded = cg_decode_string(elem->sval);
            int slen = my_strlen(decoded) + 1;
            int sc = 0;
            int flat_base = g_target * nf_per_elem;
            while (sc < slen && flat_base + sc < total_slots) {
              struct Expr *byte_e = my_malloc(80);
              byte_e->kind = ND_NUM;
              byte_e->ival = __read_byte(decoded, sc);
              flat[flat_base + sc] = byte_e;
              sc++;
            }
            g_pos_idx = g_target + 1;
          } else {
            int flat_idx = g_target * nf_per_elem;
            if (flat_idx < total_slots) { flat[flat_idx] = elem; }
            g_pos_idx = g_target + 1;
          }
          k++;
        }
        if (has_data == 0) { emit_ch('\n'); emit_line("\t.data"); has_data = 1; }
        if (gd->is_static == 0) { emit_s("\t.globl\t_"); emit_line(gd->name); }
        int gd_is_char_arr = (gd->is_char && gd->is_ptr == 0);
        int gd_esz = 8;
        if (gd_is_char_arr) { gd_esz = 1; }
        else if (gd->stype != 0 && gd->is_ptr == 0) { gd_esz = 8; }
        else if (gd->is_short && gd->is_ptr == 0) { gd_esz = 2; }
        else if (gd->is_char == 0 && gd->is_ptr == 0 && gd->stype == 0 && gd->is_long == 0 && gd->is_short == 0) { gd_esz = 4; }
        if (gd->is_ptr > 0) { gd_esz = 8; }
        int *gd_dir = "\t.quad\t";
        if (gd_esz == 1) { gd_dir = "\t.byte\t"; }
        else if (gd_esz == 4) { gd_dir = "\t.long\t"; }
        else if (gd_esz == 2) { gd_dir = "\t.short\t"; }
        if (gd_esz == 1) { emit_line("\t.p2align\t0"); }
        else if (gd_esz == 2) { emit_line("\t.p2align\t1"); }
        else if (gd_esz == 4) { emit_line("\t.p2align\t2"); }
        else { emit_line("\t.p2align\t3"); }
        emit_s("_"); emit_s(gd->name); emit_line(":");
        fsi = 0;
        while (fsi < total_slots) {
          struct Expr *fe = flat[fsi];
          if (fe == 0) {
            emit_s(gd_dir); emit_line("0");
          } else if (fe->kind == ND_NUM) {
            emit_s(gd_dir); emit_num(fe->ival); emit_ch('\n');
          } else if (fe->kind == ND_UNARY && fe->ival == '-' && fe->left->kind == ND_NUM) {
            emit_s(gd_dir); emit_ch('-'); emit_num(fe->left->ival); emit_ch('\n');
          } else if (fe->kind == ND_STRLIT) {
            // Check if this slot is a char array field - pack bytes inline
            if (ca_slot_map != 0 && ca_slot_map[fsi % nf_per_elem] > 0) {
              int *decoded = cg_decode_string(fe->sval);
              int plen = my_strlen(decoded);
              int byte_start = 0;
              if (ca_slot_byte_off != 0) { byte_start = ca_slot_byte_off[fsi % nf_per_elem]; }
              int packed_lo = 0;
              int packed_hi = 0;
              int pi = 0;
              while (pi < 4 && (byte_start + pi) < plen) {
                int byte_val = __read_byte(decoded, byte_start + pi);
                packed_lo = packed_lo | (byte_val << (pi * 8));
                pi++;
              }
              while (pi < 8 && (byte_start + pi) < plen) {
                int byte_val = __read_byte(decoded, byte_start + pi);
                packed_hi = packed_hi | (byte_val << ((pi - 4) * 8));
                pi++;
              }
              // Emit as hex: high 32 bits then low 32 bits
              emit_s("\t.quad\t0x");
              int hi = 7;
              while (hi >= 0) {
                int nibble = (packed_hi >> (hi * 4)) & 0xF;
                if (nibble < 10) { emit_ch('0' + nibble); }
                else { emit_ch('a' + nibble - 10); }
                hi = hi - 1;
              }
              hi = 7;
              while (hi >= 0) {
                int nibble = (packed_lo >> (hi * 4)) & 0xF;
                if (nibble < 10) { emit_ch('0' + nibble); }
                else { emit_ch('a' + nibble - 10); }
                hi = hi - 1;
              }
              emit_ch('\n');
            } else {
              int *slabel = cg_intern_string(fe->sval);
              emit_s("\t.quad\t"); emit_line(slabel);
            }
          } else if (fe->kind == ND_VAR) {
            emit_s("\t.quad\t_"); emit_line(fe->sval);
          } else if (fe->kind == ND_UNARY && fe->ival == '&' && fe->left != 0 && fe->left->kind == ND_VAR) {
            emit_s("\t.quad\t_"); emit_line(fe->left->sval);
          } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_NUM) {
            emit_s(gd_dir); emit_num(fe->left->ival); emit_ch('\n');
          } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_VAR) {
            emit_s("\t.quad\t_"); emit_line(fe->left->sval);
          } else {
            int cval = 0;
            if (try_eval_const(fe, &cval)) {
              emit_s(gd_dir); emit_num(cval); emit_ch('\n');
            } else {
              emit_s(gd_dir); emit_line("0");
            }
          }
          fsi++;
        }
      } else if (gd->array_size >= 0 && gd->init_str != 0) {
        // String-initialized array
        int *decoded = cg_decode_string(gd->init_str);
        int slen = my_strlen(decoded) + 1;
        if (has_data == 0) { emit_ch('\n'); emit_line("\t.data"); has_data = 1; }
        if (gd->is_static == 0) { emit_s("\t.globl\t_"); emit_line(gd->name); }
        if (gd->is_char && gd->is_ptr == 0) {
          // Bare char array: emit .byte per character
          emit_line("\t.p2align\t0");
          emit_s("_"); emit_s(gd->name); emit_line(":");
          k = 0;
          while (k < slen && k < gd->array_size) {
            ch = __read_byte(decoded, k);
            emit_s("\t.byte\t"); emit_num(ch); emit_ch('\n');
            k++;
          }
          // Zero-pad remaining bytes if array_size > slen
          while (k < gd->array_size) {
            emit_line("\t.byte\t0");
            k++;
          }
        } else {
          // Non-char array: emit element-sized directives per character
          int nc_esz = 8;
          if (gd->is_short && gd->is_ptr == 0) { nc_esz = 2; }
          else if (gd->is_char == 0 && gd->is_ptr == 0 && gd->stype == 0 && gd->is_long == 0) { nc_esz = 4; }
          if (nc_esz == 4) { emit_line("\t.p2align\t2"); }
          else if (nc_esz == 2) { emit_line("\t.p2align\t1"); }
          else { emit_line("\t.p2align\t3"); }
          emit_s("_"); emit_s(gd->name); emit_line(":");
          k = 0;
          while (k < slen && k < gd->array_size) {
            ch = __read_byte(decoded, k);
            if (nc_esz == 4) { emit_s("\t.long\t"); }
            else if (nc_esz == 2) { emit_s("\t.short\t"); }
            else { emit_s("\t.quad\t"); }
            emit_num(ch); emit_ch('\n');
            k++;
          }
        }
      } else if (gd->array_size >= 0) {
        // Uninitialized array: use .comm (or .zerofill for static)
        int elem_sz = 8;
        if (gd->is_char && gd->is_ptr == 0) {
          elem_sz = 1;
        } else if (gd->stype != 0 && gd->is_ptr == 0) {
          elem_sz = cg_struct_byte_size(gd->stype);
        } else if (gd->is_short && gd->is_ptr == 0) {
          elem_sz = 2;
        } else if (gd->is_char == 0 && gd->is_ptr == 0 && gd->stype == 0 && gd->is_long == 0) {
          elem_sz = 4;
        }
        if (gd->is_ptr > 0) { elem_sz = 8; }
        int sz = gd->array_size * elem_sz;
        if (sz == 0 && gd->stype != 0) { sz = elem_sz; }
        if (gd->is_static) {
          emit_s("\t.zerofill __DATA,__bss,_");
          emit_s(gd->name);
          emit_s(","); emit_num(sz); emit_line(",3");
        } else {
          emit_s("\t.comm\t_");
          emit_s(gd->name);
          emit_s(", ");
          emit_num(sz);
          emit_line(", 3");
        }
      } else if (gd->init_list != 0 && gd->init_list->kind == ND_INITLIST) {
        // Struct (non-array) with init list: struct S obj = {10, 20};
        if (gd->stype != 0) { printf("cc: struct init '%s' stype='%s' nargs=%d\n", gd->name, gd->stype, gd->init_list->nargs); }
        int nf_total = 0;
        if (gd->stype != 0) { nf_total = cg_struct_nfields(gd->stype); }
        if (nf_total < gd->init_list->nargs) { nf_total = gd->init_list->nargs; }
        struct Expr **sflat = my_malloc(nf_total * 8);
        fsi = 0;
        while (fsi < nf_total) { sflat[fsi] = 0; fsi++; }
        int **gs_di = gd->init_list->desig;
        int gs_pos = 0;
        k = 0;
        while (k < gd->init_list->nargs) {
          int gs_target = gs_pos;
          if (gs_di != 0 && gs_di[k] >= 0) { gs_target = gs_di[k]; }
          if (gs_target < nf_total) { sflat[gs_target] = gd->init_list->args[k]; }
          gs_pos = gs_target + 1;
          k++;
        }
        if (has_data == 0) { emit_ch('\n'); emit_line("\t.data"); has_data = 1; }
        if (gd->is_static == 0) { emit_s("\t.globl\t_"); emit_line(gd->name); }
        emit_line("\t.p2align\t3");
        emit_s("_"); emit_s(gd->name); emit_line(":");
        if (gd->stype != 0) {
          // Proper layout: emit each slot at its correct byte offset with correct size
          int *sl_off = my_malloc(nf_total * 8);
          int *sl_sz = my_malloc(nf_total * 8);
          int sl_n = cg_build_slot_layout(gd->stype, sl_off, sl_sz, nf_total);
          if (my_strcmp(gd->name, "sqlite3Config") == 0) {
            printf("cc: slot_layout for '%s': sl_n=%d nf_total=%d\n", gd->name, sl_n, nf_total);
            int di = 0;
            while (di < sl_n && di < 15) { printf("  slot[%d]: off=%d sz=%d\n", di, sl_off[di], sl_sz[di]); di++; }
          }
          int cur_off = 0;
          fsi = 0;
          while (fsi < nf_total) {
            int f_off = (fsi < sl_n) ? sl_off[fsi] : cur_off;
            int f_sz = (fsi < sl_n) ? sl_sz[fsi] : 8;
            // Emit padding
            if (f_off > cur_off) {
              emit_s("\t.zero\t"); emit_num(f_off - cur_off); emit_ch('\n');
              cur_off = f_off;
            }
            // Choose directive
            int *dir = "\t.quad\t";
            if (f_sz == 1) { dir = "\t.byte\t"; }
            else if (f_sz == 2) { dir = "\t.short\t"; }
            else if (f_sz == 4) { dir = "\t.long\t"; }
            struct Expr *fe = sflat[fsi];
            if (fe == 0) {
              emit_s(dir); emit_line("0");
            } else if (fe->kind == ND_NUM) {
              emit_s(dir); emit_num(fe->ival); emit_ch('\n');
            } else if (fe->kind == ND_UNARY && fe->ival == '-' && fe->left->kind == ND_NUM) {
              emit_s(dir); emit_ch('-'); emit_num(fe->left->ival); emit_ch('\n');
            } else if (fe->kind == ND_STRLIT) {
              int *slabel = cg_intern_string(fe->sval);
              emit_s("\t.quad\t"); emit_line(slabel);
            } else if (fe->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->sval);
            } else if (fe->kind == ND_UNARY && fe->ival == '&' && fe->left != 0 && fe->left->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->left->sval);
            } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_NUM) {
              emit_s(dir); emit_num(fe->left->ival); emit_ch('\n');
            } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->left->sval);
            } else {
              int cval = 0;
              if (try_eval_const(fe, &cval)) {
                emit_s(dir); emit_num(cval); emit_ch('\n');
              } else {
                emit_s(dir); emit_line("0");
              }
            }
            cur_off = cur_off + f_sz;
            fsi++;
          }
          // Trailing padding
          int total_bsz = cg_struct_byte_size(gd->stype);
          if (cur_off < total_bsz) {
            emit_s("\t.zero\t"); emit_num(total_bsz - cur_off); emit_ch('\n');
          }
        } else {
          // Legacy: .quad per slot
          fsi = 0;
          while (fsi < nf_total) {
            struct Expr *fe = sflat[fsi];
            if (fe == 0) {
              emit_line("\t.quad\t0");
            } else if (fe->kind == ND_NUM) {
              emit_s("\t.quad\t"); emit_num(fe->ival); emit_ch('\n');
            } else if (fe->kind == ND_UNARY && fe->ival == '-' && fe->left->kind == ND_NUM) {
              emit_s("\t.quad\t-"); emit_num(fe->left->ival); emit_ch('\n');
            } else if (fe->kind == ND_STRLIT) {
              int *slabel = cg_intern_string(fe->sval);
              emit_s("\t.quad\t"); emit_line(slabel);
            } else if (fe->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->sval);
            } else if (fe->kind == ND_UNARY && fe->ival == '&' && fe->left != 0 && fe->left->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->left->sval);
            } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_NUM) {
              emit_s("\t.quad\t"); emit_num(fe->left->ival); emit_ch('\n');
            } else if (fe->kind == ND_CAST && fe->left != 0 && fe->left->kind == ND_VAR) {
              emit_s("\t.quad\t_"); emit_line(fe->left->sval);
            } else {
              int cval = 0;
              if (try_eval_const(fe, &cval)) {
                emit_s("\t.quad\t"); emit_num(cval); emit_ch('\n');
              } else {
                emit_line("\t.quad\t0");
              }
            }
            fsi++;
          }
        }
      } else if (gd->has_init != 0 && gd->init_str != 0) {
        // String initialized
        if (has_data == 0) { emit_ch('\n'); emit_line("\t.data"); has_data = 1; }
        if (gd->is_static == 0) { emit_s("\t.globl\t_"); emit_line(gd->name); }
        emit_line("\t.p2align\t3");
        emit_s("_"); emit_s(gd->name); emit_line(":");
        int *slabel = cg_intern_string(cg_decode_string(gd->init_str));
        emit_s("\t.quad\t"); emit_line(slabel);
      } else if (gd->has_init != 0) {
        // Integer initialized
        if (has_data == 0) { emit_ch('\n'); emit_line("\t.data"); has_data = 1; }
        if (gd->is_static == 0) { emit_s("\t.globl\t_"); emit_line(gd->name); }
        emit_line("\t.p2align\t3");
        emit_s("_"); emit_s(gd->name); emit_line(":");
        emit_s("\t.quad\t"); emit_num(gd->init_val); emit_ch('\n');
      } else {
        // Uninitialized (tentative def): skip if an initialized def exists
        int skip_tentative = 0;
        int ti = 0;
        while (ti < prog->nglobals) {
          if (ti != i) {
            struct GDecl *tgd = prog->globals[ti];
            if (tgd != 0 && tgd >= 4096) {
              if (my_strcmp(tgd->name, gd->name) == 0) {
                if (tgd->has_init || tgd->init_list != 0 || tgd->init_str != 0) {
                  skip_tentative = 1;
                }
              }
            }
          }
          ti++;
        }
        if (skip_tentative) { i++; continue; }
        // Uninitialized: use .comm (or .zerofill for static)
        int gsz = 8;
        if (gd->stype != 0 && gd->is_ptr == 0) {
          gsz = cg_struct_byte_size(gd->stype);
        }
        if (gd->is_static) {
          emit_s("\t.zerofill __DATA,__bss,_");
          emit_s(gd->name);
          emit_s(","); emit_num(gsz); emit_line(",3");
        } else {
          emit_s("\t.comm\t_");
          emit_s(gd->name);
          emit_s(", "); emit_num(gsz); emit_line(", 3");
        }
      }
      i++;
    }
  }
  return 0;
}

int cg_emit_strings() {
  int i = 0;
  // String pool (emitted last so globals/static locals can intern strings)
  if (nsp > 0) {
    emit_ch('\n');
    emit_line("\t.section\t__TEXT,__cstring,cstring_literals");
    i = 0;
    while (i < nsp) {
      emit_s(sp_label[i]); emit_line(":");
      emit_s("\t.asciz\t\"");
      cg_emit_escaped_string(sp_decoded[i]);
      emit_line("\"");
      i++;
    }
  }
  return 0;
}

int codegen(struct Program *prog) {
  struct FuncDef *fd = 0;
  struct GDecl *gd = 0;
  int i = 0;
  int k = 0;
  int ch = 0;
  label_id = 0;
  nsp = 0;
  nloop = 0;
  ncg_s = 0;
  n_ptr_ret = 0;
  n_unsigned_ret = 0;
  nsl = 0;

  cg_register_functions(prog);
  cg_register_globals(prog);
  cg_register_structs(prog);

  emit_line("\t.text");

  i = 0;
  while (i < prog->nfuncs) {
    gen_func(prog->funcs[i]);
    i++;
  }

  cg_emit_globals(prog);

  // Emit static local variables
  if (nsl > 0) {
    emit_ch('\n');
    emit_line("\t.data");
    i = 0;
    while (i < nsl) {
      emit_line("\t.p2align\t3");
      emit_s(sl[i].label);
      emit_line(":");
      if (sl[i].has_init == 2 && sl[i].init_list != 0) {
        // Init list for static local array
        int si_j = 0;
        int si_n = sl[i].init_list->nargs;
        int si_arr = sl[i].arr_size;
        if (si_arr < 0) { si_arr = si_n; }
        // Build char-array-slot map for static local struct arrays
        int *sl_ca_map = 0;
        int sl_nfpe = 1;
        if (sl[i].stype != 0) {
          sl_nfpe = cg_struct_nfields(sl[i].stype);
          if (sl_nfpe > 1) {
            sl_ca_map = my_malloc(sl_nfpe * 8);
            int csm = 0;
            while (csm < sl_nfpe) { sl_ca_map[csm] = 0; csm++; }
            int *resolved_s = cg_resolve_sname(sl[i].stype);
            int sci = 0;
            while (sci < ncg_s) {
              if (cg_sname[sci] != 0 && my_strcmp(cg_sname[sci], resolved_s) == 0) {
                int slot_pos = 0;
                int fj = 0;
                while (fj < cg_snfields[sci]) {
                  int f_slots = 1;
                  if (cg_sfield_types[sci][fj] != 0) {
                    f_slots = cg_struct_nfields(cg_sfield_types[sci][fj]);
                  }
                  if (cg_s_fa[sci] != 0 && cg_s_fa[sci][fj] > 0) {
                    if (cg_s_fc[sci] != 0 && cg_s_fc[sci][fj]) {
                      if (slot_pos < sl_nfpe) { sl_ca_map[slot_pos] = cg_s_fa[sci][fj]; }
                      f_slots = 1;
                    } else {
                      f_slots = f_slots * cg_s_fa[sci][fj];
                    }
                  }
                  slot_pos += f_slots;
                  fj++;
                }
                break;
              }
              sci++;
            }
          }
        }
        while (si_j < si_arr) {
          if (si_j < si_n && sl[i].init_list->args[si_j] != 0 && sl[i].init_list->args[si_j]->kind == ND_NUM) {
            emit_s("\t.quad\t"); emit_num(sl[i].init_list->args[si_j]->ival); emit_ch('\n');
          } else if (si_j < si_n && sl[i].init_list->args[si_j] != 0 && sl[i].init_list->args[si_j]->kind == ND_STRLIT) {
            if (sl_ca_map != 0 && sl_ca_map[si_j % sl_nfpe] > 0) {
              // Pack string bytes into .quad hex for char array field
              int *decoded = cg_decode_string(sl[i].init_list->args[si_j]->sval);
              int plen = my_strlen(decoded);
              int packed = 0;
              int pi = 0;
              while (pi < 8 && pi < plen) {
                packed = packed | (__read_byte(decoded, pi) << (pi * 8));
                pi++;
              }
              emit_s("\t.quad\t0x");
              int hi = 15;
              while (hi >= 0) {
                int nibble = (packed >> (hi * 4)) & 0xF;
                if (nibble < 10) { emit_ch('0' + nibble); }
                else { emit_ch('a' + nibble - 10); }
                hi = hi - 1;
              }
              emit_ch('\n');
            } else {
              int *sl_str_label = cg_intern_string(sl[i].init_list->args[si_j]->sval);
              emit_s("\t.quad\t"); emit_s(sl_str_label); emit_ch('\n');
            }
          } else {
            emit_line("\t.quad\t0");
          }
          si_j++;
        }
      } else if (sl[i].has_init == 1) {
        emit_s("\t.quad\t");
        emit_num(sl[i].init_val);
        emit_ch('\n');
      } else {
        emit_line("\t.quad\t0");
      }
      i++;
    }
  }

  cg_emit_strings();

  return 0;
}


// ---- Driver ----

int *cmdline_defs[256];
int ncmdline_defs;
int *sys_include_dir;
int *include_dirs[64];
int ninclude_dirs;
int *cc_out_path;
int *cc_c_path;

#ifdef __STDC__
int *parse_args(int argc, char **argv) {
#else
int *parse_args(int argc, int **argv) {
#endif
  int *out_path = "a.out";
  int *c_path = 0;

  sys_include_dir = 0;

  int i = 1;
  while (i < argc) {
    int *arg = argv[i];
    if (my_strcmp(arg, "-o") == 0) {
      if (i + 1 >= argc) { my_fatal("missing arg for -o"); }
      i++;
      out_path = argv[i];
    } else if (__read_byte(arg, 0) == '-' && __read_byte(arg, 1) == 'D') {
      if (__read_byte(arg, 2) != 0) {
        // Extract substring starting at byte 2
        int dlen = 0;
        while (__read_byte(arg, 2 + dlen) != 0) { dlen++; }
        cmdline_defs[ncmdline_defs] = make_str(arg, 2, dlen);
        ncmdline_defs++;
      } else if (i + 1 < argc) {
        i++;
        cmdline_defs[ncmdline_defs] = argv[i];
        ncmdline_defs++;
      } else {
        my_fatal("missing arg for -D");
      }
    } else if (__read_byte(arg, 0) == '-' && __read_byte(arg, 1) == 'I') {
      int *idir = 0;
      if (__read_byte(arg, 2) != 0) {
        int ilen = 0;
        while (__read_byte(arg, 2 + ilen) != 0) { ilen++; }
        idir = make_str(arg, 2, ilen);
      } else if (i + 1 < argc) {
        i++;
        idir = argv[i];
      } else {
        my_fatal("missing arg for -I");
      }
      if (sys_include_dir == 0) { sys_include_dir = idir; }
      include_dirs[ninclude_dirs] = idir;
      ninclude_dirs++;
    } else if (my_strcmp(arg, "-fproper-layout") == 0) {
      // use_proper_layout is always 1; flag accepted for compatibility
    } else if (__read_byte(arg, 0) == '-') {
      printf("Unknown option: %s\n", arg);
      exit(1);
    } else {
      if (c_path != 0) { my_fatal("multiple input files"); }
      c_path = arg;
    }
    i++;
  }

  if (c_path == 0) {
    printf("Usage: cc [-o output] program.c\n");
    return 2;
  }

  // Add default include dir (include/ relative to argv[0]) if no -I given
  if (ninclude_dirs == 0) {
    int *exe = argv[0];
    int elen = my_strlen(exe);
    // Find last '/'
    int last_slash = 0 - 1;
    int si = 0;
    while (si < elen) {
      if (__read_byte(exe, si) == '/') { last_slash = si; }
      si++;
    }
    int *def_inc;
    if (last_slash >= 0) {
      int *dir = make_str(exe, 0, last_slash + 1);
      def_inc = pp_concat_paths(dir, "include");
    } else {
      def_inc = "include";
    }
    include_dirs[ninclude_dirs] = def_inc;
    ninclude_dirs++;
    sys_include_dir = def_inc;
  }

  cc_out_path = out_path;
  cc_c_path = c_path;
  return c_path;
}

int write_and_link(int *c_path, int *out_path) {
  // Write .s file
  // Build .s path: replace .c extension with .s
  int pathlen = my_strlen(c_path);
  int *s_path = my_malloc(pathlen + 4);
  int dot = 0 - 1;
  int pi = pathlen - 1;
  while (pi >= 0) {
    if (__read_byte(c_path, pi) == '.') {
      dot = pi;
      break;
    }
    if (__read_byte(c_path, pi) == '/') { break; }
    pi--;
  }
  int k = 0;
  if (dot >= 0) {
    k = 0;
    while (k < dot) {
      __write_byte(s_path, k, __read_byte(c_path, k));
      k++;
    }
    __write_byte(s_path, dot, '.');
    __write_byte(s_path, dot + 1, 's');
    __write_byte(s_path, dot + 2, 0);
  } else {
    k = 0;
    while (k < pathlen) {
      __write_byte(s_path, k, __read_byte(c_path, k));
      k++;
    }
    __write_byte(s_path, pathlen, '.');
    __write_byte(s_path, pathlen + 1, 's');
    __write_byte(s_path, pathlen + 2, 0);
  }

  int *sf = fopen(s_path, "w");
  if (sf == 0) { my_fatal("cannot write .s file"); }
  int wi = 0;
  while (wi < outlen) {
    fputc(__read_byte(outbuf, wi), sf);
    wi++;
  }
  fclose(sf);

  // Run clang
  int *cmd = my_malloc(4096);
  int cpos = 0;
  int *clang_str = "clang ";
  int ci2 = 0;
  while (__read_byte(clang_str, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(clang_str, ci2));
    cpos++;
    ci2++;
  }
  ci2 = 0;
  while (__read_byte(s_path, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(s_path, ci2));
    cpos++;
    ci2++;
  }
  int *o_str = " -o ";
  ci2 = 0;
  while (__read_byte(o_str, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(o_str, ci2));
    cpos++;
    ci2++;
  }
  ci2 = 0;
  while (__read_byte(out_path, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(out_path, ci2));
    cpos++;
    ci2++;
  }
  __write_byte(cmd, cpos, 0);

  int rc = system(cmd);
  if (rc != 0) { my_fatal("clang failed"); }

  printf("Wrote %s and built %s\n", s_path, out_path);
  return 0;
}

#ifdef __STDC__
int main(int argc, char **argv) {
#else
int main(int argc, int **argv) {
#endif
  int *c_path = parse_args(argc, argv);
  if (c_path == 0) { return 2; }
  int *out_path = cc_out_path;

  // Read source file
  int *f = fopen(c_path, "r");
  if (f == 0) {
    printf("Cannot open: %s\n", c_path);
    return 1;
  }
  int *srcbuf = my_malloc(10 * 1000 * 1000);
  int srclen = 0;
  int ch = fgetc(f);
  while (ch != 0 - 1) {
    __write_byte(srcbuf, srclen, ch);
    srclen++;
    ch = fgetc(f);
  }
  __write_byte(srcbuf, srclen, 0);
  fclose(f);

  // Join backslash-newline continuations
  for (int bsi = 0; bsi < srclen - 1; bsi++) {
    if (__read_byte(srcbuf, bsi) == '\\' && __read_byte(srcbuf, bsi + 1) == '\n') {
      __write_byte(srcbuf, bsi, ' ');
      __write_byte(srcbuf, bsi + 1, ' ');
    }
  }

  // Strip comments from source before preprocessing (preserves newlines)
  { int ri = 0; int wi = 0;
    while (ri < srclen) {
      // Skip string literals
      if (__read_byte(srcbuf, ri) == '"') {
        __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
        while (ri < srclen && __read_byte(srcbuf, ri) != '"') {
          if (__read_byte(srcbuf, ri) == '\\' && ri + 1 < srclen) {
            __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
          }
          __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
        }
        if (ri < srclen) { __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++; }
      }
      // Skip char literals
      else if (__read_byte(srcbuf, ri) == '\'' && ri + 1 < srclen) {
        __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
        while (ri < srclen && __read_byte(srcbuf, ri) != '\'') {
          if (__read_byte(srcbuf, ri) == '\\' && ri + 1 < srclen) {
            __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
          }
          __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
        }
        if (ri < srclen) { __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++; }
      }
      // Block comment: replace with space
      else if (ri + 1 < srclen && __read_byte(srcbuf, ri) == '/' && __read_byte(srcbuf, ri + 1) == '*') {
        ri = ri + 2;
        while (ri + 1 < srclen) {
          if (__read_byte(srcbuf, ri) == '*' && __read_byte(srcbuf, ri + 1) == '/') { ri = ri + 2; break; }
          if (__read_byte(srcbuf, ri) == '\n') { __write_byte(srcbuf, wi, '\n'); wi++; }
          ri++;
        }
        __write_byte(srcbuf, wi, ' '); wi++;
      }
      // Line comment: replace with nothing (keep newline)
      else if (ri + 1 < srclen && __read_byte(srcbuf, ri) == '/' && __read_byte(srcbuf, ri + 1) == '/') {
        ri = ri + 2;
        while (ri < srclen && __read_byte(srcbuf, ri) != '\n') { ri++; }
      }
      else {
        __write_byte(srcbuf, wi, __read_byte(srcbuf, ri)); ri++; wi++;
      }
    }
    srclen = wi;
    __write_byte(srcbuf, srclen, 0);
  }

  // Strip preprocessor lines and collect #define macros
  nmacros = 0;
  // Inject -D command-line macros
  int di = 0;
  while (di < ncmdline_defs) {
    int *def = cmdline_defs[di];
    // Find '=' in the string
    int eqpos = 0;
    int found_eq = 0;
    while (__read_byte(def, eqpos) != 0) {
      if (__read_byte(def, eqpos) == '=') { found_eq = 1; break; }
      eqpos++;
    }
    if (found_eq) {
      // Split at '='
      int *dm_name = make_str(def, 0, eqpos);
      int dm_vs = eqpos + 1;
      int dm_vl = 0;
      while (__read_byte(def, dm_vs + dm_vl) != 0) { dm_vl++; }
      int *dm_val = make_str(def, dm_vs, dm_vl);
      macros[nmacros].name = dm_name;
      macros[nmacros].value = dm_val;
      macros[nmacros].nparams = 0 - 1;
      macros[nmacros].params = 0;
      macros[nmacros].body = 0;
      macros[nmacros].def_pos = 0;
      nmacros++;
    } else {
      macros[nmacros].name = my_strdup(def);
      macros[nmacros].value = my_strdup("1");
      macros[nmacros].nparams = 0 - 1;
      macros[nmacros].params = 0;
      macros[nmacros].body = 0;
      macros[nmacros].def_pos = 0;
      nmacros++;
    }
    di++;
  }
  // Built-in type macros (GCC compatibility)
  {
    int *bi_names[48];
    int *bi_vals[48];
    int nbi = 0;
    bi_names[0] = "__SIZE_TYPE__"; bi_vals[0] = "unsigned long"; nbi++;
    bi_names[1] = "__INTPTR_TYPE__"; bi_vals[1] = "long"; nbi++;
    bi_names[2] = "__UINTPTR_TYPE__"; bi_vals[2] = "unsigned long"; nbi++;
    bi_names[3] = "__PTRDIFF_TYPE__"; bi_vals[3] = "long"; nbi++;
    bi_names[4] = "__INT32_TYPE__"; bi_vals[4] = "int"; nbi++;
    bi_names[5] = "__UINT32_TYPE__"; bi_vals[5] = "unsigned int"; nbi++;
    bi_names[6] = "__WCHAR_TYPE__"; bi_vals[6] = "int"; nbi++;
    bi_names[7] = "__SIZEOF_POINTER__"; bi_vals[7] = "8"; nbi++;
    bi_names[8] = "__CHAR_BIT__"; bi_vals[8] = "8"; nbi++;
    bi_names[9] = "__INT_MAX__"; bi_vals[9] = "2147483647"; nbi++;
    bi_names[10] = "__LONG_MAX__"; bi_vals[10] = "9223372036854775807L"; nbi++;
    bi_names[11] = "__LONG_LONG_MAX__"; bi_vals[11] = "9223372036854775807LL"; nbi++;
    bi_names[12] = "__SIZEOF_INT__"; bi_vals[12] = "4"; nbi++;
    bi_names[13] = "__SIZEOF_LONG__"; bi_vals[13] = "8"; nbi++;
    bi_names[14] = "__SIZEOF_LONG_LONG__"; bi_vals[14] = "8"; nbi++;
    bi_names[15] = "__UINT8_TYPE__"; bi_vals[15] = "unsigned char"; nbi++;
    bi_names[16] = "__INT8_TYPE__"; bi_vals[16] = "signed char"; nbi++;
    bi_names[17] = "__UINT16_TYPE__"; bi_vals[17] = "unsigned short"; nbi++;
    bi_names[18] = "__INT16_TYPE__"; bi_vals[18] = "short"; nbi++;
    bi_names[19] = "__UINT64_TYPE__"; bi_vals[19] = "unsigned long"; nbi++;
    bi_names[20] = "__INT64_TYPE__"; bi_vals[20] = "long"; nbi++;
    bi_names[21] = "__INT_LEAST8_TYPE__"; bi_vals[21] = "signed char"; nbi++;
    bi_names[22] = "__SIZEOF_SHORT__"; bi_vals[22] = "2"; nbi++;
    bi_names[23] = "__SIZEOF_FLOAT__"; bi_vals[23] = "4"; nbi++;
    bi_names[24] = "__SIZEOF_DOUBLE__"; bi_vals[24] = "8"; nbi++;
    bi_names[25] = "__FLT_MIN__"; bi_vals[25] = "1.17549435e-38F"; nbi++;
    bi_names[26] = "__FLT_MAX__"; bi_vals[26] = "3.40282347e+38F"; nbi++;
    bi_names[27] = "__DBL_MANT_DIG__"; bi_vals[27] = "53"; nbi++;
    bi_names[28] = "__SCHAR_MAX__"; bi_vals[28] = "127"; nbi++;
    bi_names[29] = "__SHRT_MAX__"; bi_vals[29] = "32767"; nbi++;
    bi_names[30] = "__DBL_MAX__"; bi_vals[30] = "1.7976931348623157e+308"; nbi++;
    bi_names[31] = "__UINT_LEAST32_TYPE__"; bi_vals[31] = "unsigned int"; nbi++;
    bi_names[32] = "__LDBL_MAX__"; bi_vals[32] = "1.18973149535723176502e+4932L"; nbi++;
    bi_names[33] = "__LDBL_MANT_DIG__"; bi_vals[33] = "64"; nbi++;
    bi_names[34] = "__FLT_MANT_DIG__"; bi_vals[34] = "24"; nbi++;
    bi_names[35] = "__DBL_MIN__"; bi_vals[35] = "2.2250738585072014e-308"; nbi++;
    bi_names[36] = "__LDBL_MIN__"; bi_vals[36] = "3.36210314311209350626e-4932L"; nbi++;
    bi_names[37] = "__FLT_RADIX__"; bi_vals[37] = "2"; nbi++;
    bi_names[38] = "__FLT_DIG__"; bi_vals[38] = "6"; nbi++;
    bi_names[39] = "__DBL_DIG__"; bi_vals[39] = "15"; nbi++;
    bi_names[40] = "__LDBL_DIG__"; bi_vals[40] = "18"; nbi++;
    int bi = 0;
    while (bi < nbi) {
      macros[nmacros].name = my_strdup(bi_names[bi]);
      macros[nmacros].value = my_strdup(bi_vals[bi]);
      macros[nmacros].nparams = 0 - 1;
      macros[nmacros].params = 0;
      macros[nmacros].body = 0;
      macros[nmacros].def_pos = 0;
      nmacros++;
      bi++;
    }
  }
  // __LINE__ and __FILE__ are handled as special cases in the macro expander
  if_depth = 0;

  int pp_bufsz = srclen * 4 + 1;
  if (pp_bufsz < 262144) { pp_bufsz = 262144; }
  int *cleaned = my_malloc(pp_bufsz);
  int co = 0;
  co = pp_preprocess(srcbuf, srclen, c_path, cleaned, co, 0);
  __write_byte(cleaned, co, 0);
  if (if_depth != 0) { my_fatal("Unterminated #if/#ifdef/#ifndef"); }

  // Strip block comments from preprocessed output before macro expansion
  // Must skip string/char literals to avoid stripping // inside "http://..."
  { int ri = 0; int wi = 0;
    while (ri < co) {
      if (__read_byte(cleaned, ri) == '"') {
        __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
        while (ri < co && __read_byte(cleaned, ri) != '"') {
          if (__read_byte(cleaned, ri) == '\\' && ri + 1 < co) {
            __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
          }
          __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
        }
        if (ri < co) { __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++; }
      } else if (__read_byte(cleaned, ri) == '\'' && ri + 1 < co) {
        __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
        while (ri < co && __read_byte(cleaned, ri) != '\'') {
          if (__read_byte(cleaned, ri) == '\\' && ri + 1 < co) {
            __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
          }
          __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++;
        }
        if (ri < co) { __write_byte(cleaned, wi, __read_byte(cleaned, ri)); ri++; wi++; }
      } else if (__read_byte(cleaned, ri) == '/' && ri + 1 < co && __read_byte(cleaned, ri + 1) == '*') {
        ri = ri + 2;
        while (ri + 1 < co) {
          if (__read_byte(cleaned, ri) == '*' && __read_byte(cleaned, ri + 1) == '/') { ri = ri + 2; break; }
          ri++;
        }
      } else if (__read_byte(cleaned, ri) == '/' && ri + 1 < co && __read_byte(cleaned, ri + 1) == '/') {
        ri = ri + 2;
        while (ri < co && __read_byte(cleaned, ri) != '\n') { ri++; }
      } else {
        __write_byte(cleaned, wi, __read_byte(cleaned, ri));
        wi++; ri++;
      }
    }
    co = wi;
    __write_byte(cleaned, co, 0);
  }
  // Second pass: strip orphaned comment continuations (lines with */ but no /*)
  // These occur when /* was inside a #define value and */ is on a continuation line
  { int ri = 0; int wi = 0;
    while (ri < co) {
      // Check if current line has */ but no /*
      int ls = ri; // line start
      int has_ss = 0; int has_se = 0;
      int li = ri;
      while (li < co && __read_byte(cleaned, li) != '\n') {
        if (__read_byte(cleaned, li) == '/' && li + 1 < co && __read_byte(cleaned, li + 1) == '*') { has_ss = 1; }
        if (__read_byte(cleaned, li) == '*' && li + 1 < co && __read_byte(cleaned, li + 1) == '/') { has_se = 1; }
        li++;
      }
      if (has_se && !has_ss) {
        // Orphaned comment end — skip this line
        ri = li;
        if (ri < co && __read_byte(cleaned, ri) == '\n') { ri++; }
      } else {
        // Copy line as-is
        while (ri < co && __read_byte(cleaned, ri) != '\n') {
          __write_byte(cleaned, wi, __read_byte(cleaned, ri));
          wi++; ri++;
        }
        if (ri < co) { __write_byte(cleaned, wi, '\n'); wi++; ri++; }
      }
    }
    co = wi;
    __write_byte(cleaned, co, 0);
  }
  // Build macro hash table
  { int hi = 0; while (hi < MAX_MACRO_BUCKETS) { macro_ht_head[hi] = 0 - 1; hi++; } }
  { int mi = 0; while (mi < nmacros) {
    macros[mi].nlen = my_strlen(macros[mi].name);
    macros[mi].ht_next = 0 - 1;
    int h = 0; int ci = 0;
    while (ci < macros[mi].nlen) { h = h * 31 + __read_byte(macros[mi].name, ci); ci++; }
    h = h & 65535;
    macros[mi].ht_next = macro_ht_head[h];
    macro_ht_head[h] = mi;
    mi++;
  } }
  // Expand macros if any were defined
  int *expanded = 0;
  int ei = 0;
  int eo = 0;
  int istart = 0;
  int ilen = 0;
  int found = 0;
  int mc = 0;
  int vlen = 0;
  int vi = 0;
  int ki = 0;
  { // Always run expansion pass (for __LINE__/__FILE__ even with nmacros==0)
    // Buffer must be large enough for full macro expansion.
    // co*8 may be too small when source has large macros relative to code size.
    // Add total macro body/value sizes to account for expansion.
    int macro_total = 0;
    { int mti = 0; while (mti < nmacros) {
      if (macros[mti].body) { macro_total = macro_total + my_strlen(macros[mti].body); }
      if (macros[mti].value) { macro_total = macro_total + my_strlen(macros[mti].value); }
      mti++;
    } }
    int exp_buf_size = co * 8 + 1;
    if (exp_buf_size < macro_total * 4 + co + 1) { exp_buf_size = macro_total * 4 + co + 1; }
    expanded = my_malloc(exp_buf_size);
    ei = 0;
    eo = 0;
    int dbg_next = 562300;
    while (ei < co) {
      // Skip string literals
      if (__read_byte(cleaned, ei) == '"') {
        __write_byte(expanded, eo, __read_byte(cleaned, ei));
        ei++;
        eo++;
        while (ei < co && __read_byte(cleaned, ei) != '"') {
          if (__read_byte(cleaned, ei) == '\\' && ei + 1 < co) {
            __write_byte(expanded, eo, __read_byte(cleaned, ei));
            ei++;
            eo++;
          }
          __write_byte(expanded, eo, __read_byte(cleaned, ei));
          ei++;
          eo++;
        }
        if (ei < co) {
          __write_byte(expanded, eo, __read_byte(cleaned, ei));
          ei++;
          eo++;
        }
      } else if (__read_byte(cleaned, ei) == '\'') {
        // Skip char literals
        __write_byte(expanded, eo, __read_byte(cleaned, ei));
        ei++;
        eo++;
        while (ei < co && __read_byte(cleaned, ei) != '\'') {
          if (__read_byte(cleaned, ei) == '\\' && ei + 1 < co) {
            __write_byte(expanded, eo, __read_byte(cleaned, ei));
            ei++;
            eo++;
          }
          __write_byte(expanded, eo, __read_byte(cleaned, ei));
          ei++;
          eo++;
        }
        if (ei < co) {
          __write_byte(expanded, eo, __read_byte(cleaned, ei));
          ei++;
          eo++;
        }
      } else if (is_alpha(__read_byte(cleaned, ei))) {
        // Identifier — check against macros
        istart = ei;
        while (ei < co && is_alnum(__read_byte(cleaned, ei))) {
          ei++;
        }
        ilen = ei - istart;
        int *idstr = make_str(cleaned, istart, ilen);
        // Special built-in macros
        if (ilen == 8 && my_strcmp(idstr, "__LINE__") == 0) {
          int ln = 1; int li = 0; while (li < istart) { if (__read_byte(cleaned, li) == '\n') { ln++; } li++; }
          int *lns = int_to_str(ln);
          int lnl = my_strlen(lns); int lni = 0;
          while (lni < lnl) { __write_byte(expanded, eo, __read_byte(lns, lni)); eo++; lni++; }
          found = 1;
        } else if (ilen == 8 && my_strcmp(idstr, "__FILE__") == 0) {
          __write_byte(expanded, eo, '"'); eo++;
          int fnl = my_strlen(c_path); int fni = 0;
          while (fni < fnl) { __write_byte(expanded, eo, __read_byte(c_path, fni)); eo++; fni++; }
          __write_byte(expanded, eo, '"'); eo++;
          found = 1;
        } else {
        found = 0;
        { int h = 0; int ci = 0; while (ci < ilen) { h = h * 31 + __read_byte(cleaned, istart + ci); ci++; } mc = macro_ht_head[h & 65535]; }
        while (mc >= 0) {
          if (macros[mc].nlen == ilen &&
              my_strcmp(idstr, macros[mc].name) == 0 &&
              istart >= macros[mc].def_pos) {
            // Don't expand L when followed by ' or " (wide char/string literal)
            if (ilen == 1 && __read_byte(cleaned, istart) == 'L' && ei < co && (__read_byte(cleaned, ei) == '\'' || __read_byte(cleaned, ei) == '"')) {
              break;
            }
            if (macros[mc].nparams >= 0) {
              // Function-like macro: look for '('
              int fj = ei;
              while (fj < co && (__read_byte(cleaned, fj) == ' ' || __read_byte(cleaned, fj) == '\t')) { fj++; }
              if (fj < co && __read_byte(cleaned, fj) == '(') {
                fj++; // skip '('
                // Parse arguments
                int *fargs[64];
                int fnargs = 0;
                int fdepth = 1;
                int astart = fj;
                while (fj < co && fdepth > 0) {
                  if (__read_byte(cleaned, fj) == '(') { fdepth++; }
                  else if (__read_byte(cleaned, fj) == ')') {
                    fdepth--;
                    if (fdepth == 0) {
                      if ((fj > astart || fnargs > 0) && fnargs < 64) {
                        fargs[fnargs] = make_str(cleaned, astart, fj - astart);
                        fnargs++;
                      }
                      fj++;
                      break;
                    }
                  } else if (__read_byte(cleaned, fj) == ',' && fdepth == 1) {
                    if (fnargs < 64) { fargs[fnargs] = make_str(cleaned, astart, fj - astart); }
                    fnargs++;
                    fj++;
                    while (fj < co && (__read_byte(cleaned, fj) == ' ' || __read_byte(cleaned, fj) == '\t')) { fj++; }
                    astart = fj;
                    continue;
                  } else if (__read_byte(cleaned, fj) == '"') {
                    fj++;
                    while (fj < co && __read_byte(cleaned, fj) != '"') {
                      if (__read_byte(cleaned, fj) == '\\' && fj + 1 < co) { fj++; }
                      fj++;
                    }
                    if (fj < co) { fj++; }
                    continue;
                  } else if (__read_byte(cleaned, fj) == '\'') {
                    fj++;
                    while (fj < co && __read_byte(cleaned, fj) != '\'') {
                      if (__read_byte(cleaned, fj) == '\\' && fj + 1 < co) { fj++; }
                      fj++;
                    }
                    if (fj < co) { fj++; }
                    continue;
                  }
                  fj++;
                }
                // Check argument count matches (skip expansion if mismatch)
                int argcount_ok = 1;
                if (fnargs != macros[mc].nparams && !(macros[mc].is_variadic && fnargs >= macros[mc].nparams)) {
                  // Argument count mismatch: don't expand, copy identifier + args as-is
                  int bk = istart;
                  while (bk < fj) { __write_byte(expanded, eo, __read_byte(cleaned, bk)); eo++; bk++; }
                  ei = fj; // skip past the consumed text
                  found = 1; // we already wrote output, don't copy again
                  mc = 0 - 1; // break
                  argcount_ok = 0;
                }
                // Substitute params in body
                int *mbody = macros[mc >= 0 ? mc : 0].body;
                int mblen = argcount_ok ? my_strlen(mbody) : 0;
                int bi = 0;
                int after_paste = 0;
                while (bi < mblen) {
                  if (is_alpha(__read_byte(mbody, bi))) {
                    int ps1 = bi;
                    while (bi < mblen && is_alnum(__read_byte(mbody, bi))) { bi++; }
                    int pl1 = bi - ps1;
                    int *pn1 = make_str(mbody, ps1, pl1);
                    int pf1 = 0;
                    int px1 = 0;
                    // Check if ## follows this param (strip trailing ws from arg)
                    int paste_follows = 0;
                    { int bk2 = bi; while (bk2 < mblen && (__read_byte(mbody, bk2) == ' ' || __read_byte(mbody, bk2) == '\t')) { bk2++; }
                      if (bk2 + 1 < mblen && __read_byte(mbody, bk2) == '#' && __read_byte(mbody, bk2 + 1) == '#') { paste_follows = 1; } }
                    // Don't substitute L when followed by ' or " (wide char/string literal)
                    int skip_param_sub = 0;
                    if (pl1 == 1 && __read_byte(mbody, ps1) == 'L' && bi < mblen && (__read_byte(mbody, bi) == '\'' || __read_byte(mbody, bi) == '"')) { skip_param_sub = 1; }
                    while (px1 < macros[mc].nparams && skip_param_sub == 0) {
                      if (my_strcmp(macros[mc].params[px1], pn1) == 0) {
                        // Substitute with argument
                        int alen = my_strlen(fargs[px1]);
                        int ai = 0;
                        // Skip leading whitespace if after ##
                        if (after_paste) { while (ai < alen && (__read_byte(fargs[px1], ai) == ' ' || __read_byte(fargs[px1], ai) == '\t')) { ai++; } }
                        // Find end (strip trailing whitespace if ## follows)
                        int aend = alen;
                        if (paste_follows) { while (aend > ai && (__read_byte(fargs[px1], aend - 1) == ' ' || __read_byte(fargs[px1], aend - 1) == '\t')) { aend--; } }
                        while (ai < aend) {
                          __write_byte(expanded, eo, __read_byte(fargs[px1], ai));
                          eo++;
                          ai++;
                        }
                        pf1 = 1;
                        px1 = macros[mc].nparams; // break
                      }
                      px1++;
                    }
                    if (pf1 == 0 && macros[mc].is_variadic && my_strcmp(pn1, "__VA_ARGS__") == 0) {
                      // Substitute variadic args
                      int vai = macros[mc].nparams;
                      while (vai < fnargs) {
                        if (vai > macros[mc].nparams) { __write_byte(expanded, eo, ','); eo++; __write_byte(expanded, eo, ' '); eo++; }
                        int alen = my_strlen(fargs[vai]);
                        int ai = 0;
                        while (ai < alen) { __write_byte(expanded, eo, __read_byte(fargs[vai], ai)); eo++; ai++; }
                        vai++;
                      }
                      pf1 = 1;
                    }
                    if (pf1 == 0) {
                      // Copy body identifier as-is
                      // If it matches the macro's own name, insert 0x01 marker to prevent re-expansion
                      if (pl1 == macros[mc].nlen && my_strcmp(pn1, macros[mc].name) == 0) {
                        __write_byte(expanded, eo, 1); eo++; // self-reference marker
                      }
                      int bk = ps1;
                      while (bk < bi) {
                        __write_byte(expanded, eo, __read_byte(mbody, bk));
                        eo++;
                        bk++;
                      }
                    }
                    after_paste = 0;
                  } else if (__read_byte(mbody, bi) == '#' && bi + 1 < mblen && __read_byte(mbody, bi + 1) == '#') {
                    // Token pasting: remove ## and surrounding whitespace
                    bi = bi + 2;
                    while (eo > 0 && (__read_byte(expanded, eo - 1) == ' ' || __read_byte(expanded, eo - 1) == '\t')) { eo--; }
                    while (bi < mblen && (__read_byte(mbody, bi) == ' ' || __read_byte(mbody, bi) == '\t')) { bi++; }
                    after_paste = 1;
                  } else if (__read_byte(mbody, bi) == '#' && bi + 1 < mblen && is_alpha(__read_byte(mbody, bi + 1))) {
                    // Stringify operator
                    bi++; // skip #
                    int sps = bi;
                    while (bi < mblen && is_alnum(__read_byte(mbody, bi))) { bi++; }
                    int *spn = make_str(mbody, sps, bi - sps);
                    int spf = 0;
                    int spi = 0;
                    while (spi < macros[mc].nparams) {
                      if (my_strcmp(macros[mc].params[spi], spn) == 0) {
                        __write_byte(expanded, eo, '"'); eo++;
                        int salen = my_strlen(fargs[spi]);
                        int sai = 0;
                        while (sai < salen) {
                          int sc = __read_byte(fargs[spi], sai);
                          if (sc == '"' || sc == '\\') { __write_byte(expanded, eo, '\\'); eo++; }
                          __write_byte(expanded, eo, sc); eo++;
                          sai++;
                        }
                        __write_byte(expanded, eo, '"'); eo++;
                        spf = 1; spi = macros[mc].nparams;
                      }
                      spi++;
                    }
                    if (spf == 0) {
                      __write_byte(expanded, eo, '#'); eo++;
                      int sbk = sps;
                      while (sbk < bi) { __write_byte(expanded, eo, __read_byte(mbody, sbk)); eo++; sbk++; }
                    }
                    after_paste = 0;
                  } else {
                    __write_byte(expanded, eo, __read_byte(mbody, bi));
                    eo++;
                    bi++;
                  }
                }
                if (argcount_ok) { ei = fj; found = 1; mc = 0 - 1; }
              }
              // If no '(' follows, don't expand — fall through
            } else {
              // Object-like macro: copy value
              vlen = my_strlen(macros[mc].value);
              vi = 0;
              while (vi < vlen) {
                __write_byte(expanded, eo, __read_byte(macros[mc].value, vi));
                eo++;
                vi++;
              }
              found = 1;
              mc = 0 - 1; // break
            }
          }
          if (mc >= 0) { mc = macros[mc].ht_next; }
        }
        if (found == 0) {
          // Copy identifier as-is
          ki = istart;
          while (ki < ei) {
            __write_byte(expanded, eo, __read_byte(cleaned, ki));
            eo++;
            ki++;
          }
        }
        } // close else from __LINE__/__FILE__ check
      } else {
        __write_byte(expanded, eo, __read_byte(cleaned, ei));
        ei++;
        eo++;
      }
    }
    __write_byte(expanded, eo, 0);
    cleaned = expanded;
    co = eo;

    // Repeat expansion until no more macros are found
    int expand_changed = 1;
    int expand_iter = 0;
    while (expand_changed && expand_iter < 16) {
    expand_changed = 0;
    expand_iter++;
    int exp2_size = co * 8 + 1;
    if (exp2_size < macro_total * 4 + co + 1) { exp2_size = macro_total * 4 + co + 1; }
    int *expanded2 = my_malloc(exp2_size);
    ei = 0;
    eo = 0;
    while (ei < co) {
      if (__read_byte(cleaned, ei) == '"') {
        __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
        while (ei < co && __read_byte(cleaned, ei) != '"') {
          if (__read_byte(cleaned, ei) == '\\' && ei + 1 < co) {
            __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
          }
          __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
        }
        if (ei < co) { __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++; }
      } else if (__read_byte(cleaned, ei) == '\'') {
        __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
        while (ei < co && __read_byte(cleaned, ei) != '\'') {
          if (__read_byte(cleaned, ei) == '\\' && ei + 1 < co) {
            __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
          }
          __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
        }
        if (ei < co) { __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++; }
      } else if (__read_byte(cleaned, ei) == 1 && ei + 1 < co && is_alpha(__read_byte(cleaned, ei + 1))) {
        // Self-reference marker: copy marker + identifier without expanding
        __write_byte(expanded2, eo, 1); eo++; ei++; // copy marker
        while (ei < co && is_alnum(__read_byte(cleaned, ei))) {
          __write_byte(expanded2, eo, __read_byte(cleaned, ei)); eo++; ei++;
        }
      } else if (is_alpha(__read_byte(cleaned, ei))) {
        istart = ei;
        while (ei < co && is_alnum(__read_byte(cleaned, ei))) { ei++; }
        ilen = ei - istart;
        int *idstr2 = make_str(cleaned, istart, ilen);
        // Special built-in macros in second pass
        if (ilen == 8 && my_strcmp(idstr2, "__LINE__") == 0) {
          int ln2 = 1; int li2 = 0; while (li2 < istart) { if (__read_byte(cleaned, li2) == '\n') { ln2++; } li2++; }
          int *lns2 = int_to_str(ln2);
          int lnl2 = my_strlen(lns2); int lni2 = 0;
          while (lni2 < lnl2) { __write_byte(expanded2, eo, __read_byte(lns2, lni2)); eo++; lni2++; }
          found = 1; expand_changed = 1;
        } else if (ilen == 8 && my_strcmp(idstr2, "__FILE__") == 0) {
          __write_byte(expanded2, eo, '"'); eo++;
          int fnl2 = my_strlen(c_path); int fni2 = 0;
          while (fni2 < fnl2) { __write_byte(expanded2, eo, __read_byte(c_path, fni2)); eo++; fni2++; }
          __write_byte(expanded2, eo, '"'); eo++;
          found = 1; expand_changed = 1;
        } else {
        found = 0;
        { int h = 0; int ci = 0; while (ci < ilen) { h = h * 31 + __read_byte(cleaned, istart + ci); ci++; } mc = macro_ht_head[h & 65535]; }
        while (mc >= 0) {
          if (macros[mc].nlen == ilen &&
              my_strcmp(idstr2, macros[mc].name) == 0) {
            // Don't expand L when followed by ' or " (wide char/string literal)
            if (ilen == 1 && __read_byte(cleaned, istart) == 'L' && ei < co && (__read_byte(cleaned, ei) == '\'' || __read_byte(cleaned, ei) == '"')) {
              break;
            }
            if (macros[mc].nparams >= 0) {
              int fj2 = ei;
              while (fj2 < co && (__read_byte(cleaned, fj2) == ' ' || __read_byte(cleaned, fj2) == '\t')) { fj2++; }
              if (fj2 < co && __read_byte(cleaned, fj2) == '(') {
                fj2++;
                int *fargs2[64];
                int fnargs2 = 0;
                int fdepth2 = 1;
                int astart2 = fj2;
                while (fj2 < co && fdepth2 > 0) {
                  if (__read_byte(cleaned, fj2) == '(') { fdepth2++; }
                  else if (__read_byte(cleaned, fj2) == ')') {
                    fdepth2--;
                    if (fdepth2 == 0) {
                      if ((fj2 > astart2 || fnargs2 > 0) && fnargs2 < 64) { fargs2[fnargs2] = make_str(cleaned, astart2, fj2 - astart2); fnargs2++; }
                      fj2++; break;
                    }
                  } else if (__read_byte(cleaned, fj2) == ',' && fdepth2 == 1) {
                    if (fnargs2 < 64) { fargs2[fnargs2] = make_str(cleaned, astart2, fj2 - astart2); } fnargs2++;
                    fj2++;
                    while (fj2 < co && (__read_byte(cleaned, fj2) == ' ' || __read_byte(cleaned, fj2) == '\t')) { fj2++; }
                    astart2 = fj2; continue;
                  } else if (__read_byte(cleaned, fj2) == '"') {
                    fj2++;
                    while (fj2 < co && __read_byte(cleaned, fj2) != '"') {
                      if (__read_byte(cleaned, fj2) == '\\' && fj2 + 1 < co) { fj2++; }
                      fj2++;
                    }
                    if (fj2 < co) { fj2++; }
                    continue;
                  } else if (__read_byte(cleaned, fj2) == '\'') {
                    fj2++;
                    while (fj2 < co && __read_byte(cleaned, fj2) != '\'') {
                      if (__read_byte(cleaned, fj2) == '\\' && fj2 + 1 < co) { fj2++; }
                      fj2++;
                    }
                    if (fj2 < co) { fj2++; }
                    continue;
                  }
                  fj2++;
                }
                // Check argument count matches
                int argcount_ok2 = 1;
                if (fnargs2 != macros[mc].nparams && !(macros[mc].is_variadic && fnargs2 >= macros[mc].nparams)) {
                  // Copy identifier + full argument text as-is
                  int bk2 = istart;
                  while (bk2 < fj2) { __write_byte(expanded2, eo, __read_byte(cleaned, bk2)); eo++; bk2++; }
                  ei = fj2; // skip past the consumed text
                  found = 1; // we already wrote output, don't copy again
                  mc = 0 - 1;
                  argcount_ok2 = 0;
                }
                int *mbody2 = macros[mc >= 0 ? mc : 0].body;
                int mblen2 = argcount_ok2 ? my_strlen(mbody2) : 0;
                int bi2 = 0;
                int after_paste2 = 0;
                while (bi2 < mblen2) {
                  if (is_alpha(__read_byte(mbody2, bi2))) {
                    int pstart2 = bi2;
                    while (bi2 < mblen2 && is_alnum(__read_byte(mbody2, bi2))) { bi2++; }
                    int plen2 = bi2 - pstart2;
                    int *pname2 = make_str(mbody2, pstart2, plen2);
                    int pfound2 = 0;
                    int pi2 = 0;
                    int paste_follows2 = 0;
                    { int bk3 = bi2; while (bk3 < mblen2 && (__read_byte(mbody2, bk3) == ' ' || __read_byte(mbody2, bk3) == '\t')) { bk3++; }
                      if (bk3 + 1 < mblen2 && __read_byte(mbody2, bk3) == '#' && __read_byte(mbody2, bk3 + 1) == '#') { paste_follows2 = 1; } }
                    int skip_psub2 = 0;
                    if (plen2 == 1 && __read_byte(mbody2, pstart2) == 'L' && bi2 < mblen2 && (__read_byte(mbody2, bi2) == '\'' || __read_byte(mbody2, bi2) == '"')) { skip_psub2 = 1; }
                    while (pi2 < macros[mc].nparams && skip_psub2 == 0) {
                      if (my_strcmp(macros[mc].params[pi2], pname2) == 0) {
                        int alen2 = my_strlen(fargs2[pi2]);
                        int ai2 = 0;
                        if (after_paste2) { while (ai2 < alen2 && (__read_byte(fargs2[pi2], ai2) == ' ' || __read_byte(fargs2[pi2], ai2) == '\t')) { ai2++; } }
                        int aend2 = alen2;
                        if (paste_follows2) { while (aend2 > ai2 && (__read_byte(fargs2[pi2], aend2 - 1) == ' ' || __read_byte(fargs2[pi2], aend2 - 1) == '\t')) { aend2--; } }
                        while (ai2 < aend2) { __write_byte(expanded2, eo, __read_byte(fargs2[pi2], ai2)); eo++; ai2++; }
                        pfound2 = 1; pi2 = macros[mc].nparams;
                      }
                      pi2++;
                    }
                    if (pfound2 == 0 && macros[mc].is_variadic && my_strcmp(pname2, "__VA_ARGS__") == 0) {
                      int vai2 = macros[mc].nparams;
                      while (vai2 < fnargs2) {
                        if (vai2 > macros[mc].nparams) { __write_byte(expanded2, eo, ','); eo++; __write_byte(expanded2, eo, ' '); eo++; }
                        int alen2 = my_strlen(fargs2[vai2]);
                        int ai2 = 0;
                        while (ai2 < alen2) { __write_byte(expanded2, eo, __read_byte(fargs2[vai2], ai2)); eo++; ai2++; }
                        vai2++;
                      }
                      pfound2 = 1;
                    }
                    if (pfound2 == 0) {
                      // Self-reference marker for re-expansion
                      if (plen2 == macros[mc].nlen && my_strcmp(pname2, macros[mc].name) == 0) {
                        __write_byte(expanded2, eo, 1); eo++;
                      }
                      int bk2 = pstart2;
                      while (bk2 < bi2) { __write_byte(expanded2, eo, __read_byte(mbody2, bk2)); eo++; bk2++; }
                    }
                    after_paste2 = 0;
                  } else if (__read_byte(mbody2, bi2) == '#' && bi2 + 1 < mblen2 && __read_byte(mbody2, bi2 + 1) == '#') {
                    bi2 = bi2 + 2;
                    while (eo > 0 && (__read_byte(expanded2, eo - 1) == ' ' || __read_byte(expanded2, eo - 1) == '\t')) { eo--; }
                    while (bi2 < mblen2 && (__read_byte(mbody2, bi2) == ' ' || __read_byte(mbody2, bi2) == '\t')) { bi2++; }
                    after_paste2 = 1;
                  } else if (__read_byte(mbody2, bi2) == '#' && bi2 + 1 < mblen2 && is_alpha(__read_byte(mbody2, bi2 + 1))) {
                    bi2++;
                    int sps2 = bi2;
                    while (bi2 < mblen2 && is_alnum(__read_byte(mbody2, bi2))) { bi2++; }
                    int *spn2 = make_str(mbody2, sps2, bi2 - sps2);
                    int spf2 = 0;
                    int spi2 = 0;
                    while (spi2 < macros[mc].nparams) {
                      if (my_strcmp(macros[mc].params[spi2], spn2) == 0) {
                        __write_byte(expanded2, eo, '"'); eo++;
                        int salen2 = my_strlen(fargs2[spi2]);
                        int sai2 = 0;
                        while (sai2 < salen2) {
                          int sc2 = __read_byte(fargs2[spi2], sai2);
                          if (sc2 == '"' || sc2 == '\\') { __write_byte(expanded2, eo, '\\'); eo++; }
                          __write_byte(expanded2, eo, sc2); eo++;
                          sai2++;
                        }
                        __write_byte(expanded2, eo, '"'); eo++;
                        spf2 = 1; spi2 = macros[mc].nparams;
                      }
                      spi2++;
                    }
                    if (spf2 == 0) {
                      __write_byte(expanded2, eo, '#'); eo++;
                      int sbk2 = sps2;
                      while (sbk2 < bi2) { __write_byte(expanded2, eo, __read_byte(mbody2, sbk2)); eo++; sbk2++; }
                    }
                    after_paste2 = 0;
                  } else {
                    __write_byte(expanded2, eo, __read_byte(mbody2, bi2)); eo++; bi2++;
                  }
                }
                if (argcount_ok2) { ei = fj2; found = 1; expand_changed = 1; mc = 0 - 1; }
              }
            } else {
              // Self-referential check: skip if macro name appears as identifier in value
              int selfref = 0;
              { int sr_vl = my_strlen(macros[mc].value);
                int sr_nl = macros[mc].nlen;
                int sr_i = 0;
                while (sr_i + sr_nl <= sr_vl) {
                  if (sr_i > 0 && is_alnum(__read_byte(macros[mc].value, sr_i - 1))) { sr_i++; }
                  else {
                    int sr_m = 1;
                    int sr_j = 0;
                    while (sr_j < sr_nl) {
                      if (__read_byte(macros[mc].value, sr_i + sr_j) != __read_byte(macros[mc].name, sr_j)) { sr_m = 0; sr_j = sr_nl; }
                      sr_j++;
                    }
                    if (sr_m && (sr_i + sr_nl >= sr_vl || is_alnum(__read_byte(macros[mc].value, sr_i + sr_nl)) == 0)) { selfref = 1; sr_i = sr_vl; }
                    else { sr_i++; }
                  }
                }
              }
              if (selfref == 0) {
                vlen = my_strlen(macros[mc].value);
                vi = 0;
                while (vi < vlen) { __write_byte(expanded2, eo, __read_byte(macros[mc].value, vi)); eo++; vi++; }
                found = 1; expand_changed = 1; mc = 0 - 1;
              } else {
                mc = 0 - 1;
              }
            }
          }
          if (mc >= 0) { mc = macros[mc].ht_next; }
        }
        if (found == 0) {
          ki = istart;
          while (ki < ei) { __write_byte(expanded2, eo, __read_byte(cleaned, ki)); eo++; ki++; }
        }
        } // close else from __LINE__/__FILE__ check (pass 2)
      } else {
        __write_byte(expanded2, eo, __read_byte(cleaned, ei)); ei++; eo++;
      }
    }
    __write_byte(expanded2, eo, 0);
    cleaned = expanded2;
    co = eo;
    } // end expand loop

    // Strip self-reference marker bytes (0x01) from final output
    { int si = 0; int so = 0;
      while (si < co) {
        if (__read_byte(cleaned, si) == 1) { si++; continue; }
        __write_byte(cleaned, so, __read_byte(cleaned, si));
        si++; so++;
      }
      __write_byte(cleaned, so, 0);
      co = so;
    }
  }

  // Lex
  lex(cleaned, co);

  // Parse
  struct Program *prog = parse_program();

  // Codegen
  outcap = 16 * 1000 * 1000;
  outbuf = my_malloc(outcap);
  outlen = 0;
  codegen(prog);

  write_and_link(c_path, out_path);
  return 0;
}
