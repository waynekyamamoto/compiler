int printf(int *fmt, ...);

// Test 1: Struct with char* field, byte access through field
struct Buffer {
  char *data;
  int size;
};

int test_struct_char_field() {
  char hello[] = "hello world";
  struct Buffer buf;
  buf.data = hello;
  buf.size = 11;
  if (buf.data[0] != 'h') return 1;
  if (buf.data[6] != 'w') return 2;
  if (buf.size != 11) return 3;
  return 0;
}

// Test 2: Struct char* field via arrow
int test_struct_char_arrow() {
  char msg[] = "test message";
  struct Buffer buf;
  buf.data = msg;
  buf.size = 12;
  struct Buffer *p = &buf;
  if (p->data[0] != 't') return 1;
  if (p->data[5] != 'm') return 2;
  return 0;
}

// Test 3: Write through struct char* field
int test_struct_char_write() {
  char arr[8];
  struct Buffer buf;
  buf.data = arr;
  buf.data[0] = 'A';
  buf.data[1] = 'B';
  buf.data[2] = 0;
  if (buf.data[0] != 'A') return 1;
  if (buf.data[1] != 'B') return 2;
  if (buf.data[2] != 0) return 3;
  return 0;
}

// Test 4: Struct with multiple char* fields
struct TwoStr {
  char *first;
  char *second;
};

int test_multi_char_fields() {
  struct TwoStr ts;
  ts.first = "hello";
  ts.second = "world";
  if (ts.first[0] != 'h') return 1;
  if (ts.second[0] != 'w') return 2;
  if (ts.first[4] != 'o') return 3;
  if (ts.second[4] != 'd') return 4;
  return 0;
}

// Test 5: Iterate string through struct char* field
int my_strlen_buf(struct Buffer *b) {
  int n = 0;
  while (b->data[n] != 0) n++;
  return n;
}

int test_strlen_through_struct() {
  char s[] = "abcdef";
  struct Buffer buf;
  buf.data = s;
  buf.size = 6;
  int len = my_strlen_buf(&buf);
  if (len != 6) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_char_field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_char_field code=%d\n", r); }

  r = test_struct_char_arrow();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_char_arrow code=%d\n", r); }

  r = test_struct_char_write();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_char_write code=%d\n", r); }

  r = test_multi_char_fields();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multi_char_fields code=%d\n", r); }

  r = test_strlen_through_struct();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: strlen_through_struct code=%d\n", r); }

  printf("batch77: %d passed, %d failed\n", passed, failed);
  return failed;
}
