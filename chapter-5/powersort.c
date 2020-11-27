#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "getline.c"
#include "../utils/argv.c"

#define MAXLINES 50
#define MAXLEN 20

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], char *storage, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
void str_to_dir_order(char *);
void field_substr(char *);

struct Opts
{
  int numeric;
  int reversed;
  int folded;
  int dir_ordered;
  int field_index;
};

static struct Opts opts = {0, 0, 0, 0, -1};

int main(int argc, char *argv[])
{
  opts.numeric = argv_has_flag('n', argc, argv);
  opts.reversed = argv_has_flag('r', argc, argv);
  opts.folded = argv_has_flag('f', argc, argv);
  opts.dir_ordered = argv_has_flag('d', argc, argv);
  opts.field_index = argv_int_opt('+', argc, argv);

  char storage[MAXLINES * MAXLEN];
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0)
  {
    qsort_((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(opts.numeric ? numcmp : strcmp));
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
  if (opts.reversed)
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
  {
    char *s1 = malloc(strlen(v[i]) + 1);
    char *s2 = malloc(strlen(v[left]) + 1);
    strcpy(s1, v[i]);
    strcpy(s2, v[left]);

    if (opts.field_index != -1)
    {
      field_substr(s1);
      field_substr(s2);
    }

    if (opts.folded)
    {
      str_to_lower(s1);
      str_to_lower(s2);
    }

    if (opts.dir_ordered)
    {
      str_to_dir_order(s1);
      str_to_dir_order(s2);
    }

    if ((*comp)(s1, s2) < 0)
      swap(v, ++last, i);
    free(s1);
    free(s2);
  }
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

void str_to_dir_order(char *str)
{
  int i, j, len = strlen(str);
  for (i = 0, j = 0; i < len; i++)
    if (isalnum(str[i]) || str[i] == ' ')
      str[j++] = str[i];
  str[j] = '\0';
}

#define FIELD_SEP '|'

void field_substr(char *str)
{
  int i, j, len = strlen(str);
  int current_idx = 0;
  for (i = 0, j = 0; i < len; i++)
  {
    if (str[i] == FIELD_SEP)
      current_idx++;
    else if (current_idx == opts.field_index)
      str[j++] = str[i];
    else if (current_idx > opts.field_index)
      str[j++] = '\0';
  }
  str[j] = '\0';
}
