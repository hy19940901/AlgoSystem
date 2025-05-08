#include <iostream>
#include <cstdint>
#include <climits>
using namespace std;

/**
 * 1acres 1, problem 1, Problem: Reverse Integer (LC 7)
 * --------------------------------
 * Description:
 * Given a signed 32-bit integer x, return x with its digits reversed. 
 * If reversing x causes overflow (exceeds signed 32-bit int range [-2^31, 2^31 - 1]), return 0.
 *
 * Example:
 * Input: x = 123
 * Output: 321
 *
 * Approach:
 * - Step 1: Initialize result = 0.
 * - Step 2: While x is not zero:
 *      - Pop the last digit by x % 10.
 *      - Update x by x / 10.
 *      - Before appending the digit, check if result will overflow after appending.
 * - Step 3: If safe, update result = result * 10 + digit.
 * - Step 4: Return result at the end.
 *
 * Explanation:
 * - We reverse the digits one by one.
 * - Before pushing a digit, check boundaries: (result > INT32_MAX/10) or (result == INT32_MAX/10 and digit > 7).
 * - Symmetric check for negative values.
 * - No extra memory (no string), purely arithmetic operation.
 *
 * Time Complexity: O(log|x|) — since we process each digit.
 * Space Complexity: O(1) — constant space used.
 */

 int reverse(int x) {
    int result = 0;  // Initialize the reversed number to 0
    while (x != 0) {
        int digit = x % 10;  // Extract the last digit of x
        x /= 10;             // Remove the last digit from x

        // Check for overflow before actually updating result
        // If result will overflow after multiplying by 10 and adding digit, return 0
        if (result > INT32_MAX / 10 || (result == INT32_MAX / 10 && digit > 7)) return 0;
        if (result < INT32_MIN / 10 || (result == INT32_MIN / 10 && digit < -8)) return 0;
        
        result = result * 10 + digit;  // Append the digit to the reversed number
    }
    return result;  // Return the final reversed number
}

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 1acres 1, problem 2, Problem: Degree of an Array (LC 697)
 * ------------------------------------
 * Description:
 * Given a non-empty array of non-negative integers, 
 * the degree is the maximum frequency of any element.
 * Find the smallest possible length of a contiguous subarray having the same degree as the entire array.
 *
 * Example:
 * Input: nums = [1,2,2,3,1,4,2]
 * Output: 6
 *
 * Approach:
 * - Step 1: Iterate once to record:
 *      - count[number] = frequency of number
 *      - first[number] = first occurrence index
 *      - last[number] = last occurrence index
 * - Step 2: Find the overall degree (max count).
 * - Step 3: For each number with frequency == degree:
 *      - Calculate subarray length = last[number] - first[number] + 1.
 *      - Update minimum length.
 *
 * Explanation:
 * - We only need to focus on numbers that contribute to the degree.
 * - To minimize subarray length, track both first and last occurrences.
 * - Single-pass collection + single-pass decision = O(n).
 *
 * Time Complexity: O(n) — two passes.
 * Space Complexity: O(n) — to store mappings.
 */

int findShortestSubArray(vector<int>& nums) {
    unordered_map<int, int> count, first;
    int degree = 0, minLength = nums.size();

    for (int i = 0; i < nums.size(); ++i) {
        if (!first.count(nums[i])) first[nums[i]] = i;  // Record first occurrence
        count[nums[i]]++;                               // Increment frequency
        
        if (count[nums[i]] > degree) {
            // Found a new higher degree
            degree = count[nums[i]];
            minLength = i - first[nums[i]] + 1;  // Start a new shortest length
        } else if (count[nums[i]] == degree) {
            // Same degree, check if subarray is shorter
            minLength = min(minLength, i - first[nums[i]] + 1);
        }
    }
    
    return minLength;
}

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * 1acres 1, problem 3, Problem: Longest Substring Without Repeating Characters (LC 3)
 * ---------------------------------------------------------------
 * Description:
 * Given a string s, find the length of the longest substring without repeating characters.
 *
 * Example:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: "abc" is the longest substring.
 *
 * Approach:
 * - Step 1: Use a hash map to track the last seen index of each character.
 * - Step 2: Use a sliding window [start, i]:
 *      - If s[i] has been seen and its last index >= start:
 *          - Move start to last index + 1.
 *      - Otherwise, update maxLength = max(maxLength, i - start + 1).
 * - Step 3: Continue scanning until end of string.
 *
 * Explanation:
 * - Sliding window dynamically adjusts based on character repetition.
 * - We never shrink the window incorrectly because start always jumps forward.
 * - Hash map allows O(1) lookup for last seen positions.
 *
 * Time Complexity: O(n) — each character visited at most twice.
 * Space Complexity: O(n) — to store character indices.
 */

 int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;  // Map to store the last index where each character was seen
    int maxLength = 0;                  // Maximum length of substring found so far
    int start = 0;                      // Start index of the current window (substring without repeats)

    for (int i = 0; i < s.length(); ++i) {
        // If the character has been seen before and is inside the current window
        if (lastSeen.count(s[i]) && lastSeen[s[i]] >= start) {
            // Move the start right after the previous occurrence of the current character
            start = lastSeen[s[i]] + 1;
        }

        // Update the last seen index of the current character
        lastSeen[s[i]] = i;

        // Update the maximum length found so far
        maxLength = max(maxLength, i - start + 1);
    }

    return maxLength;  // Return the maximum length of substring without repeating characters
}

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**
 * 1acres 2, problem 1, Problem: Course Schedule (LC 207)
 * -----------------------------------
 * Description:
 * There are a total of numCourses courses to take. 
 * Some courses have prerequisites. Find if it is possible to finish all courses.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * Approach:
 * - Step 1: Model the problem as a directed graph.
 * - Step 2: Use Topological Sort (Kahn's Algorithm):
 *     - Calculate in-degree (number of prerequisites) for each node.
 *     - Start with nodes with in-degree 0 (no prerequisites).
 *     - Remove courses one by one and reduce neighbors' in-degree.
 * - Step 3: If all courses are removed successfully (visited all nodes), return true.
 *
 * Explanation:
 * - No cycle: All nodes can be visited exactly once.
 * - Cycle detected: Some nodes will always have in-degree > 0.
 * - In simple terms, finishing all courses ⇔ graph is a DAG (Directed Acyclic Graph).
 *
 * Time Complexity: O(V + E) — V = number of courses, E = number of prerequisites
 * Space Complexity: O(V + E) — adjacency list + in-degree array
 */

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> inDegree(numCourses, 0);

    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
        inDegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (inDegree[i] == 0) q.push(i);
    }

    int visited = 0;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        visited++;
        for (int neighbor : graph[course]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    return visited == numCourses;
}

