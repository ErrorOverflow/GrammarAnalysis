//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

using namespace std;

struct FuncRuntime {
    string name;
    int code;
    int local_code_num;
    int mid_code_num;
};

extern string result;
extern unordered_map<int, FuncRuntime> RuntimeStack;

void WriteMipsFile();

void FuncRuntimeCheck();

void StaticDataOutput(ofstream &file);

void TextDataOutput(ofstream &file);


#endif //COMPILER_MIPSGENERATE_H
