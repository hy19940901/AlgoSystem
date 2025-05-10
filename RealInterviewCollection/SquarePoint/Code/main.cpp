#include <sstream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <mutex>

using namespace std;
// Source: [面试经验] Squarepoint NG QR.pdf

/*
Problem 1: Newton's Method for Square Root
------------------------------------------
Implement square root function using Newton's method with a given precision.
Input: double x, int precision (number of decimal places)
Output: sqrt(x) approximated to given precision
*/

double sqrtNewton(double x, int precision) {
    if (x < 0) return -1; // invalid input
    if (x == 0 || x == 1) return x;

    double eps = pow(10, -precision);
    double guess = x / 2.0;
    while (fabs(guess * guess - x) > eps) {
        guess = (guess + x / guess) / 2.0;
    }
    return round(guess * pow(10, precision)) / pow(10, precision);
}
// Explanation:
// - Newton's method approximates root by iteratively refining guess.
// - Convergence stops when guess^2 is close enough to x (based on precision).
// - Final result is rounded to the desired number of decimal places.

/*
Problem 2: Generator Parsing with Quoted Fields
----------------------------------------------
Parse a multi-line string. Each line contains comma-separated fields.
However, fields can be quoted using double quotes, and commas inside quotes should be ignored.
Implement a generator-like function that yields a dictionary for each line.
Input: string input, char separator
Output: vector<unordered_map<string, string>> parsed lines
*/


std::vector<std::unordered_map<std::string, std::string>> parseCSVWithQuotes(const std::string& input, char sep) {
    std::vector<std::unordered_map<std::string, std::string>> result;
    std::istringstream stream(input);
    std::string line;
    std::vector<std::string> headers;
    bool header_parsed = false;

    while (std::getline(stream, line)) {
        std::vector<std::string> tokens;
        std::string token;
        bool in_quotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '"') {
                in_quotes = !in_quotes;
            } else if (c == sep && !in_quotes) {
                tokens.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        tokens.push_back(token);

        if (!header_parsed) {
            headers = tokens;
            header_parsed = true;
        } else {
            std::unordered_map<std::string, std::string> dict;
            for (size_t i = 0; i < tokens.size(); ++i) {
                if (i < headers.size())
                    dict[headers[i]] = tokens[i];
            }
            result.push_back(dict);
        }
    }

    return result;
}
// Explanation:
// - Simulates CSV parsing while respecting quoted fields.
// - Quotes allow separators inside fields to be ignored.
// - First line is parsed as headers, subsequent lines mapped as dicts.
// - Double quote toggles in/out quote state.

// Example Usage
// std::string input = "name,age\n\"Doe, John\",30\nAlice,25";
// auto parsed = parseCSVWithQuotes(input, ',');

/*
Problem 3: Expected Number of Crossings Between Two Lines
----------------------------------------------------------
You have two parallel lines, each marked with numbers 1 to n in random order.
If you connect the same numbers between lines, what is the expected number of crossings?

Mathematical insight:
- Each pair (i, j) crosses with probability 0.5 (random permutations)
- Total pairs: C(n, 2) = n * (n - 1) / 2
- Expected number of crossings = C(n, 2) * 0.5 = n(n - 1)/4
*/

int expectedCrossings(int n) {
    return n * (n - 1) / 4;
}
// Explanation:
// - For every pair (i, j), the probability of crossing is 1/2.
// - Total such pairs = n(n - 1)/2.
// - So expectation = n(n - 1)/2 * 1/2 = n(n - 1)/4.

/*
Problem 4: Probability of Segment Intersection in a Unit Square
---------------------------------------------------------------
Given four points randomly selected from a unit square, what's the probability 
that line segment AB intersects CD?

Insight:
- Assume the 4 points are uniformly chosen.
- If A, B, C, D are randomly permuted, the probability that AB and CD intersect
  is 1/3.

Mathematical Fact:
- For 4 i.i.d. uniform points in a convex shape, the probability that segment AB intersects CD is 1/3.
*/

double probabilityOfIntersection() {
    return 1.0 / 3.0;
}
// Explanation:
// - Based on known result in computational geometry.
// - For 4 uniformly distributed points in convex area (e.g. square), there are 3 ways
//   to connect disjoint pairs, and 1 of them causes intersection on average.

/*
Problem 5: Hypothesis Testing on Binary Outcomes
------------------------------------------------
You run an experiment 10,000 times with binary outcome (success/failure).
You observe p_hat (sample proportion), and want to test:
   Null Hypothesis: p = p0
   Alternative: p ≠ p0
Use z-test to decide whether observed deviation is statistically significant.

Function inputs:
- observed successes
- total trials (e.g. 10000)
- expected probability p0
- significance level alpha

Returns:
- whether null hypothesis is rejected
*/

