/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

Arb* init() {
    Arb *x = malloc(sizeof(Arb));
    x->data = NULL;
    int i;
    for ( i = 0 ; i < 27 ; i++ )
        x->urm[i] = NULL;
    return x;
}

int intrSuf(Arb *x, char *sir) {
    // Daca sir[0] == '$', lasam asa
    int indice = 0;
    if ( sir[0] != '$') {
        indice = sir[0] - 96;
        // printf("Sirul este: %s\n", sir);
        // printf("Hai ca merge daca e \n");
    }
    if ( x->urm[indice] == NULL ) {
        x->urm[indice] = init();
        char *sirFirstElem = malloc(2 * sizeof(char));
        strncpy(sirFirstElem, sir, 1);
        sirFirstElem[1] = '\0';
        x->urm[indice]->data = sirFirstElem;
        // printf("Am adaugat: %s\n", x->urm[indice]->data);
    }
    if ( strlen(sir) > 1 ) {
        intrSuf(x->urm[indice], sir + 1);
    }
    return 0;
}

void parcLatime(Arb *x) {
    if ( !x )
        return;
    int i, ok = 0;
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] ) {
            ok = 1;
            printf("%s ", x->urm[i]->data);
        }
    }
    if ( ok )
        printf("\n");
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] ) {
            parcLatime(x->urm[i]);
        }
    }

}