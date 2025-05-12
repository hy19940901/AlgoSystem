#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <iostream>

/**
 * @class ListNode
 * @brief This class represents a node in the linked list.
 *
 * A ListNode object stores an integer data value and a pointer to the next node
 * in the list. This class is used as the basic element in the LinkedList class.
 */
class ListNode {
public:
    int data;               ///< The data stored in the node.
    ListNode* next;         ///< Pointer to the next node in the list.

    /**
     * @brief Constructs a ListNode with a given value.
     *
     * This constructor initializes a node with the provided data value
     * and sets the next pointer to nullptr.
     *
     * @param val The integer value to be stored in the node.
     */
    ListNode(int val);

    /**
     * @brief Constructs a ListNode with a given value and next node pointer.
     *
     * This constructor initializes a node with the provided data value
     * and sets the next pointer to point to the provided next node.
     *
     * @param x The integer value to be stored in the node.
     * @param nextNode The pointer to the next node in the list.
     */
    ListNode(int x, ListNode* next_node);
};

/**
 * @class LinkedList
 * @brief This class implements a singly linked list.
 *
 * The LinkedList class provides a variety of methods to manipulate a singly linked list,
 * including adding, removing, updating, searching, and sorting elements. The list consists 
 * of ListNode objects, each storing an integer value and a pointer to the next node.
 */
class LinkedList {
private:
    ListNode* head_;  ///< Pointer to the first node (head) of the linked list.
    bool quick_sort_debug_; ///< Controls whether quicksort debug mode is enabled.

public:
    /**
     * @brief Constructs an empty LinkedList.
     *
     * Initializes the list with no elements (head is set to nullptr).
     */
    LinkedList();

    /**
     * @brief Destructor that deallocates the memory used by the list.
     *
     * This destructor ensures that all nodes in the list are deleted,
     * preventing memory leaks.
     */
    ~LinkedList();

    /**
     * @brief Gets the head node of the linked list.
     *
     * This function is useful for accessing the start of the list,
     * typically for iteration or copying purposes.
     *
     * @return ListNode* Pointer to the head node of the list.
     */
    ListNode* GetHead() const;

    /**
     * @brief Gets the tail node of the linked list.
     *
     * This function traverses the list and returns the last node.
     *
     * @param head The starting node of the list.
     * @return ListNode* Pointer to the tail node of the list.
     */
    ListNode* GetTail(ListNode* head);

    /**
     * @brief Adds a new node with a given value to the end of the list.
     *
     * This method traverses the list to the last node and appends
     * a new node containing the specified value.
     *
     * @param val The integer value to append to the list.
     */
    void Append(int val); // lc 21

    /**
     * @brief Adds a new node with a given value to the start of the list.
     *
     * This method inserts a new node at the beginning of the list,
     * making the new node the head of the list.
     *
     * @param val The integer value to prepend to the list.
     */
    void Prepend(int val);

    /**
     * @brief Inserts a new node with a given value at a specified position.
     *
     * This method inserts a node at a given 0-based index in the list.
     * If the index is 0, the node is inserted at the head.
     *
     * @param val The integer value to insert into the list.
     * @param position The 0-based index where the node should be inserted.
     * @throws std::out_of_range If the position is out of bounds of the list size.
     */
    void Insert(int val, int position);

    /**
     * @brief Removes the first node that contains a specific value.
     *
     * This method traverses the list, finds the first occurrence of the node
     * with the specified value, and removes it from the list.
     *
     * @param val The integer value to remove from the list.
     */
    void Remove(int val); // lc 203

    /**
     * @brief Checks if a given value exists in the list.
     *
     * This method traverses the list and returns `true` if the value
     * is found in any node. Otherwise, it returns `false`.
     *
     * @param val The integer value to search for in the list.
     * @return true If the value is found in the list.
     * @return false If the value is not found in the list.
     */
    bool Contains(int val) const;

    /**
     * @brief Updates the first occurrence of a value in the list.
     *
     * This method traverses the list and updates the first node
     * that contains the specified `oldVal` to the new value `newVal`.
     *
     * @param old_val The value to be updated.
     * @param new_val The new value to replace `oldVal`.
     * @return true If the update was successful (i.e., `oldVal` was found).
     * @return false If the update was unsuccessful (i.e., `oldVal` was not found).
     */
    bool Update(int old_val, int new_val);

    /**
     * @brief Displays all the values in the linked list.
     *
     * This method traverses the list and prints the data values
     * of all the nodes in the list, in order from head to tail.
     *
     * @param limit The maximum number of nodes to display (optional).
     */
    void Display(int limit = -1);

    /**
     * @brief Reverses the order of nodes in the linked list.
     *
     * This method reverses the list in place by reversing the
     * next pointers of the nodes, so that the last node becomes the head.
     */
    void Reverse(); //lc206

    /**
     * @brief Enables quick sort debug mode.
     *
     * This method enables debug mode for quick sort,
     * which allows step-by-step visualization of the sorting process.
     */
    void EnableQuickSortDebug();

    /**
     * @brief Disables quick sort debug mode (optional).
     *
     * This method disables quick sort debug mode.
     */
    void DisableQuickSortDebug();

    /**
     * @brief Sorts the linked list using a specified sorting method.
     *
     * This method sorts the linked list using either "merge" or "quick" sort.
     *
     * @param method The sorting method to use ("merge" or "quick").
     */
    void Sort(const std::string& method);

    /**
     * @brief Checks if the linked list is sorted in non-decreasing order.
     *
     * This method traverses the list and checks if each node's value is
     * less than or equal to the next node's value.
     *
     * @return true If the list is sorted, false otherwise.
     */
    bool IsSorted() const;

private:
    /**
     * @brief Quick sort helper function for sorting the list.
     *
     * This function implements the quick sort algorithm for the linked list.
     * It recursively sorts the list between head and tail nodes.
     *
     * @return ListNode* Pointer to the new head of the sorted list.
     */
    ListNode* QuickSort();

    /**
     * @brief Partition function used by quick sort.
     *
     * This function partitions the list into two parts, where nodes smaller
     * than the pivot go to the left, and nodes greater than or equal to the
     * pivot go to the right.
     *
     * @param head The starting node of the partition.
     * @param tail The ending node of the partition.
     */
    void Partition(ListNode* head, ListNode* tail);

    /**
     * @brief Merge sort helper function for sorting the list.
     *
     * This function implements the merge sort algorithm for the linked list.
     * It recursively splits and merges the list to sort it.
     *
     * @param head The head of the list to be sorted.
     * @return ListNode* Pointer to the new head of the sorted list.
     */
    ListNode* MergeSort(ListNode* head); // lc 148

    /**
     * @brief Helper function to find the middle of the list.
     *
     * This method uses the slow-fast pointer technique to find the middle node
     * of the list for use in merge sort.
     *
     * @param head The starting node of the list.
     * @return ListNode* Pointer to the middle node of the list.
     */
    ListNode* GetMiddle(ListNode* head); // lc 876

    /**
     * @brief Merges two sorted lists into one.
     *
     * This function merges two sorted sublists into one sorted list,
     * and is used by the merge sort algorithm.
     *
     * @param left The head of the first sorted sublist.
     * @param right The head of the second sorted sublist.
     * @return ListNode* Pointer to the head of the merged sorted list.
     */
    ListNode* Merge(ListNode* left, ListNode* right); // lc 21
};

#endif
