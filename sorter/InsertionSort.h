#ifndef P1_CE2103_PAGEDARRAYS_INSERTIONSORT_H
#define P1_CE2103_PAGEDARRAYS_INSERTIONSORT_H

inline void insertionSort(PagedArray& arr, long n)
{
    for (int i = 1; i < n; i++)
    {
        int elem = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > elem) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = elem;
    }
}

#endif