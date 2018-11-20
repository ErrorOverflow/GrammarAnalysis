//
// Created by WML on 2018/11/20.
//

#include "FileIO.h"
#include "LexicalAnalysis.h"
#include "lib.h"
#include <iostream>
#include <string.h>

using namespace std;

int ReadFromFile() {
    FILE *fp;
    char str[1000];
    char mid[255];
    char path[64];
    int i = 0;//home/wml/CLionProjects/GrammarAnalysis/helloworld.txt
    cout << "Input file path: ";//C:\Users\WML\CLionProjects\GrammarAnalysis\helloworld.txt
    cin >> path;
    fp = fopen(path, "r");
    while (fgets(mid, 255, fp)) {
        strcpy(str + i * sizeof(char), mid);
        i += strlen(mid);
    }
    iden_point = str;
    line = 1;
    Program(str);
    return 0;
}