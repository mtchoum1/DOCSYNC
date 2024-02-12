#include <stdio.h>
#include <stdlib.h>
#include <bfd.h>
#include <unistd.h>
#include <string.h>
void convert_i_str(int number, char * buffer)
{
 int n, index = 0, len = 0, tmp;
 tmp = number;
 while (number != 0)
 {
   number = number / 10;
   len++;
 }
 number = tmp;
 while(number != 0)
 {
   n = number % 10;
   buffer[len - index - 1] = n + '0';
   number = number / 10;
   index++;
 }
 buffer[index] = '\0';
}

void prints_sym(bfd *abfd)
{
  long size = bfd_get_symtab_upper_bound(abfd);

  asymbol **symtab = (asymbol **)malloc(size);

  long num_symbols = bfd_canonicalize_symtab(abfd, symtab);

  for (long i = 2; i < num_symbols; ++i)
  {
    const char* name = bfd_asymbol_name(symtab[i]);
    bfd_vma vma = bfd_asymbol_value(symtab[i]);
    char vmabuff[100];
    convert_i_str(vma, vmabuff);
    write(1, vmabuff, strlen(vmabuff));
    write(1, " ", strlen(" "));
    write(1, name, strlen(name));
    write(1, "\n", strlen("\n"));
  }

  free(symtab);
  bfd_close(abfd);
}
