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
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    return minHeap.top();
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

struct compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;
    for (ListNode* list : lists) {
        if (list != nullptr) {
            minHeap.push(list);
        }
    }
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        current->next = node;
        current = current->next;
        if (node->next != nullptr) {
            minHeap.push(node->next);
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
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    for (const auto& [num, freq] : freqMap) {
        minHeap.push({freq, num});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
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
    priority_queue<int> maxHeap; // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Upper half

    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
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
string reorganizeString(string S) {
    unordered_map<char, int> freqMap;
    for (char c : S) {
        freqMap[c]++;
    }
    priority_queue<pair<int, char>> maxHeap;
    for (const auto& [ch, freq] : freqMap) {
        maxHeap.push({freq, ch});
    }
    string result = "";
    while (maxHeap.size() > 1) {
        auto first = maxHeap.top();
        maxHeap.pop();
        auto second = maxHeap.top();
        maxHeap.pop();
        result += first.second;
        result += second.second;
        if (--first.first > 0) {
            maxHeap.push(first);
        }
        if (--second.first > 0) {
            maxHeap.push(second);
        }
    }
    if (!maxHeap.empty()) {
        if (maxHeap.top().first > 1) {
            return "";
        }
        result += maxHeap.top().second;
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
vector<int> sortKSortedArray(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        minHeap.push(nums[i]);
        if (minHeap.size() > k) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
    }
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
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
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> minHeap;
    for (int i = 0; i < matrix.size(); ++i) {
        minHeap.push({matrix[i][0], {i, 0}});
    }
    while (--k > 0) {
        auto [val, pos] = minHeap.top();
        minHeap.pop();
        int row = pos.first, col = pos.second;
        if (col + 1 < matrix[row].size()) {
            minHeap.push({matrix[row][col + 1], {row, col + 1}});
        }
    }
    return minHeap.top().first;
}

int main() {
    // Test Problem 1
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    cout << "Kth Largest Element (k=2): " << findKthLargest(nums1, 2) << endl;

    // Test Problem 2
    ListNode* l1 = new ListNode(1); l1->next = new ListNode(4); l1->next->next = new ListNode(5);
    ListNode* l2 = new ListNode(1); l2->next = new ListNode(3); l2->next->next = new ListNode(4);
    ListNode* l3 = new ListNode(2); l3->next = new ListNode(6);
    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* merged = mergeKLists(lists);
    cout << "Merged k Sorted Lists: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    // Test Problem 3
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> topK = topKFrequent(nums2, 2);
    cout << "Top 2 Frequent Elements: ";
    for (int num : topK) cout << num << " ";
    cout << endl;

    // Test Problem 4
    MedianFinder medianFinder;
    medianFinder.addNum(1);
    medianFinder.addNum(2);
    cout << "Median: " << medianFinder.findMedian() << endl;
    medianFinder.addNum(3);
    cout << "Median after adding 3: " << medianFinder.findMedian() << endl;

    // Test Problem 5
    string s = "aab";
    cout << "Reorganized String: " << reorganizeString(s) << endl;

    // Test Problem 6
    vector<int> nums3 = {6, 5, 3, 2, 8, 10, 9};
    vector<int> sorted = sortKSortedArray(nums3, 3);
    cout << "Sorted Nearly Sorted Array: ";
    for (int num : sorted) cout << num << " ";
    cout << endl;

    // Test Problem 7
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    cout << "Kth Smallest Element in Matrix: " << kthSmallest(matrix, 8) << endl;

    return 0;
}
