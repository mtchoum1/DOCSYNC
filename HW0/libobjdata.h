#ifndef UNTITLED_LIBOBJDATA_H
#define UNTITLED_LIBOBJDATA_H

#include <stdlib.h>
#include <bfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dlfcn.h>
#include <stdint.h>

#endif

void print_section_info(bfd *abfd, asection *section, void *obj);

void convert_i_str(int number, char * buffer);

void vma_to_hex_str(bfd_vma value, char* buffer, int buffer_length);
