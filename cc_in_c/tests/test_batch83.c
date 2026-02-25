int printf(int *fmt, ...);

// Test 1: *s++ where s is char* (byte dereference then increment)
int test_char_deref_postinc() {
  char *s = "abcde";
  char c = *s++;
  if (c != 'a') { printf("FAIL *s++: c=%d (expected 97)\n", c); return 1; }
  c = *s++;
  if (c != 'b') { printf("FAIL *s++ 2nd: c=%d (expected 98)\n", c); return 2; }
  if (*s != 'c') { printf("FAIL after 2 s++: *s=%d (expected 99)\n", *s); return 3; }
  return 0;
}

// Test 2: String walk with *s++
int my_strlen_walk(char *s) {
  int len = 0;
  while (*s++) len++;
  return len;
}

int test_strlen_walk() {
  int len = my_strlen_walk("hello");
  if (len != 5) { printf("FAIL strlen_walk: len=%d (expected 5)\n", len); return 1; }
  len = my_strlen_walk("");
  if (len != 0) { printf("FAIL strlen_walk empty: len=%d\n", len); return 2; }
  return 0;
}

// Test 3: Copy string via *dst++ = *src++
int test_string_copy() {
  char buf[16];
  char *src = "test";
  char *dst = buf;
  while (*src != 0) {
    *dst++ = *src++;
  }
  *dst = 0;
  if (buf[0] != 't') return 1;
  if (buf[1] != 'e') return 2;
  if (buf[2] != 's') return 3;
  if (buf[3] != 't') return 4;
  if (buf[4] != 0) return 5;
  return 0;
}

// Test 4: *s-- on char pointer
int test_char_deref_postdec() {
  char *s = "xyz";
  s = s + 2;  // point to 'z'
  char c = *s--;
  if (c != 'z') { printf("FAIL *s--: c=%d (expected 122)\n", c); return 1; }
  if (*s != 'y') { printf("FAIL after s--: *s=%d (expected 121)\n", *s); return 2; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_char_deref_postinc();
  if (r == 0) { passed++; } else { failed++; }

  r = test_strlen_walk();
  if (r == 0) { passed++; } else { failed++; }

  r = test_string_copy();
  if (r == 0) { passed++; } else { failed++; }

  r = test_char_deref_postdec();
  if (r == 0) { passed++; } else { failed++; }

  printf("batch83: %d passed, %d failed\n", passed, failed);
  return failed;
}
