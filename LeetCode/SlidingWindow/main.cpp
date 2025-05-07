#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <deque>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

/**
 * Problem 1: Longest Substring Without Repeating Characters (LC 3)
 * Description:
 * Given a string s, find the length of the longest substring without repeating characters.
 * Approach:
 * Use the sliding window technique with two pointers (left, right) to dynamically adjust the window size.
 * Example:
 * Input: s = "abcabcbb"
 * Output: 3
 */
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndex;
    int left = 0, maxLength = 0;
    for (size_t right = 0; right < s.size(); right++) {
        if (charIndex.find(s[right]) != charIndex.end()) {
            left = max(left, charIndex[s[right]] + 1); // Move left to avoid repeating character
        }
        charIndex[s[right]] = right;
        maxLength = max(maxLength, static_cast<int>(right) - left + 1);
    }
    return maxLength;
}

/**
 * Problem 2: Minimum Size Subarray Sum (LC 209)
 * Description:
 * Given an array of positive integers nums and a target sum, find the minimal length of a contiguous 
 * subarray where the sum is at least target. If none exists, return 0.
 * Approach:
 * Expand the window by moving right and contract it by moving left when the sum exceeds target.
 * Example:
 * Input: nums = [2,3,1,2,4,3], target = 7
 * Output: 2
 */
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0, minLength = INT_MAX;
    for (size_t right = 0; right < nums.size(); right++) {
        sum += nums[right];  // Expand window
        while (sum >= target) {  // Contract window
            minLength = min(minLength, static_cast<int>(right) - left + 1);
            sum -= nums[left++];
        }
    }
    return minLength == INT_MAX ? 0 : minLength;
}

/**
 * Problem 3: Sliding Window Maximum (LC 239)
 * Description:
 * Given an array nums and an integer k, return the maximum value in each sliding window of size k.
 * Approach:
 * Use a deque to store indices of useful elements and maintain a decreasing order in the deque.
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == static_cast<int>(i) - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (static_cast<int>(i) >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

/**
 * Problem 4: Find All Anagrams in a String (LC 438)
 * Description:
 * Given a string s and a string p, return all start indices of p's anagrams in s.
 * Approach:
 * Use a frequency count with a sliding window to check for anagram matches.
 * Example:
 * Input: s = "cbaebabacd", p = "abc"
 * Output: [0,6]
 */
vector<int> findAnagrams(string s, string p) {
    vector<int> pCount(26, 0), sCount(26, 0), result;
    if (s.size() < p.size()) return result;

    for (char c : p) pCount[c - 'a']++;
    for (size_t i = 0; i < s.size(); i++) {
        sCount[s[i] - 'a']++;
        if (static_cast<size_t>(i) >= p.size()) sCount[s[i - p.size()] - 'a']--;
        if (sCount == pCount) result.push_back(i - p.size() + 1);
    }
    return result;
}

/**
 * Problem 5: Longest Repeating Character Replacement (LC 424)
 * Description:
 * Given a string s and an integer k, find the length of the longest substring that contains the same letter 
 * after at most k modifications.
 * Approach:
 * Use a frequency map and adjust the window based on the most frequent character in the current window.
 * Example:
 * Input: s = "AABABBA", k = 1
 * Output: 4
 */
int characterReplacement(string s, int k) {
    vector<int> count(26, 0);
    int left = 0, maxCount = 0, maxLength = 0;
    for (size_t right = 0; right < s.size(); right++) {
        maxCount = max(maxCount, ++count[s[right] - 'A']);
        while (static_cast<int>(right) - left + 1 - maxCount > k) {
            count[s[left] - 'A']--;
            left++;
        }
        maxLength = max(maxLength, static_cast<int>(right) - left + 1);
    }
    return maxLength;
}

/**
 * Problem 6: Subarrays with K Different Integers (LC 992)
 * Description:
 * Given an integer array nums and an integer k, return the number of subarrays that contain exactly k different integers.
 * Approach:
 * Use the sliding window technique to count subarrays with at most k distinct numbers, and use the difference of
 * two counts to get the exact count.
 * Example:
 * Input: nums = [1,2,1,2,3], k = 2
 * Output: 7
 */
int atMostKDistinct(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int left = 0, count = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        if (freq[nums[right]]++ == 0) k--;
        while (k < 0) {
            if (--freq[nums[left]] == 0) k++;
            left++;
        }
        count += right - left + 1;
    }
    return count;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}

/**
 * Problem 7: Binary Subarrays With Sum (LC 930)
 * Description:
 * Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum equal to goal.
 * Approach:
 * Use the sliding window to count subarrays with at most "goal" sum and at most "goal-1" sum.
 * Example:
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 */
int atMostSum(vector<int>& nums, int goal) {
    if (goal < 0) return 0;
    int left = 0, count = 0, sum = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        sum += nums[right];
        while (sum > goal) sum -= nums[left++];
        count += right - left + 1;
    }
    return count;
}

int numSubarraysWithSum(vector<int>& nums, int goal) {
    return atMostSum(nums, goal) - atMostSum(nums, goal - 1);
}

/**
 * Problem 8: Longest Subarray of 1's After Deleting One Element (LC 1493)
 * Description:
 * Given a binary array nums, return the maximum number of 1s in a row by deleting exactly one element.
 * Approach:
 * Use a sliding window with a counter that tracks the number of zeros in the window.
 * Example:
 * Input: nums = [1,1,0,1,1,1,0,1,1,1]
 * Output: 5
 */
