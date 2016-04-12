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
	MessageInvalid:	.asciiz	"Valor inv�lido.\n"
	MessageSuccess:	.asciiz	"Alteracao realizada com sucesso.\n"
.text

EntradaDia:
	li	$v0, 4
	la	$a0, MessageDia
	syscall				#Mensagem de dia
	li	$v0, 5
	syscall				#Entrada de inteiro
	move	$s0, $v0		#s0 cont�m o dia
	
	slti	$t0, $s0, 0		#Se dia < 0, t0 cont�m 1
	sgt	$t1, $s0, 15		#Se dia > 15, t1 cont�m 1
	or	$t0, $t0, $t1		#Se o dia for menor que 0 ou maior que 15, t0 cont�m 1
	beqz	$t0, EntradaAluno	#Se o valor for v�lido, continuar para a pr�xima entrada de dados
					#Sen�o, exibir mensagem de erro e voltar
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall				#Mensagem de valor inv�lido
	j	EntradaDia
	
EntradaAluno:
	li	$v0, 4
	la	$a0, MessageAluno
	syscall				#Mensagem do aluno
	li	$v0, 5
	syscall
	move	$s1, $v0		#s1 cont�m o aluno

	slti	$t0, $s1, 0		#Se aluno < 0, t0 cont�m 1
	sgt	$t1, $s1, 31		#Se aluno > 31, t1 cont�m 1
	or	$t0, $t0, $t1		#Se o �ndice do aluno for menor que 0 ou maior que 31, t0 conter� 1
	beqz	$t0, EntradaAcao	#Se t0 ainda for zero, o valor � v�lido; pular para a pr�xima entrada
	
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall
	j	EntradaAluno
	
EntradaAcao:	
	li	$v0, 4
	la	$a0, MessageAcao
	syscall				#Mensagem da a��o
	li	$v0, 5
	syscall
	move	$s2, $v0		#s2 cont�m a a��o
	
	slti	$t0, $s2, 0
	sgt	$t1, $s2, 1
	or	$t0, $t0, $t1		#Se a��o < 0 ou a��o > 1, t0 cont�m 1
	beqz	$t0, Acao		#Se t0 for 0, avan�ar para a realiza��o da a��o
					#Sen�o, voltar para a entrada da a��o	
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall
	j	EntradaAcao
	
Acao:
	move	$a0, $s0		#Dia
	move	$a1, $s1		#Aluno
	move	$a2, $s2		#A��o
	jal	RealizarAcao		#Chamada da fun��o RealizarAcao
	
	li	$v0, 4
	la	$a0, MessageSuccess
	syscall				#Mensagem de sucesso
	j	EntradaDia		#Jump para o in�cio do programa

#a0: dia; $a1: aluno; $a2: a��o
RealizarAcao:
	la	$t1, Dias		#t1 cont�m o endere�o base do vetor Dias
	sll	$t0, $a0, 2		#t0 cont�m o �ndice do dia * 4
	add	$t0, $t0, $t1		#t0 agora aponta para o endere�o correto do vetor Dias
	lw	$t1, 0($t0)		#O valor contido no endere�o apontado por t0 agora est� em t1.
	
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
