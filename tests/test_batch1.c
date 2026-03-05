int printf(int *fmt, ...);

int test_xor() {
  int a;
  a = 5 ^ 3;
  if (a != 6) {
    printf("FAIL: 5 ^ 3 = %d, expected 6\n", a);
    return 1;
  }
  a = 0xFF ^ 0x0F;
  if (a != 240) {
    printf("FAIL: 0xFF ^ 0x0F = %d, expected 240\n", a);
    return 1;
  }
  return 0;
}

int test_shifts() {
  int a;
  a = 1 << 4;
  if (a != 16) {
    printf("FAIL: 1 << 4 = %d, expected 16\n", a);
    return 1;
  }
  a = 32 >> 3;
  if (a != 4) {
    printf("FAIL: 32 >> 3 = %d, expected 4\n", a);
    return 1;
  }
  a = 7 << 0;
  if (a != 7) {
    printf("FAIL: 7 << 0 = %d, expected 7\n", a);
    return 1;
  }
  return 0;
}

int test_preinc() {
  int x;
  int y;
  x = 5;
  y = ++x;
  if (x != 6) {
    printf("FAIL: ++x, x = %d, expected 6\n", x);
    return 1;
  }
  if (y != 6) {
    printf("FAIL: ++x returned %d, expected 6\n", y);
    return 1;
  }
  return 0;
}

int test_predec() {
  int x;
  int y;
  x = 5;
  y = --x;
  if (x != 4) {
    printf("FAIL: --x, x = %d, expected 4\n", x);
    return 1;
  }
  if (y != 4) {
    printf("FAIL: --x returned %d, expected 4\n", y);
    return 1;
  }
  return 0;
}

int test_compound() {
  int x;
  x = 10;
  x += 5;
  if (x != 15) { printf("FAIL: += got %d\n", x); return 1; }
  x -= 3;
  if (x != 12) { printf("FAIL: -= got %d\n", x); return 1; }
  x *= 2;
  if (x != 24) { printf("FAIL: *= got %d\n", x); return 1; }
  x /= 6;
  if (x != 4) { printf("FAIL: /= got %d\n", x); return 1; }
  x %= 3;
  if (x != 1) { printf("FAIL: %%= got %d\n", x); return 1; }
  x = 0xFF;
  x &= 0x0F;
  if (x != 15) { printf("FAIL: &= got %d\n", x); return 1; }
  x |= 0xF0;
  if (x != 255) { printf("FAIL: |= got %d\n", x); return 1; }
  x ^= 0xFF;
  if (x != 0) { printf("FAIL: ^= got %d\n", x); return 1; }
  return 0;
}

int test_hex() {
  int a;
  a = 0xFF;
  if (a != 255) { printf("FAIL: 0xFF = %d\n", a); return 1; }
  a = 0x10;
  if (a != 16) { printf("FAIL: 0x10 = %d\n", a); return 1; }
  a = 0xABCD;
  if (a != 43981) { printf("FAIL: 0xABCD = %d\n", a); return 1; }
  a = 0x0;
  if (a != 0) { printf("FAIL: 0x0 = %d\n", a); return 1; }
  return 0;
}

int test_bitnot() {
  int a;
  a = ~0;
  if (a != -1) { printf("FAIL: ~0 = %d\n", a); return 1; }
  a = ~(-1);
  if (a != 0) { printf("FAIL: ~(-1) = %d\n", a); return 1; }
  a = ~0xFF;
  if (a != -256) { printf("FAIL: ~0xFF = %d\n", a); return 1; }
  return 0;
}

int main() {
  int fail;
  fail = 0;
  fail = fail + test_xor();
  fail = fail + test_shifts();
  fail = fail + test_preinc();
  fail = fail + test_predec();
  fail = fail + test_compound();
  fail = fail + test_hex();
  fail = fail + test_bitnot();
  if (fail == 0) {
    printf("batch1: all tests passed\n");
  } else {
    printf("batch1: %d test(s) FAILED\n", fail);
  }
  return fail;
}
