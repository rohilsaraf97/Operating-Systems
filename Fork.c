#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main(){
    int pid;
    pid = fork();
    if( pid == 0){
        sleep(50);
        printf(" child process --> pid = %d and ppid = %d\n",getpid(),getppid());
    }
    else{
        sleep(50);
        printf("\n parent process --> pid = %d",getpid());
    }
}
