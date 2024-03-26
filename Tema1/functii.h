/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>



typedef struct celula
{ 
  char info;
  struct celula* urm;
  struct celula *prev;
} TCelula, *TLista;

typedef struct coada
{ 
  TLista sf, inc;
} TCoada;

typedef struct tren
{
    TLista santinela;
    TLista mecanic;
} Tren;

TLista alocCel(char);

char ExtrQ(TCoada*);
void afisQ(TCoada*);
int IntrQ(TCoada*, char);
TCoada* InitQ();
void DistrQ(TCoada**);
void swapCoada(TCoada*);

Tren* alocTren();
void afisTren(Tren*, FILE*);
void moveLeft(Tren*);
int moveRight(Tren*);
void writeC(char, Tren*);
void clearCell(Tren*);
void distrTren(Tren**);
void clearAll(Tren**);
void insertRight(Tren*, char);
void insertLeft(Tren*, char, FILE*);