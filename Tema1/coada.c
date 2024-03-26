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

TLista2 alocCelStr(char *x) {
    TLista2 cel = (TLista2) malloc(sizeof(TCelula2));
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

TCoada2* InitQStr() {
    TCoada2 *coada = (TCoada2*) malloc(sizeof(TCoada2));
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

int IntrQStr(TCoada2 *c, char *x) {
    TLista2 aux = alocCelStr(x);
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

char* ExtrQStr(TCoada2 *c) {
    if ( c->inc ) {
        TLista2 aux = c->inc;
        char *data = c->inc->info;
        if ( c->inc->urm ) {
            c->inc->urm->prev = NULL;
            c->inc = c->inc->urm;
        } else {
            c->inc = c->sf = NULL;
        }
        // free(aux->info);
        free(aux);
        return data;
    }
    return NULL;
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

void afisQStr(TCoada2 *c) {
    printf("Coada este: ");
    TLista2 aux = c->inc;
    while ( aux ) {
        printf("%s ", aux->info);
        aux = aux->urm;
    }
    printf("\n");
}

void DistrQ(TCoada **c) {
  // if ( !(*c)->sf ) return; 
  for ( TLista aux = (*c)->inc  ; aux != NULL ; ) {
    TLista aux2 = aux;
    aux = aux->urm;
    free(aux2);
  }
  free(*c);
}

void DistrQStr(TCoada2 **c) {
  // if ( !(*c)->sf ) return; 
  for ( TLista2 aux = (*c)->inc  ; aux != NULL ; ) {
    TLista2 aux2 = aux;
    free(aux2->info);
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

void swapCoada2(TCoada2 *c) {
    // afisQ(c);
    for ( TLista2 aux = c->sf ; aux != NULL ; aux = aux->urm ) {
        TLista2 aux2 = aux->prev;
        aux->prev = aux->urm;
        aux->urm = aux2;
        // printf("aux->info: %c\n", aux->info);
    }
    TLista2 aux = c->inc;
    c->inc = c->sf;
    c->sf = aux;
    // afisQ(c);
}