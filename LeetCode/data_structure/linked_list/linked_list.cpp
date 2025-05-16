#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <functional>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};

/**
 * Problem 1: Reverse Linked List (LC 206)
 * Description:
 * Given the head of a singly linked list, reverse the list and return its head.
 * Example:
 * Input: head = [1, 2, 3, 4, 5]
 * Output: [5, 4, 3, 2, 1]
 */
ListNode* ReverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

/**
 * Problem 2: Merge Two Sorted Lists (LC 21)
 * Description:
 * You are given the heads of two sorted linked lists. Merge the two lists into one
 * sorted list in ascending order and return its head.
 * Example:
 * Input: l1 = [1, 2, 4], l2 = [1, 3, 4]
 * Output: [1, 1, 2, 3, 4, 4]
 */
ListNode* MergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    ListNode* dummy = new ListNode(0);
    dummy->next = nullptr;
    ListNode* cur = dummy, *cur1 = list1, *cur2 = list2;
    while (cur1 && cur2) {
        if (cur1->val <= cur2->val) {
            cur->next = cur1;
            cur1 = cur1->next;
        }
        else {
            cur->next = cur2;
            cur2 = cur2->next;
        }
        cur = cur->next;
    }
    if (!cur1) cur->next = cur2;
    if (!cur2) cur->next = cur1;
    return dummy->next;
}

/**
 * Problem 3: Detect Cycle in Linked List (LC 141)
 * Description:
 * Given the head of a linked list, determine if the linked list has a cycle in it.
 * A cycle occurs when a node’s next pointer points back to a previous node.
 * Example:
 * Input: head = [3, 2, 0, -4] (cycle at node with value 2)
 * Output: true
 */
bool HasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

/**
 * Problem 4: Remove Nth Node From End of List (LC 19)
 * Description:
 * Given the head of a linked list, remove the nth node from the end of the list and return its head.
 * Example:
 * Input: head = [1, 2, 3, 4, 5], n = 2
 * Output: [1, 2, 3, 5]
 */
ListNode* RemoveNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    for (int i = 0; i <= n; ++i) {
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;
    return dummy.next;
}

/**
 * Problem 5: Intersection of Two Linked Lists (LC 160)
 * Description:
 * Given the heads of two singly linked lists, find the node at which the two lists intersect.
 * If no intersection exists, return null.
 * Example:
 * Input: intersectVal = 8, listA = [4, 1, 8, 4, 5], listB = [5, 6, 1, 8, 4, 5]
 * Output: Intersection at node with value 8
 */
ListNode* GetIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    ListNode* a = headA;
    ListNode* b = headB;
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

/**
 * Problem 6: Palindrome Linked List (LC 234)
 * Description:
 * Given the head of a singly linked list, determine if it is a palindrome.
 * Example:
 * Input: head = [1, 2, 2, 1]
 * Output: true
 */
bool IsPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* second_half = ReverseList(slow);
    ListNode* first_half = head;
    while (second_half) {
        if (first_half->val != second_half->val) return false;
        first_half = first_half->next;
        second_half = second_half->next;
    }
    return true;
}

