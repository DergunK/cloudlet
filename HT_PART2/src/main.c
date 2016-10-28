static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

#include "desc.h"
#include "ints.h"
#include "print1.h"
#include "print.h"
#include "interrupts.h"
#include "pit.h"
#include "mem_map.h"
#include "buddy_alloc.h"
#include "test.h"


void main(void)
{
	qemu_gdb_hang();
	/*print_string("Hello World!\n");


	idt_init();
	__asm__ volatile ("int $0" );
	__asm__ volatile ("int $31" );
	initialize_contr();


        enable_ints();
	init_pit(2);*/

     get_memory_map();
     print_memory_map();

	printf("\nBuddy test.\n");
	init_buddy();
	test_buddy();
	printf("Finished.\n");

    //init_buddy_allocator();
  //  init_paging();

//test_buddy_allocator();
	
	while (1);
}



