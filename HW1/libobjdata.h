#ifndef UNTITLED_LIBOBJDATA_H
#define UNTITLED_LIBOBJDATA_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#endif

void loopdir(char *pathname, char *fval, int lflag, char *str);

void checkfile(char *pathname,char *symname, char *fval, int lflag, char *str);
