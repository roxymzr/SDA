/*
#include<stdio.h>

#define N 4 //nr coloane
#define M 3 //nr linii

typedef struct coordonate {
	int linie, coloana;
}coordonate;

coordonate pos[8];  //pt directiile de deplasare
coordonate a[M * N];  //pt a stoca drumul curent 
coordonate initial, final;

int matrice[M][N] = { {16, 2, 12, 20}, 
	{4, 5, 9, 30}, 
	{8, 13, 16, 19} 
};


coordonate solutii[30][20];  //matrice pt a stoca solutiile
int p = 0;  //contor pt nr de solutii


void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1;  //N
	pos[1].coloana = 1; pos[1].linie = 0;   //E
	pos[2].coloana = 0; pos[2].linie = 1;   //S
	pos[3].coloana = -1; pos[3].linie = 0;  //V
	pos[4].coloana = -1; pos[4].linie = -1; //NV
	pos[5].coloana = 1; pos[5].linie = -1;  //NE
	pos[6].coloana = -1; pos[6].linie = 1;  //SV
	pos[7].coloana = 1; pos[7].linie = 1;   //SE

	a[0].linie = initial.linie;
	a[0].coloana = initial.coloana;

	for (int i = 0;i < 30;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			solutii[i][j].coloana = 5;  //initializare solutii
		}
	}
}

int solutie(coordonate c)
{
	return (c.coloana == final.coloana && c.linie == final.linie);
}

int acceptabil(coordonate c, int k)
{
	return (matrice[c.linie][c.coloana] > k && c.linie >= 0 && c.coloana >= 0 && c.linie < M && c.coloana < N);
}

void afiseaza_sol(int k)
{
	for (int i = 0;i < k;i++)
	{
		printf("pas %d = %d-%d\n", i, a[i].linie, a[i].coloana);
	}
	printf("\n");

	for (int j = 0;j < k;j++)
	{
		solutii[p][j] = a[j];
	}
	p++;
}

void labirint(int k,int q)  //k pasul, c coordonata curenta
{
	int i; coordonate aux;
	if (solutie(a[k - 1]))        //solutie completa
		afiseaza_sol(k);
	else
	{
		for (i = 0; i < 8; i++)  // parcurgem pe rand posibilitatile
		{
			aux.coloana = a[k - 1].coloana + pos[i].coloana;
			aux.linie = a[k - 1].linie + pos[i].linie;
			if (acceptabil(aux,q))
			{//daca posibilitatea  e acceptabila
				a[k] = aux;
				labirint(k + 1, matrice[a[k].linie][a[k].coloana]);
			}
		}
	}
}


void pct1()
{
	initial.linie = 0;
	initial.coloana = 1;
	final.linie = 2;
	final.coloana = 3;

	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			printf("%d", matrice[i][j]);
		}
		printf("\n");
	}

	initializare();
	labirint(1, 2);
}


void pct2()
{
	int contor = 0;
	int min = 10;
	int index;
	for (int i = 0;i < p;i++)
	{
		contor = 0;
		for (int j = 0;j < 20;j++)
		{
			if (solutii[i][j].coloana != 5)
			{
				contor++;
			}
		}
		if (min > contor)
		{
			min = contor;
			index = i;
		}
	}

	printf("Cel mai rapid drum are %d pasi \n", min);
	for (int j = 0;j < 20 && (solutii[index][j].coloana != 5); j++)
	{
		printf("pas %d = %d-%d\n",j,solutii[index][j].linie, solutii[index][j].coloana);
	}
}

int main(void)
{
	pct1();
	pct2();
	return 0;
}

*/


/*
#include<stdio.h>

#define N 8

typedef struct coordonate {
	int linie, coloana;
}coordonate;

coordonate pos[8];

int matrice[N][N] = { 
	{0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 1, 1, 1, 0, 1, 1, 0}, 
	{0, 1, 1, 1, 0, 1, 1, 0}, 
	{0, 0, 1, 1, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 1, 1, 0}, 
	{0, 0, 0, 0, 0, 1, 1, 0}, 
	{0, 1, 1, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0} 
};

int vizitat[N][N];
int nrzona;
int celule_albe;

void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1;  //N
	pos[1].coloana = 1; pos[1].linie = 0;   //E
	pos[2].coloana = 0; pos[2].linie = 1;   //S
	pos[3].coloana = -1; pos[3].linie = 0;  //V
	pos[4].coloana = -1; pos[4].linie = -1; //NV
	pos[5].coloana = 1; pos[5].linie = -1;  //NE
	pos[6].coloana = -1; pos[6].linie = 1;  //SV
	pos[7].coloana = 1; pos[7].linie = 1;   //SE

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			vizitat[i][j] = 0;
		}
	}
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
	vizitat[linie][coloana] = 1;
	celule_albe++;

	for (int i = 0; i < 8; i++) 
		{
			coordonate aux;
			aux.coloana = coloana + pos[i].coloana;
			aux.linie = linie + pos[i].linie; 
			if (acceptabil(aux) && solutie(aux) )
			{
				labirint(aux.linie,aux.coloana);     
			}
		}
}


void nr_zone_albe()
{
	nrzona = 0;

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			coordonate coord;
			coord.linie = i;
			coord.coloana = j;
			if (solutie(coord))
			{
				celule_albe = 0;
				labirint(i, j);
				nrzona++;
				printf("C%d = %d celule albe  \n", nrzona, celule_albe);
			}
		}
	}
}

int main()
{
	initializare();
	nr_zone_albe();
	return 0;
}
*/


