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
    printf("Am gasit %d frunze\n", nrNoduriFrunze(x));
    printf("Am gasit %d sufixe pt k3\n", nrSufixe(x, 3));
    printf("Nr max mostenitori gasiti: %d\n", nrMaxDescendenti(x));
    char *t1, *t2, *t3;
    t1 = strdup("na");
    t2 = strdup("ana");
    t3 = strdup("ban");
    printf("%s se gaseste in arb? %d\n", t1, cautSufArbFull(x, t1));
    printf("%s se gaseste in arb? %d\n", t2, cautSufArbFull(x, t2));
    printf("%s se gaseste in arb? %d\n", t3, cautSufArbFull(x, t3));
    compresieArb(x);
    parcLatime(x);
    printf("Mda\n");
    DistrArb(&x);
    return 0;
}