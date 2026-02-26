int printf(int *fmt, ...);
void *malloc(long size);

// Test 1: Switch with no matching case (stack leak regression)
int test_switch_nomatch() {
  int x = 99;
  int hit = 0;
  switch (x) {
    case 1: hit = 1; break;
    case 2: hit = 2; break;
    case 3: hit = 3; break;
  }
  if (hit != 0) { printf("FAIL switch nomatch: %d\n", hit); return 1; }
  return 0;
}

// Test 2: Multiple switches in same function (accumulates stack leak)
int test_multi_switch() {
  int a = 10, b = 20, c = 30;
  int r1 = 0, r2 = 0, r3 = 0;
  switch (a) { case 10: r1 = 1; break; case 20: r1 = 2; break; }
  switch (b) { case 10: r2 = 1; break; case 20: r2 = 2; break; }
  switch (c) { case 10: r3 = 1; break; case 20: r3 = 2; break; }
  if (r1 != 1) { printf("FAIL multi switch r1: %d\n", r1); return 1; }
  if (r2 != 2) { printf("FAIL multi switch r2: %d\n", r2); return 2; }
  if (r3 != 0) { printf("FAIL multi switch r3: %d\n", r3); return 3; }
  return 0;
}

// Test 3: Switch with default case
int test_switch_default() {
  int x = 42;
  int r = 0;
  switch (x) {
    case 1: r = 10; break;
    case 2: r = 20; break;
    default: r = 99; break;
  }
  if (r != 99) { printf("FAIL switch default: %d\n", r); return 1; }
  return 0;
}

// Test 4: Switch followed by more computation
int test_switch_then_compute() {
  int x = 2;
  int r = 0;
  switch (x) {
    case 1: r = 10; break;
    case 2: r = 20; break;
    case 3: r = 30; break;
  }
  // Additional computation after switch
  int sum = r + x + 100;
  if (sum != 122) { printf("FAIL switch+compute: %d\n", sum); return 1; }
  return 0;
}

// Test 5: Many no-match switches to expose stack overflow
int test_many_switches() {
  int x = 99;
  int y = 0;
  // Each no-match switch previously leaked 16 bytes
  switch (x) { case 1: y = 1; break; case 2: y = 2; break; }
  switch (x) { case 3: y = 3; break; case 4: y = 4; break; }
  switch (x) { case 5: y = 5; break; case 6: y = 6; break; }
  switch (x) { case 7: y = 7; break; case 8: y = 8; break; }
  switch (x) { case 9: y = 9; break; case 10: y = 10; break; }
  if (y != 0) { printf("FAIL many switches: %d\n", y); return 1; }
  return 0;
}

int main() {
  int passed = 0;
  int failed = 0;
  int r;

  r = test_switch_nomatch();
  if (r == 0) { passed++; } else { failed++; printf("  switch_nomatch: FAIL %d\n", r); }

  r = test_multi_switch();
  if (r == 0) { passed++; } else { failed++; printf("  multi_switch: FAIL %d\n", r); }

  r = test_switch_default();
  if (r == 0) { passed++; } else { failed++; printf("  switch_default: FAIL %d\n", r); }

  r = test_switch_then_compute();
  if (r == 0) { passed++; } else { failed++; printf("  switch_then_compute: FAIL %d\n", r); }

  r = test_many_switches();
  if (r == 0) { passed++; } else { failed++; printf("  many_switches: FAIL %d\n", r); }

  printf("batch87: %d passed, %d failed\n", passed, failed);
  return failed;
}
