#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

int zeroOneKnapsack(int maxCapacity, const vector<Item>& items, vector<int>& selectedItems) {
    int itemCount = items.size();
    vector<vector<int>> dp(itemCount + 1, vector<int>(maxCapacity + 1, 0));

    for (int i = 1; i <= itemCount; ++i) {
        for (int j = 1; j <= maxCapacity; ++j) {
            if (items[i-1].weight <= j) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-items[i-1].weight] + items[i-1].value);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    // Backtracking to find which items were selected.
    int w = maxCapacity;
    selectedItems.assign(itemCount, 0);
    for (int i = itemCount; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selectedItems[i-1] = 1;
            w -= items[i-1].weight;
        }
    }

    return dp[itemCount][maxCapacity];
}

int completeKnapsack(int maxCapacity, const vector<Item>& items, vector<int>& itemCounts) {
    int n = items.size();
    vector<int> dp(maxCapacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = items[i].weight; j <= maxCapacity; ++j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    // Backtracking to find count of each item selected.
    itemCounts.assign(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        while (maxCapacity >= items[i].weight && dp[maxCapacity] == dp[maxCapacity - items[i].weight] + items[i].value) {
            itemCounts[i]++;
            maxCapacity -= items[i].weight;
        }
    }

    return dp.back();
}

// 0-1背包问题的DFS
int dfs01(int idx, int remainingCapacity, const vector<Item>& items, vector<int>& selectedItems) {
    if (idx == items.size() || remainingCapacity == 0) {
        return 0;
    }

    // 不选择当前物品
    int notPick = dfs01(idx + 1, remainingCapacity, items, selectedItems);

    if (items[idx].weight <= remainingCapacity) {
        // 选择当前物品
        selectedItems[idx] = 1;
        int pick = items[idx].value + dfs01(idx + 1, remainingCapacity - items[idx].weight, items, selectedItems);
        selectedItems[idx] = 0;

        return max(pick, notPick);
    }

    return notPick;
}

// 完全背包问题的DFS
int dfsComplete(int idx, int remainingCapacity, const vector<Item>& items, vector<int>& itemCounts) {
    if (idx == items.size() || remainingCapacity == 0) {
        return 0;
    }

    int maxVal = 0;
    int maxItems = remainingCapacity / items[idx].weight;

    for (int count = 0; count <= maxItems; count++) {
        int tempVal = count * items[idx].value + dfsComplete(idx + 1, remainingCapacity - count * items[idx].weight, items, itemCounts);
        if (tempVal > maxVal) {
            maxVal = tempVal;
            itemCounts[idx] = count;
        }
    }

    return maxVal;
}

int main() {
    vector<Item> items = {
        {"Gold Bar", 4, 9},
        {"Silver Coin", 3, 6},
        {"Bronze Medallion", 1, 2}
    };

    int maxCapacity = 50;

    cout << "For 0-1 Knapsack:" << endl;
    vector<int> selectedItemsFor01;
    int maxValue01 = zeroOneKnapsack(maxCapacity, items, selectedItemsFor01);
    cout << "Maximum value is: " << maxValue01 << endl;
    cout << "Selected items are:" << endl;
    for (int i = 0; i < items.size(); ++i) {
        if (selectedItemsFor01[i] == 1) {
            cout << items[i].name << endl;
        }
    }

    cout << "\nFor Complete Knapsack:" << endl;
    vector<int> selectedItemCounts;
    int maxValueComplete = completeKnapsack(maxCapacity, items, selectedItemCounts);
    cout << "Maximum value is: " << maxValueComplete << endl;
    cout << "Selected items count is:" << endl;
    for (int i = 0; i < items.size(); ++i) {
        if (selectedItemCounts[i] > 0) {
            cout << items[i].name << ": " << selectedItemCounts[i] << " units" << endl;
        }
    }

    cout << "For 0-1 Knapsack using DFS:" << endl;
    vector<int> selectedItemsFor01DFS(items.size(), 0);
    int maxValue01DFS = dfs01(0, maxCapacity, items, selectedItemsFor01DFS);
    cout << "Maximum value is: " << maxValue01DFS << endl;
    cout << "Selected items are:" << endl;
    for (int i = 0; i < items.size(); ++i) {
        if (selectedItemsFor01DFS[i] == 1) {
            cout << items[i].name << endl;
        }
    }

    cout << "\nFor Complete Knapsack using DFS:" << endl;
    vector<int> selectedItemCountsDFS(items.size(), 0);
    int maxValueCompleteDFS = dfsComplete(0, maxCapacity, items, selectedItemCountsDFS);
    cout << "Maximum value is: " << maxValueCompleteDFS << endl;
    cout << "Selected items count is:" << endl;
    for (int i = 0; i < items.size(); ++i) {
        if (selectedItemCountsDFS[i] > 0) {
            cout << items[i].name << ": " << selectedItemCountsDFS[i] << " units" << endl;
        }
    }

    return 0;
}