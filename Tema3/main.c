/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

float uzuraMaxima(TGL *x, int nod) {
    float maxUz = 0;
    AArc l = x->x[nod];
    for ( ; l != NULL ; l = l->urm ) {
        if ( maxUz < l->uz[0] )
            maxUz = l->uz[0];
    }
    return maxUz;
}

void timpuTrece(TGL *x, int an) {
    TGL *updated = Copy(x);
    // Flaw - modificare inplace, deci nu e bn
    // Solutie - lucram pe o copie a grafului
    if ( an == 0 )
        return;

    // Parcurgem fiecare nod
    for ( int i = 0 ; i < x->n ; i++ ) {
        // Ar putea returna propria uzura maxima cumva?
        // de rezolvat la checker !!!
        float maxUz = uzuraMaxima(x, i);


        // Update uzuri
        AArc l, lcp;
        for ( l = x->x[i], lcp = updated->x[i] ; l != NULL ; l = l->urm, lcp = lcp->urm) {
            for ( int j = 0 ; j < l->n ; j++ ) {
                // Daca tronsonul nu e uzat
                if ( l->uz[j] == 0 ) {
                    // Tinem cont daca e la inceput de ruta
                    if ( j == 0 ) {
                        if ( maxUz > l->uz[j + 1] )
                            lcp->uz[j] = maxUz / 2;
                        else
                            lcp->uz[j] = l->uz[j + 1] / 2;
                    } else {
                        // Sau la sfarsit
                        if ( j == l->n - 1 ) {
                            float stricat = uzuraMaxima(x, l->d);
                            if ( stricat > l->uz[j - 1])
                                lcp->uz[j] = stricat / 2;
                            else
                                lcp->uz[j] = l->uz[j - 1] / 2;
                        } else {
                        // Sau cel mai simplu caz, la mijloc
                        if ( l->uz[j - 1] > l->uz[j + 1] )
                            lcp->uz[j] = l->uz[j - 1] / 2;
                        else
                            lcp->uz[j] = l->uz[j + 1] / 2;
                        }
                    }
                } else {
                    lcp->uz[j] *= 2;
                }
                if ( lcp->uz[j] > 100 )
                    lcp->uz[j] = 100;
            }

        }
    }
    DistrG(&x);
    x = updated;
    timpuTrece(x, an - 1);
}

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
        timpuTrece(x, ani);
        AfiGrafL(x);
        DistrG(&x);

    } else if ( argv[1][0] == '2' ) {
        printf("Task 2\n");
    }


    fclose(in);
    fclose(out);
    return 0;
}