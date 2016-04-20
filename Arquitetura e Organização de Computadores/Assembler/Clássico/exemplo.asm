.data
	#vet      : .word    1,2,3,4,5,6,7,8 # vetor
.text
	#la    $t0,vet
	#addi  $t0,$t0,4
	#lw    $s0,0($t0)
	addi  $s0,$s0,10
	#sw    $s0,0($t0)
	
	
