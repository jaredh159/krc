#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
// #include "syscalls.h" ¯\_(ツ)_/¯
#include <fcntl.h>
#include "dirent.h"

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char *argv[])
{
  if (argc == 1)
    fsize(".");
  else
    while (--argc > 0)
      fsize(*++argv);
  return 0;
}

void print_dirent(char *name, struct stat file)
{
  printf("<%s>\n", name);
  printf("  --> size in bytes: %llu\n", file.st_size);
  printf("  --> mode: %o\n", file.st_mode);
  printf("  --> owner id: %i\n", file.st_uid);
  printf("  --> group id: %i\n", file.st_gid);
  printf("  --> created: %lu\n", file.st_ctime);
  printf("  --> last modified: %lu\n", file.st_mtime);
  printf("  --> last accessed: %lu\n", file.st_atime);
  printf("  --> number of links: %i\n", file.st_nlink);
  printf("  --> inode number: %llu\n", file.st_ino);
  printf("  --> device of inode: %i\n", file.st_dev);

  puts("");
}

void fsize(char *name)
{
  struct stat stbuf;
  if (stat(name, &stbuf) == -1)
  {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);
  print_dirent(name, stbuf);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
  char name[MAX_PATH];
  Dirent_ *dp;
  DIR_ *dfd;
  if ((dfd = opendir(dir)) == NULL)
  {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL)
  {
    if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
      continue; /* skip self and parent */
    if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: name %s %s too long\n",
              dir, dp->name);
    else
    {
      sprintf(name, "%s/%s", dir, dp->name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}
