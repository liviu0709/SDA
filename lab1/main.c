#include "lista.h"

int main(){
    int lg = 0;
    TLista L = NULL;

    L = CitireLista(&lg);
    printf("Dimensiune lista: %d\n", lg);
    AfisareLista(task2(L));

    DistrugeLista(&L);
    return 0;
}