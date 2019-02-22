//Sai Thatigotla
.section .rodata
output:.asciz "Result: %d %c %d = %d\n"
error: .asciz "Unknown operator '%c'\n"
int: .asciz "%d"
char: .asciz "%c"
.section .text
.global main
main:
	addi	sp, sp, -32
	sd		ra, 0(sp)  //return address

	mv		a0, a1
	sd		a0, 8(sp)  //argv saved on stack

	ld		a0, 8(a0)  //skips argv[0]

	la		a1, int

	addi	a2, sp, 16 //pointing a2 to location of future int or char
						
						/* 0-7: ra
						   8-15: **argv
						   16-19: num1
						   20: char
						   21-24: word
						   25-28: result */

	call	sscanf@plt

	lw		s1, 16(sp) //loading int from stack into s0
	ld		a0, 8(sp)  //loading argv from stack

	ld		a0, 16(a0) //skipping argv[1]

	la		a1, char
	addi	a2, sp, 16 //pointing a2 to stack again

	call	sscanf@plt

	lb		s2, 16(sp)
	ld		a0, 8(sp)
	ld		a0, 24(a0)

	la		a1, int
	addi	a2, sp, 16

	call	sscanf@plt


	lw		a3, 16(sp)	//loading value from stack to a3
	mv		a2, s2
	mv		a1, s1

	mv		a0, a1  //move values into proper arguments for ABI
	mv		a1, a2
	mv		a2, a3

	sw		a0, 16(sp)
	sb		a1, 20(sp)
	sw		a2, 21(sp)
	
	li		t0, '+'
	beq		a1, t0, 1f

	li		t0, '-'
	beq		a1, t0, 2f

	li		t0, 'x'
	beq		a1, t0, 3f

	li		t0, '/'
	beq		a1, t0, 4f

	li		t0, '%'
	beq		a1, t0, 5f

	la		a0, error
	call	printf@plt

	ld		ra, 0(sp)
	addi	sp, sp, 28
	ret

1:
	call	Add
	j		6f
2:
	call	Sub
	j		6f
3:
	call	Mult
	j		6f
4:
	call	Div
	j		6f
5:
	call	Mod

6:
	mv		a4, a0  //moving a0 into result and retruveing values from stack into args for printf
	lw		a1, 16(sp)
	lb		a2,	20(sp)
	lw		a3, 21(sp)


	la		a0, output

	call	printf@plt

	ld		ra, 0(sp)
	addi	sp, sp, 28
	ret


Add:
	add		a0, a0, a2
	ret
Sub:
	sub		a0, a0, a2
	ret
Mult:
	mul		a0, a0, a2
	ret
Div:
	div		a0, a0, a2
	ret
Mod:
	beq		a2, zero, 7f  //if right value is 0
	j		8f
7:
	li		a0, -1
	ret
8:
	rem		a0, a0, a2
	ret
