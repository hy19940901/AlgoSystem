#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

/*
题目描述：将二进制链表转整数
一亩三分地第一份面经1，LeetCode 1290

给定一个单链表，链表的每一个节点都只包含 0 或 1 两种值，表示一个二进制数字。
请将该链表表示的二进制数转换为十进制并返回整数结果。

示例：
输入：1 -> 0 -> 1
输出：5
解释：(1 * 2^2) + (0 * 2^1) + (1 * 2^0) = 5
*/

// 定义链表节点结构体
struct ListNode {
    int val;
    struct ListNode* next;
};

// 函数：将二进制链表转为十进制整数
int getDecimalValue(struct ListNode* head) {
    int result = 0;
    while (head) {
        result = (result << 1) | head->val; // 完全等价于res*2+head->val，但是更快
        head = head->next;
    }
    return result;
}

/*
题目描述：找最近的同 x 或 y 坐标的点
一亩三分地第一份面经2，LeetCode 1779 原题（面经是follow up等会写）

给定一个二维平面上的点集 points，每个点是 (x, y)，还有一个目标点 (x_target, y_target)。
要求在 points 中找出：
  - 满足 x == x_target 或 y == y_target 的点
  - 并且到目标点的曼哈顿距离最小

如果有多个满足条件的点，返回索引最小的那个。如果没有符合条件的点，返回 -1。
*/
int nearestValidPoint(int x, int y, int** points, int pointsSize, int* pointsColSize){
    int minDist = INT_MAX;
    int index = -1;

    for (int i = 0; i < pointsSize; i++) {
        int px = points[i][0];
        int py = points[i][1];

        if (px == x || py == y) {
            int dist = abs(px - x) + abs(py - y);
            if (dist < minDist) {
                minDist = dist;
                index = i;
            }
        }
    }

    return index;
}

/*
题目描述：滑动窗口最大值
一亩三分地第一份面经3，LeetCode 239 原题

给定一个整数数组 nums 和一个大小为 k 的滑动窗口，移动该滑动窗口从数组的起始位置开始，依次向右滑动一位，并返回滑动窗口中的最大值。

输入：
nums = [1,3,-1,-3,5,3,6,7], k = 3

输出：
[3,3,5,5,6,7]

提示：
- 你必须在 O(n) 时间复杂度内完成此题。
*/

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* res = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    int* deque = (int*)malloc(sizeof(int) * numsSize); // 存的是下标
    int front = 0, rear = -1;
    int ri = 0;

    for (int i = 0; i < numsSize; i++) {
        // 移除队头（不在窗口内的）
        if (front <= rear && deque[front] <= i - k)
            front++;

        // 移除所有比当前值小的（保持单调递减）
        while (front <= rear && nums[deque[rear]] < nums[i])
            rear--;

        // 把当前下标加到队尾
        deque[++rear] = i;

        // 窗口形成后开始记录结果
        if (i >= k - 1)
            res[ri++] = nums[deque[front]];
    }

    *returnSize = ri;
    free(deque);
    return res;
}

/*
题目描述：将 base16（十六进制）格式的变量转换成 base10（十进制）整数
一亩三分地第二份面经1

输入：一个十六进制字符串，例如 "0x1A3F" 或 "1A3F"
输出：对应的十进制整数，例如 6719

要求：
- 支持大小写（如 "0x1a3f"、"1A3F" 都合法）
- 可选的 "0x" 前缀需要兼容
- 不使用库函数如 strtol（面试常要求手写）
*/
int hexCharToInt(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    else if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    else return -1; // invalid character
}

int hexToDecimal(const char* hexStr) {
    int result = 0;
    int i = 0;

    // Skip optional prefix 0x or 0X
    if (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) {
        i = 2;
    }

    while (hexStr[i]) {
        int val = hexCharToInt(hexStr[i]);
        if (val == -1) {
            printf("Invalid hex character: %c\n", hexStr[i]);
            return -1;
        }
        result = result * 16 + val;
        i++;
    }

    return result;
}

/*
题目描述：反转一个单向链表
一亩三分地第二份面经2，经典题

输入：head -> 1 -> 2 -> 3 -> 4 -> NULL
输出：head -> 4 -> 3 -> 2 -> 1 -> NULL
*/
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;

    while (curr) {
        struct ListNode* next_temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_temp;
    }

    return prev;
}

/*
题目描述：反转链表区间 [m, n]
一亩三分地第二份面经2 Follow-up：LeetCode 92

反转从位置 m 到 n 的链表节点，1 ≤ m ≤ n ≤ 链表长度。

示例：
输入：1->2->3->4->5, m=2, n=4
输出：1->4->3->2->5
*/

struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    if (!head || m == n) return head;

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    for (int i = 1; i < m; ++i)
        prev = prev->next;

    struct ListNode* curr = prev->next;
    for (int i = 0; i < n - m; ++i) {
        struct ListNode* temp = curr->next;
        curr->next = temp->next;
        temp->next = prev->next;
        prev->next = temp;
    }

    return dummy.next;
}

/*
题目描述：每 K 个节点一组反转链表，不足 K 的保留原顺序
一亩三分地第二份面经2 Follow-up：LeetCode 25

输入：1→2→3→4→5, k=2
输出：2→1→4→3→5

提示：
- 使用递归或迭代都可以，需注意分组时的 K 计数
- 每组反转可调用辅助函数 reverseList(a, b)
*/

struct ListNode* reverse(struct ListNode* a, struct ListNode* b) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = a;
    while (curr != b) {
        struct ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* a = head;
    struct ListNode* b = head;

    for (int i = 0; i < k; i++) {
        if (!b) return head;  // 剩下不够k个，直接返回原头
        b = b->next;
    }

    struct ListNode* new_head = reverse(a, b);     // 反转[a, b)
    a->next = reverseKGroup(b, k);                 // 递归反转后面部分
    return new_head;
}

/*
题目描述：向一个二叉搜索树中插入一个新节点
一亩三分地第二份面经3

输入：BST 根节点，值 val
输出：插入后的新 BST 根节点
*/
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    if (root == NULL) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = node->right = NULL;
        return node;
    }

    if (val < root->val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);

    return root;
}

/*
题目描述：从 BST 中删除一个节点
一亩三分地第二份面经3 Follow-up：LeetCode 450

输入：BST root 节点 和待删除的值 key
输出：返回新 BST 根节点

处理逻辑：
- 叶子节点直接删除
- 一个子节点，返回子树
- 两个子节点，用右子树最小值替代当前值，再删除右子树中该值
*/

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) return NULL; // 情况1：没找到要删除的节点

    if (root->val == key) {
        // 情况2：叶子节点
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // 情况3：左子树为空，右子树补位
        else if (root->left == NULL) {
            struct TreeNode* retNode = root->right;
            free(root);
            return retNode;
        }
        // 情况4：右子树为空，左子树补位
        else if (root->right == NULL) {
            struct TreeNode* retNode = root->left;
            free(root);
            return retNode;
        }
        // 情况5：左右子树都存在，将左子树挂到右子树最左节点的左侧
        else {
            struct TreeNode* cur = root->right;
            while (cur->left != NULL) {
                cur = cur->left;
            }
            cur->left = root->left;

            struct TreeNode* newRoot = root->right;
            free(root);
            return newRoot;
        }
    }

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else {
        root->right = deleteNode(root->right, key);
    }

    return root;
}

/*
题目描述：判断一个单链表中是否存在环
一亩三分地第二份面经4，LeetCode 141 原题

思路：快慢指针（Floyd判圈法）
*/

