/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main() {
    Arb *x = init();
    (void)*x;
    char s[100];
    scanf("%s", s);
    strcat(s, "$");
    printf("Sir modificat: %s\n", s);
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
    parcLatime(x);
    compresieArb(x);
    parcLatime(x);
    printf("Mda\n");
    DistrArb(&x);
    return 0;
}