#include <stdio.h> 
#include <dirent.h>
#include <sys/stat.h>
  
int main(void) 
{ 
  struct dirent *de;   
  DIR *dr = opendir(".");
  struct stat buf;
  char *ptr;
  
  if (dr == NULL) 
  {
    printf("Could not open current directory" );
    return 0; 
  }
  
  while ((de = readdir(dr)) != NULL)
  {
    stat(de->d_name, &buf);
    if (S_ISREG(buf.st_mode))
      ptr = "regular";
    else if (S_ISDIR(buf.st_mode))
      ptr = "directory";
    else if (S_ISCHR(buf.st_mode))
      ptr = "character special";
    else if (S_ISBLK(buf.st_mode))
      ptr = "block special";
    else if (S_ISFIFO(buf.st_mode))
      ptr = "fifo";
    else if (S_ISLNK(buf.st_mode))
      ptr = "symbolic link";
    else if (S_ISSOCK(buf.st_mode))
      ptr = "socket";
    else
      ptr = "** unknown mode **";
    printf("%s\n", de->d_name);
    printf("%s\n", ptr);
  }
  
  closedir(dr);     
  return 0; 
} 
