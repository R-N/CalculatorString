#ifndef CALC2_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"
#include "DoubleLinkedListVoid.h"



typedef struct MathT_Struct{
    int type;
    void* data;
}* MathT;

#define MathT_Operation 0
#define MathT_int 1
#define MathT_float 2
#define MathT_double 3
#define MathT_Add 4
#define MathT_Subtract 5
#define MathT_Multiply 6
#define MathT_Divide 7
#define MathT_Modulus 8
#define MathT_Power 9


struct Operation_Struct;

typedef struct Operation_Struct* Operation;

MathT MathT_Create();

MathT MathT_FromOperation(Operation);

MathT MathT_Operator(int);

MathT MathT_FromInt(int);

MathT MathT_FromFloat(float);

MathT MathT_FromDouble(double);

bool MathT_TryConvertToInt(MathT, int*);
bool MathT_TryConvertToFloat(MathT, float*);
bool MathT_TryConvertToDouble(MathT, double*);



void MathT_Free(MathT);

typedef struct Operation_Struct{
    List op; //list of MathT
}* Operation;

Operation Operation_Create();

Operation Operation_FromString(char*);

int Operation_GetReturnType(Operation o);

bool Operation_SolveInnerOperations(Operation o);

double Operation_Solve(Operation);


int String_SkipSpaces(char*);
bool MathT_TryReadInt(char*, int*);
bool MathT_TryReadFloat(char*, float*);
bool MathT_TryReadDouble(char*, double*);
bool MathT_TryReadNumber(char*, double*);
bool MathT_TryReadOperator(char*, int*);
bool MathT_TryReadBraces(char*, Operation*);
bool Char_IsNumber(char);
bool String_IsNullOrEmpty(char* s);

bool String_HasNumber(char*);
bool String_HasOperator(char*);
bool String_HasBraces(char*);

void Operation_Free(Operation);

int String_IndexOfChar(char*, char);

void Operation_Print(Operation o);
void MathT_Print(MathT);

#define CALC2_H
#endif
