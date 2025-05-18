#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <deque>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

/**
 * 📚 Sliding Window Technique Overview
 * ====================================
 *
 * 🧠 When to Use:
 * --------------
 * The sliding window technique is ideal for problems involving:
 * - Subarrays or substrings (continuous elements).
 * - Finding max/min/sum/average over a window.
 * - Longest/shortest contiguous sequence satisfying a constraint.
 * - Counting patterns, distinct elements, or frequency comparisons.
 *
 * Look for these key phrases in problems:
 * - "contiguous subarray"
 * - "longest/shortest subarray with condition..."
 * - "sliding window of size k"
 * - "substring that contains..."
 *
 * 🔁 Common Sliding Window Patterns:
 * ----------------------------------
 *
 * 1. ✅ Fixed-size Window (e.g., window of size k)
 *    - Use when the window size is constant.
 *    - Typical use: moving max/min/sum/average over the window.
 *
 *    Template:
 *    ----------
 *    for (int right = 0; right < nums.size(); ++right) {
 *        // add nums[right] to window
 *        if (right >= k - 1) {
 *            // process window [right - k + 1, right]
 *            // remove nums[right - k + 1] if needed
 *        }
 *    }
 *
 * 2. ✅ Variable-size Window (shrinkable window)
 *    - Use when the window size depends on constraints.
 *    - Typical use: longest/shortest subarray with sum or condition.
 *
 *    Template:
 *    ----------
 *    int left = 0;
 *    for (int right = 0; right < nums.size(); ++right) {
 *        // add nums[right] to window
 *
 *        while (window violates condition) {
 *            // shrink from left
 *            left++;
 *        }
 *
 *        // update result based on window [left, right]
 *    }
 *
 * 3. ✅ Character or Frequency Count Window (Strings/Maps)
 *    - Use when comparing frequency patterns or checking anagrams.
 *    - Typically use 2 hash maps or fixed-size arrays.
 *
 *    Template:
 *    ----------
 *    unordered_map<char, int> window, target;
 *    int left = 0;
 *    for (int right = 0; right < s.size(); ++right) {
 *        // update window count
 *
 *        while (window meets criteria) {
 *            // update result if needed
 *            // shrink from left
 *            left++;
 *        }
 *    }
 *
 * 🚨 Key Points:
 * --------------
 * - Keep track of what's in the window: sum, count, max, freq, etc.
 * - Move `right` to expand, `left` to contract.
 * - Only slide `left` when constraints are violated (for variable-size).
 * - Use deque for monotonic window (for max/min tracking).
 *
 * ⏱️ Complexity:
 * --------------
 * - Time: O(n) — each element is added/removed at most once.
 * - Space: O(k) or O(n) depending on auxiliary data (deque, map, set).
 */

/**
 * Problem 1: Longest Substring Without Repeating Characters (LC 3)
 * ----------------------------------------------------------------
 * 📿 Description:
 * Given a string `s`, find the length of the longest substring without repeating characters.
 * The substring must be contiguous and contain only unique characters.
 *
 * 🔍 Example:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The longest substring without repeating characters is "abc", length 3.
 *
 * 💡 Sliding Window + Hash Map Strategy:
 * ----------------------------------------------------------------
 * - This problem requires checking all possible substrings for uniqueness.
 * - To avoid the brute-force O(n²) solution, we use the sliding window technique:
 *   ➤ Use two pointers: `left` (start of window) and `right` (end of window).
 *   ➤ Expand the window by moving `right` forward.
 *   ➤ Use a hash map to record the last index of each character seen.
 *   ➤ If a character repeats (i.e., exists in the map and its last index ≥ left), 
 *     move `left` to the right of that index to avoid duplication.
 *   ➤ At each step, compute window length as `right - left + 1`, and update the max length.
 *
 * 🧠 Edge Cases:
 * - Empty string → return 0.
 * - All characters the same → max length = 1.
 *
 * ✏️ Notes:
 * - The window always contains unique characters.
 * - `left` only moves forward, never backward, ensuring linear time complexity.
 *
 * 🗓 Time: O(n), Space: O(128) ~ O(n)
 * - Each character is visited at most twice (once by `right`, once by `left`).
 * - Hash map stores character indices (constant size for ASCII).
 */

int LengthOfLongestSubstring(string s) {
    unordered_map<char, int> char_index;
    int left = 0, max_length = 0;
    for (size_t right = 0; right < s.size(); right++) {
        if (char_index.find(s[right]) != char_index.end()) {
            left = max(left, char_index[s[right]] + 1); // Move left to avoid repeating character
        }
        char_index[s[right]] = right;
        max_length = max(max_length, static_cast<int>(right) - left + 1);
    }
    return max_length;
}

