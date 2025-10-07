	.text


la	$t0, x
la	$t1, ($t0)        #identical statements

la	$t0, cc
lw	$t1, ($t0)


	.data
x:
	.word 54
cc:
	.word 3