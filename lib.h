//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LIB_H
#define COMPILER_LIB_H

#include <unordered_map>

using namespace std;

extern char *iden_point;
extern int line;
extern unordered_map<string, int, int> SymTable;

int JumpSpace(char *str);

int SymInsert(string name, int type, int dimension);

#endif //COMPILER_LIB_H
