#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <numeric>
#include <cstdint>
using namespace std;

/**
 * Problem 1: Climbing Stairs (LC 70)
 * Description: You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * Example:
 * Input: n = 5
 * Output: 8
 */
int ClimbStairs(int n) {
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
int MaxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size(), 0); // dp[i] represents the maximum subarray sum ending at index i
    dp[0] = nums[0];
    int max_sum = dp[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        max_sum = max(max_sum, dp[i]);
    }
    return max_sum;
}
/*
Problem: Maximum Subarray (LC 53)
---------------------------------
Given an integer array `nums`, find the contiguous subarray (containing at least one number)
which has the largest sum and return its sum.

We use a 1D dp array where:
- dp[i] represents the maximum subarray sum ending at index i.

Transition:
- dp[i] = max(nums[i], dp[i-1] + nums[i])
    --> Either start a new subarray at i, or extend the previous subarray.

We track the global maximum during the loop.

Time: O(n), Space: O(n)
*/

/**
 * Problem 3: Unique Paths (LC 62)
 * Description: A robot is located at the top-left corner of a m x n grid.
 * The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner. How many possible unique paths are there?
 * Example:
 * Input: m = 3, n = 7
 * Output: 28
 */
int UniquePaths(int m, int n) {
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
/*
Problem: Unique Paths (LC 62)
-----------------------------
A robot is located at the top-left corner of an m x n grid.
It can only move either down or right at any point in time.
How many unique paths are there to reach the bottom-right corner?

We define:
- dp[i][j] = number of unique paths to reach cell (i, j)

Initialization:
- dp[0][j] = 1 for all j (only one way to reach the top row: move right)
- dp[i][0] = 1 for all i (only one way to reach the first column: move down)

Transition:
- dp[i][j] = dp[i-1][j] + dp[i][j-1]
    --> From top cell and left cell

Return dp[m-1][n-1] as the final result.

Time: O(m * n), Space: O(m * n)
*/

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
int CoinChange(vector<int>& coins, int amount) {
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
/*
Problem: Coin Change (LC 322)
-----------------------------
You are given an integer array `coins` representing different denominations and
an integer `amount` representing a total amount of money.

Return the fewest number of coins needed to make up that amount.
If that amount cannot be made up by any combination of the coins, return -1.

We define:
- dp[i]: the minimum number of coins needed to make up amount i

Initialization:
- dp[0] = 0 (0 coins to make amount 0)
- All other dp[i] initialized as INT_MAX (unreachable)

Transition:
- For each coin:
    - For each i from coin to amount:
        - if dp[i - coin] is reachable, update dp[i] = min(dp[i], dp[i - coin] + 1)

Return:
- dp[amount] if it's reachable, otherwise -1

Time: O(amount * n), where n is the number of coin denominations
Space: O(amount)
*/

/**
 * Problem 5: Longest Increasing Subsequence (LC 300)
 * Description: Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * Example:
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The LIS is [2,3,7,101], therefore the length is 4.
 */
int LengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1); // dp[i] represents the length of the LIS ending at index i
    int max_len = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}
/*
Problem: Longest Increasing Subsequence (LC 300)
-----------------------------------------------
Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

We define:
- dp[i]: the length of the longest increasing subsequence ending at index i

Initialization:
- All dp[i] = 1 (Each element is a subsequence of length 1)

Transition:
- For each i from 1 to n-1:
    - For each j from 0 to i-1:
        - If nums[i] > nums[j], dp[i] = max(dp[i], dp[j] + 1)

Track the maximum dp[i] during iteration to get the answer.

Time: O(n^2), Space: O(n)
*/

