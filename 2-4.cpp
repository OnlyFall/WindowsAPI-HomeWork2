#include <Windows.h>
#include <random>
#include <stdio.h>
#include <time.h>
#define Height 1024
#define Weight 768

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows Programing";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, "window progra1-2", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 100, 50, Height, Weight, NULL, (HMENU)NULL, hInstance, NULL);
	int x = 800;
	int y = 600;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
bool isDown[9] = { false };

int isDownCount[9] = { 0 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	char test[50];
	static char str;
	default_random_engine dre;
	uniform_int_distribution <> uid(1, 255);
	srand((unsigned int)time(NULL));
	int red = rand() % 256;
	int blue = rand() % 256;;
	int green = rand() % 256;;
	int x = 0, y = 0;

	switch (iMessage) {
	case WM_CHAR:
		hDC = GetDC(hWnd);
		str = wParam - 48;
		//a[str-1].red = 255 - (rand() % 255);
		//a[str-1].blue = 255 - (rand() % 255);
		//a[str-1].green = 255 - (rand() % 255);

		isDown[str - 1] = true;
		switch (str)
		{
		case 1:
			for (int i = 0; i <9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 1, i + 1, (i + 1) * 1);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 0 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 2:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 2, i + 1, (i + 1) * 2);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 1 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 3:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 3, i + 1, (i + 1) * 3);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 2 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 4:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 4, i + 1, (i + 1) * 4);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 3 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 5:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 5, i + 1, (i + 1) * 5);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 4 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 6:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 6, i + 1, (i + 1) * 6);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 5 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 7:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 7, i + 1, (i + 1) * 1);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 6 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 8:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 8, i + 1, (i + 1) * 1);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 7 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		case 9:
			for (int i = 0; i<9; ++i)
				wsprintf(test, TEXT("%2d x %2d = %3d"), 9, i + 1, (i + 1) * 1);
			SetBkColor(hDC, RGB(red, green, blue));
			for (int i = 0; i < 9; ++i)
				TextOut(hDC, 8 * (Height / 10), i * (Weight / 9), test, strlen(test));
			break;
		}

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}