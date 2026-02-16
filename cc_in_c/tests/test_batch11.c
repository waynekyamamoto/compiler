// Test batch 11: Struct arrays and struct type resolution through indexing

int printf(int *fmt, ...);
int *malloc(int size);

struct Point {
  int x;
  int y;
};

int test_struct_array_dot() {
  struct Point pts[3];
  pts[0].x = 10;
  pts[0].y = 20;
  pts[1].x = 30;
  pts[1].y = 40;
  pts[2].x = 50;
  pts[2].y = 60;

  int sum;
  sum = 0;
  int i;
  for (i = 0; i < 3; i++)
    sum = sum + pts[i].x + pts[i].y;
  if (sum != 210) return 1;
  return 0;
}

int test_struct_ptr_array_arrow() {
  struct Point **arr;
  arr = malloc(3 * 8);
  int i;
  for (i = 0; i < 3; i++) {
    arr[i] = malloc(16);
    arr[i]->x = i * 10;
    arr[i]->y = i * 10 + 5;
  }
  if (arr[1]->x != 10) return 1;
  if (arr[2]->y != 25) return 2;
  return 0;
}

int test_struct_array_overwrite() {
  struct Point pts[2];
  pts[0].x = 1;
  pts[0].y = 2;
  pts[1].x = 3;
  pts[1].y = 4;
  // Verify no overlap
  if (pts[0].x != 1) return 1;
  if (pts[0].y != 2) return 2;
  if (pts[1].x != 3) return 3;
  if (pts[1].y != 4) return 4;
  return 0;
}

struct Node {
  int val;
  int left;
  int right;
};

int test_struct_array_3fields() {
  struct Node nodes[2];
  nodes[0].val = 100;
  nodes[0].left = 1;
  nodes[0].right = 2;
  nodes[1].val = 200;
  nodes[1].left = 3;
  nodes[1].right = 4;
  if (nodes[0].val != 100) return 1;
  if (nodes[1].right != 4) return 2;
  if (nodes[0].left + nodes[1].left != 4) return 3;
  return 0;
}

int main() {
  if (test_struct_array_dot()) { printf("FAIL: struct_array_dot\n"); return 1; }
  if (test_struct_ptr_array_arrow()) { printf("FAIL: struct_ptr_array_arrow\n"); return 1; }
  if (test_struct_array_overwrite()) { printf("FAIL: struct_array_overwrite\n"); return 1; }
  if (test_struct_array_3fields()) { printf("FAIL: struct_array_3fields\n"); return 1; }
  printf("All batch 11 tests passed.\n");
  return 0;
}
