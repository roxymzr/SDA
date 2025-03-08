#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct GPS {
	int cod;
	struct GPS* urm;
}GPS;

typedef struct firma {
	char nume[20];
	GPS* prim;
	GPS* ultim;
	struct firma* urm;
}firma;

typedef struct {
	firma* prim;
	firma* ultim;
}F;

void init_firma(firma* f)
{
	f->prim = f->ultim = NULL;
	f->urm = NULL;
}

void init_F(F* ft)
{
	ft->prim = ft->ultim = NULL;
}

GPS* gps_nou(int cod)
{
	GPS* e = (GPS*)malloc(sizeof(GPS));
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

firma* firma_noua(char nume[20])
{
	firma* e = (firma*)malloc(sizeof(firma));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	init_firma(e);
	return e;
}

void adaugaGPS(firma* f, int cod)
{
	if (f->prim == NULL)
	{
		f->prim = f->ultim = gps_nou(cod);
	}
	else
	{
		GPS* aux = gps_nou(cod);
		f->ultim->urm = aux;
		f->ultim = aux;
	}
}

// sau
/*
void adaugaGPS(firma* f, int cod)
{
	if (f->prim == NULL)
	{
		f->prim = f->ultim = gps_nou(cod);
	}
	else
	{
		GPS* aux = gps_nou(cod);
		if (f->prim > cod)
		{
			aux->urm = f->prim;
			f->prim = aux;
		}
		else
		{
			GPS* c = f->prim->urm;
			GPS* p = f->prim;
			int flag = 0;
			for (;c != NULL;p = c, c = c->urm)
			{
				if (c->cod > cod)
				{
					aux->urm = c;
					p->urm = NULL;
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				f->ultim->urm = aux;
				f->ultim = aux;
			}
		}
	}
}
*/



void adaugaFirma(F* ft, firma* f)
{
	if (ft->prim == NULL)
	{
		ft->prim = ft->ultim = f;
	}
	else
	{
		ft->ultim->urm = f;
		ft->ultim = f;
	}
}


void afisareFirma(firma* f)
{
	for (GPS* p = f->prim;p != NULL;p = p->urm)
	{
		printf("%d ", p->cod);
	}
	printf("\n");
}


void afisareF(F* ft)
{
	for (firma* f = ft->prim;f != NULL;f = f->urm)
	{
		puts(f->nume);
		afisareFirma(f);
	}
}


void eliberareFirma(firma* f)
{
	GPS* p = f->prim;
	while (p != NULL)
	{
		GPS* aux = p->urm;
		free(p);
		p = aux;
	}
}


void eliberareF(F* ft)
{
	firma* f = ft->prim;
	while (f != NULL)
	{
		firma* aux = f->urm;
		eliberareFirma(f);
		free(f);
		f = aux;
	}
}

void stergeGPS(firma* f, int cod)
{
	if (f->prim->cod == cod)
	{
		GPS* aux = f->prim->urm;
		free(f->prim);
		f->prim = aux;
	}
	else if (f->ultim->cod == cod)
	{
		GPS* c = f->prim;
		for(;c->urm!=f->ultim;c=c->urm){}
		c->urm = NULL;
		free(f->ultim);
		f->ultim = c;
	}
	else
	{
		GPS* c = f->prim;
		GPS* p = NULL;
		for (;c != NULL;p = c, c = c->urm)
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

void eliminareGPS(F* ft, int cod)
{
	for (firma* f = ft->prim;f != NULL;f = f->urm)
	{
		stergeGPS(f, cod);
	}
}


int main()
{
	F firme;
	init_F(&firme);

	firma* f1 = NULL;
	firma* f2 = NULL;
	firma* f3 = NULL;

	f1 = firma_noua("firma1");
	f2 = firma_noua("firma2");
	f3 = firma_noua("firma3");

	for (int i = 6;i > 0;i--)
	{
		adaugaGPS(f1, i);
	}

	for (int i = 0;i < 6;i++)
	{
		adaugaGPS(f2, i * 2);
	}

	for (int i = 0;i < 6;i++)
	{
		adaugaGPS(f3, i * 3);
	}

	adaugaFirma(&firme, f1);
	adaugaFirma(&firme, f2);
	adaugaFirma(&firme, f3);

	afisareF(&firme);

	printf("dupa stergere: \n");
	eliminareGPS(&firme, 6);
	afisareF(&firme);

	return 0;
}

