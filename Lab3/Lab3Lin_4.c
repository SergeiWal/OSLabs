#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("Parent process has started\n");

    /*
    printf("Child system process has started");
    system("./Lab3Lin_2b");
    printf("Child system process has finished");
    */

    printf("Child exec process has started\n");
    //char *argv[] = {"Lab3Lin_2b", "", 0};
    char *argv[] = {NULL};
    execv("./Lab3Lin_2b",argv);
    printf("Child exec process has finished\n");

    for(int i=0;i<100;++i){
        sleep(1);
        printf("%d-%d \n", getpid(),i);
    }
    exit(0);
}