.data
a: .space 40
string1: .ascii "after\0"
string0: .ascii "before\0"
newLine: .ascii "\n"


.text
j gaaaaaab
daaaaaab:
#------------------------------
addi $sp,$sp,-12

addi $t1,$0,233
sw $t1,8($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,4($sp)

lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,0($sp)

lw $t3,0($sp)
move $v0,$t3
addi $sp,$sp,12
jr $ra
nop

addi $sp,$sp,12
jr $ra
nop

eaaaaaab:
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

gaaaaaab:
#------------------------------
addi $sp,$sp,-108

addi $t1,$0,1
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,16($sp)

addi $t1,$0,0
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,20($sp)

li $v0,5
syscall
sw $v0,28($sp)

la $a0,string0
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

jal daaaaaab
nop
move $t1,$v0
sw $t1,60($sp)
lw $t3,60($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,16($sp)

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,60($sp)

lw $t3,60($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,52($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $t1,$0,0
sw $t1,64($sp)

lw $t3,64($sp)
add $t1,$0,$t3
sw $t1,60($sp)

lw $t3,60($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,20($sp)

aaab:
lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,68($sp)

lw $t3,68($sp)
add $t1,$0,$t3
sw $t1,64($sp)

lw $t3,64($sp)
add $t1,$0,$t3
sw $t1,60($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,72($sp)

lw $t3,72($sp)
add $t1,$0,$t3
sw $t1,68($sp)

lw $t3,68($sp)
add $t1,$0,$t3
sw $t1,64($sp)

lw $t2,60($sp)
lw $t3,64($sp)
sub $t1,$t2,$t3
bltz $t1,baab
nop

j caab
nop

baab:
lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,76($sp)

lw $t3,76($sp)
add $t1,$0,$t3
sw $t1,72($sp)

lw $t3,72($sp)
add $t1,$0,$t3
sw $t1,68($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,80($sp)

addi $t1,$0,3
sw $t1,88($sp)

lw $t2,80($sp)
lw $t3,88($sp)
mult $t2,$t3
mflo $t1
sw $t1,80($sp)

lw $t3,80($sp)
add $t1,$0,$t3
sw $t1,76($sp)

lw $t3,76($sp)
add $t1,$0,$t3
sw $t1,72($sp)

la $t2,a
lw $t1,72($sp)
lw $t3,68($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

la $t2,a
lw $t3,96($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
lw $t1,0($t2)
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,80($sp)

lw $t3,80($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

lw $t2,20($sp)
addi $t1,$t2,1
sw $t1,20($sp)

j aaab
nop

caab:
lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

jal eaaaaaab
nop
move $t1,$v0
sw $t1,88($sp)
