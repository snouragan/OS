#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <keyboard.h>
#include <io.h>
#include <string.h>
#include <gdt.h>
#include <terminal.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#define xprint(X) xprint(X, 8)

extern struct gdt_entry gdt_entries[3];

void showBytes(void) 
{
	char da;
	da = keyboard_key();
        xprint(da);
        terminal_putchar('\n');
}

void showChars(void)
{
	char key;
	key = keyboard_showKey();
	if(key != 0x00)  
	{
		terminal_putchar(key);
	}

}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	keyboard_init();
	// init_gdt();
	// idt_init();
	for(;;)
	{
		//showBytes();
		showChars();
	}
}

__attribute__((interrupt))
void keyboard_interrupt(struct interrupt_frame *f)
{
	(void) f;

	terminal_writestring("Am primit un interrupt de la tastatura\nCe tare!\n");
}
