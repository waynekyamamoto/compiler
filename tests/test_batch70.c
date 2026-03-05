int printf(int *fmt, ...);

// Test 1: Global function pointer variable
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

int (*g_op)(int, int);

int test_global_funcptr() {
  g_op = add;
  if (g_op(3, 4) != 7) return 1;
  g_op = sub;
  if (g_op(10, 3) != 7) return 2;
  g_op = mul;
  if (g_op(5, 6) != 30) return 3;
  return 0;
}

// Test 2: Global funcptr reassignment in loop
int double_it(int x) { return x * 2; }
int inc_it(int x) { return x + 1; }

int (*g_transform)(int);

int test_funcptr_loop() {
  int val = 5;
  g_transform = double_it;
  val = g_transform(val);
  if (val != 10) return 1;
  g_transform = inc_it;
  val = g_transform(val);
  if (val != 11) return 2;
  return 0;
}

// Test 3: Global funcptr passed to function
int apply(int (*fn)(int, int), int a, int b) {
  return fn(a, b);
}

int test_funcptr_param() {
  g_op = add;
  if (apply(g_op, 2, 3) != 5) return 1;
  g_op = mul;
  if (apply(g_op, 4, 5) != 20) return 2;
  return 0;
}

// Test 4: Global funcptr initialized to NULL, then assigned
int (*g_cb)(int, int);

int test_funcptr_null_init() {
  g_cb = 0;
  if (g_cb != 0) return 1;
  g_cb = add;
  if (g_cb(100, 200) != 300) return 2;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_global_funcptr();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_funcptr code=%d\n", r); }
  r = test_funcptr_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: funcptr_loop code=%d\n", r); }
  r = test_funcptr_param();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: funcptr_param code=%d\n", r); }
  r = test_funcptr_null_init();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: funcptr_null_init code=%d\n", r); }
  printf("batch70: %d passed, %d failed\n", passed, failed);
  return failed;
}
