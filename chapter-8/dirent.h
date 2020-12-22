#define NAME_MAX 100
typedef struct
{
  long ino;
  char name[NAME_MAX + 1];
} Dirent_;

typedef struct
{
  int fd;
  Dirent_ d;
} DIR_;

DIR_ *opendir(char *dirname);
Dirent_ *readdir(DIR_ *dfd);
void closedir(DIR_ *dfd);
