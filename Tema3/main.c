/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

float medieRuta(float *uz, int n) {
    float sum = 0;
    for ( int i = 0 ; i < n ; i++ ) {
        sum += uz[i];
    }
    return sum / n;
}

void cerinta1(TGL *g, FILE *out) {
    char *buf = malloc(1000);
    // Citim iar de la inceput pentru a afisa ce se cere
    FILE *in = fopen("tema3.in", "r");
    int nrLeg, ani, uzat;
    fscanf(in, "%d %d %d", &nrLeg, &ani, &uzat);
    int *index = malloc((nrLeg + 1) * sizeof(int));
    int *nodS = calloc(sizeof(int), 1);
    for ( int i = 1 ; i <= nrLeg ; i++ ) {
        char *src = malloc(100);
        char *dst = malloc(100);
        // Citim doar primele 2 cuvinte de pe rand
        fscanf(in, "%s %s", src, dst);
        // Restul le ignoram pt ca nu ne trb
        fgets(buf, 1000, in);
        // Obtinem datele necesare din graful generat
        AArc input = getArc(g, src, dst, nodS);
        // Afisam ce se cere
        fprintf(out, "%s %s %d ", g->nume[*nodS], g->nume[input->d], input->n);
        for ( int i = 0 ; i < input->n ; i++ ) {
            fprintf(out, "%.2f ", input->uz[i]);
        }
        fprintf(out, "\n");
        // Verificam daca merita pastrata
        if ( medieRuta(input->uz, input->n) < uzat ) {
            index[i] = 1;
        } else {
            index[i] = 0;
        }
        free(src);
        free(dst);
    }
    // Afisam rutele pastrate
    for ( int i = 1 ; i <= nrLeg ; i++ )
        if ( index[i] )
            fprintf(out, "%d ", i);
    free(index);
    free(nodS);
    free(buf);
    fclose(in);
}

float uzuraMaxima(TGL *x, int nod) {
    float maxUz = 0;
    AArc l = x->x[nod];
    for ( ; l != NULL ; l = l->urm ) {
        if ( maxUz < l->uz[0] )
            maxUz = l->uz[0];
    }
    return maxUz;
}

TGL* timpuTrece(TGL *x, int an) {
    if ( an == 0 )
        return x;
    TGL *updated = Copy(x);
    // Flaw - modificare inplace, deci nu e bn
    // Solutie - lucram pe o copie a grafului

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
    return timpuTrece(x, an - 1);
}

int main(int argc, char *argv[]) {
    if ( argc == 1 ) {
        printf("Nema cerinta\n");
        return 1;
    }
    FILE *in = fopen("tema3.in", "r");
    FILE *out = fopen("tema3.out", "w");
    if ( argv[1][0] == '1' ) {
        // Task 1
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

    } else if ( argv[1][0] == '2' ) {
        printf("Task 2\n");
    }


    fclose(in);
    fclose(out);
    return 0;
}