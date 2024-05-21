/* STOICA Liviu-Gabriel - 311CB */
/*--- graf-L.c --- Graf implementat cu liste --*/
#include <stdlib.h>
#include <string.h>
#include "functii.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL* g = (TGL*)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  g->nume = calloc((nr+1), sizeof(char*)); /* spatiu vector adr. nume noduri */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG(TGL** ag)
{
    int i;
    AArc p, aux;
    for ( i = 0; i < (*ag)->n; i++ ) {
        free((*ag)->nume[i]);
        p = (*ag)->x[i];
        while(p) {
            aux = p; p = p->urm;
            if(aux->uz) {
                free(aux->uz);
            }
            free(aux);
        }
    }
    free((*ag)->x);
    free((*ag)->nume);
    free(*ag);
    *ag = NULL;
}

TGL* CitGraf(FILE *in, int nrLeg)
{
    TGL* g = NULL;
    int s, d;
    int x;
    AArc *p, aux;
    int n = 0;
    char *src = malloc(100);
    char *dst = malloc(100);
    g = AlocG(1000); // nu stim cate noduri are graful
    // aflam dupa ce citim tot
    if (!g) return 0;
    while (fscanf(in, "%s %s %d", src, dst, &x) == 3)
    {
        s = d = -1;
        // Caut src si dst in vectorul de nume
        int i = 0;
        for ( ; i < n ; i++ ) {
            if ( strcmp(g->nume[i], src) == 0 ) {
                s = i;
            }
            if ( strcmp(g->nume[i], dst) == 0 ) {
                d = i;
            }
        }
        // nu am gasit src, il aloc
        if ( s == -1 ) {
            char *aux = malloc(strlen(src) + 1);
            strcpy(aux, src);
            g->nume[n] = aux;
            s = n;
            n++;
        }
        // nu am gasit dst, il aloc
        if ( d == -1 ) {
            char *aux = malloc(strlen(dst) + 1);
            strcpy(aux, dst);
            g->nume[n] = aux;
            d = n;
            n++;
        }
        p = g->x + s;
        while (*p) p = &(*p)->urm;
        aux = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux) {
        DistrG(&g); return NULL;
        }
        aux->urm = *p; *p = aux;
        aux->d = d; aux->n = x;

        // citim info tronsoane
        aux->uz = (float*)malloc(x * sizeof(float));
        i = 0;
        for ( ; i < x ; i++ ) {
            float x;
            fscanf(in, "%f", &x);
            aux->uz[i] = x;
        }
        p = g->x + d;
        while (*p) p = &(*p)->urm;

        // Duplicam arcul din lista de adicenta
        AArc aux2 = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux2) {
        DistrG(&g); return NULL;
        }
        aux2->urm = *p; *p = aux2;
        aux2->d = s; aux2->n = x;

        aux2->uz = (float*)malloc(x * sizeof(float));
        // Tinem cont de ordinea tronsoanelor

        for ( i = 0 ; i < x ; i++ ) {
            aux2->uz[i] = aux->uz[x - i - 1];
        }
    }
    g->nume = realloc(g->nume, n * sizeof(char*));
    g->x = realloc(g->x, n * sizeof(AArc));
    g->n = n;
    free(src);
    free(dst);
    return g;
}

TGL* CitGraf2(FILE *in)
{
    TGL* g = NULL;
    int s, d;
    int x;
    AArc *p, aux;
    int n = 0;
    char *src = malloc(100);
    char *dst = malloc(100);
    g = AlocG(1000); // nu stim cate noduri are graful
    // aflam dupa ce citim tot
    if (!g) return 0;
    while (fscanf(in, "%s %s %d", src, dst, &x) == 3)
    {
        s = d = -1;
        // Caut src si dst in vectorul de nume
        int i = 0;
        for ( ; i < n; i++ ) {
            if ( strcmp(g->nume[i], src) == 0 ) {
                s = i;
            }
            if ( strcmp(g->nume[i], dst) == 0 ) {
                d = i;
            }
        }
        // nu am gasit src, il aloc
        if ( s == -1 ) {
            char *aux = malloc(strlen(src) + 1);
            strcpy(aux, src);
            g->nume[n] = aux;
            s = n;
            n++;
        }
        // nu am gasit dst, il aloc
        if ( d == -1 ) {
            char *aux = malloc(strlen(dst) + 1);
            strcpy(aux, dst);
            g->nume[n] = aux;
            d = n;
            n++;
        }
        p = g->x + s;
        while (*p) p = &(*p)->urm;
        aux = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux) {
        DistrG(&g); return NULL;
        }
        aux->urm = *p; *p = aux;
        aux->d = d; aux->c = x;
        // Duplicam arcul din lista de adicenta
        p = g->x + d;
        while (*p) p = &(*p)->urm;
        AArc aux2 = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux2) {
        DistrG(&g); return NULL;
        }
        aux2->urm = *p; *p = aux2;
        aux2->d = s; aux2->c = x;
    }
    g->nume = realloc(g->nume, n * sizeof(char*));
    g->x = realloc(g->x, n * sizeof(AArc));
    g->n = n;
    free(src);
    free(dst);
    return g;
}
