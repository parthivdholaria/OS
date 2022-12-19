#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched/signal.h>
#include<linux/stat.h>
#include<linux/moduleparam.h>

char buffer[512]


MODULE_LICENSE("GPL")
MODULE_AUTHOR("PARTHIV")
MODULE_DESCRIPTION("OS ASSIGNMENT 3 Q3")



static char * command= "ls";

module_param(command,char *,0000);
MODULE_PARM_DESC(command,"command line arguments");



static int _init read_struct(){

	pr_info("command line given is:",command);


	return 0;
}



static void _exit task_struct_exit(void){
	pr_info("%s Exiting\n","GoodBye");
}



module_init(read_struct);
module_exit(task_struct_exit);
