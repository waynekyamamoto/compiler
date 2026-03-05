// Test batch 101: proper struct layout field access tests
// Must be compiled with -fproper-layout flag
// Tests struct field access via pointers with proper byte offsets

int printf(int *fmt, ...);
int *malloc(int size);

struct Mixed {
  int a;
  int b;
  int *p;
  int c;
};

struct Small {
  short x;
  short y;
};

struct WithPtr {
  int *data;
  int count;
};

int main() {
  int pass = 0;
  int fail = 0;

  // Test 1: Arrow access on malloc'd struct
  struct Mixed *m = malloc(sizeof(struct Mixed));
  m->a = 10;
  m->b = 20;
  m->p = 0;
  m->c = 30;
  if (m->a == 10) { pass++; } else { printf("FAIL 1: a=%d\n", m->a); fail++; }
  if (m->b == 20) { pass++; } else { printf("FAIL 2: b=%d\n", m->b); fail++; }
  if (m->c == 30) { pass++; } else { printf("FAIL 3: c=%d\n", m->c); fail++; }

  // Test 2: sizeof checks
  if (sizeof(struct Mixed) == 24) { pass++; } else { printf("FAIL 4: sizeof Mixed=%d\n", sizeof(struct Mixed)); fail++; }
  if (sizeof(struct Small) == 4) { pass++; } else { printf("FAIL 5: sizeof Small=%d\n", sizeof(struct Small)); fail++; }
  if (sizeof(struct WithPtr) == 16) { pass++; } else { printf("FAIL 6: sizeof WithPtr=%d\n", sizeof(struct WithPtr)); fail++; }

  // Test 3: Array of structs stride
  struct Small *arr = malloc(sizeof(struct Small) * 4);
  arr[0].x = 1;
  arr[0].y = 2;
  arr[1].x = 3;
  arr[1].y = 4;
  arr[2].x = 5;
  arr[2].y = 6;
  if (arr[0].x == 1) { pass++; } else { printf("FAIL 7: arr[0].x=%d\n", arr[0].x); fail++; }
  if (arr[1].x == 3) { pass++; } else { printf("FAIL 8: arr[1].x=%d\n", arr[1].x); fail++; }
  if (arr[2].y == 6) { pass++; } else { printf("FAIL 9: arr[2].y=%d\n", arr[2].y); fail++; }

  // Test 4: Pointer arithmetic with proper stride
  struct Small *p2 = arr + 2;
  if (p2->x == 5) { pass++; } else { printf("FAIL 10: p2->x=%d\n", p2->x); fail++; }

  printf("Proper layout field access: %d passed, %d failed\n", pass, fail);
  if (fail > 0) return 1;
  return 0;
}