bool hypothesisTest(int success, int total, double p0, double alpha = 0.05) {
    double p_hat = static_cast<double>(success) / total;
    double z = (p_hat - p0) / sqrt(p0 * (1 - p0) / total);
    double critical = 1.96; // For alpha = 0.05, two-tailed

    return fabs(z) > critical;
}
// Explanation:
// - Standard z-test for proportion.
// - If |z| > z_critical (based on alpha), we reject H0.
// - Can adjust critical value for one-sided tests or different alpha.

/*
Problem 1: LRU Cache (LeetCode 146, Squarepoint Onsite)
-------------------------------------------------------
Design a Least Recently Used (LRU) cache that supports the following operations:
- get(key): Retrieve the value of the key if it exists in the cache, otherwise return -1.
- put(key, value): Insert or update the key with its value. If the cache exceeds capacity,
  remove the least recently used item.

Requirements:
- Achieve O(1) time complexity for both get and put operations.
- Use a combination of `unordered_map` and `list` from STL.
*/

class LRUCache {
    int cap;
    list<pair<int, int>> cacheList; // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> map; // key -> iterator

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        auto node = map[key];
        int value = node->second;
        cacheList.erase(node);
        cacheList.push_front({key, value});
        map[key] = cacheList.begin();
        return value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            cacheList.erase(map[key]);
        } else if (cacheList.size() >= cap) {
            int lruKey = cacheList.back().first;
            cacheList.pop_back();
            map.erase(lruKey);
        }
        cacheList.push_front({key, value});
        map[key] = cacheList.begin();
    }
};

/*
Explanation:
- list keeps track of usage order (most recent at front).
- unordered_map allows fast lookup from key to list iterator.
- On put/get, update the list order and map accordingly.
- If full, evict the back (least recently used) entry.
*/

template <typename Key, typename Value>
class LRUCacheListTemplate {
private:
    size_t capacity;
    list<pair<Key, Value>> cacheList;
    unordered_map<Key, typename list<pair<Key, Value>>::iterator> cacheMap;
    mutable mutex mtx; // 保证线程安全

public:
    explicit LRUCacheListTemplate(size_t cap) : capacity(cap) {}

    // 获取值：如果 key 存在，则移动到最前并返回；否则返回默认值
    Value get(const Key& key) {
        lock_guard<mutex> lock(mtx);
        if (!cacheMap.count(key)) return Value(); // 不存在返回默认值
        auto it = cacheMap[key];
        cacheList.splice(cacheList.begin(), cacheList, it); // 移到头部
        return it->second;
    }

    // 写入值：更新已存在的 key，或插入新 key
    void put(const Key& key, const Value& value) {
        lock_guard<mutex> lock(mtx);
        if (cacheMap.count(key)) {
            cacheList.erase(cacheMap[key]); // 删除旧值
        } else if (cacheList.size() >= capacity) {
            auto old = cacheList.back(); // 淘汰最久未使用
            cacheMap.erase(old.first);
            cacheList.pop_back();
        }
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }

    // 可选：判断 key 是否存在
    bool contains(const Key& key) const {
        lock_guard<mutex> lock(mtx);
        return cacheMap.find(key) != cacheMap.end();
    }

    // 可选：清空缓存
    void clear() {
        lock_guard<mutex> lock(mtx);
        cacheList.clear();
        cacheMap.clear();
    }
};

class LRUCacheManual {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    mutex mtx; // Mutex for thread safety, follow up

    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    LRUCacheManual(int cap) : capacity(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCacheManual() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    int get(int key) {
        lock_guard<mutex> lock(mtx); // Follow up, for thread safety
        if (!cache.count(key)) return -1;
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        lock_guard<mutex> lock(mtx); // Follow up, for thread safety
        if (cache.count(key)) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);

            if (cache.size() > static_cast<size_t>(capacity)) {
                Node* tailNode = removeTail();
                cache.erase(tailNode->key);
                delete tailNode;
            }
        }
    }
};

/**
 * LRU Cache implementation using manually implemented singly linked list.
 * Note: This is inefficient (O(n) removal complexity).
 */
class LRUCacheSingleLinkedList {
private:
    struct Node {
        int key, value;
        Node* next;
        Node(int k, int v): key(k), value(v), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;

    void addToHead(Node* node) {
        node->next = head->next;
        head->next = node;
    }

