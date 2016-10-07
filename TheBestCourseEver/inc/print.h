#ifndef __PRINT_H__
#define __PRINT_H__

#define bPORT 0x3f8

void initialization();
void print_byte(char c);
void print_string(const char* str);

#endif
