#include "dirwalk.h"
int main(int argc, char *argv[]) {
    int opt;
    int show_links = 0, show_dirs = 0, show_files = 0, sort_entries = 0;
    char *dir = "."; // По умолчанию текущий каталог
    while ((opt = getopt(argc, argv, "ldfs")) != -1) {
        switch (opt) {
            case 'l':
                show_links = 1;
                break;
            case 'd':
                show_dirs = 1;
                break;
            case 'f':
                show_files = 1;
                break;
            case 's':
                sort_entries = 1;
                break;
	    default:
                fprintf(stderr, "Usage: %s [-l] [-d] [-f] [dir]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (optind < argc) {
        dir = argv[optind]; // Устанавливаем каталог, если он указан
    }
    int total_count = 0;
    char **entries = walk_directory(dir, show_links, show_dirs, show_files, sort_entries, &total_count);
    if (entries != NULL) {
        print_entries(entries, total_count);
    }
    return 0;
}
