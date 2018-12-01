.data
newLine: .ascii "\n"


.text
j faaaaaab
daaaaaab:
#------------------------------
addi $sp,$sp,-20

addi $t1,$0,1
sw $t1,8($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,4($sp)

addi $t1,$0,1000
sw $t1,12($sp)

lw $t2,4($sp)
lw $t3,12($sp)
mult $t2,$t3
mflo $t1
sw $t1,4($sp)

lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,0($sp)

addi $t1,$0,2
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

addi $t1,$0,1
sw $t1,16($sp)

lw $t2,8($sp)
lw $t3,16($sp)
div $t2,$t3
mflo $t1
sw $t1,8($sp)

lw $t2,0($sp)
lw $t3,8($sp)
sub $t1,$t2,$t3
sw $t1,0($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,0($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,4($sp)

lw $t3,4($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $sp,$sp,20
jr $ra
nop

faaaaaab:
#------------------------------
addi $sp,$sp,-28

addi $t1,$0,1
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

jal daaaaaab
nop
move $t1,$v0
sw $t1,20($sp)
