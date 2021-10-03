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
        if(i==50){
            sleep(50);
        }
    }
    pthread_exit("Child thread");
}

int main(){
    pthread_t threadA ;
    void* thr_result;
    pid_t pid = getpid();
    int res = pthread_create(&threadA,NULL,thr_1,NULL);
    for(int i=0;i<100;++i){
        if(i==30){
            sleep(15);
        }
        sleep(2);
        printf("%d-%d\n",pid,i);
    }
    int status = pthread_join(threadA, (void**)&thr_result);
    exit(0);
}