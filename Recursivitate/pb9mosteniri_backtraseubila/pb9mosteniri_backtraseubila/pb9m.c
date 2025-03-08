#include <stdio.h>

#define N 4 // numărul de coloane
#define M 3 // numărul de linii

typedef struct coordonate {
    int linie, coloana;
} coordonate;

coordonate pos[4];
int vizitat[M][N];
coordonate a[M * N];  // pentru a stoca drumul curent
int lungime_curenta;

int matrice[M][N] = { {16, 23, 12, 20},
                      {4, 5, 9, 30},
                      {3, 2, 1, 19} };

void initializare() {
    pos[0].coloana = 0; pos[0].linie = -1;  // N
    pos[1].coloana = 1; pos[1].linie = 0;   // E
    pos[2].coloana = 0; pos[2].linie = 1;   // S
    pos[3].coloana = -1; pos[3].linie = 0;  // V

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            vizitat[i][j] = 0;
        }
    }
}

int solutie(coordonate c) {
    return (c.coloana < 0 || c.linie < 0 || c.coloana >= N || c.linie >= M);
}

int acceptabil(coordonate c, int k) {
    return (matrice[c.linie][c.coloana] < k && c.linie >= 0 && c.coloana >= 0 && c.linie < M && c.coloana < N);
}

void afiseaza_drum(int k) {
    for (int i = 0; i < k; i++) {
        printf("pas %d = %d-%d\n", i, a[i].linie, a[i].coloana);
    }
    printf("\n");
}

void labirint(int linie, int coloana, int k, int q) {
    vizitat[linie][coloana] = 1;
    a[k].linie = linie;
    a[k].coloana = coloana;
    lungime_curenta++;

    if (solutie(a[k])) {
        afiseaza_drum(k);
    }
    else {
        for (int i = 0; i < 4; i++) {
            coordonate aux;
            aux.coloana = coloana + pos[i].coloana;
            aux.linie = linie + pos[i].linie;
            if (acceptabil(aux, q) && !vizitat[aux.linie][aux.coloana]) {
                labirint(aux.linie, aux.coloana, k + 1, matrice[aux.linie][aux.coloana]);
            }
        }
    }
    vizitat[linie][coloana] = 0;
    lungime_curenta--;
}

void determina_drumuri(int linie, int coloana) {
    lungime_curenta = 0;
    labirint(linie, coloana, 0, matrice[linie][coloana]);
}

int main()
{
    initializare();
    int linie_initiala = 0;
    int coloana_initiala=1;
    determina_drumuri(linie_initiala, coloana_initiala);
    return 0;
}
