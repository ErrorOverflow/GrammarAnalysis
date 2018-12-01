#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"
#include "PCodeGenerate.h"
#include "MipsGenerate.h"

using namespace std;


int main() {//C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\helloworld.txt
    pcode_num = 0;//C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\try.txt
    ReadFromFile();
    SymPrint();
    cout << "-------------------------------" << endl;
    PCodePrint();
    cout << "-------------------------------" << endl;
    WriteMipsFile();
    system("pause");
    return 0;
}