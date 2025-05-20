#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <map>
#include <climits>
#include <cstdint>
#include <sstream>

using namespace std;

/**
 * Problem 1: Longest Substring Without Repeating Characters (LC 3)
 * -----------------------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, find the length of the longest substring without repeating characters.
 *
 * 🔍 Example:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with length 3.
 *
 * 🎯 Key Insight:
 * Use a sliding window to maintain a window with no repeated characters.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Maintain a sliding window from index `start` to `i` and track the last seen index of each character.
 *
 * ✅ Base Case Initialization:
 * start = 0 (left boundary of window), maxLen = 0
 *
 * ✅ Transition:
 * For each character at index i:
 *   - If s[i] was seen before and within current window: shrink start
 *     start = max(start, lastSeen[s[i]] + 1)
 *   - Always update lastSeen[s[i]] = i
 *   - Update maxLen = max(maxLen, i - start + 1)
 *
 * ✅ Iteration Order:
 * Iterate i from 0 to n - 1
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - All same characters → length is 1
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(128) = O(1) (ASCII map)
 */
int LengthOfLongestSubstring(string s) {
    unordered_map<char, int> last_seen;
    int max_len = 0, start = 0;

    for (int i = 0; i < s.length(); ++i) {
        if (last_seen.count(s[i]) && last_seen[s[i]] >= start) {
            start = last_seen[s[i]] + 1;  // Move start past duplicate
        }
        last_seen[s[i]] = i;
        max_len = max(max_len, i - start + 1);
    }

    return max_len;
}

/**
 * Problem 2: String to Integer (atoi) (LC 8)
 * ------------------------------------------
 * 🧠 Description:
 * Convert a string to a 32-bit signed integer (like the C/C++ atoi function).
 *
 * 🔍 Example:
 * Input: s = "   -42"
 * Output: -42
 *
 * 🎯 Key Insight:
 * Skip whitespaces, handle signs, parse digits until non-digit appears.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Track position `i`, `sign`, and accumulated `result`.
 *
 * ✅ Base Case Initialization:
 * i = 0, sign = +1, result = 0
 *
 * ✅ Transition:
 * - Skip leading whitespaces
 * - Handle '+' or '-' sign
 * - For each digit:
 *     result = result * 10 + digit
 *     Check overflow before adding!
 *
 * ✅ Iteration Order:
 * Linear pass over the string
 *
 * 🚨 Edge Cases:
 * - Overflow ⇒ return INT_MAX / INT_MIN
 * - No valid conversion ⇒ return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int MyAtoi(string s) {
    int i = 0, n = s.size(), sign = 1;
    long result = 0;

    // Skip leading whitespaces
    while (i < n && s[i] == ' ') i++;

    // Handle optional sign
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i++] == '-') ? -1 : 1;
    }

    // Parse digits and avoid overflow
    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i++] - '0');
        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
    }

    return static_cast<int>(result * sign);
}

/**
 * Problem 3: Roman to Integer (LC 13)
 * -----------------------------------
 * 🧠 Description:
 * Convert a Roman numeral string to an integer.
 *
 * 🔍 Example:
 * Input: "MCMXCIV"
 * Output: 1994
 *
 * 🎯 Key Insight:
 * Subtract if the current value is less than the next.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use a hashmap for Roman numeral values.
 *
 * ✅ Base Case Initialization:
 * result = 0
 *
 * ✅ Transition:
 * - Iterate s[i], if value[s[i]] < value[s[i+1]] ⇒ subtract
 *   else ⇒ add
 *
 * ✅ Iteration Order:
 * Left to right
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int RomanToInt(string s) {
    unordered_map<char, int> value = {
        {'I',1}, {'V',5}, {'X',10}, {'L',50},
        {'C',100}, {'D',500}, {'M',1000}
    };

    int result = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 < s.size() && value[s[i]] < value[s[i+1]])
            result -= value[s[i]];
        else
            result += value[s[i]];
    }
    return result;
}

/**
 * Problem 4: 3Sum (LC 15)
 * ------------------------
 * 🧠 Description:
 * Given an array `nums`, return all unique triplets [a,b,c] such that a+b+c = 0.
 *
 * 🔍 Example:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2], [-1,0,1]]
 *
 * 🎯 Key Insight:
 * Sort + two pointers avoids duplicate and gives O(n^2) solution.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Sort input, fix one number `a`, then use two pointers to find pairs summing to -a.
 *
 * ✅ Base Case Initialization:
 * sort(nums), result = []
 *
 * ✅ Transition:
 * For each i:
 *   - Skip duplicates
 *   - Two pointers j, k = i+1, n-1
 *   - if sum == 0: add, move both pointers (skip duplicates)
 *
 * ✅ Iteration Order:
 * i = 0 to n-3, inner j/k moves inward
 *
 * 🚨 Edge Cases:
 * - Less than 3 elements → return empty
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(1) extra (excluding output)
 */
vector<vector<int>> ThreeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates
        int j = i + 1, k = n - 1;

        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                res.push_back({nums[i], nums[j], nums[k]});
                while (j < k && nums[j] == nums[j+1]) j++;
                while (j < k && nums[k] == nums[k-1]) k--;
                j++; k--;
            } else if (sum < 0) {
                j++;
            } else {
                k--;
            }
        }
    }

    return res;
}

/**
 * Problem 5: Remove Duplicates from Sorted Array (LC 26)
 * -------------------------------------------------------
 * 🧠 Description:
 * Remove duplicates in-place from sorted array and return new length.
 *
 * 🔍 Example:
 * Input: nums = [1,1,2]
 * Output: 2 (nums = [1,2,_])
 *
 * 🎯 Key Insight:
 * Use two pointers: one for current position, one for overwrite position.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * slow = index of next unique position, fast = scanner
 *
 * ✅ Base Case Initialization:
 * slow = 1
 *
 * ✅ Transition:
 * If nums[fast] != nums[fast - 1], assign nums[slow++] = nums[fast]
 *
 * ✅ Iteration Order:
 * fast = 1 to n - 1
 *
 * 🚨 Edge Cases:
 * - Empty array → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int RemoveDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 1;

    for (int fast = 1; fast < nums.size(); ++fast) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow++] = nums[fast];  // Overwrite duplicate
        }
    }

    return slow;
}

/**
 * Problem 6: Next Permutation (LC 31)
 * -----------------------------------
 * 🧠 Description:
 * Rearranges numbers into the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, rearrange as the lowest possible order (ascending).
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [1,3,2]
 *
 * 🎯 Key Insight:
 * Find the first decreasing element from the right, then swap with the smallest larger element to its right, then reverse.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ Step 1: Scan from right to find first decreasing element nums[i - 1]
 * ✅ Step 2: Find the smallest number > nums[i - 1] on the right side (nums[j])
 * ✅ Step 3: Swap nums[i - 1] and nums[j]
 * ✅ Step 4: Reverse the subarray from i to end
 *
 * 🚨 Edge Cases:
 * - Entire array is in descending order → reverse to ascending
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
void NextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 1;

    // Step 1: Find rightmost i where nums[i - 1] < nums[i]
    while (i > 0 && nums[i - 1] >= nums[i]) i--;

    if (i > 0) {
        int j = n - 1;
        // Step 2: Find number just larger than nums[i - 1]
        while (nums[j] <= nums[i - 1]) j--;
        swap(nums[i - 1], nums[j]);
    }

    // Step 3: Reverse the decreasing suffix
    reverse(nums.begin() + i, nums.end());
}

/**
 * Problem 7: Multiply Strings (LC 43)
 * -----------------------------------
 * 🧠 Description:
 * Multiply two non-negative numbers represented as strings. Return the product as a string.
 * Do not use built-in big integer libraries or convert to integer directly.
 *
 * 🔍 Example:
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 * 🎯 Key Insight:
 * Simulate grade-school multiplication with digit-by-digit computation.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Result can be at most m+n digits. Use an array `res` to store intermediate values.
 *
 * ✅ Transition:
 * - Multiply digit-by-digit: num1[i] * num2[j] and add to res[i+j+1]
 * - Handle carry after multiplication
 *
 * ✅ Iteration Order:
 * i = num1.size()-1 downto 0
 * j = num2.size()-1 downto 0
 *
 * 🚨 Edge Cases:
 * - Any num is "0" → return "0"
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(m + n)
 */
string Multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";

    int m = num1.size(), n = num2.size();
    vector<int> res(m + n, 0);

    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int pos1 = i + j, pos2 = i + j + 1;

            int sum = mul + res[pos2];
            res[pos2] = sum % 10;
            res[pos1] += sum / 10;
        }
    }

    string result;
    for (int num : res)
        if (!(result.empty() && num == 0)) result += to_string(num);
    return result;
}

/**
 * Problem 8: Group Anagrams (LC 49)
 * ----------------------------------
 * 🧠 Description:
 * Group anagrams from a list of strings.
 *
 * 🔍 Example:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * 🎯 Key Insight:
 * Anagrams have the same sorted character sequence.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use unordered_map<string, vector<string>>: key = sorted string, value = list of anagrams
 *
 * ✅ Transition:
 * For each word, sort characters and add to map
 *
 * ✅ Iteration Order:
 * Linear scan of words
 *
 * 🚨 Edge Cases:
 * - Empty string should still be grouped
 *
 * ⏱️ Time Complexity: O(n * k log k), where n = #words, k = max word length
 * 🧠 Space Complexity: O(n * k)
 */
vector<vector<string>> GroupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (string s : strs) {
        string sorted_s = s;
        sort(sorted_s.begin(), sorted_s.end());
        groups[sorted_s].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& pair : groups) {
        result.push_back(move(pair.second));
    }

    return result;
}

/**
 * Problem 9: Add Binary (LC 67)
 * ------------------------------
 * 🧠 Description:
 * Add two binary strings and return their sum as a binary string.
 *
 * 🔍 Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * 🎯 Key Insight:
 * Simulate binary addition with carry, process from right to left.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Pointers i and j for `a` and `b`, carry for overflow
 *
 * ✅ Transition:
 * - Sum = (a[i] - '0') + (b[j] - '0') + carry
 * - Carry = sum / 2, current = sum % 2
 *
 * ✅ Iteration Order:
 * While i or j or carry
 *
 * 🚨 Edge Cases:
 * - Unequal lengths
 * - Final carry
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
string AddBinary(string a, string b) {
    string result;
    int i = a.size() - 1, j = b.size() - 1, carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        result += (sum % 2) + '0';
        carry = sum / 2;
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Problem 10: Minimum Window Substring (LC 76)
 * ---------------------------------------------
 * 🧠 Description:
 * Given two strings `s` and `t`, return the minimum window in `s` which contains all characters in `t`.
 *
 * 🔍 Example:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 *
 * 🎯 Key Insight:
 * Use sliding window with character counting to track window validity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * freqT = character counts of t, window = character counts in current window
 *
 * ✅ Transition:
 * Expand right until valid ⇒ shrink left to minimize
 *
 * ✅ Iteration Order:
 * right = 0 to s.length()
 *
 * 🚨 Edge Cases:
 * - No valid window ⇒ return ""
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (fixed char set size)
 */
string MinWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> freq_t;
    for (char c : t) freq_t[c]++;

    int left = 0, right = 0, required = freq_t.size();
    unordered_map<char, int> window;
    int formed = 0, start = 0, min_len = INT_MAX;

    while (right < s.size()) {
        char c = s[right++];
        window[c]++;
        if (freq_t.count(c) && window[c] == freq_t[c]) formed++;

        while (formed == required) {
            if (right - left < min_len) {
                start = left;
                min_len = right - left;
            }
            char d = s[left++];
            if (freq_t.count(d) && window[d]-- == freq_t[d]) formed--;
        }
    }

    return min_len == INT_MAX ? "" : s.substr(start, min_len);
}

/**
 * Problem 11: Merge Sorted Array (LC 88)
 * ---------------------------------------
 * 🧠 Description:
 * Merge two sorted arrays nums1 and nums2 into one sorted array.
 * nums1 has extra space at the end to accommodate nums2.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3
 *        nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 *
 * 🎯 Key Insight:
 * Merge from the back to avoid overwriting nums1.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Three pointers: i = m-1, j = n-1, k = m+n-1 (write index)
 *
 * ✅ Transition:
 * While i >= 0 and j >= 0:
 *   - Compare nums1[i] and nums2[j], copy larger to nums1[k]
 *   - Decrement respective pointer
 * Copy remaining nums2 if any
 *
 * 🚨 Edge Cases:
 * - If nums2 is empty → nums1 unchanged
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(1)
 */
void Merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;

    // Fill from the end
    while (i >= 0 && j >= 0) {
        nums1[k--] = (nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];
    }

    // Copy leftover from nums2
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

/**
 * Problem 12: Valid Palindrome (LC 125)
 * --------------------------------------
 * 🧠 Description:
 * Given a string, determine if it is a palindrome considering only alphanumeric characters and ignoring cases.
 *
 * 🔍 Example:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 *
 * 🎯 Key Insight:
 * Use two pointers and skip non-alphanumerics.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Two pointers: left and right
 *
 * ✅ Transition:
 * - Skip non-alphanumerics
 * - Compare lowercase letters
 *
 * ✅ Iteration Order:
 * Move inward from both ends
 *
 * 🚨 Edge Cases:
 * - Empty string → true
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
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
 * Problem 13: Read N Characters Given Read4 (LC 157)
 * ---------------------------------------------------
 * 🧠 Description:
 * Implement the function `read(char *buf, int n)` that reads `n` characters using `read4`.
 *
 * 🔍 read4(char *buf4): reads 4 chars at a time.
 *
 * 🎯 Key Insight:
 * Read in chunks of 4 and copy to result buffer until we reach `n` or EOF.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use temporary buffer buf4[4], read into it, then copy to buf.
 *
 * ✅ Iteration Order:
 * While totalRead < n and read4 returns > 0
 *
 * 🚨 Edge Cases:
 * - read4 returns < 4 → EOF reached
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */

string file_content = "LeetCodeRead4Simulation";
int file_pointer = 0;

int Read4(char *buf) {
    int count = 0;
    while (count < 4 && file_pointer < file_content.size()) {
        buf[count++] = file_content[file_pointer++];
    }
    return count;
}

int Read(char *buf, int n) {
    int total_read = 0;
    char buf4[4];

    while (total_read < n) {
        int count = Read4(buf4);
        for (int i = 0; i < count && total_read < n; ++i) {
            buf[total_read++] = buf4[i];
        }
        if (count < 4) break; // EOF
    }

    return total_read;
}

/**
 * Problem 14: Read N Characters Given Read4 II - Call multiple times (LC 158)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * `read()` can be called multiple times, so leftover chars from read4 must be cached.
 *
 * 🎯 Key Insight:
 * Use internal buffer + index tracking for caching between calls.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - buf4[4]: internal cache
 * - bufPtr, bufCnt: track remaining chars from previous read
 *
 * ✅ Transition:
 * - If buffer not empty, use from cache
 * - Else read from read4
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (but state must persist across calls)
 */
class Reader {
private:
    char buf4_[4];       // internal buffer
    int buf_ptr_ = 0;    // pointer to current reading position in buf4_
    int buf_cnt_ = 0;    // number of valid chars in buf4_

public:
    int Read(char* buf, int n) {
        int total_read = 0;

        while (total_read < n) {
            // When internal buffer is empty, refill it using Read4
            if (buf_ptr_ == buf_cnt_) {
                buf_cnt_ = Read4(buf4_);
                buf_ptr_ = 0;
                if (buf_cnt_ == 0) break;  // EOF
            }

            // Copy from buf4_ to output buffer
            while (total_read < n && buf_ptr_ < buf_cnt_) {
                buf[total_read++] = buf4_[buf_ptr_++];
            }
        }

        return total_read;
    }
};

/**
 * Problem 15: One Edit Distance (LC 161)
 * ---------------------------------------
 * 🧠 Description:
 * Given two strings s and t, return true if they are exactly one edit distance apart (insert, delete, or replace).
 *
 * 🔍 Example:
 * s = "ab", t = "acb" ⇒ true (insert 'c')
 *
 * 🎯 Key Insight:
 * Check all 3 operations via character comparison.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Check length difference:
 *   - Replace if same length
 *   - Insert/delete if len diff = 1
 *
 * ✅ Transition:
 * - Traverse, compare chars:
 *     - If mismatch: simulate edit and check remaining suffixes
 *
 * ✅ Edge Cases:
 * - Equal strings → false
 * - Empty string + 1 char → true
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
bool IsOneEditDistance(string s, string t) {
    int m = s.length(), n = t.length();

    if (abs(m - n) > 1) return false;
    if (m > n) return IsOneEditDistance(t, s);  // Ensure m <= n

    for (int i = 0; i < m; ++i) {
        if (s[i] != t[i]) {
            if (m == n) return s.substr(i + 1) == t.substr(i + 1);       // Replace
            else        return s.substr(i) == t.substr(i + 1);           // Insert in s or delete from t
        }
    }

    return m + 1 == n;  // Edge case: last char is extra
}

/**
 * Problem 16: Product of Array Except Self (LC 238)
 * --------------------------------------------------
 * 🧠 Description:
 * Given an integer array nums, return an array output such that output[i] is equal to the product 
 * of all the elements of nums except nums[i], without using division and in O(n) time.
 *
 * 🔍 Example:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * 🎯 Key Insight:
 * The product of all elements except self at index i can be obtained by multiplying:
 *   - the product of all elements to the left of i (prefix)
 *   - the product of all elements to the right of i (suffix)
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * output[i] stores the prefix product of all elements before index i
 *
 * ✅ Base Case Initialization:
 * output[0] = 1, since there are no elements to the left of index 0
 *
 * ✅ Transition:
 * First pass (left to right):
 *   output[i] = output[i - 1] * nums[i - 1]
 * Second pass (right to left):
 *   output[i] *= suffix_product; suffix_product *= nums[i]
 *
 * ✅ Iteration Order:
 * - Forward pass for prefix
 * - Backward pass for suffix
 *
 * 🚨 Edge Cases:
 * - Input contains zero(s)
 * - Length 1 array
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) (excluding output array, which is required)
 */
vector<int> ProductExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> output(n, 1);

    // Forward pass: compute prefix products
    for (int i = 1; i < n; ++i) {
        output[i] = output[i - 1] * nums[i - 1];
    }

    // Backward pass: compute suffix products and multiply
    int suffix_product = 1;
    for (int i = n - 1; i >= 0; --i) {
        output[i] *= suffix_product;
        suffix_product *= nums[i];
    }

    return output;
}

/**
 * Problem 17: Integer to English Words (LC 273)
 * ----------------------------------------------
 * 🧠 Description:
 * Convert a non-negative integer to its English words representation.
 *
 * 🔍 Example:
 * Input: 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 *
 * 🎯 Key Insight:
 * Group digits in 3's from the end. Process each chunk individually with a helper function.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Process groups: Billion, Million, Thousand, and remainder (0-999).
 *
 * ✅ Base Case Initialization:
 * Special case: 0 → "Zero"
 *
 * ✅ Transition:
 * Use helper to convert each 3-digit number.
 * Append scale name (Thousand, Million...) accordingly.
 *
 * ✅ Iteration Order:
 * Right to left, lowest chunks first, divide by 1000 per step.
 *
 * 🚨 Edge Cases:
 * - Input is 0
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
class Solution {
private:
    vector<string> below_20_ = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                                "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens_ = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> thousands_ = {"", "Thousand", "Million", "Billion"};

    string Helper(int num) {
        if (num == 0) return "";
        else if (num < 20) return below_20_[num] + " ";
        else if (num < 100) return tens_[num / 10] + " " + Helper(num % 10);
        else return below_20_[num / 100] + " Hundred " + Helper(num % 100);
    }

public:
    string NumberToWords(int num) {
        if (num == 0) return "Zero";

        string result;
        int chunk = 0;

        while (num > 0) {
            if (num % 1000 != 0) {
                result = Helper(num % 1000) + thousands_[chunk] + " " + result;
            }
            num /= 1000;
            chunk++;
        }

        while (!result.empty() && result.back() == ' ') result.pop_back(); // Trim space
        return result;
    }
};

/**
 * Problem 18: Move Zeroes (LC 283)
 * ---------------------------------
 * 🧠 Description:
 * Given an integer array nums, move all 0's to the end of it while maintaining the relative order
 * of the non-zero elements. Do it in-place.
 *
 * 🔍 Example:
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 *
 * 🎯 Key Insight:
 * Use two pointers: one to scan, one to place non-zero elements.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * `left` = index where the next non-zero should go
 *
 * ✅ Base Case Initialization:
 * left = 0
 *
 * ✅ Transition:
 * If nums[i] != 0 → move it to nums[left] and increment left
 *
 * ✅ Final Step:
 * Fill rest of array from `left` with 0's
 *
 * 🚨 Edge Cases:
 * - All zeroes
 * - No zeroes
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
void MoveZeroes(vector<int>& nums) {
    int left = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            nums[left++] = nums[i];
        }
    }

    // Fill remaining space with 0s
    while (left < nums.size()) {
        nums[left++] = 0;
    }
}

/**
 * Problem 19: Longest Substring with At Most K Distinct Characters (LC 340)
 * --------------------------------------------------------------------------
 * 🧠 Description:
 * Given a string s and an integer k, return the length of the longest substring that contains at most k distinct characters.
 *
 * 🔍 Example:
 * Input: s = "eceba", k = 2
 * Output: 3 (substring = "ece")
 *
 * 🎯 Key Insight:
 * Use sliding window and a hashmap to track current window character counts.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * left/right = window bounds; hashmap to count characters
 *
 * ✅ Base Case Initialization:
 * left = 0, max_len = 0
 *
 * ✅ Transition:
 * - Expand right
 * - While hashmap.size() > k: shrink from left
 * - Update max_len
 *
 * ✅ Iteration Order:
 * Right expands to s.size()
 *
 * 🚨 Edge Cases:
 * - k == 0 → always 0
 * - k >= s.length() → return s.length()
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(k)
 */
