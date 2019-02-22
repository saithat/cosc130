//Sai Thatigotla
.section .text
.global CalculateASM
CalculateASM:
	li		t0, '+'
	li		t1, '-'
	beq		a1, t0, 1f
	beq		a1, t1, 2f
	li		t2, -1
	sw		t2, 0(a0)
	ret
1:
	ld		s0, 8(a0)
	lw		s0, 0(s0)
	ld		s1, 16(a0)
	lw		s1, 0(s1)
	add		s2, s0, s1
	sw		s2, 0(a0)
	ret
2:
	ld		s0, 8(a0)
	lw		s0, 0(s0)
	ld		s1, 16(s0)
	lw		s1, 0(s0)
	sub		s2, s0, s1
	sw		s2, 0(a0)
	ret
	
	
