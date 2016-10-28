#include "test.h"
#include "mem_map.h"
#include "buddy_alloc.h"

void test_buddy() 
{
  unsigned long addr2 = alloc_buddy(2);
  printf("ALLOCATED: 0x%lx...0x%lx\n", addr2, addr2 + (1 << 2) * PAGE_SIZE);
  unsigned long addr3 = alloc_buddy(3);
  printf("ALLOCATED: 0x%lx...0x%lx\n", addr3, addr3 + (1 << 3) * PAGE_SIZE);
  free_buddy(addr2);
  printf("RELEASED:  0x%lx...0x%lx\n", addr2, addr2 + (1 << 2) * PAGE_SIZE);
  free_buddy(addr3);
  printf("RELEASED:  0x%lx...0x%lx\n", addr3, addr3 + (1 << 3) * PAGE_SIZE);
  addr2 = alloc_buddy(2);
  printf("ALLOCATED: 0x%lx...0x%lx\n", addr2, addr2 + (1 << 2) * PAGE_SIZE);
  addr3 = alloc_buddy(3);
  printf("ALLOCATED: 0x%lx...0x%lx\n", addr3, addr3 + (1 << 3) * PAGE_SIZE);
  free_buddy(addr2);
  printf("RELEASED:  0x%lx...0x%lx\n", addr2, addr2 + (1 << 2) * PAGE_SIZE);
  free_buddy(addr3);
  printf("RELEASED:  0x%lx...0x%lx\n", addr3, addr3 + (1 << 3) * PAGE_SIZE);
}
