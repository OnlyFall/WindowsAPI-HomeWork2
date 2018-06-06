#include <Windows.h>
#include <iostream>
#include <random>

#define Height 800
#define Weight 600

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows Programing KWB";

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	char test[50];
	default_random_engine dre;
	uniform_int_distribution <> uid(1, 255);
	int x = 0, y = 0;
	switch (iMessage) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int j = 0; j < MAX; j++)
		{
			for (int i = 0; i < MAX; i++)
			{
				wsprintf(test, TEXT("%2d x %2d = %3d"), j + 1, i + 1, (i + 1)*(j + 1));
				SetBkColor(hDC, RGB(uid(dre), uid(dre), uid(dre)));
				TextOut(hDC, j * (Height / 10), i * (Weight / 9), test, strlen(test));
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}