#include <stdio.h>

int main(void)
{
  float celc, fahr, lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("  C      F\n-----------\n");

  celc = lower;
  while (celc <= upper)
  {
    fahr = (celc + 32.0) / (5.0 / 9.0);
    printf("%3.0f %6.1f\n", celc, fahr);
    celc += step;
  }
}
