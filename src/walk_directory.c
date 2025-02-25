#define _POSIX_C_SOURCE 200809L
#include "dirwalk.h"
#include <limits.h> 
#include <linux/limits.h>
#include <string.h> 

char **walk_directory(const char *path, int show_links, int show_dirs, int show_files,int sort_entries, int *total_count) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char **entries = malloc(MAX_ENTRIES * sizeof(char *));
    if (entries == NULL) {
        perror("malloc");
        return NULL;
    }
    int count = 0;
    if (dir == NULL) {
        perror("opendir");
        free(entries);
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue; // Пропускаем скрытые файлы и каталоги
        }
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        struct stat statbuf;
        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            continue;
        }
        // Проверка на тип файла
        if ((show_links && S_ISLNK(statbuf.st_mode)) || 
            (show_dirs && S_ISDIR(statbuf.st_mode)) ||
            (show_files && S_ISREG(statbuf.st_mode)) ||
            (!show_links && !show_dirs && !show_files)) {
            if (count < MAX_ENTRIES) {
                entries[count] = strdup(fullpath); // Сохраняем полный путь
                if (entries[count] == NULL) {
                    perror("strdup");
                    // Освобождаем память при неудаче
                    for (int i = 0; i < count; i++) {
                        free(entries[i]);
                    }
                    free(entries);
                    closedir(dir);
                    return NULL;
                }
                count++;
            } else {
                fprintf(stderr, "Warning: Maximum entries exceeded\n");
            }
        }
        // Рекурсивный вызов для директорий
        if (S_ISDIR(statbuf.st_mode)) {
            int sub_count;
            char **sub_entries = walk_directory(fullpath, show_links, show_dirs, show_files, sort_entries,  &sub_count);
            for (int i = 0; i < sub_count; i++) {
                if (count < MAX_ENTRIES) {
                    entries[count] = sub_entries[i];
                    count++;
                }
            }
            free(sub_entries); // Освобождаем память для подкаталогов
        }
    }
    closedir(dir);
    *total_count = count; // Возвращаем общее количество записей
    if (sort_entries){
//	qsort(entries);
        qsort(entries, count, sizeof(char *), (int (*)(const void *, const void *))compare_entries);  
  }	
    return entries;
}