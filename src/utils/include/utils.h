#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void log_event(const char *message);
void load_config(const char *config_file);
void handle_error(const char *error_message);

#endif // UTILS_H