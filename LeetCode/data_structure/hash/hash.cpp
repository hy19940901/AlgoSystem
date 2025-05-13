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
vector<int> TwoSum(const vector<int>& nums, int target) {
    vector<int> res;
    unordered_map<int, int> num_index_map;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (num_index_map.find(complement) != num_index_map.end()) {
            res.push_back(num_index_map[complement]);
            res.push_back(i);
            return res;
        }
        num_index_map[nums[i]] = i;
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
vector<vector<string>> GroupAnagrams(const vector<string>& strs) {
    unordered_map<string, vector<string>> anagram_groups;
    for (const string& str : strs) {
        string sorted_str = str;
        sort(sorted_str.begin(), sorted_str.end());
        anagram_groups[sorted_str].push_back(str);
    }
    vector<vector<string>> res;
    for (const auto& pair : anagram_groups) {
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
int LongestConsecutive(const vector<int>& nums) {
    unordered_set<int> num_set(nums.begin(), nums.end());
    int res = 0;
    for (const int& num : num_set) {
        if (!num_set.count(num - 1)) {
            int current_num = num;
            int current_streak = 1;
            while (num_set.count(current_num + 1)) {
                current_num++;
                current_streak++;
            }
            res = max(res, current_streak);
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
int SubarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> prefix_sum_count;
    prefix_sum_count[0] = 1;
    int sum = 0, res = 0;
    for (const int& num : nums) {
        sum += num;
        if (prefix_sum_count.find(sum - k) != prefix_sum_count.end()) {
            res += prefix_sum_count[sum - k];
        }
        prefix_sum_count[sum]++;
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
bool ContainsDuplicate(const vector<int>& nums) {
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
string FrequencySort(const string& s) {
    unordered_map<char, int> freq_map;
    for (char c : s) freq_map[c]++;
    vector<pair<int, char>> freq_vec;
    for (const auto& [ch, freq] : freq_map) {
        freq_vec.push_back({freq, ch});
    }
    sort(freq_vec.rbegin(), freq_vec.rend());
    string res;
    for (const auto& [freq, ch] : freq_vec) {
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
bool CheckSubarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> remainder_map;
    remainder_map[0] = -1;
    int running_sum = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        running_sum += nums[i];
        int remainder = k == 0 ? running_sum : running_sum % k;
        if (remainder_map.find(remainder) != remainder_map.end()) {
            if (i - remainder_map[remainder] > 1) return true;
        } else {
            remainder_map[remainder] = i;
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
int LengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> char_index_map;
    int max_length = 0, start = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (char_index_map.find(s[i]) != char_index_map.end() && char_index_map[s[i]] >= start) {
            start = char_index_map[s[i]] + 1;
        }
        char_index_map[s[i]] = i;
        max_length = max(max_length, static_cast<int>(i - start + 1));
    }
    return max_length;
}

/**
 * Problem 9: Intersection of Two Arrays (LC 349)
 * Description:
 * Given two arrays, return their intersection.
 * Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 */
vector<int> Intersection(const vector<int>& nums1, const vector<int>& nums2) {
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
vector<int> TopKFrequent(const vector<int>& nums, int k) {
    unordered_map<int, int> freq_map;
    for (int num : nums) {
        freq_map[num]++;
    }
    vector<pair<int, int>> freq_vec(freq_map.begin(), freq_map.end());
    sort(freq_vec.rbegin(), freq_vec.rend(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(freq_vec[i].first);
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
bool IsIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, char> s_tot, t_tos;
    for (size_t i = 0; i < s.size(); ++i) {
        char c1 = s[i], c2 = t[i];
        if ((s_tot.count(c1) && s_tot[c1] != c2) || (t_tos.count(c2) && t_tos[c2] != c1)) {
            return false;
        }
        s_tot[c1] = c2;
        t_tos[c2] = c1;
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
bool WordPattern(const string& pattern, const string& s) {
    unordered_map<char, string> char_to_word;
    unordered_map<string, char> word_to_char;
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
        if ((char_to_word.count(c) && char_to_word[c] != word) || (word_to_char.count(word) && word_to_char[word] != c)) {
            return false;
        }
        char_to_word[c] = word;
        word_to_char[word] = c;
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
vector<TreeNode*> FindDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, vector<TreeNode*>> subtree_map;
    vector<TreeNode*> result;
    function<string(TreeNode*)> Serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        string s = to_string(node->val) + "," + Serialize(node->left) + "," + Serialize(node->right);
        subtree_map[s].push_back(node);
        return s;
    };
    Serialize(root);
    for (const auto& [key, nodes] : subtree_map) {
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
bool IsAnagram(string s, string t) {
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
bool IsHappy(int n) {
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
 * Given two strings ransom_note and magazine, return true if ransom_note can be constructed from magazine.
 * Example:
 * Input: ransom_note = "aa", magazine = "aab"
 * Output: true
 */
bool CanConstruct(string ransom_note, string magazine) {
    unordered_map<char, int> count;
    for (char c : magazine) count[c]++;
    for (char c : ransom_note) {
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
int FirstUniqChar(string s) {
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
bool ContainsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> index_map;
    for (size_t i = 0; i < nums.size(); i++) {
        if (index_map.count(nums[i]) && static_cast<int>(i) - index_map[nums[i]] <= k) {
            return true;
        }
        index_map[nums[i]] = i;
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
vector<int> TwoSumII(vector<int>& numbers, int target) {
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
int FourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> sum_map;
    int count = 0;
    for (int a : nums1) {
        for (int b : nums2) {
            sum_map[a + b]++;
        }
    }
    for (int c : nums3) {
        for (int d : nums4) {
            count += sum_map[-(c + d)];
        }
    }
    return count;
}

int main() {
    // Test Problem 1: Two Sum
    vector<int> nums1 = {2, 7, 11, 15};
    int target = 9;
    vector<int> res1 = TwoSum(nums1, target);
    cout << "Two Sum: [";
    for (size_t i = 0; i < res1.size(); ++i) {
        cout << res1[i] << (i == res1.size() - 1 ? "]" : ", ");
    }
    cout << endl;

    // Test Problem 2: Group Anagrams
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> res2 = GroupAnagrams(strs);
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
    int res3 = LongestConsecutive(nums2);
    cout << "Longest Consecutive Sequence: " << res3 << endl;

    // Test Problem 4: Subarray Sum Equals K
    vector<int> nums3 = {1, 1, 1};
    int k = 2;
    int res4 = SubarraySum(nums3, k);
    cout << "Subarray Sum Equals K: " << res4 << endl;

    // Test Problem 5: Contains Duplicate
    vector<int> nums4 = {1, 2, 3, 4, 5, 1};
    bool res5 = ContainsDuplicate(nums4);
    cout << "Contains Duplicate: " << (res5 ? "True" : "False") << endl;

    // Test Problem 6: Sort Characters By Frequency
    string s = "tree";
    string res6 = FrequencySort(s);
    cout << "Frequency Sort: " << res6 << endl;

    // Test Problem 7: Continuous Subarray Sum
    vector<int> nums5 = {23, 2, 4, 6, 7};
    int k2 = 6;
    bool res7 = CheckSubarraySum(nums5, k2);
    cout << "Continuous Subarray Sum: " << (res7 ? "True" : "False") << endl;

    // Test Problem 8: Longest Substring Without Repeating Characters
    string s2 = "abcabcbb";
    int res8 = LengthOfLongestSubstring(s2);
    cout << "Longest Substring Without Repeating Characters: " << res8 << endl;

    // Test Problem 9
    vector<int> nums9_1 = {1,2,2,1}, nums9_2 = {2,2};
    vector<int> res9 = Intersection(nums9_1, nums9_2);
    cout << "Intersection: ";
    for (int num : res9) cout << num << " ";
    cout << endl;

    // Test Problem 10
    vector<int> nums10 = {1,1,1,2,2,3};
    vector<int> res10 = TopKFrequent(nums10, 2);
    cout << "Top K Frequent Elements: ";
    for (int num : res10) cout << num << " ";
    cout << endl;

    // Test Problem 11
    cout << "Isomorphic Strings: " << (IsIsomorphic("egg", "add") ? "true" : "false") << endl;

    // Test Problem 12
    cout << "Word Pattern: " << (WordPattern("abba", "dog cat cat dog") ? "true" : "false") << endl;

    // Test Problem 13
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);
    root->right->left->left = new TreeNode(4);
    vector<TreeNode*> res13 = FindDuplicateSubtrees(root);
    cout << "Duplicate Subtrees Found: " << res13.size() << endl;

    // Test Problem 14
    cout << "Valid Anagram: " << (IsAnagram("anagram", "nagaram") ? "true" : "false") << endl;

    // Test Problem 15
    cout << "Happy Number: " << (IsHappy(19) ? "true" : "false") << endl;

    // Test Problem 16
    cout << "Ransom Note: " << (CanConstruct("aa", "aab") ? "true" : "false") << endl;

    // Test Problem 17
    cout << "First Unique Character Index: " << FirstUniqChar("leetcode") << endl;

    // Test Problem 18
    vector<int> nums18 = {1,2,3,1};
    cout << "Contains Nearby Duplicate: " << (ContainsNearbyDuplicate(nums18, 3) ? "true" : "false") << endl;

    // Test Problem 19
    vector<int> nums19 = {2,7,11,15};
    vector<int> twoSumRes19 = TwoSumII(nums19, 9);
    cout << "Two Sum II: [" << twoSumRes19[0] << ", " << twoSumRes19[1] << "]" << endl;

    // Test Problem 20
    vector<int> nums20_1 = {1,2}, nums20_2 = {-2,-1}, nums20_3 = {-1,2}, nums20_4 = {0,2};
    cout << "4Sum II Count: " << FourSumCount(nums20_1, nums20_2, nums20_3, nums20_4) << endl;

    return 0;
}
