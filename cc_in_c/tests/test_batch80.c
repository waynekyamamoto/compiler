int printf(int *fmt, ...);

// Test 1: Pointer arithmetic with array (arr + n)
int test_array_plus_int() {
  int arr[5];
  arr[0] = 10; arr[1] = 20; arr[2] = 30; arr[3] = 40; arr[4] = 50;
  int *p = arr + 3;
  if (*p != 40) { printf("FAIL arr+3: *p=%d (expected 40)\n", *p); return 1; }
  p = arr + 0;
  if (*p != 10) { printf("FAIL arr+0: *p=%d (expected 10)\n", *p); return 2; }
  return 0;
}

// Test 2: Array subtraction
int test_array_minus() {
  int arr[5];
  arr[0] = 100; arr[1] = 200; arr[2] = 300; arr[3] = 400; arr[4] = 500;
  int *p = arr + 4;
  p = p - 2;
  if (*p != 300) { printf("FAIL p-2: *p=%d (expected 300)\n", *p); return 1; }
  return 0;
}

// Test 3: Int + array (commutative)
int test_int_plus_array() {
  int arr[5];
  arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4; arr[4] = 5;
  int *p = 2 + arr;
  if (*p != 3) { printf("FAIL 2+arr: *p=%d (expected 3)\n", *p); return 1; }
  return 0;
}

// Test 4: Struct assignment through pointer (*p = s)
struct Pair { int a; int b; };

int test_struct_assign_deref() {
  struct Pair s1;
  s1.a = 42;
  s1.b = 99;
  struct Pair s2;
  s2.a = 0;
  s2.b = 0;
  struct Pair *p = &s2;
  *p = s1;
  if (s2.a != 42) { printf("FAIL *p=s: a=%d (expected 42)\n", s2.a); return 1; }
  if (s2.b != 99) { printf("FAIL *p=s: b=%d (expected 99)\n", s2.b); return 2; }
  return 0;
}

// Test 5: Struct assignment through pointer (3-field)
struct Triple { int x; int y; int z; };

int test_struct_assign_deref_triple() {
  struct Triple t1;
  t1.x = 10; t1.y = 20; t1.z = 30;
  struct Triple t2;
  t2.x = 0; t2.y = 0; t2.z = 0;
  struct Triple *p = &t2;
  *p = t1;
  if (t2.x != 10) { printf("FAIL *p=t triple: x=%d\n", t2.x); return 1; }
  if (t2.y != 20) { printf("FAIL *p=t triple: y=%d\n", t2.y); return 2; }
  if (t2.z != 30) { printf("FAIL *p=t triple: z=%d\n", t2.z); return 3; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_array_plus_int();
  if (r == 0) { passed++; } else { failed++; }

  r = test_array_minus();
  if (r == 0) { passed++; } else { failed++; }

  r = test_int_plus_array();
  if (r == 0) { passed++; } else { failed++; }

  r = test_struct_assign_deref();
  if (r == 0) { passed++; } else { failed++; }

  r = test_struct_assign_deref_triple();
  if (r == 0) { passed++; } else { failed++; }

  printf("batch80: %d passed, %d failed\n", passed, failed);
  return failed;
}
