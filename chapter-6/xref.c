#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/getline_debug.c"
#include "../utils/strlist.c"
#include "../utils/strutils.c"

#define MAX_LINE_LENGTH 150
#define MAX_OCCURRENCES 1000

typedef struct tnode
{
  char *word;
  int line_numbers[MAX_OCCURRENCES];
  struct tnode *left;
  struct tnode *right;
} tnode;

tnode *record_occurrence(tnode *, char *, int);
void print_refs(tnode *);

int main(void)
{
  strlist *words;
  tnode *refs = NULL;
  char line[MAX_LINE_LENGTH];
  int line_number = 1;

  while (getline_(line, MAX_LINE_LENGTH) != EOF)
  {
    words = whitespace_split(line);
    words = filter_strlist(words, starts_alpha);
    mutate_strlist(words, str_to_lower);
    mutate_strlist(words, remove_non_alpha);
    words = filter_strlist(words, is_not_noise_word);
    while (words->next != NULL)
    {
      refs = record_occurrence(refs, words->str, line_number);
      words = words->next;
    }
    line_number += 1;
  }
  print_refs(refs);
}

void print_refs(tnode *p)
{
  if (p != NULL)
  {
    print_refs(p->left);
    printf("%s:", p->word);
    for (int i = 0; i < MAX_OCCURRENCES && p->line_numbers[i] != -1; i++)
      printf(" %d", p->line_numbers[i]);
    printf("\n");
    print_refs(p->right);
  }
}

tnode *record_occurrence(tnode *pnode, char *str, int line_number)
{
  if (pnode == NULL)
  {
    pnode = malloc(sizeof(tnode));
    pnode->word = strdup(str);
    pnode->line_numbers[0] = line_number;
    for (int i = 1; i < MAX_OCCURRENCES; i++)
      pnode->line_numbers[i] = -1;

    return pnode;
  }

  int cond = strncmp(str, pnode->word, strlen(pnode->word));
  if (cond == 0)
  {
    for (int i = 0; i < MAX_OCCURRENCES; i++)
      if (pnode->line_numbers[i] == -1 || pnode->line_numbers[i] == line_number)
      {
        pnode->line_numbers[i] = line_number;
        return pnode;
      }
  }
  else if (cond < 0)
    pnode->left = record_occurrence(pnode->left, str, line_number);
  else
    pnode->right = record_occurrence(pnode->right, str, line_number);
  return pnode;
}
