/* STOICA Liviu-Gabriel - 311CB */
#ifndef FUNCTII_H
#define FUNCTII_H
#include <stdio.h>

typedef struct nod {
    char *data;
    struct nod* urm[27];
} Arb;

typedef struct celula {
  Arb *info;
  struct celula* urm;
  struct celula *prev;
} TCelula, *TLista;

typedef struct coada {
  TLista sf, inc;
} TCoada;

TCoada* InitQ();
int IntrQ(TCoada*, Arb*);
Arb* ExtrQ(TCoada*);
void DistrQ(TCoada**);

Arb* init();
int intrSuf(Arb*, char*);
void parcLatime(Arb*);
void DistrArb(Arb**);
void compresieArb(Arb*);
int nrNoduriFrunze(Arb*);
int nrSufixe(Arb*, int);
int nrMaxDescendenti(Arb*);
int cautSufArbFull(Arb*, char*);

#endif