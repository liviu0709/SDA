/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void executare(TCoada *c, Tren **t, FILE *out, TCoada *caractere) {
    char comanda_curenta = ExtrQ(c);
    printf("Comanda curenta: %c\n", comanda_curenta);
    if ( comanda_curenta == '0' ) {
        moveLeft(*t);
    } else if ( comanda_curenta == '1' ) {
        moveRight(*t);
    } else if ( comanda_curenta == '2' ) {
        char cc = ExtrQ(caractere);
        // printf("Caracter citit: %c\n", cc);
        writeC(cc, *t);
    } else if ( comanda_curenta == '3' ) {
        clearCell(*t);
    } else if ( comanda_curenta == '4' ) {
        clearAll(t);
    } else if ( comanda_curenta == '5' ) {
        char cc = ExtrQ(caractere);
        insertRight(*t, cc);
    } else if ( comanda_curenta == '6' ) {
        char cc = ExtrQ(caractere);
        insertLeft(*t, cc, out);
    }
}

int main(void) {
    // Initializam trenul
    Tren *t = alocTren();

    // Deschidem fisierele
    FILE *f = fopen("tema1.in", "r");
    FILE *out = fopen("tema1.out", "w");

    // Coada de comenzi
    TCoada *c = InitQ();
    TCoada *caractere = InitQ();
    int nrComenzi;
    fscanf(f, "%d", &nrComenzi);
    for ( int i = 0 ; i < nrComenzi ; i++ ) {
        char *linie = malloc(100 * sizeof(char));
        fscanf(f, "%s", linie);
        printf("Linie: %s\n", linie);
        // afisTren(t, stdout);
        // afisQ(c);
        if ( strcmp(linie, "MOVE_LEFT") == 0 ) { // MOVE_LEFT = 0
            IntrQ(c, '0');
        } else if ( strcmp(linie, "MOVE_RIGHT") == 0 ) { // MOVE_RIGHT = 1
            IntrQ(c, '1');
        } else if ( strcmp(linie, "WRITE") == 0 ) { // WRITE = 2
            IntrQ(c, '2');
            // printf("Am ajuns aici\n");
            char cc;
            fscanf(f, " %c", &cc);
            IntrQ(caractere, cc);
        } else if ( strcmp(linie, "CLEAR_CELL") == 0 ) { // CLEAR = 3
            IntrQ(c, '3');
        } else if ( strcmp(linie, "CLEAR_ALL") == 0 ) { // CLEAR_ALL = 4
            IntrQ(c, '4');
        } else if ( strcmp(linie, "INSERT_RIGHT") == 0 ) { // INSERT_RIGHT = 5
            IntrQ(c, '5');
            char cc;
            fscanf(f, " %c", &cc);
            IntrQ(caractere, cc);
        } else if ( strcmp(linie, "INSERT_LEFT") == 0 ) { // INSERT_LEFT = 6
            IntrQ(c, '6');
            char cc;
            fscanf(f, " %c", &cc);
            IntrQ(caractere, cc);
        } else if ( strcmp(linie, "EXECUTE") == 0 ) {
            executare(c, &t, out, caractere);
            afisTren(t, stdout);
        } else if ( strcmp(linie, "SHOW") == 0 ) {
            // printf("IN SHOW\n");
            afisTren(t, out);
        } else if ( strcmp(linie, "SHOW_CURRENT") == 0 ) {
            fprintf(out, "%c\n", t->mecanic->info);
        } else if ( strcmp(linie, "SWITCH") == 0 ) {
            swapCoada(c);
            swapCoada(caractere);
        }
    }

    // Inchidem fisierele
    fclose(f);
    fclose(out);

    distrTren(&t);

}