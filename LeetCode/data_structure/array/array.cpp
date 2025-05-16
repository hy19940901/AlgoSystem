#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem 1: Remove Duplicates from Sorted Array (LC 26)
 * Description:
 * Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place
 * such that each unique element appears only once. Return the number of unique elements.
 * Example:
 * Input: nums = [1, 1, 2]
 * Output: 2, nums = [1, 2, _]
 */
int RemoveDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int index = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1]) {
            nums[index++] = nums[i];
        }
    }
    return index;
}

/**
 * Problem 2: Move Zeroes (LC 283)
 * Description:
 * Given an integer array nums, move all 0's to the end while maintaining the relative order
 * of the non-zero elements.
 * Example:
 * Input: nums = [0, 1, 0, 3, 12]
 * Output: [1, 3, 12, 0, 0]
 */
void MoveZeroes(vector<int>& nums) {
    int index = 0;
    for (int num : nums) {
        if (num != 0) nums[index++] = num;
    }
    while (static_cast<size_t>(index) < nums.size()) nums[index++] = 0;
}

/**
 * Problem 3: Two Sum (LC 1)
 * Description:
 * Given an array of integers nums and an integer target, return indices of the two numbers
 * such that they add up to target.
 * Example:
 * Input: nums = [2, 7, 11, 15], target = 9
 * Output: [0, 1]
 */
vector<int> TwoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (size_t i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], static_cast<int>(i)};
        }
        seen[nums[i]] = i;
    }
    return {};
}

/**
 * Problem 4: Best Time to Buy and Sell Stock (LC 121)
 * Description:
 * Given an array prices where prices[i] is the price of a stock on the i-th day.
 * Return the maximum profit you can achieve from a single buy and sell.
 * Example:
 * Input: prices = [7, 1, 5, 3, 6, 4]
 * Output: 5
 */
int MaxProfit(vector<int>& prices) {
    int min_price = INT_MAX, max_profit = 0;
    for (int price : prices) {
        min_price = min(min_price, price);
        max_profit = max(max_profit, price - min_price);
    }
    return max_profit;
}

/**
 * Problem 5: Contains Duplicate (LC 217)
 * Description:
 * Given an integer array nums, return true if any value appears at least twice.
 * Example:
 * Input: nums = [1, 2, 3, 1]
 * Output: true
 */
bool ContainsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

/**
 * Problem 6: Rotate Array (LC 189)
 * Description:
 * Given an integer array nums, rotate the array to the right by k steps.
 * Example:
 * Input: nums = [1,2,3,4,5,6,7], k = 3
 * Output: [5,6,7,1,2,3,4]
 */
void RotateArray(vector<int>& nums, int k) {
    k = k % nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

/**
 * Problem 7: Intersection of Two Arrays (LC 349)
 * Description:
 * Given two arrays nums1 and nums2, return an array of their intersection.
 * Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 */
vector<int> Intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end()), result;
    for (int num : nums2)
        if (set1.count(num)) result.insert(num);
    return vector<int>(result.begin(), result.end());
}

/**
 * Problem 8: Find All Duplicates in an Array (LC 442)
 * Description:
 * Given an array of integers, return all elements that appear twice.
 * Example:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [2,3]
 */
vector<int> FindDuplicates(vector<int>& nums) {
    vector<int> result;
    for (int num : nums) {
        int index = abs(num) - 1;
        if (nums[index] < 0) result.push_back(index + 1);
        nums[index] = -nums[index];
    }
    return result;
}

/**
 * Problem 9: Missing Number (LC 268)
 * Description:
 * Given an array nums containing n distinct numbers in the range [0, n], return the missing number.
 * Example:
 * Input: nums = [3,0,1]
 * Output: 2
 */
int MissingNumber(vector<int>& nums) {
    int sum = nums.size() * (nums.size() + 1) / 2;
    for (int num : nums) sum -= num;
    return sum;
}

/**
 * Problem 10: Find Peak Element (LC 162)
 * Description:
 * A peak element is an element that is strictly greater than its neighbors.
 * Example:
 * Input: nums = [1,2,3,1]
 * Output: 2
 */
int FindPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) right = mid;
        else left = mid + 1;
    }
    return left;
}

/**
 * Problem 11: Third Maximum Number (LC 414)
 * Description:
 * Given an integer array, return the third distinct maximum number in this array.
 * Example:
 * Input: nums = [3,2,1]
 * Output: 1
 */
