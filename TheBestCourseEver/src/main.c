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

        disable_ints();
	idt_init();
	initialize_contr();
	__asm__ volatile ("int $0" );
	__asm__ volatile ("int $1" );
	
        idt_init();
	initialize_contr();
        enable_ints();

	pit_pit(1);
	
	while (1);
}