bool hasCycle(struct ListNode *head) {
    if (!head || !head->next) return false;

    struct ListNode* slow = head;
    struct ListNode* fast = head->next;

    while (slow != fast) {
        if (!fast || !fast->next) return false;
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

/*
题目描述：找出链表环的入口并移除它
一亩三分地第二份面经4 Follow-up：LeetCode 142 + 扩展

步骤：
- 使用快慢指针判断是否有环
- 相遇后重置一个指针到头，再次相遇即为环的起点
- 再遍历一圈找到环尾，断开 next 连接
*/
struct ListNode* detectCycle(struct ListNode* head) {
    if (!head || !head->next) return NULL;

    struct ListNode* slow = head;
    struct ListNode* fast = head;

    // 第一阶段：快慢指针相遇（判断是否有环）
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // 第二阶段：找入口
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }

    return NULL; // 无环
}

void removeCycle(struct ListNode* head) {
    struct ListNode* entrance = detectCycle(head);
    if (!entrance) return;

    struct ListNode* ptr = entrance;
    while (ptr->next != entrance) {
        ptr = ptr->next;
    }
    ptr->next = NULL; // break the cycle
}

/*
题目描述：将 base12 表达的字符串转换为 base10 整数
一亩三分地第三份面经1

输入：base12 表示的字符串，如 "1A5"（表示 1*144 + 10*12 + 5 = 245）
输出：对应的十进制整数，如 245

规则：
- 支持字符 0~9 和 A/B（代表 10 / 11）
- 不区分大小写
- 忽略前缀（如有 "0x" 等）

提示：
- 不能用 strtol，手写转换
- 注意字符合法性
*/
int base12CharToInt(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if (c == 'A' || c == 'a') return 10;
    if (c == 'B' || c == 'b') return 11;
    return -1; // 非法字符
}

int base12ToDecimal(const char* str) {
    int result = 0;
    int i = 0;
    while (str[i]) {
        int val = base12CharToInt(str[i]);
        if (val == -1) {
            printf("Invalid base12 character: %c\n", str[i]);
            return -1;
        }
        result = result * 12 + val;
        i++;
    }
    return result;
}

/*
题目描述：原地反转字符串中的单词，要求 O(n) 时间、O(1) 空间, lc151
一亩三分地第三份面经2
*/

// 原地反转字符串的 [left, right]
void reverseString(char *s, int left, int right) {
    while (left < right) {
        char temp = s[left];
        s[left++] = s[right];
        s[right--] = temp;
    }
}

// 去除多余空格：前后空格、多个空格压缩成一个
void trimSpaces(char *s) {
    int i = 0, j = 0;
    int len = strlen(s);

    // Skip leading spaces
    while (i < len && s[i] == ' ') i++;

    while (i < len) {
        if (s[i] != ' ') {
            s[j++] = s[i++];
        } else {
            s[j++] = ' ';
            while (i < len && s[i] == ' ') i++;  // skip multiple spaces
        }
    }

    // Remove trailing space
    if (j > 0 && s[j - 1] == ' ') j--;

    s[j] = '\0'; // null terminate
}

char* reverseWords(char* s) {
    trimSpaces(s);               // 去除多余空格
    int n = strlen(s);
    reverseString(s, 0, n - 1);  // 整体反转

    // 逐个单词反转
    int start = 0, end = 0;
    while (start < n) {
        while (end < n && s[end] != ' ') end++;
        reverseString(s, start, end - 1);
        start = ++end;
    }

    return s; // 直接返回原地修改后的字符串
}

/*
题目描述：每 K 个节点一组反转链表，不足 K 的保留原顺序
一亩三分地第三份面经3 ：LeetCode 25

输入：1→2→3→4→5, k=2
输出：2→1→4→3→5

提示：
- 使用递归或迭代都可以，需注意分组时的 K 计数
- 每组反转可调用辅助函数 reverseList(a, b)
*/
struct ListNode* reverseKGroup_iteration(struct ListNode* head, int k) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prevGroupTail = &dummy;
    struct ListNode* start = head;

    while (start) {
        // 找到这一组的 [start, end)
        struct ListNode* end = start;
        for (int i = 0; i < k; ++i) {
            if (!end) return dummy.next; // 剩下不足k个
            end = end->next;
        }

        // 反转当前组
        struct ListNode* newHead = reverse(start, end);

        // 接上上一组尾部
        prevGroupTail->next = newHead;

        // 接上当前组尾部
        start->next = end;

        // 准备下一组
        prevGroupTail = start;
        start = end;
    }

    return dummy.next;
}

/*
题目：最小初始值使得所有前缀和 ≥ 1
一亩三分地第三份面经4，LeetCode 1413

给定整数数组 nums，求最小正整数 x，使得：
x + nums[0] >= 1
x + nums[0] + nums[1] >= 1
...
x + 前缀和 >= 1

解法：前缀和 + 贪心
- 记录前缀和过程中的最小值 minSum
- 结果即为：1 - minSum
*/

int minStartValue(int* nums, int numsSize) {
    int sum = 0;        // 当前前缀和
    int minSum = 0;     // 所有前缀和中的最小值

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];             // 累积前缀和
        if (sum < minSum) {
            minSum = sum;           // 记录最小前缀和
        }
    }

    // 初始值 x 至少为 1 - minSum（使最坏情况也 >= 1）
    return 1 - minSum;
}

/*
题目描述：最大子数组和
一亩三分地第三份面经4 Follow-up，LeetCode 53

给定一个整数数组 nums，找到一个具有最大和的连续子数组（至少包含一个元素），返回其最大和。

示例：
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6

思路：
- 从左到右遍历
- 当前和 < 0 则舍弃（重置为当前元素）
- 保留过程中出现的最大子数组和

算法类型：前缀和 + 贪心（或优化版动态规划）
时间复杂度：O(n)
空间复杂度：O(1)
*/

int maxSubArray(int* nums, int numsSize) {
    int result = INT32_MIN;
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        count += nums[i];
        if (count > result) { // 取区间累计的最大值（相当于不断确定最大子序终止位置）
            result = count;
        }
        if (count <= 0) count = 0; // 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
    }
    return result;
}

int maxSubArrayDP(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int* dp = (int*)malloc(sizeof(int) * numsSize);
    dp[0] = nums[0];
    int maxSum = dp[0];

    for (int i = 1; i < numsSize; i++) {
        dp[i] = (dp[i - 1] > 0) ? dp[i - 1] + nums[i] : nums[i];
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
    }

    free(dp);
    return maxSum;
}

