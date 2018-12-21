//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "PCodeGenerate.h"
#include "lib.h"
#include "MipsGenerate.h"
#include "Exception.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <malloc.h>

using namespace std;

PCode pcode[4096];
unordered_map<int, RuntimeCodeInfo> code_info;
int pcode_num;

void OpExchange(int op, ofstream &file);

void PCodeOptimize();

void PCodePreProcess();

void AddressAssign(int code, int *space, int *mid_code_stack);

void PCodeInsert(int num, int x, int y, int op, int z) {
    pcode[num].x = x;
    pcode[num].y = y;
    pcode[num].z = z;
    pcode[num].op = op;
}

void PCodePrint() {
    PCodeOptimize();
    PCodePreProcess();
    const char MIPSFILE[64] = "PCode.txt\0";
    ofstream file;
    file.open(MIPSFILE, ios::out);
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP)
            continue;
        file << "PCode#" << i << ": ";
        if (pcode[i].x < MID_CODE_BASE && pcode[i].x >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].x, file);
        else {
            file << pcode[i].x;
        }
        file << " ";
        if (pcode[i].y < MID_CODE_BASE && pcode[i].y >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].y, file);
        else {
            file << pcode[i].y;
        }
        OpExchange(pcode[i].op, file);
        if (pcode[i].z < MID_CODE_BASE && pcode[i].z >= GLOBAL_CODE_BASE) {
            ZExchange(pcode[i].z, file);
        } else {
            file << pcode[i].z;
        }
        file << "\n";
    }
    file.close();
}

void PCodeOptimize() {
    int mid = 0;
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
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].z;
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
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].x;
                }
                if (pcode[j].x == pcode[i].x || pcode[j].op == LABEL) {
                    break;
                }
            }
        } else if (pcode[i].op == ADI && pcode[i].y == 0 && pcode[i].x >= MID_CODE_BASE) {
            pcode[i].op = NOP;
            CodeFind(pcode[i].x)->second.value = pcode[i].z;
            code_info.find(pcode[i].x)->second.isValue = 1;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].z;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].z;
                }
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].z;
                }
                if (pcode[j].x == pcode[i].x) {
                    break;
                }
            }
        } else if (pcode[i].x >= MID_CODE_BASE && code_info.find(pcode[i].y)->second.isValue &&
                   code_info.find(pcode[i].z)->second.isValue) {
            if (pcode[i].op == PLUS)
                mid = CodeFind(pcode[i].y)->second.value + CodeFind(pcode[i].z)->second.value;
            else if (pcode[i].op == SUB)
                mid = CodeFind(pcode[i].y)->second.value - CodeFind(pcode[i].z)->second.value;
            else if (pcode[i].op == MUL)
                mid = CodeFind(pcode[i].y)->second.value * CodeFind(pcode[i].z)->second.value;
            else if (pcode[i].op == DIV)
                mid = CodeFind(pcode[i].y)->second.value / CodeFind(pcode[i].z)->second.value;
            else if (pcode[i].op == ADI)
                mid = CodeFind(pcode[i].y)->second.value / CodeFind(pcode[i].z)->second.value;
            else
                continue;
            code_info.find(pcode[i].x)->second.isValue = 1;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].z;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].z;
                }
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].z;
                }
                if (pcode[j].x == pcode[i].x) {
                    break;
                }
            }
        }
    }
}

void AddressAssign(int code, int *space, int *mid_code_stack) {
    RuntimeCodeInfo info;
    if (code_info.find(code) != code_info.end())
        return;
    if (code >= GLOBAL_CODE_BASE && code < LOCAL_CODE_BASE) {
        if (CodeFind(code)->second.type == 1)
            info = {code, 1, 0, 0};
        else
            info = {code, 0, 0, 0};
        code_info.insert(pair<int, RuntimeCodeInfo>{code, info});
        if (CodeFind(code)->second.kind == 0)
            code_info.find(code)->second.isValue = 1;
    } else if (code >= LOCAL_CODE_BASE && code < MID_CODE_BASE) {
        *space += 1;
        if (CodeFind(code)->second.type == 1)
            info = {code, 1, 0, *mid_code_stack};
        else
            info = {code, 0, 0, *mid_code_stack};
        *mid_code_stack += 1;
        code_info.insert(pair<int, RuntimeCodeInfo>{code, info});
        if (CodeFind(code)->second.kind == 0)
            code_info.find(code)->second.isValue = 1;
    } else if (code >= MID_CODE_BASE) {
        *space += 1;
        info = {code, 0, 0, *mid_code_stack};
        *mid_code_stack += 1;
        code_info.insert(pair<int, RuntimeCodeInfo>{code, info});
    }
}

