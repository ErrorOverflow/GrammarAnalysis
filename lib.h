//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LIB_H
#define COMPILER_LIB_H

#include <unordered_map>

using namespace std;
struct Sym {
    int code;
    string name;
    int type;//0.int 1.char 2.void
    int dimension;//0.int 1.char 2.string
    int kind;//0.const 1.var 2.func
};
extern char *iden_point;
extern int line;
extern int LocalCode;
extern int MidCode;
extern int TableNum;
extern unordered_map<string, Sym> SymTable[64];

int JumpSpace(char *str);

int SymInsert(string name, int type, int dimension, int read);

int SymInsert(string name, int type);

void SymPrint();

unordered_map<string, Sym>::iterator SymFind(string name);

#endif //COMPILER_LIB_H