/*
题目：合并两个升序链表（不修改原始指针）
一亩三分地第5份面经，LeetCode 21

描述：
给定两个升序链表 l1 和 l2，将它们合并成一个新的升序链表并返回。
要求不能直接操作 l1/l2 指针，而是使用 cur1/cur2 做遍历。

输入：l1 = 1→2→4，l2 = 1→3→4
输出：1→1→2→3→4→4

时间复杂度：O(n + m)
空间复杂度：O(1)
*/
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    struct ListNode* cur1 = l1;
    struct ListNode* cur2 = l2;

    while (cur1 && cur2) {
        if (cur1->val < cur2->val) {
            tail->next = cur1;
            cur1 = cur1->next;
        } else {
            tail->next = cur2;
            cur2 = cur2->next;
        }
        tail = tail->next;
    }

    tail->next = (cur1 != NULL) ? cur1 : cur2;
    return dummy.next;
}

/*
题目：合并 k 个升序链表（不能用优先队列时的解法）
一亩三分地第三份面经5 Follow-up，LeetCode 23

描述：
给定一个包含 k 个升序链表的数组 lists，合并所有链表为一个升序链表并返回。
不能直接用 C 语言的优先队列（heap），可以先使用快排式分治（merge sort）来实现，但是肯定是优先队列更好。

思路：
- 两两合并，递归划分区间
- 时间复杂度：O(N log k)，其中 N 是节点总数，k 是链表个数
- 空间复杂度：O(log k) 递归栈

最优解法应使用小顶堆（优先队列），C 语言中需手动实现堆结构
*/

struct ListNode* mergeKListsDivide(struct ListNode** lists, int left, int right);

// 主函数：合并 k 个链表
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    return mergeKListsDivide(lists, 0, listsSize - 1);
}

// 快排式分治合并
struct ListNode* mergeKListsDivide(struct ListNode** lists, int left, int right) {
    if (left == right) return lists[left];
    int mid = left + (right - left) / 2;
    struct ListNode* l1 = mergeKListsDivide(lists, left, mid);
    struct ListNode* l2 = mergeKListsDivide(lists, mid + 1, right);
    return mergeTwoLists(l1, l2);
}

/*
题目：找出数组中前 K 大的数字（Top-K）
一亩三分地第六份面经1（简化版）

描述：
给定一个整数数组 nums 和一个整数 k，要求返回数组中前 K 大的数字。
使用 Quick Select 算法实现，不要求返回顺序正确。

示例输入：
nums = {7, 2, 1, 10, 8, 9, 4, 3, 6, 5}, k = 4
输出（任意顺序）：10, 9, 8, 7

思路：
- 快速选择（Quick Select）思想，目标是找出前 K 大元素
- 每次使用 partition 划分，使得左边都是较大的元素
- 当左边正好有 K 个元素时，前 K 大元素就在左边

时间复杂度：平均 O(n)
空间复杂度：O(1)（原地交换）
*/
// 交换两个元素
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 升序 partition（小的在左边）
int partition(int* arr, int left, int right) {
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[right]);  // pivot 放到末尾

    int store = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {  // 小的放左边
            swap(&arr[i], &arr[store]);
            store++;
        }
    }
    swap(&arr[store], &arr[right]);  // 把 pivot 放回中间
    return store;
}

// 快速选择：找前 K 大元素 → 找第 N-K 小元素为 pivot
void quickSelect(int* arr, int left, int right, int targetIndex) {
    if (left >= right) return;

    int pivotIndex = partition(arr, left, right);
    if (targetIndex < pivotIndex) {
        quickSelect(arr, left, pivotIndex - 1, targetIndex);
    } else if (targetIndex > pivotIndex) {
        quickSelect(arr, pivotIndex + 1, right, targetIndex);
    }
    // if equal: done
}

