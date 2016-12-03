#include <threads.h>
//#include <buddy_alloc.h>
#include "lock.h"
#include "alloc.h"
#include <ioport.h>
#include "print.h"
#include "ints.h"
#include "pit.h"
#include "interrupts.h"

struct initial_tf
{
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t rbx;
  uint64_t rbp;  
  uint64_t ra;
} __attribute__((packed));

typedef struct initial_tf itf;
extern void origin(void);
extern void thread_switch(void **proshloe, void *budushee);
thread_t *current_t;
thread_t kernel_t;
void init_thread_system() 
{
  current_t=&kernel_t;
  current_t->smb=NULL;
  current_t->sp=NULL;
  current_t->state=TH_run;
  current_t->prev=current_t;
  current_t->next=current_t;
  current_t->lc=0;
}
void lock1() 
{
  if (current_t->lc==0) 
  {
    __asm__ volatile("cli" : : : "cc");
  } 
  current_t->lc++;
}
void unlock1() 
{   
  current_t->lc--; 
  if (current_t->lc==0) 
  {
    __asm__ volatile("sti" : : : "cc");
  }
}
void thread_origin(runnable_t funy, void *a) 
{
  out8(0x20, 1<<5);
  __asm__ volatile("sti");
  funy(a);
  lock1();
  current_t->state=TH_join;
  unlock1();
  while (1);
}
thread_t* thread_create(runnable_t funy, void *a) 
{
  lock1();  
  thread_t *new_thread=(thread_t*) mem_alloc(sizeof(thread_t));
  new_thread->smb=mem_alloc(THREAD_STACK_SIZE);
  new_thread->sp=(void*)((uint64_t)new_thread->smb+THREAD_STACK_SIZE);
  new_thread->sp=(void*)((uint64_t)new_thread->sp-sizeof(itf));
  new_thread->state=TH_run;
  new_thread->prev=current_t;
  new_thread->next=current_t->next;
  new_thread->prev->next=new_thread;
  new_thread->next->prev=new_thread;
  itf *f=new_thread->sp;
  f->r15=(uint64_t)funy;
  f->r14=(uint64_t)a;
  f->r13=0;f->r12=0;f->rbx=0;f->rbp=0;
  f->ra=(uint64_t)(&origin);
  unlock1(); 
  return new_thread;
}
void thread_join(thread_t *other) 
{
  while (1) 
  {
    lock1();   
    if (other->state!=TH_join) 
    {
      unlock1();
      continue;
    }
    break;
  }
  other->prev->next=other->next;
  other->next->prev=other->prev;
  mem_free(other);
  unlock1();
}
void thread_schedule() 
{
  switch_thread(current_t->next);
}
void switch_thread(thread_t *other) 
{
  if (other==current_t) {return;}
  thread_t *previous=current_t;
  current_t=other;
  thread_switch(&previous->sp, other->sp);
}
thread_t* thread_current() {return current_t;}


