#include <stdio.h>

void print_paged(FILE *file, char *filename);

/* Exercise 7-8. Write a programt to print a set of files,
   starting each new one on a new page, with a title and a
   running page count for each file. */
int main(int argc, char *argv[])
{
  char *filename;
  FILE *file;

  if (argc < 2)
  {
    printf("usage: page <...file>\n");
    return 1;
  }

  while (--argc > 0)
  {
    filename = *++argv;
    file = fopen(filename, "r");
    if (file == NULL)
    {
      printf("error opening file %s\n", filename);
      return 1;
    }
    print_paged(file, filename);
    fclose(file);
  }
}

#define MAX_LINE_LEN 200
#define PAGE_SIZE 20

void print_paged(FILE *file, char *filename)
{
  char line[MAX_LINE_LEN];
  int page_num = 1, line_num = 1;
  while (1)
  {
    if (line_num == 1)
      printf("\n\x1b[32m######### <%s> page %d #########\x1b[0m\n\n", filename, page_num);

    if (fgets(line, MAX_LINE_LEN, file) == NULL)
    {
      while (line_num++ < PAGE_SIZE)
        printf("\n");
      return;
    }

    printf("%s", line);
    line_num += 1;
    if (line_num == PAGE_SIZE)
    {
      line_num = 1;
      page_num += 1;
    }
  }
}
