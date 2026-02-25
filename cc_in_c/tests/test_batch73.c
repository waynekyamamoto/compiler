int printf(int *fmt, ...);

// Test 1: char* array - basic double indexing
int test_char_arr_basic() {
  char *names[4];
  names[0] = "alpha";
  names[1] = "beta";
  names[2] = "gamma";
  names[3] = "delta";
  if (names[0][0] != 'a') return 1;
  if (names[1][0] != 'b') return 2;
  if (names[2][0] != 'g') return 3;
  if (names[3][0] != 'd') return 4;
  return 0;
}

// Test 2: char* array - single index returns pointer, not byte
int test_char_arr_ptr_load() {
  char *arr[2];
  arr[0] = "hello";
  arr[1] = "world";
  // arr[0] should be a valid pointer, not a byte
  char *s = arr[0];
  if (s[0] != 'h') return 1;
  if (s[4] != 'o') return 2;
  char *t = arr[1];
  if (t[0] != 'w') return 3;
  return 0;
}

// Test 3: char* array - iterate characters
int test_char_arr_iterate() {
  char *words[3];
  words[0] = "ab";
  words[1] = "cd";
  words[2] = "ef";
  int sum = 0;
  int i; int j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      sum += words[i][j];
    }
  }
  // a=97,b=98,c=99,d=100,e=101,f=102 = 597
  if (sum != 597) return 1;
  return 0;
}

// Test 4: char* array assignment stores pointer, not byte
int test_char_arr_store() {
  char *arr[2];
  arr[0] = "hello";
  // Reassign
  arr[0] = "world";
  if (arr[0][0] != 'w') return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_char_arr_basic();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_basic code=%d\n", r); }

  r = test_char_arr_ptr_load();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_ptr_load code=%d\n", r); }

  r = test_char_arr_iterate();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_iterate code=%d\n", r); }

  r = test_char_arr_store();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_arr_store code=%d\n", r); }

  printf("batch73: %d passed, %d failed\n", passed, failed);
  return failed;
}
