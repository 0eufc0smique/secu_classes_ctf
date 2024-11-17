#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>
#include <linux/string.h>

#define USER_DATA_LEN 0x20
#define SYSCALL_NB 0x15e

static int handle_babycaller(struct pt_regs *syscall_regs)
{
    // Get parameter
    char data[USER_DATA_LEN];
    memset(data, 0, USER_DATA_LEN);

    if (copy_from_user(data, (char *)syscall_regs->si, USER_DATA_LEN))
        return -EINVAL;

    // Finally call
    if (syscall_regs->di)
    {
        unsigned long addr = syscall_regs->di; 
        ((void (*)(void *))addr)(data);
    }
    else
        _printk(data);

    return 0;
}

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    struct pt_regs *syscall_regs = (struct pt_regs *)regs->di;
    if (syscall_regs->orig_ax == SYSCALL_NB)
        return handle_babycaller(syscall_regs);

    return 0;
}

struct kprobe kp = {
    .symbol_name = "x64_sys_call",
    .pre_handler = handler_pre
};

static int __init babycaller_init(void)
{
    int ret = register_kprobe(&kp);
    if (ret < 0)
    {
        _printk(KERN_ERR "Failed to register kprobe: %d\n", ret);
        return ret;
    }
    _printk(KERN_INFO "kprobe registered\n");
    return 0;
}

static void __exit babycaller_exit(void)
{
    unregister_kprobe(&kp);
    _printk(KERN_INFO "kprobe unregistered\n");
}

module_init(babycaller_init);
module_exit(babycaller_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ruulian");
MODULE_DESCRIPTION("XXX");
MODULE_VERSION("1.0");

