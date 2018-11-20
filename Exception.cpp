//
// Created by WML on 2018/11/20.
//

#include "Exception.h"
#include "lib.h"
#include <iostream>

using namespace std;

char *exp;

int Exception(char *str) {
    int process_len = JumpExp(str);
    char errormsg[255];
    for (int i = 0; i < process_len; i++) {
        errormsg[i] = *(str + i);
    }
    errormsg[process_len] = '\0';
    cout << "ERROR: illegal character found: " << errormsg << endl;
    cout << "this error occurs in line " << line <<endl;
    return process_len;
}

int JumpExp(char *str) {
    char *p = str;
    while (*p != '\n')
        p++;
    return (int) ((p - str) / sizeof(char));
}