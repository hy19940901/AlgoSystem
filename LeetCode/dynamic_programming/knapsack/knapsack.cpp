#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

/**
 * Problem 1: 0-1 Knapsack with Backtracking (2D DP)
 * -------------------------------------------------
 * 🧠 Description:
 * Given a list of items (each with a weight and value) and a maximum weight capacity,
 * find the maximum value you can obtain by selecting a subset of the items such that
 * their total weight does not exceed the capacity. Also return the selected items.
 *
 * 🔍 Example:
 * Input: items = [{A,2,3},{B,3,4},{C,4,5},{D,5,8}], capacity = 5
 * Output: max_value = 8, selected_items = [0,0,0,1] (i.e., only item D)
 *
 * 🎯 Key Insight:
 * For each item, we choose to either:
 *   - include it (if it fits), or
 *   - skip it.
 * Use 2D DP table where dp[i][j] is max value with first i items and capacity j.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 *   dp[i][j] = max value using first i items and total weight ≤ j
 *
 * ✅ Base Case Initialization:
 *   dp[0][*] = 0 (0 items → 0 value)
 *   dp[*][0] = 0 (0 capacity → 0 value)
 *
 * ✅ Transition:
 *   If item[i-1] can be added (weight ≤ j):
 *     dp[i][j] = max(dp[i-1][j], dp[i-1][j - weight[i-1]] + value[i-1])
 *   Else:
 *     dp[i][j] = dp[i-1][j]
 *
 * ✅ Iteration Order:
 *   for i = 1..n, j = 1..W
 *
 * 🚨 Edge Cases:
 * - No items → return 0
 * - All items heavier than capacity → return 0
 *
 * ⏱️ Time: O(n * W)
 * 🧠 Space: O(n * W)
 */
int ZeroOneKnapsack2DWithBacktrack(int max_capacity, const vector<Item>& items, vector<int>& selected_items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(max_capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= max_capacity; ++j) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Backtracking to find selected items
    selected_items.assign(n, 0);
    int w = max_capacity;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected_items[i - 1] = 1;
            w -= items[i - 1].weight;
        }
    }

    return dp[n][max_capacity];
}

/**
 * Problem 2: 0-1 Knapsack without Backtracking (2D DP)
 * -----------------------------------------------------
 * 🧠 Description:
 * Given a set of items, each with a weight and value, determine the maximum value
 * that can be obtained by picking a subset whose total weight ≤ capacity.
 * Unlike Problem 1, we do not trace which items were chosen.
 *
 * 🔍 Example:
 * Input: items = [{A,1,1},{B,3,4},{C,4,5}], capacity = 7
 * Output: 9
 *
 * 🎯 Key Insight:
 * Classic 0-1 Knapsack DP where item is either picked or skipped.
 * No backtracking is performed to recover the path.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 *   dp[i][j] = max value with first i items and capacity j
 *
 * ✅ Base Case Initialization:
 *   dp[0][*] = 0
 *   dp[*][0] = 0
 *
 * ✅ Transition:
 *   if items[i-1].weight <= j:
 *     dp[i][j] = max(dp[i-1][j], dp[i-1][j - weight[i-1]] + value[i-1])
 *   else:
 *     dp[i][j] = dp[i-1][j]
 *
 * ✅ Iteration Order:
 *   i = 1 to n, j = 0 to W
 *
 * 🚨 Edge Cases:
 * - items empty or W == 0 → return 0
 *
 * ⏱️ Time: O(n * W)
 * 🧠 Space: O(n * W)
 */
int ZeroOneKnapsack2DWithoutBacktrack(int max_capacity, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(max_capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= max_capacity; ++j) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][max_capacity];
}

