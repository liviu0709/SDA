/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

int numara(TArb r) {
	if ( r ) {
		if ( r->dr && r->st ) {
			if ( r->dr->info + r->st->info < r->info * 2 )
				return 1 + numara(r->dr) + numara(r->st);
			else
				return numara(r->dr) + numara(r->st);
		}
	} else
		return 0;
}

int parcurgeSDR(TArb r) {
	if ( r ) {
		if ( !(r->st) && r->dr ) {
			int cnt = parcurgeSDR(r->st);
			cnt += parcurgeSDR(r->dr);
			printf("%d ", r->info);
			return 1 + cnt;
		} else
			return parcurgeSDR(r->st) + parcurgeSDR(r->dr);
	} else
		return 0;
}

_Bool verifica(TArb r) {
	// Arbore vid
	if ( !r ) return 0;
	if ( r->dr == NULL && r->st == NULL )
		// Daca este frunza, este bine
		return 1;
	else {
		if ( !(r->dr && r->st) )
			// Nu e frunza, dar nu are 2 fii
			return 0;
		else
			// Continuam verificarea
			return verifica(r->st) && verifica(r->dr);
	}
}

int main ()
{
	TArb arb = NULL;
	
	randomize();
	arb = ConstrAA (5, random(20), -50, 50);

	AfiArb (arb);
	printf("Numara: %d\n", numara(arb));
	printf("Noduri doar cu fiu drept: ");
	printf("\nNr noduri afisate: %d\n", parcurgeSDR(arb));
	if ( verifica(arb) )
		printf("Toate nodurile interne au doi fii\n");
	else
		printf("Nu toate nodurile interne au doi fii\n");
	printf ("noduri: %i\n", NrNoduri(arb));

	/*-- se completeaza cu apelurile functiilor implementate --*/
	
	DistrArb (&arb);
	return 0;
}
