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
        p++;
    }
    return (int) ((p - str) / sizeof(char));
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

int Comma(char *str) {
    if (*str == ',') {
        cout << "COMMA ," << endl;
        return 1;
    }
}

int DoubleQuotationMark(char *str) {
    if (*str == '"') {
        cout << "DQM \"" << endl;
        return 1;
    }
    return 0;
}


int Identifier(char *str) {
    char *p = str;
    char word[63];
    int i = 0;
    if (Letter(*p)) {
        *(word + i) = *p;
        i++;
        p++;
    } else {
        return 0;
    }
    while (true) {
        if (Letter(*p) || Num(*p)) {
            *(word + i) = *p;
            i++;
            p++;
        } else {
            word[i] = '\0';
            cout << "IDEN " << word << endl;
            p += JumpSpace(p);
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int String(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    word[i++] = *p;
    p++;
    while (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
        word[i++] = *p;
        p++;
        continue;
    }
    word[i] = '\0';
    cout << "STRING " << word << endl;
    return (int) ((p - str) / sizeof(char));
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
                cout << "NOSIGNNUM " << word << endl;
                return (int) ((p - str) / sizeof(char));
            }
        }
    } else if (*p == '0') {
        cout << "NOSIGNNUM 0" << endl;
        return 1;
    }
    return 0;
}

int Program(char *str, int len) {
    char *p = str;
    int process_len = 0;
    while (((p - str) / sizeof(char)) <= len) {
        if ((process_len = NoSignNum(p))) {
            p += process_len;
        } else if ((process_len = String(p))) {
            p += process_len;
        }
    }
    return 0;
}


int ReadFromFile() {
    FILE *fp;
    char path[64];
    char str[1000];
    char mid[255];
    int i = 0;
    cout << "请输入代码文件绝对路径: ";
    cin >> path;//C:\Users\WML\CLionProjects\GrammarAnalysis\helloworld.txt
    fp = fopen(path, "r");
    while (fgets(mid, 255, fp)) {
        strcpy(str + i * sizeof(char), mid);
        i += strlen(mid);
    }
    cout << "code total length: " << strlen(str) << endl;
    Program(str, strlen(str));
    return 0;
}

//int main() {

//    return 0;
//}