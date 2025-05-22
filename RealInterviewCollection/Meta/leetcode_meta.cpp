#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <climits>
#include <cstdint>
#include <cmath>
#include <sstream>
#include <functional>
#include <memory>
#include <mutex>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Problem 1: Diameter of Binary Tree (LC 543)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return the length of the longest path between any two nodes.
 *
 * 🔍 Example:
 * Input: [1,2,3,4,5]
 * Output: 3 (path: 4 → 2 → 1 → 3)
 *
 * 🎯 Key Insight:
 * For each node, max path through it = left height + right height
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * height(node) = max depth from node to leaf
 * diameter = max(left + right) over all nodes
 *
 * ✅ Transition:
 * Recursively calculate height and update global max
 *
 * ✅ Iteration Order:
 * Post-order DFS
 *
 * 🚨 Edge Cases:
 * - Empty tree: return 0
 * - Tree with only one node: return 0 (no edge)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */

int MaxDepth(TreeNode* node, int& diameter) {
    if (!node) return 0;
    int left = MaxDepth(node->left, diameter);
    int right = MaxDepth(node->right, diameter);
    diameter = max(diameter, left + right);
    return max(left, right) + 1;
}

int DiameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    MaxDepth(root, diameter);
    return diameter;
}

/**
 * Problem 2: Simplify Path (LC 71)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a string `path`, which is an absolute path (starting with `/`)
 * to a file or directory in a Unix-style file system, simplify it.
 * Return the simplified canonical path.
 *
 * 🔍 Example:
 * Input: "/a/./b/../../c/"
 * Output: "/c"
 *
 * 🎯 Key Insight:
 * Use a stack to simulate the folder traversal
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Stack of valid directory names
 *
 * ✅ Transition:
 * - Split path by `/`
 * - If token is `..`: pop from stack if not empty
 * - If token is valid directory name: push to stack
 * - Ignore `.` or empty tokens
 *
 * ✅ Iteration Order:
 * - Split string by `/`, process left to right
 *
 * 🚨 Edge Cases:
 * - Empty path (""), should return "/"
 * - Path with multiple slashes ("//a///b"), should collapse them
 * - Path ending with ".." beyond root ("/../../.."), should return "/"
 * - Path with only ".", "..", and slashes ("/./.././"), should return "/"
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

string SimplifyPath(string path) {
    vector<string> stack;
    stringstream ss(path);
    string token;

    while (getline(ss, token, '/')) {
        if (token == "" || token == ".") continue;
        if (token == "..") {
            if (!stack.empty()) stack.pop_back();
        } else {
            stack.push_back(token);
        }
    }

    string result = "/";
    for (int i = 0; i < stack.size(); ++i) {
        result += stack[i];
        if (i < stack.size() - 1) result += "/";
    }
    return result;
}

/**
 * Problem 3: Merge Sorted Array (LC 88)
 * ---------------------------------------
 * 🧠 Description:
 * Merge two sorted arrays nums1 and nums2 into one sorted array.
 * nums1 has extra space at the end to accommodate nums2.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3
 *        nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 *
 * 🎯 Key Insight:
 * Merge from the back to avoid overwriting nums1.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Three pointers: i = m-1, j = n-1, k = m+n-1 (write index)
 *
 * ✅ Transition:
 * While i >= 0 and j >= 0:
 *   - Compare nums1[i] and nums2[j], copy larger to nums1[k]
 *   - Decrement respective pointer
 * Copy remaining nums2 if any
 *
 * 🚨 Edge Cases:
 * - If nums2 is empty → nums1 unchanged
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(1)
 */
void Merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;

    // Fill from the end
    while (i >= 0 && j >= 0) {
        //nums1[k--] = (nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }

    // Copy leftover from nums2
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

/**
 * Problem 4: Valid Palindrome (LC 125)
 * --------------------------------------
 * 🧠 Description:
 * Given a string, determine if it is a palindrome considering only alphanumeric characters and ignoring cases.
 *
 * 🔍 Example:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 *
 * 🎯 Key Insight:
 * Use two pointers and skip non-alphanumerics.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Two pointers: left and right
 *
 * ✅ Transition:
 * - Skip non-alphanumerics
 * - Compare lowercase letters
 *
 * ✅ Iteration Order:
 * Move inward from both ends
 *
 * 🚨 Edge Cases:
 * - Empty string → true
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
bool IsPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }

    return true;
}

/**
 * Problem 5: LRU Cache (LC 146)
 * ---------------------------------------------
 * 🧠 Description:
 * Design a data structure that follows the **Least Recently Used (LRU)** cache policy.
 * Implement LRUCache class:
 *   - `LRUCache(int capacity)` initializes the cache with positive size capacity.
 *   - `int get(int key)` returns the value if key exists, otherwise -1.
 *   - `put(int key, int value)` updates or inserts key-value. If capacity exceeded, evicts least recently used.
 *
 * 🔍 Example:
 * Input:
 *   LRUCache cache(2);
 *   cache.put(1, 1);
 *   cache.put(2, 2);
 *   cache.get(1);    // returns 1
 *   cache.put(3, 3); // evicts key 2
 *   cache.get(2);    // returns -1 (not found)
 *   cache.put(4, 4); // evicts key 1
 *   cache.get(1);    // returns -1
 *   cache.get(3);    // returns 3
 *   cache.get(4);    // returns 4
 *
 * 🎯 Key Insight:
 * Combine a hash map for O(1) key lookup and a doubly linked list for O(1) insert/erase of usage order.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - `unordered_map<int, list<pair<int,int>>::iterator>` for fast key → node lookup
 * - `list<pair<int,int>>` to maintain usage order (front = most recent)
 *
 * ✅ Transition:
 * - For `get`: move node to front
 * - For `put`: insert new node at front; evict from back if over capacity
 *
 * ✅ Iteration Order:
 * - All operations are O(1) using `unordered_map` + `list`
 *
 * 🚨 Edge Cases:
 * - Capacity = 0: should not store anything
 * - Overwrite existing key: move it to front, update value
 * - Repeated `get` should not duplicate entries
 *
 * ⏱️ Time Complexity: O(1) for both `get` and `put`
 * 🧠 Space Complexity: O(capacity)
 */

#include <unordered_map>
#include <list>
#include <iostream>
using namespace std;

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node(int k, int v) : key(k), value(v) {}
    };

    int capacity_;
    std::list<Node> cache_list_; // front = most recently used
    std::unordered_map<int, std::list<Node>::iterator> cache_map_;
    std::mutex mtx_;

public:
    // Prevents implicit conversion from int to LRUCache.
    // Ensures that objects must be constructed explicitly, e.g., LRUCache cache(10);
    explicit LRUCache(int cap) : capacity_(cap) {}

    /**
     * Retrieve value by key.
     * If key exists, move to front and return value.
     * Else, return -1.
     */
    int Get(int key) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!cache_map_.count(key)) return -1;

        auto it = cache_map_[key];
        cache_list_.splice(cache_list_.begin(), cache_list_, it); // move to front

        // ✅ Efficiently moves the node `it` to the front of the list (O(1) time).
        // No memory is allocated or deallocated.
        // Internally, it only adjusts pointers — this is the key benefit of std::list.

        // 🟰 Functionally equivalent to:
        /*
            cache_list_.push_front(*it);   // Create a new copy at the front
            cache_list_.erase(it);         // Delete the original node
        */

        // ❗ BUT:
        // - push_front + erase = 1 copy + 1 destruction → more expensive
        // - splice = pointer manipulation only → faster, no copy or destructor call

        // 🚀 Summary:
        // - splice() is the most efficient way to reorder nodes inside std::list
        // - It keeps iterator validity and avoids memory churn
        // - Ideal for LRU cache, MRU cache, or reordering operations

        return it->value;
    }

    /**
     * Insert or update key-value pair.
     * If key exists, update value and move to front.
     * If not, insert to front and evict LRU if needed.
     */
    void Put(int key, int value) {
        std::lock_guard<std::mutex> lock(mtx_);

        if (cache_map_.count(key)) {
            cache_list_.erase(cache_map_[key]); // Erase old node
        } else if (cache_list_.size() >= static_cast<size_t>(capacity_)) {
            // Evict least recently used (tail)
            auto& old = cache_list_.back();
            cache_map_.erase(old.key);
            cache_list_.pop_back();
        }

        // Insert new node at front
        cache_list_.emplace_front(key, value);
        cache_map_[key] = cache_list_.begin();
    }
};

/**
 * LFU Cache
 * ---------------------
 * 🧠 Description:
 * Design a Least Frequently Used (LFU) cache. Each key has a usage frequency, and when the cache
 * reaches capacity, it removes the least frequently used key. If multiple keys share the same frequency,
 * the least recently used one is removed.
 *
 * 🔍 Example:
 * Input:
 *   LFUCache lfu(2);
 *   lfu.put(1, 1);
 *   lfu.put(2, 2);
 *   cout << lfu.get(1) << endl;
 *   lfu.put(3, 3);  // evicts key 2
 *   cout << lfu.get(2) << endl;
 *   cout << lfu.get(3) << endl;
 * Output:
 *   1
 *   -1
 *   3
 *
 * 💡 Strategy:
 * - key_map: key → node iterator
 * - freq_map: freq → list of nodes (LRU within each freq)
 * - min_freq: track minimum frequency
 *
 * ✨ Key Insight:
 * - LFU = Frequency Bucket + LRU Order
 *
 * ⏱ Time: O(1), 🧠 Space: O(capacity)
 */

/*
LFU Cache – Explanation
------------------------
We need to evict the least frequently used key when full.
If multiple keys have same frequency, remove the least recently used among them.

Idea:
- keyMap: key → node (value, freq)
- freqMap: freq → doubly linked list of keys (LRU order)
- minFreq: track lowest frequency currently present

On get:
- Increase node frequency
- Move it to new freq list's front

On put:
- If key exists: update + bump freq
- If not: evict from minFreq list tail if full, insert with freq=1

Why this structure?
→ Separates frequency management (LFU) and recency within frequency (LRU),
   while preserving O(1) time via hashmap + linked list.
*/
/**
 * LFUCache
 * --------
 * A Least Frequently Used (LFU) cache implementation that supports:
 * - O(1) get(key): return value if key exists, otherwise -1.
 * - O(1) put(key, value): insert or update value; evict least frequently used key if needed.
 *
 * Design Overview:
 * - keyMap: maps key → iterator to the node in freqMap
 * - freqMap: maps frequency → list of nodes with that frequency
 * - minFreq: tracks the current minimum frequency in the cache
 *
 * Invariant:
 * - freqMap[freq] is a list to support recency within the same frequency (LRU within LFU).
 * - When cache is full, remove the last node from freqMap[minFreq] (least recent among LFU).
 *
 * Time Complexity:
 * - All operations: O(1) average
 */
class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity_;                         // Maximum number of entries in the cache
    int min_freq_;                          // Minimum frequency of any key currently in the cache
    unordered_map<int, list<Node>> freq_map_;              // freq → list of nodes (LRU within freq)
    unordered_map<int, list<Node>::iterator> key_map_;     // key → iterator in freqMap

public:
    // Constructor: initialize with fixed capacity
    explicit LFUCache(int capacity) : capacity_(capacity), min_freq_(0) {}

    /**
     * Retrieve a value from the cache.
     * If key exists:
     *   - Update its frequency
     *   - Move it to the new frequency bucket (at front to keep LRU order)
     *   - Update minFreq if needed
     * If not, return -1
     */
    int Get(int key) {
        if (!key_map_.count(key)) return -1;

        auto it = key_map_[key];
        int val = it->value;
        int freq = it->freq;

        // Remove node from current freq list
        freq_map_[freq].erase(it);

        // If this freq list becomes empty and it's the minFreq, update minFreq
        if (freq_map_[freq].empty() && freq == min_freq_) {
            min_freq_++;
        }

        // Insert node into new freq list (freq + 1), at front (most recent)
        freq_map_[freq + 1].push_front(Node(key, val, freq + 1));
        key_map_[key] = freq_map_[freq + 1].begin();

        return val;
    }

    /**
     * Insert or update a key-value pair.
     * If key exists:
     *   - Update value and promote its frequency via get()
     * If key is new:
     *   - If at capacity, evict LFU item (from freqMap[minFreq].back())
     *   - Insert with freq = 1 and reset minFreq to 1
     */
    void Put(int key, int value) {
        if (capacity_ == 0) return;

        // Case 1: key already exists → update and increase frequency
        if (key_map_.count(key)) {
            key_map_[key]->value = value; // update value
            Get(key);                   // promote frequency
            return;
        }

        // Case 2: cache full → evict LRU entry in the lowest frequency bucket
        if (key_map_.size() == static_cast<size_t>(capacity_)) {
            auto node = freq_map_[min_freq_].back(); // least recently used in LFU
            key_map_.erase(node.key);
            freq_map_[min_freq_].pop_back();
        }

        // Case 3: insert new key with frequency 1
        freq_map_[1].push_front(Node(key, value, 1));
        key_map_[key] = freq_map_[1].begin();
        min_freq_ = 1; // reset min_freq_ to 1 for new insert
    }
};

/**
 * Problem 6: Maximum Swap (LC 670)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a non-negative integer `num`, you can swap **at most one pair of digits** to get the maximum valued number.
 * Return the maximum number you can get.
 *
 * 🔍 Example:
 * Input: num = 2736
 * Output: 7236
 *
 * Input: num = 9973
 * Output: 9973
 *
 * 🎯 Key Insight:
 * Find the first digit from left that is smaller than a digit further right that is larger.
 * Swap it with the largest such digit as rightmost as possible.
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Convert number to string to access individual digits.
 * - Track last seen position of each digit (0–9).
 *
 * ✅ Transition:
 * - From left to right, try to find a bigger digit on the right to swap with current.
 * - Swap once with the rightmost largest digit.
 *
 * ✅ Iteration Order:
 * - Scan from left to right for first eligible digit to swap.
 * - Scan from 9 to current+1 for a larger digit to swap.
 *
 * 🚨 Edge Cases:
 * - Single digit input: return itself
 * - Already maximal number: return itself (e.g. 9987)
 * - Trailing zeros are fine (e.g. 109090 → 909010)
 *
 * ⏱️ Time Complexity: O(n) where n = number of digits
 * 🧠 Space Complexity: O(1) — fixed size map of 10 digits
 */

int MaximumSwap(int num) {
    // Convert the number to a string for digit manipulation
    string num_str = to_string(num);
    int n = num_str.length();

    // last_index[d] stores the last occurrence index of digit d (0 to 9)
    vector<int> last_index(10, -1);
    for (int i = 0; i < n; ++i) {
        last_index[num_str[i] - '0'] = i;
    }

    // Iterate through each digit from left to right (most significant to least)
    for (int i = 0; i < n; ++i) {
        int current_digit = num_str[i] - '0';

        // Try to find a larger digit (from 9 to current_digit + 1)
        // that appears later in the string
        for (int d = 9; d > current_digit; --d) {
            if (last_index[d] > i) {
                // Found a larger digit that appears after the current digit
                // Swap them to maximize the number
                swap(num_str[i], num_str[last_index[d]]);
                return stoi(num_str);  // Convert back to int and return
            }
        }
    }

    // No swap needed; number is already the maximum
    return num;
}

/**
 * Problem 7: Find Peak Element (LC 162)
 * ----------------------------------------
 * 🧠 Description:
 * A peak element is an element strictly greater than its neighbors.
 * Return the index of any one peak.
 *
 * 🔍 Example:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5
 *
 * 🎯 Key Insight:
 * Binary search — if mid < mid+1 → peak is on right
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Binary search for peak in nums
 *
 * ✅ Transition:
 * - if nums[mid] < nums[mid + 1] → search right
 * - else → search left
 *
 * ✅ Iteration Order:
 * Standard binary search
 *
 * 🚨 Edge Cases:
 * - Single element array → return 0
 * - Peak at boundary
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
int FindPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] < nums[mid + 1])
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

//Follow up, find all peaks, time complexity o(n) brute force
vector<int> FindAllPeaks(const vector<int>& nums) {
    vector<int> peaks;
    int n = nums.size();

    if (n == 0) return peaks;

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            if (n > 1 && nums[i] > nums[i + 1]) peaks.push_back(i);
        } else if (i == n - 1) {
            if (nums[i] > nums[i - 1]) peaks.push_back(i);
        } else {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
                peaks.push_back(i);
        }
    }

    return peaks;
}

/**
 * Problem 8: Valid Palindrome II (LC 680)
 * -----------------------------------------
 * 🧠 Description:
 * Given a string s, return true if the string can be a palindrome after deleting at most one character.
 *
 * 🔍 Example:
 * Input: "abca"
 * Output: true (delete 'b' or 'c')
 *
 * 🎯 Key Insight:
 * Use two pointers. On mismatch, try skipping one character and check if the rest is a palindrome.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * left, right = current pointers
 *
 * ✅ Base Case Initialization:
 * Begin with left = 0, right = s.length() - 1
 *
 * ✅ Transition:
 * If s[left] == s[right], continue.
 * If mismatch, try skipping left or right and test both substrings.
 *
 * ✅ Helper:
 * IsPalindromeInRange(s, i, j)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
bool IsPalindromeInRange(const string& s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

bool ValidPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return IsPalindromeInRange(s, left + 1, right) ||
                   IsPalindromeInRange(s, left, right - 1);
        }
        left++;
        right--;
    }

    return true;
}

/**
 * Problem 9: Dot Product of Two Sparse Vectors (LC 1570)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given two sparse vectors, compute their dot product.
 * Implement class `SparseVector` with:
 *   - `SparseVector(vector<int>& nums)`: constructor
 *   - `int DotProduct(SparseVector& vec)`: returns the dot product of this and `vec`
 *
 * The vectors are sparse, meaning most elements are zero.
 *
 * 🔍 Example:
 * Input:
 *   v1 = [1, 0, 0, 2, 3]
 *   v2 = [0, 3, 0, 4, 0]
 * Output: 8
 * Explanation: 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
 *
 * 🎯 Key Insight:
 * Use a map (or list of index-value pairs) to store non-zero elements only.
 * Then merge or lookup common indices.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - vector of {index, value} pairs for each sparse vector
 *
 * ✅ Transition:
 * - Two-pointer merge if both are sparse
 * - Or hash map + lookup if one is dense
 *
 * ✅ Iteration Order:
 * - Iterate through non-zero elements only
 *
 * 🚨 Edge Cases:
 * - One or both vectors are all zeros → return 0
 * - Large vectors with few non-zero entries → should still run fast
 *
 * ⏱️ Time Complexity: O(m + n), m/n = non-zero elements in each vector
 * 🧠 Space Complexity: O(m) per vector
 */

class SparseVector {
private:
    vector<pair<int, int>> data_; // {index, value} for non-zero entries

public:
    SparseVector(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                data_.emplace_back(i, nums[i]);
            }
        }
    }

    int DotProduct(SparseVector& vec) {
        int result = 0;
        int i = 0, j = 0;
        const vector<pair<int, int>>& a = data_;
        const vector<pair<int, int>>& b = vec.data_;

        while (i < a.size() && j < b.size()) {
            if (a[i].first == b[j].first) {
                result += a[i].second * b[j].second;
                ++i;
                ++j;
            } else if (a[i].first < b[j].first) {
                ++i;
            } else {
                ++j;
            }
        }

        return result;
    }
};
/*
    vector<int> vec1 = {1, 0, 0, 2, 3};
    vector<int> vec2 = {0, 3, 0, 4, 0};

    SparseVector sv1(vec1);
    SparseVector sv2(vec2);

    int result = sv1.DotProduct(sv2);
    cout << "Dot Product: " << result << endl; // Expected: 2*4 = 8
*/

/**
 * Problem 10: Kth Largest Element in an Array (LC 215)
 * -----------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return the k-th largest element in the array.
 * Note: It's the k-th largest **in sorted order**, not the k-th distinct.
 *
 * 🔍 Example:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 *
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 *
 * 🎯 Key Insight:
 * Quickselect is optimal: partition-based selection algorithm with average O(n) time.
 * Similar to quicksort but only recurses into one side.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - `kth_index = n - k` → converts "k-th largest" to "index in sorted array"
 *
 * ✅ Transition:
 * - Partition around random pivot
 * - If pivot == kth_index, return
 * - Else recurse on left or right depending on pivot position
 *
 * ✅ Iteration Order:
 * - Randomized quickselect to reduce worst-case chance
 *
 * 🚨 Edge Cases:
 * - Single element array
 * - All elements are equal
 * - k == 1 → return max
 *
 * ⏱️ Time Complexity: O(n) average, O(n²) worst-case
 * 🧠 Space Complexity: O(1) if in-place (ignoring recursion stack)
 */

int Partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left;

    for (int j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            swap(nums[i], nums[j]);
            ++i;
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

int QuickSelect(vector<int>& nums, int left, int right, int k_smallest) {
    if (left == right) return nums[left];

    int pivot_index = left + rand() % (right - left + 1);
    swap(nums[pivot_index], nums[right]);

    int final_index = Partition(nums, left, right);

    if (final_index == k_smallest) {
        return nums[final_index];
    } else if (final_index < k_smallest) {
        return QuickSelect(nums, final_index + 1, right, k_smallest);
    } else {
        return QuickSelect(nums, left, final_index - 1, k_smallest);
    }
}

int FindKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    int kth_index = n - k;
    return QuickSelect(nums, 0, n - 1, kth_index);
}

/**
 * 🎯 Key Insight:
 * Maintain a min-heap of the top-k largest elements seen so far.
 * Top of the heap is the k-th largest.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - A min-heap with size at most k
 *
 * ✅ Transition:
 * - Push each number
 * - If size > k, pop the smallest
 *
 * ✅ Iteration Order:
 * - Process nums from left to right
 *
 * 🚨 Edge Cases:
 * - k == nums.size() → return the smallest
 * - nums has duplicates → heap handles it naturally
 *
 * ⏱️ Time Complexity: O(n log k)
 * 🧠 Space Complexity: O(k)
 */
int FindKthLargestPq(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int num : nums) {
        min_heap.push(num);
        if (min_heap.size() > k) {
            min_heap.pop();
        }
    }

    return min_heap.top();
}

/**
 * 🔍 QuickSelect vs. Min-Heap (Priority Queue)
 * ---------------------------------------------
 * Both solve the "Find Kth Largest Element" problem, but with different trade-offs.
 *
 * 🎯 QuickSelect (Average O(n), Worst O(n^2))
 * ---------------------------------------------
 * ✅ Pros:
 *   - Very fast in practice for one-time use
 *   - In-place (no extra memory)
 *   - Average-case linear time
 *
 * ❌ Cons:
 *   - Modifies the input array
 *   - Can degrade to O(n^2) in worst case (bad pivots)
 *   - Not suitable for multiple queries or dynamic data
 *
 * Best for:
 *   - Single-shot queries where performance matters
 *   - You don't care about modifying the input
 *
 * 🎯 Min-Heap (Time: O(n log k), Space: O(k))
 * ---------------------------------------------
 * ✅ Pros:
 *   - Stable and predictable performance
 *   - Does not modify the original array
 *   - Supports streaming / multiple queries / dynamic insertion (see LC 703)
 *
 * ❌ Cons:
 *   - Slower than QuickSelect in single-run scenarios
 *   - Needs extra memory (heap of size k)
 *
 * Best for:
 *   - Data streams (online Kth largest)
 *   - Repeated queries
 *   - Large arrays with small k
 *
 * 🧠 TL;DR:
 * Use QuickSelect for one-time queries.
 * Use Min-Heap for robust, multi-query, or streaming scenarios.
 */

/**
 * Problem 11: Lowest Common Ancestor of a Binary Tree (LC 236)
 * --------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * 🔍 Example:
 * Input: root = [3,5,1,6,2,0,8], p = 5, q = 1
 * Output: 3
 *
 * 📐 Example Tree Structure:
 *         3
 *        / \
 *       5   1
 *      / \ / \
 *     6  2 0  8
 *
 * 🎯 Key Insight:
 * Use post-order traversal. Return the node itself if found. The first node where both p and q appear is the LCA.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Return current node if p or q found in subtree
 *
 * ✅ Transition:
 * Traverse left and right:
 * - If both return non-null ⇒ current is LCA
 * - Else return the non-null one
 *
 * ✅ Iteration Order:
 * Post-order
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
TreeNode* LowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    // if (!root) return nullptr;
    // if (root == p || root == q) return root;

    TreeNode* left = LowestCommonAncestor(root->left, p, q);
    TreeNode* right = LowestCommonAncestor(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
    //if (left) return left;
    //else return right;
}

/**
 * Problem 12: Lowest Common Ancestor of a Binary Tree III (LC 1650)
 * ------------------------------------------------------------------
 * 🧠 Description:
 * Given two nodes `p` and `q` in a binary tree where each node has a `parent` pointer,
 * return their **lowest common ancestor** (LCA).
 * A node can be its own ancestor.
 *
 * 🔍 Example:
 * Input: p = 5, q = 1
 * Output: 3
 *
 * 📐 Example Tree Structure:
 * Each node has a `parent` pointer (not shown in diagram).
 *
 *         3
 *        / \
 *       5   1
 *      / \ / \
 *     6  2 0  8
 *       / \
 *      7   4
 *
 * For example:
 * - Node 5's parent is 3
 * - Node 7's parent is 2
 * - Node 0's parent is 1
 *
 * 🎯 Key Insight:
 * This is equivalent to finding the intersection of two parent-linked paths (like linked list intersection).
 *
 * 💡 Strategy:
 * ------------------------------------------------------------------
 * ✅ State Definition:
 * - Traverse upward using parent pointers
 *
 * ✅ Transition:
 * - Store all ancestors of `p` in a set
 * - Traverse up from `q`, return first node in the set
 *
 * ✅ Iteration Order:
 * - Traverse upward from both nodes
 *
 * 🚨 Edge Cases:
 * - p == q → return p
 * - One is ancestor of the other → return ancestor
 *
 * ⏱️ Time Complexity: O(h), where h is the tree height
 * 🧠 Space Complexity: O(h), for hash set
 */

struct Node1650 {
    int val;
    Node1650* left;
    Node1650* right;
    Node1650* parent;
    Node1650(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node1650* LowestCommonAncestor(Node1650* p, Node1650* q) {
    unordered_set<Node1650*> ancestor_set;

    Node1650* current_node = p;
    while (current_node != nullptr) {
        ancestor_set.insert(current_node);
        current_node = current_node->parent;
    }

    current_node = q;
    while (current_node != nullptr) {
        if (ancestor_set.count(current_node)) {
            return current_node;
        }
        current_node = current_node->parent;
    }

    return nullptr;
}

/**
 * Problem 13: Binary Tree Vertical Order Traversal (LC 314) 🔒
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return its vertical order traversal.
 * Return nodes column by column from left to right, and top to bottom within each column.
 *
 * 🔍 Example:
 * Input:
 *     3
 *    / \
 *   9   8
 *  / \ / \
 * 4  0 1  7
 *
 * Output: [[4], [9], [3,0,1], [8], [7]]
 *
 * 📐 Column Assignment:
 * - Root node 3 is at column 0.
 * - Going left decreases column index by 1.
 * - Going right increases column index by 1.
 *
 * ✅ So:
 * - Node 0 is left child of 9 → col = -1 + 1 = 0
 * - Node 1 is right child of 8 → col = +1 - 1 = 0
 * → Both node 0 and node 1 end up at column 0 with node 3.
 *
 * 🎯 Key Insight:
 * BFS with a column index assigned to each node. Use a map from column to nodes.
 * Use BFS because vertical traversal requires top-to-bottom order within each column.
 * BFS naturally provides level-wise traversal, which ensures nodes are processed in top-down order.
 * 
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * queue of pairs: (node, column_index)
 * map<col_index, vector<node values>> stores result
 *
 * ✅ Base Case Initialization:
 * Push root with column 0
 *
 * ✅ Transition:
 * - left child: col - 1
 * - right child: col + 1
 *
 * ✅ Iteration Order:
 * BFS ensures top-to-bottom order
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

vector<vector<int>> VerticalOrder(TreeNode* root) {
    if (!root) return {};

    // `col_map` maps column index → list of node values in that column
    // Use map to keep column keys sorted from left to right
    map<int, vector<int>> col_map;
    queue<pair<TreeNode*, int>> q; // Queue stores pair: (node pointer, column index)
    q.push({root, 0});

    while (!q.empty()) {
        auto [node, col] = q.front(); q.pop();
        col_map[col].push_back(node->val);

        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }

    vector<vector<int>> result;
    for (auto& [col, vals] : col_map)
        result.push_back(vals);

    return result;
}

// standard level order(BFS)
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();
        vector<int> level;

        for (int i = 0; i < level_size; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}

/**
 * Problem 14: Minimum Remove to Make Valid Parentheses (LC 1249)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s` containing only letters and parentheses, remove the minimum number
 * of invalid parentheses to make the input string valid. Return any valid result.
 *
 * 🔍 Example:
 * Input: "a)b(c)d"
 * Output: "ab(c)d"
 *
 * Input: "))(("
 * Output: ""
 *
 * 🎯 Key Insight:
 * Use a stack or index set to record unmatched parentheses, then rebuild the string.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State Definition:
 * - Use a stack to track indices of unmatched '('
 * - Mark unmatched ')' directly
 *
 * ✅ Transition:
 * - Traverse string left to right
 * - Stack push when '(', pop on ')'; if no match, mark index to remove
 *
 * ✅ Iteration Order:
 * - Single pass to collect bad indices
 * - One more pass to rebuild final string
 *
 * 🚨 Edge Cases:
 * - All valid: return original string
 * - All parentheses invalid: return empty string
 * - Interleaved parentheses with letters
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n), for stack + result
 */

string MinRemoveToMakeValid(string s) {
    unordered_set<int> indices_to_remove;
    stack<int> open_stack;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            open_stack.push(i);
        } else if (s[i] == ')') {
            if (!open_stack.empty()) {
                open_stack.pop();
            } else {
                indices_to_remove.insert(i);
            }
        }
    }

    // Add remaining unmatched '('
    while (!open_stack.empty()) {
        indices_to_remove.insert(open_stack.top());
        open_stack.pop();
    }

    string result;
    for (int i = 0; i < s.size(); ++i) {
        if (!indices_to_remove.count(i)) {
            result += s[i];
        }
    }

    return result;
}

/**
 * Problem 15: Valid Word Abbreviation (LC 408)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a non-empty string `word` and an abbreviation `abbr`, return whether the abbreviation is valid.
 * A valid abbreviation follows these rules:
 *   - Letters in abbr must match the word directly.
 *   - Numbers in abbr represent how many characters to skip in `word`.
 *   - Leading zeros are invalid (e.g., "01" is invalid).
 *
 * 🔍 Example:
 * Input: word = "internationalization", abbr = "i12iz4n"
 * Output: true
 *
 * Input: word = "apple", abbr = "a2e"
 * Output: false
 *
 * 🎯 Key Insight:
 * Use two pointers to walk through both `word` and `abbr`. When a digit is found in `abbr`,
 * calculate how many characters to skip in `word`. Handle leading zero edge case.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Two pointers: one for `word`, one for `abbr`
 *
 * ✅ Transition:
 * - If `abbr[abbr_index]` is a digit: parse full number and skip in `word`
 * - If `abbr[abbr_index]` is a letter: must match `word[word_index]`
 *
 * ✅ Iteration Order:
 * - Linear scan over both strings
 *
 * 🚨 Edge Cases:
 * - Leading zero in number (e.g. "01") → invalid
 * - Skipping beyond the end of `word` → invalid
 * - Extra characters left in `word` or `abbr` → invalid
 *
 * ⏱️ Time Complexity: O(n + m)
 * 🧠 Space Complexity: O(1)
 */

bool ValidWordAbbreviation(string word, string abbr) {
    int word_index = 0;
    int abbr_index = 0;
    int word_len = word.length();
    int abbr_len = abbr.length();

    while (word_index < word_len && abbr_index < abbr_len) {
        if (isdigit(abbr[abbr_index])) {
            if (abbr[abbr_index] == '0') return false; // leading zero invalid

            int skip_length = 0;
            while (abbr_index < abbr_len && isdigit(abbr[abbr_index])) {
                skip_length = skip_length * 10 + (abbr[abbr_index] - '0');
                ++abbr_index;
            }
            word_index += skip_length;
        } else {
            if (word[word_index] != abbr[abbr_index]) return false;
            ++word_index;
            ++abbr_index;
        }
    }

    return word_index == word_len && abbr_index == abbr_len;
}

/**
 * Problem 16: Range Sum of BST (LC 938)
 * ---------------------------------------------
 * 🧠 Description:
 * Given the root of a Binary Search Tree and two integers `low` and `high`,
 * return the sum of all nodes with values in the inclusive range [low, high].
 *
 * 🔍 Example:
 * Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
 * Output: 32
 * Explanation: Nodes 7, 10, and 15 are within range.
 *
 * 🎯 Key Insight:
 * Leverage the properties of BST:
 * - If node->val > high, skip right subtree.
 * - If node->val < low, skip left subtree.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Use recursive DFS to accumulate sum
 *
 * ✅ Transition:
 * - If current node in range: include value and explore both subtrees
 * - If node value too small: explore right subtree only
 * - If node value too large: explore left subtree only
 *
 * ✅ Iteration Order:
 * - DFS (pre-order or in-order both acceptable)
 *
 * 🚨 Edge Cases:
 * - Empty tree → return 0
 * - All nodes out of range → return 0
 * - Entire tree within range → sum of all nodes
 *
 * ⏱️ Time Complexity: O(n), but pruned via BST → average O(log n + k)
 * 🧠 Space Complexity: O(h), h = height of tree (stack space)
 */

int RangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;

    // Pruning
    if (root->val < low) {
        return RangeSumBST(root->right, low, high);
    }
    // Pruning
    if (root->val > high) {
        return RangeSumBST(root->left, low, high);
    }

    return root->val +
           RangeSumBST(root->left, low, high) +
           RangeSumBST(root->right, low, high);
}

/**
 * Problem 17: K Closest Points to Origin (LC 973)
 * --------------------------------------------------
 * 🧠 Description:
 * Given an array of points `points[i] = [xi, yi]` representing coordinates on the 2D plane,
 * return the `k` closest points to the origin (0, 0).
 * The answer can be returned in any order.
 *
 * 🔍 Example:
 * Input: points = [[1,3],[-2,2]], k = 1
 * Output: [[-2,2]]
 * Explanation: Distance = sqrt(1²+3²)=3.16, sqrt(2²+(-2)²)=2.83 → pick [-2,2]
 *
 * 🎯 Key Insight:
 * Use a max-heap of size `k` to maintain the `k` closest points seen so far,
 * comparing based on squared Euclidean distance (avoid sqrt).
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Max-heap (priority queue) sorted by distance to origin
 *
 * ✅ Transition:
 * - For each point, push into heap
 * - If size exceeds k, pop the farthest point
 *
 * ✅ Iteration Order:
 * - One pass through all points
 *
 * 🚨 Edge Cases:
 * - k == points.size() → return all
 * - All points are at same distance
 *
 * ⏱️ Time Complexity: O(n log k)
 * 🧠 Space Complexity: O(k)
 */

vector<vector<int>> KClosest(vector<vector<int>>& points, int k) {
    // max-heap: {distance_squared, index}
    priority_queue<pair<int, int>> max_heap;

    for (int i = 0; i < points.size(); ++i) {
        int x = points[i][0], y = points[i][1];
        int distance_squared = x * x + y * y;
        max_heap.emplace(distance_squared, i);

        if (max_heap.size() > k) {
            max_heap.pop(); // remove farthest point
        }
    }

    vector<vector<int>> result;
    while (!max_heap.empty()) {
        result.push_back(points[max_heap.top().second]);
        max_heap.pop();
    }

    return result;
}

/**
 * Problem 18: Continuous Subarray Sum (LC 523)
 * ---------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return true if `nums` has a subarray of length at least 2 whose sum is a multiple of `k`.
 *
 * 🔍 Example:
 * Input: nums = [23,2,4,6,7], k = 6
 * Output: true ([2,4])
 *
 * 🎯 Key Insight:
 * If (prefix sum at i) % k == (prefix sum at j) % k, then subarray [j+1, i] is divisible by k.
 *
 * prefix_sum[i] = nums[0] + nums[1] + ... + nums[i]
 * sum(i..j) = prefix_sum[j] - prefix_sum[i - 1]
 * (prefix_sum[j] - prefix_sum[i-1]) % k == 0
 * prefix_sum[j] % k == prefix_sum[i-1] % k
 * 
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use map: remainder → index of first occurrence
 *
 * ✅ Base Case Initialization:
 * map[0] = -1 to handle full prefix being divisible
 *
 * ✅ Transition:
 * At each index i:
 *   - sum += nums[i]
 *   - rem = sum % k
 *   - if rem in map and i - map[rem] ≥ 2 → return true
 *
 * ✅ Iteration Order:
 * Linear from left to right
 *
 * 🚨 Edge Cases:
 * - k = 0 → check for two consecutive zeros
 * - nums.size() < 2 → return false
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(k) or O(n)
 */
bool CheckSubarraySum(vector<int>& nums, int k) {
    // Hash map to store the earliest index of each remainder
    // Key: prefix_sum % k, Value: index
    unordered_map<int, int> mod_map;
    mod_map[0] = -1;  // Handle the case where the subarray starts from index 0

    int prefix_sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
        prefix_sum += nums[i];

        // Compute remainder only if k != 0
        // (prefix_sum[j] - prefix_sum[i - 1]) % k == 0
        int rem = (k != 0) ? prefix_sum % k : prefix_sum;

        // If the same remainder was seen before
        // Check if the same remainder has been seen before
        // This means: prefix_sum[j] % k == prefix_sum[i - 1] % k
        // → sum(i..j) % k == 0 ⇒ subarray nums[i..j] is a multiple of k
        if (mod_map.count(rem)) {
            int prev_index = mod_map[rem];
            if (i - prev_index >= 2)  // // Ensure subarray length is at least 2: j - (i - 1) ≥ 2 ⇒ j - i ≥ 1 ⇒ j - prev_index ≥ 2
                return true;
        } else {
            // Only record the first occurrence of this remainder
            mod_map[rem] = i;
        }
    }

    return false;
}

// follow up return all subarrays
vector<vector<int>> AllSubarrayValuesDivByK(vector<int>& nums, int k) {
    unordered_map<int, vector<int>> mod_map;
    mod_map[0].push_back(-1);  // allow subarray starting from index 0

    vector<vector<int>> result;
    int prefix_sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
        prefix_sum += nums[i];

        int rem = (k != 0) ? prefix_sum % k : prefix_sum;
        if (rem < 0) rem += k;  // handle negative remainder

        if (mod_map.count(rem)) {
            for (int prev_index : mod_map[rem]) {
                if (i - prev_index >= 2) {
                    // Extract subarray nums[prev_index+1..i]
                    vector<int> subarray;
                    for (int j = prev_index + 1; j <= i; ++j) {
                        subarray.push_back(nums[j]);
                    }
                    result.push_back(subarray);
                }
            }
        }

        mod_map[rem].push_back(i);
    }

    return result;
}

/**
 * Problem 19: Pow(x, n) (LC 50)
 * -------------------------------
 * 🧠 Description:
 * Implement pow(x, n), which calculates x raised to the power n.
 *
 * 🔍 Example:
 * Input: x = 2.0, n = 10
 * Output: 1024.0
 *
 * 🎯 Key Insight:
 * Use fast exponentiation (divide and conquer) to reduce time complexity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * pow(x, n) = pow(x*x, n/2) if n is even
 *           = x * pow(x*x, n/2) if n is odd
 *
 * 10 = (1010), 2^10 = 2^2 * 2^8
 * 
 * N = 10 (1010) → skip, x = 2 → 4
 * N = 5  (0101) → result *= 4, x = 4 → 16
 * N = 2  (0010) → skip, x = 16 → 256
 * N = 1  (0001) → result *= 256
 * 
 * ✅ Base Case Initialization:
 * n == 0 → return 1
 *
 * ✅ Iteration Order:
 * Recursive divide & conquer (Binary Exponentiation)
 *
 * 🚨 Edge Cases:
 * - Negative exponent → invert base: 1 / pow(x, -n)
 * - n == INT_MIN → cast to long
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(log n)
 */

double MyPow(double x, int n) {
    long long N = n;  // prevent overflow for INT_MIN. if n = INT_MIN(-2,147,483,648), then -n(INT_MAX is 2,147,483,647) will overflow, so long long

    if (N < 0) {
        x = 1 / x;
        N = -N;
    }

    double result = 1;
    while (N > 0) {
        if (N & 1) result *= x;  // if last bit is 1, equal to (N % 2 == 1)
        x *= x;
        N >>= 1;  // shift right (equivalent to divide by 2)
    }

    return result;
}

/**
 * Problem 20: Merge Intervals (LC 56) (Follow up LC 435)
 * -------------------------------------
 * 🧠 Description:
 * Given a list of intervals, merge all overlapping intervals.
 *
 * 🔍 Example:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 *
 * 🎯 Key Insight:
 * Sort intervals by start time, then merge overlapping ones in one pass.
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * merged = result list
 *
 * ✅ Base Case Initialization:
 * Sort intervals by start time
 *
 * ✅ Transition:
 * If current start > merged.back().end → push new
 * Else → merge by updating end = max(end, current.end)
 *
 * ✅ Iteration Order:
 * Left to right
 *
 * 🚨 Edge Cases:
 * - Empty input → return empty
 * - Fully overlapping intervals
 *
 * ⏱️ Time Complexity: O(n log n)
 * 🧠 Space Complexity: O(n)
 */
vector<vector<int>> Merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });
    vector<vector<int>> merged;

    for (int i = 0; i < intervals.size(); ++i) {
        int curr_start = intervals[i][0];
        int curr_end = intervals[i][1];

        if (merged.empty() || merged.back()[1] < curr_start) {
            merged.push_back({curr_start, curr_end});
        } else {
            merged.back()[1] = max(merged.back()[1], curr_end);
        }
    }

    return merged;
}

/**
 * Problem 21: Find First and Last Position of Element in Sorted Array (LC 34)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers sorted in non-decreasing order, find the starting and ending position of a given target.
 *
 * 🔍 Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3, 4]
 *
 * 🎯 Key Insight:
 * Use binary search twice — once to find the first index, once for the last.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use binary search with custom condition to find left and right boundaries.
 *
 * ✅ Transition:
 * - Find left: move right when nums[mid] < target
 * - Find right: move left when nums[mid] > target
 *
 * ✅ Iteration Order:
 * Two binary searches
 *
 * 🚨 Edge Cases:
 * - Target not found → return [-1, -1]
 * - All elements = target → return [0, n-1]
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
vector<int> SearchRange(vector<int>& nums, int target) {
    int left = -1, right = -1;

    // left bound
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] < target) {
            low = mid + 1;
        } else {
            if (nums[mid] == target) left = mid;
            high = mid - 1;
        }
    }

    // right bount
    low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] > target) {
            high = mid - 1;
        } else {
            if (nums[mid] == target) right = mid;
            low = mid + 1;
        }
    }

    return {left, right};
}


/**
 * Problem 22: Binary Tree Right Side View (LC 199)
 * --------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the values of the nodes you can see from the right side.
 *
 * 🔍 Example:
 * Input: [1,2,3,null,5,null,4]
 * Output: [1,3,4]
 *
 * 🎯 Key Insight:
 * Perform level-order traversal and pick the last node of each level.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Queue for level-order traversal (BFS)
 *
 * ✅ Base Case Initialization:
 * Start with root in queue
 *
 * ✅ Transition:
 * For each level:
 *   - Traverse all nodes
 *   - Store the last node's value
 *
 * ✅ Iteration Order:
 * Level-by-level (breadth-first)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
vector<int> RightSideView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        TreeNode* rightmost = nullptr;

        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            rightmost = node;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        if (rightmost) result.push_back(rightmost->val);
    }

    return result;
}

/**
 * Problem 23: Shortest Path in Binary Matrix (LC 1091)
 * -------------------------------------------------------
 * 🧠 Description:
 * Given an n x n binary matrix `grid`, return the length of the shortest clear path
 * from top-left (0,0) to bottom-right (n-1,n-1). A clear path can only traverse cells with value 0.
 * Move in 8 directions (horizontal, vertical, and diagonal).
 * Return -1 if no such path exists.
 *
 * 🔍 Example:
 * Input: grid = [[0,1],[1,0]]
 * Output: 2
 * Explanation: Path: (0,0) → (1,1)
 *
 * 🎯 Key Insight:
 * Classic BFS shortest path on a 2D grid, with 8-direction movement.
 * Use BFS to explore levels and count steps.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - BFS node: (x, y, step_count)
 * - Use a queue and visited matrix
 *
 * ✅ Transition:
 * - From (x, y), explore all 8 directions
 * - Only push (nx, ny) if in bounds, not visited, and grid[nx][ny] == 0
 *
 * ✅ Iteration Order:
 * - BFS (level-order traversal)
 *
 * 🚨 Edge Cases:
 * - Start or end is blocked (grid[0][0] == 1 or grid[n-1][n-1] == 1)
 * - Single cell (1x1) and grid[0][0] == 0 → return 1
 *
 * ⏱️ Time Complexity: O(n²)
 * 🧠 Space Complexity: O(n²)
 */

int ShortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;
    if (n == 1) return 1;

    queue<tuple<int, int, int>> bfs_queue; // x, y, step
    bfs_queue.emplace(0, 0, 1);
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    visited[0][0] = true;

    vector<pair<int, int>> directions = {
        {0, 1}, {1, 0}, {-1, 0}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    while (!bfs_queue.empty()) {
        auto [curr_x, curr_y, steps] = bfs_queue.front();
        bfs_queue.pop();

        for (auto [dx, dy] : directions) {
            int next_x = curr_x + dx;
            int next_y = curr_y + dy;

            if (next_x >= 0 && next_x < n &&
                next_y >= 0 && next_y < n &&
                !visited[next_x][next_y] &&
                grid[next_x][next_y] == 0) {

                if (next_x == n - 1 && next_y == n - 1) {
                    return steps + 1;
                }

                visited[next_x][next_y] = true;
                bfs_queue.emplace(next_x, next_y, steps + 1);
            }
        }
    }

    return -1;
}

/**
 * Problem 24: Basic Calculator II (LC 227)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a string `s` which represents a valid expression containing non-negative integers,
 * '+', '-', '*', and '/', evaluate the expression and return the result.
 * The integer division should truncate toward zero.
 *
 * 🔍 Example:
 * Input: "3+2*2"
 * Output: 7
 *
 * Input: " 3/2 "
 * Output: 1
 *
 * Input: " 3+5 / 2 "
 * Output: 5
 *
 * 🎯 Key Insight:
 * Use a **stack** to simulate operator precedence:
 * - Push number for `+`
 * - Push -number for `-`
 * - Pop and multiply for `*`
 * - Pop and divide for `/`
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - Track `curr_num` and `curr_op`, process when op is encountered
 *
 * ✅ Transition:
 * - When operator or end is reached, process `curr_num` using `curr_op`
 * - Push result to stack
 *
 * ✅ Iteration Order:
 * - Linear scan, one pass
 *
 * 🚨 Edge Cases:
 * - Input may contain spaces → skip them
 * - Integer division truncates toward zero
 * - Final number must be processed at the end
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) for the stack
 */

int Calculate(string s) {
    int curr_num = 0;
    char curr_op = '+';
    stack<int> num_stack;

    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (isdigit(c)) {
            curr_num = curr_num * 10 + (c - '0');
        }

        // If current char is operator or at end of string
        if ((!isdigit(c) && c != ' ') || i == s.size() - 1) {
            if (curr_op == '+') {
                num_stack.push(curr_num);
            } else if (curr_op == '-') {
                num_stack.push(-curr_num);
            } else if (curr_op == '*') {
                int prev_num = num_stack.top(); num_stack.pop();
                num_stack.push(prev_num * curr_num);
            } else if (curr_op == '/') {
                int prev_num = num_stack.top(); num_stack.pop();
                num_stack.push(prev_num / curr_num);
            }

            curr_op = c;
            curr_num = 0;
        }
    }

    int result = 0;
    while (!num_stack.empty()) {
        result += num_stack.top();
        num_stack.pop();
    }

    return result;
}

/**
 * Problem 25: Subarray Sum Equals K (LC 560)
 * -------------------------------------------
 * 🧠 Description:
 * Given an integer array nums and an integer k, return the total number of continuous subarrays
 * whose sum equals to k.
 *
 * 🔍 Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use a running prefix sum and a hashmap to store the count of each prefix sum.
 * If sum[i] - sum[j] == k, then subarray nums[j..i-1] sums to k.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * sum_so_far = running sum up to current index
 * prefix_count[sum] = number of times sum has occurred
 *
 * ✅ Base Case Initialization:
 * prefix_count[0] = 1 (to handle exact match from start)
 *
 * ✅ Transition:
 * For each number:
 *   - Update sum_so_far += num
 *   - If sum_so_far - k exists in map, increment result by its frequency
 *   - Increment frequency of sum_so_far in map
 *
 * ✅ Iteration Order:
 * Left to right over nums
 *
 * 🚨 Edge Cases:
 * - Empty array → 0
 * - Negative numbers are allowed
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
int SubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_count;
    prefix_count[0] = 1;

    int sum_so_far = 0, count = 0;

    for (int num : nums) {
        sum_so_far += num;
        if (prefix_count.count(sum_so_far - k)) {
            count += prefix_count[sum_so_far - k];
        }
        prefix_count[sum_so_far]++;
    }

    return count;
}

/**
 * Problem 26: Nested List Weight Sum (LC 339)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
 * Each element is either an integer or a list whose elements may also be integers or other lists.
 *
 * 🔍 Example:
 * Input: [[1,1],2,[1,1]]
 * Output: 10
 * Explanation: (1+1)*2 + 2*1 + (1+1)*2 = 10
 *
 * 🎯 Key Insight:
 * Use DFS to track the depth and sum each integer weighted by its depth.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - Traverse nested list recursively, passing current depth
 *
 * ✅ Transition:
 * - If element is integer: add depth * value
 * - If element is list: recurse with depth + 1
 *
 * ✅ Iteration Order:
 * - DFS recursion on each element
 *
 * 🚨 Edge Cases:
 * - Empty list → return 0
 * - Deeply nested lists → stack must be deep enough
 *
 * ⏱️ Time Complexity: O(n), where n = total elements including all sublists
 * 🧠 Space Complexity: O(d), d = max depth of nesting (due to recursion stack)
 */

// This is the interface for LC 339.
// The actual implementation will be provided by the platform.
class NestedInteger339 {
public:
    bool isInteger() const;
    int getInteger() const;
    const vector<NestedInteger339>& getList() const;
};

int DepthSumHelper(const vector<NestedInteger339>& nested_list, int curr_depth) {
    int total_sum = 0;
    for (const auto& ni : nested_list) {
        if (ni.isInteger()) {
            total_sum += ni.getInteger() * curr_depth;
        } else {
            total_sum += DepthSumHelper(ni.getList(), curr_depth + 1);
        }
    }
    return total_sum;
}

int DepthSum(const vector<NestedInteger339>& nested_list) {
    return DepthSumHelper(nested_list, 1);
}

/**
 * Problem 27: Top K Frequent Elements (LC 347)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.
 * You may return the answer in any order.
 *
 * 🔍 Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 * 🎯 Key Insight:
 * Use a hash map to count frequencies, then a min-heap to keep top k.
 * This avoids full sorting and ensures O(n log k) time.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - Hash map to store frequency of each number
 * - Min-heap to maintain top-k frequent elements
 *
 * ✅ Transition:
 * - For each number, count its frequency
 * - Push into heap; if size exceeds k, remove the least frequent
 *
 * ✅ Iteration Order:
 * - Single pass through array, then through hash map
 *
 * 🚨 Edge Cases:
 * - All elements are the same
 * - k == nums.size() → return all unique elements
 *
 * ⏱️ Time Complexity: O(n log k)
 * 🧠 Space Complexity: O(n), for hash map and heap
 */

vector<int> TopKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> frequency_map;
    for (int num : nums) {
        frequency_map[num]++;
    }

    using freq_pair = pair<int, int>; // {frequency, number}
    priority_queue<freq_pair, vector<freq_pair>, greater<freq_pair>> min_heap;

    for (const auto& [num, freq] : frequency_map) {
        min_heap.emplace(freq, num);
        if (min_heap.size() > k) {
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
 * 🎯 Key Insight:
 * - Transform problem into a "Top-K selection" based on frequency.
 * - Build a frequency vector, then use QuickSelect to find top-k largest frequencies.
 *
 * 💡 Strategy:
 * --------------------------------------------------------------------------
 * ✅ Step 1: Build frequency map → vector of pairs {num, freq}
 * ✅ Step 2: Use QuickSelect to partition top-k by frequency
 * ✅ Step 3: Extract k elements from right part
 *
 * 🚨 Edge Cases:
 * - k == nums.size() → return all unique elements
 * - All numbers have same frequency → any k are valid
 *
 * ⏱️ Time Complexity: Average O(n), Worst-case O(n²)
 * 🧠 Space Complexity: O(n), for frequency map
 */

int Partition(vector<pair<int, int>>& pairs, int left, int right) {
    int pivot_freq = pairs[right].second;
    int i = left;

    for (int j = left; j < right; ++j) {
        if (pairs[j].second >= pivot_freq) {
            swap(pairs[i], pairs[j]);
            ++i;
        }
    }

    swap(pairs[i], pairs[right]);
    return i;
}

void QuickSelect(vector<pair<int, int>>& pairs, int left, int right, int k) {
    if (left >= right) return;

    int pivot_index = Partition(pairs, left, right);

    int count = pivot_index - left + 1;
    if (count == k) {
        return;
    } else if (count > k) {
        QuickSelect(pairs, left, pivot_index - 1, k);
    } else {
        QuickSelect(pairs, pivot_index + 1, right, k - count);
    }
}

vector<int> TopKFrequentQuickSelect(vector<int>& nums, int k) {
    unordered_map<int, int> frequency_map;
    for (int num : nums) {
        frequency_map[num]++;
    }

    vector<pair<int, int>> freq_list;
    for (const auto& [num, freq] : frequency_map) {
        freq_list.emplace_back(num, freq);
    }

    QuickSelect(freq_list, 0, freq_list.size() - 1, k);

    vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(freq_list[i].first);
    }

    return result;
}

/**
 * Problem 28: Custom Sort String (LC 791)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given two strings `order` and `s`, sort the characters of `s` so that:
 * - Characters that appear in `order` must be sorted as in `order`
 * - Characters not in `order` can be in any position after those in `order`
 *
 * 🔍 Example:
 * Input: order = "cba", s = "abcd"
 * Output: "cbad"
 *
 * 🎯 Key Insight:
 * Use a frequency counter for `s`, then output characters in the order specified by `order`,
 * followed by remaining characters not in `order`.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - `unordered_map<char, int>` to store character counts from `s`
 *
 * ✅ Transition:
 * - Traverse `order` to append controlled characters
 * - Then traverse `s` again to append uncontrolled characters
 *
 * ✅ Iteration Order:
 * - First `order`, then remaining characters from `s`
 *
 * 🚨 Edge Cases:
 * - `order` is empty → return original `s`
 * - `s` is empty → return empty string
 * - All characters in `s` not in `order` → output remains unchanged
 *
 * ⏱️ Time Complexity: O(n + m), where n = s.size(), m = order.size()
 * 🧠 Space Complexity: O(1), assuming fixed character set (26 lowercase letters)
 */

string CustomSortString(string order, string s) {
    unordered_map<char, int> char_count;
    for (char c : s) {
        char_count[c]++;
    }

    string result;

    // Append characters in order
    for (char c : order) {
        if (char_count.count(c)) {
            result.append(char_count[c], c);
            char_count.erase(c);
        }
    }

    // Append remaining characters
    for (const auto& [c, count] : char_count) {
        result.append(count, c);
    }

    return result;
}

/**
 * Problem 29: Diagonal Traverse (LC 498)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given an m x n matrix, return all elements in diagonal order (zigzag),
 * starting from top-left and moving diagonally upward-right, then downward-left, and so on.
 *
 * 🔍 Example:
 * Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,4,7,5,3,6,8,9]
 *
 * 🎯 Key Insight:
 * Simulate the traversal: use a direction flag to alternate between upward and downward moves.
 * When out of bounds, bounce to the next valid position based on direction.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - (row, col): current position
 * - dir: direction flag (1 = up-right, -1 = down-left)
 *
 * ✅ Transition:
 * - If dir == 1: move to (row - 1, col + 1)
 * - If dir == -1: move to (row + 1, col - 1)
 * - If out of bounds: bounce right or down depending on position and direction
 *
 * ✅ Iteration Order:
 * - Loop until all elements (m * n) are visited
 *
 * 🚨 Edge Cases:
 * - Single row or column
 * - Empty matrix → return empty vector
 * - m = 1 or n = 1 (linear output)
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(1) extra (excluding result)
 */

vector<int> FindDiagonalOrder(vector<vector<int>>& mat) {
    int m = mat.size();
    if (m == 0) return {};
    int n = mat[0].size();
    vector<int> result;
    result.reserve(m * n);

    int row = 0, col = 0, dir = 1;

    for (int i = 0; i < m * n; ++i) {
        result.push_back(mat[row][col]);

        if (dir == 1) {
            // Moving up-right
            if (col == n - 1) {
                row++;
                dir = -1;
            } else if (row == 0) {
                col++;
                dir = -1;
            } else {
                row--;
                col++;
            }
        } else {
            // Moving down-left
            if (row == m - 1) {
                col++;
                dir = 1;
            } else if (col == 0) {
                row++;
                dir = 1;
            } else {
                row++;
                col--;
            }
        }
    }

    return result;
}

/**
 * Problem 30: Copy List with Random Pointer (LC 138)
 * ---------------------------------------------------
 * 🧠 Description:
 * A linked list is given where each node contains an additional random pointer which could point to any node or null.
 * Return a deep copy of the list.
 *
 * 🔍 Example:
 * Input: head = [7,null],[13,0],[11,4],[10,2],[1,0]
 * Output: deep copy of list with same structure
 *
 * 🎯 Key Insight:
 * Use a hashmap or weave original/clone nodes together to maintain random linkage.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use a map from original to cloned nodes
 *
 * ✅ Alternative:
 * In-place interleaving copy and then detach
 *
 * ✅ Transition:
 * Step 1: Clone each node and interleave with original
 * Step 2: Assign random pointers
 * Step 3: Separate cloned list
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) if using interleaved method
 */
class Node138 {
public:
    int val;
    Node138* next;
    Node138* random;

    Node138(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

Node138* CopyRandomList(Node138* head) {
    if (!head) return nullptr;

    // Step 1: Interleave clone nodes
    Node138* curr = head;
    while (curr) {
        Node138* copy = new Node138(curr->val);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    // Step 2: Assign random pointers
    curr = head;
    while (curr) {
        if (curr->random)
            curr->next->random = curr->random->next;
        curr = curr->next->next;
    }

    // Step 3: Separate the lists
    Node138* dummy = new Node138(0);
    Node138* copy_curr = dummy;
    curr = head;
    while (curr) {
        Node138* copy = curr->next;
        curr->next = copy->next;

        copy_curr->next = copy;
        copy_curr = copy;
        curr = curr->next;
    }

    return dummy->next;
}

/**
 * Problem 31: Random Pick with Weight (LC 528)
 * --------------------------------------------------------
 * 🧠 Description:
 * You are given a list of positive integers `w` where `w[i]` is the weight of index `i`.
 * Call `PickIndex()` repeatedly to randomly pick an index proportional to its weight.
 *
 * 🔍 Example:
 * Input: w = [1, 3]
 * Output: PickIndex() returns 0 with prob 1/4, 1 with prob 3/4
 *
 * 🎯 Key Insight:
 * Use prefix sums to map index weights to intervals, then binary search.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - prefix_sums[i] = total weight up to index i
 * - total_sum = prefix_sums.back()
 *
 * ✅ Transition:
 * - Pick a number in [1, total_sum]
 * - Use lower_bound to find the interval
 *
 * ✅ Iteration:
 * - Preprocess once, then each PickIndex is O(log n)
 *
 * 🚨 Edge Cases:
 * - All weights = 1 → uniform random
 * - One weight dominates → heavily biased
 *
 * ⏱️ Time Complexity:
 * - Init: O(n)
 * - PickIndex: O(log n)
 *
 * 🧠 Space Complexity: O(n)
 */

vector<int> _prefix_sums_528;
int _total_sum_528;

void InitWeights(const vector<int>& weights) {
    _prefix_sums_528.resize(weights.size());
    _prefix_sums_528[0] = weights[0];
    for (int i = 1; i < weights.size(); ++i) {
        _prefix_sums_528[i] = _prefix_sums_528[i - 1] + weights[i];
    }
    _total_sum_528 = _prefix_sums_528.back();
}

int PickIndex() {
    int target = rand() % _total_sum_528 + 1;
    return lower_bound(_prefix_sums_528.begin(), _prefix_sums_528.end(), target) - _prefix_sums_528.begin();
}

/**
 * Problem 32: Next Permutation (LC 31)
 * -----------------------------------
 * 🧠 Description:
 * Rearranges numbers into the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, rearrange as the lowest possible order (ascending).
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [1,3,2]
 *
 * 🎯 Key Insight:
 * Find the first decreasing element from the right, then swap with the smallest larger element to its right, then reverse.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ Step 1: Scan from right to find first decreasing element nums[i - 1]
 * ✅ Step 2: Find the smallest number > nums[i - 1] on the right side (nums[j])
 * ✅ Step 3: Swap nums[i - 1] and nums[j]
 * ✅ Step 4: Reverse the subarray from i to end
 *
 * 🚨 Edge Cases:
 * - Entire array is in descending order → reverse to ascending
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
void NextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 1;

    // Step 1: Find rightmost i where nums[i - 1] < nums[i]
    while (i > 0 && nums[i - 1] >= nums[i]) i--;

    if (i > 0) {
        int j = n - 1;
        // Step 2: Find number just larger than nums[i - 1]
        while (nums[j] <= nums[i - 1]) j--;
        swap(nums[i - 1], nums[j]);
    }

    // Step 3: Reverse the decreasing suffix
    reverse(nums.begin() + i, nums.end());
}

/**
 * Problem 34: Buildings With an Ocean View (LC 1762)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given an array `heights` of buildings, return the indices of buildings with an ocean view.
 * The ocean is to the **right**, so a building has an ocean view if **all buildings to its right are shorter**.
 *
 * 🔍 Example:
 * Input: heights = [4,2,3,1]
 * Output: [0,2,3]
 *
 * 🎯 Key Insight:
 * Traverse from right to left, and track the current max height seen so far.
 * Any building taller than `max_height` can see the ocean.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - max_height: tallest building seen so far from the right
 * - result: indices of buildings with ocean view
 *
 * ✅ Transition:
 * - Iterate from right to left
 * - If current height > max_height → add to result
 *
 * ✅ Iteration Order:
 * - Reverse scan (right → left)
 *
 * 🚨 Edge Cases:
 * - Single building → always has ocean view
 * - All heights decreasing → all buildings see ocean
 * - All heights same → only the last building sees ocean
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) for result (output)
 */

vector<int> FindBuildings(vector<int>& heights) {
    vector<int> result;
    int max_height = -1;

    for (int i = heights.size() - 1; i >= 0; --i) {
        if (heights[i] > max_height) {
            result.push_back(i);
            max_height = heights[i];
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Problem 35: Kth Missing Positive Number (LC 1539)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a sorted array `arr` of positive integers and an integer `k`,
 * return the k-th missing positive number.
 *
 * 🔍 Example:
 * Input: arr = [2,3,4,7,11], k = 5
 * Output: 9
 * Explanation: Missing numbers = [1,5,6,8,9,...] → 5th is 9
 *
 * 🎯 Key Insight:
 * Use linear scan or binary search:
 * - At position `i`, missing count = arr[i] - (i + 1)
 * - Find smallest index where missing_count >= k
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ Method 1: Linear Scan
 * - Track the expected number and compare with current `arr[i]`
 * - Count how many are missing until k-th is reached
 *
 * ✅ Method 2: Binary Search (faster)
 * - missing[i] = arr[i] - (i + 1)
 * - Use BS to find first index where missing[i] ≥ k
 *
 * 🚨 Edge Cases:
 * - k-th missing is before first element → return k
 * - arr has gaps large enough to jump over k → binary search handles it
 *
 * ⏱️ Time Complexity:
 * - Linear Scan: O(n)
 * - Binary Search: O(log n)
 *
 * 🧠 Space Complexity: O(1)
 */

int FindKthPositive(vector<int>& arr, int k) {
    int left = 0, right = arr.size() - 1;

    // Binary search for smallest index where missing >= k
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int missing_count = arr[mid] - (mid + 1);

        if (missing_count < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Final answer is: left + k
    return left + k;
}

/**
 * Problem 37: Merge k Sorted Lists (LC 23)
 * --------------------------------------------------------
 * 🧠 Description:
 * You are given an array of `k` sorted linked lists.
 * Merge them into one sorted linked list and return its head.
 *
 * 🔍 Example:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 *
 * 🎯 Key Insight:
 * Use a **min-heap (priority queue)** to always extract the smallest head node among all k lists.
 * Push the next node from the same list into the heap after popping.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - Priority queue of (value, pointer) pairs, sorted by node->val
 * - Dummy head to build merged result
 *
 * ✅ Transition:
 * - Initialize heap with head of each list (if not null)
 * - Repeatedly extract min node and push its next (if any)
 *
 * ✅ Iteration:
 * - Continue until heap is empty
 *
 * 🚨 Edge Cases:
 * - Empty input list → return nullptr
 * - Some lists are empty/nullptr → skip them
 *
 * ⏱️ Time Complexity: O(N log k), where N is total number of nodes
 * 🧠 Space Complexity: O(k), size of heap
 */

struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* MergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, CompareNode> min_heap;

    for (ListNode* node : lists) {
        if (node) {
            min_heap.push(node);
        }
    }

    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;

    while (!min_heap.empty()) {
        ListNode* smallest = min_heap.top();
        min_heap.pop();

        curr->next = smallest;
        curr = curr->next;

        if (smallest->next) {
            min_heap.push(smallest->next);
        }
    }

    return dummy->next;
}

/**
 * Problem 38: Making A Large Island (LC 827)
 * --------------------------------------------------------
 * 🧠 Description:
 * You are given an n x n binary matrix grid.
 * You may change at most one 0 to 1. Return the size of the largest island possible.
 * An island is a group of 1s connected vertically or horizontally.
 *
 * 🔍 Example:
 * Input: grid = [[1, 0], [0, 1]]
 * Output: 3
 * Explanation: Change one 0 to 1 → connect two 1s into a larger island.
 *
 * 🎯 Key Insight:
 * - Step 1: Label each island with a unique ID and record its area using DFS
 * - Step 2: For each 0-cell, try changing it to 1 and check sum of connected island areas
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - `area_map`: island_id → area
 * - `grid` modified to store island_id (start from 2 to avoid confusion with 0/1)
 *
 * ✅ Transition:
 * - DFS to label each island and calculate area
 * - For each 0-cell, try adding up areas of adjacent island ids
 *
 * ✅ Iteration Order:
 * - First pass DFS to label
 * - Second pass to evaluate each 0
 *
 * 🚨 Edge Cases:
 * - All 1s → return n * n
 * - All 0s → return 1
 *
 * ⏱️ Time Complexity: O(n²)
 * 🧠 Space Complexity: O(n²) for area map and visited set
 */

int LargestIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    unordered_map<int, int> area_map;
    int island_id = 2;
    int max_area = 0;

    function<int(int, int, int)> dfs = [&](int i, int j, int id) -> int {
        if (i < 0 || j < 0 || i >= n || j >= n || grid[i][j] != 1) return 0;
        grid[i][j] = id;
        int area = 1;
        area += dfs(i + 1, j, id);
        area += dfs(i - 1, j, id);
        area += dfs(i, j + 1, id);
        area += dfs(i, j - 1, id);
        return area;
    };

    // Step 1: Label islands
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                int area = dfs(i, j, island_id);
                area_map[island_id] = area;
                max_area = max(max_area, area);
                island_id++;
            }
        }
    }

    // Step 2: Try flipping each 0
    vector<pair<int, int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                unordered_set<int> seen;
                int new_area = 1;

                for (const auto& [dx, dy] : directions) {
                    int ni = i + dx, nj = j + dy;
                    if (ni >= 0 && nj >= 0 && ni < n && nj < n && grid[ni][nj] > 1) {
                        int id = grid[ni][nj];
                        if (!seen.count(id)) {
                            new_area += area_map[id];
                            seen.insert(id);
                        }
                    }
                }

                max_area = max(max_area, new_area);
            }
        }
    }

    return max_area == 0 ? n * n : max_area;
}

