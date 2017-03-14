
#include "Calc2.h"

MathT MathT_Create(){
    MathT num = (MathT)malloc(sizeof(struct MathT_Struct));
    return num;
}

MathT MathT_FromOperation(Operation op){
    MathT num = MathT_Create();
    num->data = op;
    num->type = MathT_Operation;
}

MathT MathT_Operator(int type){
    MathT num = MathT_Create();
    num->type = type;
    num->data = null;
    return num;
}

MathT MathT_FromInt(int data){
    MathT num = MathT_Create();
    num->type = MathT_int;
    int* d = (int*)malloc(sizeof(int));
    memcpy(d, &data, sizeof(int));
    num->data = d;
    return num;
}

MathT MathT_FromFloat(float data){
    MathT num = MathT_Create();
    num->type = MathT_float;
    float* d = (float*)malloc(sizeof(float));
    memcpy(d, &data, sizeof(float));
    num->data = d;
    return num;
}

MathT MathT_FromDouble(double data){
    MathT num = MathT_Create();
    num->type = MathT_double;
    double* d = (double*)malloc(sizeof(double));
    memcpy(d, &data, sizeof(double));
    num->data = d;
    return num;
}

void MathT_Free(MathT mt){
    if (mt->type == MathT_Operation)
        Operation_Free(mt->data);
    else
        free(mt->data);
    free(mt);
}

bool Char_IsNumber(char c){
    return (c >= '0' && c <= '9');
}

int String_SkipSpaces(char* c){
    if (c == null)
        return 0;
    int i = 0;
    while(c[0] == ' '){
        ++i;
        c = &(c[1]);
    }
    return i;
}

bool MathT_TryReadInt(char* s, int* out){
    if (s == null || out == null)
        return false;
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0')
        return false;
    if (!Char_IsNumber(s[0]) && s[0] != '-')
        return false;
    int ret;
    int n;
    if(sscanf(s, "%d%n", &ret, &n) != 1)
        return false;
    if (s[n] == '.')
        return false;
    *out = ret;
    return (n+space);
}
bool MathT_TryReadFloat(char* s, float* out){
    if (s == null || out == null)
        return false;
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0')
        return false;
    if (!Char_IsNumber(s[0]) && s[0] != '-')
        return false;
    float ret;
    int n;
    if(sscanf(s, "%f%n", &ret, &n) != 1)
        return false;
    char c;
    if(s[n] != 'f')
        return false;
    *out = ret;
    return (n+space);
}

bool MathT_TryReadDouble(char* s, double* out){
    if (s == null || out == null)
        return false;
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0')
        return false;
    if (!Char_IsNumber(s[0]) && s[0] != '-')
        return false;
    double ret;
    int n;
    if(sscanf(s, "%lf%n", &ret, &n) != 1){
        printf("d5\n");
        return false;
    }
    char c;
    if(s[n] == 'f')
        return false;
    *out = ret;
    return (n+space);
}
bool MathT_TryReadNumber(char* s, double* out){
    if (s == null || out == null)
        return false;
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0')
        return false;
    if (!Char_IsNumber(s[0]) && s[0] != '-')
        return false;
    double ret;
    int n;
    if(sscanf(s, "%lf%n", &ret, &n) != 1){
        printf("n5\n");
        return false;
    }
    char c;
    *out = ret;
    return (n+space);
}
bool MathT_TryReadOperator(char* s, int* out){
    if (s == null || out == null)
        return false;
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0')
        return false;
    if (Char_IsNumber(s[0]))
        return false;
    char c = s[0];
    switch(c){
        case '+':{
            *out = MathT_Add;
            break;
        }
        case '-':{
            *out = MathT_Subtract;
            break;
        }
        case '*':{
            *out = MathT_Multiply;
            break;
        }
        case 'x':{
            *out = MathT_Multiply;
            break;
        }
        case 'X':{
            *out = MathT_Multiply;
            break;
        }
        case ':':{
            *out = MathT_Divide;
            break;
        }
        case '/':{
            *out = MathT_Divide;
            break;
        }
        default:{
            return false;
        }
    }
    return (1+space);
}

bool String_IsNullOrEmpty(char* s){
    return (s==null || s[0] == '\0' || s[String_SkipSpaces(s)] == '\0');
}

int String_IndexOfChar(char* s, char c){
    if (s == null || s[0] == '\0')
        return -1;
    int i = 0;
    while (s[0] != '\0'){
        if (s[0] == c)
            return i;
        ++i;
        s = &(s[1]);
    }
    return -1;
}


bool MathT_TryReadBraces(char* s, Operation* out){
    if (s == null || out == null){
        printf("b1");
        return false;
    }
    int space = String_SkipSpaces(s);
    if (space)
        s = &(s[space]);
    if (s[0] == '\0'){
        printf("b2");
        return false;
    }
    char c = s[0];
    if (c != '(')
        return false;
    s = &(s[1]);
    char* s0 = s;
    int i = 1;
    int n = 1;
    while (s[0] != '\0' && i > 0){
        ++n;
        if (s[0] == '(')
            ++i;
        else if (s[0] == ')')
            --i;
        s = &(s[1]);
    }
    if (i > 0)
        return false;
    char s1[n];
    int m = n-2;
    for (i = 0; i < m; ++i){
        s1[i] = s0[i];
    }
    s1[n-1] = '\0';
    *out = Operation_FromString(s1);
    return (n+space);
}

