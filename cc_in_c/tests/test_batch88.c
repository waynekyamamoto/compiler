int printf(int *fmt, ...);

// Test global struct assignment from function return

struct Token { int kind; int val; };
struct Token cur;

struct Token make_token(int kind, int val) {
  struct Token t;
  t.kind = kind;
  t.val = val;
  return t;
}

// Test 1: Basic global struct assignment from function return
int test_global_struct_assign() {
  cur = make_token(6, 42);
  if (cur.kind != 6) { printf("FAIL global assign kind: %d\n", cur.kind); return 1; }
  if (cur.val != 42) { printf("FAIL global assign val: %d\n", cur.val); return 1; }
  return 0;
}

// Test 2: Multiple assignments to same global struct
int test_multi_assign() {
  cur = make_token(1, 10);
  if (cur.kind != 1 || cur.val != 10) { printf("FAIL multi 1\n"); return 1; }
  cur = make_token(2, 20);
  if (cur.kind != 2 || cur.val != 20) { printf("FAIL multi 2\n"); return 1; }
  cur = make_token(3, 30);
  if (cur.kind != 3 || cur.val != 30) { printf("FAIL multi 3\n"); return 1; }
  return 0;
}

// Test 3: Global struct used in conditional
int test_global_in_cond() {
  cur = make_token(5, 100);
  int result = 0;
  if (cur.kind == 5) {
    result = cur.val;
  }
  if (result != 100) { printf("FAIL cond: %d\n", result); return 1; }
  return 0;
}

// Test 4: Global struct with 3 fields
struct Point { int x; int y; int z; };
struct Point gpt;

struct Point make_point(int x, int y, int z) {
  struct Point p;
  p.x = x;
  p.y = y;
  p.z = z;
  return p;
}

int test_global_3field() {
  gpt = make_point(10, 20, 30);
  if (gpt.x != 10) { printf("FAIL 3field x: %d\n", gpt.x); return 1; }
  if (gpt.y != 20) { printf("FAIL 3field y: %d\n", gpt.y); return 1; }
  if (gpt.z != 30) { printf("FAIL 3field z: %d\n", gpt.z); return 1; }
  return 0;
}

// Test 5: Global struct assigned in loop
int test_global_loop() {
  int i = 0;
  while (i < 5) {
    cur = make_token(i, i * 10);
    i = i + 1;
  }
  if (cur.kind != 4) { printf("FAIL loop kind: %d\n", cur.kind); return 1; }
  if (cur.val != 40) { printf("FAIL loop val: %d\n", cur.val); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_global_struct_assign();
  if (r == 0) { passed++; } else { failed++; printf("  global_struct_assign: FAIL\n"); }

  r = test_multi_assign();
  if (r == 0) { passed++; } else { failed++; printf("  multi_assign: FAIL\n"); }

  r = test_global_in_cond();
  if (r == 0) { passed++; } else { failed++; printf("  global_in_cond: FAIL\n"); }

  r = test_global_3field();
  if (r == 0) { passed++; } else { failed++; printf("  global_3field: FAIL\n"); }

  r = test_global_loop();
  if (r == 0) { passed++; } else { failed++; printf("  global_loop: FAIL\n"); }

  printf("batch88: %d passed, %d failed\n", passed, failed);
  return failed;
}
