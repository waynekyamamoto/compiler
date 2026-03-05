// Test batch 99: const-expr sizeof, double-pointer stride, 2D array fields

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_count = 0;
int pass_count = 0;

void check(int ok, const char *name) {
  test_count++;
  if (ok) { pass_count++; }
  else { printf("FAIL: %s\n", name); }
}

// === Feature 1: const-expr sizeof ===

struct SmallStruct { int a; int b; };
struct BigStruct { int a; int b; int c; int d; int e; };

void test_sizeof_struct() {
  // sizeof(struct SmallStruct) should be 8 (2 ints * 4)
  int arr1[sizeof(struct SmallStruct)];
  check(sizeof(struct SmallStruct) == 8, "sizeof(struct SmallStruct) == 8");

  // sizeof(struct BigStruct) should be 20 (5 ints * 4)
  check(sizeof(struct BigStruct) == 20, "sizeof(struct BigStruct) == 20");

  // sizeof(int) should be 4
  check(sizeof(int) == 4, "sizeof(int) == 4");

  // sizeof(char) should be 1
  check(sizeof(char) == 1, "sizeof(char) == 1");

  // sizeof(int *) should be 8
  check(sizeof(int *) == 8, "sizeof(int *) == 8");

  // sizeof(char[10]) should be 10
  check(sizeof(char[10]) == 10, "sizeof(char[10]) == 10");

  // sizeof(int[5]) should be 20
  check(sizeof(int[5]) == 20, "sizeof(int[5]) == 20");
}

// === Feature 2: double-pointer stride ===

struct Node { int val; int extra; };

void test_double_pointer() {
  struct Node n1; n1.val = 10; n1.extra = 20;
  struct Node n2; n2.val = 30; n2.extra = 40;
  struct Node n3; n3.val = 50; n3.extra = 60;

  // Single pointer: stride should be sizeof(struct Node)
  struct Node *arr[3];
  arr[0] = &n1;
  arr[1] = &n2;
  arr[2] = &n3;

  // Double pointer: pp[i] should use stride 8 (pointer size)
  struct Node **pp = arr;
  check(pp[0]->val == 10, "pp[0]->val == 10");
  check(pp[1]->val == 30, "pp[1]->val == 30");
  check(pp[2]->val == 50, "pp[2]->val == 50");
}

// === Feature 3: 2D array fields in structs ===

struct Matrix {
  int data[3][4];
  int label;
};

void test_2d_array_field() {
  struct Matrix m;
  m.label = 99;

  // Fill 2D array field
  int i = 0;
  while (i < 3) {
    int j = 0;
    while (j < 4) {
      m.data[i][j] = i * 10 + j;
      j++;
    }
    i++;
  }

  check(m.data[0][0] == 0, "m.data[0][0] == 0");
  check(m.data[0][3] == 3, "m.data[0][3] == 3");
  check(m.data[1][0] == 10, "m.data[1][0] == 10");
  check(m.data[1][2] == 12, "m.data[1][2] == 12");
  check(m.data[2][3] == 23, "m.data[2][3] == 23");
  check(m.label == 99, "m.label == 99");
}

struct Table {
  int rows[2][3];
  int count;
};

void test_2d_field_via_pointer() {
  struct Table t;
  t.count = 42;
  t.rows[0][0] = 1; t.rows[0][1] = 2; t.rows[0][2] = 3;
  t.rows[1][0] = 4; t.rows[1][1] = 5; t.rows[1][2] = 6;

  struct Table *tp = &t;
  check(tp->rows[0][0] == 1, "tp->rows[0][0] == 1");
  check(tp->rows[0][2] == 3, "tp->rows[0][2] == 3");
  check(tp->rows[1][1] == 5, "tp->rows[1][1] == 5");
  check(tp->rows[1][2] == 6, "tp->rows[1][2] == 6");
  check(tp->count == 42, "tp->count == 42");
}

int main() {
  test_sizeof_struct();
  test_double_pointer();
  test_2d_array_field();
  test_2d_field_via_pointer();

  printf("Test batch 99: %d/%d passed\n", pass_count, test_count);
  if (pass_count == test_count) return 0;
  return 1;
}
