.section .text
.global lgdt
.global lidt

lgdt:
	lgdt (%ecx)
	ret

lidt:
	lidt (%ecx)
	ret
