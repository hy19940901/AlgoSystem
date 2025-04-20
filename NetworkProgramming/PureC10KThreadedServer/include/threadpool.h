#ifndef THREADPOOL_H
#define THREADPOOL_H

typedef struct threadpool threadpool_t;

threadpool_t* threadpool_create(int thread_count);
void threadpool_add_task(threadpool_t* pool, void (*func)(int), int arg);
void threadpool_destroy(threadpool_t* pool);

#endif
