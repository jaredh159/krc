#include <stdio.h>
#include <string.h>

int strrindex(char haystack[], char needle[])
{
  int index = -1;
  int i, j;
  int needlelen = strlen(needle);
  if (needlelen == 0)
  {
    return index;
  }

  for (i = 0; haystack[i] != '\0'; i++)
  {
    for (j = 0; needle[j] != '\0' && haystack[i + j] != '\0' && haystack[i + j] == needle[j]; j++)
      ;
    if (j == needlelen)
      index = i;
  }
  return index;
}

int main(void)
{
  char needle[] = "lol";
  char haystack[] = "";
  printf("rightmost index of %s in %s is %d\n", needle, haystack, strrindex(haystack, needle));
}
