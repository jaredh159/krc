#include <stdio.h>
#include <string.h>

int any(char haystack[], char needles[])
{
  int i, j;
  int hlen = strlen(haystack);
  int nlen = strlen(needles);

  for (i = 0; i < hlen; i++)
  {
    for (j = 0; j < nlen; j++)
    {
      if (haystack[i] == needles[j])
        return i;
    }
  }
  return -1;
}

int main(void)
{
  char haystack[] = "Foobar";
  char needles[] = "Fr";

  printf("any(%s, %s) => %d\n", haystack, needles, any(haystack, needles));
}
