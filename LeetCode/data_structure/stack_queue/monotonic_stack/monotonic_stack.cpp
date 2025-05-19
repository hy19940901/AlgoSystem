#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * 📚 Monotonic Stack Technique Overview
 * =====================================
 *
 * 🧠 When to Use:
 * --------------
 * The monotonic stack is best suited for problems that require:
 * - Finding "next greater/smaller" elements to the left or right.
 * - Processing elements in order while maintaining a specific trend (increasing or decreasing).
 * - Handling range-based conditions in a single pass.
 *
 * Look for these key phrases in problems:
 * - "Next greater/smaller element"
 * - "Previous greater/smaller"
 * - "Span of elements", "Histogram", or "Temperatures"
 * - "Find first element to the right/left that satisfies..."
 *
 * 🔁 Common Monotonic Stack Patterns:
 * -----------------------------------
 *
 * 1. ✅ Next Greater Element (Right Side)
 *    - Traverse from right to left.
 *    - Maintain a decreasing stack (store potential greater values).
 *
 *    Template:
 *    ----------
 *    stack<int> st;
 *    for (int i = n - 1; i >= 0; --i) {
 *        while (!st.empty() && st.top() <= nums[i])
 *            st.pop(); // remove smaller values
 *
 *        res[i] = st.empty() ? -1 : st.top(); // store result
 *        st.push(nums[i]); // add current element to stack
 *    }
 *
 * 2. ✅ Next Smaller Element (Right Side)
 *    - Same idea, but maintain an increasing stack.
 *
 * 3. ✅ Previous Greater/Smaller Element (Left Side)
 *    - Traverse from left to right.
 *    - Stack order is the same: decreasing for "greater", increasing for "smaller".
 *
 * 4. ✅ Monotonic Stack with Indexes
 *    - Use when needing distances, widths, or bounds (e.g., histogram area).
 *
 *    Template:
 *    ----------
 *    stack<int> st; // store indices
 *    for (int i = 0; i < n; ++i) {
 *        while (!st.empty() && nums[st.top()] < nums[i])
 *            st.pop(); // adjust boundary
 *        // st.top() is now the nearest valid element to the left
 *        st.push(i);
 *    }
 *
 * 🚨 Key Points:
 * --------------
 * - Stack is typically used to maintain monotonicity (increasing or decreasing).
 * - Pop from stack when the invariant (monotonic order) is broken.
 * - Elements in the stack are *candidates* for future comparisons.
 * - Often used in a single-pass O(n) approach.
 *
 * ⏱️ Complexity:
 * --------------
 * - Time: O(n) — each element is pushed and popped at most once.
 * - Space: O(n) — stack holds up to n elements in the worst case.
 */

/**
 * Problem 1: Next Greater Element I (LC 496)
 * ------------------------------------------
 * 📿 Description:
 * Given an array `nums`, find the next greater element for each index.
 * The next greater element is the first greater element found on the right.
 * If there is no greater element, return -1.
 *
 * 🔍 Example:
 * Input: nums = [2, 1, 2, 4, 3]
 * Output: [4, 2, 4, -1, -1]
 *
 * 💡 Monotonic Stack Strategy:
 * ------------------------------------------
 * - Iterate from right to left and use a stack to store possible candidates.
 * - Maintain a decreasing stack: pop smaller or equal elements.
 * - If the stack is not empty, the top is the next greater.
 * - Push current element to the stack.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
vector<int> NextGreaterElement(vector<int>& nums) {
    vector<int> result(nums.size(), -1);
    stack<int> st;
    for (int i = nums.size() - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums[i]) {
            st.pop();
        }
        if (!st.empty()) {
            result[i] = st.top();
        }
        st.push(nums[i]);
    }
    return result;
}

/**
 * Problem 2: Next Greater Element II (LC 503)
 * -------------------------------------------
 * 📿 Description:
 * Given a circular array `nums`, find the next greater element for each index.
 * The next greater element is the first greater element found when traversing circularly.
 *
 * 🔍 Example:
 * Input: nums = [1, 2, 1]
 * Output: [2, -1, 2]
 *
 * 💡 Monotonic Stack Strategy:
 * -------------------------------------------
 * - Traverse array twice (simulate circular array).
 * - Use decreasing stack to track next greater elements.
 * - Store answer for each index on first pass.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
vector<int> NextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums[i % n]) {
            st.pop();
        }
        if (!st.empty()) {
            result[i % n] = st.top();
        }
        st.push(nums[i % n]);
    }
    return result;
}

/**
 * Problem 3: Largest Rectangle in Histogram (LC 84)
 * --------------------------------------------------
 * 📿 Description:
 * Given histogram bar heights, find the area of the largest rectangle.
 *
 * 🔍 Example:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 *
 * 💡 Monotonic Stack Strategy:
 * --------------------------------------------------
 * - Append a sentinel value (0) to flush stack at the end.
 * - Use a stack to maintain increasing indices.
 * - On pop, calculate area with popped bar as smallest.
 * - Update maximum area accordingly.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int LargestRectangleArea(vector<int>& heights) {
    stack<int> st;
    heights.push_back(0); // Sentinel to clear stack
    int max_area = 0;
    for (size_t i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            max_area = max(max_area, h * width);
        }
        st.push(i);
    }
    return max_area;
}

/**
 * Problem 4: Maximal Rectangle (LC 85)
 * -------------------------------------
 * 📿 Description:
 * Given a 2D binary matrix filled with '0' and '1', find the largest rectangle containing only 1s.
 *
 * 🔍 Example:
 * Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * Output: 6
 *
 * 💡 Monotonic Stack Strategy:
 * -------------------------------------
 * - For each row, update histogram heights.
 * - Use histogram largest rectangle logic row-by-row.
 * - Track the max area over all rows.
 *
 * ⏱️ Time: O(m * n)
 * 🧠 Space: O(n)
 */

int MaximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int max_area = 0, cols = matrix[0].size();
    vector<int> heights(cols, 0);
    for (const auto& row : matrix) {
        for (int j = 0; j < cols; j++) {
            heights[j] = (row[j] == '1') ? heights[j] + 1 : 0;
        }
        max_area = max(max_area, LargestRectangleArea(heights));
    }
    return max_area;
}

/**
 * Problem 5: Sliding Window Maximum (LC 239)
 * -------------------------------------------
 * 📿 Description:
 * Given an array and an integer `k`, return the maximum value in each window of size `k`.
 *
 * 🔍 Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 *
 * 💡 Monotonic Stack Strategy:
 * -------------------------------------------
 * - Use a deque to store indices of elements in decreasing order.
 * - Remove indices out of the window range.
 * - Remove from back if current value is greater than back.
 * - Front always has max value index for current window.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(k)
 */
vector<int> MaxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == static_cast<int>(i) - k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (static_cast<int>(i) >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

/**
 * Problem 6: Daily Temperatures (LC 739)
 * ---------------------------------------
 * 📿 Description:
 * Given a list of daily temperatures, return a list of how many days until a warmer temperature.
 * If no future day is warmer, return 0.
 *
 * 🔍 Example:
 * Input: temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 * Output: [1, 1, 4, 2, 1, 1, 0, 0]
 *
 * 💡 Monotonic Stack Strategy:
 * ---------------------------------------
 * - Use a stack to keep indices of decreasing temperatures.
 * - If current temp > top of stack, compute the wait days.
 * - Push current index onto the stack.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
vector<int> DailyTemperatures(vector<int>& temperatures) {
    vector<int> result(temperatures.size(), 0);
    stack<int> st;
    for (size_t i = 0; i < temperatures.size(); i++) {
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
            int index = st.top();
            st.pop();
            result[index] = i - index;
        }
        st.push(i);
    }
    return result;
}

/**
 * Problem 7: Sum of Subarray Minimums (LC 907)
 * ---------------------------------------------
 * 📿 Description:
 * Given an array `arr`, find the sum of min values of all subarrays.
 * Return result modulo 10^9 + 7.
 *
 * 🔍 Example:
 * Input: arr = [3,1,2,4]
 * Output: 17
 *
 * 💡 Monotonic Stack Strategy:
 * ---------------------------------------------
 * - For each element, find how many subarrays where it's the minimum.
 * - Use monotonic stack to find left and right boundaries.
 * - Contribution = arr[i] * (# elements to left) * (# elements to right)
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
int SumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    stack<int> st;
    int n = arr.size();
    vector<int> left(n), right(n);

    // Calculate left boundaries
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        left[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop(); // Clear stack

    // Calculate right boundaries
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        right[i] = st.empty() ? n - i : st.top() - i;
        st.push(i);
    }

    // Compute result
    long result = 0;
    for (int i = 0; i < n; i++) {
        result = (result + (long)arr[i] * left[i] * right[i]) % MOD;
    }
    return result;
}

/**
 * Problem 8: Find 132 Pattern (LC 456)
 * -------------------------------------
 * 📿 Description:
 * Find if there exists a 132 pattern in array: i < j < k and nums[i] < nums[k] < nums[j].
 *
 * 🔍 Example:
 * Input: nums = [3,1,4,2]
 * Output: true
 *
 * 💡 Monotonic Stack Strategy:
 * -------------------------------------
 * - Traverse from right to left.
 * - Use stack to track potential 3rd element.
 * - Update `third` when popping smaller values.
 * - If current < third, pattern is found.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
bool Find132pattern(vector<int>& nums) {
    stack<int> st;
    int third = INT_MIN;
    for (int i = nums.size() - 1; i >= 0; i--) {
        if (nums[i] < third) return true;
        while (!st.empty() && nums[i] > st.top()) {
            third = st.top();
            st.pop();
        }
        st.push(nums[i]);
    }
    return false;
}

/**
 * Problem 9: Removing K Digits (LC 402)
 * --------------------------------------
 * 📿 Description:
 * Given a number string and integer k, remove k digits to form the smallest number.
 *
 * 🔍 Example:
 * Input: num = "1432219", k = 3
 * Output: "1219"
 *
 * 💡 Monotonic Stack Strategy:
 * --------------------------------------
 * - Use a string as a monotonic increasing stack.
 * - Remove elements from back if larger than current.
 * - Maintain order, avoid leading zeros.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 */
string RemoveKdigits(string num, int k) {
    string result;
    for (char c : num) {
        while (!result.empty() && result.back() > c && k > 0) {
            result.pop_back();
            k--;
        }
        if (!result.empty() || c != '0') { // Avoid leading zeroes
            result.push_back(c);
        }
    }
    while (k-- > 0 && !result.empty()) result.pop_back();
    return result.empty() ? "0" : result;
}

/**
 * Problem 10: Car Fleet (LC 853)
 * -------------------------------
 * 📿 Description:
 * n cars drive to the same target. Each car has position and speed.
 * Return the number of car fleets that arrive at target.
 *
 * 🔍 Example:
 * Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
 * Output: 3
 *
 * 💡 Monotonic Stack Strategy:
 * -------------------------------
 * - Sort cars by position descending.
 * - Use stack to track times to reach target.
 * - If new car arrives later or same time, they form fleet.
 *
 * ⏱️ Time: O(n log n)
 * 🧠 Space: O(n)
 */
int CarFleet(int target, vector<int>& position, vector<int>& speed) {
    int n = position.size();
    vector<pair<int, double>> cars;
    for (int i = 0; i < n; i++) {
        cars.emplace_back(position[i], (double)(target - position[i]) / speed[i]);
    }
    sort(cars.rbegin(), cars.rend());

    int fleets = 0;
    double lastTime = 0;
    for (const auto& [pos, time] : cars) {
        if (time > lastTime) {
            fleets++;
            lastTime = time;
        }
    }
    return fleets;
}

/**
 * Main Function: Test all Monotonic Stack problems
 */
int main() {
    // Test Problem 1: Next Greater Element
    cout << "Test Problem 1: Next Greater Element (LC 496) \n";
    vector<int> nums1 = {2, 1, 2, 4, 3};
    vector<int> res1 = NextGreaterElement(nums1);
    cout << "Output: ";
    for (int num : res1) cout << num << " ";
    cout << "\nExpected: 4 2 4 -1 -1\n";

    // Test Problem 2: Next Greater Element II
    cout << "\nTest Problem 2: Next Greater Element II (LC 503) \n";
    vector<int> nums2 = {1, 2, 1};
    vector<int> res2 = NextGreaterElements(nums2);
    cout << "Output: ";
    for (int num : res2) cout << num << " ";
    cout << "\nExpected: 2 -1 2\n";

    // Test Problem 3: Largest Rectangle in Histogram
    cout << "\nTest Problem 3: Largest Rectangle in Histogram (LC 84) \n";
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Output: " << LargestRectangleArea(heights) << "\nExpected: 10\n";

    // Test Problem 4: Maximal Rectangle
    cout << "\nTest Problem 4: Maximal Rectangle (LC 85) \n";
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}};
    cout << "Output: " << MaximalRectangle(matrix) << "\nExpected: 6\n";

    // Test Problem 5: Sliding Window Maximum
    cout << "\nTest Problem 5: Sliding Window Maximum (LC 239) \n";
    vector<int> nums5 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> res5 = MaxSlidingWindow(nums5, 3);
    cout << "Output: ";
    for (int num : res5) cout << num << " ";
    cout << "\nExpected: 3 3 5 5 6 7\n";

    // Test Problem 6: Daily Temperatures
    cout << "Test Problem 6: Daily Temperatures (LC 739) \n";
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> res6 = DailyTemperatures(temperatures);
    cout << "Output: ";
    for (int num : res6) cout << num << " ";
    cout << "\nExpected: 1 1 4 2 1 1 0 0\n";

    // Test Problem 7: Sum of Subarray Minimums
    cout << "\nTest Problem 7: Sum of Subarray Minimums (LC 907) \n";
    vector<int> arr7 = {3,1,2,4};
    cout << "Output: " << SumSubarrayMins(arr7) << "\nExpected: 17\n";

    // Test Problem 8: Find 132 Pattern
    cout << "\nTest Problem 8: Find 132 Pattern (LC 456) \n";
    vector<int> nums8 = {3, 1, 4, 2};
    cout << "Output: " << (Find132pattern(nums8) ? "true" : "false") << "\nExpected: true\n";

    // Test Problem 9: Removing K Digits
    cout << "\nTest Problem 9: Removing K Digits (LC 402) \n";
    cout << "Output: " << RemoveKdigits("1432219", 3) << "\nExpected: 1219\n";
    cout << "Output: " << RemoveKdigits("10200", 1) << "\nExpected: 200\n";

    // Test Problem 10: Car Fleet
    cout << "\nTest Problem 10: Car Fleet (LC 853) \n";
    vector<int> position = {10,8,0,5,3}, speed = {2,4,1,1,3};
    cout << "Output: " << CarFleet(12, position, speed) << "\nExpected: 3\n";

    return 0;
}
