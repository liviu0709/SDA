/* STOICA Liviu-Gabriel - 311CB */
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc, char *argv[]) {
    // Daca nu avem argument, nu vrem segfault
    if ( argc == 1 ) {
        printf("Nema cerinta\n");
        return 1;
    }
    FILE *in = fopen("tema3.in", "r");
    FILE *out = fopen("tema3.out", "w");
    // Cerinta 1
    if ( argv[1][0] == '1' ) {
        int nrLeg, ani, uzat;
        fscanf(in, "%d %d %d", &nrLeg, &ani, &uzat);
        // Generare graf
        TGL *x = CitGraf(in, nrLeg);
        // Procesare graf
        x = timpuTrece(x, ani);
        // Afisare date cerute
        cerinta1(x, out);
        // Punctaj valgrind
        DistrG(&x);
    // Cerinta 2
    } else if ( argv[1][0] == '2' ) {
        char *satStart = malloc(100);
        int k, m, sat;
        fscanf(in, "%s %d %d", satStart, &k, &m);
        TGL *x = CitGraf2(in);
        // Calculam indicele satului start
        int i;
        for ( i = 0 ; i < x->n ; i++ ) {
            if ( strcmp(x->nume[i], satStart) == 0 ) {
                sat = i;
                break;
            }
        }
        // Folosind alg Dijkstra obtinem arcele care merita pastrate
        ArcExtras *dataRaw = algDijkstra(x, sat);
        // Ele sunt returnate gata sortate in functie de cost
        // Trebuie doar sa vedem daca avem macar k arce pt afisare
        int caiPastrate = 0;
        for ( i = 0 ; i < x->n ; i++ ) {
            if ( dataRaw[i].arcSalvat != NULL )
                caiPastrate++;
            if ( caiPastrate == k )
                break;
        }
        // Afisam datele cerute
        AfiCer2(out, x, dataRaw, caiPastrate);
        // Punctaj valgrind...
        free(dataRaw);
        DistrG(&x);
        free(satStart);
    }
    fclose(in);
    fclose(out);
    return 0;
}
