int printf(int *fmt, ...);

// Test 1: GNU Elvis operator (?:) with truthy value
int test_elvis_truthy() {
  int x = 42;
  int y = x ?: 0;
  return y;  // 42
}

// Test 2: GNU Elvis operator with falsy value
int test_elvis_falsy() {
  int x = 0;
  int y = x ?: 99;
  return y;  // 99
}

// Test 3: Elvis in expression chain
int test_elvis_chain() {
  int a = 0;
  int b = 0;
  int c = 77;
  int r = a ?: b ?: c;
  return r;  // 77
}

// Test 4: Designated initializer with zero-fill
int test_desig_zero() {
  int arr[5] = { [2] = 42, [4] = 99 };
  if (arr[0] != 0) return 1;
  if (arr[1] != 0) return 2;
  if (arr[2] != 42) return 3;
  if (arr[3] != 0) return 4;
  if (arr[4] != 99) return 5;
  return 0;
}

// Test 5: Partial array init is zero-filled
int test_partial_init() {
  int arr[5] = {10, 20};
  if (arr[0] != 10) return 1;
  if (arr[1] != 20) return 2;
  if (arr[2] != 0) return 3;
  if (arr[3] != 0) return 4;
  if (arr[4] != 0) return 5;
  return 0;
}

// Test 6: Struct partial init is zero-filled
struct S3 { int a; int b; int c; };

int test_struct_partial_init() {
  struct S3 s = {10};
  if (s.a != 10) return 1;
  if (s.b != 0) return 2;
  if (s.c != 0) return 3;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  if (test_elvis_truthy() == 42) { passed++; } else { failed++; printf("FAIL: elvis_truthy\n"); }
  if (test_elvis_falsy() == 99) { passed++; } else { failed++; printf("FAIL: elvis_falsy got %d\n", test_elvis_falsy()); }
  if (test_elvis_chain() == 77) { passed++; } else { failed++; printf("FAIL: elvis_chain got %d\n", test_elvis_chain()); }

  r = test_desig_zero();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: desig_zero code=%d\n", r); }

  r = test_partial_init();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: partial_init code=%d\n", r); }

  r = test_struct_partial_init();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_partial_init code=%d\n", r); }

  printf("batch61: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
