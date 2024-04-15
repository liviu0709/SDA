/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"


// Celula de baza pentru cozi
TLista alocCel(Arb *x) {
    TLista cel = (TLista) malloc(sizeof(TCelula));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = x;
    return cel;
}

TCoada* InitQ() {
    TCoada *coada = malloc(sizeof(TCoada));
    if ( !coada ) return NULL;
    coada->inc = coada->sf = NULL;
    return coada;
}

int IntrQ(TCoada *c, Arb *x) {
    TLista aux = alocCel(x);
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
Arb* ExtrQ(TCoada *c) {
    if ( c->inc ) {
        // Alocam memorie pentru sirul returnat
        // char *data = malloc(sizeof(Arb));
        // if ( !data ) return NULL;
        TLista aux = c->inc;

        Arb* data = c->inc->info;
        // Eliberam memoria din stiva
        // free(c->inc->info);
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
    TLista aux = (*c)->inc;
    for ( aux = (*c)->inc  ; aux != NULL ; ) {
        TLista aux2 = aux;
        aux = aux->urm;
        if ( aux2->info != NULL )
            free(aux2->info);
        free(aux2);
    }
    free(*c);
}
