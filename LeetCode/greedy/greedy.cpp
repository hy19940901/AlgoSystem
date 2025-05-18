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
 * 🔷 Greedy Algorithm Overview
 * -----------------------------
 * Greedy algorithms make a sequence of choices, each of which looks best at the moment,
 * in the hope that the global optimum is reached through local optimizations.
 *
 * ✅ When to Use:
 * - Problems with **"greedy-choice property"** and **optimal substructure**.
 * - No need to explore all possibilities (unlike DP or backtracking).
 * - Sorting-based decisions, local maxima, or earliest/latest constraints.
 *
 * 🧠 Typical Templates:
 * 1. Sort the input (by value, cost, or custom logic).
 * 2. Iterate and apply greedy decision at each step.
 * 3. Use heap, deque, or monotonic stack if needed.
 *
 * 🧩 Common Problem Types:
 * - Interval scheduling / merging / covering
 * - Resource allocation, task scheduling
 * - Jump game, choosing smallest/largest subset
 * - Monotonic stack: window max, 132 pattern, histogram area
 *
 * 📚 Related Tools:
 * - Monotonic Stack (for range-based greedy structure)
 * - Priority Queue (when always picking min/max on the fly)
 * - Sorting + Two Pointers (for matching, partitioning)
 */

/**
 * Problem 1: Assign Cookies (LeetCode 455)
 * ----------------------------------------
 * 📟 Description:
 * Given greed factors of children and cookie sizes, assign cookies to maximize the number of satisfied children.
 * Each child gets at most one cookie. A child is satisfied if cookie size >= their greed factor.
 *
 * 🔍 Example:
 * Input: g = [1,2,3], s = [1,1]
 * Output: 1
 *
 * 💡 Greedy Strategy:
 * ----------------------------------------
 * - Sort both greed and cookie size arrays in ascending order.
 * - Try to satisfy the least greedy child first (smallest g[i]) with the smallest available cookie.
 * - Use two pointers to iterate: one for children, one for cookies.
 * - If current cookie s[j] satisfies g[i], assign and move to next child and cookie.
 * - Otherwise, try next bigger cookie.
 * - This greedy approach ensures maximum children are satisfied with the least large cookies.
 *
 * 🚨 Edge Cases:
 * - No children or no cookies → return 0.
 * - All cookies smaller than every child's greed → return 0.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */
int FindContentChildren(vector<int>& g, vector<int>& s) {
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
 * Problem 2: Jump Game (LeetCode 55)
 * ----------------------------------
 * 📟 Description:
 * Determine if you can reach the last index starting from the first, with nums[i] being the max jump length.
 *
 * 🔍 Example:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 *
 * 💡 Greedy Strategy:
 * ----------------------------------
 * - Maintain a variable max_reach to track the farthest index reachable at any point.
 * - Iterate through the array:
 *     - If current index i > max_reach, we are stuck and return false.
 *     - Otherwise, update max_reach to max(max_reach, i + nums[i]).
 * - If we reach the end or beyond, return true.
 * - This greedy approach ensures we always try to jump as far as possible.
 *
 * 🚨 Edge Cases:
 * - First element is 0 → return false unless it's the only element.
 * - Array of length 1 → always reachable.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
bool CanJump(vector<int>& nums) {
    int max_reach = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (static_cast<int>(i) > max_reach) return false;
        max_reach = max(max_reach, static_cast<int>(i) + nums[i]);
    }
    return true;
}

