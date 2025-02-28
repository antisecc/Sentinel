#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

#include "av_kernel.h"

#define TEST_EXECUTABLE "/tmp/test_exec"
#define TEST_VIRUS_EXECUTABLE "/tmp/test_virus_exec"

static int __init kernel_tests_init(void) {
    printk(KERN_INFO "Kernel tests module loaded.\n");

    // Create test executables
    struct file *file;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    // Create a clean test executable
    file = filp_open(TEST_EXECUTABLE, O_CREAT | O_WRONLY, 0755);
    if (IS_ERR(file)) {
        printk(KERN_ERR "Failed to create test executable: %ld\n", PTR_ERR(file));
        set_fs(old_fs);
        return -1;
    }
    vfs_write(file, "int main() { return 0; }", 24, &file->f_pos);
    filp_close(file, NULL);

    // Create a virus test executable
    file = filp_open(TEST_VIRUS_EXECUTABLE, O_CREAT | O_WRONLY, 0755);
    if (IS_ERR(file)) {
        printk(KERN_ERR "Failed to create virus executable: %ld\n", PTR_ERR(file));
        set_fs(old_fs);
        return -1;
    }
    vfs_write(file, "int main() { return 1; }", 24, &file->f_pos);
    filp_close(file, NULL);

    set_fs(old_fs);
    return 0;
}

static void __exit kernel_tests_exit(void) {
    printk(KERN_INFO "Kernel tests module unloaded.\n");

    // Clean up test executables
    filp_open(TEST_EXECUTABLE, O_RDWR, 0);
    filp_open(TEST_VIRUS_EXECUTABLE, O_RDWR, 0);
}

module_init(kernel_tests_init);
module_exit(kernel_tests_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel tests for antivirus system");
MODULE_VERSION("0.1");