bool IsPalindrome_stack(ListNode* head) {
    stack<int> stack;
    ListNode* curr = head;
    while (curr) {
        stack.push(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr && curr->val == stack.top()) {
        stack.pop();
        curr = curr->next;
    }
    return curr == nullptr;
}

/**
 * Problem 7: Remove Linked List Elements (LC 203)
 * Description:
 * Remove all elements from a linked list of integers that have value val.
 * Example:
 * Input: head = [1, 2, 6, 3, 4, 5, 6], val = 6
 * Output: [1, 2, 3, 4, 5]
 */
ListNode* RemoveElements(ListNode* head, int val) {
    ListNode dummy(0, head);
    ListNode* pre = &dummy;
    while (pre->next) {
        if (pre->next->val == val) {
            ListNode* temp = pre->next;
            pre->next = pre->next->next;
            delete temp;
        } else {
            pre = pre->next;
        }
    }
    return dummy.next;
}

/**
 * Problem 8: Reverse Nodes in k-Group (LC 25)
 * Description:
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list. If the number of nodes is not a multiple of k,
 * leave the remaining nodes as is.
 * Example:
 * Input: head = [1, 2, 3, 4, 5], k = 2
 * Output: [2, 1, 4, 3, 5]
 */
ListNode* ReverseKGroup(ListNode* head, int k) {
    ListNode* curr = head;
    int count = 0;
    while (curr && count < k) {
        curr = curr->next;
        count++;
    }
    if (count == k) {
        curr = ReverseKGroup(curr, k);
        while (count--) {
            ListNode* next_temp = head->next;
            head->next = curr;
            curr = head;
            head = next_temp;
        }
        head = curr;
    }
    return head;
}

/**
 * Problem 9: Sort List (LC 148)
 * Description:
 * Given the head of a linked list, sort the list in ascending order
 * in O(n log n) time and constant space complexity.
 * Example:
 * Input: head = [4, 2, 1, 3]
 * Output: [1, 2, 3, 4]
 */
ListNode* Merge(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val < l2->val) {
        l1->next = Merge(l1->next, l2);
        return l1;
    } else {
        l2->next = Merge(l1, l2->next);
        return l2;
    }
}

ListNode* SortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* mid = slow->next;
    slow->next = nullptr;
    ListNode* left = SortList(head);
    ListNode* right = SortList(mid);
    return Merge(left, right);
}

/**
 * Problem 10: Rotate List (LC 61)
 * Description:
 * Given the head of a linked list, rotate the list to the right by k places.
 * Example:
 * Input: head = [1, 2, 3, 4, 5], k = 2
 * Output: [4, 5, 1, 2, 3]
 */
ListNode* RotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    ListNode* curr = head;
    int length = 1;
    while (curr->next) {
        curr = curr->next;
        length++;
    }
    curr->next = head; // Make it a circular list
    k = k % length;
    int steps_to_new_head = length - k;
    while (steps_to_new_head--) {
        curr = curr->next;
    }
    head = curr->next;
    curr->next = nullptr;
    return head;
}

/**
 * Problem 11: Partition List (LC 86)
 * Description:
 * Given the head of a linked list and a value x, partition the list such that all nodes
 * less than x come before nodes greater than or equal to x.
 * Example:
 * Input: head = [1, 4, 3, 2, 5, 2], x = 3
 * Output: [1, 2, 2, 4, 3, 5]
 */
ListNode* Partition(ListNode* head, int x) {
    ListNode* before = new ListNode(0);
    ListNode* after = new ListNode(0);
    ListNode* before_head = before;
    ListNode* after_head = after;
    while (head) {
        if (head->val < x) {
            before->next = head;
            before = before->next;
        } else {
            after->next = head;
            after = after->next;
        }
        head = head->next;
    }
    after->next = nullptr;
    before->next = after_head->next;
    return before_head->next;
}

/**
 * Problem 12: Copy List with Random Pointer (LC 138)
 * Description:
 * A linked list is given such that each node contains an additional random pointer
 * which could point to any node in the list or null. Return a deep copy of the list.
 * Example:
 * Input: head = [[7, null], [13, 0], [11, 4], [10, 2], [1, 0]]
 * Output: [[7, null], [13, 0], [11, 4], [10, 2], [1, 0]]
 */
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* CopyRandomList(Node* head) {
    if (!head) return nullptr;
    unordered_map<Node*, Node*> old_to_new;
    Node* curr = head;
    while (curr) {
        old_to_new[curr] = new Node(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr) {
        old_to_new[curr]->next = old_to_new[curr->next];
        old_to_new[curr]->random = old_to_new[curr->random];
        curr = curr->next;
    }
    return old_to_new[head];
}

/**
 * Problem 13: Add Two Numbers (LC 2)
 * Description:
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * Example:
 * Input: l1 = [2, 4, 3], l2 = [5, 6, 4]
 * Output: [7, 0, 8]
 */
ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }
    return dummy.next;
}

