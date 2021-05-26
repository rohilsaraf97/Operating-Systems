#include<stdio.h>

#include<stdlib.h>

int mutex = 1, readcount = 0, wrt = 1;
void reader();
void writer();
int wait(int s) {
  s--;
  return s;
}
int signal(int s) {
  s++;
  return s;
}
void reader() {
  int n;
  mutex = wait(mutex);
  readcount++;
  if (readcount == 1)
    wrt = wait(wrt);
  mutex = signal(mutex);
  printf("\nProcess %d is READING..\n", readcount);
  xy:
    printf("\n1. for reading\n2. for writing\n3. exit reading");
  printf("\n\nchoice:");
  scanf("%d", & n);
  switch (n) {
  case 1:
    reader();
    goto xy;
    break;
  case 2:
    writer();
    goto xy;
    break;
  case 3:
    break;
  }
  printf("\nProcess %d is DONE READING..\n", readcount);
  mutex = wait(mutex);
  readcount--;
  if (readcount == 0)
    wrt = signal(wrt);
  mutex = signal(mutex);
}
void writer() {
  if (wrt == 1) {
    int n;
    wrt = wait(wrt);
    printf("\n Writer is writing..\n");
    xy:
      printf("\n1. for reading\n2. for writing\n3. exit writing");
    printf("\n\nchoice:");
    scanf("%d", & n);
    switch (n) {
    case 1:
      if (wrt == 0)
        printf("\n Cannot read, writer is writing..\n");
      goto xy;
      break;
    case 2:
      if (wrt == 0)
        printf("\n Cannot write, writer is writing..\n");
      goto xy;
      break;
    case 3:
      printf("\n Process is done writing..\n");
      wrt = signal(wrt);
      break;
    }
  } 
  else
    printf("\n Cannot write, processes are reading..\n");
}
int main() {
  int n;
  while (1) {
    printf("\n\t\t Main Menu");
    printf("\n1. for reading\n2. for writing\n3. exit ");
    printf("\n\nchoice:");
    scanf("%d", & n);
    switch (n) {
    case 1:
      reader();
      break;
    case 2:
      writer();
      break;
    case 3:
      exit(1);
    }
  }
}
