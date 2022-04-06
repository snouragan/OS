#include <libc.h>
#include <i686.h>

struct gdt_entry gdt_entries[3];

struct gdt gdt = {
	.size = sizeof(gdt_entries) - 1,
	.address = (uint32_t) gdt_entries,
};

__attribute__((optimize("O0")))
static void wait();

void init_gdt()
{
	gdt_entries[0] = (struct gdt_entry) { .access = 0 };
	GDT_ENTRY_PUT_LIMIT(gdt_entries[0], 0);
	GDT_ENTRY_PUT_BASE(gdt_entries[0], 0);

	gdt_entries[1] = (struct gdt_entry) { .access = 0x9A };
	GDT_ENTRY_PUT_LIMIT(gdt_entries[1], 0xFFFFFFFF);
	GDT_ENTRY_PUT_BASE(gdt_entries[1], 0);

	gdt_entries[2] = (struct gdt_entry) { .access = 0x92 };
	GDT_ENTRY_PUT_LIMIT(gdt_entries[2], 0xFFFFFFFF);
	GDT_ENTRY_PUT_BASE(gdt_entries[2], 0);

	lgdt(((uint32_t) &gdt));
}

static void pic_init()
{
	uint8_t state1, state2;

	state1 = inb(0x21);
	state2 = inb(0xA1);

	outb(0x20, 0x11);
	wait();
	outb(0xA0, 0x11);
	wait();
	outb(0x21, 0x20);
	wait();
	outb(0xA1, 0x28);
	wait();
	outb(0x21, 4);
	wait();
	outb(0xA1, 2);
	wait();
	outb(0x21, 1);
	wait();
	outb(0xA1, 1);
	wait();

	outb(0x21, state1);
	outb(0xA1, state2);
}


__attribute__((optimize("O0")))
static
void wait()
{
	int i;

	for (i = 0; i < 0xf0000; i++)
		;
}

struct idt_entry idt_entries[256];

struct idt idt = {
	.size = sizeof(idt_entries) - 1,
	.address = (uint32_t) idt_entries,
};

void idt_init()
{

	idt_entries[0x21] = (struct idt_entry) {
		.zero = 0,
		.attr = IDT_ATR_PR | IDT_ATR_RING0 | IDT_ATR_TRAP32 /*0x8E*/, // temp
		.selector = 2 << 3,
	};
	IDT_ENTRY_PUT_OFFSET(idt_entries[0x21], (uint32_t) keyboard_interrupt);

	lidt((uint32_t) &idt);

	pic_init();

}
