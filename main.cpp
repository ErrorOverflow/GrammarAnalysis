//
// Created by WML on 2018/11/8.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

#define STRMAX 255

char *point = NULL;

using namespace std;

int Plus(char str);

int Multi(char str);

int RelationalOperator(char *str);

int Letter(char str);

int NotZeroNum(char str);

int Num(char str);

int Character(char *str);

int String(char *str);

int NoSignNum(char *str);

int Integer(char *str);

int Identifier(char *str);

int ConstDefine(char *str);

int ConstDeclare(char *str);

int DeclareHead(char *str);

int TypeIdentifier(char *str);

int VarDefine(char *str);

int VarDeclare(char *str);

int ReturnFuncDefine(char *str);

int NoReturnFuncDefine(char *str);

int CompoundSentence(char *str);

int ParameterList(char *str);

int MainFunc(char *str);

int Expression(char *str);

int Term(char *str);

int Factor(char *str);

int Sentence(char *str);

int AssignSentence(char *str);

int ConditionSentence(char *str);

int Condition(char *str);

int LoopSentence(char *str);

int Step(char *str);

int ReturnFuncCall(char *str);

int NoReturnFuncCall(char *str);

int ValueParameterList(char *str);

int SentenceColumn(char *str);

int ReadSentence(char *str);

int WriteSentence(char *str);

int ReturnSentence(char *str);

int JumpSpace(char *str);

int Plus(char str) {
    if (str == '+') {
        cout << "<plus>";
        return 1;
    } else if (str == '-') {
        cout << "<plus>";
        return 2;
    } else {
        return 0;
    }
}

int Multi(char str) {
    if (str == '*') {
        cout << "<multi>";
        return 1;
    } else if (str == '/') {
        cout << "<multi>";
        return 2;
    } else {
        return 0;
    }
}

int RelationalOperator(char *str) {
    if (*str == '<') {
        if (*(str + 1) == '=') {
            cout << "<relational operator>";
            return 2;
        } else {
            cout << "<relational operator>";
            return 1;
        }
    } else if (*str == '>') {
        if (*(str + 1) == '=') {
            cout << "<relational operator>";
            return 2;
        } else {
            cout << "<relational operator>";
            return 1;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 2;
    } else if (*str == '=' && *(str + 1) == '=') {
        cout << "<relational operator>";
        return 2;
    }
    return 0;
}

int Letter(char str) {
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || str == '_') {
        cout << "<letter>";
        return 1;
    }
    return 0;
}

int NotZeroNum(char str) {
    if (str >= '1' && str <= '9') {
        cout << "<not_zero_num>";
        return 1;
    }
    return 0;
}

int Num(char str) {
    if (str == '0' || NotZeroNum(str)) {
        cout << "<num>";
        return 1;
    }
    return 0;
}

int Character(char *str) {
    char *p = str;
    if (*p++ == '\'') {
        if (Plus(*p) || Multi(*p) || Num(*p) || Letter(*p)) {
            *p++;
            if (*p == '\'') {
                return 3;
            }
        }
    }
    return 0;
}

