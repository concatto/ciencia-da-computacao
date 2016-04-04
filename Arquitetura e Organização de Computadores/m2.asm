# Disciplina: 4189 � Arquitetura e Organiza��o de Computadores
# Atividade: Avalia��o 01 � Programa��o em Linguagem de Montagem
# Programa 02
# Acad�mico: Fernando Concatto

.data
	Dias:		.word	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
				0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
				0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
				0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	
	MessageDia:	.asciiz	"Dia (0 a 15): "
	MessageAluno:	.asciiz	"Aluno (0 a 31): "
	MessageAcao:	.asciiz	"Acao (0 para falta, 1 para presenca): "
.text

LoopEntrada:
	li	$v0, 4
	la	$a0, MessageDia
	syscall
	li	$v0, 5
	syscall
	move	$s0, $v0		#s0 cont�m o dia
	
	li	$v0, 4
	la	$a0, MessageAluno
	syscall
	li	$v0, 5
	syscall
	move	$s1, $v0		#s1 cont�m o aluno
	
	li	$v0, 4
	la	$a0, MessageAcao
	syscall
	li	$v0, 5
	syscall
	move	$s2, $v0		#s2 cont�m a a��o
	
	
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	RealizarAcao
	
	j	LoopEntrada

#a0: dia; $a1: aluno; $a2: a��o
RealizarAcao:
	la	$t1, Dias		#t1 cont�m o endere�o base do vetor Dias
	sll	$t0, $a0, 2		#t0 cont�m o �ndice do dia * 4
	add	$t0, $t0, $t1		#t0 agora aponta para o endere�o correto do vetor Dias
	lw	$t1, 0($t0)		#O valor contido no endere�o apontado por t0 agora est� em t1
	
	li	$t2, 1
	sllv	$t2, $t2, $a1		#t2 cont�m o bit 1 deslocado para a esquerda com base do �ndice do aluno
	beqz	$a2, And		#Se a a��o for 0 (falta), realizar a opera��o AND
Or:					#Sen�o, realizar OR
	or	$t1, $t1, $t2		#Bit solicitado agora est� em 1
	j	FimAcao
And:
	not	$t2, $t2
	and	$t1, $t1, $t2		#Bit solicitado agora est� em 0
FimAcao:
	sw	$t1, 0($t0)		#t1 cont�m os novos bits, e ser�o salvos no endere�o apontado por t0
	jr	$ra
