/* STOICA Liviu-Gabriel - 311CB */
#include <stdlib.h>
#include <string.h>
#include "functii.h"

// Copiem un graf
TGL* Copy(TGL *src) {
    TGL *dst = AlocG(src->n);
    int i = 0;
    for ( ; i < src->n ; i++ ) {
        dst->nume[i] = malloc(strlen(src->nume[i]) + 1);
        strcpy(dst->nume[i], src->nume[i]);
        AArc l = src->x[i];
        for ( ; l != NULL ; l = l->urm ) {
            AArc aux = (TCelArc*)calloc(sizeof(TCelArc),1);
            aux->d = l->d;
            aux->c = l->c;
            aux->n = l->n;
            aux->uz = (float*)malloc(l->n * sizeof(float));
            int j = 0;
            for ( ; j < l->n ; j++ ) {
                aux->uz[j] = l->uz[j];
            }
            AArc *p;
            p = dst->x + i;
            while (*p) p = &(*p)->urm;
            aux->urm = *p; *p = aux;
        }
    }
    // Returnam o copie fidela
    // Care nu are memorie comuna cu src
    return dst;
}

// Pointer arc return + index src efect lateral
AArc getArc(TGL *g, char* src, char* dst, int *s) {
    int d;
    int i = 0;
    for ( ; i < g->n; i++ ) {
        if ( strcmp(g->nume[i], src) == 0 ) {
            *s = i;
        }
        if ( strcmp(g->nume[i], dst) == 0 ) {
            d = i;
        }
    }
    AArc l = g->x[*s];
    for ( ; l != NULL ; l = l->urm ) {
        if ( l->d == d ) {
            return l;
        }
    }
    return NULL;
}

// Calculeaza media unui vector float
float medieRuta(float *uz, int n) {
    float sum = 0;
    int i = 0;
    for ( ; i < n ; i++ ) {
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
    int i;
    char *src = malloc(100);
    char *dst = malloc(100);
    for ( i = 1 ; i <= nrLeg ; i++ ) {
        // Citim doar primele 2 cuvinte de pe rand
        fscanf(in, "%s %s", src, dst);
        // Restul le ignoram pt ca nu ne trb
        fgets(buf, 1000, in);
        // Obtinem datele necesare din graful generat
        AArc input = getArc(g, src, dst, nodS);
        // Afisam ce se cere
        fprintf(out, "%s %s %d ", g->nume[*nodS], g->nume[input->d], input->n);
        int j = 0;
        for ( ; j < input->n ; j++ ) {
            fprintf(out, "%.2f ", input->uz[j]);
        }
        fprintf(out, "\n");
        // Verificam daca merita pastrata
        if ( medieRuta(input->uz, input->n) < uzat ) {
            index[i] = 1;
        } else {
            index[i] = 0;
        }
    }
    free(src);
    free(dst);
    // Afisam rutele pastrate
    for ( i = 1 ; i <= nrLeg ; i++ )
        if ( index[i] )
            fprintf(out, "%d ", i);
    free(index);
    free(nodS);
    free(buf);
    fclose(in);
}

// Calculeaza uzura maxima dintr-un nod
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
    // Conditie oprire
    if ( an == 0 )
        return x;
    // Facem o copie a grafului
    TGL *updated = Copy(x);
    // Parcurgem fiecare nod
    int i = 0;
    for ( ; i < x->n ; i++ ) {
        // Calculam uzura maxima dintr-un nod
        float maxUz = uzuraMaxima(x, i);
        // Update uzuri
        AArc l, lcp;
        for ( l = x->x[i], lcp = updated->x[i] ; l != NULL ; l = l->urm, lcp = lcp->urm) {
            int j = 0;
            for ( ; j < l->n ; j++ ) {
                // Daca tronsonul nu e uzat si nu este dintr-o singura bucata
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
                    // Daca este dintr-o singura bucata si este uzat
                    if ( l->n == 1 && l->uz[j] == 0) {
                        // Calculam uzuraMaxima si pentru Dst
                        float uzDst = uzuraMaxima(x, l->d);
                        // Comparam cu uzura din src
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