// 用于提取前 K 大元素（顺序不保证）
void topK(int* arr, int n, int k) {
    if (k <= 0 || k > n) return;

    // 用升序逻辑，找出第 n-k 小的数 → 它是第 K 大
    int targetIndex = n - k;
    quickSelect(arr, 0, n - 1, targetIndex);

    // 打印前 K 大元素（它们在右侧）
    printf("Top %d largest elements:\n", k);
    for (int i = targetIndex; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 代码改错
/*
 * Function: test_copy
 * --------------------
 * Copies the string from src to newly allocated memory,
 * and sets *dest to point to the copy.
 *
 * src:  Source string
 * dest: Pointer to char* that will receive the allocated copy
 *
 * returns: length of the copied string (excluding '\0'), or -1 if malloc fails
 */

/*
int test_copy(char *src, char *dest)          // ❌ 错误：dest 是值传递，修改无效
{
    char *p, *q;
    int len = strlen(src);

    dest = malloc(len);                       // ❌ 错误 1：少分配了一个字节（没有为 '\0' 留空间）
                                              // ❌ 错误 2：dest 是局部变量，malloc 后的地址不会传出

    p = src;
    q = dest;                                 // ❌ 错误 3：外部根本访问不到这个新分配的 dest

    while (p) *q++ = *p++;                     // ❌ 错误 4：while(p) 始终为真，p 不是 NULL 指针
                                              //    应该是 while(*p)，判断字符内容是否为 '\0'

    *q = '\0';                                 // ❌ 错误 5：可能越界写，因为 malloc(len) 不是 malloc(len + 1)

    return len;
}
*/

int test_copy(char *src, char **dest) { //动态内存，目的是能够自动调整空间
    char *p, *q;
    int len = strlen(src);

    *dest = (char *)malloc(len + 1);  // 分配足够空间（含 '\0'）
    if (*dest == NULL) return -1;

    p = src;
    q = *dest;

    while (*p) *q++ = *p++;  // 逐字符复制，直到遇到 '\0'
    *q = '\0';               // 添加字符串终止符

    return len;
}

// ✅ 用于测试 test_copy 的函数，不是程序主入口
void test_copy_demo()  //原题是main
{
    char src[100], *dest;
    int len;

    strcpy(src, "hello world!");           // ✅ 初始化 src 内容

    len = test_copy(src, &dest);           // ✅ 传入 dest 的地址，正确分配并复制

    printf("the dest is %s len is %d\n", dest, len);  // ✅ 输出测试结果

    free(dest);                            // ✅ 释放分配的堆内存
}

// follow up, dest改成单指针
int test_copy_easy(char *src, char *dest)  // ✅ 单指针 dest 就够，缺点是dest不能动态分配内存，只能写死
{
    char *p = src;
    char *q = dest;

    int len = 0;

    while (*p) {
        *q++ = *p++;
        len++;
    }
    *q = '\0';  // ✅ 添加字符串结尾

    return len;
}

/*
【面经题】指针传参、malloc、内存泄漏分析

问题：
void foo(int* arr, int size) {
    arr = malloc(size * sizeof(int));
}

int main() {
    int* arr = malloc(size * sizeof(int));
    foo(arr);
}

问：
Q1: 这样在 foo 中 malloc，会不会改变 main 中的 arr？
Q2: 有没有内存泄漏？为什么？
Q3: 如何正确修改 main 中的 arr？

--------------------------------------------------

【Q1】foo 中 malloc 会不会改变 main 中的 arr？
【A1】不会！

解释：
- C 是值传递，arr 是 main 中指针变量的一份拷贝
- 在 foo 中 malloc 改变的是拷贝，不会影响原始指针
- main 中的 arr 指向的地址保持不变

【Q2】有没有内存泄漏？
【A2】有！

解释：
- main 中原来的 malloc 分配了一块内存
- foo 中重新 malloc 后，main 原指针无法访问那块内存
- 造成 memory leak（悬空指针）

【Q3】怎么正确写才能修改 main 中的 arr？
【A3】传 int**（指针的地址），才能修改调用者变量的值

修改版如下 ↓
*/

#include <stdio.h>
#include <stdlib.h>

// 正确写法：传入二级指针，修改原始指针地址
void foo(int** arr, int size) {
    *arr = malloc(size * sizeof(int));  // ✅ 通过 *arr 修改调用者的 arr
}

// 虚拟主函数，模拟调用者场景（非真实 main）
void test_main() {
    int* arr = NULL;               // ✅ 初始化指针为 NULL
    foo(&arr, 10);                 // ✅ 传入 arr 的地址（即 int**）

    // ... 此处可以使用 arr 指向的内存 ...

    free(arr);                     // ✅ 最后释放，防止内存泄漏
}

/*
总结：
- C 中所有参数传递都是“值传递”，包括指针也是
- 想在 foo() 内部修改指针变量，必须传入指针的地址（int**）
- 否则 foo() 中 malloc 的只是副本，main() 中无效，且会造成内存泄漏

建议面试时用结构化方式回答，同时展示修改版本。
*/

/*
题目：向二叉树添加一层
一亩三分地第七份面经3，LeetCode 623

思路：
- 特判 depth = 1，新建根节点
- 否则递归到 depth - 1 层，左右分别插入新节点
*/

#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 辅助递归函数
void dfs(struct TreeNode* node, int val, int depth) {
    if (!node) return;

    if (depth == 1) {
        // 插入新节点
        struct TreeNode* leftNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        struct TreeNode* rightNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        leftNode->val = val;
        rightNode->val = val;
        leftNode->left = node->left;
        leftNode->right = NULL;
        rightNode->right = node->right;
        rightNode->left = NULL;
        node->left = leftNode;
        node->right = rightNode;
        return;
    }

    dfs(node->left, val, depth - 1);
    dfs(node->right, val, depth - 1);
}

// 主函数
struct TreeNode* addOneRow(struct TreeNode* root, int val, int depth) {
    if (depth == 1) {
        struct TreeNode* newRoot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newRoot->val = val;
        newRoot->left = root;
        newRoot->right = NULL;
        return newRoot;
    }
    dfs(root, val, depth - 1);
    return root;
}

/*
题目：LRU 缓存实现
一亩三分地第七份面经4，LeetCode 146

思路：
- 哈希表（key → node*）提供 O(1) 查找
- 双向链表维护访问顺序，最近使用的节点移到头部，淘汰尾部节点
*/

#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 10007  // 哈希桶大小（质数）
#define INVALID_KEY -1

// 双向链表节点
typedef struct Node {
    int key, value;
    struct Node* prev;
    struct Node* next;
} Node;

// LRU 缓存结构
typedef struct {
    int capacity;
    int size;
    Node* head;
    Node* tail;
    Node* hash[HASH_SIZE];  // 哈希表：key -> node*
} LRUCache;

// 哈希函数（简单模运算）
int hash(int key) {
    if (key < 0) key = -key;
    return key % HASH_SIZE;
}

// 创建节点
Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}

// 将节点插入头部
void insertHead(LRUCache* obj, Node* node) {
    node->next = obj->head;
    node->prev = NULL;
    if (obj->head) obj->head->prev = node;
    obj->head = node;
    if (!obj->tail) obj->tail = node;
}

// 删除节点
void removeNode(LRUCache* obj, Node* node) {
    if (node->prev) node->prev->next = node->next;
    else obj->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else obj->tail = node->prev;
}

// 移动节点到头部（访问）
void moveToHead(LRUCache* obj, Node* node) {
    removeNode(obj, node);
    insertHead(obj, node);
}

// 删除尾部节点（最久未使用）
Node* removeTail(LRUCache* obj) {
    Node* tail = obj->tail;
    if (tail) {
        removeNode(obj, tail);
    }
    return tail;
}

// 初始化 LRU 缓存
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->size = 0;
    obj->head = obj->tail = NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        obj->hash[i] = NULL;
    }
    return obj;
}

