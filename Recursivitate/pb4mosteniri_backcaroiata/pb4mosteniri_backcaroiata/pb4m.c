#include<stdio.h>

#define N 3
#define COLORS 4

typedef struct coordonate {
	int linie, coloana;
}coordonate;

int matrice[N][N];
int culori[N][N];
coordonate pos[8];


void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1; //N 
	pos[1].coloana = 1; pos[1].linie = 0; //E 
	pos[2].coloana = 0; pos[2].linie = 1; //S 
	pos[3].coloana = -1; pos[3].linie = 0; //V
	pos[4].coloana = -1; pos[4].linie = -1; //NV 
	pos[5].coloana = 1; pos[5].linie = -1; //NE 
	pos[6].coloana = -1; pos[6].linie = 1; //SV 
	pos[7].coloana = 1; pos[7].linie = 1; //SE
}

int acceptabil(coordonate c)
{
	return (c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N);
}

int labirint(int linie, int coloana, int culoare)
{
	for (int i = 0;i < 8;i++)
	{
		coordonate aux;
		aux.coloana = coloana + pos[i].coloana;
		aux.linie = linie + pos[i].linie;
		if (acceptabil(aux) && culori[aux.linie][aux.coloana]==culoare)
		{
			return 0;
		}
	}
	return 1;
}

void coloreaza_harta()
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			for (int k = 1;k <= COLORS;k++)
			{
				if (labirint(i, j,k))
				{
					culori[i][j] = k;
					break;
				}
			}
		}
	}
}

void afisare()
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			printf("%d ", culori[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	initializare();
	coloreaza_harta();
	afisare();
	return 0;
}