#include<stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)  


using namespace std;

void wczytaj(int **t, int **r, int rozmiar, FILE *plik);

enum obecnosc {
	ZERO, //0
	JEDEN,//1
	NIC   //.
};

//tworzenie tablicy dwuwymiarowej
int ** tab(int **t, int rozm) {
	t = (int **)malloc(rozm * sizeof(int));
	for (int i = 0; i < rozm; i++) {
		t[i] = (int *)malloc(rozm * sizeof(int*));
	}
	for (int i = 0; i < rozm; i++) {
		for (int j = 0; j < rozm; j++) {
			t[i][j] = NIC;
		}
	}
	return t;
}

int ** pierwsze(int **x, int rozm) {
	x = (int **)malloc(rozm * sizeof(int));
	for (int i = 0; i < rozm; i++) {
		x[i] = (int *)malloc(rozm * sizeof(int));
	}
	for (int i = 0; i < rozm; i++) {
		for (int j = 0; j < rozm; j++) {
			x[i][j] = 0;
		}
	}
	return x;
}

void zwalnianie(int **t, int **r, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		free(t[i]);
		free(r[i]);
	}
	free(t);
	free(r);
}

void nowy(int **t, int **r, int rozmiar) {
	wczytaj(t, r, rozmiar, fopen("nowy.txt", "r"));
}

void zeruj(int **t, int **r, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			t[i][j] = NIC;
			r[i][j] = 0;
		}
	}
}