/**
 * Problem 3: Jump Game II (LeetCode 45)
 * -------------------------------------
 * 📟 Description:
 * Return the minimum number of jumps to reach the last index.
 *
 * 🔍 Example:
 * Input: nums = [2,3,1,1,4]
 * Output: 2
 *
 * 💡 Greedy Strategy:
 * -------------------------------------
 * - Track the farthest reachable index (farthest) and end of the current jump window (end).
 * - Traverse from index 0 to n-2:
 *     - At each index, update farthest = max(farthest, i + nums[i]).
 *     - If index reaches the current window end:
 *         - Increment jump count.
 *         - Set new window end to farthest.
 * - Greedy choice ensures minimum jumps by always jumping to the farthest possible location.
 *
 * 🚨 Edge Cases:
 * - nums has only 1 element → return 0.
 * - First element is large enough to reach the end → return 1.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int Jump(vector<int>& nums) {
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
 * Problem 4: Minimum Number of Arrows to Burst Balloons (LeetCode 452)
 * ---------------------------------------------------------------------
 * 📟 Description:
 * Each balloon is a horizontal interval. One arrow can burst all balloons it passes through.
 * Return the minimum number of arrows needed.
 *
 * 🔍 Example:
 * Input: [[10,16], [2,8], [1,6], [7,12]]
 * Output: 2
 *
 * 💡 Greedy Strategy:
 * ---------------------------------------------------------------------
 * - Sort intervals by their end coordinate to prioritize earliest end.
 * - Initialize arrow count = 1, and shoot first arrow at the end of the first balloon.
 * - For each balloon:
 *     - If the start > current arrow position, we need a new arrow.
 *     - Shoot it at the end of current balloon, update counter.
 * - This greedy method ensures each arrow covers as many overlapping balloons as possible.
 *
 * 🚨 Edge Cases:
 * - Empty input → return 0.
 * - All balloons fully overlap → return 1.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */
int FindMinArrowShots(vector<vector<int>>& points) {
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
 * Problem 5: Non-overlapping Intervals (LeetCode 435)
 * ----------------------------------------------------
 * 📟 Description:
 * Remove minimum number of intervals so remaining intervals don’t overlap.
 *
 * 🔍 Example:
 * Input: [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 *
 * 💡 Greedy Strategy:
 * ----------------------------------------------------
 * - Sort intervals by end time ascending.
 * - Initialize end with first interval's end.
 * - For every subsequent interval:
 *     - If current start >= end, it's non-overlapping. Count it and update end.
 *     - Else, it overlaps, skip it.
 * - Minimum removals = total - number of non-overlapping intervals.
 * - This greedy choice keeps intervals with earliest end time to allow more room for others.
 *
 * 🚨 Edge Cases:
 * - Empty interval list → return 0.
 * - Already non-overlapping intervals → return 0.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */
int EraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });
    int non_overlap_count = 1;
    int end = intervals[0][1];
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] >= end) {
            non_overlap_count++;
            end = intervals[i][1];
        }
    }
    return intervals.size() - non_overlap_count;
}