/**
 * Problem 39: Group Shifted Strings (LC 249)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a list of strings, group all strings that belong to the same shifting sequence.
 * A shifting sequence is where each character can be "shifted" to the next one cyclically (a→b→c→...→z→a).
 *
 * 🔍 Example:
 * Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"]
 * Output: [["abc","bcd","xyz"],["az","ba"],["acef"],["a","z"]]
 *
 * 🎯 Key Insight:
 * Use a **shift pattern** as the grouping key.
 * Normalize each string by computing difference between each character and the first one modulo 26.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - unordered_map<string, vector<string>> to group by normalized key
 *
 * ✅ Transition:
 * - For each string, compute its shift key: difference from first char
 * - Use that key to group the strings
 *
 * ✅ Iteration:
 * - Loop through all strings, build map, return grouped result
 *
 * 🚨 Edge Cases:
 * - Single character strings → all shift to same key ("")
 * - Wrap around (e.g. 'z' → 'a') handled via modulo 26
 *
 * ⏱️ Time Complexity: O(n * m), where n = number of strings, m = average string length
 * 🧠 Space Complexity: O(n * m), for map and result storage
 */

string ComputeShiftKey(const string& s) {
    string key;
    for (int i = 1; i < s.size(); ++i) {
        int offset = (s[i] - s[i - 1] + 26) % 26;
        key += to_string(offset) + ",";
    }
    return key;
}

vector<vector<string>> GroupStrings(vector<string>& strings) {
    unordered_map<string, vector<string>> key_map;

    for (const string& s : strings) {
        string shift_key = ComputeShiftKey(s);
        key_map[shift_key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : key_map) {
        result.push_back(group);
    }

    return result;
}

/**
 * Problem 40: Course Schedule (LC 207)
 * --------------------------------------
 * 🧠 Description:
 * Given `numCourses` and a list of prerequisites, determine if it is possible to finish all courses.
 * This is equivalent to checking whether a directed graph has a cycle.
 *
 * 🔍 Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * 🎯 Key Insight:
 * Topological sort via BFS (Kahn's algorithm) or DFS cycle detection.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - indegree[i] = number of incoming edges to course i
 * - graph[i] = list of courses dependent on i
 *
 * ✅ Base Case Initialization:
 * Queue of all nodes with indegree 0
 *
 * ✅ Transition:
 * - Decrease indegree for each neighbor
 * - If indegree becomes 0, enqueue
 *
 * ✅ Iteration Order:
 * BFS
 *
 * 🚨 Edge Cases:
 * - No prerequisites → return true
 * - Self-dependency or cycle → return false
 *
 * ⏱️ Time Complexity: O(V + E)
 * 🧠 Space Complexity: O(V + E)
 */
bool CanFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (indegree[i] == 0)
            q.push(i);

    int count = 0;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        count++;

        for (int neighbor : graph[curr]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return count == numCourses;
}

/**
 * Problem 41: Best Time to Buy and Sell Stock (LC 121)
 * ------------------------------------------------------
 * 🧠 Description:
 * Given an array where the i-th element is the price of a stock on day i, find the max profit.
 * You may only complete one transaction (buy once and sell once).
 *
 * 🔍 Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5 (buy at 1, sell at 6)
 *
 * 🎯 Key Insight:
 * Track minimum price so far and calculate profit at each step.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * min_price = lowest price seen so far
 * max_profit = max(prices[i] - min_price)
 *
 * ✅ Base Case Initialization:
 * min_price = prices[0], max_profit = 0
 *
 * ✅ Transition:
 * Iterate prices:
 *   - Update min_price
 *   - Update max_profit if current profit > previous
 *
 * ✅ Iteration Order:
 * i from 1 to end
 *
 * 🚨 Edge Cases:
 * - Empty or single element → profit is 0
 * - Prices always decreasing → profit is 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int MaxProfit(vector<int>& prices) {
    if (prices.size() < 2) return 0;
    int min_price = prices[0], max_profit = 0;

    for (int i = 1; i < prices.size(); ++i) {
        min_price = min(min_price, prices[i]);
        max_profit = max(max_profit, prices[i] - min_price);
    }

    return max_profit;
}

/**
 * Problem 42: Convert Binary Search Tree to Sorted Doubly Linked List (LC 426) 🔒
 * --------------------------------------------------------------------------------
 * 🧠 Description:
 * Convert a BST to a sorted circular doubly-linked list in-place.
 *
 * 🔍 Example:
 * Input: BST [4,2,5,1,3]
 * Output: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> (circular)
 *
 * 🎯 Key Insight:
 * In-order traversal builds sorted order; link nodes as you go.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use two pointers: prev, head
 *
 * ✅ Transition:
 * During in-order traversal:
 *   - prev->right = curr; curr->left = prev
 *
 * ✅ Final:
 * Connect head and tail to make it circular
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */

// Convert a Binary Search Tree to a Circular Doubly Linked List
TreeNode* TreeToDoublyList(TreeNode* root) {
    if (!root) return nullptr;

    TreeNode* head = nullptr;  // Pointer to the head of the doubly linked list
    TreeNode* prev = nullptr;  // Pointer to the previously visited node

    // Recursive in-order traversal using std::function and lambda expression
    std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return;

        // Traverse the left subtree
        dfs(node->left);

        // Process the current node
        if (prev) {
            prev->right = node;  // Link previous node to current
            node->left = prev;   // Link current node back to previous
        } else {
            head = node;         // First node becomes the head
        }
        prev = node;             // Update previous to current

        // Traverse the right subtree
        dfs(node->right);
    };

    dfs(root);

    // After traversal, connect head and tail to make it circular
    head->left = prev;
    prev->right = head;

    return head;
}

/**
 * Problem 43: Insert into a Sorted Circular Linked List (LC 708)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a sorted circular linked list, insert a value into the list such that it remains sorted.
 * If the list is empty, create a single-node circular list.
 * Return any valid reference to the inserted node.
 *
 * 🔍 Example:
 * Input: head = [3,4,1] (circular), insert_val = 2
 * Output: [3,4,1,2] or [4,1,2,3] (any valid rotation)
 *
 * 🎯 Key Insight:
 * Since the list is circular, we have to handle:
 * - Normal ascending case (insert between two increasing nodes)
 * - Edge case (insert at rotation point, i.e., max → min)
 * - All equal values → insert anywhere
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Use `prev` and `curr` pointers to scan through list
 *
 * ✅ Transition:
 * - If insert_val fits between prev and curr → insert
 * - If at rotation point (prev > curr) and insert_val is max or min → insert
 * - If we loop once and don’t insert (all values same) → insert anywhere
 *
 * ✅ Iteration:
 * - Traverse with a do-while loop since it's circular
 *
 * 🚨 Edge Cases:
 * - Empty list → create self-pointing node
 * - All nodes have same value → insert after any node
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

ListNode* Insert(ListNode* head, int insert_val) {
    ListNode* new_node = new ListNode(insert_val);

    if (!head) {
        new_node->next = new_node;
        return new_node;
    }

    ListNode* prev = head;
    ListNode* curr = head->next;

    while (true) {
        // Case 1: insert between two nodes
        if (prev->val <= insert_val && insert_val <= curr->val) {
            break;
        }

        // Case 2: insert at rotation point (max to min)
        if (prev->val > curr->val) {
            if (insert_val >= prev->val || insert_val <= curr->val) {
                break;
            }
        }

        prev = curr;
        curr = curr->next;

        // Case 3: full loop, all values same or no valid position
        if (prev == head) break;
    }

    prev->next = new_node;
    new_node->next = curr;

    return head;
}

/**
 * Problem 44: Sum Root to Leaf Numbers (LC 129)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree where each node contains a digit (0–9),
 * each root-to-leaf path represents a number. Return the sum of all such numbers.
 *
 * 🔍 Example:
 * Input: [1,2,3]
 * Output: 25
 * Explanation: Paths are 12 and 13 → 12 + 13 = 25
 *
 * 🎯 Key Insight:
 * Use DFS to track the number formed so far while traversing down the tree.
 * At leaf nodes, add the full number to total sum.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State Definition:
 * - At each node: track current path sum as `curr_sum`
 *
 * ✅ Transition:
 * - New path sum = curr_sum * 10 + node->val
 *
 * ✅ Iteration:
 * - Pre-order DFS (root → left/right)
 *
 * 🚨 Edge Cases:
 * - Empty tree → return 0
 * - Single node → return node->val
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h) for recursion stack
 */

int SumNumbers(TreeNode* root) {
    function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int curr_sum) -> int {
        if (!node) return 0;

        int new_sum = curr_sum * 10 + node->val;

        if (!node->left && !node->right) {
            return new_sum;
        }

        return dfs(node->left, new_sum) + dfs(node->right, new_sum);
    };

    return dfs(root, 0);
}

/**
 * Problem 45: Max Consecutive Ones III (LC 1004)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a binary array `nums` and an integer `k`, return the maximum number of consecutive 1s
 * in the array if you can flip at most `k` 0s.
 *
 * 🔍 Example:
 * Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Output: 6
 * Explanation: Flip 2 zeros at positions 5 and 10 → longest 1s: [1,1,1,0,0,1,1,1,1,1,1]
 *
 * 🎯 Key Insight:
 * Use sliding window: maintain a window with at most `k` zeros,
 * expand `right` as long as valid, and shrink `left` when exceeding `k` zeros.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - left/right window pointers
 * - zero_count: number of 0s in current window
 *
 * ✅ Transition:
 * - Move right: include nums[right]
 * - If too many zeros, move left to reduce zero count
 *
 * ✅ Iteration:
 * - Standard sliding window O(n)
 *
 * 🚨 Edge Cases:
 * - All 1s → return length of array
 * - k ≥ number of 0s → return length of array
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int LongestOnes(vector<int>& nums, int k) {
    int left = 0;
    int zero_count = 0;
    int max_len = 0;

    for (int right = 0; right < nums.size(); ++right) {
        if (nums[right] == 0) {
            zero_count++;
        }

        while (zero_count > k) {
            if (nums[left] == 0) {
                zero_count--;
            }
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}

/**
 * Problem 46: Interval List Intersections (LC 986)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given two lists of closed, sorted, and disjoint intervals `first_list` and `second_list`,
 * return their intersection. Each interval is represented as a pair [start, end].
 *
 * 🔍 Example:
 * Input: first_list = [[0,2],[5,10],[13,23],[24,25]],
 *        second_list = [[1,5],[8,12],[15,24],[25,26]]
 * Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 *
 * 🎯 Key Insight:
 * Since both lists are sorted, use two pointers to find overlapping intervals in O(n) time.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - Two pointers `i` and `j` for first and second list
 * - At each step, compare first_list[i] and second_list[j]
 *
 * ✅ Transition:
 * - Overlap interval: [max(start1, start2), min(end1, end2)]
 * - Move pointer that has smaller end
 *
 * ✅ Iteration:
 * - Until either list is exhausted
 *
 * 🚨 Edge Cases:
 * - One list empty → return empty list
 * - Touching intervals (e.g., [2,4] and [4,6]) → count as intersecting at [4,4]
 *
 * ⏱️ Time Complexity: O(n + m), n = len(first_list), m = len(second_list)
 * 🧠 Space Complexity: O(1) extra, ignoring output list
 */

vector<vector<int>> IntervalIntersection(vector<vector<int>>& first_list, vector<vector<int>>& second_list) {
    vector<vector<int>> result;
    int i = 0, j = 0;

    while (i < first_list.size() && j < second_list.size()) {
        int start_max = max(first_list[i][0], second_list[j][0]);
        int end_min = min(first_list[i][1], second_list[j][1]);

        if (start_max <= end_min) {
            result.push_back({start_max, end_min});
        }

        // Move pointer with smaller end
        if (first_list[i][1] < second_list[j][1]) {
            i++;
        } else {
            j++;
        }
    }

    return result;
}

/**
 * Problem 47: Closest Binary Search Tree Value (LC 270)
 * -----------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a Binary Search Tree (BST) and a target value, return the value
 * in the BST that is closest to the target.
 *
 * 🔍 Example:
 * Input: root = [4,2,5,1,3], target = 3.714286
 * Output: 4
 *
 * 🎯 Key Insight:
 * Use BST property to traverse toward the target.
 * Keep track of the closest value seen so far by comparing absolute difference.
 *
 * 💡 Strategy:
 * -----------------------------------------------------------------
 * ✅ State:
 * - Track current closest value and minimal difference
 *
 * ✅ Transition:
 * - At each node, update `closest` if current node is nearer to target
 * - If target < node->val → go left, else go right
 *
 * ✅ Iteration:
 * - Use while-loop or recursive DFS with pruning
 *
 * 🚨 Edge Cases:
 * - Single node → return node->val
 * - Target equals some node value → return immediately
 *
 * ⏱️ Time Complexity: O(h), where h = height of BST
 * 🧠 Space Complexity: O(1) if iterative, O(h) if recursive
 */

int ClosestValue(TreeNode* root, double target) {
    int closest = root->val;
    TreeNode* curr_node = root;

    while (curr_node) {
        if (abs(curr_node->val - target) < abs(closest - target)) {
            closest = curr_node->val;
        }

        if (target < curr_node->val) {
            curr_node = curr_node->left;
        } else if (target > curr_node->val) {
            curr_node = curr_node->right;
        } else {
            return curr_node->val; // exact match
        }
    }

    return closest;
}

/**
 * Problem 48: Add Strings (LC 415)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given two non-negative integers `num1` and `num2` represented as strings,
 * return their sum as a string. You must not use built-in BigInteger or direct conversion.
 *
 * 🔍 Example:
 * Input: num1 = "11", num2 = "123"
 * Output: "134"
 *
 * 🎯 Key Insight:
 * Simulate digit-by-digit addition like elementary school math,
 * starting from the least significant digit (right to left).
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - Use indices `i` and `j` to iterate from end of num1 and num2
 * - Maintain a carry and accumulate digits in a result string
 *
 * ✅ Transition:
 * - Sum = digit1 + digit2 + carry
 * - Append (sum % 10), update carry = sum / 10
 *
 * ✅ Iteration:
 * - Continue until both strings are processed and carry is 0
 *
 * 🚨 Edge Cases:
 * - One string longer than the other
 * - Final carry-over (e.g. "9" + "9" → "18")
 *
 * ⏱️ Time Complexity: O(n), where n = max(len1, len2)
 * 🧠 Space Complexity: O(n)
 */

string AddStrings(string num1, string num2) {
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int carry = 0;
    string result;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = i >= 0 ? num1[i--] - '0' : 0;
        int digit2 = j >= 0 ? num2[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back('0' + (sum % 10));
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Problem 49: Minimum Window Substring (LC 76)
 * ---------------------------------------------
 * 🧠 Description:
 * Given two strings `s` and `t`, return the minimum window in `s` which contains all characters in `t`.
 *
 * 🔍 Example:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 *
 * 🎯 Key Insight:
 * Use sliding window with character counting to track window validity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * freqT = character counts of t, window = character counts in current window
 *
 * ✅ Transition:
 * Expand right until valid ⇒ shrink left to minimize
 *
 * ✅ Iteration Order:
 * right = 0 to s.length()
 *
 * 🚨 Edge Cases:
 * - No valid window ⇒ return ""
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (fixed char set size)
 */
string MinWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> freq_t;
    for (char c : t) freq_t[c]++;

    int left = 0, right = 0, required = freq_t.size();
    unordered_map<char, int> window;
    int formed = 0, start = 0, min_len = INT_MAX;

    while (right < s.size()) {
        char c = s[right++];
        window[c]++;
        if (freq_t.count(c) && window[c] == freq_t[c]) formed++;

        while (formed == required) {
            if (right - left < min_len) {
                start = left;
                min_len = right - left;
            }
            char d = s[left++];
            if (freq_t.count(d) && window[d]-- == freq_t[d]) formed--;
        }
    }

    return min_len == INT_MAX ? "" : s.substr(start, min_len);
}

/**
 * Problem 50: Two Sum (LC 1)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers `nums` and an integer `target`,
 * return the indices of the two numbers such that they add up to `target`.
 * Assume each input has exactly one solution, and no duplicate usage.
 *
 * 🔍 Example:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1] (because 2 + 7 = 9)
 *
 * 🎯 Key Insight:
 * Use a hash map to store each value and its index as we iterate.
 * For each number `x`, check if `target - x` is already in the map.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - unordered_map<int, int>: value → index
 *
 * ✅ Transition:
 * - For each number:
 *     - If complement exists in map → return its index + current index
 *     - Else insert current number and its index into map
 *
 * ✅ Iteration:
 * - Single pass through `nums`
 *
 * 🚨 Edge Cases:
 * - No solution? (Not possible as per problem)
 * - Negative numbers, zero, duplicates? Handled naturally
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

vector<int> TwoSum(vector<int>& nums, int target) {
    unordered_map<int, int> index_map;

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (index_map.count(complement)) {
            return {index_map[complement], i};
        }
        index_map[nums[i]] = i;
    }

    return {}; // guaranteed to have one solution per constraints
}

/**
 * Problem 51: Clone Graph (LC 133)
 * ---------------------------------
 * 🧠 Description:
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 *
 * 🔍 Example:
 * Input: Node with value 1, connected to [2, 4]
 * Output: Cloned graph with same structure
 *
 * 🎯 Key Insight:
 * Use DFS or BFS and a visited map to avoid cycles and duplicate cloning.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * visited[node] = cloned copy of node
 *
 * ✅ Transition:
 * For each neighbor, recursively clone it and add to the cloned node’s neighbors
 *
 * ✅ Iteration Order:
 * DFS traversal (recursive)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
class Node133 {
public:
    int val;
    vector<Node133*> neighbors;
    Node133() : val(0), neighbors({}) {}
    Node133(int _val) : val(_val), neighbors({}) {}
};

Node133* CloneGraphDFS(Node133* node, unordered_map<Node133*, Node133*>& visited) {
    if (!node) return nullptr;
    if (visited.count(node)) return visited[node];

    Node133* clone = new Node133(node->val);
    visited[node] = clone;

    for (Node133* neighbor : node->neighbors) {
        clone->neighbors.push_back(CloneGraphDFS(neighbor, visited));
    }

    return clone;
}

Node133* CloneGraph(Node133* node) {
    unordered_map<Node133*, Node133*> visited;
    return CloneGraphDFS(node, visited);
}

/**
 * Problem 52: Valid Number (LC 65)
 * --------------------------------------------------------
 * 🧠 Description:
 * Validate if a given string is a valid number.
 * A number can include:
 * - digits (0–9)
 * - optional decimal point `.`
 * - optional exponent part with 'e' or 'E' followed by signed integer
 * - optional leading '+' or '-'
 *
 * 🔍 Examples:
 * Input: "0" → true
 * Input: "e" → false
 * Input: "2e10" → true
 * Input: " -90e3   " → true
 * Input: " 1e" → false
 * Input: "e3" → false
 * Input: "6e-1" → true
 * Input: "99e2.5" → false
 *
 * 🎯 Key Insight:
 * Simulate a finite state machine (FSM) or use flag-based parsing.
 * Track what has been seen: digit, '.', 'e', signs.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - seen_digit: any digit before or after 'e'
 * - seen_dot: one dot allowed before 'e'
 * - seen_e: one 'e' allowed; must be followed by digit
 * - after_e_digit: digit required after 'e'
 *
 * ✅ Transition:
 * - If digit → update digit flags
 * - If dot → only allow before 'e' and only once
 * - If 'e' → only allow once and must be after digit
 * - If '+' or '-' → only allowed at beginning or after 'e'
 *
 * 🚨 Edge Cases:
 * - Leading/trailing spaces → must be trimmed before
 * - Dot with no digits → invalid (e.g. ".")
 * - Exponent without digits after → invalid
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

bool IsNumber(string s) {
    int i = 0, n = s.size();

    // Trim leading/trailing spaces
    while (i < n && s[i] == ' ') i++;
    if (i == n) return false;

    int j = n - 1;
    while (j >= 0 && s[j] == ' ') j--;
    if (j < i) return false;

    bool seen_digit = false;
    bool seen_dot = false;
    bool seen_e = false;
    bool digit_after_e = true; // default true in case no 'e'

    for (int k = i; k <= j; ++k) {
        char c = s[k];

        if (isdigit(c)) {
            seen_digit = true;
            if (seen_e) digit_after_e = true;
        } else if (c == '+' || c == '-') {
            if (k != i && s[k - 1] != 'e' && s[k - 1] != 'E') return false;
        } else if (c == '.') {
            if (seen_dot || seen_e) return false;
            seen_dot = true;
        } else if (c == 'e' || c == 'E') {
            if (seen_e || !seen_digit) return false;
            seen_e = true;
            digit_after_e = false;
        } else {
            return false;
        }
    }

    return seen_digit && digit_after_e;
}

/**
 * Problem 53: Remove Nth Node From End of List (LC 19)
 * ------------------------------------------------------------------
 * 🧠 Description:
 * Given the head of a singly linked list, remove the n-th node from the end of the list
 * and return its head.
 *
 * 🔍 Example:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 *
 * 🎯 Key Insight:
 * Use two-pointer technique:
 * - Advance the first pointer by n steps
 * - Then move both pointers until first reaches the end
 * - Second will be at the node **before** the one to delete
 *
 * 💡 Strategy:
 * ------------------------------------------------------------------
 * ✅ State:
 * - Dummy node before head to handle edge cases cleanly
 * - Two pointers: `first` and `second` start at dummy
 *
 * ✅ Transition:
 * - Advance `first` by n+1 steps
 * - Move both until `first` hits null
 * - `second->next` is the node to delete
 *
 * ✅ Iteration:
 * - Single pass through list
 *
 * 🚨 Edge Cases:
 * - n equals length → remove head
 * - One-node list → return nullptr
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

ListNode* RemoveNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* first = dummy;
    ListNode* second = dummy;

    // Advance first by n+1 steps to make gap of n
    for (int i = 0; i <= n; ++i) {
        first = first->next;
    }

    // Move both pointers until first reaches end
    while (first) {
        first = first->next;
        second = second->next;
    }

    // Delete the target node
    ListNode* node_to_delete = second->next;
    second->next = second->next->next;
    delete node_to_delete;

    return dummy->next;
}

/**
 * Problem 54: All Nodes Distance K in Binary Tree (LC 863)
 * ------------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree with a target node, return all nodes that are exactly K distance away from the target.
 *
 * 🔍 Example:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
 * Output: [7,4,1]
 *
 * 🎯 Key Insight:
 * This is a **graph BFS** problem:
 * - Convert the tree to an undirected graph using parent pointers
 * - Then BFS from `target` node to find all nodes at distance K
 *
 * 💡 Strategy:
 * ------------------------------------------------------------------
 * ✅ Step 1: DFS to record parent of each node
 * ✅ Step 2: BFS from `target`, avoid revisiting via `visited` set
 *
 * ✅ Iteration:
 * - Level-order traversal with distance tracking
 *
 * 🚨 Edge Cases:
 * - K == 0 → return target itself
 * - Target is leaf or root → no parent or no children
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

void BuildParentMap(TreeNode* node, TreeNode* parent,
                    unordered_map<TreeNode*, TreeNode*>& parent_map) {
    if (!node) return;
    parent_map[node] = parent;
    BuildParentMap(node->left, node, parent_map);
    BuildParentMap(node->right, node, parent_map);
}

vector<int> DistanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parent_map;
    BuildParentMap(root, nullptr, parent_map);

    unordered_set<TreeNode*> visited;
    queue<pair<TreeNode*, int>> bfs_queue;
    bfs_queue.push({target, 0});
    visited.insert(target);

    vector<int> result;

    while (!bfs_queue.empty()) {
        auto [node, dist] = bfs_queue.front();
        bfs_queue.pop();

        if (dist == k) {
            result.push_back(node->val);
        }

        if (dist > k) break;

        for (TreeNode* neighbor : {node->left, node->right, parent_map[node]}) {
            if (neighbor && !visited.count(neighbor)) {
                visited.insert(neighbor);
                bfs_queue.push({neighbor, dist + 1});
            }
        }
    }

    return result;
}

/**
 * Problem 55: Valid Parentheses (LC 20)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given a string containing only '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * A string is valid if:
 * - Open brackets are closed by the same type of brackets
 * - Open brackets are closed in the correct order
 *
 * 🔍 Example:
 * Input: s = "()[]{}"
 * Output: true
 *
 * Input: s = "(]"
 * Output: false
 *
 * 🎯 Key Insight:
 * Use a **stack** to store opening brackets.
 * When encountering a closing bracket, pop from the stack and check for match.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - Stack for opening brackets
 * - Hash map for matching pairs
 *
 * ✅ Transition:
 * - If opening: push to stack
 * - If closing: check if stack top matches; else invalid
 *
 * ✅ Iteration:
 * - One pass over string
 *
 * 🚨 Edge Cases:
 * - Empty string → valid
 * - Only opening/closing brackets → invalid
 * - Wrong order → invalid
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

bool IsValid(string s) {
    unordered_map<char, char> bracket_map = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    stack<char> char_stack;

    for (char c : s) {
        if (bracket_map.count(c)) {
            if (char_stack.empty() || char_stack.top() != bracket_map[c]) {
                return false;
            }
            char_stack.pop();
        } else {
            char_stack.push(c);
        }
    }

    return char_stack.empty();
}

/**
 * Problem 56: Longest Substring Without Repeating Characters (LC 3)
 * ---------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, find the length of the longest substring without repeating characters.
 *
 * 🔍 Example:
 * Input: s = "abcabcbb"
 * Output: 3   // "abc"
 *
 * Input: s = "bbbbb"
 * Output: 1   // "b"
 *
 * 🎯 Key Insight:
 * Use the **sliding window** technique with a hash map to track the last seen position of each character.
 * Move the left pointer only when a duplicate is found.
 *
 * 💡 Strategy:
 * ---------------------------------------------------------------------
 * ✅ State:
 * - left: left side of the window (start of substring)
 * - char_index[c]: last index of character c
 * - max_len: maximum substring length so far
 *
 * ✅ Transition:
 * - If s[i] was seen and its index ≥ left → move left to char_index[s[i]] + 1
 * - Update char_index[s[i]] = i
 * - Update max_len = max(max_len, i - left + 1)
 *
 * ✅ Iteration:
 * - One pass sliding window from left to right
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - All unique → return s.length()
 * - All same → return 1
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) — size of ASCII map (256 max)
 */

int LengthOfLongestSubstring(string s) {
    unordered_map<char, int> char_index;
    int left = 0, max_len = 0;

    for (int right = 0; right < s.size(); ++right) {
        char c = s[right];

        if (char_index.count(c) && char_index[c] >= left) {
            left = char_index[c] + 1;
        }

        char_index[c] = right;
        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}

/**
 * Problem 57: Remove Duplicates from Sorted Array (LC 26)
 * -------------------------------------------------------
 * 🧠 Description:
 * Remove duplicates in-place from sorted array and return new length.
 *
 * 🔍 Example:
 * Input: nums = [1,1,2]
 * Output: 2 (nums = [1,2,_])
 *
 * 🎯 Key Insight:
 * Use two pointers: one for current position, one for overwrite position.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * slow = index of next unique position, fast = scanner
 *
 * ✅ Base Case Initialization:
 * slow = 1
 *
 * ✅ Transition:
 * If nums[fast] != nums[fast - 1], assign nums[slow++] = nums[fast]
 *
 * ✅ Iteration Order:
 * fast = 1 to n - 1
 *
 * 🚨 Edge Cases:
 * - Empty array → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int RemoveDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 1;

    for (int fast = 1; fast < nums.size(); ++fast) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow++] = nums[fast];  // Overwrite duplicate
        }
    }

    return slow;
}

/**
 * Problem 58: Contains Duplicate II (LC 219)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return true
 * if there are two distinct indices i and j such that:
 * - nums[i] == nums[j]
 * - abs(i - j) <= k
 *
 * 🔍 Example:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 *
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 *
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 *
 * 🎯 Key Insight:
 * Use a hash map to store the last index of each value seen so far.
 * If a value reappears and the index difference is ≤ k, return true.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - unordered_map<int, int>: num → last seen index
 *
 * ✅ Transition:
 * - For each num at index i:
 *   - If num in map and i - map[num] ≤ k → return true
 *   - Else update map[num] = i
 *
 * ✅ Iteration:
 * - Single pass over nums
 *
 * 🚨 Edge Cases:
 * - k = 0 → always false unless duplicate at same index (not allowed)
 * - nums length < 2 → return false
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

bool ContainsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> index_map;

    for (int i = 0; i < nums.size(); ++i) {
        if (index_map.count(nums[i])) {
            int last_index = index_map[nums[i]];
            if (i - last_index <= k) {
                return true;
            }
        }
        index_map[nums[i]] = i;
    }

    return false;
}

/**
 * Problem 59: Remove All Adjacent Duplicates In String (LC 1047)
 * ---------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, repeatedly remove adjacent duplicate characters until
 * no more can be removed. Return the final string.
 *
 * 🔍 Example:
 * Input: s = "abbaca"
 * Output: "ca"
 * Explanation: "abbaca" → "a**bb**aca" → "aaca" → "c**aa**" → "ca"
 *
 * 🎯 Key Insight:
 * Use a **stack** to simulate the process:
 * - If current character matches the top of the stack → pop it
 * - Else → push current character
 *
 * 💡 Strategy:
 * ---------------------------------------------------------------------
 * ✅ State:
 * - Stack to hold characters that haven't been removed
 *
 * ✅ Transition:
 * - If top == current char → pop
 * - Else → push
 *
 * ✅ Iteration:
 * - One pass through the string
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - No duplicates at all → return original
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n), for stack
 */

string RemoveDuplicates(string s) {
    stack<char> char_stack;

    for (char c : s) {
        if (!char_stack.empty() && char_stack.top() == c) {
            char_stack.pop();
        } else {
            char_stack.push(c);
        }
    }

    string result;
    while (!char_stack.empty()) {
        result.push_back(char_stack.top());
        char_stack.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Problem 60: Exclusive Time of Functions (LC 636)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given the logs of `n` functions that ran on a single-threaded CPU.
 * Each log is formatted as "function_id:start_or_end:timestamp".
 * Return the **exclusive time** of each function — total time not including any child function calls.
 *
 * 🔍 Example:
 * Input:
 * n = 2
 * logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
 * Output: [3,4]
 *
 * 🎯 Key Insight:
 * Use a **stack** to simulate the call stack of function execution.
 * Track the `prev_time` to accumulate exclusive time only for the current active function.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - `func_stack`: holds function IDs currently on the call stack
 * - `prev_time`: timestamp of previous event
 * - `result[i]`: exclusive time of function i
 *
 * ✅ Transition:
 * - On "start": if stack not empty, update result[top] += curr_time - prev_time
 * - On "end": pop from stack, add duration = curr_time - prev_time + 1, and update prev_time = curr_time + 1
 *
 * ✅ Iteration:
 * - Single pass through all logs
 *
 * 🚨 Edge Cases:
 * - First event must be a start
 * - Log timestamps are guaranteed valid and well-ordered
 *
 * ⏱️ Time Complexity: O(m), where m = logs.size()
 * 🧠 Space Complexity: O(n + m), for result and call stack
 */

vector<int> ExclusiveTime(int n, vector<string>& logs) {
    vector<int> result(n, 0);
    stack<int> func_stack;
    int prev_time = 0;

    for (const string& log : logs) {
        int id, time;
        string type;

        // Parse log: format is "id:type:time"
        size_t p1 = log.find(':');
        size_t p2 = log.find(':', p1 + 1);
        id = stoi(log.substr(0, p1));
        type = log.substr(p1 + 1, p2 - p1 - 1);
        time = stoi(log.substr(p2 + 1));

        if (type == "start") {
            if (!func_stack.empty()) {
                result[func_stack.top()] += time - prev_time;
            }
            func_stack.push(id);
            prev_time = time;
        } else { // type == "end"
            result[func_stack.top()] += time - prev_time + 1;
            func_stack.pop();
            prev_time = time + 1;
        }
    }

    return result;
}

/**
 * Problem 61: Median of Two Sorted Arrays (LC 4)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given two sorted arrays `nums1` and `nums2`, return the median of the two sorted arrays.
 * The overall runtime complexity should be O(log(min(m,n))).
 *
 * 🔍 Example:
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.0
 *
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.5
 *
 * 🎯 Key Insight:
 * Use binary search on the smaller array to partition both arrays
 * such that left parts and right parts are properly balanced.
 *
 * 💡 Strategy: Binary Search Partition
 * ----------------------------------------------------------------
 * ✅ State:
 * - We always binary search on the shorter array to minimize complexity.
 * - Total left count = (n1 + n2 + 1) / 2
 *
 * ✅ Transition:
 * - Choose partition i in nums1 → j = total_left - i
 * - Compare left_max1, right_min1 with left_max2, right_min2
 *
 * ✅ Base Condition:
 * - If left_max1 ≤ right_min2 && left_max2 ≤ right_min1 → valid partition
 *
 * 🚨 Edge Cases:
 * - Empty array → treat left_max or right_min as ±∞
 *
 * ⏱️ Time Complexity: O(log(min(m, n)))
 * 🧠 Space Complexity: O(1)
 */

double FindMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is the smaller array
    if (nums1.size() > nums2.size()) {
        return FindMedianSortedArrays(nums2, nums1);
    }

    int n1 = nums1.size(), n2 = nums2.size();
    int left = 0, right = n1;
    int total_left = (n1 + n2 + 1) / 2;

    while (left <= right) {
        int i = left + (right - left) / 2;
        int j = total_left - i;

        int left_max1 = (i == 0) ? INT_MIN : nums1[i - 1];
        int right_min1 = (i == n1) ? INT_MAX : nums1[i];

        int left_max2 = (j == 0) ? INT_MIN : nums2[j - 1];
        int right_min2 = (j == n2) ? INT_MAX : nums2[j];

        if (left_max1 <= right_min2 && left_max2 <= right_min1) {
            if ((n1 + n2) % 2 == 0) {
                return (max(left_max1, left_max2) + min(right_min1, right_min2)) / 2.0;
            } else {
                return max(left_max1, left_max2);
            }
        } else if (left_max1 > right_min2) {
            right = i - 1;
        } else {
            left = i + 1;
        }
    }

    return 0.0; // should never reach here
}

/**
 * Problem 62: Sliding Window Median (LC 480)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an array `nums` and a sliding window size `k`, return the median of each window.
 *
 * 🔍 Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]
 *
 * 🎯 Key Insight:
 * Maintain two multisets (`small` and `large`) to simulate a balanced min/max heap:
 * - `small`: max heap (stores the smaller half)
 * - `large`: min heap (stores the larger half)
 * Balance sizes so that:
 * - if k is odd: small has 1 more than large → median is *small.rbegin()
 * - if k is even: average of *small.rbegin() and *large.begin()
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - multiset<int> small, large
 * - Balance after each insert/remove
 *
 * ✅ Transition:
 * - Insert new element to one side, rebalance if needed
 * - Remove outgoing element from corresponding multiset
 *
 * ✅ Iteration:
 * - Start inserting until k elements, then slide the window one-by-one
 *
 * 🚨 Edge Cases:
 * - Negative numbers, duplicates
 * - Even/odd window sizes
 *
 * ⏱️ Time Complexity: O(n log k)
 * 🧠 Space Complexity: O(k)
 */

class SlidingWindowMedian {
private:
    multiset<int> small_; // max heap (lower half)
    multiset<int> large_; // min heap (upper half)

    void Rebalance() {
        // Balance sizes: small can be equal or 1 more than large
        while (small_.size() > large_.size() + 1) {
            large_.insert(*small_.rbegin());
            small_.erase(prev(small_.end()));
        }
        while (large_.size() > small_.size()) {
            small_.insert(*large_.begin());
            large_.erase(large_.begin());
        }
    }

    void Insert(int num) {
        if (small_.empty() || num <= *small_.rbegin()) {
            small_.insert(num);
        } else {
            large_.insert(num);
        }
        Rebalance();
    }

    void Erase(int num) {
        if (small_.count(num)) {
            small_.erase(small_.find(num));
        } else {
            large_.erase(large_.find(num));
        }
        Rebalance();
    }

    double GetMedian() {
        if (small_.size() > large_.size()) {
            return *small_.rbegin();
        } else {
            return (*small_.rbegin() + *large_.begin()) / 2.0;
        }
    }

public:
    vector<double> MedianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;

        for (int i = 0; i < nums.size(); ++i) {
            Insert(nums[i]);
            if (i >= k) {
                Erase(nums[i - k]);
            }
            if (i >= k - 1) {
                result.push_back(GetMedian());
            }
        }

        return result;
    }
};

/**
 * Problem 63: Palindromic Substrings (LC 647)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the number of palindromic substrings in it.
 * A substring is palindromic if it reads the same forward and backward.
 *
 * 🔍 Example:
 * Input: s = "abc"
 * Output: 3  // "a", "b", "c"
 *
 * Input: s = "aaa"
 * Output: 6  // "a", "a", "a", "aa", "aa", "aaa"
 *
 * 🎯 Key Insight:
 * Use the **expand-around-center** technique to count all odd and even length palindromes.
 * There are 2n - 1 centers in a string of length n (each character and the gap between characters).
 *
 * 💡 Strategy: Expand Around Center
 * ----------------------------------------------------------------
 * ✅ State Definition:
 * - For each center index from 0 to 2n - 2:
 *   - Let `left = center / 2`
 *   - Let `right = left + (center % 2)`
 *   - We expand around the center while s[left] == s[right]
 *
 * ✅ Transition:
 * - While left >= 0 && right < n && s[left] == s[right]:
 *     - We found a valid palindrome: s[left..right]
 *     - count++
 *     - Expand window outward: left--, right++
 *
 * ✅ Iteration Order:
 * - Center loop: center = 0 to 2n - 2
 * - Expansion loop: while valid, expand outward
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - All identical chars → n(n+1)/2 palindromes
 * - No palindromes longer than 1 → still count single characters
 *
 * ⏱️ Time Complexity: O(n²)
 * 🧠 Space Complexity: O(1)
 */

int CountSubstrings(string s) {
    int n = s.size();
    int count = 0;

    for (int center = 0; center < 2 * n - 1; ++center) {
        int left = center / 2;
        int right = left + (center % 2);  // Handles odd and even length centers

        // 🔁 Transition: expand as long as s[left..right] is a valid palindrome
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }

    return count;
}

/**
 * Problem 64: Valid Palindrome III (LC 1216)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s` and an integer `k`, return true if `s` can be transformed into
 * a palindrome by removing at most `k` characters.
 *
 * 🔍 Example:
 * Input: s = "abcdeca", k = 2
 * Output: true
 * Explanation: Remove 'b' and 'e' to make "acdca", which is a palindrome.
 *
 * 🎯 Key Insight:
 * The problem is equivalent to asking:
 * - Can we make `s` a palindrome by deleting ≤ k characters?
 * - Equivalently: Are there at least `n - k` characters forming a palindromic subsequence?
 * Use bottom-up DP to compute minimum deletions to make a substring palindrome.
 *
 * 💡 Strategy: DP — Minimum Deletions to Palindrome
 * ----------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = minimum number of deletions needed to make s[i..j] a palindrome
 *
 * ✅ Base Case:
 * - dp[i][i] = 0   // single character is always a palindrome
 * - dp[i][i+1] = 0 if s[i] == s[i+1], else 1
 *
 * ✅ Transition:
 * - If s[i] == s[j]:
 *     dp[i][j] = dp[i+1][j-1]
 * - Else:
 *     dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1])
 *     // we remove either s[i] or s[j]
 *
 * ✅ Iteration Order:
 * - Bottom-up: i from n-1 → 0, j from i+1 → n-1
 *
 * 🚨 Edge Cases:
 * - Empty string → true
 * - k ≥ len(s) → always true
 *
 * ⏱️ Time Complexity: O(n²)
 * 🧠 Space Complexity: O(n²)
 */

bool IsValidPalindrome(string s, int k) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Build DP table bottom-up
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1] <= k;
}

