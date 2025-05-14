#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * Problem 1: Range Sum Query - Immutable (LC 303)
 * Description:
 * Given an integer array nums, implement a NumArray class that supports the query sumRange(i, j).
 * Approach:
 * Precompute prefix sum array such that sumRange(i, j) = prefix[j+1] - prefix[i].
 * Example:
 * Input: nums = [-2, 0, 3, -5, 2, -1]
 * Output: sumRange(0, 2) = 1
 */
class NumArray {
private:
    vector<int> prefix_;
public:
    NumArray(vector<int>& nums) {
        prefix_.push_back(0);
        for (int num : nums)
            prefix_.push_back(prefix_.back() + num);
    }
    int SumRange(int left, int right) {
        return prefix_[right + 1] - prefix_[left];
    }
};

/**
 * Problem 2: Subarray Sum Equals K (LC 560)
 * Description:
 * Given an array of integers and an integer k, find the total number of continuous subarrays whose sum equals to k.
 * Approach:
 * Use prefix sum + hashmap to count cumulative sum occurrences.
 * Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 */
int SubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_count{{0, 1}};
    int sum = 0, count = 0;
    for (int num : nums) {
        sum += num;
        count += prefix_count[sum - k];
        prefix_count[sum]++;
    }
    return count;
}

/**
 * Problem 3: Continuous Subarray Sum (LC 523)
 * Description:
 * Given an integer array and an integer k, return true if the array has a continuous subarray of size at least 2 whose sum is a multiple of k.
 * Approach:
 * Use prefix sum mod k and a hashmap to track earliest mod value occurrence.
 * Example:
 * Input: nums = [23,2,4,6,7], k = 6
 * Output: true
 */
bool CheckSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mod_index{{0, -1}};
    int sum = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        sum += nums[i];
        int mod = k == 0 ? sum : sum % k;
        if (mod_index.count(mod)) {
            if (i - mod_index[mod] >= 2) return true;
        } else {
            mod_index[mod] = i;
        }
    }
    return false;
}

/**
 * Problem 4: Subarray Sums Divisible by K (LC 974)
 * Description:
 * Return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.
 * Approach:
 * Use prefix mod count hashmap, similar to Problem 3.
 * Example:
 * Input: nums = [4,5,0,-2,-3,1], k = 5
 * Output: 7
 */
int SubarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> mod_count{{0, 1}};
    int sum = 0, count = 0;
    for (int num : nums) {
        sum += num;
        int mod = ((sum % k) + k) % k; // handle negative
        count += mod_count[mod];
        mod_count[mod]++;
    }
    return count;
}

/**
 * Problem 5: Maximum Size Subarray Sum Equals k (LC 325)
 * Description:
 * Find the maximum length of a subarray that sums to k.
 * Approach:
 * Use prefix sum + hashmap to store first occurrence of prefix sum.
 * Example:
 * Input: nums = [1, -1, 5, -2, 3], k = 3
 * Output: 4
 */
int MaxSubArrayLen(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_index;
    int sum = 0, max_len = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        sum += nums[i];
        if (sum == k) max_len = i + 1;
        if (prefix_index.count(sum - k))
            max_len = max(max_len, static_cast<int>(i) - prefix_index[sum - k]);
        if (!prefix_index.count(sum))
            prefix_index[sum] = i;
    }
    return max_len;
}

/**
 * Problem 6: Product of Array Except Self (LC 238)
 * Description:
 * Return an array output such that output[i] is equal to the product of all elements of nums except nums[i].
 * Approach:
 * Use prefix product from left and right.
 * Example:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 */
