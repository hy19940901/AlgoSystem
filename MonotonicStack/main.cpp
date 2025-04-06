#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

using namespace std;

/**
 * Problem 1: Next Greater Element I (LC 496)
 * Description:
 * Given an array `nums`, find the next greater element for each index.
 * The next greater element is the first greater element found on the right.
 * If there is no greater element, return -1.
 *
 * Example:
 * Input: nums = [2, 1, 2, 4, 3]
 * Output: [4, 2, 4, -1, -1]
 */
vector<int> nextGreaterElement(vector<int>& nums) {
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
 * Description:
 * Given a circular array `nums`, find the next greater element for each index.
 * The next greater element is the first greater element found when traversing the array circularly.
 *
 * Example:
 * Input: nums = [1, 2, 1]
 * Output: [2, -1, 2]
 */
vector<int> nextGreaterElements(vector<int>& nums) {
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
 * Description:
 * Given an array of heights representing a histogram, find the area of the largest rectangle.
 *
 * Example:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 */
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    heights.push_back(0); // Sentinel to clear stack
    int maxArea = 0;
    for (int i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    return maxArea;
}

/**
 * Problem 4: Maximal Rectangle (LC 85)
 * Description:
 * Given a binary matrix, find the largest rectangle containing only 1s.
 *
 * Example:
 * Input:
 * matrix =
 * [
 *  ["1","0","1","0","0"],
 *  ["1","0","1","1","1"],
 *  ["1","1","1","1","1"],
 *  ["1","0","0","1","0"]
 * ]
 * Output: 6
 */
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int maxArea = 0, cols = matrix[0].size();
    vector<int> heights(cols, 0);
    for (const auto& row : matrix) {
        for (int j = 0; j < cols; j++) {
            heights[j] = (row[j] == '1') ? heights[j] + 1 : 0;
        }
        maxArea = max(maxArea, largestRectangleArea(heights));
    }
    return maxArea;
}

/**
 * Problem 5: Sliding Window Maximum (LC 239)
 * Description:
 * Given an array and an integer `k`, return the maximum value in each window of size `k`.
 *
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

/**
 * Problem 6: Daily Temperatures (LC 739)
 * Description:
 * Given a list of daily temperatures, return a list where each element tells 
 * you how many days you would have to wait until a warmer temperature.
 * If there is no future day with a warmer temperature, return 0.
 *
 * Example:
 * Input: temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 * Output: [1, 1, 4, 2, 1, 1, 0, 0]
 */
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> result(temperatures.size(), 0);
    stack<int> st;
    for (int i = 0; i < temperatures.size(); i++) {
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
 * Description:
 * Given an array `arr`, find the sum of `min` values of all subarrays.
 * The answer may be large, so return it **modulo 10^9 + 7**.
 *
 * Example:
 * Input: arr = [3,1,2,4]
 * Output: 17
 */
int sumSubarrayMins(vector<int>& arr) {
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
 * Description:
 * Given an array of numbers, find if there exists a 132 pattern:
 *  i < j < k  such that nums[i] < nums[k] < nums[j]
 *
 * Example:
 * Input: nums = [3,1,4,2]
 * Output: true
 */
bool find132pattern(vector<int>& nums) {
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
 * Description:
 * Given a string representing a number and an integer `k`, remove `k` digits
 * so that the remaining number is the smallest possible.
 *
 * Example:
 * Input: num = "1432219", k = 3
 * Output: "1219"
 */
string removeKdigits(string num, int k) {
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
 * Description:
 * There are `n` cars on a one-lane road heading towards the same destination.
 * Each car has a `position` and a `speed`. A **car fleet** is a group of cars
 * that travel together at the same speed. Return the number of car fleets.
 *
 * Example:
 * Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
 * Output: 3
 */
int carFleet(int target, vector<int>& position, vector<int>& speed) {
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
    vector<int> res1 = nextGreaterElement(nums1);
    cout << "Output: ";
    for (int num : res1) cout << num << " ";
    cout << "\nExpected: 4 2 4 -1 -1\n";

    // Test Problem 2: Next Greater Element II
    cout << "\nTest Problem 2: Next Greater Element II (LC 503) \n";
    vector<int> nums2 = {1, 2, 1};
    vector<int> res2 = nextGreaterElements(nums2);
    cout << "Output: ";
    for (int num : res2) cout << num << " ";
    cout << "\nExpected: 2 -1 2\n";

    // Test Problem 3: Largest Rectangle in Histogram
    cout << "\nTest Problem 3: Largest Rectangle in Histogram (LC 84) \n";
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Output: " << largestRectangleArea(heights) << "\nExpected: 10\n";

    // Test Problem 4: Maximal Rectangle
    cout << "\nTest Problem 4: Maximal Rectangle (LC 85) \n";
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}};
    cout << "Output: " << maximalRectangle(matrix) << "\nExpected: 6\n";

    // Test Problem 5: Sliding Window Maximum
    cout << "\nTest Problem 5: Sliding Window Maximum (LC 239) \n";
    vector<int> nums5 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> res5 = maxSlidingWindow(nums5, 3);
    cout << "Output: ";
    for (int num : res5) cout << num << " ";
    cout << "\nExpected: 3 3 5 5 6 7\n";

    // Test Problem 6: Daily Temperatures
    cout << "Test Problem 6: Daily Temperatures (LC 739) \n";
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> res6 = dailyTemperatures(temperatures);
    cout << "Output: ";
    for (int num : res6) cout << num << " ";
    cout << "\nExpected: 1 1 4 2 1 1 0 0\n";

    // Test Problem 7: Sum of Subarray Minimums
    cout << "\nTest Problem 7: Sum of Subarray Minimums (LC 907) \n";
    vector<int> arr7 = {3,1,2,4};
    cout << "Output: " << sumSubarrayMins(arr7) << "\nExpected: 17\n";

    // Test Problem 8: Find 132 Pattern
    cout << "\nTest Problem 8: Find 132 Pattern (LC 456) \n";
    vector<int> nums8 = {3, 1, 4, 2};
    cout << "Output: " << (find132pattern(nums8) ? "true" : "false") << "\nExpected: true\n";

    // Test Problem 9: Removing K Digits
    cout << "\nTest Problem 9: Removing K Digits (LC 402) \n";
    cout << "Output: " << removeKdigits("1432219", 3) << "\nExpected: 1219\n";
    cout << "Output: " << removeKdigits("10200", 1) << "\nExpected: 200\n";

    // Test Problem 10: Car Fleet
    cout << "\nTest Problem 10: Car Fleet (LC 853) \n";
    vector<int> position = {10,8,0,5,3}, speed = {2,4,1,1,3};
    cout << "Output: " << carFleet(12, position, speed) << "\nExpected: 3\n";

    return 0;
}
