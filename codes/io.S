.section .text
.global inb
.global inw
.global inl
.global outb
.global outw
.global outl

inb:
	mov %ecx, %edx
	inb %dx

	ret
inw:
	mov %ecx, %edx
	inw %dx

	ret
inl:
	mov %ecx, %edx
	inl %dx

	ret

outb:
	mov %edx, %eax
	mov %ecx, %edx

	outb %dx

	ret


outw:
	mov %edx, %eax
	mov %ecx, %edx

	outw %dx

	ret


outl:
	mov %edx, %eax
	mov %ecx, %edx

	outl %dx

	ret


