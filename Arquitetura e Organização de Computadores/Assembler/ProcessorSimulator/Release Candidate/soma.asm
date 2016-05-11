.data
	vet:	.word	1, 2, 3, 4, 5, 6, 7, 8
	size:	.word	8
	sum:	.word	0
	
.text
	j 	Main

ProcSum:
	li		$t0, 0				#índice
	li		$t2, 0				#somatório parcial
Loop:
	beq		$a0, $t0, EndLoop	#se o índice passou do último elemento, terminar o loop
	sll		$t1, $t0, 2
	add		$t1, $t1, $a1		#endereço deslocado para a posição correta
	
	lw		$t1, 0($t1)			#valor do vetor no índice indicado agora está em t1
	add		$t2, $t2, $t1		#acúmulo realizado
	
	addi	$t0, $t0, 1			#incremento do índice
	j 		Loop
EndLoop:
	move	$v0, $t2			#o resultado do somatório será retornado
	jr		$ra


Main:
	la		$s0, vet			#endereço base do vetor
	la		$s1, size			#endereço do tamanho
	lw		$s1, 0($s1)			#s1 agora contém o valor
	la		$s2, sum			#endereço da soma
	
	move	$a0, $s1
	move	$a1, $s0
	jal		ProcSum				#chamada do procedimento
	sw		$v0, 0($s2)			#valor retornado é gravado na memória