// Custom binary search to find the first element >= target
int BinarySearch(const vector<int>& arr, int target) {
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
int LengthOfLISWithBinarySearch(vector<int>& nums) {
    vector<int> res; // Auxiliary array to maintain the LIS
    for (int num : nums) {
        if (res.empty() || res.back() < num) {
            res.push_back(num);
        }
        else {
            int idx = BinarySearch(res, num);
            res[idx] = num;
        }
    }
    return res.size(); // The length of dp is the length of the LIS
}
/*
Problem: Longest Increasing Subsequence (LC 300)
-----------------------------------------------
Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

Optimized Approach using Binary Search:
We use an auxiliary array `res` where:
- res[i] holds the smallest possible tail value of an increasing subsequence of length i + 1

For each number in `nums`:
- If num > last element in `res`, extend the subsequence and append num
- Otherwise, find the first element in `res` >= num using binary search and replace it

Binary search ensures that:
- `res` is always sorted
- We maintain the minimum possible values for each length

Note: The array `res` does **not** represent the actual subsequence,
but its length is equal to the LIS length.

Time: O(n log n), Space: O(n)
*/

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
int MinDistance(string word1, string word2) {
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
/*
Problem: Edit Distance (LC 72)
------------------------------
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
Allowed operations are insert, delete, or replace a character.

We define:
- dp[i][j]: the edit distance between word1[0..i-1] and word2[0..j-1]

Base cases:
- dp[i][0] = i: delete all characters from word1
- dp[0][j] = j: insert all characters to form word2

Transition:
- If word1[i-1] == word2[j-1], then dp[i][j] = dp[i-1][j-1]
- Else: dp[i][j] = 1 + min(
    dp[i-1][j]    // delete
    dp[i][j-1]    // insert
    dp[i-1][j-1]  // replace
  )

Time: O(m * n), Space: O(m * n)
*/

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
bool CanPartition(vector<int>& nums) {
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
int Rob(vector<int>& nums) {
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
/*
Problem: Partition Equal Subset Sum (LC 416)
--------------------------------------------
Given a non-empty array nums containing only positive integers,
determine if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Observation:
- This is equivalent to finding if there's a subset that sums to sum / 2

We define:
- dp[j]: whether a subset sum of j is possible

Initialization:
- dp[0] = true (empty subset)

Transition:
- For each number:
    - Traverse from target to num (in reverse to avoid reuse)
    - dp[j] = dp[j] || dp[j - num]

Return dp[target] to indicate whether such subset exists.

Time: O(n * sum), Space: O(sum)
*/

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
int NumDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = s[0] != '0' ? 1 : 0;

    for (int i = 2; i <= n; ++i) {
        if (s[i - 1] != '0') dp[i] += dp[i - 1];
        int two_digit = stoi(s.substr(i - 2, 2));
        if (two_digit >= 10 && two_digit <= 26) dp[i] += dp[i - 2];
    }
    return dp[n];
}
/*
Problem: House Robber (LC 198)
------------------------------
You are a professional robber planning to rob houses along a street.
Each house has some amount of money, but adjacent houses cannot be robbed.

We optimize with rolling variables:
- prev1: maximum profit including house i-1
- prev2: maximum profit including house i-2

For each house:
- Either rob it (prev2 + num) or skip it (prev1)
- Update rolling states accordingly

Time: O(n), Space: O(1)
*/

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
int MinimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle.back();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
        }
    }
    return dp[0];
}
/*
Problem: Triangle Minimum Path Sum (LC 120)
------------------------------------------
Given a triangle array, return the minimum path sum from top to bottom.
At each step, you may move to adjacent numbers on the row below.

We define:
- dp[j]: the minimum path sum starting from row i+1 at column j

Bottom-up DP:
- Start from the second-to-last row and update dp[j] = triangle[i][j] + min(dp[j], dp[j+1])

This uses only O(n) space (1D array), in-place updating

Time: O(n^2), Space: O(n)
*/

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
int LongestPalindromeSubseq(string s) {
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
/*
Problem: Longest Palindromic Subsequence (LC 516)
------------------------------------------------
Given a string `s`, return the length of the longest palindromic subsequence in `s`.

We define:
- dp[i][j]: the length of the longest palindromic subsequence in s[i..j]

Base case:
- dp[i][i] = 1 (single character is a palindrome)

Transition:
- if s[i] == s[j], dp[i][j] = dp[i+1][j-1] + 2
- else dp[i][j] = max(dp[i+1][j], dp[i][j-1])

Process in reverse i (from n-1 to 0), and j > i

Time: O(n^2), Space: O(n^2)
*/

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
int MaxCoins(vector<int>& nums) {
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
/*
Problem: Burst Balloons (LC 312)
-------------------------------
You are given `n` balloons, each balloon has a number.
Each time you burst a balloon `i`, you gain coins = nums[left] * nums[i] * nums[right]
You can burst balloons in any order.

We define:
- dp[left][right]: the max coins we can get by bursting balloons in (left, right) (exclusive)

Padding:
- Add 1 at both ends: balloons = [1] + nums + [1] for easier handling of boundaries

Transition:
- For each length of interval, for each [left, right], try all `k` in (left, right):
    dp[left][right] = max(dp[left][right],
                          dp[left][k - 1] + dp[k + 1][right] +
                          balloons[left - 1] * balloons[k] * balloons[right + 1])

Return dp[1][n] (excluding the padded edges)

Time: O(n^3), Space: O(n^2)
*/

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
int FindLengthOfLCIS(vector<int>& nums) {
    if (nums.empty()) return 0;

    int max_len = 1; // To track the maximum length of LCIS
    int current_len = 1; // To track the length of the current LCIS

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i - 1]) {
            current_len++; // Extend the current LCIS
        } else {
            current_len = 1; // Reset the length when the sequence breaks
        }
        max_len = max(max_len, current_len); // Update the maximum length
    }

    return max_len;
}
// dp is easy understanding
int FindLengthOfLCIS_DP(vector<int>& nums) {
    if (nums.empty()) return 0;

    int max_len = 1;
    vector<int> dp(nums.size(), 1);
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1]) dp[i] = dp[i - 1] + 1;
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}
/*
Problem: Longest Continuous Increasing Subsequence (LC 674)
-----------------------------------------------------------
Given an unsorted array of integers, return the length of the longest 
continuous increasing subsequence (i.e., strictly increasing and contiguous).

We define:
- dp[i]: the length of the LCIS ending at index i

Transition:
- If nums[i] > nums[i-1], dp[i] = dp[i-1] + 1
- Else dp[i] = 1 (start new sequence)

Track the maximum dp[i] during iteration.

Time: O(n), Space: O(n)
*/

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
int FindLengthDP(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // DP table
    int max_len = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Extend the subarray
                max_len = max(max_len, dp[i][j]); // Update maximum length
            }
        }
    }
    return max_len;
}
/*
Problem: Maximum Length of Repeated Subarray (LC 718)
-----------------------------------------------------
Given two integer arrays `nums1` and `nums2`, return the length of the maximum 
length of a subarray that appears in both arrays.

We define:
- dp[i][j]: the length of the common subarray ending at nums1[i-1] and nums2[j-1]

Transition:
- If nums1[i-1] == nums2[j-1], dp[i][j] = dp[i-1][j-1] + 1
- Else dp[i][j] = 0 (discontinuity)

Track max(dp[i][j]) during iteration.

Time: O(m * n), Space: O(m * n)
*/

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
int NumDistinctDP(string s, string t) {
    vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1, 0));
    // Initialize base cases
    for (size_t i = 0; i <= s.size(); i++) dp[i][0] = 1; // Empty t is a subsequence of any s

    // Fill DP table
    for (size_t i = 1; i <= s.size(); i++) {
        for (size_t j = 1; j <= t.size(); j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // Match or skip
            } else {
                dp[i][j] = dp[i - 1][j]; // Skip s[i-1]
            }
        }
    }
    return dp[s.size()][t.size()];
}
/*
Problem: Distinct Subsequences (LC 115)
---------------------------------------
Given strings `s` and `t`, return the number of distinct subsequences of `s` 
which equals `t`.

We define:
- dp[i][j]: number of distinct subsequences of s[0..i-1] which equals t[0..j-1]

Initialization:
- dp[i][0] = 1 (empty t is subsequence of any s prefix)
- dp[0][j>0] = 0 (non-empty t can't be matched from empty s)

Transition:
- if s[i-1] == t[j-1]:
    dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
- else:
    dp[i][j] = dp[i-1][j]

Time: O(m * n), Space: O(m * n)
*/

