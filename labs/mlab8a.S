//Sai Thatigotla
//10/11/18
//mini lab 8a
.section .rodata

/*left: .asciz "%d"
right: .asciz "%d"*/
prompt: .asciz "Enter a left and right operand: "
input: .asciz "%d %d"
output: .asciz "%d + %d = %d\n"
.section .text
.global main

main:

	addi	sp, sp, -16
	sd		ra, 0(sp)		//saved return address in stack

	la		a0, prompt
	call	printf@plt
	la		a0, input
	addi	a1, sp, 8		//arguments 1 and 2 point to the "words" on the stack
	addi	a2, sp, 12
	call	scanf@plt
	//ld		ra, 0(sp)
	lw		a1, 8(sp)		//dereference arguments
	lw		a2, 12(sp)
	add		a3, a1, a2
	la		a0, output
	call	printf@plt		//printed output

    ld		ra, 0(sp)
	addi	sp, sp, 16		//reset return address and gave back memeory from stack to computer
	ret
