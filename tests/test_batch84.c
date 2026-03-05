int printf(int *fmt, ...);
void *malloc(long size);

// Test 1: Struct by value - 2 fields
struct Pair { int a; int b; };

void check_pair(struct Pair p, int ea, int eb, int *result) {
  if (p.a != ea || p.b != eb) {
    printf("FAIL pair: got a=%d b=%d, expected a=%d b=%d\n", p.a, p.b, ea, eb);
    *result = 1;
  }
}

int test_struct_by_value_2() {
  struct Pair p;
  p.a = 10; p.b = 20;
  int r = 0;
  check_pair(p, 10, 20, &r);
  return r;
}

// Test 2: Struct by value - 3 fields
struct Vec { int x; int y; int z; };

int vec_dot(struct Vec a, struct Vec b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct Vec vec_add(struct Vec a, struct Vec b) {
  struct Vec r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  r.z = a.z + b.z;
  return r;
}

int test_struct_by_value_3() {
  struct Vec a;
  a.x = 1; a.y = 2; a.z = 3;
  struct Vec b;
  b.x = 4; b.y = 5; b.z = 6;
  int d = vec_dot(a, b);
  if (d != 32) { printf("FAIL dot: %d\n", d); return 1; }
  struct Vec c = vec_add(a, b);
  if (c.x != 5) { printf("FAIL add.x: %d\n", c.x); return 2; }
  if (c.y != 7) { printf("FAIL add.y: %d\n", c.y); return 3; }
  if (c.z != 9) { printf("FAIL add.z: %d\n", c.z); return 4; }
  return 0;
}

// Test 3: Nested struct call (struct return passed to struct param)
struct Pair make_pair(int a, int b) {
  struct Pair p;
  p.a = a; p.b = b;
  return p;
}

struct Pair swap_pair(struct Pair p) {
  struct Pair r;
  r.a = p.b; r.b = p.a;
  return r;
}

int test_nested_struct_call() {
  struct Pair p = swap_pair(make_pair(10, 20));
  if (p.a != 20) { printf("FAIL swap.a: %d\n", p.a); return 1; }
  if (p.b != 10) { printf("FAIL swap.b: %d\n", p.b); return 2; }
  return 0;
}

// Test 4: Struct by value with modification (shouldn't affect original)
void modify_pair(struct Pair p, int *out_a) {
  p.a = 999;
  *out_a = p.a;
}

int test_struct_by_value_no_alias() {
  struct Pair p;
  p.a = 10; p.b = 20;
  int got;
  modify_pair(p, &got);
  if (got != 999) { printf("FAIL modified: %d\n", got); return 1; }
  if (p.a != 10) { printf("FAIL original: %d\n", p.a); return 2; }
  return 0;
}

// Test 5: Multiple struct params
int sum_pairs(struct Pair p1, struct Pair p2, struct Pair p3) {
  return p1.a + p1.b + p2.a + p2.b + p3.a + p3.b;
}

int test_multi_struct_params() {
  struct Pair a; a.a = 1; a.b = 2;
  struct Pair b; b.a = 3; b.b = 4;
  struct Pair c; c.a = 5; c.b = 6;
  int s = sum_pairs(a, b, c);
  if (s != 21) { printf("FAIL sum_pairs: %d\n", s); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_by_value_2();
  if (r == 0) { passed++; } else { failed++; printf("  struct_by_value_2: FAIL %d\n", r); }

  r = test_struct_by_value_3();
  if (r == 0) { passed++; } else { failed++; printf("  struct_by_value_3: FAIL %d\n", r); }

  r = test_nested_struct_call();
  if (r == 0) { passed++; } else { failed++; printf("  nested_struct_call: FAIL %d\n", r); }

  r = test_struct_by_value_no_alias();
  if (r == 0) { passed++; } else { failed++; printf("  struct_by_value_no_alias: FAIL %d\n", r); }

  r = test_multi_struct_params();
  if (r == 0) { passed++; } else { failed++; printf("  multi_struct_params: FAIL %d\n", r); }

  printf("batch84: %d passed, %d failed\n", passed, failed);
  return failed;
}
