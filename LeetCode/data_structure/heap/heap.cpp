#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

/**
 * Problem 1: Kth Largest Element in an Array (LC 215)
 * Description:
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in sorted order, not the kth distinct element.
 *
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 *
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 */
int FindKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int num : nums) {
        min_heap.push(num);
        if (min_heap.size() > static_cast<size_t>(k)) {
            min_heap.pop();
        }
    }
    return min_heap.top();
}

/**
 * Problem 2: Merge k Sorted Lists (LC 23)
 * Description:
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 *
 * Example 2:
 * Input: lists = []
 * Output: []
 *
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* MergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> min_heap;
    for (ListNode* list : lists) {
        if (list != nullptr) {
            min_heap.push(list);
        }
    }
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    while (!min_heap.empty()) {
        ListNode* node = min_heap.top();
        min_heap.pop();
        current->next = node;
        current = current->next;
        if (node->next != nullptr) {
            min_heap.push(node->next);
        }
    }
    return dummy->next;
}

/**
 * Problem 3: Top K Frequent Elements (LC 347)
 * Description:
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * You may return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 */
vector<int> TopKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq_map;
    for (int num : nums) {
        freq_map[num]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
    for (const auto& [num, freq] : freq_map) {
        min_heap.push({freq, num});
        if (min_heap.size() > static_cast<size_t>(k)) {
            min_heap.pop();
        }
    }
    vector<int> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top().second);
        min_heap.pop();
    }
    return result;
}

/**
 * Problem 4: Find Median from Data Stream (LC 295)
 * Description:
 * The median is the middle value in an ordered integer list. If the size of the list is odd,
 * the median is the middle element. If the size of the list is even, the median is the
 * average of the two middle elements.
 *
 * Implement the MedianFinder class:
 * - MedianFinder() initializes the MedianFinder object.
 * - void addNum(int num) adds the integer num from the data stream to the data structure.
 * - double findMedian() returns the median of all elements so far.
 *
 * Example:
 * Input:
 * ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 * [[], [1], [2], [], [3], []]
 * Output: [null, null, null, 1.5, null, 2.0]
 */
class MedianFinder {
public:
    priority_queue<int> max_heap; // Lower half
    priority_queue<int, vector<int>, greater<int>> min_heap; // Upper half

    void AddNum(int num) {
        if (max_heap.empty() || num <= max_heap.top()) {
            max_heap.push(num);
        } else {
            min_heap.push(num);
        }
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double FindMedian() {
        if (max_heap.size() > min_heap.size()) {
            return max_heap.top();
        }
        return (max_heap.top() + min_heap.top()) / 2.0;
    }
};

/**
 * Problem 5: Reorganize String (LC 767)
 * Description:
 * Rearrange the characters of a string such that no two adjacent characters are the same.
 * Return the rearranged string, or return an empty string if not possible.
 *
 * Example 1:
 * Input: s = "aab"
 * Output: "aba"
 *
 * Example 2:
 * Input: s = "aaab"
 * Output: ""
 */
string ReorganizeString(string S) {
    unordered_map<char, int> freq_map;
    for (char c : S) {
        freq_map[c]++;
    }
    priority_queue<pair<int, char>> max_heap;
    for (const auto& [ch, freq] : freq_map) {
        max_heap.push({freq, ch});
    }
    string result = "";
    while (max_heap.size() > 1) {
        auto first = max_heap.top();
        max_heap.pop();
        auto second = max_heap.top();
        max_heap.pop();
        result += first.second;
        result += second.second;
        if (--first.first > 0) {
            max_heap.push(first);
        }
        if (--second.first > 0) {
            max_heap.push(second);
        }
    }
    if (!max_heap.empty()) {
        if (max_heap.top().first > 1) {
            return "";
        }
        result += max_heap.top().second;
    }
    return result;
}

/**
 * Problem 6: Sort a Nearly Sorted Array (No LC number)
 * Description:
 * Given an array of integers where each element is at most k positions away from its
 * sorted position, sort the array efficiently.
 *
 * Example:
 * Input: nums = [6,5,3,2,8,10,9], k = 3
 * Output: [2,3,5,6,8,9,10]
 */
vector<int> SortKSortedArray(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> min_heap;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); i++) {
        min_heap.push(nums[i]);
        if (min_heap.size() > static_cast<size_t>(k)) {
            result.push_back(min_heap.top());
            min_heap.pop();
        }
    }
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    return result;
}

/**
 * Problem 7: Kth Smallest Element in a Sorted Matrix (LC 378)
 * Description:
 * Given an n x n matrix where each of the rows and columns are sorted in ascending order,
 * return the kth smallest element in the matrix.
 *
 * Example 1:
 * Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
 * Output: 13
 */
int KthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> min_heap;
    for (size_t i = 0; i < matrix.size(); ++i) {
        min_heap.push({matrix[i][0], {i, 0}});
    }
    while (--k > 0) {
        auto [val, pos] = min_heap.top();
        min_heap.pop();
        int row = pos.first, col = pos.second;
        if (static_cast<size_t>(col + 1) < matrix[row].size()) {
            min_heap.push({matrix[row][col + 1], {row, col + 1}});
        }
    }
    return min_heap.top().first;
}

int main() {
    // Test Problem 1
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    cout << "Kth Largest Element (k=2): " << FindKthLargest(nums1, 2) << endl;

    // Test Problem 2
    ListNode* l1 = new ListNode(1); l1->next = new ListNode(4); l1->next->next = new ListNode(5);
    ListNode* l2 = new ListNode(1); l2->next = new ListNode(3); l2->next->next = new ListNode(4);
    ListNode* l3 = new ListNode(2); l3->next = new ListNode(6);
    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* merged = MergeKLists(lists);
    cout << "Merged k Sorted Lists: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    // Test Problem 3
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> topK = TopKFrequent(nums2, 2);
    cout << "Top 2 Frequent Elements: ";
    for (int num : topK) cout << num << " ";
    cout << endl;

    // Test Problem 4
    MedianFinder median_finder;
    median_finder.AddNum(1);
    median_finder.AddNum(2);
    cout << "Median: " << median_finder.FindMedian() << endl;
    median_finder.AddNum(3);
    cout << "Median after adding 3: " << median_finder.FindMedian() << endl;

    // Test Problem 5
    string s = "aab";
    cout << "Reorganized String: " << ReorganizeString(s) << endl;

    // Test Problem 6
    vector<int> nums3 = {6, 5, 3, 2, 8, 10, 9};
    vector<int> sorted = SortKSortedArray(nums3, 3);
    cout << "Sorted Nearly Sorted Array: ";
    for (int num : sorted) cout << num << " ";
    cout << endl;

    // Test Problem 7
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    cout << "Kth Smallest Element in Matrix: " << KthSmallest(matrix, 8) << endl;

    return 0;
}
