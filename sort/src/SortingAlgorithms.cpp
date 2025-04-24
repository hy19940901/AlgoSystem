#include "../include/SortingAlgorithms.h"

const int RUN = 32; // The minimum run size for the mergeSortWithInsertion algorithm


namespace SortingAlgorithms {

// Bubble Sort implementation
// Time Complexity: O(n^2) in worst and average case
void bubbleSort(vector<int>& arr, int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // Swap if elements are in wrong order
                swapped = true;
            }
        }
        if (!swapped) break; // If no elements were swapped, the array is sorted
    }
}

// Selection Sort implementation
// Time Complexity: O(n^2)
void selectionSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        // Find the minimum element in the unsorted part of the array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the current element
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Insertion Sort implementation
// Time Complexity: O(n^2)
void insertionSort(vector<int>& arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Place the key in its correct position
    }
}

// Merging two halves of an array for Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; // Size of left subarray
    int n2 = r - m;     // Size of right subarray

    // Temporary arrays for left and right subarrays
    int L[n1], R[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Merge the temporary arrays back into the original array
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

    // Copy any remaining elements of the left subarray
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements of the right subarray
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort implementation
// Time Complexity: O(n log n)
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Find the middle point
        // Recursively sort the left and right halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to heapify a subtree rooted at index i for Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;    // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root, swap it and recursively heapify the affected subtree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort implementation
// Time Complexity: O(n log n)
void heapSort(vector<int>& arr, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements one by one from the heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to the end
        swap(arr[0], arr[i]);
        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to partition the array for Quick Sort using a random pivot
int randomizedPartition(vector<int>& arr, int low, int high) {
    // Use a random device and Mersenne Twister engine for better randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);

    // Generate a random index within the range and swap with the last element
    int randomIndex = dis(gen);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high]; // Pivot element
    int i = (low - 1);     // Index of the smaller element

    // Partition the array based on the pivot
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // Place the pivot in its correct position
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort implementation
// Time Complexity: O(n log n) on average, O(n^2) in the worst case
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array around a random pivot
        int pi = randomizedPartition(arr, low, high);
        // Recursively sort the left and right subarrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Bucket Sort implementation
// Time Complexity: O(n + k), where k is the number of buckets
void bucketSort(vector<int>& arr, int n) {
    const int maxVal = *std::max_element(arr.begin(), arr.end());
    const int minVal = *std::min_element(arr.begin(), arr.end());
    const int range = maxVal - minVal + 1;
    const int bucketSize = 10; // Number of buckets can be adjusted

    // Create empty buckets
    std::vector<std::vector<int>> buckets(bucketSize);

    // Place array elements in different buckets
    for (auto i = 0; i < n; i++) {
        int index = (arr[i] - minVal) * bucketSize / range;
        buckets[index].push_back(arr[i]);
    }

    // Sort individual buckets using another sorting algorithm (e.g., Insertion Sort)
    for (auto i = 0; i < bucketSize; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Concatenate all buckets back into the original array
    int index = 0;
    for (auto i = 0; i < bucketSize; i++) {
        for (std::vector<int>::size_type j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int pivot = medianOfThree(arr, low, high); // Use the median-of-three pivot selection
    lt = low;  // Initialize lt to the starting index
    gt = high; // Initialize gt to the ending index
    int i = low;

    // Partition the array into three sections: less than, equal to, and greater than pivot
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt++], arr[i++]); // Move elements smaller than the pivot to the left
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt--]); // Move elements larger than the pivot to the right
        } else {
            i++; // Leave elements equal to the pivot in the middle
        }
    }
}

int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    // Arrange the first, middle, and last elements in ascending order
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    // Use the middle element as the pivot
    swap(arr[mid], arr[high]); // Move the pivot to the end
    return arr[high];
}

void quickSortWithInsertion(vector<int>& arr, int low, int high) {
    const int threshold = 20;  // Switch to insertion sort when subarray size is below threshold

    if (low >= high) return;

    if (high - low + 1 <= threshold) {
        // Copy the subarray [low, high] into a temporary array
        vector<int> subArr(arr.begin() + low, arr.begin() + high + 1);

        // Use the existing insertionSort function on the temporary array
        insertionSort(subArr, subArr.size());

        // Copy the sorted subarray back into the original array
        for (int i = low; i <= high; i++) {
            arr[i] = subArr[i - low];
        }
    } else {
        int lt, gt;
        // Perform three-way partition
        threeWayPartition(arr, low, high, lt, gt);

        // Recursively sort the left and right parts
        quickSortWithInsertion(arr, low, lt - 1);
        quickSortWithInsertion(arr, gt + 1, high);
    }
}

void mergeSortWithInsertion(vector<int>& arr, int n) {
    // Step 1: Use insertion sort to sort small runs of size RUN
    for (int i = 0; i < n; i += RUN) {
        int right = std::min(i + RUN - 1, n - 1);  // Define the right boundary of the current run

        // Use the existing insertionSort function to sort the run
        std::vector<int> subArr(arr.begin() + i, arr.begin() + right + 1);
        insertionSort(subArr, subArr.size());

        // Copy the sorted subarray back into the original array
        for (size_t j = 0; j < subArr.size(); ++j) {
            arr[i + j] = subArr[j];
        }
    }

    // Step 2: Merge sorted runs to create larger sorted segments
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);  // Midpoint of the current segment
            int right = std::min(left + 2 * size - 1, n - 1);  // Right boundary of the current segment

            // Merge two sorted runs if mid is before right
            if (mid < right) {
                merge(arr, left, mid, right);  // Merge two runs
            }
        }
    }
}

} // namespace SortingAlgorithms
