#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

 /**
 * Problem 1: Contains Duplicate III (LC 220)
 * Description:
 * You are given an integer array nums and two integers k and t. Return true if there are two distinct indices i and j
 * in the array such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
 *
 * Example:
 * Input: nums = [1,2,3,1], k = 3, t = 0
 * Output: true
 */
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long> window;
    for (size_t i = 0; i < nums.size(); ++i) {
        auto pos = window.lower_bound((long)nums[i] - t);
        if (pos != window.end() && *pos <= (long)nums[i] + t) {
            return true;
        }
        window.insert(nums[i]);
        if (window.size() > static_cast<size_t>(k)) {
            window.erase(nums[i - k]);
        }
    }
    return false;
}

/**
 * Problem 2: Two Sum using map (LC 1)
 * Description:
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 *
 * Example:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 */
vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> numMap;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], static_cast<int>(i)};
        }
        numMap[nums[i]] = i;
    }
    return {};
}

/**
 * Problem 3: Find All Numbers Disappeared in an Array using set (LC 448)
 * Description:
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers
 * in the range [1, n] that do not appear in nums.
 *
 * Example:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [5,6]
 */
vector<int> findDisappearedNumbers(vector<int>& nums) {
    set<int> numSet(nums.begin(), nums.end());
    vector<int> result;
    for (size_t i = 1; i <= nums.size(); ++i) {
        if (numSet.find(i) == numSet.end()) {
            result.push_back(i);
        }
    }
    return result;
}

/**
 * Problem 4: Sliding Window Maximum (LC 239)
 * Description:
 * You are given an array of integers nums, and there is a sliding window of size k which is moving from the very
 * left of the array to the very right. Return the maximum of each window.
 *
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); ++i) {
        window.insert(nums[i]);
        if (window.size() > static_cast<size_t>(k)) {
            window.erase(window.find(nums[i - k]));
        }
        if (window.size() == static_cast<size_t>(k)) {
            result.push_back(*window.rbegin());
        }
    }
    return result;
}

/**
 * Problem 5: Kth Largest Element in a Stream (LC 703)
 * Description:
 * Design a class that finds the kth largest element in a stream.
 *
 * Example:
 * Input: k = 3, nums = [4,5,8,2]
 * Output: add(3) -> 4, add(5) -> 5
 */
class KthLargest {
    multiset<int> elements;
    int capacity;

public:
    KthLargest(int k, vector<int>& nums) {
        capacity = k;
        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        elements.insert(val);
        if (elements.size() > static_cast<size_t>(capacity)) {
            elements.erase(elements.begin());
        }
        return *elements.begin();
    }
};

/**
 * Problem 6: My Calendar I (LC 729)
 * Description:
 * Implement a calendar to manage booking intervals.
 *
 * Example:
 * Input: book(10, 20) -> true, book(15, 25) -> false
 */
class MyCalendar {
    map<int, int> calendar;

public:
    MyCalendar() {}

    bool book(int start, int end) {
        auto next = calendar.lower_bound(start);
        if (next != calendar.end() && next->first < end) {
            return false;
        }
        if (next != calendar.begin() && (--next)->second > start) {
            return false;
        }
        calendar[start] = end;
        return true;
    }
};

/**
 * Problem 7: Count of Smaller Numbers After Self (LC 315)
 * Description:
 * Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
 *
 * Example:
 * Input: nums = [5,2,6,1]
 * Output: [2,1,1,0]
 */
vector<int> countSmaller(vector<int>& nums) {
    map<int, int> counts;
    vector<int> result(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i) {
        int count = 0;
        for (auto it = counts.begin(); it != counts.end() && it->first < nums[i]; ++it) {
            count += it->second;
        }
        result[i] = count;
        counts[nums[i]]++;
    }
    return result;
}

/**
 * Problem 8: Find Common Elements in Two Arrays
 * Description:
 * Given two integer arrays nums1 and nums2, return an array of their common elements.
 *
 * Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 */
