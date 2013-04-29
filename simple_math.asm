# Displays a certain mathematical sequence when executed line by line, then displays another.
# Can you find out what the two sequences are?
# Author: Will S Preston

.text
	addi $t0, $zero, 1
	add $t1, $zero, $t0
	add $t2, $t0, $t1
	add $t0, $t1, $t2
	add $t1, $t2, $t0
	add $t2, $t0, $t1
	add $t0, $t1, $t2
	add $t1, $t2, $t0
	add $t2, $t0, $t1
	add $t0, $t1, $t2
	add $t1, $t2, $t0
	# $t1 == 89
	
	# set up for next sequence
	addi $t4, $zero, 1
	addi $t5, $zero, 2
	addi $t6, $zero, 4
	addi $t7, $zero, 6
	
	sub $t3, $t1, $t7
	sub $t3, $t3, $t6
	sub $t3, $t3, $t7
	sub $t3, $t3, $t5
	sub $t3, $t3, $t6
	sub $t3, $t3, $t7
	sub $t3, $t3, $t5
	sub $t3, $t3, $t7
	sub $t3, $t3, $t7
	sub $t3, $t3, $t6
	sub $t3, $t3, $t5
	sub $t3, $t3, $t6
	sub $t3, $t3, $t7
	sub $t3, $t3, $t5
	sub $t3, $t3, $t7
	sub $t3, $t3, $t6
	sub $t3, $t3, $t5
	sub $t3, $t3, $t6
	sub $t3, $t3, $t5
	sub $t3, $t3, $t6
	sub $t3, $t3, $t5
	sub $t3, $t3, $t5
	sub $t3, $t3, $t4
	sub $t3, $t3, $t5
	# Subtracted 89 total

	# reset intermediate values for visual clarity
	sub $t0, $t0, $t0
	sub $t1, $t1, $t1
	sub $t2, $t2, $t2
	sub $t3, $t3, $t3
	sub $t4, $t4, $t4
	sub $t5, $t5, $t5
	sub $t6, $t6, $t6
	sub $t7, $t7, $t7

        li  $v0, 10
        syscall
        