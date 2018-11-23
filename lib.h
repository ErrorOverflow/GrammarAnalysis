//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LIB_H
#define COMPILER_LIB_H

#include <unordered_map>

using namespace std;
struct Sym {
    string name;
    int type;
    int dimension;
    int read;
};
struct Func{
    string name;
    int type;
    int para_num;
    int para_type[16];
};
extern char *iden_point;
extern int line;
extern unordered_map<string, Sym> SymTable;

int JumpSpace(char *str);

void WordExtract(char *str, char *word, int len);

int SymInsert(string name, int type, int dimension,int read);

#endif //COMPILER_LIB_H
