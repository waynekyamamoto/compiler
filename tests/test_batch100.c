// Test batch 100: proper struct layout sizeof tests
// Must be compiled with -fproper-layout flag

int printf(int *fmt, ...);

struct S1 {
  int a;
  int b;
};

struct S2 {
  int *p;
  int x;
};

struct S3 {
  int a;
  char b[4];
  int c;
};

struct S4 {
  short a;
  int b;
};

struct S5 {
  char a;
  char b;
  short c;
  int d;
};

struct S6 {
  int x;
  long y;
};

struct S7 {
  char a;
  int b;
  char c;
};

struct S8 {
  int *p;
  int a;
  int b;
};

struct S9 {
  int a;
  struct S1 inner;
  int b;
};

int main() {
  int pass = 0;
  int fail = 0;
  int v;

  // S1: two ints = 8 bytes
  v = sizeof(struct S1);
  if (v == 8) { pass++; } else { printf("FAIL S1: expected 8, got %d\n", v); fail++; }

  // S2: pointer(8) + int(4) + padding(4) = 16
  v = sizeof(struct S2);
  if (v == 16) { pass++; } else { printf("FAIL S2: expected 16, got %d\n", v); fail++; }

  // S3: int(4) + char[4](4) + int(4) = 12
  v = sizeof(struct S3);
  if (v == 12) { pass++; } else { printf("FAIL S3: expected 12, got %d\n", v); fail++; }

  // S4: short(2) + pad(2) + int(4) = 8
  v = sizeof(struct S4);
  if (v == 8) { pass++; } else { printf("FAIL S4: expected 8, got %d\n", v); fail++; }

  // S5: char(1) + char(1) + short(2) + int(4) = 8
  v = sizeof(struct S5);
  if (v == 8) { pass++; } else { printf("FAIL S5: expected 8, got %d\n", v); fail++; }

  // S6: int(4) + pad(4) + long(8) = 16
  v = sizeof(struct S6);
  if (v == 16) { pass++; } else { printf("FAIL S6: expected 16, got %d\n", v); fail++; }

  // S7: char(1) + pad(3) + int(4) + char(1) + pad(3) = 12
  v = sizeof(struct S7);
  if (v == 12) { pass++; } else { printf("FAIL S7: expected 12, got %d\n", v); fail++; }

  // S8: ptr(8) + int(4) + int(4) = 16
  v = sizeof(struct S8);
  if (v == 16) { pass++; } else { printf("FAIL S8: expected 16, got %d\n", v); fail++; }

  // S9: int(4) + S1(8) + int(4) = 16
  v = sizeof(struct S9);
  if (v == 16) { pass++; } else { printf("FAIL S9: expected 16, got %d\n", v); fail++; }

  printf("Proper layout sizeof tests: %d passed, %d failed\n", pass, fail);
  if (fail > 0) return 1;
  return 0;
}
