
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/moduleparam.h>
#include <linux/sched.h>

static int pid;
module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "Process ID");


int init_module(void)
{
	struct task_struct *task;
	struct task_struct *child_task;
	struct list_head *list;


	printk(KERN_INFO "Hello world KERN ALERT LEVEL.\n");
	printk(KERN_INFO "pid:%d", pid);


    for_each_process(task){ 
    	int parentID = -1;
    	if (task->parent != NULL ) 
    		parentID = task->parent->pid;
        printk(KERN_INFO "PID %d: %s (Parent:%d) \n",  task->pid, task->comm, parentID);
        
        list_for_each(list, &task->children) {
			child_task = list_entry(list, struct task_struct, sibling);
			printk(KERN_INFO "--->[%d]%s\n",  child_task->pid, child_task->comm);	
		}

    }
    

	return 0;
}

void cleanup_module(void)
{
	printk( KERN_INFO "It's over man\n" );
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wali");

