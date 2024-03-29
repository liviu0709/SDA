/* STOICA Liviu-Gabriel - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void executare(TCoada *c, Tren **t, FILE *out, TCoada *arg) {
    char *comanda = ExtrQ(c);
    char comanda_curenta = comanda[0];
    free(comanda);
    // printf("Comanda curenta: %c\n", comanda_curenta);
    if ( comanda_curenta == '0' ) {
        moveLeft(*t);
    } else if ( comanda_curenta == '1' ) {
        moveRight(*t);
    } else if ( comanda_curenta == '2' ) {
        char *cc = ExtrQ(arg);
        // printf("Caracter citit: %c\n", cc);
        writeC(cc[0], *t);
        free(cc);
    } else if ( comanda_curenta == '3' ) {
        clearCell(*t);
    } else if ( comanda_curenta == '4' ) {
        clearAll(t);
    } else if ( comanda_curenta == '5' ) {
        char *cc = ExtrQ(arg);
        insertRight(*t, cc[0]);
        free(cc);
    } else if ( comanda_curenta == '6' ) {
        char *cc = ExtrQ(arg);
        insertLeft(*t, cc[0], out);
        free(cc);
    } else if ( comanda_curenta == '7' ) {
        char *s = ExtrQ(arg);
        printf("Cuvantul citit: %s\n", s);
        search(*t, s, out);
        free(s);
    } else if ( comanda_curenta == '8' ) {
        char *s = ExtrQ(arg);
        searchLeft(*t, s, out);
        free(s);
    } else if ( comanda_curenta == '9' ) {
        char *s = ExtrQ(arg);
        searchRight(*t, s, out);
        free(s);
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
    TCoada *arg = InitQ();
    
    int nrComenzi;
    fscanf(f, "%d", &nrComenzi);
    char *linie = malloc(100 * sizeof(char));
    for ( int i = 0 ; i < nrComenzi ; i++ ) {
        
        fscanf(f, "%s", linie);
        // printf("Linie: %s\n", linie);
        // afisTren(t, stdout);
        // afisQ(c);
        if ( strcmp(linie, "MOVE_LEFT") == 0 ) { // MOVE_LEFT = 0
            IntrQ(c, "0");
        } else if ( strcmp(linie, "MOVE_RIGHT") == 0 ) { // MOVE_RIGHT = 1
            IntrQ(c, "1");
        } else if ( strcmp(linie, "WRITE") == 0 ) { // WRITE = 2
            IntrQ(c, "2");
            // printf("Am ajuns aici\n");
            char *cc = malloc(sizeof(char) * 2);
            fscanf(f, " %s", cc);
            IntrQ(arg, &cc[0]);
            free(cc);
        } else if ( strcmp(linie, "CLEAR_CELL") == 0 ) { // CLEAR = 3
            IntrQ(c, "3");
        } else if ( strcmp(linie, "CLEAR_ALL") == 0 ) { // CLEAR_ALL = 4
            IntrQ(c, "4");
        } else if ( strcmp(linie, "INSERT_RIGHT") == 0 ) { // INSERT_RIGHT = 5
            IntrQ(c, "5");
            char *cc = malloc(sizeof(char) * 2);
            fscanf(f, " %s", cc);
            IntrQ(arg, &cc[0]);
        } else if ( strcmp(linie, "INSERT_LEFT") == 0 ) { // INSERT_LEFT = 6
            IntrQ(c, "6");
            char *cc = malloc(sizeof(char) * 2);
            fscanf(f, " %s", cc);
            IntrQ(arg, &cc[0]);
        } else if ( strcmp(linie, "EXECUTE") == 0 ) {
            executare(c, &t, out, arg);
            // afisTren(t, stdout);
        } else if ( strcmp(linie, "SHOW") == 0 ) {
            // printf("IN SHOW\n");
            afisTren(t, out);
        } else if ( strcmp(linie, "SHOW_CURRENT") == 0 ) {
            fprintf(out, "%c\n", t->mecanic->info);
        } else if ( strcmp(linie, "SWITCH") == 0 ) {
            swapCoada(c);
            swapCoada(arg);
        } else if ( strcmp(linie, "SEARCH") == 0 ) { // SEARCH = 7
            IntrQ(c, "7");
            char *s = malloc(100 * sizeof(char));
            printf("Am ajuns aici\n");
            fscanf(f, " %s", s);
            IntrQ(arg, s);
            free(s);
        } else if ( strcmp(linie, "SEARCH_LEFT") == 0 ) { // SEARCH_LEFT = 8
            IntrQ(c, "8");
            char *s = malloc(100 * sizeof(char));
            fscanf(f, " %s", s);
            IntrQ(arg, s);
            free(s);
        } else if ( strcmp(linie, "SEARCH_RIGHT") == 0 ) { // SEARCH_RIGHT = 9
            IntrQ(c, "9");
            char *s = malloc(100 * sizeof(char));
            fscanf(f, " %s", s);
            IntrQ(arg, s);
            free(s);
        }
    }

    // Inchidem fisierele
    fclose(f);
    fclose(out);

    // Eliberam memoria
    free(linie);
    DistrQ(&c);
    DistrQ(&arg);
    distrTren(&t);

}