	.text
# your code goes here

main:
	# $t0 = x
main__for_loop_init:  #not necessary
	li	$t0, 24
main__for_loop_cond:
	bge	$t0, 42, main__for_loop_end
main__for_loop_body:  #not necessary
	li	$v0, 1
	move	$a0, $t0
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall

main__for_loop_incr:   #usually necessary (depends on your code)
	add	$t0, $t0, 3
	b	main__for_loop_cond
main__for_loop_end:
	jr	$ra




	.data
# global and string literals
