	.text

FLAG_ROWS = 6
FLAG_COLS = 12

main:	

main__first_for_init:
	li	$t0, 0            #$t0 = row
main__first_for_cond:
	bge	$t0, FLAG_ROWS, main__first_for_end
main__first_for_body:

main__second_for_init:
	li	$t1, 0		 # $t1 = col
main__second_for_cond:
	bge	$t1, FLAG_COLS, main__second_for_end
main__second_for_body:
	# do this
	 #           printf("%c", flag[row][col]);
	 # row = $t0
	 # col = $t1
	# flag[row][col]
	# offset = rows * num_cols + cols
	la	$t2, flag

	#get the offset
	mul	$t3, $t0, FLAG_COLS
	add	$t3, $t3, $t1
	mul	$t3, $t3, 1           #multiply offset by array element
	add	$t2, $t2, $t3

	lb	$t3, ($t2)        # t2 = address, t3 - value

	move	$a0, $t3
	li	$v0, 11
	syscall
main__second_for_iter:
	addi	$t1, $t1, 1
	j	main__second_for_cond
main__second_for_end:

	li	$v0, 11
	li	$a0, '\n'
	syscall

main__first_for_iter:
	addi	$t0, $t0, 1
	j	main__first_for_cond
main__first_for_end:

	jr	$ra



	.data
flag:
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'