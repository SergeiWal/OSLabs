#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* thr_1(void* arg){
    pid_t pid = getpid();
    for(int i=0;i<75;++i){
        sleep(1);
        printf("Child: %d-%d\n",getpid(),i);
    }
    pthread_exit("Child thread");
}

int main(){
    pthread_t threadA ;
    void* thr_result;
    pid_t pid = getpid();
    int res = pthread_create(&threadA,NULL,thr_1,NULL);
    for(int i=0;i<100;++i){
        sleep(2);
        printf("%d-%d\n",pid,i);
    }
    int status = pthread_join(threadA, (void**)&thr_result);
    exit(0);
}