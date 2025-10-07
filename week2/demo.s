	.text

main__if_start:
	li	$t0, 0    #$t0 = i

main__if_cond:
	rem	$t1, $t0, 7   #t1 = t0 % 7
	beq	$t1, 0, main__print_body

	rem	$t1, $t0, 11
	beq	$t1, 0, main__print_body

	b	main__if_end
main__print_body:

	li	$v0, 1
	move	$a0, $t0
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall



main__if_end:

	.data