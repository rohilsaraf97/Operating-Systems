#include <stdio.h>

int main()
{

    int n, i, k, p, j = 0, count = 0, no, frames[10], found;
    printf("\nEnter no of pages: ");
    scanf("%d", &n);
    int entries[n];
    printf("\nEnter page numbers: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &entries[i]);
    }
    printf("\nEnter no of frames : ");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
    {
        frames[i] = -1;
    }
    printf("Page number\t Frames\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t", entries[i]);
        found = 0;
        for (k = 0; k < no; k++)
        {
            if (frames[k] == entries[i])
            {
                found = 1;
                for (p = 0; p < no; p++)
                    printf("%d\t", frames[p]);
                printf(" HIT");
            }
        }
        if (found == 0)
        {
            frames[j] = entries[i];
            j = (j + 1) % no;
            count++;
            for (p = 0; p < no; p++)
                printf("%d\t", frames[p]);
            printf(" MISS");
        }

        printf("\n");
    }
    printf("Page fault is %d", count);
    return 0;
}