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

// ==========================
// 0-1 Knapsack (2D Array with Backtracking)
// ==========================
/*
Problem: 0-1 Knapsack (2D DP with Backtracking)
----------------------------------------------
Given a list of items with weights and values, and a maximum capacity,
find the maximum value achievable without exceeding the capacity.
Also track which items are selected.

DP Definition:
- dp[i][j]: max value using first i items within capacity j

Transition:
- If weight[i-1] <= j:
    dp[i][j] = max(dp[i-1][j], dp[i-1][j - weight[i-1]] + value[i-1])
- Else:
    dp[i][j] = dp[i-1][j]

Backtracking:
- Compare dp[i][j] vs dp[i-1][j] to determine if item i-1 is selected

Time Complexity: O(n * W)
Space Complexity: O(n * W)
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

// ===========================
// 0-1 Knapsack (2D Array without Backtracking)
// ===========================
/*
Problem: 0-1 Knapsack (2D DP without Backtracking)
--------------------------------------------------
Same logic as above, but no item tracking.

Time Complexity: O(n * W)
Space Complexity: O(n * W)
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

// ============================
// 0-1 Knapsack (1D Array with Backtracking)
// ============================
/*
Problem: 0-1 Knapsack (1D DP with Backtracking)
----------------------------------------------
Use a 1D array to reduce space and a tracking array to recover selection.

DP Definition:
- dp[j]: max value with capacity j
- last[j]: index of last item used to reach dp[j]

Transition:
- For each item i, traverse j from max_capacity to weight[i] (reverse)

Backtracking:
- Trace last[j] to reconstruct selected items

Time Complexity: O(n * W)
Space Complexity: O(W)
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

// =============================
// 0-1 Knapsack (1D Array without Backtracking)
// =============================
/*
Problem: 0-1 Knapsack (1D DP without Backtracking)
--------------------------------------------------
Space-optimized version of 0-1 knapsack without selection recovery.

Time Complexity: O(n * W)
Space Complexity: O(W)
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

// =====================
// 0-1 Knapsack (Brute Force with Backtracking)
// =====================
/*
Problem: 0-1 Knapsack (Brute Force with Backtracking)
-----------------------------------------------------
Try all subsets using DFS. Update selected items if new path gives better value.

Time Complexity: O(2^n)
Space Complexity: O(n)
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

// =====================
// Complete Knapsack (1D Array without Backtracking)
// =====================
/*
Problem: Complete Knapsack (1D DP without Backtracking)
-------------------------------------------------------
Each item can be chosen unlimited times.

DP Definition:
- dp[j]: max value for capacity j

Transition:
- For each item i:
    for j from weight[i] to max_capacity:
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i])

Time Complexity: O(n * W)
Space Complexity: O(W)
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

// =====================
// Complete Knapsack (Brute Force with Backtracking)
// =====================
/*
Problem: Complete Knapsack (Brute Force with Backtracking)
----------------------------------------------------------
Try all count options for each item (0 to max allowed).
Track item counts leading to optimal value.

Time Complexity: Exponential
Space Complexity: O(n)
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

/*
 * Problem 1: Partition Equal Subset Sum (LC 416)
 * Description:
 * Given an integer array nums, return true if you can partition the array into two subsets
 * such that the sum of the elements in both subsets is equal.
 *
 * Example:
 * Input: nums = [1,5,11,5]
 * Output: true
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
/*
Problem: Partition Equal Subset Sum (LC 416)
--------------------------------------------
Determine if the array can be split into two subsets with equal sum.

Approach:
- Equivalent to checking if there's a subset that sums to total / 2

DP Definition:
- dp[j]: whether subset sum j is possible

Transition:
- dp[j] = dp[j] || dp[j - num]

Time Complexity: O(n * sum/2)
Space Complexity: O(sum/2)
*/

