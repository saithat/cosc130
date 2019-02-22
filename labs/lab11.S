//Sai Thatigotla
.section .rodata
hexin: .asciz " %lx"
table: .asciz "    Level   Index  Byte  Offset\n"
line: .asciz "VPN[%03d]  =    %d    (%d)\n"
PO: .asciz "PO	= %x\n"
usage: .asciz "Usage: ./lab11 0x<address> \n"
.section .text
.global main
main:
	addi	sp, sp, -32
	sd		ra, 0(sp)
	sd		s0, 8(sp)
	sd		s1, 16(sp)

	li		t0, 2
	bne		a0, t0, 3f	//if argc != 2

	mv		a0, a1
	ld		a0, 8(a0)

	la		a1, hexin

	addi	a2, sp, 24

	call	sscanf@plt //hex is now stored on stack at sp=24

	la		a0, table

	call	printf@plt

	ld		s0, 24(sp) //loaded hex

	li		s1, 3

1:
	ble		s1, zero, 2f
	li		t0, 9
	mul		t0, s1, t0
	addi	t0, t0, 3		//e.g 9x3(or whatever s1 is) = 27 + 3 = 30 (amount to right shift)
	srl		t1, s0, t0
	andi	a2, t1, 511
	addi	a1, s1, -1
	li		t0, 8
	mul		a3, a2, t0
	la		a0, line
	call	printf@plt
	addi	s1, s1, -1
	j		1b
2:
	li		t0, 0xfff
	and		a1, s0, t0
	la		a0, PO

	call	printf@plt
	j		4f
3:
	la		a0, usage
	call	printf@plt
4:
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	ld		s1, 24(sp)
	addi	sp, sp, 32
