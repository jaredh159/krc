#include <stdio.h>

#define MAX_LINE_LENGTH 40
#define FOLD_LENGTH 10

int readline(char s[], int lim);
int stringlen(char s[]);
void splitline(char line[], int split, char before[], char after[]);
void handle_input_line(char line[]);

int main(void)
{
  char line[MAX_LINE_LENGTH];

  while (readline(line, MAX_LINE_LENGTH) != 0)
    handle_input_line(line);
}

void handle_input_line(char line[])
{
  int i;
  char before[MAX_LINE_LENGTH];
  char after[MAX_LINE_LENGTH];
  int line_length = stringlen(line);

  if (line_length < FOLD_LENGTH)
  {
    printf("%s", line);
    return;
  }

  for (i = FOLD_LENGTH; i > 0; i--)
  {
    if (line[i] == ' ' || line[i] == '\t')
    {
      splitline(line, i, before, after);
      printf("%s\n", before);
      return handle_input_line(after);
    }
  }

  splitline(line, FOLD_LENGTH, before, after);
  printf("%s[split]\n", before);
  return handle_input_line(after);
}

void splitline(char line[], int split, char before[], char after[])
{
  int i;
  for (i = 0; line[i] != '\0'; i++)
  {
    if (i < split)
      before[i] = line[i];
    else if (i == split)
    {
      before[i] = '\0';
      after[i - split] = line[i];
    }
    else if (i > split)
      after[i - split] = line[i];
  }
  after[i - split] = '\0';
}

int readline(char s[], int lim)
{
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
  {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';
  return i;
}

int stringlen(char s[])
{
  int len = 0;
  while (s[len] != '\0')
    len++;
  return len;
}
