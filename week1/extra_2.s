	.text
# contain our code

main: 
	# $t0 = x, $t1 = y,

	# what to do  -> print a string
	li	$v0, 4   # Load Integer
	# what to print   -> string is called "String"
	la	$a0, string   #Load Address
	syscall
	# print done.

	li	$v0, 5        #command to scanf
	syscall                   # do something
	# our scanned value is in v0
	move	$t0, $v0

	# y = x * x
	mul	$t1, $t0, $t0

	li	$v0, 1
	move	$a0, $t1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall

	jr	$ra     # memorise <- return


	.data
# contains string literals and global variables
string:
	.asciiz "Enter a number"