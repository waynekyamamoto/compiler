#include <stdio.h>

int main() {
  int x = 7;
  int *p;

  p = &x;
  printf("x=%d\n", x);
  printf("*p=%d\n", *p);

  *p = 42;
  printf("x=%d\n", x);
  return 0;
}
