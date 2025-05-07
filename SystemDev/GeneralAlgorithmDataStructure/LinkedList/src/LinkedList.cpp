#include "../include/LinkedList.h"

using namespace std;

// --- ListNode Implementation ---

ListNode::ListNode(int val) {
    data = val;
    next = nullptr;
}

// --- LinkedList Implementation ---

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

ListNode* LinkedList::getHead() const {
    return head;
}

ListNode* LinkedList::getTail(ListNode* head) {
    if (!head) return nullptr;

    while (head->next != nullptr) {
        head = head->next;
    }

    return head;
}

void LinkedList::append(int val) {
    ListNode* newNode = new ListNode(val);
    if (!head) {
        head = newNode;
    } else {
        ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::prepend(int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    head = newNode;
}

void LinkedList::insert(int val, int position) {
    ListNode* newNode = new ListNode(val);
    if (position == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    ListNode* temp = head;
    for (int i = 0; temp != nullptr && i < position - 1; i++) {
        temp = temp->next;
    }
    if (!temp) {
        std::cout << "Position out of bounds" << std::endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void LinkedList::remove(int val) {
    if (!head) return;

    if (head->data == val) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr && curr->data != val) {
        prev = curr;
        curr = curr->next;
    }

    if (curr) {
        prev->next = curr->next;
        delete curr;
    }
}

bool LinkedList::contains(int val) const {
    ListNode* temp = head;
    while (temp) {
        if (temp->data == val) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool LinkedList::update(int oldVal, int newVal) {
    ListNode* temp = head;
    while (temp) {
        if (temp->data == oldVal) {
            temp->data = newVal;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void LinkedList::display(int limit) {
    ListNode *current = head;
    int count = 0;
    while (current != nullptr && (limit == -1 || count < limit)) {
        std::cout << current->data << " ";
        current = current->next;
        ++count;
    }
    std::cout << std::endl;
}

void LinkedList::reverse() {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* pre = dummy, *cur = head;

    while (cur && cur->next) {
        ListNode* tmp = pre->next;
        pre->next = cur->next;
        cur->next = cur->next->next;
        pre->next->next = tmp;
    }

    head = dummy->next;
    delete dummy;
}

void LinkedList::enableQuickSortDebug() {
    quickSortDebug = true;
}

void LinkedList::disableQuickSortDebug() {
    quickSortDebug = false;
}

// Helper function to find the middle of the list
ListNode* LinkedList::getMiddle(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // slow is now pointing to the middle node
}

// Helper function to merge two sorted lists
ListNode* LinkedList::merge(ListNode* left, ListNode* right) {
    // If one of the lists is empty, return the other
    if (!left) return right;
    if (!right) return left;

    // Choose the smaller node and recursively merge the rest
    if (left->data <= right->data) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Merge sort function to sort the linked list
ListNode* LinkedList::mergeSort(ListNode* head) {
    // Base case: if head is null or only one element, return
    if (!head || !head->next) {
        return head;
    }

    // Step 1: Split the list into two halves
    ListNode* middle = getMiddle(head);
    ListNode* secondHalf = middle->next;
    middle->next = nullptr;  // Break the link between the two halves

    // Step 2: Recursively sort both halves
    ListNode* left = mergeSort(head);
    ListNode* right = mergeSort(secondHalf);

    // Step 3: Merge the sorted halves
    return merge(left, right);
}

void LinkedList::sort(const std::string& method) {
    if (!head || !head->next) return;

    if (method == "merge") {
        // use mergeSort
        head = mergeSort(head);
        std::cout << "Sorted using Merge Sort." << std::endl;
    } else if (method == "quick") {
        // use quickSort
        head = quickSort();
        std::cout << "Sorted using Quick Sort." << std::endl;
    } else {
        std::cout << "Invalid sorting method. Please choose 'merge' or 'quick'." << std::endl;
    }
}

ListNode* LinkedList::quickSort() {
    partition(head, nullptr);
    return head;
}

void LinkedList::partition(ListNode* head, ListNode* tail) {
    if (head == tail || head->next == tail) return;

    ListNode* slow = head;
    ListNode* fast = head;
    int pivot = head->data;

    while (fast != tail) {
        if (fast->data < pivot) {
            slow = slow->next;
            int tmp = slow->data;
            slow->data = fast->data;
            fast->data = tmp;
        }
        fast = fast->next;
    }

    head->data = slow->data;
    slow->data = pivot;

    partition(head, slow);
    partition(slow->next, tail);
}

bool LinkedList::isSorted() const {
    ListNode* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->data > current->next->data) {
            return false;  // List is not sorted
        }
        current = current->next;
    }
    return true;  // List is sorted
}