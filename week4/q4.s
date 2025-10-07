	.text

MAP_SIZE = 5
N_POINTS = 4

# main
# -> main__for_init:
# -> main__for_cond:
# -> main__for_body:
#....

main:
main__for_init:
	li	$t0, 0     #i = $t0

main__for_cond:
	bge	$t0, N_POINTS, main__for_end
main__for_body:
	# int row = my_points[i].row;

	# access this array
	la	$t2, my_points

	mul	$t3, $t0, 8
	add	$t3, $t3, $t2

	# add in the row offset
	add	$t3, $t3, 0
	lw	$t2, ($t3)     # row = $t2


	# col = my_points[i].col
	lw	$t3, 4($t3)    # col = $t3

	# element size * (row * total_cols + col)

	mul	$t4, $t2, 5
	add	$t4, $t4, $t3
	mul	$t4, $t4, 4     #array element size

	# add	$t4, $t4, topography_grid
	lw	$t4, topography_grid($t4)  #$t4 = height

	li	$v0, 4
	la	$a0, height_str
	syscall

	li	$v0, 1
	move	$a0, $t2  #row
	syscall
	
	li	$v0, 11
	li	$a0, ','
	syscall

	li	$v0, 1
	move	$a0, $t3   #col
	syscall

	li	$v0, 11
	li	$a0, '='
	syscall

	li	$v0, 1
	move	$a0, $t4   #height
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

# 2D grid representing the height data for an area.
topography_grid:
	.word	0, 1, 1, 2, 3
	.word	1, 1, 2, 3, 4
	.word	1, 2, 3, 5, 7
	.word	3, 3, 4, 5, 6
	.word	3, 4, 5, 6, 7

# Points of interest to print heights for, as a 1D array of point2D_t structs.
# Note the memory layout of this array: each element requires 8 bytes, not 4.
my_points:
	.word	1, 2
	.word	2, 3
	.word	0, 0
	.word	4, 4

height_str: .asciiz "Height at "
