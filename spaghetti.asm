# A series of jumps, otherwise known as "spaghetti code", which sets the value of register $v0.
# Author: Will S Preston

.text
	# load the number to set $v0 to
	la $a0, number
	lw $a0, 0($a0)
	
	addi $t1, $zero, 1
	
	jal start
	add $t1, $zero, $zero
start:
	beq $t1, $zero, end
	add $t0, $zero, $a0
	jr $ra
end:
	add $v0, $zero, $t0
    	
	li $v0, 10
	syscall

.data
# change this value as you like
# boolean to specify which value, 0 or 1, to overwrite the memory with, thereby safely deleting it
number:		.word 777
