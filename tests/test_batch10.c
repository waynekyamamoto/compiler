// Test batch 10: Braceless if/else/while/for/do-while bodies

int printf(int *fmt, ...);

int test_braceless_if() {
  int x;
  x = 10;
  if (x == 10)
    x = 20;
  if (x != 20) return 1;
  return 0;
}

int test_braceless_if_else() {
  int x;
  x = 5;
  int y;
  if (x == 5)
    y = 100;
  else
    y = 200;
  if (y != 100) return 1;

  if (x == 99)
    y = 300;
  else
    y = 400;
  if (y != 400) return 1;
  return 0;
}

int test_braceless_while() {
  int i;
  i = 0;
  int sum;
  sum = 0;
  while (i < 5)
    i = i + 1;
  if (i != 5) return 1;
  return 0;
}

int test_braceless_for() {
  int sum;
  sum = 0;
  int i;
  for (i = 0; i < 10; i = i + 1)
    sum = sum + i;
  if (sum != 45) return 1;
  return 0;
}

int test_braceless_if_return() {
  int x;
  x = 42;
  if (x == 42)
    return 0;
  return 1;
}

int test_else_if_chain() {
  int x;
  x = 3;
  int y;
  y = 0;
  if (x == 1)
    y = 10;
  else if (x == 2)
    y = 20;
  else if (x == 3)
    y = 30;
  else
    y = 40;
  if (y != 30) return 1;
  return 0;
}

int main() {
  if (test_braceless_if()) { printf("FAIL: braceless_if\n"); return 1; }
  if (test_braceless_if_else()) { printf("FAIL: braceless_if_else\n"); return 1; }
  if (test_braceless_while()) { printf("FAIL: braceless_while\n"); return 1; }
  if (test_braceless_for()) { printf("FAIL: braceless_for\n"); return 1; }
  if (test_braceless_if_return()) { printf("FAIL: braceless_if_return\n"); return 1; }
  if (test_else_if_chain()) { printf("FAIL: else_if_chain\n"); return 1; }
  printf("All batch 10 tests passed.\n");
  return 0;
}
