#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produs {
	int cod;
	struct produs* urm;
}produs;

typedef struct Magazin {
	produs* prim;
	produs* ultim;
	char nume[20];
	struct Magazin* urm;
}Magazin;

typedef struct {
	Magazin* prim;
	Magazin* ultim;
}Magazine;

void magazin_init(Magazin* m) {
	m->prim = m->ultim = NULL;
	m->urm = NULL;
}

void magazine_init(Magazine* m) {
	m->prim = m->ultim = NULL;
}

produs* produs_nou(int cod) {
	produs* e = (produs*)malloc(sizeof(produs));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->cod = cod;
	e->urm = NULL;
	return e;
}

Magazin* magazin_nou(char nume[20]) {
	Magazin* e = (Magazin*)malloc(sizeof(Magazin));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	magazin_init(e);
	return e;
}

void adaugareProdus(Magazin* m, int cod) {   //adaugare si pt cazul in care produsele nu sun ord crescator dupa cod, asa ca le si ordonam cand le adaugam
	if (m->prim == NULL) {
		m->prim = m->ultim = produs_nou(cod);
	}

	else {
		produs* prod = produs_nou(cod);
		if (m->prim->cod > cod) {
			prod->urm = m->prim;
			m->prim = prod;
		}
		else {
			produs* c = m->prim->urm;
			produs* p = m->prim;
			int flag = 0;
			for (; c != NULL; p = c, c = c->urm) {
				if (c->cod > cod) {
					p->urm = NULL;
					prod->urm = c;
					p->urm = prod;
					flag = 1;
					//c = prod;
					break;
				}
			}
			if (!flag) {
				produs* aux = produs_nou(cod);
				m->ultim->urm = aux;
				m->ultim = aux;
			}
		}



	}
}


void adaugareMagazin(Magazine* m, Magazin* m1) {
	if (m->prim == NULL) {
		m->prim = m->ultim = m1;
	}
	else {
		m->ultim->urm = m1;
		m->ultim = m1;

	}
}

void afisareMagazin(Magazin* m) {

	for (produs* p = m->prim; p != NULL; p = p->urm) {
		printf("%d ", p->cod);
	}printf("\n");
}

void afisareMagazine(Magazine* m) {
	for (Magazin* m1 = m->prim; m1 != NULL; m1 = m1->urm) {
		puts(m1->nume);
		afisareMagazin(m1);
	}
}

void eliberareMagazin(Magazin* m) {
	produs* p = m->prim;
	while (p != NULL) {
		produs* aux = p->urm;
		free(p);
		p = aux;
	}
}

void eliberareMagazine(Magazine* m) {
	Magazin* m1 = m->prim;
	while (m1 != NULL) {
		Magazin* aux = m1->urm;
		eliberareMagazin(m1);
		free(m1);
		m1 = aux;
	}
}

void sterge(Magazin* m, int cod) {
	if (m->prim->cod == cod) {
		produs* aux = m->prim->urm;
		free(m->prim);
		m->prim = aux;
	}
	else if (m->ultim->cod == cod) {
		produs* c = m->prim;
		for (; c->urm != m->ultim; c = c->urm) {}
		c->urm = NULL;
		free(m->ultim);
		m->ultim = c;
	}
	else {
		produs* c = m->prim;
		produs* p = NULL;
		for (; c->urm != m->ultim; p = c, c = c->urm) {
			if (c->cod == cod) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void eliminareProdus(Magazine* m, int cod) {
	for (Magazin* m1 = m->prim; m1 != NULL; m1 = m1->urm) {
		sterge(m1, cod);
	}
}

int main(void) {
	Magazine magazine;
	magazine_init(&magazine);

	Magazin* m1 = NULL, * m2 = NULL, * m3 = NULL;
	m1 = magazin_nou("Magazin1");
	m2 = magazin_nou("Magazin2");
	m3 = magazin_nou("Magazin3");

	for (int i = 1; i < 6; i++) {
		adaugareProdus(m1, i);
	}

	for (int i = 6; i > 0; i--) {
		adaugareProdus(m2, i * 2);
	}

	for (int i = 1; i < 6; i++) {
		adaugareProdus(m3, i * 3);
	}

	adaugareMagazin(&magazine, m1);
	adaugareMagazin(&magazine, m2);
	adaugareMagazin(&magazine, m3);



	afisareMagazine(&magazine);

	printf("Dupa stergere:");
	eliminareProdus(&magazine, 3);
	afisareMagazine(&magazine);


	eliberareMagazine(&magazine);

	return 0;
}