/**
 * Problem 2: Minimum Size Subarray Sum (LC 209)
 * ---------------------------------------------
 * 📿 Description:
 * Given an array of positive integers `nums` and an integer `target`, find the minimal length 
 * of a contiguous subarray of which the sum is greater than or equal to `target`.
 * If no such subarray exists, return 0 instead.
 *
 * 🔍 Example:
 * Input: nums = [2,3,1,2,4,3], target = 7
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem constraint.
 *
 * 💡 Sliding Window Strategy:
 * ---------------------------------------------
 * - Since all elements are positive, we can use a dynamic sliding window approach:
 *   ➤ Use two pointers `left` and `right` to define the current window.
 *   ➤ Move `right` to expand the window and include more elements in the sum.
 *   ➤ When the current window sum is ≥ target, try to shrink the window from the left.
 *   ➤ Each time we shrink, update the minimum length if the current window is valid.
 *
 * 🧠 Edge Cases:
 * - No valid subarray → return 0.
 * - Entire array sum < target → return 0.
 * - Single element ≥ target → return 1.
 *
 * 🗓 Time: O(n), Space: O(1)
 * - Each element is visited at most twice (once added, once removed from window).
 */

int MinSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0, min_length = INT_MAX;
    for (size_t right = 0; right < nums.size(); right++) {
        sum += nums[right];  // Expand window
        while (sum >= target) {  // Contract window
            min_length = min(min_length, static_cast<int>(right) - left + 1);
            sum -= nums[left++];
        }
    }
    return min_length == INT_MAX ? 0 : min_length;
}

/**
 * Problem 3: Sliding Window Maximum (LC 239)
 * ------------------------------------------
 * 📿 Description:
 * Given an array `nums` and an integer `k`, return the maximum value in each sliding window of size `k`.
 * The window slides one position at a time from left to right.
 *
 * 🔍 Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * Explanation:
 * - Window [1,3,-1] → max = 3
 * - Window [3,-1,-3] → max = 3
 * - Window [-1,-3,5] → max = 5
 * - Window [-3,5,3] → max = 5
 * - Window [5,3,6] → max = 6
 * - Window [3,6,7] → max = 7
 *
 * 💡 Monotonic Deque Strategy:
 * ------------------------------------------
 * - Use a double-ended queue (deque) to maintain indices of useful elements.
 * - Maintain decreasing order in the deque:
 *   ➤ Before adding a new element, remove all indices whose values are smaller.
 * - Always keep the front of the deque as the index of the current window maximum.
 * - Remove the front if it is outside the current window.
 * - After reaching window size k, record deque.front() as result.
 *
 * 🧠 Why Deque?
 * - Deque helps in efficiently maintaining a decreasing order of potential max candidates.
 * - Avoids scanning the entire window at each step.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(k)
 * - Each element is pushed and popped from the deque at most once.
 */

