#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

/**
 * Problem 1: Climbing Stairs
 * Description: You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
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
 * Problem 2: Maximum Subarray
 * Description: Given an integer array nums, find the contiguous subarray 
 * (containing at least one number) which has the largest sum and return its sum.
 */
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
 * Problem 3: Unique Paths
 * Description: A robot is located at the top-left corner of a m x n grid. 
 * The robot can only move either down or right at any point in time. 
 * The robot is trying to reach the bottom-right corner. How many possible unique paths are there?
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
 * Problem 4: Coin Change
 * Description: You are given an integer array coins representing coins of different denominations 
 * and an integer amount representing a total amount of money. Return the fewest number of coins 
 * that you need to make up that amount. If that amount of money cannot be made up, return -1.
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
 * Problem 5: Longest Increasing Subsequence
 * Description: Given an integer array nums, return the length of the longest strictly increasing subsequence.
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

/**
 * Problem 6: Edit Distance
 * Description: Given two strings word1 and word2, return the minimum number of operations required 
 * to convert word1 to word2. You can perform insert, delete, and replace operations.
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

int main() {
    // Test Problem 1: Climbing Stairs
    cout << "Climbing Stairs (n=5): " << climbStairs(5) << endl;

    // Test Problem 2: Maximum Subarray
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray: " << maxSubArray(nums1) << endl;

    // Test Problem 3: Unique Paths
    cout << "Unique Paths (3x7 grid): " << uniquePaths(3, 7) << endl;

    // Test Problem 4: Coin Change
    vector<int> coins = {1, 2, 5};
    cout << "Coin Change (amount=11): " << coinChange(coins, 11) << endl;

    // Test Problem 5: Longest Increasing Subsequence
    vector<int> nums2 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Longest Increasing Subsequence: " << lengthOfLIS(nums2) << endl;

    // Test Problem 6: Edit Distance
    string word1 = "horse", word2 = "ros";
    cout << "Edit Distance (horse -> ros): " << minDistance(word1, word2) << endl;

    return 0;
}
