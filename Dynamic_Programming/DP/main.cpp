#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <numeric>
using namespace std;

/**
 * Problem 1: Climbing Stairs (LC 70)
 * Description: You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * Example:
 * Input: n = 5
 * Output: 8
 */
int climbStairs(int n) {
    vector<int> dp(n + 1, 0); // dp[i] represents the ways to reach step i
    dp[0] = 1; // 1 way to stay at the ground
    dp[1] = 1; // 1 way to reach the first step
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/**
 * Problem 2: Maximum Subarray (LC 53)
 * Description: Given an integer array nums, find the contiguous subarray
 * (containing at least one number) which has the largest sum and return its sum.
 * Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum = 6.
 */
// greedy is better, but this is the DP solution
int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size(), 0); // dp[i] represents the maximum subarray sum ending at index i
    dp[0] = nums[0];
    int maxSum = dp[0];
    for (int i = 1; i < nums.size(); ++i) {
        dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        maxSum = max(maxSum, dp[i]);
    }
    return maxSum;
}

/**
 * Problem 3: Unique Paths (LC 62)
 * Description: A robot is located at the top-left corner of a m x n grid.
 * The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner. How many possible unique paths are there?
 * Example:
 * Input: m = 3, n = 7
 * Output: 28
 */
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j] represents the number of unique paths to cell (i, j)
    for (int i = 0; i < m; ++i) dp[i][0] = 1; // Initialize the first column
    for (int j = 0; j < n; ++j) dp[0][j] = 1; // Initialize the first row
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

/**
 * Problem 4: Coin Change (LC 322)
 * Description: You are given an integer array coins representing coins of different denominations
 * and an integer amount representing a total amount of money. Return the fewest number of coins
 * that you need to make up that amount. If that amount of money cannot be made up, return -1.
 * Example:
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 */
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX); // dp[i] represents the fewest coins needed to make up amount i
    dp[0] = 0; // Base case: 0 coins are needed to make amount 0
    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            if (dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

/**
 * Problem 5: Longest Increasing Subsequence (LC 300)
 * Description: Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * Example:
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The LIS is [2,3,7,101], therefore the length is 4.
 */
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1); // dp[i] represents the length of the LIS ending at index i
    int maxLen = 1;
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    return maxLen;
}

// Custom binary search to find the first element >= target
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        if (arr[mid] >= target) {
            right = mid - 1; // Move left to find the first occurrence
        } else {
            left = mid + 1; // Move right
        }
    }
    return left; // `left` is the position of the first element >= target
}

// Function to find the length of the LIS using custom binary search
int lengthOfLISWithBinarySearch(vector<int>& nums) {
    vector<int> res; // Auxiliary array to maintain the LIS
    for (int num : nums) {
        if (res.empty() || res.back() < num) {
            res.push_back(num);
        }
        else {
            int idx = binarySearch(res, num);
            res[idx] = num;
        }
    }
    return res.size(); // The length of dp is the length of the LIS
}

/**
 * Problem 6: Edit Distance (LC 72)
 * Description: Given two strings word1 and word2, return the minimum number of operations required
 * to convert word1 to word2. You can perform insert, delete, and replace operations.
 * Example:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * 1. horse -> rorse (replace 'h' with 'r')
 * 2. rorse -> rose (remove 'r')
 * 3. rose -> ros (remove 'e')
 */
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // dp[i][j] represents the edit distance between word1[0..i-1] and word2[0..j-1]
    for (int i = 0; i <= m; ++i) dp[i][0] = i; // Base case: converting word1[0..i-1] to empty string
    for (int j = 0; j <= n; ++j) dp[0][j] = j; // Base case: converting empty string to word2[0..j-1]
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No operation needed
            } else {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1; // Insert, delete, or replace
            }
        }
    }
    return dp[m][n];
}