    void removeTail() {
        Node* prev = head;
        while (prev->next && prev->next->next) {
            prev = prev->next;
        }
        Node* tailNode = prev->next;
        if (tailNode) {
            cache.erase(tailNode->key);
            delete tailNode;
            prev->next = nullptr;
        }
    }

public:
    LRUCacheSingleLinkedList(int cap) : capacity(cap) {
        head = new Node(-1, -1);
    }

    ~LRUCacheSingleLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    int get(int key) {
        if (!cache.count(key)) return -1;
        return cache[key]->value;
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            cache[key]->value = value;
            return;
        }
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        addToHead(newNode);

        if (cache.size() > static_cast<size_t>(capacity)) {
            removeTail();
        }
    }
};

/*
Problem 1: ATM Queue Simulation
-------------------------------
You are given a queue of people where each person needs to withdraw a certain amount of money.
There is an ATM that dispenses at most X units of money in a single transaction.
If someone can't withdraw all their money at once, they go to the end of the queue.

Input:
- vector<int> amounts: the amount of money each person needs to withdraw
- int limit: maximum amount the ATM can dispense in one transaction

Output:
- vector<int> leaveOrder: order in which people leave the queue (0-indexed)
*/

#include <queue>
#include <vector>
using namespace std;

vector<int> atmQueueOrder(const vector<int>& amounts, int limit) {
    queue<pair<int, int>> q; // {index, remaining amount}
    for (int i = 0; i < amounts.size(); ++i) {
        q.push({i, amounts[i]});
    }

    vector<int> result;
    while (!q.empty()) {
        auto [idx, amount] = q.front();
        q.pop();
        amount -= limit;
        if (amount > 0) {
            q.push({idx, amount});
        } else {
            result.push_back(idx);
        }
    }
    return result;
}

/*
Explanation:
- Use a queue to simulate the ATM line.
- Each person either finishes withdrawal and leaves, or rejoins the queue.
- Time complexity is O(n * ceil(max(amount) / limit)).
*/

/*
Problem 2: Expected Number of Loops from Connecting Noodle Ends
---------------------------------------------------------------
You are given 100 strands of spaghetti, each with 2 ends (200 free ends).
In each step, you randomly pick two free ends and connect them.
After all ends are connected, what is the expected number of loops?

Insight:
- Each loop is formed by a cycle when ends are closed.
- Known result: Expected number of loops when randomly connecting 2n endpoints is:
  --> E[#loops] = ln(2n)/2 ≈ 0.5 * ln(2n) (asymptotically)
- For 100 strands (200 ends), it's around 1.5 to 2 loops in expectation.
*/

double expectedNoodleLoops(int strands) {
    // Approximation using known result from random pairing theory
    return 0.5 * log(2.0 * strands);
}

/*
Explanation:
- Based on known result in random graph pairing.
- When 2n ends are connected randomly, expected loops ≈ 0.5 * ln(2n).
- For strands = 100, returns ~2.3.
*/


/*
Problem 1: Maximum Subsequence Sum (Subarray Variant)
------------------------------------------------------
Given an integer array, find the maximum possible sum of any **contiguous** subsequence.
This is the classic Kadane's algorithm.

Input:
- vector<int> nums
Output:
- int maxSum: maximum sum of any contiguous subarray
*/

#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int maxSubarraySum(const vector<int>& nums) {
    int current = nums[0];
    int result = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        current = max(nums[i], current + nums[i]);
        result = max(result, current);
    }
    return result;
}

/*
Explanation:
- Maintain current sum ending at index i.
- Either start new subarray at i, or extend previous one.
- Track the global maximum seen so far.
- Time: O(n), Space: O(1).
*/

/*
Problem 2: Quick Sort Implementation (Choose one sort to implement)
-------------------------------------------------------------------
Choose and implement any sorting algorithm. Here we demonstrate quicksort.
This version uses randomized pivot to avoid worst-case scenarios.
*/

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    // Randomized pivot
    int randIdx = left + rand() % (right - left + 1);
    swap(arr[randIdx], arr[right]);

    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    int mid = i + 1;
    quickSort(arr, left, mid - 1);
    quickSort(arr, mid + 1, right);
}

/*
Explanation:
- Randomly select pivot to reduce chance of O(n^2) worst case.
- Partition array around pivot.
- Recursively sort subarrays.
- Average time: O(n log n), Worst-case: O(n^2) if unrandomized.
*/

