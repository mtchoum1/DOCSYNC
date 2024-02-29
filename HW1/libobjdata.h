#ifndef UNTITLED_LIBOBJDATA_H
#define UNTITLED_LIBOBJDATA_H

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#endif

char *get_filetype(struct stat buf);

void loopdir(char *pathname);
