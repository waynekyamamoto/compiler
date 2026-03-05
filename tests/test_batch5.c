int printf(int *fmt, ...);

enum Fruit { APPLE, BANANA, CHERRY };

int test_switch_match() {
  int x;
  int result;
  x = 2;
  result = -1;
  switch (x) {
  case 1:
    result = 10;
    break;
  case 2:
    result = 20;
    break;
  case 3:
    result = 30;
    break;
  }
  if (result != 20) {
    printf("FAIL: switch match, result = %d, expected 20\n", result);
    return 1;
  }
  return 0;
}

int test_switch_default() {
  int x;
  int result;
  x = 99;
  result = -1;
  switch (x) {
  case 1:
    result = 10;
    break;
  default:
    result = 0;
    break;
  }
  if (result != 0) {
    printf("FAIL: switch default, result = %d, expected 0\n", result);
    return 1;
  }
  return 0;
}

int test_switch_fallthrough() {
  int x;
  int result;
  x = 1;
  result = 0;
  switch (x) {
  case 1:
    result = result + 1;
  case 2:
    result = result + 10;
    break;
  case 3:
    result = result + 100;
    break;
  }
  if (result != 11) {
    printf("FAIL: switch fallthrough, result = %d, expected 11\n", result);
    return 1;
  }
  return 0;
}

int test_switch_enum() {
  int f;
  int result;
  f = BANANA;
  result = -1;
  switch (f) {
  case APPLE:
    result = 0;
    break;
  case BANANA:
    result = 1;
    break;
  case CHERRY:
    result = 2;
    break;
  }
  if (result != 1) {
    printf("FAIL: switch enum, result = %d, expected 1\n", result);
    return 1;
  }
  return 0;
}

int test_switch_negative() {
  int x;
  int result;
  x = -1;
  result = 0;
  switch (x) {
  case -1:
    result = 42;
    break;
  case 0:
    result = 99;
    break;
  }
  if (result != 42) {
    printf("FAIL: switch negative, result = %d, expected 42\n", result);
    return 1;
  }
  return 0;
}

int main() {
  int fail;
  fail = 0;
  fail = fail + test_switch_match();
  fail = fail + test_switch_default();
  fail = fail + test_switch_fallthrough();
  fail = fail + test_switch_enum();
  fail = fail + test_switch_negative();
  if (fail == 0) {
    printf("batch5: all tests passed\n");
  } else {
    printf("batch5: %d test(s) FAILED\n", fail);
  }
  return fail;
}
