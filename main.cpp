//
// Created by WML on 2018/11/8.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>
#include <fstream>

#define STRMAX 255

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

int Program(char *str);

int ReadFromFile(string path);

char *iden_point;

int Plus(char str) {
    if (str == '+') {
        //cout << "<plus>";
        cout << "<PLUS +>";
        return 1;
    } else if (str == '-') {
        //cout << "<plus>";
        cout << "<PLUS ->";
        return 1;
    } else {
        return 0;
    }
}

int Multi(char str) {
    if (str == '*') {
        cout << "<MULTI *>";
        return 1;
    } else if (str == '/') {
        cout << "<MULTI />";
        return 1;
    } else {
        return 0;
    }
}

int RelationalOperator(char *str) {
    if (*str == '<') {
        if (*(str + 1) == '=') {
            cout << "<REALAOP <=>";
            return 2;
        } else {
            cout << "<REALAOP <>";
            return 1;
        }
    } else if (*str == '>') {
        if (*(str + 1) == '=') {
            cout << "<REALAOP >=>";
            return 2;
        } else {
            cout << "<REALAOP >>";
            return 1;
        }
    } else if (*str == '!' && *(str + 1) == '=') {
        cout << "<REALAOP !=>";
        return 2;
    } else if (*str == '=' && *(str + 1) == '=') {
        cout << "<REALAOP ==>";
        return 2;
    }
    return 0;
}

int Letter(char str) {
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || str == '_') {
        return 1;
    }
    return 0;
}

int NotZeroNum(char str) {
    if (str >= '1' && str <= '9') {
        return 1;
    }
    return 0;
}

int Num(char str) {
    if (str == '0' || NotZeroNum(str)) {
        return 1;
    }
    return 0;
}

int Character(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (*p == '\'') {
        word[i++] = *p;
        p++;
        if (Plus(*p) || Multi(*p) || Num(*p) || Letter(*p)) {
            word[i++] = *p;
            p++;
            if (*p == '\'') {
                word[i++] = *p;
                word[i] = '\0';
                cout << "<CHAR " << word << ">";
                return 3;
            } else {
                cout << "<WRONG " << word << ">";
            }
        }
    }
    return 0;
}