#include <iostream>
#include <vector>
using namespace std;

/**
 * 1acres 2, problem 1, Problem: Course Schedule (LC 207) - DFS Version
 * -----------------------------------------------
 * Description:
 * There are a total of numCourses courses you need to take. Some courses have prerequisites. 
 * Find if it is possible to finish all courses (no cyclic dependencies).
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * Approach:
 * - Step 1: Build a directed graph where edges represent prerequisite relationships.
 * - Step 2: Use Depth-First Search (DFS) to traverse nodes.
 *     - Maintain a visited array:
 *         - 0: unvisited
 *         - 1: visiting (currently in recursion stack)
 *         - 2: visited (already finished recursion)
 * - Step 3: For each unvisited node, start a DFS:
 *     - If we revisit a node that is marked as "visiting" (1), a cycle exists → return false.
 *     - If DFS finishes without detecting a cycle, mark the node as "visited" (2).
 * - Step 4: If all nodes can be processed without finding a cycle, return true.
 *
 * Explanation:
 * - A "back edge" in a DFS traversal (edge to an ancestor in the recursion stack) indicates a cycle.
 * - If at any time during DFS we revisit a node in the recursion path (visited == 1), it means a cycle.
 * - Otherwise, if all courses can be completed one by one without encountering cycles, it's a valid schedule.
 * - This method is intuitive for understanding the dependencies directly as recursion paths.
 *
 * Time Complexity: O(V + E) — visiting all vertices and edges
 * Space Complexity: O(V + E) — adjacency list + recursion stack
 */

bool dfs(int node, vector<vector<int>>& graph, vector<int>& visited) {
    if (visited[node] == 1) return false; // back edge detected (cycle)
    if (visited[node] == 2) return true;  // already processed

    visited[node] = 1; // mark as visiting
    for (int neighbor : graph[node]) {
        if (!dfs(neighbor, graph, visited)) return false;
    }
    visited[node] = 2; // mark as visited
    return true;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]);
    }

    vector<int> visited(numCourses, 0); // 0: unvisited, 1: visiting, 2: visited
    for (int i = 0; i < numCourses; ++i) {
        if (visited[i] == 0) {
            if (!dfs(i, graph, visited)) return false;
        }
    }
    return true;
}

#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * 1acres 2, problem 2, Problem: TTL Cache Design
 * ---------------------------
 * Description:
 * Design a TTL (Time To Live) cache:
 * - Each key has a set expiration time.
 * - System Timer triggers TTL Handler periodically to delete expired keys.
 *
 * Example:
 * Input: set("a", value, ttl=10s)
 * After 10s, "a" should be automatically deleted.
 *
 * Approach:
 * - Step 1: Use Priority Queue (Min-Heap) ordered by expiration timestamp.
 *     - Each node stores (expire_time, key).
 * - Step 2: On TTL Handler Trigger:
 *     - While heap top has expire_time <= current_time:
 *         - Pop and remove the key from the cache map.
 * - Step 3: Data Structures:
 *     - Cache: unordered_map<key, value>
 *     - Expiration Queue: priority_queue<(expire_time, key)>
 *
 * Explanation:
 * - Priority queue ensures O(log n) insertions and efficient expiry processing.
 * - Cache access remains O(1).
 * - Separation of concerns: TTL Handler only removes expired keys, does not impact cache put/get logic.
 *
 * Time Complexity:
 * - Set/Insert: O(log n) due to priority_queue.
 * - Expire Processing: O(log n) per expired key.
 * - Get: O(1)
 * Space Complexity:
 * - O(n) — number of keys.
 */

