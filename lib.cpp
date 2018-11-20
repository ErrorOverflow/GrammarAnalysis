//
// Created by WML on 2018/11/20.
//

#include "lib.h"

char *iden_point;

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ' || *p == '\n' || *p == '\t') {
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}