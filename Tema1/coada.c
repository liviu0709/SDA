/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

// Functie de baza pentru tren
TLista alocCel(char x) {
    TLista cel = (TLista) malloc(sizeof(TCelula));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = x;
    return cel;
}

// Celula de baza pentru cozi
TListaStr alocCelStr(char *x) {
    TListaStr cel = (TListaStr) malloc(sizeof(TCelulaStr));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = malloc( (strlen(x) + 1) * sizeof(char) );
    if ( !cel->info ) {
        free(cel);
        return NULL;
    }
    strcpy(cel->info, x);
    return cel;
}

TCoada* InitQ() {
    TCoada *coada = malloc(sizeof(TCoada));
    if ( !coada ) return NULL;
    coada->inc = coada->sf = NULL;
    return coada;
}

int IntrQ(TCoada *c, char *x) {
    TListaStr aux = alocCelStr(x);
    if ( !aux ) return 1;
    if ( c->inc == NULL ) {
        c->inc = c->sf = aux;
    } else {
        aux->prev = c->sf;
        c->sf->urm = aux;
        c->sf = aux;
    }
    return 0;
}


// Datele returnate trb dezalocate dupa utilizare
char* ExtrQ(TCoada *c) {
    if ( c->inc ) {
        // Alocam memorie pentru sirul returnat
        char *data = malloc(sizeof(char) * (strlen(c->inc->info) + 1));
        if ( !data ) return NULL;
        TListaStr aux = c->inc;
        strcpy(data, c->inc->info);
        // Eliberam memoria din stiva
        free(c->inc->info);
        if ( c->inc->urm ) {
            c->inc->urm->prev = NULL;
            c->inc = c->inc->urm;
        } else {
            c->inc = c->sf = NULL;
        }
        free(aux);
        return data;
    }
    return NULL;
}

// Trb punctaj la valgrind deci...
void DistrQ(TCoada **c) {
    TListaStr aux = (*c)->inc;
    for ( aux = (*c)->inc  ; aux != NULL ; ) {
        TListaStr aux2 = aux;
        aux = aux->urm;
        if ( aux2->info != NULL )
            free(aux2->info);
        free(aux2);
    }
    free(*c);
}

// Apelata pentru fiecare coada cand este citita
// Comanda SWAP
void swapCoada(TCoada *c) {
    // Inversam directia de parcurgere a cozii
    TListaStr aux = c->sf;
    for ( aux = c->sf ; aux != NULL ; aux = aux->urm ) {
        TListaStr aux2 = aux->prev;
        aux->prev = aux->urm;
        aux->urm = aux2;
    }
    // Inversam capetele cozii
    aux = c->inc;
    c->inc = c->sf;
    c->sf = aux;
}

