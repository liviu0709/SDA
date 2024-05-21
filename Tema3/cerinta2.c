/* STOICA Liviu-Gabriel - 311CB */
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "functii.h"

int minimDist(int *x, int n, int *v) {
    int minim = INT_MAX;
    int sol, i;
    for ( i = 0 ; i < n ; i++ ) {
        if ( x[i] < minim && v[i] == 0 ) {
            minim = x[i];
            sol = i;
        }
    }
    return sol;
}

int cmpArc(const void *a, const void *b) {
    ArcExtras* x = (ArcExtras*)a;
    ArcExtras* y = (ArcExtras*)b;
    if ( x->arcSalvat == NULL )
        return 1;
    if ( y->arcSalvat == NULL )
        return -1;
    return x->costDrum - y->costDrum;
}

ArcExtras* algDijkstra(TGL *G, int nod) {
    int *vizitat = calloc(G->n + 1, sizeof(int));
    int *distanta = calloc(G->n + 1, sizeof(int));
    AArc *arceSalvate = calloc(G->n + 1, sizeof(AArc));
    // Punem distante infinite
    int i;
    for ( i = 0 ; i < G->n ; i++ )
        distanta[i] = INT_MAX;
    int *parinti = calloc(G->n + 1, sizeof(int));
    // Initializam datele pt nodul src
    distanta[nod] = 0;
    parinti[nod] = -1;
    arceSalvate[nod] = NULL;
    for ( i = 0 ; i < G->n ; i++ ) {
        int index = minimDist(distanta, G->n, vizitat);
        vizitat[index] = 1;
        AArc l;
        for ( l = G->x[index] ; l != NULL ; l = l->urm ) {
            if ( vizitat[l->d] == 0 ) {
                if ( l->c + distanta[index] < distanta[l->d] ) {
                    distanta[l->d] = l->c + distanta[index];
                    parinti[l->d] = index;
                    // Salvez arcul folosit
                    arceSalvate[l->d] = l;
                }
            }
        }
    }
    // Impachetam arcul folosit, parintele si costul drumului
    // intr-o structura pe care o vom returna
    ArcExtras *data = calloc(G->n + 1, sizeof(ArcExtras));
    for ( i = 0 ; i < G->n ; i++ ) {
        data[i].arcSalvat = arceSalvate[i];
        data[i].parinte = parinti[i];
        data[i].costDrum = distanta[i];
    }

    qsort(data, G->n, sizeof(ArcExtras), cmpArc);

    free(vizitat);
    free(distanta);
    free(parinti);
    free(arceSalvate);
    return data;
}



void AfiCer2(FILE *out, TGL *x, ArcExtras *data, int nrMax) {
    // Afisam nr cai pastrate
    fprintf(out, "%d\n", nrMax);
    FILE *in = fopen("tema3.in", "r");
    // Citim iar rutele date, pentru afisarea in ordine
    char *buf = malloc(1000);
    // Nume sat - nu am nevoie de el
    fgets(buf, 1000, in);
    fgets(buf, 1000, in);
    int n, cost;
    fscanf(in, "%d", &n);
    int i = 0;
    char *src = malloc(100);
    char *dst = malloc(100);
    for ( ; i < n ; i++ ) {
        fscanf(in, "%s %s %d", src, dst, &cost);
        int amGasit = 0;
        int j = 0;
        for ( ; j < nrMax ; j++ ) {
            // Graful nu e orientat, deci ordinea nu conteaza
            if ( strcmp(x->nume[data[j].arcSalvat->d], dst) == 0 && strcmp(x->nume[data[j].parinte], src) == 0) {
                amGasit = 1;
                break;
            }
            if ( strcmp(x->nume[data[j].arcSalvat->d], src) == 0 && strcmp(x->nume[data[j].parinte], dst) == 0) {
                amGasit = 1;
                break;
            }
        }
        if ( amGasit ) {
            fprintf(out, "%s %s\n", src, dst);
        }
    }
    free(src);
    free(dst);
    free(buf);
    fclose(in);
}
