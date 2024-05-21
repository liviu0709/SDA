/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
                if ( l->uz[j] == 0 && l->n != 1 ) {
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
                    if ( l->n == 1 && l->uz[j] == 0) {
                        float uzDst = uzuraMaxima(x, l->d);
                        if ( maxUz > uzDst)
                            lcp->uz[j] = maxUz / 2;
                        else
                            lcp->uz[j] = uzDst / 2;
                    } else
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

int minimDist(int *x, int n, int *v) {
    int minim = INT_MAX;
    int sol;
    for ( int i = 0 ; i < n ; i++ ) {
        if ( x[i] < minim && v[i] == 0 ) {
            minim = x[i];
            sol = i;
        }
    }
    return sol;
}

ArcExtras* algDijkstra(TGL *G, int nod) {
    int *vizitat = calloc(G->n + 1, sizeof(int));
    int *distanta = calloc(G->n + 1, sizeof(int));
    AArc *arceSalvate = calloc(G->n + 1, sizeof(AArc));
    // Punem distante infinite
    for ( int i = 0 ; i < G->n ; i++ )
        distanta[i] = INT_MAX;
    int *parinti = calloc(G->n + 1, sizeof(int));
    // Initializam datele pt nodul src
    distanta[nod] = 0;
    parinti[nod] = -1;
    arceSalvate[nod] = NULL;
    for ( int i = 0 ; i < G->n ; i++ ) {
        int index = minimDist(distanta, G->n, vizitat);
        vizitat[index] = 1;
        for ( AArc l = G->x[index] ; l != NULL ; l = l->urm ) {
            if ( vizitat[l->d] == 0 ) {
                // Trecem la djisktra?
                if ( l->c + distanta[index] < distanta[l->d] ) {
                    distanta[l->d] = l->c + distanta[index];
                    parinti[l->d] = index;
                    // Salvez arcul ales
                    arceSalvate[l->d] = l;
                }
            }
        }
    }
    printf("\n Alg Prim");
    printf("\n Lista costuri: ");
    for ( int i = 0 ; i < G->n ; i++ )
        printf("[%d - %s]", distanta[i], G->nume[i]);
    printf("\n");
    printf("Nod src: %s\n", G->nume[nod]);
        printf(" Lista parinti: ");
    for ( int i = 0 ; i < G->n ; i++ ) {
        // printf("%d ", parinti[i]);
        if ( parinti[i] >= 0 )
            printf("%s ", G->nume[parinti[i]]);
        else
            printf("SRC ");
    }
    printf("\n");
    for ( int i = 0 ; i < G->n ; i++ ) {
        // printf("%d ", parinti[i]);
        if ( parinti[i] >= 0 )
            printf("%d ", parinti[i]);
        else
            printf("SRC ");
    }
    printf("\n");
    for ( int i = 0 ; i < G->n ; i++ ) {
        if ( arceSalvate[i] != NULL ) {
            printf("%s %s %d\n", G->nume[parinti[i]], G->nume[i], arceSalvate[i]->c);
        } else {
            printf("NEMA ARC\n");
        }
    }
    // Avem nevoie de arcele arborelui de acoperire
    // Pentru a obtine ce se cere, pastram doar
    // arcele cu cost cat mai mic
    ArcExtras *data = calloc(G->n + 1, sizeof(ArcExtras));
    for ( int i = 0 ; i < G->n ; i++ ) {
        data[i].arcSalvat = arceSalvate[i];
        data[i].parinte = parinti[i];
        data[i].costDrum = distanta[i];
    }
    free(vizitat);
    free(distanta);
    free(parinti);
    free(arceSalvate);
    return data;
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
    for ( int i = 0 ; i < n ; i++ ) {
        char *src = malloc(100);
        char *dst = malloc(100);
        fscanf(in, "%s %s %d", src, dst, &cost);
        int amGasit = 0;
        for ( int j = 0 ; j < nrMax ; j++ ) {
            // Graful nu e orientat, deci ordinea nu conteaza
            if ( strcmp(x->nume[data[j].arcSalvat->d], dst) == 0 && strcmp(x->nume[data[j].parinte], src) == 0) {
                printf("Am gasit %s %s\n", x->nume[data[j].arcSalvat->d], x->nume[data[j].parinte]);
                printf("Afisez %s %s\n", src, dst);
                amGasit = 1;
                break;
            }
            if ( strcmp(x->nume[data[j].arcSalvat->d], src) == 0 && strcmp(x->nume[data[j].parinte], dst) == 0) {
                printf("Am gasit %s %s\n", x->nume[data[j].arcSalvat->d], x->nume[data[j].parinte]);
                printf("Afisez %s %s\n", dst, src);
                amGasit = 1;
                break;
            }
        }
        if ( amGasit ) {
            fprintf(out, "%s %s\n", src, dst);
            printf("S-a incercatt %s %s\n", src, dst);
        }
        free(src);
        free(dst);
    }
    free(buf);
    fclose(in);
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
        char *satStart = malloc(100);
        int k, m, sat;
        fscanf(in, "%s %d %d", satStart, &k, &m);
        (void) m; // Kinda useless ngl
        TGL *x = CitGraf2(in);
        // Calculam indicele satului start
        for ( int i = 0 ; i < x->n ; i++ ) {
            if ( strcmp(x->nume[i], satStart) == 0 ) {
                sat = i;
                break;
            }
        }
        printf("\n Satul start: %d\n", sat);
        AfiGrafL2(x);
        ArcExtras *dataRaw = algDijkstra(x, sat);
        // Sortam arcele in functie de costul minim
        qsort(dataRaw, x->n, sizeof(ArcExtras), cmpArc);
        // Acum avem o lista sortata cu arcele care merita pastrate
        printf("Afis lista sortata\n");
        for ( int i = 0 ; i < x->n ; i++ ) {
            if ( dataRaw[i].arcSalvat != NULL ) {
                printf("%s %s %d\n", x->nume[dataRaw[i].parinte], x->nume[dataRaw[i].arcSalvat->d], dataRaw[i].costDrum);
            } else {
                printf("NEMA ARC\n");
            }
        }

        int caiPastrate = 0;
        for ( int i = 0 ; i < x->n ; i++ ) {
            if ( dataRaw[i].arcSalvat != NULL )
                caiPastrate++;
            if ( caiPastrate == k )
                break;
        }
        AfiCer2(out, x, dataRaw, caiPastrate);
        free(dataRaw);
        DistrG(&x);
        free(satStart);
    }


    fclose(in);
    fclose(out);
    return 0;
}