int String(char *str) {
    char *p = str;
    while (1) {
        if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
            *p++;
            continue;
        } else {
            cout << *p << endl;
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int NoSignNum(char *str) {
    char *p = str;
    if (NotZeroNum(*p)) {
        *p++;
        while (1) {
            if (Num(*p)) {
                *p++;
                continue;
            } else {
                return (int) ((p - str) / sizeof(char));
            }
        }
    } else if (*p == '0') {
        return 1;
    }
    return 0;
}

int Integer(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == '+' || *p == '-') {
        *p++;
    }
    if ((process_len = NoSignNum(p))) {
        *p += process_len;
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int Identifier(char *str) {
    char *p = str;
    if (Letter(*p)) {
        *p++;
    } else {
        return 0;
    }
    while (1) {
        if (Letter(*p) || Num(*p)) {
            *p++;
        } else {
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int ConstDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        *p += 3;
        if (*p++ != ' ') {
            return 0;
        }
        if (Identifier(p)) {
            *p += process_len;
            if (*p++ == '=') {
                if ((process_len = Integer(p))) {
                    *p += process_len;
                    while (*p == ',') {
                        *p++;
                        if ((process_len = Identifier(p))) {
                            *p += process_len;
                            if (*p++ == '=') {
                                if ((process_len = Integer(p))) {
                                    *p += process_len;
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        }
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        p += 4;
        if (*p++ != ' ') {
            return 0;
        }
        if (Identifier(p)) {
            p += process_len;
            if (*p++ == '=') {
                if ((process_len = Integer(p))) {
                    p += process_len;
                    while (*p == ',') {
                        p++;
                        if ((process_len = Identifier(p))) {
                            *p += process_len;
                            if (*p++ == '=') {
                                if ((process_len = Integer(p))) {
                                    *p += process_len;
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        }
    }
    return 0;
}

int ConstDeclare(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'c' && *(p + 1) == 'o' && *(p + 2) == 'n' && *(p + 3) == 's' && *(p + 4) == 't') {
        *p += 5;
        if (*p == ' ') {
            p++;
            process_len = ConstDefine(p);
            *p += process_len;
            if (*p == ';') {
                process_len = ConstDeclare(p);//递归
                if (process_len != 0) {
                    *p += process_len;
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int DeclareHead(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        *p += 3;
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        *p += 4;
    }
    if (*p == ' ') {
        p++;
        process_len = Identifier(p);
        *p += process_len;
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int TypeIdentifier(char *str) {
    if (*str == 'i' && *(str + 1) == 'n' && *(str + 2) == 't') {
        return 3;
    } else if (*str == 'c' && *(str + 1) == 'h' && *(str + 2) == 'a' && *(str + 3) == 'r') {
        return 4;
    }
    return 0;
}

int VarDefine(char *str) {
    char *p = str;
    int process_len = 0;
    int isVarDefine = 0;
    while ((process_len = TypeIdentifier(p))) {
        *p += process_len;
        if (*p++ == ' ') {
            if ((process_len = Identifier(p))) {
                *p += process_len;
                if (*p == '[') {
                    p++;
                    if ((process_len = NoSignNum(p))) {
                        *p += process_len;
                        if (*p == ']') {
                            isVarDefine = 1;
                        }
                    }
                } else {
                    isVarDefine = 1;
                }
            }
        }
        if (isVarDefine) {
            if (*p == ',') {
                p++;
            } else {
                break;
            }
        } else {
            return 0;
        }
    }
    return (int) ((p - str) / sizeof(char));
}

int VarDeclare(char *str) {
    char *p = str;
    int process_len = 0;
    int isVarDeclare = 0;
    while ((process_len = VarDefine(p))) {
        *p += process_len;
        if (*p != ',') {
            isVarDeclare = 1;
            break;
        } else {
            p++;
        }
    }
    if (isVarDeclare) {
        return (int) ((p - str) / sizeof(char));
    } else {
        return 0;
    }
}

int ReturnFuncDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = DeclareHead(p))) {
        *p += process_len;
        *p += JumpSpace(p);
        if (*p == '(') {
            p++;
            *p += JumpSpace(p);
            if ((process_len = ParameterList(p))) {
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
        p += 3;
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == '(') {
                    p++;
                    *p += JumpSpace(p);
                    if ((process_len = ParameterList(p))) {
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
}

int MainFunc(char *str) {
    char *p = str;
    int process_len = 0;
}

int Expression(char *str) {
    char *p = str;
    int process_len = 0;
}

int Term(char *str) {
    char *p = str;
    int process_len = 0;
}

int Factor(char *str) {
    char *p = str;
    int process_len = 0;
}

int Sentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int AssignSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int ConditionSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int Condition(char *str) {
    char *p = str;
    int process_len = 0;
}

int LoopSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int Step(char *str) {
    char *p = str;
    int process_len = 0;
}

int ReturnFuncCall(char *str) {
    char *p = str;
    int process_len = 0;
}

int NoReturnFuncCall(char *str) {
    char *p = str;
    int process_len = 0;
}

int ValueParameterList(char *str) {
    char *p = str;
    int process_len = 0;
}

int SentenceColumn(char *str) {
    char *p = str;
    int process_len = 0;
}

int ReadSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int WriteSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int ReturnSentence(char *str) {
    char *p = str;
    int process_len = 0;
}

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ') {
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}


int main() {
    char buf[STRMAX];
    string str(" ");
    strncpy(buf, str.c_str(), str.length());
    point = buf;
    cout << "233" << endl;
    cout << JumpSpace(buf) << endl;
    return 0;
}