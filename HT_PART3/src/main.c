#include <serial.h>
#include <memory.h>
#include <balloc.h>
#include <paging.h>
#include <debug.h>
#include <alloc.h>
#include <print.h>
#include <ints.h>
#include <time.h>
#include <threads.h>
#include "lock.h"
#include "pit.h"
#include "interrupts.h"
#include "test.h"

static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}


void main(void *bootstrap_info)
{
	qemu_gdb_hang();

	serial_setup();
	ints_setup();
	init_thread_system();
	time_setup();


	balloc_setup(bootstrap_info);
	paging_setup();
	page_alloc_setup();
	mem_alloc_setup();
	kmap_setup();
	enable_ints();

	
	printf("Tests Begin\n");
        testThreads();
	printf("Tests Finished\n");

	while (1);
}
