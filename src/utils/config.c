#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define CONFIG_FILE_PATH "config/av.conf"

static char *config_data = NULL;

int load_config() {
    FILE *file = fopen(CONFIG_FILE_PATH, "r");
    if (!file) {
        perror("Failed to open config file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    config_data = malloc(length + 1);
    if (!config_data) {
        perror("Failed to allocate memory for config data");
        fclose(file);
        return -1;
    }

    fread(config_data, 1, length, file);
    config_data[length] = '\0';

    fclose(file);
    return 0;
}

const char *get_config_value(const char *key) {
    if (!config_data) {
        return NULL;
    }

    char *line = strtok(config_data, "\n");
    while (line) {
        char *equal_sign = strchr(line, '=');
        if (equal_sign) {
            *equal_sign = '\0';
            if (strcmp(line, key) == 0) {
                return equal_sign + 1;
            }
        }
        line = strtok(NULL, "\n");
    }
    return NULL;
}

void free_config() {
    free(config_data);
}