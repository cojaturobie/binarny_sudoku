#include<stdio.h>
#include<time.h>
#include<cstdlib>

#define LOS 100 // mo¿na decydowaæ o prawdopodobieñstwu losowania im wiêksza liczba tym n=mniejsza szansa na trafienie 1 i 0


int ile_kolumna_1(int **t, int rozmiar, int kolumna);
int ile_kolumna_0(int **t, int rozmiar, int kolumna);
int ile_wiersz_1(int **t, int rozmiar, int wiersz);
int ile_wiersz_0(int **t, int rozmiar, int wiersz);

enum obecnosc {
	ZERO, //0
	JEDEN,//1
	NIC   //.
};



//losowanie polega na przydzieleniu ka¿emu z pól jakieœ wartoœci jeœli nie bêdzie przekoroczona zadsada gry
void losowanie(int **t, int **r, int rozmiar, int procent) {
	srand(time(NULL));
	for (int x = 0; x < rozmiar; x++) {
		for (int y = 0; y < rozmiar; y++) {
			int a;
			t[x][y] = NIC;
			a = rand() % LOS;
			if (a < procent) {
				if (((y - 2 >= 0 && t[x][y - 2] == JEDEN && t[x][y - 1] == JEDEN) || (y - 1 >= 0 && y + 1 < rozmiar && t[x][y - 1] == JEDEN && t[x][y + 1] == JEDEN) || (y + 2 < rozmiar && t[x][y + 1] == JEDEN && t[x][y + 2] == JEDEN)));
				else if (((x - 2 >= 0 && t[x - 2][y] == JEDEN && t[x - 1][y] == JEDEN) || (x - 1 >= 0 && x + 1 < rozmiar&& t[x - 1][y] == JEDEN && t[x + 1][y] == JEDEN) || (x + 2 < rozmiar && t[x + 1][y] == JEDEN && t[x + 2][y] == JEDEN)));
				else if (ile_wiersz_1(t, rozmiar, y) == rozmiar / 2 || ile_kolumna_1(t, rozmiar, x) == rozmiar / 2);
				else {
					t[x][y] = JEDEN;
					r[x][y] = 1;
				}
			}
			else if (a > procent) {
				if (((y - 2 >= 0 && t[x][y - 2] == ZERO && t[x][y - 1] == ZERO) || (y - 1 >= 0 && y + 1 < rozmiar && t[x][y - 1] == ZERO && t[x][y + 1] == ZERO) || (y + 2 < rozmiar && t[x][y + 1] == ZERO && t[x][y + 2] == ZERO)));
				else if (((x - 2 >= 0 && t[x - 2][y] == ZERO && t[x - 1][y] == ZERO) || (x - 1 >= 0 && x + 1 < rozmiar&& t[x - 1][y] == ZERO && t[x + 1][y] == ZERO) || (x + 2 < rozmiar && t[x + 1][y] == ZERO && t[x + 2][y] == ZERO)));
				else if (ile_wiersz_0(t, rozmiar, y) == rozmiar / 2 || ile_kolumna_0(t, rozmiar, x) == rozmiar / 2);
				else {
					t[x][y] = ZERO;
					r[x][y] = 1;
				}
			}
			else t[x][y] = NIC;
		}
	}
}