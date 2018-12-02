.data
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
j jaaaaaab
daaaaaab:
#------------------------------
addi $sp,$sp,-68

move $t3,$3
sw $t3,4($sp)

move $t3,$4
sw $t3,8($sp)

lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t2,12($sp)
lw $t3,16($sp)
sub $t1,$t2,$t3
bgez $t1,aaab
nop

j baab
nop

aaab:
lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
move $v0,$t3
addi $sp,$sp,68
jr $ra
nop

baab:
lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,32($sp)

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,32($sp)

addi $t1,$0,100
sw $t1,40($sp)

lw $t2,32($sp)
lw $t3,40($sp)
div $t2,$t3
mflo $t1
sw $t1,32($sp)

addi $t1,$0,1
sw $t1,44($sp)

lw $t2,32($sp)
lw $t3,44($sp)
mult $t2,$t3
mflo $t1
sw $t1,32($sp)

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t2,24($sp)
lw $t3,28($sp)
sub $t1,$t2,$t3
blez $t1,daab
nop

j eaab
nop

daab:
lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

addi $t1,$0,100
sw $t1,60($sp)

lw $t2,52($sp)
lw $t3,60($sp)
mult $t2,$t3
mflo $t1
sw $t1,52($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

lw $t3,48($sp)
move $3,$t3

sw $ra,68($sp)
jal daaaaaab
nop
lw $ra,68($sp)
move $t1,$v0
sw $t1,44($sp)
lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,32($sp)

lw $t3,32($sp)
move $v0,$t3
addi $sp,$sp,68
jr $ra
nop

j faab
nop

eaab:
lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,60($sp)

lw $t3,60($sp)
add $t1,$0,$t3
sw $t1,56($sp)

addi $t1,$0,10
sw $t1,64($sp)

lw $t2,56($sp)
lw $t3,64($sp)
mult $t2,$t3
mflo $t1
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,52($sp)
move $3,$t3

sw $ra,68($sp)
jal daaaaaab
nop
lw $ra,68($sp)
move $t1,$v0
sw $t1,48($sp)
lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
move $v0,$t3
addi $sp,$sp,68
jr $ra
nop

faab:
addi $t1,$0,0
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
move $v0,$t3
addi $sp,$sp,68
jr $ra
nop

addi $sp,$sp,68
jr $ra
nop

gaaaaaab:
#------------------------------
addi $sp,$sp,-28

move $t3,$3
sw $t3,0($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

addi $t1,$0,72
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t1,8($sp)
lw $t2,12($sp)
beq $t1,$t2,gaab
nop

j haab
nop

gaab:
lw $t3,0($sp)
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
li $v0,11
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
addi $sp,$sp,28
jr $ra
nop

jaaaaaab:
#------------------------------
addi $sp,$sp,-192

addi $t1,$0,5
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,80($sp)

lw $t3,80($sp)
add $t1,$0,$t3
sw $t1,76($sp)

lw $t3,76($sp)
move $a0,$t3
li $v0,11
syscall
la $a0,newLine
li $v0,4
syscall

addi $t1,$0,0
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,80($sp)

lw $t3,80($sp)
add $t1,$0,$t3
sw $t1,44($sp)

jaab:
lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

addi $t1,$0,5
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t2,84($sp)
lw $t3,88($sp)
sub $t1,$t2,$t3
bltz $t1,abab
nop

j bbab
nop

abab:
li $v0,5
syscall
sw $v0,40($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

la $t2,f
lw $t1,96($sp)
lw $t3,92($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
lw $t2,44($sp)
addi $t1,$t2,1
sw $t1,44($sp)

j jaab
nop

bbab:
addi $t1,$0,0
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,44($sp)

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

dbab:
lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
move $3,$t3

sw $ra,192($sp)
jal gaaaaaab
nop
lw $ra,192($sp)
move $t1,$v0
sw $t1,112($sp)
lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

lw $t3,120($sp)
add $t1,$0,$t3
sw $t1,116($sp)

addi $t1,$0,1
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t2,116($sp)
lw $t3,124($sp)
add $t1,$t2,$t3
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

addi $t1,$0,5
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t2,120($sp)
lw $t3,124($sp)
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
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
add $t1,$0,$t3
sw $t1,144($sp)

lw $t3,144($sp)
move $3,$t3

addi $t1,$0,100000
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
move $4,$t3

sw $ra,192($sp)
jal daaaaaab
nop
lw $ra,192($sp)
move $t1,$v0
sw $t1,140($sp)
lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

addi $t1,$0,11
sw $t1,140($sp)

lw $t2,132($sp)
lw $t3,140($sp)
mult $t2,$t3
mflo $t1
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
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
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,32($sp)

addi $t1,$0,5
sw $t1,144($sp)

lw $t3,144($sp)
add $t1,$0,$t3
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

addi $t1,$0,7
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
add $t1,$0,$t3
sw $t1,144($sp)

lw $t3,144($sp)
add $t1,$0,$t3
sw $t1,140($sp)

la $t2,c
lw $t1,140($sp)
lw $t3,136($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

addi $t1,$0,5
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,168($sp)

la $t2,c
lw $t3,168($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
lw $t1,0($t2)
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,160($sp)

lw $t3,160($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t2,148($sp)
lw $t3,152($sp)
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
sw $t1,180($sp)

lw $t3,180($sp)
add $t1,$0,$t3
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

addi $t1,$0,2
sw $t1,184($sp)

lw $t3,184($sp)
add $t1,$0,$t3
sw $t1,180($sp)

addi $t1,$0,3
sw $t1,188($sp)

lw $t2,180($sp)
lw $t3,188($sp)
mult $t2,$t3
mflo $t1
sw $t1,180($sp)

lw $t2,172($sp)
lw $t3,180($sp)
add $t1,$t2,$t3
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,164($sp)

lw $t3,164($sp)
add $t1,$0,$t3
sw $t1,160($sp)

addi $t1,$0,111
sw $t1,168($sp)

lw $t2,160($sp)
lw $t3,168($sp)
mult $t2,$t3
mflo $t1
sw $t1,160($sp)

lw $t3,160($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

