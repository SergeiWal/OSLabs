#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>
#include <errno.h>
#include <sys/wait.h>

//ps ax --sort -pid -o pid,ni,cmd

void mFun(int count, char const* name, pid_t pid, int niceValue){
    nice(niceValue);
    for(int i=0;i<count;++i){
        sleep(1);
        nice(5);
       // printf("i: %d name: %s pid:%d priority: %d\n",i,name, pid, getpriority(PRIO_PROCESS,0));
    }
}

int main(){
    pid_t pid;
    switch(pid = fork()){
        case -1:
        perror("error for create child process");exit(-1);
        case 0:
            printf("success create process child");
            printf("identifier of child process: %d", pid);
            mFun(10000, "child",pid,-10);
            exit(0);
        break;
        default:
            printf("main process");
            printf("identifier of main process: %d", getpid());
            mFun(10000, "main",getpid(),0);
            wait(NULL);
    }
    return 0;
}