.data
_GLOBAL: .space 40096
s: .space 40000
w: .space 16
string1: .ascii " | v: \0"
string2: .ascii " | b: \0"
string0: .ascii " | \0"
newLine: .ascii "\n\0"


.text
la $gp,_GLOBAL
j jbaaaaab
aaaaaaab:
#------------------------------
addi $sp,$sp,-28

sw $4,0($sp)

addi $9,$0,256
sw $9,4($sp)

lw $11,4($sp)
lw $10,0($sp)
div $10,$11
mflo $9
sw $9,8($sp)

addi $9,$0,256
sw $9,12($sp)

lw $11,12($sp)
lw $10,8($sp)
mult $10,$11
mflo $9
sw $9,8($sp)

lw $11,8($sp)
lw $10,0($sp)
sub $9,$10,$11
sw $9,16($sp)

lw $11,16($sp)
move $v0,$11
addi $sp,$sp,28
jr $ra
nop

addi $sp,$sp,28
jr $ra
nop

caaaaaab:
#------------------------------
addi $sp,$sp,-36

sw $4,0($sp)

sw $5,4($sp)

addi $9,$0,0
sw $9,8($sp)

lw $11,0($sp)
lw $10,8($sp)
sub $9,$10,$11
bgtz $9,aaab
nop

j baab
nop

aaab:
daab:
lw $11,4($sp)
lw $10,0($sp)
add $9,$10,$11
sw $9,12($sp)

lw $11,12($sp)
add $9,$0,$11
sw $9,0($sp)

addi $9,$0,0
sw $9,16($sp)

lw $11,16($sp)
lw $10,0($sp)
sub $9,$10,$11
bltz $9,daab
nop

baab:
lw $11,4($sp)
lw $10,0($sp)
sub $9,$10,$11
bltz $9,gaab
nop

j haab
nop

gaab:
lw $11,0($sp)
move $v0,$11
addi $sp,$sp,36
jr $ra
nop

j iaab
nop

haab:
lw $11,4($sp)
lw $10,0($sp)
div $10,$11
mflo $9
sw $9,20($sp)

lw $11,4($sp)
lw $10,20($sp)
mult $10,$11
mflo $9
sw $9,20($sp)

lw $11,20($sp)
lw $10,0($sp)
sub $9,$10,$11
sw $9,24($sp)

lw $11,24($sp)
add $9,$0,$11
sw $9,0($sp)

iaab:
lw $11,0($sp)
move $v0,$11
addi $sp,$sp,36
jr $ra
nop

addi $sp,$sp,36
jr $ra
nop

faaaaaab:
#------------------------------
addi $sp,$sp,-28

lw $11,72($gp)
add $9,$0,$11
sw $9,0($sp)

lw $11,0($sp)
move $4,$11

lw $11,40($gp)
add $9,$0,$11
sw $9,4($sp)

lw $11,4($sp)
move $5,$11

