#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>
#include <climits>
#include <cstdint>
using namespace std;

/**
 * Problem 1: Assign Cookies (LC 455)
 * Description:
 * Given two arrays g and s, representing the greed factors of children and sizes of cookies respectively.
 * Each child can only have one cookie, and a child can be satisfied if the cookie size is greater than
 * or equal to their greed factor. Return the maximum number of children that can be satisfied.
 *
 * Example:
 * Input: g = [1,2,3], s = [1,1]
 * Output: 1
 */
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0;
    while (static_cast<size_t>(i) < g.size() && static_cast<size_t>(j) < s.size()) {
        if (s[j] >= g[i]) i++;
        j++;
    }
    return i;
}

/**
 * Problem 2: Jump Game (LC 55)
 * Description:
 * Determine if you can reach the last index in an array where each element represents the maximum jump length.
*
 * Example:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 */
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (static_cast<int>(i) > maxReach) return false;
        maxReach = max(maxReach, static_cast<int>(i) + nums[i]);
    }
    return true;
}

/**
 * Problem 3: Jump Game II (LC 45)
 * Description:
 * Find the minimum number of jumps required to reach the last index in an array.
 *
 * Example:
 * Input: nums = [2,3,1,1,4]
 * Output: 2
 */
int jump(vector<int>& nums) {
    int jumps = 0, end = 0, farthest = 0;
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        farthest = max(farthest, static_cast<int>(i) + nums[i]);
        if (static_cast<int>(i) == end) {
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
 *
 * Example:
 * Input: points = [[10,16], [2,8], [1,6], [7,12]]
 * Output: 2
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
 *
 * Example:
 * Input: intervals = [[1,2], [2,3], [3,4], [1,3]]
 * Output: 1
 */
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });
    int nonOverlapCount = 1;
    int end = intervals[0][1];
    for (size_t i = 1; i < intervals.size(); ++i) {
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
 *
 * Example:
 * Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 * Output: 3
 */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalTank = 0, currTank = 0, start = 0;
    for (size_t i = 0; i < gas.size(); ++i) {
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
 *
 * Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 */
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0], currentSum = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
// Greedy algorithm, kadane algorithm
int maxSubArray_kadane(vector<int>& nums) {
    int result = INT32_MIN;
    int count = 0;
    for (size_t i = 0; i < nums.size(); i++) {
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
 *
 * Example:
 * Input: ratings = [1,0,2]
 * Output: 5
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
 *
 * Example:
 * Input: tasks = ['A','A','A','B','B','B'], n = 2
 * Output: 8
 */
int leastInterval(vector<char>& tasks, int n) {
    vector<int> counts(26, 0);
    for (char task : tasks) counts[task - 'A']++;
    int maxCount = *max_element(counts.begin(), counts.end());
    int maxFreqTasks = count(counts.begin(), counts.end(), maxCount);
    return max((int)tasks.size(), (maxCount - 1) * (n + 1) + maxFreqTasks);
}

/**
 * Problem 10: Queue Reconstruction by Height (LC 406)
 * Description:
 * Given an array of people represented as [height, k], where k is the number of people in front who have
 * a height greater than or equal to this person. Reconstruct the queue.
 *
 * Example:
 * Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 * Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
 */
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
        return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
    });
    vector<vector<int>> result;
    for (auto& p : people) {
        result.insert(result.begin() + p[1], p);
    }
    return result;
}

/**
 * Problem 11: Partition Labels (LC 763)
 * Description:
 * Given a string, partition it into as many parts as possible such that each letter appears in at most one part.
 *
 * Example:
 * Input: s = "ababcbacadefegdehijhklij"
 * Output: [9,7,8]
 */
vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, 0);
    for (size_t i = 0; i < s.size(); ++i) {
        lastIndex[s[i] - 'a'] = i;
    }
    vector<int> partitions;
    int start = 0, end = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        end = max(end, lastIndex[s[i] - 'a']);
        if (static_cast<int>(i) == end) {
            partitions.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return partitions;
}

