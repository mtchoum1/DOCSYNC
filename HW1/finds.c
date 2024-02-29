#include "libobjdata.h"
  
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
    ptr = get_filetype(buf);
    printf("%s\n", de->d_name);
    printf("%s\n", ptr);
  }
  
  closedir(dr);     
  return 0; 
} 
