#ifndef __THREADS_H__
#define __THREADS_H__

#include <stdint.h>

#define THREAD_STACK_SIZE 0x1000

#define TH_run 0
#define TH_join 1

struct thread 
{
  void* smb;
  void* sp;  
  int state;
  struct thread *prev;
  struct thread *next;
  uint32_t lc;
};

typedef struct thread thread_t;
typedef void (*runnable_t)(void*);

void init_thread_system();
void thread_schedule();
void switch_thread(thread_t *other);

thread_t* thread_current();
void lock1();
void unlock1();
thread_t* thread_create(runnable_t function, void *arg);
void thread_join(thread_t *other);


#endif