struct Entry {
    long long expireTime;
    string key;
    bool operator>(const Entry& other) const {
        return expireTime > other.expireTime;
    }
};

class TTLCache {
    unordered_map<string, int> cache;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pq;
public:
    void set(string key, int value, int ttlSeconds) {
        long long expireTime = currentTime() + ttlSeconds;
        cache[key] = value;
        pq.push({expireTime, key});
    }

    int get(string key) {
        if (cache.count(key)) return cache[key];
        return -1;
    }

    void handleTTL() {
        while (!pq.empty() && pq.top().expireTime <= currentTime()) {
            string key = pq.top().key;
            pq.pop();
            cache.erase(key);
        }
    }

    long long currentTime() {
        return time(nullptr); // seconds since epoch
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 1acres 3, problem 1, Problem: Find Top 3 Divisible by 7
 * -----------------------------------
 * Description:
 * Given an array of integers, find the top 3 largest numbers that are divisible by 7.
 * If there are less than 3 such numbers, return all of them.
 *
 * Example:
 * Input: [14, 21, 7, 35, 1, 2]
 * Output: [35, 21, 14]
 *
 * Approach:
 * - Step 1: Filter out numbers divisible by 7.
 * - Step 2: Sort the filtered numbers in descending order.
 * - Step 3: Take the first 3 elements if available.
 *
 * Explanation:
 * - Since we only care about divisibility by 7 and size constraint is small (top 3), sorting is acceptable.
 * - Alternatively, use a min-heap of size 3 to maintain top elements if optimization needed for large arrays.
 *
 * Time Complexity: O(n log n) — sorting dominates
 * Space Complexity: O(n) — filtered list storage
 */

 vector<int> largestThreeDivisibleBy7(const vector<int>& nums) {
    vector<int> divisible;
    for (int num : nums) {
        if (num % 7 == 0) {
            divisible.push_back(num);
        }
    }

    sort(divisible.begin(), divisible.end(), greater<int>());

    vector<int> result;
    for (int i = 0; i < min(3, (int)divisible.size()); ++i) {
        result.push_back(divisible[i]);
    }
    return result;
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * 1acres 3, problem 2, Problem: Diff Two Lists
 * ------------------------
 * Description:
 * Given two lists of characters, generate a "diff" representing:
 * - '.' if unchanged,
 * - '+' if added,
 * - '-' if deleted.
 *
 * Example:
 * Input: A = ['A', 'B'], B = ['A', '1', 'C']
 * Output: [('A', '.'), ('1', '+'), ('B', '-'), ('C', '+')]
 *
 * Approach:
 * - Step 1: Use two pointers to traverse both lists.
 * - Step 2: Compare characters at current pointers:
 *     - If same, mark '.' and move both pointers.
 *     - If different, prioritize insertion ('+') or deletion ('-') based on strategy.
 * - Step 3: After one list exhausted, process remaining elements.
 *
 * Explanation:
 * - This is a typical two-pointer or dynamic diff generation problem.
 * - Multiple valid diffs possible if there are multiple changes at once.
 *
 * Time Complexity: O(m + n) — where m and n are the lengths of the two lists
 * Space Complexity: O(m + n) — storing diff
 */

vector<pair<char, char>> diffLists(vector<char>& a, vector<char>& b) {
    int i = 0, j = 0;
    vector<pair<char, char>> result;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            result.push_back({a[i], '.'});
            ++i;
            ++j;
        } else {
            result.push_back({b[j], '+'});
            ++j;
        }
    }
    while (i < a.size()) {
        result.push_back({a[i], '-'});
        ++i;
    }
    while (j < b.size()) {
        result.push_back({b[j], '+'});
        ++j;
    }
    return result;
}

#include <iostream>
#include <vector>
using namespace std;

/**
 * 1acres 3, problem 3, Problem: Partition List and Find Minimal Left Length
 * ------------------------------------------------------
 * Description:
 * Given an array, partition it into left and right parts such that:
 * - Every element in left <= every element in right.
 * - Return the minimal length of the left part.
 * - Must achieve O(1) extra space.
 *
 * Example:
 * Input: [5,0,3,8,6]
 * Output: 3
 * Explanation: Left = [5,0,3], Right = [8,6]
 *
 * Approach:
 * - Step 1: Maintain two variables:
 *     - leftMax: max value seen in left part.
 *     - globalMax: max value seen so far.
 * - Step 2: Traverse array:
 *     - If current element < leftMax, extend left boundary to include this element.
 *     - Always update globalMax during traversal.
 *
 * Explanation:
 * - Key idea: Whenever an element is smaller than current leftMax, left must be extended.
 * - One pass scan, constant space tracking.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

int partitionDisjoint(vector<int>& nums) {
    int leftMax = nums[0];
    int globalMax = nums[0];
    int partitionIdx = 0;
    
    for (int i = 1; i < nums.size(); ++i) {
        globalMax = max(globalMax, nums[i]);
        if (nums[i] < leftMax) {
            partitionIdx = i;
            leftMax = globalMax;
        }
    }
    
    return partitionIdx + 1;
}

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Linked List Version
 * Find the minimal left length where all left elements <= right elements.
 */
int partitionDisjointList(ListNode* head) {
    if (!head || !head->next) return 1; // Only one node, left length is 1
    
    int leftMax = head->val;
    int globalMax = head->val;
    int partitionLength = 1; // Initial left length at least 1
    
    ListNode* curr = head->next;
    int idx = 1; // Start from second node (index 1)
    
    while (curr) {
        globalMax = max(globalMax, curr->val);
        
        if (curr->val < leftMax) {
            partitionLength = idx + 1; // Extend left boundary
            leftMax = globalMax;        // Update leftMax to current globalMax
        }
        
        curr = curr->next;
        idx++;
    }
    
    return partitionLength;
}

#include <iostream>
#include <vector>
using namespace std;

/**
 * 1acres 4, problem 1, Problem: Bomb the Bridge
 * --------------------------
 * Description:
 * You are given a bridge represented as a string of characters:
 * - 'P' represents a player.
 * - 'B' represents a bomb.
 * - '.' represents empty bridge space.
 * 
 * Players can only move rightward.
 * If they move onto a bomb ('B'), the bridge is destroyed, and they fail.
 * Determine if there is a safe way for all players to cross the bridge safely.
 *
 * Example:
 * Input: "P..B...P..."
 * Output: false
 *
 * Input: "P....P....."
 * Output: true
 *
 * Approach:
 * - Step 1: Traverse the bridge from left to right.
 * - Step 2: Track if there is a safe segment for each player.
 *     - If a player ('P') is encountered:
 *         - Check if there is a bomb ('B') before they can cross.
 * - Step 3: If a bomb lies between the player and the end, player fails.
 *
 * Explanation:
 * - Simple simulation problem.
 * - Once a player meets a bomb ahead, they fail.
 * - No need to overcomplicate: single traversal + conditional checking is enough.
 *
 * Time Complexity: O(n) — one pass through bridge string
 * Space Complexity: O(1) — constant extra space
 */

bool canCrossSafely(string bridge) {
    int n = bridge.length();
    bool danger = false;
    
    for (int i = 0; i < n; ++i) {
        if (bridge[i] == 'B') {
            danger = true;
        }
        if (bridge[i] == 'P') {
            if (danger) return false; // there was a bomb before this player
        }
    }
    return true;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * 1acres 5, problem 1, Problem: Sort Strings by Length and Alphabetically (Manual Sort)
 * -----------------------------------------------------------------
 * Description:
 * Sort a list of strings by:
 * - Ascending order of length
 * - If lengths are equal, alphabetically ignoring case
 *
 * No use of std::sort is allowed.
 *
 * Approach:
 * - Step 1: Implement manual sorting (Selection Sort):
 *     - For each position i:
 *         - Find the minimal element according to comparator.
 *         - Swap with i.
 * - Step 2: Define comparator:
 *     - Compare length first.
 *     - If equal, compare after converting both strings to lowercase.
 *
 * Explanation:
 * - Selection Sort is simple to implement and sufficient for interview demos.
 * - Comparator handles two-layer sorting priority.
 *
 * Time Complexity: O(n^2 * m) — n is number of strings, m is average string length.
 * Space Complexity: O(1) — in-place sorting
 */

string toLowerCase(const string& s) {
    string res = s;
    for (char& c : res) {
        c = tolower(c);
    }
    return res;
}

bool customCompare(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return toLowerCase(a) < toLowerCase(b);
}

void sortStringsByLengthAndAlphabet(vector<string>& words) {
    int n = words.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (customCompare(words[j], words[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(words[i], words[minIdx]);
        }
    }
}

#include <iostream>
#include <string>
using namespace std;

/**
 * 1acres 5, problem 2, Problem: LineParser Class (Streaming String Parser, Function Pointer Version)
 * -------------------------------------------------------------------------------
 * Description:
 * Design a LineParser class:
 * - Accept incoming string chunks.
 * - Whenever a complete line (ending with '\n') is found,
 *   immediately call a provided callback function (C-style function pointer).
 *
 * Constraints:
 * - No use of std::function.
 * - No use of std::bind or lambdas.
 * - Use simple function pointers for callback.
 *
 * Example:
 * - Chunks: "Hello Wo", "rld\nHow ", "are you\n"
 * - Callback will be called with:
 *     - "Hello World"
 *     - "How are you"
 *
 * Approach:
 * - Step 1: Keep an internal buffer string.
 * - Step 2: On each push:
 *     - Append chunk to buffer.
 *     - Extract lines ending with '\n' and invoke callback.
 *
 * Explanation:
 * - This matches C-style design: simple, low-overhead, portable.
 * - Good for embedded or strict C++ environments.
 *
 * Time Complexity: O(n) — process each character once
 * Space Complexity: O(n) — buffer proportional to input
 */

class LineParser {
private:
    string buffer;
    void (*callback)(const string&); // function pointer

public:
    explicit LineParser(void (*cb)(const string&)) : callback(cb) {}

    void push(const string& chunk) {
        buffer += chunk;
        size_t pos;
        while ((pos = buffer.find('\n')) != string::npos) {
            string line = buffer.substr(0, pos);
            if (callback) {
                callback(line);
            }
            buffer = buffer.substr(pos + 1);
        }
    }
};


#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

/**
 * 1acres 5, problem 3, Problem: Bridges and Bombs Game
 * --------------------------------
 * Description:
 * Two players (X and O) play on a 9x9 grid:
 * - X tries to connect left to right.
 * - O tries to connect top to bottom.
 * - Isolated cells become bombs with a 4-turn timer.
 * - Players can rescue bombs by connecting them to themselves.
 * - Bombs explode after countdown reaches 0, clearing cells.
 * - First player to connect their two sides wins.
 *
 * Approach:
 * - Step 1: Maintain:
 *     - Board grid (0: empty, 1: X, 2: O)
 *     - Bomb timers (same size as board, -1 means no bomb)
 * - Step 2: Each turn:
 *     - Player places a piece.
 *     - Rescue bombs connected to new piece.
 *     - Decrement bomb timers.
 *     - Explode bombs at 0 timer.
 *     - Identify new bombs.
 *     - Check for winning paths (DFS/BFS).
 *
 * Explanation:
 * - The trick is carefully managing bomb state transitions and turn-by-turn updates.
 * - Win-checking is a basic connected component search.
 *
 * Time Complexity: O(n^2) per turn
 * Space Complexity: O(n^2)
 */

const int N = 9;

class BridgesAndBombs {
private:
    vector<vector<int>> board;       // 0: empty, 1: X, 2: O
    vector<vector<int>> bombTimer;   // -1: no bomb, 0~4: countdown

public:
    BridgesAndBombs() {
        board = vector<vector<int>>(N, vector<int>(N, 0));
        bombTimer = vector<vector<int>>(N, vector<int>(N, -1));
    }

    void place(int row, int col, int player) {
        if (board[row][col] == 0) {
            board[row][col] = player;
        }
    }

    void decrementBombs() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (bombTimer[i][j] > 0)
                    bombTimer[i][j]--;
    }

    void explodeBombs() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (bombTimer[i][j] == 0) {
                    board[i][j] = 0;
                    bombTimer[i][j] = -1;
                }
    }

    void rescueBombs(int player) {
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] == player && !visited[i][j]) {
                    dfsRescue(i, j, player, visited);
                }
    }

    void dfsRescue(int x, int y, int player, vector<vector<bool>>& visited) {
        visited[x][y] = true;
        bombTimer[x][y] = -1; // Rescue this cell
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (!visited[nx][ny] && board[nx][ny] == player) {
                    dfsRescue(nx, ny, player, visited);
                }
            }
        }
    }

    void updateBombs() {
        vector<vector<bool>> connected(N, vector<bool>(N, false));
        // Find all connected cells
        for (int player = 1; player <= 2; ++player) {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (board[i][j] == player) {
                        dfsMark(i, j, player, connected);
                    }
        }
        // Any cell not marked becomes a bomb
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] != 0 && !connected[i][j]) {
                    bombTimer[i][j] = 4;
                }
    }

    void dfsMark(int x, int y, int player, vector<vector<bool>>& connected) {
        connected[x][y] = true;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (!connected[nx][ny] && board[nx][ny] == player) {
                    dfsMark(nx, ny, player, connected);
                }
            }
        }
    }

    bool checkWin(int player) {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        if (player == 1) { // X: left to right
            for (int i = 0; i < N; ++i) {
                if (board[i][0] == 1) {
                    q.push({i, 0});
                    visited[i][0] = true;
                }
            }
        } else { // O: top to bottom
            for (int j = 0; j < N; ++j) {
                if (board[0][j] == 2) {
                    q.push({0, j});
                    visited[0][j] = true;
                }
            }
        }

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if ((player == 1 && y == N-1) || (player == 2 && x == N-1)) return true;
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                    if (!visited[nx][ny] && board[nx][ny] == player) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
        return false;
    }
};

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 1acres 6, problem 1, Problem: Sort a List of Persons by Age and Name
 * ------------------------------------------------
 * Description:
 * Given a list of `Person` objects, where each `Person` has:
 * - `age` (integer)
 * - `name` (string)
 * 
 * Sort the list:
 * - First by ascending order of age.
 * - If ages are the same, then by ascending lexicographical order of name.
 * 
 * Constraints:
 * - Use standard library functions (e.g., std::sort).
 * - No need to implement the sorting algorithm manually.
 *
 * Approach:
 * - Step 1: Define a custom comparator for `Person` objects.
 *     - Compare `age` first.
 *     - If `age` is equal, compare `name`.
 * - Step 2: Use `std::sort` with this comparator.
 *
 * Explanation:
 * - Multi-key sorting is a very common pattern.
 * - By setting primary and secondary comparison rules clearly,
 *   the standard `std::sort` can handle it easily.
 *
 * Time Complexity: O(n log n) — typical sorting complexity
 * Space Complexity: O(1) — sorting is done in-place
 */

