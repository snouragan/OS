.section .text
.global lgdt
.global lidt
.global int27

lgdt:
	lgdt (%ecx)
	ret

lidt:
	lidt (%ecx)
	ret

int27:
	int $0x21
	ret
