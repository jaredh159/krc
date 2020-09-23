#include <stdio.h>
#include <ctype.h>
#include "getch.c"

int getch(void);
void ungetch(int);

int getint(int *pn)
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
    // printf("char is: ");
    // putchar(c);
    // printf("\n");
    *pn = 10 * *pn + (c - '0');
  }

  *pn *= sign;

  if (c != EOF)
    ungetch(c);

  return c;
}

int main(void)
{
  int n, array[100];

  array[1] = 43;

  for (n = 0; n < 100 && getint(&array[n]) != EOF; n++)
    ;

  printf("%d\n", array[1]);
}
