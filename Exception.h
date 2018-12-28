//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_EXCEPTION_H
#define COMPILER_EXCEPTION_H

extern char *excep;

extern int error_num;
extern int warn_num;

void ExpInit();

int JumpExp(char *str);

int Exception(char *str);

void ConstructionLoss(char colon);

void RepeatDefine(char *name);

void IllegalArraySpace(int space);

void ValuePassExp(int line, int x, int y);

void ArrayOverflowExp(int line, int x, int y);

void ValueParaListError(int line, int x, int y);

void ValueParaListWarn(int line, int x, int y);

void ValueCompareExp(int line, int x, int y);

#endif //COMPILER_EXCEPTION_H
