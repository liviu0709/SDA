#include "lista.h"

int task1(TLista L) {
    int i = 1, cnt = 0;
    for ( TLista aux = L ; aux->urm != NULL; aux = aux->urm, i++ ) {
        if ( aux->info % 2 == aux->urm->info % 2 ) {
            printf("(%d, %d): %d, %d\n", i, i + 1, aux->info, aux->urm->info);
            cnt++;
        }
    }
    return cnt;
}

TLista task2(TLista L) {
    TLista final, elNou;
    TLista inceput = final;
    int i = 1, crtSol = 0, maxim = 0;
    // Parcurgem lista
    for ( TLista aux = L ; aux->urm != NULL; aux = aux->urm, i++ ) {
        // Daca elementul curent este mai mic sau egal cu urmatorul si indicele curent este mai mare decat cel anterior
        if ( aux->info <= aux->urm->info && maxim < i ) {
            // Adaug inceputul in lista
            if ( crtSol > 0 ) {
                elNou = AlocCelula(i);
                final->urm = elNou;
                final = elNou;
                crtSol++;
                if ( i > maxim )
                    maxim = i;
            } else {
                inceput = final = AlocCelula(i);
                crtSol++;
            }
            int j = i;
            // Caut finalul secventei
            for ( TLista aux2 = aux ; aux2->urm != NULL; aux2 = aux2->urm, j++ ) {
                if ( aux2->info > aux2->urm->info )
                    break;
            }
            // Adaug finalul secventei in lista
            elNou = AlocCelula(j);
            if ( j > maxim )
                maxim = j;
            final->urm = elNou;
            final = elNou;
            crtSol++;
        }
    }
    return inceput;
}

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