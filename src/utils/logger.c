#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

void log_event(const char *message) {
    FILE *log_file = fopen("antivirus.log", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline

    fprintf(log_file, "[%s] %s\n", timestamp, message);
    fclose(log_file);
}

void log_alert(const char *alert_message) {
    log_event(alert_message);
}