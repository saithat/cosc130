//Sai Thatigotla
.section .rodata

/*left: .asciz "%d"
right: .asciz "%d"*/
prompt: .asciz "Enter a left and right operand: "
input: .asciz "%d %d"
output: .asciz "%d / %d = %d\n"
.section .text
.global main

main:

	addi	sp, sp, -16
	sd		ra, 0(sp)

	la		a0, prompt
	call	printf@plt
	la		a0, input
	addi	a1, sp, 8
	addi	a2, sp, 12
	call	scanf@plt
	lw		a1, 8(sp)
	lw		a2, 12(sp)
	div		a3, a1, a2

	li		t0, -1			//tmp values to compare when divide by zero
	li		t1, 0

	beq		t0, a3, 2f		//when division result is -1
	
	la		a0, output
	call	printf@plt

	j		0f

2:
	beq		t1, a2, 1f		//if denominator is 0
	la		a0, output
	call	printf@plt

	j		0f

1:
	mul		a3, a3, t1		//make result 0
	la		a0, output
	call	printf@plt

0:
	
    ld		ra, 0(sp)
	addi	sp, sp, 16
	ret
