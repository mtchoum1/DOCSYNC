#ifndef UNTITLED_LIBOBJDATA_H
#define UNTITLED_LIBOBJDATA_H

#include <stdlib.h>
#include <bfd.h>
#include <unistd.h>

#endif

void print_section_info(bfd *abfd, asection *section, void *obj);

void convert_i_str(int number, char * buffer);
