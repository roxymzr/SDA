#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct student {
	char nume[30];
	struct student* urm;
}student;

typedef struct conferinta {
	student* prim;
	student* ultim;
	char id[8];
	char parola[10];
	struct conferinta* urm;
}conferinta;

typedef struct {
	conferinta* prim;
	conferinta* ultim;
}Zoom;

void init_conferinta(conferinta* c)
{
	c->prim = c->ultim = NULL;
	c->urm = NULL;
}


void init_Zoom(Zoom* z)
{
	z->prim = z->ultim = NULL;
}

student* student_nou(char nume[20])
{
	student* e = (student*)malloc(sizeof(student));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	strcpy(e->nume, nume);
	e->urm = NULL;
	return e;
}

conferinta* conferinta_noua(char id[8], char parola[10])
{
	conferinta* e = (conferinta*)malloc(sizeof(conferinta));
	if (e == NULL)
	{
		printf("eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	init_conferinta(e);
	strcpy(e->id, id);
	strcpy(e->parola, parola);
	return e;
}


void adaugaStudent(conferinta* c, char nume[20])
{
	if (c->prim == NULL)
	{
		c->prim = c->ultim = student_nou(nume);
	}
	else
	{
		student* aux = student_nou(nume);
		if (strcmp(c->prim->nume, nume) > 0)
		{
			aux->urm = c->prim;
			c->prim = aux;
		}
		else
		{
			student* e = c->prim->urm;
			student* p = c->prim;
			int flag = 0;
			for (;e != NULL;p = e, e = e->urm)
			{
				if (strcmp(e->nume, nume) > 0)
				{
					p->urm = aux;
					aux->urm = e;
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				c->ultim->urm = aux;
				c->ultim = aux;
			}
		}
	}
}

void adaugaConferinta(Zoom* z, conferinta* c)
{
	if (z->prim == NULL)
	{
		z->prim = z->ultim = c;
	}
	else
	{
		z->ultim->urm = c;
		z->ultim = c;
	}
}

void afisareConferinta(conferinta* c)
{
	for (student* s = c->prim;s != NULL;s = s->urm)
	{
		printf("%s ", s->nume);
	}
	printf("\n");
}

void afisareZoom(Zoom* z)
{
	for (conferinta* c = z->prim;c != NULL;c = c->urm)
	{
		printf("ID:%s Parola: %s\n", c->id, c->parola);
		afisareConferinta(c);
	}
}


void eliberareConferinta(conferinta* c)
{
	student* s = c->prim;
	while (s != NULL)
	{
		student* aux = s->urm;
		free(s);
		s = aux;
	}
}

void eliberareZoom(Zoom* z)
{
	conferinta* c = z->prim;
	while (z != NULL)
	{
		conferinta* aux = c->urm;
		eliberareConferinta(c);
		free(c);
		c = aux;
	}
}

void stergere(conferinta* c, char nume[20])
{
	if (!strcmp(c->prim->nume, nume))
	{
		student* aux = c->prim->urm;
		free(c->prim);
		c->prim = aux;
	}
	else if (!strcmp(c->ultim->nume, nume))
	{
		student* aux = c->prim;
		for (;aux->urm != c->ultim;aux = aux->urm) {}
		aux->urm = NULL;
		free(c->ultim);
		c->ultim = aux;
	}
	else
	{
		student* s = c->prim;
		student* p = NULL;
		for (;s != NULL;p = s, s = s->urm)
		{
			if (!strcmp(s->nume, nume))
			{
				p->urm = s->urm;
				free(s);
				s = p;
			}
		}
	}
}


int main()
{
	Zoom zoom;
	init_Zoom(&zoom);

	char* nume[] = {
	"Ion Popescu", "Maria Ionescu", "Alex Dumitru", "Elena Georgescu", "Vlad Mihai",
	"Ana Vasile", "Cristian Iordache", "Daniela Marin", "Florin Petrescu", "Gabriela Enache",
	"Radu Stancu", "Irina Preda", "Mihai Ciobanu", "Simona Tudor", "Carmen Roman",
	"Victor Pavel", "Lavinia Dragomir", "Andrei Grigore", "Oana Neagu", "Ioana Barbu",
	"George Voicu", "Monica Tanase", "Bogdan Petrica", "Teodora Filip", "Alexandra Dinu",
	"Robert Stoica", "Bianca Popa", "Adrian Lungu", "Sofia Moldovan", "Paul Ene"
	};

	char* iduri[] = {
		"12345", "67890", "11223", "33445", "55678",
		"99887", "44556", "77889", "99001", "22334",
		"66554", "88123", "44122", "33556", "77441"
	};

	char* parole[] = {
		"abc123", "def456", "ghi789", "jkl012", "mno345",
		"pqr678", "stu901", "vwx234", "yz1234", "abc678",
		"def901", "ghi234", "jkl567", "mno890", "pqr123"
	};


	conferinta* waitingroom = NULL;
	waitingroom = conferinta_noua("12345", "abc123");

	for (int i = 0;i < 30;i++)
	{
		adaugaStudent(waitingroom, nume[i]);
	}

	conferinta* c1 = NULL, * c2 = NULL, * c3 = NULL;
	c1 = conferinta_noua("conf1", parole[4]);
	c2 = conferinta_noua("conf2", parole[2]);
	c3 = conferinta_noua("conf3", parole[12]);

	conferinta* cnf[3] = { c1,c2,c3 };
	srand(time(NULL));
	for (student* s = waitingroom->prim;s != NULL;s = s->urm)
	{
		if (strchr("aeiouAEIOU", s->nume[0]))
		{
			adaugaStudent(cnf[rand() % 3], s->nume);
			if (!strcmp(waitingroom->prim->nume, s->nume))
			{
				student* aux = waitingroom->prim->urm;
				free(waitingroom->prim);
				waitingroom->prim = aux;
				s = waitingroom->prim;
			}
			else if (!strcmp(waitingroom->ultim->nume, s->nume))
			{
				student* aux = waitingroom->prim;
				for(;aux->urm!=waitingroom->ultim;aux=aux->urm){}
				aux->urm = NULL;
				free(waitingroom->ultim);
				waitingroom->ultim = aux;
				s = waitingroom->ultim;
			}
			else
			{
				student* c = waitingroom->prim;
				student* p = NULL;
				for (;c != NULL;p = c, c = c->urm)
				{
					if (!strcmp(c->nume, s->nume))
					{
						p->urm = c->urm;
						free(c);
						c = p;
						s = c;
					}
				}
			}
		}
	}
	for (int i = 0;i < 3;i++)
	{
		adaugaConferinta(&zoom, cnf[i]);
	}

	afisareZoom(&zoom);

	printf("Waiting room: \n");
	afisareConferinta(waitingroom);

	eliberareZoom(&zoom);

	return 0;
}
