#include <stdio.h>
int main()
{
int n, m, i, j, k,need[5][4],status[20],index=0,proc[20];
int allocation[10][10],max[10][10],avail[10];
printf("\nEnter resources:");
scanf("%d",&m);
printf("\nEnter Processes:");
scanf("%d",&n);
printf("\nEnter Allocation matrix:\n");
for (i = 0; i < n; i++) {
for (j = 0; j < m; j++) {
scanf("%d",&allocation[i][j]);
}
}
printf("\nEnter Maximum matrix:\n");
for (i = 0; i < n; i++) {
for (j = 0; j < m; j++) {
scanf("%d",&max[i][j]);
}
}
printf("\nEnter Available matrix:\n");
for (i = 0; i < m; i++) {
scanf("%d",&avail[i]);
}
for (k = 0; k < n; k++) {
status[k] = 0;
}
for (i = 0; i < n; i++) { 
for (j = 0; j < m; j++)
need[i][j] = max[i][j] - allocation[i][j];
}
printf("\nNeed Matrix:");
for (i = 0; i < n; i++) {
printf("\n");
for (j = 0; j < m; j++)
printf("%d ",need[i][j]);
}
for (k = 0; k < n; k++) {
for (i = 0; i < n; i++) {
if (status[i] == 0) {
int flag = 0;
for (j = 0; j < m; j++) {
if (need[i][j] > avail[j]){
flag = 1;
break; }}
if (flag == 0) {
proc[index++] = i;
for (int l = 0; l < m; l++)
avail[l] += allocation[i][l];
status[i] = 1; }}
}
}
printf("\nProcess sequence: ");
for (i = 0; i < n; i++)
{
printf("p%d, ", proc[i]);
}
return 0;
}
