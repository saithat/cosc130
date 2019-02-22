//Sai Thatigotla
.section .rodata
hexin: .asciz " %lx"
entry: .asciz "Page Table Entry: 0x%016lx \n"
Address: .asciz "Physical Address: 0x%016lx \n"
SET: .asciz "SET \n"
CLEAR: .asciz "CLEAR \n"
V: .asciz "Entry bits: \nBit V: "
R: .asciz "Bit R: "
W: .asciz "Bit W: "
X: .asciz "Bit X: "
U: .asciz "Bit U: "
G: .asciz "Bit G: "
A: .asciz "Bit A: "
D: .asciz "Bit D: "
Usage: .asciz "Usage: ./lab11ec 0x<address>\n"
.section .text
.global main
main:
	addi	sp, sp, -40
	sd		ra, 0(sp)
	sd		s0, 8(sp) //hex
	sd		s1, 16(sp) //result
	sd		s2, 24(sp) //ppn

	li		t0, 2
	bne		a0, t0, fail //if argc != 2

	mv		a0, a1
	ld		a0, 8(a0)

	la		a1, hexin

	addi	a2, sp, 32

	call	sscanf@plt //hex is now stored on stack at sp=24

	la		a0, entry
	ld		a1, 32(sp) 

	call	printf@plt

	ld		s0, 32(sp) //loaded hex

	li		s1, 0

	li		t0, 67108863  //right shifting page table entry, isolating, left shifting and or-ing with a new number set to 0
	srli	s2, s0, 28
	and		s2, s2, t0
	slli	s2, s2, 30
	or		s1, s1, s2

	li		t0, 511
	srli	s2, s0, 19
	and		s2, s2, t0
	slli	s2, s2, 21
	or		s1, s1, s2

	srli	s2, s0, 10
	and		s2, s2, t0
	slli	s2, s2, 12
	or		s1, s1, s2

	mv		a1, s1
	la		a0, Address
	call	printf@plt

	li		t1, 1     //isolating and testing entry bits
	andi	t0, s0, 1
	beq		t0, t1, 1f
	la		a0, V
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		2f
1:
	la		a0, V
	call	printf@plt
	la		a0, SET
	call	printf@plt
2:
	li		t1, 1 
	srli	t0, s0, 1
	andi	t0, t0, 1
	beq		t0, t1, 3f
	la		a0, R
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		4f
3:
	la		a0, R
	call	printf@plt
	la		a0, SET
	call	printf@plt
4:
	li		t1, 1
	srli	t0, s0, 2
	andi	t0, t0, 1
	beq		t0, t1, 5f
	la		a0, W
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		6f
5:
	la		a0, W
	call	printf@plt
	la		a0, SET
	call	printf@plt
6:
	li		t1, 1
	srli	t0, s0, 3
	andi	t0, t0, 1
	beq		t0, t1, 7f
	la		a0, X
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		8f
7:
	la		a0, X
	call	printf@plt
	la		a0, SET
	call	printf@plt
8:
	li		t1, 1
	srli	t0, s0, 4
	andi	t0, t0, 1
	beq		t0, t1, 9f
	la		a0, U
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		10f
9:
	la		a0, U
	call	printf@plt
	la		a0, SET
	call	printf@plt
10:
	li		t1, 1
	srli	t0, s0, 5
	andi	t0, t0, 1
	beq		t0, t1, 11f
	la		a0, G
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		12f
11:
	la		a0, G
	call	printf@plt
	la		a0, SET
	call	printf@plt
12:
	li		t1, 1
	srli	t0, s0, 6
	andi	t0, t0, 1
	beq		t0, t1, 13f
	la		a0, A
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		14f
13:
	la		a0, A
	call	printf@plt
	la		a0, SET
	call	printf@plt
14:
	li		t1, 1
	srli	t0, s0, 7
	andi	t0, t0, 1
	beq		t0, t1, 15f
	la		a0, D
	call	printf@plt
	la		a0, CLEAR
	call	printf@plt
	j		16f

15:
	la		a0, D
	call	printf@plt
	la		a0, SET
	call	printf@plt
16:
	j		17f
fail:
	la		a0, Usage
	call	printf@plt
17:
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	ld		s1, 24(sp)
	addi	sp, sp, 40
