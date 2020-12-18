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

enum _flags
{
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020
};

typedef struct _iobuf
{
  int cnt;
  char *ptr;
  char *base;
  int flag;
  int fd;
} FILE_;

extern FILE_ _iob[OPEN_MAX];

FILE_ _iob[OPEN_MAX] = {{0, (char *)0, (char *)0, _READ, 0},
                        {0, (char *)0, (char *)0, _WRITE, 1},
                        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

#define stdin_ &_iob[0]
#define stdout_ &_iob[1]
#define stderr_ &_iob[2]

int _fillbuf(FILE_ *);
int _flushbuf(int, FILE_ *);

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE_ *fopen_(char *name, char *mode)
{
  int fd;
  FILE_ *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if ((fp->flag & (_READ | _WRITE)) == 0)
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
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/* _fillbuf: allocate and fill input buffer */ int _fillbuf(FILE_ *fp)
{
  int bufsize;
  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0)
  {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int main(void)
{
  FILE_ *file = fopen_("cat.c", "r");
  printf("fd: %d\n", file->fd);
}
