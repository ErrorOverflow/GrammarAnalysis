//
// Created by WML on 2018/11/8.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

#define STRMAX 255

char *point = NULL;

using namespace std;

int Plus(char str) {
    if (str == '+') {
        cout << "<plus>";
        return 1;
    } else if (str == '-') {
        cout << "<plus>";
        return 2;
    } else {
        return 0;
    }
}

int Multi(char str) {
    if (str == '*') {
        cout << "<multi>";
        return 1;
    } else if (str == '/') {
        cout << "<multi>";
        return 2;
    } else {
        return 0;
    }
}

int RelationalOperator(char *str) {
    if (*str == '<') {
        if (*(str + 1) == '=') {
            cout << "<relational operator>";
            return 2;
        } else {
            cout << "<relational operator>";
            return 1;
        }
    } else if (*str == '>') {
        if (*(str + 1) == '=') {
            cout << "<relational operator>";
            return 2;
        } else {
            cout << "<relational operator>";
            return 1;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 2;
    } else if (*str == '=' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 2;
    }
    return 0;
}

int Letter(char str) {
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || str == '_') {
        cout << "<letter>";
        return 1;
    }
    return 0;
}

int NotZeroNum(char str) {
    if (str >= '1' && str <= '9') {
        cout << "<not_zero_num>";
        return 1;
    }
    return 0;
}

int Num(char str) {
    if (str == '0' || NotZeroNum(str)) {
        cout << "<num>";
        return 1;
    }
    return 0;
}

int Character(char *str) {
    char *p = str;
    if (*p++ == '\'') {
        if (Plus(*p) || Multi(*p) || Num(*p) || Letter(*p)) {
            *p++;
            if (*p == '\'') {
                return 3;
            }
        }
    }
    return 0;
}

int String(char *str) {
    char *p = str;
    while (1) {
        if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
            *p++;
            continue;
        } else {
            cout << *p << endl;
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int NoSignNum(char *str) {
    char *p = str;
    if (NotZeroNum(*p)) {
        *p++;
        while (1) {
            if (Num(*p)) {
                *p++;
                continue;
            } else {
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
    int process_len=0;
    if (*p == '+' || *p == '-') {
        *p++;
    }
    if ((process_len=NoSignNum(p))) {
        *p+=process_len;
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int Identifier(char *str) {
    char *p = str;
    int process_len;
    if (Letter(*p)) {
        *p++;
    } else {
        return 0;
    }
    int i = 0;
    while (1) {
        if (Letter(*p) || Num(*p)) {
            *p++;
        } else {
            return 0;
        }
    }
}

int readsym(char *str) {
    char *p = str;
    int l = 0;
    while (Plus(*str) || Multi(*str) || Num(*str) || Letter(*str)) {
        *p++;
        l++;
    }
    return l;
}


int ConstDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        *p += 3;
        if (*p++ != ' ') {
            return 0;
        }
        process_len = readsym(p);
        if (Identifier(p, process_len)) {
            *p += process_len;
            if (*p++ == '=') {
                process_len = readsym(p);
                if (Integer(p, process_len)) {
                    *p += process_len;
                    while (*p == ',') {
                        *p++;
                        process_len = readsym(p);
                        if (Identifier(p, process_len)) {
                            *p += process_len;
                            if (*p++ == '=') {
                                process_len = readsym(p);
                                if (Integer(p, process_len)) {
                                    *p += process_len;
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        }
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        *p += 4;
        if (*p++ != ' ') {
            return 0;
        }
        process_len = readsym(p);
        if (Identifier(p, process_len)) {
            *p += process_len;
            if (*p++ == '=') {
                process_len = readsym(p);
                if (Character(p, process_len)) {
                    *p += process_len;
                    while (*p == ',') {
                        *p++;
                        process_len = readsym(p);
                        if (Identifier(p, process_len)) {
                            *p += process_len;
                            if (*p++ == '=') {
                                process_len = readsym(p);
                                if (Integer(p, process_len)) {
                                    *p += process_len;
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    return (int) ((p - str) / \
                    sizeof(char));
                }
            }
        }
    }
    return 0;
}

int ConstDeclare(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'c' && *(p + 1) == 'o' && *(p + 2) == 'n' && *(p + 3) == 's' && *(p + 4) == 't') {
        *p += 5;
        if (*p++ == ' ') {
            process_len = ConstDefine(p);
            *p += process_len;
            if (*p == ';') {
                process_len = ConstDeclare(p);//递归
                if (process_len != 0) {
                    *p += process_len;
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int DeclareHead(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {

    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {

    }
    return 0;
}

int main() {
    char buf[STRMAX];
    string str("ABC");
    strncpy(buf, str.c_str(), str.length());
    point = buf;
    cout << "233" << endl;
    cout << String(buf, str.length() - 1) << endl;
    return 0;
}