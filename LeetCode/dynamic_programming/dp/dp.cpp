#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <numeric>
#include <cstdint>
using namespace std;

/**
 * 🧠 Dynamic Programming (DP) Overview
 * ------------------------------------
 * Dynamic Programming is a method for solving complex problems by breaking them down into simpler subproblems.
 * It is applicable when the problem has overlapping subproblems and optimal substructure properties.
 * 
 * 🔍 When to Use:
 * - Problem can be divided into subproblems
 * - Subproblem results are reused (overlapping)
 * - There is an optimal substructure (global optimum depends on local optimum)
 *
 * 💡 Common DP Patterns:
 * 1. 0/1 Knapsack: choose or skip (e.g., max value with weight constraint)
 * 2. Subsequence/Substring: longest common subsequence, longest increasing subsequence
 * 3. Partition: equal sum, subset sum
 * 4. DP on Grid: unique paths, minimum path sum
 * 5. State Compression: bitmasking + DP
 * 6. Interval DP: palindrome partitioning, burst balloons
 *
 * 🧱 DP Table Design:
 * - Define state: dp[i], dp[i][j], dp[i][j][k]...
 * - Recurrence relation: how current state depends on previous states
 * - Base case(s): initial value(s)
 * - Iteration direction: bottom-up or top-down (memoization)
 *
 * 🧪 Template (Bottom-Up):
 * vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
 * for (int i = 0; i <= n; ++i) {
 *     for (int j = 0; j <= m; ++j) {
 *         // fill dp[i][j] based on recurrence
 *     }
 * }
 * return dp[n][m];
 *
 * 🧪 Template (Top-Down):
 * unordered_map<string, int> memo;
 * int dfs(int i, int j) {
 *     string key = to_string(i) + "," + to_string(j);
 *     if (memo.count(key)) return memo[key];
 *     ... // compute result
 *     return memo[key] = result;
 * }
 */

/**
 * Problem 1: Climbing Stairs (LC 70)
 * ----------------------------------
 * 🧠 Description:
 * You are climbing a staircase with `n` steps. Each time you can climb either 1 step or 2 steps.
 * You start from step 0. Return the total number of distinct ways to reach the top (step n).
 *
 * 🔍 Example:
 * Input: n = 5
 * Output: 8
 * Explanation:
 * There are 8 distinct ways to climb:
 *   - [1+1+1+1+1]
 *   - [1+1+1+2]
 *   - [1+1+2+1]
 *   - [1+2+1+1]
 *   - [2+1+1+1]
 *   - [2+2+1]
 *   - [2+1+2]
 *   - [1+2+2]
 *
 * 🎯 Key Insight:
 * The number of ways to reach step `i` is composed of:
 *   - All the ways to reach step (i-1), and take 1 more step
 *   - All the ways to reach step (i-2), and take a 2-step hop
 * This forms a Fibonacci-like recurrence: dp[i] = dp[i-1] + dp[i-2]
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Let `dp[i]` denote the total number of distinct ways to reach the i-th step.
 *
 * ✅ Base Case Initialization:
 *   - dp[0] = 1 → There is 1 way to stay at the ground (do nothing)
 *   - dp[1] = 1 → Only one way to reach the first step: a single 1-step move
 *
 * ✅ Transition:
 * To compute dp[i], we consider:
 *   - If the last step taken was a 1-step from (i-1), then there are dp[i-1] such ways
 *   - If the last step taken was a 2-step from (i-2), then there are dp[i-2] such ways
 *
 * So:
 *   dp[i] = dp[i - 1] + dp[i - 2]
 *
 * ✅ Iteration Order:
 * From i = 2 up to i = n, compute dp[i] using the above recurrence.
 *
 * 🚨 Edge Cases:
 * - n = 0 → return 1 (stay still)
 * - n = 1 → return 1 (single step)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n) — can be optimized to O(1) using two variables
 */
int ClimbStairs(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1);
    dp[0] = 1;  // One way to stay at the bottom
    dp[1] = 1;  // One way to reach the first step

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];  // Either take 1-step or 2-steps
    }

    return dp[n];
}

/**
 * 🔧 Optimized Space Version:
 * ------------------------------------------------------------
 * Instead of storing the whole dp array, we only need the last two values:
 *     prev1 = dp[i-1]
 *     prev2 = dp[i-2]
 *
 * This reduces space to O(1) while maintaining correctness.
 */
int ClimbStairsOptimal(int n) {
    if (n <= 1) return 1;
    int prev2 = 1, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

/**
 * Problem 2: Maximum Subarray (LC 53)
 * -----------------------------------
 * 📿 Description:
 * Given an integer array `nums`, find the contiguous subarray (containing at least one number)
 * which has the largest sum and return its sum.
 *
 * 🔍 Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation:
 * The subarray [4,-1,2,1] has the largest sum = 6.
 *
 * 🎯 Key Insight:
 * At every index, you choose:
 *   - To start a new subarray at this point
 *   - Or to extend the previous maximum subarray
 * This decision is captured in:
 *   dp[i] = max(nums[i], dp[i-1] + nums[i])
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * - dp[i] represents the maximum subarray sum ending at index i.
 * - Transition:
 *     To compute dp[i], we consider:
 *     ➤ Either start a new subarray at i: nums[i]
 *     ➤ Or extend the previous one: dp[i-1] + nums[i]
 *     So the recurrence is:
 *         dp[i] = max(nums[i], dp[i - 1] + nums[i])
 *
 * - Initialization:
 *     dp[0] = nums[0]
 *
 * - Iteration Order:
 *     From left to right (i = 1 to n-1)
 *
 * 🚨 Edge Cases:
 * - All elements are negative → choose the largest single number.
 * - Single-element array → return nums[0]
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n), can be optimized to O(1) using a variable for dp[i - 1]
 */
int MaxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size(), 0); // dp[i] = max subarray sum ending at index i
    dp[0] = nums[0];
    int max_sum = dp[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        max_sum = max(max_sum, dp[i]);
    }
    return max_sum;
}

