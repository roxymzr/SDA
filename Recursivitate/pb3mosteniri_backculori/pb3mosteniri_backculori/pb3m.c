#include<stdio.h>

char culori[6] = {'w','y','r','g','b','n' };
char steag[3] = "";
int n = 3;

void afisare()
{
	for (int i = 0;i < n;i++)
	{
		printf("%c ", steag[i]);
	}
	printf("\n");
}

int acceptabil(int k)
{
	int frec[6] = { 0,0,0,0,0,0 };
	for (int i = 0;i <= k;i++)
	{
		frec[steag[i] - 'a']++;
	}
	return frec[steag[0] - 'a'] <= 1 && frec[steag[1] - 'a'] <= 1 && frec[steag[2] - 'a'] <= 1;
}

int solutie(int k)
{
	return (steag[1] == 'y' || steag[1] == 'g') && k == n - 1;
}

void back(int k, int* nrsol)
{
	for (int i = 0;i < 6;i++)
	{
		steag[k] = culori[i];
		if (acceptabil(k))
		{
			if (solutie(k))
			{
				if (*nrsol >= 0)
				{
					afisare();
					*nrsol -= 1;
				}
			}
			else
			{
				back(k + 1, nrsol);
			}
		}
	}
}

int main(void)
{
	int nrsol = 3;
	back(0, &nrsol);
	return 0;
}