int LengthOfLongestSubstringKDistinct(string s, int k) {
    if (k == 0) return 0;

    unordered_map<char, int> freq;
    int left = 0, max_len = 0;

    for (int right = 0; right < s.size(); ++right) {
        freq[s[right]]++;

        // Shrink window until valid
        while (freq.size() > k) {
            if (--freq[s[left]] == 0) freq.erase(s[left]);
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}

/**
 * Problem 20: Validate IP Address (LC 468)
 * -----------------------------------------
 * 🧠 Description:
 * Given a string IP, return "IPv4", "IPv6", or "Neither" depending on whether the input is a valid IPv4 or IPv6 address.
 *
 * 🔍 Example:
 * Input: "172.16.254.1" → Output: "IPv4"
 * Input: "2001:0db8:85a3:0000:0000:8a2e:0370:7334" → Output: "IPv6"
 * Input: "256.256.256.256" → Output: "Neither"
 *
 * 🎯 Key Insight:
 * Use delimiter to distinguish IPv4 (dot) vs IPv6 (colon). Validate each segment accordingly.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Count and validate segments (4 parts for IPv4, 8 parts for IPv6)
 *
 * ✅ Transition:
 * - IPv4: parts are 0–255, no leading 0s (unless 0)
 * - IPv6: parts are 1–4 hex digits (0-9, a-f, A-F)
 *
 * ✅ Iteration Order:
 * Split by '.' or ':', then validate each part
 *
 * 🚨 Edge Cases:
 * - Leading/trailing separators
 * - Empty parts
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
bool IsIPv4(string ip) {
    vector<string> parts;
    stringstream ss(ip);
    string token;

    while (getline(ss, token, '.')) parts.push_back(token);
    if (parts.size() != 4) return false;

    for (string& part : parts) {
        if (part.empty() || (part.size() > 1 && part[0] == '0') || part.size() > 3) return false;
        for (char c : part) if (!isdigit(c)) return false;
        if (stoi(part) > 255) return false;
    }
    return true;
}

bool IsIPv6(string ip) {
    vector<string> parts;
    stringstream ss(ip);
    string token;

    while (getline(ss, token, ':')) parts.push_back(token);
    if (parts.size() != 8) return false;

    for (string& part : parts) {
        if (part.empty() || part.size() > 4) return false;
        for (char c : part) {
            if (!isxdigit(c)) return false;
        }
    }
    return true;
}

string ValidIPAddress(string IP) {
    if (count(IP.begin(), IP.end(), '.') == 3 && IsIPv4(IP)) return "IPv4";
    if (count(IP.begin(), IP.end(), ':') == 7 && IsIPv6(IP)) return "IPv6";
    return "Neither";
}

/**
 * Problem 21: Subarray Sum Equals K (LC 560)
 * -------------------------------------------
 * 🧠 Description:
 * Given an integer array nums and an integer k, return the total number of continuous subarrays
 * whose sum equals to k.
 *
 * 🔍 Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use a running prefix sum and a hashmap to store the count of each prefix sum.
 * If sum[i] - sum[j] == k, then subarray nums[j..i-1] sums to k.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * sum_so_far = running sum up to current index
 * prefix_count[sum] = number of times sum has occurred
 *
 * ✅ Base Case Initialization:
 * prefix_count[0] = 1 (to handle exact match from start)
 *
 * ✅ Transition:
 * For each number:
 *   - Update sum_so_far += num
 *   - If sum_so_far - k exists in map, increment result by its frequency
 *   - Increment frequency of sum_so_far in map
 *
 * ✅ Iteration Order:
 * Left to right over nums
 *
 * 🚨 Edge Cases:
 * - Empty array → 0
 * - Negative numbers are allowed
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
int SubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefix_count;
    prefix_count[0] = 1;

    int sum_so_far = 0, count = 0;

    for (int num : nums) {
        sum_so_far += num;
        if (prefix_count.count(sum_so_far - k)) {
            count += prefix_count[sum_so_far - k];
        }
        prefix_count[sum_so_far]++;
    }

    return count;
}

/**
 * Problem 22: Valid Palindrome II (LC 680)
 * -----------------------------------------
 * 🧠 Description:
 * Given a string s, return true if the string can be a palindrome after deleting at most one character.
 *
 * 🔍 Example:
 * Input: "abca"
 * Output: true (delete 'b' or 'c')
 *
 * 🎯 Key Insight:
 * Use two pointers. On mismatch, try skipping one character and check if the rest is a palindrome.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * left, right = current pointers
 *
 * ✅ Base Case Initialization:
 * Begin with left = 0, right = s.length() - 1
 *
 * ✅ Transition:
 * If s[left] == s[right], continue.
 * If mismatch, try skipping left or right and test both substrings.
 *
 * ✅ Helper:
 * IsPalindromeInRange(s, i, j)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
bool IsPalindromeInRange(const string& s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

bool ValidPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return IsPalindromeInRange(s, left + 1, right) ||
                   IsPalindromeInRange(s, left, right - 1);
        }
        left++;
        right--;
    }

    return true;
}

/**
 * Problem 23: Add Two Numbers (LC 2)
 * -----------------------------------
 * 🧠 Description:
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each node contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 *
 * 🔍 Example:
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 *
 * 🎯 Key Insight:
 * Simulate digit-by-digit addition, carry over if sum >= 10.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * l1, l2 = input lists; carry = current carry
 *
 * ✅ Base Case Initialization:
 * dummy head node, current = dummy
 *
 * ✅ Transition:
 * While l1 or l2 or carry:
 *   - Add corresponding digits + carry
 *   - Set new digit node = sum % 10
 *   - Update carry = sum / 10
 *
 * ✅ Iteration Order:
 * Traverse both lists
 *
 * ⏱️ Time Complexity: O(max(m, n))
 * 🧠 Space Complexity: O(max(m, n)) for result list
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0), *curr = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int val1 = l1 ? l1->val : 0;
        int val2 = l2 ? l2->val : 0;
        int sum = val1 + val2 + carry;

        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return dummy.next;
}

/**
 * Problem 24: Merge Two Sorted Lists (LC 21)
 * -------------------------------------------
 * 🧠 Description:
 * Merge two sorted linked lists and return it as a new sorted list.
 * The new list should be made by splicing together the nodes of the first two lists.
 *
 * 🔍 Example:
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 *
 * 🎯 Key Insight:
 * Use two pointers and build merged list incrementally.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * l1, l2 = input lists; dummy head to build result
 *
 * ✅ Base Case Initialization:
 * dummy node, current = dummy
 *
 * ✅ Transition:
 * Compare l1 and l2 values:
 *   - Append smaller one and move pointer
 *
 * ✅ Final Step:
 * Append remaining nodes
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(1)
 */
ListNode* MergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0), *curr = &dummy;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }

    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

/**
 * Problem 25: Copy List with Random Pointer (LC 138)
 * ---------------------------------------------------
 * 🧠 Description:
 * A linked list is given where each node contains an additional random pointer which could point to any node or null.
 * Return a deep copy of the list.
 *
 * 🔍 Example:
 * Input: head = [7,null],[13,0],[11,4],[10,2],[1,0]
 * Output: deep copy of list with same structure
 *
 * 🎯 Key Insight:
 * Use a hashmap or weave original/clone nodes together to maintain random linkage.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use a map from original to cloned nodes
 *
 * ✅ Alternative:
 * In-place interleaving copy and then detach
 *
 * ✅ Transition:
 * Step 1: Clone each node and interleave with original
 * Step 2: Assign random pointers
 * Step 3: Separate cloned list
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1) if using interleaved method
 */
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