vector<int> findCommonElements(vector<int>& nums1, vector<int>& nums2) {
    set<int> set1(nums1.begin(), nums1.end());
    set<int> set2(nums2.begin(), nums2.end());
    vector<int> result;
    for (int num : set1) {
        if (set2.find(num) != set2.end()) {
            result.push_back(num);
        }
    }
    return result;
}

/**
 * Problem 9: Top K Frequent Words (LC 692)
 * Description:
 * Given an array of words and an integer k, return the k most frequent words sorted by frequency and lexicographical order.
 *
 * Example:
 * Input: words = ["i", "love", "leetcode", "i", "love", "coding"], k = 2
 * Output: ["i", "love"]
 */
vector<string> topKFrequentWords(vector<string>& words, int k) {
    map<string, int> wordCount;
    for (string& word : words) {
        wordCount[word]++;
    }
    vector<pair<int, string>> freqList;
    for (auto& [word, freq] : wordCount) {
        freqList.push_back({-freq, word}); // Use negative frequency for reverse sorting
    }
    sort(freqList.begin(), freqList.end());
    vector<string> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(freqList[i].second);
    }
    return result;
}

/**
 * Problem 10: Longest Substring Without Repeating Characters (LC 3)
 * Description:
 * Given a string s, find the length of the longest substring without repeating characters.
 *
 * Example:
 * Input: s = "abcabcbb"
 * Output: 3
 */
int lengthOfLongestSubstring(string s) {
    map<char, int> charIndex;
    int maxLength = 0, start = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (charIndex.count(s[i]) && charIndex[s[i]] >= start) {
            start = charIndex[s[i]] + 1;
        }
        charIndex[s[i]] = i;
        maxLength = max(maxLength, static_cast<int>(i) - start + 1);
    }
    return maxLength;
}

/**
 * Problem 11: Valid Sudoku (LC 36)
 * Description:
 * Determine if a 9x9 Sudoku board is valid.
 *
 * Example:
 * Input: board =
 * [["5","3",".",".","7",".",".",".","."],
 *  ["6",".",".","1","9","5",".",".","."],
 *  ...]
 * Output: true
 */
bool isValidSudoku(vector<vector<char>>& board) {
    map<int, set<char>> rows, cols, boxes;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char num = board[i][j];
            if (num == '.') continue;
            int boxIndex = (i / 3) * 3 + (j / 3);
            if (rows[i].count(num) || cols[j].count(num) || boxes[boxIndex].count(num)) return false;
            rows[i].insert(num);
            cols[j].insert(num);
            boxes[boxIndex].insert(num);
        }
    }
    return true;
}

/**
 * Problem 12: Group Anagrams (LC 49)
 * Description:
 * Given an array of strings, group anagrams together.
 *
 * Example:
 * Input: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
 * Output: [["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]
 */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    map<string, vector<string>> anagramGroups;
    for (string str : strs) {
        string sortedStr = str;
        sort(sortedStr.begin(), sortedStr.end());
        anagramGroups[sortedStr].push_back(str);
    }
    vector<vector<string>> result;
    for (auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    return result;
}

/**
 * Problem 13: Subarray Sum Equals K (LC 560)
 * Description:
 * Given an array nums and an integer k, return the total number of continuous subarrays whose sum equals k.
 *
 * Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 */
int subarraySum(vector<int>& nums, int k) {
    map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0, count = 0;
    for (int num : nums) {
        sum += num;
        if (prefixSum.count(sum - k)) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    return count;
}

/**
 * Problem 14: Longest Consecutive Sequence (LC 128)
 * Description:
 * Given an unsorted array of integers nums, return the length of the longest consecutive sequence.
 *
 * Example:
 * Input: nums = [100, 4, 200, 1, 3, 2]
 * Output: 4
 */
int longestConsecutive(vector<int>& nums) {
    set<int> numSet(nums.begin(), nums.end());
    int maxLength = 0;
    for (int num : numSet) {
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentStreak = 1;
            while (numSet.count(currentNum + 1)) {
                currentNum++;
                currentStreak++;
            }
            maxLength = max(maxLength, currentStreak);
        }
    }
    return maxLength;
}

