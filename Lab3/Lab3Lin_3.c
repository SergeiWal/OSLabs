#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    if(fork() == 0){
        system("./Lab3Lin_2b");
    }

    for(int i=0;i<100;++i){
        sleep(1);
        printf("%d: %d\n", getpid(), i);
    }
    exit(0);
}