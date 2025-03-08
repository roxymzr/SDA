#include<stdio.h>
#include<stdlib.h>

typedef struct nod {
	int n;
	struct nod* urm;
}nod;

typedef struct {
	nod* prim;
	nod* ultim;
}lista;


void init_lista(lista* l)
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


void adauga(lista* l, int n, int* size)
{
	if (l->prim == NULL)
	{
		l->prim = l->ultim = nod_nou(n);
	}
	else
	{
		nod* aux = nod_nou(n);
		l->ultim->urm = aux;
		l->ultim = aux;
	}
	*size += 1;
}


void afisare(lista l)
{
	for (nod* c = l.prim;c != NULL;c = c->urm)
	{
		printf("%d ", c->n);
	}
	printf("\n");
}

void eliberare(lista* l)
{
	nod* c = l->prim;
	while (c != NULL)
	{
		nod* aux = c->urm;
		free(c);
		c = aux;
	}
}

void sterge_mij(lista* l, int size)
{
	nod* c = l ->prim;
	nod* p = c;
	int flag = 0;
	for (;c != NULL;p = c, c = c->urm)
	{
		if (flag == (size / 2))
		{
			p->urm = c->urm;
			free(c);
			c = p;
		}
		flag++;
	}
}

int main()
{
	lista l;
	init_lista(&l);
	int size = 0;

	for (int i = 1;i <= 7;i++)
	{
		adauga(&l, i, &size);
	}

	afisare(l);

	printf("Dupa stergere: \n");
	sterge_mij(&l, size);
	afisare(l);

	eliberare(&l);

	return 0;
}