#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_SIGNATURE_LENGTH 256
#define MAX_SIGNATURES 1024

char signatures[MAX_SIGNATURES][MAX_SIGNATURE_LENGTH];
int signature_count = 0;

void generate_signature(const char *file_path) {
    // Placeholder for actual signature generation logic
    // For demonstration, we will just use the file name as the signature
    char signature[MAX_SIGNATURE_LENGTH];
    snprintf(signature, sizeof(signature), "%s", file_path);
    
    if (signature_count < MAX_SIGNATURES) {
        strncpy(signatures[signature_count], signature, MAX_SIGNATURE_LENGTH);
        signature_count++;
        printf("Generated signature: %s\n", signature);
    } else {
        printf("Signature limit reached. Cannot generate more signatures.\n");
    }
}

void scan_directory(const char *dir_path) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dp = opendir(dir_path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { // Regular file
            char file_path[PATH_MAX];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
            if (stat(file_path, &file_stat) == 0) {
                if (file_stat.st_mode & S_IXUSR) { // Check if executable
                    generate_signature(file_path);
                }
            }
        } else if (entry->d_type == DT_DIR) { // Directory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char sub_dir_path[PATH_MAX];
                snprintf(sub_dir_path, sizeof(sub_dir_path), "%s/%s", dir_path, entry->d_name);
                scan_directory(sub_dir_path);
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_to_scan>\n", argv[0]);
        return EXIT_FAILURE;
    }

    scan_directory(argv[1]);
    printf("Total signatures generated: %d\n", signature_count);
    return EXIT_SUCCESS;
}