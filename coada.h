#include "lista.h"


#ifndef COADA
#define COADA

//structura coada
typedef struct coada
{
  size_t dime;
  TLista ic, sc;

} TCoada, *AQ;

#define IC(a) 	(((AQ)(a))->ic)
#define SC(a) 	(((AQ)(a))->sc)
#define DIMEC(a) (((AQ)(a))->dime)

//initializeaza coada
void* InitQ();

//inserare coada
int IntrQ(void* a, void* ae);

//extrage el
void *ExtrQ(void* ae);

#endif