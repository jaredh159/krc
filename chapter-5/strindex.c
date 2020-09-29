#include <stdio.h>
#include <string.h>

int strindex(char *haystack, char *needle)
{
  int i, j, k;

  for (i = 0; *(haystack + i) != '\0'; i++)
  {
    for (j = i, k = 0; *(needle + k) != '\0' && *(haystack + j) == *(needle + k); j++, k++)
      ;
    if (k > 0 && *(needle + k) == '\0')
      return i;
  }
  return -1;
}

int strindex2(char *haystack, char *needle)
{
  char *haystack_start = haystack;
  char *needle_start = needle;
  while (*haystack != '\0')
  {
    char *current_haystack = haystack;
    needle = needle_start;
    while (*needle != '\0' && *needle == *current_haystack)
    {
      needle++;
      current_haystack++;
    }
    if (*needle == '\0' && (needle - needle_start > 0))
      return haystack - haystack_start;
    haystack++;
  }
  return -1;
}

int main(void)
{
  char needle[] = "lol";
  char haystack[] = "foo-lol";
  printf("rightmost index of %s in %s is %d\n", needle, haystack, strindex2(haystack, needle));
}
