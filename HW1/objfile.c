#include "libobjdata.h"

char *get_filetype(struct stat buf)
{
  char *temp;
  if (S_ISREG(buf.st_mode))
    temp = "regular";
  else if (S_ISDIR(buf.st_mode))
    temp = "directory";
  else if (S_ISCHR(buf.st_mode))
    temp = "character special";
  else if (S_ISBLK(buf.st_mode))
    temp = "block special";
  else if (S_ISFIFO(buf.st_mode))
    temp = "fifo";
  else if (S_ISLNK(buf.st_mode))
    temp = "symbolic link";
  else if (S_ISSOCK(buf.st_mode))
    temp = "socket";
  else
    temp = "** unknown mode **";

  return temp;
}
