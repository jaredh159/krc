#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../utils/getline.c"
#include "../utils/strlist.c"
#include "../utils/strutils.c"

#define MAX_LINE_LENGTH 150

typedef struct node
{
  char *word;
  int count;
  struct node *left;
  struct node *right;
} node;

node *count_word(node *, char *);
int largest_count(node *, int, int);
void print_counts(node *, int);

int main(void)
{
  strlist *words = NULL;
  node *counts = NULL;
  char line[MAX_LINE_LENGTH];

  while (getline_(line, MAX_LINE_LENGTH) != EOF)
  {
    words = whitespace_split(line);
    words = filter_strlist(words, starts_alpha);
    mutate_strlist(words, str_to_lower);
    mutate_strlist(words, remove_non_alpha);
    words = filter_strlist(words, is_not_noise_word);

    while (words != NULL && words->str != NULL)
    {
      counts = count_word(counts, words->str);
      words = words->next;
    }
  }

  int prev_highest;
  int highest = -1;
  int ceil = INT_MAX;
  do
  {
    prev_highest = highest;
    highest = largest_count(counts, 0, ceil);
    print_counts(counts, highest);
    ceil = highest;
  } while (prev_highest != highest && highest > 1);
}

int largest_count(node *counts_node, int largest, int ceil)
{
  if (counts_node == NULL)
    return largest;
  largest = largest_count(counts_node->left, largest, ceil);
  if (counts_node->count > largest && counts_node->count < ceil)
    largest = counts_node->count;
  return largest_count(counts_node->right, largest, ceil);
}

void print_counts(node *node, int count)
{
  if (node == NULL || count < 1)
    return;
  print_counts(node->left, count);
  if (node->count == count)
    printf("%03d: %s\n", count, node->word);
  print_counts(node->right, count);
}

node *count_word(node *pnode, char *str)
{
  if (pnode == NULL)
  {
    pnode = malloc(sizeof(node));
    pnode->word = strdup(str);
    pnode->count = 1;
    pnode->left = NULL;
    pnode->right = NULL;
    return pnode;
  }
  int compare = strcmp(str, pnode->word);
  if (compare == 0)
    pnode->count += 1;
  else if (compare < 0)
    pnode->left = count_word(pnode->left, str);
  else
    pnode->right = count_word(pnode->right, str);
  return pnode;
}
