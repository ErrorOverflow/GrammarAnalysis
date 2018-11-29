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
int LabelCode = LABEL_CODE_BASE;
int LocalCode = LOCAL_CODE_BASE;
int MidCode = MID_CODE_BASE;
int TableNum = 0;
unordered_map<string, Sym> SymTable[64];
unordered_map<int, Sym> CodeIndex[64];

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

int SymInsert(string name, int type, int dimension, int read, int value) {
    Sym sym = {LocalCode++, name, type, dimension, read, value};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    CodeIndex[TableNum].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}


int SymInsert(string name, int type, int dimension, int read) {
    Sym sym = {LocalCode++, name, type, dimension, read, 0};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    CodeIndex[TableNum].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}

int SymInsert(string name, int type) {
    Sym sym = {LocalCode++, name, type, 0, 2, 0};
    SymTable[0].insert(pair<string, Sym>(name, sym));
    CodeIndex[0].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}

void SymPrint() {
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            cout << "TABLE#" << i << ": " << iter->second.code << "," << iter->second.name << "," << iter->second.type
                 << ","
                 << iter->second.dimension << "," << iter->second.kind << "," << iter->second.value << endl;
            iter++;
        }
    }
}

void SpaceDel(char *des, char *src) {
    for (int i = 0, j = 0; *(src + i) != '\0'; i++) {
        if (*(src + i) == ' ') {
            continue;
        } else {
            *(des + j) = *(src + i);
            j++;
        }
    }
}

unordered_map<string, Sym>::iterator SymFind(string name) {//unordered_map<string,Sym>::iterator
    auto iter = SymTable[TableNum].find(name);
    if (iter != SymTable[TableNum].end()) {
        return iter;
    }
    iter = SymTable[0].find(name);
    if (iter != SymTable[0].end()) {
        return iter;
    }
    cout << name << " is not in SymTable" << endl;
    exit(-1);
}

unordered_map<int, Sym>::iterator CodeFind(int code) {//unordered_map<string,Sym>::iterator
    for (int i = 0; i <= TableNum; i++) {
        auto iter = CodeIndex[i].find(code);
        if (iter != CodeIndex[i].end()) {
            return iter;
        }
    }
    cout << code << " is not LocalCode" << endl;
    exit(-2);
}