/* Optimized Dynamic Programming Solution (1D Array) */
int NumDistinctOptimized(string s, string t) {
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
/*
Problem: Distinct Subsequences (LC 115)
---------------------------------------
This is a space optimized version of the 2D DP.

We define:
- dp[j]: number of distinct subsequences of s[0..i-1] that match t[0..j-1]

Because dp[i][j] only depends on dp[i-1][j] and dp[i-1][j-1], 
we can safely update from right to left in 1D array.

Initialization:
- dp[0] = 1 (empty t is subsequence of any s)

Update from right to left for correctness.

Time: O(m * n), Space: O(n)
*/

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
int LongestCommonSubsequenceDP(string text1, string text2) {
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
/*
Problem: Longest Common Subsequence (LC 1143)
--------------------------------------------
Given two strings `text1` and `text2`, return the length of their longest common subsequence.

We define:
- dp[i][j]: length of LCS between text1[0..i-1] and text2[0..j-1]

Transition:
- If text1[i-1] == text2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Time: O(m * n), Space: O(m * n)
*/

/* Optimized Dynamic Programming Solution (1D Rolling Array) */
int LongestCommonSubsequenceOptimized(string text1, string text2) {
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
/*
Problem: Longest Common Subsequence (LC 1143)
--------------------------------------------
This is a space-optimized version of the standard 2D LCS.

Rolling optimization:
- Use 1D array + `prev` to simulate row transition

Time: O(m * n), Space: O(n)
*/

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
string LongestPalindrome(string s) {
    if (s.length() <= 1) {
        return s;
    }

    int max_len = 1;
    int start = 0;
    int end = 0;
    std::vector<std::vector<bool>> dp(s.length(), std::vector<bool>(s.length(), false));

    for (size_t i = 0; i < s.length(); ++i) {
        dp[i][i] = true;
        for (size_t j = 0; j < i; ++j) {
            if (s[j] == s[i] && (i - j <= 2 || dp[j + 1][i - 1])) {
                dp[j][i] = true;
                if (static_cast<int>(i) - static_cast<int>(j) + 1 > max_len) {
                    max_len = i - j + 1;
                    start = j;
                    end = i;
                }
            }
        }
    }

    return s.substr(start, end - start + 1);
}
/*
Problem: Longest Palindromic Substring (LC 5)
--------------------------------------------
Find the longest palindromic substring in a given string `s`.

We define:
- dp[i][j]: whether s[i..j] is a palindrome

Transition:
- s[i] == s[j] and (j - i <= 2 or dp[i+1][j-1]) → then dp[i][j] = true

Track the longest (j - i + 1) and update (start, end)

Time: O(n^2), Space: O(n^2)
*/

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
int CountSubstrings(string s) {
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
/*
Problem: Palindromic Substrings (LC 647)
----------------------------------------
Count the number of palindromic substrings in the string `s`.

We define:
- dp[i][j]: whether s[i..j] is a palindrome

Transition:
- s[i] == s[j] and (j - i < 2 || dp[i+1][j-1]) → dp[i][j] = true

Count every valid palindrome during iteration.

Time: O(n^2), Space: O(n^2)
*/

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
int MinFallingPathSum(vector<vector<int>>& matrix) {
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
/*
Problem: Minimum Falling Path Sum (LC 931)
------------------------------------------
Given an n x n integer matrix, return the minimum sum of a falling path.

A falling path moves from top to bottom choosing one element from each row,
and next row's column must be the same or adjacent (j, j-1, j+1)

We define:
- dp[j]: min falling path sum to reach column j of current row

Transition:
- curr[j] = matrix[i][j] + min(dp[j], dp[j-1], dp[j+1])

Use 1D space by rolling update of rows.

Time: O(n^2), Space: O(n)
*/

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
int NthUglyNumber(int n) {
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
/*
Problem: Ugly Number II (LC 264)
--------------------------------
Find the n-th ugly number. Ugly numbers are positive integers whose prime factors only include 2, 3, or 5.

Approach:
- Use a dynamic programming array `dp` to store the first n ugly numbers.
- Maintain three indices i2, i3, i5 to track the position of the last multiple of 2, 3, and 5.
- At each step, compute next candidates and select the smallest one as the next ugly number.
- Move the corresponding pointer(s) forward if used.

Time Complexity: O(n)
Space Complexity: O(n)
*/

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
int MaxProduct(vector<int>& nums) {
    int n = nums.size(), max_prod = nums[0], min_prod = nums[0], result = nums[0];
    for (int i = 1; i < n; ++i) {
        if (nums[i] < 0) swap(max_prod, min_prod);
        max_prod = max(nums[i], max_prod * nums[i]);
        min_prod = min(nums[i], min_prod * nums[i]);
        result = max(result, max_prod);
    }
    return result;
}
/*
Problem: Maximum Product Subarray (LC 152)
------------------------------------------
Find the contiguous subarray within an integer array that has the largest product.

Approach:
- Use dynamic programming to track both maximum and minimum product at each index,
  because a negative number could become the maximum when multiplied by another negative.
- Swap max and min when current number is negative.

State:
- max_prod: max product ending at current index
- min_prod: min product ending at current index

Transition:
- max_prod = max(nums[i], max_prod * nums[i])
- min_prod = min(nums[i], min_prod * nums[i])

Time Complexity: O(n)
Space Complexity: O(1)
*/

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
int MaxProfit(vector<int>& prices) {
    int min_price = INT_MAX, max_profit = 0;
    for (int price : prices) {
        min_price = min(min_price, price);
        max_profit = max(max_profit, price - min_price);
    }
    return max_profit;
}
/*
Problem: Best Time to Buy and Sell Stock I (LC 121)
---------------------------------------------------
You are given an array of prices, where prices[i] is the price of a stock on day i.
Return the maximum profit you can achieve from a single buy and sell.

Approach:
- Track the minimum price seen so far.
- At each step, update the maximum profit as the difference between current price and min_price.

Time Complexity: O(n)
Space Complexity: O(1)
*/

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
int MaxProfitMultiple(vector<int>& prices) {
    int profit = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    return profit;
}
/*
Problem: Best Time to Buy and Sell Stock II (LC 122)
----------------------------------------------------
You may complete as many transactions as you like (buy-sell), but cannot hold multiple stocks.

Approach:
- Greedy strategy: accumulate profit whenever there is an increase in price.

Time Complexity: O(n)
Space Complexity: O(1)
*/

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
int RobHelper(vector<int>& nums, int left, int right) {
    int prev1 = 0, prev2 = 0;
    for (int i = left; i <= right; ++i) {
        int temp = prev1;
        prev1 = max(prev1, prev2 + nums[i]);
        prev2 = temp;
    }
    return prev1;
}
int RobCircular(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    return max(RobHelper(nums, 0, nums.size() - 2), RobHelper(nums, 1, nums.size() - 1));
}
/*
Problem: House Robber II (LC 213)
---------------------------------
You cannot rob adjacent houses, and houses are arranged in a circle (first and last are adjacent).

Approach:
- Convert into two linear robbing problems:
  1. Rob from house 0 to n-2
  2. Rob from house 1 to n-1
- Return the maximum of the two results.

Time Complexity: O(n)
Space Complexity: O(1)
*/

/**
 * Problem 25: Wildcard Matching (LC 44)
 * Description:
 * Implement wildcard pattern matching with `?` (matches any single character) and `*` (matches any sequence).
 *
 * Example:
 * Input: s = "adceb", p = "*a*b"
 * Output: true
 */
bool IsMatch(string s, string p) {
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
/*
Problem: Wildcard Matching (LC 44)
----------------------------------
Implement wildcard pattern matching with support for '?' and '*'.

Definitions:
- '?' matches any single character
- '*' matches any sequence (including empty)

DP Definition:
- dp[i][j]: whether s[0..i-1] matches p[0..j-1]

Transition:
- If p[j-1] == '*': dp[i][j] = dp[i][j-1] || dp[i-1][j]
- If p[j-1] == '?' or s[i-1] == p[j-1]: dp[i][j] = dp[i-1][j-1]

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/

/**
 * Problem 26: Interleaving String (LC 97)
 * Description:
 * Given three strings `s1`, `s2`, and `s3`, return true if `s3` is formed by interleaving `s1` and `s2`.
 *
 * Example:
 * Input: s1 = "aab", s2 = "axy", s3 = "aaxaby"
 * Output: true
 */
bool IsInterleave(string s1, string s2, string s3) {
    size_t m = s1.size(), n = s2.size();
    if (m + n != s3.size()) return false;
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (size_t i = 1; i <= m; ++i) dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
    for (size_t j = 1; j <= n; ++j) dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                       (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }
    return dp[m][n];
}
/*
Problem: Interleaving String (LC 97)
------------------------------------
Given s1, s2, and s3, check if s3 is formed by an interleaving of s1 and s2.

DP Definition:
- dp[i][j]: whether s1[0..i-1] and s2[0..j-1] can form s3[0..i+j-1]

Transition:
- dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
             (dp[i][j-1] && s2[j-1] == s3[i+j-1])

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/

/**
 * Problem 27: Best Time to Buy and Sell Stock with Cooldown (LC 309)
 * Description:
 * You are given an array `stock_prices3` where `stock_prices3[i]` is the price of a stock on day `i`.
 * You may complete as many transactions as you like, but you must wait **one day cooldown** after selling.
 * 
 * Example:
 * Input: stock_prices3 = [1,2,3,0,2]
 * Output: 3
 * Explanation: Buy on day 1 (price = 1), sell on day 3 (price = 3), cooldown on day 4, buy on day 5 (price = 0), sell on day 6 (price = 2).
 */
int MaxProfitCooldown(vector<int>& stock_prices3) {
    if (stock_prices3.empty()) return 0;
    int n = stock_prices3.size();
    vector<int> buy(n, 0), sell(n, 0), cooldown(n, 0);
    
    buy[0] = -stock_prices3[0];  // First day buy
    for (int i = 1; i < n; ++i) {
        buy[i] = max(buy[i - 1], cooldown[i - 1] - stock_prices3[i]); // Buy or do nothing
        sell[i] = max(sell[i - 1], buy[i - 1] + stock_prices3[i]); // Sell or do nothing
        cooldown[i] = max(cooldown[i - 1], sell[i - 1]); // Cooldown or do nothing
    }
    return sell[n - 1];
}
/*
Problem: Best Time to Buy and Sell Stock with Cooldown (LC 309)
----------------------------------------------------------------
After selling a stock, you cannot buy on the next day (cooldown of 1 day).

States:
- buy[i]: max profit if we buy on day i
- sell[i]: max profit if we sell on day i
- cooldown[i]: max profit if we rest on day i

Transitions:
- buy[i] = max(buy[i-1], cooldown[i-1] - prices[i])
- sell[i] = max(sell[i-1], buy[i-1] + prices[i])
- cooldown[i] = max(cooldown[i-1], sell[i-1])

Time Complexity: O(n)
Space Complexity: O(n)
*/

/**
 * Problem 28: Paint House (LC 256)
 * Description:
 * There are `houses` in a row, and each house can be painted with one of `three colors`: red, blue, or green.
 * The cost of painting each house with a certain color is different.
 * You have to **paint all houses** such that **no two adjacent houses have the same color**.
 * 
 * Example:
 * Input: cost_matrix = [[17,2,17],[16,16,5],[14,3,19]]
 * Output: 10
 * Explanation: Paint house 0 as blue, house 1 as green, house 2 as blue.
 */
int MinCost(vector<vector<int>>& cost_matrix) {
    int n = cost_matrix.size();
    vector<vector<int>> dp(n, vector<int>(3, 0));
    dp[0] = cost_matrix[0]; // First house same as input

    for (int i = 1; i < n; ++i) {
        dp[i][0] = cost_matrix[i][0] + min(dp[i - 1][1], dp[i - 1][2]); // Paint Red
        dp[i][1] = cost_matrix[i][1] + min(dp[i - 1][0], dp[i - 1][2]); // Paint Blue
        dp[i][2] = cost_matrix[i][2] + min(dp[i - 1][0], dp[i - 1][1]); // Paint Green
    }
    return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}
/*
Problem: Paint House (LC 256)
-----------------------------
Each house can be painted in red, blue, or green.
No two adjacent houses can have the same color.

DP Definition:
- dp[i][c]: min cost to paint up to house i, with color c

Transition:
- dp[i][0] = cost[i][0] + min(dp[i-1][1], dp[i-1][2]) // red
- dp[i][1] = cost[i][1] + min(dp[i-1][0], dp[i-1][2]) // blue
- dp[i][2] = cost[i][2] + min(dp[i-1][0], dp[i-1][1]) // green

Time Complexity: O(n)
Space Complexity: O(n)
*/

/**
 * Problem 29: Jump Game (LC 55)
 * Description:
 * Given an array `jump_nums` where `jump_nums[i]` represents the **maximum** jump length at that position,
 * return **true** if you can reach the last index.
 * 
 * Example:
 * Input: jump_nums = [2,3,1,1,4]
 * Output: true
 */
bool CanJump(vector<int>& jump_nums) {
    int farthest = 0;
    for (size_t i = 0; i < jump_nums.size(); ++i) {
        if (static_cast<int>(i) > farthest) return false; // Cannot reach this position
        farthest = max(farthest, static_cast<int>(i) + jump_nums[i]);
    }
    return true;
}
/*
Problem: Jump Game (LC 55)
--------------------------
Given an array where each element represents your max jump length,
determine if you can reach the last index.

Approach:
- Greedily track the farthest reachable index.

Condition:
- If at any index i > farthest, return false.

Time Complexity: O(n)
Space Complexity: O(1)
*/

/**
 * Problem 30: Jump Game II (LC 45)
 * Description:
 * Given an array `jump_nums2`, return the **minimum number of jumps** required to reach the last index.
 * 
 * Example:
 * Input: jump_nums2 = [2,3,1,1,4]
 * Output: 2
 * Explanation: Jump from index 0 to 1, then from 1 to 4.
 */
int JumpMinSteps(vector<int>& jump_nums2) {
    int jumps = 0, end = 0, farthest = 0;
    for (size_t i = 0; i < jump_nums2.size() - 1; ++i) {
        farthest = max(farthest, static_cast<int>(i) + jump_nums2[i]);
        if (static_cast<int>(i) == end) {
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}
/*
Problem: Jump Game II (LC 45)
-----------------------------
Find the minimum number of jumps to reach the last index.

Approach:
- Track current jump range [start, end]
- When i == end, we increase jump count and move to the next range

Time Complexity: O(n)
Space Complexity: O(1)
*/

int main() {
    // Test Problem 1: Climbing Stairs (LC 70)
    int n = 5;
    cout << "Climbing Stairs (n=" << n << "): " << ClimbStairs(n) << endl;

    // Test Problem 2: Maximum Subarray (LC 53)
    vector<int> max_sub_array_input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray: " << MaxSubArray(max_sub_array_input) << endl;

    // Test Problem 3: Unique Paths (LC 62)
    int m = 3, grid_n = 7;
    cout << "Unique Paths (" << m << "x" << grid_n << " grid): " << UniquePaths(m, grid_n) << endl;

    // Test Problem 4: Coin Change (LC 322)
    vector<int> coin_denominations = {1, 2, 5};
    int coin_amount = 11;
    cout << "Coin Change (amount=" << coin_amount << "): " << CoinChange(coin_denominations, coin_amount) << endl;

    // Test Problem 5: Longest Increasing Subsequence (LC 300)
    vector<int> lis_input = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Longest Increasing Subsequence: " << LengthOfLIS(lis_input) << endl;
    cout << "Longest Increasing Subsequence: " << LengthOfLISWithBinarySearch(lis_input) << endl;

    // Test Problem 6: Edit Distance (LC 72)
    string edit_word1 = "horse", edit_word2 = "ros";
    cout << "Edit Distance (" << edit_word1 << " -> " << edit_word2 << "): " << MinDistance(edit_word1, edit_word2) << endl;

    // Test Problem 7: Partition Equal Subset Sum (LC 416)
    vector<int> partition_input = {1, 5, 11, 5};
    cout << "Partition Equal Subset Sum: " << (CanPartition(partition_input) ? "True" : "False") << endl;

    // Test Problem 8: House Robber (LC 198)
    vector<int> house_robber_input = {2, 7, 9, 3, 1};
    cout << "House Robber: " << Rob(house_robber_input) << endl;

    // Test Problem 9: Decode Ways (LC 91)
    string decode_input = "226";
    cout << "Decode Ways (" << decode_input << "): " << NumDecodings(decode_input) << endl;

    // Test Problem 10: Triangle Minimum Path Sum (LC 120)
    vector<vector<int>> triangle_input = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << "Triangle Minimum Path Sum: " << MinimumTotal(triangle_input) << endl;

    // Test Problem 11: Longest Palindromic Subsequence (LC 516)
    string palindrome_input = "bbbab";
    cout << "Longest Palindromic Subsequence: " << LongestPalindromeSubseq(palindrome_input) << endl;

    // Test Problem 12: Burst Balloons (LC 312)
    vector<int> balloons_input = {3, 1, 5, 8};
    cout << "Burst Balloons: " << MaxCoins(balloons_input) << endl;

    // Test Problem 13: Longest Continuous Increasing Subsequence (LC 674)
    vector<int> lcis_input = {1, 3, 5, 4, 7};
    cout << "Longest Continuous Increasing Subsequence: " << FindLengthOfLCIS(lcis_input) << endl;
    cout << "Longest Continuous Increasing Subsequence: " << FindLengthOfLCIS_DP(lcis_input) << endl;

    // Test Problem 14: Maximum Length of Repeated Subarray (LC 718)
    vector<int> pro14_nums1 = {1, 2, 3, 2, 1};
    vector<int> pro14_nums2 = {3, 2, 1, 4, 7};
    cout << "Maximum Length of Repeated Subarray (DP): " << FindLengthDP(pro14_nums1, pro14_nums2) << endl;

    // Test Problem 15: Distinct Subsequences(lc115)
    string s = "rabbbit", t = "rabbit";
    cout << "Distinct Subsequences (DP 2D): " << NumDistinctDP(s, t) << endl;
    cout << "Distinct Subsequences (DP Optimized): " << NumDistinctOptimized(s, t) << endl;

    // Test Problem 16: Distinct Subsequences(lc1143)
    string text1 = "abcde", text2 = "ace";
    cout << "Longest Common Subsequence (DP 2D): "
         << LongestCommonSubsequenceDP(text1, text2) << endl;
    cout << "Longest Common Subsequence (Optimized DP): "
         << LongestCommonSubsequenceOptimized(text1, text2) << endl;

    // Test Problem 17: Longest Palindromic Substring (LC 5)
    string lc5_input = "babad";
    cout << "Longest Palindromic Substring (LC 5): " << LongestPalindrome(lc5_input) << endl; // Output: "bab" or "aba"

    // Test Problem 18: Palindromic Substrings (LC 647)
    string lc647_input = "aaa";
    cout << "Number of Palindromic Substrings (LC 647): " << CountSubstrings(lc647_input) << endl; // Output: 6

    // Test Problem 19: Minimum Falling Path Sum (LC 931)
    vector<vector<int>> lc931_matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << "Minimum Falling Path Sum (LC 931): " << MinFallingPathSum(lc931_matrix) << endl; // Output: 13

    // Test Problem 20: Ugly Number II (LC 264)
    int lc264_n = 10;
    cout << "10th Ugly Number (LC 264): " << NthUglyNumber(lc264_n) << endl; // Output: 12

    // Test Problem 21: Maximum Product Subarray (LC 152)
    vector<int> lc152_nums = {2, 3, -2, 4};
    cout << "Maximum Product Subarray (LC 152): " << MaxProduct(lc152_nums) << endl; // Output: 6

    // Test Problem 22: Best Time to Buy and Sell Stock
    vector<int> stock_prices1 = {7,1,5,3,6,4};
    cout << "Max Profit (Single Transaction): " << MaxProfit(stock_prices1) << endl;

    // Test Problem 23: Best Time to Buy and Sell Stock II
    vector<int> stock_prices2 = {7,1,5,3,6,4};
    cout << "Max Profit (Multiple Transactions): " << MaxProfitMultiple(stock_prices2) << endl;

    // Test Problem 24: House Robber II
    vector<int> houses = {2,3,2};
    cout << "Max Robbery Amount (Circular Street): " << RobCircular(houses) << endl;

    // Test Problem 25: Wildcard Matching
    string wildcard_str = "adceb", wildcard_pattern = "*a*b";
    cout << "Wildcard Matching: " << (IsMatch(wildcard_str, wildcard_pattern) ? "true" : "false") << endl;

    // Test Problem 26: Interleaving String
    string str1 = "aab", str2 = "axy", interleaved_str = "aaxaby";
    cout << "Is Interleaving: " << (IsInterleave(str1, str2, interleaved_str) ? "true" : "false") << endl;

    // Test Problem 27: Best Time to Buy and Sell Stock with Cooldown
    vector<int> stock_prices3 = {1,2,3,0,2};
    cout << "Max Profit with Cooldown: " << MaxProfitCooldown(stock_prices3) << endl;

    // Test Problem 28: Paint House
    vector<vector<int>> cost_matrix = {{17,2,17},{16,16,5},{14,3,19}};
    cout << "Minimum Cost to Paint Houses: " << MinCost(cost_matrix) << endl;

    // Test Problem 29: Jump Game
    vector<int> jump_nums = {2,3,1,1,4};
    cout << "Can Jump to Last Index: " << (CanJump(jump_nums) ? "true" : "false") << endl;

    // Test Problem 30: Jump Game II
    vector<int> jump_nums2 = {2,3,1,1,4};
    cout << "Minimum Jumps to Reach End: " << JumpMinSteps(jump_nums2) << endl;

    return 0;
}
