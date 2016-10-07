#include "pit.h"
#include "interrupts.h"
#include "ioport.h"
#include "stdint.h"
#include "ints.h"





void pit_pit(uint16_t freq) 
{
  out8(MDP, 0xff);
  out8(SDP, 0xff);
  uint16_t init = 1193182 / freq;
  out8(PCP, (2 << 1) | 1<<4 | 1<<5);
  out8(PDP,  (init ) & 0xff);
  out8(PDP,  ((init & 0xff) >>8));
  out8(MDP, 0xfe);
  out8(SDP, 0xfe);


}