/**
 * Problem 14: Swap Nodes in Pairs (LC 24)
 * Description:
 * Given a linked list, swap every two adjacent nodes and return its head.
 * You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed).
 * Example:
 * Input: head = [1, 2, 3, 4]
 * Output: [2, 1, 4, 3]
 */
ListNode* SwapPairs(ListNode* head) {
    ListNode dummy(0, head);
    ListNode* curr = &dummy;
    while (curr->next && curr->next->next) {
        ListNode* first = curr->next;
        ListNode* second = curr->next->next;
        first->next = second->next;
        second->next = first;
        curr->next = second;
        curr = first;
    }
    return dummy.next;
}

/**
 * Problem 15: Remove Duplicates from Sorted List (LC 83)
 * Description:
 * Given the head of a sorted linked list, delete all duplicates such that each element appears only once.
 * Example:
 * Input: head = [1, 1, 2]
 * Output: [1, 2]
 */
ListNode* DeleteDuplicates(ListNode* head) {
    ListNode* curr = head;
    while (curr && curr->next) {
        if (curr->val == curr->next->val) {
            ListNode* tmp = curr->next;
            curr->next = curr->next->next;
            delete tmp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

/**
 * Problem 16: Odd Even Linked List (LC 328)
 * Description:
 * Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices.
 * Example:
 * Input: head = [1, 2, 3, 4, 5]
 * Output: [1, 3, 5, 2, 4]
 */
ListNode* OddEvenList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* even_head = even;
    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = even_head;
    return head;
}

/**
 * Problem 17: Linked List Cycle II (LC 142)
 * Description:
 * Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.
 * Example:
 * Input: head = [3, 2, 0, -4] (cycle at node with value 2)
 * Output: Node with value 2
 */
ListNode* DetectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;
        }
    }
    return nullptr;
}

/**
 * Problem 18: Flatten a Multilevel Doubly Linked List (LC 430)
 * Description:
 * You are given a doubly linked list, which contains nodes that can have a child pointer pointing to another doubly linked list.
 * Flatten the list so that all the nodes appear in a single-level, doubly linked list.
 * Example:
 * Input: head = [1, 2, 3, 4, 5, 6, null, null, null, 7, 8, 9, 10]
 * Output: [1, 2, 3, 7, 8, 9, 10, 4, 5, 6]
 */
class DoublyListNode {
public:
    int val;
    DoublyListNode* next;
    DoublyListNode* prev;
    DoublyListNode* child;

    DoublyListNode(int _val) {
        val = _val;
        next = nullptr;
        prev = nullptr;
        child = nullptr;
    }
};

DoublyListNode* Flatten(DoublyListNode* head) {
    if (!head) return nullptr;
    DoublyListNode* curr = head;
    while (curr) {
        if (curr->child) {
            DoublyListNode* next = curr->next;
            DoublyListNode* child = Flatten(curr->child);
            curr->child = nullptr;
            curr->next = child;
            child->prev = curr;
            while (child->next) {
                child = child->next;
            }
            child->next = next;
            if (next) next->prev = child;
        }
        curr = curr->next;
    }
    return head;
}

/**
 * Problem 19: Remove Duplicates from Sorted List II (LC 82)
 *
 * Description:
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
 *
 * Example 1:
 * Input: head = [1, 2, 3, 3, 4, 4, 5]
 * Output: [1, 2, 5]
 *
 * Example 2:
 * Input: head = [1, 1, 1, 2, 3]
 * Output: [2, 3]
 *
 * Constraints:
 * - The number of nodes in the list is in the range [0, 300].
 * - -100 <= Node.val <= 100
 * - The list is guaranteed to be sorted in ascending order.
 */
