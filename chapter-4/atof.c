#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof(char s[])
{
  double val, divisor, exponent;
  int i, sign, exponent_sign;

  for (i = 0; isspace(s[i]); i++)
    ; /* skip whitespace */

  sign = s[i] == '-' ? -1 : 1;
  if (s[i] == '-' || s[i] == '+')
    i++; /* move past optional sign char */

  /* non decimal digits */
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++; /* move past decimal point */

  for (divisor = 1.0; isdigit(s[i]); i++)
  {
    val = 10.0 * val + (s[i] - '0');
    divisor *= 10.0;
  }

  if (s[i] == 'e' || s[i] == 'E')
  {
    i++;
    exponent_sign = s[i] == '-' ? -1 : 1;

    if (s[i] == '-' || s[i] == '+')
      i++; /* move past optional sign char for exp */

    for (exponent = 0.0; isdigit(s[i]); i++)
      exponent = 10.0 * exponent + (s[i] - '0') * exponent_sign;

    val = val * pow(10.0, exponent);
  }

  return sign * val / divisor;
}

int main(void)
{
  char s[] = "6E+5";
  printf("%s becomes %f\n", s, atof(s));
}
