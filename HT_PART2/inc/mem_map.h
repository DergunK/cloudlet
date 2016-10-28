#ifndef __MEM_MAP_H__
#define __MEM_MAP_H__

#include <print.h>
#include <memory.h>
#include <stdint.h>
#define MEMMAP_TYPE_KERNEL    0
#define MEMMAP_TYPE_AVAILABLE 1
#define MEMMAP_TYPE_RESERVED  2
#define MEMMAP_TYPE_ALLOC     3
#define MAX_MEMMAP_TABLE_LENGTH 64
#define MEMMAP_MAX_SIZE 32	
#define memory_map_sz 4294967296
#define memmap_lng 8

struct m_e 
{
  uint32_t size;
  uint64_t base_addr;
  uint64_t length;
  uint32_t type;
}__attribute__((packed));

struct m_m_e
{
  uint64_t begin;
  uint64_t end;
  uint64_t length;
  uint32_t type;
 #define MULTIBOOT_MEMORY_AVAILABLE              1
 #define MULTIBOOT_MEMORY_RESERVED               2
}__attribute__((packed));

typedef struct m_m_e m_m_e_t;
typedef struct m_e m_e_t;
extern struct m_e memmap[];
extern struct m_m_e memory_map[];
extern uint32_t memmap_length;
extern uint64_t memory_map_size;

void get_memory_map();
void print_memory_map();
void add_Kernel(uint64_t base_addr, uint64_t length, uint32_t type);

#endif 
