#include <stdio.h>
#include <string.h>

void squeeze(char s1[], char s2[]);

int main(void)
{
  char s[] = "beep boop";
  char d[] = "beep boop";
  char remove[] = "pb";
  squeeze(s, remove);
  printf("%s without %s is: %s\n", d, remove, s);
}

void squeeze(char s[], char remove[])
{
  int i, j, k;
  int slen = strlen(s);
  int rlen = strlen(remove);
  int should_remove_char;

  for (i = j = 0; i < slen; i++)
  {
    should_remove_char = 0;
    for (k = 0; k < rlen; k++)
    {
      if (s[i] == remove[k])
        should_remove_char = 1;
    }

    if (!should_remove_char)
      s[j++] = s[i];
  }
  s[j] = '\0';
}