/**
 * Problem 7: Partition Equal Subset Sum (LC 416)
 * Description: Determine if the array can be partitioned into two subsets with equal sum.
 * Example:
 * Input: nums = [1, 5, 11, 5]
 * Output: true
 * Explanation: The array can be partitioned as [1, 5, 5] and [11].
 *
 * Approach: Dynamic Programming
 * dp[i] represents whether a subset with sum i is achievable.
 * Transition: dp[j] = dp[j] || dp[j - num]
 */
bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    return dp[target];
}

/**
 * Problem 8: House Robber (LC 198)
 * Description: You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed.
 * The only constraint stopping you from robbing each of them is that adjacent houses have security systems connected,
 * and it will automatically contact the police if two adjacent houses were broken into on the same night.
 *
 * Given an integer array nums representing the amount of money of each house, return the maximum amount
 * of money you can rob tonight without alerting the police.
 * Example:
 * Input: nums = [2,7,9,3,1]
 * Output: 12
 *
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9), and rob house 5 (money = 1).
 * Total amount you can rob = 2 + 9 + 1 = 12.
 * Approach: Dynamic Programming
 * dp[i] represents the maximum money that can be robbed up to house i.
 * Transition: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
 */
int rob(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    int prev1 = 0, prev2 = 0;

    for (int num : nums) {
        int temp = prev1;
        prev1 = max(prev1, prev2 + num);
        prev2 = temp;
    }
    return prev1;
}

/**
 * Problem 9: Decode Ways (LC 91)
 * Description: A message containing letters from A-Z can be encoded to numbers using 1-26.
 * Determine the number of ways the message can be decoded.
 * Example:
 * Input: s = "226"
 * Output: 3
 * Explanation: It can be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
 * Approach: Dynamic Programming
 * dp[i] represents the number of ways to decode the string up to index i.
 * Transition:
 * - If s[i-1] != '0': dp[i] += dp[i-1]
 * - If s[i-2..i-1] is valid (10 <= x <= 26): dp[i] += dp[i-2]
 */
int numDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = s[0] != '0' ? 1 : 0;

    for (int i = 2; i <= n; ++i) {
        if (s[i - 1] != '0') dp[i] += dp[i - 1];
        int twoDigit = stoi(s.substr(i - 2, 2));
        if (twoDigit >= 10 && twoDigit <= 26) dp[i] += dp[i - 2];
    }
    return dp[n];
}

/**
 * Problem 10: Triangle Minimum Path Sum (LC 120)
 * * Description:
 * Given a triangle array, return the minimum path sum from top to bottom.
 * For each step, you may move to an adjacent number of the row below. More formally,
 * if you are on index i on the current row, you may move to either index i or index i + 1
 * on the next row.
 *
 * Example:
 * Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
 * Output: 11
 * Explanation: The triangle looks like:
 *    2
 *   3 4
 *  6 5 7
 * 4 1 8 3
 * The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11.
 * Approach: Dynamic Programming
 * dp[i][j] represents the minimum path sum to reach triangle[i][j].
 * Transition: dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j]
 */
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle.back();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
        }
    }
    return dp[0];
}

/**
 * Problem 11: Longest Palindromic Subsequence (LC 516)
 * Description:
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting
 * some or no elements without changing the order of the remaining elements.
 *
 * Example:
 * Input: s = "bbbab"
 * Output: 4
 * Explanation: One possible longest palindromic subsequence is "bbbb".
 * Approach: Dynamic Programming
 * dp[i][j] represents the length of the longest palindromic subsequence in s[i..j].
 * Transition:
 * - If s[i] == s[j]: dp[i][j] = dp[i+1][j-1] + 2
 * - Else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])
 */
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 1; i >= 0; --i) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

