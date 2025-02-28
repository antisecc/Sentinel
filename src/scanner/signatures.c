#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

#define MAX_SIGNATURES 1024
#define SIGNATURE_LENGTH 64

static char *signatures[MAX_SIGNATURES];
static int signature_count = 0;

int load_signatures(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open signature file");
        return -1;
    }

    char line[SIGNATURE_LENGTH];
    while (fgets(line, sizeof(line), file) && signature_count < MAX_SIGNATURES) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        signatures[signature_count] = strdup(line);
        if (!signatures[signature_count]) {
            perror("Failed to allocate memory for signature");
            fclose(file);
            return -1;
        }
        signature_count++;
    }

    fclose(file);
    return 0;
}

int match_signature(const char *file_hash) {
    for (int i = 0; i < signature_count; i++) {
        if (strcmp(signatures[i], file_hash) == 0) {
            return 1; // Match found
        }
    }
    return 0; // No match
}

void free_signatures() {
    for (int i = 0; i < signature_count; i++) {
        free(signatures[i]);
    }
    signature_count = 0;
}