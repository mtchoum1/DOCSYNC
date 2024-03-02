#include "libobjdata.h"

void matchast(char *filename,char *symname, int line_num, char *source, char *test) 
{
    char arg[strlen(source)];
    int j = 0;
    for(int i = 0; i < strlen(source); i++)
    {
        if (source[i] != '*')
        {
            arg[j] = source[i];
            j++;
        }
    }
    int matrix[strlen(source)+1][2];
    matrix[strlen(source)][1] = -1;
    matrix[strlen(source)][0] = -1;
    for(int i = 0; i < strlen(source); i++)
    {
        if (source[i] != '*')
        {
            matrix[i][1] = i+1;
            if (i+2 < strlen(source))
            {
                matrix[i][0] = i+2;
            }
            else
            {
                matrix[i][0] = 0;
            }
        }
        else
        {
            matrix[i][1] = i;
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
        if (node % 2 == 0 && node != 0)
        {
             sindex++;
        }
        else if (node == 0)
        {
            sindex = 0;
            index++;
        }
    }

    if (index == strlen(test))
    {
        if (matrix[node][(test[index]==arg[sindex])] == strlen(source))
	{
	  printf("%s %s %d %s\n",symname, filename, line_num, test);
	}
    }
    else
    {
        if (matrix[node][(test[index]==arg[sindex])] == -1)
	{
	  printf("%s %s %d %s\n",symname, filename, line_num, test);
	}
    }
}
