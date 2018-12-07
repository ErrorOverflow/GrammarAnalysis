.data
_GLOBAL: .space 12
c: .space 40
a: .space 40
f: .space 80
string0: .ascii "not H\0"
string5: .ascii "b is not bigger than c[5]\0"
string3: .ascii "next period\n\0"
string1: .ascii "next period\0"
string4: .ascii "b is bigger than c[5]\0"
newLine: .ascii "\n\0"


.text
la $gp,_GLOBAL
j gaaaaaab
aaaaaaab:
#------------------------------
addi $sp,$sp,-60

move $11,$4
sw $3,0($sp)

move $11,$5
sw $3,4($sp)

lw $11,4($sp)
lw $10,0($sp)
sub $9,$10,$11
bgez $9,aaab
nop

j baab
nop

aaab:
lw $11,4($sp)
move $v0,$11
addi $sp,$sp,60
jr $ra
nop

baab:
addi $9,$0,100
sw $9,8($sp)

lw $11,8($sp)
lw $10,4($sp)
div $10,$11
mflo $9
sw $9,12($sp)

addi $9,$0,1
sw $9,16($sp)

lw $11,16($sp)
lw $10,12($sp)
mult $10,$11
mflo $9
sw $9,12($sp)

lw $11,12($sp)
lw $10,0($sp)
sub $9,$10,$11
blez $9,daab
nop

j eaab
nop

daab:
addi $9,$0,100
sw $9,20($sp)

lw $11,20($sp)
lw $10,0($sp)
mult $10,$11
mflo $9
sw $9,24($sp)

lw $11,24($sp)
move $4,$11

lw $11,4($sp)
move $5,$11

sw $ra,56($sp)
jal aaaaaaab
nop
lw $ra,56($sp)
move $9,$v0
sw $9,28($sp)
lw $11,28($sp)
move $v0,$11
addi $sp,$sp,60
jr $ra
nop

j faab
nop

eaab:
addi $9,$0,10
sw $9,36($sp)

lw $11,36($sp)
lw $10,0($sp)
mult $10,$11
mflo $9
sw $9,40($sp)

lw $11,40($sp)
move $4,$11

lw $11,4($sp)
move $5,$11

sw $ra,56($sp)
jal aaaaaaab
nop
lw $ra,56($sp)
move $9,$v0
sw $9,44($sp)
lw $11,44($sp)
move $v0,$11
addi $sp,$sp,60
jr $ra
nop

faab:
addi $9,$0,0
sw $9,48($sp)

lw $11,48($sp)
move $v0,$11
addi $sp,$sp,60
jr $ra
nop

addi $sp,$sp,60
jr $ra
nop

daaaaaab:
#------------------------------
addi $sp,$sp,-24

move $11,$4
sw $3,0($sp)

addi $9,$0,10
sw $9,4($sp)

lw $11,4($sp)
add $9,$0,$11
sw $9,8($gp)

addi $9,$0,72
sw $9,8($sp)

lw $11,8($sp)
lw $10,0($sp)
beq $10,$11,gaab
nop

j haab
nop

gaab:
lw $11,0($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

j iaab
nop

haab:
la $a0,string0
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

iaab:
addi $sp,$sp,24
jr $ra
nop

gaaaaaab:
#------------------------------
addi $sp,$sp,-156

addi $9,$0,5
sw $9,0($sp)

lw $11,0($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $9,$0,0
sw $9,4($sp)

lw $11,4($sp)
add $9,$0,$11
sw $9,8($sp)

jaab:
addi $9,$0,5
sw $9,12($sp)

lw $11,12($sp)
lw $10,8($sp)
sub $9,$10,$11
bltz $9,abab
nop

j bbab
nop

abab:
li $v0,5
syscall
sw $2,16($sp)
la $10,f
lw $9,20($sp)
lw $11,8($sp)
sll $11,$11,2
add $10,$10,$11
sw $9,0($10)
lw $10,8($sp)
addi $9,$10,1
sw $9,8($sp)

j jaab
nop

bbab:
addi $9,$0,0
sw $9,24($sp)

lw $11,24($sp)
add $9,$0,$11
sw $9,8($sp)

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

dbab:
lw $11,32($sp)
move $4,$11

sw $ra,152($sp)
jal daaaaaab
nop
lw $ra,152($sp)
move $9,$v0
sw $9,36($sp)
addi $9,$0,1
sw $9,44($sp)

lw $11,44($sp)
lw $10,8($sp)
add $9,$10,$11
sw $9,48($sp)

lw $11,48($sp)
add $9,$0,$11
sw $9,8($sp)

addi $9,$0,5
sw $9,52($sp)

lw $11,52($sp)
lw $10,8($sp)
sub $9,$10,$11
bltz $9,dbab
nop

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

addi $9,$0,100
sw $9,56($sp)

lw $11,56($sp)
move $4,$11

addi $9,$0,100000
sw $9,60($sp)

lw $11,60($sp)
move $5,$11

sw $ra,152($sp)
jal aaaaaaab
nop
lw $ra,152($sp)
move $9,$v0
sw $9,64($sp)
addi $9,$0,11
sw $9,68($sp)

lw $11,68($sp)
lw $10,64($sp)
mult $10,$11
mflo $9
sw $9,72($sp)

lw $11,72($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

la $a0,string3
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

addi $9,$0,10
sw $9,80($sp)

lw $11,80($sp)
add $9,$0,$11
sw $9,84($sp)

addi $9,$0,5
sw $9,88($sp)

addi $9,$0,7
sw $9,92($sp)

la $10,c
lw $9,96($sp)
lw $11,88($sp)
sll $11,$11,2
add $10,$10,$11
sw $9,0($10)
addi $9,$0,5
sw $9,100($sp)

la $10,c
lw $11,100($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,104($sp)
lw $11,104($sp)
lw $10,84($sp)
sub $9,$10,$11
bgtz $9,gbab
nop

j hbab
nop

gbab:
la $a0,string4
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

j ibab
nop

hbab:
la $a0,string5
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

ibab:
addi $9,$0,1
sw $9,116($sp)

addi $9,$0,2
sw $9,120($sp)

addi $9,$0,3
sw $9,124($sp)

lw $11,124($sp)
lw $10,120($sp)
mult $10,$11
mflo $9
sw $9,128($sp)

lw $11,128($sp)
lw $10,116($sp)
add $9,$10,$11
sw $9,132($sp)

addi $9,$0,111
sw $9,136($sp)

lw $11,136($sp)
lw $10,132($sp)
mult $10,$11
mflo $9
sw $9,140($sp)

lw $11,140($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

lw $11,8($gp)
add $9,$0,$11
sw $9,144($sp)

lw $11,144($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

