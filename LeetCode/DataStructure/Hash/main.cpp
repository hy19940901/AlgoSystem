#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * Problem 1: Two Sum (LC 1)
 * Description:
 * Given an array of integers `nums` and an integer `target`, return indices of the two numbers
 * such that they add up to `target`.
 * Example:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 */
vector<int> twoSum(const vector<int>& nums, int target) {
    vector<int> res;
    unordered_map<int, int> numIndexMap;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numIndexMap.find(complement) != numIndexMap.end()) {
            res.push_back(numIndexMap[complement]);
            res.push_back(i);
            return res;
        }
        numIndexMap[nums[i]] = i;
    }
    return res;
}

/**
 * Problem 2: Group Anagrams (LC 49)
 * Description:
 * Given an array of strings, group the anagrams together.
 * Example:
 * Input: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
 * Output: [["eat","tea","ate"],["tan","nat"],["bat"]]
 */
vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    unordered_map<string, vector<string>> anagramGroups;
    for (const string& str : strs) {
        string sortedStr = str;
        sort(sortedStr.begin(), sortedStr.end());
        anagramGroups[sortedStr].push_back(str);
    }
    vector<vector<string>> res;
    for (const auto& pair : anagramGroups) {
        res.push_back(pair.second);
    }
    return res;
}

/**
 * Problem 3: Longest Consecutive Sequence (LC 128)
 * Description:
 * Given an unsorted array of integers, return the length of the longest consecutive sequence.
 * Example:
 * Input: nums = [100, 4, 200, 1, 3, 2]
 * Output: 4
 */
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int res = 0;
    for (const int& num : numSet) {
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentStreak = 1;
            while (numSet.count(currentNum + 1)) {
                currentNum++;
                currentStreak++;
            }
            res = max(res, currentStreak);
        }
    }
    return res;
}

/**
 * Problem 4: Subarray Sum Equals K (LC 560)
 * Description:
 * Find the total number of continuous subarrays whose sum equals to `k`.
 * Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 */
int subarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;
    int sum = 0, res = 0;
    for (const int& num : nums) {
        sum += num;
        if (prefixSumCount.find(sum - k) != prefixSumCount.end()) {
            res += prefixSumCount[sum - k];
        }
        prefixSumCount[sum]++;
    }
    return res;
}

/**
 * Problem 5: Contains Duplicate (LC 217)
 * Description:
 * Given an array of integers, return true if any value appears at least twice.
 * Example:
 * Input: nums = [1,2,3,4,5,1]
 * Output: true
 */
bool containsDuplicate(const vector<int>& nums) {
    unordered_set<int> seen;
    for (const int& num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

/**
 * Problem 6: Sort Characters By Frequency (LC 451)
 * Description:
 * Given a string, sort it in decreasing order based on character frequency.
 * Example:
 * Input: s = "tree"
 * Output: "eert"
 */
string frequencySort(const string& s) {
    unordered_map<char, int> freqMap;
    for (char c : s) freqMap[c]++;
    vector<pair<int, char>> freqVec;
    for (const auto& [ch, freq] : freqMap) {
        freqVec.push_back({freq, ch});
    }
    sort(freqVec.rbegin(), freqVec.rend());
    string res;
    for (const auto& [freq, ch] : freqVec) {
        res.append(freq, ch);
    }
    return res;
}

/**
 * Problem 7: Continuous Subarray Sum (LC 523)
 * Description:
 * Check if the array has a continuous subarray whose sum is a multiple of `k`.
 * Example:
 * Input: nums = [23,2,4,6,7], k = 6
 * Output: true
 */
bool checkSubarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> remainderMap;
    remainderMap[0] = -1;
    int runningSum = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        runningSum += nums[i];
        int remainder = k == 0 ? runningSum : runningSum % k;
        if (remainderMap.find(remainder) != remainderMap.end()) {
            if (i - remainderMap[remainder] > 1) return true;
        } else {
            remainderMap[remainder] = i;
        }
    }
    return false;
}

/**
 * Problem 8: Longest Substring Without Repeating Characters (LC 3)
 * Description:
 * Find the length of the longest substring without repeating characters.
 * Example:
 * Input: s = "abcabcbb"
 * Output: 3
 */
int lengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> charIndexMap;
    int maxLength = 0, start = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (charIndexMap.find(s[i]) != charIndexMap.end() && charIndexMap[s[i]] >= start) {
            start = charIndexMap[s[i]] + 1;
        }
        charIndexMap[s[i]] = i;
        maxLength = max(maxLength, static_cast<int>(i - start + 1));
    }
    return maxLength;
}

/**
 * Problem 9: Intersection of Two Arrays (LC 349)
 * Description:
 * Given two arrays, return their intersection.
 * Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 */
vector<int> intersection(const vector<int>& nums1, const vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> result;
    for (int num : nums2) {
        if (set1.count(num)) {
            result.insert(num);
        }
    }
    return vector<int>(result.begin(), result.end());
}

