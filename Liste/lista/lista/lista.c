#include<stdio.h>
#include<stdlib.h>

typedef struct nod {
	int n;
	struct nod* urm;
}nod;

typedef struct {
	nod* prim;
	nod* ultim;
}Lista;

void init_lista(Lista * l)
{
	l->prim = l->ultim = NULL;
}

nod* nod_nou(int n)
{
	nod* e = (nod*)malloc(sizeof(nod));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	e->n = n;
	e->urm = NULL;
	return e;
}

void adauga(Lista* lista, int n)
{
	nod* aux = nod_nou(n);
	if (lista->prim == NULL)
	{
		lista->prim = lista->ultim = aux;
	}
	else
	{
		lista->ultim->urm = aux;
		lista->ultim = aux;
	}
}


void afisare(Lista l)
{
	nod* c = l.prim;
	for (;c != NULL;c = c->urm)
	{
		printf("%d ", c->n);
	}
	printf("\n");
}

void eliberare(Lista* l)
{
	nod* c = l->prim;
	while (c != NULL)
	{
		nod* p = c->urm;
		free(c);
		c = p;
	}
}


void stergere(Lista* l, int val)
{
	if (l->prim->n == val)
	{
		nod* aux = l->prim->urm;
		free(l->prim);
		l->prim = aux;
	}
	else if(l->ultim->n==val)
	{
		nod* c = l->prim;
		for(;c->urm->urm!=NULL;c=c->urm){}
		c->urm = NULL;
		free(l->ultim);
		l->ultim = c;
	}
	else
	{
		nod* c = l->prim;
		nod* p = NULL;
		for (;c != NULL;p = c,c = c->urm)
		{
			if (c->n == val)
			{
				p->urm = c->urm;
				free(c);
				c = p->urm;
			}
		}
	}
}

int main()
{
	Lista l;
	init_lista(&l);

	adauga(&l, 1);
	adauga(&l, 2);
	adauga(&l, 3);
	adauga(&l, 4);

	afisare(l);

	stergere(&l, 3);
	afisare(l);

	eliberare(&l);

	return 0;
}
