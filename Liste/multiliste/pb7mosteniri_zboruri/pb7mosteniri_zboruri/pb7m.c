#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pasageri {
	int cod;
	struct pasageri* urm;
}pasageri;

typedef struct zbor {
	char nume[20];
	pasageri* prim;
	pasageri* ultim;
	struct zbor* urm;
}zbor;


typedef struct {
	zbor* prim;
	zbor* ultim;
}Zboruri;

void init_zbor(zbor* z)
{
	z->prim = z->ultim = NULL;
	z->urm = NULL;
}

void init_Zboruri(Zboruri* zb)
{
	zb->prim = zb->ultim = NULL;
}

pasageri* pasager_nou(int cod)
{
	pasageri* e = (pasageri*)malloc(sizeof(pasageri));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	e->cod = cod;
	e->urm = NULL;
	return e;
}

zbor* zbor_nou(char nume[20])
{
	zbor* e = (zbor*)malloc(sizeof(zbor));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	strcpy(e->nume, nume);
	init_zbor(e);
	return e;
}

void adauga_pasager(zbor* z, int cod)
{
	if (z->prim == NULL)
	{
		z->prim = z->ultim = pasager_nou(cod);
	}
	else
	{
		pasageri* pas = pasager_nou(cod);
		if (z->prim->cod > cod)
		{
			pas->urm = z->prim;
			z->prim = pas;
		}
		else
		{
			pasageri* c = z->prim->urm;
			pasageri* p = z->prim;
			int flag = 0;
			for (;c != NULL;p = c, c = c->urm)
			{
				if (c->cod > cod)
				{
					p->urm = NULL;
					pas->urm = c;
					p->urm = pas;
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				pasageri* aux = pasager_nou(cod);
				z->ultim->urm = aux;
				z->ultim = aux;
			}
		}
	}
}


void adauga_zbor(Zboruri* zb, zbor* z)
{
	if (zb->prim == NULL)
	{
		zb->prim = zb->ultim = z;
	}
	else
	{
		zb->ultim->urm = z;
		zb->ultim = z;
	}
}

void afisare_Zbor(zbor* z)
{
	for (pasageri* p = z->prim;p != NULL;p = p->urm)
	{
		printf("%d ", p->cod);
	}
	printf("\n");
}

void afisare_Zboruri(Zboruri* zb)
{
	for (zbor* z = zb->prim;z != NULL;z = z->urm)
	{
		puts(z->nume);
		afisare_Zbor(z);
	}
}


void eliberareZbor(zbor* z)
{
	pasageri* p = z->prim;
	while (p != NULL)
	{
		pasageri* aux = p->urm;
		free(p);
		p = aux;
	}
}


void eliberareZboruri(Zboruri* zb)
{
	zbor* z = zb->prim;
	while (z != NULL)
	{
		zbor* aux = z->urm;
		eliberareZbor(z);
		free(z);
		z = aux;
	}
}


void stergere(zbor* z, int cod)
{
	if (z->prim->cod == cod)
	{
		pasageri* aux = z->prim->urm;
		free(z->prim);
		z->prim = aux;
	}
	else if (z->ultim->cod == cod)
	{
		pasageri* c = z->prim;
		for (;c->urm != z->ultim;c = c->urm) {}
		c->urm = NULL;
		free(z->ultim);
		z->ultim = c;
	}
	else
	{
		pasageri* c = z->prim;
		pasageri* p = NULL;
		for (;c->urm!=z->ultim;p = c, c = c->urm)
		{
			if (c->cod == cod)
			{
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void eliminare(Zboruri* zb, int cod)
{
	for (zbor* z = zb->prim;z != NULL;z = z->urm)
	{
		stergere(z, cod);
	}
}

int main()
{
	Zboruri zboruri;
	init_Zboruri(&zboruri);

	zbor* z1 = NULL;
	zbor* z2 = NULL;
	zbor* z3 = NULL;

	z1 = zbor_nou("zbor1");
	z2 = zbor_nou("zbor2");
	z3 = zbor_nou("zbor3");

	for (int i = 1;i < 6;i++)
	{
		adauga_pasager(z1, i);
	}

	for (int i = 6;i > 0;i--)
	{
		adauga_pasager(z2, i * 2);
	}

	for (int i = 1;i < 6;i++)
	{
		adauga_pasager(z3, i * 3);
	}

	adauga_zbor(&zboruri, z1);
	adauga_zbor(&zboruri, z2);
	adauga_zbor(&zboruri, z3);

	afisare_Zboruri(&zboruri);

	printf("dupa stergere: \n");

	eliminare(&zboruri, 3);
	afisare_Zboruri(&zboruri);

	eliberareZboruri(&zboruri);

	return 0;
}