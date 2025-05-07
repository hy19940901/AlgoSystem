#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
using namespace std;

 /**
 * Problem 1: LRU Cache (LeetCode 146)
 *
 * Design a Least Recently Used (LRU) cache that supports:
 * - `get(int key)`: Return the value of the key if it exists, otherwise return -1.
 * - `put(int key, int value)`: Insert or update the value of the key.
 *   If the cache reaches capacity, remove the least recently used key.
 *
 * Example:
 * LRUCache lru(5);
 * lru.put(1, 10);
 * lru.put(2, 20);
 * lru.put(3, 30);
 * lru.put(4, 40);
 * lru.put(5, 50);
 * cout << lru.get(1) << endl; // Output: 10
 * lru.put(6, 60); // Removes key 2
 * cout << lru.get(2) << endl; // Output: -1 (not found)
 */
/*
LRU Cache – Explanation
-----------------------
We need to support O(1) get and put operations while maintaining LRU eviction policy.
To achieve this, we combine:
1. A hashmap (key → node) for O(1) access
2. A doubly linked list to track usage order, where head is most recently used, tail is least

- On get(key): move node to head.
- On put(key, val): 
   - If key exists: update and move to head
   - If new: insert at head, and evict tail if over capacity

Why doubly linked list?
→ Allows O(1) insert and delete from both ends (vs singly which is O(n) for tail).

Why not use only hashmap?
→ Hashmap alone cannot track usage order efficiently.
*/

/**
 * LRUCacheManual
 * ---------------
 * A manual implementation of a Least Recently Used (LRU) cache using raw pointers.
 *
 * Key Concepts:
 * - A doubly linked list is used to maintain recency order (head = most recent, tail = least).
 * - An unordered_map maps keys to linked list nodes for O(1) access.
 * - Nodes are moved to the head upon access or update.
 * - When the cache exceeds capacity, the node at the tail is removed.
 * - Thread safety is ensured using std::mutex.
 *
 * Time Complexity:
 * - get / put: O(1) average
 *
 * Pitfalls:
 * - Requires careful manual memory management (new/delete).
 * - Easy to forget pointer rewiring on remove/move.
 */
class LRUCacheManual {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    mutex mtx;