/**
 * Problem 12: Burst Balloons (LC 312)
 * Description:
 * You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it
 * represented by an array nums. You are asked to burst all the balloons.
 * If you burst the i-th balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
 * If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
 * Return the maximum coins you can collect by bursting the balloons wisely.
 *
 * Example:
 * Input: nums = [3, 1, 5, 8]
 * Output: 167
 * Explanation:
 * nums = [3,1,5,8] -> [3,5,8] -> [3,8] -> [8] -> []
 * Coins = 3*1*5 + 3*5*8 + 1*3*8 + 1*8*1 = 167
 * Approach: Dynamic Programming
 * dp[i][j] represents the maximum coins you can collect by bursting all balloons in range [i, j].
 * Transition: dp[i][j] = max(dp[i][k-1] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j+1]) for i <= k <= j
 */
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    vector<int> balloons = {1};
    balloons.insert(balloons.end(), nums.begin(), nums.end());
    balloons.push_back(1);

    for (int len = 1; len <= n; ++len) {
        for (int left = 1; left <= n - len + 1; ++left) {
            int right = left + len - 1;
            for (int k = left; k <= right; ++k) {
                dp[left][right] = max(dp[left][right],
                    dp[left][k - 1] + dp[k + 1][right] +
                    balloons[left - 1] * balloons[k] * balloons[right + 1]);
            }
        }
    }
    return dp[1][n];
}

/**
 * Problem 13: Longest Continuous Increasing Subsequence (LC 674)
 * Description:
 * Given an unsorted array of integers nums, return the length of the longest continuous strictly increasing subsequence (LCIS).
 * A continuous increasing subsequence is a subsequence that can be derived from the array by deleting some or no elements
 * without changing the order of the remaining elements and whose elements are strictly increasing.
 *
 * Example:
 * Input: nums = [1,3,5,4,7]
 * Output: 3
 * Explanation: The longest continuous increasing subsequence is [1,3,5] with length 3.

 * Approach: Iterate through the array and track the current length of increasing subsequence.
 * Transition: Reset length when nums[i] <= nums[i-1].
 */
// Greedy is better
int findLengthOfLCIS(vector<int>& nums) {
    if (nums.empty()) return 0;

    int maxLen = 1; // To track the maximum length of LCIS
    int currentLen = 1; // To track the length of the current LCIS

    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i - 1]) {
            currentLen++; // Extend the current LCIS
        } else {
            currentLen = 1; // Reset the length when the sequence breaks
        }
        maxLen = max(maxLen, currentLen); // Update the maximum length
    }

    return maxLen;
}
// dp is easy understanding
int findLengthOfLCIS_DP(vector<int>& nums) {
    if (nums.empty()) return 0;

    int maxLen = 1;
    vector<int> dp(nums.size(), 1);
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1]) dp[i] = dp[i - 1] + 1;
        maxLen = max(maxLen, dp[i]);
    }
    return maxLen;
}

/**
 * Problem 14: Maximum Length of Repeated Subarray (LC 718)
 * Description:
 * - Given two integer arrays nums1 and nums2, return the length of their longest common subarray.
 * - A subarray is a contiguous part of an array.
 * Example:
 * Input: nums1 = [1, 2, 3, 2, 1], nums2 = [3, 2, 1, 4, 7]
 * Output: 3
 * Explanation: The longest common subarray is [3, 2, 1] with length 3.
 * Constraints:
 * 1. 1 <= nums1.length, nums2.length <= 1000
 * 2. 0 <= nums1[i], nums2[i] <= 100
 */

/* Dynamic Programming Solution */
int findLengthDP(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // DP table
    int maxLen = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Extend the subarray
                maxLen = max(maxLen, dp[i][j]); // Update maximum length
            }
        }
    }
    return maxLen;
}

/**
 * Problem 15: Distinct Subsequences(lc115)
 * Description:
 * - Given two strings s and t, return the number of distinct subsequences of s which equals t.
 * - A subsequence of a string is a new string generated from the original string with some characters
 *   (can be none) deleted without changing the relative order of the remaining characters.
 * Example:
 * Input: s = "rabbbit", t = "rabbit"
 * Output: 3
 * Explanation: There are 3 ways to form "rabbit" from "rabbbit":
 * 1. rabbb(it)
 * 2. rab(b)bit
 * 3. rabb(b)it
 * Constraints:
 * 1. 1 <= s.length, t.length <= 1000
 * 2. s and t consist of English letters.
 */

