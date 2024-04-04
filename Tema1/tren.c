#include <stdio.h>
#include <stdlib.h>
#include "functii.h"

// Majoritatea functiilor sunt apelate in functie 
// de comanda primita

// Initializare tren cu 1 vagon
Tren* alocTren() {
    Tren *x = (Tren*) malloc(sizeof(Tren));
    TLista vag1 = malloc(sizeof(TCelula));
    vag1->info = '#';
    x->mecanic = vag1;
    TLista sant = malloc(sizeof(TCelula));
    x->santinela = sant;
    sant->prev = sant->urm = vag1;
    vag1->prev = vag1->urm = sant;
    return x;
}

// Stergere tren -> valgrind
void distrTren(Tren **x) {
    if ( !(*x)->mecanic ) return; 
    for ( TLista aux = (*x)->santinela->urm  ; aux != (*x)->santinela ; ) {
    TLista aux2 = aux;
    aux = aux->urm;
    (void) aux2;
    free(aux2);
    }
    free((*x)->santinela);
    free(*x);
}

void moveLeft(Tren *t) {
    // Daca este primul vagon de langa locomotiva...
    if ( t->mecanic->prev == t->santinela ) {
        t->mecanic = t->santinela->prev;
    } else {
        t->mecanic = t->mecanic->prev;
    }
}

int moveRight(Tren *t) {
    // Daca este in ultimul vagon, mai cuplam unul
    if ( t->mecanic->urm == t->santinela ) {
        TLista aux = malloc(sizeof(TCelula));
        if ( !aux ) return 1;
        aux->prev = t->mecanic;
        aux->urm = t->santinela;
        aux->info = '#';
        t->mecanic->urm = aux;
        t->mecanic = aux;
        t->santinela->prev = aux;
    } else {
        t->mecanic = t->mecanic->urm;
    }
    return 0;
}

// Cea mai lunga functie din tema
void writeC(char c, Tren *t) {
    t->mecanic->info = c;
}

void clearCell(Tren *t) {
    // Primul vagon din tren
    if ( t->mecanic->prev == t->santinela ) {
        // Daca trenul avea un singur vagon
        // Se revine la starea initiala
        if ( t->mecanic->urm == t->santinela ) {
            t->mecanic->info = '#';
        // Altfel se muta mecanicul in capatul trenului
        } else {
            TLista aux = t->mecanic;
            t->santinela->urm = t->mecanic->urm;
            t->mecanic->urm->prev = t->santinela;
            t->mecanic = t->santinela->prev;
            free(aux);
        }
    } else {
        // Un vagon din mijlocul trenului
        if ( t->mecanic->urm != t->santinela ) {
            TLista aux = t->mecanic;
            t->mecanic->prev->urm = t->mecanic->urm;
            t->mecanic->urm->prev = t->mecanic->prev;
            t->mecanic = t->mecanic->prev;
            free(aux);
        // Capatul din dreapta al trenului
        } else {
            TLista aux = t->mecanic;
            t->santinela->prev = t->mecanic->prev;
            t->mecanic->prev->urm = t->santinela;
            t->mecanic = t->mecanic->prev;
            free(aux);
        }
    }
}

void clearAll(Tren** t) {
    // Stergem tot
    distrTren(t);
    // Ajungem in starea initiala
    *t = alocTren();
    
}

void insertRight(Tren *t, char c) {
    // Mecanicul este in ultimul vagon
    if ( t->mecanic->urm == t->santinela ) {
        moveRight(t);
        t->mecanic->info = c;
    } else {
        TLista aux = alocCel(c);
        aux->prev = t->mecanic;
        aux->urm = t->mecanic->urm;
        t->mecanic->urm->prev = aux;
        t->mecanic->urm = aux;
        t->mecanic = aux;
    }
}

void insertLeft(Tren *t, char c, FILE *out) {
    // Caz particular - primul vagon
    if ( t->mecanic->prev == t->santinela ) {
        fprintf(out, "ERROR\n");
    } else {
        TLista aux = alocCel(c);
        aux->urm = t->mecanic;
        aux->prev = t->mecanic->prev;
        t->mecanic->prev->urm = aux;
        t->mecanic->prev = aux;
        t->mecanic = aux;
    }
}

void afisTren(Tren* t, FILE *out) {
    for ( TLista aux = t->santinela->urm ; aux != t->santinela ; aux = aux->urm ) {
        if ( t->mecanic == aux ) {
            fprintf(out, "|%c|", aux->info);
        } else {
            fprintf(out, "%c", aux->info);
        }
    }
    fprintf(out, "\n");
}

