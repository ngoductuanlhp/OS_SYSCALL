#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "get_proc_info.h"
#define SIZE 200

int main(int argc, char* argv[]) {
    int pid = atoi(argv[1]);
    long sys_return_value;
    struct procinfos info;
    sys_return_value = get_proc_info(pid, &info);
    printf("Result: %ld\nStudent ID: %lu\n", sys_return_value, info.student_ID);
    printf("PID: %d\tName: %s\n", info.proc.pid, info.proc.name);
    printf("Parent PID: %d\tName: %s\n", info.parent_proc.pid, info.parent_proc.name);
    printf("Child PID: %d\tName: %s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
    return 0;
}
