#include "libobjdata.h"
  
int main(int argc, char *argv[]) 
{
  if (argc != 2)
  {
    printf("Write directory name");
    return 0;
  }

  loopdir(argv[1]);
  return 0; 
} 
