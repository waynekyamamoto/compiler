int printf(int *fmt, ...);
int *malloc(int size);

int main() {
  int *buf = malloc(1024);
  if (buf == 0) {
    printf("malloc failed\n");
    return 1;
  }
  printf("malloc ok\n");
  __write_byte(buf, 0, 65);
  __write_byte(buf, 1, 66);
  __write_byte(buf, 2, 0);
  int a = __read_byte(buf, 0);
  int b = __read_byte(buf, 1);
  printf("a=%d b=%d\n", a, b);
  return 0;
}
