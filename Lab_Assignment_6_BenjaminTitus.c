#include <stdlib.h>
#include <stdio.h>

int BubSort(int arr[], int n) {
    int i, j, temp, swap_amt = 0;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap_amt++;
            }
        }
    }
    return swap_amt;
}

int SelSort(int arr[], int n) {
    int i, j, minIndex, temp, swap_amt2 = 0;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
        swap_amt2++;
    }
    return swap_amt2;
}

void printSwaps(int arr[], int n, int total_swaps) {
    for (int i = 0; i < n; i++) {
        printf("%d: # of times %d is swapped\n", arr[i], arr[i]);
    }
    printf("total # of swaps: %d\n\n", total_swaps);
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);

    int total_swaps_bubble1 = BubSort(array1, n1);
    int total_swaps_selection1 = SelSort(array1, n1);
    
    printf("Bubble Sort for array1:\n");
    printSwaps(array1, n1, total_swaps_bubble1);

    printf("Selection Sort for array1:\n");
    printSwaps(array1, n1, total_swaps_selection1);

    int total_swaps_bubble2 = BubSort(array2, n2);
    int total_swaps_selection2 = SelSort(array2, n2);

    printf("Bubble Sort for array2:\n");
    printSwaps(array2, n2, total_swaps_bubble2);

    printf("Selection Sort for array2:\n");
    printSwaps(array2, n2, total_swaps_selection2);

    return 0;
}
