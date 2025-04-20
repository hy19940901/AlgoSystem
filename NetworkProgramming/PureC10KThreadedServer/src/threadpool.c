#include "threadpool.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_SIZE 1024

typedef struct task {
    void (*func)(int);
    int arg;
} task_t;

struct threadpool {
    pthread_t* threads;
    task_t queue[QUEUE_SIZE];
    int head, tail;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int stop;
};

void* thread_loop(void* arg) {
    threadpool_t* pool = (threadpool_t*)arg;
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

threadpool_t* threadpool_create(int thread_count) {
    threadpool_t* pool = calloc(1, sizeof(threadpool_t));
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);
    pool->threads = malloc(sizeof(pthread_t) * thread_count);

    for (int i = 0; i < thread_count; ++i)
        pthread_create(&pool->threads[i], NULL, thread_loop, pool);

    return pool;
}

void threadpool_add_task(threadpool_t* pool, void (*func)(int), int arg) {
    pthread_mutex_lock(&pool->lock);
    pool->queue[pool->tail] = (task_t){func, arg};
    pool->tail = (pool->tail + 1) % QUEUE_SIZE;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
}

void threadpool_destroy(threadpool_t* pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->lock);

    // Join threads and cleanup
}
