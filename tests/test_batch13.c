// Test batch 13: Pointer-to-struct arithmetic

int printf(int *fmt, ...);
int *malloc(int size);

struct Point {
  int x;
  int y;
};

// Test p + n (pointer plus integer)
int test_ptr_plus() {
  struct Point arr[4];
  arr[0].x = 10; arr[0].y = 11;
  arr[1].x = 20; arr[1].y = 21;
  arr[2].x = 30; arr[2].y = 31;
  arr[3].x = 40; arr[3].y = 41;

  struct Point *p = &arr[0];
  struct Point *q = p + 2;
  if (q->x != 30) return 1;
  if (q->y != 31) return 2;
  q = p + 3;
  if (q->x != 40) return 3;
  return 0;
}

// Test p - n (pointer minus integer)
int test_ptr_minus() {
  struct Point arr[4];
  arr[0].x = 10; arr[0].y = 11;
  arr[1].x = 20; arr[1].y = 21;
  arr[2].x = 30; arr[2].y = 31;
  arr[3].x = 40; arr[3].y = 41;

  struct Point *p = &arr[3];
  struct Point *q = p - 2;
  if (q->x != 20) return 1;
  if (q->y != 21) return 2;
  return 0;
}

// Test p[i] (index operator)
int test_ptr_index() {
  struct Point arr[3];
  arr[0].x = 100; arr[0].y = 101;
  arr[1].x = 200; arr[1].y = 201;
  arr[2].x = 300; arr[2].y = 301;

  struct Point *p = &arr[0];
  if (p[0].x != 100) return 1;
  if (p[1].x != 200) return 2;
  if (p[2].y != 301) return 3;
  return 0;
}

// Test p++ and p-- (post-increment/decrement)
int test_ptr_postinc() {
  struct Point arr[3];
  arr[0].x = 1; arr[0].y = 2;
  arr[1].x = 3; arr[1].y = 4;
  arr[2].x = 5; arr[2].y = 6;

  struct Point *p = &arr[0];
  struct Point *old = p++;
  if (old->x != 1) return 1;
  if (p->x != 3) return 2;
  p++;
  if (p->x != 5) return 3;
  p--;
  if (p->x != 3) return 4;
  return 0;
}

// Test ++p and --p (pre-increment/decrement, desugared to p = p + 1)
int test_ptr_preinc() {
  struct Point arr[3];
  arr[0].x = 10; arr[0].y = 20;
  arr[1].x = 30; arr[1].y = 40;
  arr[2].x = 50; arr[2].y = 60;

  struct Point *p = &arr[0];
  ++p;
  if (p->x != 30) return 1;
  ++p;
  if (p->x != 50) return 2;
  --p;
  if (p->x != 30) return 3;
  return 0;
}

// Test p += n and p -= n (compound assignment)
int test_ptr_compound() {
  struct Point arr[4];
  arr[0].x = 1; arr[0].y = 2;
  arr[1].x = 3; arr[1].y = 4;
  arr[2].x = 5; arr[2].y = 6;
  arr[3].x = 7; arr[3].y = 8;

  struct Point *p = &arr[0];
  p += 2;
  if (p->x != 5) return 1;
  p -= 1;
  if (p->x != 3) return 2;
  p += 2;
  if (p->x != 7) return 3;
  return 0;
}

// Test with malloc'd buffer
int test_ptr_malloc() {
  struct Point *pts = malloc(3 * 2 * 8);
  struct Point *p = pts;
  p->x = 11; p->y = 12;
  p++;
  p->x = 21; p->y = 22;
  p++;
  p->x = 31; p->y = 32;

  if (pts[0].x != 11) return 1;
  if (pts[1].x != 21) return 2;
  if (pts[2].y != 32) return 3;

  struct Point *q = pts + 1;
  if (q->x != 21) return 4;
  return 0;
}

int main() {
  int fail = 0;
  int r = 0;

  r = test_ptr_plus();
  if (r != 0) { printf("FAIL test_ptr_plus: %d\n", r); fail = 1; }

  r = test_ptr_minus();
  if (r != 0) { printf("FAIL test_ptr_minus: %d\n", r); fail = 1; }

  r = test_ptr_index();
  if (r != 0) { printf("FAIL test_ptr_index: %d\n", r); fail = 1; }

  r = test_ptr_postinc();
  if (r != 0) { printf("FAIL test_ptr_postinc: %d\n", r); fail = 1; }

  r = test_ptr_preinc();
  if (r != 0) { printf("FAIL test_ptr_preinc: %d\n", r); fail = 1; }

  r = test_ptr_compound();
  if (r != 0) { printf("FAIL test_ptr_compound: %d\n", r); fail = 1; }

  r = test_ptr_malloc();
  if (r != 0) { printf("FAIL test_ptr_malloc: %d\n", r); fail = 1; }

  if (fail == 0) {
    printf("All batch 13 tests passed.\n");
  }
  return fail;
}
