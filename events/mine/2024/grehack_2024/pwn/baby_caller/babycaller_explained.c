#include <linux/module.h>       // Core header for loading LKMs into the kernel
#include <linux/kernel.h>       // Contains types, macros, functions for the kernel
#include <linux/init.h>         // Macros used to mark up functions e.g., __init, __exit
#include <linux/kprobes.h>      // Kernel probes for dynamic instrumentation
#include <linux/string.h>       // String handling functions

#define USER_DATA_LEN 0x20      // Define the length of user data to be copied (32 bytes)
#define SYSCALL_NB 0x15e        // Define the syscall number to intercept (350 in decimal)

/**
 * handle_babycaller - Handles the custom syscall interception.
 * @syscall_regs: Pointer to the syscall registers.
 *
 * This function retrieves data from user space and either calls a function
 * at a user-specified address with that data or prints the data using _printk.
 */
static int handle_babycaller(struct pt_regs *syscall_regs)
{
    // Buffer to store data copied from user space
    char data[USER_DATA_LEN];
    // Initialize the buffer to zero
    memset(data, 0, USER_DATA_LEN);

    // Copy data from user space pointed to by the 'si' register into 'data' buffer
    if (copy_from_user(data, (char *)syscall_regs->si, USER_DATA_LEN))
        return -EINVAL;  // Return error if copy fails

    // If the 'di' register is non-zero, treat it as a function pointer and call it
    if (syscall_regs->di)
    {
        unsigned long addr = syscall_regs->di;
        // Call the function at address 'addr' with 'data' as the argument
        ((void (*)(void *))addr)(data);
    }
    else
        // If 'di' is zero, print the data using '_printk'
        _printk(data);

    return 0;
}

/**
 * handler_pre - Pre-handler function for the kprobe.
 * @p: Pointer to the kprobe struct.
 * @regs: CPU registers at the time of the probe.
 *
 * This function is called before the probed function is executed.
 * It checks if the syscall number matches and handles it accordingly.
 */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    // Get the syscall registers from 'regs->di'
    struct pt_regs *syscall_regs = (struct pt_regs *)regs->di;
    // Check if the original syscall number matches 'SYSCALL_NB'
    if (syscall_regs->orig_ax == SYSCALL_NB)
        // Call 'handle_babycaller' to process the syscall
        return handle_babycaller(syscall_regs);

    return 0;  // Continue normal execution for other syscalls
}

// Define the kprobe structure
struct kprobe kp = {
    .symbol_name = "x64_sys_call",   // The symbol to probe (entry point for syscalls)
    .pre_handler = handler_pre       // The pre-handler function to call before the probed function
};

/**
 * babycaller_init - Module initialization function.
 *
 * This function registers the kprobe when the module is loaded.
 */
static int __init babycaller_init(void)
{
    // Register the kprobe
    int ret = register_kprobe(&kp);
    if (ret < 0)
    {
        // Log an error message if registration fails
        _printk(KERN_ERR "Failed to register kprobe: %d\n", ret);
        return ret;  // Return the error code
    }
    // Log an informational message if registration succeeds
    _printk(KERN_INFO "kprobe registered\n");
    return 0;  // Return success
}

/**
 * babycaller_exit - Module cleanup function.
 *
 * This function unregisters the kprobe when the module is unloaded.
 */
static void __exit babycaller_exit(void)
{
    // Unregister the kprobe
    unregister_kprobe(&kp);
    // Log an informational message
    _printk(KERN_INFO "kprobe unregistered\n");
}

// Specify the initialization and cleanup functions
module_init(babycaller_init);
module_exit(babycaller_exit);

MODULE_LICENSE("GPL");           // Module license
MODULE_AUTHOR("Ruulian");        // Module author
MODULE_DESCRIPTION("XXX");       // Module description
MODULE_VERSION("1.0");           // Module version
