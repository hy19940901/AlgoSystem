#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/************************************************
 * 1. Implement strcpy (String Copy)
 ************************************************/
char *my_strcpy(char *dest, const char *src) {
    char *original = dest;
    while ((*dest++ = *src++) != '\0') {}
    return original;
}

/************************************************
 * 2. Implement strncpy (String Copy with Limit)
 ************************************************/
char *my_strncpy(char *dest, const char *src, size_t n) {
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

DynamicArray *create_array(int capacity) {
    DynamicArray *array = (DynamicArray *)malloc(sizeof(DynamicArray));
    array->data = (int *)malloc(capacity * sizeof(int));
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void push_back(DynamicArray *array, int value) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = (int *)realloc(array->data, array->capacity * sizeof(int));
    }
    array->data[array->size++] = value;
}

void free_array(DynamicArray *array) {
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

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insert_node(Node **head, int data) {
    Node *node = create_node(data);
    node->next = *head;
    *head = node;
}

void print_list(const Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/************************************************
 * 5. File I/O
 ************************************************/
void write_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}

void read_file(const char *filename) {
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
void *print_message(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d: Hello from thread!\n", thread_id);
    return NULL;
}

void run_threads() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    pthread_create(&thread1, NULL, print_message, &id1);
    pthread_create(&thread2, NULL, print_message, &id2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

/************************************************
 * Main Function
 ************************************************/
int main() {
    // Test my_strcpy
    char dest[100];
    my_strcpy(dest, "Hello, World!");
    printf("Copied string: %s\n", dest);

    // Test dynamic array
    DynamicArray *array = create_array(2);
    push_back(array, 10);
    push_back(array, 20);
    push_back(array, 30);
    printf("Dynamic Array: %d, %d, %d\n", array->data[0], array->data[1], array->data[2]);
    free_array(array);

    // Test linked list
    Node *head = NULL;
    insert_node(&head, 10);
    insert_node(&head, 20);
    insert_node(&head, 30);
    print_list(head);

    // Test file I/O
    write_file("test.txt", "This is a test file.\nHello, File I/O!");
    printf("Reading from file:\n");
    read_file("test.txt");

    // Test multithreading
    run_threads();

    return 0;
}
