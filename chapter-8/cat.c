#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define STDIN_FD 0
#define STDOUT_FD 1
void filecopy(int fd);

/* Exercize 8-1. Rewrite the program `cat` from Chapter 7 using
   `read`, `write`, `open`, and `close` instead of their standard
   library equivalents. */
int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    filecopy(STDIN_FD);
    return 0;
  }

  int fd;
  while (--argc > 0)
  {
    fd = open(*++argv, O_RDONLY, 0);
    if (fd == -1)
    {
      printf("cat: can't open %s\n", *argv);
      return 1;
    }
    else
    {
      filecopy(fd);
    }
  }
}

#define BUFSIZE 4096

void filecopy(int fd_src)
{
  char buf[BUFSIZE];
  int n;

  while ((n = read(fd_src, buf, BUFSIZE)) > 0)
    write(STDOUT_FD, buf, n);
}
