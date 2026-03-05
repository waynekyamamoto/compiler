int printf(int *fmt, ...);

// Test global char pointer operations

char *gmsg;

// Test 1: Index global char pointer
int test_global_char_index() {
  gmsg = "hello";
  if (gmsg[0] != 104) { printf("FAIL gcp idx0: %d\n", gmsg[0]); return 1; }
  if (gmsg[4] != 111) { printf("FAIL gcp idx4: %d\n", gmsg[4]); return 1; }
  return 0;
}

// Test 2: Reassign global char pointer
int test_global_char_reassign() {
  gmsg = "hello";
  if (gmsg[0] != 104) { printf("FAIL reassign1\n"); return 1; }
  gmsg = "world";
  if (gmsg[0] != 119) { printf("FAIL reassign2: %d\n", gmsg[0]); return 1; }
  return 0;
}

// Test 3: Deref global char pointer
int test_global_char_deref() {
  gmsg = "ABC";
  int ch = *gmsg;
  if (ch != 65) { printf("FAIL deref: %d\n", ch); return 1; }
  return 0;
}

// Test 4: Global char pointer arithmetic
int test_global_char_arith() {
  gmsg = "ABCDE";
  char *p = gmsg + 2;
  if (*p != 67) { printf("FAIL arith: %d\n", *p); return 1; }
  return 0;
}

// Test 5: Global char pointer in loop
int test_global_char_loop() {
  gmsg = "Hello";
  int len = 0;
  while (gmsg[len]) {
    len = len + 1;
  }
  if (len != 5) { printf("FAIL loop len: %d\n", len); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_global_char_index();
  if (r == 0) { passed++; } else { failed++; printf("  global_char_index: FAIL\n"); }

  r = test_global_char_reassign();
  if (r == 0) { passed++; } else { failed++; printf("  global_char_reassign: FAIL\n"); }

  r = test_global_char_deref();
  if (r == 0) { passed++; } else { failed++; printf("  global_char_deref: FAIL\n"); }

  r = test_global_char_arith();
  if (r == 0) { passed++; } else { failed++; printf("  global_char_arith: FAIL\n"); }

  r = test_global_char_loop();
  if (r == 0) { passed++; } else { failed++; printf("  global_char_loop: FAIL\n"); }

  printf("batch89: %d passed, %d failed\n", passed, failed);
  return failed;
}
