// Self-hosting C compiler - compiles itself using only the C subset it supports
// Supported: int, int *, struct, if/else, while, for, break, continue, return
// No: enum, typedef, union, switch, char, void, sizeof

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- Constants ----
// Token kinds
int TK_NUM = 0;
int TK_ID = 1;
int TK_STR = 2;
int TK_KW = 3;
int TK_OP = 4;
int TK_EOF = 5;

// Expr kinds
int ND_NUM = 0;
int ND_VAR = 1;
int ND_STRLIT = 2;
int ND_CALL = 3;
int ND_UNARY = 4;
int ND_BINARY = 5;
int ND_INDEX = 6;
int ND_FIELD = 7;
int ND_ARROW = 8;
int ND_ASSIGN = 9;

// Stmt kinds
int ST_RETURN = 0;
int ST_IF = 1;
int ST_WHILE = 2;
int ST_FOR = 3;
int ST_BREAK = 4;
int ST_CONTINUE = 5;
int ST_EXPR = 6;
int ST_VARDECL = 7;

// ---- Structs ----
struct Expr {
  int kind;
  int ival;
  int *sval;
  int *sval2;
  struct Expr *left;
  struct Expr *right;
  struct Expr **args;
  int nargs;
};

struct VarDecl {
  int *name;
  int *stype;
  int arr_size;
  struct Expr *init;
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
};

struct FuncDef {
  int *name;
  int **params;
  int nparams;
  struct Stmt **body;
  int nbody;
};

struct SDef {
  int *name;
  int **fields;
  int nfields;
};

struct SFieldInfo {
  int *name;
  int *stype;
  int is_ptr;
};

struct SDefInfo {
  int *name;
  struct SFieldInfo **flds;
  int nflds;
};

struct Program {
  struct SDef **structs;
  int nstructs;
  struct FuncDef **funcs;
  int nfuncs;
};

// ---- Globals ----
// Output buffer (byte buffer)
int *outbuf;
int outlen;
int outcap;

// Label counter
int label_id;

// String pool
int *sp_decoded[256];
int *sp_label[256];
int nsp;

// Loop stack
int *loop_brk[64];
int *loop_cont[64];
int nloop;

// Struct defs for codegen
int *cg_sname[64];
int **cg_sfields[64];
int cg_snfields[64];
int ncg_s;

// Token arrays
int tok_kind[16384];
int *tok_val[16384];
int tok_pos[16384];
int ntokens;

// Parser state
int cur_pos;

// Parser struct defs (with field type info)
struct SDefInfo *p_sdefs[64];
int np_sdefs;

// Local variable table (reset per function)
int *lv_name[256];
int *lv_stype[256];
int lv_isptr[256];
int nlv;

// Layout data
int *lay_name[256];
int lay_off[256];
int nlay;
int *lay_arr_name[64];
int lay_arr_count[64];
int nlay_arr;
int *lay_sv_name[64];
int *lay_sv_type[64];
int nlay_sv;
int lay_stack_size;

// ---- Utility functions ----

int my_fatal(int *msg) {
  printf("cc: %s\n", msg);
  exit(1);
  return 0;
}

int *my_malloc(int size) {
  int *p = malloc(size);
  if (p == 0) {
    my_fatal("out of memory");
  }
  return p;
}

int *my_strdup(int *s) {
  int len = strlen(s);
  int *p = my_malloc(len + 1);
  int i = 0;
  while (i <= len) {
    __write_byte(p, i, __read_byte(s, i));
    i = i + 1;
  }
  return p;
}

int my_strcmp(int *a, int *b) {
  return strcmp(a, b);
}

int my_strlen(int *s) {
  return strlen(s);
}

int my_atoi(int *s) {
  int val = 0;
  int i = 0;
  int neg = 0;
  if (__read_byte(s, 0) == '-') {
    neg = 1;
    i = 1;
  }
  while (__read_byte(s, i) >= '0' && __read_byte(s, i) <= '9') {
    val = val * 10 + __read_byte(s, i) - '0';
    i = i + 1;
  }
  if (neg) {
    val = 0 - val;
  }
  return val;
}

// ---- Output helpers ----

int emit_ch(int c) {
  if (outlen >= outcap) {
    outcap = outcap * 2;
    int *newbuf = my_malloc(outcap);
    int i = 0;
    while (i < outlen) {
      __write_byte(newbuf, i, __read_byte(outbuf, i));
      i = i + 1;
    }
    outbuf = newbuf;
  }
  __write_byte(outbuf, outlen, c);
  outlen = outlen + 1;
  return 0;
}

