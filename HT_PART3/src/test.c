#include "test.h"
#include "print.h"
#include "lock.h"
#include "pit.h"
#include "interrupts.h"
#include <threads.h>

#define NUM_ITER 10

void testing(void *a) 
{
  for (int i = 0; i < NUM_ITER; ++i) 
  {
    lock1();
    //printf("Проверяем поток под номером %d: результат %d\n", *((int*)a), );
    printf("Проверяем поток под номером %d: результат = %d\n", *((int*)a), (*((int*)a))*i);
    unlock1();
  }
}

void testThreads() 
{
  
  printf("Каждый поток будет брать число от 0 до %d и умножать на свой номер.\n",NUM_ITER);
  int n1 = 1;
  int n2 = 2;
  int n3 = 3;
  thread_t *test_thread1 = thread_create(testing, &n1);
  thread_t *test_thread2 = thread_create(testing, &n2);
  thread_t *test_thread3 = thread_create(testing, &n3);
  idt_init();
  initialize_contr();
  init_pit(5);
  thread_join(test_thread1);
  thread_join(test_thread2);
  thread_join(test_thread3);
}



