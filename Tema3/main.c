/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc, char *argv[]) {
    if ( argc == 1 ) {
        printf("Nema cerinta\n");
        return 1;
    }
    FILE *in = fopen("tema3.in", "r");
    FILE *out = fopen("tema3.out", "w");
    if ( argv[1][0] == '1' ) {
        printf("Task 1\n");
        int nrLeg, ani, uzat;
        fscanf(in, "%d %d %d", &nrLeg, &ani, &uzat);
        TGL *x = CitGraf(in, nrLeg);
        AfiGrafL(x);
        DistrG(&x);

    } else if ( argv[1][0] == '2' ) {
        printf("Task 2\n");
    }


    fclose(in);
    fclose(out);
    return 0;
}