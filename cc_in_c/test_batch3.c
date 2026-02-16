int printf(int *fmt, ...);

int test_type_keywords() {
  char c;
  long l;
  short s;
  unsigned u;
  signed si;
  c = 65;
  l = 100;
  s = 50;
  u = 200;
  si = -10;
  if (c != 65) { printf("FAIL: char = %d\n", c); return 1; }
  if (l != 100) { printf("FAIL: long = %d\n", l); return 1; }
  if (s != 50) { printf("FAIL: short = %d\n", s); return 1; }
  if (u != 200) { printf("FAIL: unsigned = %d\n", u); return 1; }
  if (si != -10) { printf("FAIL: signed = %d\n", si); return 1; }
  return 0;
}

int test_qualifiers() {
  int a;
  static int b;
  register int c;
  a = 10;
  b = 20;
  c = 30;
  if (a != 10) { printf("FAIL: int = %d\n", a); return 1; }
  if (b != 20) { printf("FAIL: static int = %d\n", b); return 1; }
  if (c != 30) { printf("FAIL: register int = %d\n", c); return 1; }
  return 0;
}

int test_cast() {
  int x;
  int y;
  x = 42;
  y = (int)x;
  if (y != 42) { printf("FAIL: (int)x = %d\n", y); return 1; }
  y = (long)x;
  if (y != 42) { printf("FAIL: (long)x = %d\n", y); return 1; }
  y = (char)(x + 1);
  if (y != 43) { printf("FAIL: (char)(x+1) = %d\n", y); return 1; }
  return 0;
}

int test_void_return() {
  void *p;
  p = 0;
  if (p != 0) { printf("FAIL: void *p != 0\n"); return 1; }
  return 0;
}

int main() {
  int fail;
  fail = 0;
  fail = fail + test_type_keywords();
  fail = fail + test_qualifiers();
  fail = fail + test_cast();
  fail = fail + test_void_return();
  if (fail == 0) {
    printf("batch3: all tests passed\n");
  } else {
    printf("batch3: %d test(s) FAILED\n", fail);
  }
  return fail;
}
