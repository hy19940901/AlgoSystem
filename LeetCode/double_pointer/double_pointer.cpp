#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem 1: Two Sum II - Input Array Is Sorted (LC 167)
 * Description:
 * Given a 1-indexed sorted array and a target sum, return the indices of two numbers such that they add up to target.
 *
 * Example:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 */
vector<int> TwoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) return {left + 1, right + 1};
        else if (sum < target) left++;
        else right--;
    }
    return {};
}

/**
 * Problem 2: Remove Duplicates from Sorted Array (LC 26)
 * Description:
 * Given a sorted array, remove the duplicates in-place such that each element appears only once.
 *
 * Example:
 * Input: nums = [1,1,2]
 * Output: 2 (nums = [1,2,_])
 */
int RemoveDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;
    for (size_t fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    }
    return slow + 1;
}

/**
 * Problem 3: Move Zeroes (LC 283)
 * Description:
 * Given an integer array, move all 0s to the end while maintaining the relative order of non-zero elements.
 *
 * Example:
 * Input: nums = [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 */
void MoveZeroes(vector<int>& nums) {
    int slow = 0;
    for (size_t fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) swap(nums[slow++], nums[fast]);
    }
}

/**
 * Problem 4: Reverse String (LC 344)
 * Description:
 * Given a character array, reverse it in-place.
 *
 * Example:
 * Input: s = ['h','e','l','l','o']
 * Output: ['o','l','l','e','h']
 */
void ReverseString(vector<char>& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) swap(s[left++], s[right--]);
}

/**
 * Problem 5: Valid Palindrome (LC 125)
 * Description:
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * Example:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 */
bool IsPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }
    return true;
}

/**
 * Problem 6: Container With Most Water (LC 11)
 * Description:
 * Given an array height, find two lines that can form a container to hold the most water.
 *
 * Example:
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 */
int MaxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1, max_water = 0;
    while (left < right) {
        max_water = max(max_water, min(height[left], height[right]) * (right - left));
        if (height[left] < height[right]) left++;
        else right--;
    }
    return max_water;
}

/**
 * Problem 7: 3Sum (LC 15)
 * Description:
 * Given an array nums, return all unique triplets that sum up to 0.
 *
 * Example:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 */
vector<vector<int>> ThreeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (size_t i = 0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) left++;
            else right--;
        }
    }
    return res;
}

/**
 * Problem 8: Sort Colors (LC 75)
 * Description:
 * Given an array with 0s, 1s, and 2s, sort them in-place (Dutch National Flag problem).
 *
 * Example:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 */
void SortColors(vector<int>& nums) {
    int left = 0, right = nums.size() - 1, current = 0;
    while (current <= right) {
        if (nums[current] == 0) swap(nums[left++], nums[current++]);
        else if (nums[current] == 2) swap(nums[right--], nums[current]);
        else current++;
    }
}

/**
 * Problem 9: Remove Element (LC 27)
 * Description:
 * Given an array and a value val, remove all instances of val in-place.
 *
 * Example:
 * Input: nums = [3,2,2,3], val = 3
 * Output: 2 (nums = [2,2,_])
 */
int RemoveElement(vector<int>& nums, int val) {
    int slow = 0;
    for (size_t fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != val) nums[slow++] = nums[fast];
    }
    return slow;
}

/**
 * Problem 10: Merge Sorted Array (LC 88)
 * Description:
 * Given two sorted arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
 *
 * Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 */
void Merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j >= 0) nums1[k--] = nums2[j--];
}

int main() {
    // Test Problem 1: Two Sum II
    vector<int> nums1 = {2,7,11,15};
    vector<int> result1 = TwoSum(nums1, 9);
    cout << "Test 1 - Two Sum II: [" << result1[0] << "," << result1[1] << "] (Expected: [1,2])" << endl;

    // Test Problem 2: Remove Duplicates
    vector<int> nums2 = {1,1,2};
    int newLength2 = RemoveDuplicates(nums2);
    cout << "Test 2 - Remove Duplicates: " << newLength2 << " (Expected: 2)" << endl;

    // Test Problem 3: Move Zeroes
    vector<int> nums3 = {0,1,0,3,12};
    MoveZeroes(nums3);
    cout << "Test 3 - Move Zeroes: ";
    for (int num : nums3) cout << num << " ";
    cout << "(Expected: 1 3 12 0 0)" << endl;

    // Test Problem 4: Reverse String
    vector<char> chars4 = {'h','e','l','l','o'};
    ReverseString(chars4);
    cout << "Test 4 - Reverse String: ";
    for (char c : chars4) cout << c;
    cout << " (Expected: olleh)" << endl;

    // Test Problem 5: Valid Palindrome
    string s5 = "A man, a plan, a canal: Panama";
    cout << "Test 5 - Valid Palindrome: " << IsPalindrome(s5) << " (Expected: 1)" << endl;

    // Test Problem 6: Container With Most Water
    vector<int> nums6 = {1,8,6,2,5,4,8,3,7};
    cout << "Test 6 - Container With Most Water: " << MaxArea(nums6) << " (Expected: 49)" << endl;

    // Test Problem 7: 3Sum
    vector<int> nums7 = {-1,0,1,2,-1,-4};
    vector<vector<int>> result7 = ThreeSum(nums7);
    cout << "Test 7 - 3Sum: ";
    for (auto& triplet : result7) {
        cout << "[";
        for (int num : triplet) cout << num << " ";
        cout << "] ";
    }
    cout << "(Expected: [-1,-1,2] [-1,0,1])" << endl;

    // Test Problem 8: Sort Colors
    vector<int> nums8 = {2,0,2,1,1,0};
    SortColors(nums8);
    cout << "Test 8 - Sort Colors: ";
    for (int num : nums8) cout << num << " ";
    cout << "(Expected: 0 0 1 1 2 2)" << endl;

    // Test Problem 9: Remove Element
    vector<int> nums9 = {3,2,2,3};
    int newLength9 = RemoveElement(nums9, 3);
    cout << "Test 9 - Remove Element: " << newLength9 << " (Expected: 2)" << endl;

    // Test Problem 10: Merge Sorted Array
    vector<int> nums10_1 = {1,2,3,0,0,0};
    vector<int> nums10_2 = {2,5,6};
    Merge(nums10_1, 3, nums10_2, 3);
    cout << "Test 10 - Merge Sorted Array: ";
    for (int num : nums10_1) cout << num << " ";
    cout << "(Expected: 1 2 2 3 5 6)" << endl;

    return 0;
}
