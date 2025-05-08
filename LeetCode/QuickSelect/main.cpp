#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace std;

/**
 * Problem 1: Kth Largest Element in an Array (LC 215)
 * Description:
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Use QuickSelect to find the k-th largest element in O(n) average time complexity.
 * Example:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 */
/**
 * QuickSelect Algorithm
 * This function selects the k-th largest element in an unsorted array using QuickSelect.
 * QuickSelect is an optimization of QuickSort where we only recurse into one half of the array.
 * The average time complexity is O(n), while the worst case is O(n^2) if the pivot is poorly chosen.
 *
 * Steps:
 * 1. Choose a pivot randomly and move it to the end of the array.
 * 2. Partition the array such that elements greater than or equal to the pivot are moved to the left.
 * 3. If the pivot's position matches k, return it.
 * 4. Otherwise, recursively apply QuickSelect to the appropriate half of the array.
 */
template <typename T>
T quickSelect(vector<T>& nums, int left, int right, int k) {
    srand(time(nullptr));  // Set a random seed to ensure different pivot choices in different runs.

    // **Randomly select a pivot and move it to the end**
    int randomIndex = left + rand() % (right - left + 1);
    swap(nums[randomIndex], nums[right]);  // Swap the randomly chosen pivot with the last element.
    T pivot = nums[right];

    int p = left; // Pointer to place elements greater than or equal to pivot
    for (int i = left; i < right; ++i) {
        // Move elements greater than or equal to pivot to the left side
        if (nums[i] >= pivot) swap(nums[i], nums[p++]);
    }
    swap(nums[p], nums[right]);  // Place pivot in its correct position

    // If pivot is at index k, return it
    if (p == k) return nums[p];
    // If pivot index is smaller than k, search in the right part of the array
    return p < k ? quickSelect(nums, p + 1, right, k) : quickSelect(nums, left, p - 1, k);
}


int findKthLargest(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k - 1);
}

/**
 * Problem 2: Kth Smallest Element in a Sorted Matrix (LC 378)
 * Description:
 * Given an n x n matrix where each of the rows and columns is sorted in ascending order,
 * return the k-th smallest element.
 * Example:
 * Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
 * Output: 13
 */
int kthSmallest(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k - 1);
}

/**
 * Problem 3: K Closest Points to Origin (LC 973)
 * Description:
 * Given an array of points where points[i] = [xi, yi], return the k closest points to the origin (0,0).
 * Example:
 * Input: points = [[1,3],[-2,2]], k = 1
 * Output: [[-2,2]]
 */
int distanceSquared(vector<int>& point) {
    return point[0] * point[0] + point[1] * point[1];
}

void quickSelectPoints(vector<vector<int>>& points, int left, int right, int k) {
    int pivot = distanceSquared(points[right]), p = left;
    for (int i = left; i < right; ++i) {
        if (distanceSquared(points[i]) < pivot) swap(points[i], points[p++]);
    }
    swap(points[p], points[right]);
    if (p == k) return;
    p < k ? quickSelectPoints(points, p + 1, right, k) : quickSelectPoints(points, left, p - 1, k);
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    quickSelectPoints(points, 0, points.size() - 1, k);
    return vector<vector<int>>(points.begin(), points.begin() + k);
}

/**
 * Problem 4: Find the Median of an Unsorted Array (Variant)
 * Description:
 * Given an unsorted array, find its median.
 * Example:
 * Input: nums = [3, 2, 1, 5, 4]
 * Output: 3
 */
double findMedian(vector<int>& nums) {
    int n = nums.size();
    if (n % 2 == 1) return quickSelect(nums, 0, n - 1, n / 2);
    return (quickSelect(nums, 0, n - 1, n / 2 - 1) + quickSelect(nums, 0, n - 1, n / 2)) / 2.0;
}

 /**
 * Problem 5: Kth Largest Element in a Stream (LC 703)
 * Description:
 * Design a class that finds the kth largest element in a stream.
 *
 * Example:
 * Input: [4,5,8,2], k = 3, add(3), add(5), add(10), add(9), add(4)
 * Output: [4, 5, 5, 8, 8]
 */
class KthLargest {
    vector<int> nums;
    int k;
public:
    KthLargest(int k, vector<int>& nums) : nums(nums), k(k) {}

    int add(int val) {
        nums.push_back(val);
        return findKthLargest(nums, k);
    }
};

/**
 * Problem 6: Kth Missing Positive Number (LC 1539)
 * Description:
 * Given an array arr, return the kth missing positive integer.
 *
 * Example:
 * Input: arr = [2,3,4,7,11], k = 5
 * Output: 9
 */
