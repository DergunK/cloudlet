#include "task3.h"
#include "task2.h"
#include "ioport.h"
#include "stdint.h"
#include "ints.h"



void pit_pit(uint64_t freq) 
{
  uint16_t init = 1193182 / freq;
  out8(PCP, (2 << 1) | 1<<4 | 1<<5);
  out8(PDP,  (init ) & 0xff);
  out8(PDP,  ((init & 0xff) >>8));
  out8(MDP, 0xff);
  out8(SDP, 0xff);
}
