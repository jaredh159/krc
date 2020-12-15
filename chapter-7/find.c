#include <stdio.h>
#include <stdlib.h>
#include "../utils/argv.c"

char **get_args(int argc, char *argv[]);
void find(FILE *file, char *pattern, char *filename, int except, int number);

/* 7-7: Modify the pattern finding program of Chapter 5 to take its input
   from a set of named files or, if no files are named as arguments,
   from the standard input. Should the file name be printed when a
   matching line is found? */
int main(int argc, char *argv[])
{
  int except = argv_has_flag('x', argc, argv);
  int number = argv_has_flag('n', argc, argv);

  char **args = get_args(argc, argv);
  if (args[0] == NULL)
  {
    printf("incorrect usage: find [-xn] <pattern> [...file]\n");
    return 1;
  }

  char *pattern = args[0];
  if (args[1] == NULL)
  {
    find(stdin, pattern, "<stdin>", except, number);
    return 0;
  }

  FILE *file;
  int i;
  for (i = 1; args[i] != NULL; i++)
  {
    file = fopen(args[i], "r");
    if (file == NULL)
    {
      printf("error opening file %s\n", args[i]);
      continue;
    }
    find(file, pattern, args[i], except, number);
    fclose(file);
  }
}

#define MAX_LINE_LEN 100

void find(FILE *file, char *pattern, char *filename, int except, int number)
{
  int line_num = 0;
  char line[MAX_LINE_LEN];

  while (1)
  {
    if (fgets(line, MAX_LINE_LEN, file) == NULL)
      return;

    line_num += 1;
    if ((strstr(line, pattern) != NULL) != except)
    {
      printf("%10s", filename);
      if (number)
        printf(":%-3d - ", line_num);
      else
        printf(" - ");
      printf("%s", line);
    }
  }
}

#define MAX_FILENAMES 10

char **get_args(int argc, char *argv[])
{
  /* move past program name */
  argc--;
  argv++;

  int i, j = 0;
  char **args = malloc((MAX_FILENAMES + 1) * sizeof(char *));

  for (i = 0; i < argc && i <= MAX_FILENAMES; i++)
    if (argv[i][0] != '-')
      args[j++] = argv[i];

  args[j] = NULL;
  return args;
}
