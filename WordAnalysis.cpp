#pragma warning(disable:4996)

#include "WordAnalysis.h"
#include "lib.h"
#include "PCodeGenerate.h"
#include <string.h>
#include <unordered_map>

int Plus(char str) {
    if (str == '+') {
        return 1;
    } else if (str == '-') {
        return 1;
    } else {
        return 0;
    }
}

int Multi(char str) {
    if (str == '*') {
        return 1;
    } else if (str == '/') {
        return 1;
    } else {
        return 0;
    }
}

int RelationalOperator(char *str, int *code) {
    if (*str == '<') {
        if (*(str + 1) == '=') {
            *code = BLEZ;
            return 2;
        } else {
            *code = BLTZ;
            return 1;
        }
    } else if (*str == '>') {
        if (*(str + 1) == '=') {
            *code = BGEZ;
            return 2;
        } else {
            *code = BGTZ;
            return 1;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        *code = BNE;
        return 2;
    } else if (*str == '=' && *(str + 1) == '=') {
        *code = BEQ;
        return 2;
    }
    return 0;
}

int Letter(char str) {
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || str == '_') {
        return 1;
    }
    return 0;
}

int NotZeroNum(char str) {
    if (str >= '1' && str <= '9') {
        return 1;
    }
    return 0;
}

int Num(char str) {
    if (str == '0' || NotZeroNum(str)) {
        return 1;
    }
    return 0;
}

int Character(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (*p == '\'') {
        word[i++] = *p;
        p++;
        if (Plus(*p) || Multi(*p) || Num(*p) || Letter(*p)) {
            word[i++] = *p;
            p++;
            if (*p == '\'') {
                word[i++] = *p;
                word[i] = '\0';
                return 3;
            } else {
            }
        }
    }
    return 0;
}

int String(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (*p == '"') {
        word[i++] = *(p + 1);
        p++;
        while (true) {
            if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
                word[i++] = *p;
                p++;
                continue;
            } else {
                if (*p == '"') {
                    word[i] = '\0';
                    p++;
                    SymInsert(word, 2, 0, 0);
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int NoSignNum(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (NotZeroNum(*p)) {
        word[i++] = *p;
        p++;
        while (true) {
            if (Num(*p)) {
                word[i++] = *p;
                p++;
                continue;
            } else {
                word[i] = '\0';
                return (int) ((p - str) / sizeof(char));
            }
        }
    } else if (*p == '0') {
        return 1;
    }
    return 0;
}

int Integer(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    int process_len = 0;
    if (*p == '+' || *p == '-') {
        word[i++] = *p;
        p++;
    }
    if ((process_len = NoSignNum(p))) {
        for (int mid = 0; mid < process_len; mid++) {
            word[i + mid] = *(p + mid);
        }
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int Identifier(char *str) {
    char *p = str;
    char word[63];
    int i = 0;
    if (Letter(*p)) {
        word[i++] = *p;
        p++;
    } else {
        return 0;
    }
    while (true) {
        if (Letter(*p) || Num(*p)) {
            word[i++] = *p;
            p++;
        } else {
            word[i] = '\0';
            if (!strcmp(word, "while") || !strcmp(word, "for") || !strcmp(word, "return") || !strcmp(word, "void") ||
                !strcmp(word, "main") || !strcmp(word, "do") || !strcmp(word, "scanf") || !strcmp(word, "printf")) {
                return 0;
            }
            word[i] = '\0';
            if (str > iden_point) {
                iden_point = str;
            }
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int Identifier(char *str, int code) {
    char *p = str;
    char word[63];
    int i = 0;
    int x = code, y = 0, z = 0, op = PLUS, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if (Letter(*p)) {
        word[i++] = *p;
        p++;
    } else {
        return 0;
    }
    while (true) {
        if (Letter(*p) || Num(*p)) {
            word[i++] = *p;
            p++;
        } else {
            word[i] = '\0';
            if (!strcmp(word, "while") || !strcmp(word, "for") || !strcmp(word, "return") || !strcmp(word, "void") ||
                !strcmp(word, "main") || !strcmp(word, "do") || !strcmp(word, "scanf") || !strcmp(word, "printf")) {
                return 0;
            }
            word[i] = '\0';
            if (str > iden_point) {
                iden_point = str;
            }
            auto iter = SymFind(word);
            z = iter->second.code;
            PCodeInsert(pcode_num++, x, y, op, z);
            return (int) ((p - str) / sizeof(char));
        }
    }
}