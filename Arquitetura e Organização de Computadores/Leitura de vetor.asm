.data
	A: 		.space	80
	msg_input:	.asciiz	"Tamanho (max 20): "
	msg_max:	.asciiz	"Valor maximo: "

.text

Main:
	la	$a0, msg_input
	li	$v0, 4
	syscall			
	
	li	$v0, 5
	syscall
	
	move	$s5, $v0	#s5 contém o tamanho
	li	$s2, 0		#conterá o índice
	
	la	$s1, A		#endereço base de A
Read:
	beq	$s2, $s5, ReadExit
	
	li	$v0, 5
	syscall			#lê um inteiro do console
	
	sll	$s3, $s2, 2	#multiplica o índice por 4 e grava em s3
	add	$s3, $s3, $s1	#desloca s3 para o endereço correto
	sw	$v0, 0($s3)	#salva na memória o valor lido
	
	addi	$s2, $s2, 1
	
	j 	Read
ReadExit:
	li 	$s2, 1		#índice iniciará em 1
	lw	$s4, 0($s1)	#primeiro valor de A; s4 conterá o maior valor
LoopMaximum:
	beq	$s2, $s5, Exit
	
	sll	$s3, $s2, 2
	add	$s3, $s3, $s1
	lw	$t0, 0($s3)
	
	ble	$t0, $s4, NotGreater
	move	$s4, $t0
NotGreater:
	addi	$s2, $s2, 1
	
	j	LoopMaximum
Exit:
	la	$a0, msg_max
	li	$v0, 4
	syscall

	move	$a0, $s4
	li	$v0, 1
	syscall