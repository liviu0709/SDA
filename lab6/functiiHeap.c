#include "heap.h"

THeap* AlocaHeap(int nrMax, TFCmp comp) {
    THeap* h = (THeap*) malloc(sizeof(struct Heap));
    if (!h) {
        return NULL;
    }

    h->v = (int *) malloc(nrMax * sizeof(int));
    if (!h->v) {
		free(h);
		return NULL;
	}

    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;

    return h;
}

int RelMinHeap(int a, int b) {
	return a < b;
}

int RelMaxHeap(int a, int b) {
	return a > b;
}

void AfisareHeap(THeap* h, int pos) {
    if (pos >= h->nrMax) {      
        printf("-"); 
        return;
    }
    
    printf(" %d ", h->v[pos]);
	printf("(");
	
    AfisareHeap(h, 2 * pos + 1);
	printf(",");
	
    AfisareHeap(h, 2 * pos + 2);
	printf(")");
}

void DistrugeHeap(THeap **h) {
	free((*h)->v);
	free(*h);
	*h = NULL; 
}