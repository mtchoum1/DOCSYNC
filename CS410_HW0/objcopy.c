#include <stdlib.h>
#include <bfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libobjdata.h"

void copy_sect(bfd *abfd, const char *filename)
{
  int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd == -1)
  {
    perror("open");
    return;
  }

  asection *section = bfd_get_section_by_name(abfd, ".text");
  if (!section)
  {
    perror( "Section '.text' not found.\n");
    close(fd);
    return;
  }

  bfd_byte *contents = (bfd_byte *)malloc(section->size);
  if (!contents)
  {
    perror("Memory allocation error.\n");
    close(fd);
    return;
  }

  bfd_get_section_contents(abfd, section, contents, section -> vma, section -> size);
  write(fd, contents, section -> size);

  close(fd);
  free(contents);
}

int main(int argc, char *argv[])
{
  bfd *abfd;
  bfd_init();
  if (argc != 3)
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
