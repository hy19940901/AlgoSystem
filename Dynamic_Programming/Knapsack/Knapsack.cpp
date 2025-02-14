#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

// ==========================
// 0-1 Knapsack (2D Array with Backtracking)
// ==========================
int zeroOneKnapsack2DWithBacktrack(int maxCapacity, const vector<Item>& items, vector<int>& selectedItems) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxCapacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= maxCapacity; ++j) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Backtracking to find selected items
    selectedItems.assign(n, 0);
    int w = maxCapacity;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems[i - 1] = 1;
            w -= items[i - 1].weight;
        }
    }

    return dp[n][maxCapacity];
}

// ===========================
// 0-1 Knapsack (2D Array without Backtracking)
// ===========================
int zeroOneKnapsack2DWithoutBacktrack(int maxCapacity, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxCapacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= maxCapacity; ++j) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][maxCapacity];
}

// ============================
// 0-1 Knapsack (1D Array with Backtracking)
// ============================
int zeroOneKnapsack1DWithBacktrack(int maxCapacity, const vector<Item>& items, vector<int>& selectedItems) {
    int n = items.size();
    vector<int> dp(maxCapacity + 1, 0);
    vector<int> last(maxCapacity + 1, -1); // Track path

    for (int i = 0; i < n; ++i) {
        for (int j = maxCapacity; j >= items[i].weight; --j) {
            if (dp[j] < dp[j - items[i].weight] + items[i].value) {
                dp[j] = dp[j - items[i].weight] + items[i].value;
                last[j] = i; // Record selected item index
            }
        }
    }

    // Backtracking to find selected items
    selectedItems.assign(n, 0);
    int w = maxCapacity;
    while (w > 0 && last[w] != -1) {
        int idx = last[w];
        selectedItems[idx] = 1;
        w -= items[idx].weight;
    }

    return dp[maxCapacity];
}