ListNode* DeleteAllDuplicates(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* pre = dummy;
    while (pre->next) {
        if (pre->next->next && pre->next->val == pre->next->next->val) {
            ListNode* lst = pre->next, *tmp = lst;
            int v = lst->val;
            while (lst && lst->val == v) {
                lst = lst->next;
            }
            pre->next = lst;
            while (lst && lst->val == v) {
                ListNode* cp = tmp->next;
                delete tmp;
                tmp = cp;
            }
        }
        else {
            pre = pre->next;
        }
    }
    return dummy->next;
}

/**
 * Problem 20: Merge k Sorted Lists (LC 23)
 *
 * Description:
 * You are given an array of k linked-lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Example:
 * Input: lists = [[1, 4, 5], [1, 3, 4], [2, 6]]
 * Output: [1, 1, 2, 3, 4, 4, 5, 6]
 */
ListNode* MergeKLists(vector<ListNode*>& lists) {
    auto compare = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> pq(compare);

    for (auto list : lists) {
        if (list) pq.push(list);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!pq.empty()) {
        ListNode* min_node = pq.top();
        pq.pop();
        tail->next = min_node;
        tail = tail->next;
        if (min_node->next) pq.push(min_node->next);
    }

    return dummy.next;
}

/**
 * Problem 21: Split Linked List in Parts (LC 725)
 *
 * Description:
 * Given the head of a singly linked list and an integer k, split the linked list
 * into k consecutive parts as equally as possible.
 *
 * Example:
 * Input: head = [1, 2, 3, 4], k = 5
 * Output: [[1], [2], [3], [4], []]
 */
vector<ListNode*> SplitListToParts(ListNode* head, int k) {
    int length = 0;
    ListNode* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }

    int part_size = length / k;
    int extra = length % k;

    vector<ListNode*> result(k, nullptr);
    curr = head;

    for (int i = 0; i < k && curr; ++i) {
        result[i] = curr;
        int current_part_size = part_size + (extra-- > 0 ? 1 : 0);
        for (int j = 1; j < current_part_size; ++j) {
            curr = curr->next;
        }
        ListNode* next_part = curr->next;
        curr->next = nullptr;
        curr = next_part;
    }

    return result;
}

