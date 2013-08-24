#include <stdio.h>

int fitsBits(int, int);

int main() {
  printf("%d\n", fitsBits(0x80000000, 32));
  return 0;
}

int fitsBits(int x, int n) {
  int mask = ~(~0 << n);
  return !((x & mask) ^ x);
}

