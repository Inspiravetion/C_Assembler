# Implements div function with the result stored in $s0.
# Note that opOne and OpTwo must be positive.
# Author: Will S Preston

.text
	# load the constant value of -1 from MINUS_ONE
	la $t7, MINUS_ONE
	lw $t7, 0($t7)
	# load the operands
	la $a0, opOne
	lw $a0, 0($a0)
	la $a1, opTwo
	lw $a1, 0($a1)
	# current total, initially equal to opOne
	add $t0, $zero, $a0
	# loop counter, initially equal to 0
	add $t1, $zero, $zero
# subtract opTwo from opOne until the total is less than 1
loop:
	# subtract opTwo from current total
	sub $t0, $t0, $a1
	# exit the loop if the current total is less than 0; increment loop counter otherwise
	slt $t2, $t7, $t0
	beq $t2, $zero, loopend
	addi $t1, $t1, 1
	j loop
loopend:
	add $s0, $zero, $t1
   
	
	li $v0, 10
	syscall

.data
# modify the following two values as you like, ensuring they remain 16 bit values
opOne:		.word	51
opTwo:		.word	8
# Do not modify this value
MINUS_ONE:	.word   -1
	
