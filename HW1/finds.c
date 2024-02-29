#include "libobjdata.h"
  
int main(int argc, char *argv[]) 
{
  if (argc != 2)
  {
    printf("Write directory name");
    return 0;
  }
  struct dirent *de;   
  DIR *dr = opendir(argv[1]);
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
