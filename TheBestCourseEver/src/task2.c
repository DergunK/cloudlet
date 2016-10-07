#include "memory.h"
#include "desc.h"
#include "task1.h"
#include "task2.h"
#include "ints.h"
#include "ioport.h"

extern uint64_t interrupt[];

struct idt_ptr idt_table[N_in];
struct desc_table_ptr desc_table;

char *test_error[4] = 
{ 
  " \n",
  " №0: Деление на нуль.\n", 
  " №1: Бесконечность делить на бесконечность.\n", 
  " №2: Просто обычная ошибка. :( \n"
};
void idt_init()
{
  desc_table.size=sizeof(struct idt_ptr)*N_in -1;
  desc_table.addr=(uint64_t) idt_table;
  write_idtr(&desc_table);
  for (int i = 0; i < N_in; i++)
  {
    idt_table[i].offset=((uint64_t)interrupt[i]) & 0xFFFF;
    idt_table[i].segment_sel=KERNEL_CS;
    idt_table[i].flags=1<<15 | (14 << 8);
    idt_table[i].offsett=(((uint64_t)interrupt[i]) >>16) & 0xFFFF;
    idt_table[i].offsettt=(((uint64_t)interrupt[i])>>32);
    idt_table[i].reserved=0;
  }

}


void int_handler(uint64_t int_id) 
{

  print_string("Interrupt ");
  print_string(test_error[int_id]);
  
 if (FMD <= int_id && int_id <= LMD)
    out8(MCP, 1<<5);
  if ((FSD) <= int_id && int_id <= (LSD)) 
  {
    out8(MCP, 1<<5);
    out8(SCP, 1<<5);
  }

}

void initialize_contr()
{
//disable_ints();
  out8(MCP , 1<<0 | (1 << 4));
  out8(MDP,FMD);//начальные условия
  out8(MDP,1<<2);
  out8(MDP,1);
  out8(SCP, 1<<0 | (1 << 4));
  out8(SDP,FSD);//начальные условия
  out8(SDP,2);
  out8(SDP,1);
  out8(MDP,0xFF);//маскировка
  out8(SDP,0xFF);//маскировка
//enable_ints();
}




