#include "libobjdata.h"

int main(int argc, char *argv[])
{
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
  copy_sect(abfd, argv[2]);
  bfd_close(abfd);
  return 0;
}
