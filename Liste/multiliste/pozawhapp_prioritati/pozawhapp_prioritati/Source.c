#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct proces {
	char nume[10];
	int prioritate;
	struct proces* urm;
}proces;

typedef struct lista {
	char nume[10];
	int prioritate;
	struct lista* urm;
	proces* prim;
	proces* ultim;
}lista;

typedef struct {
	lista* prim;
	lista* ultim;
}Multilista;

void init_lista(lista* l)
{
	l->prim = l->ultim = NULL;
	l->urm = NULL;
}

void init_multilista(Multilista* m)
{
	m->prim = m->ultim = NULL;
}

proces* proces_nou(char nume[10], int prioritate)
{
	proces* e = (proces*)malloc(sizeof(proces));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	strcpy(e->nume, nume);
	e->prioritate = prioritate;
	e->urm = NULL;
	return e;
}

lista* lista_noua(char nume[10], int prioritate)
{
	lista* e = (lista*)malloc(sizeof(lista));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	init_lista(e);
	strcpy(e->nume, nume);
	e->prioritate = prioritate;
	return e;
}

void adaugaProces(lista* l, char nume[10], int prioritate)
{
	if (l->prim == NULL)
	{
		l->prim = l->ultim = proces_nou(nume, prioritate);
	}
	else
	{
		proces* aux = proces_nou(nume, prioritate);
		l->ultim->urm = aux;
		l->ultim = aux;
	}
}

void adauga_lista(Multilista* m, lista* l)
{
	if (m->prim == NULL)
	{
		m->prim = m->ultim = l;
	}
	else
	{
		m->ultim->urm = l;
		m->ultim = l;
	}
}

void afisareLista(lista* l)
{
	for (proces* p = l->prim;p != NULL;p = p->urm)
	{
		printf("Nume: %s - prioritate: %d\n", p->nume, p->prioritate);
	}
	printf("\n");
}

void afisareMultilista(Multilista* m)
{
	for (lista* l = m->prim;l != NULL;l = l->urm)
	{
		printf("Nume:%s - prioritate:%d \n", l->nume, l->prioritate);
		afisareLista(l);
	}
}

void eliberareLista(lista* l)
{
	proces* c = l->prim;
	while (c != NULL)
	{
		proces* aux = c->urm;
		free(c);
		c = aux;
	}
}

void eliberareMultilista(Multilista* m)
{
	lista* l = m->prim;
	while (l != NULL)
	{
		lista* aux = l->urm;
		eliberareLista(l);
		free(l);
		l = aux;
	}
}

void mutare(Multilista* m, lista* l)
{
	while (l->prim != NULL)
	{
		proces* returnat = proces_nou(l->prim->nume, l->prim->prioritate);
		proces* aux = l->prim->urm;
		free(l->prim);
		l->prim = aux;
		for (lista* l = m->prim;l != NULL;l = l->urm)
		{
			if (l->prioritate == returnat->prioritate)
			{
				adaugaProces(l, returnat->nume, returnat->prioritate);
				break;
			}
		}
	}
}

int main()
{
	Multilista multilista;
	init_multilista(&multilista);

	lista* liste[8];
	lista* stiva = NULL;
	stiva = lista_noua("stiva", 0);

	adaugaProces(stiva, "proces100", 3);
	adaugaProces(stiva, "proces200", 7);
	adaugaProces(stiva, "proces300", 2);

	for (int i = 0;i < 8;i++)
	{
		liste[i] = NULL;
	}

	char n[10] = "Lista";
	for (int i = 0;i < 8;i++)
	{
		char aux[10] = "";
		sprintf(aux, "%s%d", n, i + 1);
		liste[i] = lista_noua(aux, i + 1);
	}

	int counter = 1;
	char pr[10] = "proces";
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			char aux[10] = "";
			sprintf(aux, "%s%d", pr, counter);
			adaugaProces(liste[i], aux, liste[i]->prioritate);
		}
	}

	for (int i = 0;i < 8;i++)
	{
		adauga_lista(&multilista, liste[i]);
	}

	afisareMultilista(&multilista);

	printf("Dupa mutare:\n");
	mutare(&multilista, stiva);
	afisareMultilista(&multilista);

	eliberareMultilista(&multilista);
	return 0;

}