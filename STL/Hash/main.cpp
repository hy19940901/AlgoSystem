#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Problem 1: Two Sum (LC 1)
 * Description:
 * Given an array of integers `nums` and an integer `target`, return indices of the two numbers
 * such that they add up to `target`.
 */
vector<int> twoSum(const vector<int>& nums, int target) {
    vector<int> res;
    unordered_map<int, int> numIndexMap;
    for (int i = 0; i < nums.size(); ++i) {
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
 * Group strings into anagrams.
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
 * Given an unsorted array of integers `nums`, return the length of the longest consecutive sequence.
 */
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int res = 0;
    for (const int& num : numSet) {
        if (!numSet.count(num - 1)) { // Start of a sequence
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
 */
int subarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1; // Initial condition
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
 * Return true if any value appears at least twice in the array.
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
 * Sort characters in a string by their frequency of appearance.
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
 */
bool checkSubarraySum(const vector<int>& nums, int k) {
    unordered_map<int, int> remainderMap;
    remainderMap[0] = -1; // Initialize remainder map with 0 remainder
    int runningSum = 0;
    for (int i = 0; i < nums.size(); ++i) {
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
 */
int lengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> charIndexMap;
    int maxLength = 0, start = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (charIndexMap.find(s[i]) != charIndexMap.end() && charIndexMap[s[i]] >= start) {
            start = charIndexMap[s[i]] + 1;
        }
        charIndexMap[s[i]] = i;
        maxLength = max(maxLength, i - start + 1);
    }
    return maxLength;
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

    return 0;
}
