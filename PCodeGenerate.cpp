//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "PCodeGenerate.h"
#include "lib.h"
#include <iostream>


using namespace std;

PCode pcode[4096];
int pcode_num;

void OpExchange(int op);

void PCodeInsert(int num, int x, int y, int op, int z) {
    pcode[num].x = x;
    pcode[num].y = y;
    pcode[num].z = z;
    pcode[num].op = op;
}

void PCodePrint() {
    for (int i = 0; i < pcode_num; i++) {
        cout << "PCode#" << i << ": " << pcode[i].x << " " << pcode[i].y;
        OpExchange(pcode[i].op);
        cout << pcode[i].z << endl;
    }
}

void OpExchange(int op) {
    switch (op) {
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
        default:
            cout << " " << op << " ";
    }
}