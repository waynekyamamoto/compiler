int printf(int *fmt, ...);
void *malloc(long size);

// Test 1: Global struct array element passed by value
struct Pair { int a; int b; };
struct Pair g_items[4];

int pair_sum(struct Pair p) {
  return p.a + p.b;
}

int test_global_struct_arr_byval() {
  g_items[0].a = 1; g_items[0].b = 2;
  g_items[1].a = 10; g_items[1].b = 20;
  g_items[2].a = 100; g_items[2].b = 200;
  int s = pair_sum(g_items[1]);
  if (s != 30) { printf("FAIL t1 a: %d\n", s); return 1; }
  s = pair_sum(g_items[2]);
  if (s != 300) { printf("FAIL t1 b: %d\n", s); return 1; }
  return 0;
}

// Test 2: Local struct array element passed by value
int test_local_struct_arr_byval() {
  struct Pair items[3];
  items[0].a = 5; items[0].b = 15;
  items[1].a = 25; items[1].b = 35;
  items[2].a = 45; items[2].b = 55;
  int s = pair_sum(items[0]);
  if (s != 20) { printf("FAIL t2 a: %d\n", s); return 1; }
  s = pair_sum(items[2]);
  if (s != 100) { printf("FAIL t2 b: %d\n", s); return 1; }
  return 0;
}

// Test 3: Struct array element byval with modification check
void modify_pair(struct Pair p) {
  p.a = 999;
  p.b = 888;
}

int test_byval_no_modify() {
  g_items[0].a = 42;
  g_items[0].b = 43;
  modify_pair(g_items[0]);
  if (g_items[0].a != 42) { printf("FAIL t3 a: %d\n", g_items[0].a); return 1; }
  if (g_items[0].b != 43) { printf("FAIL t3 b: %d\n", g_items[0].b); return 1; }
  return 0;
}

// Test 4: Struct array element returned from function
struct Pair double_pair(struct Pair p) {
  struct Pair r;
  r.a = p.a * 2;
  r.b = p.b * 2;
  return r;
}

int test_arr_elem_to_ret() {
  g_items[0].a = 7; g_items[0].b = 8;
  struct Pair d = double_pair(g_items[0]);
  if (d.a != 14) { printf("FAIL t4 a: %d\n", d.a); return 1; }
  if (d.b != 16) { printf("FAIL t4 b: %d\n", d.b); return 1; }
  return 0;
}

// Test 5: Multiple struct array elements as args
int pair_diff(struct Pair a, struct Pair b) {
  return (a.a - b.a) + (a.b - b.b);
}

int test_multi_arr_elem() {
  g_items[0].a = 10; g_items[0].b = 20;
  g_items[1].a = 3; g_items[1].b = 5;
  int d = pair_diff(g_items[0], g_items[1]);
  // (10-3) + (20-5) = 7 + 15 = 22
  if (d != 22) { printf("FAIL t5: %d\n", d); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_global_struct_arr_byval();
  if (r == 0) { passed++; } else { failed++; }
  r = test_local_struct_arr_byval();
  if (r == 0) { passed++; } else { failed++; }
  r = test_byval_no_modify();
  if (r == 0) { passed++; } else { failed++; }
  r = test_arr_elem_to_ret();
  if (r == 0) { passed++; } else { failed++; }
  r = test_multi_arr_elem();
  if (r == 0) { passed++; } else { failed++; }
  printf("batch91: %d passed, %d failed\n", passed, failed);
  return failed;
}
