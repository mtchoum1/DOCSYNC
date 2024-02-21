#include "libobjdata.h"

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

const char* const hex_digits = "0123456789abcdef";

void vma_to_hex_str(bfd_vma value, char* buffer, int buffer_length)
{
  for(int i = buffer_length - 1; i >= 0; --i)
  {
    buffer[i] = hex_digits[value % 16];
    value /= 16;
  }
}
void size_to_hex_str(bfd_size_type value, char* buffer, int buffer_length)
{
  for(int i = buffer_length - 1; i >= 0; --i)
  {
    buffer[i] = hex_digits[value % 16];
    value /= 16;
  }
}
void pos_to_hex_str(file_ptr value, char* buffer, int buffer_length)
{
  for(int i = buffer_length - 1; i >= 0; --i)
  {
    buffer[i] = hex_digits[value % 16];
    value /= 16;
  }
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
  pos_to_hex_str(pos, posbuff, 14);
  vma_to_hex_str(vma, vmabuff, 14);
  size_to_hex_str(size, sizebuff, 14);
  write(1, name, strlen(name));
  write(1, "\n", strlen("\n"));
  write(1, vmabuff, strlen(vmabuff));
  write(1, "\n", strlen("\n"));
  write(1, sizebuff, strlen(sizebuff));
  write(1, "\n", strlen("\n"));
  write(1, posbuff, strlen(posbuff));
  write(1, "\n", strlen("\n"));
}
