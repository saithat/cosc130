//Sai Thatigotla
.section .text
.global Search
.global Median
Search:
	/*
	for(int i = 0; i < (num_people*60); i = i + 60)
		{
			for(j = i; j < i + 51; j++)
			{
				if(people[j].name == name)
				{
					if(people[i].age == age)
					{
						if(people[i].gender == gender)
						{
							result = &people[i];
							return result;
						}
					}
				}
			}
			else
			{
				return 0l;
		}
			N		O		S
	char	name	0		51
	int		age		52		4
	char	gender  56		1

	size = 60
	*/

	//s0 = a0 + index
	//t0 = counter to size
	//t1 = name
	//t2 = age
	//t3 = gender

	addi	sp, sp, -16
	sd		s0, 0(sp)
	sd		s1, 8(sp)

	li		s1, 0    //starting byte of structs
	li		t1, 60
	mul		a1, a1, t1 //max size of structs
	mv		s0, a0

loop:
	beq		s1, a1, exit
	mv		t1, s1
	mv		t2, s1
	addi	t2, t2, 51
name:
	beq		t1, t2, age //checking if at the end of the name
	
	li		t4, 60
	rem		t4, t1, t4  //mod 60 so it will loop back around to the beginning of the char being compared
	
	add		t3, a2, t4 //byte in char we are comparing with
	lb		t3, 0(t3)

	add		s0, a0, t1  //changing byte in name, t1 == current place in memory
	lb		s0, 0(s0)  //deref s0 which is a pointer to a char
	
	bne		t3, s0, fail
	beq		s0, zero, age
	
	addi	t1, t1, 1
	j		name
age:
	addi	t2, t2, 1  //account for offset
	add		s0, a0, t2
	lw		s0, 0(s0)
	beq		s0, a3, gender
	j		fail
gender:
	addi	t2, t2, 4
	add		s0, a0, t2
	lb		s0, 0(s0)
	beq		s0, a4, success
	j		fail
success:
	add		t1, a0, s1
	mv		a0, t1

	ld		s0, 0(sp)
	ld		s1,	8(sp)
	addi	sp, sp, 16

	ret
fail:
	addi	s1, s1, 60
	j		loop
exit:
	mv	a0, zero

	ld		s0, 0(sp)
	ld		s1, 8(sp)
	addi	sp, sp, 16
	ret

Median:
	/*
	int left;
	int right;
	int swapped = 1;
	for(j=0; j < array_size; j++)
	{
		buffer[j] = array[j];
	}
	while(swapped == 1){
		swapped = 0;
		for(int i = 1; i < array_size; i++){
			left = buffer[i-1];
			right = buffer[i];
			if(left > right){
				buffer[i] = left;
				buffer[i-1] = right;
				swapped = 1;
			}
		}
	}
	int median = 0;
	if(((array_size) % 2) != 0)
	{
		median = (buffer[(array_size-1)/2] + buffer[((array_size-1)/2)+1])/2;
	}
	*/
	addi	sp, sp, -16
	sd		s0, 0(sp)
	sd		a2, 8(sp)

	li		t0, 4  //offset x size = 4
	//li	t0, 1
	mul		a1, a1, t0 //a1 is 4 x size
	li		t0, 0 //t0 is j
	li		s0, 1 //swapped counter
buf_loop:			//creates buffer
	bge		t0, a1, sort
	add		t1, a0, t0
	lw		t1, 0(t1)
	add		t2, a2, t0
	sw		t1, 0(t2)
	addi	t0, t0, 4
	j		buf_loop
sort:
	
	beq		s0, zero, med
	li		s0, 0
	li		t0, 4 //t0 is now i
inner_sort:
	bge		t0, a1, sort
	ld		t1, 8(sp)  //t1 is left
	add		t1, t1, t0
	addi	t1, t1, -4
	lw		t1, 0(t1)

	ld		t2, 8(sp) //t2 is right
	add		t2, t2, t0
	lw		t2, 0(t2)

	bgt		t1, t2, switch
	addi	t0, t0, 4
	j		inner_sort
switch:
	ld		t3, 8(sp)
	add		t3, t3, t0
	sw		t1, 0(t3)

	addi	t3, t3, -4
	sw		t2, 0(t3)
	li		s0, 1
	j		inner_sort
med:
	li		t4, 4 
	div		a1, a1, t4
	li		t4, 2
	rem		t4, a1, t4 //t4 is now remainder

	bne		t4, zero, average

	li		t4, 2
	div		t1, a1, t4
	li		t3, 4
	mul		t1, t1, t3
	ld		t2, 8(sp)
	add		t2, t2, t1
	lw		a0, 0(t2)
	j		return
average:
	mv		t0, a1
	li		t3, 2
	div		t0, t0, t3
	ld		t1, 8(sp) //t1 is pointer to array
	li		t3, 4
	mul		t0, t0, t3
	add		t1, t1, t0 //t1 is pointer to number
	lw		t0, 0(t1)  //t0 is now number
	
	mv		t1, a1
	li		t3, 2
	div		t1, t1, t3
	addi	t1, t1, 1
	li		t3, 4
	mul		t1, t1, t3
	ld		t2, 8(sp) //t2 is pointer to array
	add		t2, t2, t1 //t2 is pointer to number
	lw		t1, 0(t2) //t1 is number
	
	add		t0, t0, t1
	li		t3, 2
	div		a0, t0, t3
	
return:
	ld		s0, 0(sp)
	addi	sp, sp, 16
	ret
