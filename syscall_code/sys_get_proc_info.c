#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info
#include <linux/sched/signal.h>
#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <asm/errno.h>

struct proc_info {
    pid_t pid;
    char name[16];
};

struct procinfos {
    long int student_ID;
    struct proc_info proc;
    struct proc_info parent_proc;
    struct proc_info oldest_child_proc;
};

SYSCALL_DEFINE2(get_proc_info,pid_t,pid,struct procinfos*,info) {
    info->student_ID = 1710364;
    struct task_struct *task_ptr;
    pid = (pid == -1) ? current->pid : pid;
    info->proc.pid = pid;
    for_each_process(task_ptr) {
        if(task_ptr->pid == pid) {
            strcpy(info->proc.name, task_ptr->comm);
            struct task_struct *parent = task_ptr->real_parent;
            if(parent != NULL) {
                info->parent_proc.pid = parent->pid;
                strcpy(info->parent_proc.name, parent->comm);
            }
            else {
                info->parent_proc.pid = -1;
                strcpy(info->parent_proc.name, "none");
            }
            struct task_struct *oldest_child = list_first_entry_or_null(&task_ptr->children, struct task_struct, sibling);
            if(oldest_child != NULL) {
                info->oldest_child_proc.pid = oldest_child->pid;
                strcpy(info->oldest_child_proc.name, oldest_child->comm);
            }
            else {
                info->oldest_child_proc.pid = -1;
                strcpy(info->oldest_child_proc.name, "none");
            }
            return 0;
        }
    }
    strcpy(info->proc.name, "none");
    info->parent_proc.pid = -1;
    strcpy(info->parent_proc.name, "none");
    info->oldest_child_proc.pid = -1;
    strcpy(info->oldest_child_proc.name, "none");
    return EINVAL;
}
