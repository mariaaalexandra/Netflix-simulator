#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef LISTA
#define LISTA

//structura lista simplu inlantuita
typedef struct celula
{
    void *info;
    struct celula *urm;
} TCelula, *TLista;

//functie comparare
typedef int (*TFcmp)(void *, void *);

//functie afisare
typedef void (*TAfi)(void *, FILE *);

//alocare celula
TLista AlocCelula(void *el);

//inserare dupa
int ins_after(TLista l, void *el);

//inserare la inceput
int ins_first(TLista *l, void *el);

//inserare la final
int ins_last(TLista *l,  void *el);

//sterg dupa
void *sterg_after(TLista l);

//sterg inceput lista
void *sterg_first(TLista *l);

//sterg final lista
void *sterg_last(TLista *l);

#endif