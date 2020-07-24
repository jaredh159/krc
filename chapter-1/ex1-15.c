#include <stdio.h>

float getCelcius(float fahr);

int main(void)
{
  float fahr, lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("F  C\n-----\n");

  fahr = lower;
  while (fahr <= upper)
  {
    printf("%3.0f %6.1f\n", fahr, getCelcius(fahr));
    fahr += step;
  }
}

float getCelcius(float fahr)
{
  return (5.0 / 9.0) * (fahr - 32.0);
}
