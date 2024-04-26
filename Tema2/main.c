/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void procCuv(Arb *x, char *s) {
    strcat(s, "$");
    // printf("Sir modificat: %s\n", s);
    // printf("Ultimul caracter: %c\n", s[strlen(s) - 1]);
    int i;
    for ( i = strlen(s) - 1 ; i >= 0 ; i-- ) {
        // Construim sufixele
        char *sufix = malloc(strlen(s) + 1);
        strcpy(sufix, s + i);

        // printf("Sufix: %s\n", sufix);
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
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    free(s);
    fprintf(out, "%d\n", nrNoduriFrunze(x));
    // nrSufixe ia in calcul si terminatorul $
    fprintf(out, "%d\n", nrSufixe(x, k + 1));
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
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    for ( i = 0 ; i < m ; i++ ) {
        fscanf(in, "%s", s);
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
        fscanf(in, "%s", s);
        procCuv(x, s);
    }
    compresieArb(x);
    parcLatime(x, out);
    free(s);
    DistrArb(&x);
}

int main(int argc, char *argv[]) {

    int indexCerinta = 0;
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



    // parcLatime(x);
    // printf("Am gasit %d frunze\n", nrNoduriFrunze(x));
    // printf("Am gasit %d sufixe pt k3\n", nrSufixe(x, 3));
    // printf("Nr max mostenitori gasiti: %d\n", nrMaxDescendenti(x));
    // char *t1 = malloc(69), *t2 = malloc(69), *t3 = malloc(69);
    // strcpy(t1, "na");
    // strcpy(t2, "ana");
    // strcpy(t3, "ban");
    // printf("%s se gaseste in arb? %d\n", t1, cautSufArbFull(x, t1));
    // printf("%s se gaseste in arb? %d\n", t2, cautSufArbFull(x, t2));
    // printf("%s se gaseste in arb? %d\n", t3, cautSufArbFull(x, t3));
    // free(t1);
    // free(t2);
    // free(t3);
    // compresieArb(x);
    // parcLatime(x);
    // printf("Mda\n");
    // DistrArb(&x);
    fclose(in);
    fclose(out);
    return 0;
}