.data
	VetorA:		.word	1, 2, 3, 4, 5, 6, 7, 8
	VetorB:		.word	0, 5, 0, 5, 0, 5, 0, 5

.text
	
	li	$t9, 0
	not	$t0, $t0
	li	$s1, 0
	li	$s0, 8
LoopInversao:
	beq	$s1, $s0, FimInversao	#Se o �ndice for igual ao tamanho, terminar o loop
	
	sll	$t0, $s1, 2		#Multiplica o �ndice por 4 e salva em t0
	
	la	$t2, VetorA
	add	$t2, $t2, $t0		#t2 agora est� deslocado at� o �ndice atual, com base em A
	lw	$s2, 0($t2)		#s2 conter� o valor no �ndice atual no vetor A
	
	la	$t3, VetorB
	add	$t3, $t3, $t0		#t3 agora est� deslocado at� o �ndice atual, com base em B
	lw	$s3, 0($t3)		#s3 conter� o valor no �ndice atual no vetor B
	
	sw	$s2, 0($t3)		#O valor do vetor A agora est� salvo em B
	sw	$s3, 0($t2)		#O valor do vetor B agora est� salvo em A
	
	addi	$s1, $s1, 1		#�ndice++
	j 	LoopInversao	
	
FimInversao:
	nop