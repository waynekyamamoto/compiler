int printf(int *fmt, ...);
void *malloc(int size);

// Test 1: Array of char* - read bytes through double index
int test_char_ptr_arr_read() {
  char *names[4];
  names[0] = "Alice";
  names[1] = "Bob";
  names[2] = "Charlie";
  names[3] = "Dave";
  if (names[0][0] != 'A') return 1;
  if (names[1][0] != 'B') return 2;
  if (names[2][0] != 'C') return 3;
  if (names[3][0] != 'D') return 4;
  if (names[0][4] != 'e') return 5;
  return 0;
}

// Test 2: Array of char* - write bytes through double index
int test_char_ptr_arr_write() {
  char *bufs[2];
  bufs[0] = malloc(16);
  bufs[1] = malloc(16);
  bufs[0][0] = 'X';
  bufs[0][1] = 'Y';
  bufs[0][2] = 0;
  bufs[1][0] = 'A';
  bufs[1][1] = 'B';
  bufs[1][2] = 0;
  if (bufs[0][0] != 'X') return 1;
  if (bufs[0][1] != 'Y') return 2;
  if (bufs[1][0] != 'A') return 3;
  if (bufs[1][1] != 'B') return 4;
  return 0;
}

// Test 3: Array of char* - loop over strings
int test_char_ptr_arr_loop() {
  char *words[3];
  words[0] = "hi";
  words[1] = "ok";
  words[2] = "no";
  int i;
  for (i = 0; i < 3; i++) {
    if (words[i][0] < 'a' || words[i][0] > 'z') return i + 1;
  }
  return 0;
}

// Test 4: Deref of char* array element (*names[i])
int test_char_ptr_arr_deref() {
  char *strs[3];
  strs[0] = "abc";
  strs[1] = "xyz";
  strs[2] = "123";
  if (*strs[0] != 'a') return 1;
  if (*strs[1] != 'x') return 2;
  if (*strs[2] != '1') return 3;
  return 0;
}

// Test 5: Copy char* from array to local var
int test_char_ptr_arr_copy() {
  char *arr[2];
  arr[0] = "hello";
  arr[1] = "world";
  char *s = arr[0];
  if (s[0] != 'h') return 1;
  s = arr[1];
  if (s[0] != 'w') return 2;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_char_ptr_arr_read();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_arr_read code=%d\n", r); }
  r = test_char_ptr_arr_write();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_arr_write code=%d\n", r); }
  r = test_char_ptr_arr_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_arr_loop code=%d\n", r); }
  r = test_char_ptr_arr_deref();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_arr_deref code=%d\n", r); }
  r = test_char_ptr_arr_copy();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_arr_copy code=%d\n", r); }
  printf("batch69: %d passed, %d failed\n", passed, failed);
  return failed;
}
