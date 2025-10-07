	.text
main:
main__prologue:
	# move arugments
	# push here
	begin
	push	$ra
main__body:
	# rest of code
	# arugments go into a registers
	li	$a0, 11
	li	$a1, 13
	li	$a2, 17
	li	$a3, 19	
	jal	sum4

	# output (result) is in $v0
	move	$a0, $v0

	li	$v0, 1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall


main__epilogue:
	# pop here
	# your return statement does NOT go here, it goes in body.
	pop	$ra
	end

	jr	$ra


sum4:
sum4_prologue:
	# a = $a0
	# b = $a1
	# c = a2
	# d = a3
	begin
	push	$ra
	push	$s0
	push	$s2
	push	$s3

	move	$s2, $a2   #c
	move	$s3, $a3   #d


sum4_body:
	jal	sum2
	#moving output (res1) into $t0
	move	$s0, $v0    # $t0 = res1

	move	$a0, $s2
	move	$a1, $s3
	jal	sum2

	move	$t1, $v0 #t1 = res2

	move	$a0, $s0
	move	$a1, $t1
	jal	sum2
	#return value already in v0
	j	sum4_epilogue
sum4_epilogue:
	pop	$s3
	pop	$s2
	pop	$s0
	pop	$ra
	
	end
	jr	$ra



sum2:
	add	$v0, $a0, $a1
	li	$t0, 1
	jr	$ra



	.data