int emit_s(int *s) {
  int i = 0;
  while (__read_byte(s, i) != 0) {
    emit_ch(__read_byte(s, i));
    i = i + 1;
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

// Build a char* string from pieces
int *build_str2(int *a, int *b) {
  int la = my_strlen(a);
  int lb = my_strlen(b);
  int *buf = my_malloc(la + lb + 1);
  int i = 0;
  while (i < la) {
    __write_byte(buf, i, __read_byte(a, i));
    i = i + 1;
  }
  int j = 0;
  while (j < lb) {
    __write_byte(buf, i + j, __read_byte(b, j));
    j = j + 1;
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
    len = len + 1;
    n = n / 10;
  }
  int total = len;
  if (neg) {
    total = total + 1;
  }
  int *result = my_malloc(total + 1);
  int pos = 0;
  if (neg) {
    __write_byte(result, 0, '-');
    pos = 1;
  }
  int k = 0;
  while (k < len) {
    __write_byte(result, pos + k, buf[len - 1 - k]);
    k = k + 1;
  }
  __write_byte(result, total, 0);
  return result;
}

// Make a substring as a proper char* string
int *make_str(int *src, int start, int len) {
  int *buf = my_malloc(len + 1);
  int i = 0;
  while (i < len) {
    __write_byte(buf, i, __read_byte(src, start + i));
    i = i + 1;
  }
  __write_byte(buf, len, 0);
  return buf;
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
  return 0;
}

int is_alnum(int c) {
  return is_alpha(c) || is_digit(c);
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
  return 0;
}

int lex(int *src, int srclen) {
  // Strip comments into a buffer
  int *buf = my_malloc(srclen + 1);
  int j = 0;
  int i = 0;
  while (i < srclen) {
    if (__read_byte(src, i) == '/' && i + 1 < srclen && __read_byte(src, i + 1) == '/') {
      i = i + 2;
      while (i < srclen && __read_byte(src, i) != '\n') {
        i = i + 1;
      }
    } else if (__read_byte(src, i) == '/' && i + 1 < srclen && __read_byte(src, i + 1) == '*') {
      i = i + 2;
      while (i + 1 < srclen) {
        if (__read_byte(src, i) == '*' && __read_byte(src, i + 1) == '/') {
          break;
        }
        i = i + 1;
      }
      if (i + 1 < srclen) {
        i = i + 2;
      }
    } else {
      __write_byte(buf, j, __read_byte(src, i));
      j = j + 1;
      i = i + 1;
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
      i = i + 1;
      continue;
    }

    // Number
    if (is_digit(c)) {
      start = i;
      while (i < len && is_digit(__read_byte(buf, i))) {
        i = i + 1;
      }
      tok_kind[ntokens] = TK_NUM;
      tok_val[ntokens] = make_str(buf, start, i - start);
      tok_pos[ntokens] = start;
      ntokens = ntokens + 1;
      continue;
    }

    // Identifier / keyword
    if (is_alpha(c)) {
      start = i;
      while (i < len && is_alnum(__read_byte(buf, i))) {
        i = i + 1;
      }
      id_val = make_str(buf, start, i - start);
      if (is_keyword(id_val)) {
        tok_kind[ntokens] = TK_KW;
      } else {
        tok_kind[ntokens] = TK_ID;
      }
      tok_val[ntokens] = id_val;
      tok_pos[ntokens] = start;
      ntokens = ntokens + 1;
      continue;
    }

    // Character literal
    if (c == 39) {
      start = i;
      i = i + 1;
      ch = 0;
      if (__read_byte(buf, i) == '\\') {
        i = i + 1;
        ec = __read_byte(buf, i);
        if (ec == 'n') { ch = 10; }
        else if (ec == 't') { ch = 9; }
        else if (ec == 'r') { ch = 13; }
        else if (ec == '\\') { ch = 92; }
        else if (ec == 39) { ch = 39; }
        else if (ec == '0') { ch = 0; }
        else { my_fatal("bad char escape"); }
        i = i + 1;
      } else {
        ch = __read_byte(buf, i);
        i = i + 1;
      }
      if (i < len && __read_byte(buf, i) == 39) {
        i = i + 1;
      }
      tok_kind[ntokens] = TK_NUM;
      tok_val[ntokens] = int_to_str(ch);
      tok_pos[ntokens] = start;
      ntokens = ntokens + 1;
      continue;
    }

    // String literal
    if (c == '"') {
      start = i;
      i = i + 1;
      while (i < len && __read_byte(buf, i) != '"') {
        if (__read_byte(buf, i) == '\\') {
          i = i + 1;
        }
        i = i + 1;
      }
      if (i < len) {
        i = i + 1;
      }
      // Store without quotes
      tok_kind[ntokens] = TK_STR;
      tok_val[ntokens] = make_str(buf, start + 1, i - start - 2);
      tok_pos[ntokens] = start;
      ntokens = ntokens + 1;
      continue;
    }

    // Two-char operators
    if (i + 1 < len) {
      c1 = __read_byte(buf, i + 1);
      if (c == '-' && c1 == '>') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("->"); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '=' && c1 == '=') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("=="); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '!' && c1 == '=') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("!="); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '<' && c1 == '=') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("<="); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '>' && c1 == '=') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup(">="); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '&' && c1 == '&') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("&&"); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
      if (c == '|' && c1 == '|') { tok_kind[ntokens] = TK_OP; tok_val[ntokens] = my_strdup("||"); tok_pos[ntokens] = i; ntokens = ntokens + 1; i = i + 2; continue; }
    }

    // Single-char operators
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
        c == '<' || c == '>' || c == '=' || c == '!' || c == '&' ||
        c == '|' || c == '.' || c == ';' || c == ',' || c == '(' || c == ')' ||
        c == '{' || c == '}' || c == '[' || c == ']') {
      tok_kind[ntokens] = TK_OP;
      tok_val[ntokens] = make_str(buf, i, 1);
      tok_pos[ntokens] = i;
      ntokens = ntokens + 1;
      i = i + 1;
      continue;
    }

    printf("Unexpected char %d at %d\n", c, i);
    exit(1);
  }

  tok_kind[ntokens] = TK_EOF;
  tok_val[ntokens] = my_strdup("");
  tok_pos[ntokens] = len;
  ntokens = ntokens + 1;
  return 0;
}

// ---- Parser helpers ----

int p_match(int kind, int *val) {
  if (tok_kind[cur_pos] != kind) { return 0; }
  if (val != 0) {
    if (my_strcmp(tok_val[cur_pos], val) != 0) { return 0; }
  }
  return 1;
}

int *p_eat(int kind, int *val) {
  if (tok_kind[cur_pos] != kind) {
    printf("Expected kind %d, got %d at pos %d\n", kind, tok_kind[cur_pos], tok_pos[cur_pos]);
    exit(1);
  }
  if (val != 0 && my_strcmp(tok_val[cur_pos], val) != 0) {
    printf("Expected '%s', got '%s' at pos %d\n", val, tok_val[cur_pos], tok_pos[cur_pos]);
    exit(1);
  }
  int *v = tok_val[cur_pos];
  cur_pos = cur_pos + 1;
  return v;
}

int *find_lv_stype(int *name) {
  int i = 0;
  while (i < nlv) {
    if (my_strcmp(lv_name[i], name) == 0) {
      return lv_stype[i];
    }
    i = i + 1;
  }
  return 0;
}

int add_lv(int *name, int *stype, int is_ptr) {
  lv_name[nlv] = my_strdup(name);
  if (stype != 0) {
    lv_stype[nlv] = my_strdup(stype);
  } else {
    lv_stype[nlv] = 0;
  }
  lv_isptr[nlv] = is_ptr;
  nlv = nlv + 1;
  return 0;
}

