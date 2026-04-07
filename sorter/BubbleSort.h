#ifndef P1_CE2103_PAGEDARRAYS_BUBBLESORT_H
#define P1_CE2103_PAGEDARRAYS_BUBBLESORT_H

void bubbleSort(PagedArray& arr, long n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

#endif