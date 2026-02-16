int printf(int *fmt, ...);

int test_dowhile_once() {
  int count;
  count = 0;
  do {
    count = count + 1;
  } while (0);
  if (count != 1) {
    printf("FAIL: do-while body should run once, count = %d\n", count);
    return 1;
  }
  return 0;
}

int test_dowhile_counter() {
  int i;
  int sum;
  i = 0;
  sum = 0;
  do {
    sum = sum + i;
    i = i + 1;
  } while (i < 5);
  if (sum != 10) {
    printf("FAIL: do-while sum = %d, expected 10\n", sum);
    return 1;
  }
  return 0;
}

int test_goto_forward() {
  int x;
  x = 0;
  goto skip;
  x = 99;
skip:
  if (x != 0) {
    printf("FAIL: goto forward, x = %d, expected 0\n", x);
    return 1;
  }
  return 0;
}

int test_goto_backward() {
  int count;
  count = 0;
again:
  count = count + 1;
  if (count < 3) {
    goto again;
  }
  if (count != 3) {
    printf("FAIL: goto backward, count = %d, expected 3\n", count);
    return 1;
  }
  return 0;
}

int test_sizeof() {
  int x;
  int a;
  int *p;
  a = sizeof(int);
  if (a != 8) {
    printf("FAIL: sizeof(int) = %d, expected 8\n", a);
    return 1;
  }
  a = sizeof(x);
  if (a != 8) {
    printf("FAIL: sizeof(x) = %d, expected 8\n", a);
    return 1;
  }
  a = sizeof(p);
  if (a != 8) {
    printf("FAIL: sizeof(p) = %d, expected 8\n", a);
    return 1;
  }
  return 0;
}

int main() {
  int fail;
  fail = 0;
  fail = fail + test_dowhile_once();
  fail = fail + test_dowhile_counter();
  fail = fail + test_goto_forward();
  fail = fail + test_goto_backward();
  fail = fail + test_sizeof();
  if (fail == 0) {
    printf("batch2: all tests passed\n");
  } else {
    printf("batch2: %d test(s) FAILED\n", fail);
  }
  return fail;
}
