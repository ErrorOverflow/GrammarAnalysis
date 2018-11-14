//
// Created by WML on 2018/11/13.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
#include <fstream>

using namespace std;

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ' || *p == '\n' || *p == '\t') {
        if (*p == '\t') {
            cout << endl;
        }
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}

int Plus(char str) {
    if (str == '+') {
        //cout << "<plus>";
        cout << "<PLUS +>";
        return 1;
    } else if (str == '-') {
        //cout << "<plus>";
        cout << "<PLUS ->";
        return 1;
    } else {
        return 0;
    }
}

int Multi(char str) {
    if (str == '*') {
        cout << "<MULTI *>";
        return 1;
    } else if (str == '/') {
        cout << "<MULTI />";
        return 1;
    } else {
        return 0;
    }
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
            p += JumpSpace(p);
            word[i] = '\0';
            cout << "<IDEN " << word << ">";
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int String(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (*p == '"') {
        word[i++] = *p;
        p++;
        while (true) {
            if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
                word[i++] = *p;
                p++;
                continue;
            } else {
                if (*p == '"') {
                    word[i++] = *p;
                    p++;
                    word[i] = '\0';
                    cout << "<STRING " << word << ">";
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int RelationalOperator(char *str) {
    if (*str == '<') {
        if (*(str + 1) == '=') {
            cout << "<REALAOP <=>";
            return 2;
        } else {
            cout << "<REALAOP <>";
            return 1;
        }
    } else if (*str == '>') {
        if (*(str + 1) == '=') {
            cout << "<REALAOP >=>";
            return 2;
        } else {
            cout << "<REALAOP >>";
            return 1;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        cout << "<REALAOP !=>";
        return 2;
    } else if (*str == '=' && *(str + 1) == '=') {
        cout << "<REALAOP ==>";
        return 2;
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
                cout << "<NUM " << word << ">";
                return (int) ((p - str) / sizeof(char));
            }
        }
    } else if (*p == '0') {
        cout << "<NUM 0>";
        return 1;
    }
    return 0;
}

int Program(char *str, int len) {
    char *p = str;
    int process_len = 0;
    while (((p - str) / sizeof(char)) <= len) {
        if (*p == '(') {
            p++;
            cout << "<LBRACK (>";
        } else if (*p == ')') {
            p++;
            cout << "<RBRACK )>";
        } else if (*p == '{') {
            p++;
            cout << "<LBRACE {>";
        } else if (*p == '}') {
            p++;
            cout << "<RBRACE }>";
        } else if (*p == ',') {
            p++;
            cout << "<COMMA ,>";
        } else if (*p == ';') {
            p++;
            cout << "<SEMICOLON ;>";
        } else if (*p == '[') {
            p++;
            cout << "<LQBRACK [>";
        } else if (*p == ']') {
            p++;
            cout << "<RQBRACK [>";
        } else if (*p == '=') {
            p++;
            cout << "<EQUAL =>";
        } else if ((process_len = Plus(*p))) {
            p += process_len;
        } else if ((process_len = Multi(*p))) {
            p += process_len;
        } else if ((process_len = RelationalOperator(p))) {
            p += process_len;
        } else if ((process_len = NoSignNum(p))) {
            p += process_len;
        } else if ((process_len = String(p))) {
            p += process_len;
        } else if ((process_len = Identifier(p))) {
            p += process_len;
        } else {
            cout << "ERROR:" << *p << " ";
            p++;
        }
        p += JumpSpace(p);
    }
    return 0;
}


int ReadFromFile() {
    FILE *fp;
    char str[1000];
    char mid[255];
    int i = 0;//home/wml/CLionProjects/GrammarAnalysis/helloworld.txt
    cout << "Input file path: ";
    fp = fopen("C:\\Users\\WML\\CLionProjects\\GrammarAnalysis\\helloworld.txt", "r");
    while (fgets(mid, 255, fp)) {
        strcpy(str + i * sizeof(char), mid);
        i += strlen(mid);
    }
    //cout << "code total length: " << strlen(str);
    Program(str, strlen(str));
    return 0;
}

int main() {
    ReadFromFile();
    return 0;
}