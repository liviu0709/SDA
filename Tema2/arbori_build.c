/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

Arb* init() {
    Arb *x = malloc(sizeof(Arb));
    x->data = NULL;
    int i;
    for ( i = 0 ; i < 27 ; i++ )
        x->urm[i] = NULL;
    return x;
}

int intrSuf(Arb *x, char *sir) {
    // Daca sir[0] == '$', lasam asa
    int indice = 0;
    if ( sir[0] != '$') {
        indice = sir[0] - 96;
        // printf("Sirul este: %s\n", sir);
        // printf("Hai ca merge daca e \n");
    }
    if ( x->urm[indice] == NULL ) {
        x->urm[indice] = init();
        char *sirFirstElem = malloc(2 * sizeof(char));
        strncpy(sirFirstElem, sir, 1);
        sirFirstElem[1] = '\0';
        x->urm[indice]->data = sirFirstElem;
        // printf("Am adaugat: %s\n", x->urm[indice]->data);
    }
    if ( strlen(sir) > 1 ) {
        intrSuf(x->urm[indice], sir + 1);
    }
    return 0;
}

void parcLatime(Arb *x) {
    if ( !x )
        return;
    TCoada *noduri = InitQ();
    IntrQ(noduri, x);
    // Pentru delimitarea nivelelor folosim NULL
    IntrQ(noduri, NULL);
    while ( noduri->inc ) {
        Arb *nodCrt = ExtrQ(noduri);
        // Daca am gasit un alt nivel
        if ( nodCrt == NULL ) {
            printf("\n");
            // Daca mai avem alte noduri in coada
            // introducem NULL pentru delimitare...
            if ( noduri->inc )
                IntrQ(noduri, NULL);
        } else {
            // Altfel, am extras din coada un simplu nod
            if ( nodCrt != x )
                printf("%s ", nodCrt->data);
            int i;
            for ( i = 0 ; i < 27 ; i++ ) {
                if ( nodCrt->urm[i] )
                    IntrQ(noduri, nodCrt->urm[i]);
            }
        }
    }
    DistrQ(&noduri);

}

int nrFii(Arb *x) {
    int cnt = 0, i;
    for ( i = 0 ; i < 27 ; i++ )
        if ( x->urm[i] )
            cnt++;
    return cnt;
}

// Functie apelata doar la noduri cu 1 fiu
Arb* getUrm(Arb *x) {
    int i;
    for ( i = 0 ; i < 27 ; i++ )
        if ( x->urm[i] )
            return x->urm[i];
    return NULL;
}

void DistrNod(Arb *x) {
    if ( x->data )
        free(x->data);
    free(x);
}

void compresieArb(Arb *x) {
    int i;
    // Este posibila compresia !
    while ( nrFii(x) == 1 ) {
        Arb *aux = getUrm(x);
        // Conform cerinta, caracterul '$' trb sa fie separat in arborele de sufixe
        // astfel ca, nu e voie sa il compresam cu restul
        if ( aux->data[0] == '$' )
            break;
        x->data = realloc(x->data, (strlen(x->data) + 2 + strlen(aux->data)) * sizeof(char) );
        strcat(x->data, aux->data);
        for ( i = 0 ; i < 27 ; i++ )
            x->urm[i] = aux->urm[i];
        DistrNod(aux);
    }
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] )
            compresieArb(x->urm[i]);
    }
}

void DistrArb( Arb **x ) {
    if ( *x )  {
        int i;
        if ( (*x)->data )
            free((*x)->data);
        for ( i = 0 ; i < 27 ; i++)
            if ( (*x)->urm[i] )
                DistrArb( &(*x)->urm[i] );
        free(*x);
    }
}