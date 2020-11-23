#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/getline.c"
#include "../utils/strlist.c"
#include "../chapter-5/strutils.c"

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
void remove_non_alpha(char *);
int is_not_noise_word(char *);
int starts_alpha(char *);

int main(void)
{
  strlist *words;
  strlist *start;
  tnode *refs = NULL;
  char line[MAX_LINE_LENGTH];
  int line_number = 1;
  while (getline_(line, MAX_LINE_LENGTH) != EOF)
  {
    words = whitespace_split(line);
    start = words;
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

void remove_non_alpha(char *str)
{
  int j = 0;
  for (int i = 0, len = strlen(str); i < len; i++)
    if (isalpha(str[i]))
      str[j++] = str[i];
  str[j] = '\0';
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

char *noise_words[] = {
    "of",
    "and",
    "the",
    "a",
    "i",
    "in",
    "it",
    "or",
    "to",
    "is",
    "was",
    "this",
    "which",
    "who",
    "with",
};

#define NUM_NOISE_WORDS (sizeof noise_words / sizeof noise_words[0])

int starts_alpha(char *word)
{
  return isalpha(*word);
}

int is_not_noise_word(char *word)
{
  for (int i = 0; i < NUM_NOISE_WORDS; i++)
    if (strcmp(word, noise_words[i]) == 0)
      return 0;
  return 1;
}
