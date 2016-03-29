.data
	VetorA:		.word	0, 0, 0, 0, 0, 0, 0, 0
	VetorB:		.word	0, 0, 0, 0, 0, 0, 0, 0
	MessageSize:	.asciiz	"Tamanho dos vetores (max 8): "
	MessageInvalid:	.asciiz	"Valor invalido."
	MessageValue:	.asciiz "Valor: "
	MessageA:	.asciiz	"Vetor A\n"
	MessageB:	.asciiz	"Vetor B\n"
	MessageLine:	.asciiz	"\n"

.text
	
	li	$v0, 4
	la	$a0, MessageSize
	syscall				#Mostra na tela a mensagem do tamanho
	
	li	$v0, 5
	syscall				#L� um n�mero inteiro
	move	$s0, $v0		#s0 conter� o tamanho dos vetores
	
LeituraA:
	li	$v0, 4
	la	$a0, MessageA
	syscall				#Mostra na tela a mensagem "Vetor A"
	move	$a0, $s0
	la	$a1, VetorA
	jal	LerVetor		#L� valores no vetor A

LeituraB:
	li	$v0, 4
	la	$a0, MessageB
	syscall				#Mostra na tela a mensagem "Vetor B"
	move	$a0, $s0
	la	$a1, VetorB
	jal	LerVetor		#L� valores no vetor B
	
	li	$s1, 0			#s1 conter� o �ndice
	
LoopInversao:
	beq	$s1, $s0, FimInversao
	
	sll	$t0, $s1, 2		#Multiplica o �ndice por 4 e salva em t0
	
	la	$t2, VetorA		#Carrega o endere�o base em t2
	add	$t2, $t2, $t0		#t2 agora est� deslocado at� o �ndice atual, com base em A
	lw	$s2, 0($t2)		#s2 conter� o valor no �ndice atual no vetor A
	
	la	$t3, VetorB
	add	$t3, $t3, $t0		#t3 agora est� deslocado at� o �ndice atual, com base em B
	lw	$s3, 0($t3)		#s3 conter� o valor no �ndice atual no vetor B
	
	sw	$s2, 0($t3)		#O valor do vetor A agora est� salvo em B
	sw	$s3, 0($t2)		#O valor do vetor B agora est� salvo em A
	
	addi	$s1, $s1, 1
	j 	LoopInversao	
	
FimInversao:
	li	$v0, 4
	la	$a0, MessageA
	syscall				#Mostra na tela a mensagem "Vetor A"
	move	$a0, $s0
	la	$a1, VetorA
	jal	ImprimirVetor		#Imprime na tela o conte�do do vetor A

	li	$v0, 4
	la	$a0, MessageB
	syscall				#Mostra na tela a mensagem "Vetor B"
	move	$a0, $s0
	la	$a1, VetorB
	jal	ImprimirVetor		#Imprime na tela o conte�do do vetor B

	li	$v0, 17
	li	$a0, 0
	syscall				#Encerra o programa
	

#a0: quantidade de elementos; a1: endere�o base do vetor
LerVetor:
	li	$t0, 0			#t0 cont�m o �ndice
	move	$t1, $a0		#t1 cont�m a quantidade de elementos
	move	$t2, $a1		#t2 cont�m o endere�o base
	
LoopLeitura:
	beq	$t0, $t1, FinalLeitura
	
	li	$v0, 4
	la	$a0, MessageValue
	syscall				#Mostra a string Valor: na tela
	
	li	$v0, 5
	syscall				#L� um valor inteiro
	
	sll	$t3, $t0, 2
	add	$t3, $t3, $t2		#Desloca at� o endere�o correto
	sw	$v0, 0($t3)		#Salva o valor lido na mem�ria
	
	addi	$t0, $t0, 1		#Incrementa o �ndice
	j	LoopLeitura

FinalLeitura:
	jr	$ra			#Volta ao endere�o que chamou esta fun��o
	


#a0: quantidade de elementos; a1: endere�o base do vetor
ImprimirVetor:
	li	$t0, 0			#t0 cont�m o �ndice
	move	$t1, $a0		#t1 cont�m a quantidade de elementos
	move	$t2, $a1		#t2 cont�m o endere�o base

LoopImpressao:
	beq	$t0, $t1, FimImpressao
	
	sll	$t3, $t0, 2		#Multiplica o �ndice por 4 e salva em t3
	add	$t3, $t3, $t2		#Desloca o endere�o base pelo valor de t3 e salva em t3
	lw	$a0, 0($t3)		#Carrega o valor salvo no endere�o apontado por t3
	li	$v0, 1
	syscall				#Mostra na tela o valor naquele �ndice
	
	la	$a0, MessageLine
	li	$v0, 4
	syscall				#Mostra uma quebra de linha na tela
	
	addi	$t0, $t0, 1		#Incrementa o �ndice
	j	LoopImpressao
	
FimImpressao:
	jr	$ra
	