#include <terminal.h>

#include <libc.h>
#include <i686.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_putchar(char c) 
{
	switch (c) {
		case '\t': 
			terminal_column = terminal_column + 4;
			break;

		case '\n':
			++terminal_row;
			terminal_column = -1;
			for(long unsigned int i = terminal_column; i < VGA_WIDTH; i++)
				terminal_putentryat('\0', terminal_color, terminal_column, terminal_row);
			break;

		case '\b':
			--terminal_column;
			terminal_putentryat('\0', terminal_color, terminal_column, terminal_row);   
			--terminal_column;
			break;

		case 17:
			--terminal_row;
			--terminal_column;
			break;

		case 18:
			--terminal_column;
			--terminal_column;
			break;

		case 19:
			++terminal_column;
			--terminal_column;
			break;

		case 20:
			++terminal_row;
			--terminal_column;
			break;


		default:
			terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	
	}

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		++terminal_row;
	}
	if (terminal_row == VGA_HEIGHT)
		terminal_row = 0;
	update_cursor(terminal_column, terminal_row);
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void xprint(unsigned long long x, int biti)
{
	for (int i = biti - 1; i >= 0; i--)
		terminal_putchar('0' + ((x >> i) & 1));
	terminal_putchar('\n');
}



