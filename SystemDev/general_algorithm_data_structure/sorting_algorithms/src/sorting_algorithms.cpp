#include "../include/sorting_algorithms.h"

const int RUN = 32; // The minimum run size for the mergeSortWithInsertion algorithm

namespace sorting_algorithms {

// Bubble Sort implementation
// Time Complexity: O(n^2) in worst and average case
void BubbleSort(std::vector<int>& arr, int n) {
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
void SelectionSort(std::vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        // Find the minimum element in the unsorted part of the array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap the found minimum element with the current element
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

// Insertion Sort implementation
// Time Complexity: O(n^2)
void InsertionSort(std::vector<int>& arr, int n) {
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
void Merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; // Size of left subarray
    int n2 = r - m;     // Size of right subarray

    // Temporary arrays for left and right subarrays
    vector<int> left_arr(n1, 0), right_arr(n2, 0);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of the left subarray
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy any remaining elements of the right subarray
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

// Merge Sort implementation
// Time Complexity: O(n log n)
void MergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Find the middle point
        // Recursively sort the left and right halves
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        // Merge the sorted halves
        Merge(arr, l, m, r);
    }
}

// Function to heapify a subtree rooted at index i for Heap Sort
void Heapify(std::vector<int>& arr, int n, int i) {
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
        Heapify(arr, n, largest);
    }
}

// Heap Sort implementation
// Time Complexity: O(n log n)
void HeapSort(std::vector<int>& arr, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, n, i);
    }

    // Extract elements one by one from the heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to the end
        swap(arr[0], arr[i]);
        // Call heapify on the reduced heap
        Heapify(arr, i, 0);
    }
}

// Function to partition the array for Quick Sort using a random pivot
int RandomizedPartition(std::vector<int>& arr, int low, int high) {
    // Use a random device and Mersenne Twister engine for better randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);

    // Generate a random index within the range and swap with the last element
    int random_index = dis(gen);
    swap(arr[random_index], arr[high]);

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
void QuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array around a random pivot
        int pi = RandomizedPartition(arr, low, high);
        // Recursively sort the left and right subarrays
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// Bucket Sort implementation
// Time Complexity: O(n + k), where k is the number of buckets
void BucketSort(std::vector<int>& arr, int n) {
    const int kMaxVal = *std::max_element(arr.begin(), arr.end());
    const int kMinVal = *std::min_element(arr.begin(), arr.end());
    const int kRange = kMaxVal - kMinVal + 1;
    const int kBucketSize = 10; // Number of buckets can be adjusted

    // Create empty buckets
    std::vector<std::vector<int>> buckets(kBucketSize);

    // Place array elements in different buckets
    for (auto i = 0; i < n; i++) {
        int index = (arr[i] - kMinVal) * kBucketSize / kRange;
        buckets[index].push_back(arr[i]);
    }

    // Sort individual buckets using another sorting algorithm (e.g., Insertion Sort)
    for (auto i = 0; i < kBucketSize; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Concatenate all buckets back into the original array
    int index = 0;
    for (auto i = 0; i < kBucketSize; i++) {
        for (std::vector<int>::size_type j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void ThreeWayPartition(std::vector<int>& arr, int low, int high, int& lt, int& gt) {
    int pivot = MedianOfThree(arr, low, high); // Use the median-of-three pivot selection
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

int MedianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    // Arrange the first, middle, and last elements in ascending order
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    // Use the middle element as the pivot
    swap(arr[mid], arr[high]); // Move the pivot to the end
    return arr[high];
}

void QuickSortWithInsertion(std::vector<int>& arr, int low, int high) {
    const int kThreshold = 20;  // Switch to insertion sort when subarray size is below threshold

    if (low >= high) return;

    if (high - low + 1 <= kThreshold) {
        // Copy the subarray [low, high] into a temporary array
        std::vector<int> sub_arr(arr.begin() + low, arr.begin() + high + 1);

        // Use the existing insertionSort function on the temporary array
        InsertionSort(sub_arr, sub_arr.size());

        // Copy the sorted subarray back into the original array
        for (int i = low; i <= high; i++) {
            arr[i] = sub_arr[i - low];
        }
    } else {
        int lt, gt;
        // Perform three-way partition
        ThreeWayPartition(arr, low, high, lt, gt);

        // Recursively sort the left and right parts
        QuickSortWithInsertion(arr, low, lt - 1);
        QuickSortWithInsertion(arr, gt + 1, high);
    }
}

void MergeSortWithInsertion(std::vector<int>& arr, int n) {
    // Step 1: Use insertion sort to sort small runs of size RUN
    for (int i = 0; i < n; i += RUN) {
        int right = std::min(i + RUN - 1, n - 1);  // Define the right boundary of the current run

        // Use the existing insertionSort function to sort the run
        std::vector<int> sub_arr(arr.begin() + i, arr.begin() + right + 1);
        InsertionSort(sub_arr, sub_arr.size());

        // Copy the sorted subarray back into the original array
        for (size_t j = 0; j < sub_arr.size(); ++j) {
            arr[i + j] = sub_arr[j];
        }
    }

    // Step 2: Merge sorted runs to create larger sorted segments
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);  // Midpoint of the current segment
            int right = std::min(left + 2 * size - 1, n - 1);  // Right boundary of the current segment

            // Merge two sorted runs if mid is before right
            if (mid < right) {
                Merge(arr, left, mid, right);  // Merge two runs
            }
        }
    }
}

} // namespace SortingAlgorithms
