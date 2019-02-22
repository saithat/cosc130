.section .rodata
.section .text
.global GetAvg
GetAvg:
//int GetAvg(int a[], int size);
//a0 GetAvg(a0, a1)

	li		t0, 0  //t0 = iterator
			//t1 = sum
	li		t1, 0
1:
	bge		t0, a1, 1f
	
	lw		t2, 0(a0)
	add		t1, t1, t2
	addi	a0, a0, 4
	addi	t0, t0, 1
	j		1b
1:
	//return sum / size
	div		a0, t1, a1
	ret
