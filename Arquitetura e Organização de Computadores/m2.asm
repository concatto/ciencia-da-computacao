# Disciplina: 4189 – Arquitetura e Organização de Computadores
# Atividade: Avaliação 01 – Programação em Linguagem de Montagem
# Programa 02
# Acadêmico: Fernando Concatto

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
	move	$s0, $v0		#s0 contém o dia
	
	li	$v0, 4
	la	$a0, MessageAluno
	syscall
	li	$v0, 5
	syscall
	move	$s1, $v0		#s1 contém o aluno
	
	li	$v0, 4
	la	$a0, MessageAcao
	syscall
	li	$v0, 5
	syscall
	move	$s2, $v0		#s2 contém a ação
	
	
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	RealizarAcao
	
	j	LoopEntrada

#a0: dia; $a1: aluno; $a2: ação
RealizarAcao:
	la	$t1, Dias		#t1 contém o endereço base do vetor Dias
	sll	$t0, $a0, 2		#t0 contém o índice do dia * 4
	add	$t0, $t0, $t1		#t0 agora aponta para o endereço correto do vetor Dias
	lw	$t1, 0($t0)		#O valor contido no endereço apontado por t0 agora está em t1
	
	li	$t2, 1
	sllv	$t2, $t2, $a1		#t2 contém o bit 1 deslocado para a esquerda com base do índice do aluno
	beqz	$a2, And		#Se a ação for 0 (falta), realizar a operação AND
Or:					#Senão, realizar OR
	or	$t1, $t1, $t2		#Bit solicitado agora está em 1
	j	FimAcao
And:
	not	$t2, $t2
	and	$t1, $t1, $t2		#Bit solicitado agora está em 0
FimAcao:
	sw	$t1, 0($t0)		#t1 contém os novos bits, e serão salvos no endereço apontado por t0
	jr	$ra
