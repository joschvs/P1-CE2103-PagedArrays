#ifndef P1_CE2103_PAGEDARRAYS_MERGESORT_H
#define P1_CE2103_PAGEDARRAYS_MERGESORT_H

inline void merge(int* arr, long left, long mid, long right) {
    long n1 = mid - left + 1;
    long n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

inline void mergeSortRecursive(int* arr, long left, long right) {
    if (left < right) {
        long mid = left + (right - left) / 2;

        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

inline void mergeSort(int* arr, long n) {
    if (n > 1) {
        mergeSortRecursive(arr, 0, n - 1);
    }
}

#endif