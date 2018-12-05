//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "MipsGenerate.h"
#include "PCodeGenerate.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <unordered_map>

using namespace std;

unordered_map<int, FuncRuntime> RuntimeStack;
unordered_map<int, int> RuntimeType;

void WriteMipsFile() {
    const char MIPSFILE[64] = "C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\result.asm\0";
    //FuncRuntimeCheck();
    ofstream file;
    file.open(MIPSFILE, ios::out);
    file << ".data\n";
    StaticDataOutput(file);
    file << "\n.text\n";
    TextDataOutput(file);
    file.close();
}

void StaticDataOutput(ofstream &file) {
    file << "_GLOBAL: .space " << (GlobalCode - GLOBAL_CODE_BASE) * 4 << "\n";
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            if (iter->second.dimension >= 1 && iter->second.kind == 1) {
                file << iter->second.name << ": .space " << iter->second.dimension * 4 << "\n";
            }
            iter++;
        }
    }
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            if (iter->second.type == 3) {
                file << iter->second.label << ": .ascii " << "\"" << iter->second.name << "\\0\"\n";
            }
            iter++;
        }
    }
    file << "newLine: .ascii \"\\n\\0\"\n" << endl;
}

void TextDataOutput(ofstream &file) {
    char word[64];
    int func_code = 0;
    int para_reg = 0;
    unordered_map<int, FuncRuntime>::iterator iter;
    unordered_map<string, Sym>::iterator it;
    unordered_map<int, Sym>::iterator it_code;
    unordered_map<int, int>::iterator it_type;
    unordered_map<int, RuntimeCodeInfo>::iterator it_info;
    file << "la $gp,_GLOBAL\n";
    it = SymFind("main");
    Num2Char(it->second.code, word);
    file << "j " << word << "\n";
    for (int i = 0; i < pcode_num; i++) {
        PCode pc = pcode[i];
        switch (pc.op) {
            case 101: {
                //cout << " PARA ";
                iter = RuntimeStack.find(func_code);
                file << "move $t3,$" << PARA_REG_FIND << "\n";
                Reg2Mem(3, pc.z, iter, file);
                file << "\n";
                if (pcode[i + 1].op != PARA)
                    para_reg = 0;
                else
                    para_reg++;
                break;
            }
            case 102:
                //cout << " PUSH ";
                iter = RuntimeStack.find(func_code);
                Mem2Reg(3, pc.z, iter, file);
                file << "move $" << PARA_REG_FIND << ",$t3\n\n";
                para_reg++;
                break;
            case 103:
                //cout << " CALL ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.z, word);
                file << "sw $ra,"
                     << (iter->second.space + 1) * 4 << "($sp)\n";
                file << "jal " << word << "\nnop\n";
                file << "lw $ra,"
                     << (iter->second.space + 1) * 4 << "($sp)\n";
                file << "move $t1,$v0\n";
                Reg2Mem(1, pc.x, iter, file);
                para_reg = 0;
                break;
            case 104:
                //cout << " RET ";
                iter = RuntimeStack.find(func_code);
                Mem2Reg(3, pc.z, iter, file);
                file << "move $v0,$t3" << "\n";
                file << "addi $sp,$sp,"
                     << (iter->second.space + 2) * 4 << "\n";
                file << "jr $ra" << "\nnop\n\n";
                break;
            case 105:
                //cout << " GOTO ";
                Num2Char(pc.z, word);
                file << "j " << word << "\nnop\n\n";
                break;
            case 106:
                //cout << " PLUS ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0 && pc.z == 0) {
                    file << "add $t1,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "add $t1,$0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "add $t1,$t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "add $t1,$t2,$t3" << "\n";
                }
                file << "add $t1,$t2,$t3" << "\n";
                file << "sw $t1," << X_FIND << "($sp)" << "\n";
                file << "\n";
                break;
            case 107:
                //cout << " SUB ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0 && pc.z == 0) {
                    file << "sub $t1,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$t3" << "\n";
                }
                file << "sw $t1," << X_FIND << "($sp)" << "\n";
                file << "\n";
                break;
            case 108:
                //cout << " MULTI ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0 && pc.z == 0) {
                    file << "mult $0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "mult $0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "mult $t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "mult $t2,$t3" << "\n";
                }
                file << "mflo $t1\n" << "sw $t1," << X_FIND << "($sp)\n\n";
                break;
            case 109:
                //cout << " DIV ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0 && pc.z == 0) {
                    file << "div $0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "div $0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "div $t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "div $t2,$t3" << "\n";
                }
                file << "mflo $t1\n" << "sw $t1," << X_FIND << "($sp)\n\n";
                break;
            case 110: {
                //cout << " --- LABEL --- ";
                //int mid_code_max = MID_CODE_BASE;
                if (pc.z > 0 && pc.z <= MID_CODE_BASE) {
                    char label_name[16];
                    Num2Char(pc.z, label_name);
                    file << label_name << ":\n";
                } else {
                    cout << "label error";
                    exit(-3);
                }
                if (pc.z >= LOCAL_CODE_BASE && pc.z < MID_CODE_BASE) {
                    iter = RuntimeStack.find(pc.z);
                    file << "#------------------------------\n";
                    file << "addi $sp,$sp," <<
                         (iter->second.space + 2) * -4 << "\n\n";
                    func_code = pc.z;
                }
                break;
            }
            case 111:
                //cout << " BEQ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "beq $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "beq $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "beq $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "beq $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 112:
                //cout << " BNE ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "bne $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bne $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "bne $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bne $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 113:
                //cout << " BLEZ <=";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "j " << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "bgez $t3," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "blez $t2," << word << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$t3\n";
                    file << "blez $t1," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 114:
                //cout << " BGTZ >";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "bltz $t3," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "bgtz $t2," << word << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$t3\n";
                    file << "bgtz $t1," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 115:
                //cout << " BLTZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "bgtz $t3," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "bltz $t2," << word << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$t3\n";
                    file << "bltz $t1," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 116:
                //cout << " BGEZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "j " << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "blez $t3," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "bgez $t2," << word << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "sub $t1,$t2,$t3\n";
                    file << "bgez $t1," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 117:
                //cout << " WRITE ";
                iter = RuntimeStack.find(func_code);
                if (pc.z >= MID_CODE_BASE) {
                    it_type = RuntimeType.find(pc.z);
                    if (it_type != RuntimeType.end()) {
                        file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                        file << "move $a0,$t3\n";
                        file << "li $v0,11\n";
                        file << "syscall\n";
                    } else {
                        file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                        file << "move $a0,$t3\n";
                        file << "li $v0,1\n";
                        file << "syscall\n";
                    }
                } else if (pc.z >= LOCAL_CODE_BASE && pc.z < MID_CODE_BASE) {
                    it_code = CodeFind(pc.z);
                    if (it_code->second.type == 3) {
                        file << "la $a0," << it_code->second.label << "\n";
                        file << "li $v0,4\n";
                        file << "syscall\n";
                    } else {
                        file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                        file << "move $a0,$t3\n";
                        file << "li $v0,1\n";
                        file << "syscall\n";
                    }
                }
                file << "la $a0,newLine\n";
                file << "li $v0,4\n";
                file << "syscall\n\n";
                break;
            case 118:
                //cout << " READ ";
                iter = RuntimeStack.find(func_code);
                it_code = CodeFind(pc.z);
                if (it_code->second.type == 0) {
                    file << "li $v0,5\n";
                    file << "syscall\n";
                    file << "sw $v0," << Z_FIND << "($sp)\n\n";
                } else {
                    file << "li $v0,12\n";
                    file << "syscall\n";
                    file << "sw $v0," << Z_FIND << "($sp)\n\n";
                    file << "la $a0,newLine\n";
                    file << "li $v0,4\n";
                    file << "syscall\n";
                }
                break;
            case 119:
                //cout << " ADI ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0) {
                    file << "addi $t1,$0," << pc.z << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "addi $t1,$t2," << pc.z << "\n";
                }
                file << "sw $t1," << X_FIND << "($sp)" << "\n";
                file << "\n";
                break;
            case 120: {
                //cout << " LDA ";
                iter = RuntimeStack.find(func_code);
                it_code = CodeFind(pc.y);
                file << "la $t2," << it_code->second.name << "\n";
                file << "lw $t3," << Z_FIND << "($sp)\n";
                file << "sll $t3,$t3,2\nadd $t2,$t2,$t3\n";
                file << "lw $t1,0($t2)\n";
                file << "sw $t1," << X_FIND << "($sp)\n\n";
                break;
            }
            case 121:
                //cout << " END ";
                iter = RuntimeStack.find(func_code);
                file << "addi $sp,$sp,"
                     << (iter->second.space + 2) * 4 << "\n";
                file << "jr $ra\nnop\n\n";
                break;
            case 122:
                //cout << " SW ";
                iter = RuntimeStack.find(func_code);
                it_code = CodeFind(pc.y);
                file << "la $t2," << it_code->second.name << "\n";
                file << "lw $t1," << X_FIND << "($sp)\n";
                file << "lw $t3," << Z_FIND << "($sp)\n";
                file << "sll $t3,$t3,2\nadd $t2,$t2,$t3\n";
                file << "sw $t1,0($t2)\n";
                break;
            case 123:
                //cout << " NOP ";
                break;
            default:
                cout << pc.op << "unknown op" << endl;
                exit(-1);
        }
    }
}

void Mem2Reg(int reg, int code, unordered_map<int, FuncRuntime>::iterator iter, ofstream &file) {
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        file << "lw $t" << reg << "," << (code - GLOBAL_CODE_BASE) * 4 << "($gp)";
    } else {
        file << "lw $t" << reg << "," << CODE_FIND << "($sp)\n";
    }
}

void Reg2Mem(int reg, int code, unordered_map<int, FuncRuntime>::iterator iter, ofstream &file) {
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        file << "sw $t" << reg << "," << (code - GLOBAL_CODE_BASE) * 4 << "($gp)";
    } else {
        file << "sw $t" << reg << "," << CODE_FIND << "($sp)\n";
    }
}

void AddressPrint() {
    unordered_map<int, RuntimeCodeInfo>::iterator it_info;
    it_info = code_info.begin();
    while (it_info != code_info.end()) {
        cout << it_info->second.code << " " << it_info->second.address << endl;
        it_info++;
    }
}