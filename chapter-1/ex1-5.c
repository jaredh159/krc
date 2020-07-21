#include <stdio.h>

int main(void)
{
  float fahr, celcius, lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("F  C\n-----\n");

  fahr = upper;
  while (fahr >= lower)
  {
    celcius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celcius);
    fahr -= step;
  }
}
