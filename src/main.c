#include "dirwalk.h"

int main(int argc, char *argv[]) {
    // Установка локали для корректной сортировки
    setlocale(LC_COLLATE, "");

    Options opts = {0, 0, 0, 0};

    int opt;
    // Используем POSIX getopt. Допускаем объединённые опции: -ld, -s и т.п.
    opterr = 0; // отключаем стандартное сообщение об ошибке getopt
    while ((opt = getopt(argc, argv, "ldfs")) != -1) {
        switch(opt) {
            case 'l':
                opts.l_only = 1;
                break;
            case 'd':
                opts.d_only = 1;
                break;
            case 'f':
                opts.f_only = 1;
                break;
            case 's':
                opts.sort = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [options] [dir]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Определяем начальный каталог: если остался аргумент, берем его, иначе "./"
    char *start_dir = ".";
    if (optind < argc) {
        start_dir = argv[optind];
    }

    PathList plist = {0};
    plist.items = NULL;
    plist.count = 0;
    plist.capacity = 0;

    // Если начальный каталог удовлетворяет фильтру, добавить его в список
    struct stat sb;
    if (lstat(start_dir, &sb) < 0) {
        fprintf(stderr, "Error lstat '%s': %s\n", start_dir, strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (is_match(start_dir, &sb, &opts)) {
        add_path(&plist, start_dir);
    }

    // Если начальный каталог является каталогом, заходим рекурсивно
    if (S_ISDIR(sb.st_mode)) {
        walk_directory(start_dir, &opts, &plist);
    }

    if (opts.sort) {
        qsort(plist.items, plist.count, sizeof(char *), cmp_strcoll);
    }

    for (size_t i = 0; i < plist.count; i++) {
        printf("%s\n", plist.items[i]);
    }

    free_list(&plist);

    return 0;
}