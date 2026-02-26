int printf(int *fmt, ...);

// Test 1: Struct with char *ptrs[] array field - read
struct Foo {
  char *ptrs[4];
  int count;
};

int test_char_ptr_array_read() {
  struct Foo f;
  f.ptrs[0] = "hello";
  f.ptrs[1] = "world";
  f.count = 2;
  char *s = f.ptrs[0];
  if (s[0] != 'h') return 1;
  char *s2 = f.ptrs[1];
  if (s2[0] != 'w') return 2;
  if (f.count != 2) return 3;
  return 0;
}

// Test 2: Struct with char *ptrs[] array field - multiple entries
int test_char_ptr_array_multi() {
  struct Foo f;
  f.ptrs[0] = "abc";
  f.ptrs[1] = "def";
  f.ptrs[2] = "ghi";
  f.count = 3;
  char *s0 = f.ptrs[0];
  char *s1 = f.ptrs[1];
  char *s2 = f.ptrs[2];
  if (s0[0] != 'a') return 1;
  if (s1[1] != 'e') return 2;
  if (s2[2] != 'i') return 3;
  if (f.count != 3) return 4;
  return 0;
}

// Test 3: Struct with char * (scalar) field still works with byte ops
struct Buffer {
  char *data;
  int len;
};

int test_char_ptr_scalar_field() {
  char hello[] = "hello";
  struct Buffer buf;
  buf.data = hello;
  buf.len = 5;
  if (buf.data[0] != 'h') return 1;
  if (buf.data[4] != 'o') return 2;
  buf.data[0] = 'H';
  if (buf.data[0] != 'H') return 3;
  return 0;
}

// Test 4: Arrow access to char *ptrs[] field
int test_char_ptr_array_arrow() {
  struct Foo f;
  f.ptrs[0] = "test";
  f.count = 1;
  struct Foo *p = &f;
  char *s = p->ptrs[0];
  if (s[0] != 't') return 1;
  if (s[3] != 't') return 2;
  return 0;
}

// Test 5: Mixed char * scalar and char *[] array fields
struct Mixed {
  char *name;
  char *tags[3];
  int ntags;
};

int test_mixed_char_fields() {
  struct Mixed m;
  m.name = "item";
  m.tags[0] = "red";
  m.tags[1] = "blue";
  m.ntags = 2;
  if (m.name[0] != 'i') return 1;
  char *t = m.tags[0];
  if (t[0] != 'r') return 2;
  char *t2 = m.tags[1];
  if (t2[0] != 'b') return 3;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_char_ptr_array_read();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_array_read code=%d\n", r); }

  r = test_char_ptr_array_multi();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_array_multi code=%d\n", r); }

  r = test_char_ptr_scalar_field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_scalar_field code=%d\n", r); }

  r = test_char_ptr_array_arrow();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_array_arrow code=%d\n", r); }

  r = test_mixed_char_fields();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: mixed_char_fields code=%d\n", r); }

  printf("batch92: %d passed, %d failed\n", passed, failed);
  return failed;
}
