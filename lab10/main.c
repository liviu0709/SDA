#include "lista.h"

void sortareR(TListaR* L){
    TListaR anti = NULL, antj;
    for ( TListaR i = *L ; i != NULL ; anti = i, i = i->urm){
        antj = i;
        for ( TListaR j = i->urm ; j != NULL ; antj = j, j = j->urm){
             if ( i->info > j->info){
                if (i == *L) {
                    /*
                    L -> j
                    L -> i
                    */
                    if ( i->urm == j ) {
                        TListaR aux = j->urm;
                        *L = j;
                        (*L)->urm = i;
                        i->urm = aux;
                    } else {
                         /*
                        i -> ... antj -> j
                         */
                            TListaR aux = (*L)->urm, aux2 = j->urm;
                            *L = j;
                            j->urm = aux;
                            antj->urm = i;
                            i->urm = aux2;

                        }

                } else {
                    if ( i->urm == j ) {
                        /*
                        anti -> i -> j
                        anti -> j -> i
                        */
                        TListaR aux = j->urm;
                        anti->urm = j;
                        j->urm = i;
                        i->urm = aux;
                    } else {
                        /*
                        anti -> i -> ... antj -> j
                        anti -> j -> ... antj -> i
                        */
                        TListaR aux = i->urm, aux2 = j->urm;
                        anti->urm = j;
                        j->urm = aux;
                        antj->urm = i;
                        i->urm = aux2;
                        break;

                    }
                }
                    //printf("L = %lf, i = %lf, j = %lf\n", L->info, i->info, j->info);

                    //printf("L = %lf, i = %lf, j = %lf\n", L->info, i->info, j->info);

                    //printf("L->urm->info = %lf, i->urm = %lf, j->urm = %lf\n", L->urm->info, i->urm->info, j->urm->info);
                }
             //printf("L = %lf, i = %lf, j = %lf\n", L->info, i->info, j->info);
        }

    }
    printf("Inceput L: %lf\n", (*L)->info);
    for ( TListaR i = *L ; i != NULL ; anti = i, i = i->urm){
        printf("%lf ", i->info);

    }
}


int main(){

    int lg1 = 0;
    TListaR L1 = NULL;

    L1 = CitireListaR(&lg1);
    printf("Dimensiune lista: %d\n", lg1);
    AfisareListaR(L1);
    sortareR(&L1);
    AfisareListaR(L1);
    DistrugeListaR(&L1);

    getchar();
    int lg = 0;
    TListaN L = NULL;

    L = CitireListaN(&lg);
    printf("Dimensiune lista: %d\n", lg);
    AfisareListaN(L);

    DistrugeListaN(&L);
    return 0;
}