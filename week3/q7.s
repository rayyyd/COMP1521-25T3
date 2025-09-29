	.text
N_SIZE = 10
main:
	# $t0 = i
	li	$t0, 0
main__while_cond:
	bge	$t0, N_SIZE, main__while_end
	# base_address + 4 * i
	la	$t1, numbers    # base address
	mul	$t2, $t0, 4     # 4 * i
	add	$t1, $t1, $t2   # address of numbers[i]
	lw	$t2, ($t1)      # value
	#t1 = address, #t2 = value
	bge	$t2, 0, main__if_end

	addi	$t2, $t2, 42
	sw	$t2, ($t1)

main__if_end:

main__while_incr:
	addi	$t0, $t0, 1
	j	main__while_cond
main__while_end:
	jr	$ra





	.data
numbers:
	.word 0, 1, 2, -3, 4, -5, 6, -7, 8, 9