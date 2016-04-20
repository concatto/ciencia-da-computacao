.data
	A:	.word	10
.text
	la	$t0, A
	lw	$t1, 0($t0)
	addi	$t1, $t1, 5
	sw	$t1, 0($t0)