#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 📚 Prefix Sum Technique Overview
 * ================================
 *
 * 🧠 When to Use:
 * ---------------
 * Prefix sum is ideal for problems involving:
 * - Range sum queries (1D or 2D)
 * - Counting subarrays/submatrices with specific sum
 * - Detecting patterns like fixed sum, modulo divisibility, etc.
 * - Replacing nested sum loops with efficient lookup
 *
 * Typical problem keywords:
 * - "sum of subarray/submatrix"
 * - "number of subarrays with sum k"
 * - "range sum query"
 *
 * 💡 Core Idea:
 * ---------------
 * Compute cumulative sum `prefix[i] = sum(nums[0..i-1])`, then:
 * - Range sum [i..j] = prefix[j+1] - prefix[i]
 * - For exact target sum: if prefix[j+1] - prefix[i] == k,
 *   → prefix[i] == prefix[j+1] - k ⇒ count prefix values seen so far
 *
 * 🔁 Standard Template:
 * ---------------------
 * unordered_map<int, int> prefix_count{{0, 1}};
 * int sum = 0, res = 0;
 * for (int num : nums) {
 *     sum += num;
 *     res += prefix_count[sum - k];
 *     prefix_count[sum]++;
 * }
 *
 * 🧩 Variants:
 * ------------
 * 1. ✅ Fixed sum:
 *    - LC 560 Subarray Sum Equals K
 *
 * 2. ✅ Max/Longest subarray with sum:
 *    - Use map to track first occurrence of prefix_sum
 *
 * 3. ✅ Modulo problems:
 *    - Use prefix_sum % k and store mod in map
 *
 * 4. ✅ 2D prefix matrix:
 *    - prefix[i+1][j+1] = inclusion-exclusion of rectangle
 *
 * 5. ✅ Reduce 2D → 1D (LC 1074):
 *    - Fix row boundaries, compress to 1D col sums, apply prefix sum on that
 *
 * 🚨 Edge Cases:
 * --------------
 * - Negative numbers: use map instead of array
 * - Multiple 0s: initialize prefix_count[0] = 1
 * - Normalize negative mods: (mod + k) % k
 *
 * ⏱️ Complexity:
 * --------------
 * - Time: O(n) for 1D, O(m² * n) for 2D reductions
 * - Space: O(n) map or prefix array
 */

