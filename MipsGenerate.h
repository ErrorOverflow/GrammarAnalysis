//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_MIPSGENERATE_H
#define COMPILER_MIPSGENERATE_H

#include "lib.h"
#include "PCodeGenerate.h"
#include <string>

using namespace std;

extern string result;

void WriteMipsFile();

void StaticDataOutput(ofstream &file);

void OpCheck();


#endif //COMPILER_MIPSGENERATE_H
