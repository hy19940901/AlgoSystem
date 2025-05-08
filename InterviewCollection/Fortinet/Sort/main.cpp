#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ---------------- 冒泡排序（优化版）----------------
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int swapped = 0;
        for (int j = n - 1; j > i; --j) {
            if (arr[j - 1] > arr[j]) {
                int t = arr[j]; arr[j] = arr[j - 1]; arr[j - 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break; // 提前退出
    }
}

// ---------------- 插入排序 ----------------
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------------- 选择排序 ----------------
void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int t = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = t;
    }
}

// ---------------- 希尔排序 ----------------
void shellSort(int* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// ---------------- 快速排序（随机化） ----------------
void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int* arr, int left, int right) {
    // 随机 pivot
    int randIdx = left + rand() % (right - left + 1);
    swap(&arr[randIdx], &arr[right]);

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

void quickSort(int* arr, int left, int right) {
    if (left >= right) return;

    int pi = partition(arr, left, right);
    quickSort(arr, left, pi - 1);
    quickSort(arr, pi + 1, right);
}

// ---------------- 归并排序 ----------------
void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ---------------- 堆排序 ----------------
void heapify(int* arr, int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int t = arr[i]; arr[i] = arr[largest]; arr[largest] = t;
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        int t = arr[0]; arr[0] = arr[i]; arr[i] = t;
        heapify(arr, i, 0);
    }
}

// ---------------- 打印数组 ----------------
void printArray(const char* name, int* arr, int n) {
    printf("%s: ", name);
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");
}

// ---------------- 主函数测试 ----------------
int main() {
    srand(time(NULL));
    int original[] = {5, 2, 9, 1, 7};
    int n = sizeof(original) / sizeof(original[0]);

    int arr1[n], arr2[n], arr3[n], arr4[n], arr5[n], arr6[n], arr7[n];
    memcpy(arr1, original, sizeof(original));
    memcpy(arr2, original, sizeof(original));
    memcpy(arr3, original, sizeof(original));
    memcpy(arr4, original, sizeof(original));
    memcpy(arr5, original, sizeof(original));
    memcpy(arr6, original, sizeof(original));
    memcpy(arr7, original, sizeof(original));

    bubbleSort(arr1, n);      printArray("Bubble", arr1, n);
    insertionSort(arr2, n);   printArray("Insertion", arr2, n);
    selectionSort(arr3, n);   printArray("Selection", arr3, n);
    shellSort(arr4, n);       printArray("Shell", arr4, n);
    quickSort(arr5, 0, n-1);  printArray("Quick", arr5, n);
    mergeSort(arr6, 0, n-1);  printArray("Merge", arr6, n);
    heapSort(arr7, n);        printArray("Heap", arr7, n);

    return 0;
}