/**
 * Problem 3: 0-1 Knapsack Optimized (1D DP)
 * -----------------------------------------
 * 🧠 Description:
 * Space-optimized version of 0-1 Knapsack using a single 1D array.
 * Only keep current capacity states while iterating items.
 *
 * 🔍 Example:
 * Input: items = [{A,1,1},{B,3,4},{C,4,5}], capacity = 7
 * Output: 9
 *
 * 🎯 Key Insight:
 * The current state only depends on previous row's states → 1D array is sufficient.
 * Important: iterate capacity backwards to avoid overwriting needed states.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 *   dp[j] = max value achievable with capacity j
 *
 * ✅ Base Case Initialization:
 *   dp[0] = 0, all others initialized to 0
 *
 * ✅ Transition:
 *   for each item:
 *     for j = max_capacity down to item.weight:
 *       dp[j] = max(dp[j], dp[j - item.weight] + item.value)
 *
 * ✅ Iteration Order:
 *   Items outer, capacity from W → 0
 *
 * 🚨 Edge Cases:
 * - Zero items or capacity → result is 0
 *
 * ⏱️ Time: O(n * W)
 * 🧠 Space: O(W)
 */
int ZeroOneKnapsack1DWithBacktrack(int max_capacity, const vector<Item>& items, vector<int>& selected_items) {
    int n = items.size();
    vector<int> dp(max_capacity + 1, 0);
    vector<int> last(max_capacity + 1, -1); // Track path

    for (int i = 0; i < n; ++i) {
        for (int j = max_capacity; j >= items[i].weight; --j) {
            if (dp[j] < dp[j - items[i].weight] + items[i].value) {
                dp[j] = dp[j - items[i].weight] + items[i].value;
                last[j] = i; // Record selected item index
            }
        }
    }

    // Backtracking to find selected items
    selected_items.assign(n, 0);
    int w = max_capacity;
    while (w > 0 && last[w] != -1) {
        int idx = last[w];
        selected_items[idx] = 1;
        w -= items[idx].weight;
    }

    return dp[max_capacity];
}

/**
 * Problem 4: 0-1 Knapsack Optimized (1D DP without Backtracking)
 * ---------------------------------------------------------------
 * 🧠 Description:
 * Pure space-optimized implementation of the 0-1 Knapsack problem.
 * No reconstruction of which items were picked.
 *
 * 🔍 Example:
 * Input: items = [{1,1}, {3,4}, {4,5}], capacity = 7
 * Output: 9
 *
 * 🌟 Key Insight:
 * Tracking only total max value is enough when item list is not needed.
 * Avoids overhead of tracking `last[]` array.
 *
 * 🔧 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = max value that can be achieved with capacity j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0; all dp[j>0] initialized to 0
 *
 * ✅ Transition:
 * For each item i:
 *   For j = max_capacity → items[i].weight:
 *     dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value)
 *
 * ✅ Iteration Order:
 * - Outer loop: items
 * - Inner loop: j = max_capacity → weight
 *
 * ⚠️ Edge Cases:
 * - No items or capacity = 0 → answer is 0
 *
 * ⏱️ Time: O(n * W)
 * 🧠 Space: O(W)
 */
