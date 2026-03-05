// Test batch 57: typeof, __builtin_expect, long long, misc patterns
int printf(char *fmt, ...);

int main() {
  int passed = 0;
  int failed = 0;

  // Test 1: __typeof__ basic
  int x = 42;
  __typeof__(x) y = x + 1;
  if (y == 43) { passed++; } else { failed++; printf("FAIL test 1: %d\n", y); }

  // Test 2: typeof (C23 keyword)
  int a = 10;
  typeof(a) b = a * 2;
  if (b == 20) { passed++; } else { failed++; printf("FAIL test 2: %d\n", b); }

  // Test 3: __builtin_expect
  int v = 5;
  if (__builtin_expect(v > 3, 1)) { passed++; } else { failed++; printf("FAIL test 3\n"); }

  // Test 4: __builtin_expect false path
  if (__builtin_expect(v < 3, 0)) { failed++; printf("FAIL test 4\n"); } else { passed++; }

  // Test 5: long long type
  long long ll = 1;
  ll = ll * 1000000;
  ll = ll * 1000000;
  if (ll > 0) { passed++; } else { failed++; printf("FAIL test 5\n"); }

  // Test 6: unsigned long long
  unsigned long long ull = 1;
  ull = ull << 32;
  if (ull > 0) { passed++; } else { failed++; printf("FAIL test 6\n"); }

  // Test 7: Multiple comma in expression
  int c = (1, 2, 3, 4, 5);
  if (c == 5) { passed++; } else { failed++; printf("FAIL test 7: %d\n", c); }

  // Test 8: Comma in for init
  int i;
  int j;
  for (i = 0, j = 10; i < 5; i++, j--) {}
  if (i == 5 && j == 5) { passed++; } else { failed++; printf("FAIL test 8: i=%d j=%d\n", i, j); }

  // Test 9: Conditional (ternary) with side effects
  int t = 1;
  int result = t ? 100 : 200;
  if (result == 100) { passed++; } else { failed++; printf("FAIL test 9: %d\n", result); }

  // Test 10: Nested ternary
  int n = 2;
  int r = n == 1 ? 10 : n == 2 ? 20 : 30;
  if (r == 20) { passed++; } else { failed++; printf("FAIL test 10: %d\n", r); }

  printf("Batch 57: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
