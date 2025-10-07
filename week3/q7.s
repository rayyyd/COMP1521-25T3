	.text
	# where your code goes
N_SIZE = 10

main:

	# $t0 = i
	li	$t0, 0
main__while_cond:
	bge	$t0, N_SIZE, main__while_end
main__while_body:

main__if_cond:
	# base_address + element_size * i
	# numbers + 4 * $t0
	la	$t1, numbers
	mul	$t2, $t0, 4    # 4 * i
	add	$t2, $t2, $t1

	lw	$t1, ($t2)    # $t1 = value of numbers[i]
				#$t2 = address of numbers[i]

	# if (numbers[i] < 0)
	bge	$t1, 0, main__if_end

	# numbers[i] = numbers[i] + 42
	#  ^             ^
	# write         read

	addi	$t1, $t1, 42
	sw	$t1, ($t2)    # write back into numbers[i]

main__if_end:


main__while_incr:
	addi	$t0, $t0, 1
	j	main__while_cond
main__while_end:

	jr	$ra

	.data
	# global variables and string literals go
	# cheat = putting arrays/structs here asw.
numbers:
	.word	0, 1, 2, -3, 4, -5, 6, -7, 8, 9