    // Add a node right after dummy head
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove a node from the list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Move a node to the head (mark as recently used)
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    // Remove node before tail (least recently used)
    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    // Constructor: allocate dummy head and tail nodes
    explicit LRUCacheManual(int cap) : capacity(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    // Destructor: free all nodes in the list
    ~LRUCacheManual() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    /**
     * Retrieve a value from the cache.
     * If key exists, move node to front and return value.
     * If not found, return -1.
     */
    int get(int key) {
        lock_guard<mutex> lock(mtx);
        if (!cache.count(key)) return -1;

        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    /**
     * Insert or update a key-value pair in the cache.
     * Move to front if already exists; evict tail if over capacity.
     */
    void put(int key, int value) {
        lock_guard<mutex> lock(mtx);

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
 * LRUCacheSingleLinkedList
 * --------------------------
 * A basic (but inefficient) LRU cache implementation using a singly linked list.
 *
 * Key Concepts:
 * - A singly linked list is used to store usage order (head = most recent).
 * - An unordered_map stores key → node mapping.
 * - Tail removal is O(n), making this implementation inefficient for LRU.
 *
 * Time Complexity:
 * - get / put (worst case): O(n)
 * - Only suitable for small or educational use cases.
 */
class LRUCacheSingleLinkedList {
private:
    struct Node {
        int key, value;
        Node* next;
        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;

    // Add new node after dummy head
    void addToHead(Node* node) {
        node->next = head->next;
        head->next = node;
    }

    // Remove last node (least recently used) – O(n)
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
    explicit LRUCacheSingleLinkedList(int cap) : capacity(cap) {
        head = new Node(-1, -1); // dummy head
    }

    ~LRUCacheSingleLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    /**
     * Retrieve value by key (no recency tracking).
     * Returns -1 if key not found.
     */
    int get(int key) {
        if (!cache.count(key)) return -1;
        return cache[key]->value;
    }

    /**
     * Insert new key or update value.
     * Evict tail if over capacity. No access order maintained.
     */
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

/**
 * LRUCacheList
 * --------------
 * A clean, thread-safe LRU cache using STL containers.
 *
 * Key Concepts:
 * - std::list stores (key, value) in access order.
 * - unordered_map maps key → iterator for O(1) access and removal.
 * - list::splice is used to move elements to front in O(1).
 *
 * Time Complexity:
 * - get / put: O(1) average time
 *
 * Thread Safety:
 * - std::mutex used for concurrent access safety.
 */
class LRUCacheList {
private:
    int capacity;
    list<pair<int, int>> cacheList; // front = most recently used
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
    mutex mtx;

public:
    explicit LRUCacheList(int cap) : capacity(cap) {}

    /**
     * Retrieve value by key.
     * If key exists, move to front and return value.
     * Else, return -1.
     */
    int get(int key) {
        lock_guard<mutex> lock(mtx);
        if (!cacheMap.count(key)) return -1;

        auto it = cacheMap[key];
        cacheList.splice(cacheList.begin(), cacheList, it); // move to front
        // ✅ Efficiently moves the node `it` to the front of the list (O(1) time).
        // No memory is allocated or deallocated.
        // Internally, it only adjusts pointers — this is the key benefit of std::list.

        // 🟰 Functionally equivalent to:
        /*
            cacheList.push_front(*it);   // Create a new copy at the front
            cacheList.erase(it);         // Delete the original node
        */

        // ❗ BUT:
        // - push_front + erase = 1 copy + 1 destruction → more expensive
        // - splice = pointer manipulation only → faster, no copy or destructor call

        // 🚀 Summary:
        // - splice() is the most efficient way to reorder nodes inside std::list
        // - It keeps iterator validity and avoids memory churn
        // - Ideal for LRU cache, MRU cache, or reordering operations
        return it->second;
    }

    /**
     * Insert or update key-value pair.
     * If key exists, update value and move to front.
     * If not, insert to front and evict LRU if needed.
     */
    void put(int key, int value) {
        lock_guard<mutex> lock(mtx);

        if (cacheMap.count(key)) {
            cacheList.erase(cacheMap[key]); // erase old
        } else if (cacheList.size() >= static_cast<size_t>(capacity)) {
            auto old = cacheList.back();
            cacheMap.erase(old.first);
            cacheList.pop_back(); // remove LRU
        }

        cacheList.emplace_front(key, value); // insert new
        cacheMap[key] = cacheList.begin();   // update map
    }
};

/**
 * LRUCacheListTemplate<Key, Value>
 * --------------------------------
 * A generic, thread-safe implementation of a Least Recently Used (LRU) cache using C++ STL.
 *
 * Key Concepts:
 * - Stores key-value pairs using a doubly linked list (`std::list`) to track recency.
 * - Maintains a hashmap (`unordered_map`) for O(1) key-based access.
 * - When capacity is exceeded, evicts the least recently used item (at list's tail).
 * - Thread safety ensured using `std::mutex`.
 *
 * Time Complexity:
 * - get/put/contains/clear: O(1) average time
 *
 * Thread Safety:
 * - All public methods acquire a lock_guard on a mutable `mutex` to ensure concurrent access safety.
 */
template <typename Key, typename Value>
class LRUCacheListTemplate {
private:
    size_t capacity; // Maximum number of entries the cache can hold

    // Doubly linked list storing (key, value) pairs.
    // Front = most recently used, Back = least recently used
    list<pair<Key, Value>> cacheList;

    // Hash map from key to its corresponding iterator in the list
    unordered_map<Key, typename list<pair<Key, Value>>::iterator> cacheMap;

    // Mutex to guard against concurrent access (mutable for const methods)
    mutable mutex mtx;

public:
    // Constructor: initialize cache with a fixed capacity
    explicit LRUCacheListTemplate(size_t cap) : capacity(cap) {}

    /**
     * Retrieve a value from the cache.
     * If key exists, move the entry to the front (most recently used) and return its value.
     * If not found, return default-constructed Value().
     */
    Value get(const Key& key) {
        lock_guard<mutex> lock(mtx);
        if (!cacheMap.count(key)) return Value(); // Return default if not found

        auto it = cacheMap[key];
        // Move accessed item to the front of the list (most recently used)
        cacheList.splice(cacheList.begin(), cacheList, it);
        return it->second;
    }

    /**
     * Insert or update a key-value pair in the cache.
     * If the key already exists, update its value and move it to the front.
     * If the key is new:
     *   - Insert it at the front.
     *   - If the cache exceeds capacity, evict the least recently used entry at the back.
     */
    void put(const Key& key, const Value& value) {
        lock_guard<mutex> lock(mtx);

        // If key exists, erase the old entry from list
        if (cacheMap.count(key)) {
            cacheList.erase(cacheMap[key]);
        }
        // Evict LRU item if over capacity
        else if (cacheList.size() >= capacity) {
            auto old = cacheList.back(); // LRU entry is at the back
            cacheMap.erase(old.first);
            cacheList.pop_back();
        }

        // Insert new (or updated) entry at front (most recently used)
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }

    /**
     * Check whether a key exists in the cache.
     * Returns true if present, false otherwise.
     */
    bool contains(const Key& key) const {
        lock_guard<mutex> lock(mtx);
        return cacheMap.find(key) != cacheMap.end();
    }

    /**
     * Clear the entire cache, removing all entries.
     */
    void clear() {
        lock_guard<mutex> lock(mtx);
        cacheList.clear();
        cacheMap.clear();
    }
};

/**
 * Problem 2: Implement Trie (LeetCode 208)
 *
 * Design a Trie (prefix tree) that supports:
 * - `insert(string word)`: Inserts `word` into the trie.
 * - `search(string word)`: Returns `true` if `word` is in the trie.
 * - `startsWith(string prefix)`: Returns `true` if any word in the trie starts with `prefix`.
 *
 * Example:
 * Trie trie;
 * trie.insert("hello");
 * cout << trie.search("hello") << endl; // Output: true
 * cout << trie.startsWith("he") << endl; // Output: true
 */
/*
Trie (Prefix Tree) – Explanation
--------------------------------
A Trie allows efficient prefix search for a set of words.

Idea:
- Each node has a fixed set of children (e.g. 26 lowercase letters)
- We insert characters level by level
- A boolean flag marks the end of a word

- insert(word): Traverse or create children per character, mark end node
- search(word): Traverse and check isWord at end
- startsWith(prefix): Traverse and check path exists

Why use Trie?
→ Faster than hashmap-based word lookups for common prefix tasks.
→ O(L) time where L is length of word, regardless of number of words stored.
*/
class TrieNode {
public:
    unique_ptr<TrieNode> child[26];
    bool isWord;
    TrieNode() : isWord(false) {}
};

class Trie {
private:
    unique_ptr<TrieNode> root;
public:
    Trie() {
        root = make_unique<TrieNode>();
    }

    void insert(string word) {
        TrieNode* node = root.get();
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->child[index]) {
                node->child[index] = make_unique<TrieNode>();
            }
            node = node->child[index].get();
        }
        node->isWord = true;
    }

    bool search(string word) {
        TrieNode* node = root.get();
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->child[index]) {
                return false;
            }
            node = node->child[index].get();
        }
        return node->isWord;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root.get();
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->child[index]) {
                return false;
            }
            node = node->child[index].get();
        }
        return true;
    }
};

