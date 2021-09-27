#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void process(int k, char* s){
    for(int i=0;i<k;i++){
        sleep(1);
        printf("%s: %d-%d\n\n", s, getpid(), i);
    }
}

int main(){
    pid_t pid;
    switch (pid = fork())
    {
    case -1: perror("fork error");exit(-1);
    case 0: process(50, "Lab3Lin_2_1"); exit(0);
    default:
        process(100, "Lab3Lin_2");wait(NULL);
        break;
    }
    exit(0);
}