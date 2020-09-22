#include <stdio.h>
#define swap(t, x, y) \
  {                   \
    t tmp = x;        \
    x = y;            \
    y = tmp;          \
  }

int main(void)
{
  int x = 1;
  int y = 2;
  swap(int, x, y);
  printf("x: %d, y: %d\n", x, y);
}
