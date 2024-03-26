/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>



typedef struct celula
{ 
  char info;
  struct celula* urm;
  struct celula *prev;
} TCelula, *TLista;

typedef struct celulaStr
{ 
  char *info;
  struct celulaStr* urm;
  struct celulaStr *prev;
} TCelula2, *TLista2;

typedef struct coada
{ 
  TLista sf, inc;
} TCoada;

typedef struct coada2
{ 
  TLista2 sf, inc;
} TCoada2;

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
void search(Tren*, char*, FILE*);

TLista2 alocCelStr(char*);
int IntrQStr(TCoada2*, char*);
void afisQStr(TCoada2*);
void DistrQStr(TCoada2**);
char* ExtrQStr(TCoada2*);
TCoada2* InitQStr();
void swapCoada2(TCoada2*);