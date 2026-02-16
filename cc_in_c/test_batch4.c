int printf(int *fmt, ...);

enum Color { RED, GREEN, BLUE };
enum Explicit { A = 10, B = 20, C = 30 };

typedef int MyInt;

int test_enum_auto() {
  int r;
  int g;
  int b;
  r = RED;
  g = GREEN;
  b = BLUE;
  if (r != 0) { printf("FAIL: RED = %d\n", r); return 1; }
  if (g != 1) { printf("FAIL: GREEN = %d\n", g); return 1; }
  if (b != 2) { printf("FAIL: BLUE = %d\n", b); return 1; }
  return 0;
}

int test_enum_explicit() {
  int a;
  int b;
  int c;
  a = A;
  b = B;
  c = C;
  if (a != 10) { printf("FAIL: A = %d\n", a); return 1; }
  if (b != 20) { printf("FAIL: B = %d\n", b); return 1; }
  if (c != 30) { printf("FAIL: C = %d\n", c); return 1; }
  return 0;
}

int test_enum_expr() {
  int x;
  x = RED + BLUE;
  if (x != 2) { printf("FAIL: RED + BLUE = %d\n", x); return 1; }
  x = A * 2 + B;
  if (x != 40) { printf("FAIL: A*2 + B = %d\n", x); return 1; }
  return 0;
}

int main() {
  int fail;
  fail = 0;
  fail = fail + test_enum_auto();
  fail = fail + test_enum_explicit();
  fail = fail + test_enum_expr();
  if (fail == 0) {
    printf("batch4: all tests passed\n");
  } else {
    printf("batch4: %d test(s) FAILED\n", fail);
  }
  return fail;
}