int ThirdMax(vector<int>& nums) {
    long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
    for (int num : nums) {
        if (num == first || num == second || num == third) continue;
        if (num > first) {
            third = second;
            second = first;
            first = num;
        } else if (num > second) {
            third = second;
            second = num;
        } else if (num > third) {
            third = num;
        }
    }
    return third == LONG_MIN ? first : third;
}

/**
 * Problem 12: Find Pivot Index (LC 724)
 * Description:
 * Given an array nums, return the pivot index where the sum of left elements equals sum of right elements.
 * Example:
 * Input: nums = [1,7,3,6,5,6]
 * Output: 3
 */
int PivotIndex(vector<int>& nums) {
    int total_sum = 0, left_sum = 0;
    for (int num : nums) total_sum += num;
    for (size_t i = 0; i < nums.size(); i++) {
        if (left_sum == total_sum - left_sum - nums[i]) return i;
        left_sum += nums[i];
    }
    return -1;
}

/**
 * Problem 13: Find Disappeared Numbers (LC 448)
 * Description:
 * Given an array nums of n integers where nums[i] is in the range [1, n], return the missing numbers.
 * Example:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [5,6]
 */
vector<int> FindDisappearedNumbers(vector<int>& nums) {
    vector<int> result;
    for (int num : nums) {
        int index = abs(num) - 1;
        if (nums[index] > 0) nums[index] = -nums[index];
    }
    for (size_t i = 0; i < nums.size(); i++)
        if (nums[i] > 0) result.push_back(i + 1);
    return result;
}

/**
 * Problem 14: Maximum Subarray (LC 53)
 * Description:
 * Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum.
 * Example:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 */
int MaxSubArray(vector<int>& nums) {
    int max_sum = nums[0], cur_sum = nums[0];
    for (size_t i = 1; i < nums.size(); i++) {
        cur_sum = max(nums[i], cur_sum + nums[i]);
        max_sum = max(max_sum, cur_sum);
    }
    return max_sum;
}

/**
 * Problem 15: Sort Array by Parity (LC 905)
 * Description:
 * Given an integer array nums, move all even numbers to the beginning and all odd numbers to the end.
 * Example:
 * Input: nums = [3,1,2,4]
 * Output: [2,4,3,1]
 */
vector<int> SortArrayByParity(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        if (nums[left] % 2 > nums[right] % 2) {
            swap(nums[left], nums[right]);
        }
        if (nums[left] % 2 == 0) left++;
        if (nums[right] % 2 == 1) right--;
    }
    return nums;
}

/**
 * Problem 16: Largest Number (LC 179)
 * Description:
 * Given a list of non-negative integers, arrange them to form the largest number.
 * Example:
 * Input: nums = [10,2]
 * Output: "210"
 */
string LargestNumber(vector<int>& nums) {
    vector<string> str_nums;
    for (int num : nums) str_nums.push_back(to_string(num));
    sort(str_nums.begin(), str_nums.end(), [](string& a, string& b) { return a + b > b + a; });
    if (str_nums[0] == "0") return "0";
    string result;
    for (string& s : str_nums) result += s;
    return result;
}

/**
 * Problem 17: Subarray Sum Equals K (LC 560)
 * Description:
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals k.
 * Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 */
int SubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_sum;
    prefix_sum[0] = 1;
    int sum = 0, count = 0;
    for (int num : nums) {
        sum += num;
        if (prefix_sum.count(sum - k)) count += prefix_sum[sum - k];
        prefix_sum[sum]++;
    }
    return count;
}

/**
 * Problem 18: Maximum Product of Three Numbers (LC 628)
 * Description:
 * Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
 * Example:
 * Input: nums = [1,2,3]
 * Output: 6
 */
int MaximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    return max(nums[n - 1] * nums[n - 2] * nums[n - 3], nums[0] * nums[1] * nums[n - 1]);
}

/**
 * Problem 19: Find Maximum Average Subarray I (LC 643)
 * Description:
 * Given an array of integers nums, find the contiguous subarray of length k that has the maximum average value.
 * Example:
 * Input: nums = [1,12,-5,-6,50,3], k = 4
 * Output: 12.75
 */
