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
 * -----------------------------------
 * 🧠 Description:
 * Design a data structure that follows the Least Recently Used (LRU) eviction policy.
 * Implement an LRUCache class with the following methods:
 * - get(key): Return the value (will always be positive) of the key if it exists, else return -1.
 * - put(key, value): Insert or update the value. If over capacity, evict the least recently used key.
 *
 * 🔍 Example:
 * Input:
 *   LRUCache lru(2);
 *   lru.put(1, 1);
 *   lru.put(2, 2);
 *   cout << lru.get(1) << endl;
 *   lru.put(3, 3);  // evicts key 2
 *   cout << lru.get(2) << endl;
 * Output:
 *   1
 *   -1
 *
 * 💡 Strategy:
 * - Use a doubly linked list to store (key, value) in access order (most recent at front).
 * - Use a hashmap to map key → list iterator for O(1) access and update.
 * - Use std::list::splice() to move accessed nodes to the front efficiently.
 *
 * ✨ Key Insight:
 *   Combining hashmap + list achieves O(1) get and put operations.
 *
 * 🚨 Edge Cases:
 * - put() on an existing key must move it to front and update value.
 * - get() on non-existent key returns -1.
 *
 * ⏱ Time: O(1) per get/put, 🧠 Space: O(capacity)
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

    int capacity_;
    std::unordered_map<int, Node*> cache_;
    Node* head_;
    Node* tail_;
    std::mutex mtx_;

    // Add a node right after dummy head
    void AddToHead(Node* node) {
        node->next = head_->next;
        node->prev = head_;
        head_->next->prev = node;
        head_->next = node;
    }

    // Remove a node from the list
    void RemoveNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Move a node to the head (mark as recently used)
    void MoveToHead(Node* node) {
        RemoveNode(node);
        AddToHead(node);
    }

    // Remove node before tail (least recently used)
    Node* RemoveTail() {
        Node* node = tail_->prev;
        RemoveNode(node);
        return node;
    }

