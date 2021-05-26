#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#define max 25
void firstfit() {
  int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j;
  printf("\n\t\t\tMemory Management Scheme - First Fit");
  for (i = 0; i < 10; i++) {
    flags[i] = 0;
    allocation[i] = -1;
  }

  printf("\nEnter no. of blocks: ");
  scanf("%d", & bno);
  printf("Enter no. of processes: ");
  scanf("%d", & pno);

  printf("Enter size of each block: ");
  for (i = 0; i < bno; i++)
    scanf("%d", & bsize[i]);

  printf("Enter size of each process: ");
  for (i = 0; i < pno; i++)
    scanf("%d", & psize[i]);
  for (i = 0; i < pno; i++) //allocation as per first fit
    for (j = 0; j < bno; j++)
      if (flags[j] == 0 && bsize[j] >= psize[i]) {
        allocation[j] = i;
        flags[j] = 1;
        break;
      }

  printf("\nBlock no.\tsize\tprocess no.\tsize");
  for (i = 0; i < bno; i++) {
    printf("\n%d\t\t%d\t\t", i + 1, bsize[i]);
    if (flags[i] == 1)
      printf("%d\t\t\t%d", allocation[i] + 1, psize[allocation[i]]);
    else
      printf("Not allocated");
  }
}
void worstfit() {
  int i, numBlock, numProcess, * bSize, * pSize;
  int j, allocation[numProcess], fit, flag[numBlock], ext = 0, ext1 = 0, external_frag = 0, internal_frag = 0, total_internal = 0;
  printf("\n\t\t\tMemory Management Scheme - Worst Fit");
  printf("\nEnter total blocks: ");
  scanf("%d", & numBlock);
  printf("Enter total processes: ");
  scanf("%d", & numProcess);
  bSize = (int * ) malloc(numBlock * sizeof(int));
  printf("Enter size of each block: ");
  for (i = 0; i < numBlock; i++)
    scanf("%d", & bSize[i]);

  pSize = (int * ) malloc(numProcess * sizeof(int));
  printf("Enter size of each process: ");
  for (i = 0; i < numProcess; i++)
    scanf("%d", & pSize[i]);

  for (i = 0; i < numProcess; i++) {
    allocation[i] = -1;
  }
  for (i = 0; i < numBlock; i++) {
    flag[i] = 0;
  }
  for (i = 0; i < numProcess; i++) {
    fit = -1;
    for (j = 0; j < numBlock; j++) {
      if (bSize[j] - pSize[i] >= 0) {
        if (flag[j] == 0) {
          if (fit == -1) {
            fit = j;
            flag[fit] = 1;
          } else if (bSize[fit] < bSize[j]) {
            flag[fit] = 0;
            fit = j;
            flag[j] = 1;
          }
        }
      }
    }
    if (fit != -1) {
      allocation[i] = fit;
      internal_frag = bSize[fit] - pSize[i];
      bSize[fit] = internal_frag;
      total_internal += internal_frag;
    }
  }
  //To check any process unallocated
  for (i = 0; i < numProcess; i++) {
    if (allocation[i] == -1) {
      ext1 += pSize[i];
      //  printf("\nUnallocated process size: %d, ext1: %d",pSize[i],ext1);
    }
  }
  //To check unallocated block
  for (i = 0; i < numBlock; i++) {
    if (flag[i] == 0) {
      ext += bSize[i];
      //printf("\nUnallocated block size: %d, ext: %d",bSize[i],ext);
    }
  }
  if (ext >= ext1) {
    external_frag = ext;
  } else {
    external_frag = 0;
  }
  printf("\nProcess\t\tsize\t\tBlock no.");
  for (i = 0; i < numProcess; i++) {
    printf("\n%d\t\t%d\t\t", (i + 1), pSize[i]);
    if (allocation[i] != -1)
      printf("%d", (allocation[i] + 1));
    else
      printf("Not Allocated");
  }
}
void bestfit() {
  int fragment[20], b[20], p[20], i, j, nb, np, temp, lowest = 9999;
  static int barray[20], parray[20];

  printf("\n\t\t\tMemory Management Scheme - Best Fit");
  printf("\nEnter the number of blocks: ");
  scanf("%d", & nb);
  printf("Enter the number of processes: ");
  scanf("%d", & np);

  printf("Enter the size of the blocks: ");
  for (i = 1; i <= nb; i++)
    scanf("%d", & b[i]);

  printf("Enter the size of the processes : ");
  for (i = 1; i <= np; i++)
    scanf("%d", & p[i]);

  for (i = 1; i <= np; i++) {
    for (j = 1; j <= nb; j++) {
      if (barray[j] != 1) {
        temp = b[j] - p[i];
        if (temp >= 0)
          if (lowest > temp) {
            parray[i] = j;
            lowest = temp;
          }
      }
    }

    fragment[i] = lowest;
    barray[parray[i]] = 1;
    lowest = 10000;
  }

  printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment");
  for (i = 1; i <= np && parray[i] != 0; i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, p[i], parray[i], b[parray[i]], fragment[i]);
}
int main() {
  int h;
  while (1) {
    printf("\n\n\t\t\t MENU \t\t\t\n");
    printf("\n1. BEST FIT\n2. WORST FIT\n3. FIRST FIT\n4. EXIT\n");
    printf("Enter your choice:\t");
    scanf("%d", & h);
    switch (h) {
    case 1:
      bestfit();
      break;
    case 2:
      worstfit();
      break;
    case 3:
      firstfit();
      break;
    case 4:
      printf("\nYou have now exited");
      exit(1);
    default:
      printf("\ninvalid option\n");
      break;
    }
  }
  return 0;
}