/**
 * 🔧 Optimized Kadane’s Algorithm
 * ------------------------------------------------------------
 * - Instead of keeping a full dp[] array, we only need the last state.
 * - curr tracks dp[i-1], updated in-place.
 * - This reduces space from O(n) to O(1).
 */
int MaxSubArrayOptimal(vector<int>& nums) {
    int curr = nums[0];
    int max_sum = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        curr = max(nums[i], curr + nums[i]);
        max_sum = max(max_sum, curr);
    }
    return max_sum;
}

/**
 * Problem 3: Unique Paths (LC 62)
 * -------------------------------
 * 📿 Description:
 * A robot is located at the top-left corner of an `m x n` grid.
 * The robot can only move either down or right. Return the number of unique paths
 * to reach the bottom-right corner.
 *
 * 🔍 Example:
 * Input: m = 3, n = 7
 * Output: 28
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * - dp[i][j] represents the number of unique paths to reach cell (i, j).
 * - Transition:
 *     You can only move from:
 *     ➤ the cell above:    dp[i - 1][j]
 *     ➤ the cell to the left: dp[i][j - 1]
 *     So the recurrence is:
 *         dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
 *
 * - Initialization:
 *     dp[0][j] = 1 → first row: only one way (move right)
 *     dp[i][0] = 1 → first column: only one way (move down)
 *
 * - Iteration Order:
 *     From top-left to bottom-right (row-wise)
 *
 * 🚨 Edge Cases:
 * - m == 1 or n == 1 → only one path straight across/down
 *
 * ⏱️ Time: O(m * n)
 * 🧠 Space: O(m * n), can be optimized to O(n)
 */
int UniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j] = paths to (i,j)
    for (int i = 0; i < m; ++i) dp[i][0] = 1;      // first column
    for (int j = 0; j < n; ++j) dp[0][j] = 1;      // first row
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

/**
 * 🔧 Optimized Space Solution:
 * ------------------------------------------------------------
 * We only need the current and previous row → reduce to 1D array.
 */
int UniquePathsOptimal(int m, int n) {
    vector<int> dp(n, 1); // Only one row needed
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j] + dp[j - 1]; // left + top
        }
    }
    return dp[n - 1];
}


/**
 * Problem 4: Coin Change (LC 322)
 * -------------------------------
 * 📿 Description:
 * You are given an integer array `coins` and an integer `amount`.
 * Return the fewest number of coins needed to make up that amount.
 * If it's not possible, return -1.
 *
 * 🔍 Example:
 * Input: coins = [1,2,5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * - dp[i] represents the minimum number of coins needed to make amount i.
 *
 * - Transition:
 *     For each coin:
 *     ➤ dp[i] = min(dp[i], dp[i - coin] + 1) if i - coin >= 0 and dp[i - coin] != INT_MAX
 *
 * - Initialization:
 *     dp[0] = 0 (0 coins needed to make amount 0)
 *     dp[1...amount] = INT_MAX (initially unreachable)
 *
 * - Iteration Order:
 *     Outer loop on coins, inner loop on amount
 *
 * 🚨 Edge Cases:
 * - amount == 0 → return 0
 * - amount < min(coins) → return -1
 *
 * ⏱️ Time: O(amount × number of coins)
 * 🧠 Space: O(amount)
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

/**
 * Problem 5: Longest Increasing Subsequence (LC 300)
 * ---------------------------------------------------
 * 📿 Description:
 * Given an integer array `nums`, return the length of the longest strictly increasing subsequence (LIS).
 *
 * 🔍 Example:
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: LIS is [2,3,7,101]
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * - dp[i] represents the length of the LIS ending at index i.
 *
 * - Transition:
 *     For each j in [0, i):
 *     ➤ if nums[j] < nums[i], we can extend LIS at j:
 *         dp[i] = max(dp[i], dp[j] + 1)
 *
 * - Initialization:
 *     All dp[i] = 1 (each element is an LIS of length 1)
 *
 * - Iteration Order:
 *     Outer loop: i from 1 to n-1
 *     Inner loop: j from 0 to i-1
 *
 * 🚨 Edge Cases:
 * - All elements same → answer is 1
 * - Strictly increasing → answer is n
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n)
 */
int LengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    int max_len = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}

/**
 * 🔧 Optimized Approach using Binary Search:
 * ------------------------------------------------------------
 * We use an auxiliary array `res` where:
 * - res[i] holds the smallest possible tail value of an increasing subsequence of length i + 1
 *
 * For each number in `nums`:
 * - If num > last element in `res`, extend the subsequence and append num
 * - Otherwise, find the first element in `res` >= num using binary search and replace it
 *
 * Binary search ensures that:
 * - `res` is always sorted
 * - We maintain the minimum possible values for each length
 *
 * Note: The array `res` does **not** represent the actual subsequence,
 * but its length is equal to the LIS length.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
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

/**
 * Problem 6: Edit Distance (LC 72)
 * --------------------------------
 * 🧠 Description:
 * Given two strings `word1` and `word2`, return the minimum number of operations required
 * to convert word1 to word2. You can insert, delete, or replace a character.
 *
 * 🔍 Example:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * "horse" -> "ros" via 3 operations: replace h→r, remove r, remove e
 *
 * 🎯 Key Insight:
 * For each character position i, j, try all 3 operations:
 *   - Insert (dp[i][j-1])
 *   - Delete (dp[i-1][j])
 *   - Replace (dp[i-1][j-1])
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = minimum number of operations to convert word1[0..i-1] to word2[0..j-1]
 *
 * ✅ Base Case Initialization:
 * dp[0][j] = j → convert empty word1 to word2 of length j (all inserts)
 * dp[i][0] = i → convert word1 of length i to empty word2 (all deletes)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ If word1[i-1] == word2[j-1] → no operation → dp[i][j] = dp[i-1][j-1]
 *     ➤ Otherwise, try:
 *         - Insert:  dp[i][j-1] + 1
 *         - Delete:  dp[i-1][j] + 1
 *         - Replace: dp[i-1][j-1] + 1
 *     So the recurrence is:
 *         dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1
 *
 * ✅ Iteration Order:
 * i = 1..m, j = 1..n
 *
 * 🚨 Edge Cases:
 * - One or both strings are empty
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n)
 */
int MinDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1 });
        }
    }
    return dp[m][n];
}

/**
 * 🔧 Optimized Version (Rolling DP Row):
 * ------------------------------------------------------------
 * Since we only need previous and current rows,
 * we can reduce space from O(m × n) to O(n).
 *
 * ⏱️ Time Complexity: O(m × n)
 * 🧠 Space Complexity: O(n)
 */
int MinDistanceOptimal(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<int> prev(n + 1), curr(n + 1);

    for (int j = 0; j <= n; ++j) prev[j] = j;

    for (int i = 1; i <= m; ++i) {
        curr[0] = i;
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = min({ prev[j - 1], prev[j], curr[j - 1] }) + 1;
            }
        }
        prev = curr;
    }

    return prev[n];
}

/**
 * Problem 7: Partition Equal Subset Sum (LC 416)
 * ----------------------------------------------
 * 📿 Description:
 * Determine if a given array can be partitioned into two subsets with equal sum.
 *
 * 🔍 Example:
 * Input: nums = [1,5,11,5]
 * Output: true
 * Explanation: [1,5,5] and [11] both sum to 11
 *
 * 💡 DP Strategy (0/1 Knapsack):
 * ------------------------------------------------------------
 * - Goal: Can we find a subset with sum = total_sum / 2?
 * - Let target = sum / 2
 * - dp[i] = true if sum i is achievable with any subset
 *
 * - Transition:
 *     for each num in nums:
 *         for i from target to num:
 *             dp[i] |= dp[i - num]
 *
 * - Initialization:
 *     dp[0] = true (sum 0 is always achievable)
 *
 * 🚨 Edge Cases:
 * - If total sum is odd → cannot split
 *
 * ⏱️ Time: O(n * sum/2)
 * 🧠 Space: O(sum/2)
 */
bool CanPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (int num : nums) {
        for (int i = target; i >= num; --i) {
            dp[i] = dp[i] || dp[i - num];
        }
    }
    return dp[target];
}

