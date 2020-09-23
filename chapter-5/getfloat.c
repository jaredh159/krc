#include <stdio.h>
#include <ctype.h>
#include "getch.c"

int getch(void);
void ungetch(int);

int getfloat(double *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-')
  {
    ungetch(c);
    return 0;
  }

  sign = c == '-' ? -1 : 1;
  if (c == '+' || c == '-')
  {
    int symbol = c;
    c = getch();
    if (!isdigit(c))
    {
      ungetch(c);
      ungetch(c);
      return symbol;
    }
  }

  for (*pn = 0; isdigit(c); c = getch())
  {
    *pn = 10 * *pn + (c - '0');
  }

  if (c == '.')
  {
    int divisor = 1;
    c = getch();
    for (; isdigit(c); c = getch())
    {
      *pn = 10 * *pn + (c - '0');
      divisor *= 10;
    }
    *pn /= divisor;
  }

  *pn *= sign;

  if (c != EOF)
    ungetch(c);

  return c;
}

int main(void)
{
  int n;

  double array[100];

  array[1] = 43.0;

  for (n = 0; n < 100 && getfloat(&array[n]) != EOF; n++)
    ;

  printf("%f\n", array[0]);
}
