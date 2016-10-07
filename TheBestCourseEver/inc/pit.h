#ifndef __PIT_H__
#define __PIT_H__

#include "stdint.h"
#include "ioport.h"
#define PCP 0x43
#define PDP 0x40

void init_pit(uint8_t);

#endif 
