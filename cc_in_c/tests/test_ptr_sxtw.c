int printf(int *fmt, ...);
int *malloc(int size);

int main() {
  int *p = malloc(100);
  printf("ptr = %p\n", p);
  return 0;
}
