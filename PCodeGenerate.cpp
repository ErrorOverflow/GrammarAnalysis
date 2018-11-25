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

void PCodeInsert(int num, int x, int y, int op, int z) {
    pcode[num].x = x;
    pcode[num].y = y;
    pcode[num].z = z;
    pcode[num].op = op;
}

void PCodePrint() {
    for (int i = 0; i < pcode_num; i++) {
        cout << "PCode#" << i << ": " << pcode[i].x << " " << pcode[i].y << " " << pcode[i].op << " " << pcode[i].z
             << endl;
    }
}