/*
 * Problem 2: Target Sum (LC 494)
 * Description:
 * You are given an integer array nums and an integer target. You want to build an expression
 * by inserting '+' or '-' before each number. Return the number of ways you can build the expression.
 *
 * Example:
 * Input: nums = [1,1,1,1,1], target = 3
 * Output: 5
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
/*
Problem: Target Sum (LC 494)
-----------------------------
Assign '+' or '-' to each number to reach target sum.

Transformation:
- Subset sum with new_target = (total + target) / 2

DP Definition:
- dp[j]: number of ways to reach sum j

Transition:
- dp[j] += dp[j - num]

Time Complexity: O(n * new_target)
Space Complexity: O(new_target)
*/

/*
 * Problem 3: Coin Change II (LC 518)
 * Description:
 * Given an integer array coins and an integer amount, return the number of ways to make up that amount.
 *
 * Example:
 * Input: coins = [1,2,5], amount = 5
 * Output: 4
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
/*
Problem: Coin Change II (LC 518)
--------------------------------
Return the number of combinations that make up a given amount using unlimited coins.

DP Definition:
- dp[j]: number of ways to form amount j

Transition:
- For each coin:
    for j from coin to amount:
        dp[j] += dp[j - coin]

Time Complexity: O(n * amount)
Space Complexity: O(amount)
*/

/*
 * Problem 4: Last Stone Weight II (LC 1049)
 * Description:
 * You are given an array stones where stones[i] is the weight of the ith stone. We combine two stones
 * repeatedly until one stone remains. The goal is to minimize the remaining stone's weight.
 *
 * Example:
 * Input: stones = [2,7,4,1,8,1]
 * Output: 1
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
/*
Problem: Last Stone Weight II (LC 1049)
---------------------------------------
Split stones into two subsets with minimal difference in sum.

Equivalent to:
- Maximize subset sum <= total/2

DP Definition:
- dp[j]: max subset sum not exceeding j

Transition:
- dp[j] = max(dp[j], dp[j - stone] + stone)

Final Answer: total - 2 * dp[sum/2]

Time Complexity: O(n * sum/2)
Space Complexity: O(sum/2)
*/

/*
 * Problem 5: Coin Change (LC 322)
 * Description:
 * Given an integer array coins representing different coin denominations and an integer amount,
 * return the minimum number of coins needed to make up the amount.
 *
 * Example:
 * Input: coins = [1,2,5], amount = 11
 * Output: 3
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
/*
Problem: Coin Change (LC 322)
------------------------------
Find the minimum number of coins to make up a given amount.

DP Definition:
- dp[j]: min number of coins needed to make amount j

Transition:
- dp[j] = min(dp[j], dp[j - coin] + 1)

Time Complexity: O(n * amount)
Space Complexity: O(amount)
*/

/*
 * Problem 6: Perfect Squares (LC 279)
 * Description:
 * Given an integer `n`, return the least number of perfect squares that sum to `n`.
 *
 * Example:
 * Input: n = 12
 * Output: 3
 */
/**
 * Problem: Perfect Squares (LC 279)
 * ---------------------------------
 * Return the least number of perfect square numbers which sum to n.
 *
 * dp[i]: minimum number of perfect squares that sum to i
 *
 * Time: O(n * sqrt(n))
 * Space: O(n)
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
/*
Problem: Perfect Squares (LC 279)
---------------------------------
Find the minimum number of perfect square numbers that sum to n.

DP Definition:
- dp[j]: min number of squares summing to j

Transition:
- For all i*i <= j:
    dp[j] = min(dp[j], dp[j - i*i] + 1)

Time Complexity: O(n * sqrt(n))
Space Complexity: O(n)
*/

