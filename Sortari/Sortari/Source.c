/*
#include<stdio.h>
#include<stdlib.h>

int* generare(int n)
{
	int* a = (int*)malloc(n * sizeof(int));
	for (int i = 0;i < n;i++)
	{
		a[i] = n - i - 5;
	}
	return a;
}

void swap(int* el1,int* el2)
{
	int tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}

void quicksort(int* a, int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	int pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && a[stanga] < pivot)
			stanga++;
		while (dreapta >= prim && pivot < a[dreapta])
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}

void afisare(int* a,int n)
{
	for (int i = 0;i < n;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int* schimbare(int* a,int n)
{
	int inceput = 0;
	for (int i = 0;i < n;i++)
	{
		if (a[i] < 0)
		{
			swap(&a[i], &a[inceput++]);
		}
	}
	afisare(a,n);
	quicksort(a, inceput, n - 1);
	return a;
}

int main()
{
	int* a = NULL;
	int n = 10;
	a = generare(n);
	afisare(a, n);
	a = schimbare(a, n);
	afisare(a, n);
	return 0;
}
*/

/*
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
	NU,
	DA
}bonus;

typedef struct {
	char nume[35];
	int salar;
	bonus bonus;
}angajat;


void swap(angajat* el1, angajat* el2)
{
	angajat tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}


angajat* citire(angajat* v, int size)
{
	v = (angajat*)malloc(size * sizeof(angajat));

	char name[25] = "Nume";
	
	for (int i = 0;i < size;i++)
	{
		char nume[25] = "";
		sprintf(nume, "%s%d", name, i + 1);
		v[i].salar = (i + 3) * 700;
		v[i].bonus = i % 2;
		strcpy(v[i].nume, nume);
	}
	return v;
}

void afisare(angajat* v, int size)
{
	for (int i = 0;i < size;i++)
	{
		printf("Nume: %s; salar: %d; bonus:%u\n", v[i].nume, v[i].salar, v[i].bonus);
	}
}

void modif1(angajat* v, int size, int* poz)
{
	int pozitie = 0;
	for (int i = 0;i < size;i++)
	{
		if (size - pozitie < pozitie) break;
		if (v[i].bonus)
		{
			swap(&v[i], &v[pozitie++]);
		}
	}
	*poz = pozitie;
}

void quicksort(angajat a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	angajat pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && a[stanga].salar < pivot.salar)
			stanga++;
		while (dreapta >= prim && pivot.salar < a[dreapta].salar)
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}

int main()
{
	angajat* v = NULL;
	int size = 7;
	int pozitie = 0;
	v = citire(v, size);
	afisare(v, size);

	printf("\n Dupe modificare:\n");
	modif1(v, size, &pozitie);
	afisare(v, size);

	printf("\n Dupa modificarea 2:\n");
	quicksort(v, pozitie, size - 1);
	afisare(v, size);
	free(v);

	return 0;
}

*/

/*
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef enum {
	NU,
	DA
}premiu;

typedef struct {
	char nume[35];
	int varsta;
	premiu premiu;
}student;


void swap(student* el1, student* el2)
{
	student tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}

student* citire(student* v, int size)
{
	v = (student*)malloc(size * sizeof(student));

	char name[25] = "Student";

	for (int i = 0;i < size;i++)
	{
		char nume[25] = "";
		sprintf(nume, "%s%d", name, size - i);
		v[i].varsta = i + (2 * (i + 1));
		strcpy(v[i].nume, nume);
		v[i].premiu = i % 2;
	}
	return v;
}

void afisare(student* v, int size)
{
	for (int i = 0;i < size;i++)
	{
		printf("Nume: %s; varsta: %d; premiu: %u\n", v[i].nume, v[i].varsta, v[i].premiu);
	}
}

void modif1(student* v, int size, int* poz)
{
	int start = 0;
	for (int i = 0;i < size;i++)
	{
		if (start >= size - start) break;
		if (v[i].premiu)
		{
			swap(&v[i], &v[start++]);
		}
	}
	*poz = start;
}

void quicksort(student a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	student pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(a[stanga].nume,pivot.nume)<0)
			stanga++;
		while (dreapta >= prim && strcmp(pivot.nume,a[dreapta].nume)<0)
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}


int main()
{
	student* v = NULL;
	int size = 7;
	int pozitie = 0;
	v = citire(v, size);
	afisare(v, size);

	printf("Dupa modif 1:\n");
	modif1(v, size, &pozitie);
	afisare(v, size);

	printf("Dups modif 2:\n");
	quicksort(v, 0, pozitie - 1);
	afisare(v, size);

	return 0;
}
*/


