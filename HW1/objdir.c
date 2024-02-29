#include "libobjdata.h"

void loopdir(char *pathname, char *fval, int lflag, char *str)
{
  struct dirent *de;   
  DIR *dr = opendir(pathname);
  struct stat buf;
  char *ptr;
  
  if (dr == NULL) 
  {
    printf("Could not open current directory" ); 
  }
  
  while ((de = readdir(dr)) != NULL)
  {
    char full_name[256] = { 0 };
    snprintf(full_name, 100, "%s/%s", pathname, de->d_name);
    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
    {
      stat(full_name, &buf);
      if (S_ISDIR(buf.st_mode))
      {
	loopdir(full_name, fval, lflag, str);
      }
      else
      {
	if (fval != NULL && de->d_name[strlen(de->d_name)-1] == fval[strlen(fval)-1])
	{
	  checkfile(full_name,fval, lflag, str);
	}
	else if (fval == NULL)
	{
	  checkfile(full_name,fval, lflag, str);
	}
      }
    }
  }
  
  closedir(dr);
}
