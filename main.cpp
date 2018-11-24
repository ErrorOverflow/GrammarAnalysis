#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"

using namespace std;

int main() {
    ReadFromFile();
    auto iter = SymTable.begin();
    while (iter != SymTable.end()) {
        cout << iter->second.code << "," << iter->second.name << "," << iter->second.type << ","
             << iter->second.dimension << "," << iter->second.kind << endl;
        iter++;
    }
    system("pause");
    return 0;
}