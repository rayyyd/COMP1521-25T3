	.text

main:


main__for_init:
	li	$t0, 23
main__for_cond:   #required
	#opp condition (if x >= 42, go to end of loop)
	bge	$t0, 42, main__for_end
main__for_body:
	#print
	li	$v0, 1
	move	$a0, $t0
	syscall
	li	$v0, 11
	li	$a0, '\n'
	syscall
main__for_increment:    #required
	add	$t0, $t0, 3
	b	main__for_cond
main__for_end:     #required

	jr	$ra		#return


	.data