/**
 * Problem 3: LFU Cache (Custom Implementation)
 *
 * Design a Least Frequently Used (LFU) cache that supports:
 * - `get(int key)`: Return the value of the key if it exists, otherwise return -1.
 * - `put(int key, int value)`: Insert or update the value of the key.
 *   If the cache reaches capacity, remove the least frequently used key.
 *
 * Example:
 * LFUCache lfu(3);
 * lfu.put(1, 10);
 * lfu.put(2, 20);
 * lfu.put(3, 30);
 * cout << lfu.get(1) << endl; // Output: 10
 * lfu.put(4, 40); // Removes key 2 (least frequently used)
 * cout << lfu.get(2) << endl; // Output: -1 (not found)
 */
/*
LFU Cache – Explanation
------------------------
We need to evict the least frequently used key when full.
If multiple keys have same frequency, remove the least recently used among them.

Idea:
- keyMap: key → node (value, freq)
- freqMap: freq → doubly linked list of keys (LRU order)
- minFreq: track lowest frequency currently present

On get:
- Increase node frequency
- Move it to new freq list's front

On put:
- If key exists: update + bump freq
- If not: evict from minFreq list tail if full, insert with freq=1

Why this structure?
→ Separates frequency management (LFU) and recency within frequency (LRU),
   while preserving O(1) time via hashmap + linked list.
*/
/**
 * LFUCache
 * --------
 * A Least Frequently Used (LFU) cache implementation that supports:
 * - O(1) get(key): return value if key exists, otherwise -1.
 * - O(1) put(key, value): insert or update value; evict least frequently used key if needed.
 *
 * Design Overview:
 * - keyMap: maps key → iterator to the node in freqMap
 * - freqMap: maps frequency → list of nodes with that frequency
 * - minFreq: tracks the current minimum frequency in the cache
 *
 * Invariant:
 * - freqMap[freq] is a list to support recency within the same frequency (LRU within LFU).
 * - When cache is full, remove the last node from freqMap[minFreq] (least recent among LFU).
 *
 * Time Complexity:
 * - All operations: O(1) average
 */
