.data
_GLOBAL: .space 8
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
j haaaaaab
baaaaaab:
#------------------------------
addi $sp,$sp,-60

move $t3,$4
sw $t3,0($sp)

move $t3,$5
sw $t3,4($sp)

lw $t2,0($sp)
lw $t3,4($sp)
sub $t1,$t2,$t3
bgez $t1,aaab
nop

j baab
nop

aaab:
lw $t3,4($sp)
move $v0,$t3
addi $sp,$sp,60
jr $ra
nop

baab:
addi $t1,$0,100
sw $t1,8($sp)

lw $t2,4($sp)
lw $t3,8($sp)
div $t2,$t3
mflo $t1
sw $t1,12($sp)

addi $t1,$0,1
sw $t1,16($sp)

lw $t2,12($sp)
lw $t3,16($sp)
mult $t2,$t3
mflo $t1
sw $t1,12($sp)

lw $t2,0($sp)
lw $t3,12($sp)
sub $t1,$t2,$t3
blez $t1,daab
nop

j eaab
nop

daab:
addi $t1,$0,100
sw $t1,20($sp)

lw $t2,0($sp)
lw $t3,20($sp)
mult $t2,$t3
mflo $t1
sw $t1,24($sp)

lw $t3,24($sp)
move $4,$t3

lw $t3,4($sp)
move $5,$t3

sw $ra,56($sp)
jal baaaaaab
nop
lw $ra,56($sp)
move $t1,$v0
sw $t1,28($sp)
lw $t3,28($sp)
move $v0,$t3
addi $sp,$sp,60
jr $ra
nop

j faab
nop

eaab:
addi $t1,$0,10
sw $t1,36($sp)

lw $t2,0($sp)
lw $t3,36($sp)
mult $t2,$t3
mflo $t1
sw $t1,40($sp)

lw $t3,40($sp)
move $4,$t3

lw $t3,4($sp)
move $5,$t3

sw $ra,56($sp)
jal baaaaaab
nop
lw $ra,56($sp)
move $t1,$v0
sw $t1,44($sp)
lw $t3,44($sp)
move $v0,$t3
addi $sp,$sp,60
jr $ra
nop

faab:
addi $t1,$0,0
sw $t1,48($sp)

lw $t3,48($sp)
move $v0,$t3
addi $sp,$sp,60
jr $ra
nop

addi $sp,$sp,60
jr $ra
nop

eaaaaaab:
#------------------------------
addi $sp,$sp,-20

move $t3,$4
sw $t3,0($sp)

addi $t1,$0,72
sw $t1,4($sp)

lw $t1,0($sp)
lw $t2,4($sp)
beq $t1,$t2,gaab
nop

j haab
nop

gaab:
lw $t3,0($sp)
move $a0,$t3
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
addi $sp,$sp,20
jr $ra
nop

haaaaaab:
#------------------------------
addi $sp,$sp,-152

addi $t1,$0,5
sw $t1,0($sp)

lw $t3,0($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $t1,$0,0
sw $t1,4($sp)

lw $t3,4($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,8($sp)

jaab:
addi $t1,$0,5
sw $t1,12($sp)

lw $t2,8($sp)
lw $t3,12($sp)
sub $t1,$t2,$t3
bltz $t1,abab
nop

j bbab
nop

abab:
li $v0,5
syscall
sw $v0,16($sp)

la $t2,f
lw $t1,20($sp)
lw $t3,8($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
lw $t2,8($sp)
addi $t1,$t2,1
sw $t1,8($sp)

j jaab
nop

bbab:
addi $t1,$0,0
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,8($sp)

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

dbab:
lw $t3,32($sp)
move $4,$t3

sw $ra,148($sp)
jal eaaaaaab
nop
lw $ra,148($sp)
move $t1,$v0
sw $t1,36($sp)
addi $t1,$0,1
sw $t1,44($sp)

lw $t2,8($sp)
lw $t3,44($sp)
add $t1,$t2,$t3
add $t1,$t2,$t3
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,8($sp)

addi $t1,$0,5
sw $t1,52($sp)

lw $t2,8($sp)
lw $t3,52($sp)
sub $t1,$t2,$t3
bltz $t1,dbab
nop

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

addi $t1,$0,100
sw $t1,56($sp)

lw $t3,56($sp)
move $4,$t3

addi $t1,$0,100000
sw $t1,60($sp)

lw $t3,60($sp)
move $5,$t3

sw $ra,148($sp)
jal baaaaaab
nop
lw $ra,148($sp)
move $t1,$v0
sw $t1,64($sp)
addi $t1,$0,11
sw $t1,68($sp)

lw $t2,64($sp)
lw $t3,68($sp)
mult $t2,$t3
mflo $t1
sw $t1,72($sp)

lw $t3,72($sp)
move $a0,$t3
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

addi $t1,$0,10
sw $t1,80($sp)

lw $t3,80($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,84($sp)

addi $t1,$0,5
sw $t1,88($sp)

addi $t1,$0,7
sw $t1,92($sp)

la $t2,c
lw $t1,96($sp)
lw $t3,88($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
addi $t1,$0,5
sw $t1,100($sp)

la $t2,c
lw $t3,100($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
lw $t1,0($t2)
sw $t1,104($sp)

lw $t2,84($sp)
lw $t3,104($sp)
sub $t1,$t2,$t3
bgtz $t1,gbab
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
addi $t1,$0,1
sw $t1,116($sp)

addi $t1,$0,2
sw $t1,120($sp)

addi $t1,$0,3
sw $t1,124($sp)

lw $t2,120($sp)
lw $t3,124($sp)
mult $t2,$t3
mflo $t1
sw $t1,128($sp)

lw $t2,116($sp)
lw $t3,128($sp)
add $t1,$t2,$t3
add $t1,$t2,$t3
sw $t1,132($sp)

addi $t1,$0,111
sw $t1,136($sp)

lw $t2,132($sp)
lw $t3,136($sp)
mult $t2,$t3
mflo $t1
sw $t1,140($sp)

lw $t3,140($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