sw $ra,24($sp)
jal caaaaaab
nop
lw $ra,24($sp)
move $9,$v0
sw $9,8($sp)
addi $10,$gp,96
lw $11,8($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,16($sp)
lw $11,16($sp)
add $9,$0,$11
sw $9,92($gp)

addi $sp,$sp,28
jr $ra
nop

gaaaaaab:
#------------------------------
addi $sp,$sp,-132

sw $4,0($sp)

lw $11,0($sp)
move $4,$11

sw $ra,128($sp)
jal aaaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,4($sp)
lw $11,4($sp)
add $9,$0,$11
sw $9,0($sp)

lw $10,0($sp)
bne $10,$0,jaab
nop

j abab
nop

jaab:
j bbab
nop

abab:
addi $9,$0,0
sw $9,12($sp)

lw $11,12($sp)
lw $10,0($sp)
beq $10,$11,cbab
nop

j dbab
nop

cbab:
addi $9,$0,97
sw $9,16($sp)

lw $11,16($sp)
sub $9,$0,$11
sw $9,20($sp)

addi $9,$0,97
sw $9,24($sp)

lw $11,24($sp)
lw $10,20($sp)
add $9,$10,$11
sw $9,20($sp)

addi $9,$0,36
sw $9,28($sp)

lw $11,28($sp)
lw $10,20($sp)
add $9,$10,$11
sw $9,20($sp)

lw $11,20($sp)
move $4,$11

sw $ra,128($sp)
jal gaaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,32($sp)
lw $11,32($sp)
move $4,$11

sw $ra,128($sp)
jal aaaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,40($sp)
lw $11,40($sp)
move $v0,$11
addi $sp,$sp,132
jr $ra
nop

dbab:
bbab:
addi $9,$0,43
sw $9,44($sp)

lw $11,44($sp)
lw $10,0($sp)
bne $10,$11,fbab
nop

j gbab
nop

fbab:
sw $ra,128($sp)
jal faaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,48($sp)
gbab:
addi $9,$0,48
sw $9,56($sp)

addi $9,$0,1
sw $9,60($sp)

lw $11,60($sp)
lw $10,56($sp)
sub $9,$10,$11
sw $9,64($sp)

lw $11,0($sp)
lw $10,64($sp)
sub $9,$10,$11
bltz $9,ibab
nop

j jbab
nop

ibab:
addi $9,$0,57
sw $9,68($sp)

addi $9,$0,1
sw $9,72($sp)

lw $11,72($sp)
lw $10,68($sp)
mult $10,$11
mflo $9
sw $9,76($sp)

lw $11,76($sp)
lw $10,0($sp)
sub $9,$10,$11
blez $9,bcab
nop

j ccab
nop

bcab:
lw $11,0($sp)
move $4,$11

sw $ra,128($sp)
jal aaaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,80($sp)
lw $11,80($sp)
move $v0,$11
addi $sp,$sp,132
jr $ra
nop

ccab:
jbab:
addi $9,$0,32
sw $9,84($sp)

lw $11,84($sp)
lw $10,0($sp)
sub $9,$10,$11
sw $9,88($sp)

lw $11,88($sp)
move $4,$11

addi $9,$0,126
sw $9,92($sp)

addi $9,$0,32
sw $9,96($sp)

lw $11,96($sp)
lw $10,92($sp)
sub $9,$10,$11
sw $9,100($sp)

addi $9,$0,1
sw $9,104($sp)

lw $11,104($sp)
lw $10,100($sp)
add $9,$10,$11
sw $9,100($sp)

lw $11,100($sp)
move $5,$11

sw $ra,128($sp)
jal caaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,108($sp)
addi $9,$0,32
sw $9,112($sp)

lw $11,112($sp)
lw $10,108($sp)
add $9,$10,$11
sw $9,116($sp)

lw $11,116($sp)
move $4,$11

sw $ra,128($sp)
jal aaaaaaab
nop
lw $ra,128($sp)
move $9,$v0
sw $9,120($sp)
lw $11,120($sp)
move $v0,$11
addi $sp,$sp,132
jr $ra
nop

addi $sp,$sp,132
jr $ra
nop

iaaaaaab:
#------------------------------
addi $sp,$sp,-36

sw $4,0($sp)

lw $11,0($sp)
move $4,$11

addi $9,$0,4
sw $9,4($sp)

lw $11,4($sp)
move $5,$11

sw $ra,32($sp)
jal caaaaaab
nop
lw $ra,32($sp)
move $9,$v0
sw $9,8($sp)
lw $11,0($sp)
move $4,$11

addi $9,$0,4
sw $9,12($sp)

lw $11,12($sp)
move $5,$11

sw $ra,32($sp)
jal caaaaaab
nop
lw $ra,32($sp)
move $9,$v0
sw $9,16($sp)
addi $10,$gp,76
lw $11,16($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,20($sp)
lw $11,0($sp)
lw $10,20($sp)
add $9,$10,$11
sw $9,24($sp)

addi $10,$gp,76
lw $9,24($sp)
lw $11,8($sp)
sll $11,$11,2
add $10,$10,$11
sw $9,0($10)
addi $sp,$sp,36
jr $ra
nop

abaaaaab:
#------------------------------
addi $sp,$sp,-76

sw $4,0($sp)

sw $5,4($sp)

addi $9,$0,0
sw $9,8($sp)

lw $11,8($sp)
lw $10,4($sp)
add $9,$10,$11
sw $9,12($sp)

lw $11,12($sp)
move $4,$11

sw $ra,72($sp)
jal gaaaaaab
nop
lw $ra,72($sp)
move $9,$v0
sw $9,16($sp)
lw $11,16($sp)
add $9,$0,$11
sw $9,20($sp)

lw $11,20($sp)
move $4,$11

sw $ra,72($sp)
jal iaaaaaab
nop
lw $ra,72($sp)
move $9,$v0
sw $9,24($sp)
addi $9,$0,13
sw $9,32($sp)

addi $9,$0,0
sw $9,36($sp)

addi $9,$0,1
sw $9,40($sp)

lw $11,40($sp)
lw $10,36($sp)
mult $10,$11
mflo $9
sw $9,44($sp)

lw $11,44($sp)
lw $10,32($sp)
add $9,$10,$11
sw $9,48($sp)

lw $11,48($sp)
lw $10,0($sp)
mult $10,$11
mflo $9
sw $9,52($sp)

lw $11,20($sp)
lw $10,52($sp)
add $9,$10,$11
sw $9,56($sp)

lw $11,56($sp)
move $4,$11

addi $9,$0,100007
sw $9,60($sp)

lw $11,60($sp)
move $5,$11

sw $ra,72($sp)
jal caaaaaab
nop
lw $ra,72($sp)
move $9,$v0
sw $9,64($sp)
lw $11,64($sp)
move $v0,$11
addi $sp,$sp,76
jr $ra
nop

addi $sp,$sp,76
jr $ra
nop

gbaaaaab:
#------------------------------
addi $sp,$sp,-48

sw $4,0($sp)

lw $11,40($gp)
add $9,$0,$11
sw $9,4($sp)

addi $9,$0,0
sw $9,8($sp)

lw $11,8($sp)
lw $10,4($sp)
sub $9,$10,$11
blez $9,ecab
nop

j fcab
nop

ecab:
addi $sp,$sp,48
jr $ra
nop

fcab:
lw $11,0($sp)
add $9,$0,$11
sw $9,72($gp)

addi $9,$0,0
sw $9,12($sp)

lw $11,12($sp)
add $9,$0,$11
sw $9,16($sp)

hcab:
lw $11,40($gp)
add $9,$0,$11
sw $9,20($sp)

lw $11,20($sp)
lw $10,16($sp)
sub $9,$10,$11
bltz $9,icab
nop

j jcab
nop

icab:
lw $11,72($gp)
add $9,$0,$11
sw $9,24($sp)

lw $11,24($sp)
move $4,$11

addi $10,$gp,96
lw $11,16($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,28($sp)
lw $11,28($sp)
move $5,$11

sw $ra,44($sp)
jal abaaaaab
nop
lw $ra,44($sp)
move $9,$v0
sw $9,32($sp)
lw $11,32($sp)
add $9,$0,$11
sw $9,72($gp)

lw $10,16($sp)
addi $9,$10,1
sw $9,16($sp)

j hcab
nop

jcab:
addi $sp,$sp,48
jr $ra
nop

jbaaaaab:
#------------------------------
addi $sp,$sp,-220

addi $9,$0,0
sw $9,0($sp)

lw $11,0($sp)
add $9,$0,$11
sw $9,40($gp)

addi $9,$0,391
sw $9,4($sp)

lw $11,4($sp)
move $4,$11

sw $ra,216($sp)
jal gbaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,8($sp)
li $v0,5
syscall
sw $2,40($gp)
addi $9,$0,0
sw $9,16($sp)

lw $11,16($sp)
add $9,$0,$11
sw $9,20($sp)

bdab:
lw $11,40($gp)
add $9,$0,$11
sw $9,24($sp)

lw $11,24($sp)
lw $10,20($sp)
sub $9,$10,$11
bltz $9,cdab
nop

j ddab
nop

cdab:
li $v0,12
syscall
sw $2,28($sp)
la $a0,newLine
li $v0,4
syscall
addi $10,$gp,96
lw $9,28($sp)
lw $11,20($sp)
sll $11,$11,2
add $10,$10,$11
sw $9,0($10)
lw $10,20($sp)
addi $9,$10,1
sw $9,20($sp)

j bdab
nop

ddab:
addi $9,$0,20
sw $9,32($sp)

lw $11,32($sp)
sub $9,$0,$11
sw $9,36($sp)

lw $11,36($sp)
move $4,$11

addi $9,$0,2
sw $9,40($sp)

lw $11,40($sp)
move $5,$11

sw $ra,216($sp)
jal caaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,44($sp)
lw $11,44($sp)
add $9,$0,$11
sw $9,20($sp)

addi $9,$0,1
sw $9,48($sp)

lw $11,48($sp)
move $4,$11

addi $9,$0,2
sw $9,52($sp)

lw $11,52($sp)
move $5,$11

sw $ra,216($sp)
jal caaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,56($sp)
lw $11,56($sp)
add $9,$0,$11
sw $9,20($sp)

addi $9,$0,3
sw $9,60($sp)

lw $11,60($sp)
move $4,$11

addi $9,$0,2
sw $9,64($sp)

lw $11,64($sp)
move $5,$11

sw $ra,216($sp)
jal caaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,68($sp)
lw $11,68($sp)
add $9,$0,$11
sw $9,20($sp)

addi $9,$0,0
sw $9,72($sp)

lw $11,72($sp)
move $4,$11

sw $ra,216($sp)
jal gaaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,76($sp)
lw $11,76($sp)
add $9,$0,$11
sw $9,80($sp)

addi $9,$0,43
sw $9,84($sp)

addi $9,$0,1
sw $9,88($sp)

lw $11,88($sp)
lw $10,84($sp)
div $10,$11
mflo $9
sw $9,92($sp)

lw $11,92($sp)
move $4,$11

sw $ra,216($sp)
jal gaaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,96($sp)
lw $11,96($sp)
add $9,$0,$11
sw $9,80($sp)

addi $9,$0,48
sw $9,100($sp)

addi $9,$0,1
sw $9,104($sp)

lw $11,104($sp)
lw $10,100($sp)
sub $9,$10,$11
sw $9,108($sp)

lw $11,108($sp)
move $4,$11

sw $ra,216($sp)
jal gaaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,112($sp)
lw $11,112($sp)
add $9,$0,$11
sw $9,80($sp)

addi $9,$0,49
sw $9,116($sp)

addi $9,$0,0
sw $9,120($sp)

lw $11,120($sp)
lw $10,116($sp)
sub $9,$10,$11
sw $9,124($sp)

lw $11,124($sp)
move $4,$11

sw $ra,216($sp)
jal gaaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,128($sp)
lw $11,128($sp)
add $9,$0,$11
sw $9,80($sp)

lw $11,40($gp)
add $9,$0,$11
sw $9,132($sp)

lw $11,132($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

la $a0,string0
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

lw $11,40($gp)
add $9,$0,$11
sw $9,140($sp)

addi $9,$0,1
sw $9,144($sp)

lw $11,144($sp)
lw $10,140($sp)
sub $9,$10,$11
sw $9,148($sp)

lw $11,148($sp)
add $9,$0,$11
sw $9,20($sp)

fdab:
addi $9,$0,0
sw $9,152($sp)

lw $11,152($sp)
lw $10,20($sp)
sub $9,$10,$11
bgez $9,gdab
nop

j hdab
nop

gdab:
addi $10,$gp,96
lw $11,20($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,156($sp)
lw $11,156($sp)
add $9,$0,$11
sw $9,80($sp)

addi $10,$gp,96
lw $11,20($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,160($sp)
lw $11,160($sp)
move $a0,$11
li $v0,11
syscall
la $a0,newLine
li $v0,4
syscall

lw $10,20($sp)
addi $9,$10,-1
sw $9,20($sp)

j fdab
nop

hdab:
addi $9,$0,391
sw $9,164($sp)

lw $11,164($sp)
move $4,$11

sw $ra,216($sp)
jal gbaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,168($sp)
la $a0,string1
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

lw $11,72($gp)
add $9,$0,$11
sw $9,176($sp)

lw $11,176($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

lw $11,92($gp)
add $9,$0,$11
sw $9,180($sp)

addi $9,$0,0
sw $9,184($sp)

lw $11,184($sp)
lw $10,180($sp)
add $9,$10,$11
sw $9,188($sp)

lw $11,188($sp)
move $4,$11

sw $ra,216($sp)
jal gaaaaaab
nop
lw $ra,216($sp)
move $9,$v0
sw $9,192($sp)
lw $11,192($sp)
add $9,$0,$11
sw $9,80($sp)

la $a0,string2
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

lw $11,80($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

addi $9,$0,0
sw $9,200($sp)

lw $11,200($sp)
add $9,$0,$11
sw $9,20($sp)

jdab:
addi $9,$0,4
sw $9,204($sp)

lw $11,204($sp)
lw $10,20($sp)
sub $9,$10,$11
bltz $9,aeab
nop

j beab
nop

aeab:
la $a0,string0
li $v0,4
syscall
la $a0,newLine
li $v0,4
syscall

addi $10,$gp,76
lw $11,20($sp)
sll $11,$11,2
add $10,$10,$11
lw $9,0($10)
sw $9,208($sp)
lw $11,208($sp)
move $a0,$11
li $v0,1
syscall
la $a0,newLine
li $v0,4
syscall

lw $10,20($sp)
addi $9,$10,1
sw $9,20($sp)

j jdab
nop

beab:
