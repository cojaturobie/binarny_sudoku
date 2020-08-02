#include<stdio.h>
#include <stdlib.h>
#include"conio2.h"

#pragma warning(disable : 4996) 

using namespace std;

int ** tab(int **t, int rozm);
int ** pierwsze(int **x, int rozm);
void zwalnianie(int **t, int **r, int rozmiar);


enum obecnosc {
	ZERO, //0
	JEDEN,//1
	NIC   //.
};

void save(int **t, int **r, int rozmiar) {
	remove("save.txt");
	FILE *plik;
	plik = fopen("save.txt", "w");
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (t[i][j] == ZERO&&r[i][j] == 0)fprintf(plik, "%d ", 0);
			else if (t[i][j] == JEDEN && r[i][j] == 0)fprintf(plik, "%d ", 1);
			else if (t[i][j] == NIC && r[i][j] == 0)fprintf(plik, "%d ", 2);
			else if (t[i][j] == ZERO && r[i][j] == 1)fprintf(plik, "%d ", 3);
			else if (t[i][j] == JEDEN && r[i][j] == 1)fprintf(plik, "%d ", 4);
		}
		fprintf(plik, "\n", NULL);
	}
	fclose(plik);
}

void save_r(int rozmiar) {
	remove("rozmiar.txt");
	FILE *plik;
	plik = fopen("rozmiar.txt", "w+");
	fprintf(plik, "%d", rozmiar);
	fclose(plik);
}

int wczytaj_r() {
	int rozmiar;
	FILE *plik;
	plik = fopen("rozmiar.txt", "r");
	fscanf(plik, "%d", &rozmiar);
	return rozmiar;
}

void wczytaj(int **t, int **r, int rozmiar, FILE *plik) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			fscanf(plik, "%d ", &t[i][j]);
		}
		fscanf(plik, "\n", NULL);
	}
	fclose(plik);
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (t[i][j] == 3) {
				r[i][j] = 1;
				t[i][j] = 0;
			}
			else if (t[i][j] == 4) {
				r[i][j] = 1;
				t[i][j] = 1;
			}
		}
	}
}