//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "lib.h"
#include "Exception.h"
#include <unordered_map>
#include <iostream>

using namespace std;

char *iden_point;
int line;
int LocalCode = 1000;
int MidCode = 5000;
int TableNum = 0;
unordered_map<string, Sym> SymTable[64];

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ' || *p == '\n' || *p == '\t') {
        if (*p == '\n' && p >= exp) {
            line++;
            exp = p + 1;
        }
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}

int SymInsert(string name, int type, int dimension, int read) {
    Sym sym = {LocalCode++, name, type, dimension, read};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    return 1;
}

int SymInsert(string name, int type) {
    Sym sym = {LocalCode++, name, type, 0, 2};
    SymTable[0].insert(pair<string, Sym>(name, sym));
    return 1;
}

void SymPrint(){
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            cout << "TABLE#" << i << ": " << iter->second.code << "," << iter->second.name << "," << iter->second.type
                 << ","
                 << iter->second.dimension << "," << iter->second.kind << endl;
            iter++;
        }
    }
}

int SymFind(string name){
    return 0;
}

