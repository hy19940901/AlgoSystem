#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * 📚 Monotonic Queue Technique Overview
 * =====================================
 *
 * 🧠 When to Use:
 * ---------------
 * The monotonic queue is best suited for **sliding window** or **range maximum/minimum** problems.
 * It allows maintaining the maximum or minimum element in a moving window in O(1) amortized time.
 *
 * Look for these key phrases in problems:
 * - "Maximum/minimum in a sliding window"
 * - "Longest subarray satisfying..."
 * - "Dynamic window + range-based query"
 * - "Track maximum/minimum as window slides"
 *
 * 🧰 Typical Monotonic Queue Use Cases:
 * -------------------------------------
 * 1. Sliding Window Maximum / Minimum
 * 2. Longest Subarray with constraints
 * 3. Range maximum within a bounded window
 * 4. Optimizing DP over a range (e.g., LC1425)
 *
 * 🔁 Common Monotonic Queue Patterns:
 * -----------------------------------
 *
 * ✅ 1. Maintain Decreasing Queue (for Max in Window):
 *    - Use a deque to store **indices**.
 *    - Remove indices from back if they are less than current value.
 *    - Remove front if it’s outside the current window.
 *
 *    Template:
 *    ---------
 *    deque<int> dq;
 *    for (int i = 0; i < nums.size(); ++i) {
 *        if (!dq.empty() && dq.front() <= i - k)
 *            dq.pop_front(); // out of window
 *        while (!dq.empty() && nums[dq.back()] < nums[i])
 *            dq.pop_back();  // remove smaller values
 *        dq.push_back(i);
 *        if (i >= k - 1)
 *            result.push_back(nums[dq.front()]); // current max
 *    }
 *
 * ✅ 2. Maintain Increasing Queue (for Min in Window):
 *    - Same idea but reversed comparisons.
 *    - Pop back while current value is **smaller**.
 *
 * ✅ 3. Use with Prefix Sum or DP (for optimizing range):
 *    - Use deque to keep indices where value is increasing/decreasing to prune suboptimal choices.
 *    - Helps achieve O(n) optimization on naive O(n²) DP.
 *
 * 🚨 Key Points:
 * --------------
 * - The queue always maintains **monotonicity** (increasing or decreasing).
 * - Values are typically **indices** for efficient window removal.
 * - Every element is pushed and popped at most once → linear time.
 * - Great for real-time sliding analysis: min/max/longest subarray.
 *
 * ⏱️ Complexity:
 * ---------------
 * - Time: O(n) — amortized constant-time updates per element.
 * - Space: O(k) — at most k elements in the deque.
 */

/**
 * Problem 1: Sliding Window Maximum (LC 239)
 * -------------------------------------------
 * 📿 Description:
 * Given an array `nums` and an integer `k`, return the maximum value in each window of size `k`.
 *
 * 🔍 Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 *
 * 💡 Monotonic Queue Strategy:
 * - Use a deque to maintain indices in decreasing order of value.
 * - Pop from front if it's out of the window.
 * - Pop from back while current value is greater.
 * - Front holds the max of the window.
 *
 * 🚨 Edge Cases:
 * - Empty input: nums = []
 * - k = 1 → each element is max
 * - k == nums.size() → whole array max
 * - All values equal
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(k)
 */
vector<int> MaxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() <= static_cast<int>(i) - k)
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();
        dq.push_back(i);
        if (static_cast<int>(i) >= k - 1)
            result.push_back(nums[dq.front()]);
    }
    return result;
}

