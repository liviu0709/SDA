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

void searchLeft(Tren *t, char*s, FILE *out) {
    int l = strlen(s);
    // printf("Lungimea cuvantului: %d\n", l);
    TLista aux = t->mecanic;
    TLista indiceMecFinal = t->mecanic;
    int ok = 0;
    int i = 1;
    if ( t->mecanic->info == s[l - i] ) {
        i++;
        // printf("Val i START: %d\n", i);
    } else {
        aux = aux->prev;
    }
    for ( ; aux != t->santinela ; aux = aux->prev ) {

        if ( aux->info == s[l - i] ) {
            // printf("Val i FOR: %d\n", i);
            if ( i == 1 )
                indiceMecFinal = aux;
            i++;
        } else {
            i = 1;
        }
        if ( i == l + 1) {
            // printf("Am gasit ce cautam!\n");
            ok = 1;
            break;
        }
    }
    if ( ok ) {
        t->mecanic = indiceMecFinal;
        // printf("Val mecanic : %c\n", t->mecanic->info);
    } else {
        fprintf(out, "ERROR\n");
    }
}

void searchRight(Tren *t, char *s, FILE *out) {
    int l = strlen(s);
    (void) l;
}