/**
 * Problem 8: House Robber (LC 198)
 * --------------------------------
 * 🧠 Description:
 * You're a robber planning to steal from a row of houses.
 * Each house has some amount of money, but you can't rob two adjacent houses.
 * Return the maximum amount of money you can rob without triggering the alarm.
 *
 * 🔍 Example:
 * Input: nums = [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (2), house 3 (9), and house 5 (1) → 2 + 9 + 1 = 12
 *
 * 🎯 Key Insight:
 * At each house, you must decide:
 *   - Rob this house and skip the previous
 *   - Or skip this house and take whatever was best before
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = max money that can be robbed from first (i + 1) houses
 *
 * ✅ Base Case Initialization:
 * dp[0] = nums[0]
 * dp[1] = max(nums[0], nums[1])
 *
 * ✅ Transition:
 *     To compute dp[i], we consider:
 *     ➤ Rob house i → dp[i-2] + nums[i]
 *     ➤ Skip house i → dp[i-1]
 *     So the recurrence is:
 *         dp[i] = max(dp[i-1], dp[i-2] + nums[i])
 *
 * ✅ Iteration Order:
 * i from 2 to n-1
 *
 * 🚨 Edge Cases:
 * - nums.size() == 0 → return 0
 * - nums.size() == 1 → return nums[0]
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int Rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (size_t i = 2; i < nums.size(); ++i)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    return dp.back();
}

/**
 * 🔧 Optimized Version (Space O(1)):
 * ------------------------------------------------------------
 * We only need two previous values to calculate the current:
 *   prev1 = max robbed up to house i-1
 *   prev2 = max robbed up to house i-2
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int RobOptimal(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0], prev1 = max(nums[0], nums[1]);
    for (int i = 2; i < n; ++i) {
        int curr = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

/**
 * Problem 9: Decode Ways (LC 91)
 * ------------------------------
 * 🧠 Description:
 * Given a string of digits, return how many ways it can be decoded into letters (A-Z = 1–26).
 *
 * 🔍 Example:
 * Input: s = "226"
 * Output: 3 → "BZ", "VF", "BBF"
 *
 * 🎯 Key Insight:
 * dp[i] = number of ways to decode first i characters
 * Use 1-digit or 2-digit decoding based on rules:
 *   - 1-digit if s[i-1] ∈ [1-9]
 *   - 2-digit if s[i-2..i-1] ∈ [10-26]
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = number of ways to decode the first i characters (s[0..i-1])
 *
 * ✅ Base Case Initialization:
 * dp[0] = 1 → empty string = 1 way
 * dp[1] = 1 if s[0] != '0' else 0
 *
 * ✅ Transition:
 *     To compute dp[i], we consider:
 *     ➤ One-digit decode (if s[i-1] != '0') → dp[i] += dp[i-1]
 *     ➤ Two-digit decode (if 10 ≤ s[i-2..i-1] ≤ 26) → dp[i] += dp[i-2]
 *
 * ✅ Iteration Order:
 * i from 2 to n
 *
 * 🚨 Edge Cases:
 * - s starts with '0' → invalid
 * - contains invalid "0" not part of "10" or "20"
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n), can be optimized to O(1)
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

/**
 * 🔧 Optimized Version (Space O(1)):
 * ------------------------------------------------------------
 * We only need two previous values:
 *   prev1 = dp[i - 1], prev2 = dp[i - 2]
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int NumDecodingsOptimal(string s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    int prev2 = 1, prev1 = 1;

    for (int i = 1; i < n; ++i) {
        int curr = 0;
        if (s[i] != '0') curr += prev1;
        int two = stoi(s.substr(i - 1, 2));
        if (two >= 10 && two <= 26) curr += prev2;

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

/**
 * Problem 10: Triangle Minimum Path Sum (LC 120)
 * ----------------------------------------------
 * 🧠 Description:
 * Given a triangle, find the minimum path sum from top to bottom.
 * At each step, you may move to adjacent numbers in the row below.
 *
 * 🔍 Example:
 * Input: [[2],[3,4],[6,5,7],[4,1,8,3]]
 * Output: 11 → 2 + 3 + 5 + 1
 *
 * 🎯 Key Insight:
 * Start from bottom and reduce the triangle row-by-row using min transition.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = min path sum to reach triangle[i][j]
 *
 * ✅ Base Case Initialization:
 * dp = triangle[n - 1] (bottom row)
 *
 * ✅ Transition:
 *     To compute dp[j] at row i:
 *     ➤ dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j]
 *
 * ✅ Iteration Order:
 * i from n-2 up to 0
 *
 * 🚨 Edge Cases:
 * - Triangle is empty
 * - Triangle with only one row
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n) using 1D dp array
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

/**
 * Problem 11: Longest Palindromic Subsequence (LC 516)
 * ----------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the length of its longest palindromic subsequence.
 * A subsequence is a sequence derived by deleting characters without changing order.
 *
 * 🔍 Example:
 * Input: s = "bbbab"
 * Output: 4
 * Explanation: One possible longest palindromic subsequence is "bbbb".
 *
 * 🎯 Key Insight:
 * Use 2D DP: check longest palindromic subsequence between indices i and j.
 * Characters match → extend palindrome; otherwise take best from left/right.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = length of longest palindromic subsequence in s[i..j]
 *
 * ✅ Base Case Initialization:
 * dp[i][i] = 1 for all i (each character is a palindrome)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ If s[i] == s[j] → extend center: dp[i+1][j-1] + 2
 *     ➤ Else → max from skipping either end: max(dp[i+1][j], dp[i][j-1])
 *     So the recurrence is:
 *         dp[i][j] = (s[i] == s[j]) ? dp[i+1][j-1] + 2 : max(dp[i+1][j], dp[i][j-1])
 *
 * ✅ Iteration Order:
 * Fill from shorter substrings to longer: i from n-1 down to 0, j from i+1 to n-1
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - Single character → return 1
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n^2)
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

/**
 * Problem 12: Burst Balloons (LC 312)
 * -----------------------------------
 * 🧠 Description:
 * You are given balloons with numbers. When you burst balloon i, coins = nums[i-1] * nums[i] * nums[i+1].
 * You want to maximize the total coins by choosing the best burst order.
 *
 * 🔍 Example:
 * Input: nums = [3,1,5,8]
 * Output: 167
 * Explanation: Best order leads to max coins: [3,5,8] → [3,8] → [8] → []
 *
 * 🎯 Key Insight:
 * Treat problem as range DP: define which balloon is last to burst in a subrange.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = max coins for bursting all balloons in range (i, j), exclusive
 *
 * ✅ Base Case Initialization:
 * dp[i][i+1] = 0 (no balloon to burst between adjacent walls)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ Try bursting balloon k last in (i, j)
 *     ➤ Add coins: nums[i] * nums[k] * nums[j] + dp[i][k] + dp[k][j]
 *     So:
 *         dp[i][j] = max(dp[i][j], nums[i] * nums[k] * nums[j] + dp[i][k] + dp[k][j])
 *
 * ✅ Iteration Order:
 * Length from 2 to n, then all subintervals (i, j)
 *
 * 🚨 Edge Cases:
 * - nums is empty → return 0
 * - Pad with 1 on both sides to simplify logic
 *
 * ⏱️ Time: O(n^3)
 * 🧠 Space: O(n^2)
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

/**
 * Problem 13: Longest Continuous Increasing Subsequence (LC 674)
 * ---------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, return the length of the longest **contiguous** (not necessarily strictly global) 
 * increasing subarray.
 *
 * 🔍 Example:
 * Input: nums = [1,3,5,4,7]
 * Output: 3 → [1,3,5]
 *
 * 🎯 Key Insight:
 * This is not longest increasing **subsequence**, but longest **subarray**.
 * We can solve it either by greedy counting, or by DP where dp[i] means LCIS ending at i.
 *
 * 💡 Greedy Strategy (Best in Practice):
 * ------------------------------------------------------------
 * ✅ Greedy Insight:
 * - Traverse the array from left to right
 * - If current element > previous, extend the current streak
 * - Else, reset current streak to 1
 *
 * ✅ Variables:
 * - current_len = length of current increasing streak
 * - max_len = max seen so far
 *
 * 🚨 Edge Cases:
 * - Empty array → return 0
 * - All equal or descending → return 1
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
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

/**
 * 🔁 Dynamic Programming Version:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = length of the LCIS that ends at index i
 *
 * ✅ Base Case:
 * dp[0] = 1 (any element alone is length 1)
 *
 * ✅ Transition:
 * - If nums[i] > nums[i-1] → dp[i] = dp[i-1] + 1
 * - Else → dp[i] = 1 (restart from here)
 *
 * ✅ Iteration Order:
 * i = 1 to n-1
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
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

/**
 * Problem 14: Maximum Length of Repeated Subarray (LC 718)
 * ---------------------------------------------------------
 * 🧠 Description:
 * Given two integer arrays nums1 and nums2, return the length of their longest common subarray.
 * A subarray is a contiguous segment of an array.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
 * Output: 3 → The common subarray [3,2,1]
 *
 * 🎯 Key Insight:
 * This is similar to Longest Common Substring (not subsequence).
 * Use 2D DP: track length of ending-at-i-and-j matching subarrays.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = length of longest common subarray ending at nums1[i-1] and nums2[j-1]
 *
 * ✅ Base Case:
 * dp[0][*] = 0 and dp[*][0] = 0 (empty subarrays)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ If nums1[i-1] == nums2[j-1] → extend previous match: dp[i][j] = dp[i-1][j-1] + 1
 *     ➤ Else → dp[i][j] = 0 (no match ends here)
 *
 * ✅ Iteration Order:
 * i from 1..m, j from 1..n
 *
 * 🚨 Edge Cases:
 * - One array empty → return 0
 * - No common subarray → return 0
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n) → Can be optimized to O(n)
 */
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

