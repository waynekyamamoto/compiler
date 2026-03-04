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
  int count = 0;
  int ch = fgetc(f);
  while (ch != 0 - 1) {
    count = count + 1;
    ch = fgetc(f);
  }
  fclose(f);
  printf("count=%d\n", count);
  return 0;
}
