#include <linux/kernel.h>
#include <linux/syscalls.h>

/*
 * Definition for onedcopy system call
 */
SYSCALL_DEFINE4(twodcopy, float *, src, float *, dest, int, m, int, n)
{
    /* Allocate a buffer of size len to hold the elements of array */
    float buffer[15];

    /* Copy from user copies the data from src to buffer of size len */
    if (__copy_from_user(buffer, src, sizeof(float) * (m) * (n)))
        return -EFAULT;
    else
        printk(KERN_INFO "Invoked __copy_from_user successfully");

    /* Copy to user copies the data from buffer to dest of size len */
    if (__copy_to_user(dest, buffer, sizeof(float) * (m) * (n)))
        return -EFAULT;
    else
        printk(KERN_INFO "Invoked __copt_to_user successfully");

    return 0;
}
