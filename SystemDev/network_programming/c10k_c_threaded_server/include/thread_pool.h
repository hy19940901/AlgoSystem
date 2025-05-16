#ifndef THREAD_POOL_H
#define THREAD_POOL_H

typedef struct ThreadPool ThreadPool_T;

ThreadPool_T* ThreadPoolCreate(int thread_count);
void ThreadPoolAddTask(ThreadPool_T* pool, void (*func)(int), int arg);
void ThreadPoolDestroy(ThreadPool_T* pool);

#endif
