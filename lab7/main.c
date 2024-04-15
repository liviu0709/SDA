/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

int nrFrunze( TArb arb ) {
    if ( !arb )
        return 0;
    if ( arb->st == NULL && arb->dr == NULL )
        return 1;
    int cnt = 0;
    if ( arb->st )
        cnt = nrFrunze(arb->st);
    if ( arb->dr )
        cnt += nrFrunze(arb->dr);
    return cnt;
}

int nivMinFrunza( TArb arb ) {
    if ( !arb )
        return 0;
    if ( arb->dr == NULL && arb->st == NULL )
        return 1;
    int stanga, dreapta;
    if ( arb->st )
        stanga = nivMinFrunza(arb->st);
    if ( arb->dr )
        dreapta = nivMinFrunza(arb->dr);
    if ( arb->st && ! arb->dr )
        return stanga + 1;
    if ( arb->dr && ! arb->st )
        return dreapta + 1;
    if ( stanga < dreapta && arb->dr && arb->dr )
        return stanga + 1;
    else
        return dreapta + 1;
}

int auxProc( int nivel, TArb arb, int n ) {
    int foarteBine = 0;
    if ( nivel > n && arb->info % 2 == 0 ) {
        foarteBine = 1;
        // printf("Am gasit: %d\n", arb->info);
    }
    if ( !arb->st && !arb->dr )
        return foarteBine;
    int stanga, dreapta;
    if ( arb->st )
        stanga = auxProc(nivel + 1, arb->st, n);
    if ( arb->dr )
        dreapta = auxProc(nivel + 1, arb->dr, n);
    if ( arb->st && ! arb->dr )
        return stanga + foarteBine;
    if ( arb->dr && ! arb->st )
        return dreapta + foarteBine;
    return stanga + dreapta + foarteBine;
}

int NrNoduriNiv( int nivel, TArb arb, int n) {
    if ( !arb )
        return 0;
    int ok = 0;
    if ( nivel > n )
        ok++;
    if ( !arb->dr && !arb->st)
        return ok;
    if ( arb->dr && !arb->st)
        return ok + NrNoduriNiv(nivel + 1, arb->dr, n);
    if ( arb->st && !arb->dr )
        return ok + NrNoduriNiv(nivel + 1, arb->st, n);
    return ok + NrNoduriNiv(nivel + 1, arb->st, n) + NrNoduriNiv(nivel + 1, arb->dr, n);
}

float procent(TArb arb, int n) {
    if ( !arb )
        return 0;
    int dreapta = 0, stanga = 0, rad = 0;
    if ( arb->st )
        stanga = auxProc(2, arb->st, n);
    if ( arb->dr )
        dreapta = auxProc(2, arb->dr, n);
    // printf("Stanga: %d\n", stanga);
    // printf("Dreapta: %d\n", dreapta);
    if ( 1 > n && arb->info % 2 == 0 )
        rad = 1;
    // printf("Nr noduri pe nivel sub n: %d\n", NrNoduriNiv(1, arb, n));
    if ( NrNoduriNiv(1, arb, n) )
        return (float)(stanga + dreapta + rad) / NrNoduriNiv(1, arb, n) * 100;
    else
        return -1;
}

int main ()
{
	TArb arb = NULL;

	randomize();
	arb = ConstrAA (5, random(20), -50, 50);

	AfiArb (arb);
	printf ("noduri: %i\n", NrNoduri(arb));

	/*-- se completeaza cu apelurile functiilor implementate --*/
    printf("Nr frunze: %d\n", nrFrunze(arb));
    printf("Nivel minim frunze: %d\n", nivMinFrunza(arb));
    printf("Sfantul procent: %lf", procent(arb, 2));
	DistrArb (&arb);
	return 0;
}