/**
 * Problem 2: Shortest Subarray with Sum at Least K (LC 862)
 * ----------------------------------------------------------
 * 📿 Description:
 * Find the length of the shortest subarray with sum ≥ k.
 * Return -1 if no such subarray exists.
 *
 * 🔍 Example:
 * Input: nums = [2, -1, 2], k = 3
 * Output: 3
 *
 * 💡 Monotonic Queue Strategy:
 * - Use prefix sums.
 * - Maintain a deque of increasing prefix indices.
 * - For each i, pop from front if prefix[i] - prefix[dq.front()] >= k.
 *
 * 🚨 Edge Cases:
 * - All elements < 0 → no subarray exists
 * - First few elements already ≥ k
 * - Prefix sum may dip before growing
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int ShortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq;
    int res = n + 1;
    for (int i = 0; i <= n; i++) {
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            res = min(res, i - dq.front());
            dq.pop_front();
        }
        while (!dq.empty() && prefix[i] <= prefix[dq.back()])
            dq.pop_back();
        dq.push_back(i);
    }

    return res <= n ? res : -1;
}

/**
 * Problem 3: Constrained Subsequence Sum (LC 1425)
 * -------------------------------------------------
 * 📿 Description:
 * Return max sum of a non-empty subsequence such that for any two elements i < j,
 * we must have j - i <= k.
 *
 * 🔍 Example:
 * Input: nums = [10,2,-10,5,20], k = 2
 * Output: 37
 *
 * 💡 Monotonic Queue Strategy:
 * - dp[i] = nums[i] + max(dp[j]) where j in [i-k, i-1]
 * - Use deque to maintain max of sliding window
 *
 * 🚨 Edge Cases:
 * - All negatives → return largest single value
 * - k = 1 → adjacent constraints
 * - k large enough to cover entire array
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int ConstrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq;
    int res = nums[0];
    for (int i = 0; i < n; ++i) {
        dp[i] = nums[i];
        if (!dq.empty())
            dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
        res = max(res, dp[i]);

        while (!dq.empty() && dp[i] >= dp[dq.back()])
            dq.pop_back();

        if (dp[i] > 0)
            dq.push_back(i);

        if (!dq.empty() && i - dq.front() >= k)
            dq.pop_front();
    }
    return res;
}

/**
 * Problem 4: Longest Well-Performing Interval (LC 1124)
 * ------------------------------------------------------
 * 📿 Description:
 * Given an array of hours worked per day, return the length of the longest subarray
 * with more days > 8 than ≤ 8.
 *
 * 🔍 Example:
 * Input: hours = [9,9,6,0,6,6,9]
 * Output: 3
 *
 * 💡 Monotonic Stack + Prefix Sum Strategy:
 * - Convert to +1/-1 by hours[i] > 8 ?
 * - Use prefix sum and stack to find earliest smaller prefix
 *
 * 🚨 Edge Cases:
 * - All hours ≤ 8 → return 0
 * - All hours > 8 → return n
 * - Mixed → use stack to check difference from earlier prefix
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int LongestWPI(vector<int>& hours) {
    int n = hours.size();
    vector<int> score(n + 1, 0);
    for (int i = 0; i < n; i++)
        score[i + 1] = score[i] + (hours[i] > 8 ? 1 : -1);

    stack<int> st;
    for (size_t i = 0; i < score.size(); ++i) {
        if (st.empty() || score[i] < score[st.top()])
            st.push(i);
    }

    int res = 0;
    for (int j = score.size() - 1; j > 0; --j) {
        while (!st.empty() && score[j] > score[st.top()]) {
            res = max(res, j - st.top());
            st.pop();
        }
    }
    return res;
}

/**
 * Problem 5: Minimum Operations to Make Array Continuous (LC 2009)
 * ------------------------------------------------------------------
 * 📿 Description:
 * Make `nums` continuous (no duplicates, sorted consecutive) by removing/replacing elements.
 * Return the minimum operations needed.
 *
 * 🔍 Example:
 * Input: nums = [4,2,5,3], Output: 0
 *
 * 💡 Sliding Window + Set Strategy:
 * - Sort and remove duplicates.
 * - For each left index, find max length of window where diff ≤ n - 1.
 * - Result = n - max_window_size.
 *
 * 🚨 Edge Cases:
 * - Duplicates in nums → remove first
 * - Already continuous → return 0
 * - All same number → max ops = n - 1
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
 */