int ZeroOneKnapsack1DWithoutBacktrack(int max_capacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(max_capacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = max_capacity; j >= items[i].weight; --j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    return dp[max_capacity];
}

/**
 * Problem 5: 0-1 Knapsack (Brute Force with Backtracking)
 * -------------------------------------------------------
 * 🧠 Description:
 * Explore all possible subsets using DFS. Decide whether to include each item,
 * and track the selection yielding the maximum value under weight constraint.
 *
 * 🔍 Example:
 * Input: items = [{A, 1, 1}, {B, 3, 4}, {C, 4, 5}], capacity = 7
 * Output: 9 → Pick B and C (weights 3 + 4, values 4 + 5)
 *
 * 🌟 Key Insight:
 * Recursively explore the decision tree for each item: include it or not.
 * Use backtracking to update the best selection when a better value is found.
 *
 * 🔧 Backtracking Strategy:
 * ------------------------------------------------------------
 * ✅ State:
 *   idx = current index in the item list
 *   remaining_capacity = leftover capacity of the knapsack
 *   selected_items = binary vector representing selected items
 *
 * ✅ Base Case:
 *   If idx == items.size() or capacity == 0 → return 0
 *
 * ✅ Recursion:
 *   - Skip current item → value = dfs(idx+1, remaining)
 *   - Take current item (if weight fits):
 *       → value = value of current + dfs(idx+1, remaining - weight)
 *       → update selection if new value is better
 *
 * ⚠️ Edge Cases:
 * - Empty item list or zero capacity → return 0
 *
 * ⏱️ Time: O(2^n)
 * 🧠 Space: O(n) recursion stack
 */
int ZeroOneKnapsackBruteForce(int idx, int remaining_capacity, const vector<Item>& items, vector<int>& selected_items) {
    if (static_cast<size_t>(idx) == items.size() || remaining_capacity == 0) {
        return 0;
    }

    // Skip current item
    int not_pick = ZeroOneKnapsackBruteForce(idx + 1, remaining_capacity, items, selected_items);

    // Pick current item (if capacity allows)
    int pick = 0;
    if (items[idx].weight <= remaining_capacity) {
        vector<int> temp_selected = selected_items; // Copy current selection state
        temp_selected[idx] = 1;
        pick = items[idx].value + ZeroOneKnapsackBruteForce(idx + 1, remaining_capacity - items[idx].weight, items, temp_selected);

        // Update selection state if picking gives better value
        if (pick > not_pick) {
            selected_items = temp_selected;
        }
    }

    return max(pick, not_pick);
}

/**
 * Problem 6: Complete Knapsack Optimized (1D DP without Backtracking)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Each item can be used unlimited times. Find the max value achievable with given capacity.
 * 
 * 🔍 Example:
 * Input: items = [{2, 3}, {3, 4}, {4, 5}], capacity = 7
 * Output: 10 → Use item 1 (2x) and item 2 (1x)
 *
 * 🌟 Key Insight:
 * Unlike 0-1 Knapsack, we can use an item multiple times → iterate capacity forward.
 * 
 * 🔧 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = max value achievable with capacity j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0; others initialized to 0
 *
 * ✅ Transition:
 * For each item i:
 *   For j = items[i].weight to max_capacity:
 *     dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value)
 *
 * ✅ Iteration Order:
 * - Outer loop: items
 * - Inner loop: j from items[i].weight → max_capacity
 *
 * ⚠️ Edge Cases:
 * - Zero capacity or items → return 0
 *
 * ⏱️ Time: O(n * W)
 * 🧠 Space: O(W)
 */
int CompleteKnapsack1DWithoutBacktrack(int max_capacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(max_capacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = items[i].weight; j <= max_capacity; ++j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    return dp[max_capacity];
}

/**
 * Problem 7: Complete Knapsack (Brute Force with Backtracking)
 * -------------------------------------------------------------
 * 🧠 Description:
 * Try all possible counts for each item and recurse.
 *
 * 🔍 Example:
 * Input: items = [{2, 3}, {3, 4}], capacity = 6
 * Output: 9 (item 1 × 1 and item 2 × 1)
 *
 * 🌟 Key Insight:
 * Try picking 0 to max count for each item and explore all combinations.
 * Backtrack to retain the best configuration.
 *
 * 🔧 Backtracking Strategy:
 * ------------------------------------------------------------
 * ✅ State:
 *   idx = current item index
 *   remaining_capacity = remaining knapsack space
 *
 * ✅ Base Case:
 *   if idx == items.size() or remaining_capacity == 0 → return 0
 *
 * ✅ Recursion:
 *   Try count = 0 to remaining_capacity / item.weight
 *   Track total value and update item_counts if it's the best
 *
 * ⚠️ Edge Cases:
 * - Empty input → return 0
 *
 * ⏱️ Time: Exponential
 * 🧠 Space: O(n)
 */
int CompleteKnapsackBruteForce(int idx, int remaining_capacity, const vector<Item>& items, vector<int>& item_counts) {
    if (static_cast<size_t>(idx) == items.size() || remaining_capacity == 0) {
        return 0;
    }

    int max_val = 0;
    int max_items = remaining_capacity / items[idx].weight;

    for (int count = 0; count <= max_items; ++count) {
        vector<int> temp_counts = item_counts;
        temp_counts[idx] = count;
        int temp_val = count * items[idx].value + CompleteKnapsackBruteForce(idx + 1, remaining_capacity - count * items[idx].weight, items, temp_counts);

        if (temp_val > max_val) {
            max_val = temp_val;
            item_counts = temp_counts;
        }
    }

    return max_val;
}

/**
 * Problem 8: Partition Equal Subset Sum (LC 416)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, determine if it can be partitioned into two subsets such that their sums are equal.
 *
 * 🔍 Example:
 * Input: nums = [1,5,11,5]
 * Output: true
 * Explanation: The array can be split as [1, 5, 5] and [11], both summing to 11.
 *
 * 🎯 Key Insight:
 * This is a classic 0/1 knapsack subset sum problem. Try to find a subset that sums to half of the total sum.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = whether a subset of `nums` can sum up to value j
 *
 * ✅ Base Case Initialization:
 * dp[0] = true → sum 0 is always possible
 *
 * ✅ Transition:
 * For each number:
 *   for j from target down to num:
 *     dp[j] |= dp[j - num]
 *
 * ✅ Iteration Order:
 * - Outer loop: each num
 * - Inner loop: j = target → num
 *
 * 🚨 Edge Cases:
 * - Odd total sum → cannot split evenly → return false
 *
 * ⏱️ Time: O(n * sum/2)
 * 🧠 Space: O(sum/2)
 */
bool CanPartition(vector<int>& nums_partition) {
    int sum = accumulate(nums_partition.begin(), nums_partition.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums_partition) {
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    return dp[target];
}

/**
 * Problem 9: Target Sum (LC 494)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given a list of numbers and a target, count how many ways '+' or '-' can be added to reach the target.
 *
 * 🔍 Example:
 * Input: nums = [1,1,1,1,1], target = 3
 * Output: 5
 *
 * 🎯 Key Insight:
 * Transform to subset sum problem: new_target = (sum + target) / 2
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = number of ways to sum to j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 1
 *
 * ✅ Transition:
 * For each num:
 *   for j from new_target down to num:
 *     dp[j] += dp[j - num]
 *
 * ✅ Iteration Order:
 * - Outer loop: each num
 * - Inner loop: j = new_target → num
 *
 * 🚨 Edge Cases:
 * - Invalid transformation: (sum + target) is odd → return 0
 *
 * ⏱️ Time: O(n * target)
 * 🧠 Space: O(target)
 */
int FindTargetSumWays(vector<int>& nums_target, int target) {
    int sum = accumulate(nums_target.begin(), nums_target.end(), 0);
    if ((sum + target) % 2 != 0 || sum < abs(target)) return 0;

    int new_target = (sum + target) / 2;
    vector<int> dp(new_target + 1, 0);
    dp[0] = 1;

    for (int num : nums_target) {
        for (int j = new_target; j >= num; --j) {
            dp[j] += dp[j - num];
        }
    }
    return dp[new_target];
}

/**
 * Problem 10: Coin Change II (LC 518)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given coin denominations and a total amount, return the number of ways to make up the amount using unlimited coins.
 *
 * 🔍 Example:
 * Input: coins = [1,2,5], amount = 5
 * Output: 4
 *
 * 🎯 Key Insight:
 * This is a complete knapsack counting problem.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = number of ways to make amount j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 1
 *
 * ✅ Transition:
 * For each coin:
 *   for j from coin to amount:
 *     dp[j] += dp[j - coin]
 *
 * ✅ Iteration Order:
 * - Outer loop: each coin
 * - Inner loop: j = coin → amount
 *
 * 🚨 Edge Cases:
 * - No coins → return 0 unless amount is 0
 *
 * ⏱️ Time: O(n * amount)
 * 🧠 Space: O(amount)
 */
int Change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int j = coin; j <= amount; ++j) {
            dp[j] += dp[j - coin];
        }
    }
    return dp[amount];
}

