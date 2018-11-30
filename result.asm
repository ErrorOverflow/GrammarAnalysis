.data
string0: .ascii "not H"
string5: .ascii "b is not bigger than c[5]\n"
string1: .ascii "next period\n"
f: .space 80
string4: .ascii "b is bigger than c[5]\n"
a: .space 40
newLine: .ascii "\n"


.text
faaaaaab:
move $fp,$sp
addi $sp,$sp,-64

lw $t1,12($sp)
lw $t2,16($sp)
bgez $t1,$t2,aaab
nop

j aaab
aaab:

lw $t1,24($sp)
lw $t2,28($sp)
blez $t1,$t2,baab
nop

j baab
baab:
haaaaaab:
move $fp,$sp
addi $sp,$sp,-24

lw $t1,8($sp)
lw $t2,12($sp)
beq $t1,$t2,caab
nop

j caab
caab:
jaaaaaab:
move $fp,$sp
addi $sp,$sp,-188
daab:

lw $t1,88($sp)
lw $t2,92($sp)
bltz $t1,$t2,daab
nop

j daab
eaab:
faab:

lw $t1,116($sp)
lw $t2,120($sp)
bltz $t1,$t2,faab
nop

j faab
gaab:

lw $t1,148($sp)
lw $t2,152($sp)
bgtz $t1,$t2,haab
nop

j haab
haab:
