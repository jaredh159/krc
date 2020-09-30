#include <stdio.h>
#include <string.h>
#include "alloc.c"
#include "getline.c"

#define MAXLINES 5000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main(void)
{
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
  {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000 /* max length of any input line */
extern int getline_(char *, int);
extern char *alloc(int);

int readlines(char *l_lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline_(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len + 1)) == NULL)
      return -1;
    else
    {
      line[len] = '\0'; /* delete newline */
      strcpy(p, line);
      l_lineptr[nlines++] = p;
    }
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
