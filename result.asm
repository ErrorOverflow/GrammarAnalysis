.data
string0: .ascii "not H"
string5: .ascii "b is not bigger than c[5]\n"
string1: .ascii "next period\n"
f: .space 80
string4: .ascii "b is bigger than c[5]\n"
a: .space 40
newLine: .ascii "\n"


.text
daaaaaab:
#------------------------------
addi $sp,$sp,-60

move $t3,$3
sw $t3,16($sp)

move $t3,$4
sw $t3,20($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t1,8($sp)
lw $t2,12($sp)
bgez $t1,$t2,aaab
nop

j aaab
nop

j baab
nop

aaab:

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
move $vo,$t3
jr $ra
nop

j caab
nop

aaab:

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,32($sp)

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

adi $t1,$0,100
sw $t1,36($sp)

lw $t2,28($sp)
lw $t3,36($sp)
div $t1,$t2,$t3
mflo $t1
sw $t1,28($sp)

adi $t1,$0,1
sw $t1,40($sp)

lw $t2,28($sp)
lw $t3,40($sp)
mult $t1,$t2,$t3
mflo $t1
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t1,20($sp)
lw $t2,24($sp)
blez $t1,$t2,daab
nop

j daab
nop

j eaab
nop

daab:

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

adi $t1,$0,100
sw $t1,56($sp)

lw $t2,48($sp)
lw $t3,56($sp)
mult $t1,$t2,$t3
mflo $t1
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
move $3,$t3

jal daaaaaab
nop
move $t1,$v0
sw $t1,40($sp)
lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,32($sp)

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
move $vo,$t3
jr $ra
nop

j faab
nop

eaab:

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

adi $t1,$0,10
sw $t1,60($sp)

lw $t2,52($sp)
lw $t3,60($sp)
mult $t1,$t2,$t3
mflo $t1
sw $t1,52($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

lw $t3,48($sp)
move $3,$t3

jal daaaaaab
nop
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
move $vo,$t3
jr $ra
nop

faab:

adi $t1,$0,0
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
move $vo,$t3
jr $ra
nop

addi $sp,$sp,60
gaaaaaab:
#------------------------------
addi $sp,$sp,-20

move $t3,$3
sw $t3,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

lw $t3,8($sp)
add $t1,$0,$t3
sw $t1,4($sp)

adi $t1,$0,72
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

lw $t1,4($sp)
lw $t2,8($sp)
beq $t1,$t2,gaab
nop

j gaab
nop

j haab
nop

gaab:

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
move $a0,$t3
li $v0,4
syscall

j iaab
nop

haab:

lw $t3,32($sp)
move $a0,$t3
li $v0,4
syscall

iaab:

addi $sp,$sp,20
jaaaaaab:
#------------------------------
addi $sp,$sp,-188

adi $t1,$0,0
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,56($sp)

jaab:

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t1,88($sp)
lw $t2,92($sp)
bltz $t1,$t2,jaab
nop

li $v0,5
syscall
sw $v0,52($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

la $t2,
lw $t1,100($sp)
add $t1,$0,96($t2)
sw $t1,100($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t2,56($sp)
adi $t1,$t2,1
sw $t1,56($sp)

j jaab
nop

abab:

adi $t1,$0,0
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,68($sp)
move $a0,$t3
li $v0,4
syscall

adi $t1,$0,0
sw $t1,120($sp)

lw $t3,120($sp)
add $t1,$0,$t3
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,56($sp)

bbab:

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

lw $t3,120($sp)
add $t1,$0,$t3
sw $t1,116($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

lw $t1,116($sp)
lw $t2,120($sp)
bltz $t1,$t2,bbab
nop

lw $t3,64($sp)
add $t1,$0,$t3
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
move $3,$t3

lw $t2,56($sp)
adi $t1,$t2,1
sw $t1,56($sp)

j bbab
nop

cbab:

lw $t3,68($sp)
move $a0,$t3
li $v0,4
syscall

adi $t1,$0,100
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
add $t1,$0,$t3
sw $t1,144($sp)

lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,144($sp)
move $4,$t3

jal daaaaaab
nop
move $t1,$v0
sw $t1,140($sp)
lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

adi $t1,$0,11
sw $t1,140($sp)

lw $t2,132($sp)
lw $t3,140($sp)
mult $t1,$t2,$t3
mflo $t1
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
move $a0,$t3
li $v0,4
syscall

lw $t3,68($sp)
move $a0,$t3
li $v0,4
syscall

adi $t1,$0,10
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,44($sp)

adi $t1,$0,5
sw $t1,144($sp)

lw $t3,144($sp)
add $t1,$0,$t3
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

la $t2,
lw $t1,140($sp)
add $t1,$0,136($t2)
sw $t1,140($sp)

adi $t1,$0,7
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

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

adi $t1,$0,5
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,168($sp)

la $t2,
lw $t1,172($sp)
add $t1,$0,168($t2)
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

lw $t1,148($sp)
lw $t2,152($sp)
bgtz $t1,$t2,dbab
nop

j dbab
nop

j ebab
nop

dbab:

lw $t3,80($sp)
move $a0,$t3
li $v0,4
syscall

j fbab
nop

ebab:

lw $t3,84($sp)
move $a0,$t3
li $v0,4
syscall

fbab:

adi $t1,$0,1
sw $t1,180($sp)

lw $t3,180($sp)
add $t1,$0,$t3
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

adi $t1,$0,2
sw $t1,184($sp)

lw $t3,184($sp)
add $t1,$0,$t3
sw $t1,180($sp)

adi $t1,$0,3
sw $t1,188($sp)

lw $t2,180($sp)
lw $t3,188($sp)
mult $t1,$t2,$t3
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

adi $t1,$0,111
sw $t1,168($sp)

lw $t2,160($sp)
lw $t3,168($sp)
mult $t1,$t2,$t3
mflo $t1
sw $t1,160($sp)

lw $t3,160($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
move $a0,$t3
li $v0,4
syscall

addi $sp,$sp,188