class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity;                         // Maximum number of entries in the cache
    int minFreq;                          // Minimum frequency of any key currently in the cache
    unordered_map<int, list<Node>> freqMap;              // freq → list of nodes (LRU within freq)
    unordered_map<int, list<Node>::iterator> keyMap;     // key → iterator in freqMap

public:
    // Constructor: initialize with fixed capacity
    explicit LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    /**
     * Retrieve a value from the cache.
     * If key exists:
     *   - Update its frequency
     *   - Move it to the new frequency bucket (at front to keep LRU order)
     *   - Update minFreq if needed
     * If not, return -1
     */
    int get(int key) {
        if (!keyMap.count(key)) return -1;

        auto it = keyMap[key];
        int val = it->value;
        int freq = it->freq;

        // Remove node from current freq list
        freqMap[freq].erase(it);

        // If this freq list becomes empty and it's the minFreq, update minFreq
        if (freqMap[freq].empty() && freq == minFreq) {
            minFreq++;
        }

        // Insert node into new freq list (freq + 1), at front (most recent)
        freqMap[freq + 1].push_front(Node(key, val, freq + 1));
        keyMap[key] = freqMap[freq + 1].begin();

        return val;
    }

    /**
     * Insert or update a key-value pair.
     * If key exists:
     *   - Update value and promote its frequency via get()
     * If key is new:
     *   - If at capacity, evict LFU item (from freqMap[minFreq].back())
     *   - Insert with freq = 1 and reset minFreq to 1
     */
    void put(int key, int value) {
        if (capacity == 0) return;

        // Case 1: key already exists → update and increase frequency
        if (keyMap.count(key)) {
            keyMap[key]->value = value; // update value
            get(key);                   // promote frequency
            return;
        }

        // Case 2: cache full → evict LRU entry in the lowest frequency bucket
        if (keyMap.size() == static_cast<size_t>(capacity)) {
            auto node = freqMap[minFreq].back(); // least recently used in LFU
            keyMap.erase(node.key);
            freqMap[minFreq].pop_back();
        }

        // Case 3: insert new key with frequency 1
        freqMap[1].push_front(Node(key, value, 1));
        keyMap[key] = freqMap[1].begin();
        minFreq = 1; // reset minFreq to 1 for new insert
    }
};

/**
 * Problem 4: Disjoint Set Union (Union-Find)
 *
 * Implement Disjoint Set Union (Union-Find) with:
 * - `find(int x)`: Returns the representative of `x`'s set.
 * - `unite(int x, int y)`: Merges sets containing `x` and `y`.
 *
 * Example:
 * DisjointSetUnion dsu(5);
 * dsu.unite(0, 1);
 * dsu.unite(2, 3);
 * cout << dsu.find(1) << endl; // Output: Representative of set containing 1
 * cout << dsu.find(3) << endl; // Output: Representative of set containing 3
 */