/**
 * Problem 10: Top K Frequent Elements (LC 347)
 * Description:
 * Given a non-empty array of integers, return the k most frequent elements.
 * Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 */
vector<int> topKFrequent(const vector<int>& nums, int k) {
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }
    vector<pair<int, int>> freqVec(freqMap.begin(), freqMap.end());
    sort(freqVec.rbegin(), freqVec.rend(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(freqVec[i].first);
    }
    return result;
}

/**
 * Problem 11: Isomorphic Strings (LC 205)
 * Description:
 * Given two strings s and t, determine if they are isomorphic.
 * Example:
 * Input: s = "egg", t = "add"
 * Output: true
 */
bool isIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, char> sToT, tToS;
    for (size_t i = 0; i < s.size(); ++i) {
        char c1 = s[i], c2 = t[i];
        if ((sToT.count(c1) && sToT[c1] != c2) || (tToS.count(c2) && tToS[c2] != c1)) {
            return false;
        }
        sToT[c1] = c2;
        tToS[c2] = c1;
    }
    return true;
}

/**
 * Problem 12: Word Pattern (LC 290)
 * Description:
 * Given a pattern and a string s, find if s follows the same pattern.
 * Example:
 * Input: pattern = "abba", s = "dog cat cat dog"
 * Output: true
 */
bool wordPattern(const string& pattern, const string& s) {
    unordered_map<char, string> charToWord;
    unordered_map<string, char> wordToChar;
    vector<string> words;
    size_t pos = 0, found;
    while ((found = s.find(' ', pos)) != string::npos) {
        words.push_back(s.substr(pos, found - pos));
        pos = found + 1;
    }
    words.push_back(s.substr(pos));
    if (pattern.size() != words.size()) return false;
    for (size_t i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        const string& word = words[i];
        if ((charToWord.count(c) && charToWord[c] != word) || (wordToChar.count(word) && wordToChar[word] != c)) {
            return false;
        }
        charToWord[c] = word;
        wordToChar[word] = c;
    }
    return true;
}

/**
 * Problem 13: Find Duplicate Subtrees (LC 652)
 * Description:
 * Given the root of a binary tree, return all duplicate subtrees.
 * Example:
 * Input: root = [1,2,3,4,null,2,4,null,null,4]
 * Output: [[2,4],[4]]
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, vector<TreeNode*>> subtreeMap;
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

/**
 * Problem 14: Valid Anagram (LC 242)
 * Description:
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * An anagram is a word or phrase formed by rearranging the letters of a different word or phrase.
 * Example:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 */
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (char c : t) {
        if (--count[c] < 0) return false;
    }
    return true;
}

/**
 * Problem 15: Happy Number (LC 202)
 * Description:
 * A number is happy if repeatedly replacing it with the sum of the squares of its digits eventually leads to 1.
 * Example:
 * Input: n = 19
 * Output: true
 */
bool isHappy(int n) {
    unordered_set<int> seen;
    while (n != 1 && !seen.count(n)) {
        seen.insert(n);
        int sum = 0;
        while (n) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    return n == 1;
}

/**
 * Problem 16: Ransom Note (LC 383)
 * Description:
 * Given two strings ransomNote and magazine, return true if ransomNote can be constructed from magazine.
 * Example:
 * Input: ransomNote = "aa", magazine = "aab"
 * Output: true
 */
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> count;
    for (char c : magazine) count[c]++;
    for (char c : ransomNote) {
        if (--count[c] < 0) return false;
    }
    return true;
}

/**
 * Problem 17: First Unique Character in a String (LC 387)
 * Description:
 * Given a string s, return the index of the first non-repeating character. If none exists, return -1.
 * Example:
 * Input: s = "leetcode"
 * Output: 0
 */
int firstUniqChar(string s) {
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (size_t i = 0; i < s.size(); i++) {
        if (count[s[i]] == 1) return i;
    }
    return -1;
}

/**
 * Problem 18: Contains Nearby Duplicate (LC 219)
 * Description:
 * Given an integer array nums and an integer k, return true if there are two indices i and j such that nums[i] == nums[j] and abs(i - j) <= k.
 * Example:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 */
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> indexMap;
    for (size_t i = 0; i < nums.size(); i++) {
        if (indexMap.count(nums[i]) && static_cast<int>(i) - indexMap[nums[i]] <= k) {
            return true;
        }
        indexMap[nums[i]] = i;
    }
    return false;
}

/**
 * Problem 19: Two Sum II - Input Array Is Sorted (LC 167)
 * Description:
 * Given a 1-indexed sorted array, return indices of the two numbers such that they add up to target.
 * Example:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 */
vector<int> twoSumII(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) return {left + 1, right + 1};
        else if (sum < target) left++;
        else right--;
    }
    return {};
}

