#include "libobjdata.h"

void checkfile(char *filename, char *str)
{
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  char temp[512];
  int line_num = 1;
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("no file");
  }

  while ((read = getline(&line, &len, fp)) != -1)
  {
    while(fgets(temp, 512, fp) != NULL)
    {
      if((strstr(temp, str)) != NULL)
      {
	printf("%s %d %s\n",filename, line_num, temp);
      }
      line_num++;
    }
  }

  fclose(fp);
  if (line)
  {
    free(line);
  }
}
