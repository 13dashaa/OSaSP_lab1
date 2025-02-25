#include "dirwalk.h"


void print_entries(char **entries, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i]);
        free(entries[i]); // Освобождаем память
    }
    free(entries); // Освобождаем память для массива
}