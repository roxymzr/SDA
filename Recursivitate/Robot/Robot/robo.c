#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define BATTERY_INITIAL 5

typedef struct coordonate {
    int linie, coloana;
} coordonate;

coordonate pos[4];
int matrice[MAX][MAX];
int vizitat[MAX][MAX];
int n;
int min_pasi = MAX * MAX;
int baterie;
coordonate start, end;
coordonate teleport[10][2];
int nr_teleport;

void initializare() {
    pos[0].coloana = 0; pos[0].linie = -1;  // N
    pos[1].coloana = 1; pos[1].linie = 0;   // E
    pos[2].coloana = 0; pos[2].linie = 1;   // S
    pos[3].coloana = -1; pos[3].linie = 0;  // V

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            vizitat[i][j] = 0;
        }
    }
}

int solutie(coordonate c) {
    return (c.linie == end.linie && c.coloana == end.coloana);
}

int acceptabil(coordonate c) {
    return (c.linie >= 0 && c.coloana >= 0 && c.linie < n && c.coloana < n && matrice[c.linie][c.coloana] != '*' && !vizitat[c.linie][c.coloana]);
}

void backtracking(coordonate curent, int pasi, int baterie) {
    if (solutie(curent)) {
        if (pasi < min_pasi) {
            min_pasi = pasi;
        }
        return;
    }

    if (baterie <= 0) {
        return;
    }

    vizitat[curent.linie][curent.coloana] = 1;

    for (int i = 0; i < 4; i++) {
        coordonate aux;
        aux.coloana = curent.coloana + pos[i].coloana;
        aux.linie = curent.linie + pos[i].linie;

        if (acceptabil(aux)) {
            int new_baterie = baterie - 1;
            if (matrice[aux.linie][aux.coloana] == '+') {
                new_baterie += 10;
            }
            for (int t = 0; t < nr_teleport; t++) {
                if (aux.linie == teleport[t][0].linie && aux.coloana == teleport[t][0].coloana) {
                    aux = teleport[t][1];
                    break;
                }
                else if (aux.linie == teleport[t][1].linie && aux.coloana == teleport[t][1].coloana) {
                    aux = teleport[t][0];
                    break;
                }
            }
            backtracking(aux, pasi + 1, new_baterie);
        }
    }

    vizitat[curent.linie][curent.coloana] = 0;
}

void citeste_labirint() {
    FILE* file = fopen("mat3.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, " %c", &matrice[i][j]);
            if (matrice[i][j] == 'S') {
                start.linie = i;
                start.coloana = j;
            }
            else if (matrice[i][j] == 'E') {
                end.linie = i;
                end.coloana = j;
            }
            else if (matrice[i][j] >= '0' && matrice[i][j] <= '9') {
                int t = matrice[i][j] - '0';
                if (teleport[t][0].linie == 0 && teleport[t][0].coloana == 0) {
                    teleport[t][0].linie = i;
                    teleport[t][0].coloana = j;
                }
                else {
                    teleport[t][1].linie = i;
                    teleport[t][1].coloana = j;
                    nr_teleport++;
                }
            }
        }
    }

    fclose(file);
}

void scrie_rezultat() {

    if (min_pasi == MAX * MAX) {
        printf("Nu se poate ajunge la destinatie.\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (vizitat[i][j]) {
                    printf("#");
                }
                else {
                    printf("%c", matrice[i][j]);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    initializare();
    citeste_labirint();
    backtracking(start, 0, BATTERY_INITIAL);
    scrie_rezultat();

    return 0;
}
