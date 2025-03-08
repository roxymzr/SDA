#include<stdio.h>

int v[10];
int n = 6;

void afisare()
{
	for (int i = 0;i < n;i++)
	{
		printf("%d", v[i]);
	}
	printf("\n");
}

int valid(int k)
{
	return k <= n;
}

int solutie(int k)
{
	if (v[0] && v[1]) return 0;
	if (!v[n - 1]) return 0;
	return 1;
}

void back(int k)
{
	if (k == n)
	{
		if (solutie(k))
		{
			afisare();
		}
	}
	for (int i = 0;i < 2;i++)
	{
		v[k] = i;
		if (valid(k))
		{
			back(k + 1);
		}
	}
}

int main()
{
	back(0);
	return 0;
}