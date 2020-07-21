#include <stdio.h>

int main(void)
{
  if ((getchar() != EOF) == 0)
  {
    printf("it is zero\n");
  }
  else if ((getchar() != EOF) == 1)
  {
    printf("it is one\n");
  }
  else
  {
    printf("unexpected\n");
  }
}
