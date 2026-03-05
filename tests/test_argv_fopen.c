int printf(int *fmt, ...);
int *fopen(int *path, int *mode);
int fgetc(int *f);
int fclose(int *f);
int *malloc(int size);

int main(int argc, int *argv) {
  printf("argc=%d\n", argc);
  if (argc < 2) { return 1; }
  int *c_path = argv[1];
  printf("path=%s\n", c_path);
  int *f = fopen(c_path, "r");
  if (f == 0) {
    printf("cannot open\n");
    return 1;
  }
  printf("opened ok\n");
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
  return 0;
}