struct Person {
    int age;
    string name;
};

bool personComparator(const Person& a, const Person& b) {
    if (a.age != b.age) {
        return a.age < b.age; // Age ascending
    }
    return a.name < b.name;    // Name lexicographical ascending
}

void sortPersons(vector<Person>& people) {
    sort(people.begin(), people.end(), personComparator);
}

#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 1acres 6, problem 2, Problem: Socks Pairing Problem
 * --------------------------------
 * Description:
 * Given a list of socks represented as integers (colors or styles),
 * return the total number of matching pairs.
 * 
 * Each sock is represented by an integer ID.
 * A pair is two socks with the same ID.
 *
 * Example:
 * Input: [10, 20, 20, 10, 10, 30, 50, 10, 20]
 * Output: 3
 *
 * Approach:
 * - Step 1: Use a hash map to count the frequency of each sock ID.
 * - Step 2: For each sock type, the number of pairs is count / 2.
 * - Step 3: Sum up all the pairs.
 *
 * Explanation:
 * - A hash map allows O(1) insertion and lookup per sock.
 * - Dividing by 2 gives the number of complete pairs for each type.
 * - Single pass for counting, single pass for calculating total pairs.
 *
 * Time Complexity: O(n) — n is the number of socks
 * Space Complexity: O(n) — for storing counts
 */