Node* CopyRandomList(Node* head) {
    if (!head) return nullptr;

    // Step 1: Interleave clone nodes
    Node* curr = head;
    while (curr) {
        Node* copy = new Node(curr->val);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    // Step 2: Assign random pointers
    curr = head;
    while (curr) {
        if (curr->random)
            curr->next->random = curr->random->next;
        curr = curr->next->next;
    }

    // Step 3: Separate the lists
    Node* dummy = new Node(0);
    Node* copy_curr = dummy;
    curr = head;
    while (curr) {
        Node* copy = curr->next;
        curr->next = copy->next;

        copy_curr->next = copy;
        copy_curr = copy;
        curr = curr->next;
    }

    return dummy->next;
}

/**
 * Problem 26: Reorder List (LC 143)
 * ----------------------------------
 * 🧠 Description:
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln, reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * Modify in-place without changing node values.
 *
 * 🔍 Example:
 * Input: 1→2→3→4
 * Output: 1→4→2→3
 *
 * 🎯 Key Insight:
 * 1. Find the middle of the list
 * 2. Reverse the second half
 * 3. Merge the two halves alternately
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Use slow/fast pointer to find middle
 * - Reverse the second half
 * - Merge two halves
 *
 * ✅ Base Case Initialization:
 * Empty list or single node → no change
 *
 * ✅ Transition:
 * Step-by-step as above
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
void ReorderList(ListNode* head) {
    if (!head || !head->next) return;

    // Step 1: Find the middle
    ListNode* slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse second half
    ListNode* prev = nullptr, *curr = slow->next;
    while (curr) {
        ListNode* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    slow->next = nullptr;

    // Step 3: Merge two halves
    ListNode* first = head, *second = prev;
    while (second) {
        ListNode* tmp1 = first->next;
        ListNode* tmp2 = second->next;

        first->next = second;
        second->next = tmp1;

        first = tmp1;
        second = tmp2;
    }
}

/**
 * Problem 27: Validate Binary Search Tree (LC 98)
 * ------------------------------------------------
 * 🧠 Description:
 * Determine if a binary tree is a valid binary search tree (BST).
 *
 * 🔍 Example:
 * Input: [2,1,3]
 * Output: true
 *
 * 🎯 Key Insight:
 * In-order traversal of BST should yield strictly increasing values.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * prev_val = last visited node's value in in-order traversal
 *
 * ✅ Transition:
 * Use recursive in-order traversal, ensure current > prev
 *
 * ✅ Iteration Order:
 * In-order (left → root → right)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool InOrder(TreeNode* node, long& prev_val) {
    if (!node) return true;
    if (!InOrder(node->left, prev_val)) return false;
    if (node->val <= prev_val) return false;
    prev_val = node->val;
    return InOrder(node->right, prev_val);
}

bool IsValidBST(TreeNode* root) {
    long prev_val = LONG_MIN;
    return InOrder(root, prev_val);
}

/**
 * Problem 28: Flatten Binary Tree to Linked List (LC 114)
 * ---------------------------------------------------------
 * 🧠 Description:
 * Flatten a binary tree into a linked list in-place following pre-order traversal.
 *
 * 🔍 Example:
 * Input: [1,2,5,3,4,null,6]
 * Output: 1→2→3→4→5→6
 *
 * 🎯 Key Insight:
 * Reverse post-order traversal (right → left → root) with a tail pointer.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Maintain a tail pointer to connect flattened nodes
 *
 * ✅ Transition:
 * - Recursively flatten right subtree
 * - Recursively flatten left subtree
 * - Point root.right = tail; root.left = nullptr
 *
 * ✅ Iteration Order:
 * Post-order reversed: right → left → root
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
void FlattenHelper(TreeNode* node, TreeNode*& tail) {
    if (!node) return;
    FlattenHelper(node->right, tail);
    FlattenHelper(node->left, tail);

    node->right = tail;
    node->left = nullptr;
    tail = node;
}

void Flatten(TreeNode* root) {
    TreeNode* tail = nullptr;
    FlattenHelper(root, tail);
}

/**
 * Problem 29: Binary Tree Maximum Path Sum (LC 124)
 * ---------------------------------------------------
 * 🧠 Description:
 * A path in a binary tree is any sequence of nodes where each pair is connected.
 * Return the maximum sum of any path in the tree.
 *
 * 🔍 Example:
 * Input: [-10,9,20,null,null,15,7]
 * Output: 42
 *
 * 🎯 Key Insight:
 * At each node, max gain = node.val + max(left_gain, 0) + max(right_gain, 0)
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * gain(node) = max path sum from this node to any leaf or null
 *
 * ✅ Base Case Initialization:
 * Null node → return 0
 *
 * ✅ Transition:
 * Update global_max = max(global_max, node.val + left_gain + right_gain)
 *
 * ✅ Iteration Order:
 * Post-order traversal
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
int MaxPathSumHelper(TreeNode* node, int& global_max) {
    if (!node) return 0;

    int left = max(0, MaxPathSumHelper(node->left, global_max));
    int right = max(0, MaxPathSumHelper(node->right, global_max));

    global_max = max(global_max, node->val + left + right);
    return node->val + max(left, right);
}

int MaxPathSum(TreeNode* root) {
    int global_max = INT_MIN;
    MaxPathSumHelper(root, global_max);
    return global_max;
}

/**
 * Problem 30: Clone Graph (LC 133)
 * ---------------------------------
 * 🧠 Description:
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 *
 * 🔍 Example:
 * Input: Node with value 1, connected to [2, 4]
 * Output: Cloned graph with same structure
 *
 * 🎯 Key Insight:
 * Use DFS or BFS and a visited map to avoid cycles and duplicate cloning.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * visited[node] = cloned copy of node
 *
 * ✅ Transition:
 * For each neighbor, recursively clone it and add to the cloned node’s neighbors
 *
 * ✅ Iteration Order:
 * DFS traversal (recursive)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
class Node30 {
public:
    int val;
    vector<Node30*> neighbors;
    Node30() : val(0), neighbors({}) {}
    Node30(int _val) : val(_val), neighbors({}) {}
};

Node30* CloneGraphDFS(Node30* node, unordered_map<Node30*, Node30*>& visited) {
    if (!node) return nullptr;
    if (visited.count(node)) return visited[node];

    Node30* clone = new Node30(node->val);
    visited[node] = clone;

    for (Node30* neighbor : node->neighbors) {
        clone->neighbors.push_back(CloneGraphDFS(neighbor, visited));
    }

    return clone;
}

Node30* CloneGraph(Node30* node) {
    unordered_map<Node30*, Node30*> visited;
    return CloneGraphDFS(node, visited);
}

/**
 * Problem 31: Binary Tree Right Side View (LC 199)
 * --------------------------------------------------
 * 🧠 Description:
 * Given the root of a binary tree, return the values of the nodes you can see from the right side.
 *
 * 🔍 Example:
 * Input: [1,2,3,null,5,null,4]
 * Output: [1,3,4]
 *
 * 🎯 Key Insight:
 * Perform level-order traversal and pick the last node of each level.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Queue for level-order traversal (BFS)
 *
 * ✅ Base Case Initialization:
 * Start with root in queue
 *
 * ✅ Transition:
 * For each level:
 *   - Traverse all nodes
 *   - Store the last node's value
 *
 * ✅ Iteration Order:
 * Level-by-level (breadth-first)
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
vector<int> RightSideView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        TreeNode* rightmost = nullptr;

        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            rightmost = node;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        if (rightmost) result.push_back(rightmost->val);
    }

    return result;
}

/**
 * Problem 32: Number of Islands (LC 200)
 * ---------------------------------------
 * 🧠 Description:
 * Given a 2D grid of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 *
 * 🔍 Example:
 * Input:
 * [
 *   ['1','1','0','0'],
 *   ['1','1','0','0'],
 *   ['0','0','1','0'],
 *   ['0','0','0','1']
 * ]
 * Output: 3
 *
 * 🎯 Key Insight:
 * Use DFS or BFS to mark all land connected to a starting point.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * grid[i][j] = current land cell
 *
 * ✅ Transition:
 * From each '1', start DFS and mark all reachable land as visited
 *
 * ✅ Iteration Order:
 * For all cells
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(m * n) for recursion stack
 */
void DFS(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0')
        return;

    grid[i][j] = '0';
    DFS(grid, i + 1, j);
    DFS(grid, i - 1, j);
    DFS(grid, i, j + 1);
    DFS(grid, i, j - 1);
}

int NumIslands(vector<vector<char>>& grid) {
    int count = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '1') {
                DFS(grid, i, j);
                count++;
            }
        }
    }

    return count;
}

/**
 * Problem 33: Lowest Common Ancestor of a Binary Tree (LC 236)
 * --------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * 🔍 Example:
 * Input: root = [3,5,1,6,2,0,8], p = 5, q = 1
 * Output: 3
 *
 * 🎯 Key Insight:
 * Use post-order traversal. Return the node itself if found. The first node where both p and q appear is the LCA.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Return current node if p or q found in subtree
 *
 * ✅ Transition:
 * Traverse left and right:
 * - If both return non-null ⇒ current is LCA
 * - Else return the non-null one
 *
 * ✅ Iteration Order:
 * Post-order
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
TreeNode* LowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    TreeNode* left = LowestCommonAncestor(root->left, p, q);
    TreeNode* right = LowestCommonAncestor(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
}

/**
 * Problem 34: Binary Tree Paths (LC 257)
 * ---------------------------------------
 * 🧠 Description:
 * Return all root-to-leaf paths in a binary tree.
 *
 * 🔍 Example:
 * Input: [1,2,3,null,5]
 * Output: ["1->2->5", "1->3"]
 *
 * 🎯 Key Insight:
 * Use DFS to accumulate path from root to leaves.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use recursion to build path as string
 *
 * ✅ Transition:
 * At each node, append value to current path
 * If leaf node, add full path to result
 *
 * ✅ Iteration Order:
 * Pre-order DFS
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
void DFS(TreeNode* node, string path, vector<string>& result) {
    if (!node) return;
    path += to_string(node->val);

    if (!node->left && !node->right) {
        result.push_back(path);
        return;
    }

    path += "->";
    DFS(node->left, path, result);
    DFS(node->right, path, result);
}

vector<string> BinaryTreePaths(TreeNode* root) {
    vector<string> result;
    DFS(root, "", result);
    return result;
}

/**
 * Problem 35: Alien Dictionary (LC 269) 🔒
 * -----------------------------------------
 * 🧠 Description:
 * Given a sorted dictionary of an alien language, return a string representing the order of characters.
 *
 * 🔍 Example:
 * Input: words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * 🎯 Key Insight:
 * Build a directed graph and apply topological sort.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * graph[c] = set of characters that come after c
 * indegree[c] = number of incoming edges to c
 *
 * ✅ Transition:
 * For each adjacent word pair, find first mismatch and add edge
 *
 * ✅ Iteration Order:
 * BFS topological sort (Kahn's algorithm)
 *
 * ⏱️ Time Complexity: O(N)
 * 🧠 Space Complexity: O(C) where C is number of unique letters
 */
string AlienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> indegree;

    // Initialize graph
    for (const string& word : words)
        for (char c : word) indegree[c] = 0;

    // Build edges
    for (int i = 0; i < words.size() - 1; ++i) {
        string w1 = words[i], w2 = words[i + 1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for (int j = 0; j < len; ++j) {
            if (w1[j] != w2[j]) {
                if (!graph[w1[j]].count(w2[j])) {
                    graph[w1[j]].insert(w2[j]);
                    indegree[w2[j]]++;
                }
                found = true;
                break;
            }
        }
        if (!found && w1.size() > w2.size()) return "";
    }

    // Topological sort
    queue<char> q;
    for (auto& [ch, deg] : indegree)
        if (deg == 0) q.push(ch);

    string result;
    while (!q.empty()) {
        char c = q.front(); q.pop();
        result += c;

        for (char neighbor : graph[c]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return result.size() == indegree.size() ? result : "";
}

/**
 * Problem 36: Shortest Distance from All Buildings (LC 317) 🔒
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given a 2D grid with buildings (1), empty land (0), and obstacles (2),
 * find the minimum total distance from one empty land to all buildings.
 *
 * 🔍 Example:
 * Input:
 * [[1,0,2,0,1],
 *  [0,0,0,0,0],
 *  [0,0,1,0,0]]
 * Output: 7
 *
 * 🎯 Key Insight:
 * From each building, do BFS to accumulate distance to each empty cell.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - dist[i][j] = total distance from all buildings to (i,j)
 * - reach[i][j] = number of buildings that reached (i,j)
 *
 * ✅ Base Case Initialization:
 * For each building cell (value = 1), start BFS
 *
 * ✅ Transition:
 * During BFS:
 *   - For each reachable '0' cell, add to distance sum and increment reach count
 *
 * ✅ Final:
 * Return min dist[i][j] where reach[i][j] == buildingCount
 *
 * ⏱️ Time Complexity: O(m * n * buildings)
 * 🧠 Space Complexity: O(m * n)
 */
int ShortestDistance(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, 0));
    vector<vector<int>> reach(m, vector<int>(n, 0));
    int building_count = 0;

    vector<int> dirs = {0, 1, 0, -1, 0};

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 1) {
                building_count++;
                queue<pair<int, int>> q;
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                q.push({i, j});
                int level = 0;

                while (!q.empty()) {
                    int sz = q.size();
                    level++;
                    for (int k = 0; k < sz; ++k) {
                        auto [x, y] = q.front(); q.pop();
                        for (int d = 0; d < 4; ++d) {
                            int nx = x + dirs[d], ny = y + dirs[d + 1];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                                !visited[nx][ny] && grid[nx][ny] == 0) {
                                visited[nx][ny] = true;
                                dist[nx][ny] += level;
                                reach[nx][ny]++;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }

    int res = INT_MAX;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (grid[i][j] == 0 && reach[i][j] == building_count)
                res = min(res, dist[i][j]);

    return res == INT_MAX ? -1 : res;
}

/**
 * Problem 37: Diameter of Binary Tree (LC 543)
 * ---------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return the length of the longest path between any two nodes.
 *
 * 🔍 Example:
 * Input: [1,2,3,4,5]
 * Output: 3 (path: 4 → 2 → 1 → 3)
 *
 * 🎯 Key Insight:
 * For each node, max path through it = left height + right height
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * height(node) = max depth from node to leaf
 * diameter = max(left + right) over all nodes
 *
 * ✅ Transition:
 * Recursively calculate height and update global max
 *
 * ✅ Iteration Order:
 * Post-order DFS
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
int MaxDepth(TreeNode* node, int& diameter) {
    if (!node) return 0;
    int left = MaxDepth(node->left, diameter);
    int right = MaxDepth(node->right, diameter);
    diameter = max(diameter, left + right);
    return max(left, right) + 1;
}

int DiameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    MaxDepth(root, diameter);
    return diameter;
}

/**
 * Problem 38: Accounts Merge (LC 721)
 * -------------------------------------
 * 🧠 Description:
 * Given a list of accounts where each element is [name, email1, email2, ...],
 * merge accounts that have common emails.
 *
 * 🔍 Example:
 * Input: [["John", "johnsmith@mail.com", "john00@mail.com"], ...]
 * Output: Merged accounts with unique names
 *
 * 🎯 Key Insight:
 * Union-Find (Disjoint Set Union) to group emails by connectivity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * parent[email] = root representative
 *
 * ✅ Transition:
 * Union all emails in same account
 *
 * ✅ Final:
 * Collect emails by root, sort, and prepend account name
 *
 * ⏱️ Time Complexity: O(N * α(N)) where N = total emails
 * 🧠 Space Complexity: O(N)
 */
string Find(string email, unordered_map<string, string>& parent) {
    if (parent[email] != email)
        parent[email] = Find(parent[email], parent);
    return parent[email];
}

void Union(string a, string b, unordered_map<string, string>& parent) {
    parent[Find(a, parent)] = Find(b, parent);
}

vector<vector<string>> AccountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, string> parent;
    unordered_map<string, string> owner;

    // Init
    for (const auto& acc : accounts)
        for (int i = 1; i < acc.size(); ++i) {
            parent[acc[i]] = acc[i];
            owner[acc[i]] = acc[0];
        }

    // Union emails in same account
    for (const auto& acc : accounts)
        for (int i = 2; i < acc.size(); ++i)
            Union(acc[i], acc[1], parent);

    // Group emails by root
    unordered_map<string, set<string>> groups;
    for (const auto& [email, _] : parent) {
        groups[Find(email, parent)].insert(email);
    }

    // Build result
    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        vector<string> entry = {owner[root]};
        entry.insert(entry.end(), emails.begin(), emails.end());
        result.push_back(entry);
    }

    return result;
}

