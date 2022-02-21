/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "header.h"

//alocare structura sezon
sezon *aloc_sezon()
{
    sezon *el = (sezon *)malloc(1 * sizeof(sezon));
    if (el == NULL) {
        printf("EROARE DE ALOCARE SEZON\n");
        exit(-6);
    }
    el->episod = InitQ();
    if (el->episod == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }
    return el;
}

//alocare sezon nou
sezon *aloc_nou(char *line, char *name)
{
    //aloc si initializez structura cu informatiile din line
    sezon *nou = (sezon *)malloc(1 * sizeof(sezon));
    if (nou == NULL) {
        printf("EROARE ALOCARE SEZON\n");
        exit(-6);
    }
    strcpy(name, strtok(line, " \n"));
    nou->nre = atoi(strtok(NULL, " /n"));
    nou->episod = InitQ();
    if (nou->episod == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }
    int j;
    for (j = 0; j < nou->nre; j++) {
        int *durata = calloc(1, sizeof(int));
        if (durata == NULL) {
            printf("EROARE DE ALOCARE\n");
            exit(-2);
        }
        *durata = atoi(strtok(NULL, " \n"));

        //introduc durata in coada de episoade
        IntrQ(nou->episod, durata);
    }

    return nou;
}

//alocare structura serial
serial *aloc_serial(char *line)
{   
    //aloc o structura de tip serial si 
    //initializez fiecare camp cu informatia din line
    serial *el = (serial *)calloc(1, sizeof(serial));
    if (el == NULL) {
        printf("EROARE ALOCARE SERIAL\n");
        exit(-3);
    }

    el->ID = atoi(strtok(line, " \n"));
    el->nume = calloc(33, sizeof(char));
    if (el->nume == NULL) {
        printf("EROARE DE ALOCARE \n");
        exit(-2);
    }

    strcpy(el->nume, strtok(NULL, " \n"));
    el->rating = atof(strtok(NULL, " \n"));

    el->sezon = InitQ();
    if (el->sezon == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }

    el->nrs = atoi(strtok(NULL, " \n"));
    int i;
    for (i = 0; i < el->nrs; i++) {
        sezon *sez_nou = aloc_sezon();
        sez_nou->nre = atoi(strtok(NULL, " \n"));
        int j;
        for (j = 0; j < sez_nou->nre; j++) {
            int *durata = calloc(1, sizeof(int));
            if (durata == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            *durata = atoi(strtok(NULL, " \n"));
            IntrQ(sez_nou->episod, durata);
        }
        IntrQ(el->sezon, sez_nou); 
    }
    
    return el;
}

//functie comparare, 1 el1 primul, 0 el2 primul
int cmp(void *el1, void *el2)
{
    serial *seri1 = (serial *)el1;
    serial *seri2 = (serial *)el2;
    if (seri1->rating > seri2->rating) {
        return 1;
    }
    else if (seri1->rating < seri2->rating) {
        return 0;
    }
    else {
        if (strcmp(seri1->nume, seri2->nume) < 0) {
            return 1;
        }
        return 0;
    }
}

//functie adaugare serial
int add_serial(void *el, TLista *v, int nr, TFcmp f)
{
    int poz = 1;
    TLista p , ant = NULL;
    //categorie vida
    if (v[nr] == NULL) {
        ins_first(&(v[nr]), el);
        return 1;
    }
    else {
        for (p = v[nr]; p != NULL; ant = p, p = p->urm) {
            poz++;
            //ins inceput de lista
            if (f(p->info, el) == 0 && p == v[nr]) {
                ins_first(v + nr, el);
                return 1;
            }
            //ins dupa ant
            else if (f(p->info, el) == 0 ){
                ins_after(ant, el);
                poz--;
                return poz;
            }
            //ins final
            else if (f(p->info, el) == 1 && p->urm == NULL) {
                ins_after(p, el);
                return poz;
            }
        
        }
    }
    return -1;
}

//afisare nume si rating serial
void afi_serial(void *elem, FILE *fi)
{
    serial *ser = (serial *)elem;

    fprintf(fi, "(%s, %.1f)", ser->nume, ser->rating);

    return;
}

//afisare coada
void af_coada(AQ coada, TAfi f, FILE *fi)
{   
    //afisez serialele din coada
    AQ copie = InitQ();
    if (copie == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }

    fprintf(fi, "[");

    while (coada->ic != NULL && coada->sc != NULL) {
        void *extr = ExtrQ(coada);
        IntrQ((void *)copie, extr);
        f(extr, fi);
        if (coada->ic) {
            fprintf(fi, ", ");
        }
    }

    fprintf(fi,"].\n");

    //refac coada
    while (copie->ic != NULL && copie->sc != NULL) {
        void *extr = ExtrQ(copie);
        IntrQ((void *)coada, extr);
    }
    
}

//afisare stiva
void af_stiva(ASt stiva, TAfi f, FILE *fi)
{
    ASt copie = InitS();
    if (copie == NULL) {
        printf("EROARE ALOCARE STIVA\n");
        exit(-5);
    }
    void *extr;
   
    fprintf(fi, "[");

    while (stiva->vf != NULL) {
        extr = Pop((void *)stiva);
        Push((void *)copie, extr);
        f(extr, fi);
        if (stiva->vf) {
            fprintf(fi, ", ");
        }
    }

    fprintf(fi, "].\n");
    
    while (copie->vf != NULL) {
        extr = Pop((void *)copie);
        Push((void *)stiva, extr);
    }
}

//functie show 
void show (TLista *v, AQ queue, ASt stack, int nr, FILE *f)
{
    if (v) {
        TLista p = v[nr];
        if (nr == 4) {
            fprintf(f, "Categoria top10: [");
        }
        else {
            fprintf(f, "Categoria %d: [", nr);
        }
        
        for (; p != NULL; p = p->urm) {
            fprintf(f, "(%s, %.01f)", ((serial *)(p->info))->nume,
            ((serial *)(p->info))->rating);

            if(p->urm != NULL) {
                fprintf(f,", ");
            }
        }

        fprintf(f, "].\n");
        return;
    }
    
    if (queue) {
        af_coada(queue, afi_serial, f);
    }
    if (stack) {
        af_stiva(stack, afi_serial, f);
    }
}

//functie adaugare sezon
void add_sez(TLista *v, char *name, char *line, FILE *fi, ASt stiva, AQ coada)
{
    int i, j, logic = 0, lo = 0;
    TLista p;

    sezon *nou = (sezon *)malloc(1 * sizeof(sezon));
    if (nou == NULL) {
        printf("EROARE ALOCARE SEZON\n");
        exit(-6);
    }

    strcpy(name, strtok(line, " \n"));
    nou->nre = atoi(strtok(NULL, " /n"));

    nou->episod = InitQ();
    if (nou->episod == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }

    //caut in primele 4 categorii serialul
    for (i = 1; i <= 4; i++) {
        if (v[i] != NULL) {
            for (p = v[i]; p != NULL; p = p->urm) {
                if (strcmp(name, ((serial *)(p->info))->nume) == 0) {
                    logic = 1;
                    //intorduc durata in coada
                    for (j = 0; j < nou->nre; j++) {
                        int *durata = calloc(1, sizeof(int));
                        if (durata == NULL) {
                            printf("EROARE ALOCARE \n");
                            exit(-2);
                        }

                        *durata = atoi(strtok(NULL, " \n"));
                        IntrQ(nou->episod, durata);
                        
                    }
                    IntrQ(((serial *)(p->info))->sezon, nou);
                    ((serial *)(p->info))->nrs++;
                    fprintf(fi, "Serialul %s are un sezon nou.\n", name);
                }
                if (logic == 1) {
                    break;
                }
            }
            if (logic == 1) {
                break;
            }
        }
    }

    //nu gasesc in categorii, caut in watching
    if (logic == 0) {
        void *extr = NULL;
        ASt copie = InitS();
        if (copie == NULL) {
            printf("EROARE ALOCARE STIVA\n");
            exit(-5);
        }
       
       //parcurg stiva si caut serialul
        while (stiva->vf != NULL) {
            extr = Pop((void *)stiva);
            Push((void *)copie, extr);
            
            if (strcmp(name, ((serial *)(extr))->nume) == 0) {
                lo = 1;
                for (j = 0; j < nou->nre; j++) {
                    int *durata = calloc(1, sizeof(int));
                    if (durata == NULL) {
                        printf("EROARE ALOCARE\n");
                        exit(-2);
                    }

                    *durata = atoi(strtok(NULL, " \n"));
                    IntrQ(nou->episod, durata);
                }   

                IntrQ(((serial *)(extr))->sezon, nou);
                ((serial *)(extr))->nrs++;
                fprintf(fi, "Serialul %s are un sezon nou.\n", name); 
                
            }
        }

        //refac stiva
         while (copie->vf != NULL) {
            extr = Pop((void *)copie);
            Push((void *)stiva, extr);
        }
    }

    //nu gasesec in categorii si nici in watching, caut in later
    if (lo == 0) {
        AQ copy = InitQ();
        if (copy == NULL) {
            printf("EROARE ALOCARE COADA\n");
            exit(-4);
        }
        while (coada->ic != NULL && coada->sc != NULL) {
            void *ext = ExtrQ(coada);
            IntrQ((void *)copy, ext);
            if (strcmp(name, ((serial *)(ext))->nume) == 0) {
                lo = 1;
                for (j = 0; j < nou->nre; j++) {
                    int *durata = calloc(1, sizeof(int));
                    if (durata == NULL) {
                        printf("EROARE ALOCARE\n");
                        exit(-2);
                    }

                    *durata = atoi(strtok(NULL, " \n"));
                    IntrQ(nou->episod, durata);
                }   

                IntrQ(((serial *)(ext))->sezon, nou);
                ((serial *)(ext))->nrs++;
                fprintf(fi, "Serialul %s are un sezon nou.\n", name); 
            }
        }

        //refac coada
        while (copy->ic != NULL && copy->sc != NULL) {
            void *ext = ExtrQ(copy);
            IntrQ((void *)coada, ext);
        }
    }
}

//functie refacere categorie top
void refacere_top(TLista *v)
{
    int pas = 1;
    TLista p;
    //actualizez pas
    for (p = *v; p != NULL; p = p->urm) {
        ((serial *)(p->info))->poz = pas;
        pas++;
    }
    //trece limita
    if (pas == 12) {
        sterg_last(v);
    }
}

//adaugare in categoria top10
void add_top (void *el, TLista *v, FILE *fi)
{
    TLista p;
    //categorie vida
    if (v[4] == NULL || ((serial *)el)->poz == 1) {
        ins_first(&(v[4]), el);
    }
    else {
        p = v[4];
        int i;
        for (i = 0; i < ((serial *)el)->poz - 2; i++, p = p->urm);
        ins_after(p, el);
    }

    //refacem topul
    refacere_top(v + 4);

    //afisam serialele din categoria top10
    fprintf(fi, "Categoria top10: [");
    for (p = v[4]; p != NULL; p = p->urm) {
        fprintf(fi, "(%s, %.01f)", ((serial *)(p->info))->nume,
        ((serial *)(p->info))->rating);

        if(p->urm != NULL) {
            fprintf(fi, ", ");
        }
    }

    fprintf(fi, "].\n");
}

//functie contor numar de elemente din coada
int el_coada (AQ coada)
{
    AQ copie = InitQ();
    if (copie == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }

    //se contorizeaza numarul de elemente din coada
    int contor = 0;
    while (coada->ic != NULL && coada->sc != NULL) {
        void *extr = ExtrQ(coada);
        IntrQ((void *)copie, extr);
        contor++;
    }

    //se reface coada
    while (copie->ic != NULL && copie->sc != NULL) {
        void *extr = ExtrQ(copie);
        IntrQ((void *)coada, extr);
    }
    return contor;
}

//functie adaugare in coada later
void add_later(AQ later, TLista *v, char *name, TFcmp f, FILE *fi)
{
    TLista p, ant = NULL;
    int i, cat = 0, logic = 0, poz = el_coada(later) + 1;
    void *extr = NULL;
    //caut serial prin categorii si retin categoria
    for (i = 1; i <= 4; i++) {
        if (v[i] != NULL) {
            ant = NULL;
            for (p = v[i]; p != NULL; ant = p, p = p->urm) {
                if (strcmp(name, ((serial *)(p->info))->nume) == 0) {
                    extr = p->info;
                    cat = i;
                    logic = 1;

                    //introduc serialul in coada si il sterg din lista
                    IntrQ((void *)later, extr);
                   
                    if (ant != NULL) {
                        sterg_after(ant);
                    }
                    else {
                        sterg_first(v +  cat);
                    }
                     
                    break;
                }
            }
            if (logic == 1) {
                break;
            }
        }
    }

    //daca se modifica categoria top10 se reface
    if (cat == 4) {
        refacere_top(v);
    }

    fprintf(fi, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
    ((serial *)(extr))->nume, poz);

}

//cautare in coada si adaugare in stiva
void *search(AQ coada, char *nume, ASt watching)
{
    void *extr = NULL, *caut = NULL;
    AQ copie = InitQ();
    if (copie == NULL) {
        printf("EROARE ALOCARE COADA\n");
        exit(-4);
    }
    
    //se cauta in coada si se introduce in stiva elementul
    while (coada->ic != NULL && coada->sc != NULL) {
        void *extr = ExtrQ(coada);
        
        if (strcmp(nume, ((serial *)(extr))->nume) == 0) {
            Push((void *)watching, extr);
            caut = extr;
        }
        //daca nu este elementul cautat se introduce in copie
        else {
            IntrQ((void *)copie, extr);
        }
        
    }
    
    //refacem coada
    while (copie->ic != NULL && copie->sc != NULL) {
        extr = ExtrQ(copie);
        IntrQ((void *)coada, extr);
    }

    return caut;
}

//functie gestionare stiva watch si history
void watch(TLista *v, char *nume, AQ later, ASt history, ASt watching, int d, FILE *fi)
{
    TLista p, ant = NULL;
    AQ aux;
    ASt copie;
    aux = InitQ();
    if (aux == NULL) {
        printf("EROARE DE ALOCARE COADA\n");
        exit(-4);
    }

    copie = InitS();
    if (copie == NULL) {
        printf("EROARE DE ALOCARE STIVA\n");
        exit(-5);
    }

    void *extr = NULL, *caut = NULL, *dur;
    int i, logic = 0, cat = 0, durata = 0, late = 0;
    int *dif = calloc(1, sizeof(int));
    if (dif == NULL) {
        printf("EROARE DE ALOCARE\n");
        exit(-2);
    }

    //parcurg categoriile, verific daca se gaseste serialul si retin cat
    for (i = 1; i <= 4; i++) {
        if (v[i] != NULL) {
            ant = NULL;
            for (p = v[i]; p != NULL; ant = p, p = p->urm) {
                 if (strcmp(nume, ((serial *)(p->info))->nume) == 0) {
                    cat = i;
                    logic = 1;
                    Push((void *)watching, p->info);
                    caut = (p->info);
                    if (ant != NULL) {
                        sterg_after(ant);
                    }
                    else {
                        sterg_first(v +  cat);
                    } 
                    break;
                }
            }

            if (logic == 1) {
                break;
            }
        }
    }

    //caut in coada later
    if (!caut) {
        caut = search(later, nume, watching);
    }
   
    if (caut != NULL) {
        late = 1;
    }

    //caut in watching
    if (logic == 0 && late == 0) {
        //parcurg stiva, daca gasesc el ul retin in caut, altfel il adaug in stiva copie
  
        while (watching->vf != NULL) {
            extr = Pop((void *)watching);
            
            if (strcmp(nume, ((serial *)(extr))->nume) == 0) {
                caut = extr;
            }
            else {
                Push((void *)copie, extr);
            }
        }
        
        //refacere stiva
        while (copie->vf != NULL) {
            extr = Pop((void *)copie);
            Push((void *)watching, extr);
        }
        //adaugare el in varful stivei
        Push((void *)watching, caut);
    }

    //parcurg coada de sezoane 
    while (((serial *)caut)->sezon->ic != NULL &&
    ((serial *)caut)->sezon->sc != NULL) {
        
        extr = ExtrQ(((serial *)caut)->sezon);

        //parcurg coada de episoade
        while (((sezon *)extr)->episod->ic != NULL && 
        ((sezon *)extr)->episod->sc != NULL) {
            dur = ExtrQ(((sezon *)extr)->episod);
            logic = 0;
            durata = *((int *)dur);

            //nu e timp sa vad tot episodul
            if (durata > d) {
                *(dif) = durata - d;
                durata = durata - *dif;
                logic = 1;
                IntrQ((void *)(((sezon *)extr)->episod), (void *)dif);
                break;
            }

            //este timp sa vad tot, scad din durata
            else {
                d = d - durata;
                if (d == 0) { 
                    break;
                }
            }
        }
        
        //nu s-a terminat sezonul
        if (((sezon *)extr)->episod->ic != NULL && 
        ((sezon *)extr)->episod->sc != NULL) {
            IntrQ(((serial *)caut)->sezon, extr);
        }
 
        if (logic == 1) {
            break;
        }
        
        //s-a terminat serialul, il adaug in istoric si il scot din watching
        if (((serial *)caut)->sezon->ic == NULL &&
        ((serial *)caut)->sezon->sc == NULL) {
            fprintf(fi, "Serialul %s a fost vizionat integral.\n",
            ((serial *)caut)->nume);

            Pop((void *)watching);
            Push((void *)history, caut);
        }

        if (d == 0) {
            break;
        }
    }    
}

int main(int argc, char *argv[])
{
    //vector de categorii
    TLista *v;
    v = (TLista *)calloc(10, sizeof(TLista));

    //coada later
    AQ later = InitQ();
    if (later == NULL) {
        printf("EROARE DE ALOCARE COADA\n");
        exit(-4);
    }
    //stiva watching
    ASt watching = InitS();
    if (watching == NULL) {
        printf("EROARE DE ALOCARE STIVA\n");
        exit(-5);
    }
    //stiva history
    ASt history = InitS();
    if (history == NULL) {
        printf("EROARE DE ALOCARE STIVA\n");
        exit(-5);
    }

    FILE *fp, *gp;
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("EROARE DESCHIDERE FISIER\n");
        exit(-1);
    }

    gp = fopen(argv[2], "wt");
    if (gp == NULL) {
        printf("EROARE DESCHIDERE FISIER\n");
        exit(-1);
    }

    char *line = calloc(150, sizeof(char));
    if (line == NULL) {
        printf("EROARE DE ALOCARE\n");
        exit(-2);
    }
    
    while (fgets(line, 150, fp) != NULL) {
        char *comanda = calloc(10, sizeof(char));
        if (comanda == NULL) {
            printf("EROARE DE ALOCARE\n");
            exit(-2);
        }
        sscanf(line, "%s", comanda);
        int read_ch = strlen(comanda) + 1;
        if(!comanda) {
            break;
        }
        if (strcmp(comanda, "add") == 0) {
            serial *s = aloc_serial(line + read_ch);
            if (s == NULL) {
                printf("EROARE DE ALOCARE SERIAL\n");
                exit(-3);
            }
            int poz;
            poz = add_serial((void *)s, v, s->ID, cmp);
            fprintf(gp, "Serialul %s a fost adaugat la pozitia %d.\n", 
            s->nume, poz);
        }
        else if (strcmp(comanda, "show") == 0) {
            char *ind = calloc(10, sizeof(char));
            if (ind == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            sscanf(line + read_ch, "%s", ind);
            if (strcmp(ind , "top10") == 0) {
                show(v, NULL, NULL, 4, gp);
            }
            else if (strcmp(ind, "later") == 0) {
                fprintf(gp, "Categoria later: ");
                show(NULL, later, NULL, 5, gp);
            }
            else if (strcmp(ind, "watching") == 0) {
                fprintf(gp, "Categoria watching: ");
                show(NULL, NULL, watching, 6, gp);
            }
            else if (strcmp(ind, "history") == 0) {
                fprintf(gp, "Categoria history: ");
                show(NULL, NULL, history, 6, gp);
            }
            else {
                int index = atoi(ind);
                show(v, NULL, NULL, index, gp);
            }
        }
        else if (strcmp(comanda, "add_sez") ==  0) {
            char *name = (char *)malloc(33 * sizeof(char));
            if (name == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            add_sez(v, name, line + read_ch, gp, watching, later);
    
        }
        else if (strcmp(comanda, "add_top") == 0) {
            serial *s = aloc_serial(line + read_ch);
            if (s == NULL) {
                printf("EROARE DE ALOCARE SERIAL\n");
                exit(-3);
            }
            s->poz = s->ID;
            s->ID = 4;
            add_top((void *)s, v, gp);
        }
        else if (strcmp(comanda, "later") == 0) {
            char *name = calloc(33, sizeof(char));
            if (name == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            sscanf(line + read_ch, "%s", name);
            add_later(later, v, name, cmp, gp); 
        }
        else {
            char *name = calloc(33, sizeof(char));
            if (name == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            sscanf(line + read_ch, "%s", name);
            char *dur = calloc(4, sizeof(char));
            if (dur == NULL) {
                printf("EROARE DE ALOCARE\n");
                exit(-2);
            }
            
            read_ch = read_ch + strlen(name) + 1;
            sscanf(line + read_ch, "%s", dur);
            int d = atoi(dur);

            watch(v, name, later, history, watching, d, gp);
            
        }
    }

    free(line);
    fclose(fp);
    fclose(gp);

    return 0;
}

