int printf(int *fmt, ...);

// Test 1: Global int array pointer arithmetic
int g_data[8];

int test_global_array_add() {
  for (int i = 0; i < 8; i++) g_data[i] = (i + 1) * 10;
  int *p = g_data + 3;
  if (*p != 40) { printf("FAIL g+3: *p=%d (expected 40)\n", *p); return 1; }
  p = g_data + 7;
  if (*p != 80) { printf("FAIL g+7: *p=%d (expected 80)\n", *p); return 2; }
  return 0;
}

// Test 2: Global array subtraction
int test_global_array_sub() {
  for (int i = 0; i < 8; i++) g_data[i] = i * 100;
  int *p = g_data + 6;
  p = p - 4;
  if (*p != 200) { printf("FAIL g-4: *p=%d (expected 200)\n", *p); return 1; }
  return 0;
}

// Test 3: Local array pointer arithmetic (already fixed but regression test)
int test_local_array_arith() {
  int arr[5];
  arr[0] = 100; arr[1] = 200; arr[2] = 300; arr[3] = 400; arr[4] = 500;
  int *p = arr + 2;
  if (*p != 300) { printf("FAIL local arr+2: *p=%d\n", *p); return 1; }
  int *q = arr + 4;
  if (*q != 500) { printf("FAIL local arr+4: *q=%d\n", *q); return 2; }
  return 0;
}

// Test 4: Pointer diff with global array
int test_global_ptr_diff() {
  int *p1 = &g_data[1];
  int *p2 = &g_data[5];
  long diff = p2 - p1;
  if (diff != 4) { printf("FAIL ptr_diff: diff=%ld (expected 4)\n", diff); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_global_array_add();
  if (r == 0) { passed++; } else { failed++; }

  r = test_global_array_sub();
  if (r == 0) { passed++; } else { failed++; }

  r = test_local_array_arith();
  if (r == 0) { passed++; } else { failed++; }

  r = test_global_ptr_diff();
  if (r == 0) { passed++; } else { failed++; }

  printf("batch81: %d passed, %d failed\n", passed, failed);
  return failed;
}
