#include "lista.h"

TLista muta(TLista *l, int k, int *nrElem) {
    TLista sol = NULL, aux, ant = NULL;
    *nrElem = 0;
    for ( aux = *l ; aux != NULL ; ) {
        if ( aux->info % k == 0 ) {
            (*nrElem)++;
            if ( aux == *l ) {
                *l = aux->urm;
            } else {
                if ( aux->urm == NULL )
                    ant->urm = NULL;
                else {
                    if ( ant )
                        ant->urm = aux->urm;
                    else
                        *l = aux->urm;
                }
            }
			
            // Inserare ordonata
            TLista antsol, solaux, aux2 = aux;
            ant = aux;
			aux = aux->urm;
            for ( antsol = NULL, solaux = sol ; solaux != NULL && solaux->info < aux2->info ; antsol = solaux, solaux = solaux->urm );
            if ( antsol ) {
                aux2->urm = solaux;
                // aux2->urm = NULL; 
                antsol->urm = aux2;
                // antsol->urm = NULL;
            } else { 
                aux2->urm = sol;
                sol = aux2;
            }
        } else {
            ant = aux;
			aux = aux->urm;
		}
    }
    return sol;
}

TLista copie(TLista l, int a, int b, int *nrEl) {
    TLista sol = NULL, aux, ultim = NULL;
    *nrEl = 0;
    for ( aux = l ; aux != NULL ; aux = aux->urm ) {
        if ( aux->info >= a && aux->info <= b ) {
            TLista aux2 = AlocCelula(aux->info);
            if ( sol ) {
                ultim->urm = aux2;
                ultim = aux2;
            } else {
                sol = ultim = aux2;
            }
            (*nrEl)++;
        }
    }
    return sol;
}

int main(){
    int lg = 0;
    TLista L = NULL;

    L = CitireLista(&lg);
    printf("Dimensiune lista: %d\n", lg);
    AfisareLista(L);
    AfisareLista(muta(&L, 2, &lg));
    AfisareLista(L);
    printf("Nr elemente mutate: %d\n", lg);
    DistrugeLista(&L);
    getchar();
    L = CitireLista(&lg);
    AfisareLista(copie(L, 2, 7, &lg));
    printf("Nr elemente copiate: %d\n", lg);
    AfisareLista(L);
    DistrugeLista(&L);
    return 0;
}