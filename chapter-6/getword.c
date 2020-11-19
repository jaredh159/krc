#include <stdio.h>
#include <ctype.h>
#include "../utils/getch_debug.c"

int consume_str_literal(void);
int starts_comment(int);
void consume_comment(void);
int is_alnum_ext(int);

int getword(char *word, int lim)
{
  int c;
  int in_str = 0;
  char *w = word;
  while (isspace(c = getch()))
    ;

  if (c == '"')
  {
    while (consume_str_literal())
      ;
    return getword(word, lim);
  }

  if (starts_comment(c))
  {
    consume_comment();
    return getword(word, lim);
  }

  if (c != EOF)
    *w++ = c;

  if (!isalpha(c) && c != '_' && c != '#' && c != '<' && c != '>')
  {
    *w = '\0';
    return c;
  }

  for (; --lim > 0; w++)
  {
    *w = getch();
    if (*w != '_' && !isalnum(*w))
    {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

int consume_str_literal(void)
{
  int c = getch();
  return c != '"';
}

int main(void)
{
  char word[50];
  getword(word, 50);
  printf("%s\n", word);
  getword(word, 50);
  printf("%s\n", word);
  getword(word, 50);
  printf("%s\n", word);
}

int starts_comment(int c)
{
  if (c != '/')
    return 0;
  c = getch();
  if (c == '*')
    return 1;
  ungetch(c);
  return 0;
}

void consume_comment(void)
{
  int current, last = -1;
  while (1)
  {
    current = getch();
    if (current == EOF || (current == '/' && last == '*'))
      return;
    last = current;
  }
}
