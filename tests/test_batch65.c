int printf(int *fmt, ...);

// Test 1: Array of function pointers - direct syntax
int op_add(int a, int b) { return a + b; }
int op_sub(int a, int b) { return a - b; }
int op_mul(int a, int b) { return a * b; }

int test_funcptr_array() {
  int (*ops[3])(int, int);
  ops[0] = op_add;
  ops[1] = op_sub;
  ops[2] = op_mul;
  if (ops[0](10, 3) != 13) return 1;
  if (ops[1](10, 3) != 7) return 2;
  if (ops[2](10, 3) != 30) return 3;
  return 0;
}

// Test 2: Dispatch table via typedef (already works, regression test)
typedef int (*binop_t)(int, int);

int test_dispatch_typedef() {
  binop_t ops[3];
  ops[0] = op_add;
  ops[1] = op_sub;
  ops[2] = op_mul;
  if (ops[0](5, 2) != 7) return 1;
  if (ops[1](5, 2) != 3) return 2;
  if (ops[2](5, 2) != 10) return 3;
  return 0;
}

// Test 3: Callback sort with funcptr param
void bubble_sort(int *arr, int n, int (*cmp)(int, int)) {
  int i; int j; int tmp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (cmp(arr[j], arr[j+1]) > 0) {
        tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
      }
    }
  }
}

int cmp_asc(int a, int b) { return a - b; }
int cmp_desc(int a, int b) { return b - a; }

int test_callback_sort() {
  int arr[5] = {5, 3, 1, 4, 2};
  bubble_sort(arr, 5, cmp_asc);
  if (arr[0] != 1 || arr[4] != 5) return 1;
  bubble_sort(arr, 5, cmp_desc);
  if (arr[0] != 5 || arr[4] != 1) return 2;
  return 0;
}

// Test 4: Function pointer in loop (apply_all pattern)
int double_it(int x) { return x * 2; }
int negate_it(int x) { return 0 - x; }
int inc_it(int x) { return x + 1; }

int test_funcptr_loop() {
  int (*funcs[3])(int);
  funcs[0] = double_it;
  funcs[1] = negate_it;
  funcs[2] = inc_it;
  int val = 5;
  int i;
  for (i = 0; i < 3; i++) {
    val = funcs[i](val);
  }
  // 5 -> double -> 10 -> negate -> -10 -> inc -> -9
  if (val != 0 - 9) return 1;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_funcptr_array();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: funcptr_array code=%d\n", r); }

  r = test_dispatch_typedef();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: dispatch_typedef code=%d\n", r); }

  r = test_callback_sort();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: callback_sort code=%d\n", r); }

  r = test_funcptr_loop();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: funcptr_loop code=%d\n", r); }

  printf("batch65: %d passed, %d failed\n", passed, failed);
  return failed;
}
