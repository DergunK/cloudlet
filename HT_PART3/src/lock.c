#include "lock.h"

int lock_count =0;

/*void lock() 
{
  __asm__ volatile ("cli" : : : "cc");
  lock_count++;
}

void unlock() 
{
  lock_count--; 
  if (lock_count == 0) 
  {
    __asm__ volatile ("sti" : : : "cc");
  }
}*/

void lock() 
{
  if (lock_count == 0) 
  {
    __asm__ volatile ("sti" : : : "cc");
  }
  lock_count = 1;
}

void unlock() 
{

   lock_count = 0;
    __asm__ volatile ("sti" : : : "cc");

}