/**
 * Problem 15: Distinct Subsequences (LC 115)
 * ------------------------------------------
 * 🧠 Description:
 * Given strings `s` and `t`, return how many distinct subsequences of `s` equal `t`.
 * A subsequence deletes some characters from `s` (without reordering).
 *
 * 🔍 Example:
 * Input: s = "rabbbit", t = "rabbit"
 * Output: 3
 *
 * 🎯 Key Insight:
 * Use 2D DP: count number of subsequences from s[0..i] matching t[0..j].
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = number of subsequences of s[0..i-1] matching t[0..j-1]
 *
 * ✅ Base Case:
 * dp[i][0] = 1 (empty t is a subsequence of any prefix of s)
 * dp[0][j>0] = 0 (non-empty t can’t match empty s)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ If s[i-1] == t[j-1] → we can:
 *         - match both (dp[i-1][j-1])
 *         - skip s[i-1] (dp[i-1][j])
 *     ➤ Else → skip s[i-1] (dp[i-1][j])
 *
 *         dp[i][j] = dp[i-1][j] + (s[i-1]==t[j-1] ? dp[i-1][j-1] : 0)
 *
 * ✅ Iteration Order:
 * i = 1..s.size(), j = 1..t.size()
 *
 * 🚨 Edge Cases:
 * - t longer than s → return 0
 * - s == t → return 1
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n)
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

/**
 * Problem 16: Longest Common Subsequence (LC 1143)
 * ------------------------------------------------
 * 🧠 Description:
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * A subsequence allows deletion, but keeps character order.
 *
 * 🔍 Example:
 * Input: text1 = "abcde", text2 = "ace"
 * Output: 3 → "ace"
 *
 * 🎯 Key Insight:
 * Use classic 2D DP to build LCS length matrix.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = length of LCS between text1[0..i-1] and text2[0..j-1]
 *
 * ✅ Base Case:
 * dp[0][*] = 0, dp[*][0] = 0 (empty string)
 *
 * ✅ Transition:
 *     To compute dp[i][j], we consider:
 *     ➤ If text1[i-1] == text2[j-1] → extend match: dp[i-1][j-1] + 1
 *     ➤ Else → take max from excluding one: max(dp[i-1][j], dp[i][j-1])
 *
 * ✅ Iteration Order:
 * i = 1..m, j = 1..n
 *
 * 🚨 Edge Cases:
 * - One string empty → return 0
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n)
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

/**
 * Problem 17: Longest Palindromic Substring (LC 5)
 * ------------------------------------------------
 * 🧠 Description:
 * Given a string s, return the longest palindromic substring in s.
 * A string is a palindrome when it reads the same backward as forward.
 *
 * 🔍 Example:
 * Input: s = "babad"
 * Output: "bab" or "aba"
 *
 * 🎯 Key Insight:
 * A substring is a palindrome if:
 *   - The outer characters match
 *   - The inner substring is also a palindrome
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = whether s[i..j] is a palindrome
 *
 * ✅ Base Case Initialization:
 * dp[i][i] = true (every single character is a palindrome)
 *
 * ✅ Transition:
 * dp[i][j] = (s[i] == s[j]) && (j - i <= 2 || dp[i+1][j-1])
 *
 * ✅ Iteration Order:
 * j from 0 to n-1
 *   i from 0 to j
 *
 * 🚨 Edge Cases:
 * - Single character string → return s
 * - Entire string is palindrome → return s
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n^2)
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

/**
 * Problem 18: Palindromic Substrings (LC 647)
 * -------------------------------------------
 * 🧠 Description:
 * Return the total number of palindromic substrings in a given string.
 *
 * 🔍 Example:
 * Input: s = "aaa"
 * Output: 6
 * Explanation: "a", "a", "a", "aa", "aa", "aaa"
 *
 * 🎯 Key Insight:
 * A substring is palindromic if the ends match and the middle is also a palindrome.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = whether s[i..j] is a palindrome
 *
 * ✅ Base Case:
 * dp[i][i] = true (single character)
 *
 * ✅ Transition:
 * If s[i] == s[j] and (j - i < 2 || dp[i+1][j-1]) then dp[i][j] = true
 *
 * ✅ Iteration Order:
 * i from n-1 down to 0
 * j from i to n-1
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n^2)
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

/**
 * Problem 19: Minimum Falling Path Sum (LC 931)
 * ---------------------------------------------
 * 🧠 Description:
 * Find the minimum sum of a falling path in a matrix where a path starts at any element
 * in the first row and moves down to one of the three positions in the next row.
 *
 * 🔍 Example:
 * Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
 * Output: 13
 * Explanation: 1 → 5 → 7
 *
 * 🎯 Key Insight:
 * At each cell in row i, you can only come from j-1, j, or j+1 in row i-1
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = min falling path sum ending at column j of current row
 *
 * ✅ Base Case Initialization:
 * dp = matrix[0]
 *
 * ✅ Transition:
 * dp[j] = matrix[i][j] + min(dp[j], dp[j-1], dp[j+1])
 *
 * ✅ Iteration Order:
 * From top to bottom, row by row
 *
 * 🚨 Edge Cases:
 * - Only one row → return min of that row
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n)
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

/**
 * Problem 20: Ugly Number II (LC 264)
 * -----------------------------------
 * 🧠 Description:
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 * Return the n-th ugly number in the sequence.
 *
 * 🔍 Example:
 * Input: n = 10
 * Output: 12
 * Explanation: The sequence is [1, 2, 3, 4, 5, 6, 8, 9, 10, 12, ...]
 *
 * 🎯 Key Insight:
 * Each ugly number is formed by multiplying a smaller ugly number by 2, 3, or 5.
 * Use three pointers to track the next index of multiples for 2, 3, and 5.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = i-th ugly number in increasing order
 *
 * ✅ Base Case Initialization:
 * dp[0] = 1
 *
 * ✅ Transition:
 * dp[i] = min(dp[i2] * 2, dp[i3] * 3, dp[i5] * 5)
 * Update i2/i3/i5 if they were used
 *
 * ✅ Iteration Order:
 * i from 1 to n-1
 *
 * 🚨 Edge Cases:
 * - n = 1 → return 1
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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

/**
 * Problem 21: Maximum Product Subarray (LC 152)
 * ---------------------------------------------
 * 🧠 Description:
 * Given an integer array nums, find the contiguous subarray with the largest product.
 *
 * 🔍 Example:
 * Input: nums = [2,3,-2,4]
 * Output: 6 → subarray = [2,3]
 *
 * 🎯 Key Insight:
 * A negative number can flip the min/max. Need to track both.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - max_prod = max product ending at index i
 * - min_prod = min product ending at index i
 *
 * ✅ Transition:
 * If nums[i] < 0 → swap max and min
 * Then:
 *   max_prod = max(nums[i], max_prod * nums[i])
 *   min_prod = min(nums[i], min_prod * nums[i])
 *
 * ✅ Base Initialization:
 * Both set to nums[0]
 *
 * ✅ Iteration Order:
 * i = 1 to n-1
 *
 * 🚨 Edge Cases:
 * - Contains 0 → reset max/min to 0 or nums[i]
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
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

/**
 * Problem 22: Best Time to Buy and Sell Stock (LC 121)
 * -----------------------------------------------------
 * 🧠 Description:
 * Given an array of prices, where prices[i] is the price of a stock on day i,
 * return the maximum profit you can achieve from one transaction.
 *
 * 🔍 Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5 → Buy on day 2, sell on day 5 (6 - 1 = 5)
 *
 * 🎯 Key Insight:
 * At each day, find the lowest price before and compute current potential profit.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Tracking:
 * - min_price = smallest price seen so far
 * - max_profit = best profit so far
 *
 * ✅ Transition:
 * - Update min_price = min(min_price, prices[i])
 * - Update max_profit = max(max_profit, prices[i] - min_price)
 *
 * 🚨 Edge Cases:
 * - prices.size() < 2 → return 0
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int MaxProfit(vector<int>& prices) {
    int min_price = INT_MAX, max_profit = 0;
    for (int price : prices) {
        min_price = min(min_price, price);
        max_profit = max(max_profit, price - min_price);
    }
    return max_profit;
}

/**
 * Problem 23: Best Time to Buy and Sell Stock II (LC 122)
 * --------------------------------------------------------
 * 🧠 Description:
 * You may complete as many transactions as you like (buy one and sell one share of the stock multiple times).
 * You cannot hold multiple stocks simultaneously (must sell before buying again).
 *
 * 🔍 Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (1), sell on day 3 (5), buy on day 4 (3), sell on day 5 (6)
 *
 * 🎯 Key Insight:
 * Accumulate all local upward price gaps — it's always beneficial to buy before a rise.
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * ✅ State Tracking:
 * - profit accumulates whenever today's price > yesterday's
 *
 * ✅ Transition:
 * if prices[i] > prices[i-1], then profit += prices[i] - prices[i-1]
 *
 * ✅ Iteration Order:
 * From left to right (i = 1 to n - 1)
 *
 * 🚨 Edge Cases:
 * - Empty or single-day array → return 0
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
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

/**
 * Problem 24: House Robber II (LC 213)
 * -------------------------------------
 * 🧠 Description:
 * You are a professional robber planning to rob houses along a **circular street**.
 * You cannot rob two adjacent houses (first and last houses are adjacent).
 *
 * 🔍 Example:
 * Input: nums = [2,3,2]
 * Output: 3
 * Explanation: Rob house 2 (3) instead of houses 1 and 3
 *
 * 🎯 Key Insight:
 * Since the first and last houses are neighbors, robbing both is invalid.
 * Split the array into two cases:
 *   1. Rob houses 0 to n-2
 *   2. Rob houses 1 to n-1
 * Take the max result of both.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use classic linear House Robber logic within subarray [start, end]
 *
 * ✅ Base Initialization:
 * prev1 = max robbed up to house i-1
 * prev2 = max robbed up to house i-2
 *
 * ✅ Transition:
 * curr = max(prev1, prev2 + nums[i])
 *
 * ✅ Iteration Order:
 * i from start to end
 *
 * 🚨 Edge Cases:
 * - Only one house → return nums[0]
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
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

/**
 * Problem 25: Wildcard Matching (LC 44)
 * -------------------------------------
 * 🧠 Description:
 * Implement wildcard pattern matching with support for:
 *   - '?' matches any single character
 *   - '*' matches any sequence (including empty)
 * Return true if the pattern matches the string.
 *
 * 🔍 Example:
 * Input: s = "adceb", p = "*a*b"
 * Output: true
 *
 * 🎯 Key Insight:
 * Use dynamic programming to match prefixes of s and p.
 * '*' has flexible matching power.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = whether s[0..i-1] matches p[0..j-1]
 *
 * ✅ Base Case Initialization:
 * dp[0][0] = true (empty matches empty)
 * dp[0][j] = true only if p[0..j-1] is all '*'
 *
 * ✅ Transition:
 * - If p[j-1] == '*': dp[i][j] = dp[i][j-1] || dp[i-1][j]
 * - If p[j-1] == '?' or s[i-1] == p[j-1]: dp[i][j] = dp[i-1][j-1]
 *
 * ✅ Iteration Order:
 * i from 1 to m, j from 1 to n
 *
 * 🚨 Edge Cases:
 * - Consecutive '*' in pattern → compress if needed (optional optimization)
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n)
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

/**
 * Problem 26: Interleaving String (LC 97)
 * ---------------------------------------
 * 🧠 Description:
 * Given three strings `s1`, `s2`, and `s3`, return true if `s3` is formed by interleaving `s1` and `s2`.
 * Interleaving means characters of s1 and s2 are merged in order.
 *
 * 🔍 Example:
 * Input: s1 = "aab", s2 = "axy", s3 = "aaxaby"
 * Output: true
 *
 * 🎯 Key Insight:
 * At each step, choose either one character from s1 or s2 to form s3.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][j] = whether s1[0..i-1] and s2[0..j-1] can form s3[0..i+j-1]
 *
 * ✅ Base Case Initialization:
 * dp[0][0] = true
 * dp[i][0] = s1[0..i-1] == s3[0..i-1]
 * dp[0][j] = s2[0..j-1] == s3[0..j-1]
 *
 * ✅ Transition:
 * - If s1[i-1] == s3[i+j-1] and dp[i-1][j] is true → dp[i][j] = true
 * - If s2[j-1] == s3[i+j-1] and dp[i][j-1] is true → dp[i][j] = true
 *
 * ✅ Iteration Order:
 * i = 1 to m, j = 1 to n
 *
 * 🚨 Edge Cases:
 * - s1 + s2 length != s3.length → return false
 *
 * ⏱️ Time: O(m × n)
 * 🧠 Space: O(m × n)
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

/**
 * Problem 27: Best Time to Buy and Sell Stock with Cooldown (LC 309)
 * -------------------------------------------------------------------
 * 🧠 Description:
 * After you sell a stock, you cannot buy stock on the next day (cooldown).
 * Return the maximum profit.
 *
 * 🔍 Example:
 * Input: prices = [1,2,3,0,2]
 * Output: 3 → Transactions: buy(1), sell(3), cooldown, buy(0), sell(2)
 *
 * 🎯 Key Insight:
 * Use three states:
 *   - buy[i]: max profit on day i if you bought stock
 *   - sell[i]: max profit on day i if you sold stock
 *   - cooldown[i]: max profit on day i if you did nothing
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * buy[i] = max(buy[i-1], cooldown[i-1] - price)
 * sell[i] = max(sell[i-1], buy[i-1] + price)
 * cooldown[i] = max(cooldown[i-1], sell[i-1])
 *
 * ✅ Base Initialization:
 * buy[0] = -prices[0], sell[0] = 0, cooldown[0] = 0
 *
 * ✅ Iteration Order:
 * i from 1 to n-1
 *
 * 🚨 Edge Cases:
 * - prices.empty() → return 0
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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

/**
 * Problem 28: Paint House (LC 256)
 * --------------------------------
 * 🧠 Description:
 * There are `n` houses. Each house can be painted red, blue, or green.
 * No two adjacent houses can have the same color.
 * Return the minimum cost to paint all houses.
 *
 * 🔍 Example:
 * Input: cost = [[17,2,17],[16,16,5],[14,3,19]]
 * Output: 10 → Paint house 0 blue, 1 green, 2 blue
 *
 * 🎯 Key Insight:
 * Typical 3-state DP per house. Track min cost by avoiding same color as previous.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i][c] = min cost to paint house i with color c
 *
 * ✅ Base Initialization:
 * dp[0] = cost[0]
 *
 * ✅ Transition:
 * dp[i][0] = cost[i][0] + min(dp[i-1][1], dp[i-1][2])
 * dp[i][1] = cost[i][1] + min(dp[i-1][0], dp[i-1][2])
 * dp[i][2] = cost[i][2] + min(dp[i-1][0], dp[i-1][1])
 *
 * ✅ Iteration Order:
 * i from 1 to n-1
 *
 * 🚨 Edge Cases:
 * - cost.size() == 0 → return 0
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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

/**
 * Problem 29: Jump Game (LC 55)
 * -----------------------------
 * 🧠 Description:
 * Given an array `jump_nums` where `jump_nums[i]` represents the **maximum** jump length at that position,
 * return **true** if you can reach the last index.
 *
 * 🔍 Example:
 * Input: jump_nums = [2,3,1,1,4]
 * Output: true
 *
 * 🎯 Key Insight:
 * At each index, check if it's reachable from previous jumps.
 * Track the farthest index you can reach.
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * ✅ Variable Definition:
 * farthest = farthest position reachable so far
 *
 * ✅ Iteration:
 * At each index i:
 * - If i > farthest → cannot reach → return false
 * - Update farthest = max(farthest, i + jump_nums[i])
 *
 * ✅ Early Return:
 * If we reach end of array within iteration → true
 *
 * 🚨 Edge Cases:
 * - jump_nums.size() == 0 → return false
 * - jump_nums[0] == 0 and size > 1 → stuck
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
bool CanJump(vector<int>& jump_nums) {
    int farthest = 0;
    for (size_t i = 0; i < jump_nums.size(); ++i) {
        if (static_cast<int>(i) > farthest) return false; // Cannot reach this position
        farthest = max(farthest, static_cast<int>(i) + jump_nums[i]);
    }
    return true;
}

/**
 * 🔁 Dynamic Programming Approach:
 * ------------------------------------------------------------
 * 🧠 Description:
 * dp[i] = whether index i is reachable from the start.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = true if index `i` can be reached from index 0
 *
 * ✅ Base Case Initialization:
 * dp[0] = true (we start at index 0)
 *
 * ✅ Transition:
 * For each i from 1 to n-1:
 *   - Check if there exists a j < i such that:
 *     dp[j] == true AND j + nums[j] >= i → then dp[i] = true
 *
 * ✅ Iteration Order:
 * Outer loop i from 1 to n-1, inner loop j from 0 to i-1
 *
 * 🚨 Edge Cases:
 * - jump_nums is empty → return false
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n)
 */
