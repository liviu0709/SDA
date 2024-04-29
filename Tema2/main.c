/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void procCuv(Arb *x, char *s) {
    // Adaugam caracterul care marcheaza
    // finalul de sir
    strcat(s, "$");
    int i;
    for ( i = strlen(s) - 1 ; i >= 0 ; i-- ) {
        // Construim sufixele
        char *sufix = malloc(strlen(s) + 1);
        strcpy(sufix, s + i);
        // Introducere sufix arbored
        intrSuf(x, sufix);
        free(sufix);
    }
}

// Cerinta 1
void c1(FILE *in, FILE *out) {
    Arb *x = init();
    int n;
    fscanf(in, "%d", &n);
    char *s = malloc(100 * sizeof(char));
    int i;
    for ( i = 0 ; i < n ; i++ ) {
        // Citim si introducem fiecare cuvant
        // In arbore
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    free(s);
    parcLatime(x, out);
    DistrArb(&x);
}

// Cerinta 2
void c2(FILE *in, FILE *out, int k) {
    Arb *x = init();
    int n;
    fscanf(in, "%d", &n);
    char *s = malloc(100 * sizeof(char));
    int i;
    for ( i = 0 ; i < n ; i++ ) {
        // Citim si introducem fiecare cuvant
        // In arbore
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    free(s);
    // Apelam functiile pentru rezolvarea
    // taskurilor cerute
    fprintf(out, "%d\n", nrNoduriFrunze(x));
    fprintf(out, "%d\n", nrSufixe(x, k));
    fprintf(out, "%d\n", nrMaxDescendenti(x));
    DistrArb(&x);
}

// Cerinta 3
void c3(FILE *in, FILE *out) {
    Arb *x = init();
    int n, m;
    fscanf(in, "%d %d", &n, &m);
    char *s = malloc(100 * sizeof(char));
    int i;
    for ( i = 0 ; i < n ; i++ ) {
        // Citim si introducem fiecare cuvant
        // In arbore
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    for ( i = 0 ; i < m ; i++ ) {
        // Citim sufixele de cautat
        fscanf(in, "%s", s);
        // Verificam daca se gasesc sau nu in arb
        fprintf(out, "%d\n", cautSufArbFull(x, s));
    }
    free(s);
    DistrArb(&x);
}

// Cerinta 4
void c4(FILE *in, FILE *out) {
    Arb *x = init();
    int n;
    fscanf(in, "%d", &n);
    char *s = malloc(100 * sizeof(char));
    int i;
    for ( i = 0 ; i < n ; i++ ) {
        // Citim si introducem fiecare cuvant
        // In arbore
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    // Apelam functiile pentru rezolvarea
    // taskurilor cerute
    compresieArb(x);
    parcLatime(x, out);
    free(s);
    DistrArb(&x);
}

int main(int argc, char *argv[]) {

    int indexCerinta = 0;
    // Citire cerinta prin arg executabil
    if ( argc > 1 ) {
        if ( strcmp(argv[1], "-c1") == 0 ) {
            indexCerinta = 1;
        } else if ( strcmp(argv[1], "-c2") == 0 ) {
            indexCerinta = 2;
        } else if ( strcmp(argv[1], "-c3") == 0 ) {
            indexCerinta = 3;
        } else if ( strcmp(argv[1], "-c4") == 0 ) {
            indexCerinta = 4;
        }
    }
    FILE *in, *out;
    // Momentan doar -c2 are un parametru in plus
    if ( indexCerinta == 2 && argc > 4 ) {
        in = fopen(argv[3], "r");
        out = fopen(argv[4], "w");
    } else {
        in = fopen(argv[2], "r");
        out = fopen(argv[3], "w");
    }
    switch ( indexCerinta ) {
        case 1:
            c1(in, out);
            break;
        case 2:
            c2(in, out, argv[2][0] - '0');
            break;
        case 3:
            c3(in, out);
            break;
        case 4:
            c4(in, out);
            break;
        default:
            break;
    }
    fclose(in);
    fclose(out);
    return 0;
}