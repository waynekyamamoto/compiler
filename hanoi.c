#include <stdio.h>

int hanoi(int n, int from, int to, int aux) {
  if (n == 1) {
    printf("Move %d -> %d\n", from, to);
    return 0;
  } else {
    hanoi(n - 1, from, aux, to);
    printf("Move %d -> %d\n", from, to);
    hanoi(n - 1, aux, to, from);
    return 0;
  }
}

int main() {
  hanoi(3, 1, 3, 2);
  return 0;
}
