//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LEXICALANALYSIS_H
#define COMPILER_LEXICALANALYSIS_H

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

int Program(char *str);

#endif //COMPILER_LEXICALANALYSIS_H