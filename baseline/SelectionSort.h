#ifndef P1_CE2103_PAGEDARRAYS_SELECTIONSORT_H
#define P1_CE2103_PAGEDARRAYS_SELECTIONSORT_H

inline void selectionSort(int* arr, long n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}
#endif