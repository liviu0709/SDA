#include <stdio.h>
#include <stdlib.h>

/* Test lista vida */
#define ListaVida(L) (L == NULL)

typedef struct Celula{
    int info;
    struct Celula *urm;
} TCelula, *TLista;
/* TCelula este un o variabila care retine 'info' si 'urm'
   TLista este un pointer catre tipul TCelula
*/

TLista AlocCelula(int elem);
TLista CitireLista(int *dimLista);
void AfisareLista(TLista L);
void DistrugeLista(TLista* aL);

typedef struct CelulaR{
    double info;
    struct CelulaR *urm;
} TCelulaR, *TListaR;
/* TCelula este un o variabila care retine 'info' si 'urm'
   TLista este un pointer catre tipul TCelula
*/

TListaR AlocCelulaR(double elem);
TListaR CitireListaR(int *dimLista);
void AfisareListaR(TListaR L);
void DistrugeListaR(TListaR* aL);

typedef struct {
    char *nume;
    char *prenume;
    int varsta;
} Om;

typedef struct CelulaN{
    Om info;
    struct CelulaN *urm;
} TCelulaN, *TListaN;
/* TCelula este un o variabila care retine 'info' si 'urm'
   TLista este un pointer catre tipul TCelula
*/

TListaN AlocCelulaN(Om elem);
TListaN CitireListaN(int *dimLista);
void AfisareListaN(TListaN L);
void DistrugeListaN(TListaN* aL);