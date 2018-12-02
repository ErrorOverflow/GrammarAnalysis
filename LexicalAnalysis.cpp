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
    int process_len = 0, value = 0;
    int isConstDefine = 0;
    char *identifier[64], word[16];
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
                    for (int i = 0; i < process_len; i++) {
                        word[i] = *(p + i);
                    }
                    word[process_len] = '\0';
                    sscanf(word, "%d", &value);
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
                    value = *(p + 1);
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
            char name[64];
            for (int j = 0; j < identifier_len[i]; j++) {
                name[j] = *(identifier[i] + j);
            }
            name[identifier_len[i]] = '\0';
            cout << name << endl;
            SymInsert(name, identifier_type, 0, 0, value);
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
    char *identifier[64], word[64];
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
                        for (int i = 0; i < process_len; i++) {
                            word[i] = *(p + i);
                        }
                        word[process_len] = '\0';
                        sscanf(word, "%d", &identifier_dim[identifier_num]);
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ']') {
                            p++;
                            isVarDefine = 1;
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
                            char name[64];
                            for (int j = 0; j < identifier_len[i]; j++) {
                                name[j] = *(identifier[i] + j);
                            }
                            name[identifier_len[i]] = '\0';
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
    int MidCode_buf = MidCode, pcode_buf = pcode_num;
    if ((process_len = DeclareHead(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            SymInsert(func_name, func_type);
            PCodeInsert(pcode_num++, 0, 0, LABEL, LocalCode - 1);
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
                                PCodeInsert(pcode_num++, 0, 0, END, 0);
                                return (int) ((p - str) / sizeof(char));
                            }
                        }
                    }
                }
            }
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int NoReturnFuncDefine(char *str) {
    char *p = str;
    int process_len = 0;
    int MidCode_buf = MidCode, pcode_buf = pcode_num;
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
                    SymInsert(func_name, 2);
                    PCodeInsert(pcode_num++, 0, 0, LABEL, LocalCode - 1);
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
                                        PCodeInsert(pcode_num++, 0, 0, END, 0);
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
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
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
    int MidCode_buf = MidCode, pcode_buf = pcode_num;
    char sym[64];
    int sym_type;
    while ((process_len = TypeIdentifier(p))) {
        p += process_len;
        (process_len == 4) ? (sym_type = 1) : (sym_type = 0);
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                for (int i = 0; i < process_len; i++) {
                    sym[i] = *(p + i);
                }
                sym[process_len] = '\0';
                SymInsert(sym, sym_type, 0, 1);
                PCodeInsert(pcode_num++, 0, 0, PARA, LocalCode - 1);
                p += process_len;
                p += JumpSpace(p);
                if (*p != ',') {
                    isRight = 1;
                    p += JumpSpace(p);
                    break;
                } else {
                    isRight = 0;
                    p++;
                    p += JumpSpace(p);
                }
            }
        }
    }
    if (isRight) {
        return (int) ((p - str) / sizeof(char));
    } else {
        MidCode = MidCode_buf;
        pcode_num = pcode_buf;
        return 0;
    }
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
                            SymInsert("main", 2);
                            PCodeInsert(pcode_num++, 0, 0, LABEL, LocalCode - 1);
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
    int x = 0, y = 0, z = 0, op = PLUS, MidCode_buf = MidCode, pcode_buf = pcode_num;
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
            MidCode = MidCode_buf;
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
            MidCode = MidCode_buf;
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
    char *p = str, word[64];
    int process_len = 0, array_code = 0, offset = 0;
    int x = code, y = 0, z = MidCode, op = PLUS, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if ((process_len = ReturnFuncCall(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, x, y, op, z);
        MidCode = MidCode_buf;
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Identifier(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
        auto iter = SymFind(word);
        array_code = iter->second.code;
        p += process_len;
        p += JumpSpace(p);
        if (*p == '[') {
            p++;
            p += JumpSpace(p);
            offset = MidCode;
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    z = MidCode;
                    op = LDA;
                    PCodeInsert(pcode_num++, MidCode++, array_code, op, offset);
                    op = PLUS;
                    PCodeInsert(pcode_num++, x, 0, op, z);
                    MidCode = MidCode_buf;
                    return (int) ((p - str) / sizeof(char));
                }
            }
        } else {
            PCodeInsert(pcode_num++, x, 0, op, array_code);
            MidCode = MidCode_buf;
            return (int) ((p - str) / sizeof(char));
        }
    } else if ((process_len = Integer(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
        sscanf(word, "%d", &z);
        p += process_len;
        p += JumpSpace(p);
        op = ADI;
        PCodeInsert(pcode_num++, code, 0, op, z);
        MidCode = MidCode_buf;
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Character(p))) {
        z = *(p + 1);
        p += process_len;
        p += JumpSpace(p);
        op = ADI;
        PCodeInsert(pcode_num++, x, y, op, z);
        MidCode = MidCode_buf;
        return (int) ((p - str) / sizeof(char));
    } else if (*p == '(') {
        p++;
        p += JumpSpace(p);
        z = MidCode;
        if ((process_len = Expression(p, MidCode++))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == ')') {
                p++;
                p += JumpSpace(p);
                PCodeInsert(pcode_num++, code, 0, op, z);
                MidCode = MidCode_buf;
                return (int) ((p - str) / sizeof(char));
            }
        }
    }
    MidCode = MidCode_buf;
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
    char *p = str, word[64];
    int process_len = 0, x = 0, z = 0, MidCode_buf = MidCode, pcode_buf = pcode_num, array_code = 0, offset = 0;
    if ((process_len = Identifier(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
        auto iter = SymFind(word);
        array_code = iter->second.code;
        p += process_len;
        p += JumpSpace(p);
        if (*p == '=') {
            p++;
            p += JumpSpace(p);
            z = MidCode;
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                PCodeInsert(pcode_num++, array_code, 0, PLUS, z);
                cout << "<AssignSentence>";
                return (int) ((p - str) / sizeof(char));
            }
        } else if (*p == '[') {
            p++;
            p += JumpSpace(p);
            offset = MidCode;
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    x = MidCode++;
                    if (*p == '=') {
                        p++;
                        p += JumpSpace(p);
                        z = MidCode;
                        if ((process_len = Expression(p, MidCode++))) {
                            p += process_len;
                            p += JumpSpace(p);
                            cout << "<AssignSentence>";
                            PCodeInsert(pcode_num++, x, 0, PLUS, z);
                            PCodeInsert(pcode_num++, x, array_code, SW, offset);
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                }
            }
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int ConditionSentence(char *str) {
    char *p = str;
    int process_len = 0;
    int LabelCode_buf = LabelCode, MidCode_buf = MidCode, pcode_buf = pcode_num, label = LabelCode++, label_else = LabelCode++, label_end = LabelCode++;
    if (*p == 'i' && *(p + 1) == 'f') {
        p += 2;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Condition(p, label, BNE))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    p++;
                    p += JumpSpace(p);
                    PCodeInsert(pcode_num++, 0, 0, GOTO, label_else);
                    PCodeInsert(pcode_num++, 0, 0, LABEL, label);
                    if ((process_len = Sentence(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == 'e' && *(p + 1) == 'l' && *(p + 2) == 's' && *(p + 3) == 'e') {
                            p += 4;
                            p += JumpSpace(p);
                            PCodeInsert(pcode_num++, 0, 0, GOTO, label_end);
                            PCodeInsert(pcode_num++, 0, 0, LABEL, label_else);
                            if ((process_len = Sentence(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                PCodeInsert(pcode_num++, 0, 0, LABEL, label_end);
                                cout << "<IF>" << endl;
                                return (int) ((p - str) / sizeof(char));
                            }
                        } else {
                            PCodeInsert(pcode_num++, 0, 0, LABEL, label_else);
                            cout << "<IF>" << endl;
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                }
            }
        }
    }
    LabelCode = LabelCode_buf;
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int Condition(char *str, int code, int jump_op) {
    char *p = str;
    int process_len = 0;
    int x = code, y = 0, z = 0, op = 0, MidCode_buf = MidCode, pcode_buf = pcode_num;
    y = MidCode;
    if ((process_len = Expression(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        if ((process_len = RelationalOperator(p, &op))) {
            p += process_len;
            p += JumpSpace(p);
            z = MidCode;
            if ((process_len = Expression(p, MidCode++))) {
                p += process_len;
                p += JumpSpace(p);
                PCodeInsert(pcode_num++, code, y, op, z);
                return (int) ((p - str) / sizeof(char));
            }
        } else {
            op = jump_op;
            PCodeInsert(pcode_num++, x, y, op, z);
            return (int) ((p - str) / sizeof(char));
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int LoopSentence(char *str) {
    char *p = str;
    int process_len = 0;
    int LabelCode_buf = LabelCode, MidCode_buf = MidCode, pcode_buf = pcode_num, label = LabelCode++, label_for = LabelCode++, label_end = LabelCode++;
    if (*p == 'd' && *(p + 1) == 'o') {
        p += 2;
        p += JumpSpace(p);
        PCodeInsert(pcode_num++, 0, 0, LABEL, label);
        if ((process_len = Sentence(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == 'w' && *(p + 1) == 'h' && *(p + 2) == 'i' && *(p + 3) == 'l' && *(p + 4) == 'e') {
                p += 5;
                p += JumpSpace(p);
                if (*p == '(') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Condition(p, label, BEQ))) {
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
        int x = 0, y = 0, op = 0, z = 0;
        char ini[64], par[64], step[64];
        p += 3;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                for (int i = 0; i < process_len; i++) {
                    ini[i] = *(p + i);
                }
                ini[process_len] = '\0';
                auto iter = SymFind(ini);
                x = iter->second.code;
                p += process_len;
                p += JumpSpace(p);
                if (*p == '=') {
                    p++;
                    p += JumpSpace(p);
                    z = MidCode;
                    if ((process_len = Expression(p, MidCode++))) {
                        p += process_len;
                        p += JumpSpace(p);
                        y = 0;
                        op = PLUS;
                        PCodeInsert(pcode_num++, x, y, op, z);
                        PCodeInsert(pcode_num++, 0, 0, LABEL, label);
                        if (*p == ';') {
                            p++;
                            p += JumpSpace(p);
                            if ((process_len = Condition(p, label_for, BEQ))) {
                                p += process_len;
                                p += JumpSpace(p);
                                if (*p == ';') {
                                    p++;
                                    p += JumpSpace(p);
                                    if ((process_len = Identifier(p))) {
                                        for (int i = 0; i < process_len; i++) {
                                            par[i] = *(p + i);
                                        }
                                        par[process_len] = '\0';
                                        iter = SymFind(ini);
                                        x = iter->second.code;
                                        p += process_len;
                                        p += JumpSpace(p);
                                        if (*p == '+' || *p == '-') {
                                            p++;
                                            p += JumpSpace(p);
                                            if ((process_len = Step(p))) {
                                                for (int i = 0; i < process_len; i++) {
                                                    step[i] = *(p + i);
                                                }
                                                step[process_len] = '\0';
                                                sscanf(step, "%d", &z);
                                                p += process_len;
                                                p += JumpSpace(p);
                                                if (*p == ')') {
                                                    p++;
                                                    p += JumpSpace(p);
                                                    PCodeInsert(pcode_num++, 0, 0, GOTO, label_end);
                                                    PCodeInsert(pcode_num++, 0, 0, LABEL, label_for);
                                                    if ((process_len = Sentence(p))) {
                                                        p += process_len;
                                                        p += JumpSpace(p);
                                                        op = ADI;
                                                        PCodeInsert(pcode_num++, x, x, op, z);
                                                        PCodeInsert(pcode_num++, 0, 0, GOTO, label);
                                                        LabelCode++;
                                                        PCodeInsert(pcode_num++, 0, 0, LABEL, label_end);
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
    LabelCode = LabelCode_buf;
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
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

int ReturnFuncCall(char *str, int code) {
    char *p = str, word[64];
    int process_len = 0;
    int z = 0, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if ((process_len = Identifier(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
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
                    auto iter = SymFind(word);
                    z = iter->second.code;
                    PCodeInsert(pcode_num++, code, 0, CALL, z);
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int ReturnFuncCall(char *str) {
    char *p = str, word[64];
    int process_len = 0;
    if ((process_len = Identifier(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
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
                    auto iter = SymFind(word);
                    PCodeInsert(pcode_num++, MidCode++, 0, CALL, iter->second.code);
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    return 0;
}

int NoReturnFuncCall(char *str) {
    char *p = str, word[64];
    int process_len = 0;
    if ((process_len = Identifier(p))) {
        for (int i = 0; i < process_len; i++) {
            word[i] = *(p + i);
        }
        word[process_len] = '\0';
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
                    auto iter = SymFind(word);
                    PCodeInsert(pcode_num++, MidCode++, 0, CALL, iter->second.code);
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
    int x = 0, y = 0, z = MidCode, op = PUSH, MidCode_buf = MidCode, pcode_buf = pcode_num;
    while ((process_len = Expression(p, MidCode++))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == ',') {
            p++;
            p += JumpSpace(p);
        } else {
            PCodeInsert(pcode_num++, x, y, op, z);
            return (int) ((p - str) / sizeof(char));
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
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
    char *p = str, word[64];
    int process_len = 0;
    int isRight = 0;
    int z = 0, op = READ, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if (*p == 's' && *(p + 1) == 'c' && *(p + 2) == 'a' && *(p + 3) == 'n' && *(p + 4) == 'f') {
        p += 5;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            while ((process_len = Identifier(p))) {
                for (int i = 0; i < process_len; i++) {
                    word[i] = *(p + i);
                }
                word[process_len] = '\0';
                auto iter = SymFind(word);
                z = iter->second.code;
                PCodeInsert(pcode_num++, 0, 0, READ, z);
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
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int WriteSentence(char *str) {
    char *p = str, word[54];
    int process_len = 0;
    int z = MidCode, op = WRITE, MidCode_buf = MidCode, pcode_buf = pcode_num;
    if (*p == 'p' && *(p + 1) == 'r' && *(p + 2) == 'i' && *(p + 3) == 'n' && *(p + 4) == 't' && *(p + 5) == 'f') {
        p += 6;
        p += JumpSpace(p);
        if (*p == '(') {
            p++;
            p += JumpSpace(p);
            if ((process_len = String(p))) {
                for (int i = 1; i < process_len - 1; i++) {
                    word[i - 1] = *(p + i);
                }
                word[process_len - 2] = '\0';
                auto iter = SymFind(word);
                z = iter->second.code;
                PCodeInsert(pcode_num++, 0, 0, op, z);
                p += process_len;
                p += JumpSpace(p);
                if (*p == ',') {
                    p++;
                    p += JumpSpace(p);
                    z = MidCode;
                    if ((process_len = Expression(p, MidCode++))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            p++;
                            p += JumpSpace(p);
                            PCodeInsert(pcode_num++, 0, 0, op, z);
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
                    PCodeInsert(pcode_num++, 0, 0, op, z);
                    cout << "<WriteSentence>";
                    return (int) ((p - str) / sizeof(char));
                }
            }
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
    return 0;
}

int ReturnSentence(char *str) {
    char *p = str;
    int process_len = 0;
    int x = 31, y = 0, z = MidCode, op = RET, MidCode_buf = MidCode, pcode_buf = pcode_num;
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
                    PCodeInsert(pcode_num++, x, y, op, z);
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        } else {
            cout << "<ReturnSen>";
            return (int) ((p - str) / sizeof(char));
        }
    }
    MidCode = MidCode_buf;
    pcode_num = pcode_buf;
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
    MidCode = MID_CODE_BASE;
    while ((process_len = ReturnFuncDefine(p)) || (process_len = NoReturnFuncDefine(p))) {
        cout << "<FuncDefine>" << endl << endl;
        p += process_len;
        p += JumpSpace(p);
        TableNum++;
        MidCode = MID_CODE_BASE;
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
