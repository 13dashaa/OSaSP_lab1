#include "dirwalk.h"


int compare_entries(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
