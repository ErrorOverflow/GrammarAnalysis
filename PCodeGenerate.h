//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_PCODEGENERATE_H
#define COMPILER_PCODEGENERATE_H

#include <malloc.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#define PARA 101
#define PUSH 102
#define CALL 103
#define RET 104
#define GOTO 105
#define LABEL 110
#define WRITE 117
#define READ 118

#define LDA 120
#define SW 122

#define BEQ 111
#define BNE 112
#define BLEZ 113
#define BGTZ 114
#define BLTZ 115
#define BGEZ 116

#define PLUS 106
#define SUB 107
#define MUL 108
#define DIV 109
#define ADI 119
#define LCH 126

#define END 121
#define NOP 123
#define BEGIN 124
#define OVER 125


struct PCode {
    int x;
    int y;
    int op;
    int z;
    int address;
};

struct RuntimeCodeInfo {
    int code;
    int type;//0.int 1.char
    int isValue;
    int value;
    int address;
};

extern PCode pcode[4096];
extern int pcode_num;
extern unordered_map<int, RuntimeCodeInfo> code_info;

void PCodeInsert(int num, int x, int y, int op, int z);

void PCodePrint();

void ZExchange(int z, ofstream &file);

#endif //COMPILER_PCODEGENERATE_H
