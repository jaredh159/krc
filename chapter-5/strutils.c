#include <ctype.h>

int str_is_int(char *str)
{
  while (*str != '\0')
    if (!isdigit(*str++))
      return 0;
  return 1;
}
