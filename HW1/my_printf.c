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
  int *arg = &str + 4;
    
  while (*str != '\0')
  {
    if (*str == '%') 
    {
        if (*str == '%' && *(str + 1) == 's') 
        {
          write(1, *arg, sizeof(*arg));
          arg += 2;
          str += 2; 
        } 
        else 
        {
	  char buf[sizeof(*arg)];
	  itoa(buf, *(str + 1), *arg);
	  write(1, buf, strlen(buf));
          arg += 2;
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
  my_printf("Hello, %s! Your age is %d and your score is %u. Hex value: %x\n", "John", 25, 100, 0xDEADBEEF);
  
  return 0;
}
