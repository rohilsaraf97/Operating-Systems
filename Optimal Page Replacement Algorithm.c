#include <stdio.h>

int main()
{
    int flag1, flag2, n, i, k, p, j = 0, count = 0, no, frames[10], found, location[10], counter, pagefault = 0;
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
                    frames[k] = entries[i];
                    pagefault++;
                    flag2 = 1;
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
            for (k = 0; k < no; k++)
            {
                counter = 0;
                for (p = i + 1; p < n; p++)
                {
                    if (frames[k] == entries[p])
                    {
                        location[k] = p;
                        break;
                    }
                    else
                    {
                        counter++;
                    }
                }
                if (counter >= (n - i - 2))
                {
                    location[k] = n + 1;
                }
            }
            int max = location[0], maxpos;
            for (k = 0; k < no; k++)
            {
                if (location[k] > max)
                {
                    max = location[k];
                    maxpos = k;
                }
            }
            frames[maxpos] = entries[i];
            pagefault++;
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