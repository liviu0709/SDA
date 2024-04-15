/* STOICA Liviu-Gabriel - 311CB */
#ifndef FUNCTII_H
#define FUNCTII_H
#include <stdio.h>

typedef struct nod {
    char *data;
    struct nod* urm[27];
} Arb;

Arb* init();

int intrSuf(Arb*, char *);
void parcLatime(Arb*);

#endif