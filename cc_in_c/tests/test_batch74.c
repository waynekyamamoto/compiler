int printf(int *fmt, ...);

// Helper: byte-level memcpy
void my_memcpy(char *dst, char *src, int n) {
  int i;
  for (i = 0; i < n; i++) {
    dst[i] = src[i];
  }
}

// Test 1: char local array with string init, byte access
int test_char_arr_str_init() {
  char s[] = "hello";
  if (s[0] != 'h') return 1;
  if (s[1] != 'e') return 2;
  if (s[4] != 'o') return 3;
  if (s[5] != 0) return 4;
  return 0;
}

// Test 2: char local array with memcpy
int test_char_arr_memcpy() {
  char *src = "world";
  char dst[16];
  my_memcpy(dst, src, 6);
  if (dst[0] != 'w') return 1;
  if (dst[4] != 'd') return 2;
  if (dst[5] != 0) return 3;
  return 0;
}

// Test 3: char local array write and read back
int test_char_arr_rw() {
  char buf[8];
  buf[0] = 'A';
  buf[1] = 'B';
  buf[2] = 'C';
  buf[3] = 0;
  if (buf[0] != 'A') return 1;
  if (buf[1] != 'B') return 2;
  if (buf[2] != 'C') return 3;
  if (buf[3] != 0) return 4;
  return 0;
}

// Test 4: char local array passed to function
int count_chars(char *s) {
  int n = 0;
  while (s[n] != 0) n++;
  return n;
}

int test_char_arr_pass() {
  char s[] = "test";
  int len = count_chars(s);
  if (len != 4) return 1;
  return 0;
}

// Test 5: Multiple char local arrays
int test_multi_char_arr() {
  char a[] = "abc";
  char b[] = "xyz";
  if (a[0] != 'a') return 1;
  if (b[0] != 'x') return 2;
  if (a[2] != 'c') return 3;
  if (b[2] != 'z') return 4;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_char_arr_str_init();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_str_init code=%d\n", r); }

  r = test_char_arr_memcpy();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_memcpy code=%d\n", r); }

  r = test_char_arr_rw();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_rw code=%d\n", r); }

  r = test_char_arr_pass();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_pass code=%d\n", r); }

  r = test_multi_char_arr();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multi_char_arr code=%d\n", r); }

  printf("batch74: %d passed, %d failed\n", passed, failed);
  return failed;
}
