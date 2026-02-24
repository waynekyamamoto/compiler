int printf(int *fmt, ...);
void *malloc(int size);

// Test 1: Basic flexible array member
struct Header {
  int len;
  int type;
  int data[];
};

int test_basic_fam() {
  struct Header *h = malloc(64);
  h->len = 3;
  h->type = 42;
  h->data[0] = 10;
  h->data[1] = 20;
  h->data[2] = 30;
  if (h->len != 3) return 1;
  if (h->type != 42) return 2;
  if (h->data[0] != 10) return 3;
  if (h->data[1] != 20) return 4;
  if (h->data[2] != 30) return 5;
  return 0;
}

// Test 2: Fixed-size array in struct (not FAM, but should also work)
struct Fixed {
  int count;
  int vals[4];
};

int test_fixed_array() {
  struct Fixed *f = malloc(64);
  f->count = 4;
  f->vals[0] = 100;
  f->vals[1] = 200;
  f->vals[2] = 300;
  f->vals[3] = 400;
  if (f->count != 4) return 1;
  if (f->vals[0] != 100) return 2;
  if (f->vals[1] != 200) return 3;
  if (f->vals[2] != 300) return 4;
  if (f->vals[3] != 400) return 5;
  return 0;
}

// Test 3: Multiple fields before FAM
struct Multi {
  int a;
  int b;
  int c;
  int items[];
};

int test_multi_field_fam() {
  struct Multi *m = malloc(128);
  m->a = 1;
  m->b = 2;
  m->c = 3;
  m->items[0] = 10;
  m->items[1] = 20;
  m->items[2] = 30;
  m->items[3] = 40;
  if (m->a != 1) return 1;
  if (m->b != 2) return 2;
  if (m->c != 3) return 3;
  if (m->items[0] != 10) return 4;
  if (m->items[1] != 20) return 5;
  if (m->items[2] != 30) return 6;
  if (m->items[3] != 40) return 7;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_basic_fam();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: basic_fam (code %d)\n", r); }

  r = test_fixed_array();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: fixed_array (code %d)\n", r); }

  r = test_multi_field_fam();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multi_field_fam (code %d)\n", r); }

  printf("batch60: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