bool CanJumpDP(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return false;
    vector<bool> dp(n, false);
    dp[0] = true;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && j + nums[j] >= i) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n - 1];
}

/**
 * Problem 30: Jump Game II (LC 45)
 * --------------------------------
 * 🧠 Description:
 * Given an array `jump_nums2`, return the **minimum number of jumps** required to reach the last index.
 *
 * 🔍 Example:
 * Input: jump_nums2 = [2,3,1,1,4]
 * Output: 2 → Jump from 0 → 1 → 4
 *
 * 🎯 Key Insight:
 * Track current range and farthest reachable point from it.
 * Every time you exit the range → increment jump.
 *
 * 💡 Greedy Layered Strategy:
 * ------------------------------------------------------------
 * ✅ Variable Definition:
 * jumps = number of jumps made
 * end = boundary of current jump range
 * farthest = max index reachable in current range
 *
 * ✅ Iteration:
 * From index 0 to n-2:
 * - Update farthest = max(farthest, i + nums[i])
 * - If i == end → need new jump → end = farthest
 *
 * ✅ Stop Condition:
 * Reaching end or just before last index
 *
 * 🚨 Edge Cases:
 * - jump_nums2.size() == 1 → already at goal → 0 jumps
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
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

int main() {
    // Test Problem 1: Climbing Stairs (LC 70)
    int n = 5;
    cout << "Climbing Stairs (n=" << n << "): " << ClimbStairs(n) << endl;
    cout << "Climbing Stairs Optimal: " << ClimbStairsOptimal(n) << endl;

    // Test Problem 2: Maximum Subarray (LC 53)
    vector<int> max_sub_array_input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray: " << MaxSubArray(max_sub_array_input) << endl;
    cout << "Maximum Subarray Optimal: " << MaxSubArrayOptimal(max_sub_array_input) << endl;

    // Test Problem 3: Unique Paths (LC 62)
    int m = 3, grid_n = 7;
    cout << "Unique Paths (" << m << "x" << grid_n << " grid): " << UniquePaths(m, grid_n) << endl;
    cout << "Unique Paths Optimal: " << UniquePathsOptimal(m, grid_n) << endl;

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
    cout << "Edit Distance Optimal: " << MinDistanceOptimal(edit_word1, edit_word2) << endl;

    // Test Problem 7: Partition Equal Subset Sum (LC 416)
    vector<int> partition_input = {1, 5, 11, 5};
    cout << "Partition Equal Subset Sum: " << (CanPartition(partition_input) ? "True" : "False") << endl;

    // Test Problem 8: House Robber (LC 198)
    vector<int> house_robber_input = {2, 7, 9, 3, 1};
    cout << "House Robber: " << Rob(house_robber_input) << endl;
    cout << "House Robber Optimal: " << RobOptimal(house_robber_input) << endl;

    // Test Problem 9: Decode Ways (LC 91)
    string decode_input = "226";
    cout << "Decode Ways (" << decode_input << "): " << NumDecodings(decode_input) << endl;
    cout << "Decode Ways Optimal: " << NumDecodingsOptimal(decode_input) << endl;

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
    cout << "Can Jump (Greedy): " << (CanJump(jump_nums) ? "true" : "false") << endl;
    cout << "Can Jump (DP): " << (CanJumpDP(jump_nums) ? "true" : "false") << endl;

    // Test Problem 30: Jump Game II
    vector<int> jump_nums2 = {2,3,1,1,4};
    cout << "Minimum Jumps to Reach End: " << JumpMinSteps(jump_nums2) << endl;

    return 0;
}
