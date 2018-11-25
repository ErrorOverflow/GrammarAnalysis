//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "LexicalAnalysis.h"
#include "lib.h"
#include "WordAnalysis.h"
#include "Exception.h"
#include "PCodeGenerate.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
#include <fstream>
#include <windows.h>

using namespace std;

char func_name[64];
int func_type;

int ConstDefine(char *str) {
    char *p = str;
    int process_len = 0;
    int isConstDefine = 0;
    char *identifier[64];
    int identifier_len[64];
    int identifier_type = 0;
    int identifier_num = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        identifier_type = 0;
        p += 3;
        if (*p != ' ') {
            return 0;
        }
        p++;
        p += JumpSpace(p);
        while ((process_len = Identifier(p))) {
            identifier[identifier_num] = p;
            identifier_len[identifier_num] = process_len;
            p += process_len;
            p += JumpSpace(p);
            if (*p == '=') {
                p++;
                p += JumpSpace(p);
                if ((process_len = Integer(p))) {
                    p += process_len;
                    p += JumpSpace(p);
                    if (*p == ',') {
                        p++;
                        p += JumpSpace(p);
                        identifier_num++;
                        continue;
                    } else {
                        isConstDefine = 1;
                        break;
                    }
                }
            }
        }
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        identifier_type = 1;
        p += 4;
        if (*p != ' ') {
            return 0;
        }
        p++;
        p += JumpSpace(p);
        while ((process_len = Identifier(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == '=') {
                p++;
                p += JumpSpace(p);
                if ((process_len = Character(p))) {
                    p += process_len;
                    p += JumpSpace(p);
                    if (*p == ',') {
                        p++;
                        p += JumpSpace(p);
                        continue;
                    } else {
                        isConstDefine = 1;
                        break;
                    }
                }
            }
        }
    }
    if (isConstDefine) {
        for (int i = 0; i <= identifier_num; i++) {
            string name;
            for (int j = 0; j < identifier_len[i]; j++) {
                name = name + *(identifier[i] + j);
            }
            SymInsert(name, identifier_type, 0, 0);
        }
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int ConstDeclare(char *str) {
    char *p = str;
    int process_len = 0;
    int isRight = 0;
    while (*p == 'c' && *(p + 1) == 'o' && *(p + 2) == 'n' && *(p + 3) == 's' && *(p + 4) == 't' && *(p + 5) == ' ') {
        p += 6;
        p += JumpSpace(p);
        if ((process_len = ConstDefine(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == ';') {
                p++;
                p += JumpSpace(p);
                isRight = 1;
                continue;
            } else {
                isRight = 0;
                break;
            }
        }
    }
    if (isRight) {
        cout << "<ConstDeclare>";
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int DeclareHead(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        p += 3;
        func_type = 0;
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        p += 4;
        func_type = 1;
    }
    if (*p == ' ') {
        p++;
        p += JumpSpace(p);
        process_len = Identifier(p);
        for (int i = 0; i < process_len; i++) {
            func_name[i] = *(p + i);
        }
        func_name[process_len] = '\0';
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int TypeIdentifier(char *str) {
    if (*str == 'i' && *(str + 1) == 'n' && *(str + 2) == 't' && *(str + 3) == ' ') {
        return 3;
    } else if (*str == 'c' && *(str + 1) == 'h' && *(str + 2) == 'a' && *(str + 3) == 'r' && *(str + 4) == ' ') {
        return 4;
    }
    return 0;
}

int VarDefine(char *str) {
    char *p = str;
    int process_len = 0;
    int isVarDefine = 0;
    char *identifier[64];
    int identifier_len[64];
    int identifier_type;
    int identifier_dim[64];
    int identifier_num = 0;
    if ((process_len = TypeIdentifier(p))) {
        p += process_len;
        (process_len == 4) ? (identifier_type = 1) : (identifier_type = 0);
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            while ((process_len = Identifier(p))) {
                identifier[identifier_num] = p;
                p += process_len;
                p += JumpSpace(p);
                identifier_len[identifier_num] = process_len;
                if (*p == '[') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = NoSignNum(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ']') {
                            p++;
                            isVarDefine = 1;
                            identifier_dim[identifier_num] = 1;
                        }
                    }
                } else {
                    isVarDefine = 1;
                    identifier_dim[identifier_num] = 0;
                }
                p += JumpSpace(p);
                if (isVarDefine) {
                    if (*p == ',') {
                        p++;
                        p += JumpSpace(p);
                        identifier_num++;
                        continue;
                    } else {
                        for (int i = 0; i <= identifier_num; i++) {
                            string name;
                            for (int j = 0; j < identifier_len[i]; j++) {
                                name = name + *(identifier[i] + j);
                            }
                            char *mid = p;
                            mid += JumpSpace(mid);
                            if (*mid == ';') {
                                SymInsert(name, identifier_type, identifier_dim[i], 1);
                            }
                        }
                        return (int) ((p - str) / sizeof(char));
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int VarDeclare(char *str) {
    char *p = str;
    int process_len = 0;
    int isVarDeclare = 0;
    while ((process_len = VarDefine(p))) {
        p += process_len;
        if (*p != ';') {
            p -= process_len;
            break;
        } else {
            isVarDeclare = 1;
            p++;
            p += JumpSpace(p);
        }
    }
    if (isVarDeclare) {
        p += JumpSpace(p);
        cout << "<VarDeclare>";
        return (int) ((p - str) / sizeof(char));
    } else {
        return 0;
    }
}

int ReturnFuncDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = DeclareHead(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = ParameterList(p)) || *p == ')') {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    if (*p == '{') {
                        p++;
                        p += JumpSpace(p);
                        if ((process_len = CompoundSentence(p))) {
                            p += process_len;
                            p += JumpSpace(p);
                            if (*p == '}') {
                                p++;
                                p += JumpSpace(p);
                                SymInsert(func_name, func_type);
                                return (int) ((p - str) / sizeof(char));
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int NoReturnFuncDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if (*str == 'v' && *(p + 1) == 'o' && *(p + 2) == 'i' && *(p + 3) == 'd') {
        p += 4;
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                for (int i = 0; i < process_len; i++) {
                    func_name[i] = *(p + i);
                }
                func_name[process_len] = '\0';
                p += process_len;
                p += JumpSpace(p);
                if (*p == '(') {
                    p++;
                    *p += JumpSpace(p);
                    if ((process_len = ParameterList(p)) || *p == ')') {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            p++;
                            p += JumpSpace(p);
                            if (*p == '{') {
                                p++;
                                p += JumpSpace(p);
                                if ((process_len = CompoundSentence(p))) {
                                    p += process_len;
                                    p += JumpSpace(p);
                                    if (*p == '}') {
                                        p++;
                                        p += JumpSpace(p);
                                        SymInsert(func_name, 2);
                                        return (int) ((p - str) / sizeof(char));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int CompoundSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = ConstDeclare(p))) {
        p += process_len;
        p += JumpSpace(p);
    }
    if ((process_len = VarDeclare(p))) {
        p += process_len;
        p += JumpSpace(p);
    }
    if ((process_len = SentenceColumn(p))) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int ParameterList(char *str) {
    char *p = str;
    int process_len = 0;
    int isRight = 0;
    while ((process_len = TypeIdentifier(p))) {
        p += process_len;
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p != ',') {
                    isRight = 1;
                    p += JumpSpace(p);
                    break;
                } else {
                    p++;
                    p += JumpSpace(p);
                }
            }
        }
    }
    if (isRight)
        return (int) ((p - str) / sizeof(char));
    else
        return 0;
}

int MainFunc(char *str) {
    char *p = str;
    int process_len = 0;
    if (*str == 'v' && *(p + 1) == 'o' && *(p + 2) == 'i' && *(p + 3) == 'd') {
        p += 4;
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if (*p == 'm' && *(p + 1) == 'a' && *(p + 2) == 'i' && *(p + 3) == 'n') {
                p += 4;
                p += JumpSpace(p);
                if (*p == '(') {
                    p++;
                    p += JumpSpace(p);
                    if (*p == ')') {
                        p++;
                        p += JumpSpace(p);
                        if (*p == '{') {
                            p++;
                            p += JumpSpace(p);
                            if ((process_len = CompoundSentence(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                if (*p == '}') {
                                    p++;
                                    p += JumpSpace(p);
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Expression(char *str, int code) {
    char *p = str;
    int process_len = 0;
    int x = 0, y = 0, z = 0, op = 0, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if (*p == '+') {
        p++;
        p += JumpSpace(p);
        op = PLUS;
    } else if (*p == '-') {
        p++;
        p += JumpSpace(p);
        op = SUB;
    }
    x = code;
    z = MidCode;
    while ((process_len = Term(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        if ((process_len = Plus(*p))) {
            if (*p == '+')
                op = PLUS;
            else
                op = SUB;
            p += process_len;
            p += JumpSpace(p);
        } else {
            p += JumpSpace(p);
            cout << "<Expression>";
            return (int) ((p - str) / sizeof(char));
        }
        y = x;
        z = MidCode;
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int Term(char *str, int code) {
    char *p = str;
    int process_len = 0;
    int x = code, y = 0, z = MidCode, op = PLUS, MidCode_buf = MidCode, pcode_buf = pcode_num;
    while ((process_len = Factor(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        if ((process_len = Multi(*p))) {
            if (*p == '*')
                op = MULTI;
            else
                op = DIV;
            p += process_len;
            p += JumpSpace(p);
        } else {
            return (int) ((p - str) / sizeof(char));
        }
        y = x;
        z = MidCode;
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int Factor(char *str, int code) {
    char *p = str;
    int process_len = 0;
    int x = code, y = 0, z = MidCode, op = PLUS, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if ((process_len = ReturnFuncCall(p))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Identifier(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '[') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    PCodeInsert(pcode_num++, x, y, op, z);
                    return (int) ((p - str) / sizeof(char));
                }
            }
        } else {
            PCodeInsert(pcode_num++, x, y, op, z);
            return (int) ((p - str) / sizeof(char));
        }
    } else if ((process_len = Integer(p))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Character(p))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        return (int) ((p - str) / sizeof(char));
    } else if (*p == '(') {
        p++;
        p += JumpSpace(p);
        if ((process_len = Expression(p, MidCode++))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == ')') {
                p++;
                p += JumpSpace(p);
                PCodeInsert(pcode_num++, x, y, op, z);
                return (int) ((p - str) / sizeof(char));
            }
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int Sentence(char *str) {
    char *p = str;
    int process_len = 0;
    int isRight = 0;
    if ((process_len = ConditionSentence(p))) {
        isRight = 2;
    } else if ((process_len = LoopSentence(p))) {
        isRight = 2;
    } else if ((process_len = ReadSentence(p))) {
        isRight = 1;
    } else if ((process_len = WriteSentence(p))) {
        isRight = 1;
    } else if ((process_len = AssignSentence(p))) {
        isRight = 1;
    } else if ((process_len = ReturnFuncCall(p))) {
        isRight = 1;
    } else if ((process_len = NoReturnFuncCall(p))) {
        isRight = 1;
    } else if ((process_len = ReturnSentence(p))) {
        isRight = 1;
    } else if (*p == '{') {
        p++;
        p += JumpSpace(p);
        if ((process_len = SentenceColumn(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == '}') {
                p++;
                process_len = 0;
                isRight = 2;
            }
        }
    } else if (*p == ';') {
        p++;
        p += JumpSpace(p);
        cout << "<EmptySentence>" << endl;
        return (int) ((p - str) / sizeof(char));
    }
    if (isRight == 1) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == ';') {
            p++;
            p += JumpSpace(p);
            return (int) ((p - str) / sizeof(char));
        }
    } else if (isRight == 2) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    if (*p != '}')
        Exception(p);
    return 0;
}

int AssignSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = Identifier(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '=') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                cout << "<AssignSentence>";
                return (int) ((p - str) / sizeof(char));
            }
        } else if (*p == '[') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    if (*p == '=') {
                        p++;
                        p += JumpSpace(p);
                        if ((process_len = Expression(p, MidCode++))) {
                            p += process_len;
                            p += JumpSpace(p);
                            cout << "<AssignSentence>";
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int ConditionSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'f') {
        p += 2;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Condition(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Sentence(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == 'e' && *(p + 1) == 'l' && *(p + 2) == 's' && *(p + 3) == 'e') {
                            p += 4;
                            p += JumpSpace(p);
                            if ((process_len = Sentence(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                cout << "<IF>" << endl;
                                return (int) ((p - str) / sizeof(char));
                            }
                        } else {
                            cout << "<IF>" << endl;
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Condition(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = Expression(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        if ((process_len = RelationalOperator(p))) {
            p += process_len;
            p += JumpSpace(p);
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                return (int) ((p - str) / sizeof(char));
            }
        } else {
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int LoopSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'd' && *(p + 1) == 'o') {
        p += 2;
        p += JumpSpace(p);
        if ((process_len = Sentence(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == 'w' && *(p + 1) == 'h' && *(p + 2) == 'i' && *(p + 3) == 'l' && *(p + 4) == 'e') {
                p += 5;
                p += JumpSpace(p);
                if (*p == '(') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Condition(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            p++;
                            p += JumpSpace(p);
                            cout << "<DoWhile>" << endl;
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                }
            }
        }
    } else if (*p == 'f' && *(p + 1) == 'o' && *(p + 2) == 'r') {
        p += 3;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == '=') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Expression(p, MidCode++))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ';') {
                            p++;
                            p += JumpSpace(p);
                            if ((process_len = Condition(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                if (*p == ';') {
                                    p++;
                                    p += JumpSpace(p);
                                    if ((process_len = Identifier(p))) {
                                        p += process_len;
                                        p += JumpSpace(p);
                                        if (*p == '+' || *p == '-') {
                                            p++;
                                            p += JumpSpace(p);
                                            if ((process_len = Step(p))) {
                                                p += process_len;
                                                p += JumpSpace(p);
                                                if (*p == ')') {
                                                    p++;
                                                    p += JumpSpace(p);
                                                    if ((process_len = Sentence(p))) {
                                                        p += process_len;
                                                        p += JumpSpace(p);
                                                        cout << "<For>" << endl;
                                                        return (int) ((p - str) / sizeof(char));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Step(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = NoSignNum(p))) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int ReturnFuncCall(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = Identifier(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = ValueParameterList(p)) || (*p == ')')) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    cout << "<ReturnFuncCall>";
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    return 0;
}

int NoReturnFuncCall(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = Identifier(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = ValueParameterList(p)) || (*p == ')')) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    cout << "<NoReturnFuncCall>";
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    return 0;
}

int ValueParameterList(char *str) {
    char *p = str;
    int process_len = 0;
    while ((process_len = Expression(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == ',') {
            p++;
            p += JumpSpace(p);
        } else {
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int SentenceColumn(char *str) {
    char *p = str;
    int process_len = 0;
    int isRight = 0;
    while ((process_len = Sentence(p))) {
        p += process_len;
        p += JumpSpace(p);
        isRight = 1;
    }
    if (isRight)
        return (int) ((p - str) / sizeof(char));
    else
        return 0;
}

int ReadSentence(char *str) {
    char *p = str;
    int process_len = 0;
    int isRight = 0;
    if (*p == 's' && *(p + 1) == 'c' && *(p + 2) == 'a' && *(p + 3) == 'n' && *(p + 4) == 'f') {
        p += 5;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            while ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                isRight = 1;
                if (*p == ',') {
                    p++;
                } else {
                    break;
                }
            }
            if (isRight) {
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    cout << "<ReadSentence>";
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int WriteSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'p' && *(p + 1) == 'r' && *(p + 2) == 'i' && *(p + 3) == 'n' && *(p + 4) == 't' && *(p + 5) == 'f') {
        p += 6;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = String(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ',') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Expression(p, MidCode++))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            p++;
                            p += JumpSpace(p);
                            cout << "<WriteSentence>";
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                } else if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    cout << "<WriteSentence>";
                    return (int) ((p - str) / sizeof(char));
                }
            } else if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    cout << "<WriteSentence>";
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    return 0;
}

int ReturnSentence(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'r' && *(p + 1) == 'e' && *(p + 2) == 't' && *(p + 3) == 'u' && *(p + 4) == 'r' && *(p + 5) == 'n') {
        p += 6;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    cout << "<ReturnSen>";
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        } else {
            cout << "<ReturnSen>";
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int Program(char *str) {
    char *p = str;
    int process_len = 0;
    p += JumpSpace(p);
    if ((process_len = ConstDeclare(p))) {
        p += process_len;
        p += JumpSpace(p);
        cout << endl << endl;
    }
    if ((process_len = VarDeclare(p))) {
        p += process_len;
        p += JumpSpace(p);
        cout << endl << endl;
    }
    TableNum++;
    while ((process_len = ReturnFuncDefine(p)) || (process_len = NoReturnFuncDefine(p))) {
        cout << "<FuncDefine>" << endl << endl;
        p += process_len;
        p += JumpSpace(p);
        TableNum++;
    }
    if ((process_len = MainFunc(p))) {
        cout << "<MainFunc>" << endl << endl;
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    Exception(p);
    return 0;
}
