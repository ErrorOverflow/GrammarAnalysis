//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "lib.h"
#include "Exception.h"

char *iden_point;
int line;

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