int countSockPairs(const vector<int>& socks) {
    unordered_map<int, int> sockCount;
    for (int sock : socks) {
        sockCount[sock]++;
    }

    int pairs = 0;
    for (const auto& [sock, count] : sockCount) {
        pairs += count / 2;
    }
    return pairs;
}

#include <vector>
using namespace std;

/**
 * 1acres 6, problem 3, Problem: Robot Move Out of Boundary (Function Version)
 * -------------------------------------------------------
 * Description:
 * Given an `n x n` grid, a start position `(startRow, startCol)`, and maximum moves `maxMove`,
 * each move, the robot can move up, down, left, or right one step.
 * Find the total number of ways the robot can move out of the grid boundary within `maxMove` moves.
 *
 * Approach:
 * - Step 1: Use DFS (Depth-First Search) to explore paths.
 * - Step 2: Apply memoization (3D DP array) to cache results for (row, col, moveLeft).
 * - Step 3: Recursion:
 *     - Out of bounds → 1 valid path.
 *     - No moves left → 0.
 *     - Else, explore 4 directions and sum results.
 *
 * Explanation:
 * - DFS explores all possibilities.
 * - Memoization avoids recomputation of identical subproblems.
 * - The problem reduces to counting paths with bounded steps.
 *
 * Time Complexity: O(n² × maxMove)
 * Space Complexity: O(n² × maxMove)
 */

