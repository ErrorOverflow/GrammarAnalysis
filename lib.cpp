//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "lib.h"
#include "Exception.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

char *iden_point;
int line;
int LabelCode = LABEL_CODE_BASE;
int GlobalCode = GLOBAL_CODE_BASE;
int LocalCode = LOCAL_CODE_BASE;
int MidCode = MID_CODE_BASE;
int TableNum = 0;
int StringNum = 0;
unordered_map<string, Sym> SymTable[64];
unordered_map<int, Sym> CodeIndex[64];

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ' || *p == '\n' || *p == '\t') {
        if (*p == '\n' && p >= excep) {
            line++;
            excep = p + 1;
        }
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}

int SymInsert(string name, int type, int dimension, int kind, string label) {
    Sym sym = {LocalCode++, name, type, dimension, kind, 0, label};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    CodeIndex[TableNum].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}

int SymInsert(string name, int type, int dimension, int kind, int value) {
    Sym sym;
    if (!TableNum)
        sym = {GlobalCode++, name, type, dimension, kind, value, ""};
    else
        sym = {LocalCode++, name, type, dimension, kind, value, ""};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    CodeIndex[TableNum].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}


int SymInsert(string name, int type, int dimension, int kind) {
    Sym sym = {LocalCode++, name, type, dimension, kind, 0, ""};
    SymTable[TableNum].insert(pair<string, Sym>(name, sym));
    CodeIndex[TableNum].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}

int SymInsert(string name, int type) {
    Sym sym = {LocalCode++, name, type, 0, 2, 0, ""};
    SymTable[0].insert(pair<string, Sym>(name, sym));
    CodeIndex[0].insert(pair<int, Sym>(sym.code, sym));
    return 1;
}

void SymPrint() {
    const char MIPSFILE[64] = "SymTable.txt\0";
    ofstream file;
    file.open(MIPSFILE, ios::out);
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            file << "TABLE#" << i << ": " << iter->second.code << "," << iter->second.name << "," << iter->second.type
                 << ","
                 << iter->second.dimension << "," << iter->second.kind << "," << iter->second.value << ","
                 << iter->second.label << endl;
            iter++;
        }
    }
    file.close();
}

unordered_map<string, Sym>::iterator SymFind(string name) {
    auto iter = SymTable[TableNum].find(name);
    if (iter != SymTable[TableNum].end())
        return iter;
    iter = SymTable[0].find(name);
    if (iter != SymTable[0].end())
        return iter;
    cout << name << " is not in SymTable" << endl;
    iter = SymTable[0].find("ErRor");
    return iter;
}

unordered_map<int, Sym>::iterator CodeFind(int code) {
    for (int i = 0; i <= TableNum; i++) {
        auto iter = CodeIndex[i].find(code);
        if (iter != CodeIndex[i].end())
            return iter;
    }
    cout << code << " is not LocalCode or GlobalCode" << endl;
    auto iter = CodeIndex[0].find(SymTable[0].find("ErRor")->second.code);
    return iter;
}

void Num2Char(int num, char *str) {
    int number = num;
    int i = 0;
    while (number != 0) {
        *(str + i) = (char) ('a' + number % 10);
        number = number / 10;
        i++;
    }
    *(str + i) = '\0';
}