/**
 * Problem 65: Design Tic-Tac-Toe (LC 348)
 * --------------------------------------------------------
 * 🧠 Description:
 * Design a Tic-Tac-Toe game class for an `n x n` board.
 * Two players take turns marking the board with 1 and 2.
 * The game ends when one player wins (by placing n of their marks in a row/column/diagonal).
 *
 * Provide a function:
 * - `int move(int row, int col, int player)` → return 0 if no one wins yet, or player number if they win
 *
 * 🔍 Example:
 * TicTacToeMove(0, 0, 1) → 0
 * TicTacToeMove(0, 2, 2) → 0
 * TicTacToeMove(2, 2, 1) → 0
 * TicTacToeMove(1, 1, 2) → 0
 * TicTacToeMove(2, 0, 1) → 0
 * TicTacToeMove(1, 0, 2) → 0
 * TicTacToeMove(2, 1, 1) → 1  // player 1 wins
 *
 * 🎯 Key Insight:
 * Don’t maintain the whole board — just track:
 * - row sums
 * - column sums
 * - diagonal / anti-diagonal sums
 *
 * Let player 1 add +1, player 2 add -1.
 * When abs(row/col/diag sum) == n → that player wins.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - `_rows_348[i]`: net count in row i
 * - `_cols_348[j]`: net count in col j
 * - `_diag_348`, `_anti_diag_348`: net count in two diagonals
 *
 * ✅ Transition:
 * - move(row, col, player): update relevant counts with +1/-1
 * - if any of them reach ±n → return winner
 *
 * ✅ Iteration:
 * - Single operation per move
 *
 * 🚨 Edge Cases:
 * - Invalid move not considered (as per constraints)
 * - Both diagonals overlap at center (update both)
 *
 * ⏱️ Time Complexity: O(1) per move
 * 🧠 Space Complexity: O(n)
 */

vector<int> _rows_348, _cols_348;
int _diag_348, _anti_diag_348, _n_348;

void TicTacToeInit(int n) {
    _n_348 = n;
    _rows_348.assign(n, 0);
    _cols_348.assign(n, 0);
    _diag_348 = 0;
    _anti_diag_348 = 0;
}

int TicTacToeMove(int row, int col, int player) {
    int delta = (player == 1) ? 1 : -1;

    _rows_348[row] += delta;
    _cols_348[col] += delta;
    if (row == col) {
        _diag_348 += delta;
    }
    if (row + col == _n_348 - 1) {
        _anti_diag_348 += delta;
    }

    if (abs(_rows_348[row]) == _n_348 ||
        abs(_cols_348[col]) == _n_348 ||
        abs(_diag_348) == _n_348 ||
        abs(_anti_diag_348) == _n_348) {
        return player;
    }

    return 0;
}

/**
 * Problem 66: Robot Room Cleaner (LC 489)
 * --------------------------------------------------------
 * 🧠 Description:
 * You are controlling a robot in a room modeled as a grid. The robot can:
 * - move(): returns true if the cell in front is open and robot moves
 * - turnLeft(), turnRight(): rotate robot 90 degrees
 * - clean(): clean the current cell
 *
 * You do not have access to the room layout. The goal is to clean the entire room.
 * Robot starts from an unknown position and orientation.
 *
 * 🎯 Key Insight:
 * - Treat the room as an implicit graph
 * - Use DFS + backtracking to explore and clean each reachable cell
 * - Track visited positions with a coordinate map (e.g. (x,y))
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - Position: (x, y)
 * - Facing direction: 0=up, 1=right, 2=down, 3=left
 * - Visited set to avoid revisiting cleaned cells
 *
 * ✅ Transition:
 * - Try all 4 directions from current cell:
 *     - If move() returns true, recurse from new cell
 *     - After recursion, backtrack: turn 180°, move back, turn 180° again
 *
 * ✅ Iteration Order:
 * - For each cell, try directions (current facing + 0 to 3) % 4
 *
 * 🚨 Edge Cases:
 * - Robot starts near wall or in enclosed area
 * - Room may not be rectangular
 *
 * ⏱️ Time Complexity: O(mn), m = rows, n = cols (clean every cell once)
 * 🧠 Space Complexity: O(mn), for visited set and recursion stack
 */

// Assume Robot interface is given:
class Robot {
public:
    bool move();
    void turnLeft();
    void turnRight();
    void clean();
};

// === DFS Implementation with Coordinate + Direction Management ===

set<pair<int, int>> _visited_489;
vector<pair<int, int>> _dirs_489 = {{-1,0}, {0,1}, {1,0}, {0,-1}};  // up, right, down, left

void GoBack(Robot& robot) {
    robot.turnRight();
    robot.turnRight();
    robot.move();
    robot.turnRight();
    robot.turnRight();
}

void CleanRoom(Robot& robot) {
    _visited_489.clear();

    function<void(int, int, int)> dfs = [&](int x, int y, int dir) {
        _visited_489.insert({x, y});
        robot.clean();

        for (int i = 0; i < 4; ++i) {
            int new_dir = (dir + i) % 4;
            int nx = x + _dirs_489[new_dir].first;
            int ny = y + _dirs_489[new_dir].second;

            if (!_visited_489.count({nx, ny}) && robot.move()) {
                dfs(nx, ny, new_dir);
                GoBack(robot);
            }

            robot.turnRight();  // rotate to try next direction
        }
    };

    dfs(0, 0, 0);  // start at (0,0) facing up
}

/**
 * Problem 67: Expression Add Operators (LC 282)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `num` containing only digits and an integer `target`,
 * return all valid expressions that can be built by adding binary operators '+', '-', or '*'
 * between digits such that the expression evaluates to `target`.
 *
 * 🔍 Example:
 * Input: num = "123", target = 6
 * Output: ["1+2+3", "1*2*3"]
 *
 * Input: num = "105", target = 5
 * Output: ["1*0+5", "10-5"]
 *
 * 🎯 Key Insight:
 * Use DFS + backtracking:
 * - At each step, try all possible splits of remaining string
 * - Apply each operator and recursively evaluate
 * - Special handling for multiplication due to precedence
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - pos: current index in num
 * - expr: current expression string
 * - curr_val: current evaluated value of expr
 * - prev_operand: value of last operand (used for '*')
 *
 * ✅ Transition:
 * - Try all splits from pos to end of num
 * - For each substring:
 *     - If at pos==0 → take as first number
 *     - Else try '+', '-', '*' with recursion
 *     - For '*': adjust curr_val to handle precedence:
 *         new_val = (curr_val - prev_operand) + (prev_operand * curr_num)
 *
 * ✅ Edge Cases:
 * - Leading zero in multi-digit number is invalid ("05" ❌)
 *
 * ⏱️ Time Complexity: O(4^n)
 * 🧠 Space Complexity: O(n) recursion stack
 */

vector<string> AddOperators(string num, int target) {
    vector<string> result;

    function<void(int, long long, long long, string)> dfs =
        [&](int pos, long long curr_val, long long prev_operand, string expr) {
            if (pos == num.size()) {
                if (curr_val == target) result.push_back(expr);
                return;
            }

            for (int i = pos; i < num.size(); ++i) {
                // Skip numbers with leading zero
                if (i != pos && num[pos] == '0') break;

                string curr_str = num.substr(pos, i - pos + 1);
                long long curr_num = stoll(curr_str);

                if (pos == 0) {
                    // First number: no operator
                    dfs(i + 1, curr_num, curr_num, curr_str);
                } else {
                    dfs(i + 1, curr_val + curr_num,  curr_num,  expr + "+" + curr_str);
                    dfs(i + 1, curr_val - curr_num, -curr_num,  expr + "-" + curr_str);
                    dfs(i + 1, curr_val - prev_operand + prev_operand * curr_num,
                        prev_operand * curr_num, expr + "*" + curr_str);
                }
            }
        };

    dfs(0, 0, 0, "");
    return result;
}

/**
 * Problem 68: Find Median from Data Stream (LC 295)
 * --------------------------------------------------------
 * 🧠 Description:
 * Design a data structure that supports:
 * - addNum(int num): adds a number to the data structure
 * - findMedian(): returns the median of all elements added so far
 *
 * 🔍 Example:
 * Add 1, Add 2 → median = 1.5
 * Add 3 → median = 2.0
 *
 * 🎯 Key Insight:
 * Use two heaps to keep the stream balanced:
 * - max_heap (left half): stores the smaller half (inverted for max behavior)
 * - min_heap (right half): stores the larger half
 * Maintain:
 * - size difference ≤ 1
 * - max_heap.top() <= min_heap.top()
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - _max_heap_295: max heap for lower half
 * - _min_heap_295: min heap for upper half
 *
 * ✅ Transition:
 * - Insert to max_heap first, then balance to min_heap
 * - Ensure size balance (max_heap can be at most 1 larger)
 *
 * ✅ Iteration:
 * - Each insert: O(log n)
 * - Median query: O(1)
 *
 * 🚨 Edge Cases:
 * - No elements → undefined
 * - Odd vs even size determines how median is taken
 *
 * ⏱️ Time Complexity:
 * - addNum: O(log n)
 * - findMedian: O(1)
 * 🧠 Space Complexity: O(n)
 */

priority_queue<int> _max_heap_295;                               // Max heap (left half)
priority_queue<int, vector<int>, greater<int>> _min_heap_295;   // Min heap (right half)

void MedianFinder295Init() {
    while (!_max_heap_295.empty()) _max_heap_295.pop();
    while (!_min_heap_295.empty()) _min_heap_295.pop();
}

void MedianFinder295AddNum(int num) {
    _max_heap_295.push(num);

    // Balance: max_heap top should be <= min_heap top
    _min_heap_295.push(_max_heap_295.top());
    _max_heap_295.pop();

    // Rebalance size (max_heap allowed to be larger)
    if (_max_heap_295.size() < _min_heap_295.size()) {
        _max_heap_295.push(_min_heap_295.top());
        _min_heap_295.pop();
    }
}

double MedianFinder295FindMedian() {
    if (_max_heap_295.size() > _min_heap_295.size()) {
        return _max_heap_295.top();
    } else {
        return (_max_heap_295.top() + _min_heap_295.top()) / 2.0;
    }
}

/**
 * Problem 69: Minimum Add to Make Parentheses Valid (LC 921)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s` containing only `'('` and `')'`, return the minimum number of parentheses
 * needed to be added to make the string valid.
 *
 * 🔍 Example:
 * Input: s = "())"
 * Output: 1
 *
 * Input: s = "((("
 * Output: 3
 *
 * Input: s = "()))(("
 * Output: 4
 *
 * 🎯 Key Insight:
 * Track the number of unmatched opening and closing brackets using a counter.
 * - Every ')' must match a '(' before it
 * - If no matching '(', it means we need to insert one
 * - If there are unmatched '(', we must add corresponding ')' at the end
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - `open_count`: unmatched '(' that still need closing
 * - `insertions`: unmatched ')' that need an opening '('
 *
 * ✅ Transition:
 * - For '(': increment `open_count`
 * - For ')':
 *     - If `open_count` > 0 → match with previous '(' → `open_count--`
 *     - Else → unmatched ')', so `insertions++`
 *
 * ✅ Final Answer:
 * - Total insertions = unmatched ')' + unmatched '(' → `insertions + open_count`
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - All open or all close → return length
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int MinAddToMakeValid(string s) {
    int open_count = 0;
    int insertions = 0;

    for (char c : s) {
        if (c == '(') {
            open_count++;
        } else {  // c == ')'
            if (open_count > 0) {
                open_count--;
            } else {
                insertions++;  // unmatched ')'
            }
        }
    }

    return insertions + open_count;
}

/**
 * Problem 70: Number of Islands (LC 200)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D grid of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and formed by connecting adjacent lands (up/down/left/right).
 *
 * 🔍 Example:
 * Input:
 * grid = [
 *   ['1','1','0','0','0'],
 *   ['1','1','0','0','0'],
 *   ['0','0','1','0','0'],
 *   ['0','0','0','1','1']
 * ]
 * Output: 3
 *
 * 🎯 Key Insight:
 * Traverse the grid. For every unvisited land cell ('1'), start a DFS to mark the entire island.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - grid[i][j] = '1' means unvisited land
 * - Change visited land to '0' (or use visited set)
 *
 * ✅ Transition:
 * - From cell (i, j), expand to neighbors (up, down, left, right)
 * - If neighbor is '1', continue DFS
 *
 * ✅ Iteration Order:
 * - Traverse grid from top-left to bottom-right
 * - Trigger DFS on each fresh land cell
 *
 * 🚨 Edge Cases:
 * - Empty grid → return 0
 * - No '1' in grid → return 0
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(m * n) recursion stack worst case
 */

int NumIslands(vector<vector<char>>& grid) {
    int m = grid.size();
    if (m == 0) return 0;
    int n = grid[0].size();
    int count = 0;

    function<void(int, int)> dfs = [&](int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != '1') return;
        grid[i][j] = '0';  // mark as visited

        dfs(i - 1, j);  // up
        dfs(i + 1, j);  // down
        dfs(i, j - 1);  // left
        dfs(i, j + 1);  // right
    };

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                dfs(i, j);
                count++;
            }
        }
    }

    return count;
}

/**
 * Problem 71: Maximum Subarray (LC 53)
 * --------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, find the contiguous subarray (containing at least one number)
 * which has the largest sum and return its sum.
 *
 * 🔍 Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 * 🎯 Key Insight:
 * Use **Kadane's Algorithm** — keep track of max subarray ending at current position.
 *
 * 💡 Strategy:
 * --------------------------------------------------------
 * ✅ State:
 * - `curr_sum`: maximum subarray sum ending at index `i`
 * - `max_sum`: maximum value seen so far
 *
 * ✅ Transition:
 * - curr_sum = max(nums[i], curr_sum + nums[i])
 * - max_sum = max(max_sum, curr_sum)
 *
 * ✅ Iteration:
 * - Left to right scan
 *
 * 🚨 Edge Cases:
 * - All negatives → return max(nums)
 * - Single element → return that element
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int MaxSubArray(vector<int>& nums) {
    int curr_sum = nums[0];
    int max_sum = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        curr_sum = max(nums[i], curr_sum + nums[i]);
        max_sum = max(max_sum, curr_sum);
    }

    return max_sum;
}

/**
 * Problem 72: String to Integer (atoi) (LC 8)
 * ------------------------------------------
 * 🧠 Description:
 * Convert a string to a 32-bit signed integer (like the C/C++ atoi function).
 *
 * 🔍 Example:
 * Input: s = "   -42"
 * Output: -42
 *
 * 🎯 Key Insight:
 * Skip whitespaces, handle signs, parse digits until non-digit appears.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Track position `i`, `sign`, and accumulated `result`.
 *
 * ✅ Base Case Initialization:
 * i = 0, sign = +1, result = 0
 *
 * ✅ Transition:
 * - Skip leading whitespaces
 * - Handle '+' or '-' sign
 * - For each digit:
 *     result = result * 10 + digit
 *     Check overflow before adding!
 *
 * ✅ Iteration Order:
 * Linear pass over the string
 *
 * 🚨 Edge Cases:
 * - Overflow ⇒ return INT_MAX / INT_MIN
 * - No valid conversion ⇒ return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int MyAtoi(string s) {
    int i = 0, n = s.size(), sign = 1;
    long result = 0;

    // Skip leading whitespaces
    while (i < n && s[i] == ' ') i++;

    // Handle optional sign
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i++] == '-') ? -1 : 1;
    }

    // Parse digits and avoid overflow
    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i++] - '0');
        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
    }

    return static_cast<int>(result * sign);
}

/**
 * Problem 73: Construct Binary Tree from String (LC 536)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given a string `s` representing a binary tree in the format:
 * - Node value followed by optional left and right subtrees enclosed in parentheses.
 * - Example: "4(2(3)(1))(6(5))" represents:
 *
 *           4
 *         /   \
 *        2     6
 *       / \   /
 *      3   1 5
 *
 * 🎯 Key Insight:
 * Use recursive parsing with a global or reference index.
 * Parse integer → if '(' exists → recursively parse left/right subtrees.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Maintain a reference index `i` to track current parse position
 *
 * ✅ Transition:
 * - Read number (can be negative)
 * - If next char is '(', parse left subtree
 * - If another '(', parse right subtree
 * - Each subtree is enclosed and balanced by '(' and ')'
 *
 * ✅ Iteration:
 * - Single left-to-right parse
 *
 * 🚨 Edge Cases:
 * - Empty string → return nullptr
 * - Negative numbers must be supported
 *
 * ⏱️ Time Complexity: O(n), n = length of string
 * 🧠 Space Complexity: O(h), h = tree height (recursion stack)
 */

TreeNode* Str2tree(string s) {
    int i = 0;

    function<TreeNode*(void)> parse = [&]() -> TreeNode* {
        if (i >= s.size()) return nullptr;

        // Parse integer (handle sign)
        int sign = 1;
        if (s[i] == '-') {
            sign = -1;
            i++;
        }

        int num = 0;
        while (i < s.size() && isdigit(s[i])) {
            num = num * 10 + (s[i++] - '0');
        }

        TreeNode* node = new TreeNode(sign * num);

        // Parse left child
        if (i < s.size() && s[i] == '(') {
            i++;  // skip '('
            node->left = parse();
            i++;  // skip ')'
        }

        // Parse right child
        if (i < s.size() && s[i] == '(') {
            i++;  // skip '('
            node->right = parse();
            i++;  // skip ')'
        }

        return node;
    };

    if (s.empty()) return nullptr;
    return parse();
}

/**
 * Problem 74: Count Nodes Equal to Average of Subtree (LC 2265)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the number of nodes where the node's value
 * is equal to the average of values in its subtree (including itself).
 * The average is rounded down to the nearest integer.
 *
 * 🔍 Example:
 * Input: [4,8,5,0,1,null,6]
 * Output: 5
 *
 * 🎯 Key Insight:
 * Use DFS to compute for each node:
 * - Total sum and count of nodes in its subtree
 * - Compare node's value with average (sum / count)
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - For each node: return pair (sum, count)
 * - Maintain a result counter (by reference)
 *
 * ✅ Transition:
 * - Post-order traversal:
 *   - left = dfs(node->left)
 *   - right = dfs(node->right)
 *   - total_sum = left.sum + right.sum + node->val
 *   - total_count = left.count + right.count + 1
 *
 * ✅ Check:
 * - If node->val == total_sum / total_count → count++
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h) for recursion stack
 */

int AverageOfSubtree(TreeNode* root) {
    int result = 0;

    function<pair<int, int>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int, int> {
        if (!node) return {0, 0};

        auto [left_sum, left_count] = dfs(node->left);
        auto [right_sum, right_count] = dfs(node->right);

        int total_sum = left_sum + right_sum + node->val;
        int total_count = left_count + right_count + 1;

        if (node->val == total_sum / total_count) {
            result++;
        }

        return {total_sum, total_count};
    };

    dfs(root);
    return result;
}

/**
 * Problem 75: Search a 2D Matrix (LC 74)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given an m x n matrix where each row is sorted in ascending order,
 * and the first element of each row is greater than the last element of the previous row.
 * Given an integer `target`, return true if it exists in the matrix.
 *
 * 🔍 Example:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 *
 * 🎯 Key Insight:
 * The matrix can be treated as a **flattened sorted 1D array**.
 * We can apply classic binary search from index 0 to m*n - 1.
 * To convert a 1D index back to 2D:
 * - row = index / n
 * - col = index % n
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Use binary search on virtual 1D space: left = 0, right = m * n - 1
 *
 * ✅ Transition:
 * - mid = (left + right) / 2
 * - value = matrix[mid / n][mid % n]
 * - If value == target → return true
 * - Else adjust search boundaries accordingly
 *
 * ✅ Iteration:
 * - While left <= right → shrink range
 *
 * 🚨 Edge Cases:
 * - Empty matrix → return false
 *
 * ⏱️ Time Complexity: O(log(m * n))
 * 🧠 Space Complexity: O(1)
 */

bool SearchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) return false;

    int n = matrix[0].size();
    if (n == 0) return false;

    int left = 0;
    int right = m * n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n;
        int col = mid % n;
        int target_value = matrix[row][col];

        if (target_value == target) {
            return true;
        } else if (target_value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

/**
 * Problem 76: Can Place Flowers (LC 605)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `flowerbed` consisting of 0s and 1s,
 * where 0 means empty and 1 means planted.
 * Return true if `n` new flowers can be planted without violating the no-adjacent-flowers rule.
 *
 * 🔍 Example:
 * Input: flowerbed = [1,0,0,0,1], n = 1
 * Output: true
 *
 * Input: flowerbed = [1,0,0,0,1], n = 2
 * Output: false
 *
 * 🎯 Key Insight:
 * For each 0, check whether both adjacent spots are 0 or boundaries.
 * If yes → place flower (set to 1), and skip next index.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Iterate index `i` through flowerbed
 * - Place flower greedily if:
 *   - flowerbed[i] == 0
 *   - (i == 0 or flowerbed[i-1] == 0) and (i == end or flowerbed[i+1] == 0)
 *
 * ✅ Transition:
 * - After placing, set flowerbed[i] = 1
 * - Increment count
 * - If count >= n → early return true
 *
 * ✅ Iteration:
 * - Single pass, left to right
 *
 * 🚨 Edge Cases:
 * - Empty flowerbed
 * - n = 0 → always true
 * - Leading/trailing 0s must be handled
 *
 * ⏱️ Time Complexity: O(m), m = flowerbed.size()
 * 🧠 Space Complexity: O(1)
 */

bool CanPlaceFlowers(vector<int>& flowerbed, int n) {
    int count = 0;
    int size = flowerbed.size();

    for (int i = 0; i < size; ++i) {
        if (flowerbed[i] == 0) {
            bool left_empty = (i == 0 || flowerbed[i - 1] == 0);
            bool right_empty = (i == size - 1 || flowerbed[i + 1] == 0);

            if (left_empty && right_empty) {
                flowerbed[i] = 1;
                count++;
                if (count >= n) return true;
            }
        }
    }

    return count >= n;
}

/**
 * Problem 77: Set Matrix Zeroes (LC 73)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an m x n integer matrix, if an element is 0,
 * set its entire row and column to 0. Do it in-place.
 *
 * 🔍 Example:
 * Input:
 * [[1,1,1],
 *  [1,0,1],
 *  [1,1,1]]
 * Output:
 * [[1,0,1],
 *  [0,0,0],
 *  [1,0,1]]
 *
 * 🎯 Key Insight:
 * Use the first row and column as flags to avoid extra space.
 * Track whether row 0 and col 0 need to be zeroed separately.
 *
 * 💡 Strategy: In-place O(1) space marking
 * ----------------------------------------------------------------
 * ✅ Step 1:
 * - Determine if row 0 and col 0 need to be zeroed (scan them separately)
 *
 * ✅ Step 2:
 * - Use matrix[i][0] and matrix[0][j] to mark zeros in the rest of the matrix
 *
 * ✅ Step 3:
 * - Traverse the matrix (excluding row 0 and col 0) and zero based on markers
 *
 * ✅ Step 4:
 * - Finally zero row 0 and/or col 0 if necessary
 *
 * 🚨 Edge Cases:
 * - Entire first row/col has 0 → must defer final clearing to the end
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(1)
 */

void SetZeroes(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    bool row0 = false, col0 = false;

    // Check first row
    for (int j = 0; j < cols; ++j) {
        if (matrix[0][j] == 0) {
            row0 = true;
            break;
        }
    }

    // Check first column
    for (int i = 0; i < rows; ++i) {
        if (matrix[i][0] == 0) {
            col0 = true;
            break;
        }
    }

    // Use first row and column as flags
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // Zero based on flags (excluding first row and column)
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }

    // Zero first row if needed
    if (row0) {
        for (int j = 0; j < cols; ++j) {
            matrix[0][j] = 0;
        }
    }

    // Zero first column if needed
    if (col0) {
        for (int i = 0; i < rows; ++i) {
            matrix[i][0] = 0;
        }
    }
}

/**
 * Problem 78: Shortest Bridge (LC 934)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a binary grid of 0s and 1s representing two islands (connected 1s),
 * return the minimum number of 0s to flip to connect the two islands (build the shortest bridge).
 *
 * 🔍 Example:
 * Input: grid = [[0,1],[1,0]]
 * Output: 1
 *
 * 🎯 Key Insight:
 * - Step 1: Use DFS to mark all cells of one island and put them into a queue.
 * - Step 2: Use BFS from the queue to expand level-by-level until we reach the second island.
 *   The number of levels we expand = answer.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Phase 1 (DFS):
 * - Find first '1' → DFS mark all connected 1s as visited and add them to queue for BFS.
 *
 * ✅ Phase 2 (BFS):
 * - Expand from all marked first island cells.
 * - The first time we touch another '1' (not visited) → return distance
 *
 * ✅ Data:
 * - queue<pair<int, int>> for BFS
 * - visited set to avoid cycles
 * - 4-direction vector
 *
 * 🚨 Edge Cases:
 * - Smallest grid (2x2)
 * - Islands touching → shortest bridge = 0
 *
 * ⏱️ Time Complexity: O(n²)
 * 🧠 Space Complexity: O(n²)
 */

int ShortestBridge(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<pair<int, int>> bfs_queue;
    vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

    // ✅ DFS to find and mark first island
    function<void(int, int)> dfs = [&](int x, int y) {
        if (x < 0 || y < 0 || x >= n || y >= n ||
            grid[x][y] == 0 || visited[x][y]) return;

        visited[x][y] = true;
        bfs_queue.push({x, y});

        for (auto [dx, dy] : dirs) {
            dfs(x + dx, y + dy);
        }
    };

    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int j = 0; j < n && !found; ++j) {
            if (grid[i][j] == 1) {
                dfs(i, j);
                found = true;
            }
        }
    }

    // ✅ BFS to expand outwards and find shortest bridge
    int steps = 0;
    while (!bfs_queue.empty()) {
        int sz = bfs_queue.size();
        for (int i = 0; i < sz; ++i) {
            auto [x, y] = bfs_queue.front();
            bfs_queue.pop();

            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && !visited[nx][ny]) {
                    if (grid[nx][ny] == 1) {
                        return steps;
                    }
                    bfs_queue.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
        steps++;
    }

    return -1; // should not happen
}

