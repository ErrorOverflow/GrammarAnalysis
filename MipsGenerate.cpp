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
                FuncRuntime funcRuntime = {iter->second.name, func_code, local_code_max - local_code_min,
                                           mid_code_max - MID_CODE_BASE};
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
    FuncRuntime funcRuntime = {iter->second.name, func_code, local_code_max - local_code_min,
                               mid_code_max - MID_CODE_BASE};
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
                break;
            case 105:
                //cout << " GOTO ";
                char word[64];
                Num2Char(pc.z, word);
                file << "j " << word << "\n";
                break;
            case 106:
                //cout << " PLUS ";
                break;
            case 107:
                //cout << " SUB ";
                break;
            case 108:
                //cout << " MULTI ";
                break;
            case 109:
                //cout << " DIV ";
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
                    file << "addi $sp,$sp," << (iter->second.local_code_num + iter->second.mid_code_num) * -4 << "\n";
                }
                break;
            }
            case 111:
                //cout << " BEQ ";
                file << "nop\n";
                break;
            case 112:
                //cout << " BNE ";
                file << "nop\n";
                break;
            case 113:
                //cout << " BLEZ ";
                file << "nop\n";
                break;
            case 114:
                //cout << " BGTZ ";
                file << "nop\n";
                break;
            case 115:
                //cout << " BLTZ ";
                file << "nop\n";
                break;
            case 116:
                //cout << " BGEZ ";
                file << "nop\n";
                break;
            case 117:
                //cout << " WRITE ";
                break;
            case 118:
                //cout << " READ ";
                break;
            case 119:
                //cout << " ADI ";
                break;
            case 120:
                //cout << " OFFSET ";
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
