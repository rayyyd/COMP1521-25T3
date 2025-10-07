	.text
# where your program (code) goes
SQUARE_MAX = 46340

main:
        # $t0 = x, $t1 = y

        #printf("enter a number: ")

        li	$v0, 4            #load integer
        la	$a0, enter        # load address
        syscall

        #scanf("%d", &x)
        li	$v0, 5
        syscall
        # output of scanf is in $v0.
        move	$t0, $v0

        # if statements
        # >   --> greater than (gt), opp <=   --> less equal (le)
        ble     $t0, SQUARE_MAX, main__else

        li	$v0, 4
        la	$a0, too_big
        syscall
        
        b	main__else_end

main__else:
        mul	$t1, $t0, $t0       #   y = x * x

        # print(%d)
        li	$v0, 1
        move	$a0, $t1
        syscall

        # print(\n)
        li	$v0, 11
        li	$a0, '\n'
        syscall

main__else_end:
        li	$v0, 0          # return value goes in v0
        jr	$ra              # return

	.data
# where global variables and string literals go.

enter:
        .asciiz "Enter a number: "
too_big:
        .asciiz "square too big for 32 bits\n"