struct SDefInfo *find_sdef(int *name) {
  int i = 0;
  while (i < np_sdefs) {
    struct SDefInfo *sdi = p_sdefs[i];
    if (my_strcmp(sdi->name, name) == 0) {
      return sdi;
    }
    i = i + 1;
  }
  return 0;
}

int *field_stype(int *sname, int *fname) {
  struct SDefInfo *sd = find_sdef(sname);
  if (sd == 0) { my_fatal("unknown struct in field_stype"); }
  int i = 0;
  while (i < sd->nflds) {
    struct SFieldInfo *fi = sd->flds[i];
    if (my_strcmp(fi->name, fname) == 0) {
      if (fi->stype != 0) { return fi->stype; }
      my_fatal("field is not a struct type");
    }
    i = i + 1;
  }
  my_fatal("struct has no such field");
  return 0;
}

// ---- AST constructors ----

struct Expr *new_num(int val) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_NUM;
  e->ival = val;
  return e;
}

struct Expr *new_var(int *name) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_VAR;
  e->sval = my_strdup(name);
  return e;
}

struct Expr *new_strlit(int *val) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_STRLIT;
  e->sval = my_strdup(val);
  return e;
}

struct Expr *new_call(int *name, struct Expr **args, int nargs) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_CALL;
  e->sval = my_strdup(name);
  e->args = args;
  e->nargs = nargs;
  return e;
}

struct Expr *new_unary(int op, struct Expr *rhs) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_UNARY;
  e->ival = op;
  e->left = rhs;
  return e;
}

struct Expr *new_binary(int *op, struct Expr *lhs, struct Expr *rhs) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_BINARY;
  e->sval2 = my_strdup(op);
  e->left = lhs;
  e->right = rhs;
  return e;
}

struct Expr *new_index(struct Expr *base, struct Expr *idx) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_INDEX;
  e->left = base;
  e->right = idx;
  return e;
}

struct Expr *new_field(struct Expr *obj, int *field, int *stype) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_FIELD;
  e->left = obj;
  e->sval = my_strdup(field);
  e->sval2 = my_strdup(stype);
  return e;
}

struct Expr *new_arrow(struct Expr *obj, int *field, int *stype) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_ARROW;
  e->left = obj;
  e->sval = my_strdup(field);
  e->sval2 = my_strdup(stype);
  return e;
}

struct Expr *new_assign(struct Expr *target, struct Expr *rhs) {
  struct Expr *e = my_malloc(64);
  e->kind = ND_ASSIGN;
  e->left = target;
  e->right = rhs;
  return e;
}

struct Stmt *new_return_s(struct Expr *e) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_RETURN;
  s->expr = e;
  return s;
}

struct Stmt *new_if_s(struct Expr *cond, struct Stmt **body, int nbody, struct Stmt **body2, int nbody2) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_IF;
  s->expr = cond;
  s->body = body;
  s->nbody = nbody;
  s->body2 = body2;
  s->nbody2 = nbody2;
  return s;
}

struct Stmt *new_while_s(struct Expr *cond, struct Stmt **body, int nbody) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_WHILE;
  s->expr = cond;
  s->body = body;
  s->nbody = nbody;
  return s;
}

struct Stmt *new_for_s(struct Stmt *init, struct Expr *cond, struct Expr *post, struct Stmt **body, int nbody) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_FOR;
  s->init = init;
  s->expr = cond;
  s->expr2 = post;
  s->body = body;
  s->nbody = nbody;
  return s;
}

struct Stmt *new_break_s() {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_BREAK;
  return s;
}

struct Stmt *new_continue_s() {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_CONTINUE;
  return s;
}

struct Stmt *new_expr_s(struct Expr *e) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_EXPR;
  s->expr = e;
  return s;
}

struct Stmt *new_vardecl_s(struct VarDecl **decls, int ndecls) {
  struct Stmt *s = my_malloc(80);
  s->kind = ST_VARDECL;
  s->decls = decls;
  s->ndecls = ndecls;
  return s;
}

// ---- Parser ----

int *parse_base_type() {
  if (p_match(TK_KW, "int")) {
    p_eat(TK_KW, "int");
    return 0;
  }
  if (p_match(TK_KW, "struct")) {
    p_eat(TK_KW, "struct");
    int *name = p_eat(TK_ID, 0);
    return my_strdup(name);
  }
  printf("Expected type at pos %d\n", tok_pos[cur_pos]);
  exit(1);
  return 0;
}

struct Stmt **parse_block(int *out_len) {
  p_eat(TK_OP, "{");
  struct Stmt **stmts = my_malloc(512 * 8);
  int n = 0;
  while (!p_match(TK_OP, "}")) {
    stmts[n] = parse_stmt();
    n = n + 1;
  }
  p_eat(TK_OP, "}");
  *out_len = n;
  return stmts;
}

struct VarDecl *make_vd(int *name, int *stype, int arr_size, struct Expr *init) {
  struct VarDecl *vd = my_malloc(32);
  vd->name = name;
  vd->stype = stype;
  vd->arr_size = arr_size;
  vd->init = init;
  return vd;
}

struct Stmt *parse_vardecl_stmt() {
  int *stype = parse_base_type();
  struct VarDecl **decls = my_malloc(64 * 8);
  int ndecls = 0;

  while (1) {
    int is_ptr = 0;
    while (p_match(TK_OP, "*")) {
      p_eat(TK_OP, "*");
      is_ptr = 1;
    }
    int *name = my_strdup(p_eat(TK_ID, 0));
    int arr_size = 0 - 1;
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      arr_size = my_atoi(p_eat(TK_NUM, 0));
      p_eat(TK_OP, "]");
    }
    struct Expr *init = 0;
    int *decl_stype = 0;
    if (stype != 0 && is_ptr == 0 && arr_size < 0) {
      decl_stype = my_strdup(stype);
    }
    if (decl_stype == 0 && arr_size < 0 && p_match(TK_OP, "=")) {
      p_eat(TK_OP, "=");
      init = parse_expr(0);
    }
    decls[ndecls] = make_vd(my_strdup(name), decl_stype, arr_size, init);
    ndecls = ndecls + 1;
    if (stype != 0) {
      add_lv(name, stype, is_ptr);
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
  if (my_strcmp(op, "&") == 0) { return 4; }
  if (my_strcmp(op, "==") == 0 || my_strcmp(op, "!=") == 0) { return 5; }
  if (my_strcmp(op, "<") == 0 || my_strcmp(op, "<=") == 0 ||
      my_strcmp(op, ">") == 0 || my_strcmp(op, ">=") == 0) { return 6; }
  if (my_strcmp(op, "+") == 0 || my_strcmp(op, "-") == 0) { return 7; }
  if (my_strcmp(op, "*") == 0 || my_strcmp(op, "/") == 0 || my_strcmp(op, "%") == 0) { return 8; }
  return 0 - 1;
}

struct Expr *parse_expr(int min_prec) {
  struct Expr *e = parse_unary();
  struct Expr *rhs = 0;

