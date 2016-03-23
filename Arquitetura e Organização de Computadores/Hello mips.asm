.data
	A: 		.word	 1,2,3,4,5,6,7,8
	size: 		.word 	8
	i: 		.word 	10
	sum:		.word	20
	msg_sum:	.asciiz	"Sum = "

.text

Main:
	la	$t0, A		#endereço base de A
	la	$t1, size
	la	$t2, i
	la	$t3, sum
	
	lw	$s1,0($t1)	#contém o valor de size
	li	$s2,0		#conterá I
	li	$s3,0		#conterá Sum
	
	sw	$s2,0($t2)
	sw	$s3,0($t3)
	
	li	$s0, 0		#conterá o deslocamento
Loop:
	beq	$s2, $s1, Exit	#Branch de saída
	
	sll	$s0, $s2, 2	#prepara s0 com o deslocamento necessário
	add	$s0, $s0, $t0	#move s0 para o endereço correto
	lw	$s0, 0($s0)	#carrega o valor no endereço indicado por s0 no próprio s0
	add	$s3, $s3, $s0	#acumula os valores em s3 (sum)
	sw	$s3, 0($t3)	#salva o resultado na memória
	
	addi	$s2, $s2, 1	#i++
	sw	$s2, 0($t2)	#Salva na memória o valor de i
	
	j	Loop
Exit:
	nop