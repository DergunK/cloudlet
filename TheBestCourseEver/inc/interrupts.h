#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#define MCP 0x20
#define MDP 0x21
#define SCP 0xA0
#define SDP 0xA1
#define FMD 32
#define FSD 40
#define LMD 39
#define LSD 47
#define N_in 33

struct idt_ptr
{
  uint16_t offset;
  uint16_t segment_sel;
  uint16_t type;
  uint16_t offset2;
  uint32_t offset3;
  uint32_t reserved;
} __attribute__((packed));

void idt_init();
void initialize_contr();


#endif