/**
 * Problem 12: Maximize Sum After K Negations (LC 1005)
 * Description:
 * Given an array `nums` and an integer `k`, flip the sign of `k` elements to maximize the sum.
 *
 * Example:
 * Input: nums = [4,2,3], k = 1
 * Output: 5
 */
int largestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() && k > 0 && nums[i] < 0; ++i, --k) {
        nums[i] = -nums[i];
    }
    return accumulate(nums.begin(), nums.end(), 0) - (k % 2 ? 2 * *min_element(nums.begin(), nums.end()) : 0);
}

/**
 * Problem 13: Minimum Cost to Connect Sticks (LC 1167)
 * Description:
 * Given an array of stick lengths, connect them with the minimum cost.
 *
 * Example:
 * Input: sticks = [2,4,3]
 * Output: 14
 */
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> pq(sticks.begin(), sticks.end());
    int cost = 0;
    while (pq.size() > 1) {
        int first = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        cost += first + second;
        pq.push(first + second);
    }
    return cost;
}

/**
 * Problem 14: Lemonade Change (LC 860)
 * Description:
 * You have `5`, `10`, and `20` dollar bills. You must provide change for each customer.
 * Return `true` if you can provide exact change to every customer in order.
 *
 * Example:
 * Input: bills = [5,5,5,10,20]
 * Output: true
 */
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    for (int bill : bills) {
        if (bill == 5) five++;
        else if (bill == 10) {
            if (five == 0) return false;
            five--; ten++;
        } else {
            if (ten > 0 && five > 0) { ten--; five--; }
            else if (five >= 3) { five -= 3; }
            else return false;
        }
    }
    return true;
}

/**
 * Problem 15: Two City Scheduling (LC 1029)
 * Description:
 * There are `2N` people, each assigned a cost to fly to city A and city B.
 * Return the minimum cost to fly `N` people to city A and `N` to city B.
 *
 * Example:
 * Input: costs = [[10,20],[30,200],[50,10],[20,30]]
 * Output: 110
 */
int twoCitySchedCost(vector<vector<int>>& costs) {
    sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b) {
        return (a[0] - a[1]) < (b[0] - b[1]);
    });
    int totalCost = 0, n = costs.size() / 2;
    for (int i = 0; i < n; i++) totalCost += costs[i][0];
    for (int i = n; i < 2 * n; i++) totalCost += costs[i][1];
    return totalCost;
}

/**
 * Problem 16: Minimum Deletions to Make Character Frequencies Unique (LC 1647)
 * Description:
 * Given a string, delete the fewest characters so that all characters have unique frequencies.
 *
 * Example:
 * Input: s = "aaabbbcc"
 * Output: 2
 */
int minDeletions(string s) {
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;
    unordered_set<int> seen;
    int deletions = 0;
    for (int f : freq) {
        while (f > 0 && seen.count(f)) {
            f--;
            deletions++;
        }
        seen.insert(f);
    }
    return deletions;
}

/**
 * Problem 17: Hand of Straights (LC 846)
 * Description:
 * Given a list of integers representing a hand of cards, check if we can form groups of `groupSize` consecutive cards.
 *
 * Example:
 * Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
 * Output: true
 */
bool isNStraightHand(vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize != 0) return false;
    map<int, int> count;
    for (int card : hand) count[card]++;
    for (auto& [card, freq] : count) {
        while (freq > 0) {
            for (int i = 0; i < groupSize; i++) {
                if (count[card + i] == 0) return false;
                count[card + i]--;
            }
            freq--;
        }
    }
    return true;
}

/**
 * Problem 18: Minimum Cost to Move Chips to The Same Position (LC 1217)
 * Description:
 * Given a list of chip positions, find the minimum cost to move all chips to the same position.
 *
 * Example:
 * Input: position = [1,2,3]
 * Output: 1
 */
