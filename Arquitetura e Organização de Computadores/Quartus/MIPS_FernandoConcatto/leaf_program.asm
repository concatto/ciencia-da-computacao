.data
.text 				# segmento de código (programa)
	j	main
leaf_example:
	add 	$t0, $a0, $a1 	# $t0 = a + b
	add 	$t1, $a2, $a3 	# $t1 = i + j
	sub 	$v0, $t0, $t1 	# f = $t0 - $t1
	jr 	$ra		# retorna do procedimento
main:
	addi 	$a0, $zero, 4 	# inicializa lº parâmetro (g)
	addi 	$a1, $zero, 3 	# inicializa 2º parâmetro (h)
	addi 	$a2, $zero, 2 	# inicializa 3º parâmetro (i)
	addi 	$a3, $zero, 1 	# inicializa 4º parâmetro (j)
	jal 	leaf_example	# chama o procedimento