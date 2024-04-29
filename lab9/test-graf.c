/*--- test-graf.c ---*/
#include "graf-L.h"

void Dijkstra(TGL *G, int nod) {

}

int main()
{
  TGL* g;

  g = CitGraf();
  if(!g) {
    printf("-=- eroare la citire -=-\n"); return -1;
  }
  printf(" -=- graf cu %i noduri -=-\n", g->n);

  AfiGrafL(g);

  DistrG(&g);
  return 0;
}
