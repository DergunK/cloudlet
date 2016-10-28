#include "print.h"
#include "print1.h"
#include "mem_map.h"
#include "memory.h"


#include <stdint.h>


extern uint32_t mliboot_inf;


extern m_m_e_t memory_map[];
extern m_e_t  memmap[];
extern uint64_t memory_map_size;
m_m_e_t memory_map[MEMMAP_MAX_SIZE];
m_e_t memmap[MEMMAP_MAX_SIZE*2];
uint64_t memory_map_size = 0;
extern uint8_t text_phys_begin[];
extern uint8_t bss_phys_end[];

void add_Kernel(uint64_t base_addr, uint64_t length, uint32_t type) 
{
  m_m_e_t* entry = memory_map + memory_map_size;
  memory_map_size++;
  entry->begin  = base_addr;
  entry->end    = base_addr + length - 1;
  entry->length = length;
  entry->type   = type;
}

void get_memory_map() 
{
  uint64_t mliboot_inf64 = (uint64_t)mliboot_inf;

  m_m_e_t* kernel_my_entry = memory_map + memory_map_size;
  memory_map_size++;

  kernel_my_entry->begin  = (uint64_t)text_phys_begin;
  kernel_my_entry->end    = (uint64_t)bss_phys_end;
  kernel_my_entry->length = (uint64_t)kernel_my_entry->end - (uint64_t)kernel_my_entry->begin + 1;
  kernel_my_entry->type   = MEMMAP_TYPE_KERNEL;

  uint32_t memmap_length = *((uint32_t*)mliboot_inf64 + 11);
  uint64_t memmap_base_addr = (uint64_t)(*(uint64_t*)(mliboot_inf64 + 48));
	
  for (uint64_t memmap_ptr = memmap_base_addr; memmap_ptr < memmap_base_addr + memmap_length; ) 
  {
    m_e_t* entry = (m_e_t*)memmap_ptr;
    memmap_ptr += entry->size + sizeof(entry->size);

    uint64_t left  = entry->base_addr;
    uint64_t right = entry->base_addr + entry->length - 1;
		
    if (right < kernel_my_entry->begin || left > kernel_my_entry->end) 
    {
      add_Kernel(left, entry->length, entry->type);
    } 
    else if (left < kernel_my_entry->begin && kernel_my_entry->end < right) 
    {
      add_Kernel(left, kernel_my_entry->begin - left, entry->type);	
      add_Kernel(kernel_my_entry->end + 1, right - kernel_my_entry->end, entry->type);	
    } 
    else if (left < kernel_my_entry->begin) 
    {
      add_Kernel(left, kernel_my_entry->begin - left, entry->type);	
    } 
    else if (right > kernel_my_entry->end) 
    {
      add_Kernel(kernel_my_entry->end + 1, right - kernel_my_entry->end, entry->type);	
    }
  }
}

void printing(m_m_e_t entry, uint64_t num) 
{
printf("№%lli: 0x%llx-0x%llx", num, entry.begin, entry.end);
  switch (entry.type) 
  {
    case MEMMAP_TYPE_AVAILABLE:
      print_string(": available\n");
      break;
    case MEMMAP_TYPE_RESERVED:
      print_string(": reserved\n");      
      break;
    case MEMMAP_TYPE_KERNEL:
      print_string(": KerneL\n");
      break;
 }
}

void print_memory_map() 
{
  printf("Memory map!\n");

  int num = 0;
  for (uint64_t i = 1; i < 5; i++) 
  {
    printing(memory_map[i], num++);
  }
  printing(memory_map[0], num++);
  for (uint64_t i = 5; i < 8; i++) 
  {
    printing(memory_map[i], num++);
  }
 
}














