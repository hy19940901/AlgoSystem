#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * Problem 1: Search Insert Position (LC 35)
 * Description:
 * Given a sorted array and a target value, return the index where it would be inserted.
 * If the target is found, return its index. If not, return the index where it should be inserted.
 *
 * Example:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 *
 */
int searchInsertPosition(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

/**
 * Problem 2: Search in Rotated Sorted Array (LC 33)
 * Description:
 * Given a rotated sorted array and a target, return its index or -1 if not found.
 *
 * Example:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 */
int searchRotatedArray(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return -1;
}

/**
 * Problem 3: Find First and Last Position of Element in Sorted Array (LC 34)
 * Description:
 * Given a sorted array and a target value, find the first and last position of the element.
 *
 * Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 */
vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    vector<int> result(2, -1);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    if (static_cast<size_t>(left) >= nums.size() || nums[left] != target) return result;
    result[0] = left;
    right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right = mid - 1;
    }
    result[1] = right;
    return result;
}

/**
 * Problem 4: Find Minimum in Rotated Sorted Array (LC 153)
 * Description:
 * Given a rotated sorted array, find the minimum element.
 *
 * Example:
 * Input: nums = [3,4,5,1,2]
 * Output: 1
 */
int findMin(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return nums[left];
}

/**
 * Problem 5: Find Peak Element (LC 162)
 * Description:
 * Given an array of integers, find a peak element.
 *
 * Example:
 * Input: nums = [1,2,3,1]
 * Output: 2
 */
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) right = mid;
        else left = mid + 1;
    }
    return left;
}

/**
 * Problem 6: Valid Perfect Square (LC 367)
 * Description:
 * Given a positive integer num, return true if num is a perfect square.
 *
 * Example:
 * Input: num = 16
 * Output: true
 */
bool isPerfectSquare(int num) {
    long left = 1, right = num;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        long square = mid * mid;
        if (square == num) return true;
        else if (square < num) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

/**
 * Problem 7: Split Array Largest Sum (LC 410)
 * Description:
 * Given an array nums and an integer m, split the array into m non-empty continuous subarrays
 * such that the largest sum among these subarrays is minimized.
 *
 * Example:
 * Input: nums = [7,2,5,10,8], m = 2
 * Output: 18
 */
bool canSplit(vector<int>& nums, int m, int maxSum) {
    int count = 1, sum = 0;
    for (int num : nums) {
        if (sum + num > maxSum) {
            sum = num;
            count++;
            if (count > m) return false;
        } else {
            sum += num;
        }
    }
    return true;
}

int splitArray(vector<int>& nums, int m) {
    int left = *max_element(nums.begin(), nums.end()), right = accumulate(nums.begin(), nums.end(), 0);
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canSplit(nums, m, mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

/**
 * Problem 8: Kth Smallest Element in a Sorted Matrix (LC 378)
 * Description:
 * Given an n x n matrix where each row and column are sorted in ascending order,
 * return the kth smallest element.
 *
 * Example:
 * Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
 * Output: 13
 */
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int left = matrix[0][0], right = matrix.back().back();
    while (left < right) {
        int mid = left + (right - left) / 2, count = 0;
        for (auto& row : matrix) {
            count += upper_bound(row.begin(), row.end(), mid) - row.begin();
        }
        if (count < k) left = mid + 1;
        else right = mid;
    }
    return left;
}

/**
 * Problem 9: Find Square Root (LC 69)
 * Description:
 * Given a non-negative integer x, return the square root of x rounded down to the nearest integer.
 *
 * Example:
 * Input: x = 8
 * Output: 2
 */
int mySqrt(int x) {
    if (x == 0) return 0;
    int left = 1, right = x;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid && (mid + 1) > x / (mid + 1)) return mid;
        else if (mid < x / mid) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

/**
 * Problem 10: Capacity To Ship Packages Within D Days (LC 1011)
 * Description:
 * Given an array weights and an integer D, return the minimum capacity required to ship all packages within D days.
 *
 * Example:
 * Input: weights = [1,2,3,4,5,6,7,8,9,10], D = 5
 * Output: 15
 */
bool canShip(vector<int>& weights, int D, int capacity) {
    int days = 1, total = 0;
    for (int weight : weights) {
        total += weight;
        if (total > capacity) {
            days++;
            total = weight;
        }
    }
    return days <= D;
}

int shipWithinDays(vector<int>& weights, int D) {
    int left = *max_element(weights.begin(), weights.end()), right = accumulate(weights.begin(), weights.end(), 0);
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canShip(weights, D, mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

int main() {
    // Test Problem 1: Search Insert Position
    vector<int> nums1 = {1,3,5,6};
    cout << "Test 1 - Search Insert Position: " << searchInsertPosition(nums1, 5) << " (Expected: 2)" << endl;
    cout << "Test 1 - Search Insert Position: " << searchInsertPosition(nums1, 2) << " (Expected: 1)" << endl;
    cout << "Test 1 - Search Insert Position: " << searchInsertPosition(nums1, 7) << " (Expected: 4)" << endl;

    // Test Problem 2: Search in Rotated Sorted Array
    vector<int> nums2 = {4,5,6,7,0,1,2};
    cout << "Test 2 - Search in Rotated Sorted Array: " << searchRotatedArray(nums2, 0) << " (Expected: 4)" << endl;
    cout << "Test 2 - Search in Rotated Sorted Array: " << searchRotatedArray(nums2, 3) << " (Expected: -1)" << endl;

    // Test Problem 3: Find First and Last Position
    vector<int> nums3 = {5,7,7,8,8,10};
    vector<int> result3 = searchRange(nums3, 8);
    cout << "Test 3 - Find First and Last Position: [" << result3[0] << ", " << result3[1] << "] (Expected: [3,4])" << endl;

    // Test Problem 4: Find Minimum in Rotated Sorted Array
    vector<int> nums4 = {3,4,5,1,2};
    cout << "Test 4 - Find Minimum: " << findMin(nums4) << " (Expected: 1)" << endl;

    // Test Problem 5: Find Peak Element
    vector<int> nums5 = {1,2,3,1};
    cout << "Test 5 - Find Peak Element: " << findPeakElement(nums5) << " (Expected: 2)" << endl;

    // Test Problem 6: Valid Perfect Square
    cout << "Test 6 - Valid Perfect Square: " << isPerfectSquare(16) << " (Expected: true)" << endl;
    cout << "Test 6 - Valid Perfect Square: " << isPerfectSquare(14) << " (Expected: false)" << endl;

    // Test Problem 7: Split Array Largest Sum
    vector<int> nums7 = {7,2,5,10,8};
    cout << "Test 7 - Split Array Largest Sum: " << splitArray(nums7, 2) << " (Expected: 18)" << endl;

    // Test Problem 8: Kth Smallest Element in a Sorted Matrix
    vector<vector<int>> matrix8 = {{1,5,9},{10,11,13},{12,13,15}};
    cout << "Test 8 - Kth Smallest Element in Sorted Matrix: " << kthSmallest(matrix8, 8) << " (Expected: 13)" << endl;

    // Test Problem 9: Find Square Root
    cout << "Test 9 - Find Square Root: " << mySqrt(8) << " (Expected: 2)" << endl;
    cout << "Test 9 - Find Square Root: " << mySqrt(16) << " (Expected: 4)" << endl;

    // Test Problem 10: Capacity To Ship Packages Within D Days
    vector<int> weights10 = {1,2,3,4,5,6,7,8,9,10};
    cout << "Test 10 - Capacity to Ship Within Days: " << shipWithinDays(weights10, 5) << " (Expected: 15)" << endl;

    return 0;
}
