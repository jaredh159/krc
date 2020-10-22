#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "alloc.c"

#define MAXLINES 500

int nextline(char *s, int lim);
extern char *alloc(int);
int readlines(char *lineptrs[], int maxlines);

char *line_pointers[MAXLINES];

int main(int argc, char *argv[])
{
  int nlines;
  int line_num;
  int show_lines = 18;

  argc--;
  argv++;

  if (argc == 1 && **argv == '-')
  {
    char *num_arg = *argv;
    show_lines = atoi(++num_arg);
  }

  if ((nlines = readlines(line_pointers, MAXLINES)) >= 0)
  {
    line_num = nlines - show_lines;
    if (line_num < 0)
      line_num = 0;

    while (line_num < nlines)
    {
      line_num < 9 && putchar('0');
      printf("%d: %s\n", line_num + 1, line_pointers[line_num]);
      line_num++;
    }
  }
  else
  {
    printf("error: input too big\n");
  }
}

#define MAX_LINE_LENGTH 1000

int readlines(char *lineptrs[], int maxlines)
{
  int len, nlines;
  char *p, line[maxlines];

  nlines = 0;
  while ((len = nextline(line, MAX_LINE_LENGTH)) >= 0)
  {
    if (nlines >= maxlines || (p = alloc(len + 1)) == NULL)
      return -1;
    else
    {
      line[len] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptrs[nlines++] = p;
    }
  }
  return nlines;
}

int nextline(char *s, int lim)
{
  static int more_lines = 1;

  if (!more_lines)
    return -1;

  int ret;
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *s++ = c;

  *s = '\0';
  more_lines = c != EOF;
  return i;
}
