#include "arbBC.h"

/* Aloca un element de tip Arb si returneaza pointerul aferent */
TArb Constr_Frunza(int elem) {
    TArb aux = (TArb) malloc(sizeof(TNod));
    if (!aux) 
        return NULL;

    aux->info = elem;
    aux->st = aux->dr = NULL;

    return aux;
}


int InserareABC(TArb *arbore, int elem) {
    TArb p, n, aux;
    
    if(*arbore == NULL) {
        *arbore = Constr_Frunza(elem);
        if(!*arbore) return 0;
        return 1;
    }

    n = *arbore;
    while (n) {
        if (elem == n->info) 
            return 0;

        p = n;
        if (elem > n->info) 
            n = n->dr;
        else 
            n = n->st;
    }

    aux = Constr_Frunza(elem);
    if(!aux)
        return 0;
    if(p->info > elem)
        p->st = aux;
    else    
        p->dr = aux;
    return 1;
}

int numara(TArb a, int x) {
	if (!a) {
		return 0;
	}
	int cnt = numara(a->dr, x);
	if ( a->info < x ) {
		printf("%d ", a->info);
		cnt++;
	}
	return cnt + numara(a->st, x);
}

int numaraNoPrintf(TArb a, int x) {
	if (!a) {
		return 0;
	}
	int cnt = numara(a->dr, x);
	if ( a->info < x ) {
		// printf("%d ", a->info);
		cnt++;
	}
	return cnt + numaraNoPrintf(a->st, x);
}

int cautX(TArb a, int x, int nivel) {
	if(!a) return 0;
	int sol = 0;
	if ( a->info < x ) {
		sol = nivel;
	}
	return sol + cautX(a->dr, x, nivel + 1) + cautX(a->st, x, nivel + 1);
}

int verifica(TArb a, int x, int nivel) {
	if ( numaraNoPrintf(a, x) == 1 )
		return cautX(a, x, 1);
	return -1;
}

void duplica(TArb x) {
	if ( !x ) return;
	if ( x->dr == NULL && x->st != NULL) {
		TArb aux = Constr_Frunza(x->info);
		aux->st = x->st;
		x->st = aux;
		x = x->st;
	} else {
		if ( x->st == NULL && x->dr != NULL ) {
			TArb aux = Constr_Frunza(x->info);
			aux->dr = x->dr;
			x->dr = aux;
			x = x->dr;
		}
	}
	duplica(x->dr);
	duplica(x->st);
}

void SRD(TArb x) {
	if( !x ) return; 
	SRD(x->st);
	printf("%d ", x->info);
	SRD(x->dr);
}

void duplicaArb(TArb x) {
	duplica(x);
	SRD(x);
}

/* Parcurgere Radacina - Stanga - Dreapta */
void RSD(TArb a) {
	if (!a) {
        printf("-"); 
        return;
    }
	
    if (!a->st && !a->dr) {          /* conditie frunza */
        printf(" %d ", a->info);      
        return;
    }
	
    printf(" %d ", a->info);
	printf("(");
	
    RSD(a->st);                      /* apelare recursiva */
	printf(",");
	
    RSD(a->dr);                      /* apelare recursiva */
	printf(")");
}

/* Dezalocare memorie arbore */
void DistrugeArb(TArb* adrArbore) {
    if (!(*adrArbore)) {
        return;
    }

    DistrugeArb(&(*adrArbore)->st);
    DistrugeArb(&(*adrArbore)->dr);

    free(*adrArbore);
}

void Repr(TArb r, int centru, int linie, int dif, char desen[18][81], char cri[], int limita)
/*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie+1
	 dif - distanta pe orizontala intre r si fiecare dintre cei doi descendenti
	 Exemple:  dif = 5    |        dif = 2    |
					 xxx                 xxx
				___/ \___              / \
			 |         |            |   |                               -*/
{
	int k;

	if (linie > limita) return;
	if (dif <= 1) {      /* spatiu de afisare insuficient -> ... */
		memset(desen[linie]+centru, '.', 3);
		return;
	}
	desen[linie][centru] = '|';      /* legatura spre nod */
	desen[linie][0] = ':';
	if (linie+1 > limita) return;
	sprintf(cri, "%3i", r->info);   /* converteste valoare info la 3 caractere */
	k = (cri[0] == ' ') ? 2 : 1;    /* decalaj fata de centru */
	memcpy(desen[linie+1] + centru - k, cri, 3); /* copiaza cele 3 caractere in desen */
	desen[linie+1][0] = ':';
	if (linie+2 > limita) return;
	if (r->st) {
		desen[linie+2][centru-1] = '/';                     /* reprezinta ramura  ____/  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset(desen[linie+2] + centru - dif + 1, '_', dif-2);
		Repr(r->st, centru - dif, linie + 3, (dif+1)/2, desen, cri, limita);   /* si subarborele stang */
	}
	if (r->dr) {
		desen[linie + 2][centru+1] = '\\';                  /* reprezinta ramura  \____  */
		desen[linie+2][0] = ':'; desen[linie+3][0] = ':';
		memset (desen[linie+2] + centru + 2, '_', dif-2);
		Repr(r->dr, centru + dif, linie + 3, (dif+1)/2, desen, cri, limita );   /* si subarborele drept */
	}
}

/*- afiseaza arborele r -*/
void AfiArb(TArb r) 
{
	int j;
	char desen[18][81], cri[] = "xxx";  /* zona reprezentare arbore, info */
	int limita = 17; 

	for (j = 0; j <= limita; j++)
		memset (desen[j], ' ', 79);
	if (!r)
		printf ("%49s", "-=- Arbore VID -=-");
	else {
		Repr(r,40,0,19, desen, cri, limita); /* preg reprezentare cu centrul in coloana 39 a primei linii */
		for (j = 0; j <= limita && desen[j][0] == ':'; j++) {
			desen[j][79] = '\0'; printf("%s\n", desen[j]+1);
		}
	}
	printf ("\n");
}