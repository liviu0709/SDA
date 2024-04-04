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
    TLista inceputSecv = t->mecanic;
    // printf("Cautam cuvantul: %s\n", s);
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
        inceputSecv = t->mecanic;
        // Daca am gasit ce cautam ... nu mergem mai departe
        if ( i == l )
            ok = 1;
    }
    if ( !ok ) {
        do {
            aux = aux->urm;
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
                // Daca e inceputul sirului, il tinem minte
                if ( i == 1 )
                    inceputSecv = aux;
            // Daca un caracter nu mai este ce trb...
            // o luam de la 0
            } else {
                i = 0;
                // Continuam cautarea cu o pozitie mai in fata
                aux = inceputSecv->urm;
                inceputSecv = aux;
            }
            // In sfarsit am gasit ceea ce cautam!
            if ( i == l ) {
                ok = 1;
                break;
            }
        } while (aux->urm != t->mecanic);
    }

    if ( ok )
        t->mecanic = inceputSecv;
    else
        fprintf(out, "ERROR\n");
}

void searchLeft(Tren *t, char*s, FILE *out) {
    // Gasim lungimea sirului de cautat
    int l = strlen(s);
    TLista aux = t->mecanic;
    TLista inceputSecv = t->mecanic;
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
        inceputSecv = t->mecanic;
    }
    aux = aux->prev;
    for ( ; aux != t->santinela ; aux = aux->prev ) {
        // Cautam sirul...
        if ( aux->info == s[i] ) {
            i++;
            // Daca e inceputul sirului, il tinem minte
            if ( i == 1 ) {
                inceputSecv = aux;
            }
        // Daca nu e ce trb...
        // O luam de la capat
        } else {
            i = 0;
            // Continuam cautarea cu o pozitie mai la stanga
            aux = inceputSecv->prev;
            inceputSecv = aux;
        }
        // In sfarsit am gasit ceea ce cautam
        if ( i == l ) {
            ok = 1;
            break;
        }
    }
    if ( ok )
        t->mecanic = aux;
    else
        fprintf(out, "ERROR\n");
}

void searchRight(Tren *t, char *s, FILE *out) {
    // Gasim lungimea sirului de cautat
    int l = strlen(s);
    TLista aux = t->mecanic;
    TLista inceputSecv;
    int ok = 0;
    int i = 0;
    // Verificam daca primul caracter din sir se gaseste
    // cu cel din vagonul in care se afla mecanicul
    if ( t->mecanic->info == s[i] ) {
        i++;
        inceputSecv = t->mecanic;
    }
    // In caz contrar, mergem mai departe
    aux = aux->urm;
    for ( ; aux != t->santinela ; aux = aux->urm ) {
        // Cautam sirul ...
        if ( aux->info == s[i] ) {
            i++;
            if ( i == 1 ) {
                inceputSecv = aux;
            }
        // In caz contrar
        // o luam de la capat
        } else {
            i = 0;
            // Continuam cautarea cu o pozitie mai la dreapta
            aux = inceputSecv->urm;
            inceputSecv = aux;
        }
        // Am gasit ceea ce cautam
        if ( i == l ) {
            ok = 1;
            break;
        }
    }
    if ( ok )
        t->mecanic = aux;
    else
        fprintf(out, "ERROR\n");
}