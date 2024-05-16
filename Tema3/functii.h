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

TGL* CitGraf(FILE*, int);  /* citeste descriere graf */
TGL* Copy(TGL *);
void AfiGrafL(TGL *); /* afisare liste de adiacente */
void DistrG(TGL** ag);

#endif
