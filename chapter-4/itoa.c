#include <stdio.h>

void itoa(int n, char str[])
{
  if (n < 0)
  {
    n = -n;
    str[0] = '-';
    str[1] = '\0';
  }

  if (n / 10)
    itoa(n / 10, str);

  int i = 0;
  while (str[i] != '\0')
    i++;

  str[i] = n % 10 + '0';
  str[i++] = '\0';
}

int main(void)
{
  char mystr[20];
  int num = -123;
  itoa(num, mystr);
  printf("%s\n", mystr);
}
