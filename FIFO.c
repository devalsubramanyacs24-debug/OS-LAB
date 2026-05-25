#include <stdio.h>

void fifo(int pages[], int n, int capacity)
{
    int frames[10], front = 0, faults = 0;

    for(int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nFIFO PAGE REPLACEMENT\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < capacity; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frames[front] = pages[i];
            front = (front + 1) % capacity;
            faults++;
        }

        printf("Page %d -> ", pages[i]);

        for(int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void lru(int pages[], int n, int capacity)
{
    int frames[10], time[10];
    int faults = 0, counter = 0;

    for(int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU PAGE REPLACEMENT\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < capacity; j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = 0;

            for(int j = 1; j < capacity; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("Page %d -> ", pages[i]);

        for(int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void optimal(int pages[], int n, int capacity)
{
    int frames[10];
    int faults = 0;

    for(int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nOPTIMAL PAGE REPLACEMENT\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < capacity; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1, farthest = i;

            for(int j = 0; j < capacity; j++)
            {
                int k;

                for(k = i + 1; k < n; k++)
                {
                    if(frames[j] == pages[k])
                    {
                        if(k > farthest)
                        {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }

                if(k == n)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
                pos = 0;

            frames[pos] = pages[i];
            faults++;
        }

        printf("Page %d -> ", pages[i]);

        for(int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}