bool String_HasNumber(char* s){
    return Char_IsNumber(s[String_SkipSpaces(s)]);
}

bool String_HasBraces(char* s){
    return s[String_SkipSpaces(s)] == '(';
}

bool String_HasOperator(char* s){
    char c = s[String_SkipSpaces(s)];
    return (c=='+' || c=='-' || c=='*' || c=='x' || c ==':' || c=='/');
}

Operation Operation_Create(){
    Operation o = (Operation)malloc(sizeof(struct Operation_Struct));
    o->op = List_Create();
    return o;
}

Operation Operation_FromString(char* s){
    if (String_IsNullOrEmpty(s)){
        printf("fs1");
        return null;
    }
    s = &(s[String_SkipSpaces(s)]);
    if (!String_HasBraces(s)&&!String_HasNumber(s)){
        printf("fs2");
        return null;
    }
    Operation o = Operation_Create();
    Operation b;
    int n;
    bool wasOperator = true;
    int d;
    double lf;
    float f;
    char c;
    int asd = 0;
    while(s[0] != '\0'){
        ++asd;
        if(wasOperator){
            wasOperator = false;
            if (n=MathT_TryReadBraces(s, &b)){
                List_Add(o->op, MathT_FromOperation(b));
            /*}else if (n=MathT_TryReadFloat(s, &f)){
                List_Add(o->op, MathT_FromFloat(f));
            }else if (n=MathT_TryReadInt(s, &d)){
                List_Add(o->op, MathT_FromInt(d));
            }else if (n=MathT_TryReadDouble(s, &lf)){
                List_Add(o->op, MathT_FromDouble(lf));*/
            }else if (n=MathT_TryReadNumber(s, &lf)){
                List_Add(o->op, MathT_FromDouble(lf));
            }else{
                printf("fs3 %d", asd);
                return null;
            }
        }else{
            if (n=MathT_TryReadOperator(s, &d)){
                List_Add(o->op, MathT_Operator(d));
                wasOperator = true;
            }else{
                List_Add(o->op, MathT_Operator(MathT_Multiply));
                wasOperator = false;
                if (n=MathT_TryReadBraces(s, &b)){
                    List_Add(o->op, MathT_FromOperation(b));
                /*}else if (n=MathT_TryReadFloat(s, &f)){
                    List_Add(o->op, MathT_FromFloat(f));
                }else if (n=MathT_TryReadInt(s, &d)){
                    List_Add(o->op, MathT_FromInt(d));
                }else if (n=MathT_TryReadDouble(s, &lf)){
                    List_Add(o->op, MathT_FromDouble(lf));*/
                }else if (n=MathT_TryReadNumber(s, &lf)){
                    List_Add(o->op, MathT_FromDouble(lf));
                }else{
                    printf("fs4");
                    return null;
                }
            }
        }
        s=&(s[n]);
    }
    if (wasOperator){
        printf("fs5");
        return null;
    }
    if ((o->op->count-1)%2!=0){
        printf("fs6");
        return null;
    }
    List_Node node = o->op->first->next;
    int i = 1;
    while(node!=null){
        MathT op = node->data;
        if (op->type == MathT_Multiply || op->type == MathT_Divide){
            b = Operation_Create();
            MathT lhs = node->prev->data;
            MathT rhs = node->next->data;
            List_Add(b->op, lhs);
            List_Add(b->op, op);
            List_Add(b->op, rhs);
            if (!List_RemoveNode(o->op, node->prev, false))
                return null;
            if (!List_RemoveNode(o->op, node->next, false))
                return null;
            if (!List_RemoveNode(o->op, node, false))
                return null;
            if (List_Insert(o->op, MathT_FromOperation(b), i-1) == -1)
                return null;
            node = List_GetNode(o->op, i);
        }else{
            node = node->next->next;
            i+=2;
        }
    }
    return o;
}

int Operation_GetReturnType(Operation o){
    List_Node n = o->op->first;
    int ret = MathT_int;
    while(n != null){
        MathT mt = n->data;
        int t = mt->type;
        if (t == MathT_float)
            ret = MathT_float;
        else if (t == MathT_double)
            return t;
        else if (t == MathT_Operation){
            int ret2 = Operation_GetReturnType(mt->data);
            if (ret2 == MathT_float)
                ret = MathT_float;
            else if (ret2 == MathT_double)
                return MathT_double;
        }
        n = n->next->next;
    }
    return ret;
}

void Operation_Free(Operation o){
    List_Node n = o->op->first;
    while(n != null){
        MathT mt = n->data;
        MathT_Free(mt);
        List_Node m = n->next;
        free(n);
        n = m;
    }
    free(o->op);
    free(o);
}

