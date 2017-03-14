#include <stdio.h>
#include <stdlib.h>
#include "Calc2.h"

int main(){
    int d = 2;
    float f = 5.2f;
    double lf = 3.5;
    bool b = true;
    while(true){
    printf("Input : ");
    char inputBuffer[256];
    char* input = gets(inputBuffer);
    Operation op = Operation_FromString(input);

    if (op == null){
        printf("null");
        return 0;
    }
    printf("Input interpretation : ");
    Operation_Print(op);
    b = Operation_TrySolve(op, &lf);
    printf("\nOutput : %g\n", lf);
    Operation_Free(op);
    }
    return 0;
}