// =====================
// Main Function: Testing all versions
// =====================
int main() {
    vector<Item> items = {
        {"Gold Bar", 4, 9},
        {"Silver Coin", 3, 6},
        {"Bronze Medallion", 1, 2}
    };

    int max_capacity = 8;

    // 2D Array with Backtracking
    vector<int> selected_items_2d;
    int max_value_2d_with_backtrack = ZeroOneKnapsack2DWithBacktrack(max_capacity, items, selected_items_2d);
    cout << "2D Array (With Backtracking): Maximum Value = " << max_value_2d_with_backtrack << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_2d.size(); ++i) {
        if (selected_items_2d[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // 2D Array without Backtracking
    int max_value_2d_without_backtrack = ZeroOneKnapsack2DWithoutBacktrack(max_capacity, items);
    cout << "2D Array (Without Backtracking): Maximum Value = " << max_value_2d_without_backtrack << endl;

    // 1D Array with Backtracking
    vector<int> selected_items_1d;
    int max_value_1d_with_backtrack = ZeroOneKnapsack1DWithBacktrack(max_capacity, items, selected_items_1d);
    cout << "1D Array (Rolling Array, With Backtracking): Maximum Value = " << max_value_1d_with_backtrack << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_1d.size(); ++i) {
        if (selected_items_1d[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // 1D Array without Backtracking
    int max_value_1d_without_backtrack = ZeroOneKnapsack1DWithoutBacktrack(max_capacity, items);
    cout << "1D Array (Rolling Array, Without Backtracking): Maximum Value = " << max_value_1d_without_backtrack << endl;

    // Brute Force with Backtracking
    vector<int> selected_items_brute_force(items.size(), 0);
    int max_value_brute_force = ZeroOneKnapsackBruteForce(0, max_capacity, items, selected_items_brute_force);
    cout << "Brute Force (With Backtracking): Maximum Value = " << max_value_brute_force << endl;
    cout << "Selected Items: ";
    for (size_t i = 0; i < selected_items_brute_force.size(); ++i) {
        if (selected_items_brute_force[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // Complete Knapsack (Rolling Array, Without Backtracking)
    int max_value_complete_1d = CompleteKnapsack1DWithoutBacktrack(max_capacity, items);
    cout << "Complete Knapsack (Rolling Array, Without Backtracking): Maximum Value = " << max_value_complete_1d << endl;

    // Complete Knapsack (Brute Force with Backtracking)
    vector<int> item_counts_complete_brute_force(items.size(), 0);
    int max_value_complete_brute_force = CompleteKnapsackBruteForce(0, max_capacity, items, item_counts_complete_brute_force);
    cout << "Complete Knapsack (Brute Force with Backtracking): Maximum Value = " << max_value_complete_brute_force << endl;
    cout << "Selected Item Counts: ";
    for (size_t i = 0; i < item_counts_complete_brute_force.size(); ++i) {
        if (item_counts_complete_brute_force[i] > 0) {
            cout << items[i].name << " x" << item_counts_complete_brute_force[i] << " ";
        }
    }
    cout << endl;

    // Problem 1: Partition Equal Subset Sum
    vector<int> nums_partition = {1, 5, 11, 5};
    cout << "Problem 1: Can Partition Equal Subset Sum: " << (CanPartition(nums_partition) ? "true" : "false") << endl;

    // Problem 2: Target Sum
    vector<int> nums_target = {1, 1, 1, 1, 1};
    int target = 3;
    cout << "Problem 2: Target Sum Ways: " << FindTargetSumWays(nums_target, target) << endl;

    // Problem 3: Coin Change II
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 5;
    cout << "Problem 3: Ways to Make Change: " << Change(amount1, coins1) << endl;

    // Problem 4: Last Stone Weight II
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "Problem 4: Last Stone Weight II: " << LastStoneWeightII(stones) << endl;

    // Problem 5: Coin Change
    vector<int> coins2 = {1, 2, 5};
    int amount2 = 11;
    cout << "Problem 5: Fewest Coins Needed: " << CoinChange(coins2, amount2) << endl;

    // Problem 6: Perfect Squares
    int n = 12;
    cout << "Problem 6: Minimum Perfect Squares Needed: " << NumSquares(n) << endl;

    return 0;
}
