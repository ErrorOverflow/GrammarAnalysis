//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "MipsGenerate.h"
#include "PCodeGenerate.h"
#include "lib.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <unordered_map>

using namespace std;

unordered_map<int, FuncRuntime> RuntimeStack;
unordered_map<int, int> RegPool;

int para_stack[64];
int para_stack_num = 0;
int sp_extra_space = 0;

void WriteMipsFile() {
    const char MIPSFILE[64] = "result.asm\0";
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
    file << "la $gp,_GLOBAL\n";
    it = SymFind("main");
    Num2Char(it->second.code, word);
    file << "j " << word << "\n";
    for (round = 0; round < pcode_num; round++) {
        PCode pc = pcode[round];
        switch (pc.op) {
            case PARA:
                Reg2Mem(PARA_REG_FIND, pc.z, file);
                file << "\n";
                if (pcode[round + 1].op != PARA)
                    para_reg = 0;
                else
                    para_reg++;
                break;
            case PUSH:
                Mem2Reg(11, pc.z, file);
                file << "move $" << PARA_REG_FIND << ",$11\n\n";
                para_reg++;
                break;
            case CALL:
                Num2Char(pc.z, word);
                file << "addi $sp,$sp," << -4 << "\n";
                file << "sw $ra,0($sp)\n";
                file << "jal " << word << "\nnop\n";
                file << "lw $ra,0($sp)\n";
                file << "addi $sp,$sp," << 1 * 4 << "\n";
                file << "move $9,$v0\n";
                Reg2Mem(9, pc.x, file);
                para_reg = 0;
                break;
            case RET:
                iter = RuntimeStack.find(func_code);
                Mem2Reg(11, pc.z, file);
                file << "move $v0,$11" << "\n";
                file << "addi $sp,$sp,"
                     << (iter->second.space + 1) * 4 << "\n";
                file << "jr $ra" << "\nnop\n\n";
                break;
            case GOTO:
                Num2Char(pc.z, word);
                file << "j " << word << "\nnop\n\n";
                break;
            case PLUS: {
                int reg_x = 8, reg_y = 9, reg_z = 10;
                if (RegPool.find(pc.x) != RegPool.end())
                    reg_x = RegPool.find(pc.x)->second;
                if (code_info.find(pc.y)->second.isValue && code_info.find(pc.z)->second.isValue) {
                    file << "addi $" << reg_x << ",$0,"
                         << code_info.find(pc.y)->second.value + code_info.find(pc.z)->second.value << "\n";
                } else if (code_info.find(pc.y)->second.isValue) {
                    reg_z = Mem2Reg(10, pc.z, file);
                    file << "addi $" << reg_x << ",$" << reg_z << "," << code_info.find(pc.y)->second.value << "\n";
                } else if (code_info.find(pc.z)->second.isValue) {
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "addi $" << reg_x << ",$" << reg_y << "," << code_info.find(pc.z)->second.value << "\n";
                } else {
                    reg_z = Mem2Reg(10, pc.z, file);
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "add $" << reg_x << ",$" << reg_y << ",$" << reg_z << "\n";
                }
                if (reg_x == 8)
                    Reg2Mem(9, pc.x, file);
                file << "\n";
                break;
            }
            case SUB: {
                int reg_x = 8, reg_y = 9, reg_z = 10;
                if (RegPool.find(pc.x) != RegPool.end())
                    reg_x = RegPool.find(pc.x)->second;
                if (code_info.find(pc.y)->second.isValue && code_info.find(pc.z)->second.isValue) {
                    file << "addi $" << reg_x << ",$0,"
                         << code_info.find(pc.y)->second.value - code_info.find(pc.z)->second.value << "\n";
                } else if (code_info.find(pc.y)->second.isValue) {
                    reg_z = Mem2Reg(10, pc.z, file);
                    file << "addi $9,$0," << code_info.find(pc.y)->second.value << "\n";
                    file << "sub $" << reg_x << ",$9,$" << reg_z << "\n";
                } else if (code_info.find(pc.z)->second.isValue) {
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "subi $" << reg_x << ",$" << reg_y << "," << code_info.find(pc.z)->second.value << "\n";
                } else {
                    reg_z = Mem2Reg(10, pc.z, file);
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "sub $" << reg_x << ",$" << reg_y << ",$" << reg_z << "\n";
                }
                if (reg_x == 8)
                    Reg2Mem(8, pc.x, file);
                file << "\n";
                break;
            }
            case MUL: {
                int reg_x = 8, reg_y = 9, reg_z = 10;
                if (RegPool.find(pc.x) != RegPool.end())
                    reg_x = RegPool.find(pc.x)->second;
                if (code_info.find(pc.y)->second.isValue && code_info.find(pc.z)->second.isValue) {
                    file << "addi $" << reg_x << ",$0,"
                         << code_info.find(pc.y)->second.value * code_info.find(pc.z)->second.value << "\n";
                } else if (code_info.find(pc.y)->second.isValue) {
                    reg_z = Mem2Reg(10, pc.z, file);
                    file << "addi $9,$0," << code_info.find(pc.y)->second.value << "\n";
                    file << "mult $9,$" << reg_z << "\n";
                } else if (code_info.find(pc.z)->second.isValue) {
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "addi $10,$0," << code_info.find(pc.z)->second.value << "\n";
                    file << "mult $" << reg_y << ",$10\n";
                } else {
                    reg_z = Mem2Reg(10, pc.z, file);
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "mult $" << reg_y << ",$" << reg_z << "\n";
                }
                file << "mflo $" << reg_x << "\n";
                if (reg_x == 8)
                    Reg2Mem(8, pc.x, file);
                file << "\n";
                break;
            }
            case DIV: {
                int reg_x = 8, reg_y = 9, reg_z = 10;
                if (RegPool.find(pc.x) != RegPool.end())
                    reg_x = RegPool.find(pc.x)->second;
                if (code_info.find(pc.y)->second.isValue && code_info.find(pc.z)->second.isValue) {
                    file << "addi $" << reg_x << ",$0,"
                         << code_info.find(pc.y)->second.value * code_info.find(pc.z)->second.value << "\n";
                } else if (code_info.find(pc.y)->second.isValue) {
                    reg_z = Mem2Reg(10, pc.z, file);
                    file << "addi $9,$0," << code_info.find(pc.y)->second.value << "\n";
                    file << "div $9,$" << reg_z << "\n";
                } else if (code_info.find(pc.z)->second.isValue) {
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "addi $10,$0," << code_info.find(pc.z)->second.value << "\n";
                    file << "div $" << reg_y << ",$10\n";
                } else {
                    reg_z = Mem2Reg(10, pc.z, file);
                    reg_y = Mem2Reg(9, pc.y, file);
                    file << "div $" << reg_y << ",$" << reg_z << "\n";
                }
                file << "mflo $" << reg_x << "\n";
                if (reg_x == 8)
                    Reg2Mem(8, pc.x, file);
                file << "\n";
                break;
            }
            case LCH:
            case ADI:{
                int reg_x = 8;
                if (RegPool.find(pc.x) != RegPool.end())
                    reg_x = RegPool.find(pc.x)->second;
                file << "addi $" << reg_x << ",$0," << pc.z << "\n";
                if (reg_x == 8)
                    Reg2Mem(8, pc.x, file);
                file << "\n";
                break;
            }
            case LABEL: {
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
                         (iter->second.space + 1) * -4 << "\n\n";
                    func_code = pc.z;
                }
                break;
            }
            case BEQ:
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
            case BNE:
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
            case BLEZ:
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
            case BGTZ:
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
            case BLTZ:
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
            case BGEZ:
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
            case WRITE:
                if (pc.z >= MID_CODE_BASE) {
                    Mem2Reg(11, pc.z, file);
                    file << "move $a0,$11\n";
                    if (code_info.find(pc.z)->second.type)
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
                break;
            case READ:
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
            case LDA: {
                int loc = 0;
                if (pc.y >= LOCAL_CODE_BASE) {
                    it_code = CodeFind(pc.y);
                    file << "la $10," << it_code->second.name << "\n";
                } else {
                    for (i = GLOBAL_CODE_BASE; i < pc.y; i++) {
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
            case END:
                iter = RuntimeStack.find(func_code);
                if (iter->second.name != "main") {
                    file << "addi $sp,$sp,"
                         << (iter->second.space + 1) * 4 << "\n";
                    file << "jr $ra\nnop\n\n";
                }
                break;
            case SW: {
                int loc = 0;
                if (pc.y >= LOCAL_CODE_BASE) {
                    it_code = CodeFind(pc.y);
                    file << "la $10," << it_code->second.name << "\n";
                } else {
                    for (i = GLOBAL_CODE_BASE; i < pc.y; i++) {
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
            case NOP:
                break;
            case BEGIN:
                para_stack[para_stack_num++] = para_reg;
                if (para_reg) {
                    file << "addi $sp,$sp," << para_reg * -4 << "\n";
                    for (i = 0; i < para_reg; i++)
                        file << "sw $" << ((i <= 4) ? (i + 4) : (i + 8)) << "," << i * 4 << "($sp)\n";
                    sp_extra_space += para_reg;
                }
                para_reg = 0;
                break;
            case OVER:
                para_reg = para_stack[--para_stack_num];
                if (para_reg) {
                    for (i = 0; i < para_reg; i++)
                        file << "lw $" << ((i <= 4) ? (i + 4) : (i + 8)) << "," << i * 4 << "($sp)\n";
                    file << "addi $sp,$sp," << para_reg * 4 << "\n";
                    sp_extra_space -= para_reg;
                }
                break;
            default:
                cout << pc.op << "unknown op" << endl;
        }
    }
}

int Mem2Reg(int reg, int code, ofstream &file) {
    int loc = 0;
    int res_reg = 0;
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        for (int i = GLOBAL_CODE_BASE; i < code; i++) {
            auto iter = CodeFind(i);
            if (iter->second.dimension == 0)
                loc++;
            else
                loc += iter->second.dimension;
        }
        file << "lw $" << reg << "," << (loc + sp_extra_space) * 4 << "($gp)\n";
    } else {
        file << "lw $" << reg << "," << CODE_FIND << "($sp)\n";
    }
    return res_reg;
}

int Reg2Mem(int reg, int code, ofstream &file) {
    int loc = 0;
    int res_reg = 0;
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        for (int i = GLOBAL_CODE_BASE; i < code; i++) {
            auto iter = CodeFind(i);
            if (iter->second.dimension == 0)
                loc++;
            else
                loc += iter->second.dimension;
        }
        file << "sw $" << reg << "," << (loc + sp_extra_space) * 4 << "($gp)\n";
    } else {
        file << "sw $" << reg << "," << CODE_FIND << "($sp)\n";
    }
    return res_reg;
}