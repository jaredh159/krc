#include <stdio.h>
#include <string.h>
#include "alloc.c"
#include "getline.c"

#define MAXLINES 50
#define MAXLEN 20

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], char *storage, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main(void)
{
  char storage[MAXLINES * MAXLEN];
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0)
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

extern int getline_(char *, int);
extern char *alloc(int);

int readlines(char *l_lineptr[], char *storage, int maxlines)
{
  int len, nlines;
  char line[MAXLEN];
  char *p = storage;

  nlines = 0;
  while ((len = getline_(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p > (storage + MAXLINES * MAXLEN - len)))
      return -1;
    else
    {
      line[len] = '\0'; /* delete newline */
      strcpy(p, line);
      l_lineptr[nlines++] = p;
      p += len + 1;
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
