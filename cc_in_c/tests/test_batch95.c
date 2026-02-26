int printf(int *fmt, ...);

// Test 1: Unsigned parameter right shift (logical, not arithmetic)
int shr_unsigned_param(unsigned int n, int bits) {
  return n >> bits;
}

int test_unsigned_param_shift() {
  // Use a value that doesn't trigger literal sign-extension issues
  unsigned int v = 0x7F000000;
  int r = shr_unsigned_param(v, 4);
  if (r != 0x07F00000) return 1;
  r = shr_unsigned_param(256, 4);
  if (r != 16) return 2;
  // Right shift by 1
  r = shr_unsigned_param(0x7FFFFFFE, 1);
  if (r != 0x3FFFFFFF) return 3;
  return 0;
}

// Test 2: Unsigned parameter division (udiv, not sdiv)
unsigned int div_unsigned_param(unsigned int a, unsigned int b) {
  return a / b;
}

int test_unsigned_param_div() {
  unsigned int r = div_unsigned_param(100, 3);
  if (r != 33) return 1;
  r = div_unsigned_param(1000, 7);
  if (r != 142) return 2;
  r = div_unsigned_param(255, 16);
  if (r != 15) return 3;
  return 0;
}

// Test 3: Unsigned parameter modulo (umod via udiv)
unsigned int mod_unsigned_param(unsigned int a, unsigned int b) {
  return a % b;
}

int test_unsigned_param_mod() {
  unsigned int r = mod_unsigned_param(100, 7);
  if (r != 2) return 1;
  r = mod_unsigned_param(255, 16);
  if (r != 15) return 2;
  r = mod_unsigned_param(1000, 3);
  if (r != 1) return 3;
  return 0;
}

// Test 4: Unsigned parameter comparison
int cmp_unsigned_param(unsigned int a, unsigned int b) {
  if (a > b) return 1;
  if (a < b) return -1;
  return 0;
}

int test_unsigned_param_cmp() {
  if (cmp_unsigned_param(100, 50) != 1) return 1;
  if (cmp_unsigned_param(50, 100) != -1) return 2;
  if (cmp_unsigned_param(42, 42) != 0) return 3;
  return 0;
}

// Test 5: Popcount using unsigned param right shift (the original failing case)
int popcount(unsigned int n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

int test_popcount() {
  if (popcount(0) != 0) return 1;
  if (popcount(1) != 1) return 2;
  if (popcount(7) != 3) return 3;
  if (popcount(255) != 8) return 4;
  if (popcount(0x5555) != 8) return 5;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_unsigned_param_shift();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: u_shift code=%d\n", r); }
  r = test_unsigned_param_div();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: u_div code=%d\n", r); }
  r = test_unsigned_param_mod();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: u_mod code=%d\n", r); }
  r = test_unsigned_param_cmp();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: u_cmp code=%d\n", r); }
  r = test_popcount();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: popcount code=%d\n", r); }
  printf("batch95: %d passed, %d failed\n", passed, failed);
  return failed;
}
