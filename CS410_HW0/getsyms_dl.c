#include "libobjdata.h"

int main(int argc, char *argv[])
{
  void* lib_handle;
  bfd *abfd;

  lib_handle = dlopen("./libobjdata.so", RTLD_LAZY);
  if (!lib_handle) {
    dlerror();
    return 1;
  }

  struct local_file* (*printsym)(bfd *abfd);
  const char* error_msg;
  printsym = dlsym(lib_handle, "prints_sym");
  error_msg = dlerror();
  if (error_msg) {
    dlerror();
    dlclose(lib_handle);
    return 1;
  }

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

  struct local_file* a_file;
  a_file = (*printsym)(abfd);
  bfd_close(abfd);
  return 0;
}
