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

void print_section_info(bfd *abfd, asection *section, void *obj)
{
  const char* name = section -> name;
  bfd_vma vma = section -> vma;
  bfd_size_type size = section -> size;
  file_ptr pos = section -> filepos;
  char posbuff[100];
  char vmabuff[100];
  char sizebuff[100];
  convert_i_str(pos, posbuff);
  convert_i_str(vma, vmabuff);
  convert_i_str(size, sizebuff);
  write(1, name, strlen(name));
  write(1, "\n", strlen("\n"));
  write(1, vmabuff, strlen(vmabuff));
  write(1, "\n", strlen("\n"));
  write(1, sizebuff, strlen(sizebuff));
  write(1, "\n", strlen("\n"));
  write(1, posbuff, strlen(posbuff));
  write(1, "\n", strlen("\n"));
}
