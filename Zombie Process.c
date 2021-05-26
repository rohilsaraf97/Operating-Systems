#include<stdio.h> 
#include<unistd.h> 
int main() 
{ 
pid_t pid = fork(); 
if(pid > 0) { 
printf("Parent sleeps for 10 sec\n"); 
sleep(10); } 
else { printf("Child\n"); } 
return 0; 
}

