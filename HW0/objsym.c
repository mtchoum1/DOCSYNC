#include "libobjdata.h"

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
    vma_to_hex_str(vma, vmabuff, 14);
    write(1, vmabuff, strlen(vmabuff));
    write(1, " ", strlen(" "));
    write(1, name, strlen(name));
    write(1, "\n", strlen("\n"));
  }

  free(symtab);
}
