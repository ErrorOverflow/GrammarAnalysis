//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_PCODEGENERATE_H
#define COMPILER_PCODEGENERATE_H

#include <malloc.h>
#include <iostream>

using namespace std;

#define PARA 101
#define PUSH 102
#define CALL 103
#define RET 104
#define GOTO 105
#define PLUS 106
#define SUB 107
#define MULTI 108
#define DIV 109
#define LABEL 110
#define BEQ 111
#define BNE 112
#define BLEZ 113
#define BGTZ 114
#define BLTZ 115
#define BGEZ 116
#define WRITE 117
#define READ 118
#define ADI 119
#define LDA 120

struct PCode {
    int x;
    int y;
    int op;
    int z;
};

extern PCode pcode[4096];
extern int pcode_num;

void PCodeInsert(int num, int x, int y, int op, int z);

void PCodePrint();

void ZExchange(int z);

#endif //COMPILER_PCODEGENERATE_H
