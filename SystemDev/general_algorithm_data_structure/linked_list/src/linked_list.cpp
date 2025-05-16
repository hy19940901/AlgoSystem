#include "../include/linked_list.h"

using namespace std;

// --- ListNode Implementation ---

ListNode::ListNode(int val) {
    data = val;
    next = nullptr;
}

// --- LinkedList Implementation ---

LinkedList::LinkedList() {
    head_ = nullptr;
}

LinkedList::~LinkedList() {
    while (head_) {
        ListNode* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

ListNode* LinkedList::GetHead() const {
    return head_;
}

ListNode* LinkedList::GetTail(ListNode* head) {
    if (!head) return nullptr;

    while (head->next != nullptr) {
        head = head->next;
    }

    return head;
}

void LinkedList::Append(int val) {
    ListNode* new_node = new ListNode(val);
    if (!head_) {
        head_ = new_node;
    } else {
        ListNode* temp = head_;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void LinkedList::Prepend(int val) {
    ListNode* new_node = new ListNode(val);
    new_node->next = head_;
    head_ = new_node;
}

void LinkedList::Insert(int val, int position) {
    ListNode* new_node = new ListNode(val);
    if (position == 0) {
        new_node->next = head_;
        head_ = new_node;
        return;
    }

    ListNode* temp = head_;
    for (int i = 0; temp != nullptr && i < position - 1; i++) {
        temp = temp->next;
    }
    if (!temp) {
        std::cout << "Position out of bounds" << std::endl;
        delete new_node;
        return;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

void LinkedList::Remove(int val) {
    if (!head_) return;

    if (head_->data == val) {
        ListNode* temp = head_;
        head_ = head_->next;
        delete temp;
        return;
    }

    ListNode* prev = nullptr;
    ListNode* curr = head_;

    while (curr && curr->data != val) {
        prev = curr;
        curr = curr->next;
    }

    if (curr) {
        prev->next = curr->next;
        delete curr;
    }
}

bool LinkedList::Contains(int val) const {
    ListNode* temp = head_;
    while (temp) {
        if (temp->data == val) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool LinkedList::Update(int old_val, int new_val) {
    ListNode* temp = head_;
    while (temp) {
        if (temp->data == old_val) {
            temp->data = new_val;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void LinkedList::Display(int limit) {
    ListNode *current = head_;
    int count = 0;
    while (current != nullptr && (limit == -1 || count < limit)) {
        std::cout << current->data << " ";
        current = current->next;
        ++count;
    }
    std::cout << std::endl;
}

void LinkedList::Reverse() {
    ListNode* dummy = new ListNode(0);
    dummy->next = head_;
    ListNode* pre = dummy, *cur = head_;

    while (cur && cur->next) {
        ListNode* tmp = pre->next;
        pre->next = cur->next;
        cur->next = cur->next->next;
        pre->next->next = tmp;
    }

    head_ = dummy->next;
    delete dummy;
}

void LinkedList::EnableQuickSortDebug() {
    quick_sort_debug_ = true;
}

void LinkedList::DisableQuickSortDebug() {
    quick_sort_debug_ = false;
}

// Helper function to find the middle of the list
ListNode* LinkedList::GetMiddle(ListNode* head) {
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
ListNode* LinkedList::Merge(ListNode* left, ListNode* right) {
    // If one of the lists is empty, return the other
    if (!left) return right;
    if (!right) return left;

    // Choose the smaller node and recursively merge the rest
    if (left->data <= right->data) {
        left->next = Merge(left->next, right);
        return left;
    } else {
        right->next = Merge(left, right->next);
        return right;
    }
}

// Merge sort function to sort the linked list
ListNode* LinkedList::MergeSort(ListNode* head) {
    // Base case: if head is null or only one element, return
    if (!head || !head->next) {
        return head;
    }

    // Step 1: Split the list into two halves
    ListNode* middle = GetMiddle(head);
    ListNode* second_half = middle->next;
    middle->next = nullptr;  // Break the link between the two halves

    // Step 2: Recursively sort both halves
    ListNode* left = MergeSort(head);
    ListNode* right = MergeSort(second_half);

    // Step 3: Merge the sorted halves
    return Merge(left, right);
}

void LinkedList::Sort(const std::string& method) {
    if (!head_ || !head_->next) return;

    if (method == "merge") {
        // use mergeSort
        head_ = MergeSort(head_);
        std::cout << "Sorted using Merge Sort." << std::endl;
    } else if (method == "quick") {
        // use quickSort
        head_ = QuickSort();
        std::cout << "Sorted using Quick Sort." << std::endl;
    } else {
        std::cout << "Invalid sorting method. Please choose 'merge' or 'quick'." << std::endl;
    }
}

ListNode* LinkedList::QuickSort() {
    Partition(head_, nullptr);
    return head_;
}

void LinkedList::Partition(ListNode* head, ListNode* tail) {
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

    Partition(head, slow);
    Partition(slow->next, tail);
}

bool LinkedList::IsSorted() const {
    ListNode* current = head_;
    while (current != nullptr && current->next != nullptr) {
        if (current->data > current->next->data) {
            return false;  // List is not sorted
        }
        current = current->next;
    }
    return true;  // List is sorted
}