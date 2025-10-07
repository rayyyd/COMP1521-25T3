	.text

main:
	#$t0 = x
	li	$v0, 4
	la	$a0, enter
	syscall

	li	$v0, 5
	syscall
	move	$t0, $v0


	# x > 100
	ble	$t0, 100, else
	# x < 1000
	bge	$t0, 1000, else

	li	$v0, 4
	la	$a0, medium
	syscall
	b	end
else:
	li	$v0, 4
	la	$a0, small
	syscall
end:
	jr	$ra


	.data
enter:
	.asciiz "Enter a number: "
medium:
	.asciiz "medium\n"
small:
	.asciiz "small/big\n"