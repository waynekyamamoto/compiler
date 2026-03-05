int printf(int *fmt, ...);

// Test 1: Unsigned right shift of 0xFFFFFFFF
int test_unsigned_rshift_ff() {
  unsigned int x = 0xFFFFFFFF;
  unsigned int r = x >> 16;
  if (r != 65535) return 1;
  return 0;
}

// Test 2: Unsigned right shift of smaller value
int test_unsigned_rshift_small() {
  unsigned int x = 256;
  unsigned int r = x >> 4;
  if (r != 16) return 1;
  return 0;
}

// Test 3: Unsigned right shift by 1
int test_unsigned_rshift_one() {
  unsigned int x = 0x80000000;
  unsigned int r = x >> 1;
  // 0x80000000 >> 1 should be 0x40000000 = 1073741824 (unsigned)
  if (r != 1073741824) return 1;
  return 0;
}

// Test 4: Signed right shift preserves sign (negative)
int test_signed_rshift() {
  int x = 0 - 256;
  int r = x >> 4;
  // Arithmetic shift: -256 >> 4 = -16
  if (r != 0 - 16) return 1;
  return 0;
}

// Test 5: Pointer difference (int pointers)
int test_ptr_diff() {
  int arr[10];
  int *p = &arr[0];
  int *q = &arr[5];
  int diff = q - p;
  if (diff != 5) return 1;
  return 0;
}

// Test 6: Pointer difference (adjacent elements)
int test_ptr_diff_one() {
  int arr[3];
  int *p = &arr[0];
  int *q = &arr[1];
  int diff = q - p;
  if (diff != 1) return 1;
  return 0;
}

// Test 7: Pointer difference (negative)
int test_ptr_diff_neg() {
  int arr[10];
  int *p = &arr[5];
  int *q = &arr[2];
  int diff = q - p;
  if (diff != 0 - 3) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_unsigned_rshift_ff();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_rshift_ff code=%d\n", r); }

  r = test_unsigned_rshift_small();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_rshift_small code=%d\n", r); }

  r = test_unsigned_rshift_one();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_rshift_one code=%d\n", r); }

  r = test_signed_rshift();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: signed_rshift code=%d\n", r); }

  r = test_ptr_diff();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_diff code=%d\n", r); }

  r = test_ptr_diff_one();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_diff_one code=%d\n", r); }

  r = test_ptr_diff_neg();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_diff_neg code=%d\n", r); }

  printf("batch71: %d passed, %d failed\n", passed, failed);
  return failed;
}
