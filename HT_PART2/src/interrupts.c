#include "memory.h"
#include "desc.h"
#include "print1.h"
#include "interrupts.h"
#include "ints.h"
#include "ioport.h"

extern uint64_t interrupt[];

struct idt_ptr idt_table[N_in];
struct desc_table_ptr desc_table;

struct structura 
{
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rbp;
  uint64_t rdi;
  uint64_t rsi;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;
  uint64_t int_code;
  uint64_t error_code;
}__attribute__((packed));

char *test_error[32] = 
{ 
  " №0: Деление на нуль.\n", 
  " №1: Бесконечность делить на бесконечность.\n", 
  " №2: Просто обычная ошибка. :( \n",
  " №3: Просто обычная ошибка. :( \n",
  " №4: Ещё одно прерывание.\n",
  " №5: Деление на нуль.\n", 
  " №6: Бесконечность делить на бесконечность.\n", 
  " №7: Просто обычная ошибка. :( \n",
  " №8: Ещё одно прерывание.\n",
  " №9: Деление на нуль.\n", 
  " №10: Бесконечность делить на бесконечность.\n", 
  " №11: Просто обычная ошибка. :( \n",
  " №12: Ещё одно прерывание.\n",
  " №13: Деление на нуль.\n", 
  " №14: Бесконечность делить на бесконечность.\n", 
  " №15: Просто обычная ошибка. :( \n",
  " №16: Ещё одно прерывание.\n",
  " №17: Деление на нуль.\n", 
  " №18: Бесконечность делить на бесконечность.\n", 
  " №19: Просто обычная ошибка. :( \n",
  " №20: Ещё одно прерывание.\n",
  " №21: Деление на нуль.\n", 
  " №22: Бесконечность делить на бесконечность.\n", 
  " №23: Просто обычная ошибка. :( \n",
  " №24: Ещё одно прерывание.\n",
  " №25: Деление на нуль.\n", 
  " №26: Бесконечность делить на бесконечность.\n", 
  " №27: Просто обычная ошибка. :( \n",
  " №28: Ещё одно прерывание.\n",
  " №29: Деление на нуль.\n", 
  " №30: Бесконечность делить на бесконечность.\n", 
  " №31: Просто обычная ошибка. :( \n"
};


void idt_init()
{
  desc_table.size=sizeof(struct idt_ptr)*N_in -1;
  desc_table.addr=(uint64_t) idt_table;
  write_idtr(&desc_table);
  for (int i = 0; i < N_in; i++)
  {
    idt_table[i].offset=(interrupt[i]) & 0xFFFF;
    idt_table[i].segment_sel=KERNEL_CS;
    idt_table[i].type=1<<15 | (14 << 8);
    idt_table[i].offset2=((interrupt[i]) >>16) & 0xFFFF;
    idt_table[i].offset3=((interrupt[i])>>32);
    idt_table[i].reserved=0;
  }
}


void int_handler(struct structura* str) 
{
  if (str->int_code < 32) 
  {
    print_string("Interrupt: ");
    print_string(test_error[str->int_code]);
  }
  else
  {
    print_string("Interrupt: PIT\n");
    out8(SCP, 1<<5);
    out8(MCP, 1<<5);
  }
}

void initialize_contr()
{
disable_ints();
  out8(MCP , 1 | (1 << 4));
  out8(MDP,FMD);//начальные условия
  out8(MDP,1<<2);
  out8(MDP,1);
  out8(SCP, 1 | (1 << 4));
  out8(SDP,FSD);//начальные условия
  out8(SDP,2);
  out8(SDP,1);
  out8(MDP,0xFF);//маскировка
  out8(SDP,0xFF);//маскировка
enable_ints();
}
