int printf(int *fmt, ...);

// Test 1: sizeof(arr[0]) returns element size, not array size
int test_sizeof_arr_elem() {
  int arr[10];
  int sz = sizeof(arr[0]);
  if (sz != 4) return 1;
  return 0;
}

// Test 2: sizeof(arr) / sizeof(arr[0]) gives element count
int test_sizeof_countof() {
  int arr[10];
  int n = sizeof(arr) / sizeof(arr[0]);
  if (n != 10) return 1;
  return 0;
}

// Test 3: sizeof(arr) still works for full array
int test_sizeof_full_arr() {
  int arr[5];
  if (sizeof(arr) != 20) return 1;
  return 0;
}

// Test 4: sizeof with struct array element
struct Pt { int x; int y; };

int test_sizeof_struct_arr_elem() {
  struct Pt pts[4];
  int elem_sz = sizeof(pts[0]);
  int arr_sz = sizeof(pts);
  if (elem_sz != 8) return 1;
  if (arr_sz != 32) return 2;
  int n = arr_sz / elem_sz;
  if (n != 4) return 3;
  return 0;
}

// Test 5: sizeof(arr) / sizeof(arr[0]) practical usage
int test_sizeof_loop() {
  int arr[5] = {10, 20, 30, 40, 50};
  int n = sizeof(arr) / sizeof(arr[0]);
  int sum = 0;
  int i;
  for (i = 0; i < n; i++) {
    sum = sum + arr[i];
  }
  if (sum != 150) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_sizeof_arr_elem();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: sizeof_arr_elem code=%d\n", r); }
  r = test_sizeof_countof();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: sizeof_countof code=%d\n", r); }
  r = test_sizeof_full_arr();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: sizeof_full_arr code=%d\n", r); }
  r = test_sizeof_struct_arr_elem();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: sizeof_struct_arr_elem code=%d\n", r); }
  r = test_sizeof_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: sizeof_loop code=%d\n", r); }
  printf("batch67: %d passed, %d failed\n", passed, failed);
  return failed;
}
