int printf(int *fmt, ...);
int *fopen(int *path, int *mode);
int fgetc(int *f);
int fclose(int *f);

int main() {
  int *f = fopen("test_trivial.c", "r");
  if (f == 0) { return 1; }

  int ch = fgetc(f);
  printf("first ch = %d\n", ch);

  // Read to end
  int count = 0;
  while (ch != 0 - 1) {
    count = count + 1;
    if (count > 100) {
      printf("giving up after 100\n");
      break;
    }
    ch = fgetc(f);
  }
  printf("count=%d ch=%d\n", count, ch);

  // Direct test of -1
  int neg = 0 - 1;
  printf("neg = %d\n", neg);

  // Test: what does fgetc return at EOF?
  int eof = fgetc(f);
  printf("eof raw = %d\n", eof);

  // Compare
  if (eof == neg) {
    printf("eof == neg: YES\n");
  } else {
    printf("eof == neg: NO\n");
  }

  fclose(f);
  return 0;
}
