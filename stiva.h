#include "lista.h"

#ifndef STIVA
#define STIVA


//structura stiva
typedef struct stiva
{
    size_t dime;
    TLista vf;
} TStiva, *ASt;

#define VF(a) (((ASt)(a))->vf);
#define DIMES(a) (((ASt)(a))->dime);

void *InitS();

int Push(void *s, void *ae);

void *Pop(void *s);

#endif