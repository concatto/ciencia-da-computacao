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
	jal
	

#a0: dia; $a1: aluno; $a2: ação
RealizarAcao:
	
	
	
	