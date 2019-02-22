.section .rodata
prompt: .asciz "Enter min and max: "
input: .asciz "%d %d"
output:	.asciz	"%d\n"
.section .data
.global main

main:

	addi	sp, sp, -16
	sd		ra, 0(sp)
	call	printf@plt
	la		a0, input
	addi	a1, sp, 8
	addi	a2, sp, 12
	call	scanf@plt
	lw		a0, sp, 8
	lw		a1, sp, 12
	call	GetRandom
	mv		a1, a0
	la		a0, output
	call	printf@plt
	ld		ra, 0(sp)
	addi	sp, sp, 16
	ret

GetRandom:
	addi	sp, sp, -16
	sd		ra, 0(sp)

	// min + rand() %(max - min + 1 )

	call	rand@plt
	//a0				//a0 = random number
	lw		a1, 8(sp)	//a1 = min
	lw		a2, 12(sp)	//a2 = max

	sub		a2, a2, a1	//a2 = max - min
	addi	a2, a2, 1	//a2 = max - min + 1
	rem		a0, a0, a2	//a0 a0 % a2
	add		a0, a0, a1	//a0 = min + rand() % (max-min+1)

	addi	sp, sp ,16
	la		ra, 0(sp)
	ret