int findKthPositive(vector<int>& arr, int k) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] - (mid + 1) >= k) right = mid;
        else left = mid + 1;
    }
    return left + k;
}

/**
 * Problem 7: Top K Frequent Elements (LC 347)
 * Description:
 * Given an integer array nums, return the k most frequent elements.
 *
 * Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 */
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> count;
    for (int num : nums) count[num]++;
    vector<int> uniqueNums;
    for (auto& [num, freq] : count) uniqueNums.push_back(num);
    return vector<int>(uniqueNums.begin(), uniqueNums.begin() + k);
}

/**
 * Problem 8: Kth Largest XOR Coordinate Value (LC 1738)
 * Description:
 * Given a 2D matrix, return the k-th largest value after computing the XOR of all elements.
 *
 * Example:
 * Input: matrix = [[5,2],[1,6]], k = 1
 * Output: 7
 */
int kthLargestValue(vector<vector<int>>& matrix, int k) {
    vector<int> xorVals;
    for (auto& row : matrix) xorVals.insert(xorVals.end(), row.begin(), row.end());
    return findKthLargest(xorVals, k);
}

/**
 * Problem 9: Minimum Cost to Hire K Workers (LC 857)
 * Description:
 * Given an array of quality and wage, return the minimum cost to hire k workers.
 *
 * Example:
 * Input: quality = [10,20,5], wage = [70,50,30], k = 2
 * Output: 105.0
 */
double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
    vector<double> ratio;
    for (size_t i = 0; i < quality.size(); i++)
        ratio.push_back((double)wage[i] / quality[i]);
    return quickSelect(ratio, 0, ratio.size() - 1, k - 1);
}

/**
 * Problem 10: K Weakest Rows in a Matrix (LC 1337)
 * Description:
 * Given a matrix, return the k weakest rows (based on the number of soldiers).
 *
 * Example:
 * Input: mat = [[1,1,0,0],[1,1,1,0],[1,0,0,0]], k = 2
 * Output: [2,0]
 */
vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
    vector<pair<int, int>> rowStrength;
    for (size_t i = 0; i < mat.size(); i++)
        rowStrength.emplace_back(accumulate(mat[i].begin(), mat[i].end(), 0), i);
    sort(rowStrength.begin(), rowStrength.end());
    vector<int> result;
    for (int i = 0; i < k; i++) result.push_back(rowStrength[i].second);
    return result;
}

int main() {
    // Testing Problem 1
    vector<int> nums = {3,2,1,5,6,4};
    cout << "Kth Largest Element: " << findKthLargest(nums, 2) << endl;

    // Testing Problem 3
    vector<vector<int>> points = {{1, 3}, {-2, 2}};
    auto res = kClosest(points, 1);
    cout << "Closest Point: [" << res[0][0] << "," << res[0][1] << "]" << endl;

    // Testing Problem 4
    vector<int> nums2 = {3, 2, 1, 5, 4};
    cout << "Median: " << findMedian(nums2) << endl;

    // Testing Problem 5: Kth Largest Element in a Stream
    vector<int> stream = {4,5,8,2};
    KthLargest kthLargest(3, stream);
    cout << "Kth Largest in Stream: " << kthLargest.add(3) << " " << kthLargest.add(5) << " " << kthLargest.add(10) << " " << kthLargest.add(9) << " " << kthLargest.add(4) << endl;

    // Testing Problem 6: Kth Missing Positive Number
    vector<int> arr = {2,3,4,7,11};
    cout << "Kth Missing Positive Number: " << findKthPositive(arr, 5) << endl;

    // Testing Problem 7: Top K Frequent Elements
    vector<int> nums7 = {1,1,1,2,2,3};
    vector<int> topK = topKFrequent(nums7, 2);
    cout << "Top K Frequent Elements: ";
    for (int num : topK) cout << num << " ";
    cout << endl;

    // Testing Problem 8: Kth Largest XOR Coordinate Value
    vector<vector<int>> matrix = {{5,2},{1,6}};
    cout << "Kth Largest XOR Coordinate Value: " << kthLargestValue(matrix, 1) << endl;

    // Testing Problem 9: Minimum Cost to Hire K Workers
    vector<int> quality = {10,20,5};
    vector<int> wage = {70,50,30};
    cout << "Minimum Cost to Hire K Workers: " << mincostToHireWorkers(quality, wage, 2) << endl;

    // Testing Problem 10: K Weakest Rows in a Matrix
    vector<vector<int>> mat = {{1,1,0,0},{1,1,1,0},{1,0,0,0}};
    vector<int> weakestRows = kWeakestRows(mat, 2);
    cout << "K Weakest Rows: ";
    for (int row : weakestRows) cout << row << " ";
    cout << endl;

    return 0;
}
