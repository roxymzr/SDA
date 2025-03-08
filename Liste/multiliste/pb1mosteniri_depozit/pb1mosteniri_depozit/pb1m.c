#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct palet {
	int cod;
	struct palet* urm;
}palet;

typedef struct depozit {
	char nume[20];
	palet* prim;
	palet* ultim;
	struct depozit* urm;
}depozit;

typedef struct {
	depozit* prim;
	depozit* ultim;
}Depozite;

void depozit_init(depozit* d) {
	d->prim = d->ultim = NULL;
	d->urm = NULL;
}

void depozite_init(Depozite* d) {
	d->prim = d->ultim = NULL;
}

palet* palet_nou(int cod) {
	palet* e = (palet*)malloc(sizeof(palet));
	if (e == NULL) {
		printf("ERoare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->cod = cod;
	e->urm = NULL;
	return e;
}

depozit* depozit_nou(char nume[20]) {
	depozit* e = (depozit*)malloc(sizeof(depozit));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	depozit_init(e);
	strcpy(e->nume, nume);

	return e;
}

void adaugarePalet(depozit* d, int cod) {
	if (d->prim == NULL) {
		d->prim = d->ultim = palet_nou(cod);
	}
	else {
		palet* aux = palet_nou(cod);
		d->ultim->urm = aux;
		d->ultim = aux;
	}
}

void adaugareDepozit(Depozite* dep, depozit* d) {
	if (dep->prim == NULL) {
		dep->prim = dep->ultim = d;
	}
	else {

		dep->ultim->urm = d;
		dep->ultim = d;
	}
}

void afisareDepozit(depozit* d) {
	for (palet* p = d->prim; p != NULL; p = p->urm) {
		printf("%d ", p->cod);
	}printf("\n");
}

void afisareDepozite(Depozite* d) {
	for (depozit* d1 = d->prim; d1 != NULL; d1 = d1->urm) {
		puts(d1->nume);
		afisareDepozit(d1);
	}
}

void eliberareDepozit(depozit* d) {
	palet* p = d->prim;
	while (p != NULL) {
		palet* aux = p->urm;
		free(p);
		p = aux;
	}
}

void eliberareDepozite(Depozite* d) {
	depozit* d1 = d->prim;
	while (d1 != NULL) {
		depozit* aux = d1->urm;
		eliberareDepozit(d1);
		free(d1);
		d1 = aux;
	}
}

void stergere(depozit* d, int cod) {
	if (d->prim->cod == cod) {
		palet* aux = d->prim->urm;
		free(d->prim);
		d->prim = aux;
	}
	else if (d->ultim->cod == cod) {
		palet* aux = d->prim;
		for (;aux->urm != d->ultim;aux = aux->urm) {}
		aux->urm = NULL;
		free(d->ultim);
		d->ultim = aux;
	}
	else {
		palet* c = d->prim;
		palet* p = NULL;
		for (; c != NULL; p = c, c = c->urm) {
			if (c->cod == cod) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void eliminarePalet(Depozite* d, int cod) {
	for (depozit* d1 = d->prim; d1 != NULL; d1 = d1->urm) {
		stergere(d1, cod);
	}
}

int main(void) {
	Depozite depozite;
	depozite_init(&depozite);

	depozit* d1 = NULL, * d2 = NULL, * d3 = NULL;
	d1 = depozit_nou("Depozit1");
	d2 = depozit_nou("Depozit2");
	d3 = depozit_nou("Depozit3");

	for (int i = 1; i < 6; i++) {
		adaugarePalet(d1, i);
	}

	for (int i = 1; i < 6; i++) {
		adaugarePalet(d2, i * 2);
	}

	for (int i = 1; i < 6; i++) {
		adaugarePalet(d3, i * 3);
	}

	adaugareDepozit(&depozite, d1);
	adaugareDepozit(&depozite, d2);
	adaugareDepozit(&depozite, d3);

	afisareDepozite(&depozite);

	printf("Dupa eliminare:\n");
	eliminarePalet(&depozite, 3);
	afisareDepozite(&depozite);

	eliberareDepozite(&depozite);
	return 0;
}