bool Operation_SolveInnerOperations(Operation o){
    List_Node n = o->op->first;
    int i = 0;
    while(n != null){

        MathT mt = n->data;
        if (mt->type == MathT_Operation){
            Operation o2 = mt->data;
            int retType = Operation_GetReturnType(o2);

            List_Node m = n->next;

            if (!List_RemoveNode(o->op, n, false)){
                printf("sio0");
                return false;
            }

            double t;
            if (!Operation_TrySolve(o2, &t)){
                printf("sio1");
                return false;
            }
            if (retType == MathT_int){
                if(List_Insert(o->op, MathT_FromInt((int)t), i) < 0){
                    printf("sio2");
                    return false;
                }
            }else if (retType == MathT_float){
                if (List_Insert(o->op, MathT_FromFloat((float)(t)), i) < 0){
                    printf("sio3");
                    return false;
                }
            }else if (retType == MathT_double){
                if (List_Insert(o->op, MathT_FromDouble(t), i) < 0){
                    printf("sio4 %d %d", i, o->op->count);
                    return false;
                }
            }else{
                printf("sio5");
                return false;
            }
            Operation_Free(o2);
            n = m;
        }else
            n = n->next;
        ++i;
    }

    return true;
}

bool MathT_TryConvertToInt(MathT mt, int* out){
    if (mt->type == MathT_int){
        *out = *((int*)mt->data);
        return true;
    }else if (mt->type == MathT_float){
        *out = (int)(*((float*)mt->data));
        return true;
    }else if (mt->type == MathT_double){
        *out = (int)(*((double*)mt->data));
        return true;
    }
    return false;
}
bool MathT_TryConvertToFloat(MathT mt, float* out){
    if (mt->type == MathT_int){
        *out = (float)(*((int*)mt->data));
        return true;
    }else if (mt->type == MathT_float){
        *out = *((float*)mt->data);
        return true;
    }else if (mt->type == MathT_double){
        *out = (float)(*((double*)mt->data));
        return true;
    }
    return false;
}
bool MathT_TryConvertToDouble(MathT mt, double* out){
    if (mt->type == MathT_int){
        *out = (double)(*((int*)mt->data));
        return true;
    }else if (mt->type == MathT_float){
        *out = (double)(*((float*)mt->data));
        return true;
    }else if (mt->type == MathT_double){
        *out = *((double*)mt->data);
        return true;
    }
    return false;
}

bool MathT_IsNumber(MathT mt){
    return (mt->type >= 1 && mt->type <= 3);
}

bool MathT_IsOperator (MathT mt){
    return mt->type >= 4;
}

bool Operation_TrySolve(Operation o, double* out){
    if(!Operation_SolveInnerOperations(o)){
        printf("ts1");
        return false;
    }

    if (o->op->count < 1 || (o->op->count-1)%2 != 0){
        printf("ts2");
        return false;
    }


    if (o->op->count == 1){
        MathT mt = o->op->first->data;
        if (MathT_IsNumber(mt))
            return MathT_TryConvertToDouble(mt, out);
        else{
            printf("fs3");
            return false;
        }
    }
    List_Node n = o->op->first->next;
    double lhs;
    double rhs;
    if(!MathT_TryConvertToDouble(n->prev->data, &lhs)){
        printf("ts4");
        return false;
    }

    do{
        MathT op = n->data;
        if(!MathT_TryConvertToDouble(n->next->data, &rhs)){
            printf("ts5");
            return false;
        }
        switch(op->type){
            case MathT_Add:{
                lhs+=rhs;
                break;
            }
            case MathT_Subtract:{
                lhs-=rhs;
                break;
            }
            case MathT_Multiply:{
                lhs*=rhs;
                break;
            }
            case MathT_Divide:{
                lhs/=rhs;
                break;
            }
            default:{
                printf("ts6");
                return false;
            }
        }
        n = n->next->next;
    }while(n!=null);
    *out = lhs;
    return true;
}

void MathT_Print(MathT mt){
    switch(mt->type){
        case MathT_Operation:{
            printf("(");
            Operation_Print(mt->data);
            printf(")");
            break;
        }
        case MathT_int:{
            printf("%d", *((int*)mt->data));
            break;
        }
        case MathT_float:{
            printf("%g", *((float*)mt->data));
            break;
        }
        case MathT_double:{
            printf("%g", *((double*)mt->data));
            break;
        }
        case MathT_Add:{
            printf("+");
            break;
        }
        case MathT_Multiply:{
            printf("*");
            break;
        }
        case MathT_Subtract:{
            printf("-");
            break;
        }
        case MathT_Divide:{
            printf("/");
            break;
        }
    }
}

void Operation_Print(Operation o){
    if (o == null || o->op->count == 0)
        return;
    List_Node n = o->op->first;
    while(n!=null){
        MathT_Print(n->data);
        n=n->next;
    }
}
