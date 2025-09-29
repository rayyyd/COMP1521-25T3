//  la --> address
// lw lb ---> value

a) 0x10010000    
b) 666
c) ??? (machine dependent, on CSE this will be 9A)
0X 00 00 02 9A     == 666 in hex
d) 666
e) 1
f) 5
g) 5
h) # will not let you run the code.
   # lw must have an address that is 4-byte aligned


// sw sb

li	$t0, 1
sb	$t0, answer

	.data
answer:
	.word	4
array:
	.word 1, 3, 4, 5, 2