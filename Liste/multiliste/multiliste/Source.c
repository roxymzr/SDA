#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nod {
	int n;
	struct nod* urm;
}nod;

typedef struct Lista {
	char nume[30];
	nod* prim;
	nod* ultim;
	struct Lista* urm;
}Lista;

typedef struct {
	Lista* prim;
	Lista* ultim;
}Multilista;

void multilista_init(Multilista* m) {
	m->prim = m->ultim = NULL;
}

void lista_init(Lista* l) {
	l->prim = l->ultim = NULL;
	l->urm = NULL;

}

Lista* lista_noua(char nume[30]) {
	Lista* l = (Lista*)malloc(sizeof(Lista));
	if (l == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(l->nume, nume);
	lista_init(l);
	return l;
}

nod* nod_nou(int n) {
	nod* e = (nod*)malloc(sizeof(nod));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->n = n;
	e->urm = NULL;
	return e;
}

void appendLista(Multilista* m, Lista* l) {
	if (m->prim == NULL) {
		m->prim = m->ultim = l;
	}
	else {
		m->ultim->urm = l;
		m->ultim = l;
	}
}

void appendNod(Lista* l, int n) {
	if (l->prim == NULL) {
		l->prim = l->ultim = nod_nou(n);
	}
	else {
		nod* aux = nod_nou(n);
		l->ultim->urm = aux;
		l->ultim = aux;
	}
}

void afisareLista(Lista* l) {
	for (nod* c = l->prim; c != NULL; c = c->urm) {
		printf("%d ", c->n);
	}printf("\n");
}

void afisareMultilista(Multilista* m) {
	for (Lista* l = m->prim; l != NULL; l = l->urm) {
		puts(l->nume);
		afisareLista(l);
	}
}

void eliberareLista(Lista* l) {
	nod* c = l->prim;
	while (c != NULL) {
		nod* p = c->urm;
		free(c);
		c = p;
	}
}

void eliberareMultilista(Multilista* m) {
	Lista* l = m->prim;
	while (l != NULL) {
		nod* p = l->urm;
		eliberareLista(l);
		free(l);
		l = p;
	}
}

void stergeNod(Lista* l, int n) {
	if (l->prim->n == n) {
		nod* aux = l->prim->urm;
		free(l->prim);
		l->prim = aux;
	}
	else if (l->ultim->n == n) {
		nod* c = l->prim;
		for (;c->urm != l->ultim;c = c->urm) {}
		c->urm = NULL;
		free(l->ultim);
		l->ultim = c;
	}
	else {
		nod* c = l->prim;
		nod* p = NULL;
		for (; c->urm != NULL; p = c, c = c->urm) {
			if (c->n == n) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void stergeNodMultilista(Multilista* m, int n) {
	for (Lista* l = m->prim; l != NULL; l = l->urm) {
		stergeNod(l, n);
	}
}

void stergeListaMultilista(Multilista* m, char nume[30]) {
	if (!strcmp(m->prim->nume, nume)) {
		Lista* aux = m->prim->urm;
		eliberareLista(m->prim);
		m->prim = aux;
	}
	else if (!strcmp(m->ultim->nume, nume)) {
		Lista* c = m->prim;
		for (;c->urm != m->ultim;c = c->urm) {}
		c->urm = NULL;
		eliberareLista(m->ultim);
		m->ultim = c;
	}
	else {
		Lista* c = m->prim;
		Lista* p = NULL;
		for (;c != NULL;p = c, c = c->urm) {
			if (!strcmp(c->nume, nume)) {
				p->urm = c->urm;
				eliberareLista(c);
				c = p;
			}
		}

	}
}

int main(void) {
	Multilista m;
	multilista_init(&m);

	Lista* l1 = NULL;
	Lista* l2 = NULL;
	Lista* l3 = NULL;

	l1 = lista_noua("Lista1");
	l2 = lista_noua("Lista2");
	l3 = lista_noua("Lista3");

	appendNod(l1, 1);
	appendNod(l1, 2);
	appendNod(l1, 3);

	appendNod(l2, 4);
	appendNod(l2, 5);
	appendNod(l2, 6);

	appendNod(l3, 7);
	appendNod(l3, 8);
	appendNod(l3, 9);

	appendLista(&m, l1);
	appendLista(&m, l2);
	appendLista(&m, l3);

	afisareMultilista(&m);

	printf("Dupa stergerea unei liste:\n");
	stergeListaMultilista(&m, "Lista2");
	afisareMultilista(&m);


	eliberareMultilista(&m);
	
	return 0;
}