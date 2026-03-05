// Test batch 102: proper struct layout - struct copy and field stores
// Must be compiled with -fproper-layout flag

int printf(int *fmt, ...);
int *malloc(int size);

struct Pair {
  int x;
  int y;
};

struct WithShort {
  short a;
  short b;
  int c;
};

int main() {
  int pass = 0;
  int fail = 0;

  // Test 1: struct copy via pointer
  struct Pair *a = malloc(sizeof(struct Pair));
  struct Pair *b = malloc(sizeof(struct Pair));
  a->x = 100;
  a->y = 200;
  *b = *a;
  if (b->x == 100) { pass++; } else { printf("FAIL 1: b->x=%d\n", b->x); fail++; }
  if (b->y == 200) { pass++; } else { printf("FAIL 2: b->y=%d\n", b->y); fail++; }

  // Test 2: struct array post-increment
  struct Pair *arr = malloc(sizeof(struct Pair) * 3);
  struct Pair *p = arr;
  p->x = 10;
  p->y = 11;
  p++;
  p->x = 20;
  p->y = 21;
  p++;
  p->x = 30;
  p->y = 31;
  if (arr[0].x == 10) { pass++; } else { printf("FAIL 3: arr[0].x=%d\n", arr[0].x); fail++; }
  if (arr[1].x == 20) { pass++; } else { printf("FAIL 4: arr[1].x=%d\n", arr[1].x); fail++; }
  if (arr[2].y == 31) { pass++; } else { printf("FAIL 5: arr[2].y=%d\n", arr[2].y); fail++; }

  printf("Struct copy/store tests: %d passed, %d failed\n", pass, fail);
  if (fail > 0) return 1;
  return 0;
}
