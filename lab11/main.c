#include "lg.h"

int cmp(void* x, void* y) {
    int *a = x;
    int *b = y;
    if ( *a > *b )
        return 1;
    if ( *a == *b )
        return 0;
    return -1;
}

void afisareInt(void *elem) {
    int *aux = elem;
    printf("%d ", *aux);
}

void afisareReala(void *elem) {
    double *aux = elem;
    printf("%lf ", *aux);
}

void afisareOm(void *elem) {
    TCelOm *aux = elem;
    printf("%s %s %d\n", aux->nume, aux->prenume, aux->varsta);
}

int funcCondStersReale(void *elem) {
    // Stergem functiile negative
    double *aux = elem;
    if ( *aux < 0 )
        return 1;
    return 0;
}

int funcCondStersOm(void *elem) {
    // Stergem pers cu varsta mai mica de 18 ani
    TCelOm *aux = elem;
    if ( aux->varsta < 18 )
        return 1;
    return 0;
}

int deleteElems(TLG *L, int (*f)(void*), void (*elib)(void *)) {
    TLG ant = NULL, p = *L;
    while ( p ) {
        if ( f(p->info) ) {
            if ( ant ) {
                ant->urm = p->urm;
                elib(p->info);
                free(p);
                p = ant->urm;
            } else {
                *L = p->urm;
                elib(p->info);
                free(p);
                p = *L;
            }
        } else {
            ant = p;
            p = p->urm;
        }
    }
    return 1;
}

void elibOm(void *elem) {
    TCelOm *aux = elem;
    free(aux->nume);
    free(aux->prenume);
    free(aux);
}

int main() {
    int lg = 0;
    TLG L = NULL;

    L = CitireReala(&lg, cmpReal);
    printf("Dimensiune lista: %d\n", lg);
    AfisareLG(L, afisareReala);
    deleteElems(&L, funcCondStersReale, free);
    AfisareLG(L, afisareReala);
    DistrugeLG(&L, free);
    L = NULL;
    lg = 0;
    getchar();
    L = CitireOm(&lg, cmpOm);
    AfisareLG(L, afisareOm);
    deleteElems(&L, funcCondStersOm, elibOm);
    AfisareLG(L, afisareOm);
    return 0;
}