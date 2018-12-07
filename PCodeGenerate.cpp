//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "PCodeGenerate.h"
#include "lib.h"
#include "MipsGenerate.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>


using namespace std;

PCode pcode[4096];
unordered_map<int, RuntimeCodeInfo> code_info;
int pcode_num;

void OpExchange(int op, ofstream &file);

void PCodeOptimize();

void AddressAssign();

void PCodeInsert(int num, int x, int y, int op, int z) {
    pcode[num].x = x;
    pcode[num].y = y;
    pcode[num].z = z;
    pcode[num].op = op;
}

void PCodePrint() {
    PCodeOptimize();
    AddressAssign();
    const char MIPSFILE[64] = "C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\PCode.txt\0";
    ofstream file;
    file.open(MIPSFILE, ios::out);
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP)
            continue;
        file << "PCode#" << i << ": ";
        cout << "PCode#" << i << ": ";
        if (pcode[i].x < MID_CODE_BASE && pcode[i].x >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].x, file);
        else {
            file << pcode[i].x;
            cout << pcode[i].x;
        }
        file << " ";
        cout << " ";
        if (pcode[i].y < MID_CODE_BASE && pcode[i].y >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].y, file);
        else {
            file << pcode[i].y;
            cout << pcode[i].y;
        }
        OpExchange(pcode[i].op, file);
        if (pcode[i].z < MID_CODE_BASE && pcode[i].z >= GLOBAL_CODE_BASE) {
            ZExchange(pcode[i].z, file);
        } else {
            file << pcode[i].z;
            cout << pcode[i].z;
        }
        file << "\n";
        cout << endl;
    }
    file.close();
}

void PCodeOptimize() {
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].x >= MID_CODE_BASE && pcode[i].y == 0 && pcode[i].op == PLUS && pcode[i].z >= LOCAL_CODE_BASE) {
            pcode[i].op = NOP;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].z;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].z;
                }
                if (pcode[j].x == pcode[i].x || pcode[j].op == LABEL) {
                    break;
                }
            }
        } else if (pcode[i].x >= MID_CODE_BASE && pcode[i].z == 0 && pcode[i].op == PLUS &&
                   pcode[i].y >= LOCAL_CODE_BASE) {
            pcode[i].op = NOP;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].y;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].y;
                }
                if (pcode[j].x == pcode[i].x || pcode[j].op == LABEL) {
                    break;
                }
            }
        }
    }
}

void AddressAssign() {
    int mid_code_stack = 0;
    int space = 0;
    int func_code = 0;
    unordered_map<int, RuntimeCodeInfo>::iterator iter;
    unordered_map<int, FuncRuntime>::iterator it;
    unordered_map<int, Sym>::iterator it_code;
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP) {
            continue;
        }
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE) {
            mid_code_stack = 0;
            if (func_code != 0) {
                it_code = CodeFind(func_code);
                FuncRuntime funcRuntime = {it_code->second.name, func_code, space};
                RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
            }
            func_code = pcode[i].z;
            space = 0;
            continue;
        }
        if (pcode[i].y >= LOCAL_CODE_BASE) {
            iter = code_info.find(pcode[i].y);
            if (iter == code_info.end()) {
                space++;
                RuntimeCodeInfo info = {pcode[i].y, 0, 0, mid_code_stack++};
                code_info.insert(pair<int, RuntimeCodeInfo>{pcode[i].x, info});
            }
        }
        if (pcode[i].x >= LOCAL_CODE_BASE) {
            iter = code_info.find(pcode[i].x);
            if (iter == code_info.end()) {
                space++;
                RuntimeCodeInfo info = {pcode[i].x, 0, 0, mid_code_stack++};
                code_info.insert(pair<int, RuntimeCodeInfo>{pcode[i].x, info});
            }
        }
        if (pcode[i].z >= LOCAL_CODE_BASE) {
            iter = code_info.find(pcode[i].z);
            if (iter == code_info.end()) {
                space++;
                RuntimeCodeInfo info = {pcode[i].z, 0, 0, mid_code_stack++};
                code_info.insert(pair<int, RuntimeCodeInfo>{pcode[i].z, info});
            }
        }
    }
    it_code = CodeFind(func_code);
    FuncRuntime funcRuntime = {it_code->second.name, func_code, space};
    RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
}

void OpExchange(int op, ofstream &file) {
    switch (op) {
        case 101:
            file << " PARA ";
            cout << " PARA ";
            break;
        case 102:
            file << " PUSH ";
            cout << " PUSH ";
            break;
        case 103:
            file << " CALL ";
            cout << " CALL ";
            break;
        case 104:
            file << " RET ";
            cout << " RET ";
            break;
        case 105:
            file << " GOTO ";
            cout << " GOTO ";
            break;
        case 106:
            file << " PLUS ";
            cout << " PLUS ";
            break;
        case 107:
            file << " SUB ";
            cout << " SUB ";
            break;
        case 108:
            file << " MULTI ";
            cout << " MULTI ";
            break;
        case 109:
            file << " DIV ";
            cout << " DIV ";
            break;
        case 110:
            file << " --- LABEL --- ";
            cout << " --- LABEL --- ";
            break;
        case 111:
            file << " BEQ ";
            cout << " BEQ ";
            break;
        case 112:
            file << " BNE ";
            cout << " BNE ";
            break;
        case 113:
            file << " BLEZ ";
            cout << " BLEZ ";
            break;
        case 114:
            file << " BGTZ ";
            cout << " BGTZ ";
            break;
        case 115:
            file << " BLTZ ";
            cout << " BLTZ ";
            break;
        case 116:
            file << " BGEZ ";
            cout << " BGEZ ";
            break;
        case 117:
            file << " WRITE ";
            cout << " WRITE ";
            break;
        case 118:
            file << " READ ";
            cout << " READ ";
            break;
        case 119:
            file << " ADI ";
            cout << " ADI ";
            break;
        case 120:
            file << " LDA ";
            cout << " LDA ";
            break;
        case 121:
            file << " END ";
            cout << " END ";
            break;
        case 122:
            file << " SW ";
            cout << " SW ";
            break;
        default:
            file << " " << op << " ";
            cout << " " << op << " ";
    }
}


void ZExchange(int z, ofstream &file) {
    auto iter = CodeFind(z);
    file << iter->second.name;
    cout << iter->second.name;
}