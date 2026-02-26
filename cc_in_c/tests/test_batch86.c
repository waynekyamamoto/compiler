int printf(int *fmt, ...);

// Test 1: Struct array + integer pointer arithmetic
struct Pair { int a; int b; };

int test_struct_array_add() {
  struct Pair arr[5];
  arr[0].a = 10; arr[0].b = 100;
  arr[1].a = 20; arr[1].b = 200;
  arr[2].a = 30; arr[2].b = 300;
  arr[3].a = 40; arr[3].b = 400;
  arr[4].a = 50; arr[4].b = 500;
  struct Pair *p = arr + 3;
  if (p->a != 40) { printf("FAIL arr+3: a=%d\n", p->a); return 1; }
  if (p->b != 400) { printf("FAIL arr+3: b=%d\n", p->b); return 2; }
  return 0;
}

// Test 2: Struct array end pointer comparison
struct Item { int id; int price; };

int test_struct_array_end() {
  struct Item items[4];
  items[0].price = 100;
  items[1].price = 200;
  items[2].price = 300;
  items[3].price = 400;
  struct Item *p = items;
  struct Item *end = items + 4;
  int total = 0;
  while (p != end) {
    total += p->price;
    p++;
  }
  if (total != 1000) { printf("FAIL struct end iter: %d\n", total); return 1; }
  return 0;
}

// Test 3: Struct array + 0 (should be same as base)
int test_struct_array_plus_zero() {
  struct Pair arr[3];
  arr[0].a = 99;
  struct Pair *p = arr + 0;
  if (p->a != 99) { printf("FAIL arr+0: a=%d\n", p->a); return 1; }
  return 0;
}

// Test 4: Struct array pointer subtraction (array - array)
int test_struct_array_diff() {
  struct Item items[5];
  struct Item *start = items;
  struct Item *end = items + 5;
  long diff = end - start;
  if (diff != 5) { printf("FAIL arr diff: %ld\n", diff); return 1; }
  return 0;
}

// Test 5: Struct pointer walk with pre-increment
struct Triple { int x; int y; int z; };

int test_struct_pre_inc() {
  struct Triple arr[3];
  arr[0].x = 1; arr[1].x = 2; arr[2].x = 3;
  struct Triple *p = arr;
  ++p;
  if (p->x != 2) { printf("FAIL pre-inc: x=%d\n", p->x); return 1; }
  ++p;
  if (p->x != 3) { printf("FAIL pre-inc2: x=%d\n", p->x); return 2; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_array_add();
  if (r == 0) { passed++; } else { failed++; printf("  struct_array_add: FAIL %d\n", r); }

  r = test_struct_array_end();
  if (r == 0) { passed++; } else { failed++; printf("  struct_array_end: FAIL %d\n", r); }

  r = test_struct_array_plus_zero();
  if (r == 0) { passed++; } else { failed++; printf("  struct_array_plus_zero: FAIL %d\n", r); }

  r = test_struct_array_diff();
  if (r == 0) { passed++; } else { failed++; printf("  struct_array_diff: FAIL %d\n", r); }

  r = test_struct_pre_inc();
  if (r == 0) { passed++; } else { failed++; printf("  struct_pre_inc: FAIL %d\n", r); }

  printf("batch86: %d passed, %d failed\n", passed, failed);
  return failed;
}