/**
 * Problem 79: Car Pooling (LC 1094)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given a list of trips, where each trip is [num_passengers, from, to].
 * Return true if it is possible to pick up and drop off all passengers without exceeding `capacity` at any time.
 *
 * 🔍 Example:
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 4
 * Output: false
 *
 * Input: trips = [[2,1,5],[3,5,7]], capacity = 3
 * Output: true
 *
 * 🎯 Key Insight:
 * Use a prefix sum approach (also known as "difference array").
 * - At time `from`: +num_passengers
 * - At time `to`: -num_passengers
 * Then, simulate the journey along a time line to ensure the passenger count never exceeds capacity.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Use an array `timeline[0..1000]` to record changes in passenger count.
 *
 * ✅ Transition:
 * - For each trip [num, from, to]:
 *     timeline[from] += num
 *     timeline[to]   -= num
 *
 * ✅ Final Check:
 * - Traverse the timeline to ensure running sum never exceeds capacity
 *
 * 🚨 Edge Cases:
 * - Trip from == to → can be ignored (zero-length trip)
 * - Maximum location is 1000 as per constraints
 *
 * ⏱️ Time Complexity: O(N + R), N = # trips, R = max station (1001)
 * 🧠 Space Complexity: O(R)
 */

bool CarPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> timeline(1001, 0);  // since location ∈ [0, 1000]

    for (const auto& trip : trips) {
        int passengers = trip[0];
        int from = trip[1];
        int to = trip[2];

        timeline[from] += passengers;
        timeline[to] -= passengers;
    }

    int current = 0;
    for (int i = 0; i <= 1000; ++i) {
        current += timeline[i];
        if (current > capacity) {
            return false;
        }
    }

    return true;
}

/**
 * Problem 80: Create Hello World Function (LC 2667)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Write a function `CreateHelloWorld` that returns a function.
 * When called, this returned function should always return `"Hello World"`.
 *
 * 🔍 Example:
 * Input: f = CreateHelloWorld();
 * Output: f();  // "Hello World"
 *
 * 🎯 Key Insight:
 * This is a **higher-order function** pattern.
 * - Return a lambda that ignores its arguments and returns the fixed string.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Return Type:
 * - Use `function<string(...)>` to match any input signature
 *
 * ✅ Lambda:
 * - Return a lambda that takes any number of arguments and returns "Hello World"
 * - In C++, we can use `auto` or template argument deduction
 *
 * ✅ Flexibility:
 * - The returned function must accept any arguments (ignored)
 *
 * 🚨 Edge Cases:
 * - Input parameters to returned function are irrelevant
 * - Must not throw regardless of call signature
 *
 * ⏱️ Time Complexity: O(1)
 * 🧠 Space Complexity: O(1)
 */

function<string()> CreateHelloWorld() {
    return []() -> string {
        return "Hello World";
    };
}

/**
 * Problem 81: Word Ladder (LC 127)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a begin word, end word, and a word list, return the **length** of the shortest transformation sequence
 * from `begin_word` to `end_word`, such that:
 * - Only one letter can be changed at a time
 * - Each transformed word must exist in the word list
 *
 * Return 0 if no such transformation sequence exists.
 *
 * 🔍 Example:
 * Input: begin_word = "hit", end_word = "cog", word_list = ["hot","dot","dog","lot","log","cog"]
 * Output: 5
 * Explanation: hit → hot → dot → dog → cog
 *
 * 🎯 Key Insight:
 * Use BFS for shortest path. Each node is a word, and an edge exists between words that differ by one letter.
 * Build word neighbors dynamically by replacing each character with 'a'-'z'.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Each BFS node is (current_word, steps)
 * - Use unordered_set for fast lookup of word_list
 * - Track visited to avoid cycles
 *
 * ✅ Transition:
 * - For each word, change one letter at a time to generate neighbors
 * - If neighbor in word_list and not visited → enqueue
 *
 * ✅ Iteration:
 * - Standard BFS from begin_word to end_word
 *
 * 🚨 Edge Cases:
 * - end_word not in word_list → return 0
 * - All words same → return 1
 *
 * ⏱️ Time Complexity: O(N × L²), N = #words, L = word length
 * 🧠 Space Complexity: O(N)
 */

int LadderLength(string begin_word, string end_word, vector<string>& word_list) {
    unordered_set<string> word_set(word_list.begin(), word_list.end());
    if (!word_set.count(end_word)) return 0;

    queue<pair<string, int>> q;
    unordered_set<string> visited;

    q.push({begin_word, 1});
    visited.insert(begin_word);

    while (!q.empty()) {
        auto [word, steps] = q.front();
        q.pop();

        if (word == end_word) return steps;

        for (int i = 0; i < word.size(); ++i) {
            string next_word = word;

            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == word[i]) continue;
                next_word[i] = c;

                if (word_set.count(next_word) && !visited.count(next_word)) {
                    q.push({next_word, steps + 1});
                    visited.insert(next_word);
                }
            }
        }
    }

    return 0;
}

/**
 * Problem 82: Missing Ranges (LC 163)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a sorted integer array `nums`, where all elements are in [lower, upper] inclusive,
 * return the **smallest sorted list of ranges** that cover every missing number in the interval [lower, upper].
 *
 * 🔍 Example:
 * Input: nums = [0, 1, 3, 50, 75], lower = 0, upper = 99
 * Output: ["2", "4->49", "51->74", "76->99"]
 *
 * 🎯 Key Insight:
 * Treat the range as gaps between consecutive elements (including virtual boundaries before lower and after upper).
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Use a `prev` pointer initialized to `lower - 1`
 * - For each element `curr` in nums plus final `upper + 1`:
 *   - If `curr - prev >= 2`, then there is a missing range
 *   - Format:
 *     - If curr - prev == 2 → "x"
 *     - If curr - prev > 2 → "x->y"
 *
 * ✅ Final Touch:
 * - Use helper to format range strings
 *
 * 🚨 Edge Cases:
 * - Empty nums → return entire [lower, upper]
 * - No gaps → return empty list
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) extra (excluding result)
 */

vector<string> FindMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> result;

    auto FormatRange = [](int start, int end) -> string {
        return (start == end) ? to_string(start) : to_string(start) + "->" + to_string(end);
    };

    long long prev = static_cast<long long>(lower) - 1;
    long long curr = 0;

    for (int i = 0; i <= nums.size(); ++i) {
        curr = (i < nums.size()) ? nums[i] : static_cast<long long>(upper) + 1;

        if (curr - prev >= 2) {
            result.push_back(FormatRange(prev + 1, curr - 1));
        }

        prev = curr;
    }

    return result;
}

/**
 * Problem 83: Trapping Rain Water (LC 42)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an array `height` where each index represents the elevation at that point,
 * compute how much water it is able to trap after raining.
 *
 * 🔍 Example:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 *
 * 🎯 Key Insight:
 * The water trapped at index i is:
 * min(max height to the left, max height to the right) - height[i]
 * Instead of precomputing both sides, use **two pointers** to dynamically track left/right max.
 *
 * 💡 Strategy: Two Pointers
 * ----------------------------------------------------------------
 * ✅ State:
 * - `left` and `right`: two pointers from ends
 * - `left_max` and `right_max`: track max height so far from both sides
 *
 * ✅ Transition:
 * - If height[left] < height[right]:
 *     - If height[left] < left_max → water += left_max - height[left]
 *     - Else update left_max
 *     - Move left++
 * - Else:
 *     - Same logic for right side
 *
 * ✅ Iteration:
 * - Move inward from both sides
 *
 * 🚨 Edge Cases:
 * - Empty or size < 3 → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int Trap(vector<int>& height) {
    int n = height.size();
    if (n < 3) return 0;

    int left = 0, right = n - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] < left_max) {
                water += left_max - height[left];
            } else {
                left_max = height[left];
            }
            left++;
        } else {
            if (height[right] < right_max) {
                water += right_max - height[right];
            } else {
                right_max = height[right];
            }
            right--;
        }
    }

    return water;
}

/**
 * Problem 84: Best Time to Buy and Sell Stock II (LC 122)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `prices` where `prices[i]` is the price of a stock on day i.
 * You may complete as many transactions as you like (buy/sell multiple times).
 * Return the **maximum profit** you can achieve.
 * You may not hold more than one stock at a time (must sell before buying again).
 *
 * 🔍 Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (1), sell on day 3 (5), buy on day 4 (3), sell on day 5 (6)
 *
 * 🎯 Key Insight:
 * Any time we see `prices[i] > prices[i-1]`, we can earn the difference.
 * Instead of finding peaks/valleys explicitly, sum all `uphill` gains.
 *
 * 💡 Strategy: Greedy
 * ----------------------------------------------------------------
 * ✅ State:
 * - Iterate through prices from left to right
 * - Add profit whenever today's price > yesterday's
 *
 * ✅ Transition:
 * - If prices[i] > prices[i-1] → profit += prices[i] - prices[i-1]
 *
 * ✅ Iteration:
 * - Single pass from day 1 to day n-1
 *
 * 🚨 Edge Cases:
 * - prices empty or size 1 → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int MaxProfit(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}

/**
 * Problem 85: Squares of a Sorted Array (LC 977)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a sorted array `nums` in non-decreasing order, return a new array of the squares of each number,
 * also in non-decreasing order.
 *
 * 🔍 Example:
 * Input: nums = [-4, -1, 0, 3, 10]
 * Output: [0, 1, 9, 16, 100]
 *
 * 🎯 Key Insight:
 * Squaring negative numbers can make them larger than some positive numbers.
 * Use two pointers from both ends, placing the larger square at the end of result array.
 *
 * 💡 Strategy: Two Pointers
 * ----------------------------------------------------------------
 * ✅ State:
 * - `left` starts at 0
 * - `right` starts at n - 1
 * - `pos` starts at n - 1 (fill result from end to front)
 *
 * ✅ Transition:
 * - If abs(nums[left]) > abs(nums[right]):
 *     result[pos--] = nums[left]^2
 *     left++
 * - Else:
 *     result[pos--] = nums[right]^2
 *     right--
 *
 * ✅ Iteration:
 * - Loop until left > right
 *
 * 🚨 Edge Cases:
 * - All non-negative → no need to rearrange
 * - All non-positive → just reverse after squaring
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

vector<int> SortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> squares(n);
    int left = 0, right = n - 1;
    int pos = n - 1;

    while (left <= right) {
        int left_val = nums[left];
        int right_val = nums[right];

        if (abs(left_val) > abs(right_val)) {
            squares[pos--] = left_val * left_val;
            left++;
        } else {
            squares[pos--] = right_val * right_val;
            right--;
        }
    }

    return squares;
}

/**
 * Problem 86: Add Two Numbers (LC 2)
 * -----------------------------------
 * 🧠 Description:
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each node contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 *
 * 🔍 Example:
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 *
 * 🎯 Key Insight:
 * Simulate digit-by-digit addition, carry over if sum >= 10.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * l1, l2 = input lists; carry = current carry
 *
 * ✅ Base Case Initialization:
 * dummy head node, current = dummy
 *
 * ✅ Transition:
 * While l1 or l2 or carry:
 *   - Add corresponding digits + carry
 *   - Set new digit node = sum % 10
 *   - Update carry = sum / 10
 *
 * ✅ Iteration Order:
 * Traverse both lists
 *
 * ⏱️ Time Complexity: O(max(m, n))
 * 🧠 Space Complexity: O(max(m, n)) for result list
 */

ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0), *curr = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int val1 = l1 ? l1->val : 0;
        int val2 = l2 ? l2->val : 0;
        int sum = val1 + val2 + carry;

        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return dummy.next;
}

/**
 * Problem 87: Binary Search Tree Iterator (LC 173)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Implement an iterator over a binary search tree (BST).
 * `next()` and `hasNext()` should run in average O(1) time and use O(h) memory, where h is the height of the tree.
 *
 * 🔍 Example:
 * Input: root = [7, 3, 15, null, null, 9, 20]
 * Operations:
 *   BSTIterator173Init(root)
 *   BSTIterator173Next() → 3
 *   BSTIterator173Next() → 7
 *   BSTIterator173HasNext() → true
 *   BSTIterator173Next() → 9
 *
 * 🎯 Key Insight:
 * - Use an explicit stack to simulate in-order traversal.
 * - In-order traversal of BST gives values in sorted order.
 * - Initially push all left nodes from root.
 * - On next(), return top and push right subtree's left spine.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - Stack `_stack_173` holds TreeNode* simulating call stack.
 *
 * ✅ Transition:
 * - Init: push all left nodes from root
 * - Next:
 *     - pop top node
 *     - push left spine of right subtree
 *
 * ✅ Time Complexity:
 * - next(): Amortized O(1) over n calls
 * - hasNext(): O(1)
 *
 * 🚨 Edge Cases:
 * - Empty tree → hasNext() returns false
 * - Only one node → still works
 */

stack<TreeNode*> _stack_173;

void BSTIterator173Init(TreeNode* root) {
    while (!_stack_173.empty()) _stack_173.pop();

    TreeNode* curr = root;
    while (curr) {
        _stack_173.push(curr);
        curr = curr->left;
    }
}

int BSTIterator173Next() {
    TreeNode* node = _stack_173.top();
    _stack_173.pop();
    int result = node->val;

    TreeNode* curr = node->right;
    while (curr) {
        _stack_173.push(curr);
        curr = curr->left;
    }

    return result;
}

bool BSTIterator173HasNext() {
    return !_stack_173.empty();
}

/**
 * Problem 88: Merge Two Sorted Lists (LC 21)
 * -------------------------------------------
 * 🧠 Description:
 * Merge two sorted linked lists and return it as a new sorted list.
 * The new list should be made by splicing together the nodes of the first two lists.
 *
 * 🔍 Example:
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 *
 * 🎯 Key Insight:
 * Use two pointers and build merged list incrementally.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * l1, l2 = input lists; dummy head to build result
 *
 * ✅ Base Case Initialization:
 * dummy node, current = dummy
 *
 * ✅ Transition:
 * Compare l1 and l2 values:
 *   - Append smaller one and move pointer
 *
 * ✅ Final Step:
 * Append remaining nodes
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(1)
 */
ListNode* MergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0), *curr = &dummy;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }

    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

/**
 * Problem 89: Serialize and Deserialize Binary Tree (LC 297)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Design an algorithm to serialize and deserialize a binary tree.
 * - Serialization converts a tree to a string
 * - Deserialization reconstructs the tree from the string
 *
 * 🔍 Example:
 * Input: root = [1,2,3,null,null,4,5]
 * Output: after Serialize → "1,2,#,#,3,4,#,#,5,#,#"
 *
 * 🎯 Key Insight:
 * Use **pre-order traversal** for both serialize and deserialize:
 * - '#' represents null nodes
 * - Comma separates each value
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Serialize:
 * - Pre-order: root → left → right
 * - For nullptr → append '#'
 * - Otherwise → append node value
 *
 * ✅ Deserialize:
 * - Use queue to split values
 * - Recurse to build tree: root = new TreeNode(val), then left/right
 *
 * 🚨 Edge Cases:
 * - Empty tree → "#"
 * - One node → "val,#,#"
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) for queue and output string
 */

// ---- Serialize ----

void Serialize297Helper(TreeNode* root, string& result) {
    if (!root) {
        result += "#,";
        return;
    }

    result += to_string(root->val) + ",";
    Serialize297Helper(root->left, result);
    Serialize297Helper(root->right, result);
}

string Serialize297(TreeNode* root) {
    string result;
    Serialize297Helper(root, result);
    if (!result.empty()) result.pop_back();  // remove trailing comma
    return result;
}

// ---- Deserialize ----

queue<string> _queue_297;

TreeNode* Deserialize297Helper() {
    if (_queue_297.empty()) return nullptr;

    string val = _queue_297.front();
    _queue_297.pop();

    if (val == "#") return nullptr;

    TreeNode* node = new TreeNode(stoi(val));
    node->left = Deserialize297Helper();
    node->right = Deserialize297Helper();
    return node;
}

TreeNode* Deserialize297(string data) {
    while (!_queue_297.empty()) _queue_297.pop();

    stringstream ss(data);
    string token;
    while (getline(ss, token, ',')) {
        _queue_297.push(token);
    }

    return Deserialize297Helper();
}

/**
 * Problem 90: Accounts Merge (LC 721)
 * -------------------------------------
 * 🧠 Description:
 * Given a list of accounts where each element is [name, email1, email2, ...],
 * merge accounts that have common emails.
 *
 * 🔍 Example:
 * Input: [["John", "johnsmith@mail.com", "john00@mail.com"], ...]
 * Output: Merged accounts with unique names
 *
 * 🎯 Key Insight:
 * Union-Find (Disjoint Set Union) to group emails by connectivity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * parent[email] = root representative
 *
 * ✅ Transition:
 * Union all emails in same account
 *
 * ✅ Final:
 * Collect emails by root, sort, and prepend account name
 *
 * ⏱️ Time Complexity: O(N * α(N)) where N = total emails
 * 🧠 Space Complexity: O(N)
 */
string Find(string email, unordered_map<string, string>& parent) {
    if (parent[email] != email)
        parent[email] = Find(parent[email], parent);
    return parent[email];
}

void Union(string a, string b, unordered_map<string, string>& parent) {
    parent[Find(a, parent)] = Find(b, parent);
}

vector<vector<string>> AccountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, string> parent;
    unordered_map<string, string> owner;

    // Init
    for (const auto& acc : accounts)
        for (int i = 1; i < acc.size(); ++i) {
            parent[acc[i]] = acc[i];
            owner[acc[i]] = acc[0];
        }

    // Union emails in same account
    for (const auto& acc : accounts)
        for (int i = 2; i < acc.size(); ++i)
            Union(acc[i], acc[1], parent);

    // Group emails by root
    unordered_map<string, set<string>> groups;
    for (const auto& [email, _] : parent) {
        groups[Find(email, parent)].insert(email);
    }

    // Build result
    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        vector<string> entry = {owner[root]};
        entry.insert(entry.end(), emails.begin(), emails.end());
        result.push_back(entry);
    }

    return result;
}

/**
 * Problem 91: Two Sum II - Input Array Is Sorted (LC 167)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a **1-indexed** sorted array of integers `numbers` and a target sum,
 * return the indices of the two numbers such that they add up to the target.
 *
 * You must use exactly one solution, and may not use the same element twice.
 *
 * 🔍 Example:
 * Input: numbers = [2, 7, 11, 15], target = 9
 * Output: [1, 2]
 *
 * 🎯 Key Insight:
 * Since the array is sorted, use the **two pointers** method:
 * - If sum < target → move `left` forward
 * - If sum > target → move `right` backward
 *
 * 💡 Strategy: Two Pointers
 * ----------------------------------------------------------------
 * ✅ State:
 * - left = 0 (start of array)
 * - right = n - 1 (end of array)
 *
 * ✅ Transition:
 * - Check sum = numbers[left] + numbers[right]
 * - If sum == target → return {left+1, right+1}
 * - Else move left/right based on comparison
 *
 * ✅ Iteration:
 * - Single linear scan
 *
 * 🚨 Edge Cases:
 * - Only 2 elements → guaranteed correct per constraints
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

vector<int> TwoSum167(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum == target) {
            return {left + 1, right + 1};  // 1-indexed
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    return {};  // Should not happen per problem guarantee
}

/**
 * Problem 92: Longest Increasing Path in a Matrix (LC 329)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an m x n integer matrix, return the length of the longest increasing path in the matrix.
 * - From each cell, you can move in 4 directions (up/down/left/right)
 * - You may not move diagonally or wrap around.
 *
 * 🔍 Example:
 * Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
 * Output: 4
 * Explanation: The longest path is [1, 2, 6, 9]
 *
 * 🎯 Key Insight:
 * Use **DFS + memoization**:
 * - Try all 4 directions from each cell
 * - Cache results to avoid recomputation (top-down DP)
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - `memo[i][j]` = longest increasing path starting from cell (i, j)
 *
 * ✅ Transition:
 * - For each neighbor (x, y) with matrix[x][y] > matrix[i][j]:
 *     - dfs(x, y), then max_len = max(max_len, 1 + dfs result)
 *
 * ✅ Base Case:
 * - memo[i][j] > 0 → already computed
 *
 * ✅ Iteration:
 * - Try dfs(i, j) for all cells in the matrix
 *
 * 🚨 Edge Cases:
 * - Single cell → return 1
 * - No increasing path → all return 1
 *
 * ⏱️ Time Complexity: O(m × n)
 * 🧠 Space Complexity: O(m × n) + O(m × n) recursion stack worst case
 */

int LongestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> memo(m, vector<int>(n, 0));
    vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

    function<int(int, int)> dfs = [&](int i, int j) -> int {
        if (memo[i][j] != 0) return memo[i][j];

        int max_len = 1;
        for (auto [dx, dy] : dirs) {
            int x = i + dx, y = j + dy;
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j]) {
                max_len = max(max_len, 1 + dfs(x, y));
            }
        }

        memo[i][j] = max_len;
        return max_len;
    };

    int result = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result = max(result, dfs(i, j));
        }
    }

    return result;
}

/**
 * Problem 93: Count the Hidden Sequences (LC 2145)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given a list of differences (diffs) of a hidden array `a`,
 * where `a[i+1] - a[i] = differences[i]`, and a known constraint:
 * all elements of `a` must be in [lower, upper].
 *
 * Return the **number of valid sequences** of length `n = differences.size() + 1`
 * such that all elements of `a` lie within the range.
 *
 * 🔍 Example:
 * Input: differences = [1, -3, 4], lower = 1, upper = 6
 * Output: 2
 *
 * 🎯 Key Insight:
 * If we let `a[0] = x`, then the rest of the sequence is:
 * a[1] = x + diff[0], a[2] = x + diff[0] + diff[1], ...
 * So: all a[i] = x + prefix_sum[i]
 *
 * Goal: find how many integer values `x` ∈ [lower, upper] such that:
 *     x + min(prefix_sum) ≥ lower
 *     x + max(prefix_sum) ≤ upper
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1:
 * - Build prefix sum while tracking min and max of cumulative value
 *
 * ✅ Step 2:
 * - Solve for `x` range:
 *     x ∈ [lower - min_prefix, upper - max_prefix]
 *
 * ✅ Final Answer:
 * - If valid range exists → return (hi - lo + 1)
 * - Else → return 0
 *
 * 🚨 Edge Cases:
 * - All diffs = 0 → n = 1 → full range is valid
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int CountHiddenSequences(vector<int>& differences, int lower, int upper) {
    long long prefix_sum = 0;
    long long min_prefix = 0, max_prefix = 0;

    for (int diff : differences) {
        prefix_sum += diff;
        min_prefix = min(min_prefix, prefix_sum);
        max_prefix = max(max_prefix, prefix_sum);
    }

    long long min_start = lower - min_prefix;
    long long max_start = upper - max_prefix;

    return max(0LL, max_start - min_start + 1);
}

/**
 * Problem 94: Palindrome Number (LC 9)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an integer `x`, return true if it is a palindrome, and false otherwise.
 * A palindrome is a number that reads the same backward as forward.
 *
 * 🔍 Example:
 * Input: x = 121
 * Output: true
 *
 * Input: x = -121
 * Output: false  // because of leading '-'
 *
 * 🎯 Key Insight:
 * A negative number is never a palindrome.
 * Instead of converting to string, reverse half of the number and compare.
 * - More efficient, and avoids integer overflow risk.
 *
 * 💡 Strategy: Reverse Half of the Digits
 * ----------------------------------------------------------------
 * ✅ Step 1: Edge check
 * - If x < 0 or (x % 10 == 0 && x != 0) → false
 *
 * ✅ Step 2: Reverse digits until reversed >= x
 * - Build reversed = reversed * 10 + x % 10
 * - Remove last digit from x: x /= 10
 *
 * ✅ Step 3: Check
 * - Either x == reversed (even digits)
 * - Or x == reversed / 10 (odd digits, middle digit ignored)
 *
 * 🚨 Edge Cases:
 * - x = 0 → true
 * - x = 10, 100, etc. → false (trailing zero not allowed unless x = 0)
 *
 * ⏱️ Time Complexity: O(log₁₀n)
 * 🧠 Space Complexity: O(1)
 */

bool IsPalindrome9(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;

    int reversed = 0;
    while (x > reversed) {
        int digit = x % 10;
        reversed = reversed * 10 + digit;
        x /= 10;
    }

    return (x == reversed) || (x == reversed / 10);
}

/**
 * Problem 95: Decode String (LC 394)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an encoded string, return its decoded version.
 * The encoding rule is: `k[encoded_string]`, where `k` is a positive integer.
 * The string may be nested, e.g. `3[a2[c]]` → "accaccacc".
 *
 * 🔍 Example:
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 *
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 *
 * 🎯 Key Insight:
 * Use two stacks:
 * - One to track repeat counts (count_stack)
 * - One to track previous strings (str_stack)
 *
 * When we hit ']', we:
 * - Pop count and prev_str
 * - Repeat the current built string `count` times and append to prev_str
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ State:
 * - curr_str: building current segment
 * - curr_num: building current multiplier
 * - str_stack: stores string before `[`
 * - count_stack: stores multiplier before `[`
 *
 * ✅ Transition:
 * - Digit: build curr_num
 * - Letter: append to curr_str
 * - '[': push curr_str and curr_num, reset both
 * - ']': pop stack, build repeated string
 *
 * 🚨 Edge Cases:
 * - Input is valid per problem constraints
 * - Empty string → return ""
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) — stacks for nested decoding
 */

string DecodeString394(string s) {
    stack<int> count_stack;
    stack<string> str_stack;
    string curr_str;
    int curr_num = 0;

    for (char c : s) {
        if (isdigit(c)) {
            curr_num = curr_num * 10 + (c - '0');
        } else if (c == '[') {
            count_stack.push(curr_num);
            str_stack.push(curr_str);
            curr_num = 0;
            curr_str.clear();
        } else if (c == ']') {
            int repeat = count_stack.top(); count_stack.pop();
            string prev_str = str_stack.top(); str_stack.pop();

            string repeated;
            for (int i = 0; i < repeat; ++i) {
                repeated += curr_str;
            }

            curr_str = prev_str + repeated;
        } else {
            curr_str += c;
        }
    }

    return curr_str;
}

/**
 * Problem 96: Inorder Successor in BST II (LC 510)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given a node in a BST with parent pointer.
 * Return its **inorder successor** (i.e., the next node in in-order traversal).
 * If it doesn't exist, return nullptr.
 *
 * 🔍 Example:
 * Input: node = 3 (from tree: 2 <- 3 -> 4)
 * Output: 4
 *
 * 🎯 Key Insight:
 * - If the node has a right child → successor is the **leftmost node in right subtree**
 * - Else → go up using parent until current is left child of its parent
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Case 1:
 * - node has right subtree → return leftmost(node->right)
 *
 * ✅ Case 2:
 * - No right subtree:
 *   - Go up until you find a parent where curr is a left child
 *   - That parent is the successor
 *
 * 🚨 Edge Cases:
 * - node is the rightmost → return nullptr
 * - root node has no successor → return nullptr
 *
 * ⏱️ Time Complexity: O(h), h = tree height
 * 🧠 Space Complexity: O(1)
 */

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

Node* InorderSuccessor510(Node* node) {
    if (!node) return nullptr;

    // ✅ Case 1: has right subtree
    if (node->right) {
        Node* curr = node->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    // ✅ Case 2: no right subtree, go up to find next larger
    Node* curr = node;
    while (curr->parent && curr == curr->parent->right) {
        curr = curr->parent;
    }

    return curr->parent;  // may be nullptr if none
}

/**
 * Problem 97: Count Largest Group (LC 1399)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an integer n, group the numbers from 1 to n based on the **sum of their digits**.
 * Return how many groups have the largest size.
 *
 * 🔍 Example:
 * Input: n = 13
 * Output: 4
 * Explanation: Groups:
 *   - Sum 1 → [1, 10]
 *   - Sum 2 → [2, 11]
 *   - Sum 3 → [3, 12]
 *   - Sum 4 → [4, 13]
 *   - Sum 5 → [5]
 *   - ...
 * Largest group size is 2, and there are 4 such groups.
 *
 * 🎯 Key Insight:
 * Sum of digits from 1 to n is bounded (max 36 for 9999),
 * So we can map sum → count and find how many sums share the max count.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Iterate from 1 to n
 * ✅ Step 2: Compute digit sum for each number
 * ✅ Step 3: Use hash map to track frequency of each digit sum
 * ✅ Step 4: Find the largest group size and count how many groups have that size
 *
 * 🚨 Edge Cases:
 * - n = 1 → only 1 group of size 1 → return 1
 *
 * ⏱️ Time Complexity: O(n × log n) — digit sum per number
 * 🧠 Space Complexity: O(1) — digit sum range is small
 */

int CountLargestGroup1399(int n) {
    unordered_map<int, int> count_map;
    int max_size = 0;

    auto digit_sum = [](int x) -> int {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    };

    for (int i = 1; i <= n; ++i) {
        int sum = digit_sum(i);
        count_map[sum]++;
        max_size = max(max_size, count_map[sum]);
    }

    int result = 0;
    for (const auto& [key, count] : count_map) {
        if (count == max_size) {
            result++;
        }
    }

    return result;
}

/**
 * Problem 98: Subsets (LC 78)
 * -----------------------------
 * 🧠 Description:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
 *
 * 🎯 Key Insight:
 * Use backtracking to explore include/exclude paths, or iterative subset expansion.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - path: current subset
 * - index: current position in nums
 *
 * ✅ Base Case Initialization:
 * - Always push path into result at each level
 *
 * ✅ Transition:
 * - At each index, choose to include nums[i] or not
 *
 * ✅ Iteration Order:
 * DFS (pre-order), from index = 0 to nums.size()
 *
 * 🚨 Edge Cases:
 * - Empty input → returns [[]]
 * - Input of size 1 → returns [[], [x]]
 *
 * ⏱️ Time Complexity: O(2^n)
 * 🧠 Space Complexity: O(n)
 */
void Backtrack78(vector<int>& nums, int index, vector<int>& path, vector<vector<int>>& result) {
    result.push_back(path);  // push current subset
    for (int i = index; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        Backtrack78(nums, i + 1, path, result);
        path.pop_back();
    }
}

vector<vector<int>> Subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    Backtrack78(nums, 0, path, result);
    return result;
}

/**
 * Problem 99: Longest Valid Parentheses (LC 32)
 * -----------------------------------------------
 * 🧠 Description:
 * Given a string containing only '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 *
 * 🔍 Example:
 * Input: s = "(()"
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use a stack or DP to track matching parentheses positions.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = longest valid substring ending at index i
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0
 *
 * ✅ Transition:
 * If s[i] == ')' and s[i-1] == '(' → dp[i] = dp[i-2] + 2
 * If s[i] == ')' and s[i-1] == ')' and s[i-dp[i-1]-1] == '(':
 *   dp[i] = dp[i-1] + 2 + dp[i-dp[i-1]-2]
 *
 * ✅ Iteration Order:
 * i from 1 to n-1
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - No valid pair → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
int LongestValidParentheses(string s) {
    int n = s.size(), max_len = 0;
    vector<int> dp(n, 0);

    for (int i = 1; i < n; ++i) {
        if (s[i] == ')') {
            if (s[i - 1] == '(')
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                dp[i] = dp[i - 1] + 2 +
                        (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
        }
        max_len = max(max_len, dp[i]);
    }

    return max_len;
}

/**
 * Problem 100: Palindrome Linked List (LC 234)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given the head of a singly linked list, return true if it's a palindrome.
 *
 * 🔍 Example:
 * Input: 1 -> 2 -> 2 -> 1
 * Output: true
 *
 * 🎯 Key Insight:
 * 1. Use slow and fast pointers to find the middle.
 * 2. Reverse the second half of the list.
 * 3. Compare both halves node by node.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Use fast/slow pointers to reach midpoint
 * ✅ Step 2: Reverse second half of the list
 * ✅ Step 3: Compare values of both halves
 * ✅ Step 4: (Optional) Restore list if needed
 *
 * 🚨 Edge Cases:
 * - Empty list or single node → true
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

ListNode* ReverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* next_temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_temp;
    }

    return prev;
}

bool IsPalindrome234(ListNode* head) {
    if (!head || !head->next) return true;

    // ✅ Step 1: Find midpoint using slow/fast pointers
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // ✅ Step 2: Reverse second half
    ListNode* second_half = ReverseList(slow);

    // ✅ Step 3: Compare both halves
    ListNode* first_half = head;
    ListNode* second_ptr = second_half;

    while (second_ptr) {
        if (first_half->val != second_ptr->val) {
            return false;
        }
        first_half = first_half->next;
        second_ptr = second_ptr->next;
    }

    return true;
}

/**
 * Problem 101: Largest Rectangle in Histogram (LC 84)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers `heights` representing the histogram's bar height where the width of each bar is 1,
 * return the area of the largest rectangle in the histogram.
 *
 * 🔍 Example:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10  // from bar heights 5 and 6: width = 2, height = 5
 *
 * 🎯 Key Insight:
 * Use a **monotonic increasing stack** to maintain indices of bars.
 * When a lower height is encountered, pop from stack and calculate area with height = popped bar,
 * width = current index - previous lower index - 1.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Append a 0 to the end to flush the stack at the end.
 * ✅ Step 2: For each bar, push index if height is increasing.
 * ✅ Step 3: If current height < top of stack → pop and compute area.
 *
 * 🚨 Edge Cases:
 * - Empty input → return 0
 * - All increasing → resolved at end with appended 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) — for the stack
 */

