#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(void)
{
  install("foo", "bar");
  install("lol", "bar");
  undef("lol");
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
