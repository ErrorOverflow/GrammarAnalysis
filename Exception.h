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

void ValuePassExp(int num, int x, int y);

void ArrayOverflowExp(int num, int x, int y);

void ValueParaListError(int num, int x, int y);

void ValueParaListWarn(int num, int x, int y);

void ValueCompareExp(int num, int x, int y);

void NaN(int num);

#endif //COMPILER_EXCEPTION_H
