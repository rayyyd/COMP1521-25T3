	.text
MAP_SIZE = 5
N_POINTS = 4
main:
main__for_init:
	li	$t0, 0      #i = $t0
main__for_cond:
	bge	$t0, N_POINTS, main__for_end
main__for_body:
       # int row = my_points[i].row;
       # i = $t0
       #todo

       # step 1: my_points[i]
       la	$t1, my_points
       mul	$t2, $t0, 8     #multiply offset by array size, which is 8
       add	$t1, $t1, $t2   # add to base address

       # step 2: .row
       addi	$t1, $t1, 0

       # step 3: value
	lw	$t2, ($t1)     # row = $t2

	addi	$t1, $t1, 4   #.col
	lw	$t3, ($t1)     #col = $t3

	# base address + (row * num_cols + cols)
	la	$t4, topography_grid

	# calc offset
	mul	$t5, $t2, 5   # row * num_cols
	add	$t5, $t5, $t3  # + cols

	mul	$t5, $t5, 4    # mul by array element size
	add	$t5, $t4, $t5  #adding to base address

	lw	$t5, ($t5)     # $t5 = height

	li	$v0, 4
	la	$a0, height_str
	syscall

	li	$v0, 1
	move	$a0, $t2
	syscall

	move	$a0, $t3
	syscall

	li	$v0, 11
	li	$a0, '='
	syscall


	li	$v0, 1
	move	$a0, $t5       #print height
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall


main__for_iter:
	addi	$t0, $t0, 1
	j	main__for_cond
main__for_end:
	li	$v0, 0
	jr	$ra

	.data
topography_grid:
	.word	0, 1, 1, 2, 3
	.word	1, 1, 2, 3, 4
	.word	1, 2, 3, 5, 7
	.word	3, 3, 4, 5, 6
	.word	3, 4, 5, 6, 7

my_points:
	.word	1, 2
	.word	2, 3
	.word	0, 0
	.word	4, 4

height_str: .asciiz "Height at "