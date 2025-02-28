#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "avd.h"

void print_usage() {
    printf("Usage: av_control [options]\n");
    printf("Options:\n");
    printf("  -s, --start       Start the antivirus daemon\n");
    printf("  -k, --stop        Stop the antivirus daemon\n");
    printf("  -r, --scan        Perform a manual scan\n");
    printf("  -h, --help        Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    static struct option long_options[] = {
        {"start", no_argument, 0, 's'},
        {"stop", no_argument, 0, 'k'},
        {"scan", no_argument, 0, 'r'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "s:k:r:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 's':
                start_daemon();
                break;
            case 'k':
                stop_daemon();
                break;
            case 'r':
                manual_scan();
                break;
            case 'h':
                print_usage();
                exit(0);
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if (optind == 1) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    return 0;
}