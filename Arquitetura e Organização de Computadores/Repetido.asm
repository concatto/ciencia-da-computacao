.data
	A:		.space	40
	printed_chars:	.space	40
	msg_amt:	.asciiz	"Quantidade de caracteres (max 10): "
	msg_out:	.asciiz	"\nSaida: "
.text



	la	$a0, msg_amt
	li	$v0, 4
	syscall
	
	li	$v0, 5
	syscall
	
	la	$s6, printed_chars	#s6 conterá a base do vetor de caracteres exibidos
	la	$s4, A			#s4 conterá a base de A 
	move	$s1, $v0		#s1 conterá o tamanho
	li	$s0, 0			#s0 conterá o índice
	
ReadLoop:
	beq	$s1, $s0, ReadExit
	
	li	$v0, 12
	syscall
	
	sll	$t0, $s0, 2
	add	$t0, $t0, $s4
	sw	$v0, 0($t0)
	
	addi	$s0, $s0, 1
	
	j ReadLoop
	
ReadExit:
	li	$s0, 0
	li	$s3, 0		#s3 conterá o tamanho do vetor de caracteres exibidos
	
	la	$a0, msg_out
	li	$v0, 4
	syscall
PrintLoop:
	beq	$s1, $s0, PrintExit
	sll	$t0, $s0, 2
	add	$t0, $t0, $s4
	lw	$t0, 0($t0)
	
	move	$a0, $t0
	move	$a1, $s3
	move	$a2, $s6
	jal	WasPrinted
	bgtz	$v0, AlreadyPrinted

	li	$v0, 11
	syscall
	
	sll	$t1, $s3, 2
	add	$t1, $t1, $s6
	sw	$t0, 0($t1)
	addi	$s3, $s3, 1

AlreadyPrinted:
	addi	$s0, $s0, 1
	j	PrintLoop

PrintExit:
	li	$a0, 0
	li	$v0, 17
	syscall
	
	
	
	
	
#a0: caractere a ser testado; $a1: elementos no vetor; $a2: endereço base do vetor
WasPrinted:
	sw	$t0, 0($sp)
	sw	$t1, 4($sp)
	addi	$sp, $sp, 8

	li	$t0, 0
	li	$v0, 0
	
PrintedLoop:
	beq	$t0, $a1, PrintedExit
	sll	$t1, $t0, 2
	add	$t1, $t1, $a2
	lw	$t1, 0($t1)
	beq	$t1, $a0, Printed
	
	addi	$t0, $t0, 1
	j	PrintedLoop
	
Printed:
	li	$v0, 1
	
PrintedExit:
	lw	$t1, -4($sp)
	lw	$t0, -8($sp)
	addi	$sp, $sp, -8
	jr	$ra