/* Dynamic Programming Solution */
int numDistinctDP(string s, string t) {
    vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1, 0));
    // Initialize base cases
    for (int i = 0; i <= s.size(); i++) dp[i][0] = 1; // Empty t is a subsequence of any s

    // Fill DP table
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 1; j <= t.size(); j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // Match or skip
            } else {
                dp[i][j] = dp[i - 1][j]; // Skip s[i-1]
            }
        }
    }
    return dp[s.size()][t.size()];
}

/* Optimized Dynamic Programming Solution (1D Array) */
int numDistinctOptimized(string s, string t) {
    int m = s.size(), n = t.size();
    vector<uint64_t> dp(n + 1, 0); // Rolling array
    dp[0] = 1; // Empty t is a subsequence of any s

    // Fill DP table with rolling array
    for (int i = 1; i <= m; ++i) {
        for (int j = n; j >= 1; --j) { // Update from back to front
            if (s[i - 1] == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp[n];
}

/**
 * Problem 16: Longest Common Subsequence(lc1143)
 * Description:
 * - Given two strings text1 and text2, return the length of their longest common subsequence.
 * - If there is no common subsequence, return 0.
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative order
 * of the remaining characters.
 *
 * Example:
 * Input: text1 = "abcde", text2 = "ace"
 * Output: 3
 * Explanation: The longest common subsequence is "ace" and its length is 3.
 *
 * Constraints:
 * 1. 1 <= text1.length, text2.length <= 1000
 * 2. text1 and text2 consist of only lowercase English characters.
 */

/* Dynamic Programming Solution */
int longestCommonSubsequenceDP(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // DP table

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Extend the LCS
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // Choose the larger LCS
            }
        }
    }

    return dp[m][n];
}

/* Optimized Dynamic Programming Solution (1D Rolling Array) */
int longestCommonSubsequenceOptimized(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<int> dp(n + 1, 0); // Rolling array

    for (int i = 1; i <= m; ++i) {
        vector<int> prev = dp; // Save previous row
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[j] = prev[j - 1] + 1; // Extend the LCS
            } else {
                dp[j] = max(prev[j], dp[j - 1]); // Choose the larger LCS
            }
        }
    }

    return dp[n];
}

/**
 * Problem 17: Longest Palindromic Substring (LC 5)
 * Description:
 * Given a string s, return the longest palindromic substring in s.
 * A string is a palindrome when it reads the same backward as forward.
 *
 * Example:
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 *
 * Constraints:
 * 1. 1 <= s.length <= 1000
 * 2. s consist of only digits and English letters.
 */
string longestPalindrome(string s) {
    if (s.length() <= 1) {
        return s;
    }

    int max_len = 1;
    int start = 0;
    int end = 0;
    std::vector<std::vector<bool>> dp(s.length(), std::vector<bool>(s.length(), false));

    for (int i = 0; i < s.length(); ++i) {
        dp[i][i] = true;
        for (int j = 0; j < i; ++j) {
            if (s[j] == s[i] && (i - j <= 2 || dp[j + 1][i - 1])) {
                dp[j][i] = true;
                if (i - j + 1 > max_len) {
                    max_len = i - j + 1;
                    start = j;
                    end = i;
                }
            }
        }
    }

    return s.substr(start, end - start + 1);
}

/**
 * Problem 18: Palindromic Substrings (LC 647)
 * Description:
 * Given a string s, return the number of palindromic substrings in it.
 * A string is a palindrome when it reads the same backward as forward.
 * A substring is a contiguous sequence of characters within the string.
 *
 * Example:
 * Input: s = "aaa"
 * Output: 6
 * Explanation: The 6 palindromic substrings are "a", "a", "a", "aa", "aa", "aaa".
 *
 * Constraints:
 * 1. 1 <= s.length <= 1000
 * 2. s consists of lowercase English letters.
 */
int countSubstrings(string s) {
    int n = s.size(), count = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
                count++;
            }
        }
    }
    return count;
}

