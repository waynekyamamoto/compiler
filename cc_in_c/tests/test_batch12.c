// Test batch 12: Nested structs

int printf(int *fmt, ...);
int *malloc(int size);

struct Inner {
  int a;
  int b;
};

struct Outer {
  struct Inner in;
  int c;
};

int test_nested_dot() {
  struct Outer o;
  o.in.a = 10;
  o.in.b = 20;
  o.c = 30;
  if (o.in.a != 10) return 1;
  if (o.in.b != 20) return 2;
  if (o.c != 30) return 3;
  if (o.in.a + o.in.b + o.c != 60) return 4;
  return 0;
}

int test_nested_ptr() {
  struct Outer *p;
  p = malloc(24);
  p->in.a = 100;
  p->in.b = 200;
  p->c = 300;
  if (p->in.a != 100) return 1;
  if (p->in.b != 200) return 2;
  if (p->c != 300) return 3;
  return 0;
}

struct Deep {
  struct Outer outer;
  int d;
};

int test_deep_nested() {
  struct Deep deep;
  deep.outer.in.a = 1;
  deep.outer.in.b = 2;
  deep.outer.c = 3;
  deep.d = 4;
  if (deep.outer.in.a != 1) return 1;
  if (deep.outer.in.b != 2) return 2;
  if (deep.outer.c != 3) return 3;
  if (deep.d != 4) return 4;
  return 0;
}

struct TwoStructs {
  struct Inner first;
  struct Inner second;
};

int test_two_nested() {
  struct TwoStructs ts;
  ts.first.a = 10;
  ts.first.b = 20;
  ts.second.a = 30;
  ts.second.b = 40;
  if (ts.first.a != 10) return 1;
  if (ts.first.b != 20) return 2;
  if (ts.second.a != 30) return 3;
  if (ts.second.b != 40) return 4;
  return 0;
}

int main() {
  if (test_nested_dot()) { printf("FAIL: nested_dot\n"); return 1; }
  if (test_nested_ptr()) { printf("FAIL: nested_ptr\n"); return 1; }
  if (test_deep_nested()) { printf("FAIL: deep_nested\n"); return 1; }
  if (test_two_nested()) { printf("FAIL: two_nested\n"); return 1; }
  printf("All batch 12 tests passed.\n");
  return 0;
}
