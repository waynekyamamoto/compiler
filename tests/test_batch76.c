int printf(int *fmt, ...);

// Test 1: Basic struct return by value
struct Vec2 { int x; int y; };

struct Vec2 make_vec(int x, int y) {
  struct Vec2 v;
  v.x = x;
  v.y = y;
  return v;
}

int test_struct_return_basic() {
  struct Vec2 v = make_vec(3, 4);
  if (v.x != 3) return 1;
  if (v.y != 4) return 2;
  return 0;
}

// Test 2: Struct return used in expression
int test_struct_return_field() {
  struct Vec2 v = make_vec(10, 20);
  int sum = v.x + v.y;
  if (sum != 30) return 1;
  return 0;
}

// Test 3: 3-field struct return
struct Vec3 { int x; int y; int z; };

struct Vec3 make_vec3(int x, int y, int z) {
  struct Vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

int test_struct_return_3field() {
  struct Vec3 v = make_vec3(10, 20, 30);
  if (v.x != 10) return 1;
  if (v.y != 20) return 2;
  if (v.z != 30) return 3;
  return 0;
}

// Test 4: Global char* array double indexing
char *g_names[4];

int test_global_char_arr() {
  g_names[0] = "alpha";
  g_names[1] = "beta";
  g_names[2] = "gamma";
  g_names[3] = "delta";
  if (g_names[0][0] != 'a') return 1;
  if (g_names[1][0] != 'b') return 2;
  if (g_names[2][2] != 'm') return 3;
  if (g_names[3][4] != 'a') return 4;
  return 0;
}

// Test 5: Global char* array with iteration
int my_strlen(char *s) {
  int n = 0;
  while (s[n] != 0) n++;
  return n;
}

int test_global_char_strlen() {
  g_names[0] = "hello";
  int len = my_strlen(g_names[0]);
  if (len != 5) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_return_basic();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_return_basic code=%d\n", r); }

  r = test_struct_return_field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_return_field code=%d\n", r); }

  r = test_struct_return_3field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_return_3field code=%d\n", r); }

  r = test_global_char_arr();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_arr code=%d\n", r); }

  r = test_global_char_strlen();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: global_char_strlen code=%d\n", r); }

  printf("batch76: %d passed, %d failed\n", passed, failed);
  return failed;
}