int minCostToMoveChips(vector<int>& position) {
    int odd = 0, even = 0;
    for (int pos : position) {
        if (pos % 2 == 0) even++;
        else odd++;
    }
    return min(odd, even);
}

/**
 * Problem 19: Maximum Number of Events That Can Be Attended (LC 1353)
 * Description:
 * Each event has a start and end day. You can only attend one event per day.
 * Find the maximum number of events you can attend.
 *
 * Example:
 * Input: events = [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 */
int maxEvents(vector<vector<int>>& events) {
    sort(events.begin(), events.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    int i = 0, days = 0, n = events.size(), count = 0;
    while (i < n || !pq.empty()) {
        if (pq.empty() && i < n) days = events[i][0];
        while (i < n && events[i][0] == days) pq.push(events[i++][1]);
        while (!pq.empty() && pq.top() < days) pq.pop();
        if (!pq.empty()) { pq.pop(); count++; }
        days++;
    }
    return count;
}

/**
 * Problem 20: Boat to Save People (LC 881)
 * Description:
 * Given an array representing people's weights and a limit, find the minimum boats needed to rescue everyone.
 *
 * Example:
 * Input: people = [3,2,2,1], limit = 3
 * Output: 3
 */
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1, boats = 0;
    while (left <= right) {
        if (people[left] + people[right] <= limit) left++;
        right--;
        boats++;
    }
    return boats;
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

    // Test Problem 10: Queue Reconstruction by Height
    vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    auto queue_result = reconstructQueue(people);
    cout << "Reconstructed Queue: ";
    for (auto& p : queue_result) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    // Test Problem 11: Partition Labels
    string str_partition = "ababcbacadefegdehijhklij";
    auto partition_result = partitionLabels(str_partition);
    cout << "Partition Labels: ";
    for (int len : partition_result) {
        cout << len << " ";
    }
    cout << endl;

    // Test Problem 12: Maximize Sum After K Negations
    vector<int> nums = {4,2,3};
    int k = 1;
    cout << "Max Sum After K Negations: " << largestSumAfterKNegations(nums, k) << endl;

    // Test Problem 13: Minimum Cost to Connect Sticks
    vector<int> sticks = {2,4,3};
    cout << "Minimum Cost to Connect Sticks: " << connectSticks(sticks) << endl;

    // Test Problem 14: Lemonade Change
    vector<int> bills = {5,5,5,10,20};
    cout << "Lemonade Change: " << (lemonadeChange(bills) ? "True" : "False") << endl;

    // Test Problem 15: Two City Scheduling
    vector<vector<int>> costs = {{10,20},{30,200},{50,10},{20,30}};
    cout << "Two City Scheduling Cost: " << twoCitySchedCost(costs) << endl;

    // Test Problem 16: Minimum Deletions to Make Character Frequencies Unique
    string s_16 = "aaabbbcc";
    cout << "Min Deletions: " << minDeletions(s_16) << endl;

    // Test Problem 17: Hand of Straights
    vector<int> hand = {1,2,3,6,2,3,4,7,8};
    cout << "Hand of Straights: " << (isNStraightHand(hand, 3) ? "True" : "False") << endl;

    // Test Problem 18: Minimum Cost to Move Chips
    vector<int> chips = {1,2,3};
    cout << "Min Cost to Move Chips: " << minCostToMoveChips(chips) << endl;

    // Test Problem 19: Maximum Number of Events That Can Be Attended
    vector<vector<int>> events = {{1,2},{2,3},{3,4},{1,2}};
    cout << "Max Events Attended: " << maxEvents(events) << endl;

    // Test Problem 20: Boat to Save People
    vector<int> people_20 = {3,2,2,1};
    cout << "Num Rescue Boats: " << numRescueBoats(people_20, 3) << endl;

    return 0;
}
