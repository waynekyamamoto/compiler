int printf(int *fmt, ...);

// Test 1: Global struct passed by value to function
struct Point { int x; int y; };
struct Point g_origin;

struct Point offset(struct Point p, int dx, int dy) {
  struct Point r;
  r.x = p.x + dx;
  r.y = p.y + dy;
  return r;
}

int test_global_struct_byval() {
  g_origin.x = 0;
  g_origin.y = 0;
  struct Point p = offset(g_origin, 5, 10);
  if (p.x != 5) { printf("FAIL t1 x: %d\n", p.x); return 1; }
  if (p.y != 10) { printf("FAIL t1 y: %d\n", p.y); return 1; }
  return 0;
}

// Test 2: Chain of calls with global struct byval
int test_chain_global_struct() {
  g_origin.x = 1;
  g_origin.y = 2;
  struct Point p1 = offset(g_origin, 10, 20);
  struct Point p2 = offset(p1, -1, -2);
  if (p2.x != 10) { printf("FAIL t2 x: %d\n", p2.x); return 1; }
  if (p2.y != 20) { printf("FAIL t2 y: %d\n", p2.y); return 1; }
  return 0;
}

// Test 3: Global struct passed to function that reads fields
int sum_point(struct Point p) {
  return p.x + p.y;
}

int test_global_struct_read() {
  g_origin.x = 100;
  g_origin.y = 200;
  int s = sum_point(g_origin);
  if (s != 300) { printf("FAIL t3: %d\n", s); return 1; }
  return 0;
}

// Test 4: Multiple global structs passed by value
struct Rect { int x; int y; int w; int h; };
struct Rect g_rect;

int rect_area(struct Rect r) {
  return r.w * r.h;
}

int test_multi_global_struct() {
  g_rect.x = 10;
  g_rect.y = 20;
  g_rect.w = 30;
  g_rect.h = 40;
  int a = rect_area(g_rect);
  if (a != 1200) { printf("FAIL t4: %d\n", a); return 1; }
  return 0;
}

// Test 5: Global struct byval should not modify original
void modify_point(struct Point p) {
  p.x = 999;
  p.y = 888;
}

int test_byval_no_modify() {
  g_origin.x = 42;
  g_origin.y = 43;
  modify_point(g_origin);
  if (g_origin.x != 42) { printf("FAIL t5 x: %d\n", g_origin.x); return 1; }
  if (g_origin.y != 43) { printf("FAIL t5 y: %d\n", g_origin.y); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;
  r = test_global_struct_byval();
  if (r == 0) { passed++; } else { failed++; }
  r = test_chain_global_struct();
  if (r == 0) { passed++; } else { failed++; }
  r = test_global_struct_read();
  if (r == 0) { passed++; } else { failed++; }
  r = test_multi_global_struct();
  if (r == 0) { passed++; } else { failed++; }
  r = test_byval_no_modify();
  if (r == 0) { passed++; } else { failed++; }
  printf("batch90: %d passed, %d failed\n", passed, failed);
  return failed;
}
