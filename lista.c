/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "lista.h"

//alocare celula
TLista AlocCelula(void *el)
{
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));
    if (!aux) {
        return NULL;
    }
    aux->info = el;
    aux->urm = NULL;
    return aux;
}

//inserare dupa lista
int ins_after(TLista l, void *el)
{
    TLista p = l, aux;

    aux = (TLista)AlocCelula(el);
    if (aux == NULL) {
        return 0;
    }
    aux->urm = p->urm;
    p->urm = aux;
    return 1;
}

//inserare inceput de lista 
int ins_first(TLista *l, void *el)
{
    TLista aux;
    aux = (TLista)AlocCelula(el);
    if (aux == NULL) {
        return 0;
    }
    //inserare lista vida
    if (*l == NULL) {
        *l = aux;
        return 1;
    }
    aux->urm = *l;
    *l = aux;
    return 1;
}

//inserare sfarsit lista
int ins_last(TLista *l, void *el)
{
    if (*l == NULL) {
        ins_first(l, el);
    }
    TLista aux, p;
    aux = (TLista)AlocCelula(el);
    for(p = *l; p->urm != NULL; p = p->urm);
    p->urm = aux;
    return 1;
}

//stergere dupa lista
void *sterg_after(TLista l)
{
    TLista aux = l->urm;
    l->urm = l->urm->urm;

    void *info = aux->info;
    free(aux);
    return info;
}

//stergere primul element, returnez el sters
void *sterg_first(TLista *l)
{
    if (*l == NULL) {
        return NULL;
    }

    TLista aux;
    //transf lista vida
    if ((*l)->urm == NULL) {
        aux = *l;
        *l = NULL;
    }
    else {
        aux = *l;
        *l = (*l)->urm;
    }
    void *info = aux->info;
    free(aux);

    return info;
}

//stergere ultim element
void *sterg_last(TLista *l)
{
    if (*l == NULL) {
        return NULL;
    }

    TLista p;
    //lista vida
    if ((*l)->urm == NULL) {
        p = *l;
        *l = NULL;
    }
    else {
        for(p = *l; p->urm->urm != NULL; p = p->urm);
    }
    void *info = p->urm->info;
    free(p->urm);
    p->urm = NULL;
    return info;
}