/**
 * Problem 6: Gas Station (LeetCode 134)
 * --------------------------------------
 * 📟 Description:
 * Given two arrays gas and cost, return the starting index of the gas station where you can complete a full circuit.
 * If you can't travel around the circuit once in the clockwise direction, return -1.
 *
 * 🔍 Example:
 * Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 * Output: 3
 *
 * 💡 Greedy Strategy:
 * --------------------------------------
 * - If total gas < total cost, it’s impossible to finish the circuit.
 * - Iterate through stations and keep track of current gas tank.
 * - If gas tank goes negative, reset starting index to next station and reset current tank.
 * - The point after failure is the only possible valid start point (proof by contradiction).
 *
 * 🚨 Edge Cases:
 * - Total gas < total cost → return -1.
 * - Only one station → check if gas[0] >= cost[0].
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int CanCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total_tank = 0, curr_tank = 0, start = 0;
    for (size_t i = 0; i < gas.size(); ++i) {
        total_tank += gas[i] - cost[i];
        curr_tank += gas[i] - cost[i];
        if (curr_tank < 0) {
            start = i + 1;
            curr_tank = 0;
        }
    }
    return total_tank >= 0 ? start : -1;
}

/**
 * Problem 7: Maximum Subarray (LeetCode 53)
 * ------------------------------------------
 * 📟 Description:
 * Find the contiguous subarray (containing at least one number) with the largest sum.
 *
 * 🔍 Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------
 * - Kadane’s algorithm: extend current subarray as long as it improves the sum.
 * - Track current sum and reset to nums[i] if previous sum is negative.
 * - Update global maximum after every step.
 * - Greedy choice: discard any prefix that brings sum down.
 *
 * 🚨 Edge Cases:
 * - All numbers are negative → return the largest single element.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int MaxSubArray(vector<int>& nums) {
    int max_sum = nums[0], current_sum = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        current_sum = max(nums[i], current_sum + nums[i]);
        max_sum = max(max_sum, current_sum);
    }
    return max_sum;
}
// Greedy algorithm, kadane algorithm
int MaxSubArray_kadane(vector<int>& nums) {
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
 * Problem 8: Candy Distribution (LeetCode 135)
 * ---------------------------------------------
 * 📟 Description:
 * Distribute candies to children with ratings such that:
 * - Each child gets at least one candy.
 * - Children with a higher rating than their neighbors get more candies.
 * Return the minimum total candies needed.
 *
 * 🔍 Example:
 * Input: ratings = [1,0,2]
 * Output: 5
 *
 * 💡 Greedy Strategy:
 * ---------------------------------------------
 * - Do two passes:
 *   1. Left to right: if rating[i] > rating[i-1], give one more candy.
 *   2. Right to left: if rating[i] > rating[i+1], ensure it gets more than right neighbor.
 * - Combine both passes to satisfy both constraints.
 *
 * 🚨 Edge Cases:
 * - All ratings equal → everyone gets 1 candy.
 * - Ratings strictly increasing or decreasing → linear ramp up/down.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int Candy(vector<int>& ratings) {
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
 * Problem 9: Task Scheduler (LeetCode 621)
 * ----------------------------------------
 * 📟 Description:
 * Schedule CPU tasks with cooldown n so that the same task is not executed within n intervals.
 * Return the least number of units of times to finish all tasks.
 *
 * 🔍 Example:
 * Input: tasks = ['A','A','A','B','B','B'], n = 2
 * Output: 8
 *
 * 💡 Greedy Strategy:
 * ----------------------------------------
 * - Count frequency of each task.
 * - The most frequent task determines the frame: (max_count - 1) * (n + 1).
 * - Add extra slots for tasks with same max count.
 * - Result is max of calculated frame and total tasks.
 * - Greedily fill each interval to minimize idle time.
 *
 * 🚨 Edge Cases:
 * - n = 0 → just return tasks.size().
 * - All tasks are same → maximum idle time inserted.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int LeastInterval(vector<char>& tasks, int n) {
    vector<int> counts(26, 0);
    for (char task : tasks) counts[task - 'A']++;
    int max_count = *max_element(counts.begin(), counts.end());
    int max_freq_tasks = count(counts.begin(), counts.end(), max_count);
    return max((int)tasks.size(), (max_count - 1) * (n + 1) + max_freq_tasks);
}

/**
 * Problem 10: Queue Reconstruction by Height (LeetCode 406)
 * ----------------------------------------------------------
 * 📟 Description:
 * Given a list of people’s height and number of taller/equal people in front, reconstruct the queue.
 *
 * 🔍 Example:
 * Input: [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 * Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
 *
 * 💡 Greedy Strategy:
 * ----------------------------------------------------------
 * - Sort people by height descending and k-value ascending.
 * - Insert each person into the result at index equal to their k-value.
 * - Taller people are placed first, so shorter ones don’t affect their positions.
 * - This ensures the correct number of taller people is in front.
 *
 * 🚨 Edge Cases:
 * - All people have same height → insert by k only.
 * - k = 0 for all → preserve input order after sort.
 *
 * ⏱️ Time: O(n^2)
 * 🧠 Space: O(n)
 */
