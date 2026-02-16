int printf(int *fmt, ...);

int test_hex_escape_char() {
  int c;
  c = '\x41';
  if (c != 65) { printf("FAIL: '\\x41' = %d, expected 65\n", c); return 1; }
  c = '\x0A';
  if (c != 10) { printf("FAIL: '\\x0A' = %d, expected 10\n", c); return 1; }
  c = '\x7f';
  if (c != 127) { printf("FAIL: '\\x7f' = %d, expected 127\n", c); return 1; }
  return 0;
}

int test_octal_escape_char() {
  int c;
  c = '\101';
  if (c != 65) { printf("FAIL: '\\101' = %d, expected 65\n", c); return 1; }
  c = '\12';
  if (c != 10) { printf("FAIL: '\\12' = %d, expected 10\n", c); return 1; }
  c = '\0';
  if (c != 0) { printf("FAIL: '\\0' = %d, expected 0\n", c); return 1; }
  c = '\177';
  if (c != 127) { printf("FAIL: '\\177' = %d, expected 127\n", c); return 1; }
  return 0;
}

int test_extra_escapes() {
  int c;
  c = '\a';
  if (c != 7) { printf("FAIL: '\\a' = %d, expected 7\n", c); return 1; }
  c = '\b';
  if (c != 8) { printf("FAIL: '\\b' = %d, expected 8\n", c); return 1; }
  c = '\f';
  if (c != 12) { printf("FAIL: '\\f' = %d, expected 12\n", c); return 1; }
  c = '\v';
  if (c != 11) { printf("FAIL: '\\v' = %d, expected 11\n", c); return 1; }
  return 0;
}

int side_effect_var;

int side_effect() {
  side_effect_var = side_effect_var + 1;
  return side_effect_var;
}

int test_comma_operator() {
  int a;
  int b;
  a = 1;
  b = 2;
  a = (b = 10, b + 5);
  if (a != 15) { printf("FAIL: comma op a = %d, expected 15\n", a); return 1; }
  if (b != 10) { printf("FAIL: comma op b = %d, expected 10\n", b); return 1; }

  side_effect_var = 0;
  side_effect(), side_effect(), side_effect();
  if (side_effect_var != 3) { printf("FAIL: comma side effects = %d, expected 3\n", side_effect_var); return 1; }
  return 0;
}

int test_bool_type() {
  _Bool x;
  x = 1;
  if (x != 1) { printf("FAIL: _Bool x = %d, expected 1\n", x); return 1; }
  x = 0;
  if (x != 0) { printf("FAIL: _Bool x = %d, expected 0\n", x); return 1; }
  return 0;
}

int test_local_var_init() {
  int x = 42;
  int y = x + 8;
  if (x != 42) { printf("FAIL: int x = 42, got %d\n", x); return 1; }
  if (y != 50) { printf("FAIL: int y = x+8, got %d\n", y); return 1; }
  int *p = 0;
  if (p != 0) { printf("FAIL: int *p = 0, got non-null\n"); return 1; }
  return 0;
}

int test_for_init_decl() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = sum + i;
  }
  if (sum != 10) { printf("FAIL: for init decl sum = %d, expected 10\n", sum); return 1; }
  return 0;
}

int main() {
  int fail = 0;
  fail = fail + test_hex_escape_char();
  fail = fail + test_octal_escape_char();
  fail = fail + test_extra_escapes();
  fail = fail + test_comma_operator();
  fail = fail + test_bool_type();
  fail = fail + test_local_var_init();
  fail = fail + test_for_init_decl();
  if (fail == 0) {
    printf("batch6: all tests passed\n");
  } else {
    printf("batch6: %d test(s) FAILED\n", fail);
  }
  return fail;
}
