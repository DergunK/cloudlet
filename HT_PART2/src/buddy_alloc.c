#include "buddy_alloc.h"
#include "mem_map.h"
#include <limits.h>

uint8_t num_levels;
extern uint64_t* level_heads;
struct buddy_page* desc;

void set_desc_pointer(uint64_t id, uint64_t next, uint64_t prev) 
{
  desc[id].next_page = next;
  desc[id].prev_page = prev;
}

void set_desc(uint64_t id, void* ctl, uint64_t next, uint64_t prev, uint8_t level, uint8_t free, uint8_t height) 
{
  desc[id].block_ctl = ctl;
  desc[id].next_page = next;
  desc[id].prev_page = prev;
  desc[id].level = level;
  desc[id].free = free;
  desc[id].height = height;
}

void remove_buddy(uint64_t id, uint8_t level) 
{
  if (desc[id].next_page != id) 
  {
    desc[desc[id].next_page].prev_page = desc[id].prev_page;
    desc[desc[id].prev_page].next_page = desc[id].next_page;
    level_heads[level] = desc[id].next_page;
    set_desc_pointer(id, id, id);
  } 
  else level_heads[level] = ULLONG_MAX;
}

void add_buddy(uint64_t id, uint8_t level) 
{
  if (level_heads[level] != ULLONG_MAX) 
  {
    set_desc_pointer(id, level_heads[level], desc[level_heads[level]].prev_page);
    desc[desc[id].next_page].prev_page = id;
    desc[desc[id].prev_page].next_page = id;
  }
  level_heads[level] = id;
}

void free_buddy(uint64_t page_ptr) 
{
  uint64_t id = page_ptr / PAGE_SIZE;
  desc[id].free = 1;
  while (desc[id].level < desc[id].height && desc[((id) ^ (1 << (desc[id].level)))].free)
  {
    uint64_t buddy_id = ((id) ^ (1 << (desc[id].level)));
    remove_buddy(buddy_id, desc[buddy_id].level);
    if (id > buddy_id) 
    {
      uint64_t tmp = id;
      id = buddy_id;
      buddy_id = tmp;
    }
    desc[buddy_id].free = 0;
    desc[id].level++;
  }
  add_buddy(id, desc[id].level);
}

uint64_t find_buddy(uint8_t level) 
{
  while (level < num_levels && level_heads[level] == ULLONG_MAX) level++;
  if (level >= num_levels) return ULLONG_MAX;
  return level_heads[level];
}

void occupy_buddy(uint64_t id, uint8_t level) 
{
  while (level < desc[id].level) 
  {
    remove_buddy(id, desc[id].level);
    desc[id].level--;
    desc[((id) ^ (1 << (desc[id].level)))].free = 1;
    desc[((id) ^ (1 << (desc[id].level)))].level = desc[id].level;
    add_buddy(id, desc[id].level);
    add_buddy(((id) ^ (1 << (desc[id].level))), desc[id].level);
  }
  desc[id].free = 0;
  remove_buddy(id, level);
}

uint64_t alloc_buddy(uint8_t level) 
{
  uint64_t id = find_buddy(level);
  if (id == ULLONG_MAX) return 0;
  occupy_buddy(id, level);
  return (uint64_t) id * PAGE_SIZE;
}

void init_buddy(void) 
{
  num_levels = 0;
  uint32_t memmap_length=memmap_lng;
  uint64_t page_number = memory_map_sz / PAGE_SIZE;
  for (uint32_t i = 0; i < memmap_length; i++) 
  {
    if (memory_map[i].type == MEMMAP_TYPE_AVAILABLE && page_number * sizeof(struct buddy_page) <= memory_map[i].length) 
    {
      desc = (struct buddy_page*) (memory_map[i].begin + SHIFTED_FROM_HOLE);
      add_Kernel( memory_map[i].begin, page_number * sizeof(struct buddy_page),  MEMMAP_TYPE_KERNEL);
      memory_map[i].begin += page_number * sizeof(struct buddy_page);
      memory_map[i].length -= page_number * sizeof(struct buddy_page);
      memmap_length++;
      break;
    }
  }
  page_number = 0;
  for (uint32_t i = 0; i < memmap_length; i++) 
  {
    if (memory_map[i].type != MEMMAP_TYPE_AVAILABLE) continue;
    uint64_t page_left = memory_map[i].begin;
    uint64_t page_right = page_left + memory_map[i].length;
    if (page_left % PAGE_SIZE) page_left = (page_left / PAGE_SIZE + 1) * PAGE_SIZE;
    page_right -= page_right % PAGE_SIZE;
    if (page_right <= page_left) continue;
    memory_map[i].type = MEMMAP_TYPE_ALLOC;
    page_number += (page_right - page_left) / PAGE_SIZE;
    for (uint8_t j = 0; (1ULL << j) * PAGE_SIZE <= memory_map_sz; j++) level_heads[j] = ULLONG_MAX;
    while (page_left < page_right) 
    {
      uint8_t height = 0;
      uint64_t id = page_left / PAGE_SIZE;
      while (page_left + PAGE_SIZE * (1ULL << (height + 1)) <= page_right && id <= ((id) ^ (1 << (height)))) height++;
      if (num_levels < height + 1) num_levels = height + 1;
      uint64_t my_id = id + (1ULL << height);
      while (id < my_id) 
      {
        set_desc(id, 0, id, id, height, 0, UCHAR_MAX);
	id++;
      }
      id = page_left / PAGE_SIZE;
      desc[id].height = height;
      free_buddy(page_left);
      page_left += PAGE_SIZE * (1ULL << height);
    }
  }
  printf("Buddy allocator: %lld pages.\n", page_number);
}