void PCodePreProcess() {
    int mid_code_stack = 0;
    int space = 0;
    int func_code = 0;
    unordered_map<int, FuncRuntime>::iterator it;
    unordered_map<int, Sym>::iterator it_code;
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP) {
            continue;
        }
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE && pcode[i].z < MID_CODE_BASE) {
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
        AddressAssign(pcode[i].x, &space, &mid_code_stack);
        AddressAssign(pcode[i].y, &space, &mid_code_stack);
        AddressAssign(pcode[i].z, &space, &mid_code_stack);
        if (pcode[i].op == LDA && CodeFind(pcode[i].y)->second.type == 1 && pcode[i].x >= MID_CODE_BASE)
            code_info.find(pcode[i].x)->second.type = 1;
        else if (pcode[i].op == PLUS && pcode[i].x >= MID_CODE_BASE && pcode[i].y == 0 &&
                 ((pcode[i].z >= MID_CODE_BASE && code_info.find(pcode[i].z)->second.type == 1) ||
                  (pcode[i].z < MID_CODE_BASE && pcode[i].z >= GLOBAL_CODE_BASE &&
                   CodeFind(pcode[i].z)->second.type == 1)))
            code_info.find(pcode[i].x)->second.type = 1;
        if (pcode[i].op == LDA && code_info.find(pcode[i].z)->second.isValue &&
            CodeFind(pcode[i].z)->second.value >= CodeFind(pcode[i].y)->second.dimension)
            ArrayOverflowExp(pcode[i].y, pcode[i].z);
        else if (pcode[i].op == PLUS && pcode[i].y == 0 &&
                 code_info.find(pcode[i].x)->second.type != code_info.find(pcode[i].z)->second.type)
            ValuePassExp(pcode[i].x, pcode[i].z);
    }
    it_code = CodeFind(func_code);
    FuncRuntime funcRuntime = {it_code->second.name, func_code, space};
    RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
}

void OpExchange(int op, ofstream &file) {
    switch (op) {
        case PARA:
            file << " PARA ";
            break;
        case PUSH:
            file << " PUSH ";
            break;
        case CALL:
            file << " CALL ";
            break;
        case RET:
            file << " RET ";
            break;
        case GOTO:
            file << " GOTO ";
            break;
        case PLUS:
            file << " PLUS ";
            break;
        case SUB:
            file << " SUB ";
            break;
        case MUL:
            file << " MULTI ";
            break;
        case DIV:
            file << " DIV ";
            break;
        case LABEL:
            file << " --- LABEL --- ";
            break;
        case BEQ:
            file << " BEQ ";
            break;
        case BNE:
            file << " BNE ";
            break;
        case BLEZ:
            file << " BLEZ ";
            break;
        case BGTZ:
            file << " BGTZ ";
            break;
        case BLTZ:
            file << " BLTZ ";
            break;
        case BGEZ:
            file << " BGEZ ";
            break;
        case WRITE:
            file << " WRITE ";
            break;
        case READ:
            file << " READ ";
            break;
        case ADI:
            file << " ADI ";
            break;
        case LDA:
            file << " LDA ";
            break;
        case END:
            file << " END ";
            break;
        case SW:
            file << " SW ";
            break;
        case BEGIN:
            file << " BEGIN ";
            break;
        case OVER:
            file << " OVER ";
            break;
        default:
            file << " " << op << " ";
    }
}


void ZExchange(int z, ofstream &file) {
    auto iter = CodeFind(z);
    file << iter->second.name;
}