/**
 * Problem 15: Intersection of Two Arrays (LC 349)
 * Description:
 * Given two integer arrays nums1 and nums2, return an array of their intersection.
 * Each element in the result must be unique.
 *
 * Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 */
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    set<int> set1(nums1.begin(), nums1.end());
    set<int> result;
    for (int num : nums2) {
        if (set1.count(num)) {
            result.insert(num);
        }
    }
    return vector<int>(result.begin(), result.end());
}

/**
 * Problem 16: K Closest Points to Origin (LC 973)
 * Description:
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the k closest points to the origin (0,0).
 *
 * Example:
 * Input: points = [[1,3],[-2,2]], k = 1
 * Output: [[-2,2]]
 */
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    multimap<int, vector<int>> distanceMap;
    for (auto& point : points) {
        int distance = point[0] * point[0] + point[1] * point[1];
        distanceMap.insert({distance, point});
    }
    vector<vector<int>> result;
    for (auto it = distanceMap.begin(); k > 0 && it != distanceMap.end(); ++it, --k) {
        result.push_back(it->second);
    }
    return result;
}

/**
 * Problem 17: Reorganize String (LC 767)
 * Description:
 * Given a string s, rearrange the characters so that no two adjacent characters are the same.
 * If it is not possible, return an empty string.
 *
 * Example:
 * Input: s = "aab"
 * Output: "aba"
 */
string reorganizeString(string s) {
    map<char, int> count;
    for (char c : s) count[c]++;
    multimap<int, char, greater<int>> sortedCount;
    for (auto& [ch, cnt] : count) {
        sortedCount.insert({cnt, ch});
    }
    string res(s.size(), ' ');
    int index = 0;
    for (auto& [cnt, ch] : sortedCount) {
        for (int i = 0; i < cnt; ++i) {
            if (static_cast<size_t>(index) >= s.size()) index = 1;
            res[index] = ch;
            index += 2;
        }
    }
    for (size_t i = 1; i < s.size(); ++i) {
        if (res[i] == res[i - 1]) return "";
    }
    return res;
}

/**
 * Problem 18: Design HashMap (LC 706)
 * Description:
 * Design a HashMap without using built-in hash table libraries.
 *
 * Example:
 * Input: myHashMap.put(1, 1); myHashMap.get(1);
 * Output: 1
 */
class MyHashMap {
private:
    map<int, int> hashMap;
public:
    void put(int key, int value) {
        hashMap[key] = value;
    }
    int get(int key) {
        return hashMap.count(key) ? hashMap[key] : -1;
    }
    void remove(int key) {
        hashMap.erase(key);
    }
};

/**
 * Problem 19: Find Duplicate Subtrees (LC 652)
 * Description:
 * Given the root of a binary tree, return all duplicate subtrees.
 * Two trees are duplicate if they have the same structure and node values.
 *
 * Example:
 * Input: root = [1,2,3,4,null,2,4,null,null,4]
 * Output: [[2,4],[4]]
 */
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    map<string, vector<TreeNode*>> subtreeMap;
    vector<TreeNode*> result;
    function<string(TreeNode*)> serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        string s = to_string(node->val) + "," + serialize(node->left) + "," + serialize(node->right);
        subtreeMap[s].push_back(node);
        return s;
    };
    serialize(root);
    for (const auto& [key, nodes] : subtreeMap) {
        if (nodes.size() > 1) {
            result.push_back(nodes[0]);
        }
    }
    return result;
}