/*
Problem 3: Covariance of Dice Rolls
-----------------------------------
Roll a fair 6-sided dice 5 times. Let:
- X = number of times "1" appears
- Y = number of times "2" appears
Find Cov(X, Y).

Insight:
- Cov(X, Y) = E[XY] - E[X]E[Y]
- X, Y ~ Binomial(n=5, p=1/6)
- E[X] = E[Y] = 5 * 1/6 = 5/6
- Since X and Y are negatively correlated:
  --> Cov(X, Y) = -5/36 (result from multinomial covariance)
*/

double covarianceDiceXY() {
    return -5.0 / 36.0;
}

/*
Explanation:
- Based on multinomial distribution properties.
- Each face on dice is disjoint (mutually exclusive per trial).
- Cov(X_i, X_j) = -n * p_i * p_j if i ≠ j.
*/

/*
Problem 4: Door Puzzle on a Circular Track
-----------------------------------------
On a circular track with unknown number of doors (some open, some closed),
you can walk freely and only see or toggle the door at your current position.
Find a **deterministic strategy** that guarantees all doors are open, and
prove correctness.

Strategy:
1. Start at any door, move clockwise and count steps until you find a closed door.
2. Open it and walk back same number of steps.
3. Repeat this process in both directions.
4. When you arrive back at your start and it is open from both directions,
  then you must have opened all doors.

Key Proof:
- If there is a closed door, you will eventually open it during traversal.
- Once you return and find your original door is open from both directions,
  then you must have opened all doors.
*/


/*
Problem 1: Line Parser with Quoted Fields
------------------------------------------
You are given a string representing the contents of a document with multiple lines.
Each line contains comma-separated fields. Fields may optionally be enclosed in double quotes.
Quoted fields may contain commas that should not be used as separators.

Implement a generator-like function that processes one line at a time and returns
parsed fields for each line as a dictionary.

Input:
- string doc: document content
- char sep: field separator (e.g., ',')
Output:
- vector<unordered_map<string, string>>: parsed result per line
*/

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<string> splitWithQuotes(const string& line, char sep) {
    vector<string> result;
    string token;
    bool inQuotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == sep && !inQuotes) {
            result.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    result.push_back(token);
    return result;
}

vector<unordered_map<string, string>> parseDocument(const string& doc, char sep) {
    vector<unordered_map<string, string>> output;
    size_t start = 0;
    while (start < doc.length()) {
        size_t end = doc.find('\n', start);
        if (end == string::npos) end = doc.length();
        string line = doc.substr(start, end - start);
        vector<string> fields = splitWithQuotes(line, sep);

        unordered_map<string, string> entry;
        for (size_t i = 0; i < fields.size(); ++i) {
            entry["col" + to_string(i)] = fields[i];
        }
        output.push_back(entry);
        start = end + 1;
    }
    return output;
}

/*
Explanation:
- First split doc by line (`\n`), then split each line by separator.
- Quoted strings (with double quotes) may contain the separator.
- Use a state flag `inQuotes` to control whether commas are structural.
- Time complexity: O(total characters in doc).
*/

/*
Problem 1: Unique Ways to Build a Wall
--------------------------------------
Given the size of the wall `n` and a list of possible brick sizes,
return how many unique ways there are to build the wall by stacking bricks.

Input:
- int n: total length of the wall
- vector<int> bricks: allowed brick lengths
Output:
- int number of combinations

Assume order matters: [1,2] and [2,1] are considered different.
*/

int countWaysToBuildWall(int n, const vector<int>& bricks) {
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int b : bricks) {
            if (i - b >= 0) dp[i] += dp[i - b];
        }
    }
    return dp[n];
}

/*
Explanation:
This problem is a variation of the classic **unbounded knapsack (完全背包)** problem.
We are asked to compute the number of different ways to build a wall of total length `n`
using any combination of given brick sizes. Since the same brick can be used repeatedly,
it is modeled as a **complete permutation problem** (order matters).

- State definition:
  - dp[i] = number of ways to build a wall of length `i`.
  - dp[0] = 1 represents the base case: there is exactly 1 way to build a wall of size 0 (do nothing).

- Transition:
  - For each length i in [1, n], we try all bricks `b`:
    - If i >= b, then `dp[i] += dp[i - b]`, i.e., append brick b to all combinations that sum up to (i - b).

- Order matters:
  - Because the outer loop is on wall length `i`, and the inner loop is on `bricks`,
    it means we consider all brick orders → this computes all **permutations**.

- Time complexity:
  - O(n * m), where `n` is wall length, and `m` is number of bricks.

- Example:
  - For wall length n = 4, bricks = {1, 2}
  - All combinations: [1,1,1,1], [1,1,2], [1,2,1], [2,1,1], [2,2]
  - Total = 5 ways
*/

