/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

// Initializare arbore
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
        // Convertim codul ascii la
        // indicii din vectorul nostru
        indice = sir[0] - 96;
    }
    // Daca nu exista deja urm litera in arb
    // o introducem
    if ( x->urm[indice] == NULL ) {
        x->urm[indice] = init();
        char *sirFirstElem = malloc(2 * sizeof(char));
        strncpy(sirFirstElem, sir, 1);
        sirFirstElem[1] = '\0';
        x->urm[indice]->data = sirFirstElem;
    }
    // Daca mai avem de adaugat, mergem mai departe
    if ( strlen(sir) > 1 ) {
        intrSuf(x->urm[indice], sir + 1);
    }
    return 0;
}

void parcLatime(Arb *x, FILE *out) {
    if ( !x )
        return;
    TCoada *noduri = InitQ();
    IntrQ(noduri, x);
    while ( noduri->inc ) {
        Arb *nodCrt = ExtrQ(noduri);
        // Daca am gasit un alt nivel
        if ( nodCrt == NULL ) {
            fprintf(out, "\n");
            // Daca mai avem alte noduri in coada
            // introducem NULL pentru delimitare...
            if ( noduri->inc )
                IntrQ(noduri, NULL);
        } else {
            // Altfel, am extras din coada un simplu nod
            if ( nodCrt != x )
                fprintf(out, "%s ", nodCrt->data);
            int i;
            for ( i = 0 ; i < 27 ; i++ ) {
                if ( nodCrt->urm[i] )
                    IntrQ(noduri, nodCrt->urm[i]);
            }
            // Pentru delimitarea nivelelor folosim NULL
            // introducem primul \n dupa ce am introdus in stiva nodurile care au ca tata radacina
            if ( nodCrt == x )
                IntrQ(noduri, NULL);
        }
    }
    DistrQ(&noduri);

}

// Calculeaza nr fii nod
int nrFii(Arb *x) {
    int cnt = 0, i;
    for ( i = 0 ; i < 27 ; i++ )
        if ( x->urm[i] )
            cnt++;
    return cnt;
}

// Calculeaza nr frunze din arbore
int nrNoduriFrunze(Arb *x) {
    // Conditie de oprire
    if ( !x )
        return 0;
    // Am gasit frunza !
    if ( nrFii(x) == 0 )
        return 1;
    // Daca nu, mai caut in nodurile urmatoare
    else {
        int i, cnt = 0;
        for ( i = 0 ; i < 27 ; i++ )
            if ( x->urm[i] )
                cnt += nrNoduriFrunze(x->urm[i]);
        return cnt;
    }
}

// Calculeaza nr sufixe de lungime k
int nrSufixe(Arb *x, int k) {
    // Conditie oprire
    if ( !x )
        return 0;
    int cnt = 0;
    // Daca nodul are un fiu cu '$'
    // si lungime sir == 0
    // => am gasit suf de lungime k
    if ( k == 0 && x->urm[0] )
        cnt++;
    int i;
    // Apelam recursiv functia pentru fiecare fiu
    for ( i = 1 ; i < 27 ; i++ )
        if ( x->urm[i] )
            cnt += nrSufixe(x->urm[i], k - 1);
    return cnt;
}

// Caut nodul cu cei mai multi fii
int nrMaxDescendenti(Arb *x) {
    int nrDsc = nrFii(x);
    int i;
    // Apelam recursiv functia pentru fiecare fiu
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] ) {
            int nrCrt = nrMaxDescendenti(x->urm[i]);
            // Daca gasesc un nod cu mai multi fii, il salvez
            if ( nrCrt > nrDsc )
                nrDsc = nrCrt;
        }
    }
    // si il returnez
    return nrDsc;
}

// Cauta un sufix in arbore
// (se apeleaza fara nodul radacina)
int cautSufix(Arb *x, char *s) {
    // Conditie de oprire
    if ( !x )
        return 0;
    // Compar prima litera cu cea din nod
    if ( x->data[0] == s[0] ) {
        // Daca am ajuns la finalul sirului
        // Am gasit sufix!
        if ( strlen(s) == 1 )
            return 1;
        // Daca nu, continuam cautarea
        int i, cnt = 0;
        for ( i = 0 ; i < 27 ; i++ ) {
            if ( x->urm[i] )
                cnt += cautSufix(x->urm[i], s + 1);
        }
        return cnt;
    }
    // Daca litera nu se potriveste ...
    // Ghinion
    return 0;

}

int cautSufArbFull(Arb *x, char *s) {
    if ( !x )
        return 0;
    // Trb sa cautam un sufix care are si final
    // nu unul care e parte din unul mai lung
    strcat(s, "$");
    int cnt = 0, i;
    // Incepem cautarea din fii nodului radacina
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] )
            cnt += cautSufix(x->urm[i], s);
    }
    return cnt;
}

// Functie apelata doar la noduri cu 1 fiu
Arb* getUrm(Arb *x) {
    int i;
    // Returneaza fiul nodului dat
    for ( i = 0 ; i < 27 ; i++ )
        if ( x->urm[i] )
            return x->urm[i];
    return NULL;
}

// Functie gandita pentru punctaj la valgrind
void DistrNod(Arb *x) {
    if ( x->data )
        free(x->data);
    free(x);
}

// Functie comprimare arb
void compresieArb(Arb *x) {
    int i;
    // Este posibila compresia !
    while ( nrFii(x) == 1 ) {
        Arb *aux = getUrm(x);
        // Conform cerinta, caracterul '$' trb sa fie separat in arborele de sufixe
        // astfel ca, nu e voie sa il compresam cu restul
        // Deci, desi nodul are doar un fiu, acesta nu trb sa fie '$'
        if ( aux->data[0] == '$' )
            break;
        // Realocam memorie pentru sirul de caractere
        // Pentru a tine sirul din nodul urm
        x->data = realloc(x->data, (strlen(x->data) + 2 + strlen(aux->data)) * sizeof(char) );
        // Adaugam sirul din nodul urm in nodul curent
        strcat(x->data, aux->data);
        // Modificam legaturile
        for ( i = 0 ; i < 27 ; i++ )
            x->urm[i] = aux->urm[i];
        // Stergem nodul care a fost comprimat
        DistrNod(aux);
    }
    // Apelam recursiv functia pentru fiecare fiu
    for ( i = 0 ; i < 27 ; i++ ) {
        if ( x->urm[i] )
            compresieArb(x->urm[i]);
    }
}

// Vrem punctaj pe valgrind, deci...
void DistrArb( Arb **x ) {
    if ( *x )  {
        int i;
        if ( (*x)->data )
            free((*x)->data);
        for ( i = 0 ; i < 27 ; i++)
            if ( (*x)->urm[i] )
                DistrArb( &(*x)->urm[i] );
        free(*x);
    }
}