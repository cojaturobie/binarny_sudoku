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
#define LOS 5 // mo¿na decydowaæ o prawdopodobieñstwu losowania im wiêksza liczba tym n=mniejsza szansa na trafienie 1 i 0

enum obecnosc {
	ZERO, //0
	JEDEN,//1
	NIC   //.
};
void rama(int r);
int ** tab(int **t, int rozm);
void rysuj(int **t, int **r, int rozmiar);
void wpisz(int **t, int x, int y, char zn, int rozmiar, int **r);
int gtoi(char zn);
void losowanie(int **t, int **r, int rozmiar, int procent);
int ** pierwsze(int **x, int rozm);
void nowy(int **t, int **r, int rozmiar);
void zwalnianie(int **t, int **r, int rozmiar);
int ile_kolumna_1(int **t, int rozmiar, int kolumna);
int ile_kolumna_0(int **t, int rozmiar, int kolumna);
int ile_wiersz_1(int **t, int rozmiar, int wiersz);
int ile_wiersz_0(int **t, int rozmiar, int wiersz);
void ile(int **t, int rozmiar);
void zeruj(int **t, int **r, int rozmiar);
void save(int **t, int **r, int rozmiar);
void wczytaj(int **t, int **r, int rozmiar, FILE *plik);
void save_r(int rozmiar);
int wczytaj_r();
bool full(int **t, int rozmiar);


int main() {
	int zn = 0, x = POLE + 1, y = POLE2 + 1, attr = 7, back = 0, zero = 0;
	char txt[32];
	//w³asne zmienne
	int rozmiar = STARTOWY, **pole = NULL;
	int procent;
	int **rand = NULL;
	int zapisany;
	int pozycja_y = 0;
	int pozycja_x = 0;
	char buffor[10];
	//tworzenie pola o podstawowych rozmiarach i tablicy oznaczj¹cej randomowe pola
	pole = tab(pole, rozmiar);
	rand = pierwsze(rand, rozmiar);
	nowy(pole, rand, rozmiar);
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle ustawia tytu³ okienka
	settitle("Jacek Grzybek 165710");
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		gotoxy(LEGENDA, 1);
		cputs("Jacek Grzybek 165710");
		gotoxy(LEGENDA, 2);
		cputs("esc = wyjscie");
		gotoxy(LEGENDA, 3);
		cputs("strzalki = poruszanie");
		gotoxy(LEGENDA, 4);
		cputs("spacja = zmiana koloru");
		gotoxy(LEGENDA, 5);
		cputs("enter = zmiana koloru tla");
		// wypisujemy na ekranie kod ostatnio naciœniêtego klawisza
		if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		gotoxy(LEGENDA, 6);
		cputs(txt);
		//wypisujemy pozycje kursora
		gotoxy(LEGENDA, 7);
		cputs("Pozycja x:");
		gotoxy(LEGENDA, 8);
		itoa(pozycja_x, buffor, 10);
		cputs(buffor);
		gotoxy(LEGENDA, 9);
		cputs("Pozycja y:");
		gotoxy(LEGENDA, 10);
		itoa(pozycja_y, buffor, 10);
		cputs(buffor);
		gotoxy(LEGENDA, 11);
		cputs("'r' zmiana rozmiarów pola gry");
		gotoxy(LEGENDA, 12);
		cputs("'n' nowa gra o domyœlnym polu");
		gotoxy(LEGENDA, 13);
		cputs("'o' losowanie pole");
		gotoxy(LEGENDA, 14);
		cputs("wyœwietlanie iloœci zer/jedynek w kolumnach/wierszach");
		gotoxy(LEGENDA, 15);
		cputs("w,s - zapis i wczytywanie");
		gotoxy(LEGENDA, 16);
		cputs("w,s - zapis i wczytywanie");
		// rysujemy rame i pole ********************************
		ile(pole, rozmiar);
		rama(rozmiar);
		rysuj(pole, rand, rozmiar);
		//kursor
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		putch('*');
		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == 0x48 && pozycja_y != 0) {
				y--;
				pozycja_y--;
			}
			else if (zn == 0x50 && pozycja_y != rozmiar - 1) {
				y++;
				pozycja_y++;
			}
			else if (zn == 0x4b && pozycja_x != 0) {
				x--;
				pozycja_x--;
			}
			else if (zn == 0x4d && pozycja_x != rozmiar - 1) {
				x++;
				pozycja_x++;
			}
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;
		//wpisanie wartoœci do tablicy pole
		else if (zn == '0' || zn == '1')wpisz(pole, pozycja_x, pozycja_y, zn, rozmiar, rand);
		//zmiana rozmiaru
		else if (zn == 'r') {
			zwalnianie(pole, rand, rozmiar);
			rozmiar = gtoi(zn);
			procent = gtoi(zn);
			pole = tab(pole, rozmiar);
			rand = pierwsze(rand, rozmiar);
			losowanie(pole, rand, rozmiar, procent);
		}
		else if (zn == 'n') {
			zwalnianie(pole, rand, rozmiar);
			rozmiar = STARTOWY;
			pole = tab(pole, rozmiar);
			rand = pierwsze(rand, rozmiar);
			nowy(pole, rand, rozmiar);
		}
		else if (zn == 'o') {
			procent = gtoi(zn);
			losowanie(pole, rand, rozmiar, procent);
		}
		else if (zn == 'c')zeruj(pole, rand, rozmiar);
		else if (zn == 's') {
			save_r(rozmiar);
			save(pole, rand, rozmiar);
		}
		else if (zn == 'w') {
			zwalnianie(pole, rand, rozmiar);
			rozmiar = wczytaj_r();
			pole = tab(pole, rozmiar);
			rand = pierwsze(rand, rozmiar);
			wczytaj(pole, rand, rozmiar, fopen("save.txt", "r"));
		}
	} while (zn != 27);
	zwalnianie(pole, rand, rozmiar);
	return 0;
}















