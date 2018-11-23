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
unordered_map<string, Sym> SymTable;
unordered_map<string, Func> FuncTable;

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

void WordExtract(char *str, char *word, int len) {
    char *p = str;
    try {
        for (int i = 0; i < len; i++) {
            *(word + i) = *(p + i);
        }
        *(word + len) = '\0';
    } catch (exception e) {
        cout << "WordExtract: " << *str << len << endl;
    }
}

int SymInsert(string name, int type, int dimension, int read) {
    Sym sym = {name, type, dimension, read};
    SymTable.insert(pair<string, Sym>(name, sym));
    return 1;
}

