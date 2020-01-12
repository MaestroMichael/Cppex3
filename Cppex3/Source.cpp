#include <iostream>
#include "xyio.h"

#define STARTX 20
#define STARTY 3

struct DATA {
	int x = 0;
	int y = 0;
	double value = 0;
} data[4][4], sum[4], avg[4];

void init() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j].x = STARTX + 8 + 8 * j;
			data[i][j].y = STARTY + 2 + 2 * i;
			data[i][j].value = j + i * 4;
		}
	}

	for (int i = 0; i < 4; i++) {
		sum[i].x = STARTX + 8 + 8 * i;
		sum[i].y = STARTY + 12;
		sum[i].value = 0;
		avg[i].x = STARTX + 8 + 8 * i;
		avg[i].y = STARTY + 14;
		avg[i].value = 0;
	}
}

void showCell(int x, int y, double v) {
	xyprintf(x, y, "*********");

	if (v < 0) {
		if (v > -10) xyprintf(x, y + 1, "*  %.1f *", v);
		else if (v > -100) xyprintf(x, y + 1, "* %.1f *", v);
		else xyprintf(x, y + 1, "* ##### *");
	}
	else {
		if (v < 10) xyprintf(x, y + 1, "*   %.1f *", v);
		else if (v < 100)xyprintf(x, y + 1, "*  %.1f *", v);
		else if (v < 1000)xyprintf(x, y + 1, "* %.1f *", v);
		else xyprintf(x, y + 1, "* ##### *");
	}
	xyprintf(x, y + 2, "*********");
}

void showCell(int x, int y, const char* c) {
	xyprintf(x, y, "*********");
	xyprintf(x, y + 1, "* %s *", c);
	xyprintf(x, y + 2, "*********");
}

void recalculate() {
	for (int i = 0; i < 4; i++) {
		double s = 0;
		for (int j = 0; j < 4; j++) {
			s += data[j][i].value;
		}
		sum[i].value = s;
		avg[i].value = s / 4.0;
	}
}

void showTabble() {
	clear();
	recalculate();

	showCell(STARTX + 0, STARTY + 0, " Lp. ");
	showCell(STARTX + 8, STARTY + 0, "  A  ");
	showCell(STARTX + 16, STARTY + 0, "  B  ");
	showCell(STARTX + 24, STARTY + 0, "  C  ");
	showCell(STARTX + 32, STARTY + 0, "  D  ");
	showCell(STARTX + 0, STARTY + 2, "  1  ");
	showCell(STARTX + 0, STARTY + 4, "  2  ");
	showCell(STARTX + 0, STARTY + 6, "  3  ");
	showCell(STARTX + 0, STARTY + 8, "  4  ");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			showCell(data[i][j].x, data[i][j].y, data[i][j].value);
		}
	}

	showCell(STARTX + 0, STARTY + 12, " Sum.");
	showCell(STARTX + 0, STARTY + 14, " Sr. ");
	for (int i = 0; i < 4; i++) {
		showCell(sum[i].x, sum[i].y, sum[i].value);
		showCell(avg[i].x, avg[i].y, avg[i].value);
	}
}

bool validate(char x, char y) {
	if (y != '1' && y != '2' && y != '3' && y != '4') return false;
	if (x != 'A' && x != 'B' && x != 'C' && x != 'D') return false;
	return true;
}

int main() {

	init();

	char choose[10] = "";
	bool error = false;

	do {

		showTabble();
		xyprintf(STARTX, STARTY + 17, "Podaj XY komorki do edycji lub [K]oniec");
		if (error) {
			xyprintf(STARTX, STARTY + 18, "[Niepoprawna wartosc] Wybor:");
			xyscanf(STARTX + 29, STARTY + 18, "%s", &choose);
		}
		else {
			xyprintf(STARTX, STARTY + 18, "Wybor:");
			xyscanf(STARTX + 7, STARTY + 18, "%s", &choose);
		}

		if (!validate(choose[0], choose[1])) error = true;
		else {
			error = false;

			int x, y;
			switch (choose[0]) {
			case 'A': x = 0; break;
			case 'B': x = 1; break;
			case 'C': x = 2; break;
			case 'D': x = 3; break;
			}
			switch (choose[1]) {
			case '1': y = 0; break;
			case '2': y = 1; break;
			case '3': y = 2; break;
			case '4': y = 3; break;
			}

			showCell(data[y][x].x, data[y][x].y, "_____");
			xyscanf(data[y][x].x + 2, data[y][x].y + 1, "%lf", &data[y][x].value);

			for (int i = 0; i < 10; i++) choose[i] = ' ';
		}
	} while (choose[0] != 'k' && choose[0] != 'K');

	return 0;
}