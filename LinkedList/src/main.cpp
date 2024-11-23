#include "../include/LinkedList.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Creates a copy of the provided linked list
LinkedList createCopy(const LinkedList &original) {
    LinkedList copy;
    ListNode *current = original.getHead();
    while (current != nullptr) {
        copy.append(current->data);
        current = current->next;
    }
    return copy;
}

// Benchmarking the append operation for a given number of elements
void benchmarkAppend(LinkedList &list, int numElements) {
    cout << "\nStarting append benchmark for " << numElements << " elements..." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i) {
        int value = rand() % 100;
        if (numElements == 10 && i < 10) {  // Only print for numElements == 10
            cout << "Appending value: " << value << endl;
        }
        list.append(value);  // Appending random data
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);  // Corrected usage
    cout << "Time taken to append " << numElements << " elements: " << duration.count() << " seconds" << endl;
    cout << "Append operation completed." << endl;

    if (numElements == 10) {
        cout << "Original Linked List after appending " << numElements << " elements:" << endl;
        list.display();  // Print full list when numElements == 10
    }
}

// Benchmarking the remove operation for a subset of elements
void benchmarkRemove(LinkedList &list, int numElements) {
    cout << "\nStarting remove benchmark for " << numElements / 10 << " elements..." << endl;

    // Create a copy of the original list for testing remove operation
    LinkedList copy = createCopy(list);

    if (numElements == 10) {
        // Display the copy of the list before any removal if numElements == 10
        cout << "Original Linked List (Copy) before removal:" << endl;
        copy.display();  // Display the original list (copy) before removals
    }

    auto start = high_resolution_clock::now();

    // Loop to remove elements from the copy
    for (int i = 0; i < numElements / 10; ++i) {
        int value = rand() % 100;  // Generate a random value to remove

        if (numElements == 10 && i < 10) {
            cout << "Attempting to remove value: " << value << " from the copy" << endl;
        }

        // Check if the value is in the list before attempting to remove
        if (copy.contains(value)) {
            // Perform removal from the copy
            copy.remove(value);
            if (numElements == 10) {
                cout << "Successfully removed value: " << value << endl;
                cout << "Linked List (Copy) after removing " << value << ":" << endl;
                copy.display();
            }
        } else {
            if (numElements == 10) {
                cout << "Value " << value << " not found in the copy, removal failed." << endl;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to remove " << numElements / 10 << " elements from the copy: " << duration.count() << " seconds" << endl;
    cout << "Remove operation completed on the copy." << endl;

}

// Benchmarking the search operation for a subset of elements
void benchmarkSearch(const LinkedList &list, int numElements) {
    cout << "\nStarting search benchmark for " << numElements / 10 << " elements..." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements / 10; ++i) {
        int value = rand() % 100;
        bool found = list.contains(value);
        if (numElements == 10 && i < 10) {  // Only print for numElements == 10
            cout << "Searching for value: " << value << ". Found: " << (found ? "Yes" : "No") << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to search " << numElements / 10 << " elements: " << duration.count() << " seconds" << endl;
    cout << "Search operation completed." << endl;
}

// Benchmarking the update operation for a subset of elements
void benchmarkUpdate(LinkedList &list, int numElements) {
    cout << "\nStarting update benchmark for " << numElements / 10 << " elements..." << endl;
    LinkedList copy = createCopy(list);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements / 10; ++i) {
        int oldVal = rand() % 100;
        int newVal = rand() % 100;
        if (numElements == 10 && i < 10) {  // Only print for numElements == 10
            cout << "Updating value " << oldVal << " to " << newVal << endl;
        }
        copy.update(oldVal, newVal);  // Updating random elements
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to update " << numElements / 10 << " elements: " << duration.count() << " seconds" << endl;
    cout << "Update operation completed." << endl;
}

// Benchmarking the reverse operation
void benchmarkReverse(LinkedList &list, int numElements) {
    cout << "\nStarting reverse benchmark for list of " << numElements << " elements..." << endl;
    LinkedList copy = createCopy(list);
    auto start = high_resolution_clock::now();
    copy.reverse();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "Time taken to reverse list of " << numElements << " elements: " << duration.count() << " seconds" << endl;
    cout << "Reverse operation completed." << endl;

    if (numElements == 10) {
        cout << "Reversed Linked List:" << endl;
        copy.display();  // Print full reversed list when numElements == 10
    }
}

// Benchmarking the sort operation
void benchmarkSort(LinkedList &list, int numElements) {
    cout << "\nStarting merge sort benchmark for list of " << numElements << " elements..." << endl;
    
    // Create a copy of the list to sort using merge sort
    LinkedList mergeCopy = createCopy(list);
    
    // Measure merge sort time
    auto startMerge = high_resolution_clock::now();
    mergeCopy.sort("merge");
    auto stopMerge = high_resolution_clock::now();
    auto mergeDuration = duration_cast<std::chrono::duration<double>>(stopMerge - startMerge);
    cout << "Time taken to merge sort list of " << numElements << " elements: " << mergeDuration.count() << " seconds" << endl;

    // Check if merge sorted list is correct
    if (mergeCopy.isSorted()) {
        cout << "The list is sorted correctly using merge sort." << endl;
    } else {
        cout << "The list is NOT sorted correctly using merge sort." << endl;
    }

    if (numElements == 10) {
        cout << "Sorted Linked List (Merge Sort):" << endl;
        mergeCopy.display();  // Print full sorted list for merge sort
    }

    cout << "\nStarting quick sort benchmark for list of " << numElements << " elements..." << endl;

    // Create another copy of the list to sort using quick sort
    LinkedList quickCopy = createCopy(list);
    
    // If elements are 10, track quick sort steps
    if (numElements == 10) {
        cout << "Quick sort step-by-step (for 10 elements):" << endl;
        quickCopy.enableQuickSortDebug();  // Enable debug mode for quick sort
    }
    
    // Measure quick sort time
    auto startQuick = high_resolution_clock::now();
    quickCopy.sort("quick");
    auto stopQuick = high_resolution_clock::now();
    auto quickDuration = duration_cast<std::chrono::duration<double>>(stopQuick - startQuick);
    cout << "Time taken to quick sort list of " << numElements << " elements: " << quickDuration.count() << " seconds" << endl;

    // Check if quick sorted list is correct
    if (quickCopy.isSorted()) {
        cout << "The list is sorted correctly using quick sort." << endl;
    } else {
        cout << "The list is NOT sorted correctly using quick sort." << endl;
    }

    if (numElements == 10) {
        cout << "Sorted Linked List (Quick Sort):" << endl;
        quickCopy.display();  // Print full sorted list for quick sort
    }
}

// Function to run benchmarks for different numbers of elements
void runBenchmark(int numElements) {
    cout << "\n=====================================================" << endl;
    cout << "Benchmark for " << numElements << " elements:" << endl;
    cout << "=====================================================" << endl;

    LinkedList list;

    // Append data to the list
    benchmarkAppend(list, numElements);  // Insert data

    // Test reverse operation
    benchmarkReverse(list, numElements); // Reverse data

    // Test remove operation
    benchmarkRemove(list, numElements);  // Remove some elements

    // Test search operation
    benchmarkSearch(list, numElements);  // Search for some elements

    // Test update operation
    benchmarkUpdate(list, numElements);  // Update some elements

    // Test sorting operation
    benchmarkSort(list, numElements);    // Sort data

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
