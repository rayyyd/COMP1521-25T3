	.text
# your program goes here
main:

	# $t0 = x,  $t1 = y.
	li	$v0, 4           # load integer. puts 4 into $v0
	la	$a0, string      # load address. puts string into $a0
	syscall     # print a string, and the string is called "string"

	li	$v0, 5
	syscall
	# output is in $v0
	move	$t0, $v0

	mul	$t1, $t0, $t0

	#print an int
	li	$v0, 1
	move	$a0, $t1        #move y into $a0
	syscall

	#print '\n'
	li	$v0, 11
	li	$a0, '\n'
	syscall

	jr	$ra

	.data
#global variables and string literals go here
string:
	.asciiz "Enter a number: "