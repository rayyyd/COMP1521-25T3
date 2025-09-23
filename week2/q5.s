	.text
# your code goes here

SQUARE_MAX = 46340

main:
        # $t0 = x, $t1 = y

        # printf
        li	$v0, 4
        la	$a0, enter_a_num
        syscall

        #scanf
        li	$v0, 5
        syscall
        # output of this scanf is in $v0
        move	$t0, $v0

        # if statement   > (gt)  ->   <= (le)
        ble     $t0, SQUARE_MAX, main__else

        #print too big
        li	$v0, 4
        la	$a0, square_too_big
        syscall

        b	main__else_end
main__else:
        mul	$t1, $t0, $t0    #y = x * x
        
        #printf("%d\n)
        li	$v0, 1
        move	$a0, $t1
        syscall

        li	$v0, 11
        li	$a0, '\n'
        syscall


main__else_end:
        li	$v0, 0
        jr	$ra
	.data
# global variables and string literals go here.
enter_a_num:
        .asciiz "Enter a number: "
square_too_big:
        .asciiz "square too big for 32 bits\n"