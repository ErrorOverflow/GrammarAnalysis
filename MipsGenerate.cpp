//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "MipsGenerate.h"
#include "PCodeGenerate.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>

using namespace std;

string result;

void WriteMipsFile() {
    FILE *fp = fopen("C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\result.asm", "w");
    char stream[64] = ".data";
    char cat[64];
    char name[64];
    fputs(stream, fp);
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            if (iter->second.type == 3) {
                strcpy(stream, "string");
                //SpaceDel(name, iter->second.name);
                //strcat(stream,);
                //fputs(, fp);
            }
        }
    }
}

void OpCheck() {
    for (int i = 0; i < pcode_num; i++) {
        PCode pc = pcode[i];
        switch (pc.op) {
            case 101:
                cout << " PARA ";
                break;
            case 102:
                cout << " PUSH ";
                break;
            case 103:
                cout << " CALL ";
                break;
            case 104:
                cout << " RET ";
                break;
            case 105:
                cout << " GOTO ";
                break;
            case 106:
                cout << " PLUS ";
                break;
            case 107:
                cout << " SUB ";
                break;
            case 108:
                cout << " MULTI ";
                break;
            case 109:
                cout << " DIV ";
                break;
            case 110:
                cout << "--- LABEL ---";
                break;
            case 111:
                cout << " BEQ ";
                break;
            case 112:
                cout << " BNE ";
                break;
            case 113:
                cout << " BLEZ ";
                break;
            case 114:
                cout << " BGTZ ";
                break;
            case 115:
                cout << " BLTZ ";
                break;
            case 116:
                cout << " BGEZ ";
                break;
            case 117:
                cout << " WRITE ";
                break;
            case 118:
                cout << " READ ";
                break;
            case 119:
                cout << " ADI ";
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