/**
 * Problem 20: 4Sum II (LC 454)
 * Description:
 * Given four integer arrays, count how many tuples (i, j, k, l) satisfy nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0.
 * Example:
 * Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
 * Output: 2
 */
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> sumMap;
    int count = 0;
    for (int a : nums1) {
        for (int b : nums2) {
            sumMap[a + b]++;
        }
    }
    for (int c : nums3) {
        for (int d : nums4) {
            count += sumMap[-(c + d)];
        }
    }
    return count;
}

int main() {
    // Test Problem 1: Two Sum
    vector<int> nums1 = {2, 7, 11, 15};
    int target = 9;
    vector<int> res1 = twoSum(nums1, target);
    cout << "Two Sum: [";
    for (size_t i = 0; i < res1.size(); ++i) {
        cout << res1[i] << (i == res1.size() - 1 ? "]" : ", ");
    }
    cout << endl;

    // Test Problem 2: Group Anagrams
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> res2 = groupAnagrams(strs);
    cout << "Group Anagrams:" << endl;
    for (const auto& group : res2) {
        cout << "[";
        for (size_t i = 0; i < group.size(); ++i) {
            cout << group[i] << (i == group.size() - 1 ? "]" : ", ");
        }
        cout << endl;
    }

    // Test Problem 3: Longest Consecutive Sequence
    vector<int> nums2 = {100, 4, 200, 1, 3, 2};
    int res3 = longestConsecutive(nums2);
    cout << "Longest Consecutive Sequence: " << res3 << endl;

    // Test Problem 4: Subarray Sum Equals K
    vector<int> nums3 = {1, 1, 1};
    int k = 2;
    int res4 = subarraySum(nums3, k);
    cout << "Subarray Sum Equals K: " << res4 << endl;

    // Test Problem 5: Contains Duplicate
    vector<int> nums4 = {1, 2, 3, 4, 5, 1};
    bool res5 = containsDuplicate(nums4);
    cout << "Contains Duplicate: " << (res5 ? "True" : "False") << endl;

    // Test Problem 6: Sort Characters By Frequency
    string s = "tree";
    string res6 = frequencySort(s);
    cout << "Frequency Sort: " << res6 << endl;

    // Test Problem 7: Continuous Subarray Sum
    vector<int> nums5 = {23, 2, 4, 6, 7};
    int k2 = 6;
    bool res7 = checkSubarraySum(nums5, k2);
    cout << "Continuous Subarray Sum: " << (res7 ? "True" : "False") << endl;

    // Test Problem 8: Longest Substring Without Repeating Characters
    string s2 = "abcabcbb";
    int res8 = lengthOfLongestSubstring(s2);
    cout << "Longest Substring Without Repeating Characters: " << res8 << endl;

    // Test Problem 9
    vector<int> nums9_1 = {1,2,2,1}, nums9_2 = {2,2};
    vector<int> res9 = intersection(nums9_1, nums9_2);
    cout << "Intersection: ";
    for (int num : res9) cout << num << " ";
    cout << endl;

    // Test Problem 10
    vector<int> nums10 = {1,1,1,2,2,3};
    vector<int> res10 = topKFrequent(nums10, 2);
    cout << "Top K Frequent Elements: ";
    for (int num : res10) cout << num << " ";
    cout << endl;

    // Test Problem 11
    cout << "Isomorphic Strings: " << (isIsomorphic("egg", "add") ? "true" : "false") << endl;

    // Test Problem 12
    cout << "Word Pattern: " << (wordPattern("abba", "dog cat cat dog") ? "true" : "false") << endl;

    // Test Problem 13
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);
    root->right->left->left = new TreeNode(4);
    vector<TreeNode*> res13 = findDuplicateSubtrees(root);
    cout << "Duplicate Subtrees Found: " << res13.size() << endl;

    // Test Problem 14
    cout << "Valid Anagram: " << (isAnagram("anagram", "nagaram") ? "true" : "false") << endl;

    // Test Problem 15
    cout << "Happy Number: " << (isHappy(19) ? "true" : "false") << endl;

    // Test Problem 16
    cout << "Ransom Note: " << (canConstruct("aa", "aab") ? "true" : "false") << endl;

    // Test Problem 17
    cout << "First Unique Character Index: " << firstUniqChar("leetcode") << endl;

    // Test Problem 18
    vector<int> nums18 = {1,2,3,1};
    cout << "Contains Nearby Duplicate: " << (containsNearbyDuplicate(nums18, 3) ? "true" : "false") << endl;

    // Test Problem 19
    vector<int> nums19 = {2,7,11,15};
    vector<int> twoSumRes19 = twoSumII(nums19, 9);
    cout << "Two Sum II: [" << twoSumRes19[0] << ", " << twoSumRes19[1] << "]" << endl;

    // Test Problem 20
    vector<int> nums20_1 = {1,2}, nums20_2 = {-2,-1}, nums20_3 = {-1,2}, nums20_4 = {0,2};
    cout << "4Sum II Count: " << fourSumCount(nums20_1, nums20_2, nums20_3, nums20_4) << endl;

    return 0;
}
