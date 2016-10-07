#ifndef __PIT_H__
#define __PIT_H__

#include "stdint.h"
#include "ioport.h"
#define PCP 0x43
#define PDP 0x40

void pit_pit(uint16_t freq);

#endif 
