#ifndef DIRWALK_H
#define DIRWALK_H

#define _XOPEN_SOURCE 700  // Для nftw или других POSIX функций (если потребуется)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <locale.h>


typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} PathList;

typedef struct {
    int l_only;
    int d_only;
    int f_only;
    int sort;
} Options;

void add_path(PathList *path_list, const char *path); 
void free_list(PathList *pl);
int cmp_strcoll(const void *a, const void *b);
int is_match(const char *path, const struct stat *sb, const Options *opts); 
void walk_directory(const char *basepath, const Options *opts, PathList *plist);
 

#endif