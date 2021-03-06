#include "stdafx.h"
#include "TOKEN.h"
#include <windows.h>
#define _WIN32_WINNT 0x0500
using namespace std;

void draw(HWND hwnd, HDC hdc, int i1 = 110, int i2 = 150, int i3 = 550, int i4 = 590);
void graph(HWND hwnd, HDC hdc, int i1 = 110, int i2 = 150, int i3 = 550, int i4 = 590);
void setConsoleSize();
int key = 1;

int main(){
	system("color F0");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	setConsoleSize();
	SetConsoleTitle(L"Graph");
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //block of changing size
	SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY |FOREGROUND_INTENSITY | 13);
	SetBkColor(hdc, RGB(0, 255, 255)); 
	Sleep(100);
	draw(hwnd, hdc);

	cout << "  This is a program for plotting a function."<<endl;
	cout << "  Allowed operations : +, -, *, / , %, ^, sin(), cos(), tan(x), ctan(x)."<<endl;
	cout << "  To see the graph press ENTER" << endl;
	cout << "  Enter the function: y(x) = ";
	getline(cin, s); s += ';';
	
	graph(hwnd, hdc);
	cout << "   ***If you want to build another chart, press "; 
	SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY | 4); cout << "ENTER" << endl;
	SetConsoleTextAttribute(h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | 13);
	cout << "   ***To exit press ";
		SetConsoleTextAttribute(h,BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY| 4); cout << "ESC";
		while (key != 13 || key != 27) {
			if (_kbhit()) {
				key = _getch();
				if (key == 27) exit(0);
				if (key == 13) {
					system("cls");
					main();
				}
			}
	}
	_getch();
	ReleaseDC(NULL, hdc);
	return 0;
}

void draw(HWND hwnd, HDC hdc, int i1 , int i2 , int i3, int i4 ) {
	Rectangle(hdc, i1, i2, i3, i4);
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, i1, i2, NULL);
	LineTo(hdc, i3, i2);
	LineTo(hdc, i3, i4);
	LineTo(hdc, i1, i4);
	LineTo(hdc, i1, i2);
	MoveToEx(hdc, (i1 + i3) / 2, i2, NULL);
	LineTo(hdc, (i1 + i3) / 2, i4);
	MoveToEx(hdc, i1, (i2+i4)/2, NULL);
	LineTo(hdc, i3, (i2 + i4) / 2);
	DeleteObject(Pen);
};

void graph(HWND hwnd, HDC hdc, int i1, int i2, int i3, int i4) {
	double x , y = -228, z;
	int a = (i1 + i3) / 2, b = (i4 + i2) / 2, c = (i4 - i2) / 2, d = (i1 - i3) / 2;
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
	SelectObject(hdc, Pen); 
	x = d;
	while (y <= b - i4 || y >= b - i2) {
		y = calculate(x);
		MoveToEx(hdc, x + a, b - y, NULL);
		x+=0.1;
	} z = y;
	for (; x < -d; x+=0.1) {
		y = calculate(x); 
			while ((y < b - i4 || y > b - i2) && (x<-d)) {
				y = calculate(x);
				MoveToEx(hdc, x + a, b - y, NULL);
				x++;
			}
		if ( (z>0 && y<=0) || (z>=0 && y<0) || (z<=0 && y > 0) || (z < 0 && y >= 0)) MoveToEx(hdc, x + a, b - y, NULL);
		if (y > b-i4  && y < b-i2) {
			LineTo(hdc, (int)x + a, b - y);
		}
		z = y;
	};
}

void setConsoleSize() {
	const int colConsole = 73;
	const int rowConsole = 35;
	HANDLE hNdl = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = { 0,0,colConsole - 1, rowConsole - 1 };
	SetConsoleWindowInfo(hNdl, TRUE, &windowSize);
	COORD bufferSize = { colConsole, rowConsole };
	SetConsoleScreenBufferSize(hNdl, bufferSize);
}

