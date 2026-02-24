int printf(int *fmt, ...);

// Test 1: sizeof(int)
int test_sizeof_int() {
  return sizeof(int);  // 8
}

// Test 2: sizeof(char)
int test_sizeof_char() {
  return sizeof(char);  // 1
}

// Test 3: sizeof(type *)
int test_sizeof_ptr() {
  return sizeof(int *);  // 8
}

// Test 4: sizeof local array variable
int test_sizeof_arr() {
  int arr[10];
  return sizeof(arr);  // 80
}

// Test 5: sizeof local array variable (small)
int test_sizeof_arr3() {
  int x[3];
  return sizeof(x);  // 24
}

// Test 6: sizeof struct
struct S2 { int a; int b; };

int test_sizeof_struct() {
  return sizeof(struct S2);  // 16
}

// Test 7: sizeof struct variable
int test_sizeof_structvar() {
  struct S2 s;
  return sizeof(s);  // 16
}

// Test 8: sizeof type array
int test_sizeof_type_arr() {
  return sizeof(int[5]);  // 40
}

int main() {
  int passed = 0;
  int failed = 0;

  if (test_sizeof_int() == 8) { passed++; } else { failed++; printf("FAIL: sizeof_int got %d\n", test_sizeof_int()); }
  if (test_sizeof_char() == 1) { passed++; } else { failed++; printf("FAIL: sizeof_char got %d\n", test_sizeof_char()); }
  if (test_sizeof_ptr() == 8) { passed++; } else { failed++; printf("FAIL: sizeof_ptr got %d\n", test_sizeof_ptr()); }
  if (test_sizeof_arr() == 80) { passed++; } else { failed++; printf("FAIL: sizeof_arr got %d\n", test_sizeof_arr()); }
  if (test_sizeof_arr3() == 24) { passed++; } else { failed++; printf("FAIL: sizeof_arr3 got %d\n", test_sizeof_arr3()); }
  if (test_sizeof_struct() == 16) { passed++; } else { failed++; printf("FAIL: sizeof_struct got %d\n", test_sizeof_struct()); }
  if (test_sizeof_structvar() == 16) { passed++; } else { failed++; printf("FAIL: sizeof_structvar got %d\n", test_sizeof_structvar()); }
  if (test_sizeof_type_arr() == 40) { passed++; } else { failed++; printf("FAIL: sizeof_type_arr got %d\n", test_sizeof_type_arr()); }

  printf("batch62: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
