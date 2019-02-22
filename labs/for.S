//pseudocode
// for(int i = 0; i < 10 && something = True; i++) sum += 1
	li	a0, 0
Check:
	blt	a0, 10, next
	j	end
next:
	beq something, True, next2
	j end
//in the loop
in_loop:
	add	a1, a0, 1
	//increment i = i + 1
	add	a0, a0, 1
	j	Check
end
