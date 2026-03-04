int printf(int *fmt, ...);
int *fopen(int *path, int *mode);
int fgetc(int *f);
int fclose(int *f);
int *malloc(int size);

int main() {
  int *f = fopen("test_trivial.c", "r");
  if (f == 0) {
    printf("fopen failed\n");
    return 1;
  }
  printf("fopen ok\n");
  int *srcbuf = malloc(1000 * 1000);
  int srclen = 0;
  int ch = fgetc(f);
  while (ch != 0 - 1) {
    __write_byte(srcbuf, srclen, ch);
    srclen = srclen + 1;
    ch = fgetc(f);
  }
  __write_byte(srcbuf, srclen, 0);
  fclose(f);
  printf("read %d bytes\n", srclen);
  int i = 0;
  while (i < srclen) {
    int c = __read_byte(srcbuf, i);
    printf("%d ", c);
    i = i + 1;
  }
  printf("\n");
  return 0;
}
