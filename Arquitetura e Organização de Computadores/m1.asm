# Disciplina: 4189 � Arquitetura e Organiza��o de Computadores
# Atividade: Avalia��o 01 � Programa��o em Linguagem de Montagem
# Programa 01
# Acad�mico: Fernando Concatto

.data
	VetorA:		.word	0, 0, 0, 0, 0, 0, 0, 0
	VetorB:		.word	0, 0, 0, 0, 0, 0, 0, 0
	MessageSize:	.asciiz	"Tamanho dos vetores (max 8): "
	MessageInvalid:	.asciiz	"Valor invalido.\n"
	MessageValue:	.asciiz "Valor: "
	MessageA:	.asciiz	"VetorA["
	MessageB:	.asciiz	"VetorB["
	MessageClose:	.asciiz	"] = "
	MessageResult:	.asciiz "\nResultado:\n"
	MessageLine:	.asciiz	"\n"

.text
	
LeituraTamanho:
	li	$v0, 4
	la	$a0, MessageSize
	syscall				#Mostra na tela a mensagem do tamanho
	
	li	$v0, 5
	syscall				#L� um n�mero inteiro
	move	$s0, $v0		#s0 conter� o tamanho dos vetores
	slti	$t0, $s0, 1		#t0 � 1 se o tamanho for menor que 1
	sgt	$t1, $s0, 8		#t1 � 1 se o tamanho for maior que 8
	or	$t0, $t0, $t1		#t0 � 1 se o tamanho for menor que 1 OU maior que 8
	beqz	$t0, LeituraA		#se o tamanho for v�lido, pular para leitura de dados
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall
	j	LeituraTamanho
	
LeituraA:
	move	$a0, $s0
	la	$a1, VetorA
	la	$a2, MessageA
	jal	LerVetor		#L� valores no vetor A

LeituraB:
	move	$a0, $s0
	la	$a1, VetorB
	la	$a2, MessageB
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
	la	$a0, MessageResult
	syscall				#Mostra "Resultado" na tela

	move	$a0, $s0
	la	$a1, VetorA
	la	$a2, MessageA
	jal	ImprimirVetor		#Imprime na tela o conte�do do vetor A

	move	$a0, $s0
	la	$a1, VetorB
	la	$a2, MessageB
	jal	ImprimirVetor		#Imprime na tela o conte�do do vetor B

	li	$v0, 17
	li	$a0, 0
	syscall				#Encerra o programa
	

#a0: quantidade de elementos; a1: endere�o base do vetor; a2: mensagem a ser exibida
LerVetor:
	li	$t0, 0			#t0 cont�m o �ndice
	move	$t1, $a0		#t1 cont�m a quantidade de elementos
	move	$t2, $a1		#t2 cont�m o endere�o base
	move	$t3, $a2		#t3 cont�m a mensagem
	
LoopLeitura:
	beq	$t0, $t1, FinalLeitura
	
	li	$v0, 4
	move	$a0, $t3
	syscall				#Mostra a mensagem na tela
	li	$v0, 1
	move	$a0, $t0
	syscall				#Mostra o �ndice
	li	$v0, 4
	la	$a0, MessageClose
	syscall				#Termina a mensagem
	
	li	$v0, 5
	syscall				#L� um valor inteiro
	
	sll	$t4, $t0, 2
	add	$t4, $t4, $t2		#Desloca at� o endere�o correto
	sw	$v0, 0($t4)		#Salva o valor lido na mem�ria
	
	addi	$t0, $t0, 1		#Incrementa o �ndice
	j	LoopLeitura

FinalLeitura:
	jr	$ra			#Volta ao endere�o que chamou esta fun��o
	


#a0: quantidade de elementos; a1: endere�o base do vetor; a2: mensagem a ser exibida
ImprimirVetor:
	li	$t0, 0			#t0 cont�m o �ndice
	move	$t1, $a0		#t1 cont�m a quantidade de elementos
	move	$t2, $a1		#t2 cont�m o endere�o base
	move	$t3, $a2		#t3 cont�m a mensagem
LoopImpressao:
	beq	$t0, $t1, FimImpressao
	
	li	$v0, 4
	move	$a0, $t3
	syscall				#Mensagem do vetor
	li	$v0, 1
	move	$a0, $t0
	syscall				#�ndice
	li	$v0, 4
	la	$a0, MessageClose
	syscall				#Fechamento
	
	sll	$t4, $t0, 2		#Multiplica o �ndice por 4 e salva em t4
	add	$t4, $t4, $t2		#Desloca o endere�o base pelo valor de t4 e salva em t4
	lw	$a0, 0($t4)		#Carrega o valor salvo no endere�o apontado por t4
	li	$v0, 1
	syscall				#Mostra na tela o valor naquele �ndice
	
	la	$a0, MessageLine
	li	$v0, 4
	syscall				#Mostra uma quebra de linha na tela
	
	addi	$t0, $t0, 1		#Incrementa o �ndice
	j	LoopImpressao
	
FimImpressao:
	jr	$ra
	