// get 操作
int lRUCacheGet(LRUCache* obj, int key) {
    int h = hash(key);
    Node* node = obj->hash[h];
    while (node && node->key != key) node = node->next;
    if (!node) return -1;

    // 移动到头部
    moveToHead(obj, node);
    return node->value;
}

// put 操作
void lRUCachePut(LRUCache* obj, int key, int value) {
    int h = hash(key);
    Node* node = obj->hash[h];

    // 是否已存在
    while (node && node->key != key) node = node->next;

    if (node) {
        node->value = value;
        moveToHead(obj, node);
        return;
    }

    // 不存在：创建新节点
    Node* newNode = createNode(key, value);
    insertHead(obj, newNode);

    // 加入哈希表（简单头插法）
    newNode->next = obj->hash[h];
    obj->hash[h] = newNode;

    obj->size++;
    if (obj->size > obj->capacity) {
        // 淘汰尾部
        Node* tail = removeTail(obj);
        int oldKey = tail->key;

        // 删除哈希表中的 oldKey
        Node** p = &obj->hash[hash(oldKey)];
        while (*p && (*p)->key != oldKey) {
            p = &(*p)->next;
        }
        if (*p) *p = (*p)->next;

        free(tail);
        obj->size--;
    }
}

// 释放 LRU 缓存
void lRUCacheFree(LRUCache* obj) {
    Node* cur = obj->head;
    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(obj);
}

/*
题目：URLify
Glassdoor 面经1

描述：
将字符串中的空格替换为 "%20"。
假设字符串末尾有足够空间容纳额外字符，且给定“实际长度”。

示例：
输入: "Mr John Smith    ", trueLength = 13
输出: "Mr%20John%20Smith"

注意：
- 原地修改字符串
- 从末尾往前填充可避免多次移动

思路：
- 先统计实际字符数（不包括填充）
- 计算空格数量
- 从末尾倒着处理，每遇到空格填 "%20"，否则复制原字符
*/
void URLify(char str[], int trueLength) {
    int spaceCount = 0;
    for (int i = 0; i < trueLength; i++) {
        if (str[i] == ' ') spaceCount++;
    }

    int index = trueLength + spaceCount * 2;
    str[index] = '\0'; // 终止符

    for (int i = trueLength - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[index - 1] = '0';
            str[index - 2] = '2';
            str[index - 3] = '%';
            index -= 3;
        } else {
            str[--index] = str[i];
        }
    }
}