  while (1) {
    int k = tok_kind[cur_pos];
    int *v = tok_val[cur_pos];

    if (k == TK_OP && my_strcmp(v, "=") == 0 && min_prec <= 0) {
      p_eat(TK_OP, "=");
      rhs = parse_expr(0);
      e = new_assign(e, rhs);
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

struct Expr *parse_unary() {
  if (p_match(TK_OP, "-") || p_match(TK_OP, "!") || p_match(TK_OP, "*") || p_match(TK_OP, "&")) {
    int op = __read_byte(tok_val[cur_pos], 0);
    p_eat(TK_OP, 0);
    struct Expr *rhs = parse_unary();
    return new_unary(op, rhs);
  }
  return parse_primary();
}

struct Expr *parse_primary() {
  int k = tok_kind[cur_pos];
  int *v = tok_val[cur_pos];
  struct Expr *e;
  int *field = 0;
  int *st = 0;

  if (k == TK_NUM) {
    p_eat(TK_NUM, 0);
    e = new_num(my_atoi(v));
  } else if (k == TK_STR) {
    p_eat(TK_STR, 0);
    e = new_strlit(v);
  } else if (k == TK_ID) {
    int *name = my_strdup(p_eat(TK_ID, 0));
    if (p_match(TK_OP, "(")) {
      p_eat(TK_OP, "(");
      struct Expr **args = my_malloc(64 * 8);
      int nargs = 0;
      if (!p_match(TK_OP, ")")) {
        while (1) {
          args[nargs] = parse_expr(0);
          nargs = nargs + 1;
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
  } else if (p_match(TK_OP, "(")) {
    p_eat(TK_OP, "(");
    e = parse_expr(0);
    p_eat(TK_OP, ")");
  } else {
    printf("Unexpected token '%s' at %d\n", v, tok_pos[cur_pos]);
    exit(1);
    return 0;
  }

  // Postfix: [], ., ->
  while (p_match(TK_OP, "[") || p_match(TK_OP, ".") || p_match(TK_OP, "->")) {
    if (p_match(TK_OP, "[")) {
      p_eat(TK_OP, "[");
      struct Expr *idx = parse_expr(0);
      p_eat(TK_OP, "]");
      e = new_index(e, idx);
    } else if (p_match(TK_OP, ".")) {
      p_eat(TK_OP, ".");
      field = my_strdup(p_eat(TK_ID, 0));
      st = 0;
      if (e->kind == ND_VAR) {
        st = find_lv_stype(e->sval);
      } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
        st = field_stype(e->sval2, e->sval);
      }
      if (st == 0) { my_fatal("cannot resolve struct type for '.'"); }
      e = new_field(e, field, st);
    } else {
      p_eat(TK_OP, "->");
      field = my_strdup(p_eat(TK_ID, 0));
      st = 0;
      if (e->kind == ND_VAR) {
        st = find_lv_stype(e->sval);
      } else if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
        st = field_stype(e->sval2, e->sval);
      }
      if (st == 0) { my_fatal("cannot resolve struct type for '->'"); }
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

  if (p_match(TK_KW, "return")) {
    p_eat(TK_KW, "return");
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
    then_body = parse_block(&then_len);
    else_body = 0;
    else_len = 0;
    if (p_match(TK_KW, "else")) {
      p_eat(TK_KW, "else");
      else_body = parse_block(&else_len);
    }
    return new_if_s(cond, then_body, then_len, else_body, else_len);
  }

  if (p_match(TK_KW, "while")) {
    p_eat(TK_KW, "while");
    p_eat(TK_OP, "(");
    cond = parse_expr(0);
    p_eat(TK_OP, ")");
    blen = 0;
    body = parse_block(&blen);
    return new_while_s(cond, body, blen);
  }

  if (p_match(TK_KW, "for")) {
    p_eat(TK_KW, "for");
    p_eat(TK_OP, "(");

    init = 0;
    if (p_match(TK_KW, "int") || p_match(TK_KW, "struct")) {
      init = parse_vardecl_stmt();
    } else if (p_match(TK_OP, ";")) {
      p_eat(TK_OP, ";");
    } else {
      e = parse_expr(0);
      p_eat(TK_OP, ";");
      init = new_expr_s(e);
    }

    cond = 0;
    if (!p_match(TK_OP, ";")) {
      cond = parse_expr(0);
    }
    p_eat(TK_OP, ";");

    post = 0;
    if (!p_match(TK_OP, ")")) {
      post = parse_expr(0);
    }
    p_eat(TK_OP, ")");

    blen = 0;
    body = parse_block(&blen);
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

  if (p_match(TK_KW, "int") || p_match(TK_KW, "struct")) {
    return parse_vardecl_stmt();
  }

  e = parse_expr(0);
  p_eat(TK_OP, ";");
  return new_expr_s(e);
}

struct SDef *parse_struct_def() {
  p_eat(TK_KW, "struct");
  int *name = my_strdup(p_eat(TK_ID, 0));
  p_eat(TK_OP, "{");

  int **fields = my_malloc(64 * 8);
  struct SFieldInfo **finfo = my_malloc(64 * 8);
  int nf = 0;

  while (!p_match(TK_OP, "}")) {
    int *ftype = parse_base_type();
    int is_ptr = 0;
    while (p_match(TK_OP, "*")) {
      p_eat(TK_OP, "*");
      is_ptr = 1;
    }
    int *fname = my_strdup(p_eat(TK_ID, 0));
    p_eat(TK_OP, ";");

    fields[nf] = fname;
    struct SFieldInfo *fi = my_malloc(24);
    fi->name = my_strdup(fname);
    if (ftype != 0) {
      fi->stype = my_strdup(ftype);
    } else {
      fi->stype = 0;
    }
    fi->is_ptr = is_ptr;
    finfo[nf] = fi;
    nf = nf + 1;
  }
  p_eat(TK_OP, "}");
  p_eat(TK_OP, ";");

  // Register in parser struct defs
  struct SDefInfo *sdi = my_malloc(24);
  sdi->name = my_strdup(name);
  sdi->flds = finfo;
  sdi->nflds = nf;
  p_sdefs[np_sdefs] = sdi;
  np_sdefs = np_sdefs + 1;

  struct SDef *sd = my_malloc(24);
  sd->name = name;
  sd->fields = fields;
  sd->nfields = nf;
  return sd;
}

struct FuncDef *parse_func() {
  nlv = 0;
  parse_base_type();
  while (p_match(TK_OP, "*")) { p_eat(TK_OP, "*"); }
  int *name = my_strdup(p_eat(TK_ID, 0));
  p_eat(TK_OP, "(");

  int **params = my_malloc(64 * 8);
  int np = 0;

  if (!p_match(TK_OP, ")")) {
    while (1) {
      int *stype = parse_base_type();
      int is_ptr = 0;
      while (p_match(TK_OP, "*")) {
        p_eat(TK_OP, "*");
        is_ptr = 1;
      }
      int *pname = my_strdup(p_eat(TK_ID, 0));
      params[np] = my_strdup(pname);
      np = np + 1;
      if (stype != 0) {
        add_lv(pname, stype, is_ptr);
      }
      if (p_match(TK_OP, ",")) {
        p_eat(TK_OP, ",");
        continue;
      }
      break;
    }
  }
  p_eat(TK_OP, ")");

  int blen = 0;
  struct Stmt **body = parse_block(&blen);

  struct FuncDef *fd = my_malloc(40);
  fd->name = name;
  fd->params = params;
  fd->nparams = np;
  fd->body = body;
  fd->nbody = blen;
  return fd;
}

struct Program *parse_program() {
  cur_pos = 0;
  np_sdefs = 0;

  struct SDef **structs = my_malloc(64 * 8);
  int ns = 0;
  struct FuncDef **funcs = my_malloc(256 * 8);
  int nf = 0;

  while (!p_match(TK_EOF, 0)) {
    if (p_match(TK_KW, "struct")) {
      int saved = cur_pos;
      p_eat(TK_KW, "struct");
      p_eat(TK_ID, 0);
      if (p_match(TK_OP, "{")) {
        cur_pos = saved;
        structs[ns] = parse_struct_def();
        ns = ns + 1;
      } else {
        cur_pos = saved;
        funcs[nf] = parse_func();
        nf = nf + 1;
      }
    } else {
      funcs[nf] = parse_func();
      nf = nf + 1;
    }
  }

  struct Program *p = my_malloc(32);
  p->structs = structs;
  p->nstructs = ns;
  p->funcs = funcs;
  p->nfuncs = nf;
  return p;
}

// ---- Codegen ----

int *cg_new_label(int *base) {
  label_id = label_id + 1;
  int *num = int_to_str(label_id);
  int *tmp = build_str2("L_", base);
  int *tmp2 = build_str2(tmp, "_");
  return build_str2(tmp2, num);
}

int cg_find_slot(int *name) {
  int i = 0;
  while (i < nlay) {
    if (my_strcmp(lay_name[i], name) == 0) {
      return lay_off[i];
    }
    i = i + 1;
  }
  return 0 - 1;
}

int cg_is_array(int *name) {
  i = 0;
  while (i < nlay_arr) {
    if (my_strcmp(lay_arr_name[i], name) == 0) { return 1; }
    i = i + 1;
  }
  return 0;
}

int cg_is_structvar(int *name) {
  i = 0;
  while (i < nlay_sv) {
    if (my_strcmp(lay_sv_name[i], name) == 0) { return 1; }
    i = i + 1;
  }
  return 0;
}

int cg_field_index(int *sname, int *fname) {
  i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      int j = 0;
      while (j < cg_snfields[i]) {
        if (my_strcmp(cg_sfields[i][j], fname) == 0) {
          return j;
        }
        j = j + 1;
      }
      my_fatal("field not found in codegen");
    }
    i = i + 1;
  }
  my_fatal("struct not found in codegen");
  return 0 - 1;
}

int cg_struct_nfields(int *sname) {
  i = 0;
  while (i < ncg_s) {
    if (my_strcmp(cg_sname[i], sname) == 0) {
      return cg_snfields[i];
    }
    i = i + 1;
  }
  my_fatal("struct not found for nfields");
  return 0;
}

int *cg_intern_string(int *decoded) {
  i = 0;
  while (i < nsp) {
    if (my_strcmp(sp_decoded[i], decoded) == 0) {
      return sp_label[i];
    }
    i = i + 1;
  }
  num = int_to_str(nsp + 1);
  int *lab = build_str2("l_.str_", num);
  sp_decoded[nsp] = my_strdup(decoded);
  sp_label[nsp] = lab;
  nsp = nsp + 1;
  return lab;
}

// Decode C escape sequences in string literal
int *cg_decode_string(int *lit) {
  int slen = my_strlen(lit);
  int *buf = my_malloc(slen + 1);
  j = 0;
  i = 0;
  while (i < slen) {
    int c = __read_byte(lit, i);
    if (c != '\\') {
      __write_byte(buf, j, c);
      j = j + 1;
      i = i + 1;
      continue;
    }
    i = i + 1;
    int ec = __read_byte(lit, i);
    if (ec == 'n') { __write_byte(buf, j, 10); }
    else if (ec == 't') { __write_byte(buf, j, 9); }
    else if (ec == 'r') { __write_byte(buf, j, 13); }
    else if (ec == '\\') { __write_byte(buf, j, 92); }
    else if (ec == '"') { __write_byte(buf, j, 34); }
    else if (ec == '0') { __write_byte(buf, j, 0); }
    else { my_fatal("bad escape in string literal"); }
    j = j + 1;
    i = i + 1;
  }
  __write_byte(buf, j, 0);
  return buf;
}

// Escape string for .asciz directive
int cg_emit_escaped_string(int *s) {
  i = 0;
  while (1) {
    c = __read_byte(s, i);
    if (c == 0) { break; }
    if (c == '\\') { emit_ch('\\'); emit_ch('\\'); }
    else if (c == '"') { emit_ch('\\'); emit_ch('"'); }
    else if (c == 10) { emit_ch('\\'); emit_ch('n'); }
    else if (c == 9) { emit_ch('\\'); emit_ch('t'); }
    else if (c == 13) { emit_ch('\\'); emit_ch('r'); }
    else { emit_ch(c); }
    i = i + 1;
  }
  return 0;
}

// Layout computation
int lay_add_slot(int *name, int off) {
  lay_name[nlay] = my_strdup(name);
  lay_off[nlay] = off;
  nlay = nlay + 1;
  return 0;
}

int lay_walk_stmts(struct Stmt **stmts, int nstmts, int *offset) {
  i = 0;
  while (i < nstmts) {
    struct Stmt *st = stmts[i];
    if (st->kind == ST_VARDECL) {
      j = 0;
      while (j < st->ndecls) {
        struct VarDecl *vd = st->decls[j];
        if (cg_find_slot(vd->name) >= 0) {
          my_fatal("duplicate variable");
        }
        if (vd->stype != 0) {
          nf = cg_struct_nfields(vd->stype);
          *offset = *offset + nf * 8;
          lay_sv_name[nlay_sv] = my_strdup(vd->name);
          lay_sv_type[nlay_sv] = my_strdup(vd->stype);
          nlay_sv = nlay_sv + 1;
        } else if (vd->arr_size >= 0) {
          *offset = *offset + vd->arr_size * 8;
          lay_arr_name[nlay_arr] = my_strdup(vd->name);
          lay_arr_count[nlay_arr] = vd->arr_size;
          nlay_arr = nlay_arr + 1;
        } else {
          *offset = *offset + 8;
        }
        lay_add_slot(vd->name, *offset);
        j = j + 1;
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
    }
    i = i + 1;
  }
  return 0;
}

int layout_func(struct FuncDef *f) {
  nlay = 0;
  nlay_arr = 0;
  nlay_sv = 0;
  int offset = 0;

  i = 0;
  while (i < f->nparams) {
    offset = offset + 8;
    lay_add_slot(f->params[i], offset);
    i = i + 1;
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
    if (off < 0) {
      printf("Unknown variable: %s\n", e->sval);
      exit(1);
    }
    emit_s("\tsub\tx0, x29, #");
    emit_num(off);
    emit_ch('\n');
    return 0;
  }
  if (e->kind == ND_UNARY && e->ival == '*') {
    gen_value(e->left);
    return 0;
  }
  if (e->kind == ND_INDEX) {
    gen_value(e->left);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->right);
    emit_line("\tlsl\tx0, x0, #3");
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tadd\tx0, x1, x0");
    return 0;
  }
  if (e->kind == ND_FIELD) {
    gen_addr(e->left);
    fi = cg_field_index(e->sval2, e->sval);
    if (fi > 0) {
      emit_s("\tadd\tx0, x0, #");
      emit_num(fi * 8);
      emit_ch('\n');
    }
    return 0;
  }
  if (e->kind == ND_ARROW) {
    gen_value(e->left);
    fi = cg_field_index(e->sval2, e->sval);
    if (fi > 0) {
      emit_s("\tadd\tx0, x0, #");
      emit_num(fi * 8);
      emit_ch('\n');
    }
    return 0;
  }
  my_fatal("not an lvalue");
  return 0;
}

int gen_value(struct Expr *e) {
  int unary_op = 0;
  int *bin_op = 0;
  int *end_l = 0;
  int *rhs_l = 0;
  int var_space = 0;
  if (e->kind == ND_NUM) {
    int val = e->ival;
    if (val >= -65535 && val <= 65535) {
      emit_s("\tmov\tx0, #");
      emit_num(val);
      emit_ch('\n');
    } else {
      int lo = val & 65535;
      int hi = (val / 65536) & 65535;
      emit_s("\tmovz\tx0, #");
      emit_unum(lo);
      emit_ch('\n');
      if (hi != 0) {
        emit_s("\tmovk\tx0, #");
        emit_unum(hi);
        emit_s(", lsl #16\n");
      }
    }
    return 0;
  }

  if (e->kind == ND_VAR) {
    gen_addr(e);
    if (cg_is_array(e->sval) == 0 && cg_is_structvar(e->sval) == 0) {
      emit_line("\tldr\tx0, [x0]");
    }
    return 0;
  }

  if (e->kind == ND_FIELD || e->kind == ND_ARROW) {
    gen_addr(e);
    emit_line("\tldr\tx0, [x0]");
    return 0;
  }

  if (e->kind == ND_INDEX) {
    gen_addr(e);
    emit_line("\tldr\tx0, [x0]");
    return 0;
  }

  if (e->kind == ND_ASSIGN) {
    gen_addr(e->left);
    emit_line("\tstr\tx0, [sp, #-16]!");
    gen_value(e->right);
    emit_line("\tldr\tx1, [sp], #16");
    emit_line("\tstr\tx0, [x1]");
    return 0;
  }

  if (e->kind == ND_STRLIT) {
    int *decoded = cg_decode_string(e->sval);
    lab = cg_intern_string(decoded);
    emit_s("\tadrp\tx0, ");
    emit_s(lab);
    emit_line("@PAGE");
    emit_s("\tadd\tx0, x0, ");
    emit_s(lab);
    emit_line("@PAGEOFF");
    return 0;
  }

  if (e->kind == ND_UNARY) {
    unary_op = e->ival;
    if (unary_op == '&') {
      gen_addr(e->left);
      return 0;
    }
    if (unary_op == '*') {
      gen_value(e->left);
      emit_line("\tldr\tx0, [x0]");
      return 0;
    }
    gen_value(e->left);
    if (unary_op == '-') {
      emit_line("\tneg\tx0, x0");
    } else if (unary_op == '!') {
      emit_line("\tcmp\tx0, #0");
      emit_line("\tcset\tx0, eq");
    }
    return 0;
  }

  if (e->kind == ND_BINARY) {
    bin_op = e->sval2;

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

    if (my_strcmp(bin_op, "+") == 0) { emit_line("\tadd\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "-") == 0) { emit_line("\tsub\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "*") == 0) { emit_line("\tmul\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "/") == 0) { emit_line("\tsdiv\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "&") == 0) { emit_line("\tand\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "|") == 0) { emit_line("\torr\tx0, x1, x0"); }
    else if (my_strcmp(bin_op, "%") == 0) {
      emit_line("\tsdiv\tx9, x1, x0");
      emit_line("\tmsub\tx0, x9, x0, x1");
    }
    else if (my_strcmp(bin_op, "==") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, eq"); }
    else if (my_strcmp(bin_op, "!=") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, ne"); }
    else if (my_strcmp(bin_op, "<") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, lt"); }
    else if (my_strcmp(bin_op, "<=") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, le"); }
    else if (my_strcmp(bin_op, ">") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, gt"); }
    else if (my_strcmp(bin_op, ">=") == 0) { emit_line("\tcmp\tx1, x0"); emit_line("\tcset\tx0, ge"); }
    return 0;
  }

  if (e->kind == ND_CALL) {
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

    // printf: Apple ARM64 variadic ABI
    if (my_strcmp(name, "printf") == 0) {
      if (nargs < 1) { my_fatal("printf needs args"); }
      int n_var = nargs - 1;
      if (n_var > 0) {
        var_space = ((n_var * 8 + 15) / 16) * 16;
        emit_s("\tsub\tsp, sp, #");
        emit_num(var_space);
        emit_ch('\n');
        int vi = 0;
        while (vi < n_var) {
          gen_value(e->args[vi + 1]);
          emit_s("\tstr\tx0, [sp, #");
          emit_num(vi * 8);
          emit_line("]");
          vi = vi + 1;
        }
      }
      gen_value(e->args[0]);
      emit_line("\tbl\t_printf");
      if (n_var > 0) {
        var_space = ((n_var * 8 + 15) / 16) * 16;
        emit_s("\tadd\tsp, sp, #");
        emit_num(var_space);
        emit_ch('\n');
      }
      return 0;
    }

    // Regular function call
    if (nargs > 8) { my_fatal("too many args"); }
    int ai = 0;
    while (ai < nargs) {
      gen_value(e->args[ai]);
      emit_line("\tstr\tx0, [sp, #-16]!");
      ai = ai + 1;
    }
    ai = 0;
    while (ai < nargs) {
      int disp = (nargs - 1 - ai) * 16;
      emit_s("\tldr\tx");
      emit_num(ai);
      emit_s(", [sp, #");
      emit_num(disp);
      emit_line("]");
      ai = ai + 1;
    }
    emit_s("\tadd\tsp, sp, #");
    emit_num(nargs * 16);
    emit_ch('\n');
    emit_s("\tbl\t_");
    emit_line(name);
    return 0;
  }

  my_fatal("unsupported expression");
  return 0;
}

int gen_block(struct Stmt **stmts, int nstmts, int *ret_label) {
  i = 0;
  while (i < nstmts) {
    gen_stmt(stmts[i], ret_label);
    i = i + 1;
  }
  return 0;
}

int gen_stmt(struct Stmt *st, int *ret_label) {
  int *else_l = 0;
  end_l = 0;
  int *start_l = 0;
  int *post_l = 0;
  if (st->kind == ST_RETURN) {
    gen_value(st->expr);
    emit_s("\tb\t"); emit_line(ret_label);
    return 0;
  }

  if (st->kind == ST_EXPR) {
    gen_value(st->expr);
    return 0;
  }

  if (st->kind == ST_VARDECL) {
    i = 0;
    while (i < st->ndecls) {
      vd = st->decls[i];
      if (vd->stype != 0) { i = i + 1; continue; }
      if (vd->arr_size >= 0) { i = i + 1; continue; }
      off = cg_find_slot(vd->name);
      if (vd->init != 0) {
        gen_value(vd->init);
      } else {
        emit_line("\tmov\tx0, #0");
      }
      emit_s("\tstr\tx0, [x29, #-");
      emit_num(off);
      emit_line("]");
      i = i + 1;
    }
    return 0;
  }

  if (st->kind == ST_IF) {
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

  if (st->kind == ST_WHILE) {
    start_l = cg_new_label("while_start");
    end_l = cg_new_label("while_end");
    loop_brk[nloop] = end_l;
    loop_cont[nloop] = start_l;
    nloop = nloop + 1;

    emit_s(start_l); emit_line(":");
    gen_value(st->expr);
    emit_line("\tcmp\tx0, #0");
    emit_s("\tb.eq\t"); emit_line(end_l);
    gen_block(st->body, st->nbody, ret_label);
    emit_s("\tb\t"); emit_line(start_l);
    emit_s(end_l); emit_line(":");

    nloop = nloop - 1;
    return 0;
  }

  if (st->kind == ST_FOR) {
    start_l = cg_new_label("for_start");
    post_l = cg_new_label("for_post");
    end_l = cg_new_label("for_end");

    if (st->init != 0) {
      gen_stmt(st->init, ret_label);
    }

    loop_brk[nloop] = end_l;
    loop_cont[nloop] = post_l;
    nloop = nloop + 1;

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

    nloop = nloop - 1;
    return 0;
  }

  if (st->kind == ST_BREAK) {
    emit_s("\tb\t"); emit_line(loop_brk[nloop - 1]);
    return 0;
  }

  if (st->kind == ST_CONTINUE) {
    emit_s("\tb\t"); emit_line(loop_cont[nloop - 1]);
    return 0;
  }

  my_fatal("unsupported statement");
  return 0;
}

int gen_func(struct FuncDef *f) {
  layout_func(f);
  int *ret_label = cg_new_label("ret");

  emit_ch('\n');
  emit_line("\t.p2align\t2");
  emit_s("\t.globl\t_"); emit_line(f->name);
  emit_s("_"); emit_s(f->name); emit_line(":");
  emit_line("\tstp\tx29, x30, [sp, #-16]!");
  emit_line("\tmov\tx29, sp");
  if (lay_stack_size > 0) {
    emit_s("\tsub\tsp, sp, #");
    emit_num(lay_stack_size);
    emit_ch('\n');
  }

  i = 0;
  while (i < f->nparams) {
    off = cg_find_slot(f->params[i]);
    emit_s("\tstr\tx");
    emit_num(i);
    emit_s(", [x29, #-");
    emit_num(off);
    emit_line("]");
    i = i + 1;
  }

  gen_block(f->body, f->nbody, ret_label);

  emit_line("\tmov\tw0, #0");
  emit_s(ret_label); emit_line(":");
  if (lay_stack_size > 0) {
    emit_s("\tadd\tsp, sp, #");
    emit_num(lay_stack_size);
    emit_ch('\n');
  }
  emit_line("\tldp\tx29, x30, [sp], #16");
  emit_line("\tret");
  return 0;
}

int codegen(struct Program *prog) {
  label_id = 0;
  nsp = 0;
  nloop = 0;
  ncg_s = 0;

  // Register struct definitions
  i = 0;
  while (i < prog->nstructs) {
    struct SDef *sd = prog->structs[i];
    cg_sname[ncg_s] = sd->name;
    cg_sfields[ncg_s] = sd->fields;
    cg_snfields[ncg_s] = sd->nfields;
    ncg_s = ncg_s + 1;
    i = i + 1;
  }

  emit_line("\t.text");

  i = 0;
  while (i < prog->nfuncs) {
    gen_func(prog->funcs[i]);
    i = i + 1;
  }

  // String pool
  if (nsp > 0) {
    emit_ch('\n');
    emit_line("\t.section\t__TEXT,__cstring,cstring_literals");
    i = 0;
    while (i < nsp) {
      emit_s(sp_label[i]); emit_line(":");
      emit_s("\t.asciz\t\"");
      cg_emit_escaped_string(sp_decoded[i]);
      emit_line("\"");
      i = i + 1;
    }
  }

  return 0;
}

// ---- Driver ----

int main(int argc, int *argv) {
  int *out_path = "a.out";
  int *c_path = 0;

  i = 1;
  while (i < argc) {
    int *arg = argv[i];
    if (my_strcmp(arg, "-o") == 0) {
      if (i + 1 >= argc) { my_fatal("missing arg for -o"); }
      i = i + 1;
      out_path = argv[i];
    } else if (__read_byte(arg, 0) == '-') {
      printf("Unknown option: %s\n", arg);
      exit(1);
    } else {
      if (c_path != 0) { my_fatal("multiple input files"); }
      c_path = arg;
    }
    i = i + 1;
  }

  if (c_path == 0) {
    printf("Usage: cc [-o output] program.c\n");
    return 2;
  }

  // Read source file
  int *f = fopen(c_path, "r");
  if (f == 0) {
    printf("Cannot open: %s\n", c_path);
    return 1;
  }
  int *srcbuf = my_malloc(1000 * 1000);
  int srclen = 0;
  int ch = fgetc(f);
  while (ch != 0 - 1) {
    __write_byte(srcbuf, srclen, ch);
    srclen = srclen + 1;
    ch = fgetc(f);
  }
  __write_byte(srcbuf, srclen, 0);
  fclose(f);

  // Strip preprocessor lines
  int *cleaned = my_malloc(srclen + 1);
  int ci = 0;
  int co = 0;
  while (ci < srclen) {
    // Skip leading whitespace to check for #
    int si = ci;
    while (si < srclen && (__read_byte(srcbuf, si) == ' ' || __read_byte(srcbuf, si) == '\t')) {
      si = si + 1;
    }
    if (si < srclen && __read_byte(srcbuf, si) == '#') {
      // Skip entire line
      while (ci < srclen && __read_byte(srcbuf, ci) != '\n') {
        ci = ci + 1;
      }
      if (ci < srclen) {
        __write_byte(cleaned, co, '\n');
        co = co + 1;
        ci = ci + 1;
      }
    } else {
      // Copy line
      while (ci < srclen && __read_byte(srcbuf, ci) != '\n') {
        __write_byte(cleaned, co, __read_byte(srcbuf, ci));
        co = co + 1;
        ci = ci + 1;
      }
      if (ci < srclen) {
        __write_byte(cleaned, co, '\n');
        co = co + 1;
        ci = ci + 1;
      }
    }
  }
  __write_byte(cleaned, co, 0);

  // Lex
  lex(cleaned, co);

  // Parse
  struct Program *prog = parse_program();

  // Codegen
  outcap = 1000 * 100;
  outbuf = my_malloc(outcap);
  outlen = 0;
  codegen(prog);

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
    pi = pi - 1;
  }
  int k = 0;
  if (dot >= 0) {
    k = 0;
    while (k < dot) {
      __write_byte(s_path, k, __read_byte(c_path, k));
      k = k + 1;
    }
    __write_byte(s_path, dot, '.');
    __write_byte(s_path, dot + 1, 's');
    __write_byte(s_path, dot + 2, 0);
  } else {
    k = 0;
    while (k < pathlen) {
      __write_byte(s_path, k, __read_byte(c_path, k));
      k = k + 1;
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
    wi = wi + 1;
  }
  fclose(sf);

  // Run clang
  int *cmd = my_malloc(4096);
  int cpos = 0;
  int *clang_str = "clang ";
  int ci2 = 0;
  while (__read_byte(clang_str, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(clang_str, ci2));
    cpos = cpos + 1;
    ci2 = ci2 + 1;
  }
  ci2 = 0;
  while (__read_byte(s_path, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(s_path, ci2));
    cpos = cpos + 1;
    ci2 = ci2 + 1;
  }
  int *o_str = " -o ";
  ci2 = 0;
  while (__read_byte(o_str, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(o_str, ci2));
    cpos = cpos + 1;
    ci2 = ci2 + 1;
  }
  ci2 = 0;
  while (__read_byte(out_path, ci2) != 0) {
    __write_byte(cmd, cpos, __read_byte(out_path, ci2));
    cpos = cpos + 1;
    ci2 = ci2 + 1;
  }
  __write_byte(cmd, cpos, 0);

  int rc = system(cmd);
  if (rc != 0) { my_fatal("clang failed"); }

  printf("Wrote %s and built %s\n", s_path, out_path);
  return 0;
}
