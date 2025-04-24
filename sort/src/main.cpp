#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>  // Include the random number generation library
#include "../include/SortingAlgorithms.h"


using namespace std::chrono;

/**
 * Displays the contents of the array.
 *
 * @param arr The array to be displayed.
 */
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

/**
 * Checks if the array is sorted in non-decreasing order.
 *
 * @param arr The array to check.
 * @return True if the array is sorted, false otherwise.
 */
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Generates an array of random integers of a given size.
 * Uses a high-quality random number generator (Mersenne Twister) to ensure better randomness.
 *
 * @param size The size of the array to generate.
 * @return A vector of random integers between 0 and 2,000,000.
 */
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);

    // Use a random device as the seed to ensure different random numbers each time
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister engine for random number generation
    std::uniform_int_distribution<> dis(0, 2000000); // Uniform distribution in the range [0, 2,000,000]

    // Populate the array with random numbers
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }

    return arr;
}

/**
 * Benchmarks a sorting function by measuring the time it takes to sort an array.
 *
 * @param sortName The name of the sorting algorithm.
 * @param sortFunction The sorting function to benchmark.
 * @param arr The array to be sorted.
 */
void benchmarkSort(const std::string& sortName, void(*sortFunction)(std::vector<int>&, int), std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now(); // Start the timer
    sortFunction(arr, arr.size()); // Execute the sorting algorithm
    auto end = std::chrono::high_resolution_clock::now(); // Stop the timer

    // Calculate and print the elapsed time in seconds
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << sortName << " took " << duration.count() << " seconds." << std::endl;

    // Check if the array is sorted and print the result
    if (isSorted(arr)) {
        std::cout << sortName << ": Array is sorted!" << std::endl;
    } else {
        std::cout << sortName << ": Array is not sorted!" << std::endl;
    }
}

/**
 * Demonstrates sorting an array with 10 elements and displays the result.
 *
 * @param sortFunction The sorting function to demonstrate.
 */
void demonstrateSortingWith10Elements(void(*sortFunction)(vector<int>&, int)) {
    vector<int> arr = generateRandomArray(10); // Generate an array of 10 random elements

    cout << "Original Array (10 elements): ";
    displayArray(arr); // Display the original array

    sortFunction(arr, arr.size()); // Sort the array

    cout << "Sorted Array (10 elements): ";
    displayArray(arr); // Display the sorted array

    // Check if the array is sorted and print the result
    if (isSorted(arr)) {
        cout << "Array is sorted!" << endl;
    } else {
        cout << "Array is not sorted!" << endl;
    }
}

/**
 * The main function where the sorting algorithms are benchmarked with varying array sizes.
 */
int main() {
    vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000}; // Added 1,000,000 size for benchmark

    // Loop through different array sizes for benchmarking
    for (int size : sizes) {
        cout << "\nBenchmarking for array size: " << size << endl;
        vector<int> arr = generateRandomArray(size); // Generate a random array of the specified size

        // Benchmark Bubble Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            benchmarkSort("Bubble Sort", SortingAlgorithms::bubbleSort, arr);
        }

        // Benchmark Selection Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            benchmarkSort("Selection Sort", SortingAlgorithms::selectionSort, arr);
        }

        // Benchmark Insertion Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            benchmarkSort("Insertion Sort", SortingAlgorithms::insertionSort, arr);
        }

        // Benchmark Merge Sort (can handle larger arrays efficiently)
        benchmarkSort("Merge Sort", [](vector<int>& arr, int n) { SortingAlgorithms::mergeSort(arr, 0, n - 1); }, arr);

        // Benchmark Heap Sort (can handle larger arrays efficiently)
        benchmarkSort("Heap Sort", SortingAlgorithms::heapSort, arr);

        // Benchmark Quick Sort (can handle larger arrays efficiently)
        benchmarkSort("Quick Sort", [](vector<int>& arr, int n) { SortingAlgorithms::quickSort(arr, 0, n - 1); }, arr);

        // Benchmark Bucket Sort (can handle larger arrays efficiently)
        benchmarkSort("Bucket Sort", SortingAlgorithms::bucketSort, arr);

        // Benchmark 3-Way Quick Sort (optimized for large arrays with duplicates)
        benchmarkSort("3-Way Quick Sort combined with insertion", [](vector<int>& arr, int n) { SortingAlgorithms::quickSortWithInsertion(arr, 0, n - 1); }, arr);

        // Benchmark Timsort
        benchmarkSort("Merge Sort combined with insertion", [](vector<int>& arr, int n) { SortingAlgorithms::mergeSortWithInsertion(arr, n); }, arr);
    }

    // Demonstrate sorting with 10 elements using various algorithms
    cout << "\nDemonstrating sorting with 10 elements:" << endl;
    demonstrateSortingWith10Elements(SortingAlgorithms::bubbleSort);
    demonstrateSortingWith10Elements(SortingAlgorithms::selectionSort);
    demonstrateSortingWith10Elements(SortingAlgorithms::insertionSort);
    demonstrateSortingWith10Elements(SortingAlgorithms::heapSort);
    demonstrateSortingWith10Elements([](vector<int>& arr, int n){ SortingAlgorithms::mergeSort(arr, 0, n-1); });
    demonstrateSortingWith10Elements([](vector<int>& arr, int n){ SortingAlgorithms::quickSort(arr, 0, n-1); });
    demonstrateSortingWith10Elements(SortingAlgorithms::bucketSort);
    demonstrateSortingWith10Elements([](vector<int>& arr, int n){ SortingAlgorithms::quickSortWithInsertion(arr, 0, n-1); });
    demonstrateSortingWith10Elements([](vector<int>& arr, int n){ SortingAlgorithms::mergeSortWithInsertion(arr, n); });

    return 0;
}