/*
题目：自定义 FizzBuzz 打印
Glassdoor 面经2

描述：
写一个 C 程序打印 x 行：
- 如果是 2 的倍数，打印 "Fizz"
- 如果是 5 的倍数，打印 "Buzz"
- 如果同时是 2 和 5 的倍数，打印 "FizzBuzz"
- 否则打印数字本身
*/

void fizzBuzzCustom(int x) {
    for (int i = 1; i <= x; i++) {
        if (i % 10 == 0)
            printf("FizzBuzz\n");
        else if (i % 2 == 0)
            printf("Fizz\n");
        else if (i % 5 == 0)
            printf("Buzz\n");
        else
            printf("%d\n", i);
    }
}

/*
 * Follow-up: Output to File
 * --------------------------
 * Function: writeFizzBuzzToFile
 * -----------------------------
 * Same logic as runFizzBuzz, but writes the output to a file instead
 * of printing to the console.
 *
 * Parameters:
 *   x        - Number of lines to generate
 *   filename - Path to the output file
 */
void writeFizzBuzzToFile(int x, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int i = 1; i <= x; i++) {
        if (i % 2 == 0 && i % 5 == 0) {
            fprintf(file, "FizzBuzz\n");
        } else if (i % 2 == 0) {
            fprintf(file, "Fizz\n");
        } else if (i % 5 == 0) {
            fprintf(file, "Buzz\n");
        } else {
            fprintf(file, "%d\n", i);
        }
    }

    fclose(file);
}

/*
题目：Base64 编码 + Base10 <-> Base12 转换
Glassdoor 面经3

子任务：
1. 实现 Base64 编码（仅输出字符编码）
2. 将 base10 整数转为 base12 字符串
3. 将 base12 字符串转为 base10 整数

简化字符集：0-9 + A, B (即 base12：'0'-'9', 'A'=10, 'B'=11)
*/

// base10 -> base12
void base10ToBase12(int num, char* buffer) {
    char map[] = "0123456789AB";
    int i = 0;
    if (num == 0) {
        buffer[i++] = '0';
    } else {
        while (num > 0) {
            buffer[i++] = map[num % 12];
            num /= 12;
        }
    }
    buffer[i] = '\0';
    // 反转
    for (int l = 0, r = i - 1; l < r; l++, r--) {
        char t = buffer[l]; buffer[l] = buffer[r]; buffer[r] = t;
    }
}

// base12 -> base10
int base12ToBase10(const char* str) {
    int result = 0;
    while (*str) {
        int val;
        if (*str >= '0' && *str <= '9') val = *str - '0';
        else if (*str == 'A') val = 10;
        else if (*str == 'B') val = 11;
        else return -1;
        result = result * 12 + val;
        str++;
    }
    return result;
}

/*
题目：实现标准二分查找
Glassdoor 面经4

描述：
给定一个升序数组和一个目标值，返回目标值的下标。
如果不存在，返回 -1。

思路：
- 经典二分查找模板
- 注意处理 left <= right 的边界
*/

int binarySearch(int* nums, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/*
题目：Base64 转换为自定义进制（如 base16、base32 等）
Glassdoor 面经5

描述：
实现一个函数，将 base64 字符串转换为自定义 base（如 base16）
（这里只提供字符层面转换逻辑，实际 base64 编解码略）

简化模型：
- 将 base64 中的每 6 位表示为一个整数
- 再转换为目标 base（如 base16）下的字符串
*/

void toBaseN(int num, int base, char* buf) {
    const char* map = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    int i = 0;
    while (num > 0) {
        buf[i++] = map[num % base];
        num /= base;
    }
    buf[i] = '\0';
    // reverse
    for (int l = 0, r = i - 1; l < r; l++, r--) {
        char t = buf[l]; buf[l] = buf[r]; buf[r] = t;
    }
}

/*
题目：将十进制数转换为二进制，并找出所有 1 的位置
Glassdoor 面经6

示例：
输入: 22（二进制为 10110）
输出: 1 在第 1, 2, 4 位（从右往左，0-based）

思路：
- 用位运算右移每一位，记录 1 出现的位置
*/

void findOnePositions(int num) {
    int pos = 0;
    while (num) {
        if (num & 1)
            printf("Bit 1 at position %d\n", pos);
        num >>= 1;
        pos++;
    }
}

/*
题目：手动实现 strtok() 函数
Glassdoor 面经7

说明：
- strtok(str, delim) 将字符串分割为多个子串
- 每次调用返回一个 token，内部维护 static 状态

实现关键：
- 静态指针
- 跳过分隔符，标记末尾为 \0，返回 token 起始地址
*/

char* my_strtok(char* str, const char* delim) {
    static char* last;
    if (str) last = str;
    if (!last) return NULL;

    // Skip leading delimiters
    while (*last && strchr(delim, *last)) last++;
    if (*last == '\0') return NULL;

    char* token_start = last;

    while (*last && !strchr(delim, *last)) last++;

    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }

    return token_start;
}

