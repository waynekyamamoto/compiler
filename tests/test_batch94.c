int printf(int *fmt, ...);
void *malloc(long size);
void free(void *ptr);

// Test 1: struct with char* field - indexing uses correct stride
struct Token {
  char *text;
  int type;
};

int tokenize(char *input, struct Token *tokens) {
  int ntok = 0;
  while (*input) {
    if (*input == ' ') { input++; continue; }
    if (*input >= '0' && *input <= '9') {
      tokens[ntok].text = input;
      tokens[ntok].type = 0;
      while (*input >= '0' && *input <= '9') input++;
      ntok++;
    } else {
      tokens[ntok].text = input;
      tokens[ntok].type = 1;
      input++;
      ntok++;
    }
  }
  return ntok;
}

int test_struct_char_field_stride() {
  struct Token tokens[16];
  int n = tokenize("12 + 34", tokens);
  if (n != 3) return 1;
  if (tokens[0].type != 0) return 2;
  if (tokens[1].type != 1) return 3;
  if (tokens[2].type != 0) return 4;
  char *t = tokens[0].text;
  if (t[0] != '1') return 5;
  t = tokens[1].text;
  if (t[0] != '+') return 6;
  return 0;
}

// Test 2: char** local variable - indexing uses pointer stride, not byte stride
int test_char_ptr_ptr_stride() {
  char **table = malloc(4 * 8);
  table[0] = "hello";
  table[1] = "world";
  table[2] = "foo";
  table[3] = "bar";
  char *s = table[0];
  if (s[0] != 'h') return 1;
  s = table[1];
  if (s[0] != 'w') return 2;
  s = table[3];
  if (s[2] != 'r') return 3;
  free(table);
  return 0;
}

// Test 3: struct with char* after another type - last_type_is_char reset
struct Entry {
  int id;
  char *name;
};

int fill_entry(int id, char *name, struct Entry *e) {
  e->id = id;
  e->name = name;
  return 0;
}

int test_struct_type_reset() {
  struct Entry entries[3];
  fill_entry(1, "alice", &entries[0]);
  fill_entry(2, "bob", &entries[1]);
  fill_entry(3, "charlie", &entries[2]);
  if (entries[0].id != 1) return 1;
  if (entries[1].id != 2) return 2;
  if (entries[2].id != 3) return 3;
  char *n = entries[0].name;
  if (n[0] != 'a') return 4;
  n = entries[2].name;
  if (n[0] != 'c') return 5;
  return 0;
}

// Test 4: Function with char* param followed by struct* param
// (tests that last_type_is_char is properly reset between params)
struct Pair { int a; int b; };

void set_pair(char *label, struct Pair *p, int a, int b) {
  p->a = a;
  p->b = b;
}

int test_param_type_reset() {
  struct Pair pairs[3];
  set_pair("first", &pairs[0], 10, 20);
  set_pair("second", &pairs[1], 30, 40);
  set_pair("third", &pairs[2], 50, 60);
  if (pairs[0].a != 10) return 1;
  if (pairs[0].b != 20) return 2;
  if (pairs[1].a != 30) return 3;
  if (pairs[2].b != 60) return 4;
  return 0;
}

// Test 5: char** parameter - should not use byte stride
void fill_table(char **table, int n) {
  table[0] = "zero";
  table[1] = "one";
  table[2] = "two";
}

int test_char_ptr_ptr_param() {
  char **t = malloc(3 * 8);
  fill_table(t, 3);
  char *s = t[0];
  if (s[0] != 'z') return 1;
  s = t[1];
  if (s[0] != 'o') return 2;
  s = t[2];
  if (s[0] != 't') return 3;
  free(t);
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_struct_char_field_stride();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_field_stride code=%d\n", r); }
  r = test_char_ptr_ptr_stride();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_ptr_ptr code=%d\n", r); }
  r = test_struct_type_reset();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: type_reset code=%d\n", r); }
  r = test_param_type_reset();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: param_reset code=%d\n", r); }
  r = test_char_ptr_ptr_param();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: ptr_ptr_param code=%d\n", r); }
  printf("batch94: %d passed, %d failed\n", passed, failed);
  return failed;
}
