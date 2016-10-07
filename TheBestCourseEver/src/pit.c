#include "pit.h"
#include "interrupts.h"
#include "ioport.h"
#include "stdint.h"
#include "ints.h"

void init_pit(uint8_t freq) 
{
  out8(PCP,0x14);
  out8(PDP,freq);
  out8(PDP,freq>>8);
  out8(MDP, 0xfe);
}
