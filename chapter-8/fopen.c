#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include "syscalls.h"

#undef NULL
#define PERMS 0666
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct flags
{
  unsigned int read : 1;
  unsigned int write : 1;
  unsigned int unbuf : 1;
  unsigned int eof : 1;
  unsigned int err : 1;
} flags;

typedef struct _iobuf
{
  int cnt;
  char *ptr;
  char *base;
  flags flag;
  int fd;
} FILE_;

extern FILE_ _iob[OPEN_MAX];

flags stdinFlags = {1, 0, 0, 0, 0};
flags stdoutFlags = {0, 1, 0, 0, 0};
flags stderrFlags = {0, 1, 1, 0, 0};

FILE_ _iob[OPEN_MAX] = {{0, (char *)0, (char *)0, {1, 0, 0, 0, 0}, 0},
                        {0, (char *)0, (char *)0, {0, 1, 0, 0, 0}, 1},
                        {0, (char *)0, (char *)0, {0, 1, 1, 0, 0}, 2}};

#define stdin_ &_iob[0]
#define stdout_ &_iob[1]
#define stderr_ &_iob[2]

int _fillbuf(FILE_ *);
int _flushbuf(int, FILE_ *);

#define getc_(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc_(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar_() getc(stdin)
#define putchar_(x) putc((x), stdout)

FILE_ *fopen_(char *name, char *mode)
{
  int fd;
  FILE_ *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (fp->flag.read == 0 && fp->flag.write == 0)
      break;                 /* found free slot */
  if (fp >= _iob + OPEN_MAX) /* no free slots */
    return NULL;
  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a')
  {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  }
  else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1) /* couldn't access name */
    return NULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag.unbuf = 0;
  fp->flag.eof = 0;
  fp->flag.err = 0;
  if (*mode == 'r')
  {
    fp->flag.read = 1;
    fp->flag.write = 0;
  }
  else
  {
    fp->flag.read = 0;
    fp->flag.write = 1;
  }
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE_ *fp)
{
  int bufsize;
  if (!fp->flag.read || fp->flag.err || fp->flag.eof)
    return EOF;
  bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
  if (fp->base == NULL) /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0)
  {
    if (fp->cnt == -1)
      fp->flag.eof = 1;
    else
      fp->flag.err = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int main(void)
{
  FILE_ *file = fopen_("cat.c", "r");
  printf("%p\n", file);
  printf("fd: %d\n", file->fd);
  printf("%c\n", getc_(file));
}
