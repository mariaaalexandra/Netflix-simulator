/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "stiva.h"
#include "header.h"

//initializare stiva
void *InitS()
{
    ASt s;
    s = (ASt)malloc(sizeof(TStiva));
    if (!s) {
        printf("EROARE ALOCARE STIVA\n");
        return NULL;
    }

    s->vf = NULL;

    return (void *)s;
}

//inserare stiva=ins inceput de lista
int Push(void *s, void *ae)
{
    ASt stack = (ASt)s;
    int rez = ins_first(&(stack->vf), ae);

    return rez;
}

//extragere  stiva=stergere inceput de lista
void *Pop(void *s)
{
    ASt stack = (ASt)s;
    void *ae = sterg_first(&(stack->vf));
    return ae;
}
