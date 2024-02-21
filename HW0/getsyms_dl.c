#include "libobjdata.h"

#define RDTSC(var) \
{ \
  uint32_t var##_lo, var##_hi; \
  asm volatile("lfence\n\trdtsc" : "=a"(var##_lo), "=d"(var##_hi)); \
  var = var##_hi; \
  var <<= 32; \
  var |= var##_lo; \
}
unsigned long long start, finish;

int main(int argc, char *argv[])
{
  int fd = open("stats", O_RDWR | O_CREAT | O_APPEND, 0666);
  void* lib_handle;
  bfd *abfd;
  long sumtime = 0;
  if (argc != 3)
  {
    return 1;
  }
  write(fd, "Time getsyms_dl with ", strlen("Time getsyms_dl with "));
  write(fd, argv[2], strlen(argv[2]));
  write(fd, "\n", strlen("\n"));
  for (int i = 0; i < 50; i++)
  {
    RDTSC(start);

    if (strcmp(argv[2], "RTLD_NOW") == 0)
    {
      lib_handle = dlopen("./libobjdata.so", RTLD_NOW);
    }
    else if (strcmp(argv[2], "RTLD_LAZY") == 0)
    {
      lib_handle = dlopen("./libobjdata.so", RTLD_LAZY);
    }
    if (!lib_handle)
    {
      dlerror();
      return 1;
    }

    struct local_file* (*printsym)(bfd *abfd);
    const char* error_msg;
    printsym = dlsym(lib_handle, "prints_sym");
    error_msg = dlerror();
    if (error_msg)
    {
      dlerror();
      dlclose(lib_handle);
      return 1;
    }
    bfd_init();

    abfd = bfd_openr(argv[1], NULL);
    if (!bfd_check_format(abfd, bfd_object))
    {
      bfd_perror("Unrecognized file format");
      return 1;
    }
 
    struct local_file* a_file;
    a_file = (*printsym)(abfd);
    bfd_close(abfd);
    RDTSC(finish);
    long time = (finish - start)/2400;
    sumtime += time;
    char timebuff[100];
    struct local_file* (*con_str)(int number, char * buffer);
    con_str = dlsym(lib_handle, "convert_i_str");
    struct local_file* c_file;
    c_file = (*con_str)(time, timebuff);
    write(fd, timebuff, strlen(timebuff));
    write(fd, "\n", strlen("\n"));
  }
  sumtime /= 50;
  char avgbuff[100];
  struct local_file* (*con_str)(int number, char * buffer);
  con_str = dlsym(lib_handle, "convert_i_str");
  struct local_file* b_file;
  b_file = (*con_str)(sumtime, avgbuff);
  write(fd, "Average: ", strlen("Average: "));
  write(fd, avgbuff, strlen(avgbuff));
  write(fd, "\n", strlen("\n"));
  dlclose(lib_handle);
  return 0;
}
