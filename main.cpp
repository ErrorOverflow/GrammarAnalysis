//
// Created by WML on 2018/11/8.
//

#include <iostream>

using namespace std;

int plus(char str) {
    if (str == '+' || str == '-') {
        cout << " <plus_sym>";
        return 1;
    } else {
        return 0;
    }
}

int multi(char str){
    if (str == '*' || str == '/') {
        cout << " <plus_sym>";
        return 1;
    } else {
        return 0;
    }
}

int RelationalOperator(char* str){

}

int main() {
    return 0;
}