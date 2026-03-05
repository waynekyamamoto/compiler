int printf(int *fmt, ...);
void *malloc(int size);

// Test 1: Struct with fixed-size array field
struct S1 {
  int arr[4];
  int x;
};

int test_struct_arr_field() {
  struct S1 *s = malloc(64);
  s->arr[0] = 10;
  s->arr[1] = 20;
  s->arr[2] = 30;
  s->arr[3] = 40;
  s->x = 99;
  if (s->arr[0] != 10) return 1;
  if (s->arr[1] != 20) return 2;
  if (s->arr[2] != 30) return 3;
  if (s->arr[3] != 40) return 4;
  if (s->x != 99) return 5;
  return 0;
}

// Test 2: Array field at beginning, scalar after
struct Buf {
  int data[8];
  int len;
  int cap;
};

int test_buf() {
  struct Buf *b = malloc(128);
  b->len = 0;
  b->cap = 8;
  int i;
  for (i = 0; i < 8; i++) {
    b->data[i] = i * 10;
    b->len++;
  }
  if (b->len != 8) return 1;
  if (b->cap != 8) return 2;
  if (b->data[0] != 0) return 3;
  if (b->data[7] != 70) return 4;
  return 0;
}

// Test 3: Multiple array fields
struct Multi {
  int a[3];
  int b[3];
  int tag;
};

int test_multi_arr() {
  struct Multi *m = malloc(128);
  m->a[0] = 1; m->a[1] = 2; m->a[2] = 3;
  m->b[0] = 10; m->b[1] = 20; m->b[2] = 30;
  m->tag = 42;
  if (m->a[0] + m->a[1] + m->a[2] != 6) return 1;
  if (m->b[0] + m->b[1] + m->b[2] != 60) return 2;
  if (m->tag != 42) return 3;
  return 0;
}

// Test 4: Stack-based VM using struct with array
enum { OP_PUSH, OP_ADD, OP_MUL, OP_HALT };

struct VM {
  int stack[64];
  int sp;
  int *prog;
  int pc;
};

int vm_run(struct VM *vm) {
  int a; int b;
  while (1) {
    int op = vm->prog[vm->pc];
    vm->pc++;
    if (op == OP_PUSH) {
      vm->stack[vm->sp] = vm->prog[vm->pc];
      vm->sp++;
      vm->pc++;
    } else if (op == OP_ADD) {
      b = vm->stack[vm->sp - 1]; vm->sp--;
      a = vm->stack[vm->sp - 1]; vm->sp--;
      vm->stack[vm->sp] = a + b; vm->sp++;
    } else if (op == OP_MUL) {
      b = vm->stack[vm->sp - 1]; vm->sp--;
      a = vm->stack[vm->sp - 1]; vm->sp--;
      vm->stack[vm->sp] = a * b; vm->sp++;
    } else if (op == OP_HALT) {
      return vm->stack[vm->sp - 1];
    }
  }
  return 0;
}

int test_vm() {
  // Compute (3 + 4) * 5 = 35
  int prog[10] = { OP_PUSH, 3, OP_PUSH, 4, OP_ADD, OP_PUSH, 5, OP_MUL, OP_HALT };
  struct VM *vm = malloc(600);
  vm->sp = 0;
  vm->prog = prog;
  vm->pc = 0;
  return vm_run(vm);
}

// Test 5: Scalar before array field
struct Prefix {
  int type;
  int len;
  int data[4];
};

int test_prefix() {
  struct Prefix *p = malloc(64);
  p->type = 1;
  p->len = 4;
  p->data[0] = 100;
  p->data[1] = 200;
  p->data[2] = 300;
  p->data[3] = 400;
  if (p->type != 1) return 1;
  if (p->len != 4) return 2;
  if (p->data[0] != 100) return 3;
  if (p->data[3] != 400) return 4;
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_struct_arr_field();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: struct_arr_field code=%d\n", r); }

  r = test_buf();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: buf code=%d\n", r); }

  r = test_multi_arr();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: multi_arr code=%d\n", r); }

  if (test_vm() == 35) { passed++; } else { failed++; printf("FAIL: vm got %d\n", test_vm()); }

  r = test_prefix();
  if (r == 0) { passed++; } else { failed++; printf("FAIL: prefix code=%d\n", r); }

  printf("batch63: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
