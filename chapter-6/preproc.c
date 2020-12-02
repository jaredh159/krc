#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/getline.c"
#include "../utils/strlist.c"
#include "../utils/strutils.c"

typedef struct nlist
{
  struct nlist *next;
  char *name;
  char *defn;
} nlist;

#define HASHSIZE 101

static nlist *hashtab[HASHSIZE];

nlist *install(char *, char *);
unsigned hash(char *);
int undef(char *);
nlist *lookup(char *);

#define MAX_LINE_LENGTH 100

int is_macro_line(char *);
void handle_macro_line(char *);
int buffer_next_word(char *, int *, char *);

int main(void)
{
  int idx;
  char line[MAX_LINE_LENGTH];
  char word[MAX_LINE_LENGTH];

  while (getline_(line, MAX_LINE_LENGTH) != EOF)
  {
    if (is_macro_line(line))
    {
      handle_macro_line(line);
      continue;
    }

    idx = 0;
    while (buffer_next_word(line, &idx, word))
    {
      nlist *symbol;
      symbol = lookup(word);
      printf("%s", symbol == NULL ? word : symbol->defn);
    }
    putchar('\n');
  }
}

int is_c_delim_char(char c)
{
  return (c == ';' || c == '*' || c == '[' || c == ']' || c == '{' || c == '}' || c == ')' || c == '(');
}

int buffer_next_word(char *line, int *line_idx, char *word)
{
  int c;
  int in_word = 0;
  int word_idx = 0;
  int line_len = strlen(line);
  for (; *line_idx < line_len; (*line_idx)++)
  {
    c = line[*line_idx];
    if (!in_word)
    {
      if (is_whitespace(c) || is_c_delim_char(c))
        putchar(c);
      else
      {
        word[word_idx++] = c;
        in_word = 1;
      }
    }
    else
    {
      if (is_word_end(c) || is_c_delim_char(c))
      {
        word[word_idx] = '\0';
        return 1;
      }
      else
        word[word_idx++] = c;
    }
  }
  if (in_word)
  {
    word[word_idx] = '\0';
    return 1;
  }
  return 0;
}

int undef(char *name)
{
  nlist *last = NULL;
  nlist *current = NULL;
  unsigned int hashed = hash(name);
  for (current = hashtab[hashed]; current != NULL; current = current->next)
  {
    if (strcmp(current->name, name) == 0)
    {
      nlist *next = current->next;
      free((void *)current->name);
      free((void *)current->defn);
      free((void *)current);
      if (last == NULL)
        hashtab[hashed] = next;
      else
        last->next = next;
      return 1;
    }
    last = current;
  }
  return 0;
}

unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

nlist *lookup(char *s)
{
  nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;
  return NULL;
}

nlist *install(char *name, char *defn)
{
  nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL)
  {
    np = (nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else
    free((void *)np->defn);
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

int is_define(char *line)
{
  return strncmp("#define", line, 7) == 0;
}

int is_undef(char *line)
{
  return strncmp("#undef", line, 6) == 0;
}

int is_macro_line(char *line)
{
  return is_undef(line) || is_define(line);
}

void die(char *msg)
{
  printf("%s\n", msg);
  exit(1);
}

void handle_macro_line(char *line)
{
  char *name;
  char *defn;
  strlist *words = whitespace_split(line);

  if (is_define(line))
  {
    if (strlist_len(words) < 3)
      die("syntax error defining symbol");

    name = words->next->str;
    defn = words->next->next->str;
    install(name, defn);
    return;
  }

  if (strlist_len(words) < 2)
    die("syntax error un-defing symbol");

  name = words->next->str;
  undef(name);
}
