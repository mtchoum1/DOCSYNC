#include "libobjdata.h"
#include <dlfcn.h>
#include <stdint.h>
#define RDTSC(var)
{
  uint64_t var_lo, var_hi;
  asm volatile("lfence\n\trdtsc" : "=a"(var_lo), "=d"(var_hi));
  var = (((uint64_t)var_hi) | (((uint64_t)var_lo) << 32));
}

unsigned long long start, finish;

int main(int argc, char *argv[])
{
  void* lib_handle;
  bfd *abfd;
  RDTSC(start);
  if (argc != 3)
  {
    return 1;
  }

  lib_handle = dlopen("./libobjdata.so",  atoi(argv[2]));
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
  RDTSC(finish);
  return 0;
}
