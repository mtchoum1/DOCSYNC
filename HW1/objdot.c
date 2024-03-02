#include "libobjdata.h"

void matchdot(char *filename,char *symname, int line_num, char *source, char *test) 
{
  int matrix[strlen(source)+1][2];
  matrix[strlen(source)][1] = -1;
  matrix[strlen(source)][0] = -1;
  for(int i = 0; i < strlen(source); i++)
  {
    if (source[i] != '.')
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
  while (matrix[node][(test[index]==source[sindex])] != -1 && index < strlen(test))
  {
    prevnode = node;
    node = matrix[node][test[index]==source[sindex]];
    if (prevnode + 1 == node)
    {
	sindex++; 
	index++;
    }
    else
    {
      sindex = 0;
      if (node == 0)
      {
	index++;
      }
    }
  }
  if (matrix[node][(test[index]==source[sindex])] == -1)
  {
    printf("%s %s %d %s\n",symname, filename, line_num, test);
  }
}