int MinOperations(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    int res = n, j = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        while (static_cast<size_t>(j) < nums.size() && nums[j] < nums[i] + n)
            j++;
        res = min(res, n - (j - static_cast<int>(i)));
    }
    return res;
}

/**
 * Problem 6: Sum of Subarray Maximums (Custom Variant of LC 907)
 * --------------------------------------------------------------
 * 📿 Description:
 * Return the sum of **maximums** of all subarrays.
 *
 * 💡 Monotonic Stack Strategy:
 * - Similar to LC 907 (minimum), but maintain decreasing stack.
 * - For each element, compute how many subarrays it is the max in.
 *
 * 🚨 Edge Cases:
 * - All equal values → same contribution each
 * - Strictly increasing/decreasing → symmetric result
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int SumSubarrayMaxs(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();
    vector<int> left(n), right(n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] <= arr[i])
            st.pop();
        left[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] < arr[i])
            st.pop();
        right[i] = st.empty() ? n - i : st.top() - i;
        st.push(i);
    }

    long res = 0;
    for (int i = 0; i < n; i++)
        res = (res + (long)arr[i] * left[i] * right[i]) % MOD;
    return res;
}

/**
 * Problem 7: Maximum of All Subarrays of Size K (Classic Monotonic Queue)
 * ------------------------------------------------------------------------
 * 📿 Description:
 * Print max in every subarray of size k (like LC 239).
 *
 * 💡 Strategy:
 * Identical to LC 239: Monotonic decreasing deque of indices.
 *
 * 🚨 Edge Cases:
 * - k > nums.size() → no output
 * - nums.size() == 0 → return []
 */
vector<int> MaxOfAllWindows(vector<int>& nums, int k) {
    if (nums.empty() || static_cast<size_t>(k) > nums.size()) return {};
    deque<int> dq;
    vector<int> res;

    for (size_t i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() == static_cast<int>(i) - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();
        dq.push_back(i);
        if (static_cast<int>(i) >= k - 1)
            res.push_back(nums[dq.front()]);
    }
    return res;
}

/**
 * Problem 8: Number of Subarrays with Bounded Maximum (LC 795)
 * -------------------------------------------------------------
 * 📿 Description:
 * Return count of subarrays where max element is in range [left, right].
 *
 * 💡 Strategy:
 * Count subarrays with max ≤ right minus subarrays with max < left.
 * Use sliding window and count.
 *
 * 🚨 Edge Cases:
 * - All elements below left
 * - All elements above right
 */
int CountBounded(vector<int>& nums, int bound) {
    int count = 0, curr = 0;
    for (int x : nums) {
        if (x <= bound)
            curr++;
        else
            curr = 0;
        count += curr;
    }
    return count;
}

int NumSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    return CountBounded(nums, right) - CountBounded(nums, left - 1);
}

