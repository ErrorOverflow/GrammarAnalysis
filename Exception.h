//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_EXCEPTION_H
#define COMPILER_EXCEPTION_H

extern char *excep;

int Exception(char *str);

int JumpExp(char *str);

int ValuePassExp(int line,int x, int y);

int ArrayOverflowExp(int line,int x, int y);

int ValueParaListError(int line,int x, int y);

int ValueParaListWarn(int line,int x, int y);

#endif //COMPILER_EXCEPTION_H
