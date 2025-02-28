#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/fanotify.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "av_kernel.h"

#define FAN_EVENT_FLAGS (FAN_OPEN | FAN_CLOSE_WRITE | FAN_MODIFY)

static struct fanotify_group *fan_group;

static void handle_event(struct fanotify_event_metadata *metadata) {
    struct file *file;
    char *filename;
    char *path;
    
    // Get the file associated with the event
    file = fget(metadata->fd);
    if (!file) {
        return;
    }

    // Allocate memory for the filename
    filename = kmalloc(PATH_MAX, GFP_KERNEL);
    if (!filename) {
        fput(file);
        return;
    }

    // Get the path of the file
    path = dentry_path_raw(file->f_path.dentry, filename, PATH_MAX);
    if (IS_ERR(path)) {
        kfree(filename);
        fput(file);
        return;
    }

    // Check if the file is an executable
    if (S_ISREG(file_inode(file)->i_mode) && (file_inode(file)->i_mode & S_IXUSR)) {
        // Scan the file for viruses
        if (scan_file(path)) {
            printk(KERN_ALERT "Virus detected in file: %s\n", path);
            // Handle the virus detection (e.g., alert user, quarantine file)
        }
    }

    // Clean up
    kfree(filename);
    fput(file);
}

static int fanotify_callback(struct fanotify_event_metadata *metadata) {
    if (metadata->mask & FAN_Q_OVERFLOW) {
        printk(KERN_WARNING "Fanotify queue overflow\n");
        return 0;
    }

    handle_event(metadata);
    return 0;
}

static int __init file_monitor_init(void) {
    fan_group = fanotify_init(FAN_CLASS_CONTENT | FAN_NONBLOCK, O_RDONLY);
    if (IS_ERR(fan_group)) {
        printk(KERN_ERR "Failed to initialize fanotify\n");
        return PTR_ERR(fan_group);
    }

    if (fanotify_mark(fan_group, FAN_MARK_FLUSH, FAN_EVENT_FLAGS, AT_FDCWD, NULL) < 0) {
        printk(KERN_ERR "Failed to mark fanotify group\n");
        fanotify_destroy(fan_group);
        return -1;
    }

    printk(KERN_INFO "File monitor initialized\n");
    return 0;
}

static void __exit file_monitor_exit(void) {
    fanotify_destroy(fan_group);
    printk(KERN_INFO "File monitor exited\n");
}

module_init(file_monitor_init);
module_exit(file_monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Linux Antivirus File Monitor using Fanotify");