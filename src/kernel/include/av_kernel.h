#ifndef AV_KERNEL_H
#define AV_KERNEL_H

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/sched.h>

// Define the maximum length for file paths
#define MAX_PATH_LEN 4096

// Structure to hold information about scanned executables
struct scanned_file_info {
    char path[MAX_PATH_LEN];
    bool is_infected;
};

// Function prototypes
void monitor_new_executable(struct file *file);
void prevent_execution(struct task_struct *task);
int scan_executable(const char *path);
void load_signatures(void);
void unload_signatures(void);

#endif // AV_KERNEL_H