#include <stdio.h>

int main()
{

    int flag1, flag2, n, i, k, no, frames[10], used[10], counter = 0, pagefault = 0;
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
    printf("\nPage number\t Frames\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t", entries[i]);
        flag1 = flag2 = 0;
        for (k = 0; k < no; k++)
        {
            if (frames[k] == entries[i])
            {
                flag1 = flag2 = 1;
                counter++;
                used[k] = counter;
                for (k = 0; k < no; k++)
                {
                    printf("%d\t", frames[k]);
                }
                printf(" HIT");
                break;
            }
        }

        if (flag1 == 0)
        {
            for (k = 0; k < no; k++)
            {
                if (frames[k] == -1)
                {
                    counter++;
                    pagefault++;
                    flag1 = flag2 = 1;
                    used[k] = counter;
                    frames[k] = entries[i];
                    for (k = 0; k < no; k++)
                    {
                        printf("%d\t", frames[k]);
                    }
                    printf(" MISS");
                    break;
                }
            }
        }

        if (flag2 == 0)
        {
            int min = used[0], minpos;
            for (k = 0; k < no; k++)
            {
                if (used[k] < min)
                {
                    min = used[k];
                    minpos = k;
                }
            }
            frames[minpos] = entries[i];
            counter++;
            pagefault++;
            used[minpos] = counter;
            for (k = 0; k < no; k++)
            {
                printf("%d\t", frames[k]);
            }
            printf(" MISS");
        }

        printf("\n");
    }

    printf("Page fault is %d", pagefault);
    return 0;
}