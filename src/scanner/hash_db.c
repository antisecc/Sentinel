#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

#define HASH_DB_FILE "hash_db.txt"
#define MAX_HASH_LENGTH 64

static char **hash_db = NULL;
static size_t hash_count = 0;

static void load_hashes() {
    FILE *file = fopen(HASH_DB_FILE, "r");
    if (!file) {
        perror("Failed to open hash database");
        return;
    }

    char line[MAX_HASH_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        hash_db = realloc(hash_db, sizeof(char *) * (hash_count + 1));
        hash_db[hash_count] = strdup(line);
        hash_count++;
    }
    fclose(file);
}

static void save_hash(const char *hash) {
    FILE *file = fopen(HASH_DB_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", hash);
        fclose(file);
    } else {
        perror("Failed to open hash database for writing");
    }
}

int check_hash(const char *hash) {
    for (size_t i = 0; i < hash_count; i++) {
        if (strcmp(hash_db[i], hash) == 0) {
            return 1; // Hash found
        }
    }
    return 0; // Hash not found
}

void add_hash(const char *hash) {
    if (!check_hash(hash)) {
        save_hash(hash);
        hash_db = realloc(hash_db, sizeof(char *) * (hash_count + 1));
        hash_db[hash_count] = strdup(hash);
        hash_count++;
    }
}

void free_hash_db() {
    for (size_t i = 0; i < hash_count; i++) {
        free(hash_db[i]);
    }
    free(hash_db);
    hash_db = NULL;
    hash_count = 0;
}

void init_hash_db() {
    load_hashes();
}