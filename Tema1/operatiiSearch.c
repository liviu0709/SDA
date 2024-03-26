#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void search(Tren *t, char *s, FILE *out) {
    int l = strlen(s);
    // printf("Lungimea cuvantului: %d\n", l);
    TLista aux = t->mecanic;
    // printf("Cautam cuvantul: %s\n", s);
    int ok = 0;
    int i = 0;
    if ( t->mecanic->info == s[i] ) {
        i++;
    } else {
        aux = aux->urm;
    }
    // printf("Val i: %d\n", i);
    for ( ; aux->urm != t->mecanic ; aux = aux->urm ) {
        if ( aux == t->santinela ) {
            aux = aux->urm;
            if ( aux == t->mecanic ) {
                break;
            }
        }
        if ( aux->info == s[i] ) {
            i++;
        } else {
            i = 0;
        }
        if ( i == l - 1 ) {
            ok = 1;
            break;
        }
    }
    if ( ok ) {
        printf("Am gasit ce cautam!\n");
        for ( int j = 0 ; j < i - 1; j++ ) {
            aux = aux->prev;
            if ( aux == t->santinela ) {
                aux = aux->prev;
            }
        }
        t->mecanic = aux;
    } else {
        fprintf(out, "ERROR\n");
        printf("Nu am gasit ce cautam!\n");
    }
}