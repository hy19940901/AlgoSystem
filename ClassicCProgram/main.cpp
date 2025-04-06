/**
 *
 * Description:
 * This file contains multiple C programming exercises commonly used in technical interviews.
 * It covers topics such as pointers, memory management, string manipulation, data structures,
 * file I/O, and multithreading.
 *
 * Each function is implemented with detailed explanations and comments.
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>

 /************************************************
  * 1. Implement strcpy (String Copy)
  * Copies a string from source to destination.
  ************************************************/
 char *my_strcpy(char *dest, const char *src) {
     char *original = dest;
     while ((*dest++ = *src++) != '\0'); // Copy characters until null terminator
     return original;
 }

 /************************************************
  * 2. Implement strncpy (String Copy with Limit)
  * Copies a limited number of characters from source to destination.
  ************************************************/
 char *my_strncpy(char *dest, const char *src, size_t n) {
     char *original = dest;
     while (n-- && (*dest++ = *src++) != '\0'); // Copy up to n characters
     while (n--) *dest++ = '\0'; // Pad with null terminator if needed
     return original;
 }

 /************************************************
  * 3. Implement a Dynamic Array
  * Supports push_back operation and dynamic resizing.
  ************************************************/
 typedef struct {
     int *data;
     int size;
     int capacity;
 } DynamicArray;

 DynamicArray* createArray(int capacity) {
     DynamicArray *arr = (DynamicArray*) malloc(sizeof(DynamicArray));
     arr->data = (int*) malloc(capacity * sizeof(int));
     arr->size = 0;
     arr->capacity = capacity;
     return arr;
 }

 void push_back(DynamicArray *arr, int value) {
     if (arr->size == arr->capacity) {
         arr->capacity *= 2;
         arr->data = (int*) realloc(arr->data, arr->capacity * sizeof(int));
     }
     arr->data[arr->size++] = value;
 }

 void freeArray(DynamicArray *arr) {
     free(arr->data);
     free(arr);
 }

 /************************************************
  * 4. Implement a Singly Linked List
  * Supports insertion and printing.
  ************************************************/
 typedef struct Node {
     int data;
     struct Node *next;
 } Node;

 Node* createNode(int data) {
     Node *node = (Node*)malloc(sizeof(Node));
     node->data = data;
     node->next = NULL;
     return node;
 }

 void insert(Node **head, int data) {
     Node *node = createNode(data);
     node->next = *head;
     *head = node;
 }

 void printList(Node *head) {
     while (head) {
         printf("%d -> ", head->data);
         head = head->next;
     }
     printf("NULL\n");
 }

 /************************************************
  * 5. Implement File I/O (Read and Write to a File)
  * Writes a string to a file and reads it back.
  ************************************************/
 void writeFile(const char *filename, const char *content) {
     FILE *file = fopen(filename, "w");
     if (!file) {
         perror("Failed to open file");
         return;
     }
     fprintf(file, "%s", content);
     fclose(file);
 }

 void readFile(const char *filename) {
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
  * 6. Implement Multithreading (Two Threads Printing Messages)
  * Creates and joins two threads that print messages.
  ************************************************/
 void* printMessage(void *arg) {
     printf("Thread %d: Hello from thread!\n", *(int*)arg);
     return NULL;
 }

 void runThreads() {
     pthread_t thread1, thread2;
     int id1 = 1, id2 = 2;
     pthread_create(&thread1, NULL, printMessage, &id1);
     pthread_create(&thread2, NULL, printMessage, &id2);
     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);
 }

 /************************************************
  * Main Function (Test All Implementations)
  * Calls each function to verify correctness.
  ************************************************/
 int main() {
     // Test strcpy
     char dest[100];
     my_strcpy(dest, "Hello, World!");
     printf("Copied string: %s\n", dest);

     // Test Dynamic Array
     DynamicArray *arr = createArray(2);
     push_back(arr, 10);
     push_back(arr, 20);
     push_back(arr, 30);
     printf("Dynamic Array: %d, %d, %d\n", arr->data[0], arr->data[1], arr->data[2]);
     freeArray(arr);

     // Test Linked List
     Node *head = NULL;
     insert(&head, 10);
     insert(&head, 20);
     insert(&head, 30);
     printList(head);

     // Test File I/O
     writeFile("test.txt", "This is a test file.\nHello, File I/O!");
     printf("Reading from file:\n");
     readFile("test.txt");

     // Test Multithreading
     runThreads();

     return 0;
 }
