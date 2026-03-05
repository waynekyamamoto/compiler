int printf(int *fmt, ...);
void *malloc(long size);

// Test 1: unsigned function return not corrupted by sxtw
unsigned int hash_str(char *s) {
  unsigned int h = 0;
  while (*s) { h = h * 31 + *s; s++; }
  return h;
}

int test_unsigned_return_no_sxtw() {
  unsigned int h = hash_str("banana");
  // hash("banana") should have bit 31 set
  // If sxtw is wrongly applied, h would become negative when treated as signed
  unsigned int idx = h % 16;
  if (idx >= 16) return 1;
  return 0;
}

// Test 2: unsigned modulo with hash results
int test_unsigned_modulo() {
  // Use hash function to produce large unsigned values
  unsigned int h = hash_str("test_mod");
  unsigned int r = h % 100;
  if (r >= 100) return 1;
  // Verify consistency: same input => same result
  unsigned int h2 = hash_str("test_mod");
  unsigned int r2 = h2 % 100;
  if (r != r2) return 2;
  return 0;
}

// Test 3: unsigned division with hash results
int test_unsigned_division() {
  unsigned int h = hash_str("hello");
  unsigned int d = h / 7;
  unsigned int check = d * 7;
  // check should be <= h and h - check < 7
  if (check > h) return 1;
  unsigned int diff = h - check;
  if (diff >= 7) return 2;
  return 0;
}

// Test 4: unsigned comparison with function returns
int test_unsigned_comparison() {
  unsigned int a = hash_str("abc");
  unsigned int b = hash_str("abd");
  // Both should be non-negative when treated as unsigned
  if (a == b) return 1; // different strings should have different hashes
  // Verify comparison works correctly for unsigned values
  unsigned int small = hash_str("a"); // small hash
  if (small >= 1000000000) return 2; // "a" hash should be small (just 97)
  return 0;
}

// Test 5: hashmap using unsigned hash (the original crash scenario)
struct Entry { char *key; int val; int used; };
struct HashMap { struct Entry entries[16]; int count; };

int my_streq(char *a, char *b) {
  while (*a && *b) { if (*a != *b) return 0; a++; b++; }
  return *a == *b;
}

void hm_init(struct HashMap *m) {
  m->count = 0;
  int i = 0;
  while (i < 16) { m->entries[i].used = 0; i++; }
}

void hm_put(struct HashMap *m, char *key, int val) {
  unsigned int idx = hash_str(key) % 16;
  int i = 0;
  while (i < 16) {
    int j = (idx + i) % 16;
    if (m->entries[j].used == 0 || my_streq(m->entries[j].key, key)) {
      if (m->entries[j].used == 0) m->count++;
      m->entries[j].key = key;
      m->entries[j].val = val;
      m->entries[j].used = 1;
      return;
    }
    i++;
  }
}

int hm_get(struct HashMap *m, char *key) {
  unsigned int idx = hash_str(key) % 16;
  int i = 0;
  while (i < 16) {
    int j = (idx + i) % 16;
    if (m->entries[j].used == 0) return -1;
    if (my_streq(m->entries[j].key, key)) return m->entries[j].val;
    i++;
  }
  return -1;
}

int test_hashmap_unsigned() {
  struct HashMap m;
  hm_init(&m);
  hm_put(&m, "apple", 1);
  hm_put(&m, "banana", 2);
  hm_put(&m, "cherry", 3);
  if (hm_get(&m, "apple") != 1) return 1;
  if (hm_get(&m, "banana") != 2) return 2;
  if (hm_get(&m, "cherry") != 3) return 3;
  if (m.count != 3) return 4;
  hm_put(&m, "apple", 10);
  if (hm_get(&m, "apple") != 10) return 5;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_unsigned_return_no_sxtw();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_return code=%d\n", r); }
  r = test_unsigned_modulo();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_mod code=%d\n", r); }
  r = test_unsigned_division();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_div code=%d\n", r); }
  r = test_unsigned_comparison();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: unsigned_cmp code=%d\n", r); }
  r = test_hashmap_unsigned();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: hashmap code=%d\n", r); }
  printf("batch93: %d passed, %d failed\n", passed, failed);
  return failed;
}
