#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<malloc.h>
#define total_memory 200
typedef struct partition {
  int num; //Partition Number 
  int startAdress; //Partition Start Address 
  int leisureAdress; //Free Address 
  int size; //Remaining space 
  int state; //Status, 0 unallocated, 1 assigned 
  struct partition * next;
}
partition, * PART;
PART createPartition(int p) {
  PART partHead = NULL, mPart = NULL;

  printf("\nEnter size of memory blocks: ");
  int sizes[p], i;
  for (i = 0; i < p; i++) {
    scanf("%d", & sizes[i]);
  }

  int startAdress = 20;
  for (i = 1; i <= p; i++) {
    if (i == 1) {
      mPart = partHead = (PART) malloc(sizeof(partition));
      mPart -> num = i;
      mPart -> startAdress = startAdress;
      mPart -> leisureAdress = startAdress;
      mPart -> size = sizes[i - 1];
      mPart -> state = 0;
      startAdress += mPart -> size;
      mPart -> next = NULL;
    } else {
      mPart -> next = (PART) malloc(sizeof(partition));
      mPart = mPart -> next;
      mPart -> num = i;
      mPart -> startAdress = startAdress;
      mPart -> leisureAdress = startAdress;
      mPart -> size = sizes[i - 1];
      mPart -> state = 0;
      startAdress += mPart -> size;
      mPart -> next = NULL;
    }
  }
  return partHead;
}
void printPartitionQue(PART partHead) {
  PART mPart = partHead;
  printf("----------------------------------------------------------------------------------");
  printf("\n|Partition No  |Address        |Free Address   |Free space     |state          |\n");
  while (mPart != NULL) {
    printf("|%3d           |", mPart -> num);
    printf("%3d            |", mPart -> startAdress);
    printf("%3d            |", mPart -> leisureAdress);
    printf("%3d            |", mPart -> size);
    printf("%3d            |", mPart -> state);

    printf("\n");
    mPart = mPart -> next;
  }
  printf("\n");
  printf("----------------------------------------------------------------------------------\n");
}
PART sort(PART partHead, int totalPart, int val) {
  PART sortHead = NULL;
  PART nPart = NULL, tPart = NULL;;
  PART temp;
  int min = 0, max = 0;
  while (totalPart != 0) {
    if (val == 0) {
      min = partHead -> size;
      nPart = partHead -> next;
      //Get the smallest size assignment to min 
      while (nPart != NULL) {
        if (min > nPart -> size) {
          min = nPart -> size;
        }
        nPart = nPart -> next;
      }
      nPart = partHead;
    } else if (val == 1) {
      min = partHead -> size;
      nPart = partHead -> next;
      while (nPart != NULL) {
        if (min < nPart -> size) {
          min = nPart -> size;
        }
        nPart = nPart -> next;
      }
      nPart = partHead;
    }
    while (nPart != NULL) {
      if (nPart -> size == min) {
        temp = nPart;
        if (sortHead == NULL) {
          tPart = sortHead = (PART) malloc(sizeof(partition));
          tPart -> num = nPart -> num;
          tPart -> startAdress = nPart -> startAdress;
          tPart -> leisureAdress = nPart -> leisureAdress;
          tPart -> size = nPart -> size;
          tPart -> state = nPart -> state;
          tPart -> next = NULL;
        } else {
          tPart -> next = (PART) malloc(sizeof(partition));
          tPart = tPart -> next;
          tPart -> num = nPart -> num;
          tPart -> startAdress = nPart -> startAdress;
          tPart -> leisureAdress = nPart -> leisureAdress;
          tPart -> size = nPart -> size;
          tPart -> state = nPart -> state;
          tPart -> next = NULL;
        }
        PART mPart = partHead;
        while (mPart != NULL) {
          if (mPart == temp) {
            partHead = partHead -> next;
            totalPart--;
            break;
          } else if (mPart -> next == temp) {
            mPart -> next = temp -> next;
            totalPart--;
            break;
          }
          mPart = mPart -> next;
        }
      }

      nPart = nPart -> next;
    }
  }

  return sortHead;
}

void assignOfFirstFit(PART partHead, PART mPart, int size) {
  mPart = partHead;
  while (mPart != NULL) {
    if (mPart -> size >= size) {
      mPart -> size -= size;
      mPart -> leisureAdress += size;
      mPart -> state = 1;
      printf("\t\t\tFIRST FIT\t\t\t\n");
      printPartitionQue(partHead);
      break;
    }
    mPart = mPart -> next;
  }
  if (mPart == NULL) {
    printf("insufficient memory!\n");
  }
}

//	Best-fit algorithm

PART assignOfBestFit(PART partHead, PART mPart, int size, int p) {
  mPart = sort(partHead, p, 0);
  partHead = mPart;
  while (mPart != NULL) {
    if (mPart -> size >= size) {
      mPart -> size -= size;
      mPart -> leisureAdress += size;
      mPart -> state = 1;
      printf("\t\t\tBEST FIT\t\t\t\n");
      partHead = sort(partHead, p, 0);
      printPartitionQue(partHead);
      return partHead;
    }
    mPart = mPart -> next;
  }
  if (mPart == NULL) {
    printf("insufficient memory!\n");
    return partHead;
  }
}

PART assignOfWorstFit(PART partHead, PART mPart, int size, int p) {
  mPart = sort(partHead, p, 1);
  partHead = mPart;
  while (mPart != NULL) {
    if (mPart -> size >= size) {
      mPart -> size -= size;
      mPart -> leisureAdress += size;
      mPart -> state = 1;
      printf("\t\t\tWORST FIT\t\t\t\n");
      partHead = sort(partHead, p, 1);
      printPartitionQue(partHead);
      return partHead;
    }
    mPart = mPart -> next;
  }
  if (mPart == NULL) {
    printf("insufficient memory!\n");
    return partHead;
  }
}

int assignMemory(PART partHead, int assignType, int p) { //allocate memory//
  int totalPart = p;
  PART mPart = partHead;
  char c;
  int size = 0;
  printf("Whether to enter a process(Y/N):");
  scanf(" %c", & c);
  while (c == 'Y' || c == 'y') {
    printf("\nPlease enter process size: ");
    scanf("%d", & size);

    switch (assignType) {
    case 1:
      assignOfFirstFit(partHead, mPart, size);
      break;
    case 2:
      partHead = assignOfBestFit(partHead, mPart, size, totalPart);
      break;
    case 3:
      partHead = assignOfWorstFit(partHead, mPart, size, totalPart);
      break;
    }

    printf("Whether to enter a process(Y/N):");
    getchar();
    scanf(" %c", & c);
  }
  if (c == 'N' || c == 'n') {
    printf("\nYou have now exited");
    exit(1);
  }
  return 0;
}

int main() {
  int h, p, m, x;
  int k;
  printf("\nEnter initial no processes to populate the memory: ");
  scanf("%d", & p);

  PART partHead = createPartition(p);
  while (1) {
    printf("\n\n\t\t\t MENU \t\t\t\n");
    printf("\n1. FIRST FIT\n2. BEST FIT\n3. WORST FIT\n4. EXIT\n");
    printf("Enter your choice:\t");
    scanf("%d", & h);
    switch (h) {
    case 1:
      assignMemory(partHead, 1, p);
    case 2:
      assignMemory(partHead, 2, p);
    case 3:
      assignMemory(partHead, 3, p);
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

