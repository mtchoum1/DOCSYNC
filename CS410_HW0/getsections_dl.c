#include "libobjdata.h"
#include <dlfcn.h>

int main(int argc, char *argv[])
{
  void* lib_handle;
  bfd *abfd;

  lib_handle = dlopen("./libobjdata.so", RTLD_LAZY);
  if (!lib_handle) {
    dlerror();
    return 1;
  }

  struct local_file* (*printsect)(bfd *abfd, asection *section, void *obj);
  const char* error_msg;
  printsect = dlsym(lib_handle, "print_section_info");
  error_msg = dlerror();
  if (error_msg) {
    dlerror();
    dlclose(lib_handle);
    return 1;
  }

  bfd_init();
  if (argc != 2)
  {
    dlclose(lib_handle);
    return 1;
  }

  abfd = bfd_openr(argv[1], NULL);
  if (!abfd) {
    bfd_errmsg(bfd_get_error());
    dlclose(lib_handle);
    return 1;
  }

  if (!bfd_check_format(abfd, bfd_object))
  {
    bfd_errmsg(bfd_get_error());
    bfd_close(abfd);
    dlclose(lib_handle);
    return 1;
  }

  bfd_map_over_sections(abfd, (void (*)(bfd *, asection *, void *))printsect, NULL);
  bfd_close(abfd);
  dlclose(lib_handle);
  return 0;
}
