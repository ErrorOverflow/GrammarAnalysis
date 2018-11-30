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
unordered_map<int, int> RuntimeStack;

void WriteMipsFile() {
    const char MIPSFILE[64] = "C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\result.asm";
    ofstream file;
    file.open(MIPSFILE, ios::out);
    file << ".data\n";
    StaticDataOutput(file);
    file << "\n.text\n";
    TextDataOutput(file);
    file.close();
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
                int mid_code_max = MID_CODE_BASE;
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
                    auto iter = CodeFind(pc.z);
                    for (int j = 1; pcode[i + j].op != LABEL &&
                                    (pcode[i + j].z >= LOCAL_CODE_BASE && pcode[i + j].z < MID_CODE_BASE); j++) {
                        if (pcode[i + j].x > mid_code_max) {
                            mid_code_max = pcode[i + j].x;
                        }
                        if (pcode[i + j].y > mid_code_max) {
                            mid_code_max = pcode[i + j].y;
                        }
                        if (pcode[i + j].z > mid_code_max) {
                            mid_code_max = pcode[i + j].z;
                        }
                    }
                    file << "addi $sp,$sp," << (mid_code_max - MID_CODE_BASE) * 4 << "\n";
                }
                break;
            }
            case 111:
                //cout << " BEQ ";
                break;
            case 112:
                //cout << " BNE ";
                break;
            case 113:
                //cout << " BLEZ ";
                break;
            case 114:
                //cout << " BGTZ ";
                break;
            case 115:
                //cout << " BLTZ ";
                break;
            case 116:
                //cout << " BGEZ ";
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