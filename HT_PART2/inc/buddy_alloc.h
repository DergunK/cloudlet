#ifndef __BUDDY_ALLOC_H__
#define __BUDDY_ALLOC_H__

#include "memory.h"
#include <stdint.h>

struct buddy_page 
{
  void* block_ctl;
  uint64_t next_page;
  uint64_t prev_page;
  uint8_t level;
  uint8_t free;
  uint8_t height;
};

extern struct buddy_page* desc;
void init_buddy(void);
uint64_t find_buddy(uint8_t level);
void occupy_buddy(uint64_t id, uint8_t level);
uint64_t alloc_buddy(uint8_t level);
void free_buddy(uint64_t page_ptr);
uint64_t virt_address(uint64_t p);
uint64_t phys_address(uint64_t p);

#endif
