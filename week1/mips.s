	.text
# where we write out code
main:
	# $t0 = x, $t1 = y

	li	$v0, 4         #li means load integer
	la	$a0, string    #la means L oad A ddress
	syscall    # what to do..... and about what

	jr	$ra


	.data
# where string literals and global variables go
string:
	.asciiz "Enter a number: "