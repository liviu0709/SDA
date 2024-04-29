/*--- test-graf.c ---*/
#include "graf-L.h"

#include <limits.h>

int minimDist(int *x, int n, int *v) {
    int minim = INT_MAX;
    int sol;
    for ( int i = 1 ; i <= n ; i++ ) {
        if ( x[i] < minim && v[i] == 0 ) {
            minim = x[i];
            sol = i;
        }
    }
    return sol;
}

void Dijkstra(TGL *G, int nod) {
    int *vizitat = calloc(G->n + 1, sizeof(int));
    int *distanta = calloc(G->n + 1, sizeof(int));
    // Punem distante infinite
    for ( int i = 1 ; i <= G->n ; i++ )
        distanta[i] = INT_MAX;
    // Init dist nod start
    distanta[nod] = 0;
    // Parcurg fiecare nod
    for ( int i = 1 ; i <= G->n ; i++ ) {
        int index = minimDist(distanta, G->n, vizitat);
        vizitat[index] = 1;
        // Parcurgem vecinii fiecarui nod
        for ( AArc l = G->x[index] ; l != NULL ; l = l->urm ) {
            // Daca gasim un drum mai ieftin, il schimbam
            if ( vizitat[l->d] == 0 )
                if ( l->c + distanta[index] < distanta[l->d] )
                    distanta[l->d] = l->c + distanta[index];
        }
    }
    printf("\nAlg Dijkstra - lista costuri: ");
    for ( int i = 1 ; i <= G->n ; i++ )
        printf("%d ", distanta[i]);
    printf("\n");
}

void algPrim(TGL *G, int nod) {
    int *vizitat = calloc(G->n + 1, sizeof(int));
    int *distanta = calloc(G->n + 1, sizeof(int));
    // Punem distante infinite
    for ( int i = 1 ; i <= G->n ; i++ )
        distanta[i] = INT_MAX;
    int *parinti = calloc(G->n + 1, sizeof(int));
    distanta[nod] = 0;
    parinti[nod] = -1;
    for ( int i = 1 ; i <= G->n ; i++ ) {
        int index = minimDist(distanta, G->n, vizitat);
        vizitat[index] = 1;
        for ( AArc l = G->x[index] ; l != NULL ; l = l->urm ) {
            if ( vizitat[l->d] == 0 ) {
                if ( l->c < distanta[l->d] ) {
                    distanta[l->d] = l->c;
                    parinti[l->d] = index;
                }
            }
        }
    }
    printf("\n Alg Prim");
    printf("\n Lista costuri: ");
    for ( int i = 1 ; i <= G->n ; i++ )
        printf("%d ", distanta[i]);
    printf("\n");
        printf("\n Lista parinti: ");
    for ( int i = 1 ; i <= G->n ; i++ )
        printf("%d ", parinti[i]);
    printf("\n");
}

int main()
{
  TGL* g;

  g = CitGrafNeorientat();
    algPrim(g, 1);
DistrG(&g);
  g = CitGraf();
  if(!g) {
    printf("-=- eroare la citire -=-\n"); return -1;
  }
  printf(" -=- graf cu %i noduri -=-\n", g->n);

  AfiGrafL(g);
    Dijkstra(g, 1);
    algPrim(g, 1);
  DistrG(&g);
  return 0;
}
