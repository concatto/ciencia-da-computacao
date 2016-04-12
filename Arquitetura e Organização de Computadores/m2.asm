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
	MessageInvalid:	.asciiz	"Valor inválido.\n"
	MessageSuccess:	.asciiz	"Alteracao realizada com sucesso.\n"
.text

EntradaDia:
	li	$v0, 4
	la	$a0, MessageDia
	syscall				#Mensagem de dia
	li	$v0, 5
	syscall				#Entrada de inteiro
	move	$s0, $v0		#s0 contém o dia
	
	slti	$t0, $s0, 0		#Se dia < 0, t0 contém 1
	sgt	$t1, $s0, 15		#Se dia > 15, t1 contém 1
	or	$t0, $t0, $t1		#Se o dia for menor que 0 ou maior que 15, t0 contém 1
	beqz	$t0, EntradaAluno	#Se o valor for válido, continuar para a próxima entrada de dados
					#Senão, exibir mensagem de erro e voltar
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall				#Mensagem de valor inválido
	j	EntradaDia
	
EntradaAluno:
	li	$v0, 4
	la	$a0, MessageAluno
	syscall				#Mensagem do aluno
	li	$v0, 5
	syscall
	move	$s1, $v0		#s1 contém o aluno

	slti	$t0, $s1, 0		#Se aluno < 0, t0 contém 1
	sgt	$t1, $s1, 31		#Se aluno > 31, t1 contém 1
	or	$t0, $t0, $t1		#Se o índice do aluno for menor que 0 ou maior que 31, t0 conterá 1
	beqz	$t0, EntradaAcao	#Se t0 ainda for zero, o valor é válido; pular para a próxima entrada
	
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall
	j	EntradaAluno
	
EntradaAcao:	
	li	$v0, 4
	la	$a0, MessageAcao
	syscall				#Mensagem da ação
	li	$v0, 5
	syscall
	move	$s2, $v0		#s2 contém a ação
	
	slti	$t0, $s2, 0
	sgt	$t1, $s2, 1
	or	$t0, $t0, $t1		#Se ação < 0 ou ação > 1, t0 contém 1
	beqz	$t0, Acao		#Se t0 for 0, avançar para a realização da ação
					#Senão, voltar para a entrada da ação	
	li	$v0, 4
	la	$a0, MessageInvalid
	syscall
	j	EntradaAcao
	
Acao:
	move	$a0, $s0		#Dia
	move	$a1, $s1		#Aluno
	move	$a2, $s2		#Ação
	jal	RealizarAcao		#Chamada da função RealizarAcao
	
	li	$v0, 4
	la	$a0, MessageSuccess
	syscall				#Mensagem de sucesso
	j	EntradaDia		#Jump para o início do programa

#a0: dia; $a1: aluno; $a2: ação
RealizarAcao:
	la	$t1, Dias		#t1 contém o endereço base do vetor Dias
	sll	$t0, $a0, 2		#t0 contém o índice do dia * 4
	add	$t0, $t0, $t1		#t0 agora aponta para o endereço correto do vetor Dias
	lw	$t1, 0($t0)		#O valor contido no endereço apontado por t0 agora está em t1.
	
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
