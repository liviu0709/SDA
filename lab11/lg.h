#include <stdio.h>
#include <stdlib.h>

typedef struct celulag {
    void *info;
    struct celulag *urm;
}TCelulaG, *TLG;

typedef struct {
    char *nume;
    char *prenume;
    int varsta;
} TCelOm, *Om;
/* La fel ca in laboratorul 1, numai ca retinem 'void*' in loc de 'int' */

TLG AlocCelulaG(void *elem);
int InserareLG(TLG* aL, void *elem);
TLG CitireLG(int *dimLista);
void AfisareLG(TLG L, void (*afisareElem)(void *));
void DistrugeLG(TLG* aL, void (*stergeElem)(void *));

TLG CitireReala(int *dimLista, int (*fcmp)(void*, void*));
int cmpReal(void*, void*);
int cmpOm(void*, void*);
TLG CitireOm(int *dimLista, int (*fcmp)(void*, void*));