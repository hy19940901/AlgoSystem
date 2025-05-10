#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using std::vector;

namespace SortingAlgorithms {
/**
 * Sorts an array using the Bubble Sort algorithm.
 *
 * @param arr The array to sort.
 * @param n The size of the array.
 *
 * Bubble Sort repeatedly swaps adjacent elements if they are in the wrong order.
 * The time complexity is O(n^2), making it inefficient for large arrays.
 */
void bubbleSort(vector<int>& arr, int n);

/**
 * Sorts an array using the Selection Sort algorithm.
 *
 * @param arr The array to sort.
 * @param n The size of the array.
 *
 * Selection Sort works by repeatedly finding the minimum element from the unsorted part
 * and putting it at the beginning. The time complexity is O(n^2).
 */
void selectionSort(vector<int>& arr, int n);

/**
 * Sorts an array using the Insertion Sort algorithm.
 *
 * @param arr The array to sort.
 * @param n The size of the array.
 *
 * Insertion Sort builds the final sorted array one item at a time. It is much more efficient 
 * on small datasets and mostly sorted arrays. Time complexity is O(n^2).
 */
void insertionSort(vector<int>& arr, int n);

/**
 * Merges two halves of an array. Used in Merge Sort.
 *
 * @param arr The array to merge.
 * @param l The left index.
 * @param m The middle index.
 * @param r The right index.
 *
 * Merge function takes two sorted arrays (left and right) and merges them into one sorted array.
 */
void merge(vector<int>& arr, int l, int m, int r);

/**
 * Sorts an array using the Merge Sort algorithm.
 *
 * @param arr The array to sort.
 * @param l The left index (starting point of the array).
 * @param r The right index (ending point of the array).
 *
 * Merge Sort divides the array into two halves, recursively sorts them, and then merges them.
 * It is an efficient algorithm with time complexity O(n log n).
 */
void mergeSort(vector<int>& arr, int l, int r);

/**
 * Helps to maintain the heap property of a subtree rooted at index i.
 * Used in Heap Sort.
 *
 * @param arr The array representing the heap.
 * @param n The size of the heap.
 * @param i The index of the root of the subtree.
 *
 * Heapify ensures that the subtree satisfies the heap property (parent nodes are greater than child nodes).
 * This function is called recursively.
 */
void heapify(vector<int>& arr, int n, int i);

/**
 * Sorts an array using the Heap Sort algorithm.
 *
 * @param arr The array to sort.
 * @param n The size of the array.
 *
 * Heap Sort builds a max-heap and then extracts the maximum element one by one.
 * It has time complexity O(n log n).
 */
void heapSort(vector<int>& arr, int n);

/**
 * Partitions the array for Quick Sort using a random pivot.
 *
 * @param arr The array to partition.
 * @param low The starting index.
 * @param high The ending index.
 * @return The partition index.
 *
 * This function selects a random pivot and rearranges the array such that elements smaller than the pivot
 * are on the left, and elements larger than the pivot are on the right.
 */
int randomizedPartition(vector<int>& arr, int low, int high);

/**
 * Sorts an array using the Quick Sort algorithm.
 *
 * @param arr The array to sort.
 * @param low The starting index.
 * @param high The ending index.
 *
 * Quick Sort is a divide-and-conquer algorithm that selects a pivot and partitions the array around it.
 * The time complexity is O(n log n) on average, but can be O(n^2) in the worst case.
 */
void quickSort(vector<int>& arr, int low, int high);

/**
 * Sorts an array using the Bucket Sort algorithm.
 *
 * @param arr The array to sort.
 * @param n The size of the array.
 *
 * Bucket Sort divides the array into several "buckets" and then sorts each bucket individually using another sorting algorithm (like Insertion Sort).
 * It is efficient for uniformly distributed data with time complexity O(n + k), where k is the number of buckets.
 */
void bucketSort(vector<int>& arr, int n);

/**
 * Finds the median of the first, middle, and last elements in the array.
 * This helps in selecting a better pivot for quicksort to avoid worst-case scenarios.
 *
 * @param arr The array from which the pivot is selected.
 * @param low The starting index of the array.
 * @param high The ending index of the array.
 * @return The median element to be used as the pivot.
 */
int medianOfThree(vector<int>& arr, int low, int high);

/**
 * Partitions the array into three parts: less than, equal to, and greater than the pivot.
 * The pivot is chosen using the median-of-three method for better partitioning performance.
 *
 * @param arr The array to be partitioned.
 * @param low The starting index of the array.
 * @param high The ending index of the array.
 * @param lt Reference to the index where the 'less than pivot' region ends.
 * @param gt Reference to the index where the 'greater than pivot' region starts.
 */
void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt);

/**
 * Sorts the array using a combination of 3-way quick sort and insertion sort.
 * When the subarray size is smaller than a predefined threshold, insertion sort
 * is used for better performance on small datasets. For larger datasets, 3-way
 * quick sort is applied.
 *
 * @param arr The array to be sorted.
 * @param low The starting index of the subarray.
 * @param high The ending index of the subarray.
 *
 * This hybrid approach improves the performance of quicksort by leveraging
 * insertion sort for small subarrays. The time complexity is O(n log n) on average.
 */
void quickSortWithInsertion(vector<int>& arr, int low, int high);

/**
 * mergeSortWithInsertion main logic
 *
 * This algorithm is a hybrid approach that uses insertion sort for small blocks
 * and merge sort to combine the sorted blocks into a fully sorted array. The array
 * is divided into blocks of size RUN, sorted using insertion sort, and then merged.
 *
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void mergeSortWithInsertion(vector<int>& arr, int n);

} // namespace SortingAlgorithms

#endif
