#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"

using namespace std;

int main() {
    ReadFromFile();
    for (int i = 0; i <= TableNum; i++) {
        auto iter = SymTable[i].begin();
        while (iter != SymTable[i].end()) {
            cout << "TABLE#" << i << ": " << iter->second.code << "," << iter->second.name << "," << iter->second.type
                 << ","
                 << iter->second.dimension << "," << iter->second.kind << endl;
            iter++;
        }
    }
    system("pause");
    return 0;
}