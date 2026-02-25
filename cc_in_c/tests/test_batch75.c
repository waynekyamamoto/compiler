int printf(int *fmt, ...);

// Test 1: *(ptr + n) with int pointer
int test_ptr_add_deref() {
  int arr[4] = {10, 20, 30, 40};
  int *p = arr;
  if (*(p + 0) != 10) return 1;
  if (*(p + 1) != 20) return 2;
  if (*(p + 2) != 30) return 3;
  if (*(p + 3) != 40) return 4;
  return 0;
}

// Test 2: ptr + n == &ptr[n]
int test_ptr_add_equiv() {
  int arr[5] = {100, 200, 300, 400, 500};
  int *p = arr;
  int *q = p + 3;
  if (*q != 400) return 1;
  if (q != &arr[3]) return 2;
  return 0;
}

// Test 3: n + ptr (commutative)
int test_ptr_add_commute() {
  int arr[3] = {11, 22, 33};
  int *p = arr;
  if (*(2 + p) != 33) return 1;
  return 0;
}

// Test 4: ptr - n (subtraction)
int test_ptr_sub_n() {
  int arr[5] = {1, 2, 3, 4, 5};
  int *p = &arr[4];
  if (*(p - 2) != 3) return 1;
  if (*(p - 4) != 1) return 2;
  return 0;
}

// Test 5: Pointer arithmetic in loop
int test_ptr_loop() {
  int arr[5] = {10, 20, 30, 40, 50};
  int *p = arr;
  int sum = 0;
  int i;
  for (i = 0; i < 5; i++) {
    sum += *(p + i);
  }
  if (sum != 150) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_ptr_add_deref();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_add_deref code=%d\n", r); }

  r = test_ptr_add_equiv();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_add_equiv code=%d\n", r); }

  r = test_ptr_add_commute();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_add_commute code=%d\n", r); }

  r = test_ptr_sub_n();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_sub_n code=%d\n", r); }

  r = test_ptr_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_loop code=%d\n", r); }

  printf("batch75: %d passed, %d failed\n", passed, failed);
  return failed;
}
