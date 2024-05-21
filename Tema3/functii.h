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
TGL* Copy(TGL *);
AArc getArc(TGL *g, char* src, char* dst, int* nodS);
void AfiGrafL(TGL *); /* afisare liste de adiacente */
void DistrG(TGL** ag);

TGL* CitGraf2(FILE*);  /* citeste descriere graf, conform cerinta 2 */
void AfiGrafL2(TGL *);

#endif
