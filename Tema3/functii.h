/* STOICA Liviu-Gabriel - 311CB */
#ifndef FUNCTII_H
#define FUNCTII_H
#include <stdio.h>

typedef struct celarc
{ int d;           /* destinatie arc */
  int c;            /* cost arc */
  float *uz;       /* vector uzuri */
  int n;           /* numar uzuri */
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
  char **nume; /* nume noduri */
} TGL;

typedef struct
{
    AArc arcSalvat; /* pointer arc salvat */
    int parinte; /* index parinte */
    int costDrum; /* cost drum */
} ArcExtras;

TGL* CitGraf(FILE*, int);  /* citeste descriere graf, conform cerinta 1 */
void DistrG(TGL** ag); /* distruge graf -> punctaj valgrind */
TGL* AlocG(int nr); /* aloca memorie pentru un graf */
TGL* CitGraf2(FILE*);  /* citeste descriere graf, conform cerinta 2 */

// Cerinta 1
TGL* timpuTrece(TGL *x, int an);
void cerinta1(TGL *g, FILE *out);

// Cerinta 2
void AfiCer2(FILE *out, TGL *x, ArcExtras *data, int nrMax);
ArcExtras* algDijkstra(TGL *G, int nod);

#endif
