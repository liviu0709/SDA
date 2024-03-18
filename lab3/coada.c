/*-- TcoadaLD1.c -- coada este reprezentata ca Lista circulara simplu inlantuita
                 -- Operatii de baza --*/
#include "tcoada.h"


TCoada* InitQ (void)  /* creeaza coada vida */
{ 
  TCoada* c;          /* spatiu pentru descriptor coada */
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( ! c ) return NULL;                  /* nu exista spatiu -> "esec" */

  c->sf = NULL;
  return c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, int x)  /* adauga element la sfarsitul cozii */
 /* intoarce 1: operatie reusita, 0: in caz contrar */
{
  //printf("Am ajuns in IntrQ\n");
  TCelula* aux = (TCelula*)malloc(sizeof(TCelula));
  
  if ( !aux ) return 0;
  aux->info = x;
  if ( c->sf ) {
    aux->urm = c->sf->urm;
    c->sf->urm = aux;
    c->sf = aux;
    //printf("Am legat %d\n", x);
  } else {
    c->sf = aux;
    c->sf->urm = aux;
  }
  return 1;             
}

int ExtrQ(TCoada *c, int *x)  /* extrage primul element din coada la adresa ae */
/* intoarce 1: operatie reusita, 0: in caz contrar */
{
  if ( ! c->sf ) return 0;
  if ( c->sf != c->sf->urm ) {
    *x = c->sf->urm->info;
    TLista aux = c->sf->urm;
    c->sf->urm = aux->urm;
    free(aux);
  } else {
    *x = c->sf->info;
    free(c->sf);
    c->sf = NULL;
  }
  
  return 1;                
}

void DistrQ(TCoada **c) /* distruge coada */
{
  if ( !(*c)->sf ) return;
  TLista inceput = (*c)->sf->urm;
  (*c)->sf->urm = NULL;
  for ( TLista aux = inceput  ; aux != NULL ; ) {
    TLista aux2 = aux;
    aux = aux->urm;
    free(aux2);
  }
  free(*c);

}

void AfisareQ(TCoada *c)  /* afisare elementele cozii */
{
  if(!c->sf) return;
  TLista aux = c->sf->urm;
  printf("[");
  if ( c->sf->urm != c->sf ) {
    printf("%d ", c->sf->urm->info);
    for ( TLista j = c->sf->urm->urm ; j != aux ; j = j->urm ) {
      printf("%d ", j->info);
    }
  } else {
    printf("%d", c->sf->info);
  }
  printf("]\n");
}