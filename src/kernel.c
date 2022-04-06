#include <libc.h>
#include <i686.h>
#include <keyboard.h>
#include <terminal.h>


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

volatile int i = 0;

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	keyboard_init();
	/*init_gdt();
	idt_init();*/

	//int27();
	for(;;)
	{
		
		showChars();
		/*if (i == 0)
			terminal_writestring("i = 0");
		else
			terminal_writestring("seex");*/
	}
}

__attribute__((interrupt))
void keyboard_interrupt(struct interrupt_frame *f)
{
	(void) f;

	//terminal_writestring("Am primit un interrupt de la tastatura\nCe tare!\n");

	i = 1;
}
