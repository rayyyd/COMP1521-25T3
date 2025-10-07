	.text

main:
	la	$t0, string         #char* s
	li	$t1, 0              #length

main__while_cond:
	beq	$t0, $zero, main__while_end

	addi	$t1, $t1, 1
	addi	$t0, $t0, 1

	j	main__while_cond

main__while_end:
	jr	$ra

	.data
string:
   .asciiz  "...."