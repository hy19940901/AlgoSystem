#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/************************************************
 * 1. Implement strcpy (String Copy)
 ************************************************/
char *MyStrcpy(char *dest, const char *src) {
    char *original = dest;
    while ((*dest++ = *src++) != '\0') {}
    return original;
}

/************************************************
 * 2. Implement strncpy (String Copy with Limit)
 ************************************************/
char *MyStrncpy(char *dest, const char *src, size_t n) {
    char *original = dest;
    while (n-- && (*dest++ = *src++) != '\0') {}
    while (n--) *dest++ = '\0';
    return original;
}

/************************************************
 * 3. Dynamic Array
 ************************************************/
typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray *CreateArray(int capacity) {
    DynamicArray *array = (DynamicArray *)malloc(sizeof(DynamicArray));
    array->data = (int *)malloc(capacity * sizeof(int));
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void PushBack(DynamicArray *array, int value) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = (int *)realloc(array->data, array->capacity * sizeof(int));
    }
    array->data[array->size++] = value;
}

void FreeArray(DynamicArray *array) {
    free(array->data);
    free(array);
}

/************************************************
 * 4. Singly Linked List
 ************************************************/
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *CreateNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void InsertNode(Node **head, int data) {
    Node *node = CreateNode(data);
    node->next = *head;
    *head = node;
}

void PrintList(const Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/************************************************
 * 5. File I/O
 ************************************************/
void WriteFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}

void ReadFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

/************************************************
 * 6. Multithreading Example
 ************************************************/
void *PrintMessage(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d: Hello from thread!\n", thread_id);
    return NULL;
}

void RunThreads() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    pthread_create(&thread1, NULL, PrintMessage, &id1);
    pthread_create(&thread2, NULL, PrintMessage, &id2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

/************************************************
 * Main Function
 ************************************************/
int main() {
    // Test MyStrcpy
    char dest[100];
    MyStrcpy(dest, "Hello, World!");
    printf("Copied string: %s\n", dest);

    size_t dest_size = sizeof(dest);
    MyStrncpy(dest, "Hello, World!", dest_size);
    dest[dest_size - 1] = '\0';
    printf("Safe Copied string: %s\n", dest);

    // Test dynamic array
    DynamicArray *array = CreateArray(2);
    PushBack(array, 10);
    PushBack(array, 20);
    PushBack(array, 30);
    printf("Dynamic Array: %d, %d, %d\n", array->data[0], array->data[1], array->data[2]);
    FreeArray(array);

    // Test linked list
    Node *head = NULL;
    InsertNode(&head, 10);
    InsertNode(&head, 20);
    InsertNode(&head, 30);
    PrintList(head);

    // Test file I/O
    WriteFile("test.txt", "This is a test file.\nHello, File I/O!");
    printf("Reading from file:\n");
    ReadFile("test.txt");

    // Test multithreading
    RunThreads();

    return 0;
}
