#ifndef P1_CE2103_PAGEDARRAYS_QUICKSORT_H
#define P1_CE2103_PAGEDARRAYS_QUICKSORT_H
inline long partition(PagedArray& arr, long low, long high) {
    int pivot = arr[high];
    long i = low - 1;

    for (long j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

inline void quickSortAux(PagedArray& arr, long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);

        quickSortAux(arr, low, pi - 1);
        quickSortAux(arr, pi + 1, high);
    }
}

inline void quickSort(PagedArray& arr, long n) {
    if (n > 1) {
        quickSortAux(arr, 0, n - 1);
    }
}

#endif