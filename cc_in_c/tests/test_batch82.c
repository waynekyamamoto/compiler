int printf(int *fmt, ...);

// Test 1: Pointer post-increment (p++)
int test_ptr_postinc() {
  int arr[4];
  arr[0] = 10; arr[1] = 20; arr[2] = 30; arr[3] = 40;
  int *p = arr;
  p++;
  if (*p != 20) { printf("FAIL p++: *p=%d (expected 20)\n", *p); return 1; }
  p++;
  if (*p != 30) { printf("FAIL p++ again: *p=%d (expected 30)\n", *p); return 2; }
  return 0;
}

// Test 2: Pointer post-decrement (p--)
int test_ptr_postdec() {
  int arr[4];
  arr[0] = 10; arr[1] = 20; arr[2] = 30; arr[3] = 40;
  int *p = arr + 3;
  p--;
  if (*p != 30) { printf("FAIL p--: *p=%d (expected 30)\n", *p); return 1; }
  p--;
  if (*p != 20) { printf("FAIL p-- again: *p=%d (expected 20)\n", *p); return 2; }
  return 0;
}

// Test 3: *p++ (dereference then increment)
int test_deref_postinc() {
  int arr[3];
  arr[0] = 100; arr[1] = 200; arr[2] = 300;
  int *p = arr;
  int v = *p++;
  if (v != 100) { printf("FAIL *p++: v=%d (expected 100)\n", v); return 1; }
  if (*p != 200) { printf("FAIL *p++ ptr: *p=%d (expected 200)\n", *p); return 2; }
  v = *p++;
  if (v != 200) { printf("FAIL *p++ 2nd: v=%d (expected 200)\n", v); return 3; }
  if (*p != 300) { printf("FAIL *p++ 2nd ptr: *p=%d (expected 300)\n", *p); return 4; }
  return 0;
}

// Test 4: Pointer walk with p++ in loop
int test_ptr_walk_loop() {
  int data[6];
  data[0] = 1; data[1] = 2; data[2] = 3; data[3] = 4; data[4] = 5; data[5] = 0;
  int *p = data;
  int sum = 0;
  while (*p != 0) {
    sum += *p;
    p++;
  }
  if (sum != 15) { printf("FAIL ptr_walk: sum=%d (expected 15)\n", sum); return 1; }
  return 0;
}

// Test 5: Pre-increment on pointer (++p uses p = p + 1)
int test_ptr_preinc() {
  int arr[3];
  arr[0] = 10; arr[1] = 20; arr[2] = 30;
  int *p = arr;
  int v = *++p;
  if (v != 20) { printf("FAIL *++p: v=%d (expected 20)\n", v); return 1; }
  if (*p != 20) { printf("FAIL *++p ptr: *p=%d (expected 20)\n", *p); return 2; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_ptr_postinc();
  if (r == 0) { passed++; } else { failed++; }

  r = test_ptr_postdec();
  if (r == 0) { passed++; } else { failed++; }

  r = test_deref_postinc();
  if (r == 0) { passed++; } else { failed++; }

  r = test_ptr_walk_loop();
  if (r == 0) { passed++; } else { failed++; }

  r = test_ptr_preinc();
  if (r == 0) { passed++; } else { failed++; }

  printf("batch82: %d passed, %d failed\n", passed, failed);
  return failed;
}
