#include<stdio.h> 
#include<unistd.h> 
int main() { 
pid_t pid = fork(); 
if(pid > 0) { 
printf("Parent\n"); } 
else { 
sleep(10); 
printf("Child sleeps for 10 sec\n"); 
} 
return 0;

