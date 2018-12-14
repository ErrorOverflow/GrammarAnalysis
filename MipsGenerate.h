//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

#define CODE_FIND (code_info.find(code)->second.address+sp_extra_space)*4
#define PARA_REG_FIND ((para_reg <= 4) ? (para_reg+4) : (para_reg+8))

using namespace std;

struct FuncRuntime {
    string name;
    int code;
    int space;
};

extern unordered_map<int, FuncRuntime> RuntimeStack;

void WriteMipsFile();

void StaticDataOutput(ofstream &file);

void TextDataOutput(ofstream &file);

void Mem2Reg(int reg, int code, ofstream &file);

void Reg2Mem(int reg, int code, ofstream &file);

#endif //COMPILER_MIPSGENERATE_H
