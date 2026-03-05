int printf(int *fmt, ...);

// Test 1: (*pp)->field with offset 0
struct Pair { int a; int b; };

int test_deref_ptr_arrow_a() {
  struct Pair s;
  s.a = 10;
  s.b = 20;
  struct Pair *p = &s;
  struct Pair **pp = &p;
  if ((*pp)->a != 10) return 1;
  return 0;
}

// Test 2: (*pp)->field with offset > 0
int test_deref_ptr_arrow_b() {
  struct Pair s;
  s.a = 10;
  s.b = 20;
  struct Pair *p = &s;
  struct Pair **pp = &p;
  if ((*pp)->b != 20) return 1;
  return 0;
}

// Test 3: Write through (*pp)->field
int test_deref_ptr_arrow_write() {
  struct Pair s;
  s.a = 0;
  s.b = 0;
  struct Pair *p = &s;
  struct Pair **pp = &p;
  (*pp)->a = 42;
  (*pp)->b = 99;
  if (s.a != 42) return 1;
  if (s.b != 99) return 2;
  return 0;
}

// Test 4: 3-field struct through double pointer
struct Triple { int x; int y; int z; };

int test_deref_ptr_triple() {
  struct Triple t;
  t.x = 1;
  t.y = 2;
  t.z = 3;
  struct Triple *p = &t;
  struct Triple **pp = &p;
  if ((*pp)->x != 1) return 1;
  if ((*pp)->y != 2) return 2;
  if ((*pp)->z != 3) return 3;
  return 0;
}

// Test 5: (*pp)->char_field with byte access
struct StrBuf { int len; char *data; };

int test_deref_ptr_char_field() {
  struct StrBuf sb;
  sb.len = 5;
  sb.data = "hello";
  struct StrBuf *p = &sb;
  struct StrBuf **pp = &p;
  if ((*pp)->len != 5) return 1;
  if ((*pp)->data[0] != 'h') return 2;
  if ((*pp)->data[4] != 'o') return 3;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_deref_ptr_arrow_a();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: deref_ptr_arrow_a code=%d\n", r); }

  r = test_deref_ptr_arrow_b();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: deref_ptr_arrow_b code=%d\n", r); }

  r = test_deref_ptr_arrow_write();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: deref_ptr_arrow_write code=%d\n", r); }

  r = test_deref_ptr_triple();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: deref_ptr_triple code=%d\n", r); }

  r = test_deref_ptr_char_field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: deref_ptr_char_field code=%d\n", r); }

  printf("batch78: %d passed, %d failed\n", passed, failed);
  return failed;
}
