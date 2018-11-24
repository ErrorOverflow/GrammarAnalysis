//
// Created by WML on 2018/11/24.
//

#ifndef COMPILER_PCODEGENERATE_H
#define COMPILER_PCODEGENERATE_H

#define PARA 101
#define PUSH 102
#define CALL 103
#define RET 104
#define GOTO 105
#define PLUS 106
#define SUB 107
#define MULTI 108
#define DIV 109

struct PCode {
    int x;
    int y;
    int op;
    int z;
};

extern PCode code[4096];

#endif //COMPILER_PCODEGENERATE_H
