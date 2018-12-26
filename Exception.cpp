//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "Exception.h"
#include "lib.h"
#include <iostream>
#include <windows.h>

using namespace std;

char *excep;

void ExpInit() {
    Sym sym = {MidCode++, "error", 0, 0, 0, 0, ""};
    SymTable[0].insert(pair<string, Sym>("error", sym));
    CodeIndex[0].insert(pair<int, Sym>(sym.code, sym));
}

int JumpExp(char *str) {
    char *p = str;
    while (*p != '\n')
        p++;
    return (int) ((p - str) / sizeof(char));
}

void ValuePassExp(int line, int x, int y) {
    cout << "WARNING: illegal value pass in line " << line << ": From " << y << " to " << x << endl;
}

void ArrayOverflowExp(int line, int x, int y) {
    cout << "WARNING: array overflow in line " << line << ": #array:" << x << " loc:" << y << endl;
}

void ValueParaListError(int line, int x, int y) {
    cout << "WARNING: ValueParaList's para miss or overflow in line " << line << ": #Func Call:" << x << " Para:" << y << endl;
}

void ValueParaListWarn(int line, int x, int y) {
    cout << "WARNING: Type is not match in ValueParaList in line " << line << ": #Func Call:" << x << " Para:" << y << endl;
}

void ValueCompareExp(int line, int x, int y) {
    cout << "WARNING: illegal value type compare in line " << line << ": From " << y << " to " << x << endl;
}