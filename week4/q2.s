	.text

FLAG_ROWS = 6
FLAG_COLS = 12

main:

main__outer_for_init:
	li	$t0, 0		#t0 = row
main__outer_for_cond:
	bge	$t0, FLAG_ROWS, main__outer_for_end
main__outer_for_body:

main__inner_for_init:
	li	$t1, 0		#t1 = col
main__inner_for_cond:
	bge	$t1, FLAG_COLS, main__inner_for_end
main__inner_for_body:
	# printf("%c", flag[row][col]);
	# row = $t0
	# col = $t1
	# offset = row * total_cols + col

	# base address
	la	$t2, flag
	# offset
	mul	$t3, $t0, FLAG_COLS    # row * total_cols
	add	$t3, $t3, $t1          # add col        
	mul	$t3, $t3, 1            #elem size
	# add tgt and lb
	add	$t2, $t2, $t3

	lb	$t3, ($t2)       # t2 = addresss, $t3 = value

	li	$v0, 1
	move	$a0, $t3
	syscall

main__inner_for_iter:
	addi	$t1, $t1, 1
	j	main__inner_for_cond
main__inner_for_end:
	li	$v0, 11
	li	$a0, '\n'
	syscall
main__outer_for_iter:
	addi	$t0, $t0, 1
	j	main__outer_for_cond
main__outer_for_end:



	.data
flag:
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'