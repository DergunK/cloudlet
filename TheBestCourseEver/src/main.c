static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

#include "desc.h"
#include "ints.h"
#include "print.h"
#include "interrupts.h"
#include "pit.h"

void main(void)
{
	qemu_gdb_hang();
	print_string("Hello World!\n");


	idt_init();
	__asm__ volatile ("int $0" );
	__asm__ volatile ("int $31" );
	initialize_contr();


        enable_ints();
	init_pit(2);
	
	while (1);
}
