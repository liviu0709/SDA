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

int nrNoduriFrunze(Arb *x) {
    if ( !x )
        return 0;
    if ( nrFii(x) == 0 )
        return 1;
    else {
        int i, cnt = 0;
        for ( i = 0 ; i < 27 ; i++ )
            if ( x->urm[i] )
                cnt += nrNoduriFrunze(x->urm[i]);
        return cnt;
    }
}

int nrSufixe(Arb *x, int k) {
    if ( !x )
        return 0;
    int cnt = 0;
    if ( k == 1 && x->urm[0] )
        cnt++;
    int i;
    for ( i = 1 ; i < 27 ; i++ )
        if ( x->urm[i] )
            cnt += nrSufixe(x->urm[i], k - 1);
    return cnt;
}

int nrMaxDescendenti(Arb *x) {
    int nrDsc = nrFii(x);
    int i;
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] ) {
            int nrCrt = nrMaxDescendenti(x->urm[i]);
            if ( nrCrt > nrDsc )
                nrDsc = nrCrt;
        }
    }
    return nrDsc;
}

int cautSufix(Arb *x, char *s) {
    if ( !x )
        return 0;
    if ( x->data[0] == s[0] ) {
        if ( strlen(s) == 1 )
            return 1;
        int i, cnt = 0;
        for ( i = 0 ; i < 27 ; i++ ) {
            if ( x->urm[i] )
                cnt += cautSufix(x->urm[i], s + 1);
        }
        return cnt;
    }
    return 0;

}

int cautSufArbFull(Arb *x, char *s) {
    if ( !x )
        return 0;
    // Trb sa cautam un sufix care are si final
    // nu unul care e parte din unul mai lung
    strcat(s, "$");
    int cnt = 0;
    for ( int i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] )
            cnt += cautSufix(x->urm[i], s);
    }
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