/**
 * Problem 1: Range Sum Query - Immutable (LC 303)
 * -----------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, implement a class `NumArray` that supports:
 * sumRange(i, j): Return the sum of elements between indices i and j (inclusive).
 *
 * 🔍 Example:
 * Input: nums = [-2, 0, 3, -5, 2, -1]
 * Query: sumRange(0, 2)
 * Output: 1
 *
 * 💡 Prefix Sum Strategy:
 * -----------------------------------------------
 * - Precompute a prefix sum array such that:
 *   prefix[i] = sum of nums[0..i-1]
 * - Then, sumRange(i, j) = prefix[j+1] - prefix[i]
 * - This allows answering any range sum query in O(1) time.
 *
 * 🚨 Edge Cases:
 * - Handle empty array input by initializing prefix_[0] = 0.
 * - Ensure indices are within bounds in production code.
 *
 * ⏱️ Time: O(n) preprocessing, O(1) per query
 * 🧠 Space: O(n) for prefix array
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
 * -----------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return the total number of 
 * continuous subarrays whose sum equals exactly `k`.
 *
 * 🔍 Example:
 * Input: nums = [1, 1, 1], k = 2
 * Output: 2
 *
 * 💡 Prefix Sum + Hash Map Strategy:
 * -----------------------------------------
 * - Let `prefix_sum` be the cumulative sum of elements up to current index.
 * - For each prefix_sum, if (prefix_sum - k) has occurred before,
 *   then there exists a previous subarray ending before current index that sums to `k`.
 * - Use a hashmap to store frequency of prefix sums seen so far.
 *
 * Algorithm:
 * - Initialize prefix_count[0] = 1 to handle case where prefix_sum == k.
 * - Iterate over array, update prefix_sum.
 * - At each step:
 *    → result += prefix_count[prefix_sum - k]
 *    → prefix_count[prefix_sum]++
 *
 * 🚨 Edge Cases:
 * - Handle zeros properly; subarrays with sum 0 may be valid.
 * - Can have overlapping subarrays.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n) — for prefix_sum count map
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
 * -------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return true if there exists a 
 * continuous subarray of at least length 2 such that the sum of its elements is a multiple of `k`.
 *
 * 🔍 Example:
 * Input: nums = [23, 2, 4, 6, 7], k = 6
 * Output: true
 * Explanation: [2, 4] and [4, 6] both sum to multiples of 6.
 *
 * 💡 Prefix Sum Modulo + Hash Map Strategy:
 * -------------------------------------------
 * - Let prefix_sum[i] = sum(nums[0..i])
 * - A subarray sum nums[i+1..j] is divisible by k if:
 *   (prefix_sum[j] - prefix_sum[i]) % k == 0  ⇒  prefix_sum[j] % k == prefix_sum[i] % k
 * - Use a map to store first occurrence of each mod value.
 * - If the same mod appears again and indices are ≥ 2 apart, return true.
 *
 * Algorithm:
 * - Initialize map[0] = -1 to handle case where the prefix itself is divisible by k.
 * - Iterate through nums:
 *     → Compute cumulative sum
 *     → mod = (k == 0 ? sum : sum % k)
 *     → If mod seen before and distance ≥ 2 → return true
 *     → Else store mod → index in map
 *
 * 🚨 Edge Cases:
 * - If k == 0, look for subarray with sum == 0 and length ≥ 2.
 * - Negative mod: normalize using (mod + k) % k if needed.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(k) — at most k mod classes stored in map
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
 * ------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return the number of non-empty 
 * subarrays whose sum is divisible by `k`.
 *
 * 🔍 Example:
 * Input: nums = [4,5,0,-2,-3,1], k = 5
 * Output: 7
 *
 * 💡 Prefix Sum Modulo + Frequency Hash Map:
 * ------------------------------------------------
 * - Use the prefix sum concept: sum of subarray [i..j] is divisible by k if:
 *   prefix[j+1] % k == prefix[i] % k
 * - Maintain a hash map to count how many times each mod class has occurred.
 * - For every current mod:
 *     → The number of previous prefix sums with the same mod gives the number of valid subarrays ending here.
 *
 * Implementation:
 * - Initialize mod_count[0] = 1 (empty prefix is divisible by k).
 * - Normalize mod to avoid negatives: (mod + k) % k.
 * - Add mod to map after counting (avoid overcounting current prefix).
 *
 * 🚨 Edge Cases:
 * - k can be negative → use absolute value if needed.
 * - Normalize mod to ensure non-negative key.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(k)
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
 * -------------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, find the length of the longest 
 * subarray that sums to exactly `k`.
 *
 * 🔍 Example:
 * Input: nums = [1, -1, 5, -2, 3], k = 3
 * Output: 4  (subarray: [1, -1, 5, -2])
 *
 * 💡 Prefix Sum + First Occurrence Map Strategy:
 * -------------------------------------------------------
 * - Let prefix_sum be the cumulative sum up to index `i`.
 * - If `prefix_sum - k` has appeared before at index `j`, then nums[j+1..i] sums to k.
 * - Track the **first occurrence** of each prefix_sum in a hash map.
 *   → This ensures the subarray is the longest possible for a given sum.
 *
 * Implementation:
 * - Update max_len = max(max_len, i - prefix_index[sum - k]) if match found.
 * - Only store first occurrence of a prefix_sum (don't overwrite).
 *
 * 🚨 Edge Cases:
 * - If sum == k from beginning → max_len = i + 1
 * - Can include negative numbers.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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
 * -------------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums`, return an array `output` where:
 * output[i] = product of all elements in `nums` except nums[i].
 * You must do this without using division and in O(n) time.
 *
 * 🔍 Example:
 * Input: nums = [1, 2, 3, 4]
 * Output: [24, 12, 8, 6]
 *
 * 💡 Prefix + Suffix Product Strategy:
 * -------------------------------------------------
 * - Create two passes:
 *   ➤ Left-to-right: store prefix product of all elements before index `i`.
 *   ➤ Right-to-left: multiply suffix product after index `i`.
 * - Use only the output array and two scalars for prefix and suffix.
 *
 * Implementation:
 * - Initialize output[i] = product of nums[0..i-1] (prefix)
 * - Traverse from right, multiply output[i] *= suffix, then update suffix *= nums[i]
 *
 * 🚨 Edge Cases:
 * - Zeros in array → handled naturally without division.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1) extra space (excluding output)
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
 * ---------------------------------------------------
 * 🧠 Description:
 * Given an array `nums` and an integer `k`, return the number of subarrays
 * that contain exactly `k` odd numbers.
 *
 * 🔍 Example:
 * Input: nums = [1,1,2,1,1], k = 3
 * Output: 2
 * Explanation: Subarrays [1,1,2,1], [1,2,1,1] both have exactly 3 odd numbers.
 *
 * 💡 Prefix Sum of Odd Counts + Hash Map:
 * ---------------------------------------------------
 * - Treat the problem as prefix sum of number of odds.
 * - Let `odd_count[i]` = number of odd numbers in nums[0..i].
 * - We want: odd_count[j] - odd_count[i] == k → odd_count[i] = odd_count[j] - k
 * - Maintain frequency of previous odd count values in a map.
 *
 * Implementation:
 * - Traverse array and increment count if number is odd.
 * - For each `odd_count`, add frequency of `odd_count - k` to result.
 * - Update the frequency of current odd count in map.
 *
 * 🚨 Edge Cases:
 * - Empty subarray not allowed (subarrays must be non-empty).
 * - All elements are even → count = 0.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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
 * ---------------------------------------------
 * 🧠 Description:
 * Given a binary array `nums` and an integer `goal`, return the number of 
 * non-empty subarrays whose sum is exactly equal to `goal`.
 *
 * 🔍 Example:
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 * Explanation: Subarrays [1,0,1], [0,1,0,1], [1,0,1], [1,0,1] have sum 2.
 *
 * 💡 Prefix Sum + Hash Map Count:
 * ---------------------------------------------
 * - Maintain running sum of elements.
 * - For each `sum`, check how many times `sum - goal` has occurred.
 * - Use hash map to track count of prefix sums.
 *
 * Implementation:
 * - Initialize prefix_count[0] = 1 for base case (empty prefix).
 * - Update result += prefix_count[sum - goal] at each index.
 *
 * 🚨 Edge Cases:
 * - Goal == 0: still need to count valid 0-sum subarrays.
 * - Binary array simplifies the problem (no negative numbers).
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
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
 * --------------------------------------------------
 * 🧠 Description:
 * Given a 2D matrix, implement a class `NumMatrix` that supports:
 * sumRegion(row1, col1, row2, col2): returns the sum of all elements in the rectangle
 * defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 *
 * 🔍 Example:
 * Input:
 * matrix = [
 *   [3, 0, 1, 4, 2],
 *   [5, 6, 3, 2, 1],
 *   [1, 2, 0, 1, 5],
 *   [4, 1, 0, 1, 7],
 *   [1, 0, 3, 0, 5]
 * ]
 * sumRegion(2, 1, 4, 3) = 8
 *
 * 💡 2D Prefix Sum Strategy:
 * --------------------------------------------------
 * - Build a (m+1)x(n+1) prefix sum matrix `prefix_` where:
 *   prefix_[i+1][j+1] = sum of all elements from (0,0) to (i,j)
 * - Use inclusion-exclusion to compute sumRegion in O(1):
 *   prefix[row2+1][col2+1] - prefix[row1][col2+1] - prefix[row2+1][col1] + prefix[row1][col1]
 *
 * 🚨 Edge Cases:
 * - Matrix may be empty → handle 0 size in constructor.
 *
 * ⏱️ Time: O(mn) to build, O(1) per query
 * 🧠 Space: O(mn)
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
 * --------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D matrix and an integer `target`, return the number of non-empty 
 * submatrices that sum to `target`.
 *
 * 🔍 Example:
 * Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
 * Output: 4
 * Explanation:
 * There are 4 submatrices that sum to 0:
 * - Single-element zeros
 * - Top-left + bottom-right quadrants where positives/negatives cancel
 *
 * 💡 Reduce to 1D Subarray Sum Strategy:
 * --------------------------------------------------------------
 * - Fix two row boundaries (top, bottom), compress rows into a 1D array `sums[]`
 *   where sums[col] = sum of elements between top and bottom rows for each column.
 * - For this 1D array, use the classic prefix sum + hashmap trick to count subarrays with sum = target.
 *   ➤ This reduces the 2D matrix problem to multiple 1D problems.
 *
 * Implementation:
 * - Iterate over all pairs of rows (O(m²) combinations).
 * - For each row pair, compress into column sums and apply prefix sum hash map.
 * - Use map to count how many times (current_sum - target) has occurred.
 *
 * 🚨 Edge Cases:
 * - Works with negative values.
 * - Can be optimized with precomputed prefix matrix for rows if needed.
 *
 * ⏱️ Time: O(m² * n)
 * 🧠 Space: O(n) — hash map and column buffer
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
