#include<stdio.h>
#include <stdlib.h>

using namespace std;

int ile_kolumna_1(int **t, int rozmiar, int kolumna) {
	int ile = 0;
	for (int i = 0; i<rozmiar; i++) {
		if (t[kolumna][i] == 1)ile++;
	}
	return ile;
}

int ile_kolumna_0(int **t, int rozmiar, int kolumna) {
	int ile = 0;
	for (int i = 0; i<rozmiar; i++) {
		if (t[kolumna][i] == 0)ile++;
	}
	return ile;
}

int ile_wiersz_1(int **t, int rozmiar, int wiersz) {
	int ile = 0;
	for (int i = 0; i<rozmiar; i++) {
		if (t[i][wiersz] == 1)ile++;
	}
	return ile;
}

int ile_wiersz_0(int **t, int rozmiar, int wiersz) {
	int ile = 0;
	for (int i = 0; i<rozmiar; i++) {
		if (t[i][wiersz] == 0)ile++;
	}
	return ile;
}