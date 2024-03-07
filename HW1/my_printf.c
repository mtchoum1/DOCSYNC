#include "libobjdata.h"

void itoa (char *buf, int base, int d)
{
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
     
  /* If %d is specified and D is minus, put `-' in the head. */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;
     
  /* Divide UD by DIVISOR until UD == 0. */
  do
    {
      int remainder = ud % divisor;
     
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);
     
  /* Terminate BUF. */
  *p = 0;
     
  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

void my_printf(char *str, ...)
{
    char *arg[5];
    register int *s __asm__( "esi" );
    arg[0] = s;
    register int *ss __asm__( "edx" );
    arg[1] = ss;
    register int *sss __asm__( "ecx" );
    arg[2] = sss;
    register int *ssss __asm__( "r8" );
    arg[3] = ssss;
    register int *sssss __asm__( "r9" );
    arg[4] = sssss;
    int i = 0;
  
    
  while (*str != '\0')
  {
    if (*str == '%') 
    {
        if (*(str + 1) == 's') 
        {
          write(1, arg[i], strlen(arg[i]));
          i++;
          str += 2; 
        }
        else if (*(str + 1) == 'c') 
        {
            char buf[1]; 
            buf[0] = arg[i];
          write(1, buf, 1);
            i++;
          str += 2; 
        }
        else 
        {
	  char buf[sizeof(arg[i])];
	  itoa(buf, *(str + 1), arg[i]);
	  write(1, buf, strlen(buf));
          i++;
          str += 2; 
        } 
    }
    else 
    {
      char buf[sizeof(*str)]; 
      buf[0] = *str;
      write(1, buf, sizeof(*str));
      str++;
    }
  }
}

int main()
{
  my_printf("Hello, %s! Your age is %d and your score is %u. Hex value: %x char: %c\n", "John", 25, 100, 0xDEADBEEF, 'h');
  
  return 0;
}
