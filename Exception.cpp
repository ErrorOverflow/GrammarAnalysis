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

int Exception(char *str) {
    int process_len = JumpExp(str);
    char errormsg[255];
    for (int i = 0; i < process_len; i++) {
        errormsg[i] = *(str + i);
    }
    errormsg[process_len] = '\0';
    cout << endl << "ERROR: illegal character found: " << errormsg << endl;
    cout << "this error occurs in line " << line << endl;
    return process_len;
}

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
    cout << "illegal value pass in line " << line << ": From " << y << " to " << x << endl;
}

void ArrayOverflowExp(int line, int x, int y) {
    cout << "array overflow in line " << line << ": #array:" << x << " loc:" << y << endl;
}

void ValueParaListError(int line, int x, int y) {
    cout << "eror occurs in ValueParaList in line " << line << ": #Func Call:" << x << " Para:" << y << endl;
}

void ValueParaListWarn(int line, int x, int y) {
    cout << "Type is not match in ValueParaList in line " << line << ": #Func Call:" << x << " Para:" << y << endl;
}

void ValueCompareExp(int line, int x, int y) {
    cout << "illegal value type compare in line " << line << ": From " << y << " to " << x << endl;
}