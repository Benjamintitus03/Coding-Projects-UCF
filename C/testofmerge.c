// Function to merge two halves in descending order
void merge(array arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   // Size of the left subarray
    int n2 = right - mid;      // Size of the right subarray

    array L[n1], R[n2];         // Temporary arrays for left and right halves

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;  // Initial indexes for subarrays and merged array

    // Merging elements in descending order
    while (i < n1 && j < n2) {
        if (L[i].Vol >= R[j].Vol) {    // Compare volumes for descending order
            arr[k] = L[i];            // Take element from left array
            i++;
        } else {
            arr[k] = R[j];            // Take element from right array
            j++;
        }
        k++;
    }

    // Copy remaining elements from left array, if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements from right array, if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergesort(array arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(arr, left, mid);       // Sort the left half
        mergesort(arr, mid + 1, right);  // Sort the right half
        merge(arr, left, mid, right);    // Merge the two sorted halves
    }
}