/**
 * Problem 39: Convert Binary Search Tree to Sorted Doubly Linked List (LC 426) 🔒
 * --------------------------------------------------------------------------------
 * 🧠 Description:
 * Convert a BST to a sorted circular doubly-linked list in-place.
 *
 * 🔍 Example:
 * Input: BST [4,2,5,1,3]
 * Output: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> (circular)
 *
 * 🎯 Key Insight:
 * In-order traversal builds sorted order; link nodes as you go.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use two pointers: prev, head
 *
 * ✅ Transition:
 * During in-order traversal:
 *   - prev->right = curr; curr->left = prev
 *
 * ✅ Final:
 * Connect head and tail to make it circular
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(h)
 */
class Node39 {
public:
    int val;
    Node39* left;
    Node39* right;
    Node39(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

void Dfs(Node39* node, Node39*& prev, Node39*& head) {
    if (!node) return;
    Dfs(node->left, prev, head);

    if (prev) {
        prev->right = node;
        node->left = prev;
    } else {
        head = node;
    }
    prev = node;

    Dfs(node->right, prev, head);
}

Node39* TreeToDoublyList(Node39* root) {
    if (!root) return nullptr;
    Node39* head = nullptr, *prev = nullptr;
    Dfs(root, prev, head);

    // Connect head and tail
    head->left = prev;
    prev->right = head;
    return head;
}

/**
 * Problem 40: Is Graph Bipartite? (LC 785)
 * -----------------------------------------
 * 🧠 Description:
 * Given an undirected graph, return true if it's bipartite.
 *
 * 🔍 Example:
 * Input: [[1,3],[0,2],[1,3],[0,2]]
 * Output: true
 *
 * 🎯 Key Insight:
 * Use BFS (or DFS) to color graph with 2 colors.
 * If any two adjacent nodes share the same color → not bipartite.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * color[i] = -1 (unvisited), 0 or 1 otherwise
 *
 * ✅ Transition:
 * For each neighbor:
 *   - If unvisited → assign opposite color
 *   - If already visited and same color → invalid
 *
 * ✅ Iteration Order:
 * BFS for disconnected components
 *
 * ⏱️ Time Complexity: O(V + E)
 * 🧠 Space Complexity: O(V)
 */
bool IsBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);

    for (int i = 0; i < n; ++i) {
        if (color[i] != -1) continue;

        queue<int> q;
        q.push(i);
        color[i] = 0;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int neighbor : graph[node]) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                } else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * Problem 41: Binary Tree Vertical Order Traversal (LC 314) 🔒
 * -------------------------------------------------------------
 * 🧠 Description:
 * Given a binary tree, return its vertical order traversal.
 * Return nodes column by column from left to right, and top to bottom within each column.
 *
 * 🔍 Example:
 * Input:
 *     3
 *    / \
 *   9   8
 *  / \ / \
 * 4  0 1  7
 * Output: [[4], [9], [3,0,1], [8], [7]]
 *
 * 🎯 Key Insight:
 * BFS with a column index assigned to each node. Use a map from column to nodes.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * queue of pairs: (node, column_index)
 * map<col_index, vector<node values>> stores result
 *
 * ✅ Base Case Initialization:
 * Push root with column 0
 *
 * ✅ Transition:
 * - left child: col - 1
 * - right child: col + 1
 *
 * ✅ Iteration Order:
 * BFS ensures top-to-bottom order
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
vector<vector<int>> VerticalOrder(TreeNode* root) {
    if (!root) return {};

    map<int, vector<int>> col_map;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [node, col] = q.front(); q.pop();
        col_map[col].push_back(node->val);

        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }

    vector<vector<int>> result;
    for (auto& [col, vals] : col_map)
        result.push_back(vals);

    return result;
}

/**
 * Problem 42: Letter Combinations of a Phone Number (LC 17)
 * -----------------------------------------------------------
 * 🧠 Description:
 * Given a string of digits from 2–9, return all possible letter combinations.
 *
 * 🔍 Example:
 * Input: "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * 🎯 Key Insight:
 * Backtracking on digit positions, append all valid letters.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * digit_to_letters[d] = mapped letters
 * path = current letter string
 *
 * ✅ Base Case Initialization:
 * path.length() == digits.length() → add to result
 *
 * ✅ Transition:
 * For each letter in digit mapping → recurse
 *
 * ⏱️ Time Complexity: O(3^n) to O(4^n)
 * 🧠 Space Complexity: O(n) for call stack
 */
void Backtrack(const string& digits, const unordered_map<char, string>& mapping,
               int index, string& path, vector<string>& result) {
    if (index == digits.size()) {
        result.push_back(path);
        return;
    }

    for (char c : mapping.at(digits[index])) {
        path.push_back(c);
        Backtrack(digits, mapping, index + 1, path, result);
        path.pop_back();
    }
}

vector<string> LetterCombinations(string digits) {
    if (digits.empty()) return {};

    unordered_map<char, string> mapping = {
        {'2',"abc"}, {'3',"def"}, {'4',"ghi"}, {'5',"jkl"},
        {'6',"mno"}, {'7',"pqrs"}, {'8',"tuv"}, {'9',"wxyz"}
    };

    vector<string> result;
    string path;
    Backtrack(digits, mapping, 0, path, result);
    return result;
}

/**
 * Problem 43: Permutations (LC 46)
 * ---------------------------------
 * 🧠 Description:
 * Return all possible permutations of a list of distinct integers.
 *
 * 🔍 Example:
 * Input: [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],...]
 *
 * 🎯 Key Insight:
 * Backtracking with used[] array to track available numbers.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * path = current permutation
 * used[i] = whether nums[i] has been used
 *
 * ✅ Base Case Initialization:
 * If path.size() == nums.size() → add to result
 *
 * ✅ Transition:
 * For all unused nums[i], mark used and recurse
 *
 * ⏱️ Time Complexity: O(n!)
 * 🧠 Space Complexity: O(n) for recursion
 */
void Backtrack(vector<int>& nums, vector<bool>& used,
               vector<int>& path, vector<vector<int>>& result) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        Backtrack(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> Permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    Backtrack(nums, used, path, result);
    return result;
}

/**
 * Problem 44: Permutations II (LC 47)
 * ------------------------------------
 * 🧠 Description:
 * Given a list with duplicate integers, return all unique permutations.
 *
 * 🔍 Example:
 * Input: [1,1,2]
 * Output: [[1,1,2],[1,2,1],[2,1,1]]
 *
 * 🎯 Key Insight:
 * Sort input. Skip duplicate values when the previous identical number hasn't been used.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * used[i] = whether nums[i] is used
 *
 * ✅ Base Case Initialization:
 * If path.size() == nums.size() → add to result
 *
 * ✅ Transition:
 * - Skip i if used[i]
 * - Skip duplicates: if nums[i] == nums[i-1] and !used[i-1]
 *
 * ⏱️ Time Complexity: O(n!)
 * 🧠 Space Complexity: O(n)
 */
void Backtrack(vector<int>& nums, vector<bool>& used,
               vector<int>& path, vector<vector<int>>& result) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

        used[i] = true;
        path.push_back(nums[i]);
        Backtrack(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> PermuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    Backtrack(nums, used, path, result);
    return result;
}

/**
 * Problem 45: Remove Invalid Parentheses (LC 301)
 * ------------------------------------------------
 * 🧠 Description:
 * Remove the minimum number of invalid parentheses to make the input string valid.
 * Return all possible results.
 *
 * 🔍 Example:
 * Input: "()())()"
 * Output: ["(())()", "()()()"]
 *
 * 🎯 Key Insight:
 * Use BFS to try all removals level by level. Stop when we find valid expressions.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use queue<string> for BFS; unordered_set to avoid duplicates
 *
 * ✅ Base Case Initialization:
 * Start from original string
 *
 * ✅ Transition:
 * At each level, remove one parenthesis from each position
 *
 * ⏱️ Time Complexity: Exponential in worst case
 * 🧠 Space Complexity: O(N * 2^N)
 */
bool IsValid(const string& s) {
    int count = 0;
    for (char c : s) {
        if (c == '(') count++;
        else if (c == ')') {
            if (--count < 0) return false;
        }
    }
    return count == 0;
}

vector<string> RemoveInvalidParentheses(string s) {
    unordered_set<string> visited;
    queue<string> q;
    vector<string> result;
    bool found = false;

    q.push(s);
    visited.insert(s);

    while (!q.empty()) {
        string curr = q.front(); q.pop();

        if (IsValid(curr)) {
            result.push_back(curr);
            found = true;
        }

        if (found) continue;

        for (int i = 0; i < curr.size(); ++i) {
            if (curr[i] != '(' && curr[i] != ')') continue;
            string next = curr.substr(0, i) + curr.substr(i + 1);
            if (visited.insert(next).second)
                q.push(next);
        }
    }

    return result;
}

