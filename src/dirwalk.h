#ifndef DIRWALK_H
#define DIRWALK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_ENTRIES 1024

char **walk_directory(const char *path, int show_links, int show_dirs, int show_files,int sort_entries, int *total_count);
int compare_entries(const void *a, const void *b);
void print_entries(char **entries, int count);

#endif