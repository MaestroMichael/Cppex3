#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#ifdef UNICODE

#undef UNICODE
#define _MBCS

#endif

#ifndef __cplusplus

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#else

#include <cstdlib>
#include <cstdio>
#include <cstdarg>

#endif

#include <windows.h>

#ifndef __XYIO_H_
#define __XYIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
	/* brak implementacji przed VC++ 12 (VS 2013) */
	static int vsscanf(const char* s, const char* fmt, va_list ap);
#endif

	int xyscanf(int x, int y, const char* format, ...);
	int xyprintf(int x, int y, const char* format, ...);
	void setcursor(int x, int y);
	void getcursor(int* x, int* y);
	void getscreen(int* xorg, int* yorg, int* xend, int* yend);
	void getrange(int* maxx, int* maxy);
	void clear(void);

#ifdef __cplusplus
}
#endif

#endif