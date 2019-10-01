#include <get_proc_info.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argv[1] == NULL)
        return 0;
    pid_t mypid = atoi(argv[1]);
    printf("PID: %d\n", mypid);
    struct procinfos info;
    if(get_proc_info(mypid, &info) == 0) {
        printf("Student ID: %lu\n", info.student_ID);
        printf("PID: %d\tName: %s\n", info.proc.pid, info.proc.name);
        printf("Parent PID: %d\tName: %s\n", info.parent_proc.pid, info.parent_proc.name);
        printf("Child PID: %d\tName: %s\n", info.oldest_child_proc.pid, info.oldest_child_proc.name);
        return 1;
    }
    return 0;
}