/**
 * Problem 9: Longest Subarray with Absolute Diff ≤ Limit (LC 1438)
 * -----------------------------------------------------------------
 * 📿 Description:
 * Return length of longest subarray where max - min ≤ limit.
 *
 * 💡 Strategy:
 * Two deques:
 * - maxDeque for decreasing max values
 * - minDeque for increasing min values
 * Slide window and shrink left when condition violated.
 *
 * 🚨 Edge Cases:
 * - All elements equal
 * - One element much larger than others
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int LongestSubarray(vector<int>& nums, int limit) {
    deque<int> max_dq, min_dq;
    int l = 0, res = 0;

    for (size_t r = 0; r < nums.size(); ++r) {
        while (!max_dq.empty() && nums[r] > max_dq.back()) max_dq.pop_back();
        while (!min_dq.empty() && nums[r] < min_dq.back()) min_dq.pop_back();

        max_dq.push_back(nums[r]);
        min_dq.push_back(nums[r]);

        while (!max_dq.empty() && !min_dq.empty() &&
               max_dq.front() - min_dq.front() > limit) {
            if (nums[l] == max_dq.front()) max_dq.pop_front();
            if (nums[l] == min_dq.front()) min_dq.pop_front();
            l++;
        }
        res = max(res, static_cast<int>(r) - l + 1);
    }
    return res;
}

/**
 * Problem 10: Total Strength of Wizards (LC 2281)
 * -----------------------------------------------
 * 📿 Description:
 * Return total strength = sum of (min * sum) over all subarrays.
 *
 * 💡 Strategy:
 * - Use monotonic stack to find bounds of minimum.
 * - Use prefix sums for quick sum calculation in O(1).
 *
 * 🚨 Edge Cases:
 * - All same value → repeated subarrays
 * - Min always at start or end → asymmetric bounds
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int TotalStrength(vector<int>& strength) {
    const int MOD = 1e9 + 7;
    int n = strength.size();
    vector<int> left(n), right(n), prefix(n + 2), prefix2(n + 2);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && strength[st.top()] >= strength[i]) st.pop();
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && strength[st.top()] > strength[i]) st.pop();
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        prefix[i + 1] = (prefix[i] + strength[i]) % MOD;
        prefix2[i + 1] = (prefix2[i] + 1LL * strength[i] * (i + 1)) % MOD;
    }

    long res = 0;
    for (int i = 0; i < n; i++) {
        int l = left[i], r = right[i];
        long total = (prefix2[r] - prefix2[i] - 1L * (i) * (prefix[r] - prefix[i])) % MOD;
        long total_left = (prefix2[i] - prefix2[l + 1] - 1L * (l + 1) * (prefix[i] - prefix[l + 1])) % MOD;
        long contrib = strength[i] * ((total * (i - l) % MOD - total_left * (r - i) % MOD) % MOD) % MOD;
        res = (res + contrib + MOD) % MOD;
    }

    return res;
}

int main() {
    // ✅ Problem 1: LC 239
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    auto res1 = MaxSlidingWindow(nums1, 3);
    cout << "LC239 Sliding Window Max: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    // ✅ Problem 2: LC 862
    vector<int> nums2 = {2, -1, 2};
    cout << "LC862 Shortest Subarray Sum ≥ K: " << ShortestSubarray(nums2, 3) << endl;

    // ✅ Problem 3: LC 1425
    vector<int> nums3 = {10, 2, -10, 5, 20};
    cout << "LC1425 Constrained Subsequence Sum: " << ConstrainedSubsetSum(nums3, 2) << endl;

    // ✅ Problem 4: LC 1124
    vector<int> hours = {9, 9, 6, 0, 6, 6, 9};
    cout << "LC1124 Longest WPI: " << LongestWPI(hours) << endl;

    // ✅ Problem 5: LC 2009
    vector<int> nums5 = {4, 2, 5, 3};
    cout << "LC2009 Min Operations to Make Continuous: " << MinOperations(nums5) << endl;

    // ✅ Problem 6: Subarray Max Sum (Custom)
    vector<int> nums6 = {3, 1, 2, 4};
    cout << "Sum of Subarray Maximums: " << SumSubarrayMaxs(nums6) << endl;

    // ✅ Problem 7: Max of All Windows
    vector<int> nums7 = {10, 5, 2, 7, 8, 7};
    auto res7 = MaxOfAllWindows(nums7, 3);
    cout << "Max in All Windows: ";
    for (int x : res7) cout << x << " ";
    cout << endl;

    // ✅ Problem 8: LC 795
    vector<int> nums8 = {2, 1, 4, 3};
    cout << "LC795 Num Subarray Bounded Max: " << NumSubarrayBoundedMax(nums8, 2, 3) << endl;

    // ✅ Problem 9: LC 1438
    vector<int> nums9 = {8, 2, 4, 7};
    cout << "LC1438 Longest Subarray with Limit: " << LongestSubarray(nums9, 4) << endl;

    // ✅ Problem 10: LC 2281
    vector<int> strength = {1, 3, 1, 2};
    cout << "LC2281 Total Strength of Wizards: " << TotalStrength(strength) << endl;

    return 0;
}