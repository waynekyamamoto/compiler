// Test batch 56: Floating-point support
int printf(char *fmt, ...);

double add_doubles(double a, double b) {
  return a + b;
}

double mul_doubles(double a, double b) {
  return a * b;
}

int main() {
  int passed = 0;
  int failed = 0;

  // Test 1: Float literal assignment
  double x = 1.5;
  double y = 2.5;
  double z = x + y;
  // z should be 4.0 => (int)z == 4
  if ((int)z == 4) { passed++; } else { failed++; printf("FAIL test 1: expected 4, got %d\n", (int)z); }

  // Test 2: Float subtraction
  double d = 10.0 - 3.5;
  if ((int)d == 6) { passed++; } else { failed++; printf("FAIL test 2: expected 6, got %d\n", (int)d); }

  // Test 3: Float multiplication
  double m = 3.0 * 4.0;
  if ((int)m == 12) { passed++; } else { failed++; printf("FAIL test 3: expected 12, got %d\n", (int)m); }

  // Test 4: Float division
  double dv = 15.0 / 4.0;
  if ((int)dv == 3) { passed++; } else { failed++; printf("FAIL test 4: expected 3, got %d\n", (int)dv); }

  // Test 5: Float comparison <
  if (1.5 < 2.5) { passed++; } else { failed++; printf("FAIL test 5\n"); }

  // Test 6: Float comparison >
  if (3.5 > 1.5) { passed++; } else { failed++; printf("FAIL test 6\n"); }

  // Test 7: Float comparison ==
  double eq1 = 2.5;
  double eq2 = 2.5;
  if (eq1 == eq2) { passed++; } else { failed++; printf("FAIL test 7\n"); }

  // Test 8: Float comparison <=
  if (2.5 <= 3.0) { passed++; } else { failed++; printf("FAIL test 8\n"); }

  // Test 9: Float negation
  double neg = -3.5;
  double pos = -neg;
  if ((int)pos == 3) { passed++; } else { failed++; printf("FAIL test 9: expected 3, got %d\n", (int)pos); }

  // Test 10: Int to float assignment
  int ival = 42;
  double fval = ival;
  if ((int)fval == 42) { passed++; } else { failed++; printf("FAIL test 10: expected 42, got %d\n", (int)fval); }

  // Test 11: Float to int assignment
  double fval2 = 7.9;
  int ival2 = (int)fval2;
  if (ival2 == 7) { passed++; } else { failed++; printf("FAIL test 11: expected 7, got %d\n", ival2); }

  // Test 12: Float function call and return
  double r = add_doubles(1.5, 2.5);
  if ((int)r == 4) { passed++; } else { failed++; printf("FAIL test 12: expected 4, got %d\n", (int)r); }

  // Test 13: Mixed int/float arithmetic
  double mixed = 10.0 + 5;
  if ((int)mixed == 15) { passed++; } else { failed++; printf("FAIL test 13: expected 15, got %d\n", (int)mixed); }

  // Test 14: Float-to-int cast of (double)int
  int ci = 7;
  double cf = (double)ci;
  if ((int)cf == 7) { passed++; } else { failed++; printf("FAIL test 14: expected 7, got %d\n", (int)cf); }

  // Test 15: != comparison
  double ne1 = 1.5;
  double ne2 = 2.5;
  if (ne1 != ne2) { passed++; } else { failed++; printf("FAIL test 15\n"); }

  // Test 16: >= comparison
  if (3.0 >= 3.0) { passed++; } else { failed++; printf("FAIL test 16\n"); }

  // Test 17: Float mul_doubles function
  double mr = mul_doubles(3.0, 4.0);
  if ((int)mr == 12) { passed++; } else { failed++; printf("FAIL test 17: expected 12, got %d\n", (int)mr); }

  printf("Float tests: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
