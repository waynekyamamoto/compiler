int printf(int *fmt, ...);
void *malloc(int size);

// Test 1: char* field byte access through arrow
struct Buf {
  char *data;
  int len;
};

int test_char_field_read() {
  struct Buf b;
  b.data = "hello";
  b.len = 5;
  if (b.data[0] != 'h') return 1;
  if (b.data[1] != 'e') return 2;
  if (b.data[4] != 'o') return 3;
  return 0;
}

// Test 2: char* field write through pointer
int test_char_field_write() {
  struct Buf *b = malloc(24);
  b->data = malloc(16);
  b->data[0] = 'A';
  b->data[1] = 'B';
  b->data[2] = 0;
  if (b->data[0] != 'A') return 1;
  if (b->data[1] != 'B') return 2;
  return 0;
}

// Test 3: Lexer-like pattern
struct Lexer {
  char *input;
  int pos;
};

int lex_peek(struct Lexer *l) {
  return l->input[l->pos];
}

int test_lexer_pattern() {
  struct Lexer l;
  l.input = "abc";
  l.pos = 0;
  if (lex_peek(&l) != 'a') return 1;
  l.pos = 1;
  if (lex_peek(&l) != 'b') return 2;
  l.pos = 2;
  if (lex_peek(&l) != 'c') return 3;
  return 0;
}

// Test 4: Skip whitespace pattern
void skip_ws(struct Lexer *l) {
  while (l->input[l->pos] == ' ' || l->input[l->pos] == '\t') {
    l->pos++;
  }
}

int test_skip_ws() {
  struct Lexer l;
  l.input = "  \thello";
  l.pos = 0;
  skip_ws(&l);
  if (l.pos != 3) return 1;
  if (l.input[l.pos] != 'h') return 2;
  return 0;
}

// Test 5: Count chars
int count_char(struct Lexer *l, int ch) {
  int count = 0;
  int i = 0;
  while (l->input[i] != 0) {
    if (l->input[i] == ch) count++;
    i++;
  }
  return count;
}

int test_count() {
  struct Lexer l;
  l.input = "abracadabra";
  l.pos = 0;
  if (count_char(&l, 'a') != 5) return 1;
  if (count_char(&l, 'b') != 2) return 2;
  if (count_char(&l, 'z') != 0) return 3;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_char_field_read();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_field_read code=%d\n", r); }

  r = test_char_field_write();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: char_field_write code=%d\n", r); }

  r = test_lexer_pattern();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: lexer_pattern code=%d\n", r); }

  r = test_skip_ws();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: skip_ws code=%d\n", r); }

  r = test_count();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: count code=%d\n", r); }

  printf("batch64: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
