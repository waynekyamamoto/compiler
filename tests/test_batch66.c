int printf(int *fmt, ...);
int strlen(char *s);
int strcmp(char *a, char *b);

// Test 1: Global char* with string literal - byte read
char *g_str = "hello";

int test_global_char_read() {
  if (g_str[0] != 'h') return 1;
  if (g_str[1] != 'e') return 2;
  if (g_str[4] != 'o') return 3;
  return 0;
}

// Test 2: Global char* dereference
char *g_str2 = "world";

int test_global_char_deref() {
  if (*g_str2 != 'w') return 1;
  return 0;
}

// Test 3: Global char* with strlen
char *g_str3 = "testing";

int test_global_char_strlen() {
  int len = strlen(g_str3);
  if (len != 7) return 1;
  return 0;
}

// Test 4: Global char* reassignment
char *g_str4 = "first";

int test_global_char_reassign() {
  if (g_str4[0] != 'f') return 1;
  g_str4 = "second";
  if (g_str4[0] != 's') return 2;
  if (g_str4[1] != 'e') return 3;
  return 0;
}

// Test 5: Multiple global char* vars
char *g_name = "Alice";
char *g_greeting = "Hello";

int test_multi_global_char() {
  if (g_name[0] != 'A') return 1;
  if (g_greeting[0] != 'H') return 2;
  if (strlen(g_name) != 5) return 3;
  if (strlen(g_greeting) != 5) return 4;
  return 0;
}

// Test 6: Global char* passed to function
char *g_msg = "pass me";

int check_first_char(char *s, int expected) {
  return s[0] == expected;
}

int test_global_char_param() {
  if (check_first_char(g_msg, 'p') != 1) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_global_char_read();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_read code=%d\n", r); }
  r = test_global_char_deref();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_deref code=%d\n", r); }
  r = test_global_char_strlen();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_strlen code=%d\n", r); }
  r = test_global_char_reassign();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_reassign code=%d\n", r); }
  r = test_multi_global_char();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multi_global_char code=%d\n", r); }
  r = test_global_char_param();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_param code=%d\n", r); }
  printf("batch66: %d passed, %d failed\n", passed, failed);
  return failed;
}