/**
 * Problem 22: Convert Sorted List to Binary Search Tree (LC 109)
 *
 * Description:
 * Given the head of a singly linked list where elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * Example:
 * Input: head = [-10, -3, 0, 5, 9]
 * Output: [0, -3, 9, -10, null, 5]
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* SortedListToBST(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) return new TreeNode(head->val);

    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = nullptr;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    TreeNode* root = new TreeNode(slow->val);
    if (prev) prev->next = nullptr;
    root->left = SortedListToBST(head == slow ? nullptr : head);
    root->right = SortedListToBST(slow->next);

    return root;
}

int main() {
    // Test Problem 1: Reverse Linked List
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    head = ReverseList(head);
    cout << "Reversed List: ";
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;

    // Test Problem 2: Merge Two Sorted Lists
    ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* merged = MergeTwoLists(l1, l2);
    cout << "Merged List: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    // Test Problem 3: Detect Cycle in Linked List
    ListNode* cycle_head = new ListNode(3, new ListNode(2, new ListNode(0, new ListNode(-4))));
    cycle_head->next->next->next->next = cycle_head->next; // Create cycle
    cout << "Has Cycle: " << (HasCycle(cycle_head) ? "True" : "False") << endl;

    // Test Problem 4: Remove Nth Node From End of List
    ListNode* remove_nth_head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    remove_nth_head = RemoveNthFromEnd(remove_nth_head, 2);
    cout << "After Removing Nth Node: ";
    while (remove_nth_head) {
        cout << remove_nth_head->val << " ";
        remove_nth_head = remove_nth_head->next;
    }
    cout << endl;

    // Test Problem 5: Intersection of Two Linked Lists
    ListNode* intersect_a = new ListNode(4, new ListNode(1));
    ListNode* intersect_b = new ListNode(5, new ListNode(6, new ListNode(1)));
    ListNode* intersection = new ListNode(8, new ListNode(4, new ListNode(5)));
    intersect_a->next->next = intersection;
    intersect_b->next->next->next = intersection;
    ListNode* intersect_node = GetIntersectionNode(intersect_a, intersect_b);
    cout << "Intersection Node: " << (intersect_node ? to_string(intersect_node->val) : "None") << endl;

    // Test Problem 6: Palindrome Linked List
    ListNode* palindrome_head = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
    cout << "Is Palindrome: " << (IsPalindrome(palindrome_head) ? "True" : "False") << endl;
    ListNode* palindrome_Head_copy = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
    cout << "Is Palindrome: " << (IsPalindrome_stack(palindrome_Head_copy) ? "True" : "False") << endl;

    // Test Problem 7: Remove Linked List Elements
    ListNode* remove_elements_head = new ListNode(1, new ListNode(2, new ListNode(6, new ListNode(3, new ListNode(4, new ListNode(5, new ListNode(6)))))));
    remove_elements_head = RemoveElements(remove_elements_head, 6);
    cout << "After Removing Elements: ";
    while (remove_elements_head) {
        cout << remove_elements_head->val << " ";
        remove_elements_head = remove_elements_head->next;
    }
    cout << endl;

    // Test Problem 8: Reverse Nodes in k-Group
    ListNode* reverse_k_group_head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    reverse_k_group_head = ReverseKGroup(reverse_k_group_head, 2);
    cout << "After Reversing in k-Group: ";
    while (reverse_k_group_head) {
        cout << reverse_k_group_head->val << " ";
        reverse_k_group_head = reverse_k_group_head->next;
    }
    cout << endl;

    // Test Problem 9: Sort List
    ListNode* sort_list_head = new ListNode(4, new ListNode(2, new ListNode(1, new ListNode(3))));
    sort_list_head = SortList(sort_list_head);
    cout << "Sorted List: ";
    while (sort_list_head) {
        cout << sort_list_head->val << " ";
        sort_list_head = sort_list_head->next;
    }
    cout << endl;

    // Test Problem 10: Rotate List
    ListNode* rotate_head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    rotate_head = RotateRight(rotate_head, 2);
    cout << "Rotated List: ";
    while (rotate_head) {
        cout << rotate_head->val << " ";
        rotate_head = rotate_head->next;
    }
    cout << endl;

    // Test Problem 11: Partition List
    ListNode* partition_head = new ListNode(1, new ListNode(4, new ListNode(3, new ListNode(2, new ListNode(5, new ListNode(2))))));
    partition_head = Partition(partition_head, 3);
    cout << "Partitioned List: ";
    while (partition_head) {
        cout << partition_head->val << " ";
        partition_head = partition_head->next;
    }
    cout << endl;

    // Test Problem 12: Copy List with Random Pointer
    Node* random_list = new Node(7);
    random_list->next = new Node(13);
    random_list->next->next = new Node(11);
    random_list->next->next->next = new Node(10);
    random_list->next->next->next->next = new Node(1);
    random_list->random = nullptr;
    random_list->next->random = random_list;
    random_list->next->next->random = random_list->next->next->next->next;
    random_list->next->next->next->random = random_list->next->next;
    random_list->next->next->next->next->random = random_list;
    Node* copied_list = CopyRandomList(random_list);
    cout << "Copied List: ";
    while (copied_list) {
        cout << "[" << copied_list->val << ", Random: " << (copied_list->random ? to_string(copied_list->random->val) : "null") << "] ";
        copied_list = copied_list->next;
    }
    cout << endl;

    // Test Problem 13: Add Two Numbers
    ListNode* l1_13 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2_13 = new ListNode(5, new ListNode(6, new ListNode(4)));
    ListNode* sum_list = AddTwoNumbers(l1_13, l2_13);
    cout << "Sum List: ";
    while (sum_list) {
        cout << sum_list->val << " ";
        sum_list = sum_list->next;
    }
    cout << endl;

    // Test Problem 14: Swap Nodes in Pairs
    ListNode* swap_head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    swap_head = SwapPairs(swap_head);
    cout << "Swapped Pairs: ";
    while (swap_head) {
        cout << swap_head->val << " ";
        swap_head = swap_head->next;
    }
    cout << endl;

    // Test Problem 15: Remove Duplicates from Sorted List
    ListNode* dup_head = new ListNode(1, new ListNode(1, new ListNode(2)));
    dup_head = DeleteDuplicates(dup_head);
    cout << "Duplicates Removed: ";
    while (dup_head) {
        cout << dup_head->val << " ";
        dup_head = dup_head->next;
    }
    cout << endl;

    // Test Problem 16: Odd Even Linked List
    ListNode* odd_even_head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    odd_even_head = OddEvenList(odd_even_head);
    cout << "Odd Even List: ";
    while (odd_even_head) {
        cout << odd_even_head->val << " ";
        odd_even_head = odd_even_head->next;
    }
    cout << endl;

    // Test Problem 17: Detect Cycle in Linked List
    ListNode* cycle_head_17 = new ListNode(3, new ListNode(2, new ListNode(0, new ListNode(-4))));
    cycle_head_17->next->next->next->next = cycle_head_17->next; // Create cycle
    ListNode* cycle_node = DetectCycle(cycle_head_17);
    cout << "Cycle Detected at Node: " << (cycle_node ? to_string(cycle_node->val) : "None") << endl;

    // Test Problem 18: Flatten a Multilevel Doubly Linked List
    DoublyListNode* node1 = new DoublyListNode(1);
    DoublyListNode* node2 = new DoublyListNode(2);
    DoublyListNode* node3 = new DoublyListNode(3);
    DoublyListNode* node4 = new DoublyListNode(4);
    DoublyListNode* node5 = new DoublyListNode(5);
    DoublyListNode* node6 = new DoublyListNode(6);
    DoublyListNode* node7 = new DoublyListNode(7);
    DoublyListNode* node8 = new DoublyListNode(8);
    DoublyListNode* node9 = new DoublyListNode(9);
    DoublyListNode* node10 = new DoublyListNode(10);

    // Construct the multilevel doubly linked list
    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;
    node4->next = node5;
    node5->prev = node4;
    node5->next = node6;
    node6->prev = node5;

    node3->child = node7;
    node7->next = node8;
    node8->prev = node7;
    node8->next = node9;
    node9->prev = node8;
    node9->next = node10;
    node10->prev = node9;

    // Flatten the list
    DoublyListNode* flattened_head = Flatten(node1);
    cout << "Flattened List: ";
    DoublyListNode* curr = flattened_head;
    while (curr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    ListNode* head_19 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3, new ListNode(4, new ListNode(4, new ListNode(5)))))));
    // Remove duplicates
    ListNode* cur_19 = DeleteAllDuplicates(head_19);
    while (cur_19) {
        cout << cur_19->val << " ";
        cur_19 = cur_19->next;
    }
    cout << endl;

    vector<ListNode*> lists_20 = {
        new ListNode(1, new ListNode(4, new ListNode(5))),
        new ListNode(1, new ListNode(3, new ListNode(4))),
        new ListNode(2, new ListNode(6))
    };
    ListNode* merged_list = MergeKLists(lists_20);
    cout << "Merged k Sorted Lists: ";
    while (merged_list) {
        cout << merged_list->val << " ";
        merged_list = merged_list->next;
    }
    cout << endl;

    ListNode* head_21 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    vector<ListNode*> parts = SplitListToParts(head_21, 5);
    cout << "Split Linked List into Parts: \n";
    for (auto part : parts) {
        ListNode* curr = part;
        while (curr) {
            cout << curr->val << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    ListNode* head_22 = new ListNode(-10, new ListNode(-3, new ListNode(0, new ListNode(5, new ListNode(9)))));
    TreeNode* bst = SortedListToBST(head_22);
    cout << "Converted Sorted List to BST (pre-order traversal): ";
    function<void(TreeNode*)> PrintPreOrder = [&](TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        PrintPreOrder(node->left);
        PrintPreOrder(node->right);
    };
    PrintPreOrder(bst);
    cout << endl;

    return 0;
}
