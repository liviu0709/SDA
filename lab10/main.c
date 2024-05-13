#include "lista.h"

// citire nr reale

// citire nume prenume varsta

int main(){
    int lg = 0;
    TListaN L = NULL;

    L = CitireListaN(&lg);
    printf("Dimensiune lista: %d\n", lg);
    AfisareListaN(L);

    DistrugeListaN(&L);
    return 0;
}