/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "coada.h"

//initializare coada
void *InitQ()
{
    AQ c;
    c = (AQ)malloc(sizeof(TCoada));
    if (!c) {
        printf("EROARE ALOCARE COADA\n");
        return NULL;
    }

    c->ic = NULL;
    c->sc = NULL;

    return (void *)c;
}

//inserare coada=inserare final
int IntrQ(void* c, void *ae)
{
    AQ queue = (AQ)c;
    int rez;

    //ins in coada vida
    if (queue->ic == NULL && queue->sc == NULL) {
        rez = ins_first(&(queue->ic), ae);
        queue->sc = queue->ic;
    }
    else {
       rez = ins_after(queue->sc, ae);
       queue->sc = queue->sc->urm;
    }
    return rez;
}

//extragere coada=stergere prim
void *ExtrQ(void *c)
{
    AQ queue = (AQ)c;
    void *ae = sterg_first(&(queue->ic));
    if (queue->ic == NULL) {
        queue->sc = NULL;
    }
    
    return ae;
}
