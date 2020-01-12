

#include "xyio.h"

void setcursor(int x, int y)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD punkt = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(ekran, punkt);
}

void getcursor(int* x, int* y)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*x = bufor.dwCursorPosition.X;
	*y = bufor.dwCursorPosition.Y;
}

void getrange(int* maxx, int* maxy)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*maxx = bufor.dwMaximumWindowSize.X;
	*maxy = bufor.dwMaximumWindowSize.Y;
}

void getscreen(int* xorg, int* yorg, int* xend, int* yend)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*xorg = bufor.srWindow.Left;
	*yorg = bufor.srWindow.Top;
	*xend = bufor.srWindow.Right;
	*yend = bufor.srWindow.Bottom;
}

int xyscanf(int x, int y, const char* format, ...)
{
	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	setcursor(x, y);
	sukces = ReadConsole(klawiatura, tekst, 150, &znaki, NULL);
	if (!sukces) rezultat = EOF;
	else {
		while (znaki > 0 && (tekst[znaki - 1] == '\n' || tekst[znaki - 1] == '\r')) znaki--;
		tekst[znaki] = '\0';
		rezultat = vsscanf(tekst, format, argumenty);
	}
	va_end(argumenty);
	return rezultat;
}

int xyprintf(int x, int y, const char* format, ...)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	rezultat = vsprintf(tekst, format, argumenty);
	if (rezultat >= 0) {
		znaki = (DWORD)rezultat;
		setcursor(x, y);
		sukces = WriteConsole(ekran, tekst, znaki, NULL, NULL);
		if (!sukces) rezultat = EOF;
	}
	va_end(argumenty);
	return rezultat;
}

void clear(void)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}

#if defined(_MSC_VER) && (_MSC_VER < 1800)
static int vsscanf(const char* buffer, const char* format, va_list argPtr)
{
	void* a[10];
	int i;
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		a[i] = va_arg(argPtr, void*);
	return sscanf(buffer, format, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
}
#endif