/**
 * Problem 19: Minimum Falling Path Sum (LC 931)
 * Description:
 * Given an n x n array of integers matrix, return the minimum sum of any falling path
 * through the matrix. A falling path starts at any element in the first row and chooses
 * one element from each row. The next row's choice must be in the column directly below,
 * or diagonally left/right.
 *
 * Example:
 * Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
 * Output: 13
 * Explanation: The falling path with the smallest sum is 1 → 5 → 7.
 *
 * Constraints:
 * 1. n == matrix.length == matrix[i].length
 * 2. 1 <= n <= 100
 * 3. -100 <= matrix[i][j] <= 100
 */
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> dp(matrix[0]); // Start with the first row
    for (int i = 1; i < n; ++i) {
        vector<int> curr(n, INT_MAX);
        for (int j = 0; j < n; ++j) {
            curr[j] = matrix[i][j] + dp[j];
            if (j > 0) curr[j] = min(curr[j], matrix[i][j] + dp[j - 1]);
            if (j < n - 1) curr[j] = min(curr[j], matrix[i][j] + dp[j + 1]);
        }
        dp = curr;
    }
    return *min_element(dp.begin(), dp.end());
}

/**
 * Problem 20: Ugly Number II (LC 264)
 * Description:
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 * Given an integer n, return the nth ugly number.
 *
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: The sequence of ugly numbers is [1, 2, 3, 4, 5, 6, 8, 9, 10, 12, ...].
 *
 * Constraints:
 * 1. 1 <= n <= 1690
 */
int nthUglyNumber(int n) {
    vector<int> dp(n, 0);
    dp[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;

    for (int i = 1; i < n; ++i) {
        int next2 = dp[i2] * 2, next3 = dp[i3] * 3, next5 = dp[i5] * 5;
        dp[i] = min({next2, next3, next5});
        if (dp[i] == next2) i2++;
        if (dp[i] == next3) i3++;
        if (dp[i] == next5) i5++;
    }
    return dp[n - 1];
}

/**
 * Problem 21: Maximum Product Subarray (LC 152)
 * Description:
 * Given an integer array nums, find the contiguous subarray within an array (containing at least one number)
 * which has the largest product.
 *
 * Example:
 * Input: nums = [2,3,-2,4]
 * Output: 6
 * Explanation: The subarray [2,3] has the largest product = 6.
 *
 * Constraints:
 * 1. 1 <= nums.length <= 2 * 10^4
 * 2. -10 <= nums[i] <= 10
 */
int maxProduct(vector<int>& nums) {
    int n = nums.size(), maxProd = nums[0], minProd = nums[0], result = nums[0];
    for (int i = 1; i < n; ++i) {
        if (nums[i] < 0) swap(maxProd, minProd);
        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        result = max(result, maxProd);
    }
    return result;
}

/**
 * Problem 22: Best Time to Buy and Sell Stock (LC 121)
 * Description:
 * Given an array `prices` where prices[i] is the price of a stock on day `i`,
 * return the maximum profit you can achieve from a single transaction.
 *
 * Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6 - 1 = 5.
 */
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX, maxProfit = 0;
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}

/**
 * Problem 23: Best Time to Buy and Sell Stock II (LC 122)
 * Description:
 * You may complete as many transactions as you like (buy one and sell one share of the stock multiple times).
 *
 * Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (1), sell on day 3 (5), buy on day 4 (3), sell on day 5 (6).
 */
int maxProfitMultiple(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}

/**
 * Problem 24: House Robber II (LC 213)
 * Description:
 * You are a professional robber planning to rob houses along a **circular street**. Each house has a certain amount of money stashed.
 *
 * Example:
 * Input: nums = [2,3,2]
 * Output: 3
 * Explanation: You cannot rob both house 1 and house 3 because they are adjacent.
 */
int robHelper(vector<int>& nums, int left, int right) {
    int prev1 = 0, prev2 = 0;
    for (int i = left; i <= right; ++i) {
        int temp = prev1;
        prev1 = max(prev1, prev2 + nums[i]);
        prev2 = temp;
    }
    return prev1;
}
int robCircular(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    return max(robHelper(nums, 0, nums.size() - 2), robHelper(nums, 1, nums.size() - 1));
}

