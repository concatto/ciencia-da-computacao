.data
	vet:	.word	1, 2, 3, 4, 5, 6, 7, 8
	size:	.word	8
	sum:	.word	0
	
.text
	j 	Main

ProcSum:
	li		$t0, 0				#�ndice
	li		$t2, 0				#somat�rio parcial
Loop:
	beq		$a0, $t0, EndLoop	#se o �ndice passou do �ltimo elemento, terminar o loop
	sll		$t1, $t0, 2
	add		$t1, $t1, $a1		#endere�o deslocado para a posi��o correta
	
	lw		$t1, 0($t1)			#valor do vetor no �ndice indicado agora est� em t1
	add		$t2, $t2, $t1		#ac�mulo realizado
	
	addi	$t0, $t0, 1			#incremento do �ndice
	j 		Loop
EndLoop:
	move	$v0, $t2			#o resultado do somat�rio ser� retornado
	jr		$ra


Main:
	la		$s0, vet			#endere�o base do vetor
	la		$s1, size			#endere�o do tamanho
	lw		$s1, 0($s1)			#s1 agora cont�m o valor
	la		$s2, sum			#endere�o da soma
	
	move	$a0, $s1
	move	$a1, $s0
	jal		ProcSum				#chamada do procedimento
	sw		$v0, 0($s2)			#valor retornado � gravado na mem�ria