/**
 * Problem 46: Regular Expression Matching (LC 10)
 * -------------------------------------------------
 * 🧠 Description:
 * Implement regular expression matching with support for '.' and '*'.
 * - '.' matches any single character.
 * - '*' matches zero or more of the preceding element.
 *
 * 🔍 Example:
 * Input: s = "aab", p = "c*a*b"
 * Output: true
 *
 * 🎯 Key Insight:
 * Use dynamic programming. '*' can act as zero or multiple of previous char.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Let dp[i][j] be true if s[0..i-1] matches p[0..j-1]
 *
 * ✅ Base Case Initialization:
 * - dp[0][0] = true
 * - dp[0][j] = true only if p[j-1] == '*' and dp[0][j-2] == true
 *
 * ✅ Transition:
 * - If p[j-1] == '*':
 *     dp[i][j] = dp[i][j-2]                        (zero preceding element)
 *                || (dp[i-1][j] and s[i-1] matches p[j-2])  (extend match)
 * - Else:
 *     dp[i][j] = dp[i-1][j-1] and s[i-1] matches p[j-1]
 *
 * ✅ Iteration Order:
 * Bottom-up from i = 0..m, j = 0..n
 *
 * 🚨 Edge Cases:
 * - s or p is empty
 * - p starts with '*': invalid pattern
 * - multiple consecutive '*': must associate with previous char
 * - p = ".*" matches anything
 *
 * ⏱️ Time Complexity: O(m * n)
 * 🧠 Space Complexity: O(m * n)
 */
bool IsMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // Initialize empty string with pattern like a*, a*b*, etc.
    for (int j = 2; j <= n; j += 2) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] ||
                          (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
            } else {
                dp[i][j] = dp[i - 1][j - 1] &&
                          (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }

    return dp[m][n];
}

/**
 * Problem 47: Subsets (LC 78)
 * -----------------------------
 * 🧠 Description:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 *
 * 🔍 Example:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
 *
 * 🎯 Key Insight:
 * Use backtracking to explore include/exclude paths, or iterative subset expansion.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - path: current subset
 * - index: current position in nums
 *
 * ✅ Base Case Initialization:
 * - Always push path into result at each level
 *
 * ✅ Transition:
 * - At each index, choose to include nums[i] or not
 *
 * ✅ Iteration Order:
 * DFS (pre-order), from index = 0 to nums.size()
 *
 * 🚨 Edge Cases:
 * - Empty input → returns [[]]
 * - Input of size 1 → returns [[], [x]]
 *
 * ⏱️ Time Complexity: O(2^n)
 * 🧠 Space Complexity: O(n)
 */
void Backtrack(vector<int>& nums, int index, vector<int>& path, vector<vector<int>>& result) {
    result.push_back(path);  // push current subset
    for (int i = index; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        Backtrack(nums, i + 1, path, result);
        path.pop_back();
    }
}

vector<vector<int>> Subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    Backtrack(nums, 0, path, result);
    return result;
}

/**
 * Problem 48: Strobogrammatic Number II (LC 247) 🔒
 * --------------------------------------------------
 * 🧠 Description:
 * Return all strobogrammatic numbers that are of length n.
 * A strobogrammatic number looks the same when rotated 180 degrees.
 *
 * 🔍 Example:
 * Input: n = 2
 * Output: ["11","69","88","96"]
 *
 * 🎯 Key Insight:
 * Use recursive construction by filling numbers from outside-in.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - Use start and end pointers to construct numbers recursively
 *
 * ✅ Base Case Initialization:
 * - When start > end, push result
 * - If start == end, only add self-symmetric digits: '0', '1', '8'
 *
 * ✅ Transition:
 * Fill symmetric pairs: ('0','0'), ('1','1'), ('6','9'), ('8','8'), ('9','6')
 *
 * ✅ Iteration Order:
 * DFS from start to end
 *
 * 🚨 Edge Cases:
 * - Do not allow numbers to start with '0' unless n == 1
 *
 * ⏱️ Time Complexity: O(5^(n/2))
 * 🧠 Space Complexity: O(n)
 */
void BuildStrobogrammatic(vector<string>& result, vector<char>& current, int left, int right) {
    vector<pair<char, char>> pairs = {{'0','0'}, {'1','1'}, {'6','9'}, {'8','8'}, {'9','6'}};

    if (left > right) {
        result.push_back(string(current.begin(), current.end()));
        return;
    }

    for (auto [a, b] : pairs) {
        if (left == right && a != b) continue;         // middle char must be symmetric
        if (left == 0 && a == '0' && current.size() > 1) continue; // avoid leading 0

        current[left] = a;
        current[right] = b;
        BuildStrobogrammatic(result, current, left + 1, right - 1);
    }
}

vector<string> FindStrobogrammatic(int n) {
    vector<string> result;
    vector<char> current(n);
    BuildStrobogrammatic(result, current, 0, n - 1);
    return result;
}

/**
 * Problem 49: Divide Two Integers (LC 29)
 * ----------------------------------------
 * 🧠 Description:
 * Divide two integers without using multiplication, division, or mod operator.
 * Return quotient after truncating toward zero.
 *
 * 🔍 Example:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 *
 * 🎯 Key Insight:
 * Use bit shifts to subtract large multiples of divisor efficiently.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use long long to avoid overflow; perform subtraction via bit shifts.
 *
 * ✅ Base Case Initialization:
 * Convert to positive, track sign separately
 *
 * ✅ Transition:
 * For each shift from 31 to 0:
 *   If (dividend >> shift) >= divisor, subtract (divisor << shift)
 *
 * ✅ Iteration Order:
 * Top-down (shift = 31 to 0)
 *
 * 🚨 Edge Cases:
 * - divisor = 0 → undefined (return INT_MAX)
 * - overflow case: INT_MIN / -1 → return INT_MAX
 *
 * ⏱️ Time Complexity: O(log N)
 * 🧠 Space Complexity: O(1)
 */
int Divide(int dividend, int divisor) {
    if (divisor == 0) return INT_MAX;
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;

    long long dvd = abs((long long)dividend);
    long long dvs = abs((long long)divisor);
    int result = 0;

    for (int i = 31; i >= 0; --i) {
        if ((dvd >> i) >= dvs) {
            dvd -= dvs << i;
            result += 1 << i;
        }
    }

    return (dividend > 0) == (divisor > 0) ? result : -result;
}

/**
 * Problem 50: Search in Rotated Sorted Array (LC 33)
 * ---------------------------------------------------
 * 🧠 Description:
 * Given a rotated sorted array and a target, return its index if found; else -1.
 *
 * 🔍 Example:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * 🎯 Key Insight:
 * Use binary search with logic to identify which half is sorted.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * left = 0, right = nums.size() - 1
 *
 * ✅ Transition:
 * At each step:
 *   - Determine if left to mid is sorted or mid to right is sorted
 *   - Narrow search to correct side based on target position
 *
 * ✅ Iteration Order:
 * Standard binary search loop
 *
 * 🚨 Edge Cases:
 * - Duplicates not allowed in this version
 * - Empty array → return -1
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
int Search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) return mid;

        // Left half sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half sorted
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

/**
 * Problem 51: Find First and Last Position of Element in Sorted Array (LC 34)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * Given an array of integers sorted in non-decreasing order, find the starting and ending position of a given target.
 *
 * 🔍 Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3, 4]
 *
 * 🎯 Key Insight:
 * Use binary search twice — once to find the first index, once for the last.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use binary search with custom condition to find left and right boundaries.
 *
 * ✅ Transition:
 * - Find left: move right when nums[mid] < target
 * - Find right: move left when nums[mid] > target
 *
 * ✅ Iteration Order:
 * Two binary searches
 *
 * 🚨 Edge Cases:
 * - Target not found → return [-1, -1]
 * - All elements = target → return [0, n-1]
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
int FindBound(vector<int>& nums, int target, bool left) {
    int low = 0, high = nums.size() - 1, bound = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] == target) {
            bound = mid;
            if (left) high = mid - 1;
            else low = mid + 1;
        } else if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return bound;
}

vector<int> SearchRange(vector<int>& nums, int target) {
    return {FindBound(nums, target, true), FindBound(nums, target, false)};
}

/**
 * Problem 52: Pow(x, n) (LC 50)
 * -------------------------------
 * 🧠 Description:
 * Implement pow(x, n), which calculates x raised to the power n.
 *
 * 🔍 Example:
 * Input: x = 2.0, n = 10
 * Output: 1024.0
 *
 * 🎯 Key Insight:
 * Use fast exponentiation (divide and conquer) to reduce time complexity.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * pow(x, n) = pow(x*x, n/2) if n is even
 *           = x * pow(x*x, n/2) if n is odd
 *
 * ✅ Base Case Initialization:
 * n == 0 → return 1
 *
 * ✅ Iteration Order:
 * Recursive divide & conquer
 *
 * 🚨 Edge Cases:
 * - Negative exponent → invert base: 1 / pow(x, -n)
 * - n == INT_MIN → cast to long
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(log n)
 */
double MyPow(double x, int n) {
    long long N = n;
    if (N < 0) {
        x = 1 / x;
        N = -N;
    }

    double result = 1;
    while (N) {
        if (N % 2 == 1) result *= x;
        x *= x;
        N /= 2;
    }

    return result;
}

/**
 * Problem 53: Merge Intervals (LC 56)
 * -------------------------------------
 * 🧠 Description:
 * Given a list of intervals, merge all overlapping intervals.
 *
 * 🔍 Example:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 *
 * 🎯 Key Insight:
 * Sort intervals by start time, then merge overlapping ones in one pass.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * merged = result list
 *
 * ✅ Base Case Initialization:
 * Sort intervals by start time
 *
 * ✅ Transition:
 * If current start > merged.back().end → push new
 * Else → merge by updating end = max(end, current.end)
 *
 * ✅ Iteration Order:
 * Left to right
 *
 * 🚨 Edge Cases:
 * - Empty input → return empty
 * - Fully overlapping intervals
 *
 * ⏱️ Time Complexity: O(n log n)
 * 🧠 Space Complexity: O(n)
 */
vector<vector<int>> Merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;

    for (auto& interval : intervals) {
        if (merged.empty() || merged.back()[1] < interval[0]) {
            merged.push_back(interval);
        } else {
            merged.back()[1] = max(merged.back()[1], interval[1]);
        }
    }

    return merged;
}

/**
 * Problem 54: Find Peak Element (LC 162)
 * ----------------------------------------
 * 🧠 Description:
 * A peak element is an element strictly greater than its neighbors.
 * Return the index of any one peak.
 *
 * 🔍 Example:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5
 *
 * 🎯 Key Insight:
 * Binary search — if mid < mid+1 → peak is on right
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Binary search for peak in nums
 *
 * ✅ Transition:
 * - if nums[mid] < nums[mid + 1] → search right
 * - else → search left
 *
 * ✅ Iteration Order:
 * Standard binary search
 *
 * 🚨 Edge Cases:
 * - Single element array → return 0
 * - Peak at boundary
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */
int FindPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] < nums[mid + 1])
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