// =============================
// 0-1 Knapsack (1D Array without Backtracking)
// =============================
int zeroOneKnapsack1DWithoutBacktrack(int maxCapacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(maxCapacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = maxCapacity; j >= items[i].weight; --j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    return dp[maxCapacity];
}

// =====================
// 0-1 Knapsack (Brute Force with Backtracking)
// =====================
int zeroOneKnapsackBruteForce(int idx, int remainingCapacity, const vector<Item>& items, vector<int>& selectedItems) {
    if (idx == items.size() || remainingCapacity == 0) {
        return 0;
    }

    // Skip current item
    int notPick = zeroOneKnapsackBruteForce(idx + 1, remainingCapacity, items, selectedItems);

    // Pick current item (if capacity allows)
    int pick = 0;
    if (items[idx].weight <= remainingCapacity) {
        vector<int> tempSelected = selectedItems; // Copy current selection state
        tempSelected[idx] = 1;
        pick = items[idx].value + zeroOneKnapsackBruteForce(idx + 1, remainingCapacity - items[idx].weight, items, tempSelected);

        // Update selection state if picking gives better value
        if (pick > notPick) {
            selectedItems = tempSelected;
        }
    }

    return max(pick, notPick);
}

// =====================
// Complete Knapsack (1D Array without Backtracking)
// =====================
int completeKnapsack1DWithoutBacktrack(int maxCapacity, const vector<Item>& items) {
    int n = items.size();
    vector<int> dp(maxCapacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = items[i].weight; j <= maxCapacity; ++j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    return dp[maxCapacity];
}

// =====================
// Complete Knapsack (Brute Force with Backtracking)
// =====================
int completeKnapsackBruteForce(int idx, int remainingCapacity, const vector<Item>& items, vector<int>& itemCounts) {
    if (idx == items.size() || remainingCapacity == 0) {
        return 0;
    }

    int maxVal = 0;
    int maxItems = remainingCapacity / items[idx].weight;

    for (int count = 0; count <= maxItems; ++count) {
        vector<int> tempCounts = itemCounts;
        tempCounts[idx] = count;
        int tempVal = count * items[idx].value + completeKnapsackBruteForce(idx + 1, remainingCapacity - count * items[idx].weight, items, tempCounts);

        if (tempVal > maxVal) {
            maxVal = tempVal;
            itemCounts = tempCounts;
        }
    }

    return maxVal;
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
bool canPartition(vector<int>& numsPartition) {
    int sum = accumulate(numsPartition.begin(), numsPartition.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : numsPartition) {
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    return dp[target];
}

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
int findTargetSumWays(vector<int>& numsTarget, int target) {
    int sum = accumulate(numsTarget.begin(), numsTarget.end(), 0);
    if ((sum + target) % 2 != 0 || sum < abs(target)) return 0;

    int newTarget = (sum + target) / 2;
    vector<int> dp(newTarget + 1, 0);
    dp[0] = 1;

    for (int num : numsTarget) {
        for (int j = newTarget; j >= num; --j) {
            dp[j] += dp[j - num];
        }
    }
    return dp[newTarget];
}

/*
 * Problem 3: Coin Change II (LC 518)
 * Description:
 * Given an integer array coins and an integer amount, return the number of ways to make up that amount.
 *
 * Example:
 * Input: coins = [1,2,5], amount = 5
 * Output: 4
 */
int change(int amount, vector<int>& coins) {
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
 * Problem 4: Last Stone Weight II (LC 1049)
 * Description:
 * You are given an array stones where stones[i] is the weight of the ith stone. We combine two stones
 * repeatedly until one stone remains. The goal is to minimize the remaining stone's weight.
 *
 * Example:
 * Input: stones = [2,7,4,1,8,1]
 * Output: 1
 */
int lastStoneWeightII(vector<int>& stones) {
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
 * Problem 5: Coin Change (LC 322)
 * Description:
 * Given an integer array coins representing different coin denominations and an integer amount,
 * return the minimum number of coins needed to make up the amount.
 *
 * Example:
 * Input: coins = [1,2,5], amount = 11
 * Output: 3
 */
int coinChange(vector<int>& coins, int amount) {
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
 * Problem 6: Perfect Squares (LC 279)
 * Description:
 * Given an integer `n`, return the least number of perfect squares that sum to `n`.
 *
 * Example:
 * Input: n = 12
 * Output: 3
 */
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i * i <= n; ++i) {
        for (int j = i * i; j <= n; ++j) {
            dp[j] = min(dp[j], dp[j - i * i] + 1);
        }
    }
    return dp[n];
}

// =====================
// Main Function: Testing all versions
// =====================
int main() {
    vector<Item> items = {
        {"Gold Bar", 4, 9},
        {"Silver Coin", 3, 6},
        {"Bronze Medallion", 1, 2}
    };

    int maxCapacity = 8;

    // 2D Array with Backtracking
    vector<int> selectedItems2D;
    int maxValue2DWithBacktrack = zeroOneKnapsack2DWithBacktrack(maxCapacity, items, selectedItems2D);
    cout << "2D Array (With Backtracking): Maximum Value = " << maxValue2DWithBacktrack << endl;
    cout << "Selected Items: ";
    for (int i = 0; i < selectedItems2D.size(); ++i) {
        if (selectedItems2D[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // 2D Array without Backtracking
    int maxValue2DWithoutBacktrack = zeroOneKnapsack2DWithoutBacktrack(maxCapacity, items);
    cout << "2D Array (Without Backtracking): Maximum Value = " << maxValue2DWithoutBacktrack << endl;

    // 1D Array with Backtracking
    vector<int> selectedItems1D;
    int maxValue1DWithBacktrack = zeroOneKnapsack1DWithBacktrack(maxCapacity, items, selectedItems1D);
    cout << "1D Array (Rolling Array, With Backtracking): Maximum Value = " << maxValue1DWithBacktrack << endl;
    cout << "Selected Items: ";
    for (int i = 0; i < selectedItems1D.size(); ++i) {
        if (selectedItems1D[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // 1D Array without Backtracking
    int maxValue1DWithoutBacktrack = zeroOneKnapsack1DWithoutBacktrack(maxCapacity, items);
    cout << "1D Array (Rolling Array, Without Backtracking): Maximum Value = " << maxValue1DWithoutBacktrack << endl;

    // Brute Force with Backtracking
    vector<int> selectedItemsBruteForce(items.size(), 0);
    int maxValueBruteForce = zeroOneKnapsackBruteForce(0, maxCapacity, items, selectedItemsBruteForce);
    cout << "Brute Force (With Backtracking): Maximum Value = " << maxValueBruteForce << endl;
    cout << "Selected Items: ";
    for (int i = 0; i < selectedItemsBruteForce.size(); ++i) {
        if (selectedItemsBruteForce[i]) cout << items[i].name << " ";
    }
    cout << endl;

    // Complete Knapsack (Rolling Array, Without Backtracking)
    int maxValueComplete1D = completeKnapsack1DWithoutBacktrack(maxCapacity, items);
    cout << "Complete Knapsack (Rolling Array, Without Backtracking): Maximum Value = " << maxValueComplete1D << endl;

    // Complete Knapsack (Brute Force with Backtracking)
    vector<int> itemCountsCompleteBruteForce(items.size(), 0);
    int maxValueCompleteBruteForce = completeKnapsackBruteForce(0, maxCapacity, items, itemCountsCompleteBruteForce);
    cout << "Complete Knapsack (Brute Force with Backtracking): Maximum Value = " << maxValueCompleteBruteForce << endl;
    cout << "Selected Item Counts: ";
    for (int i = 0; i < itemCountsCompleteBruteForce.size(); ++i) {
        if (itemCountsCompleteBruteForce[i] > 0) {
            cout << items[i].name << " x" << itemCountsCompleteBruteForce[i] << " ";
        }
    }
    cout << endl;

    // Problem 1: Partition Equal Subset Sum
    vector<int> numsPartition = {1, 5, 11, 5};
    cout << "Problem 1: Can Partition Equal Subset Sum: " << (canPartition(numsPartition) ? "true" : "false") << endl;

    // Problem 2: Target Sum
    vector<int> numsTarget = {1, 1, 1, 1, 1};
    int target = 3;
    cout << "Problem 2: Target Sum Ways: " << findTargetSumWays(numsTarget, target) << endl;

    // Problem 3: Coin Change II
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 5;
    cout << "Problem 3: Ways to Make Change: " << change(amount1, coins1) << endl;

    // Problem 4: Last Stone Weight II
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "Problem 4: Last Stone Weight II: " << lastStoneWeightII(stones) << endl;

    // Problem 5: Coin Change
    vector<int> coins2 = {1, 2, 5};
    int amount2 = 11;
    cout << "Problem 5: Fewest Coins Needed: " << coinChange(coins2, amount2) << endl;

    // Problem 6: Perfect Squares
    int n = 12;
    cout << "Problem 6: Minimum Perfect Squares Needed: " << numSquares(n) << endl;

    return 0;
}
