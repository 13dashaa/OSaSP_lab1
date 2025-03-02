#include "dirwalk.h"

void walk_directory(const char *basepath, const Options *opts, PathList *plist) {
    DIR *dir = opendir(basepath);
    if (!dir) {
        fprintf(stderr, "Ошибка при открытии каталога '%s': %s\n", basepath, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", basepath, entry->d_name);

        struct stat sb;
        // Используем lstat, чтобы не следовать символическим ссылкам
        if (lstat(path, &sb) < 0) {
            fprintf(stderr, "Ошибка при lstat '%s': %s\n", path, strerror(errno));
            continue;
        }
        if (is_match(path, &sb, opts)) {
            add_path(plist, path);
        }
        if (S_ISDIR(sb.st_mode)) {
            walk_directory(path, opts, plist);
        }
    }
    closedir(dir);
}