vector<int> MaxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    for (size_t i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == static_cast<int>(i) - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (static_cast<int>(i) >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

/**
 * Problem 4: Find All Anagrams in a String (LC 438)
 * -------------------------------------------------
 * 📿 Description:
 * Given two strings `s` and `p`, return a list of all start indices in `s` where the substring is 
 * an anagram of `p`. You may return the answer in any order.
 *
 * 🔍 Example:
 * Input: s = "cbaebabacd", p = "abc"
 * Output: [0,6]
 * Explanation:
 * - Substring s[0:3] = "cba" is an anagram of "abc"
 * - Substring s[6:9] = "bac" is an anagram of "abc"
 *
 * 💡 Sliding Window + Frequency Count Strategy:
 * -------------------------------------------------
 * - Use two fixed-length frequency arrays of size 26 (for lowercase letters only).
 *   ➤ One for the target string `p` (p_count), and one for the current window in `s` (s_count).
 * - Move a sliding window of size `p.length()` across `s`.
 *   ➤ Add new character at the right, remove old character at the left.
 * - If the two frequency arrays match, current window is an anagram → store index.
 *
 * 🧠 Edge Cases:
 * - If `s.size()` < `p.size()`, return empty result.
 * - Matching is case-sensitive, and only lowercase characters are expected.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 * - The frequency arrays are fixed size 26, regardless of input size.
 * - Each character in `s` is visited once.
 */

vector<int> FindAnagrams(string s, string p) {
    vector<int> p_count(26, 0), s_count(26, 0), result;
    if (s.size() < p.size()) return result;

    for (char c : p) p_count[c - 'a']++;
    for (size_t i = 0; i < s.size(); i++) {
        s_count[s[i] - 'a']++;
        if (static_cast<size_t>(i) >= p.size()) s_count[s[i - p.size()] - 'a']--;
        if (s_count == p_count) result.push_back(i - p.size() + 1);
    }
    return result;
}

/**
 * Problem 5: Longest Repeating Character Replacement (LC 424)
 * -----------------------------------------------------------
 * 📿 Description:
 * Given a string `s` and an integer `k`, you can replace at most `k` characters in the string
 * to make all characters in a substring the same. Return the length of the longest such substring.
 *
 * 🔍 Example:
 * Input: s = "AABABBA", k = 1
 * Output: 4
 * Explanation:
 * - Replace the one 'A' in "ABBA" to get "AAAA".
 * - Longest same-character substring after at most 1 replacement is length 4.
 *
 * 💡 Sliding Window + Frequency Count Strategy:
 * -----------------------------------------------------------
 * - Use a window and a character count array of size 26 for uppercase letters.
 * - Track the count of the most frequent character in the window (`max_count`).
 * - If window size - max_count > k → too many changes needed → shrink window from left.
 * - Always expand right side to include new characters.
 * - The longest valid window found during traversal is the result.
 *
 * 🧠 Why "window size - max_count > k"?
 * - Because only `max_count` characters need no change. The rest must be replaced (at most k).
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 * - Fixed alphabet size (26), each character visited once by both left and right pointers.
 */

int CharacterReplacement(string s, int k) {
    vector<int> count(26, 0);
    int left = 0, max_count = 0, max_length = 0;
    for (size_t right = 0; right < s.size(); right++) {
        max_count = max(max_count, ++count[s[right] - 'A']);
        while (static_cast<int>(right) - left + 1 - max_count > k) {
            count[s[left] - 'A']--;
            left++;
        }
        max_length = max(max_length, static_cast<int>(right) - left + 1);
    }
    return max_length;
}

/**
 * Problem 6: Subarrays with K Different Integers (LC 992)
 * --------------------------------------------------------
 * 📿 Description:
 * Given an array `nums` and an integer `k`, return the number of subarrays that contain 
 * exactly `k` different integers.
 *
 * 🔍 Example:
 * Input: nums = [1,2,1,2,3], k = 2
 * Output: 7
 * Explanation:
 * Subarrays with exactly 2 distinct integers: [1,2], [2,1], [1,2], [2,1,2], [1,2,3], [2,1,2,3], [2,3]
 *
 * 💡 Sliding Window with Inclusion-Exclusion Strategy:
 * --------------------------------------------------------
 * - Let `F(k)` be the number of subarrays with at most k distinct integers.
 * - Then the result is: `F(k) - F(k - 1)` to get exactly k distinct.
 * - Use two pointers and a frequency map to count subarrays with at most k distinct values.
 *   ➤ Expand window by moving `right`, and shrink from `left` when count > k.
 *   ➤ For each right-end, the number of valid subarrays is (right - left + 1).
 *
 * 🧠 Edge Cases:
 * - k > number of unique values in nums → result is 0.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 * - Each element is visited at most twice.
 * - Hash map can grow up to size of distinct numbers in nums.
 */

int AtMostKDistinct(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int left = 0, count = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        if (freq[nums[right]]++ == 0) k--;
        while (k < 0) {
            if (--freq[nums[left]] == 0) k++;
            left++;
        }
        count += right - left + 1;
    }
    return count;
}

int SubarraysWithKDistinct(vector<int>& nums, int k) {
    return AtMostKDistinct(nums, k) - AtMostKDistinct(nums, k - 1);
}

/**
 * Problem 7: Binary Subarrays With Sum (LC 930)
 * ---------------------------------------------
 * 📿 Description:
 * Given a binary array `nums` (only 0s and 1s) and an integer `goal`, return the number of
 * non-empty subarrays whose sum is exactly equal to `goal`.
 *
 * 🔍 Example:
 * Input: nums = [1,0,1,0,1], goal = 2
 * Output: 4
 * Explanation:
 * Valid subarrays: [1,0,1], [0,1,0,1], [1,0,1], [1,0,1]
 *
 * 💡 Sliding Window + Inclusion-Exclusion Strategy:
 * -------------------------------------------------------------
 * - We define two helper functions: `countAtMost(goal)` and `countAtMost(goal - 1)`
 * - The answer is `countAtMost(goal) - countAtMost(goal - 1)`:
 *   ➤ `countAtMost(x)` returns the number of subarrays with sum ≤ x.
 *   ➤ This is valid because binary elements (0 or 1) ensure monotonicity.
 * - Use two pointers and a sum variable to maintain the current window.
 *   ➤ Expand the window with `right`, shrink it from `left` when sum > goal.
 *
 * 🧠 Why Inclusion-Exclusion?
 * - To isolate the exact count of subarrays with sum == goal, subtract all subarrays
 *   with sum < goal from all subarrays with sum ≤ goal.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 * - Each element is visited at most twice by sliding window.
 * - Constant space used for sum and counters.
 */

int AtMostSum(vector<int>& nums, int goal) {
    if (goal < 0) return 0;
    int left = 0, count = 0, sum = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        sum += nums[right];
        while (sum > goal) sum -= nums[left++];
        count += right - left + 1;
    }
    return count;
}

