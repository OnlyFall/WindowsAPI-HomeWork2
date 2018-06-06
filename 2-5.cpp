#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h>
#define Height 1280
#define Weight 720

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
static char str;
int p = 0, position[100];
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	static TCHAR stra[100][100] = { NULL };
	static TCHAR CARET[100][100];
	ShowCaret(hWnd);
	static int x = 0;
	static int y = 0;
	static char str;
	static int line = 80;
	static SIZE size;
	for (int i = 0; i < 80; ++i)
		for (int j = 0; j < 80; ++j)
			stra[i][j] = 'a';

	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 7, 20);
		SetCaretPos(x += 8, y);
		ShowCaret(hWnd);
		return 0;
	case WM_CHAR:
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_LEFT)
			SetCaretPos(x -= 8, y);
		else if (wParam == VK_RIGHT)
			SetCaretPos(x += 8, y);
		else if (wParam == VK_UP)
			SetCaretPos(x, y -= 20);
		else if (wParam == VK_DOWN)
			SetCaretPos(x, y += 20);
		else if (wParam == VK_RETURN)
			SetCaretPos(x, y += 20);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i <= line; i++)
			TextOut(hDC, 0, i * 20, stra[i], lstrlen(stra[i]));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}
