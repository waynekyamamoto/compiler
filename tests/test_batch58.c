int printf(int *fmt, ...);

int main() {
  int passed = 0;
  int failed = 0;

  // Binary literals
  if (0b0 == 0) { passed++; } else { failed++; printf("FAIL: 0b0 != 0\n"); }
  if (0b1 == 1) { passed++; } else { failed++; printf("FAIL: 0b1 != 1\n"); }
  if (0b1010 == 10) { passed++; } else { failed++; printf("FAIL: 0b1010 != 10\n"); }
  if (0b11111111 == 255) { passed++; } else { failed++; printf("FAIL: 0b11111111 != 255\n"); }
  if (0B1100 == 12) { passed++; } else { failed++; printf("FAIL: 0B1100 != 12\n"); }

  // Octal literals
  if (0777 == 511) { passed++; } else { failed++; printf("FAIL: 0777 != 511\n"); }
  if (0644 == 420) { passed++; } else { failed++; printf("FAIL: 0644 != 420\n"); }
  if (010 == 8) { passed++; } else { failed++; printf("FAIL: 010 != 8\n"); }
  if (00 == 0) { passed++; } else { failed++; printf("FAIL: 00 != 0\n"); }

  // Hex (sanity check)
  if (0xFF == 255) { passed++; } else { failed++; printf("FAIL: 0xFF != 255\n"); }
  if (0xDEAD == 57005) { passed++; } else { failed++; printf("FAIL: 0xDEAD\n"); }

  printf("batch58: %d passed, %d failed\n", passed, failed);
  if (failed > 0) return 1;
  return 0;
}
