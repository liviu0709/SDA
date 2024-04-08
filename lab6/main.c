#include "heap.h"

void insHeap(THeap *H, int val) {
    if( H->nrElem < H->nrMax ) {
        H->nrElem++;
        int D = H->nrElem - 1;
        int i = 0;
        int parinte = 0;
        int st = 2 * i + 1;
        int dr = 2 * i + 2;
        while ( D && !H->comp(H->v[(D - 1) / 2], val) ) {
            H->v[D] = H->v[(D - 1) / 2];
            D = (D - 1) / 2;
        }
        H->v[D] = val;
        
    }
}

int extrHeap(THeap *H) {
    int sol = H->v[0];
    int D = 0;
    H->nrElem--;
    int t = H->v[H->nrElem];
    H->v[0] = t;
    while ( 2 * D + 1 < H->nrElem ) {
        int s = 2 * D + 1;
        if ( 2 * D + 2 < H->nrElem && ! H->comp(H->v[s], H->v[2 * D + 2]) ) {
            s = 2 * D + 2;
        }
        if ( H->comp(H->v[D], H->v[s]) )
            break;
        else {
            int aux = H->v[D];
            H->v[D] = H->v[s];
            H->v[s] = aux;
            D = s;
        }
    }
    return sol;
}

void testare(int (*f)(int, int)) {
    int v[] = {2, 5, 3, 4, 7, 9};
    int dimVec = sizeof(v) / sizeof(v[0]);
    THeap *h = AlocaHeap(dimVec, f);
    for (int i = 0; i < dimVec; i++) {
        // h->nrElem++;
        // h->v[i] = v[i];
        insHeap(h, v[i]);
    }
    AfisareHeap(h, 0);
    printf("\nAm extras: %d\n", extrHeap(h));
    AfisareHeap(h, 0);
    printf("\n");
    DistrugeHeap(&h);
}

int main() {
    // int v[] = {2, 5, 3, 4, 7, 9};
    // int dimVec = sizeof(v) / sizeof(v[0]);
    // THeap* h = NULL;
    // h = AlocaHeap(dimVec, RelMaxHeap);
    // //h = AlocaHeap(dimVec, RelMinHeap);
    // for (int i = 0; i < dimVec; i++) {
    //     // h->nrElem++;
    //     // h->v[i] = v[i];
    //     insHeap(h, v[i]);
    // }
    // AfisareHeap(h ,0);
    printf("MinHeap:\n");
    testare(RelMinHeap);
    //printf("\nAm extras: %d", extrHeap(h));
    //printf("\n");
    //AfisareHeap(h, 0);
    //printf("\n");
    printf("MaxHeap:\n");
    testare(RelMaxHeap);
}