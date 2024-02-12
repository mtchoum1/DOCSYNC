#include "libobjdata.h"
#include <dlfcn.h>


int main(int argc, char *argv[])
{
  void* lib_handle;
  lib_handle = dlopen("libobjdata.so", RTLD_LAZY);
  if (!lib_handle)
  {
    dlerror();
    return 1;
  }
  struct local_file *(*printsect)(bfd *abfd, asection *sect, void *obj);
  const char* error_msg;
  struct local_file* a_file;
  printsect = dlsym(lib_handle, "print_section_info");
  error_msg = dlerror();
  if (error_msg)
  {
    dlerror();
    return 1;
  }
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
  bfd_map_over_sections(abfd, printsect(abfd, section, NULL), NULL);
  bfd_close(abfd);
  dlclose(lib_handle);
  return 0;
}
