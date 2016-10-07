static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

#include "desc.h"
#include "ints.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

void main(void)
{
	qemu_gdb_hang();
	print_string("Hello World!\n");

disable_ints();
	idt_init();
	initialize_contr();
	__asm__ volatile ("int $1" );
	__asm__ volatile ("int $3" );

//enable_ints();

	pit_pit(10);
	
	while (1);
}
