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
nop
aaab:
nop
baab:
haaaaaab:
move $fp,$sp
addi $sp,$sp,-24
nop
caab:
jaaaaaab:
move $fp,$sp
addi $sp,$sp,-188
daab:
nop
j daab
eaab:
faab:
nop
j faab
gaab:
nop
haab:
