#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
    //nice(5);
    for(int i=0;i<1000000;++i){
        printf("%d-%d\n",i,getpid());
    }
    printf("Priority: %d\n", getpriority(PRIO_PROCESS,0));
    return 0;
}