/**
 * Problem 25: Wildcard Matching (LC 44)
 * Description:
 * Implement wildcard pattern matching with `?` (matches any single character) and `*` (matches any sequence).
 *
 * Example:
 * Input: s = "adceb", p = "*a*b"
 * Output: true
 */
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= n; ++j) {
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[m][n];
}

/**
 * Problem 26: Interleaving String (LC 97)
 * Description:
 * Given three strings `s1`, `s2`, and `s3`, return true if `s3` is formed by interleaving `s1` and `s2`.
 *
 * Example:
 * Input: s1 = "aab", s2 = "axy", s3 = "aaxaby"
 * Output: true
 */
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != s3.size()) return false;
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= m; ++i) dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
    for (int j = 1; j <= n; ++j) dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                       (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }
    return dp[m][n];
}

/**
 * Problem 27: Best Time to Buy and Sell Stock with Cooldown (LC 309)
 * Description:
 * You are given an array `stockPrices3` where `stockPrices3[i]` is the price of a stock on day `i`.
 * You may complete as many transactions as you like, but you must wait **one day cooldown** after selling.
 * 
 * Example:
 * Input: stockPrices3 = [1,2,3,0,2]
 * Output: 3
 * Explanation: Buy on day 1 (price = 1), sell on day 3 (price = 3), cooldown on day 4, buy on day 5 (price = 0), sell on day 6 (price = 2).
 */
int maxProfitCooldown(vector<int>& stockPrices3) {
    if (stockPrices3.empty()) return 0;
    int n = stockPrices3.size();
    vector<int> buy(n, 0), sell(n, 0), cooldown(n, 0);
    
    buy[0] = -stockPrices3[0];  // First day buy
    for (int i = 1; i < n; ++i) {
        buy[i] = max(buy[i - 1], cooldown[i - 1] - stockPrices3[i]); // Buy or do nothing
        sell[i] = max(sell[i - 1], buy[i - 1] + stockPrices3[i]); // Sell or do nothing
        cooldown[i] = max(cooldown[i - 1], sell[i - 1]); // Cooldown or do nothing
    }
    return sell[n - 1];
}

/**
 * Problem 28: Paint House (LC 256)
 * Description:
 * There are `houses` in a row, and each house can be painted with one of `three colors`: red, blue, or green.
 * The cost of painting each house with a certain color is different.
 * You have to **paint all houses** such that **no two adjacent houses have the same color**.
 * 
 * Example:
 * Input: costMatrix = [[17,2,17],[16,16,5],[14,3,19]]
 * Output: 10
 * Explanation: Paint house 0 as blue, house 1 as green, house 2 as blue.
 */
int minCost(vector<vector<int>>& costMatrix) {
    int n = costMatrix.size();
    vector<vector<int>> dp(n, vector<int>(3, 0));
    dp[0] = costMatrix[0]; // First house same as input

    for (int i = 1; i < n; ++i) {
        dp[i][0] = costMatrix[i][0] + min(dp[i - 1][1], dp[i - 1][2]); // Paint Red
        dp[i][1] = costMatrix[i][1] + min(dp[i - 1][0], dp[i - 1][2]); // Paint Blue
        dp[i][2] = costMatrix[i][2] + min(dp[i - 1][0], dp[i - 1][1]); // Paint Green
    }
    return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}

/**
 * Problem 29: Jump Game (LC 55)
 * Description:
 * Given an array `jumpNums` where `jumpNums[i]` represents the **maximum** jump length at that position,
 * return **true** if you can reach the last index.
 * 
 * Example:
 * Input: jumpNums = [2,3,1,1,4]
 * Output: true
 */
bool canJump(vector<int>& jumpNums) {
    int farthest = 0;
    for (int i = 0; i < jumpNums.size(); ++i) {
        if (i > farthest) return false; // Cannot reach this position
        farthest = max(farthest, i + jumpNums[i]);
    }
    return true;
}

