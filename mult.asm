# Implements mult function with the result stored in $v0.
# Note that opOne and OpTwo must be positive.
# Author: Will S Preston

.text
	# load the operands
	la $a0, opOne
	lw $a0, 0($a0)
	la $a1, opTwo
	lw $a1, 0($a1)
	# current total, initially equal to opOne
	add $t0, $zero, $a0
	# loop counter, initially equal to 1
	addi $t1, $zero, 1
# add opOne to itself for opTwo iterations
loop:	
	# check for completion (when $t1 == 'opTwo' stored in $a1); if not complete, increment counter
	beq $t1, $a1, loopend
	addi $t1, $t1, 1
	# add opOne to current total
	add $t0, $t0, $a0
	j loop
loopend:
	add $v0, $zero, $t0
	
	li $v0, 10
	syscall

.data
# modify the following two values as you like, ensuring they remain 16 bit values
opOne:		.word	5
opTwo:		.word	8
