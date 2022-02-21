DRUGA MARIA-ALEXANDRA
313 CB
TEMA 2 SD

Am organizat functiile de inserare si stergere din lista in fisierul lista.c.
Acestea vor fi apelate atat in cadrul fisierelor coada.c si stiva.c, cat si in
fisierul tema2.c.

FISIER COADA.C
    Contine:
        ->functie de initializare coada
            ~returneaza adresa cozii initializate
        ->functie de introducere in coada(apeleaza inserare la inceput sau dupa)
            ~returneaza 1 pentru succes, 0 altfel
        ->functie de extragere din coada(apeleaza stergere primul element)
            ~returneaza adresa elementului eliminat

FISIER STIVA.C
    Contine:
        ->functir de initializare stiva
            ~returneaza adresa stive initializate
        ->functir de introducere in stiva(apeleaza inserare la inceput)
            ~returneaza 1 pentru succes, 0 altfel
        ->functie de extragere din stiva(apeleaza stergere inceput)
            ~returneaza adreasa elementului eliminat

***CODURI DE EROARE:
        -1 = EROARE DESCHIDERE FISIER
        -2 = EROARE DE ALOCARE
        -3 = EROARE DE ALOCARE SERIAL
        -4 = EROARE DE ALOCARE COADA
        -5 = EROARE DE ALOCARE STIVA
        -6 = EROARE DE ALOCARE SEZON

FISIER TEMA2.C
    Functia MAIN:
        ->deschid fisierele de citire si afisare
        ->variabila line retine intreaga linie  din fisier
        ->verific la ce comanda ma aflu si apelez functia corespunzatoare
    Functia aloc_sezon:
        ->aloca o structura de tip sezon 
        ->intoarce adresa structurii alocate
    Functia aloc_nou:
        ->aloca o structura de tip sezon pentru un sezon nou 
        ->initializeaza fiecare camp cu informatiile citite din line
    Functia aloc_serial:
        ->aloca o structura de tip serial
        ->initializeaza fiecare camp cu informatiile citite din line
    Functia auxiliara cmp:
        ->compara doua elemente de tip void * date ca parametrii
        ->compararea se face descrescator dupa rating si crescator dupa alfabet
        ->functia intoarce 1 daca el1 este primul la ordine sau 2 altfel
    Functia add_serial:
        ->functia adauga un seria nou intr-o categorie precizata de nr
        ->se verifica daca lista categoriei este goala si se face inserare la
        inceput, atlfel se parcurge intreaga lista pana se gaseste elementul
        se incrementeaza pozitita de iniserare si introduce elementul in functie
        de elementul anterior lui: la inceput de lista, dupa ant sau la final
        ->functia returneaza pozitia de inserare
    Functia auxiliara afi_serial:
        ->afiseaza numele si ratingul serialului in fisierul de iesire
    Functia auxiliara afi_coada:
        ->afiseaza serialele din coada in fisierul de iesire
    Functia auxiliara afi_stiva:
        ->afiseaza serialele din stiva in fisierul de iesire
    Functia show:
        ->afiseaza categoria de serial specificata de nr: daca nr=4, se afiseaza
        categoria top10, altfel una din celelalte 3; daca se doreste afisarea
        cozii sau a stivei se apeleaza functiile specifice
    Functia add_sez:
        ->adauga sezon nou unui serial aflat in cele 4 categorii sau in coada
        later sau in stiva watching
        ->mai intai se cauta in primele 4 categorii si se intorduce durata in
        coada de episoade; daca nu s-a gasit serialul, se cauta in stiva
        watching: daca nu s-a gasit nici aici caut in coada later
    Functia auxiliara refacere_top:
        ->functia actualizeaza indicii pentru serialele din top10
        ->se parurge lista si se insereeaza pasul
        ->se verifica daca a fost trecuta limita de 10 seriale
    Functia add_top:
        ->functia adauga serial in top10
        ->indicele 4 din vectorul de categorii reprezinta categoria top10
        ->daca lista este vida sau poz e 1 se insereaza la inceput, altfel dupa
        si se apeleaza functia de refacere_top
        ->se afiseaza serialele din categoria top10
    Functia auxiliara el_coada:
        ->functia numara cate elemente se afla in coada data ca parametru
        ->se parcurge coada si se incrementeaza contor 
        ->se reface coada
    Functia add_later:
        ->functia scoate din cele 4 categorii si adauga serial in coada 
        later
        ->daca s-a modificat top10, apelam functia de refacere top10
    Functia auxiliara search:
        ->cauta elementul in coada, daca il gaseste il scoate si il introduce
        in stiva
        ->se reface coada initiala cu toate elementele, mai putin cu elementul
        sters
        ->functia returneaza elementul cautat
    Functia watch:
        ->functia gestioneaza stiva watch si history
        ->mai intai se parcurg categoriile si se verifica daca elementul se 
        gaseste, caz in care logic devine 1; daca este gasit elementul se
        sterge din lista si se adauga in stiva
        ->daca nu se gaseste in categorii se apeleaza functia search, care
        cauta in coada si adauga in stiva
        ->daca elementul nu s-a gasit inca, se cauta in stiva 
        watching; se parcurge stiva si se retine elementul; apoi refac stiva
        si adaug elementul in varf
        ->dupa ce s-a adaugat serialul in stiva watching, il parcugem si extrag 
        sezon cu sezon, pe care il parcurg, de asemenea; verific daca am timp
        sa il vizionez, iar in caz negativ adaug diferenta in coada si ies din
        instructiunea while, daca, insa, este timp scad din d durata vizionata
        ->daca nu s-a terminat sezonul, acesta este adaugat la loc in coada
        ->daca s-a terminat serialul, atunci il scot din stiva watching si il
        adaug in stiva history