int NumSubarraysWithSum(vector<int>& nums, int goal) {
    return AtMostSum(nums, goal) - AtMostSum(nums, goal - 1);
}

/**
 * Problem 8: Longest Subarray of 1's After Deleting One Element (LC 1493)
 * -----------------------------------------------------------------------
 * 📿 Description:
 * Given a binary array `nums`, return the length of the longest subarray of 1's 
 * you can get by deleting exactly one element (can be 0 or 1).
 *
 * 🔍 Example:
 * Input: nums = [1,1,0,1]
 * Output: 3
 * Explanation:
 * Delete the 0 to get [1,1,1], which is the longest subarray of 1's.
 *
 * 💡 Sliding Window with Zero Counter:
 * -----------------------------------------------------------------------
 * - The core idea is to maintain a window that contains at most one 0.
 *   ➤ Whenever the number of 0s exceeds 1, shrink the window from the left.
 * - The window always contains valid candidates (≤1 zero).
 * - Track the maximum window length observed.
 * - Since one element must be deleted, the final result is (window length - 1) if no 0 was removed.
 *
 * 🧠 Edge Cases:
 * - All 1s → we must still delete one → answer is length - 1.
 * - Only one element → return 0.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 * - Single pass with two pointers.
 * - Only a few integer variables used.
 */

int LongestSubarray(vector<int>& nums) {
    int left = 0, max_length = 0, zero_count = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zero_count++;
        while (zero_count > 1) {
            if (nums[left++] == 0) zero_count--;
        }
        max_length = max(max_length, static_cast<int>(right) - left);
    }
    return max_length == static_cast<int>(nums.size()) ? max_length - 1 : max_length;
}

/**
 * Problem 9: Maximum Points You Can Obtain from Cards (LC 1423)
 * -------------------------------------------------------------
 * 📿 Description:
 * Given an array `cardPoints` and an integer `k`, return the maximum score you can obtain by 
 * picking exactly `k` cards from either the beginning or the end of the array.
 *
 * 🔍 Example:
 * Input: cardPoints = [1,2,3,4,5,6,1], k = 3
 * Output: 12
 * Explanation:
 * Pick cards: [1, 6, 5] or [6,1,5] → sum = 12
 *
 * 💡 Sliding Window + Complement Subarray Strategy:
 * -------------------------------------------------------------
 * - Instead of directly picking from both ends, we flip the perspective:
 *   ➤ The `n - k` middle cards that are not picked should have the **minimum sum**.
 * - Total max = totalSum - minSum(subarray of length `n - k`)
 * - Use sliding window to find the minimum sum subarray of length (n - k).
 *
 * 🧠 Why this approach?
 * - Brute force of all pick combinations has exponential complexity.
 * - This trick reduces it to a single linear scan.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(1)
 * - One pass to compute total sum.
 * - One pass with a sliding window to find min subarray.
 */

int MaxScore(vector<int>& card_points, int k) {
    int n = card_points.size(), total_sum = accumulate(card_points.begin(), card_points.end(), 0);
    if (k == n) return total_sum;

    int min_subarray_sum = accumulate(card_points.begin(), card_points.begin() + (n - k), 0);
    int current_sum = min_subarray_sum;
    for (int i = n - k; i < n; i++) {
        current_sum += card_points[i] - card_points[i - (n - k)];
        min_subarray_sum = min(min_subarray_sum, current_sum);
    }
    return total_sum - min_subarray_sum;
}