public:
    // Constructor: allocate dummy head and tail nodes
    explicit LRUCacheManual(int cap) : capacity_(cap) {
        head_ = new Node(-1, -1);
        tail_ = new Node(-1, -1);
        head_->next = tail_;
        tail_->prev = head_;
    }

    // Destructor: free all nodes in the list
    ~LRUCacheManual() {
        Node* curr = head_;
        while (curr) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }

    /**
     * Retrieve a value from the cache.
     * If key exists, move node to front and return value.
     * If not found, return -1.
     */
    int Get(int key) {
        lock_guard<mutex> lock(mtx_);
        if (!cache_.count(key)) return -1;

        Node* node = cache_[key];
        MoveToHead(node);
        return node->value;
    }

    /**
     * Insert or update a key-value pair in the cache.
     * Move to front if already exists; evict tail if over capacity.
     */
    void Put(int key, int value) {
        lock_guard<mutex> lock(mtx_);

        if (cache_.count(key)) {
            Node* node = cache_[key];
            node->value = value;
            MoveToHead(node);
        } else {
            Node* new_node = new Node(key, value);
            cache_[key] = new_node;
            AddToHead(new_node);

            if (cache_.size() > static_cast<size_t>(capacity_)) {
                Node* tail_node = RemoveTail();
                cache_.erase(tail_node->key);
                delete tail_node;
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

    int capacity_;
    unordered_map<int, Node*> cache_;
    Node* head_;

    // Add new node after dummy head
    void AddToHead(Node* node) {
        node->next = head_->next;
        head_->next = node;
    }

    // Remove last node (least recently used) – O(n)
    void RemoveTail() {
        Node* prev = head_;
        while (prev->next && prev->next->next) {
            prev = prev->next;
        }

        Node* tail_node = prev->next;
        if (tail_node) {
            cache_.erase(tail_node->key);
            delete tail_node;
            prev->next = nullptr;
        }
    }

public:
    explicit LRUCacheSingleLinkedList(int cap) : capacity_(cap) {
        head_ = new Node(-1, -1); // dummy head
    }

    ~LRUCacheSingleLinkedList() {
        Node* curr = head_;
        while (curr) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }

    /**
     * Retrieve value by key (no recency tracking).
     * Returns -1 if key not found.
     */
    int Get(int key) {
        if (!cache_.count(key)) return -1;
        return cache_[key]->value;
    }

    /**
     * Insert new key or update value.
     * Evict tail if over capacity. No access order maintained.
     */
    void Put(int key, int value) {
        if (cache_.count(key)) {
            cache_[key]->value = value;
            return;
        }

        Node* new_node = new Node(key, value);
        cache_[key] = new_node;
        AddToHead(new_node);

        if (cache_.size() > static_cast<size_t>(capacity_)) {
            RemoveTail();
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
    struct Node {
        int key;
        int value;
        Node(int k, int v) : key(k), value(v) {}
    };

    int capacity_;
    std::list<Node> cache_list_; // front = most recently used
    std::unordered_map<int, std::list<Node>::iterator> cache_map_;
    std::mutex mtx_;

public:
    // Prevents implicit conversion from int to LRUCacheList.
    // Ensures that objects must be constructed explicitly, e.g., LRUCacheList cache(10);
    explicit LRUCacheList(int cap) : capacity_(cap) {}

    /**
     * Retrieve value by key.
     * If key exists, move to front and return value.
     * Else, return -1.
     */
    int Get(int key) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!cache_map_.count(key)) return -1;

        auto it = cache_map_[key];
        cache_list_.splice(cache_list_.begin(), cache_list_, it); // move to front

        // ✅ Efficiently moves the node `it` to the front of the list (O(1) time).
        // No memory is allocated or deallocated.
        // Internally, it only adjusts pointers — this is the key benefit of std::list.

        // 🟰 Functionally equivalent to:
        /*
            cache_list_.push_front(*it);   // Create a new copy at the front
            cache_list_.erase(it);         // Delete the original node
        */

        // ❗ BUT:
        // - push_front + erase = 1 copy + 1 destruction → more expensive
        // - splice = pointer manipulation only → faster, no copy or destructor call

        // 🚀 Summary:
        // - splice() is the most efficient way to reorder nodes inside std::list
        // - It keeps iterator validity and avoids memory churn
        // - Ideal for LRU cache, MRU cache, or reordering operations

        return it->value;
    }

    /**
     * Insert or update key-value pair.
     * If key exists, update value and move to front.
     * If not, insert to front and evict LRU if needed.
     */
    void Put(int key, int value) {
        std::lock_guard<std::mutex> lock(mtx_);

        if (cache_map_.count(key)) {
            cache_list_.erase(cache_map_[key]); // Erase old node
        } else if (cache_list_.size() >= static_cast<size_t>(capacity_)) {
            // Evict least recently used (tail)
            auto& old = cache_list_.back();
            cache_map_.erase(old.key);
            cache_list_.pop_back();
        }

        // Insert new node at front
        cache_list_.emplace_front(key, value);
        cache_map_[key] = cache_list_.begin();
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
    size_t capacity_; // Maximum number of entries the cache can hold

    // Doubly linked list storing (key, value) pairs.
    // Front = most recently used, Back = least recently used
    list<pair<Key, Value>> cache_list_;

    // Hash map from key to its corresponding iterator in the list
    unordered_map<Key, typename list<pair<Key, Value>>::iterator> cache_map_;

    // Mutex to guard against concurrent access (mutable for const methods)
    mutable mutex mtx_;

public:
    // Constructor: initialize cache with a fixed capacity
    explicit LRUCacheListTemplate(size_t cap) : capacity_(cap) {}

    /**
     * Retrieve a value from the cache.
     * If key exists, move the entry to the front (most recently used) and return its value.
     * If not found, return default-constructed Value().
     */
    Value Get(const Key& key) {
        lock_guard<mutex> lock(mtx_);
        if (!cache_map_.count(key)) return Value(); // Return default if not found

        auto it = cache_map_[key];
        // Move accessed item to the front of the list (most recently used)
        cache_list_.splice(cache_list_.begin(), cache_list_, it);
        return it->second;
    }

    /**
     * Insert or update a key-value pair in the cache.
     * If the key already exists, update its value and move it to the front.
     * If the key is new:
     *   - Insert it at the front.
     *   - If the cache exceeds capacity, evict the least recently used entry at the back.
     */
    void Put(const Key& key, const Value& value) {
        lock_guard<mutex> lock(mtx_);

        // If key exists, erase the old entry from list
        if (cache_map_.count(key)) {
            cache_list_.erase(cache_map_[key]);
        }
        // Evict LRU item if over capacity
        else if (cache_list_.size() >= capacity_) {
            auto old = cache_list_.back(); // LRU entry is at the back
            cache_map_.erase(old.first);
            cache_list_.pop_back();
        }

        // Insert new (or updated) entry at front (most recently used)
        cache_list_.emplace_front(key, value);
        cache_map_[key] = cache_list_.begin();
    }

    /**
     * Check whether a key exists in the cache.
     * Returns true if present, false otherwise.
     */
    bool Contains(const Key& key) const {
        lock_guard<mutex> lock(mtx_);
        return cache_map_.find(key) != cache_map_.end();
    }

    /**
     * Clear the entire cache, removing all entries.
     */
    void Clear() {
        lock_guard<mutex> lock(mtx_);
        cache_list_.clear();
        cache_map_.clear();
    }
};

/**
 * Problem 2: Implement Trie (LeetCode 208)
 * -----------------------------------------
 * 🧠 Description:
 * A Trie (prefix tree) supports fast insert and lookup for strings. Implement methods:
 * - insert(word): Insert a word into the trie.
 * - search(word): Return true if the exact word exists.
 * - startsWith(prefix): Return true if any word starts with the given prefix.
 *
 * 🔍 Example:
 * Input:
 *   Trie trie;
 *   trie.insert("apple");
 *   trie.search("apple");   // true
 *   trie.search("app");     // false
 *   trie.startsWith("app"); // true
 * Output:
 *   true
 *   false
 *   true
 *
 * 💡 Strategy:
 * - Use 26 children nodes for lowercase letters.
 * - Each node tracks whether it ends a word.
 *
 * ✨ Key Insight:
 * - Time complexity is proportional to word length, not total word count.
 *
 * ⏱ Time: O(L), 🧠 Space: O(N * L)
 *   where L = word length, N = number of words
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
    bool is_word;
    TrieNode() : is_word(false) {}
};

class Trie {
private:
    unique_ptr<TrieNode> root_;
public:
    Trie() {
        root_ = make_unique<TrieNode>();
    }

    void Insert(string word) {
        TrieNode* node = root_.get();
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->child[index]) {
                node->child[index] = make_unique<TrieNode>();
            }
            node = node->child[index].get();
        }
        node->is_word = true;
    }

    bool Search(string word) {
        TrieNode* node = root_.get();
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->child[index]) {
                return false;
            }
            node = node->child[index].get();
        }
        return node->is_word;
    }

    bool StartsWith(string prefix) {
        TrieNode* node = root_.get();
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
 * Problem 3: LFU Cache
 * ---------------------
 * 🧠 Description:
 * Design a Least Frequently Used (LFU) cache. Each key has a usage frequency, and when the cache
 * reaches capacity, it removes the least frequently used key. If multiple keys share the same frequency,
 * the least recently used one is removed.
 *
 * 🔍 Example:
 * Input:
 *   LFUCache lfu(2);
 *   lfu.put(1, 1);
 *   lfu.put(2, 2);
 *   cout << lfu.get(1) << endl;
 *   lfu.put(3, 3);  // evicts key 2
 *   cout << lfu.get(2) << endl;
 *   cout << lfu.get(3) << endl;
 * Output:
 *   1
 *   -1
 *   3
 *
 * 💡 Strategy:
 * - key_map: key → node iterator
 * - freq_map: freq → list of nodes (LRU within each freq)
 * - min_freq: track minimum frequency
 *
 * ✨ Key Insight:
 * - LFU = Frequency Bucket + LRU Order
 *
 * ⏱ Time: O(1), 🧠 Space: O(capacity)
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

    int capacity_;                         // Maximum number of entries in the cache
    int min_freq_;                          // Minimum frequency of any key currently in the cache
    unordered_map<int, list<Node>> freq_map_;              // freq → list of nodes (LRU within freq)
    unordered_map<int, list<Node>::iterator> key_map_;     // key → iterator in freqMap

public:
    // Constructor: initialize with fixed capacity
    explicit LFUCache(int capacity) : capacity_(capacity), min_freq_(0) {}

    /**
     * Retrieve a value from the cache.
     * If key exists:
     *   - Update its frequency
     *   - Move it to the new frequency bucket (at front to keep LRU order)
     *   - Update minFreq if needed
     * If not, return -1
     */
    int Get(int key) {
        if (!key_map_.count(key)) return -1;

        auto it = key_map_[key];
        int val = it->value;
        int freq = it->freq;

        // Remove node from current freq list
        freq_map_[freq].erase(it);

        // If this freq list becomes empty and it's the minFreq, update minFreq
        if (freq_map_[freq].empty() && freq == min_freq_) {
            min_freq_++;
        }

        // Insert node into new freq list (freq + 1), at front (most recent)
        freq_map_[freq + 1].push_front(Node(key, val, freq + 1));
        key_map_[key] = freq_map_[freq + 1].begin();

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
    void Put(int key, int value) {
        if (capacity_ == 0) return;

        // Case 1: key already exists → update and increase frequency
        if (key_map_.count(key)) {
            key_map_[key]->value = value; // update value
            Get(key);                   // promote frequency
            return;
        }

        // Case 2: cache full → evict LRU entry in the lowest frequency bucket
        if (key_map_.size() == static_cast<size_t>(capacity_)) {
            auto node = freq_map_[min_freq_].back(); // least recently used in LFU
            key_map_.erase(node.key);
            freq_map_[min_freq_].pop_back();
        }

        // Case 3: insert new key with frequency 1
        freq_map_[1].push_front(Node(key, value, 1));
        key_map_[key] = freq_map_[1].begin();
        min_freq_ = 1; // reset min_freq_ to 1 for new insert
    }
};

/**
 * Problem 4: Disjoint Set Union (Union-Find)
 * -------------------------------------------
 * 🧠 Description:
 * Implement a disjoint-set data structure with the following operations:
 * - find(x): Return representative of x's set
 * - unite(x, y): Union the sets that contain x and y
 *
 * 🔍 Example:
 * Input:
 *   DisjointSetUnion dsu(5);
 *   dsu.unite(0, 1);
 *   dsu.unite(2, 3);
 *   cout << dsu.find(1) << endl;
 *   cout << dsu.find(3) << endl;
 * Output:
 *   (representatives of sets)
 *
 * 💡 Strategy:
 * - Use path compression in find().
 * - Use union by rank to keep tree shallow.
 *
 * ✨ Key Insight:
 * - Critical in Kruskal's MST, connectivity, dynamic components.
 *
 * ⏱ Time: O(α(N)) per operation, 🧠 Space: O(N)
 *   (α(N) is the inverse Ackermann function, nearly constant)
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
    vector<int> parent_, rank_;

public:
    DisjointSetUnion(int n) {
        parent_.resize(n);
        rank_.resize(n, 0);
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }

    int Find(int x) {
        if (parent_[x] != x) {
            parent_[x] = Find(parent_[x]); // Path compression
        }
        return parent_[x];
    }

    void Unite(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        if (root_x != root_y) {
            if (rank_[root_x] > rank_[root_y]) {
                parent_[root_y] = root_x;
            } else if (rank_[root_x] < rank_[root_y]) {
                parent_[root_x] = root_y;
            } else {
                parent_[root_y] = root_x;
                rank_[root_x]++;
            }
        }
    }
};

/**
 * Main Function to Test Data Structures
 */
int main() {
    // Testing manual doubly linked list implementation
    LRUCacheManual lru_manual(5);
    lru_manual.Put(1, 10);
    lru_manual.Put(2, 20);
    lru_manual.Put(3, 30);
    lru_manual.Put(4, 30);
    lru_manual.Put(5, 30);
    cout << "Manual LRU get(2): " << lru_manual.Get(2) << endl;
    lru_manual.Put(6, 60); // Removes key 1
    cout << "Manual LRU get(1): " << lru_manual.Get(1) << endl; // Output: -1

    // Testing manual single linked list implementation
    LRUCacheSingleLinkedList lru_single_list(5);
    lru_single_list.Put(1, 10);
    lru_single_list.Put(2, 20);
    lru_single_list.Put(3, 30);
    lru_single_list.Put(4, 40);
    lru_single_list.Put(5, 50);
    cout << "Single List LRU Get(2): " << lru_single_list.Get(2) << endl; // Output: 600
    lru_single_list.Put(6, 60); // Removes key 2
    cout << "Single List LRU Get(1): " << lru_single_list.Get(1) << endl; // Output: -1

    // Testing std::list implementation
    LRUCacheList lru_list(5);
    lru_list.Put(1, 10);
    lru_list.Put(2, 20);
    lru_list.Put(3, 30);
    lru_list.Put(4, 40);
    lru_list.Put(5, 50);
    cout << "List LRU Get(2): " << lru_list.Get(2) << endl; // Output: 600
    lru_list.Put(6, 60); // Removes key 2
    cout << "List LRU Get(1): " << lru_list.Get(1) << endl; // Output: -1

    // 示例：int -> string 类型的缓存
    LRUCacheListTemplate<int, string> lru(3);
    lru.Put(1, "one");
    lru.Put(2, "two");
    lru.Put(3, "three");

    cout << "Get 2: " << lru.Get(2) << endl; // Output: two
    lru.Put(4, "four"); // 淘汰 key=1
    cout << "Get 1 (evicted): " << lru.Get(1) << endl; // Output: (empty string)
    cout << "Get 3: " << lru.Get(3) << endl; // Output: three

    return 0;

    // Test Trie
    Trie trie;
    trie.Insert("hello");
    trie.Insert("world");
    trie.Insert("hi");
    cout << "Trie Search(hello): " << trie.Search("hello") << endl; // true
    cout << "Trie Search(world): " << trie.Search("world") << endl; // true
    cout << "Trie Search(hell): " << trie.Search("hell") << endl; // false
    cout << "Trie StartsWith(he): " << trie.StartsWith("he") << endl; // true
    cout << "Trie StartsWith(wo): " << trie.StartsWith("wo") << endl; // true

    // Test LFU Cache
    LFUCache lfu(3);
    lfu.Put(1, 10);
    lfu.Put(2, 20);
    lfu.Put(3, 30);
    cout << "LFU Get(1): " << lfu.Get(1) << endl; // 10
    lfu.Put(4, 40); // Removes key 2 (least frequently used)
    cout << "LFU Get(2): " << lfu.Get(2) << endl; // -1 (not found)
    cout << "LFU Get(3): " << lfu.Get(3) << endl; // 30
    lfu.Get(1); // Increase frequency of key 1
    lfu.Put(5, 50); // Removes key 3 (least frequently used now)
    cout << "LFU Get(3): " << lfu.Get(3) << endl; // -1 (not found)
    cout << "LFU Get(1): " << lfu.Get(1) << endl; // 10

    // Test Disjoint Set Union
    DisjointSetUnion dsu(5);
    dsu.Unite(0, 1);
    dsu.Unite(2, 3);
    cout << "DSU Find(1): " << dsu.Find(1) << endl;
    cout << "DSU Find(3): " << dsu.Find(3) << endl;
    dsu.Unite(1, 2);
    cout << "DSU Find(0): " << dsu.Find(0) << endl; // Now 0, 1, 2, and 3 are in the same set

    return 0;
}
