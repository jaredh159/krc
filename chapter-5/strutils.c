#include <ctype.h>

int str_is_int(char *str)
{
  while (*str != '\0')
    if (!isdigit(*str++))
      return 0;
  return 1;
}

void str_to_lower(char *str)
{
  for (int i = 0, len = strlen(str); i < len; i++)
    str[i] = tolower(str[i]);
}
