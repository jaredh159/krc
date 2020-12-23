#include <stdlib.h>
#include <stdio.h>

typedef long Align;

union header
{
  struct
  {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
#define NALLOC 1024
#define MAX_ALLOWED_MEMORY 4096
static Header *morecore_(unsigned);
void free_(void *);

void *malloc_(unsigned nbytes)
{
  Header *p, *prevp;
  unsigned nunits;

  if (nbytes < 1 || nbytes > MAX_ALLOWED_MEMORY)
    return NULL;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL)
  {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
  {
    if (p->s.size >= nunits)
    {
      if (p->s.size == nunits) /* exactly */
        prevp->s.ptr = p->s.ptr;
      else
      { /* allocate tail end */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) /* wrapped around free list */
      if ((p = morecore_(nunits)) == NULL)
        return NULL;
  }
}

static Header *morecore_(unsigned nu)
{
  char *cp, *sbrk(int);
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;

  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1)
    return NULL;

  up = (Header *)cp;
  up->s.size = nu;
  free_((void *)(up + 1));
  return freep;
}

void free_(void *ap)
{
  Header *bp, *p;
  bp = (Header *)ap - 1; /* point to block header */

  if (bp->s.size < 1 || bp->s.size > MAX_ALLOWED_MEMORY)
  {
    printf("error, unexpected size for block to free: %d\n", bp->s.size);
    return;
  }

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; /* freed block at start or end of arena */
  if (bp + bp->s.size == p->s.ptr)
  {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  }
  else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp)
  {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  }
  else
    p->s.ptr = bp;
  freep = p;
}

void bfree_(void *ap, unsigned num_bytes)
{
  if (num_bytes <= (sizeof(Header) + sizeof(Header)))
    return;

  Header *p;
  p = (Header *)ap;
  p->s.size = num_bytes / sizeof(Header);
  printf("size is %lu, %d\n", sizeof(Header), p->s.size);
  p->s.ptr = NULL;
  free_(p + 1);
}

void *calloc_(unsigned int num_objects, unsigned int object_size)
{
  unsigned int num_bytes = num_objects * object_size;
  void *pointer = malloc_(num_bytes);
  if (pointer == NULL)
    return NULL;

  void *current = pointer;
  char *raw_pointer;
  int i;
  for (i = 0; i < num_bytes; i++)
  {
    raw_pointer = (char *)((long)current + (i * sizeof(char *)));
    *raw_pointer = 0;
  }
  return pointer;
}

static char *string = "0123456789012345678901234567890123456789";

int main(void)
{
  // char *s1 = malloc_(5);
  // *s1 = 'H';
  // free_(s1);
  // char *str = calloc_(5, sizeof(char *));
  // // char *str = malloc_(5);
  // printf("pointer is %p\n", str);
  // printf("char %d is %d, or %c\n", 0, (int)str[0], str[0]);
  // free_(str);
  bfree_(&string, 40);
  return 0;
}
