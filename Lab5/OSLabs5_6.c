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
    for(int i=0;i<1000000;++i){
        sleep(1);
        printf("%d-%d\n",i,getpid());
    }
    return 0;
}