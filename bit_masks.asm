# Stores the results of various logical operations, shifts, and bit masking in registers $t0-$t7.
# Try to guess whether $v0 will store a 0 or a 1 depending on the 'number' in the data section.
# Author: Will S Preston

.text
	# load the bit masks
	la $a0, mask_all
	lw $a0, 0($a0)
	la $a1, mask_none
	lw $a1, 0($a1)
	la $a2, mask_upper
	lw $a2, 0($a2)
	la $a3, mask_lower
	lw $a3, 0($a3)

	# call operators
	and $t0, $a0, $a2
	
	and $t1, $a0, $a3
	
	or $t2, $a2, $a3
	
	andi $t3, $a0, 0x1010
	
	ori $t4, $a1, 0x1010
	
	sll $t5, $a3, 8
	
	srl $t6, $a2, 8
	
	add $v0, $t0, $t1
	add $v0, $v0, $t2
	add $v0, $v0, $t3
	add $v0, $v0, $t4
	add $v0, $v0, $t5
	add $v0, $v0, $t6
	add $v0, $v0, $t7
	la $t0, number
	lw $t0, 0($t0)
	slti $t1, $t0, 0x7FFF
	beq $t1, $zero, highBits
	sll $t0, $t0, 16
	sll $v0, $v0, 16
highBits:
	srl $t0, $t0, 16
	srl $v0, $v0, 16
	slt $v0, $v0, $t0
	
	li $v0, 10
	syscall
	
	
.data
# change this value as you like
number:		.word 0x1234

# do not modify these values
mask_all:	.word 0xFFFFFFFF
mask_none:	.word 0x00000000
mask_upper:	.word 0xFFFF0000
mask_lower:	.word 0x0000FFFF