int dfs(int row, int col, int n, int moveLeft, vector<vector<vector<int>>>& dp) {
    if (row < 0 || row >= n || col < 0 || col >= n) {
        return 1; // Successfully moved out
    }
    if (moveLeft == 0) {
        return 0; // No moves left, still inside
    }
    if (dp[row][col][moveLeft] != -1) {
        return dp[row][col][moveLeft];
    }

    int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int totalWays = 0;
    for (auto& d : dirs) {
        int newRow = row + d[0];
        int newCol = col + d[1];
        totalWays += dfs(newRow, newCol, n, moveLeft - 1, dp);
    }
    dp[row][col][moveLeft] = totalWays;
    return totalWays;
}

int findPaths(int n, int maxMove, int startRow, int startCol) {
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(maxMove + 1, -1)));
    return dfs(startRow, startCol, n, maxMove, dp);
}

/**
 * 1acres 7, problem 1, Problem: Ultimate Tic Tac Toe (9x9 Board)
 * ------------------------------------------
 * Description:
 * - The game consists of a 9x9 board, which itself is divided into 9 small 3x3 tic-tac-toe boards.
 * - Two players, X and O, alternate turns.
 * - First move is free anywhere.
 * - After that, the move must be made within a small board determined by the last move's cell.
 * - A player wins a small board by forming a 3-in-a-row inside that 3x3 grid.
 * - A player wins the overall game by winning 3 small boards in a row horizontally, vertically, or diagonally.
 *
 * Approach:
 * 1. Represent the full board as a 9x9 2D array of players.
 * 2. Represent the current player (X or O).
 * 3. Implement a `render` method to print the current board nicely formatted.
 * 4. Implement a `getUserMove` method to accept move coordinates from the user.
 * 5. In `play`, loop turns:
 *     - Render board.
 *     - Get move input.
 *     - Validate move (check if empty).
 *     - Place the move.
 *     - Switch players.
 *
 * Explanation:
 * - The game structure mirrors real Tic Tac Toe with an additional "meta-layer" (winning small boards to win big board).
 * - This base framework focuses on setting up a playable board and turn management.
 * - Later enhancements can add:
 *     - Winning small boards detection
 *     - Winning big board detection
 *     - Move constraint enforcement
 *
 * Time Complexity: O(1) per move (fixed size)
 * Space Complexity: O(1) (fixed 9x9 board)
 */

// Enumeration to represent player types
enum class Player {
    X, O, EMPTY
};