int LargestRectangleArea84(vector<int>& heights) {
    heights.push_back(0);  // Sentinel to flush remaining stack
    stack<int> index_stack;
    int max_area = 0;

    for (int i = 0; i < heights.size(); ++i) {
        while (!index_stack.empty() && heights[i] < heights[index_stack.top()]) {
            int height = heights[index_stack.top()];
            index_stack.pop();
            int width = index_stack.empty() ? i : i - index_stack.top() - 1;
            max_area = max(max_area, height * width);
        }
        index_stack.push(i);
    }

    return max_area;
}

/**
 * Problem 102: Battleships in a Board (LC 419)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D board where 'X' represents part of a battleship and '.' represents empty water,
 * count how many **distinct battleships** are on the board.
 *
 * Constraints:
 * - Battleships are placed either horizontally or vertically.
 * - Battleships are separated by at least one empty cell.
 *
 * 🔍 Example:
 * Input:
 * X . . X
 * . . . X
 * . . . X
 * Output: 2
 *
 * 🎯 Key Insight:
 * Only count the **top-left** cell (start of each ship).
 * A cell is a "new battleship head" if:
 * - It's 'X'
 * - Top and left neighbors are not 'X'
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Traverse each cell in board
 * ✅ If board[i][j] == 'X' and
 *    - (i == 0 or board[i-1][j] != 'X') and
 *    - (j == 0 or board[i][j-1] != 'X') → count++
 *
 * 🚨 Edge Cases:
 * - Empty board → return 0
 * - All '.' → return 0
 * - All connected 'X' → only count once
 *
 * ⏱️ Time Complexity: O(m × n)
 * 🧠 Space Complexity: O(1) — no extra space used
 */

int CountBattleships419(vector<vector<char>>& board) {
    int rows = board.size();
    if (rows == 0) return 0;

    int cols = board[0].size();
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] != 'X') continue;
            if (i > 0 && board[i - 1][j] == 'X') continue;
            if (j > 0 && board[i][j - 1] == 'X') continue;
            count++;
        }
    }

    return count;
}

/**
 * Problem 103: Product of Two Run-Length Encoded Arrays (LC 1868)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * You are given two run-length encoded arrays `encoded1` and `encoded2`.
 * Each element is a pair [val, freq], meaning that `val` repeats `freq` times.
 * Return the run-length encoded product of the two arrays, where:
 * - Each value is the product of corresponding positions in the full arrays.
 * - Output should also be run-length encoded.
 *
 * 🔍 Example:
 * Input: encoded1 = [[1,3],[2,3]], encoded2 = [[6,3],[3,3]]
 * Output: [[6,3],[6,3]]
 * Explanation:
 * Full arrays: [1,1,1,2,2,2] and [6,6,6,3,3,3]
 * Product:     [6,6,6,6,6,6] → RLE: [[6,6]]
 *
 * 🎯 Key Insight:
 * Simulate merge of two RLE streams using two pointers.
 * For each pair, take `min(freq1, freq2)`, and multiply their values.
 * Merge adjacent same-product segments in result.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Use two pointers `i` and `j` to track positions in encoded1 and encoded2
 * ✅ Track remaining frequencies `f1` and `f2` at each position
 * ✅ For each iteration:
 *   - Take min(f1, f2)
 *   - product = v1 * v2
 *   - Merge into result if product matches last
 *
 * 🚨 Edge Cases:
 * - Result segments with same value should be merged
 * - Arrays of unequal expansion length are invalid by problem constraint
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(k), where k is number of output segments
 */

vector<vector<int>> FindRLEArray1868(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
    vector<vector<int>> result;
    int i = 0, j = 0;
    int f1 = 0, f2 = 0;

    while (i < encoded1.size() && j < encoded2.size()) {
        int v1 = encoded1[i][0], v2 = encoded2[j][0];
        f1 = encoded1[i][1];
        f2 = encoded2[j][1];

        int min_freq = min(f1, f2);
        int product = v1 * v2;

        if (!result.empty() && result.back()[0] == product) {
            result.back()[1] += min_freq;
        } else {
            result.push_back({product, min_freq});
        }

        encoded1[i][1] -= min_freq;
        encoded2[j][1] -= min_freq;

        if (encoded1[i][1] == 0) i++;
        if (encoded2[j][1] == 0) j++;
    }

    return result;
}

/**
 * Problem 104: Zigzag Conversion (LC 6)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Convert the input string into a zigzag pattern over `num_rows`,
 * and then read row by row to produce the final output string.
 *
 * 🔍 Example:
 * Input: s = "PAYPALISHIRING", num_rows = 3
 * Output: "PAHNAPLSIIGYIR"
 * Explanation:
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * 🎯 Key Insight:
 * Simulate placing characters into `num_rows` strings, one for each row.
 * Switch direction when reaching top or bottom row.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Initialize an array of `num_rows` strings.
 * ✅ Step 2: Use a pointer `curr_row` and direction flag `going_down`.
 * ✅ Step 3: Traverse `s`, add each char to `rows[curr_row]`, and update row index.
 * ✅ Step 4: Concatenate all rows to form result.
 *
 * 🚨 Edge Cases:
 * - num_rows == 1 → return original string (no zigzag)
 * - num_rows >= s.length() → same as above
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

string ConvertZigzag6(string s, int num_rows) {
    if (num_rows == 1 || s.length() <= num_rows) return s;

    vector<string> rows(num_rows);
    int curr_row = 0;
    bool going_down = false;

    for (char c : s) {
        rows[curr_row] += c;
        if (curr_row == 0 || curr_row == num_rows - 1) {
            going_down = !going_down;
        }
        curr_row += going_down ? 1 : -1;
    }

    string result;
    for (const string& row : rows) {
        result += row;
    }

    return result;
}

/**
 * Problem 105: Letter Combinations of a Phone Number (LC 17)
 * -----------------------------------------------------------
 * 🧠 Description:
 * Given a string of digits from 2–9, return all possible letter combinations.
 *
 * 🔍 Example:
 * Input: "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * 🎯 Key Insight:
 * Backtracking on digit positions, append all valid letters.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * digit_to_letters[d] = mapped letters
 * path = current letter string
 *
 * ✅ Base Case Initialization:
 * path.length() == digits.length() → add to result
 *
 * ✅ Transition:
 * For each letter in digit mapping → recurse
 *
 * ⏱️ Time Complexity: O(3^n) to O(4^n)
 * 🧠 Space Complexity: O(n) for call stack
 */
void Backtrack17(const string& digits, const unordered_map<char, string>& mapping,
               int index, string& path, vector<string>& result) {
    if (index == digits.size()) {
        result.push_back(path);
        return;
    }

    for (char c : mapping.at(digits[index])) {
        path.push_back(c);
        Backtrack17(digits, mapping, index + 1, path, result);
        path.pop_back();
    }
}

vector<string> LetterCombinations(string digits) {
    if (digits.empty()) return {};

    unordered_map<char, string> mapping = {
        {'2',"abc"}, {'3',"def"}, {'4',"ghi"}, {'5',"jkl"},
        {'6',"mno"}, {'7',"pqrs"}, {'8',"tuv"}, {'9',"wxyz"}
    };

    vector<string> result;
    string path;
    Backtrack17(digits, mapping, 0, path, result);
    return result;
}

/**
 * Problem 106: Goat Latin (LC 824)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Convert a sentence to "Goat Latin" using these rules:
 * 1. If a word begins with a vowel, append "ma" to the end.
 * 2. If a word begins with a consonant, move first letter to end and add "ma".
 * 3. Add one 'a' for each word index (starting from 1).
 *
 * 🔍 Example:
 * Input: "I speak Goat Latin"
 * Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
 *
 * 🎯 Key Insight:
 * - Use a helper to check vowels.
 * - Split by space, process word-by-word.
 * - Track word index to build trailing 'a's.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Split string into words by space
 * ✅ Step 2: Apply Goat Latin rules per word
 * ✅ Step 3: Join words with space
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - Multiple spaces not expected per constraints
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

string ToGoatLatin824(string sentence) {
    istringstream iss(sentence);
    string word, result;
    string suffix = "a";
    unordered_set<char> vowels = {'a','e','i','o','u','A','E','I','O','U'};

    while (iss >> word) {
        if (vowels.count(word[0])) {
            word += "ma";
        } else {
            word = word.substr(1) + word[0] + "ma";
        }

        word += suffix;
        suffix += "a";

        if (!result.empty()) result += " ";
        result += word;
    }

    return result;
}

/**
 * Problem 107: Count Subarrays With Score Less Than K (LC 2302)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers `nums` and a positive number `k`, return the number of **contiguous subarrays**
 * where the score = (sum of elements) × (length of subarray) is **strictly less than k**.
 *
 * 🔍 Example:
 * Input: nums = [2,1,4,3,5], k = 10
 * Output: 6
 * Explanation:
 * Valid subarrays: [2], [1], [4], [3], [5], [2,1]
 *
 * 🎯 Key Insight:
 * Use a sliding window to maintain a valid range [start, end] where the score is valid:
 * - score = (sum of subarray) × (end - start + 1) < k
 * - Shrink window from left if score exceeds or equals k
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Maintain window [start...end]
 * ✅ Track current window sum
 * ✅ For each `end`, shrink `start` while score ≥ k
 * ✅ For valid window, add (end - start + 1) to result
 *
 * 🚨 Edge Cases:
 * - k is very small → may result in 0
 * - Empty array → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

long long CountSubarrays2302(vector<int>& nums, long long k) {
    long long result = 0;
    long long total = 0;
    int start = 0;

    for (int end = 0; end < nums.size(); ++end) {
        total += nums[end];

        while (total * (end - start + 1) >= k) {
            total -= nums[start++];
        }

        result += end - start + 1;
    }

    return result;
}

/**
 * Problem 108: Find the Most Common Response (LC 3527)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D string array `responses` where each `responses[i]` is an array of strings
 * representing survey responses from the ith day, return the most common response.
 * If there is a tie, return the lexicographically smallest response.
 *
 * 🔍 Example:
 * Input: responses = [["a","b","c"],["a","b","b"],["b","c","d"]]
 * Output: "b"
 *
 * 🎯 Key Insight:
 * - For each day's responses, consider only unique responses.
 * - Count the number of days each unique response appears.
 * - Return the response with the highest count; in case of tie, the lex smallest.
 *
 * 💡 Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Initialize a hash map to count response occurrences.
 * ✅ Step 2: For each day's responses:
 *     - Convert to a set to remove duplicates.
 *     - Increment count for each unique response.
 * ✅ Step 3: Iterate over the hash map to find the response with the highest count.
 *     - In case of tie, select the lexicographically smallest response.
 *
 * 🚨 Edge Cases:
 * - Empty responses → return empty string.
 *
 * ⏱️ Time Complexity: O(n * m), where n is number of days, m is average responses per day.
 * 🧠 Space Complexity: O(k), where k is total number of unique responses.
 */

string FindMostCommonResponse3527(vector<vector<string>>& responses) {
    unordered_map<string, int> response_count;
    for (const auto& day_responses : responses) {
        unordered_set<string> unique_responses(day_responses.begin(), day_responses.end());
        for (const auto& response : unique_responses) {
            response_count[response]++;
        }
    }

    string result;
    int max_count = 0;
    for (const auto& [response, count] : response_count) {
        if (count > max_count || (count == max_count && response < result)) {
            max_count = count;
            result = response;
        }
    }

    return result;
}

/**
 * Problem 109: Count Subarrays Where Max Element Appears at Least K Times (LC 2962)
 * -----------------------------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return the number of subarrays
 * where the maximum element in that subarray appears at least `k` times.
 *
 * 🔍 Example:
 * Input: nums = [1,3,2,3,3], k = 2
 * Output: 6
 * Explanation: The valid subarrays are:
 * [3,2,3], [3,2,3,3], [2,3,3], [3,3], [1,3,2,3], [1,3,2,3,3]
 *
 * 💡 Key Insight:
 * - Maintain a sliding window where the global max appears at least k times.
 * - Every subarray ending at `right` and starting from `left` is valid when this condition is met.
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------------------------
 * ✅ Step 1: Identify the global maximum element in the array.
 * ✅ Step 2: Initialize sliding window using two pointers: left and right.
 * ✅ Step 3: Track the number of times `max_val` appears in the current window.
 * ✅ Step 4: Shrink the window from the left when the count of max exceeds or equals k.
 * ✅ Step 5: For every valid window, all subarrays ending at right and starting from left are valid.
 *
 * 🚨 Edge Cases:
 * - Empty array → return 0
 * - k == 0 → return 0 (no subarray satisfies this)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int CountSubarrays2962(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0 || k == 0) return 0;

    int max_val = *max_element(nums.begin(), nums.end());
    int left = 0, count = 0;
    long long result = 0;

    for (int right = 0; right < n; ++right) {
        if (nums[right] == max_val) {
            count++;
        }

        while (count >= k) {
            result += (n - right);  // all subarrays starting at `left` are valid
            if (nums[left] == max_val) {
                count--;
            }
            left++;
        }
    }

    return static_cast<int>(result);
}

/**
 * Problem 110: Remove All Adjacent Duplicates in String II (LC 1209)
 * -------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, a k integer `k`, remove all adjacent duplicates in the string where
 * a group of k or more adjacent characters are the same. The removals should be performed
 * repeatedly until no more k adjacent duplicates remain.
 * Return the final string after all such duplicate removals have been performed.
 *
 * 🔍 Example:
 * Input: s = "deeedbbcccbdaa", k = 3
 * Output: "aa"
 * Explanation:
 * - Remove "eee" -> "ddbbcccbdaa"
 * - Remove "ccc" -> "ddbbbd"
 * - Remove "bbb" -> "dd"
 * - Result is "aa"
 *
 * 💡 Key Insight:
 * - Use a stack to store pairs of (character, count).
 * - If the top of stack matches current char, increment count.
 * - Once count reaches k, pop that element from stack.
 * - Rebuild the final string from the stack.
 *
 * ✅ Strategy:
 * -------------------------------------------------------------------
 * ✅ Step 1: Iterate over each character in the input string.
 * ✅ Step 2: Use a stack to track the character and its consecutive count.
 * ✅ Step 3: If current character equals top of stack, increment count.
 * ✅ Step 4: If count reaches k, pop the element (simulate removal).
 * ✅ Step 5: After traversal, rebuild the resulting string.
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - k = 1 → all characters should be removed
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

string RemoveDuplicates1209(string s, int k) {
    stack<pair<char, int>> char_stack;

    for (char ch : s) {
        if (!char_stack.empty() && char_stack.top().first == ch) {
            char_stack.top().second++;
            if (char_stack.top().second == k) {
                char_stack.pop();  // remove the k duplicates
            }
        } else {
            char_stack.emplace(ch, 1);
        }
    }

    string result;
    while (!char_stack.empty()) {
        auto [ch, count] = char_stack.top();
        char_stack.pop();
        result.append(count, ch);
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Problem 111: Find Numbers with Even Number of Digits (LC 1295)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an array `nums` of integers, return how many of them contain an even number of digits.
 *
 * 🔍 Example:
 * Input: nums = [12,345,2,6,7896]
 * Output: 2
 * Explanation:
 * - 12 has 2 digits → even
 * - 345 has 3 digits → odd
 * - 2 has 1 digit → odd
 * - 6 has 1 digit → odd
 * - 7896 has 4 digits → even
 * => Count = 2
 *
 * 💡 Key Insight:
 * - To count digits in a number, either:
 *   - Convert to string and check length, or
 *   - Use division or logarithmic method.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Traverse each number in `nums`.
 * ✅ Step 2: Count number of digits using string conversion or division.
 * ✅ Step 3: If the digit count is even, increment result.
 *
 * 🚨 Edge Cases:
 * - Negative numbers still count their digits (sign doesn't matter).
 * - 0 has 1 digit.
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int FindNumbers1295(vector<int>& nums) {
    int result = 0;

    for (int num : nums) {
        int digit_count = 0;
        int val = abs(num);  // Ensure positive

        do {
            digit_count++;
            val /= 10;
        } while (val > 0);

        if (digit_count % 2 == 0) {
            result++;
        }
    }

    return result;
}

/**
 * Problem 112: Kth Smallest Element in a Sorted Matrix (LC 378)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given an `n x n` matrix where each of the rows and columns is sorted in ascending order,
 * and an integer `k`, return the kth smallest element in the matrix.
 *
 * 🔍 Example:
 * Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
 * Output: 13
 * Explanation: The elements in order are:
 * [1,5,9,10,11,12,13,13,15]; the 8th smallest is 13.
 *
 * 💡 Key Insight:
 * - Binary search on value range instead of index.
 * - Count how many elements are less than or equal to mid using each row.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Define the search space: [matrix[0][0], matrix[n-1][n-1]].
 * ✅ Step 2: Use binary search to guess a mid value.
 * ✅ Step 3: For each guess, count how many elements in matrix ≤ mid.
 * ✅ Step 4: If count < k → move right; else move left.
 *
 * 🚨 Edge Cases:
 * - Matrix of size 1x1 → return the only element
 * - k = 1 → return minimum element
 * - k = n*n → return maximum element
 *
 * ⏱️ Time Complexity: O(n * log(max - min))
 * 🧠 Space Complexity: O(1)
 */