int String(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (*p == '"') {
        word[i++] = *p;
        p++;
        while (true) {
            if (*p == 32 || *p == 33 || (*p >= 35 && *p <= 126)) {
                word[i++] = *p;
                p++;
                continue;
            } else {
                if (*p == '"') {
                    word[i++] = *p;
                    p++;
                    word[i] = '\0';
                    cout << "<STRING " << word << ">";
                    return (int) ((p - str) / sizeof(char));
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int NoSignNum(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    if (NotZeroNum(*p)) {
        word[i++] = *p;
        p++;
        while (true) {
            if (Num(*p)) {
                word[i++] = *p;
                p++;
                continue;
            } else {
                word[i] = '\0';
                cout << "<NUM " << word << ">";
                return (int) ((p - str) / sizeof(char));
            }
        }
    } else if (*p == '0') {
        cout << "<NUM 0>";
        return 1;
    }
    return 0;
}

int Integer(char *str) {
    char *p = str;
    char word[64];
    int i = 0;
    int process_len = 0;
    if (*p == '+' || *p == '-') {
        word[i++] = *p;
        p++;
    }
    if ((process_len = NoSignNum(p))) {
        for (int mid = 0; mid < process_len; mid++) {
            word[i + mid] = *(p + mid);
        }
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int Identifier(char *str) {
    char *p = str;
    char word[63];
    int i = 0;
    if (Letter(*p)) {
        word[i++] = *p;
        p++;
    } else {
        return 0;
    }
    while (true) {
        if (Letter(*p) || Num(*p)) {
            word[i++] = *p;
            p++;
        } else {
            word[i] = '\0';
            if (!strcmp(word, "while") || !strcmp(word, "for") || !strcmp(word, "return") || !strcmp(word, "void") ||
                !strcmp(word, "main") || !strcmp(word, "do") || !strcmp(word, "scanf") || !strcmp(word, "printf")) {
                return 0;
            }
            p += JumpSpace(p);
            word[i] = '\0';
            if (str > iden_point) {
                iden_point = str;
                cout << "<IDEN " << word << ">";
            }
            return (int) ((p - str) / sizeof(char));
        }
    }
}

int ConstDefine(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        p += 3;
        if (*p != ' ') {
            return 0;
        }
        p++;
        if ((process_len = Identifier(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == '=') {
                p++;
                p += JumpSpace(p);
                if ((process_len = Integer(p))) {
                    p += process_len;
                    while (*p == ',') {
                        p++;
                        cout << "<COMMA ,>";
                        p += JumpSpace(p);
                        if ((process_len = Identifier(p))) {
                            p += process_len;
                            if (*p++ == '=') {
                                if ((process_len = Integer(p))) {
                                    p += process_len;
                                    p += JumpSpace(p);
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    p += JumpSpace(p);
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        }
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        p += 4;
        if (*p != ' ') {
            return 0;
        }
        if (Identifier(p)) {
            p += process_len;
            if (*p == '=') {
                p++;
                p += JumpSpace(p);
                if ((process_len = Integer(p))) {
                    p += process_len;
                    p += JumpSpace(p);
                    while (*p == ',') {
                        p++;
                        cout << "<COMMA ,>";
                        p += JumpSpace(p);
                        if ((process_len = Identifier(p))) {
                            p += process_len;
                            p += JumpSpace(p);
                            if (*p == '=') {
                                p++;
                                p += JumpSpace(p);
                                if ((process_len = Integer(p))) {
                                    p += process_len;
                                    p += JumpSpace(p);
                                    return (int) ((p - str) / sizeof(char));
                                }
                            }
                        }
                    }
                    p += JumpSpace(p);
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
    int isRight = 0;
    if (*p == 'c' && *(p + 1) == 'o' && *(p + 2) == 'n' && *(p + 3) == 's' && *(p + 4) == 't') {
        p += 5;
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            while ((process_len = ConstDefine(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ';') {
                    cout << "<SEMISY ;>";
                    p++;
                    p += JumpSpace(p);
                    isRight = 1;
                    break;
                } else {
                    isRight = 0;
                    break;
                }
            }
        }
        if (isRight) {
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int DeclareHead(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == 'i' && *(p + 1) == 'n' && *(p + 2) == 't') {
        p += 3;
    } else if (*p == 'c' && *(p + 1) == 'h' && *(p + 2) == 'a' && *(p + 3) == 'r') {
        p += 4;
    }
    if (*p == ' ') {
        p++;
        process_len = Identifier(p);
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int TypeIdentifier(char *str) {
    if (*str == 'i' && *(str + 1) == 'n' && *(str + 2) == 't' && *(str + 3) == ' ') {
        cout << "<TYPEIDEN int>";
        return 3;
    } else if (*str == 'c' && *(str + 1) == 'h' && *(str + 2) == 'a' && *(str + 3) == 'r' && *(str + 4) == ' ') {
        cout << "<TYPEIDEN char>";
        return 4;
    }
    return 0;
}

int VarDefine(char *str) {
    char *p = str;
    int process_len = 0;
    int isVarDefine = 0;
    while ((process_len = TypeIdentifier(p))) {
        p += process_len;
        if (*p++ == ' ') {
            if ((process_len = Identifier(p))) {
                p += process_len;
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
                cout << "<COMMA ,>";
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
        p += process_len;
        if (*p != ';') {
            break;
        } else {
            cout << "<SEMISY ;>";
            isVarDeclare = 1;
            p++;
        }
    }
    if (isVarDeclare) {
        p += JumpSpace(p);
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
            cout << "<LBRACK (>";
            p++;
            p += JumpSpace(p);
            if ((process_len = ParameterList(p)) || *p == ')') {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    if (*p == '{') {
                        cout << "<LBRACE {>";
                        p++;
                        p += JumpSpace(p);
                        if ((process_len = CompoundSentence(p))) {
                            p += process_len;
                            p += JumpSpace(p);
                            if (*p == '}') {
                                cout << "<RBRACE }>";
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
        p += 4;
        cout << "<TYPEIDEN void>";
        if (*p == ' ') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == '(') {
                    cout << "<LBRACK (>";
                    p++;
                    *p += JumpSpace(p);
                    if ((process_len = ParameterList(p)) || *p == ')') {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            cout << "<RBRACK )>";
                            p++;
                            p += JumpSpace(p);
                            if (*p == '{') {
                                cout << "<LBRACE {>";
                                p++;
                                p += JumpSpace(p);
                                if ((process_len = CompoundSentence(p))) {
                                    p += process_len;
                                    p += JumpSpace(p);
                                    if (*p == '}') {
                                        cout << "<RBRACE }>";
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
                    cout << "<COMMA ,>";
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
                    cout << "<LBRACK (>";
                    p++;
                    p += JumpSpace(p);
                    if (*p == ')') {
                        cout << "<RBRACK )>";
                        p++;
                        p += JumpSpace(p);
                        if (*p == '{') {
                            cout << "<LBRACE {>";
                            p++;
                            p += JumpSpace(p);
                            if ((process_len = CompoundSentence(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                if (*p == '}') {
                                    cout << "<RBRACE }>";
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

int Expression(char *str) {
    char *p = str;
    int process_len = 0;
    if (*p == '+' || *p == '-') {
        p++;
    }
    p += JumpSpace(p);
    while ((process_len = Term(p))) {
        p += process_len;
        p += JumpSpace(p);
        if ((process_len = Plus(*p))) {
            p += process_len;
            p += JumpSpace(p);
        } else {
            p += JumpSpace(p);
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int Term(char *str) {
    char *p = str;
    int process_len = 0;
    while ((process_len = Factor(p))) {
        p += process_len;
        p += JumpSpace(p);
        if ((process_len = Multi(*p))) {
            p += process_len;
            p += JumpSpace(p);
        } else {
            return (int) ((p - str) / sizeof(char));
        }
    }
    return 0;
}

int Factor(char *str) {
    char *p = str;
    int process_len = 0;
    if ((process_len = ReturnFuncCall(p))) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Identifier(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == '[') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    return (int) ((p - str) / sizeof(char));
                }
            }
        } else {
            return (int) ((p - str) / sizeof(char));
        }
    } else if ((process_len = Integer(p))) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    } else if ((process_len = Character(p))) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    } else if (*p == '(') {
        cout << "<LBRACK (>";
        p++;
        p += JumpSpace(p);
        if ((process_len = Expression(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == ')') {
                cout << "<RBRACK )>";
                p++;
                p += JumpSpace(p);
                return (int) ((p - str) / sizeof(char));
            }
        }
    }
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
        cout << "<LBRACE {>";
        p++;
        p += JumpSpace(p);
        if ((process_len = SentenceColumn(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == '}') {
                cout << "<RBRACE }>";
                p++;
                process_len = 0;
                isRight = 2;
            }
        }
    } else if (*p == ';') {
        cout << "<SEMISY ;>";
        p++;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    if (isRight == 1) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == ';') {
            cout << "<SEMISY ;>";
            p++;
            p += JumpSpace(p);
            return (int) ((p - str) / sizeof(char));
        }
    } else if (isRight == 2) {
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
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
            if ((process_len = Expression(p))) {
                p += process_len;
                p += JumpSpace(p);
                //cout << "<AssignSentence>";
                return (int) ((p - str) / sizeof(char));
            }
        } else if (*p == '[') {
            p++;
            p += JumpSpace(p);
            if ((process_len = Expression(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ']') {
                    p++;
                    p += JumpSpace(p);
                    if (*p == '=') {
                        p++;
                        p += JumpSpace(p);
                        if ((process_len = Expression(p))) {
                            p += process_len;
                            p += JumpSpace(p);
                            //cout << "<AssignSentence>";
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
            cout << "<LBRACK (>";
            p++;
            p += JumpSpace(p);
            cout << "<REWORD if>";
            if ((process_len = Condition(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
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
                                //cout << "<IF>";
                                return (int) ((p - str) / sizeof(char));
                            }
                        } else {
                            //cout << "<IF>";
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
    if ((process_len = Expression(p))) {
        p += process_len;
        p += JumpSpace(p);
        if ((process_len = RelationalOperator(p))) {
            p += process_len;
            p += JumpSpace(p);
            if ((process_len = Expression(p))) {
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
        cout << "<REWORD do>";
        if ((process_len = Sentence(p))) {
            p += process_len;
            p += JumpSpace(p);
            if (*p == 'w' && *(p + 1) == 'h' && *(p + 2) == 'i' && *(p + 3) == 'l' && *(p + 4) == 'e') {
                p += 5;
                p += JumpSpace(p);
                cout << "<REWORD while>";
                if (*p == '(') {
                    cout << "<LBRACK (>";
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Condition(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            cout << "<RBRACK )>";
                            p++;
                            p += JumpSpace(p);
                            //cout << "<DoWhile>";
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
            cout << "<REWORD for>";
            cout << "<LBRACK (>";
            p++;
            p += JumpSpace(p);
            if ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == '=') {
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Expression(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ';') {
                            cout << "<SEMISY ;>";
                            p++;
                            p += JumpSpace(p);
                            if ((process_len = Condition(p))) {
                                p += process_len;
                                p += JumpSpace(p);
                                if (*p == ';') {
                                    cout << "<SEMISY ;>";
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
                                                    cout << "<RBRACK )>";
                                                    p++;
                                                    p += JumpSpace(p);
                                                    if ((process_len = Sentence(p))) {
                                                        p += process_len;
                                                        p += JumpSpace(p);
                                                        //cout << "<For>";
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
            cout << "<LBRACK (>";
            p++;
            p += JumpSpace(p);
            if ((process_len = ValueParameterList(p)) || (*p == ')')) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    //cout << "<ReturnFuncCall>";
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
            cout << "<LBRACK (>";
            p++;
            p += JumpSpace(p);
            if ((process_len = ValueParameterList(p)) || (*p == ')')) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    //cout << "<NoReturnFuncCall>";
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
    while ((process_len = Expression(p))) {
        p += process_len;
        p += JumpSpace(p);
        if (*p == ',') {
            cout << "<COMMA ,>";
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
            cout << "<REWORD scanf>";
            cout << "<LBRACK (>";
            while ((process_len = Identifier(p))) {
                p += process_len;
                p += JumpSpace(p);
                isRight = 1;
                if (*p == ',') {
                    cout << "<COMMA ,>";
                    p++;
                } else {
                    break;
                }
            }
            if (isRight) {
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    //cout << "<ReadSentence>";
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
            cout << "<REWORD printf>";
            cout << "<LBRACK (>";
            if ((process_len = String(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ',') {
                    cout << "<COMMA ,>";
                    p++;
                    p += JumpSpace(p);
                    if ((process_len = Expression(p))) {
                        p += process_len;
                        p += JumpSpace(p);
                        if (*p == ')') {
                            cout << "<RBRACK )>";
                            p++;
                            p += JumpSpace(p);
                            //cout << "<WriteSentence>";
                            return (int) ((p - str) / sizeof(char));
                        }
                    }
                } else if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    //cout << "<WriteSentence>";
                    return (int) ((p - str) / sizeof(char));
                }
            } else if ((process_len = Expression(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    p += JumpSpace(p);
                    //cout << "<WriteSentence>";
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
            cout << "<REWORD return>";
            cout << "<LBRACK (>";
            if ((process_len = Expression(p))) {
                p += process_len;
                p += JumpSpace(p);
                if (*p == ')') {
                    cout << "<RBRACK )>";
                    p++;
                    //cout << "<ReturnSen>";
                    return (int) ((p - str) / sizeof(char));;
                }
            }
        } else {
            //cout << "<ReturnSen>";
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
        //cout << "<ConstDeclare>";
    }
    if ((process_len = VarDeclare(p))) {
        p += process_len;
        p += JumpSpace(p);
        //cout << "<VarDeclare>";
    }
    while ((process_len = ReturnFuncDefine(p)) || (process_len = NoReturnFuncDefine(p))) {
        //cout << "<FuncDefine>";
        p += process_len;
        p += JumpSpace(p);
    }
    if ((process_len = MainFunc(p))) {
        //cout << "<MainFunc>";
        p += process_len;
        p += JumpSpace(p);
        return (int) ((p - str) / sizeof(char));
    }
    return 0;
}

int JumpSpace(char *str) {
    char *p = str;
    while (*p == ' ' || *p == '\n' || *p == '\t') {
        if (*p == '\t') {
            cout << endl;
        }
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}


int ErrorJump(char *str) {
    char *p = str;
    while (*p != ';') {
        p++;
    }
    return (int) ((p - str) / sizeof(char));
}

int ReadFromFile() {
    FILE *fp;
    char str[1000];
    char mid[255];
    int i = 0;//home/wml/CLionProjects/GrammarAnalysis/helloworld.txt
    cout << "Input file path: ";
    fp = fopen("C:\\Users\\WML\\CLionProjects\\GrammarAnalysis\\helloworld.txt", "r");
    while (fgets(mid, 255, fp)) {
        strcpy(str + i * sizeof(char), mid);
        i += strlen(mid);
    }
    iden_point = str;
    //cout << "code total length: " << strlen(str);
    int
            isFinish = Program(str);
    if (isFinish)
        cout << "Right";
    else
        cout << "wrong";
    return 0;
}


int main() {
    char buf[STRMAX];
    string str("  ");
    strncpy(buf, str.c_str(), str.length());
    ReadFromFile();
    return 0;
}