#include <stdio.h>
#include <stdlib.h>

// 优先队列结构（最小堆）
typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

// 工具函数：交换两个整数
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 创建优先队列（使用 malloc，并显式转换类型）
PriorityQueue* create_pq(int initial_capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (!pq) {
        fprintf(stderr, "Failed to allocate memory for PriorityQueue.\n");
        exit(1);
    }

    pq->data = (int *)malloc(sizeof(int) * initial_capacity);
    if (!pq->data) {
        fprintf(stderr, "Failed to allocate memory for data array.\n");
        free(pq);
        exit(1);
    }

    pq->size = 0;
    pq->capacity = initial_capacity;
    return pq;
}

// 销毁优先队列
void destroy_pq(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

// 扩容函数
void resize(PriorityQueue *pq) {
    pq->capacity *= 2;
    int *new_data = (int *)realloc(pq->data, sizeof(int) * pq->capacity);
    if (!new_data) {
        fprintf(stderr, "Failed to resize priority queue.\n");
        destroy_pq(pq);
        exit(1);
    }
    pq->data = new_data;
}

// 插入元素
void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        resize(pq);
    }

    int i = pq->size++;
    pq->data[i] = value;

    // 上浮
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->data[parent] <= pq->data[i]) break;
        swap(&pq->data[parent], &pq->data[i]);
        i = parent;
    }
}

// 查看最小值
int peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        fprintf(stderr, "Priority queue is empty.\n");
        return -1;
    }
    return pq->data[0];
}

// 移除最小值
int extract_min(PriorityQueue *pq) {
    if (pq->size == 0) {
        fprintf(stderr, "Priority queue is empty.\n");
        return -1;
    }

    int min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];

    // 下沉
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < pq->size && pq->data[left] < pq->data[smallest])
            smallest = left;
        if (right < pq->size && pq->data[right] < pq->data[smallest])
            smallest = right;

        if (smallest == i) break;

        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }

    return min;
}

// 测试代码
int main() {
    PriorityQueue *pq = create_pq(4);

    int values[] = {10, 4, 15, 2, 8, 1};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; ++i) {
        insert(pq, values[i]);
        printf("Inserted: %d, Current top: %d\n", values[i], peek(pq));
    }

    printf("\nFinal heap (extracting in order):\n");
    while (pq->size > 0) {
        printf("%d ", extract_min(pq));
    }
    printf("\n");

    destroy_pq(pq);
    return 0;
}