vector<vector<int>> ReconstructQueue(vector<vector<int>>& people) {
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
 * Problem 11: Partition Labels (LeetCode 763)
 * -------------------------------------------
 * 📟 Description:
 * A string is to be partitioned into as many parts as possible so that each letter appears in at most one part.
 * Return a list of integers representing the size of these parts.
 *
 * 🔍 Example:
 * Input: s = "ababcbacadefegdehijhklij"
 * Output: [9,7,8]
 *
 * 💡 Greedy Strategy:
 * -------------------------------------------
 * - First record the last occurrence of each character.
 * - Start a partition from index 0.
 * - While traversing, track the maximum end position seen so far.
 * - Once current index == max position, cut the partition.
 * - Repeat until the end of the string.
 *
 * 🚨 Edge Cases:
 * - Each letter appears only once → each partition is size 1.
 * - All letters same → return one partition of full length.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
vector<int> PartitionLabels(string s) {
    vector<int> last_index(26, 0);
    for (size_t i = 0; i < s.size(); ++i) {
        last_index[s[i] - 'a'] = i;
    }
    vector<int> partitions;
    int start = 0, end = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        end = max(end, last_index[s[i] - 'a']);
        if (static_cast<int>(i) == end) {
            partitions.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return partitions;
}

/**
 * Problem 12: Maximize Sum After K Negations (LeetCode 1005)
 * ------------------------------------------------------------
 * 📟 Description:
 * Given an integer array `nums` and an integer `k`, flip the sign of `k` elements to maximize the array sum.
 *
 * 🔍 Example:
 * Input: nums = [4,2,3], k = 1
 * Output: 5
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * - Sort the array so that we can flip the smallest (most negative) numbers first.
 * - Flip signs of negative numbers greedily until k becomes 0 or no negatives remain.
 * - If k is still odd, flip the smallest number (now positive) once more.
 * - This ensures maximum increase in the total sum.
 *
 * 🚨 Edge Cases:
 * - All numbers positive → only flip if k is odd.
 * - Repeated minimum value after flips → flip again if k is odd.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */
int LargestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() && k > 0 && nums[i] < 0; ++i, --k) {
        nums[i] = -nums[i];
    }
    return accumulate(nums.begin(), nums.end(), 0) - (k % 2 ? 2 * *min_element(nums.begin(), nums.end()) : 0);
}

/**
 * Problem 13: Minimum Cost to Connect Sticks (LeetCode 1167)
 * ------------------------------------------------------------
 * 📟 Description:
 * You are given an array of stick lengths. Connect any two sticks to form one longer stick,
 * the cost being the sum of their lengths. Return the minimum total cost to connect all sticks.
 *
 * 🔍 Example:
 * Input: sticks = [2,4,3]
 * Output: 14
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------------------
 * - Use a min-heap (priority queue) to always combine the two smallest sticks.
 * - Push the combined stick back into the heap.
 * - Repeat until one stick remains.
 * - This greedy approach ensures smallest combinations occur early, minimizing total cost.
 *
 * 🚨 Edge Cases:
 * - Only one stick → return 0.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
 */
int ConnectSticks(vector<int>& sticks) {
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
 * Problem 14: Lemonade Change (LeetCode 860)
 * -------------------------------------------
 * 📟 Description:
 * Customers pay with 5, 10, or 20 dollar bills in order. You must provide exact change.
 * Return true if you can provide change to all customers in order.
 *
 * 🔍 Example:
 * Input: bills = [5,5,5,10,20]
 * Output: true
 *
 * 💡 Greedy Strategy:
 * -------------------------------------------
 * - Track how many $5 and $10 bills you have.
 * - Always try to give one $10 and one $5 as change for $20, or three $5s otherwise.
 * - This greedy strategy uses larger bills first to keep smaller ones for future use.
 *
 * 🚨 Edge Cases:
 * - First customer pays with $10 or $20 → return false.
 * - Insufficient $5 bills at any point → return false.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
bool LemonadeChange(vector<int>& bills) {
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
 * Problem 15: Two City Scheduling (LeetCode 1029)
 * ------------------------------------------------
 * 📟 Description:
 * Each person has a cost for flying to city A and city B. Send n people to each city with minimum total cost.
 *
 * 🔍 Example:
 * Input: costs = [[10,20],[30,200],[50,10],[20,30]]
 * Output: 110
 *
 * 💡 Greedy Strategy:
 * ------------------------------------------------
 * - Sort the people based on cost difference: costA - costB.
 * - Send first n people (cheaper to go to A) to A, and rest to B.
 * - This minimizes cost by choosing the lowest deltas.
 *
 * 🚨 Edge Cases:
 * - All people cheaper to go to one city → cost difference handles balance.
 * - Equal cost for both cities → choose any.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */
int TwoCitySchedCost(vector<vector<int>>& costs) {
    sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b) {
        return (a[0] - a[1]) < (b[0] - b[1]);
    });
    int total_cost = 0, n = costs.size() / 2;
    for (int i = 0; i < n; i++) total_cost += costs[i][0];
    for (int i = n; i < 2 * n; i++) total_cost += costs[i][1];
    return total_cost;
}

