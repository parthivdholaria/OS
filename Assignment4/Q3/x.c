#include<linux/kernel.h>
#include<linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include<linux/stat.h>
#include<linux/moduleparam.h>
#include <asm/uaccess.h>
#include <linux/fs.h> 
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>
#include<linux/sched.h>
#include <linux/cred.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("PARTHIV");
MODULE_DESCRIPTION("OS ASSIGNMENT 3 Q3");

int p_id;
struct pid *struct_pid;
struct task_struct * task;
pid_t pgid;

int myint=4;

module_param(myint,int,0);


static int __init read_struct(void){

	struct_pid = find_get_pid(myint);
	task = pid_task(struct_pid,PIDTYPE_PID);
	printk(KERN_INFO "process id= %d\n",task->pid);
	printk(KERN_INFO "process user_id= %d\n",task->cred->uid.val);
	printk(KERN_INFO "process command path: %s\n",task->comm);
	printk(KERN_INFO "process group id is= %d\n",task->cred->gid.val);
	return 0;
}



static void __exit task_struct_exit(void){
	printk(KERN_INFO "%s Exiting\n","GoodBye");
}


//MODULE_LICENSE("GPL");
module_init(read_struct);
module_exit(task_struct_exit);
