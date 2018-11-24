//
// Created by WML on 2018/11/24.
//

#include "MipsGenerate.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string result;

void PrintASM(int reg){
    //result.append("move $a0,$"+reg+"\n");
    result.append("li $v0,4");
    result.append("syscall\n");
}

void PrintASM(string label){
    result.append("la $a0,"+label+"\n");
    result.append("li $v0,4");
    result.append("syscall\n");
}

void WriteMips(){
    cout<<result<<endl;
}