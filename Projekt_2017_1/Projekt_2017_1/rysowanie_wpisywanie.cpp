#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include"conio2.h"

#pragma warning(disable : 4996)  

//ustawienie pozycji legendy, pola gry i rozmiarów
#define LEGENDA 1 // pozycja legendy na osi y
#define POLE 58  // pozycja pola na osi y
#define POLE2 5   // pozycja pola na osi x
#define STARTOWY 12 // pocz¹tkowe rozmiary pola gry


int ile_kolumna_1(int **t, int rozmiar, int kolumna);
int ile_kolumna_0(int **t, int rozmiar, int kolumna);
int ile_wiersz_1(int **t, int rozmiar, int wiersz);
int ile_wiersz_0(int **t, int rozmiar, int wiersz);

enum obecnosc {
	ZERO, //0
	JEDEN,//1
	NIC   //.
};

//rysowanie ramki wokó³ pola gry
void rama(int rozm) {
	int rozmiar = rozm + 2;
	for (int i = POLE; i < POLE + rozmiar; i++) {
		for (int j = POLE2; j < POLE2 + rozmiar; j++) {
			if (i == POLE || i == POLE + rozmiar - 1 || j == POLE2 || j == POLE2 + rozmiar - 1) {
				gotoxy(i, j);
				textbackground(BLUE);
				cputs(" ");
			}
		}
	}
}

void ile(int **t, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (j == 0) {
				gotoxy(POLE + 1 + i, POLE2 - 1);
				char x[10];
				itoa(ile_kolumna_0(t, rozmiar, i), x, 10);
				textcolor(LIGHTGREEN);
				if (ile_kolumna_0(t, rozmiar, i) > rozmiar / 2)textcolor(LIGHTRED);
				cputs(x);
			}
			else if (j == rozmiar - 1) {
				gotoxy(POLE + 1 + i, POLE2 + rozmiar + 2);
				char x[10];
				itoa(ile_kolumna_1(t, rozmiar, i), x, 10);
				textcolor(LIGHTGREEN);
				if (ile_kolumna_1(t, rozmiar, i) > rozmiar / 2)textcolor(LIGHTRED);
				cputs(x);
			}
			if (i == 0) {
				gotoxy(POLE - 1, POLE2 + j + 1);
				char x[10];
				itoa(ile_wiersz_0(t, rozmiar, j), x, 10);
				textcolor(LIGHTGREEN);
				if (ile_wiersz_0(t, rozmiar, j) > rozmiar / 2)textcolor(LIGHTRED);
				cputs(x);
			}
			else if (i == rozmiar - 1) {
				gotoxy(POLE + rozmiar + 2, POLE2 + j + 1);
				char x[10];
				itoa(ile_wiersz_1(t, rozmiar, j), x, 10);
				textcolor(LIGHTGREEN);
				if (ile_wiersz_1(t, rozmiar, j) > rozmiar / 2)textcolor(LIGHTRED);
				cputs(x);
			}
		}
	}
}

//rysowanie pola gry
void rysuj(int **t, int **r, int rozmiar) {
	textcolor(WHITE);
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			gotoxy(i + POLE + 1, j + POLE2 + 1);
			if (t[i][j] == JEDEN && r[i][j] == 1) {
				textcolor(LIGHTCYAN);
				textbackground(BLACK);
				cputs("1");
			}
			else if (t[i][j] == JEDEN && r[i][j] == false) {
				textbackground(BLACK);
				textcolor(WHITE);
				cputs("1");
			}
			else if (t[i][j] == ZERO && r[i][j] == 1) {
				textcolor(LIGHTCYAN);
				textbackground(BLACK);
				cputs("0");
			}
			else if (t[i][j] == ZERO && r[i][j] == false) {
				textbackground(BLACK);
				textcolor(WHITE);
				cputs("0");
			}
			else if (t[i][j] == NIC) {
				textbackground(BLACK);
				textcolor(WHITE);
				cputs(".");
			}
		}
	}
}

//wpisanie wartoœci do tablicy w miejscu wyznaczonym przez po³o¿enie kursora x,y po³¹czone z piwresz¹ zasad¹ gry
void wpisz(int **t, int x, int y, char zn, int rozmiar, int **r) {
	if (r[x][y] != 1) {
		if (zn == '1') {
			//sprwdzianie po wierszach
			if ((y - 2 >= 0 && t[x][y - 2] == JEDEN && t[x][y - 1] == JEDEN) || (y - 1 >= 0 && y + 1 < rozmiar && t[x][y - 1] == JEDEN && t[x][y + 1] == JEDEN) || (y + 2 < rozmiar && t[x][y + 1] == JEDEN && t[x][y + 2] == JEDEN)) {
				textbackground(BLACK);
				clrscr();
				textcolor(7);
				gotoxy(55, 1);
				cputs("nie mo¿na wpisaæ liczby");
			}
			//sprawdzanie po kolumncah
			else if ((x - 2 >= 0 && t[x - 2][y] == JEDEN && t[x - 1][y] == JEDEN) || (x - 1 >= 0 && x + 1 < rozmiar&& t[x - 1][y] == JEDEN && t[x + 1][y] == JEDEN) || (x + 2 < rozmiar && t[x + 1][y] == JEDEN && t[x + 2][y] == JEDEN)) {
				textbackground(BLACK);
				clrscr();
				textcolor(7);
				gotoxy(1, 20);
				cputs("nie mo¿na wpisaæ liczby");
			}
			else t[x][y] = JEDEN;
		}
		else if (zn == '0') {
			//sprawdzanie po wierszach
			if ((y - 2 >= 0 && t[x][y - 2] == ZERO && t[x][y - 1] == ZERO) || (y - 1 >= 0 && y + 1 < rozmiar && t[x][y - 1] == ZERO && t[x][y + 1] == ZERO) || (y + 2 < rozmiar && t[x][y + 1] == ZERO && t[x][y + 2] == ZERO)) {
				textbackground(BLACK);
				clrscr();
				textcolor(7);
				gotoxy(1, 20);
				cputs("nie mo¿na wpisaæ liczby");
			}
			//sprawdzanie po kolumnach
			else if ((x - 2 >= 0 && t[x - 2][y] == ZERO && t[x - 1][y] == ZERO) || (x - 1 >= 0 && x + 1 < rozmiar&& t[x - 1][y] == ZERO && t[x + 1][y] == ZERO) || (x + 2 < rozmiar && t[x + 1][y] == ZERO && t[x + 2][y] == ZERO)) {
				textbackground(BLACK);
				clrscr();
				textcolor(7);
				gotoxy(1, 20);
				cputs("nie mo¿na wpisaæ liczby");
			}
			else t[x][y] = ZERO;
		}
	}
}


//gtoi oznacza ¿e poœrednio przez zmienn¹ char o rozmiarze 10 zmieniamy z getch na int
int gtoi(char zn) {
	char x[10];
	int i = 0;
	while (zn != 13) {
		zn = getch();
		if (zn == '0' || zn == '1' || zn == '2' || zn == '3' || zn == '4' || zn == '5' || zn == '6' || zn == '7' || zn == '8' || zn == '9') { //wpicujemy tylko cyfry
			x[i] = zn;
			i++;
		}
	}
	int liczba = atoi(x);
	if (liczba % 2 == 0)return liczba;
	else return liczba + 1;
}