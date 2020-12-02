#include <stdlib.h>

typedef struct strlist
{
  char *str;
  struct strlist *next;
  int line_idx;
} strlist;

strlist *whitespace_split(char *line)
{
  int index = 0;
  int j, k;
  int line_len = strlen(line);
  strlist *p_first = malloc(sizeof(strlist));
  strlist *current = p_first;

  for (index = 0; index < line_len; index++)
  {
    j = 0;
    while (line[index + j] == ' ')
      j += 1;

    while ((index + j) < line_len && line[index + j] != ' ')
      j += 1;

    if (j > 0)
    {
      int word_len = j + 1;
      current->line_idx = index;
      current->str = malloc(word_len);
      for (k = 0; k < j; k++)
        current->str[k] = line[index + k];
      current->str[j] = '\0';
      current->next = malloc(sizeof(strlist));
      current = current->next;
      index += j;
    }
  }

  return p_first;
}

strlist *push_unique(strlist *strs, char *word)
{
  if (strs == NULL)
  {
    strs = malloc(sizeof(strlist));
    strs->str = strdup(word);
  }
  else if (strs->str == NULL)
    strs->str = strdup(word);
  else if (strcmp(strs->str, word) != 0)
    strs->next = push_unique(strs->next, word);
  return strs;
}

void mutate_strlist(strlist *strs, void (*mutator)(char *))
{
  while (strs->str != NULL)
  {
    (*mutator)(strs->str);
    strs = strs->next;
  }
}

strlist *filter_strlist(strlist *start, int (*predicate)(char *))
{
  if (start == NULL || start->next == NULL)
    return start;

  if ((*predicate)(start->str) == 0)
    return filter_strlist(start->next, predicate);

  start->next = filter_strlist(start->next, predicate);
  return start;
}

void free_strlist(strlist *words)
{
  strlist *next;
  while (words->next != NULL)
  {
    next = words->next;
    free(words);
    words = next;
  }
}

int strlist_len(strlist *words)
{
  int len = 0;
  for (; words != NULL; words = words->next)
    if (words->str != NULL)
      len += 1;
  return len;
}
