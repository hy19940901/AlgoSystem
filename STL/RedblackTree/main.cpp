#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Problem 1: Contains Duplicate III (LC 220)
 * Description:
 * You are given an integer array nums and two integers k and t. Return true if there are two distinct indices i and j 
 * in the array such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
 */
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long> window;
    for (int i = 0; i < nums.size(); ++i) {
        auto pos = window.lower_bound((long)nums[i] - t);
        if (pos != window.end() && *pos <= (long)nums[i] + t) {
            return true;
        }
        window.insert(nums[i]);
        if (window.size() > k) {
            window.erase(nums[i - k]);
        }
    }
    return false;
}

/**
 * Problem 2: Two Sum using map (LC 1)
 * Description:
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 */
vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> numMap;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {};
}

/**
 * Problem 3: Find All Numbers Disappeared in an Array using set (LC 448)
 * Description:
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers 
 * in the range [1, n] that do not appear in nums.
 */
vector<int> findDisappearedNumbers(vector<int>& nums) {
    set<int> numSet(nums.begin(), nums.end());
    vector<int> result;
    for (int i = 1; i <= nums.size(); ++i) {
        if (numSet.find(i) == numSet.end()) {
            result.push_back(i);
        }
    }
    return result;
}

/**
 * Problem 4: Sliding Window Maximum (LC 239)
 * Description:
 * You are given an array of integers nums, and there is a sliding window of size k which is moving from the very 
 * left of the array to the very right. Return the maximum of each window.
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    multiset<int> window;
    vector<int> result;
    for (int i = 0; i < nums.size(); ++i) {
        window.insert(nums[i]);
        if (window.size() > k) {
            window.erase(window.find(nums[i - k]));
        }
        if (window.size() == k) {
            result.push_back(*window.rbegin());
        }
    }
    return result;
}

/**
 * Problem 5: Kth Largest Element in a Stream (LC 703)
 * Description:
 * Design a class to find the kth largest element in a stream.
 */
class KthLargest {
    multiset<int> elements;
    int capacity;

public:
    KthLargest(int k, vector<int>& nums) {
        capacity = k;
        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        elements.insert(val);
        if (elements.size() > capacity) {
            elements.erase(elements.begin());
        }
        return *elements.begin();
    }
};

/**
 * Problem 6: My Calendar I (LC 729)
 * Description:
 * Implement a class to manage booking intervals. Determine if a new booking can be added without overlapping.
 */
class MyCalendar {
    map<int, int> calendar;

public:
    MyCalendar() {}

    bool book(int start, int end) {
        auto next = calendar.lower_bound(start);
        if (next != calendar.end() && next->first < end) {
            return false;
        }
        if (next != calendar.begin() && (--next)->second > start) {
            return false;
        }
        calendar[start] = end;
        return true;
    }
};

/**
 * Problem 7: Count of Smaller Numbers After Self (LC 315)
 * Description:
 * Given an array nums, return a list of integers representing the count of smaller numbers to the right of each element.
 */
vector<int> countSmaller(vector<int>& nums) {
    map<int, int> counts;
    vector<int> result(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i) {
        int count = 0;
        for (auto it = counts.begin(); it != counts.end() && it->first < nums[i]; ++it) {
            count += it->second;
        }
        result[i] = count;
        counts[nums[i]]++;
    }
    return result;
}

/**
 * Problem 8: Find Common Elements in Two Arrays
 * Description:
 * Given two integer arrays, return the common elements using set operations.
 */
vector<int> findCommonElements(vector<int>& nums1, vector<int>& nums2) {
    set<int> set1(nums1.begin(), nums1.end());
    set<int> set2(nums2.begin(), nums2.end());
    vector<int> result;
    for (int num : set1) {
        if (set2.find(num) != set2.end()) {
            result.push_back(num);
        }
    }
    return result;
}

/**
 * Problem 9: Top K Frequent Words (LC 692)
 * Description:
 * Given a list of words and an integer k, return the k most frequent words.
 */
vector<string> topKFrequentWords(vector<string>& words, int k) {
    map<string, int> wordCount;
    for (string& word : words) {
        wordCount[word]++;
    }
    vector<pair<int, string>> freqList;
    for (auto& [word, freq] : wordCount) {
        freqList.push_back({-freq, word}); // Use negative frequency for reverse sorting
    }
    sort(freqList.begin(), freqList.end());
    vector<string> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(freqList[i].second);
    }
    return result;
}

int main() {
    // Test Problem 1
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Contains Nearby Almost Duplicate: " << (containsNearbyAlmostDuplicate(nums1, 3, 0) ? "True" : "False") << endl;

    // Test Problem 2
    vector<int> nums2 = {2, 7, 11, 15};
    vector<int> result2 = twoSum(nums2, 9);
    cout << "Two Sum Indices: [" << result2[0] << ", " << result2[1] << "]" << endl;

    // Test Problem 3
    vector<int> nums3 = {4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> result3 = findDisappearedNumbers(nums3);
    cout << "Disappeared Numbers: ";
    for (int num : result3) cout << num << " ";
    cout << endl;

    // Test Problem 4
    vector<int> nums4 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> result4 = maxSlidingWindow(nums4, 3);
    cout << "Sliding Window Maximum: ";
    for (int num : result4) cout << num << " ";
    cout << endl;

    // Test Problem 5
    vector<int> nums5 = {4, 5, 8, 2};
    KthLargest kthLargest(3, nums5);
    cout << "Kth Largest after adding 3: " << kthLargest.add(3) << endl;
    cout << "Kth Largest after adding 5: " << kthLargest.add(5) << endl;

    // Test Problem 6
    MyCalendar myCalendar;
    cout << "Book [10, 20]: " << (myCalendar.book(10, 20) ? "True" : "False") << endl;
    cout << "Book [15, 25]: " << (myCalendar.book(15, 25) ? "True" : "False") << endl;

    // Test Problem 7
    vector<int> nums7 = {5, 2, 6, 1};
    vector<int> result7 = countSmaller(nums7);
    cout << "Count of Smaller Numbers After Self: ";
    for (int num : result7) cout << num << " ";
    cout << endl;

    // Test Problem 8
    vector<int> nums8a = {1, 2, 2, 1};
    vector<int> nums8b = {2, 2};
    vector<int> result8 = findCommonElements(nums8a, nums8b);
    cout << "Common Elements: ";
    for (int num : result8) cout << num << " ";
    cout << endl;

    // Test Problem 9
    vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"};
    vector<string> result9 = topKFrequentWords(words, 2);
    cout << "Top K Frequent Words: ";
    for (string& word : result9) cout << word << " ";
    cout << endl;

    return 0;
}
