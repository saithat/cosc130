.section .rodata
char: .asciz "%c"
int: .asciz "%d"
output: .asciz "Your number is: %d %c %d \n"
.section .text
.global main
main:

	addi	sp, sp, -28
	sd		ra, 0(sp)

	mv		a0, a1

	sd		a0, 8(sp)

	ld		a0, 8(a0)

	la		a1, int
	
	addi	a2, sp, 16
	
	call	sscanf@plt

	lw		s1, 16(sp)

	ld		a0, 8(sp)
	ld		a0, 16(a0)
	la		a1, char
	addi	a2, sp, 16

	call	sscanf@plt

	lb		s2, 16(sp)
	ld		a0, 8(sp)
	ld		a0, 24(a0)
	la		a1, int
	addi	a2, sp, 16

	call	sscanf@plt

	lw		a3, 16(sp)
	mv		a2, s2
	mv		a1, s1
	la		a0, output

	call	printf@plt

	ld		ra, 0(sp)
	addi	sp, sp, 28
	ret
