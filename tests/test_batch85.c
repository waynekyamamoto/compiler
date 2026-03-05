int printf(int *fmt, ...);
void *malloc(long size);

// Test 1: Struct pointer difference
struct Pair { int a; int b; };

int test_struct_ptr_diff() {
  struct Pair arr[5];
  struct Pair *p1 = &arr[1];
  struct Pair *p2 = &arr[4];
  long diff = p2 - p1;
  if (diff != 3) { printf("FAIL struct diff: %ld\n", diff); return 1; }
  return 0;
}

// Test 2: Struct pointer difference - 3 field struct
struct Triple { int x; int y; int z; };

int test_triple_ptr_diff() {
  struct Triple arr[4];
  struct Triple *p1 = &arr[0];
  struct Triple *p2 = &arr[3];
  long diff = p2 - p1;
  if (diff != 3) { printf("FAIL triple diff: %ld\n", diff); return 1; }
  return 0;
}

// Test 3: Struct pointer arithmetic (add) still works
int test_struct_ptr_add() {
  struct Pair arr[3];
  arr[0].a = 10; arr[0].b = 100;
  arr[1].a = 20; arr[1].b = 200;
  arr[2].a = 30; arr[2].b = 300;
  struct Pair *p = arr;
  struct Pair *q = p + 2;
  if (q->a != 30) { printf("FAIL ptr+2: a=%d\n", q->a); return 1; }
  if (q->b != 300) { printf("FAIL ptr+2: b=%d\n", q->b); return 2; }
  return 0;
}

// Test 4: Struct pointer subtraction with int (ptr - int)
int test_struct_ptr_sub_int() {
  struct Pair arr[4];
  arr[0].a = 1; arr[1].a = 2; arr[2].a = 3; arr[3].a = 4;
  struct Pair *p = &arr[3];
  struct Pair *q = p - 2;
  if (q->a != 2) { printf("FAIL ptr-2: a=%d\n", q->a); return 1; }
  return 0;
}

// Test 5: Struct pointer walk with increment
int test_struct_ptr_walk() {
  struct Pair arr[4];
  arr[0].a = 10; arr[1].a = 20; arr[2].a = 30; arr[3].a = 40;
  struct Pair *p = arr;
  int sum = 0;
  for (int i = 0; i < 4; i++) {
    sum += p->a;
    p++;
  }
  if (sum != 100) { printf("FAIL walk sum: %d\n", sum); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_ptr_diff();
  if (r == 0) { passed++; } else { failed++; printf("  struct_ptr_diff: FAIL %d\n", r); }

  r = test_triple_ptr_diff();
  if (r == 0) { passed++; } else { failed++; printf("  triple_ptr_diff: FAIL %d\n", r); }

  r = test_struct_ptr_add();
  if (r == 0) { passed++; } else { failed++; printf("  struct_ptr_add: FAIL %d\n", r); }

  r = test_struct_ptr_sub_int();
  if (r == 0) { passed++; } else { failed++; printf("  struct_ptr_sub_int: FAIL %d\n", r); }

  r = test_struct_ptr_walk();
  if (r == 0) { passed++; } else { failed++; printf("  struct_ptr_walk: FAIL %d\n", r); }

  printf("batch85: %d passed, %d failed\n", passed, failed);
  return failed;
}
