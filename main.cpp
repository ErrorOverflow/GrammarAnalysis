//
// Created by WML on 2018/11/8.
//

#include <iostream>

#define STRMAX 255

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
        cout<< "<letter>";
        return 1;
    }
    return 0;
}

int NotZeroNum(char str){
    if(str>='1' && str<='9'){
        cout<< "<not_zero_num>";
        return 1;
    }
    return 0;
}

int Num(char str){
    if(str=='0' || NotZeroNum(str)){
        cout << "<num>";
        return 1;
    }
    return 0;
}

int Character(char str){
    if(Plus(str) || Multi(str) || Num(str) || Letter(str)){
        return 1;
    }
    return 0;
}

int String(char *str){
    int i=0;
    char *p = str;
    while(*p != '\0' || i++>STRMAX){
        if(*p==32 || *p==33 || (*p>=35 && *p<=126)){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

int main() {
    return 0;
}