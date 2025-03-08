#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct persoana {
	int id;
	char nume[35];
	char ocupatie[35];
	struct persona* urm;
	struct Contacte* contacte;
}persoana;

typedef struct Contacte {
	persoana* prim;
	persoana* ultim;
}Contacte;

typedef struct Pers {
	persoana* prim;
	persoana* ultim;
}Pers;

void init_pers(Pers* p)
{
	p->prim = p->ultim = NULL;
}

void init_contacte(Contacte* c)
{
	c->prim = c->ultim = NULL;
}

Contacte* contact_nou()
{
	Contacte* e = (Contacte*)malloc(sizeof(Contacte));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	init_contacte(e);
	return e;
}


persoana* persoana_noua(int id, char nume[35], char ocupatie[35])
{
	persoana* e = (persoana*)malloc(sizeof(persoana));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	e->urm = NULL;
	e->contacte = contact_nou();
	e->id = id;
	strcpy(e->nume, nume);
	strcpy(e->ocupatie, ocupatie);
	return e;
}

void adaugareContact(persoana* nod, int id, char nume[35], char ocupatie[35])
{
	persoana* aux = persoana_noua(id, nume, ocupatie);
	if (nod->contacte->prim == NULL)
	{
		nod->contacte->prim = nod->contacte->ultim = aux;
	}
	else
	{
		nod->contacte->ultim->urm = aux;
		nod->contacte->ultim = aux;
	}
}

void adaugarepersoana(Pers* p, persoana* p1)
{
	if (p->prim == NULL)
	{
		p->prim = p->ultim = p1;
	}
	else
	{
		p->ultim->urm = p1;
		p->ultim = p1;
	}
}

void afisareContacte(Contacte* c)
{
	printf("Contacte:\n");
	for (persoana* p = c->prim;p != NULL;p = p->urm)
	{
		printf("ID: %d; Nume: %s; Ocupatie: %s\n", p->id, p->nume, p->ocupatie);
	}
	printf("\n");
}

void afisarepersoana(persoana* p)
{
	printf("ID: %d; Nume: %s; Ocupatie: %s\n", p->id, p->nume, p->ocupatie);
	afisareContacte(p->contacte);
}

void afisarePers(Pers* p)
{
	for (persoana* p1 = p->prim;p1 != NULL;p1 = p1->urm)
	{
		afisarepersoana(p1);
	}
}

void eliberareContact(Contacte* c)
{
	persoana* p = c->prim;
	while (p != NULL)
	{
		persoana* aux = p->urm;
		free(p);
		p = aux;
	}
	free(c);
}

void eliberarePers(Pers* p)
{
	persoana* p1 = p->prim;
	while (p1 != NULL)
	{
		persoana* aux = p1->urm;
		eliberareContact(p1->contacte);
		free(p1);
		p1 = aux;
	}
}

void adaugareContactPers(Pers* p, char numeNod[35], int id, char nume[35], char ocupatie[35])
{
	for (persoana* p1 = p->prim;p1 != NULL;p1 = p1->urm)
	{
		if (!strcmp(p1->nume, numeNod))
		{
			adaugareContact(p1, id, nume, ocupatie);
			break;
		}
	}
}

int main()
{
	Pers pers;
	init_pers(&pers);

	persoana* p1 = NULL, * p2 = NULL, *p3 = NULL;

	p1 = persoana_noua(1234, "ion", "brutar");
	p2 = persoana_noua(324, "roxana", "ITist");
	p3 = persoana_noua(2134, "Eric", "fotbalist");

	adaugareContact(p1, 1223, "Ana", "Croitoreasa");
	adaugareContact(p1, 3456, "Vasile", "Mester");
	adaugareContact(p1, 23515, "Bogdan", "Electrician");

	adaugareContact(p2, 298715, "Eric", "Boss");
	adaugareContact(p2, 15625, "Cristina", "Economista");
	adaugareContact(p2, 39815, "Andrei", "Nimic");

	adaugareContact(p3, 515097, "Andreea", "Inginera");
	adaugareContact(p3, 87549, "Dragos", "Sef");
	adaugareContact(p3, 76346, "Adrian", "...");

	adaugarepersoana(&pers, p1);
	adaugarepersoana(&pers, p2);
	adaugarepersoana(&pers, p3);

	afisarePers(&pers);

	adaugareContactPers(&pers, "ion", 53564, "dani", "tot");
	afisarePers(&pers);

	eliberarePers(&pers);

	return 0;
}