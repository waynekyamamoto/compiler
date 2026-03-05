int printf(int *fmt, ...);

// Test 1: Struct with int array member
struct WithArr {
  int data[5];
  int count;
};

int test_struct_int_array() {
  struct WithArr w;
  w.count = 3;
  w.data[0] = 10;
  w.data[1] = 20;
  w.data[2] = 30;
  w.data[3] = 40;
  w.data[4] = 50;
  if (w.data[0] != 10) return 1;
  if (w.data[1] != 20) return 2;
  if (w.data[2] != 30) return 3;
  if (w.data[3] != 40) return 4;
  if (w.data[4] != 50) return 5;
  if (w.count != 3) return 6;
  return 0;
}

// Test 2: Struct with array and fields after it
struct Multi {
  int x;
  int arr[3];
  int y;
  int z;
};

int test_struct_arr_layout() {
  struct Multi m;
  m.x = 1;
  m.arr[0] = 10;
  m.arr[1] = 20;
  m.arr[2] = 30;
  m.y = 2;
  m.z = 3;
  if (m.x != 1) return 1;
  if (m.arr[0] != 10) return 2;
  if (m.arr[1] != 20) return 3;
  if (m.arr[2] != 30) return 4;
  if (m.y != 2) return 5;
  if (m.z != 3) return 6;
  return 0;
}

// Test 3: Pointer to struct with array, access via arrow
int test_struct_arr_arrow() {
  struct WithArr w;
  w.count = 7;
  w.data[0] = 100;
  w.data[4] = 500;
  struct WithArr *p = &w;
  if (p->count != 7) return 1;
  if (p->data[0] != 100) return 2;
  if (p->data[4] != 500) return 3;
  return 0;
}

// Test 4: Array doesn't corrupt adjacent struct members
int test_struct_arr_no_corrupt() {
  struct Multi m;
  m.x = 99;
  m.y = 88;
  m.z = 77;
  // Fill array - should not overwrite x, y, or z
  int i;
  for (i = 0; i < 3; i++) {
    m.arr[i] = i * 100;
  }
  if (m.x != 99) return 1;
  if (m.y != 88) return 2;
  if (m.z != 77) return 3;
  if (m.arr[0] != 0) return 4;
  if (m.arr[1] != 100) return 5;
  if (m.arr[2] != 200) return 6;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_int_array();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_int_array code=%d\n", r); }

  r = test_struct_arr_layout();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_arr_layout code=%d\n", r); }

  r = test_struct_arr_arrow();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_arr_arrow code=%d\n", r); }

  r = test_struct_arr_no_corrupt();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_arr_no_corrupt code=%d\n", r); }

  printf("batch72: %d passed, %d failed\n", passed, failed);
  return failed;
}