/**
 * Problem 30: Jump Game II (LC 45)
 * Description:
 * Given an array `jumpNums2`, return the **minimum number of jumps** required to reach the last index.
 * 
 * Example:
 * Input: jumpNums2 = [2,3,1,1,4]
 * Output: 2
 * Explanation: Jump from index 0 to 1, then from 1 to 4.
 */
int jumpMinSteps(vector<int>& jumpNums2) {
    int jumps = 0, end = 0, farthest = 0;
    for (int i = 0; i < jumpNums2.size() - 1; ++i) {
        farthest = max(farthest, i + jumpNums2[i]);
        if (i == end) {
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}

int main() {
    // Test Problem 1: Climbing Stairs (LC 70)
    int n = 5;
    cout << "Climbing Stairs (n=" << n << "): " << climbStairs(n) << endl;

    // Test Problem 2: Maximum Subarray (LC 53)
    vector<int> maxSubArrayInput = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray: " << maxSubArray(maxSubArrayInput) << endl;

    // Test Problem 3: Unique Paths (LC 62)
    int m = 3, gridN = 7;
    cout << "Unique Paths (" << m << "x" << gridN << " grid): " << uniquePaths(m, gridN) << endl;

    // Test Problem 4: Coin Change (LC 322)
    vector<int> coinDenominations = {1, 2, 5};
    int coinAmount = 11;
    cout << "Coin Change (amount=" << coinAmount << "): " << coinChange(coinDenominations, coinAmount) << endl;

    // Test Problem 5: Longest Increasing Subsequence (LC 300)
    vector<int> lisInput = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Longest Increasing Subsequence: " << lengthOfLIS(lisInput) << endl;
    cout << "Longest Increasing Subsequence: " << lengthOfLISWithBinarySearch(lisInput) << endl;

    // Test Problem 6: Edit Distance (LC 72)
    string editWord1 = "horse", editWord2 = "ros";
    cout << "Edit Distance (" << editWord1 << " -> " << editWord2 << "): " << minDistance(editWord1, editWord2) << endl;

    // Test Problem 7: Partition Equal Subset Sum (LC 416)
    vector<int> partitionInput = {1, 5, 11, 5};
    cout << "Partition Equal Subset Sum: " << (canPartition(partitionInput) ? "True" : "False") << endl;

    // Test Problem 8: House Robber (LC 198)
    vector<int> houseRobberInput = {2, 7, 9, 3, 1};
    cout << "House Robber: " << rob(houseRobberInput) << endl;

    // Test Problem 9: Decode Ways (LC 91)
    string decodeInput = "226";
    cout << "Decode Ways (" << decodeInput << "): " << numDecodings(decodeInput) << endl;

    // Test Problem 10: Triangle Minimum Path Sum (LC 120)
    vector<vector<int>> triangleInput = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << "Triangle Minimum Path Sum: " << minimumTotal(triangleInput) << endl;

    // Test Problem 11: Longest Palindromic Subsequence (LC 516)
    string palindromeInput = "bbbab";
    cout << "Longest Palindromic Subsequence: " << longestPalindromeSubseq(palindromeInput) << endl;

    // Test Problem 12: Burst Balloons (LC 312)
    vector<int> balloonsInput = {3, 1, 5, 8};
    cout << "Burst Balloons: " << maxCoins(balloonsInput) << endl;

    // Test Problem 13: Longest Continuous Increasing Subsequence (LC 674)
    vector<int> lcisInput = {1, 3, 5, 4, 7};
    cout << "Longest Continuous Increasing Subsequence: " << findLengthOfLCIS(lcisInput) << endl;
    cout << "Longest Continuous Increasing Subsequence: " << findLengthOfLCIS_DP(lcisInput) << endl;

    // Test Problem 14: Maximum Length of Repeated Subarray (LC 718)
    vector<int> pro14Nums1 = {1, 2, 3, 2, 1};
    vector<int> pro14Nums2 = {3, 2, 1, 4, 7};
    cout << "Maximum Length of Repeated Subarray (DP): " << findLengthDP(pro14Nums1, pro14Nums2) << endl;

    // Test Problem 15: Distinct Subsequences(lc115)
    string s = "rabbbit", t = "rabbit";
    cout << "Distinct Subsequences (DP 2D): " << numDistinctDP(s, t) << endl;
    cout << "Distinct Subsequences (DP Optimized): " << numDistinctOptimized(s, t) << endl;

    // Test Problem 16: Distinct Subsequences(lc1143)
    string text1 = "abcde", text2 = "ace";
    cout << "Longest Common Subsequence (DP 2D): "
         << longestCommonSubsequenceDP(text1, text2) << endl;
    cout << "Longest Common Subsequence (Optimized DP): "
         << longestCommonSubsequenceOptimized(text1, text2) << endl;

    // Test Problem 17: Longest Palindromic Substring (LC 5)
    string lc5_input = "babad";
    cout << "Longest Palindromic Substring (LC 5): " << longestPalindrome(lc5_input) << endl; // Output: "bab" or "aba"

    // Test Problem 18: Palindromic Substrings (LC 647)
    string lc647_input = "aaa";
    cout << "Number of Palindromic Substrings (LC 647): " << countSubstrings(lc647_input) << endl; // Output: 6

    // Test Problem 19: Minimum Falling Path Sum (LC 931)
    vector<vector<int>> lc931_matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << "Minimum Falling Path Sum (LC 931): " << minFallingPathSum(lc931_matrix) << endl; // Output: 13

    // Test Problem 20: Ugly Number II (LC 264)
    int lc264_n = 10;
    cout << "10th Ugly Number (LC 264): " << nthUglyNumber(lc264_n) << endl; // Output: 12

    // Test Problem 21: Maximum Product Subarray (LC 152)
    vector<int> lc152_nums = {2, 3, -2, 4};
    cout << "Maximum Product Subarray (LC 152): " << maxProduct(lc152_nums) << endl; // Output: 6

    // Test Problem 22: Best Time to Buy and Sell Stock
    vector<int> stockPrices1 = {7,1,5,3,6,4};
    cout << "Max Profit (Single Transaction): " << maxProfit(stockPrices1) << endl;

    // Test Problem 23: Best Time to Buy and Sell Stock II
    vector<int> stockPrices2 = {7,1,5,3,6,4};
    cout << "Max Profit (Multiple Transactions): " << maxProfitMultiple(stockPrices2) << endl;

    // Test Problem 24: House Robber II
    vector<int> houses = {2,3,2};
    cout << "Max Robbery Amount (Circular Street): " << robCircular(houses) << endl;

    // Test Problem 25: Wildcard Matching
    string wildcardStr = "adceb", wildcardPattern = "*a*b";
    cout << "Wildcard Matching: " << (isMatch(wildcardStr, wildcardPattern) ? "true" : "false") << endl;

    // Test Problem 26: Interleaving String
    string str1 = "aab", str2 = "axy", interleavedStr = "aaxaby";
    cout << "Is Interleaving: " << (isInterleave(str1, str2, interleavedStr) ? "true" : "false") << endl;

    // Test Problem 27: Best Time to Buy and Sell Stock with Cooldown
    vector<int> stockPrices3 = {1,2,3,0,2};
    cout << "Max Profit with Cooldown: " << maxProfitCooldown(stockPrices3) << endl;

    // Test Problem 28: Paint House
    vector<vector<int>> costMatrix = {{17,2,17},{16,16,5},{14,3,19}};
    cout << "Minimum Cost to Paint Houses: " << minCost(costMatrix) << endl;

    // Test Problem 29: Jump Game
    vector<int> jumpNums = {2,3,1,1,4};
    cout << "Can Jump to Last Index: " << (canJump(jumpNums) ? "true" : "false") << endl;

    // Test Problem 30: Jump Game II
    vector<int> jumpNums2 = {2,3,1,1,4};
    cout << "Minimum Jumps to Reach End: " << jumpMinSteps(jumpNums2) << endl;

    return 0;
}
