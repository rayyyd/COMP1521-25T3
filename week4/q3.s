	.text

main:
main__prologue:
	# pushing
	# relocate input args.

	push	$ra
main__body:
	li	$a0, 11
	li	$a1, 13
	li	$a2, 17
	li	$a3, 19
	jal	sum4
	#output comes out in $v0, <<<--- result

	move	$a0, $v0
	li	$v0, 1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall


main__epilogue:
	#how we return
	# pop
	pop	$ra
	jr 	$ra



# sum4
#

sum4:



sum4__prologue:
	push	$ra
	push	$s0
	push	$s2
	push	$s3

	move	$s2, $a2   #c
	move	$s3, $a3   #d
sum4__body:
	# a and b are already in a0 and a1
	jal	sum2
	move	$s0, $v0    #move res1 into $s0  #t0 = 8
	# <--------res 1

	move	$a0, $s2
	move	$a1, $s3
	jal	sum2
	# <---- res2 = $v0
	move	$a0, $s0   # <----res1 again   #t0 = 1
	move	$a1, $v0   # <--- using res2 in the final fn call.
	jal	sum2


function_name__some_description:
sum4__epilogue:


	pop	$s3
	pop	$s2
	pop	$s0
	pop	$ra

	jr	$ra
















sum2:
	push	$s0
	add	$v0, $a0, $a1
	li	$t0, 0
	li	$s0, 0
	pop	$s0
	jr	$ra


	.data