// Struct to represent a coordinate
struct Coordinate {
    int x;
    int y;
    Coordinate(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

// Main game class
class Game {
private:
    vector<vector<Player>> board; // 9x9 board
    Player currentPlayer;         // Current player (X or O)

public:
    Game() : board(9, vector<Player>(9, Player::EMPTY)), currentPlayer(Player::X) {}

    // Render the current state of the board
    void render() {
        cout << "  a b c   d e f   g h i" << endl;
        for (int outerY = 0; outerY < 3; ++outerY) { // For each group of rows (3 groups)
            for (int innerY = 0; innerY < 3; ++innerY) { // For each row inside a small board
                cout << outerY * 3 + innerY + 1 << ' '; // Row label (1–9)
                for (int outerX = 0; outerX < 3; ++outerX) { // For each group of columns
                    for (int innerX = 0; innerX < 3; ++innerX) { // For each cell inside small board
                        Player p = board[outerX * 3 + innerX][outerY * 3 + innerY];
                        if (p == Player::X) cout << 'X';
                        else if (p == Player::O) cout << 'O';
                        else if (innerY < 2) cout << '_'; // Draw underscores for empty mid-rows
                        else cout << ' ';
                        if (innerX < 2) cout << '|'; // Separator inside small board
                    }
                    if (outerX < 2) cout << " | "; // Separator between small boards
                }
                cout << endl;
            }
            if (outerY < 2) cout << "  ------|-------|------" << endl; // Separator between large boards
        }
    }

    // Get user input for move (e.g., "a1", "f5")
    Coordinate getUserMove() {
        string text;
        getline(cin, text);
        if (text.size() < 2) return getUserMove(); // Invalid input, retry

        int x = tolower(text[0]) - 'a'; // Convert 'a'-'i' to 0–8
        int y = text[1] - '1';           // Convert '1'-'9' to 0–8

        // Clamp into valid range
        x = max(0, min(8, x));
        y = max(0, min(8, y));

        return Coordinate(x, y);
    }

    // Main gameplay loop
    void play() {
        while (true) {
            render(); // Print board

            cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << "'s move: ";
            Coordinate move = getUserMove(); // Read move

            if (board[move.x][move.y] == Player::EMPTY) { // Valid move
                board[move.x][move.y] = currentPlayer;    // Place move

                // TODO: Here, you could add small-board and big-board win checks

                // Switch player
                currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
            } else {
                cout << "Cell already occupied, try again!" << endl;
            }
        }
    }
};

#include <vector>
using namespace std;

/**
 * 1acres 8, problem 1, Problem: Match-3 消消乐游戏
 * ----------------------------
 * Description:
 * Given an 8x8 board represented as a 2D array,
 * - If three or more same-colored cells are connected horizontally or vertically, they are "cleared" (set to 0).
 * - After clearing, cells above fall down to fill empty spots.
 * - Repeat this process until no more matches can be cleared.
 *
 * Return the final state of the board.
 *
 * Approach:
 * - Step 1: Scan the board to find horizontal and vertical matches (mark them).
 * - Step 2: Clear the matched cells by setting them to 0.
 * - Step 3: Drop cells down to fill the empty spaces.
 * - Step 4: Repeat until no new matches are found.
 *
 * Explanation:
 * - The key idea is to separate the "marking" step and the "clearing" step to avoid mid-scan mutation issues.
 * - After clearing, gravity pulls non-zero cells downward.
 * - Need to loop multiple times because clearing one group may cause new matches.
 *
 * Time Complexity: O(m * n * (number of rounds))
 * Space Complexity: O(1) — modify board in-place
 */

void markMatches(vector<vector<int>>& board, vector<vector<bool>>& toClear) {
    int m = board.size();
    int n = board[0].size();

    // Horizontal matches
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n - 2; ++j) {
            int val = board[i][j];
            if (val != 0 && val == board[i][j + 1] && val == board[i][j + 2]) {
                toClear[i][j] = toClear[i][j + 1] = toClear[i][j + 2] = true;
            }
        }
    }
    // Vertical matches
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m - 2; ++i) {
            int val = board[i][j];
            if (val != 0 && val == board[i + 1][j] && val == board[i + 2][j]) {
                toClear[i][j] = toClear[i + 1][j] = toClear[i + 2][j] = true;
            }
        }
    }
}

void clearBoard(vector<vector<int>>& board, vector<vector<bool>>& toClear) {
    int m = board.size();
    int n = board[0].size();
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (toClear[i][j])
                board[i][j] = 0;
}

void applyGravity(vector<vector<int>>& board) {
    int m = board.size();
    int n = board[0].size();

    for (int j = 0; j < n; ++j) {
        int writeIdx = m - 1;
        for (int i = m - 1; i >= 0; --i) {
            if (board[i][j] != 0) {
                board[writeIdx--][j] = board[i][j];
            }
        }
        while (writeIdx >= 0) {
            board[writeIdx--][j] = 0;
        }
    }
}

