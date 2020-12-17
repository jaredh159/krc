#include <stdio.h>

#define is_up(c) (((c) >= 'A' && (c) <= 'Z') ? 1 : 0)

int is_upper_(int c)
{
  return c >= 'A' && c <= 'Z';
}

int main(void)
{
  printf("%d, %d\n", is_up('X'), is_up('q'));
}