/*
Problem 1: Best Time to Buy and Sell Stock with Cooldown (Leetcode 309)
------------------------------------------------------------------------
You are given an array prices where prices[i] is the price of a given stock on the i-th day.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like
(buy one and sell one share of the stock multiple times) with the following restrictions:

- After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
- You may not engage in multiple transactions simultaneously (i.e., you must sell before you buy again).

Input:
- vector<int> prices: stock prices per day
Output:
- int: the maximum profit achievable

Example:
Input: prices = [1,2,3,0,2]
Output: 3
Explanation:
- Buy on day 0 (price = 1)
- Sell on day 1 (price = 2), profit = 1
- Cooldown on day 2
- Buy on day 3 (price = 0)
- Sell on day 4 (price = 2), profit = 2
- Total profit = 3
*/

#include <vector>
#include <algorithm>
using namespace std;

// Method 1: Full DP arrays
int maxProfitWithCooldown(const vector<int>& prices) {
    int n = prices.size();
    if (n == 0) return 0;

    vector<int> hold(n, 0);  // Hold a stock
    vector<int> sold(n, 0);  // Just sold a stock
    vector<int> rest(n, 0);  // Cooldown or idle

    hold[0] = -prices[0];    // First day: only option is to buy
    sold[0] = 0;             // Can't sell on first day
    rest[0] = 0;             // Or do nothing

    for (int i = 1; i < n; ++i) {
        hold[i] = max(hold[i - 1], rest[i - 1] - prices[i]);
        sold[i] = hold[i - 1] + prices[i];
        rest[i] = max(rest[i - 1], sold[i - 1]);
    }

    return max(sold[n - 1], rest[n - 1]);
}

/*
Explanation:
We define three states:
- hold[i]: max profit at day i if holding a stock
- sold[i]: profit at day i if we just sold
- rest[i]: max profit if we do nothing at day i (cooldown or idle)

Transition:
- hold[i] = max(hold[i-1], rest[i-1] - prices[i])
- sold[i] = hold[i-1] + prices[i]
- rest[i] = max(rest[i-1], sold[i-1])

Answer = max(sold[n-1], rest[n-1])

Time: O(n), Space: O(n)
*/

// Method 2: Optimized to O(1) space
int maxProfitWithCooldownOptimized(const vector<int>& prices) {
    int n = prices.size();
    if (n == 0) return 0;

    int hold = -prices[0];
    int sold = 0;
    int rest = 0;

    for (int i = 1; i < n; ++i) {
        int prevHold = hold;
        int prevSold = sold;
        int prevRest = rest;

        hold = max(prevHold, prevRest - prices[i]);
        sold = prevHold + prices[i];
        rest = max(prevRest, prevSold);
    }

    return max(sold, rest);
}

/*
Explanation:
This version compresses the DP arrays into variables.
We only store the previous day's values.

Time: O(n)
Space: O(1)
*/


/*
Problem 1: Word Break (Leetcode 139)
------------------------------------
Given a string s and a dictionary of strings wordDict,
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

You may assume that the dictionary does not contain duplicate words and all words are non-empty.

Input:
- string s: the target string
- vector<string> wordDict: list of valid dictionary words
Output:
- bool: true if s can be segmented, false otherwise

Example:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: "leetcode" -> "leet" + "code"
*/

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;  // base case: empty string can always be segmented

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

/*
Explanation:
- dp[i] means whether s[0..i-1] can be segmented using the dictionary
- Initialize dp[0] = true since empty string is trivially segmentable

Transition:
- For each position i, we check all j < i:
  if dp[j] == true and s[j..i-1] in dict → dp[i] = true

Time Complexity: O(n^2)
Space Complexity: O(n)
*/

/*
Problem 1: Meeting Room Overlap Check (Leetcode 252)
-----------------------------------------------------
Given an array of meeting time intervals where each interval is represented as [start, end],
determine if a person could attend all meetings (i.e., no two meetings overlap).

Input:
- vector<vector<int>> intervals: list of meeting time intervals [start, end)
Output:
- bool: true if no overlaps, false otherwise

Example:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
Explanation: The meetings [0,30] and [5,10] overlap.
*/

#include <vector>
#include <algorithm>
using namespace std;

bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < intervals[i - 1][1]) {
            return false; // overlap found
        }
    }
    return true;
}

/*
Explanation:
- First, sort all intervals by their start time.
- Then, for each pair of consecutive intervals, check whether the current start time is earlier than the previous end time.
- If so, an overlap exists and return false.

Time Complexity: O(n log n) for sorting
Space Complexity: O(1) if sorting in place
*/
