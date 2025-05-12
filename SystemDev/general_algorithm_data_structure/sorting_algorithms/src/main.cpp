#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>  // Include the random number generation library
#include "../include/sorting_algorithms.h"


/**
 * Displays the contents of the array.
 *
 * @param arr The array to be displayed.
 */
void DisplayArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

/**
 * Checks if the array is sorted in non-decreasing order.
 *
 * @param arr The array to check.
 * @return True if the array is sorted, false otherwise.
 */
bool IsSorted(const std::vector<int>& arr) {
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
std::vector<int> GenerateRandomArray(int size) {
    std::vector<int> arr(size);

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
 * @param sort_name The name of the sorting algorithm.
 * @param SortFunction The sorting function to benchmark.
 * @param arr The array to be sorted.
 */
void BenchmarkSort(const std::string& sort_name, void(*SortFunction)(std::vector<int>&, int), std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now(); // Start the timer
    SortFunction(arr, arr.size()); // Execute the sorting algorithm
    auto end = std::chrono::high_resolution_clock::now(); // Stop the timer

    // Calculate and print the elapsed time in seconds
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << sort_name << " took " << duration.count() << " seconds." << std::endl;

    // Check if the array is sorted and print the result
    if (IsSorted(arr)) {
        std::cout << sort_name << ": Array is sorted!" << std::endl;
    } else {
        std::cout << sort_name << ": Array is not sorted!" << std::endl;
    }
}

/**
 * Demonstrates sorting an array with 10 elements and displays the result.
 *
 * @param SortFunction The sorting function to demonstrate.
 */
void DemonstrateSortingWith10Elements(void(*SortFunction)(std::vector<int>&, int)) {
    std::vector<int> arr = GenerateRandomArray(10); // Generate an array of 10 random elements

    std::cout << "Original Array (10 elements): ";
    DisplayArray(arr); // Display the original array

    SortFunction(arr, arr.size()); // Sort the array

    std::cout << "Sorted Array (10 elements): ";
    DisplayArray(arr); // Display the sorted array

    // Check if the array is sorted and print the result
    if (IsSorted(arr)) {
        std::cout << "Array is sorted!" << std::endl;
    } else {
        std::cout << "Array is not sorted!" << std::endl;
    }
}

/**
 * The main function where the sorting algorithms are benchmarked with varying array sizes.
 */
int main() {
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000}; // Added 1,000,000 size for benchmark

    // Loop through different array sizes for benchmarking
    for (int size : sizes) {
        std::cout << "\nBenchmarking for array size: " << size << std::endl;
        std::vector<int> arr = GenerateRandomArray(size); // Generate a random array of the specified size

        // Benchmark Bubble Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            BenchmarkSort("Bubble Sort", sorting_algorithms::BubbleSort, arr);
        }

        // Benchmark Selection Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            BenchmarkSort("Selection Sort", sorting_algorithms::SelectionSort, arr);
        }

        // Benchmark Insertion Sort (limit to smaller arrays due to its O(n^2) time complexity)
        if (size <= 10000) {
            BenchmarkSort("Insertion Sort", sorting_algorithms::InsertionSort, arr);
        }

        // Benchmark Merge Sort (can handle larger arrays efficiently)
        BenchmarkSort("Merge Sort", [](std::vector<int>& arr, int n) { sorting_algorithms::MergeSort(arr, 0, n - 1); }, arr);

        // Benchmark Heap Sort (can handle larger arrays efficiently)
        BenchmarkSort("Heap Sort", sorting_algorithms::HeapSort, arr);

        // Benchmark Quick Sort (can handle larger arrays efficiently)
        BenchmarkSort("Quick Sort", [](std::vector<int>& arr, int n) { sorting_algorithms::QuickSort(arr, 0, n - 1); }, arr);

        // Benchmark Bucket Sort (can handle larger arrays efficiently)
        BenchmarkSort("Bucket Sort", sorting_algorithms::BucketSort, arr);

        // Benchmark 3-Way Quick Sort (optimized for large arrays with duplicates)
        BenchmarkSort("3-Way Quick Sort combined with insertion", [](std::vector<int>& arr, int n) { sorting_algorithms::QuickSortWithInsertion(arr, 0, n - 1); }, arr);

        // Benchmark Timsort
        BenchmarkSort("Merge Sort combined with insertion", [](std::vector<int>& arr, int n) { sorting_algorithms::MergeSortWithInsertion(arr, n); }, arr);
    }

    // Demonstrate sorting with 10 elements using various algorithms
    std::cout << "\nDemonstrating sorting with 10 elements:" << std::endl;
    DemonstrateSortingWith10Elements(sorting_algorithms::BubbleSort);
    DemonstrateSortingWith10Elements(sorting_algorithms::SelectionSort);
    DemonstrateSortingWith10Elements(sorting_algorithms::InsertionSort);
    DemonstrateSortingWith10Elements(sorting_algorithms::HeapSort);
    DemonstrateSortingWith10Elements([](std::vector<int>& arr, int n){ sorting_algorithms::MergeSort(arr, 0, n-1); });
    DemonstrateSortingWith10Elements([](std::vector<int>& arr, int n){ sorting_algorithms::QuickSort(arr, 0, n-1); });
    DemonstrateSortingWith10Elements(sorting_algorithms::BucketSort);
    DemonstrateSortingWith10Elements([](std::vector<int>& arr, int n){ sorting_algorithms::QuickSortWithInsertion(arr, 0, n-1); });
    DemonstrateSortingWith10Elements([](std::vector<int>& arr, int n){ sorting_algorithms::MergeSortWithInsertion(arr, n); });

    return 0;
}