/**
 * Problem 11: Last Stone Weight II (LC 1049)
 * ------------------------------------------------------------
 * 🧠 Description:
 * You're given an array `stones`. In each turn, choose two stones and smash them.
 * You want to minimize the weight of the final stone.
 *
 * 🔍 Example:
 * Input: stones = [2,7,4,1,8,1]
 * Output: 1
 *
 * 🎯 Key Insight:
 * Partition stones into two subsets with minimum difference.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = max subset sum ≤ j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0
 *
 * ✅ Transition:
 * For each stone:
 *   for j from total/2 down to stone:
 *     dp[j] = max(dp[j], dp[j - stone] + stone)
 *
 * ✅ Iteration Order:
 * - Outer loop: stones
 * - Inner loop: j = target → stone
 *
 * 🚨 Edge Cases:
 * - Empty stones array → return 0
 *
 * ⏱️ Time: O(n * sum/2)
 * 🧠 Space: O(sum/2)
 */
int LastStoneWeightII(vector<int>& stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    int target = sum / 2;

    vector<int> dp(target + 1, 0);
    for (int stone : stones) {
        for (int j = target; j >= stone; --j) {
            dp[j] = max(dp[j], dp[j - stone] + stone);
        }
    }
    return sum - 2 * dp[target];
}