int KthSmallest378(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0];
    int right = matrix[n - 1][n - 1];

    auto count_less_equal = [&](int mid) {
        int count = 0, row = n - 1, col = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += (row + 1);
                col++;
            } else {
                row--;
            }
        }
        return count;
    };

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (count_less_equal(mid) < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

/**
 * Problem 113: Binary Tree Inorder Traversal (LC 94)
 * -----------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the inorder traversal of its nodes' values.
 * Inorder traversal visits nodes in the order: left → root → right.
 *
 * 🔍 Example:
 * Input: root = [1,null,2,3]
 * Output: [1,3,2]
 *
 * 💡 Key Insight:
 * - Recursively traverse the left subtree, then the root, then the right subtree.
 * - Alternatively, use an explicit stack for iterative traversal.
 *
 * ✅ Strategy:
 * -----------------------------------------------------
 * ✅ Step 1: Initialize an empty stack and a current pointer to root.
 * ✅ Step 2: Traverse leftmost subtree while pushing nodes onto stack.
 * ✅ Step 3: Process the top of stack and move to right child.
 * ✅ Step 4: Repeat until stack is empty and current is null.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return empty vector.
 * - Tree with single node → return [root->val]
 *
 * ⏱️ Time Complexity: O(n), where n is the number of nodes.
 * 🧠 Space Complexity: O(n), for the stack in the worst case.
 */

vector<int> InorderTraversal94(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> node_stack;
    TreeNode* current = root;

    while (current != nullptr || !node_stack.empty()) {
        while (current != nullptr) {
            node_stack.push(current);
            current = current->left;
        }

        current = node_stack.top();
        node_stack.pop();
        result.push_back(current->val);
        current = current->right;
    }

    return result;
}

/**
 * Problem 114: Maximum Number of Tasks You Can Assign (LC 2071)
 * -----------------------------------------------------------------
 * 🧠 Description:
 * You have `n` tasks and `m` workers. Each task has a strength requirement, and each worker has strength.
 * You can assign up to `pills` temporary strength boosts (each boost adds `strength` to a worker).
 * Return the **maximum number of tasks** you can assign such that:
 * - Each task is assigned to a worker with sufficient strength (with or without pill).
 * - Each worker is assigned at most one task.
 *
 * 🔍 Example:
 * Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
 * Output: 3
 * Explanation:
 * Assign task 1 (1) to worker 1 (3)
 * Assign task 2 (2) to worker 2 (3)
 * Assign task 0 (3) to worker 0 (0) with a pill (0+1 >= 3)
 *
 * 💡 Key Insight:
 * - Binary search for maximum number of assignable tasks.
 * - Use multiset for efficient worker assignment.
 * - Try to greedily assign strongest worker to hardest task within limit.
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------
 * ✅ Step 1: Sort tasks and workers in non-increasing order.
 * ✅ Step 2: Use binary search on number of tasks to assign.
 * ✅ Step 3: For each guess, simulate assignment using multiset and pills.
 * ✅ Step 4: For each task from hardest to easiest, try:
 *     - Assign strongest available worker directly.
 *     - Or assign weakest one using pill (if feasible).
 *
 * 🚨 Edge Cases:
 * - No pills → workers must directly satisfy tasks.
 * - strength = 0 → pills are ineffective.
 *
 * ⏱️ Time Complexity: O(n log n + m log m + log n * n log n)
 * 🧠 Space Complexity: O(n)
 */

bool CanAssign(int k, const vector<int>& tasks, const vector<int>& workers, int pills, int strength) {
    multiset<int> available_workers(workers.end() - k, workers.end());

    int used_pills = 0;
    for (int i = k - 1; i >= 0; --i) {
        int task = tasks[i];

        // Try strongest available worker directly
        auto it = prev(available_workers.end());
        if (*it >= task) {
            available_workers.erase(it);
        } else {
            // Try weakest that can be boosted
            auto weak = available_workers.lower_bound(task - strength);
            if (weak == available_workers.end()) return false;
            available_workers.erase(weak);
            used_pills++;
            if (used_pills > pills) return false;
        }
    }

    return true;
}

int MaxTasks2071(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    int left = 0, right = min(tasks.size(), workers.size()), result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (CanAssign(mid, tasks, workers, pills, strength)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

/**
 * Problem 115: Alien Dictionary (LC 269) 🔒
 * -----------------------------------------
 * 🧠 Description:
 * Given a sorted dictionary of an alien language, return a string representing the order of characters.
 *
 * 🔍 Example:
 * Input: words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * 🎯 Key Insight:
 * Build a directed graph and apply topological sort.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * graph[c] = set of characters that come after c
 * indegree[c] = number of incoming edges to c
 *
 * ✅ Transition:
 * For each adjacent word pair, find first mismatch and add edge
 *
 * ✅ Iteration Order:
 * BFS topological sort (Kahn's algorithm)
 *
 * ⏱️ Time Complexity: O(N)
 * 🧠 Space Complexity: O(C) where C is number of unique letters
 */
string AlienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> indegree;

    // Initialize graph
    for (const string& word : words)
        for (char c : word) indegree[c] = 0;

    // Build edges
    for (int i = 0; i < words.size() - 1; ++i) {
        string w1 = words[i], w2 = words[i + 1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for (int j = 0; j < len; ++j) {
            if (w1[j] != w2[j]) {
                if (!graph[w1[j]].count(w2[j])) {
                    graph[w1[j]].insert(w2[j]);
                    indegree[w2[j]]++;
                }
                found = true;
                break;
            }
        }
        if (!found && w1.size() > w2.size()) return "";
    }

    // Topological sort
    queue<char> q;
    for (auto& [ch, deg] : indegree)
        if (deg == 0) q.push(ch);

    string result;
    while (!q.empty()) {
        char c = q.front(); q.pop();
        result += c;

        for (char neighbor : graph[c]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return result.size() == indegree.size() ? result : "";
}

/**
 * Problem 116: Missing Element in Sorted Array (LC 1060)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a sorted array `nums` with no duplicates, and an integer `k`,
 * return the kth missing number starting from the first element in the array.
 *
 * 🔍 Example:
 * Input: nums = [4,7,9,10], k = 1
 * Output: 5
 *
 * Input: nums = [4,7,9,10], k = 3
 * Output: 8
 *
 * 💡 Key Insight:
 * - For any index `i`, the number of missing integers before index `i` is:
 *     missing(i) = nums[i] - nums[0] - i
 * - Binary search for the smallest index where missing(i) ≥ k.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Define helper function missing(i) = nums[i] - nums[0] - i.
 * ✅ Step 2: Use binary search to find the first index where missing(i) ≥ k.
 * ✅ Step 3: If k > total missing → return nums[n - 1] + (k - missing(n - 1))
 * ✅ Step 4: Else, compute the kth missing using: nums[left - 1] + (k - missing(left - 1))
 *
 * 🚨 Edge Cases:
 * - k = 1 → return nums[0] + 1 if no missing before index 0
 * - Large k → might fall beyond last element
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */

int MissingElement1060(vector<int>& nums, int k) {
    int n = nums.size();

    auto missing = [&](int index) {
        return nums[index] - nums[0] - index;
    };

    // If kth missing is beyond the last number
    if (k > missing(n - 1)) {
        return nums[n - 1] + (k - missing(n - 1));
    }

    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (missing(mid) < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return nums[left - 1] + (k - missing(left - 1));
}

/**
 * Problem 117: Push Dominoes (LC 838)
 * -------------------------------------------------------------
 * 🧠 Description:
 * There are `n` dominoes in a line, each domino is either:
 *   - 'L' (pushed to the left)
 *   - 'R' (pushed to the right)
 *   - '.' (standing still)
 *
 * After each second, a domino that is falling pushes the adjacent one in its direction.
 * Return the final state of the dominoes after all movements are done.
 *
 * 🔍 Example:
 * Input: dominoes = "RR.L"
 * Output: "RR.L"
 * Explanation:
 * - The first two dominoes push to the right.
 * - The third remains upright because it's pushed from both sides simultaneously.
 *
 * Input: dominoes = ".L.R...LR..L.."
 * Output: "LL.RR.LLRRLL.."
 *
 * 💡 Key Insight:
 * - Simulate the forces from left to right (positive force for 'R') and from right to left (negative force for 'L').
 * - At each position, the net force determines the final state.
 * - Use two passes to accumulate force, then determine the result.
 *
 * ✅ Strategy:
 * -------------------------------------------------------------
 * ✅ Step 1: First pass from left to right to apply force of 'R'.
 * ✅ Step 2: Second pass from right to left to apply force of 'L'.
 * ✅ Step 3: For each index, decide:
 *     - Positive force → 'R'
 *     - Negative force → 'L'
 *     - Zero → '.'
 *
 * 🚨 Edge Cases:
 * - No dominoes → return ""
 * - All '.' → return original string
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

string PushDominoes838(string dominoes) {
    int n = dominoes.size();
    vector<int> force(n, 0);

    int f = 0;
    // → Apply rightward force
    for (int i = 0; i < n; ++i) {
        if (dominoes[i] == 'R') {
            f = n;  // maximum force
        } else if (dominoes[i] == 'L') {
            f = 0;  // reset
        } else {
            f = max(f - 1, 0);  // decay
        }
        force[i] += f;
    }

    f = 0;
    // ← Apply leftward force
    for (int i = n - 1; i >= 0; --i) {
        if (dominoes[i] == 'L') {
            f = n;
        } else if (dominoes[i] == 'R') {
            f = 0;
        } else {
            f = max(f - 1, 0);
        }
        force[i] -= f;
    }

    string result;
    for (int i = 0; i < n; ++i) {
        if (force[i] > 0) {
            result += 'R';
        } else if (force[i] < 0) {
            result += 'L';
        } else {
            result += '.';
        }
    }

    return result;
}

/**
 * Problem 118: Add Two Integers (LC 2235)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given two integers `num1` and `num2`, return their sum.
 *
 * 🔍 Example:
 * Input: num1 = 12, num2 = 5
 * Output: 17
 *
 * Input: num1 = -10, num2 = 4
 * Output: -6
 *
 * 💡 Key Insight:
 * - This is a direct arithmetic operation with no edge constraints.
 * - Simply return the sum of two integers.
 *
 * ✅ Strategy:
 * -------------------------------------------------------------
 * ✅ Step 1: Add the two input numbers using `+` operator.
 *
 * 🚨 Edge Cases:
 * - Handles both positive and negative integers.
 * - No overflow/underflow constraint mentioned, assume 32-bit int.
 *
 * ⏱️ Time Complexity: O(1)
 * 🧠 Space Complexity: O(1)
 */

int AddTwoIntegers2235(int num1, int num2) {
    return num1 + num2;
}

/**
 * Problem 119: Binary Tree Cameras (LC 968)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, place cameras on some nodes so that every node is monitored.
 * Each camera at a node can monitor its parent, itself, and its immediate children.
 * Return the **minimum number of cameras** needed to monitor all nodes.
 *
 * 🔍 Example:
 * Input: root = [0,0,null,0,0]
 * Output: 1
 * Explanation: One camera placed at node 1 or 2 covers the whole tree.
 *
 * 💡 Key Insight:
 * - Use **post-order DFS traversal**.
 * - For each node, track its coverage status:
 *   - 0 → Node needs a camera
 *   - 1 → Node has a camera
 *   - 2 → Node is covered by a camera
 *
 * ✅ Strategy:
 * -------------------------------------------------------------
 * ✅ Step 1: Traverse tree in post-order (left → right → root).
 * ✅ Step 2: At each node:
 *     - If any child needs a camera → place camera here.
 *     - If any child has a camera → this node is covered.
 *     - If both children are covered → this node needs a camera.
 * ✅ Step 3: After traversal, if root needs a camera → add one more.
 *
 * 🚨 Edge Cases:
 * - Single node tree → requires one camera.
 * - Full binary tree → may require cameras at alternating depths.
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h), h is the height of the tree (stack space)
 */

int _camera_count = 0;

// Return status:
// 0 = needs camera
// 1 = has camera
// 2 = covered
int dfs_camera(TreeNode* node) {
    if (!node) return 2;

    int left = dfs_camera(node->left);
    int right = dfs_camera(node->right);

    if (left == 0 || right == 0) {
        _camera_count++;
        return 1;
    }

    if (left == 1 || right == 1) {
        return 2;
    }

    return 0;
}

int MinCameraCover968(TreeNode* root) {
    _camera_count = 0;
    if (dfs_camera(root) == 0) {
        _camera_count++;
    }
    return _camera_count;
}

/**
 * Problem 120: Minesweeper (LC 529)
 * -------------------------------------------------------------
 * 🧠 Description:
 * You are given a 2D char matrix representing the game board and a cell to click.
 * Implement the **reveal logic** for Minesweeper:
 * - If a mine ('M') is clicked → change to 'X'.
 * - If an empty square ('E') with adjacent mines → show number of adjacent mines.
 * - If an empty square ('E') with no adjacent mines → mark as 'B' and recurse on neighbors.
 *
 * 🔍 Example:
 * Input:
 * board = [
 *   ['E','E','E','E','E'],
 *   ['E','E','M','E','E'],
 *   ['E','E','E','E','E'],
 *   ['E','E','E','E','E']
 * ]
 * click = [3,0]
 * Output:
 * [
 *   ['B','1','E','1','B'],
 *   ['B','1','M','1','B'],
 *   ['B','1','1','1','B'],
 *   ['B','B','B','B','B']
 * ]
 *
 * 💡 Key Insight:
 * - Standard DFS problem with boundary checks and mine counting.
 * - Use direction vectors to explore 8-connected neighbors.
 *
 * ✅ Strategy:
 * -------------------------------------------------------------
 * ✅ Step 1: If click is a mine, mark it as 'X'.
 * ✅ Step 2: Otherwise, perform DFS from the clicked cell.
 * ✅ Step 3: If current cell has adjacent mines → write digit and stop.
 * ✅ Step 4: Else mark as 'B' and recurse on all 8 neighbors.
 *
 * 🚨 Edge Cases:
 * - Clicking on a mine ends the game.
 * - Ensure boundary checks for recursion.
 *
 * ⏱️ Time Complexity: O(m * n) in worst case
 * 🧠 Space Complexity: O(m * n) for recursion stack
 */

vector<vector<int>> directions529 = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

bool IsValid529(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

int CountAdjacentMines(vector<vector<char>>& board, int x, int y) {
    int m = board.size(), n = board[0].size();
    int count = 0;
    for (const auto& dir : directions529) {
        int nx = x + dir[0], ny = y + dir[1];
        if (IsValid529(nx, ny, m, n) && board[nx][ny] == 'M') {
            count++;
        }
    }
    return count;
}

void DfsReveal(vector<vector<char>>& board, int x, int y) {
    int m = board.size(), n = board[0].size();
    if (!IsValid529(x, y, m, n) || board[x][y] != 'E') return;

    int mine_count = CountAdjacentMines(board, x, y);
    if (mine_count > 0) {
        board[x][y] = '0' + mine_count;
    } else {
        board[x][y] = 'B';
        for (const auto& dir : directions529) {
            int nx = x + dir[0], ny = y + dir[1];
            DfsReveal(board, nx, ny);
        }
    }
}

vector<vector<char>> UpdateBoard529(vector<vector<char>>& board, vector<int>& click) {
    int x = click[0], y = click[1];
    if (board[x][y] == 'M') {
        board[x][y] = 'X';
    } else {
        DfsReveal(board, x, y);
    }
    return board;
}

/**
 * Problem 121: Boundary of Binary Tree (LC 545)
 * -----------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return the values of its boundary in **anti-clockwise** direction starting from the root.
 * The boundary includes:
 * - The left boundary (excluding leaves),
 * - All the leaf nodes (from left to right),
 * - The right boundary (excluding leaves, in reverse order).
 *
 * 🔍 Example:
 * Input: root = [1,null,2,3,4]
 * Output: [1,3,4,2]
 *
 * 💡 Key Insight:
 * - Decompose the problem into 3 parts:
 *     1. Left boundary (excluding leaves)
 *     2. Leaves (all leaves left to right)
 *     3. Right boundary (excluding leaves, reversed)
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------
 * ✅ Step 1: Collect left boundary nodes starting from root->left.
 * ✅ Step 2: Collect all leaf nodes using DFS traversal.
 * ✅ Step 3: Collect right boundary nodes starting from root->right.
 * ✅ Step 4: Combine in order: root → left → leaves → reversed right.
 *
 * 🚨 Edge Cases:
 * - Tree with only root → just [root->val]
 * - Tree with only left or right subtree → boundary = root + that side
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

bool IsLeaf545(TreeNode* node) {
    return node && !node->left && !node->right;
}

void AddLeftBoundary(TreeNode* node, vector<int>& result) {
    TreeNode* cur = node->left;
    while (cur) {
        if (!IsLeaf545(cur)) result.push_back(cur->val);
        cur = (cur->left) ? cur->left : cur->right;
    }
}

void AddRightBoundary(TreeNode* node, vector<int>& result) {
    TreeNode* cur = node->right;
    vector<int> temp;
    while (cur) {
        if (!IsLeaf545(cur)) temp.push_back(cur->val);
        cur = (cur->right) ? cur->right : cur->left;
    }
    reverse(temp.begin(), temp.end());
    result.insert(result.end(), temp.begin(), temp.end());
}

void AddLeaves(TreeNode* node, vector<int>& result) {
    if (!node) return;
    if (IsLeaf545(node)) {
        result.push_back(node->val);
        return;
    }
    AddLeaves(node->left, result);
    AddLeaves(node->right, result);
}

vector<int> BoundaryOfBinaryTree545(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    if (!IsLeaf545(root)) result.push_back(root->val);
    AddLeftBoundary(root, result);
    AddLeaves(root, result);
    AddRightBoundary(root, result);

    return result;
}

/**
 * Problem 122: Partition to K Equal Sum Subsets (LC 698)
 * ----------------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return true if it's possible
 * to partition the array into `k` non-empty subsets whose sums are all equal.
 *
 * 🔍 Example:
 * Input: nums = [4,3,2,3,5,2,1], k = 4
 * Output: true
 * Explanation: It's possible to partition as (5), (1,4), (2,3), (2,3)
 *
 * 💡 Key Insight:
 * - If total sum isn't divisible by k → impossible.
 * - Use backtracking to try placing each number into a bucket.
 * - Sort in descending order to prune early.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------
 * ✅ Step 1: Check if sum of all elements is divisible by `k`.
 * ✅ Step 2: Use DFS/backtracking to assign elements to `k` buckets.
 * ✅ Step 3: For each number, try placing it into any bucket that has enough capacity.
 * ✅ Step 4: Backtrack if placement doesn't lead to solution.
 *
 * 🚨 Edge Cases:
 * - nums.size() < k → impossible
 * - Largest number > target → impossible
 *
 * ⏱️ Time Complexity: O(k * 2^n)
 * 🧠 Space Complexity: O(n) for visited array and recursion stack
 */

bool DfsPartition(vector<int>& nums, vector<int>& buckets, int index, int target) {
    if (index == nums.size()) return true;

    for (int i = 0; i < buckets.size(); ++i) {
        if (buckets[i] + nums[index] > target) continue;

        buckets[i] += nums[index];
        if (DfsPartition(nums, buckets, index + 1, target)) return true;
        buckets[i] -= nums[index];

        if (buckets[i] == 0) break;  // Prune: no point trying other empty buckets
    }

    return false;
}

bool CanPartitionKSubsets698(vector<int>& nums, int k) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0 || nums.size() < k) return false;

    int target = total / k;
    sort(nums.rbegin(), nums.rend());  // Start from largest to optimize pruning

    if (nums[0] > target) return false;

    vector<int> buckets(k, 0);
    return DfsPartition(nums, buckets, 0, target);
}

/**
 * Problem 123: Domino and Tromino Tiling (LC 790)
 * ---------------------------------------------------------------------
 * 🧠 Description:
 * You have 2 x n board. You can cover it with:
 * - Dominoes: 2 x 1 tiles
 * - Trominoes: L-shaped tiles (2 x 2 minus one square)
 *
 * Return the number of ways to tile the board. Since the answer may be large,
 * return it modulo 10^9 + 7.
 *
 * 🔍 Example:
 * Input: n = 3
 * Output: 5
 * Explanation:
 * The five ways are:
 * - [1x2][1x2][1x2]
 * - [1x2][2x2-L]
 * - [2x2-L][1x2]
 * - [2x2-L flipped][1x2]
 * - [1x2][2x2-L flipped]
 *
 * 💡 Key Insight:
 * - This is a **DP problem** with recurrence:
 *   dp[n] = dp[n-1] + dp[n-2] + 2 * sum(dp[0..n-3])
 * - Or optimized as:
 *   dp[n] = 2 * dp[n-1] + dp[n-3]
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------
 * ✅ Step 1: Handle base cases for n = 0, 1, 2
 * ✅ Step 2: Use bottom-up DP with recurrence:
 *     dp[i] = 2 * dp[i-1] + dp[i-3]
 * ✅ Step 3: Use modulo 1e9 + 7 to prevent overflow.
 *
 * 🚨 Edge Cases:
 * - n = 0 → return 1
 * - n = 1 → return 1
 * - n = 2 → return 2
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) or O(1) with rolling variables
 */

const int MOD = 1e9 + 7;

int NumTilings790(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    vector<long long> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; ++i) {
        dp[i] = (2 * dp[i - 1] % MOD + dp[i - 3]) % MOD;
    }

    return static_cast<int>(dp[n]);
}

/**
 * Problem 124: Longest Common Prefix (LC 14)
 * --------------------------------------------------------------------
 * 🧠 Description:
 * Write a function to find the **longest common prefix string** amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 *
 * 🔍 Example:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 *
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 * 💡 Key Insight:
 * - Vertical scanning: compare characters column by column.
 * - Stop at first mismatch or shortest string end.
 *
 * ✅ Strategy:
 * --------------------------------------------------------------------
 * ✅ Step 1: If input is empty, return "".
 * ✅ Step 2: Take the first string as base, iterate character by character.
 * ✅ Step 3: For each character, check if all strings share the same character at that position.
 * ✅ Step 4: If mismatch, return prefix up to that point.
 *
 * 🚨 Edge Cases:
 * - Empty input list → return ""
 * - One string only → return that string
 * - Any empty string inside list → return ""
 *
 * ⏱️ Time Complexity: O(n * m), where n = number of strings, m = length of shortest string
 * 🧠 Space Complexity: O(1)
 */

string LongestCommonPrefix14(vector<string>& strs) {
    if (strs.empty()) return "";

    for (int i = 0; i < strs[0].size(); ++i) {
        char ch = strs[0][i];
        for (int j = 1; j < strs.size(); ++j) {
            if (i >= strs[j].size() || strs[j][i] != ch) {
                return strs[0].substr(0, i);
            }
        }
    }

    return strs[0];
}

/**
 * Problem 125: Strobogrammatic Number (LC 246)
 * ----------------------------------------------------------------------
 * 🧠 Description:
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees.
 * Given a string `num` representing a number, return true if it is strobogrammatic.
 *
 * 🔍 Example:
 * Input: num = "69"
 * Output: true
 *
 * Input: num = "88"
 * Output: true
 *
 * Input: num = "962"
 * Output: false
 *
 * 💡 Key Insight:
 * - Use a mapping between strobogrammatic digits:
 *     - '0' ↔ '0', '1' ↔ '1', '6' ↔ '9', '8' ↔ '8', '9' ↔ '6'
 * - Compare characters from both ends, applying the mapping.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------
 * ✅ Step 1: Build a hash map of valid strobogrammatic digit pairs.
 * ✅ Step 2: Use two pointers (left, right) to compare digits.
 * ✅ Step 3: At each step, check if digits are valid and match after rotation.
 *
 * 🚨 Edge Cases:
 * - Empty string → return true
 * - Any invalid character → return false
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

bool IsStrobogrammatic246(const string& num) {
    unordered_map<char, char> strobomap = {
        {'0', '0'},
        {'1', '1'},
        {'6', '9'},
        {'8', '8'},
        {'9', '6'}
    };

    int left = 0, right = num.size() - 1;
    while (left <= right) {
        char l = num[left], r = num[right];
        if (!strobomap.count(l) || strobomap[l] != r) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

/**
 * Problem 126: Best Time to Buy and Sell Stock III (LC 123)
 * ------------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `prices` where `prices[i]` is the price of a stock on day i.
 * You may complete **at most two transactions** (buy once + sell once = one transaction).
 * Return the maximum profit you can achieve.
 * Note: You may not engage in multiple transactions at the same time.
 *
 * 🔍 Example:
 * Input: prices = [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation:
 * - Buy on day 4 (price=0), sell on day 5 (price=3), profit = 3
 * - Buy on day 6 (price=1), sell on day 7 (price=4), profit = 3
 *
 * 💡 Key Insight:
 * - Use dynamic programming:
 *     dp[k][i] = max profit up to day i with at most k transactions
 * - Optimize space to use 1D arrays.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------
 * ✅ Step 1: Initialize two arrays: buy[k] and sell[k] for k = 0..2
 * ✅ Step 2: Track max profit after each buy/sell
 * ✅ Step 3: Update state transitions for up to 2 transactions
 *
 * 🚨 Edge Cases:
 * - prices.size() < 2 → return 0
 * - All prices decreasing → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int MaxProfit123(vector<int>& prices) {
    if (prices.empty()) return 0;

    int buy1 = INT_MIN, buy2 = INT_MIN;
    int sell1 = 0, sell2 = 0;

    for (int price : prices) {
        buy1 = max(buy1, -price);           // First buy: max(-price)
        sell1 = max(sell1, buy1 + price);   // First sell: max(profit1)
        buy2 = max(buy2, sell1 - price);    // Second buy: max(profit1 - price)
        sell2 = max(sell2, buy2 + price);   // Second sell: max(profit2)
    }

    return sell2;
}

/**
 * Problem 127: Longest Substring with At Most Two Distinct Characters (LC 159)
 * ------------------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the length of the longest substring that contains
 * **at most two distinct characters**.
 *
 * 🔍 Example:
 * Input: s = "eceba"
 * Output: 3
 * Explanation: The substring is "ece"
 *
 * Input: s = "ccaabbb"
 * Output: 5
 * Explanation: The substring is "aabbb"
 *
 * 💡 Key Insight:
 * - Use sliding window technique with a hash map to track character frequency.
 * - Shrink the window when the number of distinct characters > 2.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------------
 * ✅ Step 1: Use a hash map to count character frequencies in the current window.
 * ✅ Step 2: Expand the right boundary and update the count.
 * ✅ Step 3: Shrink the left boundary if distinct characters exceed 2.
 * ✅ Step 4: Update the max length during the expansion phase.
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - String with only 1 or 2 types of characters → return s.length()
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (since alphabet is bounded, at most 128 entries)
 */

int LengthOfLongestSubstringTwoDistinct159(const string& s) {
    unordered_map<char, int> freq;
    int left = 0, max_len = 0;

    for (int right = 0; right < s.size(); ++right) {
        freq[s[right]]++;

        while (freq.size() > 2) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) {
                freq.erase(s[left]);
            }
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}

/**
 * Problem 128: Single Element in a Sorted Array (LC 540)
 * --------------------------------------------------------------------
 * 🧠 Description:
 * You are given a sorted array consisting of only integers where every element appears
 * exactly twice, except for one element which appears exactly once.
 * Return the single element that appears only once.
 *
 * 🔍 Example:
 * Input: nums = [1,1,2,3,3,4,4,8,8]
 * Output: 2
 *
 * Input: nums = [3,3,7,7,10,11,11]
 * Output: 10
 *
 * 💡 Key Insight:
 * - Use **binary search** to achieve O(log n) time.
 * - For the first index of a pair:
 *     - If index is even and nums[i] == nums[i+1], the unique element is on the right.
 *     - If index is odd and nums[i] == nums[i-1], the unique is still on the right.
 *     - Otherwise, it's on the left.
 *
 * ✅ Strategy:
 * --------------------------------------------------------------------
 * ✅ Step 1: Initialize left and right pointers for binary search.
 * ✅ Step 2: At each step, ensure mid is even to always compare with mid + 1.
 * ✅ Step 3: Narrow the search range based on where the pairing breaks.
 *
 * 🚨 Edge Cases:
 * - Only 1 element → return it directly.
 * - Unique element at start or end → still works with same logic.
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */

int SingleNonDuplicate540(const vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mid % 2 == 1) mid--;  // ensure mid is even

        if (nums[mid] == nums[mid + 1]) {
            left = mid + 2;  // pair is correct, unique is on the right
        } else {
            right = mid;     // pair breaks, unique is on the left or at mid
        }
    }

    return nums[left];
}

/**
 * Problem 129: Generate Parentheses (LC 22)
 * --------------------------------------------------------------------
 * 🧠 Description:
 * Given `n` pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 * 🔍 Example:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * 💡 Key Insight:
 * - This is a classic backtracking problem.
 * - Only add '(' if left count < n.
 * - Only add ')' if right count < left count.
 *
 * ✅ Strategy:
 * --------------------------------------------------------------------
 * ✅ Step 1: Define a helper backtracking function with current string, left, right count.
 * ✅ Step 2: Base case → when current string size is 2 * n, add to result.
 * ✅ Step 3: Recurse by adding '(' or ')' as long as constraints are satisfied.
 *
 * 🚨 Edge Cases:
 * - n = 0 → return empty list
 *
 * ⏱️ Time Complexity: O(4^n / sqrt(n)) (Catalan number)
 * 🧠 Space Complexity: O(n) recursion depth + result storage
 */

void BacktrackParentheses(int n, int open, int close, string current, vector<string>& result) {
    if (current.size() == n * 2) {
        result.push_back(current);
        return;
    }

    if (open < n) {
        BacktrackParentheses(n, open + 1, close, current + '(', result);
    }

    if (close < open) {
        BacktrackParentheses(n, open, close + 1, current + ')', result);
    }
}

vector<string> GenerateParenthesis22(int n) {
    vector<string> result;
    BacktrackParentheses(n, 0, 0, "", result);
    return result;
}

/**
 * Problem 130: Basic Calculator (LC 224)
 * ------------------------------------------------------------------------
 * 🧠 Description:
 * Implement a basic calculator to evaluate a simple expression string `s`.
 * The expression may contain:
 * - Digits
 * - '+', '-' operators
 * - Parentheses '(', ')'
 * - Whitespaces (ignored)
 *
 * 🔍 Example:
 * Input: s = "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 *
 * 💡 Key Insight:
 * - Use a stack to evaluate expressions with parentheses.
 * - Maintain a `sign` and current `result`.
 * - On encountering '(', push result and sign to stack and reset.
 * - On ')', pop last sign and result to update expression.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------
 * ✅ Step 1: Iterate over each character in the string.
 * ✅ Step 2: Parse numbers and apply current sign.
 * ✅ Step 3: On '(', push current result and sign, reset to handle subexpression.
 * ✅ Step 4: On ')', finalize inner result and combine with previous.
 *
 * 🚨 Edge Cases:
 * - Multiple digits → must build full number
 * - Leading '+' or '-' signs
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) for the stack
 */

int Calculate224(const string& s) {
    stack<int> stk;
    int result = 0;
    int number = 0;
    int sign = 1;  // 1 for '+', -1 for '-'

    for (int i = 0; i < s.size(); ++i) {
        char ch = s[i];

        if (isdigit(ch)) {
            number = number * 10 + (ch - '0');
        } else if (ch == '+') {
            result += sign * number;
            sign = 1;
            number = 0;
        } else if (ch == '-') {
            result += sign * number;
            sign = -1;
            number = 0;
        } else if (ch == '(') {
            stk.push(result);
            stk.push(sign);
            result = 0;
            sign = 1;
        } else if (ch == ')') {
            result += sign * number;
            number = 0;
            result *= stk.top(); stk.pop();      // sign before '('
            result += stk.top(); stk.pop();      // result before '('
        }
    }

    result += sign * number;
    return result;
}

/**
 * Problem 131: Number of Visible People in a Queue (LC 1944)
 * ------------------------------------------------------------------------
 * 🧠 Description:
 * There are `n` people standing in a queue, and the array `heights[i]` represents
 * the height of the ith person from the front.
 * A person can **see another person** in front of them if:
 * - That person is **shorter**, and
 * - There is **no one taller** in between blocking the view.
 * Each person can see multiple people, until their view is blocked.
 * Return an array where result[i] is the number of people person i can see.
 *
 * 🔍 Example:
 * Input: heights = [10,6,8,5,11,9]
 * Output: [3,1,2,1,1,0]
 *
 * 💡 Key Insight:
 * - This is a **monotonic decreasing stack** problem.
 * - Traverse from **right to left** and simulate the viewing process.
 * - For each person, maintain a stack of people they can see (shorter or equal).
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------
 * ✅ Step 1: Traverse the array from right to left.
 * ✅ Step 2: Use a stack to keep track of who is visible.
 * ✅ Step 3: Pop all shorter people from the stack — each is visible.
 * ✅ Step 4: If stack is not empty after popping, one more (taller) person is visible.
 *
 * 🚨 Edge Cases:
 * - Last person can never see anyone → count = 0
 * - Heights are strictly increasing → each person sees exactly 1
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

vector<int> CanSeePersonsCount1944(const vector<int>& heights) {
    int n = heights.size();
    vector<int> result(n, 0);
    stack<int> stk;  // stores height values

    for (int i = n - 1; i >= 0; --i) {
        int count = 0;
        while (!stk.empty() && heights[i] > stk.top()) {
            stk.pop();
            count++;
        }
        if (!stk.empty()) count++;  // can see the first taller person
        result[i] = count;
        stk.push(heights[i]);
    }

    return result;
}

/**
 * Problem 132: Product of Array Except Self (LC 238)
 * --------------------------------------------------
 * 🧠 Description:
 * Given an integer array nums, return an array output such that output[i] is equal to the product 
 * of all the elements of nums except nums[i], without using division and in O(n) time.
 *
 * 🔍 Example:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * 🎯 Key Insight:
 * The product of all elements except self at index i can be obtained by multiplying:
 *   - the product of all elements to the left of i (prefix)
 *   - the product of all elements to the right of i (suffix)
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * output[i] stores the prefix product of all elements before index i
 *
 * ✅ Base Case Initialization:
 * output[0] = 1, since there are no elements to the left of index 0
 *
 * ✅ Transition:
 * First pass (left to right):
 *   output[i] = output[i - 1] * nums[i - 1]
 * Second pass (right to left):
 *   output[i] *= suffix_product; suffix_product *= nums[i]
 *
 * ✅ Iteration Order:
 * - Forward pass for prefix
 * - Backward pass for suffix
 *
 * 🚨 Edge Cases:
 * - Input contains zero(s)
 * - Length 1 array
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (excluding output array, which is required)
 */
vector<int> ProductExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> output(n, 1);

    // Forward pass: compute prefix products
    for (int i = 1; i < n; ++i) {
        output[i] = output[i - 1] * nums[i - 1];
    }

    // Backward pass: compute suffix products and multiply
    int suffix_product = 1;
    for (int i = n - 1; i >= 0; --i) {
        output[i] *= suffix_product;
        suffix_product *= nums[i];
    }

    return output;
}

/**
 * Problem 133: Maximum Sum of Almost Unique Subarray (LC 3343)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * You are given an integer array `nums` and an integer `k`.
 * A subarray is called "almost unique" if no number appears more than `k` times.
 * Return the **maximum sum** of any almost unique subarray.
 *
 * 🔍 Example:
 * Input: nums = [1,2,1,2,1,2,1], k = 2
 * Output: 9
 * Explanation:
 * The subarray [2,1,2,1,2] is invalid (1 appears 3 times), but [1,2,1,2] is valid and has sum 6.
 * The valid max sum is from subarray [2,1,2,1] → sum = 6 or [1,2,1,2] → sum = 6
 *
 * 💡 Key Insight:
 * - Use sliding window + frequency map.
 * - If count of any number exceeds k, shrink window from the left.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------------
 * ✅ Step 1: Initialize sliding window and a hash map to count frequency.
 * ✅ Step 2: Expand window by moving right pointer.
 * ✅ Step 3: If any number exceeds k occurrences, shrink left pointer.
 * ✅ Step 4: Track current sum and update max sum when valid.
 *
 * 🚨 Edge Cases:
 * - k = 0 → no number allowed → return 0
 * - nums contains all unique → full window is valid
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

int MaxSumAlmostUniqueSubarray3343(const vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int left = 0, curr_sum = 0, max_sum = 0;

    for (int right = 0; right < nums.size(); ++right) {
        freq[nums[right]]++;
        curr_sum += nums[right];

        while (freq[nums[right]] > k) {
            freq[nums[left]]--;
            curr_sum -= nums[left];
            left++;
        }

        max_sum = max(max_sum, curr_sum);
    }

    return max_sum;
}

/**
 * Problem 134: Reverse Integer (LC 7)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Given a signed 32-bit integer `x`, return `x` with its digits reversed.
 * If reversing causes the value to go outside the signed 32-bit range, return 0.
 * Range: [-2^31, 2^31 - 1]
 *
 * 🔍 Example:
 * Input: x = 123
 * Output: 321
 *
 * Input: x = -123
 * Output: -321
 *
 * Input: x = 1534236469
 * Output: 0 (overflow)
 *
 * 💡 Key Insight:
 * - Use modulus and division to extract and append digits.
 * - Carefully check for overflow before multiplying and adding.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------
 * ✅ Step 1: Pop digit from x using x % 10, x /= 10.
 * ✅ Step 2: Push digit to reversed number using res = res * 10 + digit.
 * ✅ Step 3: Before pushing, check if it causes overflow.
 *
 * 🚨 Edge Cases:
 * - x = 0 → return 0
 * - Overflow check: res > INT_MAX / 10 or res == INT_MAX / 10 and digit > 7
 *
 * ⏱️ Time Complexity: O(log x)
 * 🧠 Space Complexity: O(1)
 */

int ReverseInteger7(int x) {
    int result = 0;

    while (x != 0) {
        int digit = x % 10;
        x /= 10;

        // Check for overflow
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) return 0;
        if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit < -8)) return 0;

        result = result * 10 + digit;
    }

    return result;
}

/**
 * Problem 135: Three Consecutive Odds (LC 1550)
 * -----------------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers `arr`, return true if there are three consecutive
 * odd numbers in the array, otherwise return false.
 *
 * 🔍 Example:
 * Input: arr = [2,6,4,1]
 * Output: false
 *
 * Input: arr = [1,2,34,3,4,5,7,23,12]
 * Output: true  // [5,7,23]
 *
 * 💡 Key Insight:
 * - Use a simple counter to track how many consecutive odd numbers have appeared.
 * - Reset counter if an even number is found.
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------
 * ✅ Step 1: Traverse the array from left to right.
 * ✅ Step 2: If current number is odd → increment counter.
 * ✅ Step 3: If it's even → reset counter to 0.
 * ✅ Step 4: If counter reaches 3, return true.
 *
 * 🚨 Edge Cases:
 * - Array size < 3 → return false immediately.
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

bool ThreeConsecutiveOdds1550(const vector<int>& arr) {
    int count = 0;
    for (int num : arr) {
        if (num % 2 == 1) {
            count++;
            if (count == 3) return true;
        } else {
            count = 0;
        }
    }
    return false;
}

/**
 * Problem 136: Merge Strings Alternately (LC 1768)
 * ----------------------------------------------------------------------
 * 🧠 Description:
 * You are given two strings `word1` and `word2`.
 * Merge the strings by adding letters in alternating order, starting with `word1`.
 * If one string is longer, append the remaining characters at the end.
 *
 * 🔍 Example:
 * Input: word1 = "abc", word2 = "pqr"
 * Output: "apbqcr"
 *
 * Input: word1 = "ab", word2 = "pqrs"
 * Output: "apbqrs"
 *
 * 💡 Key Insight:
 * - Simulate merging character by character.
 * - Append remaining suffix once one word is exhausted.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------
 * ✅ Step 1: Initialize result string and two pointers.
 * ✅ Step 2: While both strings have characters, alternate adding them.
 * ✅ Step 3: Append leftover part from either string.
 *
 * 🚨 Edge Cases:
 * - One string is empty → return the other.
 *
 * ⏱️ Time Complexity: O(n + m)
 * 🧠 Space Complexity: O(n + m)
 */

string MergeAlternately1768(const string& word1, const string& word2) {
    string result;
    int i = 0, j = 0;

    while (i < word1.size() && j < word2.size()) {
        result += word1[i++];
        result += word2[j++];
    }

    // Append remaining characters
    result += word1.substr(i);
    result += word2.substr(j);

    return result;
}

/**
 * Problem 137: Capacity To Ship Packages Within D Days (LC 1011)
 * ---------------------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `weights` of packages and an integer `days`.
 * Your goal is to ship all the packages within `days` days.
 * You must ship the packages in order, and the ship has a weight limit (capacity).
 * Return the **minimum ship capacity** to ship all packages in `days`.
 *
 * 🔍 Example:
 * Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
 * Output: 15
 * Explanation: Minimum capacity to ship in 5 days is 15.
 *
 * 💡 Key Insight:
 * - Binary search over capacity range: [max(weights), sum(weights)].
 * - For each capacity guess, simulate how many days it would take.
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------------
 * ✅ Step 1: Set binary search range: left = max(weights), right = sum(weights).
 * ✅ Step 2: For each mid capacity, simulate shipping day count.
 * ✅ Step 3: Narrow the range to find the minimum feasible capacity.
 *
 * 🚨 Edge Cases:
 * - days = weights.size() → need at least max(weights)
 * - days = 1 → need full sum
 *
 * ⏱️ Time Complexity: O(n * log(sum - max))
 * 🧠 Space Complexity: O(1)
 */

bool CanShipInDays(const vector<int>& weights, int capacity, int days) {
    int current = 0, required_days = 1;

    for (int weight : weights) {
        if (current + weight > capacity) {
            required_days++;
            current = 0;
        }
        current += weight;
    }

    return required_days <= days;
}

int ShipWithinDays1011(const vector<int>& weights, int days) {
    int left = *max_element(weights.begin(), weights.end());
    int right = accumulate(weights.begin(), weights.end(), 0);
    int result = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (CanShipInDays(weights, mid, days)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

/**
 * Problem 138: Text Justification (LC 68)
 * ------------------------------------------------------------------------
 * 🧠 Description:
 * Given an array of words and a maxWidth, format the text such that each line
 * has exactly maxWidth characters and is fully (left and right) justified.
 *
 * You should pack your words in a greedy approach (i.e., as many as fit).
 * - Use spaces to fill lines.
 * - Last line should be **left-justified**, no extra space between words.
 * - Lines with one word are also left-justified.
 *
 * 🔍 Example:
 * Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16  
 * Output:
 * [
 *   "This    is    an",
 *   "example  of text",
 *   "justification.  "
 * ]
 *
 * 💡 Key Insight:
 * - Build lines greedily: keep adding words until adding one more would exceed maxWidth.
 * - For each line (except the last), evenly distribute spaces.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------
 * ✅ Step 1: Group words into lines with ≤ maxWidth characters.
 * ✅ Step 2: For each line:
 *     - If it's the last line or has one word → left-justify.
 *     - Else → distribute extra spaces as evenly as possible.
 * ✅ Step 3: Build and store each line with proper padding.
 *
 * 🚨 Edge Cases:
 * - Single word in a line → pad spaces to the end.
 * - Last line → always left-justified.
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (excluding output)
 */

string BuildLine(const vector<string>& words, int start, int end, int maxWidth, bool is_last) {
    int word_count = end - start + 1;
    int total_chars = 0;
    for (int i = start; i <= end; ++i) {
        total_chars += words[i].size();
    }

    int total_spaces = maxWidth - total_chars;
    string line;

    if (is_last || word_count == 1) {
        // Left-justified
        for (int i = start; i <= end; ++i) {
            line += words[i];
            if (i != end) line += ' ';
        }
        line += string(maxWidth - line.size(), ' ');
    } else {
        int space_between = total_spaces / (word_count - 1);
        int extra_spaces = total_spaces % (word_count - 1);

        for (int i = start; i < end; ++i) {
            line += words[i];
            line += string(space_between + (i - start < extra_spaces ? 1 : 0), ' ');
        }
        line += words[end];  // last word, no trailing space
    }

    return line;
}

vector<string> FullJustify68(vector<string>& words, int maxWidth) {
    vector<string> result;
    int n = words.size();
    int start = 0;

    while (start < n) {
        int end = start;
        int line_len = words[end].size();

        // Expand the line greedily
        while (end + 1 < n && line_len + 1 + words[end + 1].size() <= maxWidth) {
            ++end;
            line_len += 1 + words[end].size();
        }

        bool is_last = (end == n - 1);
        result.push_back(BuildLine(words, start, end, maxWidth, is_last));
        start = end + 1;
    }

    return result;
}

/**
 * Problem 139: Consecutive Characters (LC 1446)
 * ----------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the length of the longest substring
 * with the same character repeated consecutively.
 *
 * 🔍 Example:
 * Input: s = "leetcode"
 * Output: 2
 * Explanation: The longest run is "ee"
 *
 * Input: s = "abbcccddddeeeeedcba"
 * Output: 5
 * Explanation: The longest run is "eeeee"
 *
 * 💡 Key Insight:
 * - Traverse the string, keep a counter of current streak.
 * - Update max length whenever a character changes.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------
 * ✅ Step 1: Initialize max_len = 0, curr_len = 1.
 * ✅ Step 2: Traverse from second character to end:
 *     - If same as previous → increment curr_len.
 *     - Else → update max_len, reset curr_len to 1.
 * ✅ Step 3: After loop, compare max_len with last streak.
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - All same characters → return s.length()
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

int MaxPower1446(const string& s) {
    if (s.empty()) return 0;

    int max_len = 1;
    int curr_len = 1;

    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            curr_len++;
        } else {
            max_len = max(max_len, curr_len);
            curr_len = 1;
        }
    }

    return max(max_len, curr_len);
}

/**
 * Problem 140: Finding 3-Digit Even Numbers (LC 2094)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `digits`, return all **unique** 3-digit even numbers
 * that can be formed using the digits in any order **without reuse**.
 *
 * 🔍 Example:
 * Input: digits = [2,1,3,0]
 * Output: [102,120,130,132,210,230,302,310,312,320]
 *
 * Input: digits = [2,2,8,8,2]
 * Output: [222,228,282,288,822,828,882]
 *
 * 💡 Key Insight:
 * - Brute-force all combinations of 3 digits (i ≠ j ≠ k), check:
 *   - No leading 0
 *   - Last digit is even
 * - Use a set or array to track seen results
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------------
 * ✅ Step 1: Try all permutations of 3 digits (i, j, k).
 * ✅ Step 2: Skip if i == j or j == k or i == k (or use visited flag).
 * ✅ Step 3: Check leading digit ≠ 0 and num % 2 == 0.
 * ✅ Step 4: Use boolean array to track valid numbers from 100 to 998.
 *
 * 🚨 Edge Cases:
 * - Leading digit = 0 → skip
 * - Digits too small to form 3-digit → return empty list
 *
 * ⏱️ Time Complexity: O(n^3)
 * 🧠 Space Complexity: O(1) (bounded to 900 possibilities)
 */

vector<int> FindEvenNumbers2094(vector<int>& digits) {
    vector<bool> valid(1000, false);

    int n = digits.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;

                int d1 = digits[i], d2 = digits[j], d3 = digits[k];
                if (d1 == 0) continue;       // no leading zero
                if (d3 % 2 != 0) continue;   // must be even

                int number = d1 * 100 + d2 * 10 + d3;
                valid[number] = true;
            }
        }
    }

    vector<int> result;
    for (int i = 100; i <= 998; i += 2) {
        if (valid[i]) result.push_back(i);
    }

    return result;
}

/**
 * Problem 141: All Paths From Source to Target (LC 797)
 * ----------------------------------------------------------------------
 * 🧠 Description:
 * Given a **directed acyclic graph (DAG)** of `n` nodes from `0` to `n-1`,
 * represented as an adjacency list `graph`, return **all possible paths**
 * from node `0` to node `n - 1`.
 *
 * 🔍 Example:
 * Input: graph = [[1,2],[3],[3],[]]
 * Output: [[0,1,3],[0,2,3]]
 *
 * 💡 Key Insight:
 * - This is a classical DFS traversal problem from node 0 to n-1.
 * - Use backtracking to explore all possible paths.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------
 * ✅ Step 1: Start DFS from node 0 with an empty path.
 * ✅ Step 2: At each node, add to path and recurse on its neighbors.
 * ✅ Step 3: If current node is the target (n-1), add path to result.
 * ✅ Step 4: Backtrack to explore other branches.
 *
 * 🚨 Edge Cases:
 * - Only one node (n=1): return [[0]]
 * - No outgoing edges from start: return empty list
 *
 * ⏱️ Time Complexity: O(2^n * n) (worst-case exponential path combinations)
 * 🧠 Space Complexity: O(n) recursion depth + output list
 */

void DfsAllPaths797(const vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& result) {
    path.push_back(node);

    if (node == graph.size() - 1) {
        result.push_back(path);
    } else {
        for (int neighbor : graph[node]) {
            DfsAllPaths797(graph, neighbor, path, result);
        }
    }

    path.pop_back();  // backtrack
}

vector<vector<int>> AllPathsSourceTarget797(const vector<vector<int>>& graph) {
    vector<vector<int>> result;
    vector<int> path;
    DfsAllPaths797(graph, 0, path, result);
    return result;
}

/**
 * Problem 142: Minimum Depth of Binary Tree (LC 111)
 * ------------------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return its **minimum depth**.
 * The minimum depth is the number of nodes along the shortest path from the root
 * node down to the nearest **leaf node**.
 *
 * 🔍 Example:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 2
 * Explanation: The shortest path is 3 → 9 or 3 → 20
 *
 * 💡 Key Insight:
 * - A **leaf** is a node with no left or right child.
 * - Must handle cases where one child is null (don’t take min of 0).
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------
 * ✅ Step 1: Recursively compute minDepth for left and right subtrees.
 * ✅ Step 2: If either child is null, do not consider its depth in min().
 * ✅ Step 3: Base case — null node returns depth 0.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return 0
 * - Only root node → return 1
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h) recursion depth (worst-case O(n))
 */

int MinDepth111(TreeNode* root) {
    if (!root) return 0;

    if (!root->left) return 1 + MinDepth111(root->right);
    if (!root->right) return 1 + MinDepth111(root->left);

    return 1 + min(MinDepth111(root->left), MinDepth111(root->right));
}