/*
题目：清除整数中某一段范围的比特位
Glassdoor 面经8

描述：
删除整数中从 bit i 到 bit j（含）的所有位（置 0）

方法：
- 使用掩码屏蔽位 [i, j]
*/

int clearBitRange(int x, int i, int j) {
    int left = ~0 << (j + 1);
    int right = (1 << i) - 1;
    int mask = left | right;
    return x & mask;
}

/*
题目：在迷宫中寻找一条路径（0 可通行，1 为墙）
Glassdoor 面经9

思路：
- 用 DFS 或 BFS 寻找从起点到终点的路径
- 注意边界、回溯、标记访问过的位置
*/

#define MAX 100

int visited[MAX][MAX];

int dfsMaze(int maze[MAX][MAX], int x, int y, int m, int n) {
    if (x < 0 || y < 0 || x >= m || y >= n || maze[x][y] == 1 || visited[x][y]) return 0;
    if (x == m - 1 && y == n - 1) return 1; // 到达终点

    visited[x][y] = 1;
    if (dfsMaze(maze, x + 1, y, m, n)) return 1;
    if (dfsMaze(maze, x - 1, y, m, n)) return 1;
    if (dfsMaze(maze, x, y + 1, m, n)) return 1;
    if (dfsMaze(maze, x, y - 1, m, n)) return 1;

    return 0;
}

/*
 * 功能：将完整格式的 IPv6 地址缩写为简写形式（符合 RFC 5952）
 * ------------------------------------------
 * 缩写规则说明（RFC 5952）：
 * ✅ 规则 1：每段的前导 0 必须去掉。例如 "0042" → "42"，"0000" → "0"
 * ✅ 规则 2：最长的连续 0 段可以缩写为 "::"，但整串中最多只能缩写一次
 * ✅ 规则 3：如果有多个相同长度的连续 0，优先压缩靠前的
 * ✅ 规则 4：压缩后的地址中不能出现两个 "::"，仅保留一个
 * ✅ 规则 5：如果地址全部为 0，可以缩写为 "::"
 */
// 函数：将全写 IPv6 地址进行缩写
void shorten_ipv6(const char *ipv6_long, char *output) {
    char ip_copy[100];
    strncpy(ip_copy, ipv6_long, sizeof(ip_copy));
    ip_copy[sizeof(ip_copy) - 1] = '\0';  // 防止字符串溢出

    // 拆分 IPv6 地址为 8 段，每段用 ':' 分隔
    char *hextets[8];
    char *token = strtok(ip_copy, ":");
    int count = 0;

    while (token && count < 8) {
        // ✅ 规则 1：去掉前导 0
        while (*token == '0' && *(token + 1) != '\0') token++;
        hextets[count++] = token;
        token = strtok(NULL, ":");
    }

    // 查找最长连续 "0" 段（用于 :: 压缩）
    // max_start, max_len 表示最长的连续 0 开始位置和长度
    int max_len = 0, max_start = -1;
    int d_len = 0, d_start = -1;

    for (int i = 0; i < 8; i++) {
        if (strcmp(hextets[i], "0") == 0 || strcmp(hextets[i], "") == 0) {
            // 当前是 0 段，记录连续起点
            if (d_start == -1) d_start = i;
            d_len++;
            // ✅ 规则 3：更新最长 0 段记录
            if (d_len > max_len) {
                max_len = d_len;
                max_start = d_start;
            }
        } else {
            d_len = 0;
            d_start = -1;
        }
    }

    // 构建缩写后的地址字符串
    output[0] = '\0';

    for (int i = 0; i < 8;) {
        if (max_len > 1 && i == max_start) {
            // ✅ 规则 2 和 4：压缩最长连续 0 段为 "::"（只能压一次）
            strcat(output, "::");
            i += max_len;  // 跳过压缩段
            if (i == 8) break;  // 如果压缩到最后，不再加冒号
            if (output[strlen(output) - 1] != ':') strcat(output, ":");
        } else {
            // 正常拼接非 0 段
            strcat(output, hextets[i]);
            i++;
            // 添加 ":" 分隔符（不能多加）
            if (i < 8 && !(max_len > 1 && i == max_start)) {
                strcat(output, ":");
            }
        }
    }

    // ✅ 规则 5：如全 0 地址，会输出 "::"
}