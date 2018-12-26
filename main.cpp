#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"
#include "PCodeGenerate.h"
#include "MipsGenerate.h"
#include "Exception.h"

using namespace std;


int main() {//C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\helloworld.txt
    ExpInit();//C:\Users\wml\Desktop\1056\test_3\test_3.txt
    pcode_num = 0;//C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\try.txt
    ReadFromFile();//C:\Users\WML\Desktop\16061187_test.txt
    SymPrint();//C:\Users\WML\Desktop\233.txt
    PCodePrint();//C:\Users\WML\Desktop\common1.txt
    WriteMipsFile();
    getchar();
    getchar();
    return 0;
}