/**
 * Problem 143: Sliding Window Maximum (LC 239)
 * -----------------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `nums` and an integer `k`.
 * Return the maximum value in every sliding window of size `k`.
 *
 * 🔍 Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 *
 * 💡 Key Insight:
 * - Use a deque (double-ended queue) to maintain a **monotonically decreasing**
 *   window of indices — front always stores the max.
 * - Remove out-of-window indices and elements smaller than current.
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------------
 * ✅ Step 1: Use deque to store indices of useful elements (monotonic decreasing).
 * ✅ Step 2: For each index `i`, pop back all indices whose nums[] is smaller.
 * ✅ Step 3: Remove front if it's out of the window.
 * ✅ Step 4: Add nums[deque.front()] to result after reaching valid window.
 *
 * 🚨 Edge Cases:
 * - k = 1 → return original array
 * - nums.size() < k → return empty
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(k)
 */

vector<int> MaxSlidingWindow239(const vector<int>& nums, int k) {
    deque<int> dq;  // stores indices
    vector<int> result;

    for (int i = 0; i < nums.size(); ++i) {
        // Remove indices out of current window
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Maintain decreasing order in deque
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Append result when window is fully formed
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

/**
 * Problem 144: Longest Palindromic Substring (LC 5)
 * --------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the longest palindromic substring in `s`.
 *
 * 🔍 Example:
 * Input: s = "babad"
 * Output: "bab" or "aba"
 *
 * 🎯 Key Insight:
 * Expand around every center (both odd and even) to find longest palindrome.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Expand from center `l` and `r`, extend while s[l] == s[r]
 *
 * ✅ Base Case Initialization:
 * Check all i and i+1 as potential centers
 *
 * ✅ Transition:
 * For each center, expand and compare with longest so far
 *
 * ✅ Iteration Order:
 * i = 0 to n - 1
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - All characters same → whole string is result
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(1)
 */
string Expand(string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
        l--; r++;
    }
    return s.substr(l + 1, r - l - 1);
}

string LongestPalindrome(string s) {
    string res;
    for (int i = 0; i < s.size(); ++i) {
        string odd = Expand(s, i, i);
        string even = Expand(s, i, i + 1);
        if (odd.size() > res.size()) res = odd;
        if (even.size() > res.size()) res = even;
    }
    return res;
}

/**
 * Problem 145: Course Schedule II (LC 210)
 * -----------------------------------------
 * 🧠 Description:
 * Same as Course Schedule I, but return the order in which you should take the courses.
 *
 * 🔍 Example:
 * Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 *
 * 🎯 Key Insight:
 * Use topological sort to determine valid course order.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - graph[i] = list of courses dependent on i
 * - indegree[i] = number of prerequisites for course i
 *
 * ✅ Transition:
 * BFS to reduce indegree and build result
 *
 * ✅ Final:
 * If all nodes processed → return result; else → return empty
 *
 * 🚨 Edge Cases:
 * - No prerequisites → return [0..n-1]
 * - Cycle → return empty vector
 *
 * ⏱️ Time Complexity: O(V + E)
 * 🧠 Space Complexity: O(V + E)
 */
vector<int> FindOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> result;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        result.push_back(curr);

        for (int neighbor : graph[curr]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return result.size() == numCourses ? result : vector<int>();
}

/**
 * Problem 146: Find the Closest Palindrome (LC 564)
 * --------------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `n` representing an integer, return the closest integer
 * (as a string) that is a palindrome and **not equal** to `n` itself.
 * If there is a tie, return the smaller one.
 *
 * 🔍 Example:
 * Input: n = "123"
 * Output: "121"
 *
 * Input: n = "1"
 * Output: "0"
 *
 * 💡 Key Insight:
 * - Any closest palindrome must be one of:
 *   - The mirrored version of the first half
 *   - The mirrored version of first half + 1
 *   - The mirrored version of first half - 1
 * - Also handle edge cases like 10...01 → 9...9 or 100...001 → 99...99
 *
 * ✅ Strategy:
 * --------------------------------------------------------------------------
 * ✅ Step 1: Create three candidate palindromes by mirroring:
 *     - original prefix
 *     - prefix + 1
 *     - prefix - 1
 * ✅ Step 2: Add edge case candidates: "9...9", "1...1" style
 * ✅ Step 3: Exclude `n` itself and choose the closest based on absolute diff
 *     → In tie, return lex smaller
 *
 * 🚨 Edge Cases:
 * - Single digit input like "1" → return "0"
 * - All 9s → return one less digit, all 9s
 * - 100...01 → return 999...99
 *
 * ⏱️ Time Complexity: O(len(n))
 * 🧠 Space Complexity: O(1) (excluding result)
 */

string Mirror(const string& half, bool even_len) {
    string mirrored = half;
    int i = even_len ? half.size() - 1 : half.size() - 2;
    while (i >= 0) mirrored += half[i--];
    return mirrored;
}

string NearestPalindromic564(const string& n) {
    int len = n.size();
    long long self = stoll(n);
    set<long long> candidates;

    // Edge cases
    candidates.insert((long long)pow(10, len - 1) - 1);           // 99...9
    candidates.insert((long long)pow(10, len) + 1);               // 100...001

    // Middle prefix
    long long prefix = stoll(n.substr(0, (len + 1) / 2));
    for (int delta : {-1, 0, 1}) {
        string half = to_string(prefix + delta);
        string pal = Mirror(half, len % 2 == 0);
        candidates.insert(stoll(pal));
    }

    candidates.erase(self);  // must not equal itself

    long long min_diff = LLONG_MAX, ans = -1;
    for (long long cand : candidates) {
        long long diff = abs(cand - self);
        if (diff < min_diff || (diff == min_diff && cand < ans)) {
            min_diff = diff;
            ans = cand;
        }
    }

    return to_string(ans);
}

/**
 * Problem 147: 3Sum (LC 15)
 * ------------------------
 * 🧠 Description:
 * Given an array `nums`, return all unique triplets [a,b,c] such that a+b+c = 0.
 *
 * 🔍 Example:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2], [-1,0,1]]
 *
 * 🎯 Key Insight:
 * Sort + two pointers avoids duplicate and gives O(n^2) solution.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Sort input, fix one number `a`, then use two pointers to find pairs summing to -a.
 *
 * ✅ Base Case Initialization:
 * sort(nums), result = []
 *
 * ✅ Transition:
 * For each i:
 *   - Skip duplicates
 *   - Two pointers j, k = i+1, n-1
 *   - if sum == 0: add, move both pointers (skip duplicates)
 *
 * ✅ Iteration Order:
 * i = 0 to n-3, inner j/k moves inward
 *
 * 🚨 Edge Cases:
 * - Less than 3 elements → return empty
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(1) extra (excluding output)
 */
vector<vector<int>> ThreeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates
        int j = i + 1, k = n - 1;

        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                res.push_back({nums[i], nums[j], nums[k]});
                while (j < k && nums[j] == nums[j+1]) j++;
                while (j < k && nums[k] == nums[k-1]) k--;
                j++; k--;
            } else if (sum < 0) {
                j++;
            } else {
                k--;
            }
        }
    }

    return res;
}

/**
 * Problem 148: Binary Tree Maximum Path Sum (LC 124)
 * ---------------------------------------------------
 * 🧠 Description:
 * A path in a binary tree is any sequence of nodes where each pair is connected.
 * Return the maximum sum of any path in the tree.
 *
 * 🔍 Example:
 * Input: [-10,9,20,null,null,15,7]
 * Output: 42
 *
 * 🎯 Key Insight:
 * At each node, max gain = node.val + max(left_gain, 0) + max(right_gain, 0)
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * gain(node) = max path sum from this node to any leaf or null
 *
 * ✅ Base Case Initialization:
 * Null node → return 0
 *
 * ✅ Transition:
 * Update global_max = max(global_max, node.val + left_gain + right_gain)
 *
 * ✅ Iteration Order:
 * Post-order traversal
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
int MaxPathSumHelper(TreeNode* node, int& global_max) {
    if (!node) return 0;

    int left = max(0, MaxPathSumHelper(node->left, global_max));
    int right = max(0, MaxPathSumHelper(node->right, global_max));

    global_max = max(global_max, node->val + left + right);
    return node->val + max(left, right);
}

int MaxPathSum(TreeNode* root) {
    int global_max = INT_MIN;
    MaxPathSumHelper(root, global_max);
    return global_max;
}

/**
 * Problem 149: Word Break (LC 139)
 * ---------------------------------
 * 🧠 Description:
 * Given a string s and a dictionary of words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
 *
 * 🔍 Example:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 *
 * 🎯 Key Insight:
 * Use dynamic programming to track valid segmentations ending at each index.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = true if s[0..i-1] can be segmented
 *
 * ✅ Base Case Initialization:
 * dp[0] = true (empty string)
 *
 * ✅ Transition:
 * For j in [0, i): if dp[j] && s[j..i-1] in wordDict → dp[i] = true
 *
 * ✅ Iteration Order:
 * i from 1 to s.length()
 *
 * 🚨 Edge Cases:
 * - Empty string → true
 * - No match in wordDict → false
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(n)
 */
bool WordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

/**
 * Problem 150: Rotting Oranges (LC 994)
 * ---------------------------------------------------------------------------
 * 🧠 Description:
 * You are given a 2D grid where:
 * - 0 = empty cell
 * - 1 = fresh orange
 * - 2 = rotten orange
 *
 * Every minute, any fresh orange adjacent (4-directionally) to a rotten orange becomes rotten.
 * Return the minimum number of minutes to rot all fresh oranges.
 * If impossible, return -1.
 *
 * 🔍 Example:
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * 💡 Key Insight:
 * - Use BFS to simulate rot spreading level-by-level (minute-by-minute).
 * - Count total fresh oranges and track time until all are rotten.
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------------
 * ✅ Step 1: Add all rotten oranges to BFS queue; count fresh ones.
 * ✅ Step 2: For each level (minute), rot adjacent fresh oranges.
 * ✅ Step 3: Keep track of minutes and remaining fresh count.
 * ✅ Step 4: If fresh count == 0 → return time, else → return -1.
 *
 * 🚨 Edge Cases:
 * - No fresh oranges → return 0
 * - No rotten oranges → return -1 if fresh exists
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(m * n)
 */

int OrangesRotting994(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;

    // Initialize BFS queue with all rotten oranges
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 2) {
                q.emplace(i, j);
            } else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }

    if (fresh == 0) return 0;

    vector<pair<int, int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};
    int minutes = 0;

    while (!q.empty()) {
        int size = q.size();
        bool rotted_this_round = false;

        for (int i = 0; i < size; ++i) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    fresh--;
                    q.emplace(nx, ny);
                    rotted_this_round = true;
                }
            }
        }

        if (rotted_this_round) minutes++;
    }

    return fresh == 0 ? minutes : -1;
}

/**
 * Problem 151: Max Points on a Line (LC 149)
 * ---------------------------------------------------------------------------
 * 🧠 Description:
 * Given an array of `points` where `points[i] = [xi, yi]`, return the maximum number
 * of points that lie on the same straight line.
 *
 * 🔍 Example:
 * Input: points = [[1,1],[2,2],[3,3]]
 * Output: 3
 *
 * 💡 Key Insight:
 * - Two points define a line.
 * - Normalize slope using (dy / dx) as reduced fraction to avoid floating-point error.
 * - Count all slopes from a given anchor point.
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------------
 * ✅ Step 1: Iterate through each point as anchor.
 * ✅ Step 2: For each other point, compute slope relative to anchor.
 * ✅ Step 3: Normalize slope with GCD to avoid precision issues.
 * ✅ Step 4: Use hashmap to count how many points share the same slope.
 *
 * 🚨 Edge Cases:
 * - Duplicate points → count separately
 * - Vertical lines → dx = 0, handle as special slope
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(n)
 */

int Gcd(int a, int b) {
    return b == 0 ? a : Gcd(b, a % b);
}

int MaxPoints149(vector<vector<int>>& points) {
    int n = points.size();
    if (n <= 2) return n;

    int max_points = 0;

    for (int i = 0; i < n; ++i) {
        unordered_map<string, int> slope_count;
        int duplicates = 1;  // count itself
        int curr_max = 0;

        for (int j = i + 1; j < n; ++j) {
            int dx = points[j][0] - points[i][0];
            int dy = points[j][1] - points[i][1];

            if (dx == 0 && dy == 0) {
                duplicates++;
                continue;
            }

            int g = Gcd(dx, dy);
            dx /= g;
            dy /= g;

            // Normalize sign: ensure consistent representation
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }

            string slope = to_string(dy) + "/" + to_string(dx);
            slope_count[slope]++;
            curr_max = max(curr_max, slope_count[slope]);
        }

        max_points = max(max_points, curr_max + duplicates);
    }

    return max_points;
}

/**
 * Problem 152: Search in Rotated Sorted Array (LC 33)
 * ---------------------------------------------------
 * 🧠 Description:
 * Given a rotated sorted array and a target, return its index if found; else -1.
 *
 * 🔍 Example:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * 🎯 Key Insight:
 * Use binary search with logic to identify which half is sorted.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * left = 0, right = nums.size() - 1
 *
 * ✅ Transition:
 * At each step:
 *   - Determine if left to mid is sorted or mid to right is sorted
 *   - Narrow search to correct side based on target position
 *
 * ✅ Iteration Order:
 * Standard binary search loop
 *
 * 🚨 Edge Cases:
 * - Duplicates not allowed in this version
 * - Empty array → return -1
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
int Search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) return mid;

        // Left half sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half sorted
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

/**
 * Problem 153: Plus One (LC 66)
 * ---------------------------------------------------------------------
 * 🧠 Description:
 * Given a non-empty array of decimal digits representing a non-negative integer,
 * increment the integer by one and return the resulting array of digits.
 *
 * Digits are stored such that the most significant digit is at the head of the list.
 *
 * 🔍 Example:
 * Input: digits = [1,2,3]
 * Output: [1,2,4]
 *
 * Input: digits = [9,9,9]
 * Output: [1,0,0,0]
 *
 * 💡 Key Insight:
 * - Simulate the addition from right to left.
 * - If there's a carry at the most significant digit, prepend 1.
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------
 * ✅ Step 1: Traverse from the last digit to the front.
 * ✅ Step 2: If digit < 9 → increment and return.
 * ✅ Step 3: Else set digit to 0 and carry over.
 * ✅ Step 4: If loop completes → all were 9s, insert 1 at the front.
 *
 * 🚨 Edge Cases:
 * - All digits are 9 → new digit added at front
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (in-place, except result growth)
 */

vector<int> PlusOne66(vector<int>& digits) {
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }

    // If all were 9s
    digits.insert(digits.begin(), 1);
    return digits;
}

/**
 * Problem 154: Sort Colors (LC 75)
 * ---------------------------------------------------------------------
 * 🧠 Description:
 * Given an array `nums` with `n` objects colored red (0), white (1), or blue (2),
 * sort them **in-place** so that objects of the same color are adjacent,
 * with the colors in the order: 0 → 1 → 2.
 *
 * You must solve this without using the library's sort function.
 *
 * 🔍 Example:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 *
 * 💡 Key Insight:
 * - Use **three pointers**:
 *   - `low` to track end of 0s
 *   - `mid` to iterate through array
 *   - `high` to track start of 2s
 * - Swap and move pointers based on `nums[mid]`
 *
 * ✅ Strategy:
 * ---------------------------------------------------------------------
 * ✅ Step 1: Initialize low = 0, mid = 0, high = n - 1.
 * ✅ Step 2: While mid <= high:
 *     - If nums[mid] == 0 → swap with low and increment both.
 *     - If nums[mid] == 1 → move mid.
 *     - If nums[mid] == 2 → swap with high and decrement high only.
 *
 * 🚨 Edge Cases:
 * - Already sorted → no swaps
 * - All same value → handle correctly
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

void SortColors75(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low++], nums[mid++]);
        } else if (nums[mid] == 1) {
            mid++;
        } else {  // nums[mid] == 2
            swap(nums[mid], nums[high--]);
        }
    }
}

/**
 * Problem 155: Roman to Integer (LC 13)
 * -----------------------------------
 * 🧠 Description:
 * Convert a Roman numeral string to an integer.
 *
 * 🔍 Example:
 * Input: "MCMXCIV"
 * Output: 1994
 *
 * 🎯 Key Insight:
 * Subtract if the current value is less than the next.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use a hashmap for Roman numeral values.
 *
 * ✅ Base Case Initialization:
 * result = 0
 *
 * ✅ Transition:
 * - Iterate s[i], if value[s[i]] < value[s[i+1]] ⇒ subtract
 *   else ⇒ add
 *
 * ✅ Iteration Order:
 * Left to right
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int RomanToInt(string s) {
    unordered_map<char, int> value = {
        {'I',1}, {'V',5}, {'X',10}, {'L',50},
        {'C',100}, {'D',500}, {'M',1000}
    };

    int result = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 < s.size() && value[s[i]] < value[s[i+1]])
            result -= value[s[i]];
        else
            result += value[s[i]];
    }
    return result;
}

/**
 * Problem 156: Maximum Sum BST in Binary Tree (LC 1373)
 * ------------------------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return the **maximum sum** of all keys of any subtree which is a **Binary Search Tree (BST)**.
 * A subtree of a node is a tree consisting of that node and all its descendants.
 * A BST is defined as: for every node, left < root < right.
 *
 * 🔍 Example:
 * Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
 * Output: 20
 * Explanation: Maximum-sum BST subtree is:
 *        3
 *       / \
 *      2   5
 *         / \
 *        4   6
 *
 * 💡 Key Insight:
 * - Use **post-order traversal** to check if a subtree is BST and compute sum.
 * - For each node, return 5 values:
 *     - isBST
 *     - min value in subtree
 *     - max value in subtree
 *     - total sum of subtree
 *     - max sum so far
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------------
 * ✅ Step 1: Traverse tree bottom-up using DFS.
 * ✅ Step 2: At each node, get left/right subtree info and check BST condition.
 * ✅ Step 3: If valid BST → compute sum and update global max.
 * ✅ Step 4: If not BST → return isBST=false to upper level.
 *
 * 🚨 Edge Cases:
 * - Tree with only one node → return that node value
 * - No valid BST subtree → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h) recursion stack
 */

struct SubtreeInfo {
    bool isBST;
    int minVal;
    int maxVal;
    int sum;
};

int _maxSumBST = 0;

SubtreeInfo DfsMaxSumBST(TreeNode* node) {
    if (!node) {
        return {true, INT_MAX, INT_MIN, 0};
    }

    SubtreeInfo left = DfsMaxSumBST(node->left);
    SubtreeInfo right = DfsMaxSumBST(node->right);

    if (left.isBST && right.isBST && node->val > left.maxVal && node->val < right.minVal) {
        int currSum = node->val + left.sum + right.sum;
        _maxSumBST = max(_maxSumBST, currSum);
        return {true, min(node->val, left.minVal), max(node->val, right.maxVal), currSum};
    }

    return {false, 0, 0, 0};  // invalid BST, values don't matter
}

int MaxSumBST1373(TreeNode* root) {
    _maxSumBST = 0;
    DfsMaxSumBST(root);
    return _maxSumBST;
}

/**
 * Problem 157: Longest Repeating Character Replacement (LC 424)
 * -------------------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s` and an integer `k`, return the length of the longest substring
 * that can be obtained by replacing **at most `k` characters** so that all the characters
 * in the substring are the same.
 *
 * 🔍 Example:
 * Input: s = "ABAB", k = 2
 * Output: 4
 * Explanation: Replace the two 'A's or two 'B's to get "AAAA" or "BBBB".
 *
 * Input: s = "AABABBA", k = 1
 * Output: 4
 * Explanation: Replace one 'A' to get "AABBBBA" → "ABBB" is valid.
 *
 * 💡 Key Insight:
 * - Use a sliding window to track a range where the most frequent character can dominate
 *   after at most `k` replacements.
 * - Track the count of the most frequent character in the window.
 *
 * ✅ Strategy:
 * -------------------------------------------------------------------------
 * ✅ Step 1: Initialize a frequency counter and sliding window pointers.
 * ✅ Step 2: Expand right pointer, update max frequency.
 * ✅ Step 3: If window size - max_freq > k, shrink left.
 * ✅ Step 4: Track max window length throughout.
 *
 * 🚨 Edge Cases:
 * - All same characters → return s.length()
 * - k >= s.length() → entire string can be converted
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (fixed 26 letters)
 */

int CharacterReplacement424(const string& s, int k) {
    vector<int> freq(26, 0);
    int left = 0, max_count = 0, result = 0;

    for (int right = 0; right < s.size(); ++right) {
        freq[s[right] - 'A']++;
        max_count = max(max_count, freq[s[right] - 'A']);

        // If more than k chars need replacement, shrink window
        while ((right - left + 1) - max_count > k) {
            freq[s[left] - 'A']--;
            left++;
        }

        result = max(result, right - left + 1);
    }

    return result;
}

/**
 * Problem 158: Move Zeroes (LC 283)
 * ---------------------------------
 * 🧠 Description:
 * Given an integer array nums, move all 0's to the end of it while maintaining the relative order
 * of the non-zero elements. Do it in-place.
 *
 * 🔍 Example:
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 *
 * 🎯 Key Insight:
 * Use two pointers: one to scan, one to place non-zero elements.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * `left` = index where the next non-zero should go
 *
 * ✅ Base Case Initialization:
 * left = 0
 *
 * ✅ Transition:
 * If nums[i] != 0 → move it to nums[left] and increment left
 *
 * ✅ Final Step:
 * Fill rest of array from `left` with 0's
 *
 * 🚨 Edge Cases:
 * - All zeroes
 * - No zeroes
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
void MoveZeroes(vector<int>& nums) {
    int left = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            nums[left++] = nums[i];
        }
    }

    // Fill remaining space with 0s
    while (left < nums.size()) {
        nums[left++] = 0;
    }
}

/**
 * Problem 159: Painting a Grid With Three Different Colors (LC 1931)
 * ------------------------------------------------------------------------------------
 * 🧠 Description:
 * You are given two integers `m` and `n`, representing an `m x n` grid.
 * Each cell must be painted with one of **three colors**.
 * No two **adjacent** cells (vertically or horizontally) can have the same color.
 * Return the total number of valid colorings **modulo 1e9 + 7**.
 *
 * 🔍 Example:
 * Input: m = 1, n = 1 → Output: 3
 * Input: m = 1, n = 2 → Output: 6
 *
 * 💡 Key Insight:
 * - Use **state compression** to encode one column of m cells as a "pattern".
 * - Two adjacent columns must not have same color in the same row.
 * - Precompute all valid patterns, and compatible pairs.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------------------
 * ✅ Step 1: Generate all valid colorings for a single column of m cells (no adjacent same color).
 * ✅ Step 2: For each pair of column patterns, check compatibility (no vertical conflict).
 * ✅ Step 3: Use DP:
 *     - dp[i][p] = number of ways to paint first i columns ending in pattern p
 * ✅ Step 4: Use previous column's valid patterns to fill current column.
 *
 * 🚨 Edge Cases:
 * - m ≥ 6 → total pattern count explodes → constraints likely limit m ≤ 5
 *
 * ⏱️ Time Complexity: O(n * P^2), where P = number of valid patterns (exponential in m)
 * 🧠 Space Complexity: O(P)
 */

const int MOD = 1e9 + 7;

void GenerateValidPatterns(int m, int row = 0, int depth = 0, vector<int>& path = *(new vector<int>()), vector<vector<int>>& patterns = *(new vector<vector<int>>())) {
    if (depth == m) {
        patterns.push_back(path);
        return;
    }

    for (int color = 0; color < 3; ++color) {
        if (depth == 0 || path.back() != color) {
            path.push_back(color);
            GenerateValidPatterns(m, row, depth + 1, path, patterns);
            path.pop_back();
        }
    }
}

bool AreCompatible(const vector<int>& a, const vector<int>& b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == b[i]) return false;
    }
    return true;
}

int ColorTheGrid1931(int m, int n) {
    vector<vector<int>> patterns;
    GenerateValidPatterns(m, 0, 0, *(new vector<int>()), patterns);
    int P = patterns.size();

    // Map pattern vector to index
    unordered_map<string, int> pattern_index;
    vector<string> encoded_patterns;
    for (int i = 0; i < P; ++i) {
        string key;
        for (int c : patterns[i]) key += to_string(c);
        pattern_index[key] = i;
        encoded_patterns.push_back(key);
    }

    // Precompute compatible pairs
    vector<vector<int>> compatible(P);
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            if (AreCompatible(patterns[i], patterns[j])) {
                compatible[i].push_back(j);
            }
        }
    }

    vector<int> dp(P, 1);  // first column: all valid patterns count as 1

    for (int col = 1; col < n; ++col) {
        vector<int> new_dp(P, 0);
        for (int i = 0; i < P; ++i) {
            for (int prev : compatible[i]) {
                new_dp[i] = (new_dp[i] + dp[prev]) % MOD;
            }
        }
        dp = new_dp;
    }

    int result = 0;
    for (int count : dp) {
        result = (result + count) % MOD;
    }

    return result;
}

/**
 * Problem 160: Check Completeness of a Binary Tree (LC 958)
 * ------------------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return true if it is a **complete binary tree**.
 *
 * A **complete binary tree** is a binary tree where:
 * - Every level is completely filled, except possibly the last level.
 * - The last level has all nodes as far left as possible.
 *
 * 🔍 Example:
 * Input: root = [1,2,3,4,5,6]
 * Output: true
 *
 * Input: root = [1,2,3,4,5,null,7]
 * Output: false
 *
 * 💡 Key Insight:
 * - Use **level-order traversal (BFS)**.
 * - Once a `null` node is seen, all following nodes **must also be null**.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------
 * ✅ Step 1: Perform BFS using a queue.
 * ✅ Step 2: Push left and right children (even if null).
 * ✅ Step 3: Once a null node is encountered, set a flag.
 * ✅ Step 4: If any non-null node appears after a null → tree is not complete.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return true
 * - Single node → return true
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */

bool IsCompleteTree958(TreeNode* root) {
    if (!root) return true;

    queue<TreeNode*> q;
    q.push(root);
    bool null_seen = false;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (!node) {
            null_seen = true;
        } else {
            if (null_seen) return false;  // Found a node after a null
            q.push(node->left);
            q.push(node->right);
        }
    }

    return true;
}

/**
 * Problem 161: Koko Eating Bananas (LC 875)
 * -----------------------------------------------------------------------
 * 🧠 Description:
 * Koko loves to eat bananas. You are given an array `piles`, where piles[i]
 * represents the number of bananas in the ith pile. She can eat at most `k` bananas per hour.
 * Given an integer `h`, return the **minimum integer k** such that she can eat
 * all the bananas within `h` hours.
 *
 * 🔍 Example:
 * Input: piles = [3,6,7,11], h = 8
 * Output: 4
 *
 * 💡 Key Insight:
 * - The more bananas per hour (k), the fewer hours needed.
 * - Use **binary search** over k ∈ [1, max(piles)] to find the minimum feasible k.
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------------
 * ✅ Step 1: Binary search k from 1 to max(piles).
 * ✅ Step 2: For each mid = candidate speed, calculate required hours.
 * ✅ Step 3: If total hours ≤ h → try smaller k; else try bigger k.
 *
 * 🚨 Edge Cases:
 * - piles.size() == h → must eat 1 pile per hour, return max(piles)
 * - piles = [30], h = 10 → return 3
 *
 * ⏱️ Time Complexity: O(n * log(max(piles)))
 * 🧠 Space Complexity: O(1)
 */

int GetHoursAtSpeed(const vector<int>& piles, int speed) {
    int hours = 0;
    for (int bananas : piles) {
        hours += (bananas + speed - 1) / speed;  // ceil(bananas / speed)
    }
    return hours;
}

int MinEatingSpeed875(const vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end());
    int result = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int hours = GetHoursAtSpeed(piles, mid);

        if (hours <= h) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

/**
 * Problem 162: Path Sum II (LC 113)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree and an integer `targetSum`, return all root-to-leaf
 * paths where each path's sum equals `targetSum`. A leaf is a node with no children.
 *
 * 🔍 Example:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 *
 * 💡 Key Insight:
 * - Use DFS + backtracking to explore all root-to-leaf paths.
 * - Only record a path when reaching a leaf and the remaining sum is 0.
 *
 * ✅ Strategy:
 * ----------------------------------------------------------------------------
 * ✅ Step 1: Perform DFS traversal from root.
 * ✅ Step 2: At each node, add value to path and subtract from remaining sum.
 * ✅ Step 3: When reaching a leaf, check if path sum equals target.
 * ✅ Step 4: Backtrack after exploring each subtree.
 *
 * 🚨 Edge Cases:
 * - Empty tree → return empty list
 * - Single-node tree matching target → return [node.val]
 *
 * ⏱️ Time Complexity: O(n^2) worst case (n paths × path length)
 * 🧠 Space Complexity: O(h) recursion stack + result
 */

void DfsPathSum113(TreeNode* node, int target, vector<int>& path, vector<vector<int>>& result) {
    if (!node) return;

    path.push_back(node->val);
    target -= node->val;

    if (!node->left && !node->right && target == 0) {
        result.push_back(path);  // found a valid path
    }

    DfsPathSum113(node->left, target, path, result);
    DfsPathSum113(node->right, target, path, result);

    path.pop_back();  // backtrack
}

vector<vector<int>> PathSum113(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    DfsPathSum113(root, targetSum, path, result);
    return result;
}

/**
 * Problem 163: Cutting Ribbons (LC 1891)
 * -----------------------------------------------------------------------------
 * 🧠 Description:
 * You are given an array `ribbons`, where ribbons[i] represents the length of
 * a ribbon. You need to **cut these ribbons** into pieces of integer length.
 * Return the **maximum length** you can make `k` or more ribbons of **equal length**.
 *
 * 🔍 Example:
 * Input: ribbons = [9,7,5], k = 3
 * Output: 5
 * Explanation: Cut ribbons into [5,2], [5,2], [5] → 3 ribbons of length 5
 *
 * 💡 Key Insight:
 * - The problem is to **maximize the length** of ribbons such that we get at least `k` pieces.
 * - Use **binary search** over possible lengths from 1 to max(ribbons).
 *
 * ✅ Strategy:
 * -----------------------------------------------------------------------------
 * ✅ Step 1: Define search range: [1, max(ribbons)]
 * ✅ Step 2: For each mid value, simulate cutting and count how many pieces.
 * ✅ Step 3: If count >= k → mid is a valid answer, search right for longer.
 * ✅ Step 4: Else, search left.
 *
 * 🚨 Edge Cases:
 * - All ribbons too short → return 0
 *
 * ⏱️ Time Complexity: O(n * log(max_length))
 * 🧠 Space Complexity: O(1)
 */

bool CanCutAtLength(const vector<int>& ribbons, int length, int k) {
    int count = 0;
    for (int r : ribbons) {
        count += r / length;
    }
    return count >= k;
}

int MaxLength1891(const vector<int>& ribbons, int k) {
    int left = 1, right = *max_element(ribbons.begin(), ribbons.end());
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (CanCutAtLength(ribbons, mid, k)) {
            result = mid;       // try longer
            left = mid + 1;
        } else {
            right = mid - 1;    // try shorter
        }
    }

    return result;
}

/**
 * Problem 164: Intersection of Two Arrays (LC 349)
 * ------------------------------------------------
 * 🧠 Description:
 * Given two integer arrays `nums1` and `nums2`, return their intersection.
 * Each element in the result must be unique, and the result can be in any order.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 *
 * 🎯 Key Insight:
 * Use sets to track and find common elements efficiently.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - seen = set of nums1 elements
 * - result = set of common elements
 *
 * ✅ Transition:
 * - Iterate nums2, if element in seen → insert to result
 *
 * ✅ Iteration Order:
 * Loop over both arrays
 *
 * 🚨 Edge Cases:
 * - One or both arrays are empty → return empty vector
 * - All duplicates → result still has unique elements
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(m + n)
 */
vector<int> Intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> result;

    for (int num : nums2) {
        if (set1.count(num)) result.insert(num);
    }

    return vector<int>(result.begin(), result.end());
}

/**
 * Problem 165: Make Three Strings Equal (LC 3545)
 * ------------------------------------------------------------------------------
 * 🧠 Description:
 * You are given three strings `s1`, `s2`, and `s3`. In one operation, you can:
 * - Choose any of the strings and delete the **last character**.
 * Return the **length** of the longest common prefix (from the start) that can
 * remain **after any number of such operations**.
 *
 * 🔍 Example:
 * Input: s1 = "abc", s2 = "abcdef", s3 = "ab"
 * Output: 2
 * Explanation: The maximum prefix all three can be reduced to is "ab".
 *
 * 💡 Key Insight:
 * - You can only **shorten strings from the end**, so the final prefix must be
 *   the common prefix of all three strings from the **start**.
 *
 * ✅ Strategy:
 * ------------------------------------------------------------------------------
 * ✅ Step 1: Initialize index `i = 0`.
 * ✅ Step 2: Compare s1[i], s2[i], s3[i] while all are equal and within bounds.
 * ✅ Step 3: Return the final index — longest common prefix length.
 *
 * 🚨 Edge Cases:
 * - Any string is empty → return 0
 * - No common prefix at all → return 0
 *
 * ⏱️ Time Complexity: O(min(len1, len2, len3))
 * 🧠 Space Complexity: O(1)
 */

int LongestCommonPrefix3545(const string& s1, const string& s2, const string& s3) {
    int i = 0;
    while (i < s1.size() && i < s2.size() && i < s3.size()) {
        if (s1[i] == s2[i] && s2[i] == s3[i]) {
            i++;
        } else {
            break;
        }
    }
    return i;
}