/*
Disjoint Set Union (Union-Find) – Explanation
---------------------------------------------
Used to track connected components or dynamic groups.

Two core operations:
- find(x): Return root of x’s set, compress path for future speed
- union(x, y): Merge sets via root comparison

Optimizations:
- Path Compression (in find): Flatten tree height
- Union by Rank: Attach smaller tree under larger

Why needed?
→ Enables nearly O(1) operations, critical for graph algorithms like Kruskal’s MST,
   or dynamic connectivity queries.
*/
class DisjointSetUnion {
private:
    vector<int> parent, rank;

public:
    DisjointSetUnion(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

/**
 * Main Function to Test Data Structures
 */
int main() {
    // Testing manual doubly linked list implementation
    LRUCacheManual lruManual(5);
    lruManual.put(1, 10);
    lruManual.put(2, 20);
    lruManual.put(3, 30);
    lruManual.put(4, 30);
    lruManual.put(5, 30);
    cout << "Manual LRU get(2): " << lruManual.get(2) << endl;
    lruManual.put(6, 60); // Removes key 1
    cout << "Manual LRU get(1): " << lruManual.get(1) << endl; // Output: -1

    // Testing manual single linked list implementation
    LRUCacheSingleLinkedList lruSingleList(5);
    lruSingleList.put(1, 10);
    lruSingleList.put(2, 20);
    lruSingleList.put(3, 30);
    lruSingleList.put(4, 40);
    lruSingleList.put(5, 50);
    cout << "Single List LRU get(2): " << lruSingleList.get(2) << endl; // Output: 600
    lruSingleList.put(6, 60); // Removes key 2
    cout << "Single List LRU get(1): " << lruSingleList.get(1) << endl; // Output: -1

    // Testing std::list implementation
    LRUCacheList lruList(5);
    lruList.put(1, 10);
    lruList.put(2, 20);
    lruList.put(3, 30);
    lruList.put(4, 40);
    lruList.put(5, 50);
    cout << "List LRU get(2): " << lruList.get(2) << endl; // Output: 600
    lruList.put(6, 60); // Removes key 2
    cout << "List LRU get(1): " << lruList.get(1) << endl; // Output: -1

    // 示例：int -> string 类型的缓存
    LRUCacheListTemplate<int, string> lru(3);
    lru.put(1, "one");
    lru.put(2, "two");
    lru.put(3, "three");

    cout << "Get 2: " << lru.get(2) << endl; // Output: two
    lru.put(4, "four"); // 淘汰 key=1
    cout << "Get 1 (evicted): " << lru.get(1) << endl; // Output: (empty string)
    cout << "Get 3: " << lru.get(3) << endl; // Output: three

    return 0;

    // Test Trie
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hi");
    cout << "Trie Search(hello): " << trie.search("hello") << endl; // true
    cout << "Trie Search(world): " << trie.search("world") << endl; // true
    cout << "Trie Search(hell): " << trie.search("hell") << endl; // false
    cout << "Trie StartsWith(he): " << trie.startsWith("he") << endl; // true
    cout << "Trie StartsWith(wo): " << trie.startsWith("wo") << endl; // true

    // Test LFU Cache
    LFUCache lfu(3);
    lfu.put(1, 10);
    lfu.put(2, 20);
    lfu.put(3, 30);
    cout << "LFU Get(1): " << lfu.get(1) << endl; // 10
    lfu.put(4, 40); // Removes key 2 (least frequently used)
    cout << "LFU Get(2): " << lfu.get(2) << endl; // -1 (not found)
    cout << "LFU Get(3): " << lfu.get(3) << endl; // 30
    lfu.get(1); // Increase frequency of key 1
    lfu.put(5, 50); // Removes key 3 (least frequently used now)
    cout << "LFU Get(3): " << lfu.get(3) << endl; // -1 (not found)
    cout << "LFU Get(1): " << lfu.get(1) << endl; // 10

    // Test Disjoint Set Union
    DisjointSetUnion dsu(5);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    cout << "DSU Find(1): " << dsu.find(1) << endl;
    cout << "DSU Find(3): " << dsu.find(3) << endl;
    dsu.unite(1, 2);
    cout << "DSU Find(0): " << dsu.find(0) << endl; // Now 0, 1, 2, and 3 are in the same set
    return 0;

    return 0;
}
