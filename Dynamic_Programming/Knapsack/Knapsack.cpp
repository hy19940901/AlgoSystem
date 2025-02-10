#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    return 0;
}