/*
#include<stdio.h>

#define N 5

typedef struct coordonate {
	int linie, coloana;
}coordonate;

coordonate pos[4];
int vizitat[N][N];
int lungime_max;
int lungime_curenta;

int matrice[N][N] = {
	{1,1,0,0,0},
	{0,1,1,0,0},
	{0,0,1,0,1},
	{1,0,0,0,1},
	{0,1,0,1,1}
};

void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1;  //N
	pos[1].coloana = 1; pos[1].linie = 0;   //E
	pos[2].coloana = 0; pos[2].linie = 1;   //S
	pos[3].coloana = -1; pos[3].linie = 0;  //V

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			vizitat[i][j] = 0;
		}
	}
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
	vizitat[linie][coloana] = 1;
	lungime_curenta++;

	if (lungime_curenta > lungime_max)
	{
		lungime_max = lungime_curenta;
	}

	for (int i = 0; i < 4; i++)
	{
		coordonate aux;
		aux.coloana = coloana + pos[i].coloana;
		aux.linie = linie + pos[i].linie;
		if (acceptabil(aux) && solutie(aux))
		{
			labirint(aux.linie, aux.coloana);
		}
	}
	vizitat[linie][coloana] = 0;
	lungime_curenta--;
}

void determina_lmax()
{
	lungime_max = 0;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (matrice[i][j] == 1 && !vizitat[i][j])
			{
				lungime_curenta = 0;
				labirint(i, j);
			}
		}
	}
	printf("Lungimea maxima este: %d \n", lungime_max);
}



int main()
{
	initializare();
	determina_lmax();
	return 0;
}
*/



#include<stdio.h>

#define N 6

typedef struct coordonate {
	int linie, coloana;
}coordonate;

coordonate pos[4];

int matrice[N][N] = {
	{1,1,1,1,1,1},
	{1,1,0,1,0,1},
	{1,1,0,1,1,1},
	{1,1,1,0,0,1},
	{1,0,1,1,1,1},
	{1,1,1,1,1,1}
};

int vizitat[N][N];
int nr_incaperi;
int supraf_max;
int supraf_curenta;

void initializare()
{
	pos[0].coloana = 0; pos[0].linie = -1;  //N
	pos[1].coloana = 1; pos[1].linie = 0;   //E
	pos[2].coloana = 0; pos[2].linie = 1;   //S
	pos[3].coloana = -1; pos[3].linie = 1;  //V

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			vizitat[i][j] = 0;
		}
	}
}

void reset_vizitat()
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			vizitat[i][j] = 0;
		}
	}
}

int solutie(coordonate c)
{
	return (matrice[c.linie][c.coloana] == 0 && !vizitat[c.linie][c.coloana]);
}

int acceptabil(coordonate c)
{
	return (c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N);
}

void labirint(int linie, int coloana)
{
	vizitat[linie][coloana] = 1;

	supraf_curenta++;
	if (supraf_curenta > supraf_max)
	{
		supraf_max = supraf_curenta;
	}

	for (int i = 0; i < 4; i++)
	{
		coordonate aux;
		aux.coloana = coloana + pos[i].coloana;
		aux.linie = linie + pos[i].linie;
		if (acceptabil(aux) && solutie(aux))
		{
			labirint(aux.linie, aux.coloana);
		}
	}
	
}

void numarincaperi()
{
	nr_incaperi = 0;

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			coordonate aux;
			aux.linie = i;
			aux.coloana = j;
			if (solutie(aux))
			{
				nr_incaperi++;
				labirint(i, j);
			}
		}
	}
	printf("Numarul de incaperi este: %d \n", nr_incaperi);
}

void suprafata_max()
{
	supraf_max = 0;

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (matrice[i][j] == 0 && !vizitat[i][j])
			{
				supraf_curenta = 0;
				labirint(i, j);
			}
		}
	}
	printf("Suprafata maxima este: %d \n", supraf_max);
}


int main()
{
	initializare();
	numarincaperi();
	reset_vizitat();
	suprafata_max();
	return 0;
}
