#ifndef GDT_H
#define GDT_H

#include <libc.h>

__attribute__((fastcall))
uint8_t inb(unsigned int port);
__attribute__((fastcall))
uint16_t inw(unsigned int port);
__attribute__((fastcall))
uint32_t inl(unsigned int port);

__attribute__((fastcall))
void outb(unsigned int port, uint8_t data);
__attribute__((fastcall))
void outw(unsigned int port, uint16_t data);
__attribute__((fastcall))
void outl(unsigned int port, uint32_t data);

struct gdt {
	uint16_t size;
	uint32_t address;
} __attribute__((packed));


struct gdt_entry {
	uint16_t limit_1;
	uint16_t base_1;
	uint8_t base_2;
	uint8_t access;
	unsigned int limit_2 : 4;
	unsigned int flags : 4;
	uint8_t base_3;
} __attribute__((packed));

enum {
	GDT_ACC_RW = 0x02,
	GDT_ACC_DC = 0x04,
	GDT_ACC_EX = 0x08,
	GDT_ACC_S  = 0x10,
	GDT_ACC_RING0 = 0,
	GDT_ACC_RING1 = 1 << 5,
	GDT_ACC_RING2 = 2 << 5,
	GDT_ACC_RING3 = 3 << 5,
	GDT_ACC_PR = 0x80,

	GDT_FLG_BLOCKS = 0x8,
	GDT_FLG_32BIT = 0x4,
};

#define GDT_ENTRY_PUT_LIMIT(ENTRY, LIMIT) \
	((ENTRY).limit_1 = (uint16_t) (LIMIT) & 0xFFFF, \
		(ENTRY).limit_2 = (uint8_t) (((LIMIT) & 0xF0000) >> 16))

#define GDT_ENTRY_PUT_BASE(ENTRY, BASE) \
	((ENTRY).base_1 = (uint16_t) (BASE) & 0xFFFF, \
		(ENTRY).base_2 = (uint8_t) ((BASE) & 0xFF0000 >> 16), \
		(ENTRY).base_3 = (uint16_t) ((BASE) & 0xFF000000 >> 24))

#define GDT_ENTRY_GET_LIMIT(ENTRY) \
	((ENTRY).limit_1 + (ENTRY).limit_2 << 16)

#define GDT_ENTRY_GET_BASE(ENTRY, BASE) \
	((ENTRY).base_1 + (ENTRY).base_2 << 16 + (ENTRY).base_3 << 24);

__attribute__((fastcall))
void lgdt(uint32_t location);
void init_gdt();

struct interrupt_frame {
	uint16_t ip;
	uint16_t cs;
	uint16_t flags;
	uint16_t sp;
	uint16_t ss;
} __attribute__((packed));

__attribute__((interrupt))
void keyboard_interrupt(struct interrupt_frame*);

struct idt {
	uint16_t size;
	uint32_t address;
} __attribute__((packed));

struct idt_entry {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t zero;
	uint8_t attr;
	uint16_t offset_2;
} __attribute__((packed));

enum {
	IDT_ATR_PR = 0x80,

	IDT_ATR_RING0 = 0,
	IDT_ATR_RING1 = 1 << 5,
	IDT_ATR_RING2 = 2 << 5,
	IDT_ATR_RING3 = 3 << 5,

	IDT_ATR_S  = 0x10,

	IDT_ATR_TASK32 = 0x05,
	IDT_ATR_TRAP16 = 0x06,
	IDT_ATR_INTR16 = 0x07,
	IDT_ATR_TRAP32 = 0x0E,
	IDT_ATR_INTR32 = 0x0F,
};

#define IDT_ENTRY_PUT_OFFSET(ENTRY, OFFSET) \
	((ENTRY).offset_1 = (uint16_t) (OFFSET) & 0xFFFF,\
	(ENTRY).offset_2 = (uint16_t) ((OFFSET) >> 16))

#define IDT_ENTRY_GET_OFFSET(ENTRY) \
	((ENTRY).offset_1 + (ENTRY).offset_2 << 16)


__attribute__((fastcall))
void lidt(uint32_t location);
void idt_init();

__attribute__((fastcall))
void int27(void);

#endif