/**
 * Problem 16: Minimum Deletions to Make Character Frequencies Unique (LeetCode 1647)
 * -----------------------------------------------------------------------------------
 * 📟 Description:
 * Given a string, delete the fewest characters so that no two characters have the same frequency.
 *
 * 🔍 Example:
 * Input: s = "aaabbbcc"
 * Output: 2
 *
 * 💡 Greedy Strategy:
 * -----------------------------------------------------------------------------------
 * - Count character frequencies.
 * - Use a hash set to track used frequencies.
 * - Decrease frequency greedily until it’s unique or zero.
 * - This ensures minimal deletions while maintaining uniqueness.
 *
 * 🚨 Edge Cases:
 * - All characters appear once → no deletion needed.
 * - Many characters with same frequency → multiple decrements needed.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int MinDeletions(string s) {
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
 * Problem 17: Hand of Straights (LeetCode 846)
 * ---------------------------------------------
 * 📟 Description:
 * Check if the hand of cards can be rearranged into groups of consecutive group_size.
 *
 * 🔍 Example:
 * Input: hand = [1,2,3,6,2,3,4,7,8], group_size = 3
 * Output: true
 *
 * 💡 Greedy Strategy:
 * ---------------------------------------------
 * - Use a map to count card frequencies.
 * - Iterate from smallest card, for each group:
 *   - Ensure all k consecutive cards exist.
 *   - Decrease their frequencies accordingly.
 * - Greedily form groups from the lowest card possible.
 *
 * 🚨 Edge Cases:
 * - hand size not divisible by group_size → return false.
 * - Missing a card in a required sequence → return false.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
 */
bool IsNStraightHand(vector<int>& hand, int group_size) {
    if (hand.size() % group_size != 0) return false;
    map<int, int> count;
    for (int card : hand) count[card]++;
    for (auto& [card, freq] : count) {
        while (freq > 0) {
            for (int i = 0; i < group_size; i++) {
                if (count[card + i] == 0) return false;
                count[card + i]--;
            }
            freq--;
        }
    }
    return true;
}

/**
 * Problem 18: Minimum Cost to Move Chips to The Same Position (LeetCode 1217)
 * -----------------------------------------------------------------------------
 * 📟 Description:
 * You can move chips by 2 steps for free or 1 step for cost = 1.
 * Return minimum cost to make all chips at the same position.
 *
 * 🔍 Example:
 * Input: position = [1,2,3]
 * Output: 1
 *
 * 💡 Greedy Strategy:
 * -----------------------------------------------------------------------------
 * - Count how many chips are on odd and even positions.
 * - Move the smaller group to the other’s side (cost per odd-even move is 1).
 * - Greedy choice: pick the cheaper of odd or even.
 *
 * 🚨 Edge Cases:
 * - All chips on same parity (all even or all odd) → cost is 0.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 */
int MinCostToMoveChips(vector<int>& position) {
    int odd = 0, even = 0;
    for (int pos : position) {
        if (pos % 2 == 0) even++;
        else odd++;
    }
    return min(odd, even);
}

/**
 * Problem 19: Maximum Number of Events That Can Be Attended (LeetCode 1353)
 * --------------------------------------------------------------------------
 * 📟 Description:
 * Attend as many events as possible. Each has a start and end day. One event per day.
 *
 * 🔍 Example:
 * Input: events = [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 *
 * 💡 Greedy Strategy:
 * --------------------------------------------------------------------------
 * - Sort events by start day.
 * - Use a min-heap to track ending days of events that are ongoing.
 * - For each day, attend the event with the earliest end time.
 * - This strategy ensures earliest-ending events are prioritized, maximizing attendance.
 *
 * 🚨 Edge Cases:
 * - Events with same start and end → only one can be picked per day.
 * - Overlapping events → heap ensures correct prioritization.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
 */
