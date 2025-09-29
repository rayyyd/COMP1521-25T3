	.text
lb	$t0, answer

li	$t1, 0
lb	$t0, s($t1)   // address at answer + 0



	.data

s:
	.word 4