int printf(int *fmt, ...);

int test_basic_computed_goto() {
  int result = 0;
  void *table[3];
  table[0] = &&L0;
  table[1] = &&L1;
  table[2] = &&L2;

  goto *table[1];

  L0: result = 10; goto done;
  L1: result = 20; goto done;
  L2: result = 30; goto done;
  done:
  return result;
}

int test_loop_dispatch() {
  int sum = 0;
  int ops[5];
  ops[0] = 0;
  ops[1] = 1;
  ops[2] = 0;
  ops[3] = 1;
  ops[4] = 2;

  void *dispatch[3];
  dispatch[0] = &&op_add;
  dispatch[1] = &&op_mul;
  dispatch[2] = &&op_done;

  int pc = 0;
  goto *dispatch[ops[pc]];

  op_add:
    sum = sum + 10;
    pc++;
    goto *dispatch[ops[pc]];

  op_mul:
    sum = sum * 2;
    pc++;
    goto *dispatch[ops[pc]];

  op_done:
  return sum;
}

int test_label_addr() {
  void *p = &&target;
  int x = 0;
  goto *p;
  x = 99;
  target:
  return x;
}

int main() {
  int passed = 0;
  int failed = 0;

  if (test_basic_computed_goto() == 20) { passed++; } else { failed++; printf("FAIL: basic computed goto\n"); }
  if (test_loop_dispatch() == 60) { passed++; } else { failed++; printf("FAIL: loop dispatch got %d\n", test_loop_dispatch()); }
  if (test_label_addr() == 0) { passed++; } else { failed++; printf("FAIL: label addr\n"); }

  printf("batch59: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
