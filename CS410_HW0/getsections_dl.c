#include "libobjdata.h"
#include <dlfcn.h>

int main(int argc, char *argv[])
{
  void* lib_handle;       

  lib_handle = dlopen("libobjdata.so", RTLD_LAZY);
  struct local_file* (*printsect)(bfd *abfd, asection *section, void *obj);
  const char* error_msg;
  printsect = dlsym(lib_handle, "print_section_info");
  error_msg = dlerror();
  bfd *abfd;
  bfd_init();
  if (argc != 2)
  {
    bfd_perror("Error No Argument");
    return 1;
  }

  abfd = bfd_openr(argv[1], NULL);
  if (!bfd_check_format(abfd, bfd_object))
  {
    bfd_perror("Unrecognized file format");
    return 1;
  }
  bfd_map_over_sections(abfd, (printsect), NULL);
  bfd_close(abfd);
  dlclose(lib_handle);
  return 0;
}
