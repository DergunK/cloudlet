#include "ioport.h"
#include "task1.h"


void initialization()
{
  out8(bPORT+1,0);//отключаем прерывания
  out8(bPORT+3,10);//задаём коэффициент деления
  out8(bPORT+0,1);//младший байт
  out8(bPORT+1,0);//старший байт
  out8(bPORT+3,3);//формат кадра
}


void print_byte(char c)
{
  while (in8(bPORT + 5) && 1<<5 == 0);
    out8(bPORT, c);
}
void print_string(const char* str)
{
  for (int i = 0; str[i]; ++i) 
  {
    print_byte((uint8_t) str[i]);
  }
}




