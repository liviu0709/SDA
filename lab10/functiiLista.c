#include "lista.h"
#include <string.h>

/* Aloca un element de tip Celula si returneaza pointerul aferent */
TLista AlocCelula(int elem) {
    TLista aux = (TLista) malloc(sizeof(TCelula));   /* alocare */
    if (aux) {                                    /* aux != NULL */
        aux->info = elem;
        aux->urm = NULL;
    }
    return aux;                                   /* returnare adresa sau NULL */
}

/* Citeste de la tastatura numere de adaugat in lista */
TLista CitireLista(int *dimLista) {
    TLista L = NULL, aux, ultim;
    int x;
    char ch;
    *dimLista = 0;

    printf("Introduceti numerele de adaugat in lista:\n");
    while (scanf("%i", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */

        aux = AlocCelula(x);
        if (!aux) {                  /* aux == NULL, !aux != NULL */
            return L;
        }

        if (L == NULL) {             /* initializare cap de lista */
            L = aux;
        } else {                     /* adaugare celula la final de lista */
            ultim->urm = aux;
        }

        ultim = aux;                 /* pointerul pentru ultima celula este actualizat */
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareLista(TLista L) {
    printf("Lista: [");
    while (L) {                   /* L != NULL */
        printf("%d ", L->info);
        L = L->urm;
    }
    printf("]\n");
}

/* Dezalocare memorie lista */
void DistrugeLista(TLista* aL) {
    TLista aux;
    while (*aL) {           /* *aL != NULL, dereferentiere adresa aL */
        aux = *aL;
        *aL = (*aL)->urm;
        free(aux);
    }
}

/* Aloca un element de tip Celula si returneaza pointerul aferent */
TListaR AlocCelulaR(double elem) {
    TListaR aux = (TListaR) malloc(sizeof(TCelulaR));   /* alocare */
    if (aux) {                                    /* aux != NULL */
        aux->info = elem;
        aux->urm = NULL;
    }
    return aux;                                   /* returnare adresa sau NULL */
}

/* Citeste de la tastatura numere de adaugat in lista */
TListaR CitireListaR(int *dimLista) {
    TListaR L = NULL, aux, ultim;
    double x;
    char ch;
    *dimLista = 0;

    printf("Introduceti numerele REALE de adaugat in lista:\n");
    while (scanf("%lf", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */

        aux = AlocCelulaR(x);
        if (!aux) {                  /* aux == NULL, !aux != NULL */
            return L;
        }

        if (L == NULL) {             /* initializare cap de lista */
            L = aux;
        } else {                     /* adaugare celula la final de lista */
            ultim->urm = aux;
        }

        ultim = aux;                 /* pointerul pentru ultima celula este actualizat */
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareListaR(TListaR L) {
    printf("Lista reala: [");
    while (L) {                   /* L != NULL */
        printf("%lf ", L->info);
        L = L->urm;
    }
    printf("]\n");
}

/* Dezalocare memorie lista */
void DistrugeListaR(TListaR* aL) {
    TListaR aux;
    while (*aL) {           /* *aL != NULL, dereferentiere adresa aL */
        aux = *aL;
        *aL = (*aL)->urm;
        free(aux);
    }
}

TListaN AlocCelulaN(Om elem) {
    TListaN aux = (TListaN) malloc(sizeof(TCelulaN));   /* alocare */
    if (aux) {                                    /* aux != NULL */
        aux->info = elem;
        aux->urm = NULL;
    }
    return aux;                                   /* returnare adresa sau NULL */
}

/* Citeste de la tastatura numere de adaugat in lista */
TListaN CitireListaN(int *dimLista) {
    TListaN L = NULL, aux, ultim;
    char ch;
    *dimLista = 0;

    printf("Introduceti oamenii de adaugat in lista:\n");
    int citesc = 1;
    while (citesc) {   /* se citesc oameni pana cand se citeste -1 */
        Om x;
        x.nume = (char*) malloc(100 * sizeof(char));
        x.prenume = (char*) malloc(100 * sizeof(char));
        printf("Nume: ");
        scanf("%s", x.nume);
        if ( x.nume[0] == '-' && x.nume[1] == '1' ) {
            free(x.nume);
            break;
        }
        x.nume = realloc(x.nume, (strlen(x.nume) + 1) * sizeof(char));
        printf("Prenume: ");
        scanf("%s", x.prenume);
        x.prenume = realloc(x.prenume, (strlen(x.prenume) + 1) * sizeof(char));
        printf("Varsta: ");
        scanf("%d", &x.varsta);
        aux = AlocCelulaN(x);
        if (!aux) {                  /* aux == NULL, !aux != NULL */
            return L;
        }

        if (L == NULL) {             /* initializare cap de lista */
            L = aux;
        } else {                     /* adaugare celula la final de lista */
            ultim->urm = aux;
        }

        ultim = aux;                 /* pointerul pentru ultima celula este actualizat */
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareListaN(TListaN L) {
    printf("Lista oameni: [");
    while (L) {                   /* L != NULL */
        printf("(%s %s %d) ", L->info.nume, L->info.prenume, L->info.varsta);
        L = L->urm;
    }
    printf("]\n");
}

/* Dezalocare memorie lista */
void DistrugeListaN(TListaN* aL) {
    TListaN aux;
    while (*aL) {           /* *aL != NULL, dereferentiere adresa aL */
        aux = *aL;
        *aL = (*aL)->urm;
        if ( aux->info.nume ) {
            free(aux->info.nume);
        }
        if ( aux->info.prenume ) {
            free(aux->info.prenume);
        }
        free(aux);
    }
}