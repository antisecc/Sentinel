#ifndef COMMON_H
#define COMMON_H

#include <linux/types.h>

#define MAX_PATH_LENGTH 4096
#define MAX_SIGNATURE_LENGTH 256
#define MAX_HASH_LENGTH 64

typedef struct {
    char path[MAX_PATH_LENGTH];
    uid_t owner_uid;
    gid_t owner_gid;
    size_t size;
    time_t creation_time;
} file_info_t;

typedef struct {
    char signature[MAX_SIGNATURE_LENGTH];
    char description[256];
} virus_signature_t;

typedef struct {
    char hash[MAX_HASH_LENGTH];
    file_info_t file_info;
} hash_entry_t;

#endif // COMMON_H