/**
 * Problem 55: First Bad Version (LC 278)
 * ----------------------------------------
 * 🧠 Description:
 * You are given API `bool isBadVersion(int version)` which tells whether version is bad.
 * Find the first bad version that causes all following versions to be bad.
 *
 * 🔍 Example:
 * Input: n = 5, first bad = 4
 * Output: 4
 *
 * 🎯 Key Insight:
 * Binary search — search for smallest index where isBadVersion is true.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Binary search to minimize first version where isBadVersion(version) == true
 *
 * ✅ Transition:
 * - If mid is bad → search left
 * - Else → search right
 *
 * ✅ Iteration Order:
 * Binary search from 1 to n
 *
 * 🚨 Edge Cases:
 * - First version is bad
 * - All versions are good → undefined (or return n+1)
 *
 * ⏱️ Time Complexity: O(log n)
 * 🧠 Space Complexity: O(1)
 */

// Mocked global variable: assume version 4 is the first bad version
int bad = 4;

// Simulated isBadVersion API
bool isBadVersion(int version) {
    return version >= bad;
}

int FirstBadVersion(int n) {
    int left = 1, right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isBadVersion(mid))
            right = mid;
        else
            left = mid + 1;
    }

    return left;
}

/**
 * Problem 56: Intersection of Two Arrays (LC 349)
 * ------------------------------------------------
 * 🧠 Description:
 * Given two integer arrays `nums1` and `nums2`, return their intersection.
 * Each element in the result must be unique, and the result can be in any order.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 *
 * 🎯 Key Insight:
 * Use sets to track and find common elements efficiently.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - seen = set of nums1 elements
 * - result = set of common elements
 *
 * ✅ Transition:
 * - Iterate nums2, if element in seen → insert to result
 *
 * ✅ Iteration Order:
 * Loop over both arrays
 *
 * 🚨 Edge Cases:
 * - One or both arrays are empty → return empty vector
 * - All duplicates → result still has unique elements
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(m + n)
 */
vector<int> Intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> result;

    for (int num : nums2) {
        if (set1.count(num)) result.insert(num);
    }

    return vector<int>(result.begin(), result.end());
}

/**
 * Problem 57: Intersection of Two Arrays II (LC 350)
 * ---------------------------------------------------
 * 🧠 Description:
 * Given two integer arrays `nums1` and `nums2`, return their intersection including duplicate counts.
 *
 * 🔍 Example:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2,2]
 *
 * 🎯 Key Insight:
 * Use hashmap to count occurrences, then match in second array.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - count1[num] = number of times num appears in nums1
 *
 * ✅ Transition:
 * - For each num in nums2, if count1[num] > 0, add to result
 *
 * ✅ Iteration Order:
 * First map nums1, then iterate nums2
 *
 * 🚨 Edge Cases:
 * - One array empty → return empty
 * - No common elements → return empty
 *
 * ⏱️ Time Complexity: O(m + n)
 * 🧠 Space Complexity: O(m)
 */
vector<int> Intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> count;
    for (int num : nums1) count[num]++;

    vector<int> result;
    for (int num : nums2) {
        if (count[num] > 0) {
            result.push_back(num);
            count[num]--;
        }
    }

    return result;
}

/**
 * Problem 58: Longest Palindromic Substring (LC 5)
 * --------------------------------------------------
 * 🧠 Description:
 * Given a string `s`, return the longest palindromic substring in `s`.
 *
 * 🔍 Example:
 * Input: s = "babad"
 * Output: "bab" or "aba"
 *
 * 🎯 Key Insight:
 * Expand around every center (both odd and even) to find longest palindrome.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Expand from center `l` and `r`, extend while s[l] == s[r]
 *
 * ✅ Base Case Initialization:
 * Check all i and i+1 as potential centers
 *
 * ✅ Transition:
 * For each center, expand and compare with longest so far
 *
 * ✅ Iteration Order:
 * i = 0 to n - 1
 *
 * 🚨 Edge Cases:
 * - Empty string → return ""
 * - All characters same → whole string is result
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(1)
 */
string Expand(string& s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
        l--; r++;
    }
    return s.substr(l + 1, r - l - 1);
}

string LongestPalindrome(string s) {
    string res;
    for (int i = 0; i < s.size(); ++i) {
        string odd = Expand(s, i, i);
        string even = Expand(s, i, i + 1);
        if (odd.size() > res.size()) res = odd;
        if (even.size() > res.size()) res = even;
    }
    return res;
}

/**
 * Problem 59: Longest Valid Parentheses (LC 32)
 * -----------------------------------------------
 * 🧠 Description:
 * Given a string containing only '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 *
 * 🔍 Example:
 * Input: s = "(()"
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use a stack or DP to track matching parentheses positions.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = longest valid substring ending at index i
 *
 * ✅ Base Case Initialization:
 * dp[0] = 0
 *
 * ✅ Transition:
 * If s[i] == ')' and s[i-1] == '(' → dp[i] = dp[i-2] + 2
 * If s[i] == ')' and s[i-1] == ')' and s[i-dp[i-1]-1] == '(':
 *   dp[i] = dp[i-1] + 2 + dp[i-dp[i-1]-2]
 *
 * ✅ Iteration Order:
 * i from 1 to n-1
 *
 * 🚨 Edge Cases:
 * - Empty string → return 0
 * - No valid pair → return 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
int LongestValidParentheses(string s) {
    int n = s.size(), max_len = 0;
    vector<int> dp(n, 0);

    for (int i = 1; i < n; ++i) {
        if (s[i] == ')') {
            if (s[i - 1] == '(')
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                dp[i] = dp[i - 1] + 2 +
                        (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
        }
        max_len = max(max_len, dp[i]);
    }

    return max_len;
}

/**
 * Problem 60: Decode Ways (LC 91)
 * ---------------------------------
 * 🧠 Description:
 * Given a string s containing digits, return the number of ways to decode it.
 * 'A' = 1, ..., 'Z' = 26
 *
 * 🔍 Example:
 * Input: s = "226"
 * Output: 3 ("2 2 6", "22 6", "2 26")
 *
 * 🎯 Key Insight:
 * Use dynamic programming to count valid decodings from left to right.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = # ways to decode first i characters
 *
 * ✅ Base Case Initialization:
 * dp[0] = 1 (empty string)
 * dp[1] = 1 if s[0] ≠ '0'
 *
 * ✅ Transition:
 * - If s[i-1] ≠ '0' → dp[i] += dp[i-1]
 * - If valid 2-digit (10–26) → dp[i] += dp[i-2]
 *
 * ✅ Iteration Order:
 * i = 2 to s.length()
 *
 * 🚨 Edge Cases:
 * - Starts with '0' → return 0
 * - Contains invalid segments like "30", "01" → skip those paths
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
int NumDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (s[i - 1] != '0') dp[i] += dp[i - 1];
        int two_digit = stoi(s.substr(i - 2, 2));
        if (two_digit >= 10 && two_digit <= 26) dp[i] += dp[i - 2];
    }

    return dp[n];
}

/**
 * Problem 61: Best Time to Buy and Sell Stock (LC 121)
 * ------------------------------------------------------
 * 🧠 Description:
 * Given an array where the i-th element is the price of a stock on day i, find the max profit.
 * You may only complete one transaction (buy once and sell once).
 *
 * 🔍 Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5 (buy at 1, sell at 6)
 *
 * 🎯 Key Insight:
 * Track minimum price so far and calculate profit at each step.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * min_price = lowest price seen so far
 * max_profit = max(prices[i] - min_price)
 *
 * ✅ Base Case Initialization:
 * min_price = prices[0], max_profit = 0
 *
 * ✅ Transition:
 * Iterate prices:
 *   - Update min_price
 *   - Update max_profit if current profit > previous
 *
 * ✅ Iteration Order:
 * i from 1 to end
 *
 * 🚨 Edge Cases:
 * - Empty or single element → profit is 0
 * - Prices always decreasing → profit is 0
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int MaxProfit(vector<int>& prices) {
    if (prices.size() < 2) return 0;
    int min_price = prices[0], max_profit = 0;

    for (int i = 1; i < prices.size(); ++i) {
        min_price = min(min_price, prices[i]);
        max_profit = max(max_profit, prices[i] - min_price);
    }

    return max_profit;
}

/**
 * Problem 62: Word Break (LC 139)
 * ---------------------------------
 * 🧠 Description:
 * Given a string s and a dictionary of words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
 *
 * 🔍 Example:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 *
 * 🎯 Key Insight:
 * Use dynamic programming to track valid segmentations ending at each index.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * dp[i] = true if s[0..i-1] can be segmented
 *
 * ✅ Base Case Initialization:
 * dp[0] = true (empty string)
 *
 * ✅ Transition:
 * For j in [0, i): if dp[j] && s[j..i-1] in wordDict → dp[i] = true
 *
 * ✅ Iteration Order:
 * i from 1 to s.length()
 *
 * 🚨 Edge Cases:
 * - Empty string → true
 * - No match in wordDict → false
 *
 * ⏱️ Time Complexity: O(n^2)
 * 🧠 Space Complexity: O(n)
 */
bool WordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

/**
 * Problem 63: Range Sum Query 2D - Immutable (LC 304)
 * -----------------------------------------------------
 * 🧠 Description:
 * Given a 2D matrix, implement a class with method sumRegion(row1, col1, row2, col2)
 * that returns the sum of elements in the rectangular area.
 *
 * 🔍 Example:
 * Input: matrix = [[3,0,1],[5,6,3],[1,2,0]], query: (2,1,2,2)
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use a prefix sum matrix where sum[i][j] = sum from (0,0) to (i-1,j-1)
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * prefix[i+1][j+1] = matrix[0..i][0..j] sum
 *
 * ✅ Base Case Initialization:
 * prefix[0][*] = prefix[*][0] = 0
 *
 * ✅ Transition:
 * prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
 *
 * ✅ Query:
 * sum = A - B - C + D using inclusion-exclusion
 *
 * 🚨 Edge Cases:
 * - Empty matrix → all sum queries return 0
 *
 * ⏱️ Time Complexity:
 * - Init: O(m * n)
 * - Query: O(1)
 * 🧠 Space Complexity: O(m * n)
 */
class NumMatrix {
private:
    vector<vector<int>> prefix;

public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix.empty() ? 0 : matrix[0].size();
        prefix = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] +
                               prefix[i][j-1] - prefix[i-1][j-1];
    }

    int SumRegion(int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - prefix[r2+1][c1] -
               prefix[r1][c2+1] + prefix[r1][c1];
    }
};

