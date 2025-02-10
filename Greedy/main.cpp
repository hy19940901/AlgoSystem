#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

/**
 * Problem 1: Assign Cookies (LC 455)
 * Description:
 * Given two arrays g and s, representing the greed factors of children and sizes of cookies respectively.
 * Each child can only have one cookie, and a child can be satisfied if the cookie size is greater than
 * or equal to their greed factor. Return the maximum number of children that can be satisfied.
 */
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0;
    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) i++;
        j++;
    }
    return i;
}

/**
 * Problem 2: Jump Game (LC 55)
 * Description:
 * Determine if you can reach the last index in an array where each element represents the maximum jump length.
 */
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    return true;
}

/**
 * Problem 3: Jump Game II (LC 45)
 * Description:
 * Find the minimum number of jumps required to reach the last index in an array.
 */
int jump(vector<int>& nums) {
    int jumps = 0, end = 0, farthest = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
        farthest = max(farthest, i + nums[i]);
        if (i == end) {
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}

/**
 * Problem 4: Minimum Number of Arrows to Burst Balloons (LC 452)
 * Description:
 * Determine the minimum number of arrows needed to burst all balloons represented by intervals [start, end].
 */
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.empty()) return 0;
    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });
    int arrows = 1;
    int end = points[0][1];
    for (const auto& point : points) {
        if (point[0] > end) {
            arrows++;
            end = point[1];
        }
    }
    return arrows;
}

/**
 * Problem 5: Non-overlapping Intervals (LC 435)
 * Description:
 * Find the minimum number of intervals to remove to make the rest non-overlapping.
 */
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });
    int nonOverlapCount = 1;
    int end = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] >= end) {
            nonOverlapCount++;
            end = intervals[i][1];
        }
    }
    return intervals.size() - nonOverlapCount;
}

/**
 * Problem 6: Gas Station (LC 134)
 * Description:
 * Determine the starting gas station index to complete a circular route if possible.
 */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalTank = 0, currTank = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i) {
        totalTank += gas[i] - cost[i];
        currTank += gas[i] - cost[i];
        if (currTank < 0) {
            start = i + 1;
            currTank = 0;
        }
    }
    return totalTank >= 0 ? start : -1;
}

/**
 * Problem 7: Maximum Subarray (LC 53)
 * Description:
 * Find the contiguous subarray with the largest sum.
 */
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0], currentSum = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
// Greedy algorithm, kadane algorithm
int maxSubArray_kadane(vector<int>& nums) {
    int result = INT32_MIN;
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        count += nums[i];
        if (count > result) { // 取区间累计的最大值（相当于不断确定最大子序终止位置）
            result = count;
        }
        if (count <= 0) count = 0; // 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
    }
    return result;
}

/**
 * Problem 8: Candy Distribution (LC 135)
 * Description:
 * Each child has a rating, and you want to distribute candies such that:
 * - Each child gets at least one candy.
 * - A child with a higher rating gets more candies than its neighbors.
 * Return the minimum number of candies required.
 */
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1); // Give each child at least one candy
    // Left-to-right pass
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    }
    // Right-to-left pass
    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) candies[i] = max(candies[i], candies[i + 1] + 1);
    }
    return accumulate(candies.begin(), candies.end(), 0);
}

/**
 * Problem 9: Task Scheduler (LC 621)
 * Description:
 * You are given a list of tasks and a cooldown period `n`. Each task can only be executed after `n` intervals
 * since its last execution. Return the minimum time needed to finish all tasks.
 */
int leastInterval(vector<char>& tasks, int n) {
    vector<int> counts(26, 0);
    for (char task : tasks) counts[task - 'A']++;
    int maxCount = *max_element(counts.begin(), counts.end());
    int maxFreqTasks = count(counts.begin(), counts.end(), maxCount);
    return max((int)tasks.size(), (maxCount - 1) * (n + 1) + maxFreqTasks);
}

int main() {
    // Test Problem 1: Assign Cookies
    vector<int> g = {1, 2, 3}, s = {1, 1};
    cout << "Assign Cookies: " << findContentChildren(g, s) << endl;

    // Test Problem 2: Jump Game
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Can Jump: " << (canJump(nums1) ? "True" : "False") << endl;

    // Test Problem 3: Jump Game II
    vector<int> nums2 = {2, 3, 1, 1, 4};
    cout << "Minimum Jumps: " << jump(nums2) << endl;

    // Test Problem 4: Minimum Number of Arrows to Burst Balloons
    vector<vector<int>> points = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    cout << "Minimum Arrows: " << findMinArrowShots(points) << endl;

    // Test Problem 5: Non-overlapping Intervals
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Erase Overlap Intervals: " << eraseOverlapIntervals(intervals) << endl;

    // Test Problem 6: Gas Station
    vector<int> gas = {1, 2, 3, 4, 5}, cost = {3, 4, 5, 1, 2};
    cout << "Gas Station Start Index: " << canCompleteCircuit(gas, cost) << endl;

    // Test Problem 7: Maximum Subarray
    vector<int> nums3 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << maxSubArray(nums3) << endl;
    cout << "Maximum Subarray Sum: " << maxSubArray_kadane(nums3) << endl;

    // Test Problem 8: Candy Distribution
    vector<int> ratings = {1, 0, 2};
    cout << "Candy Distribution: " << candy(ratings) << endl;

    // Test Problem 9: Task Scheduler
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    cout << "Task Scheduler: " << leastInterval(tasks, n) << endl;

    return 0;
}
