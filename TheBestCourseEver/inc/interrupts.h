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
#define N_in 32

struct idt_ptr
{
  uint16_t offset;
  uint16_t segment_sel;
  uint16_t flags;
  uint16_t offsett;
  uint32_t offsettt;
  uint32_t reserved;
} __attribute__((packed));

void idt_init();
void int_handler(uint64_t int_id);
void initialize_contr();
void unmask_master(uint8_t m);
void unmask_slave(uint8_t m);


#endif