vector<int> ProductExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);
    int left = 1, right = 1;
    for (int i = 0; i < n; i++) {
        res[i] *= left;
        left *= nums[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}

/**
 * Problem 7: Count Number of Nice Subarrays (LC 1248)
 * Description:
 * Count the number of subarrays with exactly k odd numbers.
 * Approach:
 * Use prefix sum of odd counts and hashmap.
 * Example:
 * Input: nums = [1,1,2,1,1], k = 3
 * Output: 2
 */
int NumberOfSubarrays(vector<int>& nums, int k) {
    unordered_map<int, int> count{{0, 1}};
    int odd = 0, res = 0;
    for (int num : nums) {
        odd += num % 2;
        res += count[odd - k];
        count[odd]++;
    }
    return res;
}

/**
 * Problem 8: Binary Subarrays With Sum (LC 930)
 * Description:
 * Count the number of subarrays that sum to a given target in a binary array.
 * Approach:
 * Same as Problem 2, using hashmap of prefix sums.
 * Example:
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 */
int NumSubarraysWithSum(vector<int>& nums, int goal) {
    unordered_map<int, int> prefix_count{{0, 1}};
    int sum = 0, count = 0;
    for (int num : nums) {
        sum += num;
        count += prefix_count[sum - goal];
        prefix_count[sum]++;
    }
    return count;
}

/**
 * Problem 9: Range Sum Query 2D - Immutable (LC 304)
 * Description:
 * Implement a 2D matrix range sum query with precomputed prefix sum.
 * Approach:
 * Use prefix[i+1][j+1] for matrix[i][j], sumRegion is computed via inclusion-exclusion.
 * Example:
 * Input: sumRegion(2,1,4,3)
 * Output: 8
 */
class NumMatrix {
private:
    vector<vector<int>> prefix_;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0;
        prefix_ = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                prefix_[i + 1][j + 1] = matrix[i][j] + prefix_[i][j + 1] + prefix_[i + 1][j] - prefix_[i][j];
    }
    int SumRegion(int row1, int col1, int row2, int col2) {
        return prefix_[row2 + 1][col2 + 1] - prefix_[row1][col2 + 1] - prefix_[row2 + 1][col1] + prefix_[row1][col1];
    }
};

/**
 * Problem 10: Number of Submatrices That Sum to Target (LC 1074)
 * Description:
 * Given a matrix and target, return the number of non-empty submatrices that sum to target.
 * Approach:
 * Fix row pairs and reduce to 1D subarray sum to target (use hash map).
 * Example:
 * Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
 * Output: 4
 */
int NumSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size(), res = 0;
    for (int top = 0; top < m; ++top) {
        vector<int> sum(n, 0);
        for (int bottom = top; bottom < m; ++bottom) {
            for (int col = 0; col < n; ++col)
                sum[col] += matrix[bottom][col];
            unordered_map<int, int> mp{{0, 1}};
            int s = 0;
            for (int val : sum) {
                s += val;
                res += mp[s - target];
                mp[s]++;
            }
        }
    }
    return res;
}

int main() {
    cout << "===== Prefix Sum Problems =====\n\n";

    // Problem 1
    vector<int> nums1 = {-2, 0, 3, -5, 2, -1};
    NumArray obj(nums1);
    cout << "Problem 1: SumRange(0,2) = " << obj.SumRange(0,2) << "\n\n";

    // Problem 2
    vector<int> nums2 = {1,1,1};
    cout << "Problem 2: SubarraySum = " << SubarraySum(nums2, 2) << "\n\n";

    // Problem 3
    vector<int> nums3 = {23, 2, 4, 6, 7};
    cout << "Problem 3: CheckSubarraySum = " << (CheckSubarraySum(nums3, 6) ? "true" : "false") << "\n\n";

    // Problem 4
    vector<int> nums4 = {4,5,0,-2,-3,1};
    cout << "Problem 4: SubarraysDivByK = " << SubarraysDivByK(nums4, 5) << "\n\n";

    // Problem 5
    vector<int> nums5 = {1, -1, 5, -2, 3};
    cout << "Problem 5: MaxSubArrayLen = " << MaxSubArrayLen(nums5, 3) << "\n\n";

    // Problem 6
    vector<int> nums6 = {1,2,3,4};
    vector<int> res6 = ProductExceptSelf(nums6);
    cout << "Problem 6: ProductExceptSelf = ";
    for (int x : res6) cout << x << " ";
    cout << "\n\n";

    // Problem 7
    vector<int> nums7 = {1,1,2,1,1};
    cout << "Problem 7: NumberOfSubarrays = " << NumberOfSubarrays(nums7, 3) << "\n\n";

    // Problem 8
    vector<int> nums8 = {1,0,1,0,1};
    cout << "Problem 8: NumSubarraysWithSum = " << NumSubarraysWithSum(nums8, 2) << "\n\n";

    // Problem 9
    vector<vector<int>> mat9 = {{3, 0, 1, 4, 2},
                                {5, 6, 3, 2, 1},
                                {1, 2, 0, 1, 5},
                                {4, 1, 0, 1, 7},
                                {1, 0, 3, 0, 5}};
    NumMatrix obj9(mat9);
    cout << "Problem 9: SumRegion = " << obj9.SumRegion(2, 1, 4, 3) << "\n\n";

    // Problem 10
    vector<vector<int>> mat10 = {{0,1,0},{1,1,1},{0,1,0}};
    cout << "Problem 10: NumSubmatrixSumTarget = " << NumSubmatrixSumTarget(mat10, 0) << "\n\n";

    return 0;
}
