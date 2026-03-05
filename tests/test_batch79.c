int printf(int *fmt, ...);

// Test 1: Global struct array - basic field access
struct Entry { int key; int val; };
struct Entry g_table[4];

int test_global_struct_array_basic() {
  g_table[0].key = 10;
  g_table[0].val = 100;
  g_table[1].key = 20;
  g_table[1].val = 200;
  if (g_table[0].key != 10) return 1;
  if (g_table[0].val != 100) return 2;
  if (g_table[1].key != 20) return 3;
  if (g_table[1].val != 200) return 4;
  return 0;
}

// Test 2: Global struct array - 3-field struct
struct Triple { int x; int y; int z; };
struct Triple g_triples[3];

int test_global_struct_array_triple() {
  g_triples[0].x = 1;
  g_triples[0].y = 2;
  g_triples[0].z = 3;
  g_triples[1].x = 10;
  g_triples[1].y = 20;
  g_triples[1].z = 30;
  if (g_triples[0].x != 1) return 1;
  if (g_triples[0].y != 2) return 2;
  if (g_triples[0].z != 3) return 3;
  if (g_triples[1].x != 10) return 4;
  if (g_triples[1].y != 20) return 5;
  if (g_triples[1].z != 30) return 6;
  return 0;
}

// Test 3: Global struct array with loop
int test_global_struct_array_loop() {
  int i = 0;
  while (i < 4) {
    g_table[i].key = i * 10;
    g_table[i].val = i * 100;
    i++;
  }
  if (g_table[2].key != 20) return 1;
  if (g_table[2].val != 200) return 2;
  if (g_table[3].key != 30) return 3;
  if (g_table[3].val != 300) return 4;
  return 0;
}

// Test 4: Global struct pointer array (should use stride 8, not struct size)
struct Node { int id; int val; };
struct Node g_nodes[4];
struct Node *g_node_ptrs[4];

int test_global_struct_ptr_array() {
  g_nodes[0].id = 1; g_nodes[0].val = 10;
  g_nodes[1].id = 2; g_nodes[1].val = 20;
  g_node_ptrs[0] = &g_nodes[0];
  g_node_ptrs[1] = &g_nodes[1];
  if (g_node_ptrs[0]->id != 1) return 1;
  if (g_node_ptrs[0]->val != 10) return 2;
  if (g_node_ptrs[1]->id != 2) return 3;
  if (g_node_ptrs[1]->val != 20) return 4;
  return 0;
}

// Test 5: Pass global struct array element address to function
int sum_entry(struct Entry *e) {
  return e->key + e->val;
}

int test_global_struct_array_pass() {
  g_table[0].key = 5;
  g_table[0].val = 15;
  g_table[1].key = 7;
  g_table[1].val = 13;
  int s0 = sum_entry(&g_table[0]);
  int s1 = sum_entry(&g_table[1]);
  if (s0 != 20) return 1;
  if (s1 != 20) return 2;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_global_struct_array_basic();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_struct_array_basic code=%d\n", r); }

  r = test_global_struct_array_triple();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_struct_array_triple code=%d\n", r); }

  r = test_global_struct_array_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_struct_array_loop code=%d\n", r); }

  r = test_global_struct_ptr_array();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_struct_ptr_array code=%d\n", r); }

  r = test_global_struct_array_pass();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_struct_array_pass code=%d\n", r); }

  printf("batch79: %d passed, %d failed\n", passed, failed);
  return failed;
}
