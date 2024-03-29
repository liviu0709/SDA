/* STOICA Liviu-Gabriel - 311CB */
#include "functii.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TLista alocCel(char x) {
    TLista cel = (TLista) malloc(sizeof(TCelula));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = x;
    return cel;
}

TListaStr alocCelStr(char *x) {
    TListaStr cel = (TListaStr) malloc(sizeof(TCelulaStr));
    if ( !cel ) return NULL;
    cel->prev = NULL;
    cel->urm = NULL;
    cel->info = malloc( (strlen(x) + 1) * sizeof(char) );
    strcpy(cel->info, x);
    return cel;
}

TCoada* InitQ() {
    TCoada *coada = (TCoada*) malloc(sizeof(TCoada));
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
        // c->sf->urm = aux;
        // aux->prev = c->sf;
        // c->sf = aux;
    }
    return 0;
}


// Datele returnate trb dezalocate dupa utilizare
char* ExtrQ(TCoada *c) {
    if ( c->inc ) {
        char *data = malloc(sizeof(char) * (strlen(c->inc->info) + 1));
        TListaStr aux = c->inc;
        strcpy(data, c->inc->info);
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


void afisQ(TCoada *c) {
    printf("Coada este: ");
    TListaStr aux = c->inc;
    while ( aux ) {
        printf("%s ", aux->info);
        aux = aux->urm;
    }
    printf("\n");
}


void DistrQ(TCoada **c) {
  // if ( !(*c)->sf ) return; 
  for ( TListaStr aux = (*c)->inc  ; aux != NULL ; ) {
    TListaStr aux2 = aux;
    aux = aux->urm;
    if( aux2->info != NULL ) free(aux2->info);
    free(aux2);
  }
  free(*c);
}


void swapCoada(TCoada *c) {
    // afisQ(c);
    for ( TListaStr aux = c->sf ; aux != NULL ; aux = aux->urm ) {
        TListaStr aux2 = aux->prev;
        aux->prev = aux->urm;
        aux->urm = aux2;
        // printf("aux->info: %c\n", aux->info);
    }
    TListaStr aux = c->inc;
    c->inc = c->sf;
    c->sf = aux;
    // afisQ(c);
}

