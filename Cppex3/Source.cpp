#include <iostream>
#include "xyio.h"

//struktura tabelki, sredniej i 
struct DATA {
	int x = 0;
	int y = 0;
	double value = 0;
} data[4][4], sum[4], avg[4];


//wpisanie danych do struct�w 
//podstawowy rozmiar kom�rki :  X = 8 , Y = 2 
void inicjuj() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j].x = 8 + 8 * j;
			data[i][j].y = 2 + 2 * i;
			data[i][j].value = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		sum[i].x = 8 + 8 * i;
		sum[i].y = 12;
		sum[i].value = 0;
		avg[i].x = 8 + 8 * i;
		avg[i].y = 14;
		avg[i].value = 0;
	}
}

//rysowanie pojedynczej komorki. Gora i dol ramki pokrywaj� si� (zaz�biaj�) i rysuj� w tej samej linii co zapewnia
//�e g�ra i d� tableki zostan� naryswoane oraz �e pomi�dzy wierszami jest jedna linia a nie dwie. 
void rysujKomorke(int x, int y, double v) {
	xyprintf(x, y, "#########");

	//sprawdzenie d�ugo�ci wpisanego tekstu aby zajmowa� odpowiedni� ilo�� miejsca
	if (v < 0) {
		if (v > -10) xyprintf(x, y + 1, "|  %.1f |", v);
		else if (v > -100) xyprintf(x, y + 1, "| %.1f |", v);
		else xyprintf(x, y + 1, "| ##### |");
	}
	else {
		if (v < 10) xyprintf(x, y + 1, "|   %.1f |", v);
		else if (v < 100)xyprintf(x, y + 1, "|  %.1f |", v);
		else if (v < 1000)xyprintf(x, y + 1, "| %.1f |", v);
		else xyprintf(x, y + 1, "| ##### |");
	}
	xyprintf(x, y + 2, "#########");
}

//rysowanie kom�rki dla znaku typu char
void rysujKomorke(int x, int y, const char* c) {
	xyprintf(x, y, "#########");
	xyprintf(x, y + 1, "| %s |", c);
	xyprintf(x, y + 2, "#########");
}

//obliczenie sumy i �redniej dla wszystkich kom�rek
void obliczenia() {
	for (int i = 0; i < 4; i++) {
		double suma = 0;
		for (int j = 0; j < 4; j++) {
			suma += data[j][i].value;
		}
		sum[i].value = suma;
		avg[i].value = suma / 4.0;
	}
}


void rysujTabelke() {
	clear();
	obliczenia();

	rysujKomorke(0, 0, " Lp. ");
	rysujKomorke(8, 0, "  A  ");
	rysujKomorke(16, 0, "  B  ");
	rysujKomorke(24, 0, "  C  ");
	rysujKomorke(32, 0, "  D  ");
	rysujKomorke(0, 2, "  1  ");
	rysujKomorke(0, 4, "  2  ");
	rysujKomorke(0, 6, "  3  ");
	rysujKomorke(0, 8, "  4  ");

	//rysowanie kom�rek z warto�ciami z structu data
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rysujKomorke(data[i][j].x, data[i][j].y, data[i][j].value);
		}
	}

	//rysowanie kom�rek dla sumy i �redniej
	rysujKomorke(0, 12, " Sum.");
	rysujKomorke(0, 14, " Sr. ");
	for (int i = 0; i < 4; i++) {
		rysujKomorke(sum[i].x, sum[i].y, sum[i].value);
		rysujKomorke(avg[i].x, avg[i].y, avg[i].value);
	}
}

//walidacja czy wpisano odpowiedni symbol kom�rki 
bool walidacja(char x, char y) {
	if (y != '1' && y != '2' && y != '3' && y != '4') return false;
	if (x != 'A' && x != 'B' && x != 'C' && x != 'D' && x != 'a' && x != 'b' && x != 'c' && x != 'd') return false;
	return true;
}

int main() {

	//inicjalizacja struct�w
	inicjuj();

	char daneWejsciowe[10] = "";
	bool error = false;

	//p�tla g��wna programu
	do {

		rysujTabelke();
		xyprintf(0, 17, "Wpisz wspolrzedne komorki lub K aby zakonczyc dzialanie programu");


		if (error) {
			xyprintf(0, 18, "Podano niepoprawn� warto��. Wpisz ponownie:");
			xyscanf(29, 18, "%s", &daneWejsciowe);
		}
		else {
			xyprintf(0, 18, "Wybor:");
			xyscanf(7, 18, "%s", &daneWejsciowe);
		}

		//walidacja danych wej�ciowych
		if (!walidacja(daneWejsciowe[0], daneWejsciowe[1])) error = true;
		else {
			error = false;

			//ustawienie danych wej�ciowych na kom�rk� tabeli
			int x, y;
			switch (daneWejsciowe[0]) {
			case 'A': x = 0; break;
			case 'B': x = 1; break;
			case 'C': x = 2; break;
			case 'D': x = 3; break;
			case 'a': x = 0; break;
			case 'b': x = 1; break;
			case 'c': x = 2; break;
			case 'd': x = 3; break;
			}
			switch (daneWejsciowe[1]) {
			case '1': y = 0; break;
			case '2': y = 1; break;
			case '3': y = 2; break;
			case '4': y = 3; break;
			}

			//rysowanie kreski w miejscu wybranej kom�rki
			rysujKomorke(data[y][x].x, data[y][x].y, "_____");
			xyscanf(data[y][x].x + 2, data[y][x].y + 1, "%lf", &data[y][x].value);

			for (int i = 0; i < 10; i++) daneWejsciowe[i] = ' ';
		}
	} while (daneWejsciowe[0] != 'k' && daneWejsciowe[0] != 'K');

	return 0;
}