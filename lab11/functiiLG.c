#include "lg.h"
#include <string.h>

/* Aloca un element de tip Celula si returneaza pointerul aferent */
TLG AlocCelulaG(void *elem) {
    TLG aux = (TLG) malloc(sizeof(TCelulaG));
    if (aux) {
        aux->info = elem;
        aux->urm = NULL;
    }
    return aux;
}

/* Inserare elem ordonat*/
int InserareOrd(TLG* al, void *elem, int (*fcmp)(void*, void*)) {
    TLG aux = AlocCelulaG(elem);

    if (!aux) {
        return 0;
    }

    TLG ant = NULL, p = *al;


    while (p && fcmp(p->info, elem) == -1) {
        ant = p;
        p = p->urm;
    }

    if (ant) {
        ant->urm = aux;
    } else {
        *al = aux;
    }

    aux->urm = p;
    return 1;
}

/* Inserare elem la sfarsit de lista */
int InserareLG(TLG* aL, void *elem) {
    TLG p, aux;

    aux = AlocCelulaG(elem);
    if (!aux) {
        return 0;
    }

    if (!(*aL)) {                                   /* initializare cap de lista */
        *aL = aux;
        return 1;
    } else {
        for(p = *aL; p->urm != NULL; p = p->urm);   /* parcurge lista pana in momentul inserarii */
        p->urm = aux;
        return 1;
    }
    return 0;
}

int cmpReal(void *a, void *b) {
    double x = *(double*)a;
    double y = *(double*)b;

    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

TLG CitireReala(int *dimLista, int (*fcmp)(void*, void*)) {
    TLG L = NULL, aux, ultim;
    double x, *elem;

    *dimLista = 0;
    printf("Introduceti elemente de adaugat in lista:\n");
    while (scanf("%lf", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        elem = malloc(sizeof(double));
        *elem = x;

        InserareOrd(&L, elem, fcmp);
        (*dimLista)++;
    }

    return L;

}

int cmpOm(void *a, void *b) {
    TCelOm *x = (TCelOm*)a;
    TCelOm *y = (TCelOm*)b;
    if ( strcmp(x->nume, y->nume) < 0 )
        return -1;
    if ( strcmp(x->nume, y->nume) > 0 )
        return 1;
    if ( strcmp(x->prenume, y->prenume) < 0 )
        return -1;
    if ( strcmp(x->prenume, y->prenume) > 0 )
        return 1;
    if ( x->varsta < y->varsta )
        return -1;
    if ( x->varsta > y->varsta )
        return 1;
    return 0;

}

TLG CitireOm(int *dimLista, int (*fcmp)(void*, void*)) {
    TLG L = NULL, aux, ultim;
    char num[100], pren[100];
    int varsta;
    *dimLista = 0;
    printf("Introduceti elemente de adaugat in lista:\n");
    while (scanf("%d", &varsta) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        TCelOm *elem = malloc(sizeof(TCelOm));
        scanf("%s %s", num, pren);
        elem->nume = malloc(strlen(num) + 1);
        elem->prenume = malloc(strlen(pren) + 1);
        elem->varsta = varsta;
        strcpy(elem->nume, num);
        strcpy(elem->prenume, pren);

        InserareOrd(&L, elem, fcmp);
        (*dimLista)++;
    }

    return L;

}

/* Citeste de la tastatura numere de adaugat in lista */
TLG CitireLG(int *dimLista) {
    TLG L = NULL, aux, ultim;
    int x, *elem;

    *dimLista = 0;
    printf("Introduceti elemente de adaugat in lista:\n");
    while (scanf("%i", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        elem = malloc(sizeof(int));
        *elem = x;

        aux = AlocCelulaG(elem);
        if (!aux) {
            return L;
        }

        if (L == NULL) {
            L = aux;
        } else {
            ultim->urm = aux;
        }

        ultim = aux;
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista, primim un pointer la o functie de printare */
void AfisareLG(TLG L, void (*afisareElem)(void *)) {
    printf("Lista: [");
	while (L) {
        afisareElem(L->info);
        L = L->urm;
    }
	printf("]\n");
}

/* Dezalocare memorie lista, primim un pointer la o functie de dezalocare */
void DistrugeLG(TLG* aL, void (*stergeElem)(void *)) {
    TLG aux;
    while (*aL) {
        aux = *aL;
        *aL = (*aL)->urm;
        stergeElem(aux->info);
        free(aux);
    }
}