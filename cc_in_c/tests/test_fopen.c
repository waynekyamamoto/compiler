int printf(int *fmt, ...);
int *fopen(int *path, int *mode);
int fgetc(int *f);
int fclose(int *f);

int main() {
  int *f = fopen("test_trivial.c", "r");
  if (f == 0) {
    printf("fopen failed\n");
    return 1;
  }
  printf("fopen ok\n");
  int ch = fgetc(f);
  printf("first char: %d\n", ch);
  fclose(f);
  return 0;
}
