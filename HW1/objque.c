#include "libobjdata.h"

void matchque(char *filename,char *symname, int line_num, char *source, char *test)
{
  int j = 0;
  int arglen = 0;
  for(int i = 0; i < strlen(source); i++)
  {
    if (source[i] != '?')
    {
      arglen++;
    }
  }
  char arg[arglen];
  for(int i = 0; i < strlen(source); i++)
  {
    if (source[i] != '?')
    {
      arg[j] = source[i];
      j++;
    }
  }
  int matrix[arglen+1][2];
  matrix[arglen][1] = -1;
  matrix[arglen][0] = -1;
  for(int i = 0; i < arglen; i++)
  {
    if (i == arglen-1)
    {
      matrix[i][1] = i+1;
      matrix[i][0] = 0;
    }
    else
    {
      matrix[i][1] = i+1;
      matrix[i][0] = i+1;
    }
  }
  int prevnode = 0;
  int node = 0;
  int index = 0;
  int sindex = 0;
  while (matrix[node][(test[index]==arg[sindex])] != -1 && index < strlen(test))
  {
    prevnode = node;
    node = matrix[node][test[index]==arg[sindex]];
    index += (test[index]==arg[sindex]);
    if (node == 0)
    {
      sindex = 0;
      index++;
    }
    else
    {
      sindex++;
    }
  }
  
  if (matrix[node][(test[index]==source[sindex])] == -1)
  {
    printf("%s %s %d %s\n",symname, filename, line_num, test);
  }
}
