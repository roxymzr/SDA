#include<stdio.h>

#define N 4

typedef struct coordonate {
	int linie, coloana;
}coordonate;


int vizitat[N][N];
int nrobiecte;
coordonate pos[4];
int matrice[N][N] = {
	{1,0,0,1},
	{0,1,1,0},
	{1,0,1,0},
	{0,1,0,1}
};

void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1;
	pos[1].coloana = 1; pos[1].linie = 0;
	pos[2].coloana = 0; pos[2].linie = 1;
	pos[3].coloana = -1; pos[3].linie = 0;
}

int solutie(coordonate c)
{
	return (matrice[c.linie][c.coloana] == 1 && !vizitat[c.linie][c.coloana]);
}

int acceptabil(coordonate c)
{
	return (c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N);
}

void labirint(int linie, int coloana)
{
	vizitat[linie][coloana] = 2;

	for (int i = 0;i < 4;i++)
	{
		coordonate aux;
		aux.coloana = coloana + pos[i].coloana;
		aux.linie = linie + pos[i].linie;
		if (acceptabil(aux)&& solutie(aux))
		{
			labirint(aux.linie,aux.coloana);
		}
	}
}

void nr_obiecte()
{
	nrobiecte=0;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			coordonate coord;
			coord.linie = i;
			coord.coloana = j;;
			if (solutie(coord))
			{
				nrobiecte++;
				labirint(i, j);
				
			}
		}
	}
	printf("Sunt %d obiecte\n", nrobiecte);
}

int main()
{
	initializare();
	nr_obiecte();
	return 0;
}