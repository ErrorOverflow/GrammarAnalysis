//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_EXCEPTION_H
#define COMPILER_EXCEPTION_H

extern char *excep;

void ExpInit();

int JumpExp(char *str);

void ValuePassExp(int line, int x, int y);

void ArrayOverflowExp(int line, int x, int y);

void ValueParaListError(int line, int x, int y);

void ValueParaListWarn(int line, int x, int y);

void ValueCompareExp(int line, int x, int y);

#endif //COMPILER_EXCEPTION_H