/**
 * Problem 10: Maximum Erasure Value (LC 1695)
 * --------------------------------------------
 * 📿 Description:
 * Given an array of positive integers `nums`, return the maximum sum of any subarray
 * with all unique elements (no duplicates allowed).
 *
 * 🔍 Example:
 * Input: nums = [4,2,4,5,6]
 * Output: 17
 * Explanation:
 * The subarray [2,4,5,6] has no duplicate and maximum sum = 17.
 *
 * 💡 Sliding Window + Hash Set Strategy:
 * --------------------------------------------
 * - Use two pointers and a hash set to maintain a window with unique elements.
 * - Expand the window by moving `right`, and shrink from `left` if a duplicate is encountered.
 *   ➤ On removing from left, also subtract from current sum and erase from the set.
 * - Keep updating the maximum sum encountered during the scan.
 *
 * 🧠 Why this works?
 * - All elements are positive, so removing earlier elements only reduces sum.
 * - Maintaining uniqueness ensures the window is valid.
 *
 * ⏱️ Time: O(n)
 * 🧠 Space: O(n)
 * - Each element is inserted and erased at most once.
 * - Hash set stores at most n elements.
 */

int MaximumUniqueSubarray(vector<int>& nums) {
    unordered_set<int> unique_nums;
    int left = 0, max_sum = 0, current_sum = 0;
    for (size_t right = 0; right < nums.size(); right++) {
        while (unique_nums.count(nums[right])) {
            current_sum -= nums[left];
            unique_nums.erase(nums[left++]);
        }
        unique_nums.insert(nums[right]);
        current_sum += nums[right];
        max_sum = max(max_sum, current_sum);
    }
    return max_sum;
}

/**
 * Main Function: Test all problems
 */
int main() {
    // Test Problem 1: Longest Substring Without Repeating Characters
    cout << "Test Problem 1: Longest Substring Without Repeating Characters (LC 3) \n";
    cout << "Length: " << LengthOfLongestSubstring("abcabcbb") << " (Expected: 3)" << endl;

    // Test Problem 2: Minimum Size Subarray Sum
    cout << "Test Problem 2: Minimum Size Subarray Sum (LC 209) \n";
    vector<int> nums2 = {2, 3, 1, 2, 4, 3};
    cout << "Min Length: " << MinSubArrayLen(7, nums2) << " (Expected: 2)" << endl;

    // Test Problem 3: Sliding Window Maximum
    cout << "Test Problem 3: Sliding Window Maximum (LC 239) \n";
    vector<int> nums3 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> result3 = MaxSlidingWindow(nums3, 3);
    cout << "Max Sliding Window: ";
    for (int num : result3) cout << num << " ";
    cout << "(Expected: 3 3 5 5 6 7)" << endl;

    // Test Problem 4: Find All Anagrams in a String
    cout << "Test Problem 4: Find All Anagrams in a String (LC 438) \n";
    vector<int> result4 = FindAnagrams("cbaebabacd", "abc");
    cout << "Anagram Indices: ";
    for (int idx : result4) cout << idx << " ";
    cout << "(Expected: 0 6)" << endl;

    // Test Problem 5: Longest Repeating Character Replacement
    cout << "Test Problem 5: Longest Repeating Character Replacement (LC 424) \n";
    cout << "Longest Length: " << CharacterReplacement("AABABBA", 1) << " (Expected: 4)" << endl;

    // Test Problem 6: Subarrays with K Different Integers
    cout << "Test Problem 6: Subarrays with K Different Integers (LC 992) \n";
    vector<int> nums6 = {1, 2, 1, 2, 3};
    cout << "Subarray Count: " << SubarraysWithKDistinct(nums6, 2) << " (Expected: 7)" << endl;

    // Test Problem 7: Binary Subarrays With Sum
    cout << "Test Problem 7: Binary Subarrays With Sum (LC 930) \n";
    vector<int> nums7 = {1, 0, 1, 0, 1};
    cout << "Binary Subarrays: " << NumSubarraysWithSum(nums7, 2) << " (Expected: 4)" << endl;

    // Test Problem 8: Longest Subarray of 1's After Deleting One Element
    cout << "Test Problem 8: Longest Subarray of 1's After Deleting One Element (LC 1493) \n";
    vector<int> nums8 = {1, 1, 0, 1};
    cout << "Max Consecutive 1's: " << LongestSubarray(nums8) << " (Expected: 3)" << endl;

    // Test Problem 9: Maximum Points You Can Obtain from Cards
    cout << "Test Problem 9: Maximum Points You Can Obtain from Cards (LC 1423) \n";
    vector<int> nums9 = {1, 2, 3, 4, 5, 6, 1};
    cout << "Max Score: " << MaxScore(nums9, 3) << " (Expected: 12)" << endl;

    // Test Problem 10: Maximum Erasure Value
    cout << "Test Problem 10: Maximum Erasure Value (LC 1695) \n";
    vector<int> nums10 = {4, 2, 4, 5, 6};
    cout << "Max Erasure Value: " << MaximumUniqueSubarray(nums10) << " (Expected: 17)" << endl;

    return 0;
}
