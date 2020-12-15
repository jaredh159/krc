#include <stdio.h>
#include <string.h>

#define MAXLINE 100

/* Exercise 7-6. Write a program to compare two files,
   printing the first line where they differ. */
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("usage: compare <file1> <file2>\n");
    return 1;
  }

  FILE *file1 = fopen(*++argv, "r");
  if (file1 == NULL)
  {
    printf("error opening %s\n", *argv);
    return 1;
  }

  FILE *file2 = fopen(*++argv, "r");
  if (file2 == NULL)
  {
    printf("error opening %s\n", *argv);
    return 1;
  }

  char f1_line[MAXLINE];
  char f2_line[MAXLINE];
  int line_num = 1;

  while (1)
  {
    if (fgets(f1_line, MAXLINE, file1) == NULL)
      return 0;

    if (fgets(f2_line, MAXLINE, file2) == NULL)
      return 0;

    if (strcmp(f1_line, f2_line) != 0)
    {
      printf("line %d does not match:\n", line_num);
      printf("  %15s -> %s", *(argv - 1), f1_line);
      printf("  %15s -> %s", *(argv - 0), f2_line);
      fclose(file1);
      fclose(file2);
      return 0;
    }

    line_num += 1;
  }

  fclose(file1);
  fclose(file2);
  return 0;
}
