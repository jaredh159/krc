#include <ctype.h>

int str_is_int(char *str)
{
  while (*str != '\0')
    if (!isdigit(*str++))
      return 0;
  return 1;
}

void str_to_lower(char *str)
{
  for (int i = 0, len = strlen(str); i < len; i++)
    str[i] = tolower(str[i]);
}

void remove_non_alpha(char *str)
{
  int j = 0;
  for (int i = 0, len = strlen(str); i < len; i++)
    if (isalpha(str[i]))
      str[j++] = str[i];
  str[j] = '\0';
}

int is_whitespace(char c)
{
  return (c == ' ' || c == '\t');
}

int is_word_end(char c)
{
  return (is_whitespace(c) || c == '\0');
}

static char *noise_words[] = {
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
