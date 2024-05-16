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

// Copiem un graf
TGL* Copy(TGL *src) {
    TGL *dst = AlocG(src->n);
    for ( int i = 0 ; i < src->n ; i++ ) {
        dst->nume[i] = malloc(strlen(src->nume[i]) + 1);
        strcpy(dst->nume[i], src->nume[i]);
        AArc l = src->x[i];
        for ( ; l != NULL ; l = l->urm ) {
            AArc aux = (TCelArc*)calloc(sizeof(TCelArc),1);
            aux->d = l->d;
            aux->c = l->c;
            aux->n = l->n;
            aux->uz = (float*)malloc(l->n * sizeof(float));
            for ( int j = 0 ; j < l->n ; j++ ) {
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


void DistrG(TGL** ag)
{
    int i;
    AArc p, aux;
    for(i = 0; i < (*ag)->n; i++){
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
        for (int i = 0; i < n; i++) {
            if ( strcmp(g->nume[i], src) == 0 ) {
                s = i;
            }
            if ( strcmp(g->nume[i], dst) == 0 ) {
                d = i;
            }
        }
        // nu am gasit src, il aloc
        if ( s == -1 ) {
            char *aux = malloc(sizeof(strlen(src)) + 1);
            strcpy(aux, src);
            g->nume[n] = aux;
            s = n;
            n++;
        }
        // nu am gasit dst, il aloc
        if ( d == -1 ) {
            char *aux = malloc(sizeof(strlen(dst)) + 1);
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
        for ( int i = 0 ; i < x ; i++ ) {
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
        for ( int i = 0 ; i < x ; i++ ) {
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

void AfiGrafL(TGL * g)
{
  AArc l;
  int i;

  for(i = 0; i < g->n; i++){
    l = g->x[i];
    if(!l)
      printf("%s: - ", g->nume[i]);
    else
      printf("%s: ", g->nume[i]);
    for(; l != NULL; l = l->urm) {
        //skipp %d l->c
      printf(" %s () [", g->nume[l->d]);
      for( int i = 0 ; i < l->n ; i++ )
        printf(" %.2f", l->uz[i]);
    printf("]");
    }
    printf("\n");
  }
}

// Pointer arc return + index src efect lateral
AArc getArc(TGL *g, char* src, char* dst, int *s) {
    int d;
    for (int i = 0; i < g->n; i++) {
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