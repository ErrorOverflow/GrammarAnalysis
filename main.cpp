//
// Created by WML on 2018/11/8.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

#define STRMAX 255
#define NUMMAX 9

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
            return 4;
        } else {
            cout << "<relational operator>";
            return 3;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 5;
    } else if (*str == '=' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 5;
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

int Character(char str) {
    if (Plus(str) || Multi(str) || Num(str) || Letter(str)) {
        return 1;
    }
    return 0;
}

int String(char *str, int len) {
    int i = 0;
    char *p = str;
    while (i++ < len) {
        if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
            *p++;
            continue;
        } else {
            cout << *p << endl;
            return 0;
        }
    }
    return 1;
}

int NoSignNum(char *str, int len) {
    char *p = str;
    if (NotZeroNum(*p)) {
        *p++;
        int i = 0;
        while (i++ < len - 1) {
            if (Num(*p)) {
                *p++;
                continue;
            } else {
                return 0;
            }
        }
        return 1;
    } else if (*p == '0' && len == 1) {
        return 1;
    }
    return 0;
}

int Integer(char *str, int len) {
    char *p = str;
    int l = len;
    if (*p == '+' || *p == '-') {
        *p++;
        l--;
    }
    if (NoSignNum(p, l)) {
        return 1;
    }
    return 0;
}

int Identifier(char *str, int len) {
    char *p = str;
    int l = len;
    if (Character(*p)) {
        *p++;
        len - 1;
    } else {
        return 0;
    }
    int i = 0;
    while (i++ < l) {
        if (Character(*p) || Num(*p)) {
            *p++;
        } else {
            return 0;
        }
    }
    return 1;
}

int ConstDefine(char *str, int len) {
    char *p = str;
    int l = len;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        *p += 3;
        l -= 3;
        if (*p++ != ' ') {
            l--;
            return 0;
        }
        if(Identifier(p,l)){

            if(Integer(p,l)){

            }
        }
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        *p += 4;
        l -= 4;
    }
}

int main() {
    char buf[STRMAX];
    string str("aasdaqdwdwdABC");
    strncpy(buf, str.c_str(), str.length());
    cout << "233" << endl;
    cout << String(buf, str.length() - 1) << endl;
    return 0;
}