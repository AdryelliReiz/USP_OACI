#include <stdio.h>

void insertionSort(short int *arr, int n) {
    int i, j;
    short int key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    short int arr[] = {3, 2, 1, 5, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