int MaxEvents(vector<vector<int>>& events) {
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
 * Problem 20: Boat to Save People (LeetCode 881)
 * -----------------------------------------------
 * 📟 Description:
 * People can share boats with a weight limit. Return minimum boats needed to rescue everyone.
 *
 * 🔍 Example:
 * Input: people = [3,2,2,1], limit = 3
 * Output: 3
 *
 * 💡 Greedy Strategy:
 * -----------------------------------------------
 * - Sort people by weight.
 * - Use two pointers: lightest and heaviest.
 * - If both can share a boat, move both; otherwise, move the heavier one alone.
 * - Greedy pairing ensures the fewest boats.
 *
 * 🚨 Edge Cases:
 * - One person heavier than limit → invalid (not handled in this implementation).
 * - All people weight exactly limit → one boat per person.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(1)
 */

int NumRescueBoats(vector<int>& people, int limit) {
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
    cout << "Assign Cookies: " << FindContentChildren(g, s) << endl;

    // Test Problem 2: Jump Game
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Can Jump: " << (CanJump(nums1) ? "True" : "False") << endl;

    // Test Problem 3: Jump Game II
    vector<int> nums2 = {2, 3, 1, 1, 4};
    cout << "Minimum Jumps: " << Jump(nums2) << endl;

    // Test Problem 4: Minimum Number of Arrows to Burst Balloons
    vector<vector<int>> points = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    cout << "Minimum Arrows: " << FindMinArrowShots(points) << endl;

    // Test Problem 5: Non-overlapping Intervals
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Erase Overlap Intervals: " << EraseOverlapIntervals(intervals) << endl;

    // Test Problem 6: Gas Station
    vector<int> gas = {1, 2, 3, 4, 5}, cost = {3, 4, 5, 1, 2};
    cout << "Gas Station Start Index: " << CanCompleteCircuit(gas, cost) << endl;

    // Test Problem 7: Maximum Subarray
    vector<int> nums3 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << MaxSubArray(nums3) << endl;
    cout << "Maximum Subarray Sum: " << MaxSubArray_kadane(nums3) << endl;

    // Test Problem 8: Candy Distribution
    vector<int> ratings = {1, 0, 2};
    cout << "Candy Distribution: " << Candy(ratings) << endl;

    // Test Problem 9: Task Scheduler
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    cout << "Task Scheduler: " << LeastInterval(tasks, n) << endl;

    // Test Problem 10: Queue Reconstruction by Height
    vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    auto queue_result = ReconstructQueue(people);
    cout << "Reconstructed Queue: ";
    for (auto& p : queue_result) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    // Test Problem 11: Partition Labels
    string str_partition = "ababcbacadefegdehijhklij";
    auto partition_result = PartitionLabels(str_partition);
    cout << "Partition Labels: ";
    for (int len : partition_result) {
        cout << len << " ";
    }
    cout << endl;

    // Test Problem 12: Maximize Sum After K Negations
    vector<int> nums = {4,2,3};
    int k = 1;
    cout << "Max Sum After K Negations: " << LargestSumAfterKNegations(nums, k) << endl;

    // Test Problem 13: Minimum Cost to Connect Sticks
    vector<int> sticks = {2,4,3};
    cout << "Minimum Cost to Connect Sticks: " << ConnectSticks(sticks) << endl;

    // Test Problem 14: Lemonade Change
    vector<int> bills = {5,5,5,10,20};
    cout << "Lemonade Change: " << (LemonadeChange(bills) ? "True" : "False") << endl;

    // Test Problem 15: Two City Scheduling
    vector<vector<int>> costs = {{10,20},{30,200},{50,10},{20,30}};
    cout << "Two City Scheduling Cost: " << TwoCitySchedCost(costs) << endl;

    // Test Problem 16: Minimum Deletions to Make Character Frequencies Unique
    string s_16 = "aaabbbcc";
    cout << "Min Deletions: " << MinDeletions(s_16) << endl;

    // Test Problem 17: Hand of Straights
    vector<int> hand = {1,2,3,6,2,3,4,7,8};
    cout << "Hand of Straights: " << (IsNStraightHand(hand, 3) ? "True" : "False") << endl;

    // Test Problem 18: Minimum Cost to Move Chips
    vector<int> chips = {1,2,3};
    cout << "Min Cost to Move Chips: " << MinCostToMoveChips(chips) << endl;

    // Test Problem 19: Maximum Number of Events That Can Be Attended
    vector<vector<int>> events = {{1,2},{2,3},{3,4},{1,2}};
    cout << "Max Events Attended: " << MaxEvents(events) << endl;

    // Test Problem 20: Boat to Save People
    vector<int> people_20 = {3,2,2,1};
    cout << "Num Rescue Boats: " << NumRescueBoats(people_20, 3) << endl;

    return 0;
}
