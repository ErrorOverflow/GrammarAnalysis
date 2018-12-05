//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

//#define CODE_FIND ((code >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + code - iter->second.mid_code_min+1) * 4): ((code - iter->second.local_code_min) * 4))
//#define X_FIND ((pc.x >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.x - iter->second.mid_code_min+1) * 4): ((pc.x - iter->second.local_code_min) * 4))
//#define Y_FIND ((pc.y >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.y - iter->second.mid_code_min+1) * 4): ((pc.y - iter->second.local_code_min) * 4))
//#define Z_FIND ((pc.z >= MID_CODE_BASE) ? ((iter->second.local_code_max - iter->second.local_code_min + pc.z - iter->second.mid_code_min+1) * 4): ((pc.z - iter->second.local_code_min) * 4))
#define CODE_FIND (code_info.find(code)->second.address)*4
#define X_FIND (code_info.find(pc.x)->second.address)*4
#define Y_FIND (code_info.find(pc.y)->second.address)*4
#define Z_FIND (code_info.find(pc.z)->second.address)*4
#define PARA_REG_FIND ((para_reg <= 4) ? (para_reg+4) : (para_reg+8))

using namespace std;

struct FuncRuntime {
    string name;
    int code;
    int space;
};

extern unordered_map<int, FuncRuntime> RuntimeStack;
extern unordered_map<int, int> RuntimeType;

void WriteMipsFile();

void StaticDataOutput(ofstream &file);

void TextDataOutput(ofstream &file);

void Mem2Reg(int reg, int code, unordered_map<int, FuncRuntime>::iterator iter, ofstream &file);

void Reg2Mem(int reg, int code, unordered_map<int, FuncRuntime>::iterator iter, ofstream &file);

void AddressPrint();


#endif //COMPILER_MIPSGENERATE_H
