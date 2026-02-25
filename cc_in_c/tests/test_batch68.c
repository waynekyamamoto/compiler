int printf(int *fmt, ...);

// Test 1: Stringify macro
#define STRINGIFY(x) #x

int test_stringify() {
  char *s = STRINGIFY(hello);
  if (s[0] != 'h') return 1;
  if (s[4] != 'o') return 2;
  return 0;
}

// Test 2: Token pasting after comment
#define PASTE(a, b) a ## b

int PASTE(test_,paste)() {
  int PASTE(my_,var) = 42;
  if (PASTE(my_,var) != 42) return 1;
  return 0;
}

// Test 3: Nested macros
#define DOUBLE(x) ((x) * 2)
#define QUAD(x) DOUBLE(DOUBLE(x))

int test_nested_macro() {
  if (QUAD(3) != 12) return 1;
  if (DOUBLE(DOUBLE(5)) != 20) return 2;
  return 0;
}

// Test 4: Conditional compilation
#define FEATURE_A 1
#undef FEATURE_B

int test_ifdef() {
  int r = 0;
#ifdef FEATURE_A
  r = r + 1;
#endif
#ifdef FEATURE_B
  r = r + 100;
#endif
#ifndef FEATURE_B
  r = r + 10;
#endif
  if (r != 11) return 1;
  return 0;
}

// Test 5: Multi-line macro
#define MAX(a, b) \
  ((a) > (b) ? (a) : (b))

int test_multiline_macro() {
  if (MAX(3, 5) != 5) return 1;
  if (MAX(10, 2) != 10) return 2;
  return 0;
}

// Test 6: Variadic macro
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

int test_variadic_macro() {
  LOG("val=%d\n", 42);
  return 0;
}

/* Block comment before paste macro use */
#define JOIN(a, b) a ## b

// Line comment before paste macro use
int JOIN(test_,join)() {
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_stringify();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: stringify code=%d\n", r); }
  r = test_paste();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: paste code=%d\n", r); }
  r = test_nested_macro();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: nested_macro code=%d\n", r); }
  r = test_ifdef();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ifdef code=%d\n", r); }
  r = test_multiline_macro();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multiline_macro code=%d\n", r); }
  r = test_variadic_macro();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: variadic_macro code=%d\n", r); }
  r = test_join();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: join code=%d\n", r); }
  printf("batch68: %d passed, %d failed\n", passed, failed);
  return failed;
}
