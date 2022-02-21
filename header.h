#include "coada.h"
#include "stiva.h"

typedef struct s
{
    int ID;
    char *nume;
    float rating;
    int nrs;
    int poz;
    AQ sezon;
} serial;

typedef struct sez
{
    int nre;
    AQ episod;
} sezon;