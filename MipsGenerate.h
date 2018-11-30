//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

#define X_FIND ((pc.y >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.y - MID_CODE_BASE) * 4): ((pc.y - LOCAL_CODE_BASE) * 4))
#define Y_FIND ((pc.z >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.z - MID_CODE_BASE) * 4): ((pc.z - LOCAL_CODE_BASE) * 4))

using namespace std;

struct FuncRuntime {
    string name;
    int code;
    int local_code_max;
    int local_code_min;
    int mid_code_max;
};

extern string result;
extern unordered_map<int, FuncRuntime> RuntimeStack;

void WriteMipsFile();

void FuncRuntimeCheck();

void StaticDataOutput(ofstream &file);

void TextDataOutput(ofstream &file);


#endif //COMPILER_MIPSGENERATE_H
