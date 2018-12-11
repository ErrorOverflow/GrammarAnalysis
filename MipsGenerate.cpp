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
    int space = 0;
    for (int i = GLOBAL_CODE_BASE; i < GlobalCode; i++) {
        auto iter = CodeFind(i);
        if (iter->second.dimension == 0) {
            space++;
        } else {
            space += iter->second.dimension;
        }
    }
    file << "_GLOBAL: .space " << space * 4 << "\n";
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
    int func_code = 0, round = 0, i = 0, para_reg = 0;
    unordered_map<int, FuncRuntime>::iterator iter;
    unordered_map<string, Sym>::iterator it;
    unordered_map<int, Sym>::iterator it_code;
    unordered_map<int, int>::iterator it_type;
    file << "la $gp,_GLOBAL\n";
    it = SymFind("main");
    Num2Char(it->second.code, word);
    file << "j " << word << "\n";
    for (round = 0; round < pcode_num; round++) {
        PCode pc = pcode[round];
        switch (pc.op) {
            case 101: {
                //cout << " PARA ";
                Reg2Mem(PARA_REG_FIND, pc.z, file);
                file << "\n";
                if (pcode[round + 1].op != PARA)
                    para_reg = 0;
                else
                    para_reg++;
                break;
            }
            case 102:
                //cout << " PUSH ";
                Mem2Reg(11, pc.z, file);
                file << "move $" << PARA_REG_FIND << ",$11\n\n";
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
                file << "move $9,$v0\n";
                Reg2Mem(9, pc.x, file);
                para_reg = 0;
                break;
            case 104:
                //cout << " RET ";
                iter = RuntimeStack.find(func_code);
                Mem2Reg(11, pc.z, file);
                file << "move $v0,$11" << "\n";
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
                if (pc.y == 0 && pc.z == 0) {
                    file << "add $9,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    if (pc.z >= GLOBAL_CODE_BASE && pc.z < MID_CODE_BASE && CodeFind(pc.z)->second.type == 1) {
                        RuntimeType.insert(pair<int, int>{pc.x, pc.x});
                    } else if (pc.z >= MID_CODE_BASE && RuntimeType.find(pc.z) != RuntimeType.end()) {
                        RuntimeType.insert(pair<int, int>{pc.x, pc.x});
                    }
                    Mem2Reg(11, pc.z, file);
                    file << "add $9,$0,$11" << "\n";
                } else if (pc.z == 0) {
                    if (pc.y >= GLOBAL_CODE_BASE && pc.y < MID_CODE_BASE && CodeFind(pc.y)->second.type == 1) {
                        RuntimeType.insert(pair<int, int>{pc.x, pc.x});
                    } else if (pc.y >= MID_CODE_BASE && RuntimeType.find(pc.y) != RuntimeType.end()) {
                        RuntimeType.insert(pair<int, int>{pc.x, pc.x});
                    }
                    Mem2Reg(10, pc.y, file);
                    file << "add $9,$10,$0" << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "add $9,$10,$11" << "\n";
                }
                Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            case 107:
                //cout << " SUB ";
                if (pc.y == 0 && pc.z == 0) {
                    file << "sub $9,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "sub $9,$0,$11" << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$0" << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$11" << "\n";
                }
                Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            case 108:
                //cout << " MULTI ";
                if (pc.y == 0 && pc.z == 0) {
                    file << "mult $0,$0" << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "mult $0,$11" << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "mult $10,$0" << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "mult $10,$11" << "\n";
                }
                file << "mflo $9\n";
                Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            case 109:
                //cout << " DIV ";
                if (pc.y == 0 && pc.z == 0) {
                    file << "div $0,$0" << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "div $0,$11" << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "div $10,$0" << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "div $10,$11" << "\n";
                }
                file << "mflo $9\n";
                Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            case 110: {
                //cout << " --- LABEL --- ";
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
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "j " << word << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "beq $0,$11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "beq $10,$0," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "beq $10,$11," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 112:
                //cout << " BNE ";
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "bne $0,$11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "bne $10,$0," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "bne $10,$11," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 113:
                //cout << " BLEZ <=";
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "j " << word << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "bgez $11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "blez $10," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$11\n";
                    file << "blez $9," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 114:
                //cout << " BGTZ >";
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "bltz $11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "bgtz $10," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$11\n";
                    file << "bgtz $9," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 115:
                //cout << " BLTZ ";
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "bgtz $11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "bltz $10," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$11\n";
                    file << "bltz $9," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 116:
                //cout << " BGEZ ";
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "j " << word << "\n";
                } else if (pc.y == 0) {
                    Mem2Reg(11, pc.z, file);
                    file << "blez $11," << word << "\n";
                } else if (pc.z == 0) {
                    Mem2Reg(10, pc.y, file);
                    file << "bgez $10," << word << "\n";
                } else {
                    Mem2Reg(11, pc.z, file);
                    Mem2Reg(10, pc.y, file);
                    file << "sub $9,$10,$11\n";
                    file << "bgez $9," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 117:
                //cout << " WRITE ";
                if (pc.z >= MID_CODE_BASE) {
                    it_type = RuntimeType.find(pc.z);
                    Mem2Reg(11, pc.z, file);
                    file << "move $a0,$11\n";
                    if (it_type != RuntimeType.end())
                        file << "li $v0,11\n";
                    else
                        file << "li $v0,1\n";
                    file << "syscall\n";
                } else if (pc.z >= LOCAL_CODE_BASE && pc.z < MID_CODE_BASE) {
                    it_code = CodeFind(pc.z);
                    if (it_code->second.type == 3) {
                        file << "la $a0," << it_code->second.label << "\n";
                        file << "li $v0,4\n";
                    } else if (it_code->second.type == 0) {
                        Mem2Reg(11, pc.z, file);
                        file << "move $a0,$11\n";
                        file << "li $v0,1\n";
                    } else if (it_code->second.type == 1) {
                        Mem2Reg(11, pc.z, file);
                        file << "move $a0,$11\n";
                        file << "li $v0,11\n";
                    }
                    file << "syscall\n";
                }
                file << "la $a0,newLine\n";
                file << "li $v0,4\n";
                file << "syscall\n\n";
                break;
            case 118:
                //cout << " READ ";
                it_code = CodeFind(pc.z);
                if (it_code->second.type == 0) {
                    file << "li $v0,5\n";
                    file << "syscall\n";
                    Reg2Mem(2, pc.z, file);
                } else {
                    file << "li $v0,12\n";
                    file << "syscall\n";
                    Reg2Mem(2, pc.z, file);
                    file << "la $a0,newLine\n";
                    file << "li $v0,4\n";
                    file << "syscall\n";
                }
                break;
            case 119:
                //cout << " ADI ";
                if (pc.y == 0) {
                    file << "addi $9,$0," << pc.z << "\n";
                } else {
                    Mem2Reg(10, pc.y, file);
                    file << "addi $9,$10," << pc.z << "\n";
                }
                Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            case 120: {
                //cout << " LDA ";
                int loc = 0;
                if (pc.y >= GLOBAL_CODE_BASE && pc.y < MID_CODE_BASE && CodeFind(pc.y)->second.type == 1) {
                    RuntimeType.insert(pair<int, int>{pc.x, pc.x});
                }
                if (pc.y >= LOCAL_CODE_BASE) {
                    it_code = CodeFind(pc.y);
                    file << "la $10," << it_code->second.name << "\n";
                } else {
                    for (i = GLOBAL_CODE_BASE; i < GlobalCode - 1; i++) {
                        it_code = CodeFind(i);
                        if (it_code->second.dimension == 0)
                            loc++;
                        else
                            loc += it_code->second.dimension;
                    }
                    file << "addi $10,$gp," << loc * 4 << "\n";
                }
                Mem2Reg(11, pc.z, file);
                file << "sll $11,$11,2\nadd $10,$10,$11\n";
                file << "lw $9,0($10)\n";
                Reg2Mem(9, pc.x, file);
                break;
            }
            case 121:
                //cout << " END ";
                iter = RuntimeStack.find(func_code);
                file << "addi $sp,$sp,"
                     << (iter->second.space + 2) * 4 << "\n";
                file << "jr $ra\nnop\n\n";
                break;
            case 122: {
                //cout << " SW ";
                int loc = 0;
                if (pc.y >= LOCAL_CODE_BASE) {
                    it_code = CodeFind(pc.y);
                    file << "la $10," << it_code->second.name << "\n";
                } else {
                    for (i = GLOBAL_CODE_BASE; i < GlobalCode - 1; i++) {
                        it_code = CodeFind(i);
                        if (it_code->second.dimension == 0)
                            loc++;
                        else
                            loc += it_code->second.dimension;
                    }
                    file << "addi $10,$gp," << loc * 4 << "\n";
                }
                Mem2Reg(9, pc.x, file);
                Mem2Reg(11, pc.z, file);
                file << "sll $11,$11,2\nadd $10,$10,$11\n";
                file << "sw $9,0($10)\n";
                break;
            }
            case 123:
                //cout << " NOP ";
                break;
            default:
                cout << pc.op << "unknown op" << endl;
                exit(-1);
        }
    }
}

void Mem2Reg(int reg, int code, ofstream &file) {
    int loc = 0;
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        for (int i = GLOBAL_CODE_BASE; i < code; i++) {
            auto iter = CodeFind(i);
            if (iter->second.dimension == 0)
                loc++;
            else
                loc += iter->second.dimension;
        }
        file << "lw $" << reg << "," << loc * 4 << "($gp)\n";
    } else {
        file << "lw $" << reg << "," << CODE_FIND << "($sp)\n";
    }
}

void Reg2Mem(int reg, int code, ofstream &file) {
    int loc = 0;
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        for (int i = GLOBAL_CODE_BASE; i < code; i++) {
            auto iter = CodeFind(i);
            if (iter->second.dimension == 0)
                loc++;
            else
                loc += iter->second.dimension;
        }
        file << "sw $" << reg << "," << loc * 4 << "($gp)\n";
    } else {
        file << "sw $" << reg << "," << CODE_FIND << "($sp)\n";
    }
}