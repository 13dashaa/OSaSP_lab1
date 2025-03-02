#include "dirwalk.h"


void add_path(PathList *path_list, const char *path) {
   if (path_list->count == path_list->capacity) {
       size_t new_capacity = path_list->capacity == 0 ? 16 : path_list->capacity * 2;
       char **new_items = realloc(path_list->items, new_capacity * sizeof(char *));
       if (!new_items) {
           perror("realloc");
           exit(EXIT_FAILURE);
       }
       path_list->items = new_items;
       path_list->capacity = new_capacity;
   }
   path_list->items[path_list->count] = strdup(path);
   if (!path_list->items[path_list->count]) {
       perror("strdup");
       exit(EXIT_FAILURE);
   }
   path_list->count++;
}

void free_list(PathList *pl) {
    for (size_t i = 0; i < pl->count; i++) {
        free(pl->items[i]);
    }
    free(pl->items);
}

int cmp_strcoll(const void *a, const void *b) {
    const char * const *pa = a;
    const char * const *pb = b;
    return strcoll(*pa, *pb);
}
int is_match(const char *path, const struct stat *sb, const Options *opts) {
   if (!(opts->l_only || opts->d_only || opts->f_only)) {
       return 1;
   }

   return ((opts->l_only && S_ISLNK(sb->st_mode)) ||
          (opts->d_only && S_ISDIR(sb->st_mode)) ||
          (opts->f_only && S_ISREG(sb->st_mode)));
}