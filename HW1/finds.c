#include "libobjdata.h"
  
int main(int argc, char *argv[]) 
{
  char *pathname = NULL;
  char *fval = NULL;
  int lflag = 0;
  char *str = NULL;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "p:f:ls:")) != -1)
  {
    switch (c)
    {
    case 'p':
      pathname = optarg;
      break;
    case 'f':
      fval = optarg;
      break;
    case 'l':
      lflag = 1;
      break;
    case 's':
      str = optarg;
      break;
    case '?':
      if (optopt == 'p')
	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      if (optopt == 'f')
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      if (optopt == 's')
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
	fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort ();
    }
  }

  loopdir(pathname, fval, lflag, str);
  return 0; 
} 
