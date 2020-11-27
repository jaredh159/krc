#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/getline_debug.c"
#include "../utils/strlist.c"
#include "../utils/argv.c"

#define MAX_LINE_LEN 100

typedef struct grp_node
{
  char *prefix;
  strlist *vars;
  struct grp_node *right;
  struct grp_node *left;
} grp_node;

int next_var(int *, char *, char *);
int is_whitespace(char);
int is_word_end(char);
int is_keyword(char *);
int consume_skippable(int *, char *);
int consume_whitespace(int *, char *);
int consume_comment(int *, char *);
int consume_string(int *, char *);
int consume_non_vars(int *, char *);
grp_node *add_var(grp_node *, char *);
int pref_len = 3;

grp_node *add_var(grp_node *node, char *var)
{
  if (node == NULL)
  {
    node = malloc(sizeof(grp_node));
    node->prefix = malloc(pref_len + 1);
    strncpy(node->prefix, var, pref_len);
    node->left = NULL;
    node->right = NULL;
    node->vars = malloc(sizeof(strlist));
    node->vars->str = strdup(var);
    node->vars->next = NULL;
  }

  return NULL;
}

/* write a program that reads a C program and prints in alphabetical order each group
   of variable names that are identical in the first 6 characters, but different
   somewhat thereafter. Don't count words withing strings and comments. Make `6`
   a parameter that can be set from the command line. */
int main(int argc, char *argv[])
{
  int idx;
  char var[MAX_LINE_LEN];
  char line[MAX_LINE_LEN];
  grp_node *grps = NULL;

  int user_length = argv_int_opt('-', argc, argv);
  if (user_length != -1)
    pref_len = user_length;

  // int test_idx = 0;
  // char *test = "#inc foob <rofl> { } lolbar";
  // //            0123456789012345678
  // i = 0;
  // int ret = next_var(&i, test, var);
  // printf("var: %s, return: %d, index: %d\n", var, ret, i);
  // ret = next_var(&i, test, var);
  // printf("var: %s, return: %d, index: %d\n", var, ret, i);
  // return 0;

  while (getline_(line, MAX_LINE_LEN) != EOF)
  {
    idx = 0;
    while (next_var(&idx, line, var))
      grps = add_var(grps, var);
  }
}

int consume_skippable(int *idx, char *line)
{
  if (consume_whitespace(idx, line))
    return consume_skippable(idx, line);
  if (consume_comment(idx, line))
    return consume_skippable(idx, line);
  if (consume_string(idx, line))
    return consume_skippable(idx, line);
  if (consume_non_vars(idx, line))
    return consume_skippable(idx, line);
  return 0;
}

int next_var(int *idx, char *line, char *word)
{
  consume_skippable(idx, line);
  if (*idx >= strlen(line) - 1)
    return 0;

  if (line[*idx] == '*')
    *idx += 1;

  int i = 0;
  while (!is_word_end(line[*idx]))
    word[i++] = line[(*idx)++];
  word[i] = '\0';

  if (strlen(word) < pref_len)
    return next_var(idx, line, word);

  if (is_keyword(word))
    return next_var(idx, line, word);

  return 1;
}

int consume_string(int *idx, char *line)
{
  if (line[*idx] != '"')
    return 0;

  *idx += 1;
  while (line[*idx] != '"' || line[*idx] == '\\')
    *idx += 1;

  *idx += 1;
  return 1;
}

int consume_whitespace(int *idx, char *line)
{
  int start_idx = *idx;
  while (is_whitespace(line[*idx]))
    *idx += 1;
  return *idx != start_idx;
}

int consume_comment(int *idx, char *line)
{
  if (line[*idx] != '/')
    return 0;

  if (line[*idx + 1] != '*')
    return 0;

  *idx += 2;
  while (line[*idx] != '*' || line[*idx + 1] != '/')
    *idx += 1;

  *idx += 2;
  return 1;
}

int consume_non_vars(int *idx, char *line)
{
  if (line[*idx] == '_' || isalpha(line[*idx]) || line[*idx] == '*')
    return 0;

  *idx += 1;
  while (!is_word_end(line[*idx]))
    *idx += 1;

  return 1;
}

int is_word_end(char c)
{
  return (is_whitespace(c) || c == '\0');
}

int is_whitespace(char c)
{
  return (c == ' ' || c == '\t');
}

static char *keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
};

#define NUM_KEYWORDS (sizeof keywords / sizeof keywords[0])

int is_keyword(char *word)
{
  for (int i = 0; i < NUM_KEYWORDS; i++)
    if (strcmp(word, keywords[i]) == 0)
      return 1;
  return 0;
}