int longestSubarray(vector<int>& nums) {
    int left = 0, maxLength = 0, zeroCount = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zeroCount++;
        while (zeroCount > 1) {
            if (nums[left++] == 0) zeroCount--;
        }
        maxLength = max(maxLength, static_cast<int>(right) - left);
    }
    return maxLength;
}

/**
 * Problem 9: Maximum Points You Can Obtain from Cards (LC 1423)
 * Description:
 * Given an array cardPoints and an integer k, return the maximum score you can get by picking exactly k cards 
 * from either the start or the end of the array.
 * Approach:
 * Instead of picking from both ends directly, find the minimum sum of the remaining window of size (n - k) 
 * and subtract it from the total sum.
 * Example:
 * Input: cardPoints = [1,2,3,4,5,6,1], k = 3
 * Output: 12
 */
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size(), totalSum = accumulate(cardPoints.begin(), cardPoints.end(), 0);
    if (k == n) return totalSum;

    int minSubarraySum = accumulate(cardPoints.begin(), cardPoints.begin() + (n - k), 0);
    int currentSum = minSubarraySum;
    for (int i = n - k; i < n; i++) {
        currentSum += cardPoints[i] - cardPoints[i - (n - k)];
        minSubarraySum = min(minSubarraySum, currentSum);
    }
    return totalSum - minSubarraySum;
}

/**
 * Problem 10: Maximum Erasure Value (LC 1695)
 * Description:
 * Given an array of positive integers nums, return the maximum sum of a subarray with all unique elements.
 * Approach:
 * Use a sliding window with a hash set to track the unique numbers and update the maximum sum.
 * Example:
 * Input: nums = [4,2,4,5,6]
 * Output: 17
 */
int maximumUniqueSubarray(vector<int>& nums) {
    unordered_set<int> uniqueNums;
    int left = 0, maxSum = 0, currentSum = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        while (uniqueNums.count(nums[right])) {
            currentSum -= nums[left];
            uniqueNums.erase(nums[left++]);
        }
        uniqueNums.insert(nums[right]);
        currentSum += nums[right];
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

/**
 * Main Function: Test all problems
 */
int main() {
    // Test Problem 1: Longest Substring Without Repeating Characters
    cout << "Test Problem 1: Longest Substring Without Repeating Characters (LC 3) \n";
    cout << "Length: " << lengthOfLongestSubstring("abcabcbb") << " (Expected: 3)" << endl;

    // Test Problem 2: Minimum Size Subarray Sum
    cout << "Test Problem 2: Minimum Size Subarray Sum (LC 209) \n";
    vector<int> nums2 = {2, 3, 1, 2, 4, 3};
    cout << "Min Length: " << minSubArrayLen(7, nums2) << " (Expected: 2)" << endl;

    // Test Problem 3: Sliding Window Maximum
    cout << "Test Problem 3: Sliding Window Maximum (LC 239) \n";
    vector<int> nums3 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> result3 = maxSlidingWindow(nums3, 3);
    cout << "Max Sliding Window: ";
    for (int num : result3) cout << num << " ";
    cout << "(Expected: 3 3 5 5 6 7)" << endl;

    // Test Problem 4: Find All Anagrams in a String
    cout << "Test Problem 4: Find All Anagrams in a String (LC 438) \n";
    vector<int> result4 = findAnagrams("cbaebabacd", "abc");
    cout << "Anagram Indices: ";
    for (int idx : result4) cout << idx << " ";
    cout << "(Expected: 0 6)" << endl;

    // Test Problem 5: Longest Repeating Character Replacement
    cout << "Test Problem 5: Longest Repeating Character Replacement (LC 424) \n";
    cout << "Longest Length: " << characterReplacement("AABABBA", 1) << " (Expected: 4)" << endl;

    // Test Problem 6: Subarrays with K Different Integers
    cout << "Test Problem 6: Subarrays with K Different Integers (LC 992) \n";
    vector<int> nums6 = {1, 2, 1, 2, 3};
    cout << "Subarray Count: " << subarraysWithKDistinct(nums6, 2) << " (Expected: 7)" << endl;

    // Test Problem 7: Binary Subarrays With Sum
    cout << "Test Problem 7: Binary Subarrays With Sum (LC 930) \n";
    vector<int> nums7 = {1, 0, 1, 0, 1};
    cout << "Binary Subarrays: " << numSubarraysWithSum(nums7, 2) << " (Expected: 4)" << endl;

    // Test Problem 8: Longest Subarray of 1's After Deleting One Element
    cout << "Test Problem 8: Longest Subarray of 1's After Deleting One Element (LC 1493) \n";
    vector<int> nums8 = {1, 1, 0, 1, 1, 1, 0, 1, 1, 1};
    cout << "Max Consecutive 1's: " << longestSubarray(nums8) << " (Expected: 5)" << endl;

    // Test Problem 9: Maximum Points You Can Obtain from Cards
    cout << "Test Problem 9: Maximum Points You Can Obtain from Cards (LC 1423) \n";
    vector<int> nums9 = {1, 2, 3, 4, 5, 6, 1};
    cout << "Max Score: " << maxScore(nums9, 3) << " (Expected: 12)" << endl;

    // Test Problem 10: Maximum Erasure Value
    cout << "Test Problem 10: Maximum Erasure Value (LC 1695) \n";
    vector<int> nums10 = {4, 2, 4, 5, 6};
    cout << "Max Erasure Value: " << maximumUniqueSubarray(nums10) << " (Expected: 17)" << endl;

    return 0;
}
