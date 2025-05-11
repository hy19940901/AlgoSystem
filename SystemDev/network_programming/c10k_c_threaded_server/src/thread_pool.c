#include "../include/thread_pool.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_SIZE 1024

typedef struct task {
    void (*func)(int);
    int arg;
} task_t;

struct ThreadPool {
    pthread_t* threads;
    task_t queue[QUEUE_SIZE];
    int head, tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int stop;
};

void* ThreadLoop(void* arg) {
    ThreadPool_T* pool = (ThreadPool_T*)arg;
    while (1) {
        pthread_mutex_lock(&pool->lock);
        while (pool->head == pool->tail && !pool->stop)
            pthread_cond_wait(&pool->cond, &pool->lock);
        if (pool->stop) break;

        task_t t = pool->queue[pool->head];
        pool->head = (pool->head + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&pool->lock);

        t.func(t.arg);
    }
    pthread_mutex_unlock(&pool->lock);
    return NULL;
}

ThreadPool_T* ThreadPoolCreate(int thread_count) {
    ThreadPool_T* pool = calloc(1, sizeof(ThreadPool_T));
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);
    pool->threads = malloc(sizeof(pthread_t) * thread_count);

    for (int i = 0; i < thread_count; ++i)
        pthread_create(&pool->threads[i], NULL, ThreadLoop, pool);

    return pool;
}

void ThreadPoolAddTask(ThreadPool_T* pool, void (*func)(int), int arg) {
    pthread_mutex_lock(&pool->lock);
    pool->queue[pool->tail] = (task_t){func, arg};
    pool->tail = (pool->tail + 1) % QUEUE_SIZE;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
}

void ThreadPoolDestroy(ThreadPool_T* pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->lock);

    // Join threads and cleanup
}
