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
j haaaaaab
baaaaaab:
#------------------------------
addi $sp,$sp,-200

move $t3,$3
sw $t3,4($sp)

move $t3,$4
sw $t3,8($sp)

lw $t2,4($sp)
lw $t3,8($sp)
sub $t1,$t2,$t3
bgez $t1,aaab
nop

j baab
nop

aaab:
lw $t3,8($sp)
move $v0,$t3
addi $sp,$sp,200
jr $ra
nop

baab:
addi $t1,$0,100
sw $t1,92($sp)

lw $t2,80($sp)
lw $t3,92($sp)
div $t2,$t3
mflo $t1
sw $t1,80($sp)

addi $t1,$0,1
sw $t1,100($sp)

lw $t2,80($sp)
lw $t3,100($sp)
mult $t2,$t3
mflo $t1
sw $t1,80($sp)

lw $t2,4($sp)
lw $t3,80($sp)
sub $t1,$t2,$t3
blez $t1,daab
nop

j eaab
nop

daab:
addi $t1,$0,100
sw $t1,140($sp)

lw $t2,128($sp)
lw $t3,140($sp)
mult $t2,$t3
mflo $t1
sw $t1,128($sp)

lw $t3,128($sp)
move $3,$t3

sw $ra,200($sp)
jal baaaaaab
nop
lw $ra,200($sp)
move $t1,$v0
sw $t1,120($sp)
lw $t3,120($sp)
move $v0,$t3
addi $sp,$sp,200
jr $ra
nop

j faab
nop

eaab:
addi $t1,$0,10
sw $t1,180($sp)

lw $t2,168($sp)
lw $t3,180($sp)
mult $t2,$t3
mflo $t1
sw $t1,168($sp)

lw $t3,168($sp)
move $3,$t3

sw $ra,200($sp)
jal baaaaaab
nop
lw $ra,200($sp)
move $t1,$v0
sw $t1,160($sp)
lw $t3,160($sp)
move $v0,$t3
addi $sp,$sp,200
jr $ra
nop

faab:
addi $t1,$0,0
sw $t1,196($sp)

lw $t3,196($sp)
move $v0,$t3
addi $sp,$sp,200
jr $ra
nop

addi $sp,$sp,200
jr $ra
nop

eaaaaaab:
#------------------------------
addi $sp,$sp,-244

move $t3,$3
sw $t3,0($sp)

addi $t1,$0,72
sw $t1,224($sp)

lw $t1,0($sp)
lw $t2,224($sp)
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
addi $sp,$sp,244
jr $ra
nop

haaaaaab:
#------------------------------
addi $sp,$sp,-728

addi $t1,$0,5
sw $t1,324($sp)

lw $t3,324($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $t1,$0,0
sw $t1,340($sp)

lw $t3,340($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,44($sp)

jaab:
addi $t1,$0,5
sw $t1,372($sp)

lw $t2,44($sp)
lw $t3,372($sp)
sub $t1,$t2,$t3
bltz $t1,abab
nop

j bbab
nop

abab:
li $v0,5
syscall
sw $v0,40($sp)

la $t2,f
lw $t1,396($sp)
lw $t3,44($sp)
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
sw $t1,424($sp)

lw $t3,424($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,44($sp)

la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

dbab:
lw $t3,52($sp)
move $3,$t3

sw $ra,728($sp)
jal eaaaaaab
nop
lw $ra,728($sp)
move $t1,$v0
sw $t1,448($sp)
addi $t1,$0,1
sw $t1,472($sp)

lw $t2,452($sp)
lw $t3,472($sp)
add $t1,$t2,$t3
add $t1,$t2,$t3
sw $t1,452($sp)

lw $t3,452($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,44($sp)

addi $t1,$0,5
sw $t1,504($sp)

lw $t2,44($sp)
lw $t3,504($sp)
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
sw $t1,536($sp)

lw $t3,536($sp)
move $3,$t3

addi $t1,$0,100000
sw $t1,552($sp)

lw $t3,552($sp)
move $4,$t3

sw $ra,728($sp)
jal baaaaaab
nop
lw $ra,728($sp)
move $t1,$v0
sw $t1,524($sp)
addi $t1,$0,11
sw $t1,560($sp)

lw $t2,516($sp)
lw $t3,560($sp)
mult $t2,$t3
mflo $t1
sw $t1,516($sp)

lw $t3,516($sp)
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
sw $t1,576($sp)

lw $t3,576($sp)
add $t1,$0,$t3
add $t1,$t2,$t3
sw $t1,32($sp)

addi $t1,$0,5
sw $t1,592($sp)

addi $t1,$0,7
sw $t1,612($sp)

la $t2,c
lw $t1,600($sp)
lw $t3,592($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
sw $t1,0($t2)
addi $t1,$0,5
sw $t1,660($sp)

la $t2,c
lw $t3,660($sp)
sll $t3,$t3,2
add $t2,$t2,$t3
lw $t1,0($t2)
sw $t1,668($sp)

lw $t2,32($sp)
lw $t3,668($sp)
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
sw $t1,696($sp)

addi $t1,$0,2
sw $t1,708($sp)

addi $t1,$0,3
sw $t1,716($sp)

lw $t2,704($sp)
lw $t3,716($sp)
mult $t2,$t3
mflo $t1
sw $t1,704($sp)

lw $t2,688($sp)
lw $t3,704($sp)
add $t1,$t2,$t3
add $t1,$t2,$t3
sw $t1,688($sp)

addi $t1,$0,111
sw $t1,724($sp)

lw $t2,676($sp)
lw $t3,724($sp)
mult $t2,$t3
mflo $t1
sw $t1,676($sp)

lw $t3,676($sp)
move $a0,$t3
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

