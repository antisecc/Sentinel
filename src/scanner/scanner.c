#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "scanner.h"

int is_elf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;

    unsigned char e_ident[EI_NIDENT];
    fread(e_ident, sizeof(unsigned char), EI_NIDENT, file);
    fclose(file);

    return e_ident[0] == 0x7f && e_ident[1] == 'E' && e_ident[2] == 'L' && e_ident[3] == 'F';
}

void scan_directory(const char *dir_path) {
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir = opendir(dir_path);

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (stat(full_path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                scan_directory(full_path); // Recursively scan subdirectories
            }
        } else if (S_ISREG(statbuf.st_mode) && is_elf(full_path)) {
            // Check the file against known virus signatures
            if (check_signature(full_path)) {
                printf("Virus detected in file: %s\n", full_path);
            } else {
                printf("File is clean: %s\n", full_path);
            }
        }
    }

    closedir(dir);
}

// Main scanning function
void scan_filesystem(const char *root_path) {
    scan_directory(root_path);
}