/**
 * Problem 64: Continuous Subarray Sum (LC 523)
 * ---------------------------------------------
 * 🧠 Description:
 * Given an integer array `nums` and an integer `k`, return true if `nums` has a subarray of length at least 2 whose sum is a multiple of `k`.
 *
 * 🔍 Example:
 * Input: nums = [23,2,4,6,7], k = 6
 * Output: true ([2,4])
 *
 * 🎯 Key Insight:
 * If (prefix sum at i) % k == (prefix sum at j) % k, then subarray [j+1, i] is divisible by k.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Use map: remainder → index of first occurrence
 *
 * ✅ Base Case Initialization:
 * map[0] = -1 to handle full prefix being divisible
 *
 * ✅ Transition:
 * At each index i:
 *   - sum += nums[i]
 *   - rem = sum % k
 *   - if rem in map and i - map[rem] ≥ 2 → return true
 *
 * ✅ Iteration Order:
 * Linear from left to right
 *
 * 🚨 Edge Cases:
 * - k = 0 → check for two consecutive zeros
 * - nums.size() < 2 → return false
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(k) or O(n)
 */
bool CheckSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mod_index = {{0, -1}};
    int sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
        int rem = k ? sum % k : sum;

        if (mod_index.count(rem)) {
            if (i - mod_index[rem] > 1) return true;
        } else {
            mod_index[rem] = i;
        }
    }

    return false;
}

/**
 * Problem 66: Implement Trie (Prefix Tree) (LC 208)
 * ---------------------------------------------------
 * 🧠 Description:
 * Implement a trie with insert, search, and startsWith operations.
 *
 * 🔍 Example:
 * Trie trie;
 * trie.Insert("apple");
 * trie.Search("apple"); // true
 * trie.Search("app");   // false
 * trie.StartsWith("app"); // true
 *
 * 🎯 Key Insight:
 * Each node stores children for next letters and a flag for word end.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * TrieNode has:
 *   - children[26] = array of TrieNode*
 *   - is_end = marks end of word
 *
 * ✅ Base Case Initialization:
 * Root is empty node
 *
 * ✅ Transition:
 * - insert: follow/create children
 * - search: follow path; return is_end
 * - startsWith: same as search but no is_end check
 *
 * 🚨 Edge Cases:
 * - Insert empty string → no-op
 * - Search for prefix of word should be false if not is_end
 *
 * ⏱️ Time Complexity:
 * - Insert/Search/StartsWith: O(L), where L = word length
 * 🧠 Space Complexity: O(n * L)
 */
class TrieNode {
public:
    TrieNode* children[26] = {};
    bool is_end = false;
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void Insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->is_end = true;
    }

    bool Search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return node->is_end;
    }

    bool StartsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return true;
    }
};

/**
 * Problem 67: Design Add and Search Words Data Structure (LC 211)
 * ----------------------------------------------------------------
 * 🧠 Description:
 * Add words to dictionary and search using '.' as a wildcard for any letter.
 *
 * 🔍 Example:
 * addWord("bad"); addWord("dad");
 * search("b..") → true
 *
 * 🎯 Key Insight:
 * Trie + DFS for '.' wildcard support
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * Same as TrieNode, add DFS for wildcard '.'
 *
 * ✅ Base Case Initialization:
 * Root initialized
 *
 * ✅ Transition:
 * - '.' → recursively try all children
 * - letter → follow trie path
 *
 * 🚨 Edge Cases:
 * - "." → match any single-char word
 * - "..." → match any 3-letter word
 *
 * ⏱️ Time Complexity:
 * - addWord: O(L)
 * - search worst-case: O(26^L)
 * 🧠 Space Complexity: O(n * L)
 */
class WordDictionary {
private:
    TrieNode* root;

    bool Dfs(TrieNode* node, const string& word, int i) {
        if (!node) return false;
        if (i == word.size()) return node->is_end;

        char c = word[i];
        if (c == '.') {
            for (auto child : node->children)
                if (Dfs(child, word, i + 1)) return true;
        } else {
            return Dfs(node->children[c - 'a'], word, i + 1);
        }
        return false;
    }

public:
    WordDictionary() { root = new TrieNode(); }

    void AddWord(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->is_end = true;
    }

    bool Search(const string& word) {
        return Dfs(root, word, 0);
    }
};

/**
 * Problem 68: Number of Connected Components in an Undirected Graph (LC 323)
 * ----------------------------------------------------------------------------
 * 🧠 Description:
 * Given `n` nodes labeled from 0 to n-1 and a list of undirected edges,
 * return the number of connected components.
 *
 * 🔍 Example:
 * Input: n = 5, edges = [[0,1],[1,2],[3,4]]
 * Output: 2
 *
 * 🎯 Key Insight:
 * Union-Find or DFS to track disjoint sets.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - parent[i] = representative of component
 *
 * ✅ Base Case Initialization:
 * Each node is its own parent
 *
 * ✅ Transition:
 * Union each edge, reduce component count
 *
 * 🚨 Edge Cases:
 * - No edges → n components
 * - Fully connected → 1 component
 *
 * ⏱️ Time Complexity: O(E α(N))
 * 🧠 Space Complexity: O(N)
 */
int Find(vector<int>& parent, int x) {
    return parent[x] == x ? x : parent[x] = Find(parent, parent[x]);
}

void Union(vector<int>& parent, int x, int y) {
    int px = Find(parent, x), py = Find(parent, y);
    if (px != py) parent[px] = py;
}

int CountComponents(int n, vector<vector<int>>& edges) {
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);
    int count = n;

    for (auto& e : edges) {
        if (Find(parent, e[0]) != Find(parent, e[1])) {
            Union(parent, e[0], e[1]);
            count--;
        }
    }

    return count;
}

/**
 * Problem 69: Count Complete Tree Nodes (LC 222)
 * -----------------------------------------------
 * 🧠 Description:
 * Count the number of nodes in a complete binary tree in less than O(n) time.
 *
 * 🔍 Example:
 * Input: [1,2,3,4,5,6]
 * Output: 6
 *
 * 🎯 Key Insight:
 * If left and right subtree heights are equal, left is full: count by formula.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - left height, right height
 *
 * ✅ Transition:
 * - if left == right: return 2^h - 1
 * - else: recursively count left + right + 1
 *
 * 🚨 Edge Cases:
 * - Null tree → return 0
 *
 * ⏱️ Time Complexity: O(log^2 n)
 * 🧠 Space Complexity: O(log n)
 */
int GetHeight(TreeNode* node, bool left) {
    int h = 0;
    while (node) {
        h++;
        node = left ? node->left : node->right;
    }
    return h;
}

int CountNodes(TreeNode* root) {
    if (!root) return 0;
    int lh = GetHeight(root, true);
    int rh = GetHeight(root, false);

    if (lh == rh) return (1 << lh) - 1;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

/**
 * Problem 70: Missing Number (LC 268)
 * -------------------------------------
 * 🧠 Description:
 * Given an array nums containing n distinct numbers in range [0, n], return the one missing number.
 *
 * 🔍 Example:
 * Input: [3,0,1]
 * Output: 2
 *
 * 🎯 Key Insight:
 * Use sum formula or XOR trick.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * total = expected sum of [0..n]
 * actual = sum of nums
 *
 * ✅ Transition:
 * missing = total - actual
 *
 * ✅ Alternative:
 * XOR all indices and values → remaining is missing
 *
 * 🚨 Edge Cases:
 * - Missing number is 0 or n
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(1)
 */
int MissingNumber(vector<int>& nums) {
    int n = nums.size();
    int total = n * (n + 1) / 2;

    int actual = accumulate(nums.begin(), nums.end(), 0);
    return total - actual;
}

/**
 * Problem 71: Course Schedule (LC 207)
 * --------------------------------------
 * 🧠 Description:
 * Given `numCourses` and a list of prerequisites, determine if it is possible to finish all courses.
 * This is equivalent to checking whether a directed graph has a cycle.
 *
 * 🔍 Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * 🎯 Key Insight:
 * Topological sort via BFS (Kahn's algorithm) or DFS cycle detection.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - indegree[i] = number of incoming edges to course i
 * - graph[i] = list of courses dependent on i
 *
 * ✅ Base Case Initialization:
 * Queue of all nodes with indegree 0
 *
 * ✅ Transition:
 * - Decrease indegree for each neighbor
 * - If indegree becomes 0, enqueue
 *
 * ✅ Iteration Order:
 * BFS
 *
 * 🚨 Edge Cases:
 * - No prerequisites → return true
 * - Self-dependency or cycle → return false
 *
 * ⏱️ Time Complexity: O(V + E)
 * 🧠 Space Complexity: O(V + E)
 */
bool CanFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (indegree[i] == 0)
            q.push(i);

    int count = 0;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        count++;

        for (int neighbor : graph[curr]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return count == numCourses;
}

/**
 * Problem 72: Course Schedule II (LC 210)
 * -----------------------------------------
 * 🧠 Description:
 * Same as Course Schedule I, but return the order in which you should take the courses.
 *
 * 🔍 Example:
 * Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 *
 * 🎯 Key Insight:
 * Use topological sort to determine valid course order.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ State Definition:
 * - graph[i] = list of courses dependent on i
 * - indegree[i] = number of prerequisites for course i
 *
 * ✅ Transition:
 * BFS to reduce indegree and build result
 *
 * ✅ Final:
 * If all nodes processed → return result; else → return empty
 *
 * 🚨 Edge Cases:
 * - No prerequisites → return [0..n-1]
 * - Cycle → return empty vector
 *
 * ⏱️ Time Complexity: O(V + E)
 * 🧠 Space Complexity: O(V + E)
 */
vector<int> FindOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> result;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        result.push_back(curr);

        for (int neighbor : graph[curr]) {
            if (--indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return result.size() == numCourses ? result : vector<int>();
}

/**
 * Problem 73: Serialize and Deserialize Binary Tree (LC 297)
 * ------------------------------------------------------------
 * 🧠 Description:
 * Design an algorithm to serialize and deserialize a binary tree.
 *
 * 🔍 Example:
 * Input tree:    1
 *               / \
 *              2   3
 *                 / \
 *                4   5
 * Output serialized: "1,2,#,#,3,4,#,#,5,#,#"
 *
 * 🎯 Key Insight:
 * Use pre-order traversal with null markers to uniquely encode structure.
 *
 * 💡 Strategy:
 * ------------------------------------------------------------
 * ✅ Serialize:
 * - Pre-order DFS with "#" for nulls
 * ✅ Deserialize:
 * - Use stringstream and recursive construction
 *
 * 🚨 Edge Cases:
 * - Empty tree → "#"
 * - Skewed trees → handle left/right recursion properly
 *
 * ⏱️ Time Complexity: O(n)
 * 🧠 Space Complexity: O(n)
 */
class Codec {
public:
    string Serialize(TreeNode* root) {
        if (!root) return "#";
        return to_string(root->val) + "," +
               Serialize(root->left) + "," +
               Serialize(root->right);
    }

    TreeNode* DeserializeHelper(istringstream& ss) {
        string val;
        getline(ss, val, ',');
        if (val == "#") return nullptr;

        TreeNode* node = new TreeNode(stoi(val));
        node->left = DeserializeHelper(ss);
        node->right = DeserializeHelper(ss);
        return node;
    }

    TreeNode* Deserialize(string data) {
        istringstream ss(data);
        return DeserializeHelper(ss);
    }
};