double FindMaxAverage(vector<int>& nums, int k) {
    double sum = 0;
    for (size_t i = 0; i < static_cast<size_t>(k); i++) sum += nums[i];
    double max_avg = sum;
    for (size_t i = k; i < nums.size(); i++) {
        sum += nums[i] - nums[i - k];
        max_avg = max(max_avg, sum);
    }
    return max_avg / k;
}

/**
 * Problem 20: Can Place Flowers (LC 605)
 * Description:
 * Given a flowerbed (an array of 0s and 1s), check if n flowers can be planted without violating adjacent flower rule.
 * Example:
 * Input: flowerbed = [1,0,0,0,1], n = 1
 * Output: true
 */
bool CanPlaceFlowers(vector<int>& flowerbed, int n) {
    for (size_t i = 0; i < flowerbed.size() && n > 0; i++) {
        if (flowerbed[i] == 0 &&
            (i == 0 || flowerbed[i - 1] == 0) &&
            (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0)) {
            flowerbed[i] = 1;
            n--;
        }
    }
    return n == 0;
}

/**
 * Main function: Test all array functions
 */
int main() {
    // Test Problem 1: Remove Duplicates from Sorted Array
    cout << "Test Problem 1: Remove Duplicates from Sorted Array (LC 26) \n";
    vector<int> nums1 = {1, 1, 2};
    int len1 = RemoveDuplicates(nums1);
    cout << "Output: " << len1 << " (Expected: 2)\n";

    // Test Problem 2: Move Zeroes
    cout << "\nTest Problem 2: Move Zeroes (LC 283) \n";
    vector<int> nums2 = {0, 1, 0, 3, 12};
    MoveZeroes(nums2);
    cout << "Output: ";
    for (int num : nums2) cout << num << " ";
    cout << "(Expected: 1 3 12 0 0)\n";

    // Test Problem 3: Two Sum
    cout << "\nTest Problem 3: Two Sum (LC 1) \n";
    vector<int> nums3 = {2, 7, 11, 15};
    vector<int> res3 = TwoSum(nums3, 9);
    cout << "Output: " << res3[0] << ", " << res3[1] << " (Expected: 0, 1)\n";

    // Test Problem 4: Best Time to Buy and Sell Stock
    cout << "\nTest Problem 4: Best Time to Buy and Sell Stock (LC 121) \n";
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Output: " << MaxProfit(prices) << " (Expected: 5)\n";

    // Test Problem 5: Contains Duplicate
    cout << "\nTest Problem 5: Contains Duplicate (LC 217) \n";
    vector<int> nums5 = {1, 2, 3, 1};
    cout << "Output: " << (ContainsDuplicate(nums5) ? "true" : "false") << " (Expected: true)\n";

    // Test Problem 6: Rotate Array
    cout << "Test Problem 6: Rotate Array (LC 189) \n";
    vector<int> nums6 = {1, 2, 3, 4, 5, 6, 7};
    RotateArray(nums6, 3);
    cout << "Output: ";
    for (int num : nums6) cout << num << " ";
    cout << "(Expected: 5 6 7 1 2 3 4)\n";

    // Test Problem 7: Intersection of Two Arrays
    cout << "\nTest Problem 7: Intersection of Two Arrays (LC 349) \n";
    vector<int> nums7_1 = {1, 2, 2, 1}, nums7_2 = {2, 2};
    vector<int> res7 = Intersection(nums7_1, nums7_2);
    cout << "Output: ";
    for (int num : res7) cout << num << " ";
    cout << "(Expected: 2)\n";

    // Test Problem 8: Find All Duplicates in an Array
    cout << "\nTest Problem 8: Find All Duplicates in an Array (LC 442) \n";
    vector<int> nums8 = {4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> res8 = FindDuplicates(nums8);
    cout << "Output: ";
    for (int num : res8) cout << num << " ";
    cout << "(Expected: 2 3)\n";

    // Test Problem 9: Missing Number
    cout << "\nTest Problem 9: Missing Number (LC 268) \n";
    vector<int> nums9 = {3, 0, 1};
    cout << "Output: " << MissingNumber(nums9) << " (Expected: 2)\n";

    // Test Problem 10: Find Peak Element
    cout << "\nTest Problem 10: Find Peak Element (LC 162) \n";
    vector<int> nums10 = {1, 2, 3, 1};
    cout << "Output: " << FindPeakElement(nums10) << " (Expected: 2)\n";

    // Test Problem 11: Third Maximum Number
    cout << "\nTest Problem 11: Third Maximum Number (LC 414) \n";
    vector<int> nums11 = {3, 2, 1};
    cout << "Output: " << ThirdMax(nums11) << " (Expected: 1)\n";

    vector<int> nums11_2 = {2, 2, 3, 1};
    cout << "Output: " << ThirdMax(nums11_2) << " (Expected: 1)\n";

    // Test Problem 12: Find Pivot Index
    cout << "\nTest Problem 12: Find Pivot Index (LC 724) \n";
    vector<int> nums12 = {1, 7, 3, 6, 5, 6};
    cout << "Output: " << PivotIndex(nums12) << " (Expected: 3)\n";

    vector<int> nums12_2 = {1, 2, 3};
    cout << "Output: " << PivotIndex(nums12_2) << " (Expected: -1)\n";

    // Test Problem 13: Find Disappeared Numbers
    cout << "\nTest Problem 13: Find Disappeared Numbers (LC 448) \n";
    vector<int> nums13 = {4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> res13 = FindDisappearedNumbers(nums13);
    cout << "Output: ";
    for (int num : res13) cout << num << " ";
    cout << "(Expected: 5 6)\n";

    vector<int> nums13_2 = {1, 1};
    vector<int> res13_2 = FindDisappearedNumbers(nums13_2);
    cout << "Output: ";
    for (int num : res13_2) cout << num << " ";
    cout << "(Expected: 2)\n";

    // Test Problem 14: Maximum Subarray
    cout << "\nTest Problem 14: Maximum Subarray (LC 53) \n";
    vector<int> nums14 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Output: " << MaxSubArray(nums14) << " (Expected: 6)\n";

    vector<int> nums14_2 = {5, 4, -1, 7, 8};
    cout << "Output: " << MaxSubArray(nums14_2) << " (Expected: 23)\n";

    // Test Problem 15: Sort Array by Parity
    cout << "Test Problem 15: Sort Array by Parity (LC 905) \n";
    vector<int> nums15 = {3, 1, 2, 4};
    vector<int> res15 = SortArrayByParity(nums15);
    cout << "Output: ";
    for (int num : res15) cout << num << " ";
    cout << "(Expected: 2 4 3 1)\n";

    // Test Problem 16: Largest Number
    cout << "\nTest Problem 16: Largest Number (LC 179) \n";
    vector<int> nums16 = {10, 2};
    cout << "Output: " << LargestNumber(nums16) << " (Expected: 210)\n";

    vector<int> nums16_2 = {3, 30, 34, 5, 9};
    cout << "Output: " << LargestNumber(nums16_2) << " (Expected: 9534330)\n";

    // Test Problem 17: Subarray Sum Equals K
    cout << "\nTest Problem 17: Subarray Sum Equals K (LC 560) \n";
    vector<int> nums17 = {1, 1, 1};
    cout << "Output: " << SubarraySum(nums17, 2) << " (Expected: 2)\n";

    vector<int> nums17_2 = {1, 2, 3};
    cout << "Output: " << SubarraySum(nums17_2, 3) << " (Expected: 2)\n";

    // Test Problem 18: Maximum Product of Three Numbers
    cout << "\nTest Problem 18: Maximum Product of Three Numbers (LC 628) \n";
    vector<int> nums18 = {1, 2, 3};
    cout << "Output: " << MaximumProduct(nums18) << " (Expected: 6)\n";

    vector<int> nums18_2 = {-10, -10, 5, 2};
    cout << "Output: " << MaximumProduct(nums18_2) << " (Expected: 500)\n";

    // Test Problem 19: Find Maximum Average Subarray I
    cout << "\nTest Problem 19: Find Maximum Average Subarray I (LC 643) \n";
    vector<int> nums19 = {1, 12, -5, -6, 50, 3};
    cout << "Output: " << FindMaxAverage(nums19, 4) << " (Expected: 12.75)\n";

    // Test Problem 20: Can Place Flowers
    cout << "\nTest Problem 20: Can Place Flowers (LC 605) \n";
    vector<int> nums20 = {1, 0, 0, 0, 1};
    cout << "Output: " << (CanPlaceFlowers(nums20, 1) ? "true" : "false") << " (Expected: true)\n";

    return 0;
}
