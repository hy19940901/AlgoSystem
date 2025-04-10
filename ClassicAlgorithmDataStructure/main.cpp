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

/**
 * LRU Cache implementation using manually implemented doubly linked list.
 */
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


/**
 * LRU Cache implementation using std::list.
 */
class LRUCacheList {
private:
    int capacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
    mutex mtx; // Mutex for thread safety, follow up

public:
    LRUCacheList(int cap) : capacity(cap) {}

    int get(int key) {
        lock_guard<mutex> lock(mtx); // Follow up, for thread safety
        if (!cacheMap.count(key)) return -1;
        auto it = cacheMap[key];
        cacheList.splice(cacheList.begin(), cacheList, it);
        return it->second;
    }

    void put(int key, int value) {
        lock_guard<mutex> lock(mtx); // Follow up, for thread safety
        if (cacheMap.count(key)) {
            cacheList.erase(cacheMap[key]);
        } else if (cacheList.size() >= static_cast<size_t>(capacity)) {
            auto old = cacheList.back();
            cacheList.pop_back();
            cacheMap.erase(old.first);
        }

        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
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
class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity, minFreq;
    unordered_map<int, list<Node>> freqMap; // Frequency to nodes mapping
    unordered_map<int, list<Node>::iterator> keyMap; // Key to node mapping

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (!keyMap.count(key)) return -1;
        auto it = keyMap[key];
        int val = it->value, freq = it->freq;
        freqMap[freq].erase(it);
        if (freqMap[freq].empty() && freq == minFreq) minFreq++;
        freqMap[freq + 1].push_front({key, val, freq + 1});
        keyMap[key] = freqMap[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyMap.count(key)) {
            keyMap[key]->value = value;
            get(key); // Update frequency
        } else {
            if (keyMap.size() == static_cast<size_t>(capacity)) {
                auto node = freqMap[minFreq].back();
                keyMap.erase(node.key);
                freqMap[minFreq].pop_back();
            }
            freqMap[1].push_front({key, value, 1});
            keyMap[key] = freqMap[1].begin();
            minFreq = 1;
        }
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
