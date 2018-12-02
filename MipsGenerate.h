//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

#define X_FIND ((pc.x >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.x - MID_CODE_BASE) * 4): ((pc.x - iter->second.local_code_min) * 4))
#define Y_FIND ((pc.y >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.y - MID_CODE_BASE) * 4): ((pc.y - iter->second.local_code_min) * 4))
#define Z_FIND ((pc.z >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.z - MID_CODE_BASE) * 4): ((pc.z - iter->second.local_code_min) * 4))
#define PARA_REG_FIND ((para_reg <= 4) ? (para_reg+3) : (para_reg+7))

using namespace std;

struct FuncRuntime {
    string name;
    int code;
    int local_code_max;
    int local_code_min;
    int mid_code_max;
};

extern unordered_map<int, FuncRuntime> RuntimeStack;
extern unordered_map<int, int> RuntimeType;

void WriteMipsFile();

void FuncRuntimeCheck();

void StaticDataOutput(ofstream &file);

void TextDataOutput(ofstream &file);


#endif //COMPILER_MIPSGENERATE_H
