#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getline.c"
#include "argv.c"

#define MAXLINES 50
#define MAXLEN 20

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], char *storage, int nlines);
void writelines(char *lineptr[], int nlines, int reversed);
void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);

int main(int argc, char *argv[])
{
  int numeric = argv_idx("-n", argc, argv) != -1;
  int reversed = argv_idx("-r", argc, argv) != -1;

  char storage[MAXLINES * MAXLEN];
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0)
  {
    qsort_((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines, reversed);
    return 0;
  }
  else
  {
    printf("error: input too big to sort\n");
    return 1;
  }
}

extern int getline_(char *, int);

int readlines(char *l_lineptr[], char *storage, int maxlines)
{
  int len, nlines;
  char line[MAXLEN];
  char *p = storage;

  nlines = 0;
  while ((len = getline_debug(line, MAXLEN)) > 0)
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

void writelines(char *lineptr[], int nlines, int reversed)
{
  if (reversed)
  {
    while (nlines-- > 0)
      printf("%s\n", *(lineptr + nlines));
    return;
  }
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

void qsort_(void *v[], int left, int right, int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort_(v, left, last - 1, comp);
  qsort_(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int numcmp(const char *s1, const char *s2)
{
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}