int main() {
    // Test Problem 1
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Contains Nearby Almost Duplicate: " << (containsNearbyAlmostDuplicate(nums1, 3, 0) ? "True" : "False") << endl;

    // Test Problem 2
    vector<int> nums2 = {2, 7, 11, 15};
    vector<int> result2 = twoSum(nums2, 9);
    cout << "Two Sum Indices: [" << result2[0] << ", " << result2[1] << "]" << endl;

    // Test Problem 3
    vector<int> nums3 = {4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> result3 = findDisappearedNumbers(nums3);
    cout << "Disappeared Numbers: ";
    for (int num : result3) cout << num << " ";
    cout << endl;

    // Test Problem 4
    vector<int> nums4 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> result4 = maxSlidingWindow(nums4, 3);
    cout << "Sliding Window Maximum: ";
    for (int num : result4) cout << num << " ";
    cout << endl;

    // Test Problem 5
    vector<int> nums5 = {4, 5, 8, 2};
    KthLargest kthLargest(3, nums5);
    cout << "Kth Largest after adding 3: " << kthLargest.add(3) << endl;
    cout << "Kth Largest after adding 5: " << kthLargest.add(5) << endl;

    // Test Problem 6
    MyCalendar myCalendar;
    cout << "Book [10, 20]: " << (myCalendar.book(10, 20) ? "True" : "False") << endl;
    cout << "Book [15, 25]: " << (myCalendar.book(15, 25) ? "True" : "False") << endl;

    // Test Problem 7
    vector<int> nums7 = {5, 2, 6, 1};
    vector<int> result7 = countSmaller(nums7);
    cout << "Count of Smaller Numbers After Self: ";
    for (int num : result7) cout << num << " ";
    cout << endl;

    // Test Problem 8
    vector<int> nums8a = {1, 2, 2, 1};
    vector<int> nums8b = {2, 2};
    vector<int> result8 = findCommonElements(nums8a, nums8b);
    cout << "Common Elements: ";
    for (int num : result8) cout << num << " ";
    cout << endl;

    // Test Problem 9
    vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
    vector<string> result9 = topKFrequentWords(words, 2);
    cout << "Top K Frequent Words: ";
    for (string& word : result9) cout << word << " ";
    cout << endl;

    // Test Problem 10
    cout << "Problem 10 - Longest Substring Without Repeating Characters: " << lengthOfLongestSubstring("abcabcbb") << endl;

    // Test Problem 11
    vector<vector<char>> board_11 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    cout << "Problem 11 - Valid Sudoku: " << (isValidSudoku(board_11) ? "true" : "false") << endl;

    // Test Problem 12
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> groupedAnagrams = groupAnagrams(strs);
    cout << "Problem 12 - Group Anagrams: " << groupedAnagrams.size() << " groups" << endl;

    // Test Problem 13
    vector<int> nums13 = {1,1,1};
    cout << "Problem 13 - Subarray Sum Equals K: " << subarraySum(nums13, 2) << endl;

    // Test Problem 14
    vector<int> nums14 = {100,4,200,1,3,2};
    cout << "Problem 14 - Longest Consecutive Sequence: " << longestConsecutive(nums14) << endl;

    // Test Problem 15
    vector<int> nums15_1 = {1,2,2,1};
    vector<int> nums15_2 = {2,2};
    vector<int> result15 = intersection(nums15_1, nums15_2);
    cout << "Problem 15 - Intersection: ";
    for (int num : result15) cout << num << " ";
    cout << endl;

    // Test Problem 16
    vector<vector<int>> points = {{1,3},{-2,2}};
    vector<vector<int>> result16 = kClosest(points, 1);
    cout << "Problem 16 - K Closest Points: " << result16.size() << " points" << endl;

    // Test Problem 17
    cout << "Problem 17 - Reorganized String: " << reorganizeString("aab") << endl;

    // Test Problem 18
    MyHashMap myHashMap;
    myHashMap.put(1, 1);
    cout << "Problem 18 - MyHashMap Get: " << myHashMap.get(1) << endl;

    // Test Problem 19
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);
    root->right->left->left = new TreeNode(4);
    vector<TreeNode*> result19 = findDuplicateSubtrees(root);
    cout << "Problem 19 - Find Duplicate Subtrees: " << result19.size() << " duplicates" << endl;

    return 0;
}