void matchThreeGame(vector<vector<int>>& board) {
    int m = board.size();
    int n = board[0].size();

    while (true) {
        vector<vector<bool>> toClear(m, vector<bool>(n, false));
        markMatches(board, toClear);

        bool found = false;
        for (int i = 0; i < m && !found; ++i)
            for (int j = 0; j < n && !found; ++j)
                if (toClear[i][j]) found = true;

        if (!found) break;

        clearBoard(board, toClear);
        applyGravity(board);
    }
}

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * 1acres 9, problem 1, Problem: Split String and Count Occurrences
 * --------------------------------------------
 * Description:
 * Given a long string containing words separated by spaces,
 * split the string into individual words, and count how many times each word appears.
 *
 * Example:
 * Input: "hello world hello lucid lucid motors"
 * Output:
 * - "hello": 2
 * - "world": 1
 * - "lucid": 2
 * - "motors": 1
 *
 * Approach:
 * - Step 1: Split the input string by spaces into words.
 * - Step 2: Use an unordered_map to count occurrences of each word.
 * - Step 3: Return or process the frequency table.
 *
 * Explanation:
 * - Splitting by spaces is a standard string parsing operation.
 * - Hash map (unordered_map) allows O(1) average insert and lookup time.
 *
 * Time Complexity: O(n) — n is total length of string
 * Space Complexity: O(k) — k is number of unique words
 */

 vector<string> splitWords(const string& s) {
    vector<string> words;
    int n = s.length();
    int i = 0;
    while (i < n) {
        while (i < n && s[i] == ' ') i++; // Skip spaces
        int start = i;
        while (i < n && s[i] != ' ') i++; // Read a word
        if (start < i) {
            words.push_back(s.substr(start, i - start));
        }
    }
    return words;
}

unordered_map<string, int> countWords(const string& s) {
    unordered_map<string, int> wordCount;
    vector<string> words = splitWords(s);
    for (const string& word : words) {
        wordCount[word]++;
    }
    return wordCount;
}

string formatWordCount_manual(const string& s) {
    unordered_map<string, int> wordCount = countWords(s);
    string result;
    for (const auto& [word, count] : wordCount) {
        result += "\"" + word + "\": " + to_string(count) + "\n";
    }
    return result;
}

// using streamstring method 2
#include <sstream>
string formatWordCount_ss(const string& s) {
    unordered_map<string, int> wordCount;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        wordCount[word]++;
    }

    stringstream output;
    for (const auto& [w, count] : wordCount) {
        output << "\"" << w << "\": " << count << "\n";
    }
    return output.str();
}

/**
 * 1acres 9, problem 1, Problem: Extract Last Letter of Each Word
 * ---------------------------------------------
 * Description:
 * Given a string, extract the last letter of each word and concatenate them into a new string.
 *
 * Input Example:
 * Input: "Hello world from lucid"
 *
 * Output Example:
 * Output: "odmd"
 *
 * Approach:
 * - Traverse the string character by character.
 * - When encountering a non-space followed by a space (or end of string), collect the letter.
 *
 * Explanation:
 * - A word's last letter is identified when the next character is a space or the end of the string.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

 string extractLastLetters(const string& s) {
    string result;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] != ' ' && (i + 1 == n || s[i + 1] == ' ')) {
            result += s[i];
        }
    }
    return result;
}

#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

/**
 * 1acres 9, problem 2, Problem 40: Simplified Minesweeper
 * -----------------------------------
 * Description:
 * Implement a simplified Minesweeper board:
 * - First click determines mine placement (no mines around initial click).
 * - Reveal cells accordingly (BFS).
 *
 * Input Example:
 * Input:
 *   Initial board: 5x5 grid with all cells 'E'
 *   click = (2, 2)
 *   mineCount = 5
 *
 * Output Example:
 * Output:
 *   Board after placing mines and revealing cells (may vary due to randomness)
 *
 * Approach:
 * - Step 1: After first click, randomly place mines (excluding click area and neighbors).
 * - Step 2: Use BFS to reveal empty cells recursively.
 *
 * Explanation:
 * - Simulate Minesweeper logic.
 * - BFS reveals connected empty spaces.
 *
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void placeMines(vector<vector<char>>& board, int mines, int clickX, int clickY) {
    int m = board.size();
    int n = board[0].size();

    while (mines > 0) {
        int x = rand() % m;
        int y = rand() % n;

        bool safeZone = abs(x - clickX) <= 1 && abs(y - clickY) <= 1;
        if (board[x][y] == 'E' && !safeZone) {
            board[x][y] = 'M';
            mines--;
        }
    }
}

void bfs(vector<vector<char>>& board, int x, int y) {
    int m = board.size();
    int n = board[0].size();

    queue<pair<int, int>> q;
    q.push({x, y});

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        int mineCount = 0;
        for (int d = 0; d < 8; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'M') {
                mineCount++;
            }
        }

        if (mineCount > 0) {
            board[cx][cy] = '0' + mineCount;
        } else {
            board[cx][cy] = 'B';
            for (int d = 0; d < 8; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'E') {
                    board[nx][ny] = 'V'; // Mark visited
                    q.push({nx, ny});
                }
            }
        }
    }
}

void updateBoard(vector<vector<char>>& board, int clickX, int clickY, int mineCount) {
    if (board[clickX][clickY] == 'M') {
        board[clickX][clickY] = 'X'; // Stepped on a mine
        return;
    }

    placeMines(board, mineCount, clickX, clickY);
    bfs(board, clickX, clickY);
}