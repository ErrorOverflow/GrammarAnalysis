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


string result;
unordered_map<int, FuncRuntime> RuntimeStack;

void WriteMipsFile() {
    const char MIPSFILE[64] = "C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\result.asm";
    FuncRuntimeCheck();
    ofstream file;
    file.open(MIPSFILE, ios::out);
    file << ".data\n";
    StaticDataOutput(file);
    file << "\n.text\n";
    TextDataOutput(file);
    file.close();
}

void FuncRuntimeCheck() {
    int local_code_min = 0;
    int local_code_max = 0;
    int mid_code_max = 0;
    int func_code = 0;
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE && pcode[i].z < MID_CODE_BASE) {
            if (func_code != 0) {
                auto iter = CodeFind(func_code);
                FuncRuntime funcRuntime = {iter->second.name, func_code, local_code_max, local_code_min,
                                           mid_code_max};
                RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
                local_code_max = 0;
                local_code_min = 0;
                mid_code_max = 0;
            }
            func_code = pcode[i].z;
        } else {
            if (pcode[i].x >= LOCAL_CODE_BASE && pcode[i].x < MID_CODE_BASE) {
                if (pcode[i].x > local_code_max) {
                    local_code_max = pcode[i].x;
                }
                if (pcode[i].x < local_code_min || local_code_min == 0) {
                    local_code_min = pcode[i].x;
                }
            } else if (pcode[i].x >= MID_CODE_BASE && pcode[i].x > mid_code_max) {
                mid_code_max = pcode[i].x;
            }
            if (pcode[i].y >= LOCAL_CODE_BASE && pcode[i].y < MID_CODE_BASE) {
                if (pcode[i].y > local_code_max) {
                    local_code_max = pcode[i].y;
                }
                if (pcode[i].y < local_code_min || local_code_min == 0) {
                    local_code_min = pcode[i].y;
                }
            } else if (pcode[i].y >= MID_CODE_BASE && pcode[i].y > mid_code_max) {
                mid_code_max = pcode[i].y;
            }
            if (pcode[i].z >= LOCAL_CODE_BASE && pcode[i].z < MID_CODE_BASE && pcode[i].op != ADI) {
                if (pcode[i].z > local_code_max) {
                    local_code_max = pcode[i].z;
                }
                if (pcode[i].z < local_code_min || local_code_min == 0) {
                    local_code_min = pcode[i].z;
                }
            } else if (pcode[i].z >= MID_CODE_BASE && pcode[i].z > mid_code_max && pcode[i].op != LABEL) {
                mid_code_max = pcode[i].z;
            }
        }
    }
    auto iter = CodeFind(func_code);
    FuncRuntime funcRuntime = {iter->second.name, func_code, local_code_max, local_code_min,
                               mid_code_max};
    RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
}

void StaticDataOutput(ofstream &file) {
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            if (iter->second.type == 3) {
                file << iter->second.label << ": .ascii " << "\"" << iter->second.name << "\"\n";
            } else if (iter->second.dimension >= 1 && iter->second.kind == 1) {
                file << iter->second.name << ": .space " << iter->second.dimension * 4 << "\n";
            }
            iter++;
        }
    }
    file << "newLine: .ascii \"\\n\"\n" << endl;
}

void TextDataOutput(ofstream &file) {
    char word[64];
    int func_code = 0;
    unordered_map<int, FuncRuntime>::iterator iter;
    for (int i = 0; i < pcode_num; i++) {
        PCode pc = pcode[i];
        switch (pc.op) {
            case 101:
                //cout << " PARA ";
                break;
            case 102:
                //cout << " PUSH ";
                break;
            case 103:
                //cout << " CALL ";
                break;
            case 104:
                //cout << " RET ";
                file << "move $vo," << Z_FIND << "\n";
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
                if (Z_FIND < 0) {
                    cout << pc.z << endl;
                }
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
                    file << "mult $t1,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "mult $t1,$0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "mult $t1,$t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "mult $t1,$t2,$t3" << "\n";
                }
                file << "mflo " << X_FIND << "\n\n";
                break;
            case 109:
                //cout << " DIV ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0 && pc.z == 0) {
                    file << "div $t1,$0,$0" << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "div $t1,$0,$t3" << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "div $t1,$t2,$0" << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t3," << Z_FIND << "($sp)" << "\n";
                    file << "div $t1,$t2,$t3" << "\n";
                }
                file << "mflo " << X_FIND << "\n\n";
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
                    file << "move $fp,$sp\n";
                    auto iter = RuntimeStack.find(pc.z);
                    file << "addi $sp,$sp," <<
                         (iter->second.local_code_max - iter->second.local_code_min + iter->second.mid_code_max -
                          MID_CODE_BASE) * -4 << "\n";
                    func_code = pc.z;
                }
                file << "\n";
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
                //cout << " BLEZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "blez $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "blez $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "blez $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "blez $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 114:
                //cout << " BGTZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "bgtz $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bgtz $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "bgtz $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bgtz $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 115:
                //cout << " BLTZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "bltz $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bltz $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "bltz $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bltz $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 116:
                //cout << " BGEZ ";
                iter = RuntimeStack.find(func_code);
                Num2Char(pc.x, word);
                if (pc.y == 0 && pc.z == 0) {
                    file << "bgez $t1,$t2," << word << "\n";
                } else if (pc.y == 0) {
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bgez $0,$t2," << word << "\n";
                } else if (pc.z == 0) {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "bgez $t1,$0," << word << "\n";
                } else {
                    file << "lw $t1," << Y_FIND << "($sp)" << "\n";
                    file << "lw $t2," << Z_FIND << "($sp)" << "\n";
                    file << "bgez $t1,$t2," << word << "\n";
                }
                file << "nop\n";
                file << "\n";
                break;
            case 117:
                //cout << " WRITE ";
                break;
            case 118:
                //cout << " READ ";
                break;
            case 119:
                //cout << " ADI ";
                iter = RuntimeStack.find(func_code);
                if (pc.y == 0) {
                    file << "adi $t1,$0," << pc.z << "\n";
                } else {
                    file << "lw $t2," << Y_FIND << "($sp)" << "\n";
                    file << "adi $t1,$t2," << pc.z << "\n";
                }
                file << "sw $t1," << X_FIND << "($sp)" << "\n";
                file << "\n";
                break;
            case 120:
                cout << " OFFSET ";
                break;
            default:
                cout << pc.op << "unknown op" << endl;
                exit(-1);
        }
    }
}

void PrintASM(int reg) {
    //result.append("move $a0,$"+reg+"\n");
    result.append("li $v0,4");
    result.append("syscall\n");
}

void PrintASM(string label) {
    result.append("la $a0," + label + "\n");
    result.append("li $v0,4");
    result.append("syscall\n");
}

void WriteMips() {
    cout << result << endl;
}
