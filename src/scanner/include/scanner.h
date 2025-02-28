#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>

#define MAX_SIGNATURES 1024
#define MAX_PATH_LENGTH 4096

typedef struct {
    char signature[64];
    char description[256];
} VirusSignature;

typedef struct {
    VirusSignature signatures[MAX_SIGNATURES];
    size_t count;
} SignatureDatabase;

void initialize_signature_database(SignatureDatabase *db);
int load_signatures(SignatureDatabase *db, const char *file_path);
int scan_file(const char *file_path, SignatureDatabase *db);
void cleanup_signature_database(SignatureDatabase *db);

#endif // SCANNER_H