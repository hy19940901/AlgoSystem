#include "../include/linked_list.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Creates a copy of the provided linked list
LinkedList CreateCopy(const LinkedList &original) {
    LinkedList copy;
    ListNode *current = original.GetHead();
    while (current != nullptr) {
        copy.Append(current->data);
        current = current->next;
    }
    return copy;
}

// Benchmarking the append operation for a given number of elements
void BenchmarkAppend(LinkedList &list, int num_elements) {
    cout << "\nStarting append benchmark for " << num_elements << " elements..." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        int value = rand() % 100;
        if (num_elements == 10 && i < 10) {  // Only print for num_elements == 10
            cout << "Appending value: " << value << endl;
        }
        list.Append(value);  // Appending random data
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);  // Corrected usage
    cout << "Time taken to append " << num_elements << " elements: " << duration.count() << " seconds" << endl;
    cout << "Append operation completed." << endl;

    if (num_elements == 10) {
        cout << "Original Linked List after appending " << num_elements << " elements:" << endl;
        list.Display();  // Print full list when num_elements == 10
    }
}

// Benchmarking the remove operation for a subset of elements
void BenchmarkRemove(LinkedList &list, int num_elements) {
    cout << "\nStarting remove benchmark for " << num_elements / 10 << " elements..." << endl;

    // Create a copy of the original list for testing remove operation
    LinkedList copy = CreateCopy(list);

    if (num_elements == 10) {
        // Display the copy of the list before any removal if num_elements == 10
        cout << "Original Linked List (Copy) before removal:" << endl;
        copy.Display();  // Display the original list (copy) before removals
    }

    auto start = high_resolution_clock::now();

    // Loop to remove elements from the copy
    for (int i = 0; i < num_elements / 10; ++i) {
        int value = rand() % 100;  // Generate a random value to remove

        if (num_elements == 10 && i < 10) {
            cout << "Attempting to remove value: " << value << " from the copy" << endl;
        }

        // Check if the value is in the list before attempting to remove
        if (copy.Contains(value)) {
            // Perform removal from the copy
            copy.Remove(value);
            if (num_elements == 10) {
                cout << "Successfully removed value: " << value << endl;
                cout << "Linked List (Copy) after removing " << value << ":" << endl;
                copy.Display();
            }
        } else {
            if (num_elements == 10) {
                cout << "Value " << value << " not found in the copy, removal failed." << endl;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to remove " << num_elements / 10 << " elements from the copy: " << duration.count() << " seconds" << endl;
    cout << "Remove operation completed on the copy." << endl;

}

// Benchmarking the search operation for a subset of elements
void BenchmarkSearch(const LinkedList &list, int num_elements) {
    cout << "\nStarting search benchmark for " << num_elements / 10 << " elements..." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num_elements / 10; ++i) {
        int value = rand() % 100;
        bool found = list.Contains(value);
        if (num_elements == 10 && i < 10) {  // Only print for num_elements == 10
            cout << "Searching for value: " << value << ". Found: " << (found ? "Yes" : "No") << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to search " << num_elements / 10 << " elements: " << duration.count() << " seconds" << endl;
    cout << "Search operation completed." << endl;
}

// Benchmarking the update operation for a subset of elements
void BenchmarkUpdate(LinkedList &list, int num_elements) {
    cout << "\nStarting update benchmark for " << num_elements / 10 << " elements..." << endl;
    LinkedList copy = CreateCopy(list);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num_elements / 10; ++i) {
        int old_val = rand() % 100;
        int new_val = rand() % 100;
        if (num_elements == 10 && i < 10) {  // Only print for num_elements == 10
            cout << "Updating value " << old_val << " to " << new_val << endl;
        }
        copy.Update(old_val, new_val);  // Updating random elements
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to update " << num_elements / 10 << " elements: " << duration.count() << " seconds" << endl;
    cout << "Update operation completed." << endl;
}

// Benchmarking the reverse operation
void BenchmarkReverse(LinkedList &list, int num_elements) {
    cout << "\nStarting reverse benchmark for list of " << num_elements << " elements..." << endl;
    LinkedList copy = CreateCopy(list);
    auto start = high_resolution_clock::now();
    copy.Reverse();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to reverse list of " << num_elements << " elements: " << duration.count() << " seconds" << endl;
    cout << "Reverse operation completed." << endl;

    if (num_elements == 10) {
        cout << "Reversed Linked List:" << endl;
        copy.Display();  // Print full reversed list when num_elements == 10
    }
}

// Benchmarking the sort operation
void BenchmarkSort(LinkedList &list, int num_elements) {
    cout << "\nStarting merge sort benchmark for list of " << num_elements << " elements..." << endl;

    // Create a copy of the list to sort using merge sort
    LinkedList mergeCopy = CreateCopy(list);

    // Measure merge sort time
    auto startMerge = high_resolution_clock::now();
    mergeCopy.Sort("merge");
    auto stopMerge = high_resolution_clock::now();
    auto mergeDuration = duration_cast<std::chrono::duration<double>>(stopMerge - startMerge);
    cout << "Time taken to merge sort list of " << num_elements << " elements: " << mergeDuration.count() << " seconds" << endl;

    // Check if merge sorted list is correct
    if (mergeCopy.IsSorted()) {
        cout << "The list is sorted correctly using merge sort." << endl;
    } else {
        cout << "The list is NOT sorted correctly using merge sort." << endl;
    }

    if (num_elements == 10) {
        cout << "Sorted Linked List (Merge Sort):" << endl;
        mergeCopy.Display();  // Print full sorted list for merge sort
    }

    cout << "\nStarting quick sort benchmark for list of " << num_elements << " elements..." << endl;

    // Create another copy of the list to sort using quick sort
    LinkedList quickCopy = CreateCopy(list);

    // If elements are 10, track quick sort steps
    if (num_elements == 10) {
        cout << "Quick sort step-by-step (for 10 elements):" << endl;
        quickCopy.EnableQuickSortDebug();  // Enable debug mode for quick sort
    }

    // Measure quick sort time
    auto startQuick = high_resolution_clock::now();
    quickCopy.Sort("quick");
    auto stopQuick = high_resolution_clock::now();
    auto quickDuration = duration_cast<std::chrono::duration<double>>(stopQuick - startQuick);
    cout << "Time taken to quick sort list of " << num_elements << " elements: " << quickDuration.count() << " seconds" << endl;

    // Check if quick sorted list is correct
    if (quickCopy.IsSorted()) {
        cout << "The list is sorted correctly using quick sort." << endl;
    } else {
        cout << "The list is NOT sorted correctly using quick sort." << endl;
    }

    if (num_elements == 10) {
        cout << "Sorted Linked List (Quick Sort):" << endl;
        quickCopy.Display();  // Print full sorted list for quick sort
    }
}

// Function to run benchmarks for different numbers of elements
void runBenchmark(int num_elements) {
    cout << "\n=====================================================" << endl;
    cout << "Benchmark for " << num_elements << " elements:" << endl;
    cout << "=====================================================" << endl;

    LinkedList list;

    // Append data to the list
    BenchmarkAppend(list, num_elements);  // Insert data

    // Test reverse operation
    BenchmarkReverse(list, num_elements); // Reverse data

    // Test remove operation
    BenchmarkRemove(list, num_elements);  // Remove some elements

    // Test search operation
    BenchmarkSearch(list, num_elements);  // Search for some elements

    // Test update operation
    BenchmarkUpdate(list, num_elements);  // Update some elements

    // Test sorting operation
    BenchmarkSort(list, num_elements);    // Sort data

    cout << "=====================================================\n" << endl;
}

int main() {
    srand(time(0));  // Initialize random seed

    // Define the different sizes for benchmarking
    int sizes[] = {10, 100, 1000, 10000, 100000};

    // Loop over the different sizes and run benchmarks
    for (int size : sizes) {
        runBenchmark(size);  // Run benchmark for each size
    }

    return 0;
}
