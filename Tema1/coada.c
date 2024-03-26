/* STOICA Liviu-Gabriel - 311CB */
#include "functii.h"
#include <stdio.h>
#include <stdlib.h>

TLista alocCel(char x) {
    TLista cel = (TLista) malloc(sizeof(TCelula));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = x;
    return cel;
}

TCoada* InitQ() {
    TCoada *coada = (TCoada*) malloc(sizeof(TCoada));
    if ( !coada ) return NULL;
    coada->inc = coada->sf = NULL;
    return coada;
}

int IntrQ(TCoada *c, char x) {
    TLista aux = alocCel(x);
    if ( !aux ) return 1;
    if ( c->inc == NULL ) {
        c->inc = c->sf = aux;
    } else {
        aux->prev = c->sf;
        c->sf->urm = aux;
        c->sf = aux;
        // c->sf->urm = aux;
        // aux->prev = c->sf;
        // c->sf = aux;
    }
    return 0;
}

char ExtrQ(TCoada *c) {
    if ( c->inc ) {
        TLista aux = c->inc;
        char data = c->inc->info;
        if ( c->inc->urm ) {
            c->inc->urm->prev = NULL;
            c->inc = c->inc->urm;
        } else {
            c->inc = c->sf = NULL;
        }
        free(aux);
        return data;
    }
    return -1;
}

void afisQ(TCoada *c) {
    printf("Coada este: ");
    TLista aux = c->inc;
    while ( aux ) {
        printf("%c ", aux->info);
        aux = aux->urm;
    }
    printf("\n");
}

void DistrQ(TCoada **c) {
  if ( !(*c)->sf ) return; 
  for ( TLista aux = (*c)->inc  ; aux != NULL ; ) {
    TLista aux2 = aux;
    aux = aux->urm;
    free(aux2);
  }
  free(*c);
}

void swapCoada(TCoada *c) {
    // afisQ(c);
    for ( TLista aux = c->sf ; aux != NULL ; aux = aux->urm ) {
        TLista aux2 = aux->prev;
        aux->prev = aux->urm;
        aux->urm = aux2;
        // printf("aux->info: %c\n", aux->info);
    }
    TLista aux = c->inc;
    c->inc = c->sf;
    c->sf = aux;
    // afisQ(c);
}