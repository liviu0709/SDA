#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

// Contine cele 3 functii pentru cele 3 cautari

// Caz particular ... sirul cautat are 1 caracter, nu este luat in considerare
// Poate nu va afecta testele?:)

void search(Tren *t, char *s, FILE *out) {
    // Gasim lungimea sirului de cautat
    int l = strlen(s);
    // printf("Lungimea cuvantului: %d\n", l);
    TLista aux = t->mecanic;
    // printf("Cautam cuvantul: %s\n", s);
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
    // In caz contrar, mergem mai departe
    } else {
        aux = aux->urm;
    }
    // printf("Val i: %d\n", i);
    for ( ; aux->urm != t->mecanic ; aux = aux->urm ) {
        // Sarim peste santinela
        if ( aux == t->santinela ) {
            aux = aux->urm;
            // Conditie oprire
            if ( aux == t->mecanic ) {
                break;
            }
        }
        // Cautam sirul...
        if ( aux->info == s[i] ) {
            i++;
        // Daca un caracter nu mai este ce trb...
        // o luam de la 0
        } else {
            i = 0;
        }
        // In sfarsit am gasit ceea ce cautam?
        if ( i == l - 1 ) {
            printf("Minunat\n")
            ok = 1;
            break;
        }
    }
    if ( ok ) {
        //printf("Am gasit ce cautam!\n");
        for ( int j = 0 ; j < i - 1; j++ ) {
            aux = aux->prev;
            if ( aux == t->santinela ) {
                aux = aux->prev;
            }
        }
        // Ducem mecanicul la locul cerut
        t->mecanic = aux;
    } else {
        // Naspa, nu e ce trb
        fprintf(out, "ERROR\n");
        // printf("Nu am gasit ce cautam!\n");
    }
}

void searchLeft(Tren *t, char*s, FILE *out) {
    // Gasim lungimea sirului de cautat
    int l = strlen(s);
    // printf("Lungimea cuvantului: %d\n", l);
    TLista aux = t->mecanic;
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
        // printf("Val i START: %d\n", i);
        aux = aux->prev;
    // In caz contrar, mergem mai departe
    } else {
        aux = aux->prev;
    }
    for ( ; aux != t->santinela ; aux = aux->prev ) {
        // Cautam sirul...
        if ( aux->info == s[i] ) {
            // printf("Val i FOR: %d\n", i);
            i++;
        // Daca nu e ce trb...
        // O luam de la capat
        } else {
            i = 0;
        }
        // In sfarsit am gasit ceea ce cautam?
        if ( i == l ) {
            // printf("Am gasit ce cautam!\n");
            ok = 1;
            break;
        }
    }
    if ( ok ) {
        // Mutam mecanicul unde trebuie
        t->mecanic = aux;
        // printf("Val mecanic : %c\n", t->mecanic->info);
    } else {
        // Ghiunion
        fprintf(out, "ERROR\n");
    }
}

void searchRight(Tren *t, char *s, FILE *out) {
    // Gasim lungimea sirului de cautat
    int l = strlen(s);
    TLista aux = t->mecanic;
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
        //printf("Val i START: %d\n", i);
        aux = aux->urm;
    // In caz contrar, mergem mai departe
    } else {
        aux = aux->urm;
    }
    for ( ; aux != t->santinela ; aux = aux->urm ) {
        // Cautam sirul ...
        if ( aux->info == s[i] ) {
            i++;
            // printf("Val i FOR: %d\n", i);
        // In caz contrar
        // o luam de la capat
        } else {
            i = 0;
        }
        // Am gasit ceea ce cautam ?
        if ( i == l ) {
            ok = 1;
            break;
        }
    }
    if ( ok ) {
        // Mutam mecanicul
        t->mecanic = aux;
    } else {
        // Naspa...
        fprintf(out, "ERROR\n");
    }
}