/**
 * Problem 12: Coin Change (LC 322)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given coin denominations and an amount, return the minimum number of coins needed to make the amount.
 *
 * 🔍 Example:
 * Input: coins = [1,2,5], amount = 11
 * Output: 3 (5 + 5 + 1)
 *
 * 🎯 Key Insight:
 * Classic unbounded knapsack variant minimizing coin count.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[j] = minimum coins to make amount j
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0; others = INF
 *
 * ✅ Transition:
 * For each coin:
 *   for j from coin to amount:
 *     dp[j] = min(dp[j], dp[j - coin] + 1)
 *
 * ✅ Iteration Order:
 * - Outer loop: coins
 * - Inner loop: j = coin → amount
 *
 * 🚨 Edge Cases:
 * - If dp[amount] is still INF → no solution → return -1
 *
 * ⏱️ Time: O(n * amount)
 * 🧠 Space: O(amount)
 */
int CoinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int coin : coins) {
        for (int j = coin; j <= amount; ++j) {
            if (dp[j - coin] != INT_MAX) {
                dp[j] = min(dp[j], dp[j - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

/**
 * Problem 13: Perfect Squares (LC 279)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Given an integer `n`, return the least number of perfect square numbers which sum to `n`.
 * 
 * 🔍 Example:
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 *
 * 🎯 Key Insight:
 * This is a complete knapsack problem where each perfect square can be used unlimited times.
 *
 * 💡 DP Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = minimum number of perfect squares needed to sum to i
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0 (0 numbers sum to 0)
 *
 * ✅ Transition:
 * For all square numbers (i*i):
 *   for j from i*i to n:
 *     dp[j] = min(dp[j], dp[j - i*i] + 1)
 *
 * ✅ Iteration Order:
 * - Outer loop: i from 1 to sqrt(n)
 * - Inner loop: j = i*i to n
 *
 * 🚨 Edge Cases:
 * - n = 0 → return 0
 *
 * ⏱️ Time: O(n * sqrt(n))
 * 🧠 Space: O(n)
 */
int NumSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i * i <= n; ++i) {
        for (int j = i * i; j <= n; ++j) {
            dp[j] = min(dp[j], dp[j - i * i] + 1);
        }
    }
    return dp[n];
}

int main() {
    vector<Item> items = {
        {"Gold Bar", 4, 9},
        {"Silver Coin", 3, 6},
        {"Bronze Medallion", 1, 2}
    };
    int max_capacity = 8;

    // Problem 1: 0-1 Knapsack (2D DP with Backtracking)
    vector<int> selected_items_2d;
    int max_value_2d_with_backtrack = ZeroOneKnapsack2DWithBacktrack(max_capacity, items, selected_items_2d);
    cout << "Problem 1: 0-1 Knapsack (2D DP with Backtracking): Maximum Value = " << max_value_2d_with_backtrack << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_2d.size(); ++i) {
        if (selected_items_2d[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // Problem 2: 0-1 Knapsack (2D DP without Backtracking)
    int max_value_2d_without_backtrack = ZeroOneKnapsack2DWithoutBacktrack(max_capacity, items);
    cout << "Problem 2: 0-1 Knapsack (2D DP without Backtracking): Maximum Value = " << max_value_2d_without_backtrack << endl;

    // Problem 3: 0-1 Knapsack (1D DP with Backtracking)
    vector<int> selected_items_1d;
    int max_value_1d_with_backtrack = ZeroOneKnapsack1DWithBacktrack(max_capacity, items, selected_items_1d);
    cout << "Problem 3: 0-1 Knapsack (1D DP with Backtracking): Maximum Value = " << max_value_1d_with_backtrack << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_1d.size(); ++i) {
        if (selected_items_1d[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // Problem 4: 0-1 Knapsack (1D DP without Backtracking)
    int max_value_1d_without_backtrack = ZeroOneKnapsack1DWithoutBacktrack(max_capacity, items);
    cout << "Problem 4: 0-1 Knapsack (1D DP without Backtracking): Maximum Value = " << max_value_1d_without_backtrack << endl;

    // Problem 5: 0-1 Knapsack (Brute Force with Backtracking)
    vector<int> selected_items_brute_force(items.size(), 0);
    int max_value_brute_force = ZeroOneKnapsackBruteForce(0, max_capacity, items, selected_items_brute_force);
    cout << "Problem 5: 0-1 Knapsack (Brute Force): Maximum Value = " << max_value_brute_force << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_brute_force.size(); ++i) {
        if (selected_items_brute_force[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // Problem 6: Complete Knapsack (1D DP without Backtracking)
    int max_value_complete_1d = CompleteKnapsack1DWithoutBacktrack(max_capacity, items);
    cout << "Problem 6: Complete Knapsack (1D DP): Maximum Value = " << max_value_complete_1d << endl;

    // Problem 7: Complete Knapsack (Brute Force with Backtracking)
    vector<int> item_counts_complete_brute_force(items.size(), 0);
    int max_value_complete_brute_force = CompleteKnapsackBruteForce(0, max_capacity, items, item_counts_complete_brute_force);
    cout << "Problem 7: Complete Knapsack (Brute Force): Maximum Value = " << max_value_complete_brute_force << endl;
    cout << "Selected Item Counts: ";
    for (size_t i = 0; i < item_counts_complete_brute_force.size(); ++i) {
        if (item_counts_complete_brute_force[i] > 0) {
            cout << items[i].name << " x" << item_counts_complete_brute_force[i] << " ";
        }
    }
    cout << endl;

    // Problem 8: Partition Equal Subset Sum (LC 416)
    vector<int> nums_partition = {1, 5, 11, 5};
    cout << "Problem 8: Partition Equal Subset Sum: " << (CanPartition(nums_partition) ? "true" : "false") << endl;

    // Problem 9: Target Sum (LC 494)
    vector<int> nums_target = {1, 1, 1, 1, 1};
    int target = 3;
    cout << "Problem 9: Target Sum Ways: " << FindTargetSumWays(nums_target, target) << endl;

    // Problem 10: Coin Change II (LC 518)
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 5;
    cout << "Problem 10: Coin Change II: " << Change(amount1, coins1) << endl;

    // Problem 11: Last Stone Weight II (LC 1049)
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "Problem 11: Last Stone Weight II: " << LastStoneWeightII(stones) << endl;

    // Problem 12: Coin Change (LC 322)
    vector<int> coins2 = {1, 2, 5};
    int amount2 = 11;
    cout << "Problem 12: Coin Change (Fewest Coins): " << CoinChange(coins2, amount2) << endl;

    // Problem 13: Perfect Squares (LC 279)
    int n = 12;
    cout << "Problem 13: Minimum Perfect Squares: " << NumSquares(n) << endl;

    return 0;
}