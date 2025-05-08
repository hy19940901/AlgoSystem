#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// OA 11 Delete an item in a linked list
// 1->2->3->4->5->NULL, and get a value 3, then 1->2->4->5->NULL
struct node {
    int data;
    struct node *next;
};

static void delete_item(struct node **root, int value) {
    struct node *temp = *root, *prev = NULL;

    // If head node itself holds the value to be deleted
    if (temp != NULL && temp->data == value) {
        *root = temp->next; // Change head
        free(temp);         // Free old head
        return;
    }

    // Search for the value to be deleted
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If value was not present
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}

// OA 12 Air Invaders Problem
//Define a Plane struct to store the time each plane will reach the ground
typedef struct {
    double timeToLand; // Time in seconds before the plane hits the ground
} Plane;

// Comparison function for qsort: sort planes by timeToLand in ascending order
int comparePlanes(const void* a, const void* b) {
    double t1 = ((Plane*)a)->timeToLand;
    double t2 = ((Plane*)b)->timeToLand;
    if (t1 < t2) return -1;
    else if (t1 > t2) return 1;
    else return 0;
}

/**
 * Returns the maximum number of planes that can be shot down before any of them lands.
 *
 * @param startHeight_count The number of planes (length of the startHeight array)
 * @param startHeight Array of initial heights of the planes
 * @param descentRate_count The number of planes (length of the descentRate array)
 * @param descentRate Array of descent rates (distance each plane descends per second)
 * @return Maximum number of planes that can be destroyed before one lands
 */
int maxPlanes(int startHeight_count, int* startHeight, int descentRate_count, int* descentRate) {
    int n = startHeight_count;
    Plane* planes = (Plane*)malloc(sizeof(Plane) * n);

    // Calculate time to land for each plane
    for (int i = 0; i < n; ++i) {
        planes[i].timeToLand = (double)startHeight[i] / descentRate[i];
    }

    // Sort planes by time to land (earliest landing plane first)
    qsort(planes, n, sizeof(Plane), comparePlanes);

    int count = 0;
    // Try to shoot down one plane per second
    for (int i = 0; i < n; ++i) {
        // If the current plane will land after time i, we can shoot it
        if (planes[i].timeToLand > i) {
            count++;
        } else {
            break;
        }
    }

    free(planes);
    return count;
}

// follow up, if shoot one plane, then generate a new plane, how do we use it?
// 随机生成一架新飞机
struct ComparePlaneNew {
    bool operator()(const Plane& a, const Plane& b) {
        return a.timeToLand > b.timeToLand;  // 小的优先
    }
};

Plane generateNewPlane() {
    int height = rand() % 500 + 100;     // 100 ~ 599
    int rate = rand() % 20 + 1;          // 1 ~ 20
    Plane p;
    p.timeToLand = static_cast<double>(height) / rate;
    return p;
}

// 主逻辑：每秒打掉一架最早落地的飞机，并生成一架新的
int maxPlanesShot(int startHeight_count, int* startHeight, int descentRate_count, int* descentRate) {
    priority_queue<Plane, vector<Plane>, ComparePlaneNew> minHeap; //时间复杂度logn

    // 初始化飞机
    for (int i = 0; i < startHeight_count; ++i) {
        Plane p;
        p.timeToLand = static_cast<double>(startHeight[i]) / descentRate[i];
        minHeap.push(p);
    }

    int time = 0;
    int count = 0;

    while (!minHeap.empty()) {
        Plane current = minHeap.top();

        // 有飞机落地，结束
        if (current.timeToLand <= time) {
            break;
        }

        minHeap.pop();  // 打掉当前飞机
        count++;
        time++;

        Plane newPlane = generateNewPlane();
        minHeap.push(newPlane);
    }

    return count;
}

/*
 * oa 12: Counting Bits
 *
 * Given an integer n, determine the following:
 *
 * 1. How many 1-bits are in its binary representation?
 * 2. The number n's binary representation has k significant bits indexed from 1 to k.
 *    What are the respective positions of each 1-bit, in ascending order (from left to right)?
 *
 * Return an array with the following format:
 *    [count, pos1, pos2, ..., posN]
 * Where:
 *    - count is the total number of 1-bits
 *    - pos1 to posN are the 1-based positions of each 1-bit from left to right
 *
 * Example:
 * Input:  n = 161  (binary: 10100001)
 * Output: [3, 1, 3, 8]
 */
int* getOneBits(int n, int* result_count) {
    int bits[32]; // 存储所有1的位置，最多32位
    int total_bits = 0;
    int temp = n;

    // 先求出 n 的有效二进制位数
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }

    // 从高位（左边）开始扫描，记录第几个是1
    int pos = 1; // 表示当前是第几个有效位（从左往右，第一个1是第1位）
    int* positions = (int*)malloc(32 * sizeof(int));
    int count = 0;

    // Traverse bits from highest to lowest
    for (int i = total_bits - 1; i >= 0; i--) {
        // n & 1等价于n % 2 == 1，但是位运算效率更高
        if ((n >> i) & 1) {
            positions[count++] = pos;
        }
        pos++;
    }

    *result_count = count + 1;
    int* result = (int*)malloc((*result_count) * sizeof(int));
    result[0] = count;
    for (int i = 0; i < count; i++) {
        result[i + 1] = positions[i];
    }

    free(positions);
    return result;
}

/*
 * oa 14: Creating a Binary Search Tree (BST) with Insert Count
 *
 * Given an array of unique integers, construct a binary search tree (BST)
 * by inserting each element from left to right. Each insertion is done
 * recursively. You are to track and print how many times the 'insert' function
 * is called (i.e., the number of recursive insert attempts) after each key is inserted.
 *
 * For the first key, a new root node is created and no insert calls are made.
 * Starting from the second key, each insertion may involve one or more insert calls.
 * After inserting each key, print the current value of the insert counter.
 *
 * Example:
 * Input:  keys = [2, 1, 3, 4]
 *
 * Insertion steps:
 * - Insert 2: Create root → counter = 0 → print 0
 * - Insert 1: insert(2) → counter = 1 → print 1
 * - Insert 3: insert(2) → counter = 2 → print 2
 * - Insert 4: insert(2) → insert(3) → counter = 4 → print 4
 *
 * Output:
 * 0
 * 1
 * 2
 * 4
 */

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

// Global counter to count insert calls
int counter = 0;

// Recursive insert function that adds a new key to the BST
void insert(Node* root, int key) {
    counter++;

    if (key < root->val) {
        if (root->left == NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->val = key;
            newNode->left = NULL;
            newNode->right = NULL;
            root->left = newNode;
        } else {
            insert(root->left, key);
        }
    } else {
        if (root->right == NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->val = key;
            newNode->left = NULL;
            newNode->right = NULL;
            root->right = newNode;
        } else {
            insert(root->right, key);
        }
    }
}
void createBST(int keys_count, int* keys) {
    counter = 0;

    Node* root = NULL;

    for (int i = 0; i < keys_count; i++) {
        if (root == NULL) {
            // First key becomes the root; no insert call
            root = (Node*)malloc(sizeof(Node));
            root->val = keys[i];
            root->left = NULL;
            root->right = NULL;
        } else {
            // Insert remaining keys into the BST
            insert(root, keys[i]);
        }
        printf("%d\n", counter); // Print counter after each insertion
    }

}

